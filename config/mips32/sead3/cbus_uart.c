/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2000-2003 by Industrial Technology Institute,
 *                              Miyagi Prefectural Government, JAPAN
 *  Copyright (C) 2007-     by Monami Software Limited Partnership, JAPAN
 * 
 *  上記著作権者は，以下の (1)〜(4) の条件か，Free Software Foundation 
 *  によって公表されている GNU General Public License の Version 2 に記
 *  述されている条件を満たす場合に限り，本ソフトウェア（本ソフトウェア
 *  を改変したものを含む．以下同じ）を使用・複製・改変・再配布（以下，
 *  利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *      の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
 *      と．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *        作権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *        報告すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 * 
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，その適用可能性も
 *  含めて，いかなる保証も行わない．また，本ソフトウェアの利用により直
 *  接的または間接的に生じたいかなる損害に関しても，その責任を負わない．
 * 
 */

#include <cbus_uart.h>

/*
 *	CBUS UART (tty2)用 簡易SIOドライバ
 */

/*
 *  シリアルI/Oポート初期化ブロックの定義
 */
typedef struct sio_port_initialization_block {
	VP	channel_addr;	/* シリアルポートの開始番地 */

	UB	lcr_def;	/* LCR設定値 b0-b6;
				(送受信ビット数、ストップビット，パリティ) */
	UB	scr_def;	/* SCR設定値（プリスケーラ；）*/
	UB	boud_hi_def;	/* DLM設定値（ボーレート上位の設定値） */
	UB	boud_lo_def;	/* DLL設定値（ボーレート下位の設定値） */
} SIOPINIB;

/*
 *  シリアルI/Oポート管理ブロックの定義
 */
struct sio_port_control_block {
	const SIOPINIB	*siopinib;	/* シリアルI/Oポート初期化ブロック */
	VP_INT		exinf;		/* 拡張情報 */
	BOOL		openflag;	/* オープン済みフラグ */
	BOOL		getready;	/* 文字を受信した状態 */
	BOOL		putready;	/* 文字を送信できる状態 */
};

/*
 *  シリアルI/Oポート初期化ブロック
 *    ID = 1 をポート1に対応させている．
 */
const SIOPINIB siopinib_table[TNUM_SIOP] = {
	{ (VP)  UART_CH01,
	  (UB)	WORD_LENGTH_8 | STOP_BITS_1 | PARITY_NON,
	  (UB)	PRE_DIVISOR,
	  (UB)	HI8(DIVISOR),
	  (UB)	LO8(DIVISOR) },
};

/*
 *  シリアルI/Oポート初期化ブロックの取出し
 */
#define INDEX_SIOPINIB(siopid)	((UINT)((siopid) - 1))
#define get_siopinib(siopid)	(&(siopinib_table[INDEX_SIOPINIB(siopid)]))


/*
 *  シリアルI/Oポート管理ブロックのエリア
 */
SIOPCB	siopcb_table[TNUM_SIOP];

/*
 *  シリアルI/OポートIDから管理ブロックを取り出すためのマクロ
 */
#define INDEX_SIOP(siopid)	((UINT)((siopid) - 1))
#define get_siopcb(siopid)	(&(siopcb_table[INDEX_SIOP(siopid)]))

/*
 *  SIO用レジスタ操作関数
 */
Inline void
cbus_uart_orb( VP addr, UW reg, UB val )
{
	cbus_uart_wrb( addr, reg, cbus_uart_reb( addr, reg ) | val );
}

Inline void
cbus_uart_andb( VP addr, UW reg, UB val )
{
	cbus_uart_wrb( addr, reg, cbus_uart_reb( addr, reg ) & val );
}


/*
 *  状態の読出し（IIRの読出し）
 */
static void
cbus_uart_get_stat(SIOPCB *siopcb)
{
	UB	iir;

	iir = cbus_uart_reb( siopcb->siopinib->channel_addr, IIR) & INT_MASK;

	switch( iir ) {
		case INT_TRANS_EMPTY :
			siopcb->putready = TRUE;
			break;
		case INT_RECEIVE_DATA :
		case INT_CHAR_TIME_OUT :
			siopcb->getready = TRUE;
			break;
		default :
			break;
	}

}

/*
 *  文字を受信できるか？
 */
Inline BOOL
cbus_uart_getready(SIOPCB *siopcb)
{
	return(siopcb->getready);
}

/*
 *  文字を送信できるか？
 */
Inline BOOL
cbus_uart_putready(SIOPCB *siopcb)
{
	return(siopcb->putready);
}

/*
 *  受信した文字の取出し
 */
Inline char
cbus_uart_getchar(SIOPCB *siopcb)
{
	siopcb->getready = FALSE;
	return((char) cbus_uart_reb( siopcb->siopinib->channel_addr, RBR ));
	/* 1byte 単位での文字の取り出しを行ったいるため、cbus_uart_opn_por内の
	   受信バッファ設定を増やしたとしても性能の向上は見られない。
	   性能の向上には、バッファ全体のブロック転送を行うなどの修正が必要。*/
}

/*
 *  送信する文字の書込み
 */
Inline void
cbus_uart_putchar(SIOPCB *siopcb, char c)
{
	siopcb->putready = FALSE;
	cbus_uart_wrb( siopcb->siopinib->channel_addr, THR, c );
}

/*
 *  SIOドライバの初期化ルーチン
 */
void
cbus_uart_initialize()
{
	SIOPCB	*siopcb;
	UINT	i;

	/*
	 *  シリアルI/Oポート管理ブロックの初期化
	 */
	for (siopcb = siopcb_table, i = 0; i < TNUM_SIOP; siopcb++, i++) {
		siopcb->siopinib = &(siopinib_table[i]);
		siopcb->openflag = FALSE;
	}
}

/*
 *  SIOレジスタ初期化ルーチン
 */
void
cbus_uart_init_siopinib( const SIOPINIB  *siopinib )
{
	/*
	 * SIOレジスタの初期化
	 */
	/* 初期処理 */
	cbus_uart_wrb( siopinib->channel_addr, IER, DIS_INT );

	cbus_uart_wrb( siopinib->channel_addr, MCR, ENABLE_EXT_INT );

	/* ボーレートの設定 */
	cbus_uart_wrb( siopinib->channel_addr, LCR, siopinib->lcr_def | DIVISOR_LATCH_ACC );

	cbus_uart_wrb( siopinib->channel_addr, SCR, siopinib->scr_def );

	cbus_uart_wrb( siopinib->channel_addr, DLL, siopinib->boud_lo_def );
	cbus_uart_wrb( siopinib->channel_addr, DLM, siopinib->boud_hi_def );

	/* モードの設定 */
	cbus_uart_wrb( siopinib->channel_addr, LCR, siopinib->lcr_def );

	/* FIFOの設定 */
	cbus_uart_wrb( siopinib->channel_addr, FCR, FIFO_ENABLE );
	cbus_uart_wrb( siopinib->channel_addr, FCR, FIFO_ENABLE | RECEIVE_FIFO_RESET | TRANS_FIFO_RESET | RECEIVE_TRIG_1_BYTE );
	cbus_uart_wrb( siopinib->channel_addr, FCR, FIFO_ENABLE | RECEIVE_TRIG_1_BYTE );

	/* 終了処理 */
	cbus_uart_wrb( siopinib->channel_addr, MCR, DTR | RTS | ENABLE_EXT_INT );

	cbus_uart_wrb( siopinib->channel_addr, IER, RECEIVE_DATA_AVAILABLE);
}

/*
 *  カーネル起動時のバーナー出力用の初期化
 */
void
cbus_uart_init(void)
{
	cbus_uart_init_siopinib( get_siopinib(1) );
}

/*
 *  オープンしているポートがあるか？
 */
BOOL
cbus_uart_openflag(void)
{
	return(siopcb_table[0].openflag);
}

/*
 *  シリアルI/Oポートのオープン
 */
SIOPCB *
cbus_uart_opn_por(ID siopid, VP_INT exinf)
{
	SIOPCB		*siopcb = get_siopcb(siopid);
	const SIOPINIB	*siopinib = siopcb->siopinib;

	/* シリアルコントローラの初期化 */
	cbus_uart_init_siopinib( siopinib );

	/* 割込みレベル設定、割込み要求クリアは、sio_opn_por(hw_serial.h)で行う。 */

	siopcb->exinf = exinf;
	siopcb->getready = siopcb->putready = FALSE;
	siopcb->openflag = TRUE;

	return(siopcb);
}

/*
 *  シリアルI/Oポートのクローズ
 */
void
cbus_uart_cls_por(SIOPCB *siopcb)
{
	cbus_uart_wrb( siopcb->siopinib->channel_addr, IER, DIS_INT );

	siopcb->openflag = FALSE;
}

/*
 *  シリアルI/Oポートへの文字送信
 */
BOOL
cbus_uart_snd_chr(SIOPCB *siopcb, char c)
{
	if (cbus_uart_putready(siopcb)) {
		cbus_uart_putchar(siopcb, c);
		return(TRUE);
	}
	return(FALSE);
}

/*
 *  シリアルI/Oポートからの文字受信
 */
INT
cbus_uart_rcv_chr(SIOPCB *siopcb)
{
	if (cbus_uart_getready(siopcb)) {
		return((INT)(UB) cbus_uart_getchar(siopcb));
	}
	return(-1);
}

/*
 *  シリアルI/Oポートからのコールバックの許可
 */
void
cbus_uart_ena_cbr(SIOPCB *siopcb, UINT cbrtn)
{
	UB	ier_bit = 0;

	switch (cbrtn) {
	case SIO_ERDY_SND:
		ier_bit = TRANS_REG_EMPTY;
		break;
	case SIO_ERDY_RCV:
		ier_bit = (RECEIVE_DATA_AVAILABLE | RECEIVE_LINE_STATUS);
		break;
	}

	cbus_uart_orb( siopcb->siopinib->channel_addr, IER, ier_bit );
}

/*
 *  シリアルI/Oポートからのコールバックの禁止
 */
void
cbus_uart_dis_cbr(SIOPCB *siopcb, UINT cbrtn)
{
	UB	ier_bit = 0;

	switch (cbrtn) {
	case SIO_ERDY_SND:
		ier_bit = TRANS_REG_EMPTY;
		break;
	case SIO_ERDY_RCV:
		ier_bit = (RECEIVE_DATA_AVAILABLE | RECEIVE_LINE_STATUS);
		break;
	}

	cbus_uart_andb( siopcb->siopinib->channel_addr, IER, ~ier_bit );
}

/*
 *  シリアルI/Oポートに対する割込み処理
 */
static void
cbus_uart_isr_siop(SIOPCB *siopcb)
{
	cbus_uart_get_stat(siopcb);

	if ( cbus_uart_getready(siopcb) ) {
		/*
		 *  受信通知コールバックルーチンを呼び出す．
		 */
		cbus_uart_ierdy_rcv(siopcb->exinf);
	} else if ( cbus_uart_putready(siopcb) ) {
		/*
		 *  送信可能コールバックルーチンを呼び出す．
		 */
		cbus_uart_ierdy_snd(siopcb->exinf);
	}
}

/*
 *  SIOの割込みサービスルーチン
 */
void
cbus_uart_uart0_isr()
{
	if (siopcb_table[0].openflag) {
		cbus_uart_isr_siop(&(siopcb_table[0]));
	}
}

/*
 *  シリアルI/Oポートへのポーリングでの出力
 */
void
cbus_uart_putchar_pol( char val ) {

	const SIOPINIB  *siopinib = get_siopinib( LOGTASK_PORTID );

	/* 送信部エンプティになるまで待つ。 */
	while( (cbus_uart_reb( siopinib->channel_addr, LSR ) & (TEMT) ) == 0 );

	cbus_uart_wrb( siopinib->channel_addr, THR, val );
}

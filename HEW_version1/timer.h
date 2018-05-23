//=============================================================================
//
// タイマー処理 [timer.h]
// Author : 眞戸原史也
// プログラム作成日 : 2018/3/09
//
//=============================================================================

// 多重インクルード防止の為
#ifndef _TIMER_H_
#define _TIMER_H_

// ライブライ＆マクロの使用の為
#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define FRAME_CNT			(60)								// 一秒のフレーム数
#define DECIMAL_TEN			(10.0f)								// １０進数の基数
#define BASE_HUNDRED		(100)								// １００
#define BASE_TEN			(10)								// １０
#define TIME_DRAW_MAX		(999)								// 表示最大数

#define	NUM_PLACE			(3)									// タイマーの桁数

#define	TEXTURE_TIMER		"data/TEXTURE/deg_number3.png"		// 読み込むテクスチャファイル名
#define	TIMER_SIZE_X		(60.0f)								// タイマーの数字の幅
#define	TIMER_SIZE_Y		(95.0f)								// タイマーの数字の高さ
#define	TIMER_INTERVAL_X	(0.0f)								// タイマーの数字の表示間隔

#define	TIMER_BASE_POS		D3DXVECTOR3(0.0f, 0.0f, 0.0f)		// タイマーの基本位置
#define	TIMER_POS_X			(SCREEN_WIDTH/2 - ((TIMER_SIZE_X * NUM_PLACE + TIMER_INTERVAL_X * (NUM_PLACE - 1)) / 2) )	// タイマーの表示基準位置Ｘ座標
#define	TIMER_POS_Y			(12.0f)																						// タイマーの表示基準位置Ｙ座標

#define TIMER_MAX			(180)								// タイマーのスタートの値

#define	KILL_SIZE_X			(60.0f)								// 必殺技ゲージの数字の幅
#define	KILL_SIZE_Y			(90.0f)								// 必殺技ゲージの数字の高さ

#define	TIMER_PLAYER_POS	D3DXVECTOR3(80.0f, 620.0f, 0.0f)		// 必殺技ゲージプレイヤーの基本位置
#define	NUM_PLAYER_POS_X	(SCREEN_WIDTH - ((NUM_HP_SIZE_X * NUM_PLACE + TIMER_INTERVAL_X * (NUM_PLACE - 1)) / 2) )	// HPの表示基準位置Ｘ座標
#define	NUM_PLAYER_POS_Y	(80.0f)																						// HPの表示基準位置Ｙ座標

#define	TIMER_ENEMY_POS		D3DXVECTOR3(1050.0f, 620.0f, 0.0f)		// 必殺技ゲージエネミーの基本位置
#define	NUM_ENEMY_POS_X		(SCREEN_WIDTH - ((NUM_HP_SIZE_X * NUM_PLACE + TIMER_INTERVAL_X * (NUM_PLACE - 1)) / 2) )	// HPの表示基準位置Ｘ座標
#define	NUM_ENEMY_POS_Y		(80.0f)																						// HPの表示基準位置Ｙ座標



// タイマー制御マクロ
enum
{
	NUM_TIMER,			// タイマー
	NUM_PLAYER_KILL,	// 必殺技ゲージプレイヤー
	NUM_ENEMY_KILL,		// 必殺技ゲージエネミー
	NUM_MAX,			// マクロ最大数
};

// 桁制御マクロ
enum
{
	NUM_THREE_DIGIT,	// 三桁目
	NUM_DOUBLE_DIGIT,	// 二桁目
	NUM_DIGIT,			// 一桁目
	NUM_DIGIT_MAX,		// マクロ最大数
};


//=============================================================================
// 構造体宣言
//=============================================================================

// タイトル構造体
typedef struct
{

	bool					use;			// 描画制御変数 true:使用 false:未使用

	D3DXVECTOR3				pos;			// 座標格納変数
	D3DXVECTOR3				rot;			// 回転格納変数

	int						nummax;			// 数値格納変数

	LPDIRECT3DVERTEXBUFFER9 buff;			// 頂点バッファインターフェースへのポインタ変数

}TIMER;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitTimer(int type);				// 初期化処理関数
void UninitTimer(void);						// 終了処理関数
void UpdateTimer(void);						// 更新処理関数
void DrawTimer(void);						// 描画処理関数

void EnableTimer(bool bEnable);				// タイマー開始関数
void ResetTimer(int nTime = TIME_DRAW_MAX);	// タイマーリセット関数

#endif

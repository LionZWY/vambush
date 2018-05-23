//=============================================================================
//
// CALL画面処理 [call.h]
// Author : 眞戸原史也
// プログラム作成日 : 2018/3/09
//
//=============================================================================

// 多重インクルード防止の為
#ifndef _CALL_H_
#define _CALL_H_

// ライブラリ＆マクロ使用の為
#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define START_TIME_CALL					(4)														// 開始までの秒数

#define	CALL_BASE_TEXTURE				("data/TEXTURE/deg_number3.png")						// 読み込むテクスチャファイル名
#define	CALL_BASE_SIZE_X				(200/2.0f)											// テクスチャの幅
#define	CALL_BASE_SIZE_Y				(250/2)												// テクスチャの高さ
#define CALL_BASE_POS					D3DXVECTOR3(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f,0.0f)			// HPバー下地の位置

#define CALL_ANIM_PATTERN_DIVIDE_X		(10)												// アニメパターンのテクスチャ内分割数（X)
#define CALL_ANIM_PATTERN_DIVIDE_Y		(1)													// アニメパターンのテクスチャ内分割数（Y)
#define CALL_ANIM_PATTERN_NUM			(CALL_ANIM_PATTERN_DIVIDE_X*CALL_ANIM_PATTERN_DIVIDE_Y)	// アニメーションパターン数

#define	CALL_BATTLE_TEXTURE				("data/TEXTURE/バトルスタート.png")						// 読み込むテクスチャファイル名
#define	CALL_BATTLE_SIZE_X				(600/2.0f)											// テクスチャの幅
#define	CALL_BATTLE_SIZE_Y				(300/2)												// テクスチャの高さ



// タイトル構造体制御マクロ
enum
{
	CALL_NUM,							// HPバー下地
	CALL_BATTLE,		

	CALL_MAX,								// CALL構造体最大数
};

//=============================================================================
// 構造体宣言
//=============================================================================

// タイトル構造体
typedef struct
{

	bool use;											// 描画制御変数 true:使用 false:未使用

	int						PatternAnim;				// アニメーションパターンナンバー変数

	D3DXVECTOR3				pos;						// 座標格納変数
	D3DXVECTOR3				rot;						// 回転格納変数

	LPDIRECT3DTEXTURE9		Texture;					// テクスチャへのポインタ
	VERTEX_2D				vertex[NUM_VERTEX];			// 頂点情報格納ワーク

}CALL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitCall(int type);								// 初期化処理関数
void UninitCall(void);									// 終了処理関数
void UpdateCall(void);									// 更新処理関数
void DrawCall(void);										// 描画処理関数

void SetTextureCall(int no, int cntPattern);				// テクスチャ座標の設定
bool *GetStartFlag(void);

#endif

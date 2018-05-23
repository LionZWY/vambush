//=============================================================================
//
// タイトル画面処理 [result.h]
// Author : 眞戸原史也
// プログラム作成日 : 2018/3/09
//
//=============================================================================

// 多重インクルード防止の為
#ifndef _RESULT_H_
#define _RESULT_H_

// マクロ＆ライブラリ使用の為
#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define RESULT_EFFECT_SPEED				(2)		// 点滅速度速度
#define RESULT_SPEED					(3)		// 点滅速度速度
#define RESULT_RANK_SPEED				(32.0f)	// 点滅速度速度
#define RESULT_BGM_TIME					(9)		

#define	RESULT_BASE_TEXTURE				("data/TEXTURE/vambush_title01.png")						// 読み込むテクスチャファイル名
#define	RESULT_BASE_LIGHT_TEXTURE		("data/TEXTURE/vambush_title03.png")						// 読み込むテクスチャファイル名
#define	RESULT_BOAD_AI_TEXTURE			("data/TEXTURE/1Pwin00.png")								// 読み込むテクスチャファイル名
#define	RESULT_BOAD_VIRUS_TEXTURE		("data/TEXTURE/2Pwin00.png")								// 読み込むテクスチャファイル名

#define	RESULT_BASE_SIZE_X				(SCREEN_WIDTH/2.0f)											// テクスチャの幅
#define	RESULT_BASE_SIZE_Y				(SCREEN_HEIGHT/2.0f)										// テクスチャの高さ
#define RESULT_BASE_POS					D3DXVECTOR3(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f,0.0f)		// 砂浜の位置

#define	RESULT_AI_TEXTURE				("data/TEXTURE/hew_player01.png")									// 読み込むテクスチャファイル名
#define	RESULT_AI_SIZE_X				(1300/2)														// テクスチャの幅
#define	RESULT_AI_SIZE_Y				(722/2)														// テクスチャの高さ
#define RESULT_AI_POS					D3DXVECTOR3(641.0f,326.0f,0.0f)							// サフの位置

#define	RESULT_VIRUS_TEXTURE			("data/TEXTURE/hew_enemy00.png")							// 読み込むテクスチャファイル名
#define	RESULT_VIRUS_SIZE_X				(928/2)														// テクスチャの幅
#define	RESULT_VIRUS_SIZE_Y				(754/2)														// テクスチャの高さ
#define RESULT_VIRUS_POS				D3DXVECTOR3(464.0f,370.0f,0.0f)								// アイビスの位置

#define	RESULT_AI_RANK_TEXTURE			("data/TEXTURE/1Pwin01.png")									// 読み込むテクスチャファイル名
#define	RESULT_VIRUS_RANK_TEXTURE		("data/TEXTURE/2Pwin01.png")									// 読み込むテクスチャファイル名

#define	RESULT_RANK_SIZE_X				(580/2)														// テクスチャの幅
#define	RESULT_RANK_SIZE_Y				(194/2)														// テクスチャの高さ
#define RESULT_RANK_POS					D3DXVECTOR3(1280.0f,325.0f,0.0f)								// 評価の位置

#define	RESULT_RANK_EFFECT_SIZE_X		(595/2)														// テクスチャの幅
#define	RESULT_RANK_EFFECT_SIZE_Y		(209/2)														// テクスチャの高さ


#define	RESULT_BLACK_S_TEXTURE			("data/TEXTURE/window03.png")							// 読み込むテクスチャファイル名
#define	RESULT_BLACK_S_SIZE_X			(310/2)														// テクスチャの幅
#define	RESULT_BLACK_S_SIZE_Y			(318/2)														// テクスチャの高さ
#define RESULT_BLACK_S_POS				D3DXVECTOR3(SCREEN_WIDTH/2.0f,500.0f,0.0f)					// 黒板メニューの位置

#define	RESULT_INIT_TEXTURE				("data/TEXTURE/やりなおす.png")								// 読み込むテクスチャファイル名
#define	RESULT_INIT_SIZE_X				(280/2)														// テクスチャの幅
#define	RESULT_INIT_SIZE_Y				(70/2)														// テクスチャの高さ
#define RESULT_INIT_POS					D3DXVECTOR3(SCREEN_WIDTH/2.0f,445.,0.0f)					// やりなおすの位置

#define	RESULT_FINISH_TEXTURE			("data/TEXTURE/おわる.png")									// 読み込むテクスチャファイル名
#define	RESULT_FINISH_SIZE_X			(180/2)														// テクスチャの幅
#define	RESULT_FINISH_SIZE_Y			(70/2)														// テクスチャの高さ
#define RESULT_FINISH_POS				D3DXVECTOR3(SCREEN_WIDTH/2.0f,555.0f,0.0f)					// おわるの位置

#define	RESULT_ANY_EFFECT_SIZE_X		(290/2)														// テクスチャの幅
#define	RESULT_ANY_EFFECT_SIZE_Y		(80/2)														// テクスチャの高さ
#define	RESULT_FINISH_EFFECT_SIZE_X		(190/2)														// テクスチャの幅
#define	RESULT_FINISH_EFFECT_SIZE_Y		(80/2)														// テクスチャの高さ


// タイトル構造体制御マクロ
enum
{
	RESULT_BASE,							// 背景

	RESULT_BOAD_AI,							// 勝利フラグプレイヤー
	RESULT_AI,								// プレイヤー
	RESULT_AI_RANK,							// 評価プレイヤー
	RESULT_AI_RANK_EFFECT,					// エフェクト:評価プレイヤー

	RESULT_BOAD_VIRUS,						// 勝利フラグウイルス
	RESULT_VIRUS,							// ウイルス
	RESULT_VIRUS_RANK,						// 評価ウイルス
	RESULT_VIRUS_RANK_EFFECT,				// エフェクト:評価ウイルス

	RESULT_BASE_LIGHT,						// 背景ハイライト

	RESULT_BLACK_S,							// カーソルウインドウ表示
	RESULT_INIT,							// UI:"やりなおす"
	RESULT_INIT_EFFECT,						// UIエフェクト:"やりなおす"
	RESULT_FINISH,							// UI:"おわる"
	RESULT_FINISH_EFFECT,					// UIエフェクト:"おわる"
	RESULT_MAX,								// 構造体最大数
};


// リザルトカーソル制御マクロ
enum
{
	RESULT_UI_INIT,					// UI:"やりなおす"
	RESULT_UI_FINISH,				// UI:"おわる"
	RESULT_UI_MAX,					// UIカーソル最大数
};

//=============================================================================
// 構造体宣言
//=============================================================================

// タイトル構造体
typedef struct
{

	bool use;											// 描画制御変数

	D3DXVECTOR3				pos;						// 座標格納変数

	LPDIRECT3DTEXTURE9		Texture;					// テクスチャへのポインタ変数
	VERTEX_2D				vertex[NUM_VERTEX];			// 頂点情報格納ワーク変数

}RESULT;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitResult(int type);							// 初期化処理関数
void UninitResult(void);								// 終了処理関数
void UpdateResult(void);								// 更新処理関数
void DrawResult(void);									// 描画処理関数
bool *GetWinFlag(void);									// 勝利フラグ取得関数

#endif

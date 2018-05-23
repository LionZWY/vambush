//=============================================================================
//
// タイトル画面処理 [title.h]
// Author : 眞戸原史也
// プログラム作成日 : 2018/3/09
//
//=============================================================================


// 多重インクルード防止の為
#ifndef _TITLE_H_
#define _TITLE_H_

// マクロ＆ライブラリ使用の為
#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define INIT_EFFECT					(1)												// エフェクトのRGBの初期値
#define ALPHA_TEST					(125)											// アルファテストのαの値
#define ALPHA_BASE					(1)												// テクスチャのαの値
#define ALPHA_MAX					(255)											// αの値の最大値
#define EFFECT_SPEED				(2)												// 点滅速度速度

#define B_ALPHA_BASE				(0)												// テクスチャのαの値
#define B_ALPHA_MAX					(100)											// αの値の最大値
#define B_EFFECT_SPEED				(1)												// 点滅速度速度

#define	TITLE_BASE_TEXTURE			("data/TEXTURE/vambush_title01.png")					// 読み込むテクスチャファイル名
#define	TITLE_BASE_SIZE_X			(SCREEN_WIDTH/2)											// テクスチャの幅
#define	TITLE_BASE_SIZE_Y			(SCREEN_HEIGHT/2)											// テクスチャの高さ
#define TITLE_BASE_POS				D3DXVECTOR3(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f,0.0f)	// タイトル背景の位置

#define	TITLE_BASE_LIGHT_TEXTURE	("data/TEXTURE/vambush_title03.png")					// 読み込むテクスチャファイル名

#define	TITLE_EFFECT_TEXTURE		("data/TEXTURE/vambush_title00.png")					// 読み込むテクスチャファイル名
#define	TITLE_EFFECT_SIZE_X			(880/2)													// テクスチャの幅
#define	TITLE_EFFECT_SIZE_Y			(732/2)													// テクスチャの高さ
#define TITLE_EFFECT_POS			D3DXVECTOR3(637.0f,367.0f,0.0f)							// タイトル背景エフェクトの位置

#define	TITLE_AI_TEXTURE			("data/TEXTURE/hew_player01.png")						// 読み込むテクスチャファイル名
#define	TITLE_AI_SIZE_X				(552/2)													// テクスチャの幅
#define	TITLE_AI_SIZE_Y				(488/2)													// テクスチャの高さ
#define TITLE_AI_POS				D3DXVECTOR3(1024.0f,508.0f,0.0f)							// キャラクター:AIの位置

#define	TITLE_VIRUS_TEXTURE			("data/TEXTURE/hew_enemy00.png")						// 読み込むテクスチャファイル名
#define	TITLE_VIRUS_SIZE_X			(540/2)													// テクスチャの幅
#define	TITLE_VIRUS_SIZE_Y			(494/2)													// テクスチャの高さ
#define TITLE_VIRUS_POS				D3DXVECTOR3(266.0f,198.0f,0.0f)							// キャラクター:ウイルスの位置

#define	TITLE_LOGO_TEXTURE			("data/TEXTURE/vambush_titlelogo.png")					// 読み込むテクスチャファイル名
#define	TITLE_LOGO_SIZE_X			(866/2)													// テクスチャの幅
#define	TITLE_LOGO_SIZE_Y			(280/2)													// テクスチャの高さ
#define TITLE_LOGO_POS				D3DXVECTOR3(SCREEN_WIDTH/2.0f,324.0f,0.0f)			// タイトルロゴの位置

#define	TITLE_ANY_TEXTURE			("data/TEXTURE/PRESS_BUTTON.png")				// 読み込むテクスチャファイル名
#define	TITLE_ANY_SIZE_X			(392/2)											// テクスチャの幅
#define	TITLE_ANY_SIZE_Y			(130/2)											// テクスチャの高さ
#define TITLE_ANY_POS				D3DXVECTOR3(625.0f,557.0f,0.0f)					// UI:"ボタンをおしてね"

#define	TITLE_START_TEXTURE			("data/TEXTURE/はじめる.png")					// 読み込むテクスチャファイル名
#define	TITLE_START_SIZE_X			(354/2)											// テクスチャの幅
#define	TITLE_START_SIZE_Y			(90/2)											// テクスチャの高さ
#define TITLE_START_POS				D3DXVECTOR3(637.0f,506.0f,0.0f)		// UI:"はじめる"

#define	TITLE_CREDIT_TEXTURE		("data/TEXTURE/操作説明.png")				// 読み込むテクスチャファイル名
#define	TITLE_CREDIT_SIZE_X			(354/2)											// タイトルの幅
#define	TITLE_CREDIT_SIZE_Y			(90/2)											// タイトルの高さ
#define TITLE_CREDIT_POS			D3DXVECTOR3(637.0f,610.0f,0.0f)					// UI:"クレジット"

#define	TITLE_BOAD_TEXTURE			("data/TEXTURE/操作方法.JPG")							// 読み込むテクスチャファイル名
#define	TITLE_BOAD_SIZE_X			(1100/2)													// テクスチャの幅
#define	TITLE_BOAD_SIZE_Y			(650/2)														// テクスチャの高さ
#define TITLE_BOAD_POS				D3DXVECTOR3(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f,0.0f)		// UI:"クレジットED"(クレジットテクスチャ)

#define	TITLE_ANY_EFFECT_SIZE_X		(404/2)											// テクスチャの幅
#define	TITLE_ANY_EFFECT_SIZE_Y		(140/2)											// テクスチャの高さ

#define	TITLE_START_EFFECT_SIZE_X	(364/2)											// テクスチャの幅
#define	TITLE_START_EFFECT_SIZE_Y	(100/2)											// テクスチャの高さ


#define COLOR_WHITE					D3DCOLOR_RGBA(255, 255, 255, 255);				// UIカーソルの色:白
#define COLOR_YELLOW				D3DCOLOR_RGBA(255, 175, 0, 255);				// UIカーソルの色:黄色
	#define COLOR_RED				D3DCOLOR_RGBA(255, 0, 0, 255);				// UIカーソルの色:赤色
	#define COLOR_BULE				D3DCOLOR_RGBA(0, 0, 255, 255);				// UIカーソルの色:青色

// タイトル構造体制御マクロ
enum
{
	TITLE_BASE,						// タイトル背景
	TITLE_BASE_LIGHT,				// ハイライト
	TITLE_EFFECT,					// タイトル背景エフェクト
	TITLE_AI,						// キャラクター:AI
	TITLE_VIRUS,					// キャラクター:ウイルス
	TITLE_LOGO,						// タイトルロゴ

	TITLE_ANY,						// UI:"ボタンをおしてね"
	TITLE_ANY_EFFECT,				// UIエフェクト:"ボタンをおしてね"
	TITLE_START,					// UI:"はじめる"
	TITLE_START_EFFECT,				// UIエフェクト:"はじめる"
	TITLE_CREDIT,					// UI:"操作説明"
	TITLE_CREDIT_EFFECT,			// UIエフェクト:"操作説明"

	TITLE_BOAD,						// UI:"クレジットED"(クレジットテクスチャ)
	TITLE_MAX,						// タイトル構造体最大数
};

// UIカーソル制御マクロ
enum
{
	TITLE_UI_START,					// UI:"はじめる"
	TITLE_UI_CREDIT,				// UI:"クレジット"
	TITLE_UI_MAX,					// UIカーソル最大数
};


//=============================================================================
// 構造体宣言
//=============================================================================

// タイトル構造体
typedef struct
{

	bool					use;						// 描画制御変数

	D3DXVECTOR3				pos;						// 座標格納変数

	LPDIRECT3DTEXTURE9		Texture;					// テクスチャへのポインタ変数
	VERTEX_2D				vertex[NUM_VERTEX];			// 頂点情報格納ワーク変数

}TITLE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitTitle(int type);							// 初期化処理関数
void UninitTitle(void);									// 終了処理関数
void UpdateTitle(void);									// 更新処理関数
void DrawTitle(void);									// 描画処理関数

#endif

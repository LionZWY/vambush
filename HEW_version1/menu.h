//=============================================================================
//
// ポーズメニュー処理 [menu.h]
// Author : 眞戸原史也
// プログラム作成日 : 2018/3/09
//
//=============================================================================

// 多重インクルード防止の為
#ifndef _MENU_H_
#define _MENU_H_

// マクロ＆ライブラリ使用使用の為
#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define EFFECT_MENU_SPEED			(2)															// 点滅速度速度

#define	MENU_BASE_SIZE_X			(SCREEN_WIDTH/2)											// ポリゴンの幅
#define	MENU_BASE_SIZE_Y			(SCREEN_HEIGHT/2)											// ポリゴンの高さ
#define MENU_BASE_POS				D3DXVECTOR3(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f,0.0f)		// メニュー暗転の位置

#define	MENU_BLACK_TEXTURE			("data/TEXTURE/window03.png")							// 読み込むテクスチャファイル名
#define	MENU_BLACK_SIZE_X			(360/2)														// テクスチャの幅
#define	MENU_BLACK_SIZE_Y			(450/2)														// テクスチャの高さ
#define MENU_BLACK_POS				D3DXVECTOR3(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f,0.0f)		// 黒板メニュー:Aの位置

#define	MENU_ANY_TEXTURE			("data/TEXTURE/つづける.png")								// 読み込むテクスチャファイル名
#define	MENU_ANY_SIZE_X				(210/2)														// テクスチャの幅
#define	MENU_ANY_SIZE_Y				(70/2)														// テクスチャの高さ
#define MENU_ANY_POS				D3DXVECTOR3(SCREEN_WIDTH/2.0f,450/2.0f,0.0f)					// つづけるの位置

#define	MENU_ANY_EFFECT_SIZE_X		(220/2)														// テクスチャの幅
#define	MENU_ANY_EFFECT_SIZE_Y		(80/2)														// テクスチャの高さ

#define	MENU_INIT_TEXTURE			("data/TEXTURE/やりなおす.png")								// 読み込むテクスチャファイル名
#define	MENU_INIT_SIZE_X			(280/2)														// テクスチャの幅
#define	MENU_INIT_SIZE_Y			(70/2)														// テクスチャの高さ
#define MENU_INIT_POS				D3DXVECTOR3(SCREEN_WIDTH/2.0f,700/2.0f,0.0f)					// やりなおすの位置

#define	MENU_INIT_EFFECT_SIZE_X		(290/2)														// テクスチャの幅
#define	MENU_INIT_EFFECT_SIZE_Y		(80/2)														// テクスチャの高さ

#define	MENU_FINISH_TEXTURE			("data/TEXTURE/おわる.png")									// 読み込むテクスチャファイル名
#define	MENU_FINISH_SIZE_X			(180/2)														// テクスチャの幅
#define	MENU_FINISH_SIZE_Y			(70/2)														// テクスチャの高さ
#define MENU_FINISH_POS				D3DXVECTOR3(SCREEN_WIDTH/2.0f,950/2.0f,0.0f)					// おわるの位置

#define	MENU_FINISH_EFFECT_SIZE_X	(190/2)														// テクスチャの幅
#define	MENU_FINISH_EFFECT_SIZE_Y	(80/2)														// テクスチャの高さ


// メニュー構造体制御マクロ
enum
{
	MENU_BASE,						// メニュー暗転
	MENU_BLACK,						// 黒板メニュー
	MENU_ANY,						// UI:"つづける"
	MENU_ANY_EFFECT,				// UIエフェクト:"つづける"
	MENU_INIT,						// UI:"やりなおす"
	MENU_INIT_EFFECT,				// UIエフェクト:"やりなおす"
	MENU_FINISH,					// UI:"おわる"
	MENU_FINISH_EFFECT,				// UIエフェクト:"おわる"
	MENU_MAX,						// メニュー構造体最大数
};

// メニューカーソル制御マクロ
enum
{
	MENU_UI_ANY,					// UI:"つづける"
	MENU_UI_INIT,					// UI:"やりなおす"
	MENU_UI_FINISH,					// UI:"おわる"
	MENU_UI_MAX,					// UIカーソル最大数
};


//=============================================================================
// 構造体宣言
//=============================================================================

// メニュー構造体
typedef struct
{

	bool					use;						// true:使用 false:未使用

	D3DXVECTOR3				pos;						// 座標格納変数

	LPDIRECT3DTEXTURE9		Texture;					// テクスチャへのポインタ変数
	VERTEX_2D				vertex[NUM_VERTEX];			// 頂点情報格納ワーク変数

}MENU;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitMenu(int type);								// 初期化処理関数
void UninitMenu(void);									// 終了処理関数
void UpdateMenu(void);									// 更新処理関数
void DrawMenu(void);									// 描画処理関数
void SetTextureMenu(int no, int cntPattern);			// テクスチャ座標の設定

#endif

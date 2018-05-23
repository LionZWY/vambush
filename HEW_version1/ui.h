//=============================================================================
//
// UI画面処理 [ui.h]
// Author : 眞戸原史也
// プログラム作成日 : 2018/3/09
//
//=============================================================================

// 多重インクルード防止の為
#ifndef _UI_H_
#define _UI_H_

// ライブラリ＆マクロ使用の為
#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define UI_EFFECT_BASE				(150)												// UIエフェクトのα値
#define UI_EFFECT_SPEED				(5)													// 点滅速度速度

#define	UI_BASE_TEXTURE				("data/TEXTURE/life_bg00.png")						// 読み込むテクスチャファイル名
#define	UI_BASE_SIZE_X				(1280/2.0f)											// テクスチャの幅
#define	UI_BASE_SIZE_Y				(232/2)												// テクスチャの高さ
#define UI_BASE_POS					D3DXVECTOR3(SCREEN_WIDTH/2.0f,125.0f,0.0f)			// HPバー下地の位置

#define	UI_HP_TEXTURE				("data/TEXTURE/life_bar.png")						// 読み込むテクスチャファイル名
#define	UI_HP_FRAME_SIZE_X			(582/2)											// テクスチャの幅
#define	UI_HP_FRAME_SIZE_Y			(72/2)												// テクスチャの高さ
#define UI_HP_FRAME_POS				D3DXVECTOR3(400.0f,59.0f,0.0f)						// プレイヤーHPバー枠の位置
#define UI_EHP_FRAME_POS			D3DXVECTOR3(931.0f,59.0f,0.0f)					// エネミ－HPバー枠の位置

#define	UI_AI_TEXTURE				("data/TEXTURE/ui_player.png")						// 読み込むテクスチャファイル名
#define	UI_AI_SIZE_X				(148/2)												// テクスチャの幅
#define	UI_AI_SIZE_Y				(138/2)												// テクスチャの高さ
#define UI_AI_POS					D3DXVECTOR3(64.0f,58.0f,0.0f)						// キャラクター:AIの位置

#define	UI_VIRUS_TEXTURE			("data/TEXTURE/ui_enemy.png")						// 読み込むテクスチャファイル名
#define	UI_VIRUS_SIZE_X				(140/2)												// テクスチャの幅
#define	UI_VIRUS_SIZE_Y				(134/2)												// テクスチャの高さ
#define UI_VIRUSE_POS				D3DXVECTOR3(1207.0f,59.0f,0.0f)						// キャラクター:ウイルスの位置

#define	UI_HP_SIZE_X				(435.0f)											// テクスチャの幅
#define	UI_HP_SIZE_Y				(60)												// テクスチャの高さ
#define UI_HP_POS					D3DXVECTOR3(103.0f,29.0f,0.0f)						// HPバーの位置
#define UI_EHP_POS					D3DXVECTOR3(1177.0f,29.0f,0.0f)						// エネミ－HPバーの位置

#define	UI_FRAME_TEXTURE			("data/TEXTURE/window01.png")						// 読み込むテクスチャファイル名
#define	UI_FRAME_SIZE_X				(198/2)												// テクスチャの幅
#define	UI_FRAME_SIZE_Y				(114/2)												// テクスチャの高さ
#define UI_FRAME_POS				D3DXVECTOR3(640.0f,60.0f,0.0f)						// タイマーの枠の位置

#define	UI_FRAME_AI_TEXTURE			("data/TEXTURE/window02.png")						// 読み込むテクスチャファイル名
#define	UI_FRAME_AI_SIZE_X			(296/2)												// テクスチャの幅
#define	UI_FRAME_AI_SIZE_Y			(206/2)												// テクスチャの高さ
#define UI_FRAME_AI_POS				D3DXVECTOR3(155.0f,612.0f,0.0f)						// 技枠AIの位置

#define	UI_FRAME_VIRUS_TEXTURE		("data/TEXTURE/window00.png")						// 読み込むテクスチャファイル名
#define UI_FRAME_VIRUS_POS			D3DXVECTOR3(1125.0f,612.0f,0.0f)					// 技枠ウイルスの位置


#define	UI_SKILL_A_TEXTURE			("data/TEXTURE/skill00_icon.png")						// 読み込むテクスチャファイル名
#define	UI_SKILL_B_TEXTURE			("data/TEXTURE/skill01_icon.png")						// 読み込むテクスチャファイル名
#define	UI_SKILL_C_TEXTURE			("data/TEXTURE/skill02_UI.png")						// 読み込むテクスチャファイル名

#define	UI_SKILL_SIZE_X				(42/2)												// テクスチャの幅
#define	UI_SKILL_SIZE_Y				(48/2)												// テクスチャの高さ

#define	UI_SKILL_C_SIZE_X			(70/2)												// テクスチャの幅
#define	UI_SKILL_C_SIZE_Y			(82/2)												// テクスチャの高さ

#define UI_SKILL_A_POS				D3DXVECTOR3(152.0f,547.0f,0.0f)						// スキル1の位置
#define UI_SKILL_B_POS				D3DXVECTOR3(152.0f,599.0f,0.0f)						// スキル2の位置
#define UI_SKILL_C_POS				D3DXVECTOR3(46.0f,665.0f,0.0f)						// スキル3の位置
#define UI_ESKILL_A_POS				D3DXVECTOR3(1122.0f,547.0f,0.0f)						// スキル1の位置
#define UI_ESKILL_B_POS				D3DXVECTOR3(1122.0f,599.0f,0.0f)						// スキル2の位置
#define UI_ESKILL_C_POS				D3DXVECTOR3(1016.0f,665.0f,0.0f)						// スキル3の位置

#define	UI_SKILL_KEY_TEXTURE		("data/TEXTURE/skill00_UI.png")						// 読み込むテクスチャファイル名
#define	UI_SKILL_BKEY_TEXTURE		("data/TEXTURE/skill01_UI.png")						// 読み込むテクスチャファイル名

#define	UI_SKILL_KEY_SIZE_X			(108/2)												// テクスチャの幅
#define	UI_SKILL_KEY_SIZE_Y			(32/2)												// テクスチャの高さ
#define UI_SKILL_KEY_POS			D3DXVECTOR3(70.0f,545.0f,0.0f)						// スキル1の位置
#define UI_SKILL_BKEY_POS			D3DXVECTOR3(70.0f,597.0f,0.0f)						// スキル2の位置
#define UI_ESKILL_KEY_POS			D3DXVECTOR3(1040.0f,545.0f,0.0f)						// スキル1の位置
#define UI_ESKILL_BKEY_POS			D3DXVECTOR3(1040.0f,597.0f,0.0f)						// スキル2の位置

#define	UI_SKILL_CROSS_TEXTURE		("data/TEXTURE/deg_X.png")						// 読み込むテクスチャファイル名

#define	UI_SKILL_CROSS_SIZE_X		(28/2)												// テクスチャの幅
#define	UI_SKILL_CROSS_SIZE_Y		(28/2)												// テクスチャの高さ
#define UI_SKILL_CROSS_POS			D3DXVECTOR3(199.0f,545.0f,0.0f)						// スキル1の位置
#define UI_SKILL_BCROSS_POS			D3DXVECTOR3(199.0f,597.0f,0.0f)						// スキル2の位置
#define UI_ESKILL_CROSS_POS			D3DXVECTOR3(1169.0f,545.0f,0.0f)						// スキル1の位置
#define UI_ESKILL_BCROSS_POS		D3DXVECTOR3(1169.0f,597.0f,0.0f)						// スキル2の位置

#define	UI_SKILL_NUM_TEXTURE		("data/TEXTURE/deg_number3.png")						// 読み込むテクスチャファイル名

#define	UI_SKILL_NUM_SIZE_X			(42/2)												// テクスチャの幅
#define	UI_SKILL_NUM_SIZE_Y			(64/2)												// テクスチャの高さ
#define UI_SKILL_NUM_POS			D3DXVECTOR3(258.0f,546.0f,0.0f)						// スキル1の位置
#define UI_SKILL_BNUM_POS			D3DXVECTOR3(258.0f,601.0f,0.0f)						// スキル2の位置
#define UI_ESKILL_NUM_POS			D3DXVECTOR3(1228.0f,546.0f,0.0f)						// スキル1の位置
#define UI_ESKILL_BNUM_POS			D3DXVECTOR3(1228.0f,601.0f,0.0f)						// スキル2の位置

#define UI_ANIM_PATTERN_DIVIDE_X	(10)												// アニメパターンのテクスチャ内分割数（X)
#define UI_ANIM_PATTERN_DIVIDE_Y	(1)													// アニメパターンのテクスチャ内分割数（Y)
#define UI_ANIM_PATTERN_NUM			(UI_ANIM_PATTERN_DIVIDE_X*UI_ANIM_PATTERN_DIVIDE_Y)	// アニメーションパターン数

#define	UI_SKILL_PAR_TEXTURE		("data/TEXTURE/deg_percent.png")						// 読み込むテクスチャファイル名

#define	UI_SKILL_PAR_SIZE_X			(32/2)												// テクスチャの幅
#define	UI_SKILL_PAR_SIZE_Y			(44/2)												// テクスチャの高さ
#define UI_SKILL_PAR_POS			D3DXVECTOR3(277.0f,678.0f,0.0f)						// スキル1の位置
#define UI_ESKILL_PAR_POS			D3DXVECTOR3(1247.0f,678.0f,0.0f)						// スキル1の位置


// タイトル構造体制御マクロ
enum
{
	UI_BASE,							// HPバー下地
	UI_HP_FRAME,						// プレイヤーHPバー枠
	UI_EHP_FRAME,						// エネミ－HPバー枠
	UI_HP,								// プレイヤーHPバー
	UI_HP_EFFECT,						// プレイヤーHPバーエフェクト
	UI_EHP,								// エネミ－HPバー
	UI_EHP_EFFECT,						// エネミ－HPバーエフェクト
	UI_AI,								// キャラクター:AI
	UI_VIRUS,							// キャラクター:ウイルス

	UI_FRAME,							// タイマーの枠
	UI_FRAME_AI,						// 技枠AI
	UI_FRAME_VIRUS,						// 技枠ウイルス

	UI_SKILL_A,							// スキル1アイコン
	UI_SKILL_KEY,						// スキル1キー
	UI_SKILL_CROSS,						// スキル1演算子
	UI_SKILL_NUM,						// スキル1数字

	UI_SKILL_B,							// スキル2アイコン
	UI_SKILL_BKEY,						// スキル2キー
	UI_SKILL_BCROSS,					// スキル2演算子
	UI_SKILL_BNUM,						// スキル2数字

	UI_SKILL_C,							// スキル3アイコン
	UI_SKILL_PAR,						// スキル3演算子

	UI_ESKILL_A,						// スキル1アイコン
	UI_ESKILL_KEY,						// スキル1キー
	UI_ESKILL_CROSS,					// スキル1演算子
	UI_ESKILL_NUM,						// スキル1数字

	UI_ESKILL_B,						// スキル2アイコン
	UI_ESKILL_BKEY,						// スキル2キー
	UI_ESKILL_BCROSS,					// スキル2演算子
	UI_ESKILL_BNUM,						// スキル2数字

	UI_ESKILL_C,						// スキル3アイコン
	UI_ESKILL_PAR,						// スキル3演算子


	UI_MAX,								// UI構造体最大数
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


	bool					effectflag;					// エフェクト用制御変数
	int						effect;						// エフェクト用変数

	LPDIRECT3DTEXTURE9		Texture;					// テクスチャへのポインタ
	VERTEX_2D				vertex[NUM_VERTEX];			// 頂点情報格納ワーク

}UI;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitUi(int type);								// 初期化処理関数
void UninitUi(void);									// 終了処理関数
void UpdateUi(void);									// 更新処理関数
void DrawUi(void);										// 描画処理関数

void SetTextureUi(int no, int cntPattern);				// テクスチャ座標の設定

#endif

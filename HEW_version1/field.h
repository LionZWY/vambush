//=============================================================================
//
// メッシュ地面の処理 [field.h]
// Name : GP11B243 30 眞戸原史也
// プログラム作成日:2018/1/25
//
//=============================================================================
#ifndef _FIELD_H_
#define _FIELD_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define FIELD_EFFECT_SPEED		(0.025f)							// 点滅速度速度

#define	TEXTURE_BG				"data/TEXTURE/battlebg00.png"	// 読み込むテクスチャファイル名
#define	TEXTURE_BG_EFFECT		"data/TEXTURE/battlebg01.png"	// 読み込むテクスチャファイル名

#define FIELD_BG_POS			D3DXVECTOR3(0.0f,-100.0f,0.0f)		// 地面初期座標
#define FIELD_BG_ROT			D3DXVECTOR3(0.0f,0.0f,0.0f)		// 地面初期回転
#define NUM_BG_BLOCK_X			(20)							// 地面ポリゴン数X
#define NUM_BG_BLOCK_Z			(20)							// 地面ポリゴン数Z
#define SIZE_BG_BLOCK_X			(240.0f)							// 地面ポリゴンサイズX
#define SIZE_BG_BLOCK_Z			(240.0f)							// 地面ポリゴンサイズZ

#define	TEXTURE_BATTLE			"data/TEXTURE/battlebg02.png"	// 読み込むテクスチャファイル名

#define FIELD_BG_NUM_BLOCK_X	(13)							// 地面ポリゴン数X
#define FIELD_BG_NUM_BLOCK_Z	(8)								// 地面ポリゴン数Z
#define FIELD_BG_SIZE_BLOCK_X	(60.0f)							// 地面ポリゴンサイズX
#define FIELD_BG_SIZE_BLOCK_Z	(60.0f)							// 地面ポリゴンサイズZ

#define FIELD_SCL_MAX_X			((FIELD_BG_NUM_BLOCK_X * FIELD_BG_SIZE_BLOCK_X) / 2)
#define FIELD_SCL_MAX_Z			((FIELD_BG_NUM_BLOCK_Z * FIELD_BG_SIZE_BLOCK_Z) / 2)

#define FIELD_COLOR				D3DXCOLOR(1.0f,1.0f,1.0f,0.6f)	// 地面の色


// フィールド用構造体識別マクロ
enum
{
	FIELD_BG,			// 背景
	FIELD_BG_EFFECT,	// 背景エフェクト
	FIELD_BATTLE,		// バトル
	FIELD_MAX,			// 構造体最大数
};


//=============================================================================
// 構造体宣言
//=============================================================================

typedef struct // フィールド構造体
{
	D3DXMATRIX		world;						// ワールドマトリックス
	D3DXVECTOR3		pos;						// ポリゴン表示位置の中心座標
	D3DXVECTOR3		rot;						// ポリゴンの回転角

	int				blockX, blockZ;				// ブロック数
	int				vertex;						// 総頂点数	
	int				vertexIndex;				// 総インデックス数
	int				polygon;					// 総ポリゴン数
	float			sizeX, sizeZ;				// ブロックサイズ

	LPDIRECT3DTEXTURE9		Texture;			// テクスチャ読み込み場所
	LPDIRECT3DVERTEXBUFFER9 VtxField;			// 頂点バッファインターフェースへのポインタ
	LPDIRECT3DINDEXBUFFER9	IdxField;			// インデックスバッファインターフェースへのポインタ

}FIELD;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitField(int type);				// 初期化処理関数
void UninitField(void);						// 終了処理関数
void UpdateField(void);						// 更新処理関数
void DrawField(void);						// 描画処理関数

FIELD *GetField(int no);

#endif

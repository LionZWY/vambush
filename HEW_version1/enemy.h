//=============================================================================
//
// エネミー処理 [enemy.h]
// Author : 朱文渊
// プログラム作成日 : 2018/3/09
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_ENEMY_W		"data/TEXTURE/enemy01.png"	// 読み込むテクスチャファイル名
#define	TEXTURE_ENEMY_S		"data/TEXTURE/enemy02.png"	// 読み込むテクスチャファイル名
#define	TEXTURE_ENEMY_A		"data/TEXTURE/enemy00.png"	// 読み込むテクスチャファイル名
#define	TEXTURE_ENEMY_D		"data/TEXTURE/enemy03.png"	// 読み込むテクスチャファイル名
#define	ENEMY_SIZE_X		(20.0f)						// ビルボードの幅
#define	ENEMY_SIZE_Y		(20.0f)						// ビルボードの高さ
#define	VALUE_MOVE_ENEMY	(0.30f)						// 移動速度
#define	VALUE_JUMP_ENEMY			(10.0f)				// ジャンプ力
#define	VALUE_GRAVITY_ENEMY			(0.45f)				// 重力
#define	RATE_REGIST_ENEMY			(0.075f)			// 抵抗係数
#define	RATE_REFRECT_ENEMY			(-0.90f)			// 反射係数
#define ENEMY_HP_MAX				(150.0f)			// HP最大値
//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct 
{
	D3DXMATRIX				world;				// ワールドマトリックス
	D3DXVECTOR3				pos;				// 位置
	D3DXVECTOR3				scl;				// スケール
	D3DXVECTOR3				move;				// 移動量
	D3DXVECTOR3				rot;				// 回転量
	int						hp;					// hp
	int						kill;				// 必殺技ゲージ
	int						shadowId;			// 影ID
	D3DXVECTOR2				SizeShadow;			// 影のサイズ
	D3DXCOLOR				colShadow;			// 影の色
	VERTEX_3D               *vectex;			// 頂点バッファへのポインタ
	bool					damage;				// ダメージフラグ
	bool					norSk;				// 特殊弾のフラグ
	int						timeSk;				// 特殊弾のタイムカウント
	bool					defSk;				// 特殊弾のフラグ
	int						timeDefSk;			// 特殊弾のタイムカウント
	bool					supSk;				// 特殊弾のフラグ
											

}ENEMY;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
ENEMY *GetEnemy(void);
#endif

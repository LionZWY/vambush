//=============================================================================
//
// ビルボード処理 [player.h]
// Author : 朱文渊
// プログラム作成日 : 2018/3/09
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_PLAYER_W			"data/TEXTURE/player01.png"		// 読み込むテクスチャファイル名
#define	TEXTURE_PLAYER_S			"data/TEXTURE/player02.png"		// 読み込むテクスチャファイル名
#define	TEXTURE_PLAYER_A			"data/TEXTURE/player00.png"		// 読み込むテクスチャファイル名
#define	TEXTURE_PLAYER_D			"data/TEXTURE/player03.png"		// 読み込むテクスチャファイル名
#define	PLAYER_SIZE_X				(20.0f)							// ビルボードの幅
#define	PLAYER_SIZE_Y				(20.0f)							// ビルボードの高さ
#define	VALUE_MOVE_PLAYER			(0.30f)							// 移動速度
#define	VALUE_JUMP_PLAYER			(10.0f)							// ジャンプ力
#define	VALUE_GRAVITY_PLAYER		(0.45f)							// 重力
#define	RATE_REGIST_PLAYER			(0.075f)						// 抵抗係数
#define	RATE_REFRECT_PLAYER			(-0.90f)						// 反射係数
#define PLAYER_HP_MAX				(150)							// HP最大値
#define TEXTURE_PATTERN_DIVIDE_X	(4)
#define TEXTURE_PATTERN_DIVIDE_Y	(3)
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
	bool					defSk;				// 特殊弾のタイムカウント
	int						timeDefSk;			// 特殊弾のフラグ
	int						timeSk;				// 特殊弾のタイムカウント
	bool					supSk;				// 特殊弾のフラグ

}PLAYER;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER *GetPlayer(void);
#endif

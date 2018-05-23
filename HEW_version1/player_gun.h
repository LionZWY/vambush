//=============================================================================
//
// 銃処理 [playergun.h]
// Author : 朱文渊
// プログラム作成日 : 2018/3/09
//=============================================================================
#ifndef _PLAYERGUN_H_
#define _PLAYERGUN_H_

#include "main.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	PLAYERGUN_CAR		"data/MODEL/gun_1.x"							// 読み込む銃名

#define	VALUE_MOVE		(5.0f)											// 移動量
#define	VALUE_ROTATE	(D3DX_PI * 0.02f)								// 回転量
#define VALUE_ROTATE_PLAYERGUN	(D3DX_PI * 0.05f)
#define	NUM_LIGHT		(3)
#define PLAYERGUN_ROTTIME	(0.5f)
//*****************************************************************************
// グローバル変数
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3			pos;				// 銃の位置
	D3DXVECTOR3			rot;				// 銃の向き(回転)
	D3DXVECTOR3			rotDest;			// 回転目的への差分
	float				diffRot;
	D3DXVECTOR3			scl;				// 銃の大きさ(スケール)
	D3DXVECTOR3			face;				// 銃の向き


	D3DXMATRIX			world;				// ワールドマトリックス

}PLAYERGUN;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPlayerGun(void);
void UninitPlayerGun(void);
void UpdatePlayerGun(void);
void DrawPlayerGun(void);
PLAYERGUN *GetPlayerGun(void);
#endif

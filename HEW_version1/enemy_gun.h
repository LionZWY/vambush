//=============================================================================
//
// 銃処理 [enemygun.h]
// Author : 朱文渊
// プログラム作成日 : 2018/3/09
//=============================================================================
#ifndef _ENEMYGUN_H_
#define _ENEMYGUN_H_

#include "main.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	ENEMYGUN_CAR		"data/MODEL/gun_2.x"						// 読み込む銃名

#define	VALUE_MOVE				(5.0f)									// 移動量					
#define VALUE_ROTATE_ENEMYGUN	(D3DX_PI * 0.05f)						// 回転量
#define ENEMYGUN_ROTTIME		(0.5f)									// 回転速度
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

}ENEMYGUN;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEnemyGun(void);
void UninitEnemyGun(void);
void UpdateEnemyGun(void);
void DrawEnemyGun(void);
ENEMYGUN *GetEnemyGun(void);
#endif

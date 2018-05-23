//=============================================================================
//
// ビルボード処理 [cursor.h]
// Author : 朱文渊
// プログラム作成日 : 2018/3/09
//=============================================================================
#ifndef _CURSOR_ENEMY_H_
#define _CURSOR_ENEMY_H_

#include "main.h"

typedef struct 
{
	D3DXMATRIX				world;				// ワールドマトリックス
	D3DXVECTOR3				pos;				// 位置
	D3DXVECTOR3				scl;				// スケール
	D3DXVECTOR3				move;				// 移動量
	D3DXVECTOR3				rot;				// 回転量
	int						shadowId;			// 影ID
	float					SizeShadow;			// 影のサイズ
	D3DXCOLOR				colShadow;			// 影の色
	VERTEX_3D               *vectex;
	D3DXVECTOR2				size;				// カーソルのサイズ
	float					ECtoEPDistance;		// カーソルから視点への距離
	bool					lock;

}CURSOR_ENEMY;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitCursorEnemy(void);
void UninitCursorEnemy(void);
void UpdateCursorEnemy(void);
void DrawCursorEnemy(void);
CURSOR_ENEMY *GetCursorEnemy(void);
void CheckHitPandC(void);
#endif

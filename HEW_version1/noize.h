//=============================================================================
//
// 爆発処理 [noize.h]
// Author : 朱文渊
// プログラム作成日 : 2018/3/09
//=============================================================================
#ifndef _NOIZE_H_
#define _NOIZE_H_

#include "main.h"

//**************************************
// 種類
//**************************************
enum
{
	NOIZETYPE_NOIZE_PLAYER = 0,		// プレイヤーの弾の爆発
	NOIZETYPE_NOIZE_ENEMY,			// 敵の弾の爆発
	NOIZETYPE_MAX
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitNoize(void);
void UninitNoize(void);
void UpdateNoize(void);
void DrawNoize(void);

int SetNoize(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nType);

#endif

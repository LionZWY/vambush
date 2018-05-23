//=============================================================================
//
// エフェクト処理 [effect.h]
// Author : 朱文渊
// プログラム作成日 : 2018/3/09
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{

			D3DXMATRIX			world;
			D3DXVECTOR3			pos;		// 位置
			D3DXVECTOR3			rot;		// 回転
			D3DXVECTOR3			scl;		// スケール
			D3DXVECTOR3			move;		// 移動量
			D3DXCOLOR			col;		// 色
			D3DXVECTOR2			size;
			int					timer;		// タイマー
			float				nDecAlpha;	// 減衰値
			bool				bUse;		// 使用しているかどうか
} EFFECT;


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);

int SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, D3DXVECTOR2 size, int timer);

#endif

//=============================================================================
//
// 影処理 [shadow.h]
// Author : 朱文渊 
// プログラム作成日 : 2018/3/09
//=============================================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);

int CreateShadow(D3DXVECTOR3 pos, D3DXVECTOR2 size);
void ReleaseShadow(int nIdxShadow);
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos);
void SetVertexShadow(int nIdxShadow, D3DXVECTOR2 size);
void SetColorShadow(int nIdxShadow, D3DXCOLOR col);

#endif

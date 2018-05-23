//=============================================================================
//
// カメラ処理 [camera.h]
// Author : 朱文渊
// プログラム作成日 : 2018/3/09
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"


typedef struct 
{
	D3DXVECTOR3		posEye;				// カメラの視点
	D3DXVECTOR3		posAt;				// カメラの注視点
	D3DXVECTOR3		vecUp;				// カメラの上方向
	D3DXVECTOR3		rot;				// カメラの回転
	float			EyeToAtDistance;	// カメラの視点と注視点の距離
	D3DXMATRIX		view;				// ビューマトリックス
	D3DXMATRIX		proj;				// プロジェクションマトリックス
	D3DXVECTOR3		PTPVec;				// プレイヤー間のベクトル
	float			PTPDistance;		// プレイヤー間の距離

}CAMERA;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);

void SetCamera(void);
D3DXVECTOR3 GetRotCamera(void);
D3DXMATRIX GetMtxView(void);

CAMERA *GetCamera(void);
#endif

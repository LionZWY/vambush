//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author : 朱文渊
// プログラム作成日 : 2018/3/09
//
//=============================================================================
#include "camera.h"
#include "input.h"
#include "enemy.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	CAM_POS_P_X			(0.0f)					// カメラの視点初期位置(X座標)
#define	CAM_POS_P_Y			(150.0f)				// カメラの視点初期位置(Y座標)
#define	CAM_POS_P_Z			(0.0f)					// カメラの視点初期位置(Z座標)
#define	CAM_POS_R_X			(0.0f)					// カメラの注視点初期位置(X座標)
#define	CAM_POS_R_Y			(0.0f)					// カメラの注視点初期位置(Y座標)
#define	CAM_POS_R_Z			(0.0f)					// カメラの注視点初期位置(Z座標)
#define	VIEW_ANGLE			(D3DXToRadian(45.0f))							// ビュー平面の視野角
#define	VIEW_ASPECT			((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// ビュー平面のアスペクト比
#define	VIEW_NEAR_Z			(10.0f)											// ビュー平面のNearZ値
#define	VIEW_FAR_Z			(5000.0f)										// ビュー平面のFarZ値
#define	VALUE_MOVE_CAMERA	(2.0f)											// カメラの移動量
#define	VALUE_ROTATE_CAMERA	(D3DX_PI * 0.01f)								// カメラの回転量

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

CAMERA				cameraWk[1];
//*****************************************************************************
// グローバル変数
//*****************************************************************************


//=============================================================================
// カメラの初期化処理
//=============================================================================
HRESULT InitCamera(void)
{
	CAMERA *camera = cameraWk;
	PLAYER *player = GetPlayer();
	ENEMY *enemy = GetEnemy();

	camera->posEye = D3DXVECTOR3(CAM_POS_P_X, CAM_POS_P_Y, CAM_POS_P_Z);
	camera->posAt = D3DXVECTOR3(CAM_POS_R_X, CAM_POS_R_X, CAM_POS_R_X);
	camera->vecUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	camera->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//エネミーとプレイヤーの距離
	float pVecX, pVecZ;
	pVecX = enemy->pos.x - player->pos.x;
	pVecZ = enemy->pos.z - player->pos.z;
	camera->PTPDistance = (sqrtf(pVecX * pVecX + pVecZ * pVecZ));

	//カメラ視点と注視点の距離
	float fVecX,fVecZ;
	fVecX = camera->posEye.x - camera->posAt.x;
	fVecZ = camera->posEye.z - camera->posAt.z;
	camera->EyeToAtDistance = sqrtf(fVecX * fVecX + fVecZ * fVecZ);



	return S_OK;
}

//=============================================================================
// カメラの終了処理
//=============================================================================
void UninitCamera(void)
{

}

//=============================================================================
// カメラの更新処理
//=============================================================================
void UpdateCamera(void)
{
	CAMERA *camera = cameraWk;
	PLAYER *player = GetPlayer();
	ENEMY *enemy = GetEnemy();

	//エネミーとプレイヤーの距離の更新
	float pVecX, pVecZ;
	pVecX = enemy->pos.x - player->pos.x;
	pVecZ = enemy->pos.z - player->pos.z;
	camera->PTPDistance = (sqrtf(pVecX * pVecX + pVecZ * pVecZ));
	camera->PTPVec = enemy->pos - player->pos;
	camera->PTPVec /= D3DXVec3Length(&camera->PTPVec);

	//カメラ視点と注視点の距離の更新
	float fVecX, fVecZ;
	fVecX = camera->posEye.x - camera->posAt.x;
	fVecZ = camera->posEye.z - camera->posAt.z;
	camera->EyeToAtDistance = sqrtf(fVecX * fVecX + fVecZ * fVecZ);


	//注視点と視点の更新処理
	if (GetKeyboardPress(DIK_Y))
	{// 視点移動「上」
		camera->posEye.y += VALUE_MOVE_CAMERA;
	}
	if (GetKeyboardPress(DIK_N))
	{// 視点移動「下」
		camera->posEye.y -= VALUE_MOVE_CAMERA;
	}

	if (player->pos == enemy->pos)
	{
		camera->posAt.x = player->pos.x;
		camera->posAt.z = player->pos.z;
	}
	else
	{
		camera->posAt.x = player->pos.x + camera->PTPVec.x * (camera->PTPDistance / 2);
		camera->posAt.z = player->pos.z + camera->PTPVec.z * (camera->PTPDistance / 2);
	}

	camera->posEye.x = camera->posAt.x - sinf(camera->rot.y) * camera->PTPDistance;
	if ((camera->PTPDistance >= 100.0f) && (camera->PTPDistance <= 630.0f))
	{

		camera->posEye.z = camera->posAt.z - cosf(camera->rot.y) * camera->PTPDistance;
		camera->posEye.y = camera->PTPDistance;
	}
	else
	{
		camera->posEye.z = camera->posAt.z - cosf(camera->rot.y) * camera->EyeToAtDistance;
		if (camera->PTPDistance < 300.0f)
		{
			camera->posEye.y = 100.0f;
		}
		else
		{
			camera->posEye.y = 630.0f;
		}
	}

}

//=============================================================================
// カメラの設定処理
//=============================================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice(); 
	CAMERA *camera = cameraWk;

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&camera->view);

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&camera->view, 
						&camera->posEye,		// カメラの視点
						&camera->posAt,			// カメラの注視点
						&camera->vecUp);		// カメラの上方向

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &camera->view);


	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&camera->proj);

	// プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&camera->proj,
								VIEW_ANGLE,			// ビュー平面の視野角
								VIEW_ASPECT,		// ビュー平面のアスペクト比
								VIEW_NEAR_Z,		// ビュー平面のNearZ値
								VIEW_FAR_Z);		// ビュー平面のFarZ値

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &camera->proj);
}

//=============================================================================
// カメラの向きの取得
//=============================================================================
D3DXVECTOR3 GetRotCamera(void)
{
	CAMERA *camera = cameraWk;

	return camera->rot;
}

//=============================================================================
// ビューマトリックスの取得
//=============================================================================
D3DXMATRIX GetMtxView(void)
{
	CAMERA *camera = cameraWk;

	return camera->view;
}

CAMERA *GetCamera(void)
{
	return cameraWk;
}
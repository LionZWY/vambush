//=============================================================================
//
// モデル処理 [playergun.cpp]
// Author : 朱文渊
// プログラム作成日 : 2018/3/09
//=============================================================================
#include "player_gun.h"
#include "input.h"
#include "camera.h"
#include "field.h"
#include "player.h"
#include "player_cursor.h"


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTexturePlayerGun;		// テクスチャへのポインタ

LPD3DXMESH			g_pD3DXMeshPlayerGun;		// メッシュ情報へのポインタ
LPD3DXBUFFER		g_pD3DXBuffMatPlayerGun;	// マテリアル情報へのポインタ
DWORD				g_nNumMatPlayerGun;			// マテリアル情報の数

PLAYERGUN				playergunWK[1];
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayerGun(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYERGUN *playergun = playergunWK;
	PLAYER *player = GetPlayer();


	// 位置・回転・スケールの初期設定
	playergun->pos = D3DXVECTOR3(player->pos.x, player->pos.y, player->pos.z);
	playergun->rot = D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f);
	playergun->rotDest = D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f);
	playergun->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	playergun->face = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	playergun->face = playergun->face - playergun->pos;

	// モデル関係の初期化
	g_pD3DTexturePlayerGun = NULL;
	g_pD3DXMeshPlayerGun = NULL;
	g_pD3DXBuffMatPlayerGun = NULL;
	g_nNumMatPlayerGun = 0;

	//Xファイルの読み込み
	if (FAILED(D3DXLoadMeshFromX(PLAYERGUN_CAR,	//モデルデータ
		D3DXMESH_SYSTEMMEM,								//使用するメモリのオプション
		pDevice,										//デバイス
		NULL,											//未使用
		&g_pD3DXBuffMatPlayerGun,							//マテリアルデータへのポインタ
		NULL,											//未使用
		&g_nNumMatPlayerGun,								//D3DXMATERIAL構造体の数
		&g_pD3DXMeshPlayerGun)))							//メッシュデータへのポインタ
	{
		return E_FAIL;
	}

	

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayerGun(void)
{
	if(g_pD3DTexturePlayerGun != NULL)
	{// テクスチャの開放
		g_pD3DTexturePlayerGun->Release();
		g_pD3DTexturePlayerGun = NULL;
	}

	if(g_pD3DXMeshPlayerGun != NULL)
	{// メッシュの開放
		g_pD3DXMeshPlayerGun->Release();
		g_pD3DXMeshPlayerGun = NULL;
	}

	if(g_pD3DXBuffMatPlayerGun != NULL)
	{// マテリアルの開放
		g_pD3DXBuffMatPlayerGun->Release();
		g_pD3DXBuffMatPlayerGun = NULL;
	}
}

//=============================================================================
// 更新処理 
//=============================================================================
void UpdatePlayerGun(void)
{
	CAMERA *camera = GetCamera();
	PLAYERGUN *playergun = playergunWK;
	PLAYER *player = GetPlayer();
	CURSOR_PLAYER *Pcursor = GetCursorPlayer();

	playergun->pos = player->pos;

	//D3DXVECTOR3 vecEM;
	//vecEM = Pcursor->pos - playergun->pos;
	//D3DXVECTOR3 vec;
	//D3DXVec3Cross(&vec, &playergun->face, &vecEM);
	//if (vec.y > 0)
	//{
	//	playergun->face.x = playergun->face.x*cosf(-VALUE_ROTATE_PLAYERGUN) - playergun->face.z*sinf(-VALUE_ROTATE_PLAYERGUN);
	//	playergun->face.z = playergun->face.z*cosf(-VALUE_ROTATE_PLAYERGUN) + playergun->face.x*sinf(-VALUE_ROTATE_PLAYERGUN);
	//	playergun->rotDest.y += VALUE_ROTATE_PLAYERGUN;
	//	if (playergun->rotDest.y > D3DX_PI)
	//	{
	//		// 360度を超えたら360度を引く
	//		playergun->rotDest.y -= D3DX_PI * 2.0f;
	//	}

	//}
	//else if (vec.y < 0)
	//{
	//	playergun->face.x = playergun->face.x*cosf(VALUE_ROTATE_PLAYERGUN) - playergun->face.z*sinf(VALUE_ROTATE_PLAYERGUN);
	//	playergun->face.z = playergun->face.z*cosf(VALUE_ROTATE_PLAYERGUN) + playergun->face.x*sinf(VALUE_ROTATE_PLAYERGUN);
	//	playergun->rotDest.y -= VALUE_ROTATE_PLAYERGUN;
	//	if (playergun->rotDest.y < -D3DX_PI)
	//	{
	//		// 360度を超えたら360度を引く
	//		playergun->rotDest.y += D3DX_PI * 2.0f;
	//	}
	//}
	//else if (vec.y == 0)
	//{
	//	playergun->face.x = playergun->face.x;
	//	playergun->face.z = playergun->face.z;
	//}

	playergun->rotDest.y = atan2(Pcursor->pos.x - playergun->pos.x, Pcursor->pos.z - playergun->pos.z);
	playergun->rotDest.y -= D3DX_PI;

	playergun->diffRot = playergun->rotDest.y - playergun->rot.y;
	if (playergun->diffRot > D3DX_PI)
	{
		playergun->diffRot -= D3DX_PI*2.0f;
	}
	if (playergun->diffRot < -D3DX_PI)
	{
		playergun->diffRot += D3DX_PI*2.0f;
	}

	playergun->rot.y += playergun->diffRot*PLAYERGUN_ROTTIME;
	if (playergun->rot.y > D3DX_PI)
	{
		// 360度を超えたら360度を引く
		playergun->rot.y -= D3DX_PI * 2.0f;
	}
	if (playergun->rot.y < -D3DX_PI)
	{
		// 360度を超えたら360度を引く
		playergun->rot.y += D3DX_PI * 2.0f;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayerGun(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	PLAYERGUN *playergun = playergunWK;
	CAMERA *camera = GetCamera();


	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&playergun->world);


	// スケールを反映
	D3DXMatrixScaling(&mtxScl, playergun->scl.x, playergun->scl.y, playergun->scl.z);
	D3DXMatrixMultiply(&playergun->world, &playergun->world, &mtxScl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, playergun->rot.y, playergun->rot.x, playergun->rot.z);
	D3DXMatrixMultiply(&playergun->world, &playergun->world, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, playergun->pos.x, playergun->pos.y, playergun->pos.z);
	D3DXMatrixMultiply(&playergun->world, &playergun->world, &mtxTranslate);


	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &playergun->world);

	// モデルの描画

	//現在のマテリアルを保存
	pDevice->GetMaterial(&matDef);

	//マテリアル情報へのポインタを取得
	pD3DXMat = (D3DXMATERIAL*)g_pD3DXBuffMatPlayerGun->GetBufferPointer();

	for (int i = 0;i < (int)g_nNumMatPlayerGun;i++)
	{
		pDevice->SetMaterial(&pD3DXMat[i].MatD3D);	//マテリアルの設定
		pDevice->SetTexture(0, g_pD3DTexturePlayerGun);	//テクスチャの設定
		g_pD3DXMeshPlayerGun->DrawSubset(i);
	}

	//マテリアルを元に戻す
	pDevice->SetMaterial(&matDef);


}


PLAYERGUN *GetPlayerGun(void)
{
	return playergunWK;
}

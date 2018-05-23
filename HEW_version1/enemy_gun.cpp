//=============================================================================
//
// 銃処理 [enemygun.cpp]
// Author : 朱文渊
// プログラム作成日 : 2018/3/09
//=============================================================================
#include "enemy_gun.h"
#include "input.h"
#include "camera.h"
#include "field.h"
#include "enemy.h"
#include "enemy_cursor.h"


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTextureEnemyGun;		// テクスチャへのポインタ

LPD3DXMESH			g_pD3DXMeshEnemyGun;		// メッシュ情報へのポインタ
LPD3DXBUFFER		g_pD3DXBuffMatEnemyGun;	// マテリアル情報へのポインタ
DWORD				g_nNumMatEnemyGun;			// マテリアル情報の数

ENEMYGUN				enemygunWK[1];
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEnemyGun(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMYGUN *enemygun = enemygunWK;
	ENEMY *enemy = GetEnemy();


	// 位置・回転・スケールの初期設定
	enemygun->pos = D3DXVECTOR3(enemy->pos.x, enemy->pos.y, enemy->pos.z);
	enemygun->rot = D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f);
	enemygun->rotDest = D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f);
	enemygun->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	enemygun->face = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
	enemygun->face = enemygun->face - enemygun->pos;

	// モデル関係の初期化
	g_pD3DTextureEnemyGun = NULL;
	g_pD3DXMeshEnemyGun = NULL;
	g_pD3DXBuffMatEnemyGun = NULL;
	g_nNumMatEnemyGun = 0;

	//Xファイルの読み込み
	if (FAILED(D3DXLoadMeshFromX(ENEMYGUN_CAR,	//モデルデータ
		D3DXMESH_SYSTEMMEM,								//使用するメモリのオプション
		pDevice,										//デバイス
		NULL,											//未使用
		&g_pD3DXBuffMatEnemyGun,							//マテリアルデータへのポインタ
		NULL,											//未使用
		&g_nNumMatEnemyGun,								//D3DXMATERIAL構造体の数
		&g_pD3DXMeshEnemyGun)))							//メッシュデータへのポインタ
	{
		return E_FAIL;
	}

	

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemyGun(void)
{
	if(g_pD3DTextureEnemyGun != NULL)
	{// テクスチャの開放
		g_pD3DTextureEnemyGun->Release();
		g_pD3DTextureEnemyGun = NULL;
	}

	if(g_pD3DXMeshEnemyGun != NULL)
	{// メッシュの開放
		g_pD3DXMeshEnemyGun->Release();
		g_pD3DXMeshEnemyGun = NULL;
	}

	if(g_pD3DXBuffMatEnemyGun != NULL)
	{// マテリアルの開放
		g_pD3DXBuffMatEnemyGun->Release();
		g_pD3DXBuffMatEnemyGun = NULL;
	}
}

//=============================================================================
// 更新処理 
//=============================================================================
void UpdateEnemyGun(void)
{
	CAMERA *camera = GetCamera();
	ENEMYGUN *enemygun = enemygunWK;
	ENEMY *enemy = GetEnemy();
	CURSOR_ENEMY *Pcursor = GetCursorEnemy();

	//位置の更新
	enemygun->pos = enemy->pos;

	//回転の更新
	enemygun->rotDest.y = atan2(Pcursor->pos.x - enemygun->pos.x, Pcursor->pos.z - enemygun->pos.z);
	enemygun->rotDest.y -= D3DX_PI;

	enemygun->diffRot = enemygun->rotDest.y - enemygun->rot.y;
	if (enemygun->diffRot > D3DX_PI)
	{
		enemygun->diffRot -= D3DX_PI*2.0f;
	}
	if (enemygun->diffRot < -D3DX_PI)
	{
		enemygun->diffRot += D3DX_PI*2.0f;
	}

	enemygun->rot.y += enemygun->diffRot*ENEMYGUN_ROTTIME;
	if (enemygun->rot.y > D3DX_PI)
	{
		// 360度を超えたら360度を引く
		enemygun->rot.y -= D3DX_PI * 2.0f;
	}
	if (enemygun->rot.y < -D3DX_PI)
	{
		// 360度を超えたら360度を引く
		enemygun->rot.y += D3DX_PI * 2.0f;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemyGun(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	ENEMYGUN *enemygun = enemygunWK;
	CAMERA *camera = GetCamera();

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&enemygun->world);

	// スケールを反映
	D3DXMatrixScaling(&mtxScl, enemygun->scl.x, enemygun->scl.y, enemygun->scl.z);
	D3DXMatrixMultiply(&enemygun->world, &enemygun->world, &mtxScl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, enemygun->rot.y, enemygun->rot.x, enemygun->rot.z);
	D3DXMatrixMultiply(&enemygun->world, &enemygun->world, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, enemygun->pos.x, enemygun->pos.y, enemygun->pos.z);
	D3DXMatrixMultiply(&enemygun->world, &enemygun->world, &mtxTranslate);


	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &enemygun->world);

	// モデルの描画

	//現在のマテリアルを保存
	pDevice->GetMaterial(&matDef);

	//マテリアル情報へのポインタを取得
	pD3DXMat = (D3DXMATERIAL*)g_pD3DXBuffMatEnemyGun->GetBufferPointer();

	for (int i = 0;i < (int)g_nNumMatEnemyGun;i++)
	{
		pDevice->SetMaterial(&pD3DXMat[i].MatD3D);	//マテリアルの設定
		pDevice->SetTexture(0, g_pD3DTextureEnemyGun);	//テクスチャの設定
		g_pD3DXMeshEnemyGun->DrawSubset(i);
	}

	//マテリアルを元に戻す
	pDevice->SetMaterial(&matDef);


}


ENEMYGUN *GetEnemyGun(void)
{
	return enemygunWK;
}

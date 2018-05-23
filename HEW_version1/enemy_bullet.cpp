//=============================================================================
//
// 弾処理 [enemybullet.cpp]
// Author : 朱文渊
// プログラム作成日 : 2018/3/09
//=============================================================================
#include "enemy_bullet.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "effect.h"
#include "enemy.h"
#include "field.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexEnemyBullet(LPDIRECT3DDEVICE9 pDevice);
void SetVertexEnemyBullet(int nIdxBullet, D3DXVECTOR2 size);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureEnemyBullet1 = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffEnemyBullet = NULL;		// 頂点バッファインターフェースへのポインタ

ENEMY_BULLET					enemybulletWk[MAX_BULLET];			// 弾ワーク
int						enemybulletType;
LPDIRECT3DTEXTURE9		TextureEnemyEnemyBullet;
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEnemyBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY_BULLET *enemybullet = enemybulletWk;

	// 頂点情報の作成
	MakeVertexEnemyBullet(pDevice);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
		TEXTURE_BULLET_ENEMY,				// ファイルの名前
		&g_pD3DTextureEnemyBullet1);	// 読み込むメモリー



	for (int i = 0; i < MAX_BULLET; i++, enemybullet++)
	{
		enemybullet->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		enemybullet->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		enemybullet->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		enemybullet->move = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		enemybullet->size.x = BULLET_SIZE_X;
		enemybullet->size.y = BULLET_SIZE_Y;
		enemybullet->timer = 0;
		enemybullet->bUse = false;
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemyBullet(void)
{
	if (g_pD3DTextureEnemyBullet1 != NULL)
	{// テクスチャの開放
		g_pD3DTextureEnemyBullet1->Release();
		g_pD3DTextureEnemyBullet1 = NULL;
	}

	if (g_pD3DVtxBuffEnemyBullet != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffEnemyBullet->Release();
		g_pD3DVtxBuffEnemyBullet = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemyBullet(void)
{
	D3DXVECTOR3 rotCamera;
	ENEMY_BULLET *enemybullet = enemybulletWk;


	// カメラの回転を取得
	rotCamera = GetRotCamera();

	for (int i = 0; i < MAX_BULLET; i++, enemybullet++)
	{
		if (enemybullet->bUse)
		{
			enemybullet->pos.x += enemybullet->move.x;
			enemybullet->pos.z += enemybullet->move.z;

			enemybullet->timer--;
			if (enemybullet->timer <= 0)
			{
				ReleaseShadow(enemybullet->nIdxShadow);
				enemybullet->bUse = false;
			}
			else
			{
				// 影の位置設定
				SetPositionShadow(enemybullet->nIdxShadow, D3DXVECTOR3(enemybullet->pos.x, 0.1f, enemybullet->pos.z));

				// エフェクトの設定
				SetEffect(enemybullet->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(0.65f, 0.05f, 0.85f, 0.50f), D3DXVECTOR2(16.0f, 16.0f), 10);
				SetEffect(enemybullet->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(0.05f, 0.85f, 0.65f, 0.30f), D3DXVECTOR2(12.0f, 12.0f), 10);
				SetEffect(enemybullet->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(0.05f, 0.45f, 0.45f, 0.20f), D3DXVECTOR2(6.0f, 6.0f), 10);
			}

			D3DXVECTOR2	size;
			size.x = 8.0f + (enemybullet->pos.y - 4.0f) * 0.05f;
			if (size.x < 8.0f)
			{
				size.x = 8.0f;
			}
			size.y = 8.0f + (enemybullet->pos.y - 4.0f) * 0.05f;
			if (size.y < 8.0f)
			{
				size.y = 8.0f;
			}

			SetVertexShadow(enemybullet->nIdxShadow, size);

			float colA = (200.0f - (enemybullet->pos.y - 4.0f)) / 400.0f;
			if (colA < 0.0f)
			{
				colA = 0.0f;
			}
			SetColorShadow(enemybullet->nIdxShadow, D3DXCOLOR(1.0f, 1.0f, 1.0f, colA));

			if (enemybullet->pos.x < (BULLET_SIZE_X / 2) - FIELD_SCL_MAX_X)
			{
				DeleteEnemyBullet(i);
			}
			if (enemybullet->pos.x > FIELD_SCL_MAX_X - (BULLET_SIZE_X / 2))
			{
				DeleteEnemyBullet(i);
			}
			if (enemybullet->pos.z > FIELD_SCL_MAX_Z)
			{
				DeleteEnemyBullet(i);
			}
			if (enemybullet->pos.z < (BULLET_SIZE_Y / 2) - FIELD_SCL_MAX_Z)
			{
				DeleteEnemyBullet(i);
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemyBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxscl, mtxTranslate;
	ENEMY_BULLET *enemybullet = enemybulletWk;

	// ライティングを無効に
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// αテストを有効に
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (int i = 0; i < MAX_BULLET; i++, enemybullet++)
	{
		if (enemybullet->bUse)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&enemybullet->world);

			// ビューマトリックスを取得
			mtxView = GetMtxView();

			enemybullet->world._11 = mtxView._11;
			enemybullet->world._12 = mtxView._21;
			enemybullet->world._13 = mtxView._31;
			enemybullet->world._21 = mtxView._12;
			enemybullet->world._22 = mtxView._22;
			enemybullet->world._23 = mtxView._32;
			enemybullet->world._31 = mtxView._13;
			enemybullet->world._32 = mtxView._23;
			enemybullet->world._33 = mtxView._33;

			// スケールを反映
			D3DXMatrixScaling(&mtxscl, enemybullet->scl.x, enemybullet->scl.y, enemybullet->scl.z);
			D3DXMatrixMultiply(&enemybullet->world, &enemybullet->world, &mtxscl);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, enemybullet->pos.x, enemybullet->pos.y, enemybullet->pos.z);
			D3DXMatrixMultiply(&enemybullet->world, &enemybullet->world, &mtxTranslate);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &enemybullet->world);

			// 頂点バッファをデバイスのデータストリームにバインド
			pDevice->SetStreamSource(0, g_pD3DVtxBuffEnemyBullet, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pD3DTextureEnemyBullet1);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (i * 4), NUM_POLYGON);
		}
	}

	// ライティングを有効に
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}

//=============================================================================
// 頂点情報の作成
//=============================================================================
HRESULT MakeVertexEnemyBullet(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * MAX_BULLET,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,							// 頂点バッファの使用法　
		FVF_VERTEX_3D,								// 使用する頂点フォーマット
		D3DPOOL_MANAGED,							// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffEnemyBullet,						// 頂点バッファインターフェースへのポインタ
		NULL)))										// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffEnemyBullet->Lock(0, 0, (void**)&pVtx, 0);

		for (int i = 0; i < MAX_BULLET; i++, pVtx += 4)
		{
			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(-BULLET_SIZE_X / 2, -BULLET_SIZE_Y / 2, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(BULLET_SIZE_X / 2, -BULLET_SIZE_Y / 2, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(-BULLET_SIZE_X / 2, BULLET_SIZE_Y / 2, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(BULLET_SIZE_X / 2, BULLET_SIZE_Y / 2, 0.0f);

			// 法線の設定
			pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

			// 反射光の設定
			pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}

		// 頂点データをアンロックする
		g_pD3DVtxBuffEnemyBullet->Unlock();
	}

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexEnemyBullet(int nIdxEnemyBullet, D3DXVECTOR2 size)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffEnemyBullet->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxEnemyBullet * 4);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(-size.x / 2, -size.y / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-size.x / 2, size.y / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(size.x / 2, -size.y / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(size.x / 2, size.y / 2, 0.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffEnemyBullet->Unlock();
	}
}

//=============================================================================
// 弾の設定
//=============================================================================
int SetEnemyBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 size, int timer)
{
	ENEMY_BULLET *enemybullet = enemybulletWk;

	int nIdxEnemyBullet = -1;

	enemybullet = GetEnemyBullet(0);
	for (int i = 0; i < MAX_BULLET; i++, enemybullet++)
	{
		if (!enemybullet->bUse)
		{

			enemybullet->pos = pos;
			enemybullet->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			enemybullet->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			enemybullet->move = move;
			enemybullet->size.x = size.x;
			enemybullet->size.y = size.y;
			enemybullet->timer = timer;
			enemybullet->bUse = true;

			// 影の設定
			enemybullet->nIdxShadow = CreateShadow(pos, D3DXVECTOR2(8.0f, 8.0f));		// 影の設定

																						// 頂点座標の設定
			SetVertexEnemyBullet(i, size);

			nIdxEnemyBullet = i;

			break;
		}
	}

	return nIdxEnemyBullet;
}

//=============================================================================
// 弾の削除
//=============================================================================
void DeleteEnemyBullet(int nIdxEnemyBullet)
{
	if (nIdxEnemyBullet >= 0 && nIdxEnemyBullet < MAX_BULLET)
	{
		ReleaseShadow(enemybulletWk[nIdxEnemyBullet].nIdxShadow);
		enemybulletWk[nIdxEnemyBullet].bUse = false;
	}
}

int GetEnemyBulletType(void)
{
	return enemybulletType;
}

ENEMY_BULLET *GetEnemyBullet(int no)
{
	return(&enemybulletWk[no]);
}
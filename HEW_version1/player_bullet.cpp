//=============================================================================
//
// 通常弾処理 [playerplayerbullet.cpp]
// Author : 朱文渊
// プログラム作成日 : 2018/3/09
//=============================================================================
#include "player_bullet.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "effect.h"
#include "player.h"
#include "field.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexPlayerBullet(LPDIRECT3DDEVICE9 pDevice);
void SetVertexPlayerBullet(int nIdxBullet, D3DXVECTOR2 size);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTexturePlayerBullet = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffPlayerBullet	= NULL;		// 頂点バッファインターフェースへのポインタ

PLAYER_BULLET					playerbulletWk[MAX_BULLET];			// 弾ワーク
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayerBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER_BULLET *playerbullet = playerbulletWk;

	// 頂点情報の作成
	MakeVertexPlayerBullet(pDevice);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
								TEXTURE_BULLET_PLAYER,				// ファイルの名前
								&g_pD3DTexturePlayerBullet);	// 読み込むメモリー

													

	for(int i = 0; i < MAX_BULLET; i++, playerbullet++)
	{
		playerbullet->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		playerbullet->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		playerbullet->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		playerbullet->move = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		playerbullet->size.x = BULLET_SIZE_X;
		playerbullet->size.y = BULLET_SIZE_Y;
		playerbullet->timer = 0;
		playerbullet->bUse = false;
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayerBullet(void)
{
	if(g_pD3DTexturePlayerBullet != NULL)
	{// テクスチャの開放
		g_pD3DTexturePlayerBullet->Release();
		g_pD3DTexturePlayerBullet = NULL;
	}

	if(g_pD3DVtxBuffPlayerBullet != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffPlayerBullet->Release();
		g_pD3DVtxBuffPlayerBullet = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayerBullet(void)
{
	D3DXVECTOR3 rotCamera;
	PLAYER_BULLET *playerbullet = playerbulletWk;


	// カメラの回転を取得
	rotCamera = GetRotCamera();

 for(int i = 0; i < MAX_BULLET; i++, playerbullet++)
	{
		if(playerbullet->bUse)
		{
			playerbullet->pos.x += playerbullet->move.x;
			playerbullet->pos.z += playerbullet->move.z;

			playerbullet->timer--;
			if(playerbullet->timer <= 0)
			{
				ReleaseShadow(playerbullet->nIdxShadow);
				playerbullet->bUse = false;
			}
			else
			{
				// 影の位置設定
				SetPositionShadow(playerbullet->nIdxShadow, D3DXVECTOR3(playerbullet->pos.x, 0.1f, playerbullet->pos.z));


				// エフェクトの設定
				SetEffect(playerbullet->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(0.85f, 0.05f, 0.15f, 0.50f), D3DXVECTOR2(16.0f, 16.0f), 10);
				SetEffect(playerbullet->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(0.65f, 0.10f, 0.10f, 0.30f), D3DXVECTOR2(12.0f, 12.0f), 10);
				SetEffect(playerbullet->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(0.45f, 0.15f, 0.05f, 0.20f), D3DXVECTOR2(6.0f, 6.0f), 10);


			}

			D3DXVECTOR2	size;
			size.x = 8.0f + (playerbullet->pos.y - 4.0f) * 0.05f;
			if(size.x < 8.0f)
			{
				size.x = 8.0f;
			}
			size.y = 8.0f + (playerbullet->pos.y - 4.0f) * 0.05f;
			if(size.y < 8.0f)
			{
				size.y = 8.0f;
			}

			SetVertexShadow(playerbullet->nIdxShadow, size);

			float colA = (200.0f - (playerbullet->pos.y - 4.0f)) / 400.0f;
			if(colA < 0.0f)
			{
				colA = 0.0f;
			}
			SetColorShadow(playerbullet->nIdxShadow, D3DXCOLOR(1.0f, 1.0f, 1.0f, colA));

			if (playerbullet->pos.x < (BULLET_SIZE_X / 2) - FIELD_SCL_MAX_X)
			{
				DeletePlayerBullet(i);
			}
			if (playerbullet->pos.x > FIELD_SCL_MAX_X - (BULLET_SIZE_X / 2))
			{
				DeletePlayerBullet(i);
			}
			if (playerbullet->pos.z > FIELD_SCL_MAX_Z)
			{
				DeletePlayerBullet(i);
			}
			if (playerbullet->pos.z < (BULLET_SIZE_Y / 2) - FIELD_SCL_MAX_Z)
			{
				DeletePlayerBullet(i);
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayerBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView,mtxscl,mtxTranslate;
	PLAYER_BULLET *playerbullet = playerbulletWk;

	// ライティングを無効に
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// αテストを有効に
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

 for(int i = 0; i < MAX_BULLET; i++, playerbullet++)
	{
		if(playerbullet->bUse)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&playerbullet->world);

			// ビューマトリックスを取得
			mtxView = GetMtxView();

			playerbullet->world._11 = mtxView._11;
			playerbullet->world._12 = mtxView._21;
			playerbullet->world._13 = mtxView._31;
			playerbullet->world._21 = mtxView._12;
			playerbullet->world._22 = mtxView._22;
			playerbullet->world._23 = mtxView._32;
			playerbullet->world._31 = mtxView._13;
			playerbullet->world._32 = mtxView._23;
			playerbullet->world._33 = mtxView._33;

			// スケールを反映
			D3DXMatrixScaling(&mtxscl, playerbullet->scl.x, playerbullet->scl.y, playerbullet->scl.z);
			D3DXMatrixMultiply(&playerbullet->world, &playerbullet->world, &mtxscl);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, playerbullet->pos.x, playerbullet->pos.y, playerbullet->pos.z);
			D3DXMatrixMultiply(&playerbullet->world, &playerbullet->world, &mtxTranslate);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &playerbullet->world);

			// 頂点バッファをデバイスのデータストリームにバインド
			pDevice->SetStreamSource(0, g_pD3DVtxBuffPlayerBullet, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pD3DTexturePlayerBullet);

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
HRESULT MakeVertexPlayerBullet(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
    if( FAILED( pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * MAX_BULLET,	// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,							// 頂点バッファの使用法　
												FVF_VERTEX_3D,								// 使用する頂点フォーマット
												D3DPOOL_MANAGED,							// リソースのバッファを保持するメモリクラスを指定
												&g_pD3DVtxBuffPlayerBullet,						// 頂点バッファインターフェースへのポインタ
												NULL)))										// NULLに設定
	{
        return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffPlayerBullet->Lock(0, 0, (void**)&pVtx, 0);

		for(int i = 0; i < MAX_BULLET; i++, pVtx += 4)
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
		g_pD3DVtxBuffPlayerBullet->Unlock();
	}

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexPlayerBullet(int nIdxPlayerBullet, D3DXVECTOR2 size)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffPlayerBullet->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxPlayerBullet * 4);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(-size.x / 2, -size.y / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-size.x / 2, size.y / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(size.x / 2, -size.y / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(size.x / 2, size.y / 2, 0.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffPlayerBullet->Unlock();
	}
}

//=============================================================================
// 弾の設定
//=============================================================================
int SetPlayerBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 size, int timer)
{
	PLAYER_BULLET *playerbullet = playerbulletWk;

	int nIdxPlayerBullet = -1;

	playerbullet = GetPlayerBullet(0);
 for(int i = 0; i < MAX_BULLET; i++, playerbullet++)
	{
		if(!playerbullet->bUse)
		{

			playerbullet->pos = pos;
			playerbullet->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			playerbullet->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			playerbullet->move = move;
			playerbullet->size.x = size.x;
			playerbullet->size.y = size.y;
			playerbullet->timer = timer;
			playerbullet->bUse = true;

			// 影の設定
			playerbullet->nIdxShadow = CreateShadow(pos, D3DXVECTOR2(8.0f, 8.0f));		// 影の設定

			// 頂点座標の設定
			SetVertexPlayerBullet(i, size);

			nIdxPlayerBullet = i;

			break;
		}
	}

	return nIdxPlayerBullet;
}

//=============================================================================
// 弾の削除
//=============================================================================
void DeletePlayerBullet(int nIdxPlayerBullet)
{
	if(nIdxPlayerBullet >= 0 && nIdxPlayerBullet < MAX_BULLET)
	{
		ReleaseShadow(playerbulletWk[nIdxPlayerBullet].nIdxShadow);
		playerbulletWk[nIdxPlayerBullet].bUse = false;
	}
}


PLAYER_BULLET *GetPlayerBullet(int no)
{
	return(&playerbulletWk[no]);
}
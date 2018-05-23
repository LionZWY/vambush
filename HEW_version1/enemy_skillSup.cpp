//=============================================================================
//
// 特殊弾02処理 [enemySupSk.cpp]
// Author : 朱文渊
// プログラム作成日 : 2018/3/09
//=============================================================================
#include "enemy_skillSup.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "effect.h"
#include "player.h"
#include "field.h"
#include "checkhit.h"
#include "enemy.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexEnemySupSkill(LPDIRECT3DDEVICE9 pDevice);
void SetVertexEnemySupSkill(int nIdxSupSkill, D3DXVECTOR2 size);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureEnemySupSkill = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffEnemySupSkill	= NULL;		// 頂点バッファインターフェースへのポインタ

ENEMY_SUPSKILL			enemysupSkillWk[MAX_SUPSKILL];			// 弾ワーク
LPDIRECT3DTEXTURE9		TextureEnemyEnemySupSkill;
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEnemySupSkill(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY_SUPSKILL *enemysupSkill = enemysupSkillWk;

	// 頂点情報の作成
	MakeVertexEnemySupSkill(pDevice);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
								TEXTURE_SUPSKILL_ENEMY,				// ファイルの名前
								&g_pD3DTextureEnemySupSkill);	// 読み込むメモリー

													

	for(int i = 0; i < MAX_SUPSKILL; i++, enemysupSkill++)
	{
		enemysupSkill->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		enemysupSkill->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		enemysupSkill->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		enemysupSkill->move = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		enemysupSkill->size.x = SUPSKILL_SIZE_X;
		enemysupSkill->size.y = SUPSKILL_SIZE_Y;
		enemysupSkill->timer = 0;
		enemysupSkill->bUse = false;
		enemysupSkill->Track = true;
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemySupSkill(void)
{
	if(g_pD3DTextureEnemySupSkill != NULL)
	{// テクスチャの開放
		g_pD3DTextureEnemySupSkill->Release();
		g_pD3DTextureEnemySupSkill = NULL;
	}

	if(g_pD3DVtxBuffEnemySupSkill != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffEnemySupSkill->Release();
		g_pD3DVtxBuffEnemySupSkill = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemySupSkill(void)
{
	D3DXVECTOR3 rotCamera;
	ENEMY_SUPSKILL *enemysupSkill = enemysupSkillWk;
	PLAYER *player = GetPlayer();
	ENEMY *enemy = GetEnemy();


	// カメラの回転を取得
	rotCamera = GetRotCamera();

 for(int i = 0; i < MAX_SUPSKILL; i++, enemysupSkill++)
	{
		if(enemysupSkill->bUse)
		{

			if (enemysupSkill->Track)
			{

				enemysupSkill->rot.y = atan2(player->pos.x - enemysupSkill->pos.x, player->pos.z - enemysupSkill->pos.z);
				enemysupSkill->rot.y -= D3DX_PI;
				enemysupSkill->move.x = -sinf(enemysupSkill->rot.y)*4.0f;
				enemysupSkill->move.z = -cosf(enemysupSkill->rot.y)*4.0f;
				if (CheckHitBC(enemysupSkill->pos, player->pos, 2.0f, 30.0f))
				{
					enemysupSkill->Track = false;

				}
		
			}
			else if (enemysupSkill->Track == false)
			{
				enemysupSkill->move.x = -sinf(enemysupSkill->rot.y)*4.0f;
				enemysupSkill->move.z = -cosf(enemysupSkill->rot.y)*4.0f;
			}

			enemysupSkill->pos.x += enemysupSkill->move.x;
			enemysupSkill->pos.z += enemysupSkill->move.z;

			enemysupSkill->timer--;
			if(enemysupSkill->timer <= 0)
			{
				ReleaseShadow(enemysupSkill->nIdxShadow);
				enemysupSkill->bUse = false;
			}
			else
			{
				// 影の位置設定
				SetPositionShadow(enemysupSkill->nIdxShadow, D3DXVECTOR3(enemysupSkill->pos.x, 0.1f, enemysupSkill->pos.z));


				// エフェクトの設定
				SetEffect(enemysupSkill->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(0.65f, 0.05f, 0.85f, 0.50f), D3DXVECTOR2(15.0f, 15.0f), 10);
				SetEffect(enemysupSkill->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(0.05f, 0.85f, 0.65f, 0.30f), D3DXVECTOR2(8.0f, 8.0f), 10);
				SetEffect(enemysupSkill->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(0.05f, 0.45f, 0.45f, 0.20f), D3DXVECTOR2(4.0f, 4.0f), 10);


			}

			D3DXVECTOR2	size;
			size.x = 8.0f + (enemysupSkill->pos.y - 4.0f) * 0.05f;
			if(size.x < 8.0f)
			{
				size.x = 8.0f;
			}
			size.y = 8.0f + (enemysupSkill->pos.y - 4.0f) * 0.05f;
			if(size.y < 8.0f)
			{
				size.y = 8.0f;
			}

			SetVertexShadow(enemysupSkill->nIdxShadow, size);

			float colA = (200.0f - (enemysupSkill->pos.y - 4.0f)) / 400.0f;
			if(colA < 0.0f)
			{
				colA = 0.0f;
			}
			SetColorShadow(enemysupSkill->nIdxShadow, D3DXCOLOR(1.0f, 1.0f, 1.0f, colA));

			if (enemysupSkill->pos.x < (SUPSKILL_SIZE_X / 2) - FIELD_SCL_MAX_X)
			{
				DeleteEnemySupSkill(i);
			}
			if (enemysupSkill->pos.x > FIELD_SCL_MAX_X - (SUPSKILL_SIZE_X / 2))
			{
				DeleteEnemySupSkill(i);
			}
			if (enemysupSkill->pos.z > FIELD_SCL_MAX_Z)
			{
				DeleteEnemySupSkill(i);
			}
			if (enemysupSkill->pos.z < (SUPSKILL_SIZE_Y / 2) - FIELD_SCL_MAX_Z)
			{
				DeleteEnemySupSkill(i);
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemySupSkill(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView,mtxscl,mtxTranslate;
	ENEMY_SUPSKILL *enemysupSkill = enemysupSkillWk;

	// ライティングを無効に
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// αテストを有効に
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

 for(int i = 0; i < MAX_SUPSKILL; i++, enemysupSkill++)
	{
		if(enemysupSkill->bUse)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&enemysupSkill->world);

			// ビューマトリックスを取得
			mtxView = GetMtxView();

			enemysupSkill->world._11 = mtxView._11;
			enemysupSkill->world._12 = mtxView._21;
			enemysupSkill->world._13 = mtxView._31;
			enemysupSkill->world._21 = mtxView._12;
			enemysupSkill->world._22 = mtxView._22;
			enemysupSkill->world._23 = mtxView._32;
			enemysupSkill->world._31 = mtxView._13;
			enemysupSkill->world._32 = mtxView._23;
			enemysupSkill->world._33 = mtxView._33;

			// スケールを反映
			D3DXMatrixScaling(&mtxscl, enemysupSkill->scl.x, enemysupSkill->scl.y, enemysupSkill->scl.z);
			D3DXMatrixMultiply(&enemysupSkill->world, &enemysupSkill->world, &mtxscl);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, enemysupSkill->pos.x, enemysupSkill->pos.y, enemysupSkill->pos.z);
			D3DXMatrixMultiply(&enemysupSkill->world, &enemysupSkill->world, &mtxTranslate);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &enemysupSkill->world);

			// 頂点バッファをデバイスのデータストリームにバインド
			pDevice->SetStreamSource(0, g_pD3DVtxBuffEnemySupSkill, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pD3DTextureEnemySupSkill);

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
HRESULT MakeVertexEnemySupSkill(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
    if( FAILED( pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * MAX_SUPSKILL,	// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,							// 頂点バッファの使用法　
												FVF_VERTEX_3D,								// 使用する頂点フォーマット
												D3DPOOL_MANAGED,							// リソースのバッファを保持するメモリクラスを指定
												&g_pD3DVtxBuffEnemySupSkill,						// 頂点バッファインターフェースへのポインタ
												NULL)))										// NULLに設定
	{
        return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffEnemySupSkill->Lock(0, 0, (void**)&pVtx, 0);

		for(int i = 0; i < MAX_SUPSKILL; i++, pVtx += 4)
		{
			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(-SUPSKILL_SIZE_X / 2, -SUPSKILL_SIZE_Y / 2, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(SUPSKILL_SIZE_X / 2, -SUPSKILL_SIZE_Y / 2, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(-SUPSKILL_SIZE_X / 2, SUPSKILL_SIZE_Y / 2, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(SUPSKILL_SIZE_X / 2, SUPSKILL_SIZE_Y / 2, 0.0f);

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
		g_pD3DVtxBuffEnemySupSkill->Unlock();
	}

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexEnemySupSkill(int nIdxEnemySupSkill, D3DXVECTOR2 size)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffEnemySupSkill->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxEnemySupSkill * 4);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(-size.x / 2, -size.y / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-size.x / 2, size.y / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(size.x / 2, -size.y / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(size.x / 2, size.y / 2, 0.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffEnemySupSkill->Unlock();
	}
}

//=============================================================================
// 弾の設定
//=============================================================================
int SetEnemySupSkill(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 size, int timer)
{
	ENEMY_SUPSKILL *enemysupSkill = enemysupSkillWk;

	int nIdxEnemySupSkill = -1;

	enemysupSkill = GetEnemySupSkill(0);
 for(int i = 0; i < MAX_SUPSKILL; i++, enemysupSkill++)
	{
		if(!enemysupSkill->bUse)
		{

			enemysupSkill->pos = pos;
			enemysupSkill->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			enemysupSkill->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			enemysupSkill->move = move;
			enemysupSkill->size.x = size.x;
			enemysupSkill->size.y = size.y;
			enemysupSkill->timer = timer;
			enemysupSkill->bUse = true;
			enemysupSkill->Track = true;

			// 影の設定
			enemysupSkill->nIdxShadow = CreateShadow(pos, D3DXVECTOR2(8.0f, 8.0f));		// 影の設定

			// 頂点座標の設定
			SetVertexEnemySupSkill(i, size);

			nIdxEnemySupSkill = i;

			break;
		}
	}

	return nIdxEnemySupSkill;
}

//=============================================================================
// 弾の削除
//=============================================================================
void DeleteEnemySupSkill(int nIdxEnemySupSkill)
{
	if(nIdxEnemySupSkill >= 0 && nIdxEnemySupSkill < MAX_SUPSKILL)
	{
		ReleaseShadow(enemysupSkillWk[nIdxEnemySupSkill].nIdxShadow);
		enemysupSkillWk[nIdxEnemySupSkill].bUse = false;
	}
}

ENEMY_SUPSKILL *GetEnemySupSkill(int no)
{
	return(&enemysupSkillWk[no]);
}


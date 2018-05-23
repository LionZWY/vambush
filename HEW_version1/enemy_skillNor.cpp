//=============================================================================
//
// 特殊弾03処理 [enemyNorSk.cpp]
// Author : 朱文渊
// プログラム作成日 : 2018/3/09
//=============================================================================
#include "enemy_skillNor.h"
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
HRESULT MakeVertexEnemyNorSkill(LPDIRECT3DDEVICE9 pDevice);
void SetVertexEnemyNorSkill(int nIdxNorSkill, D3DXVECTOR2 size);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureEnemyNorSkill1 = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffEnemyNorSkill	= NULL;		// 頂点バッファインターフェースへのポインタ

ENEMY_NORSKILL			enemynorSkillWk[MAX_NORSKILL];			// 弾ワーク
int						enemynorSkillType;						// 弾のタイプ
LPDIRECT3DTEXTURE9		TextureEnemyEnemyNorSkill;				// テクスチャへのポインタ
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEnemyNorSkill(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY_NORSKILL *enemynorSkill = enemynorSkillWk;

	// 頂点情報の作成
	MakeVertexEnemyNorSkill(pDevice);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
								TEXTURE_NORSKILL_ENEMY,				// ファイルの名前
								&g_pD3DTextureEnemyNorSkill1);	// 読み込むメモリー

													

	for(int i = 0; i < MAX_NORSKILL; i++, enemynorSkill++)
	{
		enemynorSkill->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		enemynorSkill->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		enemynorSkill->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		enemynorSkill->move = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		enemynorSkill->size.x = NORSKILL_SIZE_X;
		enemynorSkill->size.y = NORSKILL_SIZE_Y;
		enemynorSkill->timer = 0;
		enemynorSkill->cnt=3;
		enemynorSkill->bUse = false;
		enemynorSkill->Track = true;
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemyNorSkill(void)
{
	if(g_pD3DTextureEnemyNorSkill1 != NULL)
	{// テクスチャの開放
		g_pD3DTextureEnemyNorSkill1->Release();
		g_pD3DTextureEnemyNorSkill1 = NULL;
	}

	if(g_pD3DVtxBuffEnemyNorSkill != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffEnemyNorSkill->Release();
		g_pD3DVtxBuffEnemyNorSkill = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemyNorSkill(void)
{
	D3DXVECTOR3 rotCamera;
	ENEMY_NORSKILL *enemynorSkill = enemynorSkillWk;
	PLAYER *player = GetPlayer();
	ENEMY *enemy = GetEnemy();


	// カメラの回転を取得
	rotCamera = GetRotCamera();

 for(int i = 0; i < MAX_NORSKILL; i++, enemynorSkill++)
	{
		if(enemynorSkill->bUse)
		{

			if (enemynorSkill->Track)
			{

				enemynorSkill->rot.y = atan2(player->pos.x - enemynorSkill->pos.x, player->pos.z - enemynorSkill->pos.z);
				enemynorSkill->rot.y -= D3DX_PI;
				enemynorSkill->move.x = -sinf(enemynorSkill->rot.y)*3.0f;
				enemynorSkill->move.z = -cosf(enemynorSkill->rot.y)*3.0f;
				if (CheckHitBC(enemynorSkill->pos, player->pos, 2.0f, 20.0f))
				{
					enemynorSkill->Track = false;

				}
		
			}
			else if (enemynorSkill->Track == false)
			{
				enemynorSkill->move.x = -sinf(enemynorSkill->rot.y)*3.0f;
				enemynorSkill->move.z = -cosf(enemynorSkill->rot.y)*3.0f;
			}

			enemynorSkill->pos.x += enemynorSkill->move.x;
			enemynorSkill->pos.z += enemynorSkill->move.z;

			enemynorSkill->timer--;
			if(enemynorSkill->timer <= 0)
			{
				ReleaseShadow(enemynorSkill->nIdxShadow);
				enemynorSkill->bUse = false;
			}
			else
			{
				// 影の位置設定
				SetPositionShadow(enemynorSkill->nIdxShadow, D3DXVECTOR3(enemynorSkill->pos.x, 0.1f, enemynorSkill->pos.z));


				// エフェクトの設定
				SetEffect(enemynorSkill->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(0.65f, 0.05f, 0.85f, 0.50f), D3DXVECTOR2(8.0f, 8.0f), 10);
				SetEffect(enemynorSkill->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(0.05f, 0.85f, 0.65f, 0.30f), D3DXVECTOR2(6.0f, 6.0f), 10);
				SetEffect(enemynorSkill->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(0.05f, 0.45f, 0.45f, 0.20f), D3DXVECTOR2(3.0f, 3.0f), 10);


			}

			D3DXVECTOR2	size;
			size.x = 8.0f + (enemynorSkill->pos.y - 4.0f) * 0.05f;
			if(size.x < 8.0f)
			{
				size.x = 8.0f;
			}
			size.y = 8.0f + (enemynorSkill->pos.y - 4.0f) * 0.05f;
			if(size.y < 8.0f)
			{
				size.y = 8.0f;
			}

			SetVertexShadow(enemynorSkill->nIdxShadow, size);

			float colA = (200.0f - (enemynorSkill->pos.y - 4.0f)) / 400.0f;
			if(colA < 0.0f)
			{
				colA = 0.0f;
			}
			SetColorShadow(enemynorSkill->nIdxShadow, D3DXCOLOR(1.0f, 1.0f, 1.0f, colA));

			if (enemynorSkill->pos.x < (NORSKILL_SIZE_X / 2) - FIELD_SCL_MAX_X)
			{
				DeleteEnemyNorSkill(i);
			}
			if (enemynorSkill->pos.x > FIELD_SCL_MAX_X - (NORSKILL_SIZE_X / 2))
			{
				DeleteEnemyNorSkill(i);
			}
			if (enemynorSkill->pos.z > FIELD_SCL_MAX_Z)
			{
				DeleteEnemyNorSkill(i);
			}
			if (enemynorSkill->pos.z < (NORSKILL_SIZE_Y / 2) - FIELD_SCL_MAX_Z)
			{
				DeleteEnemyNorSkill(i);
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemyNorSkill(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView,mtxscl,mtxTranslate;
	ENEMY_NORSKILL *enemynorSkill = enemynorSkillWk;

	// ライティングを無効に
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// αテストを有効に
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

 for(int i = 0; i < MAX_NORSKILL; i++, enemynorSkill++)
	{
		if(enemynorSkill->bUse)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&enemynorSkill->world);

			// ビューマトリックスを取得
			mtxView = GetMtxView();

			enemynorSkill->world._11 = mtxView._11;
			enemynorSkill->world._12 = mtxView._21;
			enemynorSkill->world._13 = mtxView._31;
			enemynorSkill->world._21 = mtxView._12;
			enemynorSkill->world._22 = mtxView._22;
			enemynorSkill->world._23 = mtxView._32;
			enemynorSkill->world._31 = mtxView._13;
			enemynorSkill->world._32 = mtxView._23;
			enemynorSkill->world._33 = mtxView._33;

			// スケールを反映
			D3DXMatrixScaling(&mtxscl, enemynorSkill->scl.x, enemynorSkill->scl.y, enemynorSkill->scl.z);
			D3DXMatrixMultiply(&enemynorSkill->world, &enemynorSkill->world, &mtxscl);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, enemynorSkill->pos.x, enemynorSkill->pos.y, enemynorSkill->pos.z);
			D3DXMatrixMultiply(&enemynorSkill->world, &enemynorSkill->world, &mtxTranslate);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &enemynorSkill->world);

			// 頂点バッファをデバイスのデータストリームにバインド
			pDevice->SetStreamSource(0, g_pD3DVtxBuffEnemyNorSkill, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, TextureEnemyEnemyNorSkill);

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
HRESULT MakeVertexEnemyNorSkill(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
    if( FAILED( pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * MAX_NORSKILL,	// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,							// 頂点バッファの使用法　
												FVF_VERTEX_3D,								// 使用する頂点フォーマット
												D3DPOOL_MANAGED,							// リソースのバッファを保持するメモリクラスを指定
												&g_pD3DVtxBuffEnemyNorSkill,						// 頂点バッファインターフェースへのポインタ
												NULL)))										// NULLに設定
	{
        return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffEnemyNorSkill->Lock(0, 0, (void**)&pVtx, 0);

		for(int i = 0; i < MAX_NORSKILL; i++, pVtx += 4)
		{
			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(-NORSKILL_SIZE_X / 2, -NORSKILL_SIZE_Y / 2, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(NORSKILL_SIZE_X / 2, -NORSKILL_SIZE_Y / 2, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(-NORSKILL_SIZE_X / 2, NORSKILL_SIZE_Y / 2, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(NORSKILL_SIZE_X / 2, NORSKILL_SIZE_Y / 2, 0.0f);

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
		g_pD3DVtxBuffEnemyNorSkill->Unlock();
	}

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexEnemyNorSkill(int nIdxEnemyNorSkill, D3DXVECTOR2 size)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffEnemyNorSkill->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxEnemyNorSkill * 4);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(-size.x / 2, -size.y / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-size.x / 2, size.y / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(size.x / 2, -size.y / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(size.x / 2, size.y / 2, 0.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffEnemyNorSkill->Unlock();
	}
}

//=============================================================================
// 弾の設定
//=============================================================================
int SetEnemyNorSkill(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 size, int timer,int type)
{
	ENEMY_NORSKILL *enemynorSkill = enemynorSkillWk;
	enemynorSkillType = type;

	switch (type)
	{
	case EB_TYPE_NORMAL:
		TextureEnemyEnemyNorSkill = g_pD3DTextureEnemyNorSkill1;
		break;
	}

	int nIdxEnemyNorSkill = -1;

	enemynorSkill = GetEnemyNorSkill(0);
 for(int i = 0; i < MAX_NORSKILL; i++, enemynorSkill++)
	{
		if(!enemynorSkill->bUse)
		{

			enemynorSkill->pos = pos;
			enemynorSkill->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			enemynorSkill->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			enemynorSkill->move = move;
			enemynorSkill->size.x = size.x;
			enemynorSkill->size.y = size.y;
			enemynorSkill->timer = timer;
			enemynorSkill->cnt--;
			enemynorSkill->bUse = true;
			enemynorSkill->Track = true;

			// 影の設定
			enemynorSkill->nIdxShadow = CreateShadow(pos, D3DXVECTOR2(8.0f, 8.0f));		// 影の設定

			// 頂点座標の設定
			SetVertexEnemyNorSkill(i, size);

			nIdxEnemyNorSkill = i;

			break;
		}
	}

	return nIdxEnemyNorSkill;
}

//=============================================================================
// 弾の削除
//=============================================================================
void DeleteEnemyNorSkill(int nIdxEnemyNorSkill)
{
	if(nIdxEnemyNorSkill >= 0 && nIdxEnemyNorSkill < MAX_NORSKILL)
	{
		ReleaseShadow(enemynorSkillWk[nIdxEnemyNorSkill].nIdxShadow);
		enemynorSkillWk[nIdxEnemyNorSkill].bUse = false;
	}
}

int GetEnemyNorSkillType(void)
{
	return enemynorSkillType;
}

ENEMY_NORSKILL *GetEnemyNorSkill(int no)
{
	return(&enemynorSkillWk[no]);
}


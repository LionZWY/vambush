//=============================================================================
//
// 特殊弾01処理 [enemyskillDef.cpp]
// Author : 朱文渊
// プログラム作成日 : 2018/3/09
//=============================================================================
#include "enemy_skillDef.h"
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
HRESULT MakeVertexEnemySkillDef(LPDIRECT3DDEVICE9 pDevice);
void SetVertexEnemySkillDef(int nIdxSkillDef, D3DXVECTOR2 size);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureEnemySkillDef = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffEnemySkillDef	= NULL;		// 頂点バッファインターフェースへのポインタ

ENEMY_SKILLDEF					enemyskillDefWk[MAX_SKILLDEF];			// 弾ワーク
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEnemySkillDef(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY_SKILLDEF *enemyskillDef = enemyskillDefWk;

	// 頂点情報の作成
	MakeVertexEnemySkillDef(pDevice);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
								TEXTURE_SKILLDEF_ENEMY,				// ファイルの名前
								&g_pD3DTextureEnemySkillDef);	// 読み込むメモリー

													

	for(int i = 0; i < MAX_SKILLDEF; i++, enemyskillDef++)
	{
		enemyskillDef->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		enemyskillDef->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		enemyskillDef->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		enemyskillDef->move = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		enemyskillDef->size.x = SKILLDEF_SIZE_X;
		enemyskillDef->size.y = SKILLDEF_SIZE_Y;
		enemyskillDef->timer = 0;
		enemyskillDef->cnt = 3;
		enemyskillDef->bUse = false;
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemySkillDef(void)
{
	if(g_pD3DTextureEnemySkillDef != NULL)
	{// テクスチャの開放
		g_pD3DTextureEnemySkillDef->Release();
		g_pD3DTextureEnemySkillDef = NULL;
	}

	if(g_pD3DVtxBuffEnemySkillDef != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffEnemySkillDef->Release();
		g_pD3DVtxBuffEnemySkillDef = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemySkillDef(void)
{
	D3DXVECTOR3 rotCamera;
	ENEMY_SKILLDEF *enemyskillDef = enemyskillDefWk;


	// カメラの回転を取得
	rotCamera = GetRotCamera();

 for(int i = 0; i < MAX_SKILLDEF; i++, enemyskillDef++)
	{
		if(enemyskillDef->bUse)
		{
			enemyskillDef->pos.x += enemyskillDef->move.x;
			enemyskillDef->pos.z += enemyskillDef->move.z;

			enemyskillDef->timer--;
			if(enemyskillDef->timer <= 0)
			{
				ReleaseShadow(enemyskillDef->nIdxShadow);
				enemyskillDef->bUse = false;
			}
			else
			{
				// 影の位置設定
				SetPositionShadow(enemyskillDef->nIdxShadow, D3DXVECTOR3(enemyskillDef->pos.x, 0.1f, enemyskillDef->pos.z));


				// エフェクトの設定
				SetEffect(enemyskillDef->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(0.65f, 0.05f, 0.85f, 0.50f), D3DXVECTOR2(35.0f, 35.0f), 10);
				SetEffect(enemyskillDef->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(0.05f, 0.85f, 0.65f, 0.30f), D3DXVECTOR2(20.0f, 20.0f), 10);
				SetEffect(enemyskillDef->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(0.05f, 0.45f, 0.45f, 0.20f), D3DXVECTOR2(6.0f, 6.0f), 10);


			}

			//弾のサイズの更新
			D3DXVECTOR2	size;
			size.x = 8.0f + (enemyskillDef->pos.y - 4.0f) * 0.05f;
			if(size.x < 8.0f)
			{
				size.x = 8.0f;
			}
			size.y = 8.0f + (enemyskillDef->pos.y - 4.0f) * 0.05f;
			if(size.y < 8.0f)
			{
				size.y = 8.0f;
			}

			SetVertexShadow(enemyskillDef->nIdxShadow, size);

			float colA = (200.0f - (enemyskillDef->pos.y - 4.0f)) / 400.0f;
			if(colA < 0.0f)
			{
				colA = 0.0f;
			}
			SetColorShadow(enemyskillDef->nIdxShadow, D3DXCOLOR(1.0f, 1.0f, 1.0f, colA));


			//範囲外に出たら消去
			if (enemyskillDef->pos.x < (SKILLDEF_SIZE_X / 2) - FIELD_SCL_MAX_X)
			{
				DeleteEnemySkillDef(i);
			}
			if (enemyskillDef->pos.x > FIELD_SCL_MAX_X - (SKILLDEF_SIZE_X / 2))
			{
				DeleteEnemySkillDef(i);
			}
			if (enemyskillDef->pos.z > FIELD_SCL_MAX_Z)
			{
				DeleteEnemySkillDef(i);
			}
			if (enemyskillDef->pos.z < (SKILLDEF_SIZE_Y / 2) - FIELD_SCL_MAX_Z)
			{
				DeleteEnemySkillDef(i);
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemySkillDef(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView,mtxscl,mtxTranslate;
	ENEMY_SKILLDEF *enemyskillDef = enemyskillDefWk;

	// ライティングを無効に
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// αテストを有効に
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

 for(int i = 0; i < MAX_SKILLDEF; i++, enemyskillDef++)
	{
		if(enemyskillDef->bUse)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&enemyskillDef->world);

			// ビューマトリックスを取得
			mtxView = GetMtxView();

			enemyskillDef->world._11 = mtxView._11;
			enemyskillDef->world._12 = mtxView._21;
			enemyskillDef->world._13 = mtxView._31;
			enemyskillDef->world._21 = mtxView._12;
			enemyskillDef->world._22 = mtxView._22;
			enemyskillDef->world._23 = mtxView._32;
			enemyskillDef->world._31 = mtxView._13;
			enemyskillDef->world._32 = mtxView._23;
			enemyskillDef->world._33 = mtxView._33;

			// スケールを反映
			D3DXMatrixScaling(&mtxscl, enemyskillDef->scl.x, enemyskillDef->scl.y, enemyskillDef->scl.z);
			D3DXMatrixMultiply(&enemyskillDef->world, &enemyskillDef->world, &mtxscl);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, enemyskillDef->pos.x, enemyskillDef->pos.y, enemyskillDef->pos.z);
			D3DXMatrixMultiply(&enemyskillDef->world, &enemyskillDef->world, &mtxTranslate);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &enemyskillDef->world);

			// 頂点バッファをデバイスのデータストリームにバインド
			pDevice->SetStreamSource(0, g_pD3DVtxBuffEnemySkillDef, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pD3DTextureEnemySkillDef);

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
HRESULT MakeVertexEnemySkillDef(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
    if( FAILED( pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * MAX_SKILLDEF,	// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,							// 頂点バッファの使用法　
												FVF_VERTEX_3D,								// 使用する頂点フォーマット
												D3DPOOL_MANAGED,							// リソースのバッファを保持するメモリクラスを指定
												&g_pD3DVtxBuffEnemySkillDef,						// 頂点バッファインターフェースへのポインタ
												NULL)))										// NULLに設定
	{
        return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffEnemySkillDef->Lock(0, 0, (void**)&pVtx, 0);

		for(int i = 0; i < MAX_SKILLDEF; i++, pVtx += 4)
		{
			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(-SKILLDEF_SIZE_X / 2, -SKILLDEF_SIZE_Y / 2, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(SKILLDEF_SIZE_X / 2, -SKILLDEF_SIZE_Y / 2, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(-SKILLDEF_SIZE_X / 2, SKILLDEF_SIZE_Y / 2, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(SKILLDEF_SIZE_X / 2, SKILLDEF_SIZE_Y / 2, 0.0f);

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
		g_pD3DVtxBuffEnemySkillDef->Unlock();
	}

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexEnemySkillDef(int nIdxEnemySkillDef, D3DXVECTOR2 size)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffEnemySkillDef->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxEnemySkillDef * 4);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(-size.x / 2, -size.y / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-size.x / 2, size.y / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(size.x / 2, -size.y / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(size.x / 2, size.y / 2, 0.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffEnemySkillDef->Unlock();
	}
}

//=============================================================================
// 弾の設定
//=============================================================================
int SetEnemySkillDef(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 size, int timer)
{
	ENEMY_SKILLDEF *enemyskillDef = enemyskillDefWk;

	int nIdxEnemySkillDef = -1;

	enemyskillDef = GetEnemySkillDef(0);
 for(int i = 0; i < MAX_SKILLDEF; i++, enemyskillDef++)
	{
		if(!enemyskillDef->bUse)
		{

			enemyskillDef->pos = pos;
			enemyskillDef->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			enemyskillDef->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			enemyskillDef->move = move;
			enemyskillDef->size.x = size.x;
			enemyskillDef->size.y = size.y;
			enemyskillDef->timer = timer;
			enemyskillDef->cnt --;
			enemyskillDef->bUse = true;

			// 影の設定
			enemyskillDef->nIdxShadow = CreateShadow(pos, D3DXVECTOR2(8.0f, 8.0f));		// 影の設定

			// 頂点座標の設定
			SetVertexEnemySkillDef(i, size);

			nIdxEnemySkillDef = i;

			break;
		}
	}

	return nIdxEnemySkillDef;
}

//=============================================================================
// 弾の削除
//=============================================================================
void DeleteEnemySkillDef(int nIdxEnemySkillDef)
{
	if(nIdxEnemySkillDef >= 0 && nIdxEnemySkillDef < MAX_SKILLDEF)
	{
		ReleaseShadow(enemyskillDefWk[nIdxEnemySkillDef].nIdxShadow);
		enemyskillDefWk[nIdxEnemySkillDef].bUse = false;
	}
}

//=============================================================================
// 弾の取得
//=============================================================================
ENEMY_SKILLDEF *GetEnemySkillDef(int no)
{
	return(&enemyskillDefWk[no]);
}
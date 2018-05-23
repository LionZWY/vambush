//=============================================================================
//
// 弾処理 [playerNorSk.cpp]
// Author : 朱文渊
// プログラム作成日 : 2018/3/09
//=============================================================================
#include "player_skillNor.h"
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
HRESULT MakeVertexPlayerNorSkill(LPDIRECT3DDEVICE9 pDevice);
void SetVertexPlayerNorSkill(int nIdxNorSkill, D3DXVECTOR2 size);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTexturePlayerNorSkill1 = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffPlayerNorSkill	= NULL;		// 頂点バッファインターフェースへのポインタ

PLAYER_NORSKILL					playernorSkillWk[MAX_NORSKILL];			// 弾ワーク
int						playernorSkillType;
LPDIRECT3DTEXTURE9		TexturePlayerPlayerNorSkill;
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayerNorSkill(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER_NORSKILL *playernorSkill = playernorSkillWk;

	// 頂点情報の作成
	MakeVertexPlayerNorSkill(pDevice);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
								TEXTURE_NORSKILL_PLAYER,				// ファイルの名前
								&g_pD3DTexturePlayerNorSkill1);	// 読み込むメモリー

													

	for(int i = 0; i < MAX_NORSKILL; i++, playernorSkill++)
	{
		playernorSkill->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		playernorSkill->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		playernorSkill->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		playernorSkill->move = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		playernorSkill->size.x = NORSKILL_SIZE_X;
		playernorSkill->size.y = NORSKILL_SIZE_Y;
		playernorSkill->timer = 0;
		playernorSkill->cnt = 3;
		playernorSkill->bUse = false;
		playernorSkill->Track = true;
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayerNorSkill(void)
{
	if(g_pD3DTexturePlayerNorSkill1 != NULL)
	{// テクスチャの開放
		g_pD3DTexturePlayerNorSkill1->Release();
		g_pD3DTexturePlayerNorSkill1 = NULL;
	}

	if(g_pD3DVtxBuffPlayerNorSkill != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffPlayerNorSkill->Release();
		g_pD3DVtxBuffPlayerNorSkill = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayerNorSkill(void)
{
	D3DXVECTOR3 rotCamera;
	PLAYER_NORSKILL *playernorSkill = playernorSkillWk;
	PLAYER *player = GetPlayer();
	ENEMY *enemy = GetEnemy();


	// カメラの回転を取得
	rotCamera = GetRotCamera();

 for(int i = 0; i < MAX_NORSKILL; i++, playernorSkill++)
	{
		if(playernorSkill->bUse)
		{

			if (playernorSkill->Track)
			{

				playernorSkill->rot.y = atan2(enemy->pos.x - playernorSkill->pos.x, enemy->pos.z - playernorSkill->pos.z);
				playernorSkill->rot.y -= D3DX_PI;
				playernorSkill->move.x = -sinf(playernorSkill->rot.y)*3.0f;
				playernorSkill->move.z = -cosf(playernorSkill->rot.y)*3.0f;
				if (CheckHitBC(playernorSkill->pos, enemy->pos, 2.0f, 20.0f))
				{
					playernorSkill->Track = false;

				}
		
			}
			else if (playernorSkill->Track == false)
			{
				playernorSkill->move.x = -sinf(playernorSkill->rot.y)*3.0f;
				playernorSkill->move.z = -cosf(playernorSkill->rot.y)*3.0f;
			}

			playernorSkill->pos.x += playernorSkill->move.x;
			playernorSkill->pos.z += playernorSkill->move.z;

			playernorSkill->timer--;
			if(playernorSkill->timer <= 0)
			{
				ReleaseShadow(playernorSkill->nIdxShadow);
				playernorSkill->bUse = false;
			}
			else
			{
				// 影の位置設定
				SetPositionShadow(playernorSkill->nIdxShadow, D3DXVECTOR3(playernorSkill->pos.x, 0.1f, playernorSkill->pos.z));


				// エフェクトの設定
				SetEffect(playernorSkill->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(0.85f, 0.05f, 0.15f, 0.50f), D3DXVECTOR2(8.0f, 8.0f), 10);
				SetEffect(playernorSkill->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(0.65f, 0.10f, 0.10f, 0.30f), D3DXVECTOR2(6.0f, 6.0f), 10);
				SetEffect(playernorSkill->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(0.45f, 0.15f, 0.05f, 0.20f), D3DXVECTOR2(3.0f, 3.0f), 10);


			}

			D3DXVECTOR2	size;
			size.x = 8.0f + (playernorSkill->pos.y - 4.0f) * 0.05f;
			if(size.x < 8.0f)
			{
				size.x = 8.0f;
			}
			size.y = 8.0f + (playernorSkill->pos.y - 4.0f) * 0.05f;
			if(size.y < 8.0f)
			{
				size.y = 8.0f;
			}

			SetVertexShadow(playernorSkill->nIdxShadow, size);

			float colA = (200.0f - (playernorSkill->pos.y - 4.0f)) / 400.0f;
			if(colA < 0.0f)
			{
				colA = 0.0f;
			}
			SetColorShadow(playernorSkill->nIdxShadow, D3DXCOLOR(1.0f, 1.0f, 1.0f, colA));

			if (playernorSkill->pos.x < (NORSKILL_SIZE_X / 2) - FIELD_SCL_MAX_X)
			{
				DeletePlayerNorSkill(i);
			}
			if (playernorSkill->pos.x > FIELD_SCL_MAX_X - (NORSKILL_SIZE_X / 2))
			{
				DeletePlayerNorSkill(i);
			}
			if (playernorSkill->pos.z > FIELD_SCL_MAX_Z)
			{
				DeletePlayerNorSkill(i);
			}
			if (playernorSkill->pos.z < (NORSKILL_SIZE_Y / 2) - FIELD_SCL_MAX_Z)
			{
				DeletePlayerNorSkill(i);
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayerNorSkill(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView,mtxscl,mtxTranslate;
	PLAYER_NORSKILL *playernorSkill = playernorSkillWk;

	// ライティングを無効に
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// αテストを有効に
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

 for(int i = 0; i < MAX_NORSKILL; i++, playernorSkill++)
	{
		if(playernorSkill->bUse)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&playernorSkill->world);

			// ビューマトリックスを取得
			mtxView = GetMtxView();

			playernorSkill->world._11 = mtxView._11;
			playernorSkill->world._12 = mtxView._21;
			playernorSkill->world._13 = mtxView._31;
			playernorSkill->world._21 = mtxView._12;
			playernorSkill->world._22 = mtxView._22;
			playernorSkill->world._23 = mtxView._32;
			playernorSkill->world._31 = mtxView._13;
			playernorSkill->world._32 = mtxView._23;
			playernorSkill->world._33 = mtxView._33;

			// スケールを反映
			D3DXMatrixScaling(&mtxscl, playernorSkill->scl.x, playernorSkill->scl.y, playernorSkill->scl.z);
			D3DXMatrixMultiply(&playernorSkill->world, &playernorSkill->world, &mtxscl);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, playernorSkill->pos.x, playernorSkill->pos.y, playernorSkill->pos.z);
			D3DXMatrixMultiply(&playernorSkill->world, &playernorSkill->world, &mtxTranslate);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &playernorSkill->world);

			// 頂点バッファをデバイスのデータストリームにバインド
			pDevice->SetStreamSource(0, g_pD3DVtxBuffPlayerNorSkill, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, TexturePlayerPlayerNorSkill);

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
HRESULT MakeVertexPlayerNorSkill(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
    if( FAILED( pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * MAX_NORSKILL,	// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,							// 頂点バッファの使用法　
												FVF_VERTEX_3D,								// 使用する頂点フォーマット
												D3DPOOL_MANAGED,							// リソースのバッファを保持するメモリクラスを指定
												&g_pD3DVtxBuffPlayerNorSkill,						// 頂点バッファインターフェースへのポインタ
												NULL)))										// NULLに設定
	{
        return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffPlayerNorSkill->Lock(0, 0, (void**)&pVtx, 0);

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
		g_pD3DVtxBuffPlayerNorSkill->Unlock();
	}

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexPlayerNorSkill(int nIdxPlayerNorSkill, D3DXVECTOR2 size)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffPlayerNorSkill->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxPlayerNorSkill * 4);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(-size.x / 2, -size.y / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-size.x / 2, size.y / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(size.x / 2, -size.y / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(size.x / 2, size.y / 2, 0.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffPlayerNorSkill->Unlock();
	}
}

//=============================================================================
// 弾の設定
//=============================================================================
int SetPlayerNorSkill(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 size, int timer,int type)
{
	PLAYER_NORSKILL *playernorSkill = playernorSkillWk;
	playernorSkillType = type;

	switch (type)
	{
	case PB_TYPE_NORMAL:
		TexturePlayerPlayerNorSkill = g_pD3DTexturePlayerNorSkill1;
		break;
	}

	int nIdxPlayerNorSkill = -1;

	playernorSkill = GetPlayerNorSkill(0);
 for(int i = 0; i < MAX_NORSKILL; i++, playernorSkill++)
	{
		if(!playernorSkill->bUse)
		{

			playernorSkill->pos = pos;
			playernorSkill->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			playernorSkill->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			playernorSkill->move = move;
			playernorSkill->size.x = size.x;
			playernorSkill->size.y = size.y;
			playernorSkill->timer = timer;
			playernorSkill->cnt --;
			playernorSkill->bUse = true;
			playernorSkill->Track = true;

			// 影の設定
			playernorSkill->nIdxShadow = CreateShadow(pos, D3DXVECTOR2(8.0f, 8.0f));		// 影の設定

			// 頂点座標の設定
			SetVertexPlayerNorSkill(i, size);

			nIdxPlayerNorSkill = i;

			break;
		}
	}

	return nIdxPlayerNorSkill;
}

//=============================================================================
// 弾の削除
//=============================================================================
void DeletePlayerNorSkill(int nIdxPlayerNorSkill)
{
	if(nIdxPlayerNorSkill >= 0 && nIdxPlayerNorSkill < MAX_NORSKILL)
	{
		ReleaseShadow(playernorSkillWk[nIdxPlayerNorSkill].nIdxShadow);
		playernorSkillWk[nIdxPlayerNorSkill].bUse = false;
	}
}

int GetPlayerNorSkillType(void)
{
	return playernorSkillType;
}

PLAYER_NORSKILL *GetPlayerNorSkill(int no)
{
	return(&playernorSkillWk[no]);
}


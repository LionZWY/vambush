//=============================================================================
//
// 弾処理 [playerSupSk.cpp]
// Author : 朱文渊
// プログラム作成日 : 2018/3/09
//=============================================================================
#include "player_skillSup.h"
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
HRESULT MakeVertexPlayerSupSkill(LPDIRECT3DDEVICE9 pDevice);
void SetVertexPlayerSupSkill(int nIdxSupSkill, D3DXVECTOR2 size);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTexturePlayerSupSkill = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffPlayerSupSkill	= NULL;		// 頂点バッファインターフェースへのポインタ

PLAYER_SUPSKILL			playersupSkillWk[MAX_SUPSKILL];			// 弾ワーク
LPDIRECT3DTEXTURE9		TexturePlayerPlayerSupSkill;
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayerSupSkill(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER_SUPSKILL *playersupSkill = playersupSkillWk;

	// 頂点情報の作成
	MakeVertexPlayerSupSkill(pDevice);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
								TEXTURE_SUPSKILL_PLAYER,				// ファイルの名前
								&g_pD3DTexturePlayerSupSkill);	// 読み込むメモリー

													

	for(int i = 0; i < MAX_SUPSKILL; i++, playersupSkill++)
	{
		playersupSkill->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		playersupSkill->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		playersupSkill->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		playersupSkill->move = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		playersupSkill->size.x = SUPSKILL_SIZE_X;
		playersupSkill->size.y = SUPSKILL_SIZE_Y;
		playersupSkill->timer = 0;
		playersupSkill->bUse = false;
		playersupSkill->Track = true;
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayerSupSkill(void)
{
	if(g_pD3DTexturePlayerSupSkill != NULL)
	{// テクスチャの開放
		g_pD3DTexturePlayerSupSkill->Release();
		g_pD3DTexturePlayerSupSkill = NULL;
	}

	if(g_pD3DVtxBuffPlayerSupSkill != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffPlayerSupSkill->Release();
		g_pD3DVtxBuffPlayerSupSkill = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayerSupSkill(void)
{
	D3DXVECTOR3 rotCamera;
	PLAYER_SUPSKILL *playersupSkill = playersupSkillWk;
	PLAYER *player = GetPlayer();
	ENEMY *enemy = GetEnemy();


	// カメラの回転を取得
	rotCamera = GetRotCamera();

 for(int i = 0; i < MAX_SUPSKILL; i++, playersupSkill++)
	{
		if(playersupSkill->bUse)
		{

			if (playersupSkill->Track)
			{

				playersupSkill->rot.y = atan2(enemy->pos.x - playersupSkill->pos.x, enemy->pos.z - playersupSkill->pos.z);
				playersupSkill->rot.y -= D3DX_PI;
				playersupSkill->move.x = -sinf(playersupSkill->rot.y)*4.0f;
				playersupSkill->move.z = -cosf(playersupSkill->rot.y)*4.0f;
				if (CheckHitBC(playersupSkill->pos, enemy->pos, 2.0f, 30.0f))
				{
					playersupSkill->Track = false;

				}
		
			}
			else if (playersupSkill->Track == false)
			{
				playersupSkill->move.x = -sinf(playersupSkill->rot.y)*4.0f;
				playersupSkill->move.z = -cosf(playersupSkill->rot.y)*4.0f;
			}

			playersupSkill->pos.x += playersupSkill->move.x;
			playersupSkill->pos.z += playersupSkill->move.z;

			playersupSkill->timer--;
			if(playersupSkill->timer <= 0)
			{
				ReleaseShadow(playersupSkill->nIdxShadow);
				playersupSkill->bUse = false;
			}
			else
			{
				// 影の位置設定
				SetPositionShadow(playersupSkill->nIdxShadow, D3DXVECTOR3(playersupSkill->pos.x, 0.1f, playersupSkill->pos.z));


				// エフェクトの設定
				SetEffect(playersupSkill->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(0.85f, 0.05f, 0.15f, 0.50f), D3DXVECTOR2(15.0f, 15.0f), 10);
				SetEffect(playersupSkill->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(0.65f, 0.10f, 0.10f, 0.30f), D3DXVECTOR2(8.0f, 8.0f), 10);
				SetEffect(playersupSkill->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(0.45f, 0.15f, 0.05f, 0.20f), D3DXVECTOR2(4.0f, 4.0f), 10);

			}

			D3DXVECTOR2	size;
			size.x = 8.0f + (playersupSkill->pos.y - 4.0f) * 0.05f;
			if(size.x < 8.0f)
			{
				size.x = 8.0f;
			}
			size.y = 8.0f + (playersupSkill->pos.y - 4.0f) * 0.05f;
			if(size.y < 8.0f)
			{
				size.y = 8.0f;
			}

			SetVertexShadow(playersupSkill->nIdxShadow, size);

			float colA = (200.0f - (playersupSkill->pos.y - 4.0f)) / 400.0f;
			if(colA < 0.0f)
			{
				colA = 0.0f;
			}
			SetColorShadow(playersupSkill->nIdxShadow, D3DXCOLOR(1.0f, 1.0f, 1.0f, colA));

			if (playersupSkill->pos.x < (SUPSKILL_SIZE_X / 2) - FIELD_SCL_MAX_X)
			{
				DeletePlayerSupSkill(i);
			}
			if (playersupSkill->pos.x > FIELD_SCL_MAX_X - (SUPSKILL_SIZE_X / 2))
			{
				DeletePlayerSupSkill(i);
			}
			if (playersupSkill->pos.z > FIELD_SCL_MAX_Z)
			{
				DeletePlayerSupSkill(i);
			}
			if (playersupSkill->pos.z < (SUPSKILL_SIZE_Y / 2) - FIELD_SCL_MAX_Z)
			{
				DeletePlayerSupSkill(i);
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayerSupSkill(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView,mtxscl,mtxTranslate;
	PLAYER_SUPSKILL *playersupSkill = playersupSkillWk;

	// ライティングを無効に
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// αテストを有効に
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

 for(int i = 0; i < MAX_SUPSKILL; i++, playersupSkill++)
	{
		if(playersupSkill->bUse)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&playersupSkill->world);

			// ビューマトリックスを取得
			mtxView = GetMtxView();

			playersupSkill->world._11 = mtxView._11;
			playersupSkill->world._12 = mtxView._21;
			playersupSkill->world._13 = mtxView._31;
			playersupSkill->world._21 = mtxView._12;
			playersupSkill->world._22 = mtxView._22;
			playersupSkill->world._23 = mtxView._32;
			playersupSkill->world._31 = mtxView._13;
			playersupSkill->world._32 = mtxView._23;
			playersupSkill->world._33 = mtxView._33;

			// スケールを反映
			D3DXMatrixScaling(&mtxscl, playersupSkill->scl.x, playersupSkill->scl.y, playersupSkill->scl.z);
			D3DXMatrixMultiply(&playersupSkill->world, &playersupSkill->world, &mtxscl);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, playersupSkill->pos.x, playersupSkill->pos.y, playersupSkill->pos.z);
			D3DXMatrixMultiply(&playersupSkill->world, &playersupSkill->world, &mtxTranslate);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &playersupSkill->world);

			// 頂点バッファをデバイスのデータストリームにバインド
			pDevice->SetStreamSource(0, g_pD3DVtxBuffPlayerSupSkill, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pD3DTexturePlayerSupSkill);

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
HRESULT MakeVertexPlayerSupSkill(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
    if( FAILED( pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * MAX_SUPSKILL,	// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,							// 頂点バッファの使用法　
												FVF_VERTEX_3D,								// 使用する頂点フォーマット
												D3DPOOL_MANAGED,							// リソースのバッファを保持するメモリクラスを指定
												&g_pD3DVtxBuffPlayerSupSkill,						// 頂点バッファインターフェースへのポインタ
												NULL)))										// NULLに設定
	{
        return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffPlayerSupSkill->Lock(0, 0, (void**)&pVtx, 0);

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
		g_pD3DVtxBuffPlayerSupSkill->Unlock();
	}

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexPlayerSupSkill(int nIdxPlayerSupSkill, D3DXVECTOR2 size)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffPlayerSupSkill->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxPlayerSupSkill * 4);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(-size.x / 2, -size.y / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-size.x / 2, size.y / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(size.x / 2, -size.y / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(size.x / 2, size.y / 2, 0.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffPlayerSupSkill->Unlock();
	}
}

//=============================================================================
// 弾の設定
//=============================================================================
int SetPlayerSupSkill(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 size, int timer)
{
	PLAYER_SUPSKILL *playersupSkill = playersupSkillWk;

	int nIdxPlayerSupSkill = -1;

	playersupSkill = GetPlayerSupSkill(0);
 for(int i = 0; i < MAX_SUPSKILL; i++, playersupSkill++)
	{
		if(!playersupSkill->bUse)
		{

			playersupSkill->pos = pos;
			playersupSkill->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			playersupSkill->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			playersupSkill->move = move;
			playersupSkill->size.x = size.x;
			playersupSkill->size.y = size.y;
			playersupSkill->timer = timer;
			playersupSkill->bUse = true;
			playersupSkill->Track = true;

			// 影の設定
			playersupSkill->nIdxShadow = CreateShadow(pos, D3DXVECTOR2(8.0f, 8.0f));		// 影の設定

			// 頂点座標の設定
			SetVertexPlayerSupSkill(i, size);

			nIdxPlayerSupSkill = i;

			break;
		}
	}

	return nIdxPlayerSupSkill;
}

//=============================================================================
// 弾の削除
//=============================================================================
void DeletePlayerSupSkill(int nIdxPlayerSupSkill)
{
	if(nIdxPlayerSupSkill >= 0 && nIdxPlayerSupSkill < MAX_SUPSKILL)
	{
		ReleaseShadow(playersupSkillWk[nIdxPlayerSupSkill].nIdxShadow);
		playersupSkillWk[nIdxPlayerSupSkill].bUse = false;
	}
}

PLAYER_SUPSKILL *GetPlayerSupSkill(int no)
{
	return(&playersupSkillWk[no]);
}


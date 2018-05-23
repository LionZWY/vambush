//=============================================================================
//
// 弾処理 [playerskillDef.cpp]
// Author : 朱文渊
// プログラム作成日 : 2018/3/09
//=============================================================================
#include "player_skillDef.h"
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
HRESULT MakeVertexPlayerSkillDef(LPDIRECT3DDEVICE9 pDevice);
void SetVertexPlayerSkillDef(int nIdxSkillDef, D3DXVECTOR2 size);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTexturePlayerSkillDef = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffPlayerSkillDef	= NULL;		// 頂点バッファインターフェースへのポインタ

PLAYER_SKILLDEF					playerskillDefWk[MAX_SKILLDEF];			// 弾ワーク
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayerSkillDef(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER_SKILLDEF *playerskillDef = playerskillDefWk;

	// 頂点情報の作成
	MakeVertexPlayerSkillDef(pDevice);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
								TEXTURE_SKILLDEF_PLAYER,				// ファイルの名前
								&g_pD3DTexturePlayerSkillDef);	// 読み込むメモリー

													

	for(int i = 0; i < MAX_SKILLDEF; i++, playerskillDef++)
	{
		playerskillDef->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		playerskillDef->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		playerskillDef->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		playerskillDef->move = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		playerskillDef->size.x = SKILLDEF_SIZE_X;
		playerskillDef->size.y = SKILLDEF_SIZE_Y;
		playerskillDef->timer = 0;
		playerskillDef->cnt = 3;
		playerskillDef->bUse = false;
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayerSkillDef(void)
{
	if(g_pD3DTexturePlayerSkillDef != NULL)
	{// テクスチャの開放
		g_pD3DTexturePlayerSkillDef->Release();
		g_pD3DTexturePlayerSkillDef = NULL;
	}

	if(g_pD3DVtxBuffPlayerSkillDef != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffPlayerSkillDef->Release();
		g_pD3DVtxBuffPlayerSkillDef = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayerSkillDef(void)
{
	D3DXVECTOR3 rotCamera;
	PLAYER_SKILLDEF *playerskillDef = playerskillDefWk;


	// カメラの回転を取得
	rotCamera = GetRotCamera();

 for(int i = 0; i < MAX_SKILLDEF; i++, playerskillDef++)
	{
		if(playerskillDef->bUse)
		{
			playerskillDef->pos.x += playerskillDef->move.x;
			playerskillDef->pos.z += playerskillDef->move.z;

			playerskillDef->timer--;
			if(playerskillDef->timer <= 0)
			{
				ReleaseShadow(playerskillDef->nIdxShadow);
				playerskillDef->bUse = false;
			}
			else
			{
				// 影の位置設定
				SetPositionShadow(playerskillDef->nIdxShadow, D3DXVECTOR3(playerskillDef->pos.x, 0.1f, playerskillDef->pos.z));


				// エフェクトの設定
				SetEffect(playerskillDef->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(0.85f, 0.05f, 0.15f, 0.50f), D3DXVECTOR2(32.0f, 32.0f), 10);
				SetEffect(playerskillDef->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(0.65f, 0.10f, 0.10f, 0.30f), D3DXVECTOR2(20.0f, 20.0f), 10);
				SetEffect(playerskillDef->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(0.45f, 0.15f, 0.05f, 0.20f), D3DXVECTOR2(6.0f, 6.0f), 10);


			}

			D3DXVECTOR2	size;
			size.x = 8.0f + (playerskillDef->pos.y - 4.0f) * 0.05f;
			if(size.x < 8.0f)
			{
				size.x = 8.0f;
			}
			size.y = 8.0f + (playerskillDef->pos.y - 4.0f) * 0.05f;
			if(size.y < 8.0f)
			{
				size.y = 8.0f;
			}

			SetVertexShadow(playerskillDef->nIdxShadow, size);

			float colA = (200.0f - (playerskillDef->pos.y - 4.0f)) / 400.0f;
			if(colA < 0.0f)
			{
				colA = 0.0f;
			}
			SetColorShadow(playerskillDef->nIdxShadow, D3DXCOLOR(1.0f, 1.0f, 1.0f, colA));

			if (playerskillDef->pos.x < (SKILLDEF_SIZE_X / 2) - FIELD_SCL_MAX_X)
			{
				DeletePlayerSkillDef(i);
			}
			if (playerskillDef->pos.x > FIELD_SCL_MAX_X - (SKILLDEF_SIZE_X / 2))
			{
				DeletePlayerSkillDef(i);
			}
			if (playerskillDef->pos.z > FIELD_SCL_MAX_Z)
			{
				DeletePlayerSkillDef(i);
			}
			if (playerskillDef->pos.z < (SKILLDEF_SIZE_Y / 2) - FIELD_SCL_MAX_Z)
			{
				DeletePlayerSkillDef(i);
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayerSkillDef(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView,mtxscl,mtxTranslate;
	PLAYER_SKILLDEF *playerskillDef = playerskillDefWk;

	// ライティングを無効に
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// αテストを有効に
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

 for(int i = 0; i < MAX_SKILLDEF; i++, playerskillDef++)
	{
		if(playerskillDef->bUse)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&playerskillDef->world);

			// ビューマトリックスを取得
			mtxView = GetMtxView();

			playerskillDef->world._11 = mtxView._11;
			playerskillDef->world._12 = mtxView._21;
			playerskillDef->world._13 = mtxView._31;
			playerskillDef->world._21 = mtxView._12;
			playerskillDef->world._22 = mtxView._22;
			playerskillDef->world._23 = mtxView._32;
			playerskillDef->world._31 = mtxView._13;
			playerskillDef->world._32 = mtxView._23;
			playerskillDef->world._33 = mtxView._33;

			// スケールを反映
			D3DXMatrixScaling(&mtxscl, playerskillDef->scl.x, playerskillDef->scl.y, playerskillDef->scl.z);
			D3DXMatrixMultiply(&playerskillDef->world, &playerskillDef->world, &mtxscl);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, playerskillDef->pos.x, playerskillDef->pos.y, playerskillDef->pos.z);
			D3DXMatrixMultiply(&playerskillDef->world, &playerskillDef->world, &mtxTranslate);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &playerskillDef->world);

			// 頂点バッファをデバイスのデータストリームにバインド
			pDevice->SetStreamSource(0, g_pD3DVtxBuffPlayerSkillDef, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pD3DTexturePlayerSkillDef);

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
HRESULT MakeVertexPlayerSkillDef(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
    if( FAILED( pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * MAX_SKILLDEF,	// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,							// 頂点バッファの使用法　
												FVF_VERTEX_3D,								// 使用する頂点フォーマット
												D3DPOOL_MANAGED,							// リソースのバッファを保持するメモリクラスを指定
												&g_pD3DVtxBuffPlayerSkillDef,						// 頂点バッファインターフェースへのポインタ
												NULL)))										// NULLに設定
	{
        return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffPlayerSkillDef->Lock(0, 0, (void**)&pVtx, 0);

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
		g_pD3DVtxBuffPlayerSkillDef->Unlock();
	}

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexPlayerSkillDef(int nIdxPlayerSkillDef, D3DXVECTOR2 size)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffPlayerSkillDef->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxPlayerSkillDef * 4);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(-size.x / 2, -size.y / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-size.x / 2, size.y / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(size.x / 2, -size.y / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(size.x / 2, size.y / 2, 0.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffPlayerSkillDef->Unlock();
	}
}

//=============================================================================
// 弾の設定
//=============================================================================
int SetPlayerSkillDef(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 size, int timer)
{
	PLAYER_SKILLDEF *playerskillDef = playerskillDefWk;

	int nIdxPlayerSkillDef = -1;

	playerskillDef = GetPlayerSkillDef(0);
 for(int i = 0; i < MAX_SKILLDEF; i++, playerskillDef++)
	{
		if(!playerskillDef->bUse)
		{

			playerskillDef->pos = pos;
			playerskillDef->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			playerskillDef->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			playerskillDef->move = move;
			playerskillDef->size.x = size.x;
			playerskillDef->size.y = size.y;
			playerskillDef->timer = timer;
			playerskillDef->cnt --;
			playerskillDef->bUse = true;

			// 影の設定
			playerskillDef->nIdxShadow = CreateShadow(pos, D3DXVECTOR2(8.0f, 8.0f));		// 影の設定

			// 頂点座標の設定
			SetVertexPlayerSkillDef(i, size);

			nIdxPlayerSkillDef = i;

			break;
		}
	}

	return nIdxPlayerSkillDef;
}

//=============================================================================
// 弾の削除
//=============================================================================
void DeletePlayerSkillDef(int nIdxPlayerSkillDef)
{
	if(nIdxPlayerSkillDef >= 0 && nIdxPlayerSkillDef < MAX_SKILLDEF)
	{
		ReleaseShadow(playerskillDefWk[nIdxPlayerSkillDef].nIdxShadow);
		playerskillDefWk[nIdxPlayerSkillDef].bUse = false;
	}
}


PLAYER_SKILLDEF *GetPlayerSkillDef(int no)
{
	return(&playerskillDefWk[no]);
}
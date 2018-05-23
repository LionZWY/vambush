//=============================================================================
//
// エフェクト処理 [effect.cpp]
// Author : 朱文渊
// プログラム作成日 : 2018/3/09
//=============================================================================
#include "effect.h"
#include "input.h"
#include "camera.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_EFFECT			"data/TEXTURE/shadow000.jpg"	// 読み込むテクスチャファイル名
#define	EFFECT_SIZE_X			(10.0f)							// ビルボードの幅
#define	EFFECT_SIZE_Y			(10.0f)							// ビルボードの高さ
#define	VALUE_MOVE_BULLET		(2.0f)							// 移動速度

#define	MAX_EFFECT				(4096)							// エフェクト最大数


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice);
void SetVertexEffect(int nIdxEffect, D3DXVECTOR2 size);
void SetColorEffect(int nIdxEffect, D3DXCOLOR col);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureEffect = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffEffect = NULL;		// 頂点バッファインターフェースへのポインタ

EFFECT					effectWk[MAX_EFFECT];			// 弾ワーク

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT *effect = effectWk;

	// 頂点情報の作成
	MakeVertexEffect(pDevice);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
								TEXTURE_EFFECT,			// ファイルの名前
								&g_pD3DTextureEffect);	// 読み込むメモリー

	for(int i = 0; i < MAX_EFFECT; i++, effect++)
	{
		effect->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		effect->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		effect->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		effect->move = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		effect->size.x = EFFECT_SIZE_X;
		effect->size.y = EFFECT_SIZE_Y;
		effect->timer = 0;
		effect->bUse = false;
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEffect(void)
{
	if(g_pD3DTextureEffect != NULL)
	{// テクスチャの開放
		g_pD3DTextureEffect->Release();
		g_pD3DTextureEffect = NULL;
	}

	if(g_pD3DVtxBuffEffect != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffEffect->Release();
		g_pD3DVtxBuffEffect = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEffect(void)
{
	D3DXVECTOR3 rotCamera;
	EFFECT *effect = effectWk;

	// カメラの回転を取得
	rotCamera = GetRotCamera();

 for(int i = 0; i < MAX_EFFECT; i++, effect++)
	{
		if(effect->bUse)
		{
			effect->pos.x += effect->move.x;
			effect->pos.z += effect->move.z;

			effect->col.a -= effect->nDecAlpha;
			if(effect->col.a <= 0.0f)
			{
				effect->col.a = 0.0f;
			}
			SetColorEffect(i,
							D3DXCOLOR(effect->col.r,effect->col.b,
										effect->col.b, effect->col.a));

			effect->timer--;
			if(effect->timer <= 0)
			{
				effect->bUse = false;
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView,mtxscl,mtxTranslate;
	EFFECT *effect = effectWk;

	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);			// αデスティネーションカラーの指定
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);			// Z比較なし

//	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// アルファブレンディング処理
//	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// 最初のアルファ引数
//	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// ２番目のアルファ引数

 for(int i = 0; i < MAX_EFFECT; i++, effect++)
	{
		if(effect->bUse)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&effect->world);

			// ビューマトリックスを取得
			mtxView = GetMtxView();

			effect->world._11 = mtxView._11;
			effect->world._12 = mtxView._21;
			effect->world._13 = mtxView._31;
			effect->world._21 = mtxView._12;
			effect->world._22 = mtxView._22;
			effect->world._23 = mtxView._32;
			effect->world._31 = mtxView._13;
			effect->world._32 = mtxView._23;
			effect->world._33 = mtxView._33;

			// スケールを反映
			D3DXMatrixScaling(&mtxscl, effect->scl.x, effect->scl.y, effect->scl.z);
			D3DXMatrixMultiply(&effect->world, &effect->world, &mtxscl);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, effect->pos.x, effect->pos.y, effect->pos.z);
			D3DXMatrixMultiply(&effect->world, &effect->world, &mtxTranslate);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &effect->world);

			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			// 頂点バッファをデバイスのデータストリームにバインド
			pDevice->SetStreamSource(0, g_pD3DVtxBuffEffect, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pD3DTextureEffect);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (i * 4), NUM_POLYGON);

			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		}
	}

	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);				// Z比較あり

//	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
//	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
//	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
HRESULT MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
    if( FAILED( pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * MAX_EFFECT,	// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,							// 頂点バッファの使用法　
												FVF_VERTEX_3D,								// 使用する頂点フォーマット
												D3DPOOL_MANAGED,							// リソースのバッファを保持するメモリクラスを指定
												&g_pD3DVtxBuffEffect,						// 頂点バッファインターフェースへのポインタ
												NULL)))										// NULLに設定
	{
        return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

		for(int i = 0; i < MAX_EFFECT; i++, pVtx += 4)
		{
			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(-EFFECT_SIZE_X / 2, -EFFECT_SIZE_Y / 2, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(EFFECT_SIZE_X / 2, -EFFECT_SIZE_Y / 2, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(-EFFECT_SIZE_X / 2, EFFECT_SIZE_Y / 2, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(EFFECT_SIZE_X / 2, EFFECT_SIZE_Y / 2, 0.0f);

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
		g_pD3DVtxBuffEffect->Unlock();
	}

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexEffect(int nIdxEffect, D3DXVECTOR2 size)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxEffect * 4);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(-size.x / 2, -size.y / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-size.x / 2, size.y / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(size.x / 2, -size.y / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(size.x / 2, size.y / 2, 0.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffEffect->Unlock();
	}
}

//=============================================================================
// 頂点カラーの設定
//=============================================================================
void SetColorEffect(int nIdxEffect, D3DXCOLOR col)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxEffect * 4);

		// 頂点座標の設定
		pVtx[0].diffuse =
		pVtx[1].diffuse =
		pVtx[2].diffuse =
		pVtx[3].diffuse = col;

		// 頂点データをアンロックする
		g_pD3DVtxBuffEffect->Unlock();
	}
}
//=============================================================================
// エフェクトの設定
//=============================================================================
int SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, D3DXVECTOR2 size, int timer)
{
	EFFECT *effect = effectWk;

	int nIdxEffect = -1;

 for(int i = 0; i < MAX_EFFECT; i++, effect++)
	{
		if(!effect->bUse)
		{
			effect->pos = pos;
			effect->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			effect->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			effect->move = move;
			effect->col = col;
			effect->size.x = size.x;
			effect->size.y = size.y;
			effect->timer = timer;
			effect->nDecAlpha = col.a / timer;
			effect->bUse = true;

			// 頂点座標の設定
			SetVertexEffect(i, size);

			// 頂点カラーの設定
			SetColorEffect(i,
							D3DXCOLOR(effect->col.r,effect->col.b,
										effect->col.b, effect->col.a));

			nIdxEffect = i;

			break;
		}
	}

	return nIdxEffect;
}

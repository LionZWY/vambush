//=============================================================================
//
// 爆発処理 [noize.cpp]
// Author : 朱文渊
// プログラム作成日 : 2018/3/09
//=============================================================================
#include "noize.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_NOIZE		"data/TEXTURE/noize_eff.png"	// 読み込むテクスチャファイル名
#define	NOIZE_SIZE_X		(50.0f)							// ビルボードの幅
#define	NOIZE_SIZE_Y		(50.0f)							// ビルボードの高さ
#define	VALUE_MOVE_NOIZE	(2.0f)							// 移動速度

#define	MAX_NOIZE			(128)							// ビルボード最大数

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 rot;		// 回転
	D3DXVECTOR3 scale;		// スケール
	D3DXCOLOR col;			// 色
	float fSizeX;			// 幅
	float fSizeY;			// 高さ
	int nCounter;			// カウンター
	int nPattern;			// パターンNo.
	int nType;				// 種類
	bool bUse;				// 使用しているかどうか
} NOIZE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexNoize(LPDIRECT3DDEVICE9 pDevice);
void SetVertexNoize(int nIdxBullet, float fSizeX, float fSizeY);
void SetColorNoize(int nIdxNoize, D3DXCOLOR col);
void SetTextureNoize(int nIdxNoize, int nPattern);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureNoize = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffNoize = NULL;	// 頂点バッファインターフェースへのポインタ

D3DXMATRIX				g_mtxWorldNoize;			// ワールドマトリックス

NOIZE				g_aNoize[MAX_NOIZE];	// 爆発ワーク

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitNoize(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点情報の作成
	MakeVertexNoize(pDevice);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
								TEXTURE_NOIZE,			// ファイルの名前
								&g_pD3DTextureNoize);	// 読み込むメモリー

	for(int nCntNoize = 0; nCntNoize < MAX_NOIZE; nCntNoize++)
	{
		g_aNoize[nCntNoize].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aNoize[nCntNoize].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aNoize[nCntNoize].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_aNoize[nCntNoize].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aNoize[nCntNoize].fSizeX = NOIZE_SIZE_X;
		g_aNoize[nCntNoize].fSizeY = NOIZE_SIZE_Y;
		g_aNoize[nCntNoize].nCounter = 0;
		g_aNoize[nCntNoize].nPattern = 0;
		g_aNoize[nCntNoize].nType = NOIZETYPE_NOIZE_PLAYER;
		g_aNoize[nCntNoize].bUse = false;
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitNoize(void)
{
	if(g_pD3DTextureNoize != NULL)
	{// テクスチャの開放
		g_pD3DTextureNoize->Release();
		g_pD3DTextureNoize = NULL;
	}

	if(g_pD3DVtxBuffNoize != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffNoize->Release();
		g_pD3DVtxBuffNoize = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateNoize(void)
{
	D3DXVECTOR3 rotCamera;
	CAMERA *camera = GetCamera();

	// カメラの回転を取得
	rotCamera = camera->rot;

	for(int nCntNoize = 0; nCntNoize < MAX_NOIZE; nCntNoize++)
	{
		if(g_aNoize[nCntNoize].bUse)
		{
			g_aNoize[nCntNoize].nCounter--;
			if((g_aNoize[nCntNoize].nCounter % 4) == 0)
			{
				g_aNoize[nCntNoize].nPattern++;
				if(g_aNoize[nCntNoize].nPattern >= 6)
				{
					g_aNoize[nCntNoize].bUse = false;
				}
				else
				{
					// テクスチャ座標の設定
					SetTextureNoize(nCntNoize, g_aNoize[nCntNoize].nPattern);
				}
			}

			// 頂点座標の設定
			g_aNoize[nCntNoize].fSizeX += 0.50f;
			g_aNoize[nCntNoize].fSizeY += 0.50f;
			SetVertexNoize(nCntNoize, g_aNoize[nCntNoize].fSizeX, g_aNoize[nCntNoize].fSizeY);

			if(g_aNoize[nCntNoize].nPattern >= 2)
			{
				// 頂点カラーの設定
				g_aNoize[nCntNoize].col.a -= 0.02f;
				if(g_aNoize[nCntNoize].col.a < 0.0f)
				{
					g_aNoize[nCntNoize].col.a = 0.0f;
				}
				SetColorNoize(nCntNoize, g_aNoize[nCntNoize].col);
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawNoize(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView,mtxScale,mtxTranslate;

	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);				// Z比較なし

	for(int nCntNoize = 0; nCntNoize < MAX_NOIZE; nCntNoize++)
	{
		if(g_aNoize[nCntNoize].bUse)
		{

			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_mtxWorldNoize);

			// ビューマトリックスを取得
			mtxView = GetMtxView();

			g_mtxWorldNoize._11 = mtxView._11;
			g_mtxWorldNoize._12 = mtxView._21;
			g_mtxWorldNoize._13 = mtxView._31;
			g_mtxWorldNoize._21 = mtxView._12;
			g_mtxWorldNoize._22 = mtxView._22;
			g_mtxWorldNoize._23 = mtxView._32;
			g_mtxWorldNoize._31 = mtxView._13;
			g_mtxWorldNoize._32 = mtxView._23;
			g_mtxWorldNoize._33 = mtxView._33;

			// スケールを反映
			D3DXMatrixScaling(&mtxScale, g_aNoize[nCntNoize].scale.x, g_aNoize[nCntNoize].scale.y, g_aNoize[nCntNoize].scale.z);
			D3DXMatrixMultiply(&g_mtxWorldNoize, &g_mtxWorldNoize, &mtxScale);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, g_aNoize[nCntNoize].pos.x, g_aNoize[nCntNoize].pos.y, g_aNoize[nCntNoize].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldNoize, &g_mtxWorldNoize, &mtxTranslate);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldNoize);

			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			// 頂点バッファをデバイスのデータストリームにバインド
			pDevice->SetStreamSource(0, g_pD3DVtxBuffNoize, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pD3DTextureNoize);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntNoize * 3), NUM_POLYGON);

			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		}
	}

	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);				// Z比較あり
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
HRESULT MakeVertexNoize(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
    if( FAILED( pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * MAX_NOIZE,	// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,							// 頂点バッファの使用法　
												FVF_VERTEX_3D,								// 使用する頂点フォーマット
												D3DPOOL_MANAGED,							// リソースのバッファを保持するメモリクラスを指定
												&g_pD3DVtxBuffNoize,					// 頂点バッファインターフェースへのポインタ
												NULL)))										// NULLに設定
	{
        return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffNoize->Lock(0, 0, (void**)&pVtx, 0);

		for(int nCntNoize = 0; nCntNoize < MAX_NOIZE; nCntNoize++, pVtx += 4)
		{
			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(-NOIZE_SIZE_X / 2, -NOIZE_SIZE_Y / 2, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(NOIZE_SIZE_X / 2, -NOIZE_SIZE_Y / 2, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(-NOIZE_SIZE_X / 2, NOIZE_SIZE_Y / 2, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(NOIZE_SIZE_X / 2, NOIZE_SIZE_Y / 2, 0.0f);

			// 法線の設定
			pVtx[0].vtx = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[1].vtx = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[2].vtx = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[3].vtx = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

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
		g_pD3DVtxBuffNoize->Unlock();
	}

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexNoize(int nIdxNoize, float fSizeX, float fSizeY)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffNoize->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxNoize * 4);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(-fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-fSizeX / 2, fSizeY / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(fSizeX / 2, fSizeY / 2, 0.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffNoize->Unlock();
	}
}

//=============================================================================
// 頂点カラーの設定
//=============================================================================
void SetColorNoize(int nIdxNoize, D3DXCOLOR col)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffNoize->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxNoize * 4);

		// 頂点座標の設定
		pVtx[0].diffuse =
		pVtx[1].diffuse =
		pVtx[2].diffuse =
		pVtx[3].diffuse = col;

		// 頂点データをアンロックする
		g_pD3DVtxBuffNoize->Unlock();
	}
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureNoize(int nIdxNoize, int nPattern)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffNoize->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxNoize * 4);

		// 頂点座標の設定
		pVtx[0].tex = D3DXVECTOR2(nPattern * (float)(1.0f / 6), 0.0f);
		pVtx[1].tex = D3DXVECTOR2((nPattern + 1) * (float)(1.0f / 6), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(nPattern * (float)(1.0f / 6), 1.0f);
		pVtx[3].tex = D3DXVECTOR2((nPattern + 1) * (float)(1.0f / 6), 1.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffNoize->Unlock();
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
int SetNoize(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nType)
{
	int nIdxNoize = -1;

	for(int nCntNoize = 0; nCntNoize < MAX_NOIZE; nCntNoize++)
	{
		if(!g_aNoize[nCntNoize].bUse)
		{
			g_aNoize[nCntNoize].pos = pos;
			g_aNoize[nCntNoize].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aNoize[nCntNoize].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_aNoize[nCntNoize].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_aNoize[nCntNoize].fSizeX = fSizeX;
			g_aNoize[nCntNoize].fSizeY = fSizeY;
			g_aNoize[nCntNoize].nCounter = 0;
			g_aNoize[nCntNoize].nPattern = 0;
			g_aNoize[nCntNoize].nType = nType;
			g_aNoize[nCntNoize].bUse = true;

			// 頂点座標の設定
			SetVertexNoize(nCntNoize, fSizeX, fSizeY);

			if(g_aNoize[nCntNoize].nType == NOIZETYPE_NOIZE_PLAYER)
			{
				g_aNoize[nCntNoize].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); 
			}
			else if(g_aNoize[nCntNoize].nType == NOIZETYPE_NOIZE_ENEMY)
			{
				g_aNoize[nCntNoize].col = D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f); 
			}
			SetColorNoize(nCntNoize, g_aNoize[nCntNoize].col);

			// テクスチャ座標の設定
			SetTextureNoize(nCntNoize, 0);

			nIdxNoize = nCntNoize;

			break;
		}
	}

	return nIdxNoize;
}

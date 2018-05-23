//=============================================================================
//
// フェード処理 [fade.cpp]
// Author : 眞戸原史也
// プログラム作成日 : 2018/3/09
//
//=============================================================================
#include "fade.h"					// マクロ使用の為
#include "main.h"					// 同上
#include "game.h"					// 同上
#include "camera.h"					// 関数使用の為
#include "sound.h"					// 同上

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	FADE_RATE		(0.02f)		// フェード係数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexFade(LPDIRECT3DDEVICE9 pDevice);		// 頂点作成関数
void SetColor(D3DCOLOR col);							// 色設定関数

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_p3DTextureFade = NULL;	// テクスチャへのポインタ変数
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffFade = NULL;	// 頂点バッファインターフェースへのポインタ変数

D3DXCOLOR				g_color;					// 色格納変数
FADE					g_fade = FADE_IN;			// 状態格納変数

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT InitFade(void)
{
	// ポインタの初期化
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点情報の設定
	MakeVertexFade(pDevice);

	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void UninitFade(void)
{
	if(g_p3DTextureFade != NULL)
	{// テクスチャの開放
		g_p3DTextureFade->Release();
	}

	if(g_pD3DVtxBuffFade != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffFade->Release();
	}
}

//=============================================================================
// 更新処理関数
//=============================================================================
void UpdateFade(void)
{
	// フェード処理
	if(g_fade != FADE_NONE)
	{
		// フェード処理中
		if(g_fade == FADE_OUT)
		{
			// フェードアウト処理
			g_color.a += FADE_RATE;		// α値を加算して画面を消していく

			// フェードアウト終了
			if(g_color.a >= 1.0f)
			{

				// フェードイン処理に切り替え
				g_color.a = 1.0f;
				SetFade(FADE_IN);

				//// 現在のモードを取得
				int *mode = GetStage();

				// モードを１つ進める
				*mode = ((*mode + 1) % STAGE_MAX);

				// ゲームカメラに切り替え
				if (*mode == STAGE_GAME)
				{
					InitCamera();
				}

				// モードを設定
				SetStage(*mode);

				// モード中の音楽の適応
				int sound = *mode;

				// 音楽を設定
				SetSound(sound);
			}

			// 色を設定
			SetColor(g_color);
		}

		// フェードイン処理
		else if(g_fade == FADE_IN)
		{
			
			// α値を減算して画面を浮き上がらせる
			g_color.a -= FADE_RATE;

			// フェードイン終了
			if(g_color.a <= 0.0f)
			{
				// フェード処理終了
				g_color.a = 0.0f;
				SetFade(FADE_NONE);
			}

			// 色を設定
			SetColor(g_color);
		}
	}
}

//=============================================================================
// 描画処理関数
//=============================================================================
void DrawFade(void)
{

	// ポインタの初期化
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pD3DVtxBuffFade, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, NULL);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//=============================================================================
// 頂点作成関数
//=============================================================================
HRESULT MakeVertexFade(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
    if( FAILED( pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,		// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,				// 頂点バッファの使用法　
												FVF_VERTEX_2D,					// 使用する頂点フォーマット
												D3DPOOL_MANAGED,				// リソースのバッファを保持するメモリクラスを指定
												&g_pD3DVtxBuffFade,				// 頂点バッファインターフェースへのポインタ
												NULL)))							// NULLに設定
	{
        return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

		// テクスチャのパースペクティブコレクト用
		pVtx[0].rhw =
		pVtx[1].rhw =
		pVtx[2].rhw =
		pVtx[3].rhw = 1.0f;

		// 反射光の設定
		g_color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[0].diffuse = g_color;
		pVtx[1].diffuse = g_color;
		pVtx[2].diffuse = g_color;
		pVtx[3].diffuse = g_color;

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);	

		// 頂点データをアンロックする
		g_pD3DVtxBuffFade->Unlock();
	}

	return S_OK;
}

//=============================================================================
// 色設定関数
//=============================================================================
void SetColor(D3DCOLOR col)
{
	VERTEX_2D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pD3DVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	// 反射光の設定
	pVtx[0].diffuse = col;
	pVtx[1].diffuse = col;
	pVtx[2].diffuse = col;
	pVtx[3].diffuse = col;

	// 頂点データをアンロックする
	g_pD3DVtxBuffFade->Unlock();
}

//=============================================================================
// フェード状態設定関数
//=============================================================================
void SetFade(FADE fade)
{
	g_fade = fade;
}

//=============================================================================
// フェード状態取得関数
//=============================================================================
FADE GetFade(void)
{
	return g_fade;
}

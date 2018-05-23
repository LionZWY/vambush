//=============================================================================
//
// CALL画面処理 [call.cpp]
// Author : 眞戸原史也
// プログラム作成日 : 2018/3/09
//
//=============================================================================

#include "call.h"						// マクロ＆構造体使用の為
#include "main.h"						// マクロ使用の為
#include "game.h"						// 同上
#include "title.h"						// 同上
#include "debugproc.h"					// 同上(デバッグ用)
#include "sound.h"						// 関数使用の為
#include "timer.h"						// マクロ使用の為

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexCall(int no);			// 頂点作成関数
void SetVertexCallEffect(int no);			// エフェクト関数

//*****************************************************************************
// グローバル変数
//*****************************************************************************

CALL callWk[CALL_MAX];						// タイトル構造体最大数宣言

int start_cnt;

bool start_flag;
bool start_bgm;

//float sizex, sizey;						// デバッグ用テクスチャ移動処理変数

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT InitCall(int type)
{

	// ポインタの初期化
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CALL *call = &callWk[0];

	start_flag = false;
	start_bgm = false;
	start_cnt = START_TIME_CALL*FRAME_CNT;

	//// デバッグ用テクスチャ移動処理変数の初期化
	//sizex = CALL_SKILL_PAR_SIZE_X;
	//sizey = CALL_SKILL_PAR_SIZE_Y;

	// 構造体最大数初期化処理
	for(int i = 0; i < CALL_MAX;i++, call++)
	{
		call->PatternAnim = 3;								// アニメパターン番号をランダムで初期化
		call->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 回転の初期化

		// 初起動時
		if (type == FIRST)
		{

			// 全てNULLで初期化
			call->Texture = NULL;

			// HPバー下地
			if (i == CALL_NUM)
			{
				// 位置の設定
				call->use = true;						// 使用で初期
				call->pos = CALL_BASE_POS;				// HPバー下地の位置の初期化

				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					CALL_BASE_TEXTURE,				// ファイルの名前
					&call->Texture);					// 読み込むメモリー
			}

			// HPバー下地
			if (i == CALL_BATTLE)
			{
				// 位置の設定
				call->use = false;						// 使用で初期
				call->pos = CALL_BASE_POS;				// HPバー下地の位置の初期化

														// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					CALL_BATTLE_TEXTURE,				// ファイルの名前
					&call->Texture);					// 読み込むメモリー
			}



			// 頂点情報の作成
			MakeVertexCall(i);
		}

		else if (type == UPDATA)
		{
			// HPバー下地
			if (i == CALL_NUM)
			{
				// 位置の設定
				call->use = true;						// 使用で初期
			}

			// HPバー下地
			if (i == CALL_BATTLE)
			{
				// 位置の設定
				call->use = false;						// 使用で初期
			}

		}
	}

	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void UninitCall(void)
{
	// ポインタの初期化
	CALL *call = &callWk[0];

	// 構造体最大数終了処理
	for (int i = 0; i < CALL_MAX;i++, call++)
	{

		// テクスチャの開放出来ていなかったら
		if (call->Texture != NULL)
		{

			// テクスチャの開放
			call->Texture->Release();
			call->Texture = NULL;
		}
	}

}

//=============================================================================
// 更新処理関数
//=============================================================================
void UpdateCall(void)
{

	// ポインタの初期化
	CALL *call = &callWk[CALL_NUM];
	CALL *callB = &callWk[CALL_BATTLE];

	int Bcnt;
	Bcnt = 0;

	// ゲームスタート時
	if (start_bgm == false)
	{
		// スタートコール再生
		PlaySound(BGM_CALL_START, E_DS8_FLAG_NONE);

		// フラグを使用に変化
		start_bgm = true;
	}

	// 毎フレームデクリメント
	start_cnt--;

	// フレームを秒数に直す
	Bcnt= start_cnt / FRAME_CNT;
	
	// パターンの切り替え
	call->PatternAnim = Bcnt;

	// テクスチャ座標を設定
	SetTextureCall(CALL_NUM, call->PatternAnim);

	if (Bcnt == 0)
	{
		call->use = false;
	}

	if (call->use == false)
	{
		callB->use = true;
	}

	if (start_cnt == 0)
	{
		callB->use = false;
		start_flag = true;
	}


//		// デバッグ用移動拡大処理
//		if (i == CALL_SKILL_PAR)
//		{
//
//			// 左
//			if (GetKeyboardPress(DIK_V))
//			{
//				call->pos.x--;
//			}
//
//			// 右
//			else if (GetKeyboardPress(DIK_B))
//			{
//				call->pos.x++;
//			}
//
//			// 上
//			if (GetKeyboardPress(DIK_N))
//			{
//				call->pos.y--;
//
//			}
//			// 下
//			else if (GetKeyboardPress(DIK_M))
//			{
//				call->pos.y++;
//			}
//
//			// x拡大
//			if (GetKeyboardPress(DIK_I))
//			{
//				sizex++;
//			}
//
//			// x縮小
//			else if (GetKeyboardPress(DIK_O))
//			{
//				sizex--;
//			}
//
//			// Y拡大
//			if (GetKeyboardPress(DIK_K))
//			{
//				sizey++;
//
//			}
//			// Y縮小
//			else if (GetKeyboardPress(DIK_L))
//			{
//				sizey--;
//			}
//
//			// デバック中
//#ifdef _DEBUG
//			// デバック表示
//			PrintDebugProc("サイズ:x%f)\n", sizex*2);
//			PrintDebugProc("サイズ:y%f)\n", sizey*2);
//			PrintDebugProc("座標:X %f)\n", call->pos.x);
//			PrintDebugProc("座標:Y %f)\n", call->pos.y);
//#endif
//		}


}

//=============================================================================
// 描画処理関数
//=============================================================================
void DrawCall(void)
{
	// ポインタの初期化
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CALL *call = &callWk[0];
	
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);


	// 構造体最大数終了処理
	for (int i = 0; i < CALL_MAX;i++, call++)
	{
		// 使用していたら
		if (call->use == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, call->Texture);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, call->vertex, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点作成関数
//=============================================================================
HRESULT MakeVertexCall(int no)
{
	
	// ポインタの初期化
	CALL *call = &callWk[no];

	//  HPバー下地
	if (no==CALL_NUM)
	{
		// 頂点座標の設定
		call->vertex[0].vtx = D3DXVECTOR3(call->pos.x - CALL_BASE_SIZE_X, call->pos.y - CALL_BASE_SIZE_Y, 0.0f);
		call->vertex[1].vtx = D3DXVECTOR3(call->pos.x + CALL_BASE_SIZE_X, call->pos.y - CALL_BASE_SIZE_Y, 0.0f);
		call->vertex[2].vtx = D3DXVECTOR3(call->pos.x - CALL_BASE_SIZE_X, call->pos.y + CALL_BASE_SIZE_Y, 0.0f);
		call->vertex[3].vtx = D3DXVECTOR3(call->pos.x + CALL_BASE_SIZE_X, call->pos.y + CALL_BASE_SIZE_Y, 0.0f);

		// 反射光の設定
		call->vertex[0].diffuse = COLOR_RED;
		call->vertex[1].diffuse = COLOR_BULE;
		call->vertex[2].diffuse = COLOR_RED;
		call->vertex[3].diffuse = COLOR_BULE;

	}

	//  HPバー下地
	if (no == CALL_BATTLE)
	{
		// 頂点座標の設定
		call->vertex[0].vtx = D3DXVECTOR3(call->pos.x - CALL_BATTLE_SIZE_X, call->pos.y - CALL_BATTLE_SIZE_Y, 0.0f);
		call->vertex[1].vtx = D3DXVECTOR3(call->pos.x + CALL_BATTLE_SIZE_X, call->pos.y - CALL_BATTLE_SIZE_Y, 0.0f);
		call->vertex[2].vtx = D3DXVECTOR3(call->pos.x - CALL_BATTLE_SIZE_X, call->pos.y + CALL_BATTLE_SIZE_Y, 0.0f);
		call->vertex[3].vtx = D3DXVECTOR3(call->pos.x + CALL_BATTLE_SIZE_X, call->pos.y + CALL_BATTLE_SIZE_Y, 0.0f);

		// 反射光の設定
		call->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		call->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		call->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		call->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}


	// テクスチャのパースペクティブコレクト用
	call->vertex[0].rhw =
	call->vertex[1].rhw =
	call->vertex[2].rhw =
	call->vertex[3].rhw = 1.0f;


	// テクスチャ座標の設定
	call->vertex[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	call->vertex[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	call->vertex[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	call->vertex[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// テクスチャ座標設定関数
//=============================================================================
void SetTextureCall(int no, int cntPattern)
{

	// ポインタの初期化
	CALL *call = &callWk[no];

	// テクスチャ座標の設定
	int x = cntPattern % CALL_ANIM_PATTERN_DIVIDE_X;
	int y = cntPattern / CALL_ANIM_PATTERN_DIVIDE_Y;
	float sizeX = 1.0f / CALL_ANIM_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / CALL_ANIM_PATTERN_DIVIDE_Y;
	call->vertex[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	call->vertex[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	call->vertex[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	call->vertex[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}


//=============================================================================
// スタートフラグ取得関数
//=============================================================================
bool *GetStartFlag(void)
{
	return(&start_flag);
}

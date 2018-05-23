//=============================================================================
//
// タイトル画面処理 [title.cpp]
// Author : 眞戸原史也
// プログラム作成日 : 2018/3/09
//
//=============================================================================

#include "title.h"					// 構造体＆マクロ使用の為
#include "main.h"					// マクロ使用の為
#include "input.h"					// 関数使用の為
#include "game.h"					// 関数＆マクロ使用の為
#include "debugproc.h"				// 同上(デバッグ用)
#include "fade.h"					// 関数使用の為
#include "sound.h"					// 同上

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexTitle(int no);					// 頂点作成関数
void SetVertexTitleEffect(int no);					// エフェクト関数

//*****************************************************************************
// グローバル変数
//*****************************************************************************


TITLE					titleWk[TITLE_MAX];			// タイトル構造体最大数宣言

bool					effectflag;					// エフェクト用制御変数
int						effect;						// エフェクト用変数

bool					effectflagB;				// エフェクト用制御変数
int						effectB;					// エフェクト用変数

int						g_Alpha;					// αテストの閾値

int						serect;						// 画面遷移制御変数
int						titlecnt;					// カーソル制御変数

//float sizex, sizey;									// デバッグ用テクスチャ移動処理変数

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT InitTitle(int type)
{

	// ポインタの初期化
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TITLE *title = &titleWk[0];

	// エフェクト関係の初期化
	effectflag = true;				// true:プラスする false:マイナスする
	effect=INIT_EFFECT;				// エフェクトのα値の初期化

	effectflagB = false;			// true:プラスする false:マイナスする
	effectB = B_ALPHA_MAX;			// エフェクトのα値の初期化


	// 画面制御変数の初期化
	serect = 0;
	titlecnt = 0;

	// アルファテストの値の設定
	g_Alpha = ALPHA_TEST;

	//// デバッグ用テクスチャ移動処理変数の初期化
	//sizex = TITLE_LOGO_SIZE_X;
	//sizey = TITLE_LOGO_SIZE_Y;

	// 構造体最大数初期化処理
	for(int i = 0; i < TITLE_MAX;i++, title++)
	{

		// 初起動時
		if (type == FIRST)
		{

			// 全てNULLで初期化
			title->Texture = NULL;

			// タイトル下部
			if (i == TITLE_BASE)
			{
				// 位置の設定
				title->use = true;					// true:使用 false:未使用 使用で初期化
				title->pos = TITLE_BASE_POS;		// タイトル背景の位置の初期化

				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					TITLE_BASE_TEXTURE,				// ファイルの名前
					&title->Texture);				// 読み込むメモリー
			}

			// タイトル背景ハイライト
			if (i == TITLE_BASE_LIGHT)
			{
				// 位置の設定
				title->use = true;					// true:使用 false:未使用 使用で初期化
				title->pos = TITLE_BASE_POS;		// タイトル背景ハイライトの位置の初期化

													// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					TITLE_BASE_LIGHT_TEXTURE,		// ファイルの名前
					&title->Texture);				// 読み込むメモリー
			}


			// タイトル背景エフェクト
			else if (i == TITLE_EFFECT)
			{
				// 位置の設定
				title->use = true;					// 使用で初期化
				title->pos = TITLE_EFFECT_POS;		// タイトル背景エフェクトの位置の初期化

				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					TITLE_EFFECT_TEXTURE,			// ファイルの名前
					&title->Texture);				// 読み込むメモリー
			}


			// キャラクター:AI
			else if (i == TITLE_AI)
			{
				// 位置の設定
				title->use = true;					// 使用で初期化
				title->pos = TITLE_AI_POS;			// キャラクター:AIの位置の初期化

													// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					TITLE_AI_TEXTURE,				// ファイルの名前
					&title->Texture);				// 読み込むメモリー
			}

			// キャラクター:ウイルス
			else if (i == TITLE_VIRUS)
			{
				// 位置の設定
				title->use = true;					// 使用で初期化
				title->pos = TITLE_VIRUS_POS;		// キャラクター:ウイルスの位置の初期化

													// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					TITLE_VIRUS_TEXTURE,			// ファイルの名前
					&title->Texture);				// 読み込むメモリー
			}


			// タイトルロゴ
			else if (i == TITLE_LOGO)
			{
				// 位置の設定
				title->use = true;					// 使用で初期化
				title->pos = TITLE_LOGO_POS;		// タイトル上部の位置の初期化

				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					TITLE_LOGO_TEXTURE,				// ファイルの名前
					&title->Texture);				// 読み込むメモリー
			}


			// UI:"ボタンをおしてね"
			// UIエフェクト:"ボタンをおしてね"
			else if ((i == TITLE_ANY)||(i == TITLE_ANY_EFFECT))
			{
				// 位置の設定
				title->use = true;					// 使用で初期化
				title->pos = TITLE_ANY_POS;			// UI:"ボタンをおしてね"＆UIエフェクト:"ボタンをおしてね"の位置の初期化


				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					TITLE_ANY_TEXTURE,				// ファイルの名前
					&title->Texture);				// 読み込むメモリー
			}

			// UI:"はじめる"
			// UIエフェクト:"はじめる"
			else if ((i == TITLE_START) || (i == TITLE_START_EFFECT))
			{
				// 位置の設定
				title->use = false;					// 未使用で初期化
				title->pos = TITLE_START_POS;		// UI:"はじめる"＆UIエフェクト:"はじめる"の位置の初期化

				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					TITLE_START_TEXTURE,			// ファイルの名前
					&title->Texture);				// 読み込むメモリー
			}

			// UI:"はじめる"
			// UIエフェクト:"はじめる"
			else if ((i == TITLE_CREDIT) || (i == TITLE_CREDIT_EFFECT))
			{
				// 位置の設定
				title->use = false;					// 未使用で初期化
				title->pos = TITLE_CREDIT_POS;		// UI:"クレジット"＆UIエフェクト:"クレジット"の位置の初期化

				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					TITLE_CREDIT_TEXTURE,			// ファイルの名前
					&title->Texture);				// 読み込むメモリー
			}

			// UI:"クレジットED"(クレジットテクスチャ)
			else if (i == TITLE_BOAD)
			{
				// 位置の設定
				title->use = false;					// 未使用で初期化
				title->pos = TITLE_BOAD_POS;		// UI:"クレジットED"(クレジットテクスチャ)の位置の初期化

				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					TITLE_BOAD_TEXTURE,				// ファイルの名前
					&title->Texture);				// 読み込むメモリー
			}
		}

		// ゲーム更新時
		else if (type == UPDATA)
		{
			// ひとまず使用で初期化
			title->use = true;

			// タイトルで最初表示するもの以外は未使用で初期化
			// UI:"はじめる"
			// UIエフェクト:"はじめる"
			// UI:"クレジット"
			// UIエフェクト:"クレジット"
			// UI:"クレジットED"(クレジットテクスチャ)
			if ((i == TITLE_START) || (i == TITLE_START_EFFECT) || (i == TITLE_CREDIT) || (i == TITLE_CREDIT_EFFECT)||(i == TITLE_BOAD))
			{
				title->use = false;		// 未使用
			}
		}

		// 頂点情報の作成
		MakeVertexTitle(i);
	}

	return S_OK;
}
//=============================================================================
// 終了処理関数
//=============================================================================
void UninitTitle(void)
{
	// ポインタの初期化
	TITLE *title = &titleWk[0];

	// 構造体最大数終了処理
	for (int i = 0; i < TITLE_MAX;i++, title++)
	{

		// テクスチャの開放出来ていなかったら
		if (title->Texture != NULL)
		{

			// テクスチャの開放
			title->Texture->Release();
			title->Texture = NULL;
		}
	}

}
//=============================================================================
// 更新処理関数
//=============================================================================
void UpdateTitle(void)
{

	// ポインタの初期化
	TITLE *title = &titleWk[0];

	// エフェクト処理
	// プラスフラグ
	if (effectflag == true)
	{
		// エフェクトα値にEFFECT_SPEEDを足す
		effect += EFFECT_SPEED;

		// エフェクトα値が最大
		if (effect == ALPHA_MAX)
		{
			// フラグをマイナスに
			effectflag = false;
		}
	}

	// マイナスフラグ
	else if (effectflag == false)
	{
		// エフェクトα値にEFFECT_SPEEDを引く
		effect -= EFFECT_SPEED;

		// エフェクトα値が最小
		if (effect == ALPHA_BASE)
		{
			// フラグをプラスにに
			effectflag = true;
		}

	}

	// エフェクト処理
	// プラスフラグ
	if (effectflagB == true)
	{
		// エフェクトα値にEFFECT_SPEEDを足す
		effectB += B_EFFECT_SPEED;

		// エフェクトα値が最大
		if (effectB == ALPHA_MAX)
		{
			// フラグをマイナスに
			effectflagB = false;
		}
	}

	// マイナスフラグ
	else if (effectflagB == false)
	{
		// エフェクトα値にEFFECT_SPEEDを引く
		effectB -= B_EFFECT_SPEED;

		// エフェクトα値が最小
		if (effectB == B_ALPHA_BASE)
		{
			// フラグをプラスにに
			effectflagB = true;
		}

	}


	// アニメーション
	// 構造体最大数更新処理
	for (int i = 0; i < TITLE_MAX;i++, title++)
	{

		//		//	 デバッグ用移動拡大処理
		//		if (i == TITLE_START)
		//		{
		//
		//			// 左
		//			if (GetKeyboardPress(DIK_V))
		//			{
		//				title->pos.x--;
		//			}
		//
		//			// 右
		//			else if (GetKeyboardPress(DIK_B))
		//			{
		//				title->pos.x++;
		//			}
		//
		//			// 上
		//			if (GetKeyboardPress(DIK_N))
		//			{
		//				title->pos.y--;
		//
		//			}
		//			// 下
		//			else if (GetKeyboardPress(DIK_M))
		//			{
		//				title->pos.y++;
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
		//			PrintDebugProc("座標:X %f)\n", title->pos.x);
		//			PrintDebugProc("座標:Y %f)\n", title->pos.y);
		//#endif
		//		}

		// エフェクト処理
		SetVertexTitleEffect(i);
	}

	// ステージ遷移処理
	// 初起動時
	if (serect == FIRST)
	{

		// Enter押したら、ステージを切り替える
		if ((GetKeyboardTrigger(DIK_A))||(IsButtonTriggered(0, BUTTON_START)))
		{

			// カーソル決定SEの再生
			PlaySound(SE_PUSH, E_DS8_FLAG_NONE);

			// ポインタの初期化
			TITLE *title = &titleWk[TITLE_ANY];

			// UI部分の更新処理
			for (int i = TITLE_ANY;i < TITLE_MAX;i++, title++)
			{

				// 最初に表示するものを使用
				if ((i == TITLE_START) || (i == TITLE_START_EFFECT) || (i == TITLE_CREDIT))
				{
					title->use = true;
				}

				// それ以外を未使用
				else
				{
					title->use = false;
				}

			}

			// セレクトUIの表示
			serect = UPDATA;
		}
	}

	// セレクトUIの表示中
	else if(serect == UPDATA)
	{
		// 使用する構造体のポインタの初期化
		TITLE *titles = &titleWk[TITLE_START];						// UI:"はじめる"
		TITLE *titleS = &titleWk[TITLE_START_EFFECT];				// UIエフェクト:"はじめる"
		TITLE *titlec = &titleWk[TITLE_CREDIT];						// UI:"クレジット"
		TITLE *titleC = &titleWk[TITLE_CREDIT_EFFECT];				// UIエフェクト:"クレジット"

		// カーソル移動
		switch (titlecnt)
		{

		// UI:"はじめる"の処理
		case TITLE_UI_START:
		{

			// UIエフェクト:"はじめる"を使用に
			titleS->use = true;

			// UIエフェクト:"クレジット"を未使用に
			titleC->use = false;

			// UI:"はじめる"の色を変化
			titles->vertex[0].diffuse = COLOR_RED;
			titles->vertex[1].diffuse = COLOR_BULE;
			titles->vertex[2].diffuse = COLOR_BULE;
			titles->vertex[3].diffuse = COLOR_BULE;

			// UI:"クレジット"の色を元に戻す
			titlec->vertex[0].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
			titlec->vertex[1].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
			titlec->vertex[2].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
			titlec->vertex[3].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);

			// Enterまたは×ボタンを押したら、ステージを切り替える
			if ((GetKeyboardTrigger(DIK_RETURN)) || (IsButtonTriggered(0, BUTTON_C)))
			{

				// カーソル決定SEの再生
				PlaySound(SE_PUSH, E_DS8_FLAG_NONE);

				// 画面遷移:ゲーム
				SetFade(FADE_OUT);

			}

			// Wまたは↑スティックを押したら、カーソル移動
			if ((GetKeyboardTrigger(DIK_W)) || (IsButtonTriggered(0, BUTTON_UP)))
			{

				// カーソル選択SEの再生
				PlaySound(SE_SERECT, E_DS8_FLAG_NONE);

				// カーソルを上に移動
				titlecnt--;
			}

			// Sまたは↓スティックを押したら、カーソル移動
			else if ((GetKeyboardTrigger(DIK_S)) || (IsButtonTriggered(0, BUTTON_DOWN)))
			{

				// カーソル選択SEの再生
				PlaySound(SE_SERECT, E_DS8_FLAG_NONE);

				// カーソルを下に移動
				titlecnt++;
			}

			break;
		}

		// UI:"クレジット"の処理
		case TITLE_UI_CREDIT:
		{

			// UIエフェクト:"クレジット"を使用に
			titleC->use = true;

			// UI:"クレジット"の色を黄色に
			titlec->vertex[0].diffuse = COLOR_RED;
			titlec->vertex[1].diffuse = COLOR_BULE;
			titlec->vertex[2].diffuse = COLOR_BULE;
			titlec->vertex[3].diffuse = COLOR_BULE;

			// UI:"はじめる"の色を元に戻す
			titles->vertex[0].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
			titles->vertex[1].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
			titles->vertex[2].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
			titles->vertex[3].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);

			// UIエフェクト:"はじめる"を未使用に
			titleS->use = false;

			// Enterまたは×ボタンを押したら、クレジットを表示
			if ((GetKeyboardTrigger(DIK_RETURN)) || (IsButtonTriggered(0, BUTTON_C)))
			{

				// カーソル決定SEの再生
				PlaySound(SE_PUSH, E_DS8_FLAG_NONE);

				// カーソル制御変数をクレジットに
				serect = CREDIT;

			}

			// Wまたは↑スティックを押したら、カーソル移動
			if ((GetKeyboardTrigger(DIK_W)) || (IsButtonTriggered(0, BUTTON_UP)))
			{

				// カーソル選択SEの再生
				PlaySound(SE_SERECT, E_DS8_FLAG_NONE);

				// カーソルを上に移動
				titlecnt--;
			}

			// Sまたは↓スティックを押したら、カーソル移動
			else if ((GetKeyboardTrigger(DIK_S)) || (IsButtonTriggered(0, BUTTON_DOWN)))
			{

				// カーソル選択SEの再生
				PlaySound(SE_SERECT, E_DS8_FLAG_NONE);

				// カーソルを下に移動
				titlecnt++;
			}

			break;
		}

		}

		// カーソルループ移動処理
		// UI:"はじめる"で↑入力時
		if (titlecnt < TITLE_UI_START)
		{
			// UI:"クレジット"に移動
			titlecnt = TITLE_UI_MAX - 1;
		}

		// UI:"クレジット"で↓入力時
		else if (titlecnt > TITLE_UI_MAX - 1)
		{
			// UI:"はじめる"に移動
			titlecnt = TITLE_UI_START;
		}
	}

	// UI:"クレジットED"(クレジットテクスチャ)
	else if (serect == CREDIT)
	{

		// 使用する構造体のポインタの初期化 UI:"クレジットED"(クレジットテクスチャ)
		TITLE *titleB = &titleWk[TITLE_BOAD];

		// UI:"クレジットED"(クレジットテクスチャ)を表示
		titleB ->use= true;

		// Enterまたは×ボタンを押したら、カーソル選択に戻る
		if ((GetKeyboardTrigger(DIK_RETURN)) || (IsButtonTriggered(0, BUTTON_C)))
		{

			// カーソル決定SEの再生
			PlaySound(SE_PUSH, E_DS8_FLAG_NONE);

			titleB->use = false;			// UI:"クレジットED"(クレジットテクスチャ)を非表示
			serect = UPDATA;				// 前のカーソル選択処理に戻す
			titlecnt = TITLE_UI_START;		// カーソルを初期位置に戻す
		}

	}


}
//=============================================================================
// 描画処理関数
//=============================================================================
void DrawTitle(void)
{
	// ポインタの初期化
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TITLE *title = &titleWk[0];
	
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// αテストを有効に
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, g_Alpha);		 //条件：変数数値
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);//条件:大きかったら

	// 構造体最大数終了処理
	for (int i = 0; i < TITLE_MAX;i++, title++)
	{

		// テクスチャ使用中
		if (title->use == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, title->Texture);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, title->vertex, sizeof(VERTEX_2D));
		}
	}

	// αテストを無効に
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

//#ifdef _DEBUG
//	// デバッグメッセージ表示
//	DrawDebugProc();
//#endif

}

//=============================================================================
// 頂点の作成関数
//=============================================================================
HRESULT MakeVertexTitle(int no)
{
	
	// ポインタの初期化
	TITLE *title = &titleWk[no];

	// タイトル背景なら
	if ((no==TITLE_BASE)|| (no == TITLE_BASE_LIGHT))
	{
		// 頂点座標の設定
		title->vertex[0].vtx = D3DXVECTOR3(title->pos.x - TITLE_BASE_SIZE_X, title->pos.y - TITLE_BASE_SIZE_Y, 0.0f);
		title->vertex[1].vtx = D3DXVECTOR3(title->pos.x + TITLE_BASE_SIZE_X, title->pos.y - TITLE_BASE_SIZE_Y, 0.0f);
		title->vertex[2].vtx = D3DXVECTOR3(title->pos.x - TITLE_BASE_SIZE_X, title->pos.y + TITLE_BASE_SIZE_Y, 0.0f);
		title->vertex[3].vtx = D3DXVECTOR3(title->pos.x + TITLE_BASE_SIZE_X, title->pos.y + TITLE_BASE_SIZE_Y, 0.0f);

		// 反射光の設定
		title->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 180);
		title->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 180);
		title->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 180);
		title->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 180);

	}

	// タイトル背景エフェクト
	else if (no == TITLE_EFFECT)
	{
		// 頂点座標の設定
		title->vertex[0].vtx = D3DXVECTOR3(title->pos.x - TITLE_EFFECT_SIZE_X, title->pos.y - TITLE_EFFECT_SIZE_Y, 0.0f);
		title->vertex[1].vtx = D3DXVECTOR3(title->pos.x + TITLE_EFFECT_SIZE_X, title->pos.y - TITLE_EFFECT_SIZE_Y, 0.0f);
		title->vertex[2].vtx = D3DXVECTOR3(title->pos.x - TITLE_EFFECT_SIZE_X, title->pos.y + TITLE_EFFECT_SIZE_Y, 0.0f);
		title->vertex[3].vtx = D3DXVECTOR3(title->pos.x + TITLE_EFFECT_SIZE_X, title->pos.y + TITLE_EFFECT_SIZE_Y, 0.0f);

		// 反射光の設定
		title->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 180);
		title->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 180);
		title->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 180);
		title->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 180);
	}

	// キャラクター:AI
	else if (no == TITLE_AI)
	{
		// 頂点座標の設定
		title->vertex[0].vtx = D3DXVECTOR3(title->pos.x - TITLE_AI_SIZE_X, title->pos.y - TITLE_AI_SIZE_Y, 0.0f);
		title->vertex[1].vtx = D3DXVECTOR3(title->pos.x + TITLE_AI_SIZE_X, title->pos.y - TITLE_AI_SIZE_Y, 0.0f);
		title->vertex[2].vtx = D3DXVECTOR3(title->pos.x - TITLE_AI_SIZE_X, title->pos.y + TITLE_AI_SIZE_Y, 0.0f);
		title->vertex[3].vtx = D3DXVECTOR3(title->pos.x + TITLE_AI_SIZE_X, title->pos.y + TITLE_AI_SIZE_Y, 0.0f);

		// 反射光の設定
		title->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// キャラクター:ウイルス
	else if (no == TITLE_VIRUS)
	{
		// 頂点座標の設定
		title->vertex[0].vtx = D3DXVECTOR3(title->pos.x - TITLE_VIRUS_SIZE_X, title->pos.y - TITLE_VIRUS_SIZE_Y, 0.0f);
		title->vertex[1].vtx = D3DXVECTOR3(title->pos.x + TITLE_VIRUS_SIZE_X, title->pos.y - TITLE_VIRUS_SIZE_Y, 0.0f);
		title->vertex[2].vtx = D3DXVECTOR3(title->pos.x - TITLE_VIRUS_SIZE_X, title->pos.y + TITLE_VIRUS_SIZE_Y, 0.0f);
		title->vertex[3].vtx = D3DXVECTOR3(title->pos.x + TITLE_VIRUS_SIZE_X, title->pos.y + TITLE_VIRUS_SIZE_Y, 0.0f);

		// 反射光の設定
		title->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}


	// タイトルロゴ
	else if (no == TITLE_LOGO)
	{
		// 頂点座標の設定
		title->vertex[0].vtx = D3DXVECTOR3(title->pos.x - TITLE_LOGO_SIZE_X, title->pos.y - TITLE_LOGO_SIZE_Y, 0.0f);
		title->vertex[1].vtx = D3DXVECTOR3(title->pos.x + TITLE_LOGO_SIZE_X, title->pos.y - TITLE_LOGO_SIZE_Y, 0.0f);
		title->vertex[2].vtx = D3DXVECTOR3(title->pos.x - TITLE_LOGO_SIZE_X, title->pos.y + TITLE_LOGO_SIZE_Y, 0.0f);
		title->vertex[3].vtx = D3DXVECTOR3(title->pos.x + TITLE_LOGO_SIZE_X, title->pos.y + TITLE_LOGO_SIZE_Y, 0.0f);

		// 反射光の設定
		title->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}


	// UI:"ボタンをおしてね"
	else if (no == TITLE_ANY)
	{
		// 頂点座標の設定
		title->vertex[0].vtx = D3DXVECTOR3(title->pos.x - TITLE_ANY_SIZE_X, title->pos.y - TITLE_ANY_SIZE_Y, 0.0f);
		title->vertex[1].vtx = D3DXVECTOR3(title->pos.x + TITLE_ANY_SIZE_X, title->pos.y - TITLE_ANY_SIZE_Y, 0.0f);
		title->vertex[2].vtx = D3DXVECTOR3(title->pos.x - TITLE_ANY_SIZE_X, title->pos.y + TITLE_ANY_SIZE_Y, 0.0f);
		title->vertex[3].vtx = D3DXVECTOR3(title->pos.x + TITLE_ANY_SIZE_X, title->pos.y + TITLE_ANY_SIZE_Y, 0.0f);

		// 反射光の設定
		title->vertex[0].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		title->vertex[1].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		title->vertex[2].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		title->vertex[3].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);

	}


	// UIエフェクト:"ボタンをおしてね"
	else if (no == TITLE_ANY_EFFECT)
	{
		// 頂点座標の設定
		title->vertex[0].vtx = D3DXVECTOR3(title->pos.x - TITLE_ANY_EFFECT_SIZE_X, title->pos.y - TITLE_ANY_EFFECT_SIZE_Y, 0.0f);
		title->vertex[1].vtx = D3DXVECTOR3(title->pos.x + TITLE_ANY_EFFECT_SIZE_X, title->pos.y - TITLE_ANY_EFFECT_SIZE_Y, 0.0f);
		title->vertex[2].vtx = D3DXVECTOR3(title->pos.x - TITLE_ANY_EFFECT_SIZE_X, title->pos.y + TITLE_ANY_EFFECT_SIZE_Y, 0.0f);
		title->vertex[3].vtx = D3DXVECTOR3(title->pos.x + TITLE_ANY_EFFECT_SIZE_X, title->pos.y + TITLE_ANY_EFFECT_SIZE_Y, 0.0f);

		// 反射光の設定
		title->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, effect);
		title->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, effect);
		title->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, effect);
		title->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, effect);

	}

	// UI:"はじめる"
	else if (no == TITLE_START)
	{
		// 頂点座標の設定
		title->vertex[0].vtx = D3DXVECTOR3(title->pos.x - TITLE_START_SIZE_X, title->pos.y - TITLE_START_SIZE_Y, 0.0f);
		title->vertex[1].vtx = D3DXVECTOR3(title->pos.x + TITLE_START_SIZE_X, title->pos.y - TITLE_START_SIZE_Y, 0.0f);
		title->vertex[2].vtx = D3DXVECTOR3(title->pos.x - TITLE_START_SIZE_X, title->pos.y + TITLE_START_SIZE_Y, 0.0f);
		title->vertex[3].vtx = D3DXVECTOR3(title->pos.x + TITLE_START_SIZE_X, title->pos.y + TITLE_START_SIZE_Y, 0.0f);

		// 反射光の設定
		title->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255,255, 255);
		title->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255,255, 255);
		title->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255,255, 255);
		title->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255,255, 255);

	}


	// UIエフェクト:"はじめる"
	else if (no == TITLE_START_EFFECT)
	{
		// 頂点座標の設定
		title->vertex[0].vtx = D3DXVECTOR3(title->pos.x - TITLE_START_EFFECT_SIZE_X, title->pos.y - TITLE_START_EFFECT_SIZE_Y, 0.0f);
		title->vertex[1].vtx = D3DXVECTOR3(title->pos.x + TITLE_START_EFFECT_SIZE_X, title->pos.y - TITLE_START_EFFECT_SIZE_Y, 0.0f);
		title->vertex[2].vtx = D3DXVECTOR3(title->pos.x - TITLE_START_EFFECT_SIZE_X, title->pos.y + TITLE_START_EFFECT_SIZE_Y, 0.0f);
		title->vertex[3].vtx = D3DXVECTOR3(title->pos.x + TITLE_START_EFFECT_SIZE_X, title->pos.y + TITLE_START_EFFECT_SIZE_Y, 0.0f);

		// 反射光の設定
		title->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, effect);
		title->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, effect);
		title->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, effect);
		title->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, effect);

	}


	// UI:"クレジット"
	else if (no == TITLE_CREDIT)
	{
		// 頂点座標の設定
		title->vertex[0].vtx = D3DXVECTOR3(title->pos.x - TITLE_CREDIT_SIZE_X, title->pos.y - TITLE_CREDIT_SIZE_Y, 0.0f);
		title->vertex[1].vtx = D3DXVECTOR3(title->pos.x + TITLE_CREDIT_SIZE_X, title->pos.y - TITLE_CREDIT_SIZE_Y, 0.0f);
		title->vertex[2].vtx = D3DXVECTOR3(title->pos.x - TITLE_CREDIT_SIZE_X, title->pos.y + TITLE_CREDIT_SIZE_Y, 0.0f);
		title->vertex[3].vtx = D3DXVECTOR3(title->pos.x + TITLE_CREDIT_SIZE_X, title->pos.y + TITLE_CREDIT_SIZE_Y, 0.0f);

		// 反射光の設定
		title->vertex[0].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		title->vertex[1].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		title->vertex[2].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		title->vertex[3].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);

	}

	// UIエフェクト:"クレジット"
	else if (no == TITLE_CREDIT_EFFECT)
	{
		// 頂点座標の設定
		title->vertex[0].vtx = D3DXVECTOR3(title->pos.x - TITLE_START_EFFECT_SIZE_X, title->pos.y - TITLE_START_EFFECT_SIZE_Y, 0.0f);
		title->vertex[1].vtx = D3DXVECTOR3(title->pos.x + TITLE_START_EFFECT_SIZE_X, title->pos.y - TITLE_START_EFFECT_SIZE_Y, 0.0f);
		title->vertex[2].vtx = D3DXVECTOR3(title->pos.x - TITLE_START_EFFECT_SIZE_X, title->pos.y + TITLE_START_EFFECT_SIZE_Y, 0.0f);
		title->vertex[3].vtx = D3DXVECTOR3(title->pos.x + TITLE_START_EFFECT_SIZE_X, title->pos.y + TITLE_START_EFFECT_SIZE_Y, 0.0f);

		// 反射光の設定
		title->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, effect);
		title->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, effect);
		title->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, effect);
		title->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, effect);

	}

	// UI:"クレジットED"(クレジットテクスチャ)
	else if (no == TITLE_BOAD)
	{
		// 頂点座標の設定
		title->vertex[0].vtx = D3DXVECTOR3(title->pos.x - TITLE_BOAD_SIZE_X, title->pos.y - TITLE_BOAD_SIZE_Y, 0.0f);
		title->vertex[1].vtx = D3DXVECTOR3(title->pos.x + TITLE_BOAD_SIZE_X, title->pos.y - TITLE_BOAD_SIZE_Y, 0.0f);
		title->vertex[2].vtx = D3DXVECTOR3(title->pos.x - TITLE_BOAD_SIZE_X, title->pos.y + TITLE_BOAD_SIZE_Y, 0.0f);
		title->vertex[3].vtx = D3DXVECTOR3(title->pos.x + TITLE_BOAD_SIZE_X, title->pos.y + TITLE_BOAD_SIZE_Y, 0.0f);

		// 反射光の設定
		title->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}


	// テクスチャのパースペクティブコレクト用
	title->vertex[0].rhw =
	title->vertex[1].rhw =
	title->vertex[2].rhw =
	title->vertex[3].rhw = 1.0f;


	// テクスチャ座標の設定
	title->vertex[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	title->vertex[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	title->vertex[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	title->vertex[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// エフェクト関数
//=============================================================================
void SetVertexTitleEffect(int no)
{

	// ポインタの初期化
	TITLE *title = &titleWk[no];



	// デバッグ用テクスチャ更新
	// HPバー
	//if (no == TITLE_START)
	//{
	//	// 頂点座標の設定
	//	title->vertex[0].vtx = D3DXVECTOR3(title->pos.x - sizex, title->pos.y - sizey, 0.0f);
	//	title->vertex[1].vtx = D3DXVECTOR3(title->pos.x + sizex, title->pos.y - sizey, 0.0f);
	//	title->vertex[2].vtx = D3DXVECTOR3(title->pos.x - sizex, title->pos.y + sizey, 0.0f);
	//	title->vertex[3].vtx = D3DXVECTOR3(title->pos.x + sizex, title->pos.y + sizey, 0.0f);

	//}


	// 変更されたエフェクトのα値の設定
	// タイトル背景
	if (no == TITLE_BASE_LIGHT)
	{

		 //反射光の設定
		title->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, effectB);
		title->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, effectB);
		title->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, effectB);
		title->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, effectB);

	}

	// UIエフェクト:"ボタンをおしてね"
	 if (no == TITLE_ANY_EFFECT)
	{

		// 反射光の設定
		title->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, effect);
		title->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, effect);
		title->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, effect);
		title->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, effect);

	}

	 // UIエフェクト:"はじめる"
	 if (no == TITLE_START_EFFECT)
	 {

		 // 反射光の設定
		 title->vertex[0].diffuse = D3DCOLOR_RGBA(255, 0, 0, effect);
		 title->vertex[1].diffuse = D3DCOLOR_RGBA(0, 0, 255, effect);
		 title->vertex[2].diffuse = D3DCOLOR_RGBA(255, 0, 0, effect);
		 title->vertex[3].diffuse = D3DCOLOR_RGBA(0, 0, 255, effect);

	 }

	 // UIエフェクト:"操作説明"
	 if (no == TITLE_CREDIT_EFFECT)
	 {

		 // 反射光の設定
		 title->vertex[0].diffuse = D3DCOLOR_RGBA(255, 0, 0, effect);
		 title->vertex[1].diffuse = D3DCOLOR_RGBA(0, 0, 255, effect);
		 title->vertex[2].diffuse = D3DCOLOR_RGBA(255, 0, 0, effect);
		 title->vertex[3].diffuse = D3DCOLOR_RGBA(0, 0, 255, effect);

	 }

}

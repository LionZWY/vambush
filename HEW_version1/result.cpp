//=============================================================================
//
// タイトル画面処理 [result.cpp]
// Author : 眞戸原史也
// プログラム作成日 : 2018/3/09
//
//=============================================================================
#include "result.h"				// 構造体＆マクロ使用の為
#include "main.h"				// マクロ使用の為
#include "input.h"				// 関数使用の為
#include "game.h"				// 関数＆マクロ使用の為
#include "debugproc.h"			// 関数使用の為(デバッグ用)
#include "sound.h"				// 関数使用の為
#include "fade.h"				// 同上
#include "title.h"				// マクロ使用の為
#include "timer.h"				// 同上

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexResult(int no);					// 頂点作成関数
void SetVertexResultEffect(int no);					// エフェクト関数

//*****************************************************************************
// グローバル変数
//*****************************************************************************


RESULT resultWk[RESULT_MAX];						// タイトル構造体最大数宣言

bool resultflag;									// エフェクト用制御変数
int resulteffect;									// エフェクト用変数
int resulteffectB;									// エフェクト用変数

int resultserect;									// 画面遷移制御変数
int resultcnt;										// カーソル制御変数

float rankpos;

int bgmcnt;

bool winflag;										// 勝利フラグ

//float sizex, sizey;								// デバッグ用テクスチャ移動処理変数


//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT InitResult(int type)
{

	// ポインタの初期化
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	RESULT *result = &resultWk[0];

	// エフェクト関係の初期化
	resultflag = true;				// true:プラスする false:マイナスする
	resulteffect = INIT_EFFECT;		// エフェクトのα値の初期化

	// 勝利フラグの初期化
	winflag = true;

	// 画面制御変数の初期化
	resultserect = 0;
	resultcnt = 0;

	resulteffectB = 0;

	bgmcnt = RESULT_BGM_TIME*FRAME_CNT;

	// スクリーンサイズ
	rankpos = SCREEN_WIDTH;

	//// デバッグ用テクスチャ移動処理変数の初期化
	//sizex = RESULT_RANK_SIZE_X;
	//sizey = RESULT_RANK_SIZE_Y;

	// 構造体最大数初期化処理
	for (int i = 0; i < RESULT_MAX;i++, result++)
	{

		// 初起動時
		if (type == FIRST)
		{

			// 全てNULLで初期化
			result->Texture = NULL;

			// 背景
			if (i == RESULT_BASE)
			{
				// 位置の設定
				result->use = true;					// 使用で初期化
				result->pos = RESULT_BASE_POS;		// 背景の位置

				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					RESULT_BASE_TEXTURE,			// ファイルの名前
					&result->Texture);				// 読み込むメモリー
			}

			// 背景
			else if (i == RESULT_BASE_LIGHT)
			{
				// 位置の設定
				result->use = true;					// 使用で初期化
				result->pos = RESULT_BASE_POS;		// 背景の位置

													// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					RESULT_BASE_LIGHT_TEXTURE,			// ファイルの名前
					&result->Texture);				// 読み込むメモリー
			}



			// 勝利フラグプレイヤー
			else if (i == RESULT_BOAD_AI)
			{
				// 位置の設定
				result->use = false;					// 使用で初期化
				result->pos = RESULT_BASE_POS;		// リザルトボードの位置

				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					RESULT_BOAD_AI_TEXTURE,			// ファイルの名前
					&result->Texture);				// 読み込むメモリー
			}

			// 勝利フラグウイルス
			else if (i == RESULT_BOAD_VIRUS)
			{
				// 位置の設定
				result->use = false;					// 使用で初期化
				result->pos = RESULT_BASE_POS;		// リザルトボードの位置

				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					RESULT_BOAD_VIRUS_TEXTURE,		// ファイルの名前
					&result->Texture);				// 読み込むメモリー
			}

			// 勝利プレイヤー
			else if (i == RESULT_AI)
			{
				// 位置の設定
				result->use = false;					// 使用で初期化
				result->pos = RESULT_AI_POS;		// リザルトボードの位置

				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					RESULT_AI_TEXTURE,			// ファイルの名前
					&result->Texture);				// 読み込むメモリー
			}

			// 勝利ウイルス
			else if (i == RESULT_VIRUS)
			{
				// 位置の設定
				result->use = false;					// 使用で初期化
				result->pos = RESULT_VIRUS_POS;		// リザルトボードの位置

													// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					RESULT_VIRUS_TEXTURE,		// ファイルの名前
					&result->Texture);				// 読み込むメモリー
			}

			// 評価プレイヤー
			else if (i == RESULT_AI_RANK)
			{
				// 位置の設定
				result->use = false;						// 使用で初期化
				result->pos = RESULT_RANK_POS;			// 評価の位置

				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
					RESULT_AI_RANK_TEXTURE,				// ファイルの名前
					&result->Texture);					// 読み込むメモリー
			}

			// エフェクト:評価プレイヤー
			else if (i == RESULT_AI_RANK_EFFECT)
			{
				// 位置の設定
				result->use = false;						// 使用で初期化
				result->pos = RESULT_RANK_POS;			// エフェクト:評価の位置

				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
					RESULT_AI_RANK_TEXTURE,				// ファイルの名前
					&result->Texture);					// 読み込むメモリー
			}

			// 評価ウイルス
			else if (i == RESULT_VIRUS_RANK)
			{
				// 位置の設定
				result->use = false;						// 使用で初期化
				result->pos = RESULT_RANK_POS;			// 評価の位置

														// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
					RESULT_VIRUS_RANK_TEXTURE,				// ファイルの名前
					&result->Texture);					// 読み込むメモリー
			}

			// エフェクト:評価ウイルス
			else if (i == RESULT_VIRUS_RANK_EFFECT)
			{
				// 位置の設定
				result->use = false;						// 使用で初期化
				result->pos = RESULT_RANK_POS;			// エフェクト:評価の位置

														// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
					RESULT_VIRUS_RANK_TEXTURE,				// ファイルの名前
					&result->Texture);					// 読み込むメモリー
			}


			// 黒板メニュー
			else if (i == RESULT_BLACK_S)
			{
				// 位置の設定
				result->use = false;					// 未使用で初期化
				result->pos = RESULT_BLACK_S_POS;		// 黒板メニューの位置

				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
					RESULT_BLACK_S_TEXTURE,				// ファイルの名前
					&result->Texture);					// 読み込むメモリー
			}

			// UI:"やりなおす"
			// UIエフェクト:"やりなおす"
			else if ((i == RESULT_INIT) || (i == RESULT_INIT_EFFECT))
			{
				// 位置の設定
				result->use = false;					// 未使用で初期化
				result->pos = RESULT_INIT_POS;			// UI:"やりなおす" UIエフェクト:"やりなおす"の位置

				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
					RESULT_INIT_TEXTURE,				// ファイルの名前
					&result->Texture);					// 読み込むメモリー
			}

			// UI:"おわる"
			// UIエフェクト:"おわる"
			else if ((i == RESULT_FINISH) || (i == RESULT_FINISH_EFFECT))
			{
				// 位置の設定
				result->use = false;					// 未使用で初期化
				result->pos = RESULT_FINISH_POS;		// UI:"おわる" UIエフェクト:"おわる"の位置

				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
					RESULT_FINISH_TEXTURE,				// ファイルの名前
					&result->Texture);					// 読み込むメモリー
			}
		}

		// ゲーム更新時
		else if (type == UPDATA)
		{
			// メニューで最初表示するもの以外は未使用で初期化
			if ((i == RESULT_BASE) || (i == RESULT_BASE_LIGHT))
			{
				result->use = true;					// 未使用で初期化
			}

			else
			{
				result->use = false;							// 使用で初期化
			}
		}


		// 頂点情報の作成
		MakeVertexResult(i);
	}

	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void UninitResult(void)
{
	// ポインタの初期化
	RESULT *result = &resultWk[0];

	// 構造体最大数終了処理
	for (int i = 0; i < RESULT_MAX;i++, result++)
	{

		// テクスチャの開放出来ていなかったら
		if (result->Texture != NULL)
		{

			// テクスチャの開放
			result->Texture->Release();
			result->Texture = NULL;
		}
	}

}

//=============================================================================
// 更新処理関数
//=============================================================================
void UpdateResult(void)
{

	// ポインタの初期化
	RESULT *result = &resultWk[0];
	RESULT *resultLight = &resultWk[RESULT_BASE_LIGHT];
	RESULT *resultAi = &resultWk[RESULT_BOAD_AI];
	RESULT *resultVirus = &resultWk[RESULT_BOAD_VIRUS];


	// 背景処理
	if (winflag == true)
	{
		resultAi->use = true;
	}
	else if (winflag == false)
	{
		resultVirus->use = true;
	}


	// エフェクトα値が最大
	if (resulteffectB >= ALPHA_MAX)
	{
		// フラグをマイナスに
		resulteffectB = ALPHA_MAX;
		resultLight->use = false;
		if (winflag == true)
		{

			for (int i = RESULT_BOAD_AI;i <= RESULT_AI_RANK_EFFECT;i++, resultAi++)
			{
				resultAi->use = true;
			}
		}

		else if (winflag == false)
		{
			for (int i = RESULT_BOAD_VIRUS;i <= RESULT_VIRUS_RANK_EFFECT;i++, resultVirus++)
			{
				resultVirus->use = true;
			}

		}

	}

	else if (resulteffectB < ALPHA_MAX)
	{
		// エフェクトα値にEFFECT_SPEEDを足す
		resulteffectB += RESULT_SPEED;

	}


	// エフェクト処理
	if (resultflag == true)
	{
		// エフェクトα値にEFFECT_SPEEDを足す
		resulteffect += RESULT_EFFECT_SPEED;

		// エフェクトα値が最大
		if (resulteffect == ALPHA_MAX)
		{
			// フラグをマイナスに
			resultflag = false;
		}
	}

	// マイナスフラグ
	else if (resultflag == false)
	{
		// エフェクトα値にEFFECT_SPEEDを引く
		resulteffect -= RESULT_EFFECT_SPEED;

		// エフェクトα値が最小
		if (resulteffect == ALPHA_BASE)
		{
			// フラグをプラスに
			resultflag = true;
		}

	}

	// アニメーション
	// 構造体最大数更新処理
	for (int i = 0; i < RESULT_MAX;i++, result++)
	{

		if ((i == RESULT_AI_RANK) || (i == RESULT_VIRUS_RANK))
		{
			if (result->use == true)
			{
				rankpos -= RESULT_RANK_SPEED;

				if (rankpos < SCREEN_WIDTH / 2)
				{
					rankpos = SCREEN_WIDTH / 2;
				}
			}
		}

		// //デバッグ用移動拡大処理
		//if (i == RESULT_VIRUS)
		//		{
		//
		//			// 左
		//			if (GetKeyboardPress(DIK_V))
		//			{
		//				result->pos.x--;
		//			}
		//			// 右
		//			else if (GetKeyboardPress(DIK_B))
		//			{
		//				result->pos.x++;
		//			}
		//
		//			// 上
		//			if (GetKeyboardPress(DIK_N))
		//			{
		//				result->pos.y--;
		//
		//			}
		//			// 下
		//			else if (GetKeyboardPress(DIK_M))
		//			{
		//				result->pos.y++;
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
		//			PrintDebugProc("座標:X %f)\n", result->pos.x);
		//			PrintDebugProc("座標:Y %f)\n", result->pos.y);
		//#endif
		//		}


		// エフェクト処理
		SetVertexResultEffect(i);

	}


	bgmcnt--;
	if (bgmcnt == 0)
	{
		StopSound(BGM_CALL_RESULT);							// 通常戦闘BGMの停止
		PlaySound(BGM_RESULT, E_DS8_FLAG_LOOP);		// リザルトBGMの再生

	}

	// リザルト遷移処理
	// 初回
	if (resultserect == FIRST)
	{

		// Enter押したら、ステージを切り替える
		if ((GetKeyboardTrigger(DIK_A)) || (IsButtonTriggered(0, BUTTON_START)))
		{

			// カーソル決定SEの再生
			PlaySound(SE_PUSH, E_DS8_FLAG_NONE);

			// ポインタの初期化
			RESULT *result = &resultWk[RESULT_BLACK_S];

			// リザルトカーソル部分の更新処理
			for (int i = RESULT_BLACK_S;i < RESULT_MAX;i++, result++)
			{
				// 最初に表示しないものを未使用
				if (i == RESULT_FINISH_EFFECT)
				{
					result->use = false;
				}

				// 最初に表示するものを使用
				else
				{
					result->use = true;
				}
			}

			// セレクトUIの表示
			resultserect = UPDATA;
		}
	}

	// セレクトUIの表示中
	else if (resultserect == UPDATA)
	{

		// 使用する構造体のポインタの初期化
		RESULT *resultS = &resultWk[RESULT_INIT_EFFECT];
		RESULT *results = &resultWk[RESULT_INIT];
		RESULT *resultC = &resultWk[RESULT_FINISH_EFFECT];
		RESULT *resultc = &resultWk[RESULT_FINISH];

		// セレクトメニューの表示中
		switch (resultcnt)
		{

			// UI:"やりなおす"の処理
		case RESULT_UI_INIT:
		{

			// UIエフェクト:"やりなおす"の処理
			resultS->use = true;

			// UIエフェクト:"おわる"を未使用に
			resultC->use = false;

			// UI:"やりなおす"の色を黄色に
			results->vertex[0].diffuse = D3DCOLOR_RGBA(255, 0, 0, 255);
			results->vertex[1].diffuse = D3DCOLOR_RGBA(0, 0, 255, 255);
			results->vertex[2].diffuse = D3DCOLOR_RGBA(0, 0, 255, 255);
			results->vertex[3].diffuse = D3DCOLOR_RGBA(0, 0, 255, 255);

			// UI:"おわる"の色を元に戻す
			resultc->vertex[0].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
			resultc->vertex[1].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
			resultc->vertex[2].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
			resultc->vertex[3].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);

			// Enterまたは×ボタンを押したら、ゲームを初期化
			if ((GetKeyboardTrigger(DIK_RETURN)) || (IsButtonTriggered(0, BUTTON_C)))
			{

				// カーソル決定SEの再生
				PlaySound(SE_PUSH, E_DS8_FLAG_NONE);

				InitGame(UPDATA);				// ゲームの再初期化処理
				SetStage(STAGE_TITLE);			// ステージ変数の初期化
				SetFade(FADE_OUT);				// 画面遷移:ゲーム
			}

			// ×ボタンを押したら黒板リザルトを非表示
			if (IsButtonTriggered(0, BUTTON_B))
			{

				// カーソル決定SEの再生
				PlaySound(SE_PUSH, E_DS8_FLAG_NONE);

				// ポインタの初期化
				RESULT *result = &resultWk[RESULT_BLACK_S];

				// 黒板リザルト以下を全て非表示に
				for (int i = RESULT_BLACK_S;i < RESULT_MAX;i++, result++)
				{
					result->use = false;			// 日表示

				}

				// 初回に戻す
				resultserect = FIRST;
			}

			// Wまたは↑スティックを押したら、カーソル移動
			else if ((GetKeyboardTrigger(DIK_W)) || (IsButtonTriggered(0, BUTTON_UP)))
			{

				// カーソル選択SEの再生
				PlaySound(SE_SERECT, E_DS8_FLAG_NONE);

				// カーソルを上に移動
				resultcnt--;
			}

			// Sまたは↓スティックを押したら、カーソル移動
			else if ((GetKeyboardTrigger(DIK_S)) || (IsButtonTriggered(0, BUTTON_DOWN)))
			{

				// カーソル選択SEの再生
				PlaySound(SE_SERECT, E_DS8_FLAG_NONE);

				// カーソルを下に移動
				resultcnt++;
			}

			break;
		}

		// UI:"おわる"の処理
		case RESULT_UI_FINISH:
		{

			// UIエフェクト:"おわる"を使用に
			resultC->use = true;

			// UIエフェクト:"やりなおす"を未使用に
			resultS->use = false;

			// UIエフェクト:"おわる"の色を黄色に
			resultc->vertex[0].diffuse = D3DCOLOR_RGBA(255, 0, 0, 255);
			resultc->vertex[1].diffuse = D3DCOLOR_RGBA(0, 0, 255, 255);
			resultc->vertex[2].diffuse = D3DCOLOR_RGBA(0, 0, 255, 255);
			resultc->vertex[3].diffuse = D3DCOLOR_RGBA(0, 0, 255, 255);

			// UIエフェクト:"やりなおす"の色を元に戻す
			results->vertex[0].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
			results->vertex[1].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
			results->vertex[2].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
			results->vertex[3].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);


			// Enterまたは〇ボタンを押したら、ステージを切り替える
			if ((GetKeyboardTrigger(DIK_RETURN)) || (IsButtonTriggered(0, BUTTON_C)))
			{

				// カーソル決定SEの再生
				PlaySound(SE_PUSH, E_DS8_FLAG_NONE);

				InitGame(UPDATA);				// ゲームの再初期化処理
				SetFade(FADE_OUT);				// 画面遷移:タイトル

			}


				// ×ボタンを押したら黒板リザルトを非表示
				if (IsButtonTriggered(0, BUTTON_B))
				{

					// カーソル決定SEの再生
					PlaySound(SE_PUSH, E_DS8_FLAG_NONE);

					// ポインタの初期化
					RESULT *result = &resultWk[RESULT_BLACK_S];

					// 黒板リザルト以下を全て非表示に
					for (int i = RESULT_BLACK_S;i < RESULT_MAX;i++, result++)
					{
						result->use = false;			// 日表示

					}

					// 初回に戻す
					resultserect = FIRST;
				}


				// Wまたは↑スティックを押したら、カーソル移動
				else if ((GetKeyboardTrigger(DIK_W)) || (IsButtonTriggered(0, BUTTON_UP)))
				{

					// カーソル選択SEの再生
					PlaySound(SE_SERECT, E_DS8_FLAG_NONE);

					// カーソルを上に移動
					resultcnt--;
				}

				// Sまたは↓スティックを押したら、カーソル移動
				else if ((GetKeyboardTrigger(DIK_S)) || (IsButtonTriggered(0, BUTTON_DOWN)))
				{


					// カーソル選択SEの再生
					PlaySound(SE_SERECT, E_DS8_FLAG_NONE);

					// カーソルを下に移動
					resultcnt++;
				}

				break;

		}

		}
	}

	// カーソルループ移動処理
	// UI:"やりなおす"で↑入力時
	if (resultcnt < RESULT_UI_INIT)
	{
		// UI:"おわる"に移動
		resultcnt = RESULT_UI_MAX - 1;
	}

	// UI:"おわる"で↓入力時
	if (resultcnt > RESULT_UI_MAX - 1)
	{
		// UI:"やりなおす"に移動
		resultcnt = RESULT_UI_INIT;
	}

}
//=============================================================================
// 描画処理関数
//=============================================================================
void DrawResult(void)
{
	// ポインタの初期化
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	RESULT *result = &resultWk[0];

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	 // 構造体最大数終了処理
	for (int i = 0; i < RESULT_MAX;i++, result++)
	{
		if (result->use == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, result->Texture);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, result->vertex, sizeof(VERTEX_2D));
		}
	}

//#ifdef _DEBUG
//	// デバッグメッセージ表示
//	DrawDebugProc();
//#endif

}

//=============================================================================
// 頂点の作成関数
//=============================================================================
HRESULT MakeVertexResult(int no)
{

	// ポインタの初期化
	RESULT *result = &resultWk[no];

	// 背景
	if ((no == RESULT_BASE)||(no == RESULT_BASE_LIGHT))
	{
		// 頂点座標の設定
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_BASE_SIZE_X, result->pos.y - RESULT_BASE_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_BASE_SIZE_X, result->pos.y - RESULT_BASE_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_BASE_SIZE_X, result->pos.y + RESULT_BASE_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_BASE_SIZE_X, result->pos.y + RESULT_BASE_SIZE_Y, 0.0f);

		// 反射光の設定
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// 勝利フラグプレイヤー
	if (no == RESULT_BOAD_AI)
	{
		// 頂点座標の設定
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_BASE_SIZE_X, result->pos.y - RESULT_BASE_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_BASE_SIZE_X, result->pos.y - RESULT_BASE_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_BASE_SIZE_X, result->pos.y + RESULT_BASE_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_BASE_SIZE_X, result->pos.y + RESULT_BASE_SIZE_Y, 0.0f);

		// 反射光の設定
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// 背景
	if (no == RESULT_BOAD_VIRUS
		)
	{
		// 頂点座標の設定
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_BASE_SIZE_X, result->pos.y - RESULT_BASE_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_BASE_SIZE_X, result->pos.y - RESULT_BASE_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_BASE_SIZE_X, result->pos.y + RESULT_BASE_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_BASE_SIZE_X, result->pos.y + RESULT_BASE_SIZE_Y, 0.0f);

		// 反射光の設定
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// 背景
	if (no == RESULT_AI)
	{
		// 頂点座標の設定
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_AI_SIZE_X, result->pos.y - RESULT_AI_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_AI_SIZE_X, result->pos.y - RESULT_AI_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_AI_SIZE_X, result->pos.y + RESULT_AI_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_AI_SIZE_X, result->pos.y + RESULT_AI_SIZE_Y, 0.0f);

		// 反射光の設定
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 120);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 120);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 120);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 120);

	}



	// 背景
	if (no == RESULT_VIRUS)
	{
		// 頂点座標の設定
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_VIRUS_SIZE_X, result->pos.y - RESULT_VIRUS_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_VIRUS_SIZE_X, result->pos.y - RESULT_VIRUS_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_VIRUS_SIZE_X, result->pos.y + RESULT_VIRUS_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_VIRUS_SIZE_X, result->pos.y + RESULT_VIRUS_SIZE_Y, 0.0f);

		// 反射光の設定
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 120);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 120);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 120);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 120);

	}

	// 評価
	else if ((no == RESULT_AI_RANK)||(no == RESULT_VIRUS_RANK))
	{
		// 頂点座標の設定
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_RANK_SIZE_X, result->pos.y - RESULT_RANK_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_RANK_SIZE_X, result->pos.y - RESULT_RANK_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_RANK_SIZE_X, result->pos.y + RESULT_RANK_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_RANK_SIZE_X, result->pos.y + RESULT_RANK_SIZE_Y, 0.0f);

		// 反射光の設定
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 0, 0, 255);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(0, 0, 255, 255);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(0, 0, 255, 255);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(0, 0, 255, 255);

	}

	// エフェクト:評価
	else if ((no == RESULT_AI_RANK_EFFECT)||(no == RESULT_VIRUS_RANK_EFFECT))
	{
		// 頂点座標の設定
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_RANK_EFFECT_SIZE_X, result->pos.y - RESULT_RANK_EFFECT_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_RANK_EFFECT_SIZE_X, result->pos.y - RESULT_RANK_EFFECT_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_RANK_EFFECT_SIZE_X, result->pos.y + RESULT_RANK_EFFECT_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_RANK_EFFECT_SIZE_X, result->pos.y + RESULT_RANK_EFFECT_SIZE_Y, 0.0f);

		// 反射光の設定
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 175, 0, 255);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 175, 0, 255);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 175, 0, 255);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 175, 0, 255);

	}

	// 黒板メニュー
	else if (no == RESULT_BLACK_S)
	{
		// 頂点座標の設定
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_BLACK_S_SIZE_X, result->pos.y - RESULT_BLACK_S_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_BLACK_S_SIZE_X, result->pos.y - RESULT_BLACK_S_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_BLACK_S_SIZE_X, result->pos.y + RESULT_BLACK_S_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_BLACK_S_SIZE_X, result->pos.y + RESULT_BLACK_S_SIZE_Y, 0.0f);

		// 反射光の設定
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}


	// UI:"やりなおす"
	else if (no == RESULT_INIT)
	{
		// 頂点座標の設定
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_INIT_SIZE_X, result->pos.y - RESULT_INIT_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_INIT_SIZE_X, result->pos.y - RESULT_INIT_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_INIT_SIZE_X, result->pos.y + RESULT_INIT_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_INIT_SIZE_X, result->pos.y + RESULT_INIT_SIZE_Y, 0.0f);

		// 反射光の設定
		result->vertex[0].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);

	}


	// UIエフェクト:"やりなおす"
	else if (no == RESULT_INIT_EFFECT)
	{
		// 頂点座標の設定
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_ANY_EFFECT_SIZE_X, result->pos.y - RESULT_ANY_EFFECT_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_ANY_EFFECT_SIZE_X, result->pos.y - RESULT_ANY_EFFECT_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_ANY_EFFECT_SIZE_X, result->pos.y + RESULT_ANY_EFFECT_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_ANY_EFFECT_SIZE_X, result->pos.y + RESULT_ANY_EFFECT_SIZE_Y, 0.0f);

		// 反射光の設定
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// UI:"おわる"
	else if (no == RESULT_FINISH)
	{
		// 頂点座標の設定
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_FINISH_SIZE_X, result->pos.y - RESULT_FINISH_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_FINISH_SIZE_X, result->pos.y - RESULT_FINISH_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_FINISH_SIZE_X, result->pos.y + RESULT_FINISH_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_FINISH_SIZE_X, result->pos.y + RESULT_FINISH_SIZE_Y, 0.0f);

		// 反射光の設定
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// UIエフェクト:"おわる"
	else if (no == RESULT_FINISH_EFFECT)
	{
		// 頂点座標の設定
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_FINISH_EFFECT_SIZE_X, result->pos.y - RESULT_FINISH_EFFECT_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_FINISH_EFFECT_SIZE_X, result->pos.y - RESULT_FINISH_EFFECT_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_FINISH_EFFECT_SIZE_X, result->pos.y + RESULT_FINISH_EFFECT_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_FINISH_EFFECT_SIZE_X, result->pos.y + RESULT_FINISH_EFFECT_SIZE_Y, 0.0f);

		// 反射光の設定
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}


	// テクスチャのパースペクティブコレクト用
	result->vertex[0].rhw =
	result->vertex[1].rhw =
	result->vertex[2].rhw =
	result->vertex[3].rhw = 1.0f;


	// テクスチャ座標の設定
	result->vertex[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	result->vertex[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	result->vertex[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	result->vertex[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}
//=============================================================================
// エフェクト関数
//=============================================================================
void SetVertexResultEffect(int no)
{

	// ポインタの初期化
	RESULT *result = &resultWk[no];


	//// デバッグ用テクスチャ更新
	//// ボタンをおしてね:エフェクト
	//if (no == RESULT_VIRUS)
	//{

	//	// 頂点座標の設定
	//	result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - sizex, result->pos.y - sizey, 0.0f);
	//	result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + sizex, result->pos.y - sizey, 0.0f);
	//	result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - sizex, result->pos.y + sizey, 0.0f);
	//	result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + sizex, result->pos.y + sizey, 0.0f);

	//}

	// エフェクト:評価
	if ((no == RESULT_BASE_LIGHT) || (no == RESULT_BOAD_AI) || (no == RESULT_BOAD_VIRUS))
	{

		// 反射光の設定
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, resulteffectB);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, resulteffectB);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, resulteffectB);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, resulteffectB);

	}

	// エフェクト:評価
	if ((no == RESULT_AI_RANK)||(no == RESULT_VIRUS_RANK))
	{

		result->pos.x = rankpos;

		// 頂点座標の設定
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_RANK_SIZE_X, result->pos.y - RESULT_RANK_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_RANK_SIZE_X, result->pos.y - RESULT_RANK_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_RANK_SIZE_X, result->pos.y + RESULT_RANK_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_RANK_SIZE_X, result->pos.y + RESULT_RANK_SIZE_Y, 0.0f);

	}

	// エフェクト:評価
	if ((no == RESULT_AI_RANK_EFFECT)||(no == RESULT_VIRUS_RANK_EFFECT))
	{
		result->pos.x = rankpos;

		// 頂点座標の設定
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_RANK_EFFECT_SIZE_X, result->pos.y - RESULT_RANK_EFFECT_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_RANK_EFFECT_SIZE_X, result->pos.y - RESULT_RANK_EFFECT_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_RANK_EFFECT_SIZE_X, result->pos.y + RESULT_RANK_EFFECT_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_RANK_EFFECT_SIZE_X, result->pos.y + RESULT_RANK_EFFECT_SIZE_Y, 0.0f);


		// 反射光の設定
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 0, 0, resulteffect);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(0, 0, 255, resulteffect);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 0, 0, resulteffect);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(0, 0, 255, resulteffect);


	}

	// UIエフェクト:"やりなおす"
	 if (no == RESULT_INIT_EFFECT)
	{

		// 反射光の設定
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 0, 0, resulteffect);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(0, 0, 255, resulteffect);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 0, 0, resulteffect);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(0, 0, 255, resulteffect);

	}

	// UIエフェクト:"おわる"
	else if (no == RESULT_FINISH_EFFECT)
	{

		// 反射光の設定
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 0, 0, resulteffect);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(0, 0, 255, resulteffect);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 0, 0, resulteffect);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(0, 0, 255, resulteffect);

	}

}


//=============================================================================
// x勝利フラグ取得関数
//=============================================================================
bool *GetWinFlag(void)
{
	return (&winflag);
}
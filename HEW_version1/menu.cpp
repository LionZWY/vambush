//=============================================================================
//
// ポーズメニュー処理 [menu.cpp]
// Author : 眞戸原史也
// プログラム作成日 : 2018/3/09
//
//=============================================================================

#include "menu.h"						// 構造体＆マクロ使用の為
#include "main.h"						// マクロ使用の為
#include "input.h"						// 関数使用の為
#include "game.h"						// 関数＆マクロ使用の為
#include "debugproc.h"					// 関数使用の為(デバッグ用)
#include "sound.h"						// 関数使用の為
#include "fade.h"						// 関数＆マクロ使用の為
#include "title.h"						// マクロ使用の為

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexMenu(int no);			// 頂点作成関数
void SetVertexMenuEffect(int no);		// エフェクト関数

//*****************************************************************************
// グローバル変数
//*****************************************************************************

MENU menuWk[MENU_MAX];					// メニュー構造体最大数宣言

bool menueffectflag;					// エフェクト用制御変数
int menueffect;							// エフェクト用変数
int menucnt;							// 画面制御変数

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT InitMenu(int type)
{

	// ポインタの初期化
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MENU *menu = &menuWk[0];

	// エフェクト関係の初期化
	menueffectflag = true;				// true:プラスする false:マイナスする
	menueffect= INIT_EFFECT;			// エフェクトのα値の初期化

	// 画面制御変数の初期化
	menucnt = 0;

	// 構造体最大数初期化処理
	for(int i = 0; i < MENU_MAX;i++, menu++)
	{

		// 初起動時
		if (type == FIRST)
		{

			// 全てNULLで初期化
			menu->Texture = NULL;

			// メニュー暗転
			if (i == MENU_BASE)
			{
				// 位置の設定
				menu->use = true;					// true:使用 false:未使用 使用で初期化
				menu->pos = MENU_BASE_POS;			// メニュー暗転の位置の初期化

			}

			// 黒板メニュー
			else if (i == MENU_BLACK)
			{
				// 位置の設定
				menu->use = true;					// true:使用 false:未使用 使用で初期化
				menu->pos = MENU_BLACK_POS;			// 黒板メニューの位置の初期化


				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					MENU_BLACK_TEXTURE,				// ファイルの名前
					&menu->Texture);				// 読み込むメモリー

			}

			// UI:"つづける"
			else if (i == MENU_ANY)
			{
				// 位置の設定
				menu->use = true;					// true:使用 false:未使用 使用で初期化
				menu->pos = MENU_ANY_POS;			// UI:"つづける",UIエフェクト:"つづける"の位置の初期化

				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					MENU_ANY_TEXTURE,				// ファイルの名前
					&menu->Texture);				// 読み込むメモリー
			}

			// UI:"つづける"
			else if (i == MENU_ANY_EFFECT)
			{
				// 位置の設定
				menu->use = true;					// true:使用 false:未使用 使用で初期化
				menu->pos = MENU_ANY_POS;			// UI:"つづける",UIエフェクト:"つづける"の位置の初期化

													// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					MENU_ANY_TEXTURE,				// ファイルの名前
					&menu->Texture);				// 読み込むメモリー
			}

			// UI:"やりなおす"
			// UIエフェクト:"やりなおす"
			else if (i == MENU_INIT)
			{
				// 位置の設定
				menu->use = true;					// true:使用 false:未使用 使用で初期化
				menu->pos = MENU_INIT_POS;			// UI:"やりなおす"の位置の初期化

				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					MENU_INIT_TEXTURE,				// ファイルの名前
					&menu->Texture);				// 読み込むメモリー
			}

			// UIエフェクト:"やりなおす"
			else if (i == MENU_INIT_EFFECT)
			{
				// 位置の設定
				menu->use = false;					// true:使用 false:未使用 使用で初期化
				menu->pos = MENU_INIT_POS;			// UI:"やりなおす"の位置の初期化

				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					MENU_INIT_TEXTURE,				// ファイルの名前
					&menu->Texture);				// 読み込むメモリー
			}


			// UI:"おわる"
			else if (i == MENU_FINISH) 
			{
				// 位置の設定
				menu->use = true;					// true:使用 false:未使用 使用で初期化
				menu->pos = MENU_FINISH_POS;		// メニュー暗転の位置の初期化

				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					MENU_FINISH_TEXTURE,			// ファイルの名前
					&menu->Texture);				// 読み込むメモリー
			}

			// UIエフェクト:"おわる"
			else if (i == MENU_FINISH_EFFECT)
			{
				// 位置の設定
				menu->use = false;					// true:使用 false:未使用 使用で初期化
				menu->pos = MENU_FINISH_POS;		// メニュー暗転の位置の初期化

				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					MENU_FINISH_TEXTURE,			// ファイルの名前
					&menu->Texture);				// 読み込むメモリー
			}

		}

		// 頂点情報の作成
		MakeVertexMenu(i);
	}

	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void UninitMenu(void)
{
	// ポインタの初期化
	MENU *menu = &menuWk[0];

	// 構造体最大数終了処理
	for (int i = 0; i < MENU_MAX;i++, menu++)
	{

		// テクスチャの開放出来ていなかったら
		if (menu->Texture != NULL)
		{

			// テクスチャの開放
			menu->Texture->Release();
			menu->Texture = NULL;
		}
	}

}

//=============================================================================
// 更新処理関数
//=============================================================================
void UpdateMenu(void)
{

	// ポインタの初期化
	MENU *menu = &menuWk[0];

	// 現在のメニューフラグを確認
	bool *flag = GetMenu();

	// エフェクト処理
	// プラスフラグ
	if (menueffectflag==true)
	{

		// エフェクトα値にEFFECT_MENU_SPEEDを足す
		menueffect += EFFECT_MENU_SPEED;

		// エフェクトα値が最大
		if (menueffect == ALPHA_MAX)
		{
			// フラグをマイナスに
			menueffectflag = false;
		}
	}

	// マイナスフラグ
	else if (menueffectflag == false)
	{
		// エフェクトα値にEFFECT_MENU_SPEEDを引く
		menueffect-= EFFECT_MENU_SPEED;

		// エフェクトα値が最小
		if (menueffect == ALPHA_BASE)
		{
			// フラグをプラスにに
			menueffectflag = true;
		}

	}


	// 構造体最大数更新処理
	for (int i = 0; i < MENU_MAX;i++, menu++)
	{

		// エフェクト処理
		SetVertexMenuEffect(i);

	}

	MENU *menuAny = &menuWk[MENU_ANY];
	MENU *menuAnyef = &menuWk[MENU_ANY_EFFECT];
	MENU *menuInit = &menuWk[MENU_INIT];
	MENU *menuInitef = &menuWk[MENU_INIT_EFFECT];
	MENU *menuFin = &menuWk[MENU_FINISH];
	MENU *menuFinef = &menuWk[MENU_FINISH_EFFECT];


	// セレクトメニューの表示中
	switch (menucnt)
	{
	// UI:"つづける"の処理
	case MENU_UI_ANY:
	{
		// UI:"つづける"を使用に
		menuAnyef->use = true;

		// UI:"やりなおす"を未使用に
		menuInitef->use = false;

		// UI:"おわる"を未使用に
		menuFinef->use = false;

		// UI:"つづける"の色を黄色に
		menuAny->vertex[0].diffuse = D3DCOLOR_RGBA(255, 0, 0, 255);
		menuAny->vertex[1].diffuse = D3DCOLOR_RGBA(0, 0, 255, 255);
		menuAny->vertex[2].diffuse = D3DCOLOR_RGBA(0, 0, 255, 255);
		menuAny->vertex[3].diffuse = D3DCOLOR_RGBA(0, 0, 255, 255);

		// UI:"やりなおす"の色を元に戻す
		menuInit->vertex[0].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		menuInit->vertex[1].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		menuInit->vertex[2].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		menuInit->vertex[3].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);

		// UI:"おわる"の色を元に戻す
		menuFin->vertex[0].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		menuFin->vertex[1].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		menuFin->vertex[2].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		menuFin->vertex[3].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);


		// Enterまたは×ボタンを押したら、メニューを閉じる
		if ((GetKeyboardTrigger(DIK_RETURN)) || (IsButtonTriggered(0, BUTTON_C)))
		{

			// カーソル決定SEの再生
			PlaySound(SE_PUSH, E_DS8_FLAG_NONE);

			// メニューを閉じる
			*flag = false;
		}

		// Wまたは↑スティックを押したら、カーソル移動
		else if ((GetKeyboardTrigger(DIK_W)) || (IsButtonTriggered(0, BUTTON_UP)))
		{

			// カーソル選択SEの再生
			PlaySound(SE_SERECT, E_DS8_FLAG_NONE);

			// カーソルを上に移動
			menucnt--;
		}

		// Sまたは↓スティックを押したら、カーソル移動
		else if ((GetKeyboardTrigger(DIK_S)) || (IsButtonTriggered(0, BUTTON_DOWN)))
		{

			// カーソル選択SEの再生
			PlaySound(SE_SERECT, E_DS8_FLAG_NONE);

			// カーソルを下に移動
			menucnt++;
		}

		break;
	}

	// UI:"やりなおす"の処理
	case MENU_UI_INIT:
	{
		// UI:"やりなおす"を使用に
		menuInitef->use = true;

		// UI:"つづけるを未使用に
		menuAnyef->use = false;

		// UI:"おわる"を未使用に
		menuFinef->use = false;

		// UI:"やりなおす"の色を黄色に
		menuInit->vertex[0].diffuse = D3DCOLOR_RGBA(255, 0, 0, 255);
		menuInit->vertex[1].diffuse = D3DCOLOR_RGBA(0, 0, 255, 255);
		menuInit->vertex[2].diffuse = D3DCOLOR_RGBA(0, 0, 255, 255);
		menuInit->vertex[3].diffuse = D3DCOLOR_RGBA(0, 0, 255, 255);

		// UI:"つづける"の色を元に戻す
		menuAny->vertex[0].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		menuAny->vertex[1].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		menuAny->vertex[2].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		menuAny->vertex[3].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);

		// UI:"おわる"の色を元に戻す
		menuFin->vertex[0].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		menuFin->vertex[1].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		menuFin->vertex[2].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		menuFin->vertex[3].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);

		// Enterまたは×ボタンを押したら、ゲームを初期化
		if ((GetKeyboardTrigger(DIK_RETURN)) || (IsButtonTriggered(0, BUTTON_C)))
		{

			// カーソル決定SEの再生
			PlaySound(SE_PUSH, E_DS8_FLAG_NONE);

			InitGame(UPDATA);				// ゲームの再初期化処理
			SetStage(STAGE_TITLE);			// ステージ変数の初期化
			SetFade(FADE_OUT);				// 画面遷移:ゲーム
		}

		// Wまたは↑スティックを押したら、カーソル移動
		else if ((GetKeyboardTrigger(DIK_W)) || (IsButtonTriggered(0, BUTTON_UP)))
		{

			// カーソル選択SEの再生
			PlaySound(SE_SERECT, E_DS8_FLAG_NONE);

			// カーソルを上に移動
			menucnt--;
		}

		// Sまたは↓スティックを押したら、カーソル移動
		else if ((GetKeyboardTrigger(DIK_S)) || (IsButtonTriggered(0, BUTTON_DOWN)))
		{

			// カーソル選択SEの再生
			PlaySound(SE_SERECT, E_DS8_FLAG_NONE);

			// カーソルを下に移動
			menucnt++;
		}

		break;
	}

	// UI:"おわる"の処理
	case MENU_UI_FINISH:
	{

		// UI:"おわる"を使用に
		menuFinef->use = true;

		// UI:"やりなおす"を未使用に
		menuInitef->use = false;

		// UI:"つづける"を未使用に
		menuAnyef->use = false;


		// UI:"おわる"の色を黄色に
		menuFin->vertex[0].diffuse = D3DCOLOR_RGBA(255, 0, 0, 255);
		menuFin->vertex[1].diffuse = D3DCOLOR_RGBA(0, 0, 255, 255);
		menuFin->vertex[2].diffuse = D3DCOLOR_RGBA(0, 0, 255, 255);
		menuFin->vertex[3].diffuse = D3DCOLOR_RGBA(0, 0, 255, 255);

		// UI:"やりなおす"の色を元に戻す
		menuInit->vertex[0].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		menuInit->vertex[1].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		menuInit->vertex[2].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		menuInit->vertex[3].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);

		// UI:"つづける"の色を元に戻す
		menuAny->vertex[0].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		menuAny->vertex[1].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		menuAny->vertex[2].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		menuAny->vertex[3].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);

		// Enter押したら、ステージを切り替える
		if ((GetKeyboardTrigger(DIK_RETURN)) || (IsButtonTriggered(0, BUTTON_C)))
		{
			// カーソル決定SEの再生
			PlaySound(SE_PUSH, E_DS8_FLAG_NONE);
			InitGame(UPDATA);				// ゲームの再初期化処理
			SetStage(STAGE_RESULT);			// ステージ変数のリザルトの前にセット
			SetFade(FADE_OUT);					// 画面遷移:リザルト

		}

		// Wまたは↑スティックを押したら、カーソル移動
		else if ((GetKeyboardTrigger(DIK_W)) || (IsButtonTriggered(0, BUTTON_UP)))
		{

			// カーソル選択SEの再生
			PlaySound(SE_SERECT, E_DS8_FLAG_NONE);

			// カーソルを上に移動
			menucnt--;
		}

		// Sまたは↓スティックを押したら、カーソル移動
		else if ((GetKeyboardTrigger(DIK_S)) || (IsButtonTriggered(0, BUTTON_DOWN)))
		{

			// カーソル選択SEの再生
			PlaySound(SE_SERECT, E_DS8_FLAG_NONE);

			// カーソルを下に移動
			menucnt++;
		}

		break;
	}
	}

	// カーソルループ移動処理
	// UI:"つづける"で↑入力時
	if (menucnt < MENU_UI_ANY)
	{
		// UI:"おわる"に移動
		menucnt = MENU_UI_MAX - 1;
	}

	// UI:"おわる"で↓入力時
	if (menucnt > MENU_UI_MAX - 1)
	{
		// UI:"つづける""に移動
		menucnt = MENU_UI_ANY;
	}

}

//=============================================================================
// 描画処理関数
//=============================================================================
void DrawMenu(void)
{
	// ポインタの初期化
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MENU *menu = &menuWk[0];
	
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);


	// 構造体最大数終了処理
	for (int i = 0; i < MENU_MAX;i++, menu++)
	{

		// 使用状態なら描画する
		if (menu->use == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, menu->Texture);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, menu->vertex, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成関数
//=============================================================================
HRESULT MakeVertexMenu(int no)
{
	
	// ポインタの初期化
	MENU *menu = &menuWk[no];

	// メニュー暗転
	if (no==MENU_BASE)
	{
		// 頂点座標の設定
		menu->vertex[0].vtx = D3DXVECTOR3(menu->pos.x - MENU_BASE_SIZE_X, menu->pos.y - MENU_BASE_SIZE_Y, 0.0f);
		menu->vertex[1].vtx = D3DXVECTOR3(menu->pos.x + MENU_BASE_SIZE_X, menu->pos.y - MENU_BASE_SIZE_Y, 0.0f);
		menu->vertex[2].vtx = D3DXVECTOR3(menu->pos.x - MENU_BASE_SIZE_X, menu->pos.y + MENU_BASE_SIZE_Y, 0.0f);
		menu->vertex[3].vtx = D3DXVECTOR3(menu->pos.x + MENU_BASE_SIZE_X, menu->pos.y + MENU_BASE_SIZE_Y, 0.0f);

		// 反射光の設定
		menu->vertex[0].diffuse = D3DCOLOR_RGBA(0, 0, 0, 150);
		menu->vertex[1].diffuse = D3DCOLOR_RGBA(0, 0, 0, 150);
		menu->vertex[2].diffuse = D3DCOLOR_RGBA(0, 0, 0, 150);
		menu->vertex[3].diffuse = D3DCOLOR_RGBA(0, 0, 0, 150);

	}

	// 黒板メニュー
	if (no == MENU_BLACK)
	{
		// 頂点座標の設定
		menu->vertex[0].vtx = D3DXVECTOR3(menu->pos.x - MENU_BLACK_SIZE_X, menu->pos.y - MENU_BLACK_SIZE_Y, 0.0f);
		menu->vertex[1].vtx = D3DXVECTOR3(menu->pos.x + MENU_BLACK_SIZE_X, menu->pos.y - MENU_BLACK_SIZE_Y, 0.0f);
		menu->vertex[2].vtx = D3DXVECTOR3(menu->pos.x - MENU_BLACK_SIZE_X, menu->pos.y + MENU_BLACK_SIZE_Y, 0.0f);
		menu->vertex[3].vtx = D3DXVECTOR3(menu->pos.x + MENU_BLACK_SIZE_X, menu->pos.y + MENU_BLACK_SIZE_Y, 0.0f);

		// 反射光の設定
		menu->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		menu->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		menu->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		menu->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}


	// UI:"つづける"
	else if (no == MENU_ANY)
	{
		// 頂点座標の設定
		menu->vertex[0].vtx = D3DXVECTOR3(menu->pos.x - MENU_ANY_SIZE_X, menu->pos.y - MENU_ANY_SIZE_Y, 0.0f);
		menu->vertex[1].vtx = D3DXVECTOR3(menu->pos.x + MENU_ANY_SIZE_X, menu->pos.y - MENU_ANY_SIZE_Y, 0.0f);
		menu->vertex[2].vtx = D3DXVECTOR3(menu->pos.x - MENU_ANY_SIZE_X, menu->pos.y + MENU_ANY_SIZE_Y, 0.0f);
		menu->vertex[3].vtx = D3DXVECTOR3(menu->pos.x + MENU_ANY_SIZE_X, menu->pos.y + MENU_ANY_SIZE_Y, 0.0f);

		// 反射光の設定
		menu->vertex[0].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		menu->vertex[1].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		menu->vertex[2].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		menu->vertex[3].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);

	}


	// UIエフェクト:"つづける"
	else if (no == MENU_ANY_EFFECT)
	{
		// 頂点座標の設定
		menu->vertex[0].vtx = D3DXVECTOR3(menu->pos.x - MENU_ANY_EFFECT_SIZE_X, menu->pos.y - MENU_ANY_EFFECT_SIZE_Y, 0.0f);
		menu->vertex[1].vtx = D3DXVECTOR3(menu->pos.x + MENU_ANY_EFFECT_SIZE_X, menu->pos.y - MENU_ANY_EFFECT_SIZE_Y, 0.0f);
		menu->vertex[2].vtx = D3DXVECTOR3(menu->pos.x - MENU_ANY_EFFECT_SIZE_X, menu->pos.y + MENU_ANY_EFFECT_SIZE_Y, 0.0f);
		menu->vertex[3].vtx = D3DXVECTOR3(menu->pos.x + MENU_ANY_EFFECT_SIZE_X, menu->pos.y + MENU_ANY_EFFECT_SIZE_Y, 0.0f);

		// 反射光の設定
		menu->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, menueffect);
		menu->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, menueffect);
		menu->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, menueffect);
		menu->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, menueffect);

	}


	// UI:"やりなおす"
	else if (no == MENU_INIT)
	{
		// 頂点座標の設定
		menu->vertex[0].vtx = D3DXVECTOR3(menu->pos.x - MENU_INIT_SIZE_X, menu->pos.y - MENU_INIT_SIZE_Y, 0.0f);
		menu->vertex[1].vtx = D3DXVECTOR3(menu->pos.x + MENU_INIT_SIZE_X, menu->pos.y - MENU_INIT_SIZE_Y, 0.0f);
		menu->vertex[2].vtx = D3DXVECTOR3(menu->pos.x - MENU_INIT_SIZE_X, menu->pos.y + MENU_INIT_SIZE_Y, 0.0f);
		menu->vertex[3].vtx = D3DXVECTOR3(menu->pos.x + MENU_INIT_SIZE_X, menu->pos.y + MENU_INIT_SIZE_Y, 0.0f);

		// 反射光の設定
		menu->vertex[0].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		menu->vertex[1].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		menu->vertex[2].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		menu->vertex[3].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);

	}


	// UIエフェクト:"やりなおす"
	else if (no == MENU_INIT_EFFECT)
	{
		// 頂点座標の設定
		menu->vertex[0].vtx = D3DXVECTOR3(menu->pos.x - MENU_INIT_EFFECT_SIZE_X, menu->pos.y - MENU_INIT_EFFECT_SIZE_Y, 0.0f);
		menu->vertex[1].vtx = D3DXVECTOR3(menu->pos.x + MENU_INIT_EFFECT_SIZE_X, menu->pos.y - MENU_INIT_EFFECT_SIZE_Y, 0.0f);
		menu->vertex[2].vtx = D3DXVECTOR3(menu->pos.x - MENU_INIT_EFFECT_SIZE_X, menu->pos.y + MENU_INIT_EFFECT_SIZE_Y, 0.0f);
		menu->vertex[3].vtx = D3DXVECTOR3(menu->pos.x + MENU_INIT_EFFECT_SIZE_X, menu->pos.y + MENU_INIT_EFFECT_SIZE_Y, 0.0f);

		// 反射光の設定
		menu->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, menueffect);
		menu->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, menueffect);
		menu->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, menueffect);
		menu->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, menueffect);

	}

	// UI:"おわる"
	else if (no == MENU_FINISH)
	{
		// 頂点座標の設定
		menu->vertex[0].vtx = D3DXVECTOR3(menu->pos.x - MENU_FINISH_SIZE_X, menu->pos.y - MENU_FINISH_SIZE_Y, 0.0f);
		menu->vertex[1].vtx = D3DXVECTOR3(menu->pos.x + MENU_FINISH_SIZE_X, menu->pos.y - MENU_FINISH_SIZE_Y, 0.0f);
		menu->vertex[2].vtx = D3DXVECTOR3(menu->pos.x - MENU_FINISH_SIZE_X, menu->pos.y + MENU_FINISH_SIZE_Y, 0.0f);
		menu->vertex[3].vtx = D3DXVECTOR3(menu->pos.x + MENU_FINISH_SIZE_X, menu->pos.y + MENU_FINISH_SIZE_Y, 0.0f);

		// 反射光の設定
		menu->vertex[0].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		menu->vertex[1].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		menu->vertex[2].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		menu->vertex[3].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);

	}


	// UIエフェクト:"おわる"
	else if (no == MENU_FINISH_EFFECT)
	{
		// 頂点座標の設定
		menu->vertex[0].vtx = D3DXVECTOR3(menu->pos.x - MENU_FINISH_EFFECT_SIZE_X, menu->pos.y - MENU_FINISH_EFFECT_SIZE_Y, 0.0f);
		menu->vertex[1].vtx = D3DXVECTOR3(menu->pos.x + MENU_FINISH_EFFECT_SIZE_X, menu->pos.y - MENU_FINISH_EFFECT_SIZE_Y, 0.0f);
		menu->vertex[2].vtx = D3DXVECTOR3(menu->pos.x - MENU_FINISH_EFFECT_SIZE_X, menu->pos.y + MENU_FINISH_EFFECT_SIZE_Y, 0.0f);
		menu->vertex[3].vtx = D3DXVECTOR3(menu->pos.x + MENU_FINISH_EFFECT_SIZE_X, menu->pos.y + MENU_FINISH_EFFECT_SIZE_Y, 0.0f);

		// 反射光の設定
		menu->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, menueffect);
		menu->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, menueffect);
		menu->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, menueffect);
		menu->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, menueffect);

	}

	// テクスチャのパースペクティブコレクト用
	menu->vertex[0].rhw =
	menu->vertex[1].rhw =
	menu->vertex[2].rhw =
	menu->vertex[3].rhw = 1.0f;


	// テクスチャ座標の設定
	menu->vertex[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	menu->vertex[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	menu->vertex[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	menu->vertex[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// エフェクト関数
//=============================================================================
void SetVertexMenuEffect(int no)
{

	// ポインタの初期化
	MENU *menu = &menuWk[no];

	// UIエフェクト:"つづける"
	 if (no == MENU_ANY_EFFECT)
	{

		// 反射光の設定
		menu->vertex[0].diffuse = D3DCOLOR_RGBA(255, 0, 0, menueffect);
		menu->vertex[1].diffuse = D3DCOLOR_RGBA(0, 0, 255, menueffect);
		menu->vertex[2].diffuse = D3DCOLOR_RGBA(255, 0, 0, menueffect);
		menu->vertex[3].diffuse = D3DCOLOR_RGBA(0, 0, 255, menueffect);

	}

	 // UIエフェクト:"やりなおす"
	 if (no == MENU_INIT_EFFECT)
	 {

		 // 反射光の設定
		 menu->vertex[0].diffuse = D3DCOLOR_RGBA(255, 0, 0, menueffect);
		 menu->vertex[1].diffuse = D3DCOLOR_RGBA(0, 0, 255, menueffect);
		 menu->vertex[2].diffuse = D3DCOLOR_RGBA(255, 0, 0, menueffect);
		 menu->vertex[3].diffuse = D3DCOLOR_RGBA(0, 0, 255, menueffect);

	 }


	 // UIエフェクト:"おわる"
	 if (no == MENU_FINISH_EFFECT)
	 {

		 // 反射光の設定
		menu->vertex[0].diffuse = D3DCOLOR_RGBA(255, 0, 0, menueffect);
		menu->vertex[1].diffuse = D3DCOLOR_RGBA(0, 0, 255, menueffect);
		menu->vertex[2].diffuse = D3DCOLOR_RGBA(255, 0, 0, menueffect);
		menu->vertex[3].diffuse = D3DCOLOR_RGBA(0, 0, 255, menueffect);


	 }

}

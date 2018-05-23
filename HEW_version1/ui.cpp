//=============================================================================
//
// UI画面処理 [ui.cpp]
// Author : 眞戸原史也
// プログラム作成日 : 2018/3/09
//
//=============================================================================

#include "ui.h"							// マクロ＆構造体使用の為
#include "main.h"						// マクロ使用の為
#include "input.h"						// 関数使用の為
#include "game.h"						// 同上
#include "player.h"						// 関数使用の為
#include "player_skillNor.h"
#include "player_skillDef.h"
#include "player_skillSup.h"
#include "enemy.h"						// 同上
#include "enemy_skillNor.h"
#include "enemy_skillDef.h"
#include "enemy_skillSup.h"
#include "debugproc.h"					// 同上(デバッグ用)
#include "title.h"						// マクロ使用の為

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexUi(int no);			// 頂点作成関数
void SetVertexUiEffect(int no);			// エフェクト関数

//*****************************************************************************
// グローバル変数
//*****************************************************************************


UI uiWk[UI_MAX];						// タイトル構造体最大数宣言

float Hsize,Esize;						// ゲージ制御変数

int oldHp,oldEhp;						// 更新動作判定用変数

//float sizex, sizey;						// デバッグ用テクスチャ移動処理変数


//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT InitUi(int type)
{

	// ポインタの初期化
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	UI *ui = &uiWk[0];

	// ゲージ制御変数の初期化
	Hsize = 0;			// プレイヤーHPバー
	Esize = 0;			// エネミ－HPバー

	// 更新動作判定用変数の初期化
	oldHp = PLAYER_HP_MAX;		// プレイヤーHPバー
	oldEhp = ENEMY_HP_MAX;		// エネミ－HPバー

	//// デバッグ用テクスチャ移動処理変数の初期化
	//sizex = UI_SKILL_PAR_SIZE_X;
	//sizey = UI_SKILL_PAR_SIZE_Y;

	// 構造体最大数初期化処理
	for(int i = 0; i < UI_MAX;i++, ui++)
	{
		ui->PatternAnim = 0;								// アニメパターン番号をランダムで初期化
		ui->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 回転の初期化
		ui->effect = UI_EFFECT_BASE;						// エフェクトのα値の初期化
		ui->effectflag = true;								// 全て使用で初期

		// 初起動時
		if (type == FIRST)
		{

			// 全てNULLで初期化
			ui->Texture = NULL;

			// HPバー下地
			if (i == UI_BASE)
			{
				// 位置の設定
				ui->use = true;						// 使用で初期
				ui->pos = UI_BASE_POS;				// HPバー下地の位置の初期化

				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					UI_BASE_TEXTURE,				// ファイルの名前
					&ui->Texture);					// 読み込むメモリー
			}

			// HPバー枠
			else if (i == UI_HP_FRAME)
			{
				// 位置の設定
				ui->use = true;						// 使用で初期化
				ui->pos = UI_HP_FRAME_POS;			// HPバーの位置の初期化

													// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					UI_HP_TEXTURE,					// ファイルの名前
					&ui->Texture);					// 読み込むメモリー
			}

			// エネミ－HPバー枠
			else if (i == UI_EHP_FRAME)
			{
				// 位置の設定
				ui->use = true;						// 使用で初期化
				ui->pos = UI_EHP_FRAME_POS;			// HPバーの位置の初期化

													// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					UI_HP_TEXTURE,					// ファイルの名前
					&ui->Texture);					// 読み込むメモリー
			}

			// HPバー
			else if (i == UI_HP)
			{
				// 位置の設定
				ui->use = true;						// 使用で初期化
				ui->pos = UI_HP_POS;				// HPバーの位置の初期化

				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					UI_HP_TEXTURE,					// ファイルの名前
					&ui->Texture);					// 読み込むメモリー
			}

			// HPバーエフェクト
			else if (i == UI_HP_EFFECT)
			{
				// 位置の設定
				ui->use = false;					// 未使用で初期化
				ui->pos = UI_HP_POS;				// HPバーエフェクトの位置の初期化

				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					UI_HP_TEXTURE,					// ファイルの名前
					&ui->Texture);					// 読み込むメモリー
			}

			// エネミ－HPバー
			else if (i == UI_EHP)
			{
				// 位置の設定
				ui->use = true;						// 使用で初期化
				ui->pos = UI_EHP_POS;				// HPバーの位置の初期化

													// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					UI_HP_TEXTURE,					// ファイルの名前
					&ui->Texture);					// 読み込むメモリー
			}

			//エネミ－ HPバーエフェクト
			else if (i == UI_EHP_EFFECT)
			{
				// 位置の設定
				ui->use = false;					// 未使用で初期化
				ui->pos = UI_EHP_POS;				// HPバーエフェクトの位置の初期化

				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					UI_HP_TEXTURE,					// ファイルの名前
					&ui->Texture);					// 読み込むメモリー
			}

			// キャラクター:AIの位置
			else if (i == UI_AI)
			{
				// 位置の設定
				ui->use = true;						// 使用で初期
				ui->pos = UI_AI_POS;				// キャラクター:AIの位置の初期化

													// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					UI_AI_TEXTURE,					// ファイルの名前
					&ui->Texture);					// 読み込むメモリー
			}


			// キャラクター:ウイルスの位置
			else if (i == UI_VIRUS)
			{
				// 位置の設定
				ui->use = true;						// 使用で初期
				ui->pos = UI_VIRUSE_POS;			// キャラクター:ウイルスの位置の初期化

													// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					UI_VIRUS_TEXTURE,				// ファイルの名前
					&ui->Texture);					// 読み込むメモリー
			}


			// タイマーの枠の位置
			else if (i == UI_FRAME)
			{
				// 位置の設定
				ui->use = true;						// 使用で初期
				ui->pos = UI_FRAME_POS;				// タイマーの枠の位置の初期化

													// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					UI_FRAME_TEXTURE,				// ファイルの名前
					&ui->Texture);					// 読み込むメモリー
			}


			// タイマーの枠の位置
			else if (i == UI_FRAME_AI)
			{
				// 位置の設定
				ui->use = true;						// 使用で初期
				ui->pos = UI_FRAME_AI_POS;			// タイマーの枠の位置の初期化

													// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					UI_FRAME_AI_TEXTURE,				// ファイルの名前
					&ui->Texture);					// 読み込むメモリー
			}


			// タイマーの枠の位置
			else if (i == UI_FRAME_VIRUS)
			{
				// 位置の設定
				ui->use = true;						// 使用で初期
				ui->pos = UI_FRAME_VIRUS_POS;		// タイマーの枠の位置の初期化

				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					UI_FRAME_VIRUS_TEXTURE,			// ファイルの名前
					&ui->Texture);					// 読み込むメモリー
			}

			// スキル1アイコンの枠の位置
			else if (i == UI_SKILL_A)
			{
				// 位置の設定
				ui->use = true;						// 使用で初期
				ui->pos = UI_SKILL_A_POS;		// スキル1アイコンの位置の初期化

													// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					UI_SKILL_A_TEXTURE,			// ファイルの名前
					&ui->Texture);					// 読み込むメモリー
			}

			// スキル2アイコンの枠の位置
			else if (i == UI_SKILL_B)
			{
				// 位置の設定
				ui->use = true;						// 使用で初期
				ui->pos = UI_SKILL_B_POS;		// スキル2アイコンの位置の初期化

												// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					UI_SKILL_B_TEXTURE,			// ファイルの名前
					&ui->Texture);					// 読み込むメモリー
			}

			// スキル3アイコンの枠の位置
			else if (i == UI_SKILL_C)
			{
				// 位置の設定
				ui->use = true;						// 使用で初期
				ui->pos = UI_SKILL_C_POS;		// スキル3アイコンの位置の初期化

												// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					UI_SKILL_C_TEXTURE,			// ファイルの名前
					&ui->Texture);					// 読み込むメモリー
			}

			// スキル1アイコンの枠の位置
			else if (i == UI_ESKILL_A)
			{
				// 位置の設定
				ui->use = true;						// 使用で初期
				ui->pos = UI_ESKILL_A_POS;		// スキル1アイコンの位置の初期化

												// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					UI_SKILL_A_TEXTURE,			// ファイルの名前
					&ui->Texture);					// 読み込むメモリー
			}

			// スキル2アイコンの枠の位置
			else if (i == UI_ESKILL_B)
			{
				// 位置の設定
				ui->use = true;						// 使用で初期
				ui->pos = UI_ESKILL_B_POS;		// スキル2アイコンの位置の初期化

												// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					UI_SKILL_B_TEXTURE,			// ファイルの名前
					&ui->Texture);					// 読み込むメモリー
			}

			// スキル3アイコンの枠の位置
			else if (i == UI_ESKILL_C)
			{
				// 位置の設定
				ui->use = true;						// 使用で初期
				ui->pos = UI_ESKILL_C_POS;		// スキル3アイコンの位置の初期化

												// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					UI_SKILL_C_TEXTURE,			// ファイルの名前
					&ui->Texture);					// 読み込むメモリー
			}

			// キーアイコンの枠の位置
			else if (i == UI_SKILL_KEY)
			{
				// 位置の設定
				ui->use = true;						// 使用で初期
				ui->pos = UI_SKILL_KEY_POS;		// キーアイコンの位置の初期化

												// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					UI_SKILL_KEY_TEXTURE,			// ファイルの名前
					&ui->Texture);					// 読み込むメモリー
			}

			// キーアイコンの枠の位置
			else if (i == UI_SKILL_BKEY)
			{
				// 位置の設定
				ui->use = true;						// 使用で初期
				ui->pos = UI_SKILL_BKEY_POS;		// キーアイコンの位置の初期化

												// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					UI_SKILL_BKEY_TEXTURE,			// ファイルの名前
					&ui->Texture);					// 読み込むメモリー
			}

			// キーアイコンの枠の位置
			else if (i == UI_ESKILL_KEY)
			{
				// 位置の設定
				ui->use = true;						// 使用で初期
				ui->pos = UI_ESKILL_KEY_POS;		// キーアイコンの位置の初期化

												// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					UI_SKILL_KEY_TEXTURE,			// ファイルの名前
					&ui->Texture);					// 読み込むメモリー
			}

			// キーアイコンの枠の位置
			else if (i == UI_ESKILL_BKEY)
			{
				// 位置の設定
				ui->use = true;						// 使用で初期
				ui->pos = UI_ESKILL_BKEY_POS;		// キーアイコンの位置の初期化

													// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					UI_SKILL_BKEY_TEXTURE,			// ファイルの名前
					&ui->Texture);					// 読み込むメモリー
			}

			// 演算子アイコンの枠の位置
			else if (i == UI_SKILL_CROSS)
			{
				// 位置の設定
				ui->use = true;						// 使用で初期
				ui->pos = UI_SKILL_CROSS_POS;		// キーアイコンの位置の初期化

												// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					UI_SKILL_CROSS_TEXTURE,			// ファイルの名前
					&ui->Texture);					// 読み込むメモリー
			}

			// 演算子アイコンの枠の位置
			else if (i == UI_SKILL_BCROSS)
			{
				// 位置の設定
				ui->use = true;						// 使用で初期
				ui->pos = UI_SKILL_BCROSS_POS;		// キーアイコンの位置の初期化

													// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					UI_SKILL_CROSS_TEXTURE,			// ファイルの名前
					&ui->Texture);					// 読み込むメモリー
			}

			// 演算子アイコンの枠の位置
			else if (i == UI_ESKILL_CROSS)
			{
				// 位置の設定
				ui->use = true;						// 使用で初期
				ui->pos = UI_ESKILL_CROSS_POS;		// キーアイコンの位置の初期化

													// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					UI_SKILL_CROSS_TEXTURE,			// ファイルの名前
					&ui->Texture);					// 読み込むメモリー
			}

			// 演算子アイコンの枠の位置
			else if (i == UI_ESKILL_BCROSS)
			{
				// 位置の設定
				ui->use = true;						// 使用で初期
				ui->pos = UI_ESKILL_BCROSS_POS;		// キーアイコンの位置の初期化

													// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					UI_SKILL_CROSS_TEXTURE,			// ファイルの名前
					&ui->Texture);					// 読み込むメモリー
			}

			// 数字アイコンの枠の位置
			else if (i == UI_SKILL_NUM)
			{
				// 位置の設定
				ui->use = true;						// 使用で初期
				ui->pos = UI_SKILL_NUM_POS;			// キーアイコンの位置の初期化

													// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					UI_SKILL_NUM_TEXTURE,			// ファイルの名前
					&ui->Texture);					// 読み込むメモリー
			}

			// 数字アイコンの枠の位置
			else if (i == UI_SKILL_BNUM)
			{
				// 位置の設定
				ui->use = true;						// 使用で初期
				ui->pos = UI_SKILL_BNUM_POS;		// キーアイコンの位置の初期化

													// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					UI_SKILL_NUM_TEXTURE,			// ファイルの名前
					&ui->Texture);					// 読み込むメモリー
			}

			// 数字アイコンの枠の位置
			else if (i == UI_ESKILL_NUM)
			{
				// 位置の設定
				ui->use = true;						// 使用で初期
				ui->pos = UI_ESKILL_NUM_POS;		// キーアイコンの位置の初期化

													// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					UI_SKILL_NUM_TEXTURE,			// ファイルの名前
					&ui->Texture);					// 読み込むメモリー
			}

			// 数字アイコンの枠の位置
			else if (i == UI_ESKILL_BNUM)
			{
				// 位置の設定
				ui->use = true;					// 使用で初期
				ui->pos = UI_ESKILL_BNUM_POS;		// キーアイコンの位置の初期化

				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					UI_SKILL_NUM_TEXTURE,			// ファイルの名前
					&ui->Texture);					// 読み込むメモリー
			}

			// 演算子(スペシャル)の枠の位置
			else if (i == UI_SKILL_PAR)
			{
				// 位置の設定
				ui->use = true;						// 使用で初期
				ui->pos = UI_SKILL_PAR_POS;			// キーアイコンの位置の初期化

													// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					UI_SKILL_PAR_TEXTURE,			// ファイルの名前
					&ui->Texture);					// 読み込むメモリー
			}

			/// 演算子(スペシャル)の枠の位置
			else if (i == UI_ESKILL_PAR)
			{
				// 位置の設定
				ui->use = true;					// 使用で初期
				ui->pos = UI_ESKILL_PAR_POS;		// キーアイコンの位置の初期化

													// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
					UI_SKILL_PAR_TEXTURE,			// ファイルの名前
					&ui->Texture);					// 読み込むメモリー
			}


		}

		// ゲーム更新時
		else if (type == UPDATA)
		{
			ui->use = true;		// 使用で初期化

			// UIで最初表示するもの以外は未使用で初期化
			// プレイヤーHPバーエフェクト
			// エネミ－HPバーエフェクト
			if ((i == UI_HP_EFFECT)||(i == UI_EHP_EFFECT))
			{
				ui->use = false;					// 未使用で初期化
			}
		}

		// 頂点情報の作成
		MakeVertexUi(i);
	}

	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void UninitUi(void)
{
	// ポインタの初期化
	UI *ui = &uiWk[0];

	// 構造体最大数終了処理
	for (int i = 0; i < UI_MAX;i++, ui++)
	{

		// テクスチャの開放出来ていなかったら
		if (ui->Texture != NULL)
		{

			// テクスチャの開放
			ui->Texture->Release();
			ui->Texture = NULL;
		}
	}

}

//=============================================================================
// 更新処理関数
//=============================================================================
void UpdateUi(void)
{

	// ポインタの初期化
	PLAYER *player = GetPlayer();
	ENEMY *enemy = GetEnemy();
	PLAYER_NORSKILL *playernorSkill = GetPlayerNorSkill(0);
	ENEMY_NORSKILL *enemynorSkill = GetEnemyNorSkill(0);
	PLAYER_SKILLDEF *playerskillDef = GetPlayerSkillDef(0);
	ENEMY_SKILLDEF *enemyskillDef = GetEnemySkillDef(0);
	PLAYER_SUPSKILL *playersupSkill = GetPlayerSupSkill(0);
	ENEMY_SUPSKILL *enemysupSkill = GetEnemySupSkill(0);


	// 使用する構造体のポインタの初期化
	UI *ui = &uiWk[0];
	UI *uiH = &uiWk[UI_HP_EFFECT];					// プレイヤーHPバーエフェクト
	UI *uiE = &uiWk[UI_EHP_EFFECT];					// エネミ－HPバーエフェクト

	// HPバーに変化
	if (oldHp != player->hp)
	{

		// HPバーエフェクトを使用に
		uiH->use = true;
		uiH->effectflag = true;

	}

	// HPバーに変化
	if (oldEhp != enemy->hp)
	{

		// HPバーエフェクトを使用に
		uiE->use = true;
		uiE->effectflag = true;

	}

	// スキル1
	if (player->norSk == false)
	{

		UI *uiA = &uiWk[UI_SKILL_A];

		for (int i = UI_SKILL_A;i <= UI_SKILL_NUM;i++, uiA++)
		{
			// 反射光の設定
			uiA->vertex[0].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
			uiA->vertex[1].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
			uiA->vertex[2].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
			uiA->vertex[3].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);

		}
	}
	else if (player->norSk == true)
	{
		UI *uiA = &uiWk[UI_SKILL_A];

		for (int i = UI_SKILL_A;i <= UI_SKILL_NUM;i++, uiA++)
		{
			// 反射光の設定
			uiA->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			uiA->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			uiA->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			uiA->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		}

	}

	// スキル2
	if (player->defSk == false)
	{

		UI *uiB = &uiWk[UI_SKILL_B];

		for (int i = UI_SKILL_B;i <= UI_SKILL_BNUM;i++, uiB++)
		{
			// 反射光の設定
			uiB->vertex[0].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
			uiB->vertex[1].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
			uiB->vertex[2].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
			uiB->vertex[3].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);

		}
	}
	else if (player->defSk == true)
	{
		UI *uiB = &uiWk[UI_SKILL_B];

		for (int i = UI_SKILL_B;i <= UI_SKILL_BNUM;i++, uiB++)
		{
			// 反射光の設定
			uiB->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			uiB->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			uiB->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			uiB->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		}

	}

	// スキル3
	if (player->supSk == false)
	{

		UI *uiC = &uiWk[UI_SKILL_C];

		for (int i = UI_SKILL_C;i <= UI_SKILL_PAR;i++, uiC++)
		{
			// 反射光の設定
			uiC->vertex[0].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
			uiC->vertex[1].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
			uiC->vertex[2].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
			uiC->vertex[3].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);

		}
	}
	else if (player->supSk == true)
	{
		UI *uiC = &uiWk[UI_SKILL_C];

		for (int i = UI_SKILL_C;i <= UI_SKILL_PAR;i++, uiC++)
		{
			// 反射光の設定
			uiC->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			uiC->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			uiC->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			uiC->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		}

	}


	// スキル1
	if (enemy->norSk == false)
	{

		UI *uiEA = &uiWk[UI_ESKILL_A];

		for (int i = UI_ESKILL_A;i <= UI_ESKILL_NUM;i++, uiEA++)
		{
			// 反射光の設定
			uiEA->vertex[0].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
			uiEA->vertex[1].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
			uiEA->vertex[2].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
			uiEA->vertex[3].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);

		}
	}
	else if (enemy->norSk ==true)
	{
		UI *uiEA = &uiWk[UI_ESKILL_A];

		for (int i = UI_ESKILL_A;i <= UI_ESKILL_NUM;i++, uiEA++)
		{
			// 反射光の設定
			uiEA->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			uiEA->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			uiEA->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			uiEA->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		}

	}


	// スキル2
	if (enemy->defSk == false)
	{

		UI *uiEB = &uiWk[UI_ESKILL_B];

		for (int i = UI_ESKILL_B;i <= UI_ESKILL_BNUM;i++, uiEB++)
		{
			// 反射光の設定
			uiEB->vertex[0].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
			uiEB->vertex[1].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
			uiEB->vertex[2].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
			uiEB->vertex[3].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);

		}
	}
	else if (enemy->defSk == true)
	{
		UI *uiEB = &uiWk[UI_ESKILL_B];

		for (int i = UI_ESKILL_B;i <= UI_ESKILL_BNUM;i++, uiEB++)
		{
			// 反射光の設定
			uiEB->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			uiEB->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			uiEB->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			uiEB->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		}

	}

	// スキル3
	if (enemy->supSk == false)
	{

		UI *uiEC = &uiWk[UI_ESKILL_C];

		for (int i = UI_ESKILL_C;i <= UI_ESKILL_PAR;i++, uiEC++)
		{
			// 反射光の設定
			uiEC->vertex[0].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
			uiEC->vertex[1].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
			uiEC->vertex[2].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
			uiEC->vertex[3].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);

		}
	}
	else if (enemy->supSk == true)
	{
		UI *uiEC = &uiWk[UI_ESKILL_C];

		for (int i = UI_ESKILL_C;i <= UI_ESKILL_PAR;i++, uiEC++)
		{
			// 反射光の設定
			uiEC->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			uiEC->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			uiEC->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			uiEC->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		}

	}


	
	// 構造体最大数更新処理
	for (int i = 0; i < UI_MAX;i++, ui++)
	{
		// プレイヤーHPバーエフェクト
		// エネミ－HPバーエフェクト
		if ((i == UI_HP_EFFECT) || (i == UI_EHP_EFFECT))
		{

			// 使用していたら
			if (ui->use == true)
			{
				// エフェクト処理
				// プラスフラグ
				if (ui->effectflag == true)
				{
					// エフェクトαの値にUI_EFFECT_SPEEDを足す
					ui->effect += UI_EFFECT_SPEED;

					// エフェクトα値が最大
					if (ui->effect > ALPHA_MAX)
					{
						// フラグをマイナスに
						ui->effectflag = false;

						// エフェクトα値を最大値に固定
						ui->effect = ALPHA_MAX;
					}
				}

				// マイナスフラグ
				else if (ui->effectflag == false)
				{

					// エフェクトαの値にUI_EFFECT_SPEEDを引く
					ui->effect -= UI_EFFECT_SPEED;

					// エフェクトα値が最小
					if (ui->effect < ALPHA_BASE)
					{
						// フラグをプラスに
						ui->effectflag = true;

						// 処理が終了したものを未使用に
						ui->use = false;
					}

				}

			}
		}

		// スキル1残弾
		if (i == UI_SKILL_NUM)
		{
			// パターンの切り替え
			ui->PatternAnim = playernorSkill->cnt;

			// テクスチャ座標を設定
			SetTextureUi(i, ui->PatternAnim);
		}

		// スキル2残弾
		if (i == UI_SKILL_BNUM)
		{
			// パターンの切り替え
			ui->PatternAnim = playerskillDef->cnt;

			// テクスチャ座標を設定
			SetTextureUi(i, ui->PatternAnim);
		}

		// スキル1残弾(敵)
		if (i == UI_ESKILL_NUM)
		{
			// パターンの切り替え
			ui->PatternAnim = enemynorSkill->cnt;

			// テクスチャ座標を設定
			SetTextureUi(i, ui->PatternAnim);
		}

		// スキル1残弾(敵)
		if (i == UI_ESKILL_BNUM)
		{
			// パターンの切り替え
			ui->PatternAnim = enemyskillDef->cnt;

			// テクスチャ座標を設定
			SetTextureUi(i, ui->PatternAnim);
		}


//		// デバッグ用移動拡大処理
//		if (i == UI_SKILL_PAR)
//		{
//
//			// 左
//			if (GetKeyboardPress(DIK_V))
//			{
//				ui->pos.x--;
//			}
//
//			// 右
//			else if (GetKeyboardPress(DIK_B))
//			{
//				ui->pos.x++;
//			}
//
//			// 上
//			if (GetKeyboardPress(DIK_N))
//			{
//				ui->pos.y--;
//
//			}
//			// 下
//			else if (GetKeyboardPress(DIK_M))
//			{
//				ui->pos.y++;
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
//			PrintDebugProc("座標:X %f)\n", ui->pos.x);
//			PrintDebugProc("座標:Y %f)\n", ui->pos.y);
//#endif
//		}


		// エフェクト処理
		SetVertexUiEffect(i);

	}

	// 現在のプレイヤーHP、エネミ－HPの値を保存
	oldHp = player->hp;
	oldEhp = enemy->hp;

}

//=============================================================================
// 描画処理関数
//=============================================================================
void DrawUi(void)
{
	// ポインタの初期化
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	UI *ui = &uiWk[0];
	
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);


	// 構造体最大数終了処理
	for (int i = 0; i < UI_MAX;i++, ui++)
	{
		// 使用していたら
		if (ui->use == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, ui->Texture);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, ui->vertex, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点作成関数
//=============================================================================
HRESULT MakeVertexUi(int no)
{
	
	// ポインタの初期化
	UI *ui = &uiWk[no];

	//  HPバー下地
	if (no==UI_BASE)
	{
		// 頂点座標の設定
		ui->vertex[0].vtx = D3DXVECTOR3(ui->pos.x - UI_BASE_SIZE_X, ui->pos.y - UI_BASE_SIZE_Y, 0.0f);
		ui->vertex[1].vtx = D3DXVECTOR3(ui->pos.x + UI_BASE_SIZE_X, ui->pos.y - UI_BASE_SIZE_Y, 0.0f);
		ui->vertex[2].vtx = D3DXVECTOR3(ui->pos.x - UI_BASE_SIZE_X, ui->pos.y + UI_BASE_SIZE_Y, 0.0f);
		ui->vertex[3].vtx = D3DXVECTOR3(ui->pos.x + UI_BASE_SIZE_X, ui->pos.y + UI_BASE_SIZE_Y, 0.0f);

		// 反射光の設定
		ui->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// HPバー枠
	else if ((no == UI_HP_FRAME)|| (no == UI_EHP_FRAME))
	{
		// 頂点座標の設定
		ui->vertex[0].vtx = D3DXVECTOR3(ui->pos.x - UI_HP_FRAME_SIZE_X, ui->pos.y - UI_HP_FRAME_SIZE_Y, 0.0f);
		ui->vertex[1].vtx = D3DXVECTOR3(ui->pos.x + UI_HP_FRAME_SIZE_X, ui->pos.y - UI_HP_FRAME_SIZE_Y, 0.0f);
		ui->vertex[2].vtx = D3DXVECTOR3(ui->pos.x - UI_HP_FRAME_SIZE_X, ui->pos.y + UI_HP_FRAME_SIZE_Y, 0.0f);
		ui->vertex[3].vtx = D3DXVECTOR3(ui->pos.x + UI_HP_FRAME_SIZE_X, ui->pos.y + UI_HP_FRAME_SIZE_Y, 0.0f);

		// 反射光の設定
		ui->vertex[0].diffuse = D3DCOLOR_RGBA(0, 0, 0, 255);
		ui->vertex[1].diffuse = D3DCOLOR_RGBA(0, 0, 0, 255);
		ui->vertex[2].diffuse = D3DCOLOR_RGBA(0, 0, 0, 255);
		ui->vertex[3].diffuse = D3DCOLOR_RGBA(0, 0, 0, 255);

	}

	// HPバー
	else if (no == UI_HP)
	{
		// 頂点座標の設定
		ui->vertex[0].vtx = D3DXVECTOR3(ui->pos.x , ui->pos.y , 0.0f);
		ui->vertex[1].vtx = D3DXVECTOR3(ui->pos.x + UI_HP_SIZE_X, ui->pos.y, 0.0f);
		ui->vertex[2].vtx = D3DXVECTOR3(ui->pos.x , ui->pos.y + UI_HP_SIZE_Y, 0.0f);
		ui->vertex[3].vtx = D3DXVECTOR3(ui->pos.x + UI_HP_SIZE_X, ui->pos.y + UI_HP_SIZE_Y, 0.0f);

		// 反射光の設定
		ui->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// HPバーエフェクト
	else if (no == UI_EHP_EFFECT)
	{
		// 頂点座標の設定
		ui->vertex[0].vtx = D3DXVECTOR3(ui->pos.x, ui->pos.y, 0.0f);
		ui->vertex[1].vtx = D3DXVECTOR3(ui->pos.x + UI_HP_SIZE_X, ui->pos.y, 0.0f);
		ui->vertex[2].vtx = D3DXVECTOR3(ui->pos.x, ui->pos.y + UI_HP_SIZE_Y, 0.0f);
		ui->vertex[3].vtx = D3DXVECTOR3(ui->pos.x + UI_HP_SIZE_X, ui->pos.y + UI_HP_SIZE_Y, 0.0f);

		// 反射光の設定
		ui->vertex[0].diffuse = D3DCOLOR_RGBA(255, 0, 0, ui->effect);
		ui->vertex[1].diffuse = D3DCOLOR_RGBA(255, 0, 0, ui->effect);
		ui->vertex[2].diffuse = D3DCOLOR_RGBA(255, 0, 0, ui->effect);
		ui->vertex[3].diffuse = D3DCOLOR_RGBA(255, 0, 0, ui->effect);

	}

	// エネミ－HPバー
	else if (no == UI_EHP)
	{
		// 頂点座標の設定
		ui->vertex[0].vtx = D3DXVECTOR3(ui->pos.x - UI_HP_SIZE_X, ui->pos.y, 0.0f);
		ui->vertex[1].vtx = D3DXVECTOR3(ui->pos.x, ui->pos.y, 0.0f);
		ui->vertex[2].vtx = D3DXVECTOR3(ui->pos.x - UI_HP_SIZE_X, ui->pos.y + UI_HP_SIZE_Y, 0.0f);
		ui->vertex[3].vtx = D3DXVECTOR3(ui->pos.x, ui->pos.y + UI_HP_SIZE_Y, 0.0f);

		// 反射光の設定
		ui->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// エネミ－HPバーエフェクト
	else if (no == UI_EHP_EFFECT)
	{

		// 頂点座標の設定
		ui->vertex[0].vtx = D3DXVECTOR3(ui->pos.x - UI_HP_SIZE_X, ui->pos.y, 0.0f);
		ui->vertex[1].vtx = D3DXVECTOR3(ui->pos.x, ui->pos.y, 0.0f);
		ui->vertex[2].vtx = D3DXVECTOR3(ui->pos.x - UI_HP_SIZE_X, ui->pos.y + UI_HP_SIZE_Y, 0.0f);
		ui->vertex[3].vtx = D3DXVECTOR3(ui->pos.x, ui->pos.y + UI_HP_SIZE_Y, 0.0f);

		// 反射光の設定
		ui->vertex[0].diffuse = D3DCOLOR_RGBA(0, 0, 255, ui->effect);
		ui->vertex[1].diffuse = D3DCOLOR_RGBA(0, 0, 255, ui->effect);
		ui->vertex[2].diffuse = D3DCOLOR_RGBA(0, 0, 255, ui->effect);
		ui->vertex[3].diffuse = D3DCOLOR_RGBA(0, 0, 255, ui->effect);

	}

	// キャラクター:AI
	else if (no == UI_AI)
	{
		// 頂点座標の設定
		ui->vertex[0].vtx = D3DXVECTOR3(ui->pos.x - UI_AI_SIZE_X, ui->pos.y - UI_AI_SIZE_Y, 0.0f);
		ui->vertex[1].vtx = D3DXVECTOR3(ui->pos.x + UI_AI_SIZE_X, ui->pos.y - UI_AI_SIZE_Y, 0.0f);
		ui->vertex[2].vtx = D3DXVECTOR3(ui->pos.x - UI_AI_SIZE_X, ui->pos.y + UI_AI_SIZE_Y, 0.0f);
		ui->vertex[3].vtx = D3DXVECTOR3(ui->pos.x + UI_AI_SIZE_X, ui->pos.y + UI_AI_SIZE_Y, 0.0f);

		// 反射光の設定
		ui->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// キャラクター:ウイルス
	else if (no == UI_VIRUS)
	{
		// 頂点座標の設定
		ui->vertex[0].vtx = D3DXVECTOR3(ui->pos.x - UI_VIRUS_SIZE_X, ui->pos.y - UI_VIRUS_SIZE_Y, 0.0f);
		ui->vertex[1].vtx = D3DXVECTOR3(ui->pos.x + UI_VIRUS_SIZE_X, ui->pos.y - UI_VIRUS_SIZE_Y, 0.0f);
		ui->vertex[2].vtx = D3DXVECTOR3(ui->pos.x - UI_VIRUS_SIZE_X, ui->pos.y + UI_VIRUS_SIZE_Y, 0.0f);
		ui->vertex[3].vtx = D3DXVECTOR3(ui->pos.x + UI_VIRUS_SIZE_X, ui->pos.y + UI_VIRUS_SIZE_Y, 0.0f);

		// 反射光の設定
		ui->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// タイマーの枠
	else if (no == UI_FRAME)
	{
		// 頂点座標の設定
		ui->vertex[0].vtx = D3DXVECTOR3(ui->pos.x - UI_FRAME_SIZE_X, ui->pos.y - UI_FRAME_SIZE_Y, 0.0f);
		ui->vertex[1].vtx = D3DXVECTOR3(ui->pos.x + UI_FRAME_SIZE_X, ui->pos.y - UI_FRAME_SIZE_Y, 0.0f);
		ui->vertex[2].vtx = D3DXVECTOR3(ui->pos.x - UI_FRAME_SIZE_X, ui->pos.y + UI_FRAME_SIZE_Y, 0.0f);
		ui->vertex[3].vtx = D3DXVECTOR3(ui->pos.x + UI_FRAME_SIZE_X, ui->pos.y + UI_FRAME_SIZE_Y, 0.0f);

		// 反射光の設定
		ui->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// 技枠AI
	else if (no == UI_FRAME_AI)
	{
		// 頂点座標の設定
		ui->vertex[0].vtx = D3DXVECTOR3(ui->pos.x - UI_FRAME_AI_SIZE_X, ui->pos.y - UI_FRAME_AI_SIZE_Y, 0.0f);
		ui->vertex[1].vtx = D3DXVECTOR3(ui->pos.x + UI_FRAME_AI_SIZE_X, ui->pos.y - UI_FRAME_AI_SIZE_Y, 0.0f);
		ui->vertex[2].vtx = D3DXVECTOR3(ui->pos.x - UI_FRAME_AI_SIZE_X, ui->pos.y + UI_FRAME_AI_SIZE_Y, 0.0f);
		ui->vertex[3].vtx = D3DXVECTOR3(ui->pos.x + UI_FRAME_AI_SIZE_X, ui->pos.y + UI_FRAME_AI_SIZE_Y, 0.0f);

		// 反射光の設定
		ui->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 180);
		ui->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 180);
		ui->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 180);
		ui->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 180);

	}

	// 技枠ウイルス
	else if (no == UI_FRAME_VIRUS)
	{
		// 頂点座標の設定
		ui->vertex[0].vtx = D3DXVECTOR3(ui->pos.x - UI_FRAME_AI_SIZE_X, ui->pos.y - UI_FRAME_AI_SIZE_Y, 0.0f);
		ui->vertex[1].vtx = D3DXVECTOR3(ui->pos.x + UI_FRAME_AI_SIZE_X, ui->pos.y - UI_FRAME_AI_SIZE_Y, 0.0f);
		ui->vertex[2].vtx = D3DXVECTOR3(ui->pos.x - UI_FRAME_AI_SIZE_X, ui->pos.y + UI_FRAME_AI_SIZE_Y, 0.0f);
		ui->vertex[3].vtx = D3DXVECTOR3(ui->pos.x + UI_FRAME_AI_SIZE_X, ui->pos.y + UI_FRAME_AI_SIZE_Y, 0.0f);

		// 反射光の設定
		ui->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 180);
		ui->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 180);
		ui->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 180);
		ui->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 180);

	}

	// スキルアイコン
	else if ((no == UI_SKILL_A)|| (no == UI_SKILL_B) || (no == UI_ESKILL_A) || (no == UI_ESKILL_B))
	{
		// 頂点座標の設定
		ui->vertex[0].vtx = D3DXVECTOR3(ui->pos.x - UI_SKILL_SIZE_X, ui->pos.y - UI_SKILL_SIZE_Y, 0.0f);
		ui->vertex[1].vtx = D3DXVECTOR3(ui->pos.x + UI_SKILL_SIZE_X, ui->pos.y - UI_SKILL_SIZE_Y, 0.0f);
		ui->vertex[2].vtx = D3DXVECTOR3(ui->pos.x - UI_SKILL_SIZE_X, ui->pos.y + UI_SKILL_SIZE_Y, 0.0f);
		ui->vertex[3].vtx = D3DXVECTOR3(ui->pos.x + UI_SKILL_SIZE_X, ui->pos.y + UI_SKILL_SIZE_Y, 0.0f);

		// 反射光の設定
		ui->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// スキルアイコン
	else if ((no == UI_SKILL_C) || (no == UI_ESKILL_C))
	{
		// 頂点座標の設定
		ui->vertex[0].vtx = D3DXVECTOR3(ui->pos.x - UI_SKILL_C_SIZE_X, ui->pos.y - UI_SKILL_C_SIZE_Y, 0.0f);
		ui->vertex[1].vtx = D3DXVECTOR3(ui->pos.x + UI_SKILL_C_SIZE_X, ui->pos.y - UI_SKILL_C_SIZE_Y, 0.0f);
		ui->vertex[2].vtx = D3DXVECTOR3(ui->pos.x - UI_SKILL_C_SIZE_X, ui->pos.y + UI_SKILL_C_SIZE_Y, 0.0f);
		ui->vertex[3].vtx = D3DXVECTOR3(ui->pos.x + UI_SKILL_C_SIZE_X, ui->pos.y + UI_SKILL_C_SIZE_Y, 0.0f);

		// 反射光の設定
		ui->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// キーアイコン
	else if ((no == UI_SKILL_KEY) || (no == UI_SKILL_BKEY) || (no == UI_ESKILL_KEY) || (no == UI_ESKILL_BKEY))
	{
		// 頂点座標の設定
		ui->vertex[0].vtx = D3DXVECTOR3(ui->pos.x - UI_SKILL_KEY_SIZE_X, ui->pos.y - UI_SKILL_KEY_SIZE_Y, 0.0f);
		ui->vertex[1].vtx = D3DXVECTOR3(ui->pos.x + UI_SKILL_KEY_SIZE_X, ui->pos.y - UI_SKILL_KEY_SIZE_Y, 0.0f);
		ui->vertex[2].vtx = D3DXVECTOR3(ui->pos.x - UI_SKILL_KEY_SIZE_X, ui->pos.y + UI_SKILL_KEY_SIZE_Y, 0.0f);
		ui->vertex[3].vtx = D3DXVECTOR3(ui->pos.x + UI_SKILL_KEY_SIZE_X, ui->pos.y + UI_SKILL_KEY_SIZE_Y, 0.0f);

		// 反射光の設定
		ui->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// 演算子
	else if ((no == UI_SKILL_CROSS) || (no == UI_SKILL_BCROSS) || (no == UI_ESKILL_CROSS) || (no == UI_ESKILL_BCROSS))
	{
		// 頂点座標の設定
		ui->vertex[0].vtx = D3DXVECTOR3(ui->pos.x - UI_SKILL_CROSS_SIZE_X, ui->pos.y - UI_SKILL_CROSS_SIZE_Y, 0.0f);
		ui->vertex[1].vtx = D3DXVECTOR3(ui->pos.x + UI_SKILL_CROSS_SIZE_X, ui->pos.y - UI_SKILL_CROSS_SIZE_Y, 0.0f);
		ui->vertex[2].vtx = D3DXVECTOR3(ui->pos.x - UI_SKILL_CROSS_SIZE_X, ui->pos.y + UI_SKILL_CROSS_SIZE_Y, 0.0f);
		ui->vertex[3].vtx = D3DXVECTOR3(ui->pos.x + UI_SKILL_CROSS_SIZE_X, ui->pos.y + UI_SKILL_CROSS_SIZE_Y, 0.0f);

		// 反射光の設定
		ui->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}


	// 数字
	else if ((no == UI_SKILL_NUM) || (no == UI_SKILL_BNUM) || (no == UI_ESKILL_NUM) || (no == UI_ESKILL_BNUM))
	{
		// 頂点座標の設定
		ui->vertex[0].vtx = D3DXVECTOR3(ui->pos.x - UI_SKILL_NUM_SIZE_X, ui->pos.y - UI_SKILL_NUM_SIZE_Y, 0.0f);
		ui->vertex[1].vtx = D3DXVECTOR3(ui->pos.x + UI_SKILL_NUM_SIZE_X, ui->pos.y - UI_SKILL_NUM_SIZE_Y, 0.0f);
		ui->vertex[2].vtx = D3DXVECTOR3(ui->pos.x - UI_SKILL_NUM_SIZE_X, ui->pos.y + UI_SKILL_NUM_SIZE_Y, 0.0f);
		ui->vertex[3].vtx = D3DXVECTOR3(ui->pos.x + UI_SKILL_NUM_SIZE_X, ui->pos.y + UI_SKILL_NUM_SIZE_Y, 0.0f);

		// 反射光の設定
		ui->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// スキルアイコン
	else if ((no == UI_SKILL_PAR) || (no == UI_ESKILL_PAR))
	{
		// 頂点座標の設定
		ui->vertex[0].vtx = D3DXVECTOR3(ui->pos.x - UI_SKILL_PAR_SIZE_X, ui->pos.y - UI_SKILL_PAR_SIZE_Y, 0.0f);
		ui->vertex[1].vtx = D3DXVECTOR3(ui->pos.x + UI_SKILL_PAR_SIZE_X, ui->pos.y - UI_SKILL_PAR_SIZE_Y, 0.0f);
		ui->vertex[2].vtx = D3DXVECTOR3(ui->pos.x - UI_SKILL_PAR_SIZE_X, ui->pos.y + UI_SKILL_PAR_SIZE_Y, 0.0f);
		ui->vertex[3].vtx = D3DXVECTOR3(ui->pos.x + UI_SKILL_PAR_SIZE_X, ui->pos.y + UI_SKILL_PAR_SIZE_Y, 0.0f);

		// 反射光の設定
		ui->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}



	// テクスチャのパースペクティブコレクト用
	ui->vertex[0].rhw =
	ui->vertex[1].rhw =
	ui->vertex[2].rhw =
	ui->vertex[3].rhw = 1.0f;


	// テクスチャ座標の設定
	ui->vertex[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	ui->vertex[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	ui->vertex[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	ui->vertex[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// テクスチャ座標設定関数
//=============================================================================
void SetTextureUi(int no, int cntPattern)
{

	// ポインタの初期化
	UI *ui = &uiWk[no];

	// テクスチャ座標の設定
	int x = cntPattern % UI_ANIM_PATTERN_DIVIDE_X;
	int y = cntPattern / UI_ANIM_PATTERN_DIVIDE_Y;
	float sizeX = 1.0f / UI_ANIM_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / UI_ANIM_PATTERN_DIVIDE_Y;
	ui->vertex[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	ui->vertex[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	ui->vertex[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	ui->vertex[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}


//=============================================================================
// エフェクト関数
//=============================================================================
void SetVertexUiEffect(int no)
{

	// ポインタの初期化
	UI *ui = &uiWk[no];
	PLAYER *player = GetPlayer();
	ENEMY *enemy = GetEnemy();


	// //デバッグ用テクスチャ更新
	////// //HPバー
	//if (no == UI_SKILL_PAR)
	//{
	//	// 頂点座標の設定
	//	ui->vertex[0].vtx = D3DXVECTOR3(ui->pos.x - sizex, ui->pos.y - sizey, 0.0f);
	//	ui->vertex[1].vtx = D3DXVECTOR3(ui->pos.x + sizex, ui->pos.y - sizey, 0.0f);
	//	ui->vertex[2].vtx = D3DXVECTOR3(ui->pos.x - sizex, ui->pos.y + sizey, 0.0f);
	//	ui->vertex[3].vtx = D3DXVECTOR3(ui->pos.x + sizex, ui->pos.y + sizey, 0.0f);

	//}

	//// HPバー
	// if (no == UI_HP_FRAME)
	//{
	//	// 頂点座標の設定
	//	ui->vertex[0].vtx = D3DXVECTOR3(ui->pos.x, ui->pos.y, 0.0f);
	//	ui->vertex[1].vtx = D3DXVECTOR3(ui->pos.x + sizex, ui->pos.y, 0.0f);
	//	ui->vertex[2].vtx = D3DXVECTOR3(ui->pos.x, ui->pos.y + sizey, 0.0f);
	//	ui->vertex[3].vtx = D3DXVECTOR3(ui->pos.x + sizex, ui->pos.y + sizey, 0.0f);

	//}

	//// HPバー
	// if (no == UI_EHP)
	//{
	//	// 頂点座標の設定
	//	ui->vertex[0].vtx = D3DXVECTOR3(ui->pos.x - sizex, ui->pos.y, 0.0f);
	//	ui->vertex[1].vtx = D3DXVECTOR3(ui->pos.x, ui->pos.y, 0.0f);
	//	ui->vertex[2].vtx = D3DXVECTOR3(ui->pos.x - sizex, ui->pos.y + sizey, 0.0f);
	//	ui->vertex[3].vtx = D3DXVECTOR3(ui->pos.x, ui->pos.y + sizey, 0.0f);


	//}

	// HPバー
	if (no == UI_HP)
	{

		// 現在のHPゲージ割り出し
		Hsize = (UI_HP_SIZE_X / PLAYER_HP_MAX)*player->hp;

		// 頂点座標の設定
		ui->vertex[0].vtx = D3DXVECTOR3(ui->pos.x, ui->pos.y, 0.0f);
		ui->vertex[1].vtx = D3DXVECTOR3(ui->pos.x + Hsize, ui->pos.y, 0.0f);
		ui->vertex[2].vtx = D3DXVECTOR3(ui->pos.x, ui->pos.y + UI_HP_SIZE_Y, 0.0f);
		ui->vertex[3].vtx = D3DXVECTOR3(ui->pos.x + Hsize, ui->pos.y + UI_HP_SIZE_Y, 0.0f);

	}

	// HPバーエフェクト
	else if (no == UI_HP_EFFECT)
	{
		// 現在のHPゲージ割り出し
		Hsize = (UI_HP_SIZE_X / PLAYER_HP_MAX)*player->hp;

		// 頂点座標の設定
		ui->vertex[0].vtx = D3DXVECTOR3(ui->pos.x, ui->pos.y, 0.0f);
		ui->vertex[1].vtx = D3DXVECTOR3(ui->pos.x + Hsize, ui->pos.y, 0.0f);
		ui->vertex[2].vtx = D3DXVECTOR3(ui->pos.x, ui->pos.y + UI_HP_SIZE_Y, 0.0f);
		ui->vertex[3].vtx = D3DXVECTOR3(ui->pos.x + Hsize, ui->pos.y + UI_HP_SIZE_Y, 0.0f);


		// 反射光の設定
		ui->vertex[0].diffuse = D3DCOLOR_RGBA(255, 0, 0, ui->effect);
		ui->vertex[1].diffuse = D3DCOLOR_RGBA(255, 0, 0, ui->effect);
		ui->vertex[2].diffuse = D3DCOLOR_RGBA(255, 0, 0, ui->effect);
		ui->vertex[3].diffuse = D3DCOLOR_RGBA(255, 0, 0, ui->effect);

	}

	 // エネミ－HPバー
	 if (no == UI_EHP)
	 {

	 	// 現在のHPゲージ割り出し
	 	Esize = (UI_HP_SIZE_X / ENEMY_HP_MAX)*enemy->hp;

	 	// 頂点座標の設定
		ui->vertex[0].vtx = D3DXVECTOR3(ui->pos.x - Esize, ui->pos.y, 0.0f);
	 	ui->vertex[1].vtx = D3DXVECTOR3(ui->pos.x, ui->pos.y, 0.0f);
	 	ui->vertex[2].vtx = D3DXVECTOR3(ui->pos.x - Esize, ui->pos.y + UI_HP_SIZE_Y, 0.0f);
		ui->vertex[3].vtx = D3DXVECTOR3(ui->pos.x, ui->pos.y + UI_HP_SIZE_Y, 0.0f);

	 }

	 // エネミ－HPバーエフェクト
	else if (no == UI_EHP_EFFECT)
	{
		// 現在のHPゲージ割り出し
		Esize = (UI_HP_SIZE_X / ENEMY_HP_MAX)*enemy->hp;

		// 頂点座標の設定
		ui->vertex[0].vtx = D3DXVECTOR3(ui->pos.x - Esize, ui->pos.y, 0.0f);
		ui->vertex[1].vtx = D3DXVECTOR3(ui->pos.x, ui->pos.y, 0.0f);
		ui->vertex[2].vtx = D3DXVECTOR3(ui->pos.x - Esize, ui->pos.y + UI_HP_SIZE_Y, 0.0f);
		ui->vertex[3].vtx = D3DXVECTOR3(ui->pos.x, ui->pos.y + UI_HP_SIZE_Y, 0.0f);

		// 反射光の設定
		ui->vertex[0].diffuse = D3DCOLOR_RGBA(0, 255, 255, ui->effect);
		ui->vertex[1].diffuse = D3DCOLOR_RGBA(0, 255, 255, ui->effect);
		ui->vertex[2].diffuse = D3DCOLOR_RGBA(0, 255, 255, ui->effect);
		ui->vertex[3].diffuse = D3DCOLOR_RGBA(0, 255, 255, ui->effect);

	}


}

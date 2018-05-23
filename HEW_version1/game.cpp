//=============================================================================
//
// ゲーム画面処理 [game.cpp]
// Author : 眞戸原史也
// プログラム作成日 : 2018/3/09
//
//=============================================================================

#include "game.h"				// マクロ使用の為
#include "input.h"				// 関数使用の為
#include "light.h"				// 同上
#include "camera.h"				// 同上
#include "field.h"				// 同上
#include "shadow.h"				// 同上
#include "player.h"				// 同上
#include "player_gun.h"			// 同上
#include "player_cursor.h"		// 同上
#include "player_bullet.h"		// 同上
#include "player_skillNor.h"	// 同上
#include "player_skillDef.h"	// 同上
#include "player_skillSup.h"	// 同上
#include "enemy.h"				// 同上
#include "enemy_gun.h"			// 同上
#include "enemy_cursor.h"		// 同上
#include "enemy_bullet.h"		// 同上
#include "enemy_skillNor.h"		// 同上
#include "enemy_skillDef.h"		// 同上
#include "enemy_skillSup.h"		// 同上
#include "effect.h"				// 同上
#include "noize.h"				// 同上
#include "checkhit.h"			// 同上
#include "ui.h"					// 同上
#include "timer.h"				// 同上
#include "debugproc.h"			// 同上
#include "sound.h"				// 同上
#include "fade.h"				// 同上
#include "call.h"				// 同上
#include "title.h"				// 同上
#include "menu.h"				// 同上
#include "result.h"				// 同上

//*****************************************************************************
// グローバル変数:
//*****************************************************************************

bool menuflag;						// ポーズメニュー制御変数

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT InitGame(int type)
{
	
	// ポーズフラグの初期化(false:未使用)
	menuflag = false;

	// ライトの初期化処理
	InitLight();

	// カメラの初期化処理
	InitCamera();

	// 地面の初期化
	InitField(type);
		
	// shadowの初期化処理
	InitShadow();

	// プレイヤーの初期化処理
	InitPlayer();

	// プレイヤーガンの初期化処理
	InitPlayerGun();

	// エネミーの初期化処理
	InitEnemy();

	// エネミーガンの初期化処理
	InitEnemyGun();

	// プレイヤーカーソルの初期化処理
	InitCursorPlayer();

	// エネミーカーソルの初期化処理
	InitCursorEnemy();

	// 弾の初期化処理
	InitPlayerBullet();
	InitEnemyBullet();

	// 弾(ワーム)の初期化処理
	InitPlayerNorSkill();
	InitEnemyNorSkill();

	// 弾(カスケード)の初期化処理
	InitPlayerSkillDef();
	InitEnemySkillDef();

	// 弾(スペシャル)の初期化処理
	InitPlayerSupSkill();
	InitEnemySupSkill();

	// エフェクトの初期化処理
	InitEffect();

	// ヒットエフェクトの初期化処理
	InitNoize();

	// UIの初期化処理
	InitUi(type);

	// タイマー初期化処理
	InitTimer(type);

	// デバッグメッセージの初期化処理
	InitDebugProc();

	// フェードの初期化処理
	InitFade();

	// コールの初期化処理
	InitCall(type);

	// タイトルの初期化処理
	InitTitle(type);

	// メニューの初期化処理
	InitMenu(type);

	// リザルトの初期化処理
	InitResult(type);

	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void UninitGame(void)
{

	// 入力の終了処理
	UninitInput();

	// ライトの終了処理
	UninitLight();

	// カメラの終了処理
	UninitCamera();

	// 地面の終了処理
	UninitField();

	// shadowの終了処理
	UninitShadow();

	// プレイヤーの終了処理
	UninitPlayer();

	// プレイヤーガンの終了処理
	UninitPlayerGun();

	// エネミーの終了処理
	UninitEnemy();

	// エネミーガンの終了処理
	UninitEnemyGun();

	// プレイヤーカーソルの終了処理
	UninitCursorPlayer();

	// エネミーカーソルの終了処理
	UninitCursorEnemy();

	// 弾の終了処理
	UninitPlayerBullet();
	UninitEnemyBullet();

	// 弾(ワーム)の終了処理
	UninitPlayerNorSkill();
	UninitEnemyNorSkill();

	// 弾(カスケード)の終了処理
	UninitPlayerSkillDef();
	UninitEnemySkillDef();

	// 弾(スペシャル)の終了処理
	UninitPlayerSupSkill();
	UninitEnemySupSkill();

	// エフェクトの終了処理
	UninitEffect();

	// ヒットエフェクトの終了処理
	UninitNoize();

	// UIの終了処理
	UninitUi();

	// タイマーの終了処理
	UninitTimer();

	// デバッグメッセージの終了処理
	UninitDebugProc();

	// サウンドの終了処理
	UninitSound();

	// フェードの終了処理
	UninitFade();

	// コールの終了処理
	UninitCall();

	// タイトルの終了処理
	UninitTitle();

	// メニューの終了処理
	UninitMenu();

	// リザルトの終了処理
	UninitResult();
	
}

//=============================================================================
// 更新処理関数
//=============================================================================
void UpdateGame(void)
{


	bool *start = GetStartFlag();

	if (*start == false)
	{

		// ライトの更新処理
		UpdateLight();

		// カメラの更新処理
		UpdateCamera();

		// 地形の更新処理
		UpdateField();

		// shadowの更新処理
		UpdateShadow();

		UpdateCall();

		// UIの更新処理
		UpdateUi();

	}

	else if(*start == true)
	{

		// Gを押したらポーズ
		if ((GetKeyboardPress(DIK_G)) || (IsButtonTriggered(0, BUTTON_START)))
		{
			menuflag = true;				// ポーズのフラグを使用に
		}



		// ゲーム中
		if (menuflag == false)
		{

			// ライトの更新処理
			UpdateLight();

			// カメラの更新処理
			UpdateCamera();

			// 地形の更新処理
			UpdateField();

			// shadowの更新処理
			UpdateShadow();

			// プレイヤーの更新処理
			UpdatePlayer();

			// プレイヤーガンの更新処理
			UpdatePlayerGun();

			//　エネミーの更新処理
			UpdateEnemy();

			// エネミーガンの更新処理
			UpdateEnemyGun();

			// プレイヤーカーソルの更新処理
			UpdateCursorPlayer();

			// エネミーカーソルの更新処理
			UpdateCursorEnemy();

			// 弾の更新処理
			UpdatePlayerBullet();
			UpdateEnemyBullet();

			// 弾(ワーム)の更新処理
			UpdatePlayerNorSkill();
			UpdateEnemyNorSkill();

			// 弾(カスケード)の更新処理
			UpdatePlayerSkillDef();
			UpdateEnemySkillDef();

			// 弾(スペシャル)の更新処理
			UpdatePlayerSupSkill();
			UpdateEnemySupSkill();

			// エフェクトの更新処理
			UpdateEffect();

			// ヒットエフェクトの更新処理
			UpdateNoize();

			// UIの更新処理
			UpdateUi();

			// タイマーの更新処理
			UpdateTimer();

			// 当たり判定処理
			CheckHitPaE();

		}

		// ポーズメニュー中
		else if (menuflag == true)
		{
			// ポーズメニューの更新処理
			UpdateMenu();
		}
	}
}

//=============================================================================
// 描画処理関数
//=============================================================================
void DrawGame(void)
{

	// カメラの設定処理
	SetCamera();

	// 地形の描画処理
	DrawField();

	// shadowの描画処理
	DrawShadow();

	// プレイヤーの描画処理
	DrawPlayer();

	// プレイヤーガンの描画処理
	DrawPlayerGun();

	// エネミーの描画処理
	DrawEnemy();

	// エネミーガンの描画処理
	DrawEnemyGun();

	// プレイヤーカーソルの描画処理
	DrawCursorPlayer();

	// エネミーカーソルの描画処理
	DrawCursorEnemy();

	// 弾の描画処理
	DrawPlayerBullet();
	DrawEnemyBullet();

	// 弾(ワーム)の描画処理
	DrawPlayerNorSkill();
	DrawEnemyNorSkill();

	// 弾(カスケード)の描画処理
	DrawPlayerSkillDef();
	DrawEnemySkillDef();

	// 弾(スペシャル)の描画処理
	DrawPlayerSupSkill();
	DrawEnemySupSkill();

	// エフェクトの描画処理
	DrawEffect();

	// ヒットエフェクトの描画処理
	DrawNoize();

	// UIの描画
	DrawUi();

	// タイマーの描画
	DrawTimer();

	// コールの描画処理
	DrawCall();

	// ポーズメニュー中
	if (menuflag == true)
	{
		// メニューの描画処理
		DrawMenu();
	}


//#ifdef _DEBUG
//	// デバッグメッセージ表示
//	DrawDebugProc();
//#endif
}

//=============================================================================
// ポーズフラグ取得関数
//=============================================================================
bool *GetMenu(void)
{
	return(&menuflag);
}

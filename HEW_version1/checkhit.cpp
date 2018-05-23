//=============================================================================
//
// 当たり判定処理 [checkhit.cpp]
// Author : 朱文渊
// プログラム作成日 : 2018/3/09
//
//=============================================================================
#include "checkhit.h"
#include "fade.h"
#include "noize.h"
#include "player.h"
#include "player_bullet.h"
#include "player_skillNor.h"
#include "player_skillDef.h"
#include "player_skillSup.h"
#include "enemy.h"
#include "enemy_bullet.h"
#include "enemy_skillNor.h"
#include "enemy_skillDef.h"
#include "enemy_skillSup.h"
#include "sound.h"
#include "result.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define DAMAGE_BULLET		(5)				// 通常弾のダメージ
#define DAMAGE_NORSK		(5)				// 特殊弾のダメージ

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
int			EdamageTimeCount = 50;			//ダメージ時間カウント
int			PdamageTimeCount = 50;			//同上
//*****************************************************************************
// 当たり判定処理
//*****************************************************************************
void CheckHitPaE(void)
{
	PLAYER *player = GetPlayer();
	ENEMY *enemy = GetEnemy();
	PLAYER_BULLET *playerbullet = GetPlayerBullet(0);
	ENEMY_BULLET *enemybullet = GetEnemyBullet(0);
	PLAYER_NORSKILL *playernorSkill = GetPlayerNorSkill(0);
	ENEMY_NORSKILL *enemynorSkill = GetEnemyNorSkill(0);
	PLAYER_SKILLDEF *playerskillDef = GetPlayerSkillDef(0);
	ENEMY_SKILLDEF *enemyskillDef = GetEnemySkillDef(0);
	PLAYER_SUPSKILL *playersupSkill = GetPlayerSupSkill(0);
	ENEMY_SUPSKILL *enemysupSkill = GetEnemySupSkill(0);
	bool *win = GetWinFlag();

	int oldhp, oldehp;
	bool pflag, eflag;

	oldhp = player->hp;
	oldehp = enemy->hp;
	pflag = true;
	eflag = true;

	//通常弾の当たり判定
	for (int i = 0; i < MAX_BULLET;i++, playerbullet++)
	{
		if (playerbullet->bUse)
		{
			if ((playerbullet->pos.z >= enemy->pos.z - 1.0f) || (playerbullet->pos.z <= enemy->pos.z + 1.0f))
			{
				if (CheckHitBC(enemy->pos, playerbullet->pos, 7.0f, 3.0f))
				{
					PlaySound(SE_HIT, E_DS8_FLAG_NONE);
					enemy->hp -= DAMAGE_BULLET;
					DeletePlayerBullet(i);
					SetNoize(enemy->pos, 20.0f, 20.0f, 1);

				}
			}

		}
	}

	for (int i = 0; i < MAX_BULLET;i++, enemybullet++)
	{
		if (enemybullet->bUse)
		{
			if ((enemybullet->pos.z >= player->pos.z - 1.0f) || (enemybullet->pos.z <= player->pos.z + 1.0f))
			{
				if (CheckHitBC(player->pos, enemybullet->pos, 7.0f, 3.0f))
				{
					PlaySound(SE_HIT, E_DS8_FLAG_NONE);
					player->hp -= DAMAGE_BULLET;
					DeleteEnemyBullet(i);
					SetNoize(player->pos, 20.0f, 20.0f, 0);
				}
			}
			
		}
	}

	//特殊弾01の当たり判定
	for (int i = 0; i < MAX_SKILLDEF;i++, playerskillDef++)
	{
		if (playerskillDef->bUse)
		{
			if ((playerskillDef->pos.z >= enemy->pos.z - 1.0f) || (playerskillDef->pos.z <= enemy->pos.z + 1.0f))
			{
				if (CheckHitBC(enemy->pos, playerskillDef->pos, 7.0f, SKILLDEF_SIZE_X / 2))
				{
					PlaySound(SE_HIT, E_DS8_FLAG_NONE);
					enemy->norSk = false;
					enemy->defSk = false;
					DeletePlayerSkillDef(i);
					SetNoize(enemy->pos, 20.0f, 20.0f, 1);

				}
			}

		}
	}

	for (int i = 0; i < MAX_SKILLDEF;i++, enemyskillDef++)
	{
		if (enemyskillDef->bUse)
		{
			if ((enemyskillDef->pos.z >= player->pos.z - 1.0f) || (enemyskillDef->pos.z <= player->pos.z + 1.0f))
			{
				if (CheckHitBC(player->pos, enemyskillDef->pos, 7.0f, SKILLDEF_SIZE_X / 2))
				{
					PlaySound(SE_HIT, E_DS8_FLAG_NONE);
					player->norSk = false;
					player->defSk = false;
					DeleteEnemySkillDef(i);
					SetNoize(player->pos, 20.0f, 20.0f, 0);
				}
			}

		}
	}

	//特殊弾02の当たり判定
	for (int i = 0; i < MAX_SUPSKILL;i++, playersupSkill++)
	{
		if (playersupSkill->bUse)
		{
			if ((playersupSkill->pos.z >= enemy->pos.z - 1.0f) || (playersupSkill->pos.z <= enemy->pos.z + 1.0f))
			{
				if (CheckHitBC(enemy->pos, playersupSkill->pos, 7.0f, 3.0f))
				{
					PlaySound(SE_HIT, E_DS8_FLAG_NONE);
					enemy->hp = 10.0f;
					DeletePlayerSupSkill(i);
					SetNoize(enemy->pos, 20.0f, 20.0f, 1);
				}
			}

		}
	}

	for (int i = 0; i < MAX_SUPSKILL;i++, enemysupSkill++)
	{
		if (enemysupSkill->bUse)
		{
			if ((enemysupSkill->pos.z >= player->pos.z - 1.0f) || (enemysupSkill->pos.z <= player->pos.z + 1.0f))
			{
				if (CheckHitBC(player->pos, enemysupSkill->pos, 7.0f, 3.0f))
				{
					PlaySound(SE_HIT, E_DS8_FLAG_NONE);
					player->hp = 10.0f;
					DeleteEnemySupSkill(i);
					SetNoize(player->pos, 20.0f, 20.0f, 0);
				}
			}

		}
	}

	//特殊弾03の当たり判定
	for (int i = 0; i < MAX_NORSKILL;i++, playernorSkill++)
	{
		if (playernorSkill->bUse)
		{
			if ((playernorSkill->pos.z >= enemy->pos.z - 1.0f) || (playernorSkill->pos.z <= enemy->pos.z + 1.0f))
			{
				if (CheckHitBC(enemy->pos, playernorSkill->pos, 7.0f, 2.0f))
				{
					PlaySound(SE_HIT, E_DS8_FLAG_NONE);
					enemy->damage = true;
					DeletePlayerNorSkill(i);
					SetNoize(enemy->pos, 20.0f, 20.0f, 1);

				}
			}
		}
	}
	if (enemy->damage)
	{
		EdamageTimeCount++;
		if (EdamageTimeCount % 60 == 0)
		{
			PlaySound(SE_HIT, E_DS8_FLAG_NONE);
			enemy->hp -= DAMAGE_NORSK;
			if (EdamageTimeCount == 300)
			{

				enemy->damage = false;
			}
		}
	}
	else if (enemy->damage == false)
	{
		EdamageTimeCount = 50;
	}

	for (int i = 0; i < MAX_NORSKILL;i++, enemynorSkill++)
	{
		if (enemynorSkill->bUse)
		{
			if ((enemynorSkill->pos.z >= player->pos.z - 1.0f) || (enemynorSkill->pos.z <= player->pos.z + 1.0f))
			{
				if (CheckHitBC(player->pos, enemynorSkill->pos, 7.0f, 2.0f))
				{
					PlaySound(SE_HIT, E_DS8_FLAG_NONE);
					player->damage = true;
					DeleteEnemyNorSkill(i);
					SetNoize(player->pos, 20.0f, 20.0f, 0);

				}
			}
		}
	}
	if (player->damage)
	{
		PdamageTimeCount++;
		if (PdamageTimeCount % 60 == 0)
		{
			PlaySound(SE_HIT, E_DS8_FLAG_NONE);
			player->hp -= DAMAGE_NORSK;
			if (PdamageTimeCount == 300)
			{

				player->damage = false;
			}
		}
	}
	else if (player->damage == false)
	{
		PdamageTimeCount = 50;
	}


	//HP減少処理
	if ((player->kill < 100)&&(pflag==true))
	{

		player->kill += (oldhp - player->hp);
	}

	else if (player->kill >= 100)
	{
		player->kill = 100;
		player->supSk = true;
		pflag = false;
	}

	if ((enemy->kill < 100) && (eflag == true))
	{

		enemy->kill += (oldehp - enemy->hp);
	}

	else if (enemy->kill >= 100)
	{
		enemy->kill = 100;
		enemy->supSk = true;
		eflag = false;
	}


	// どちらが倒れたら
	if ((player->hp <= 0) || (enemy->hp <= 0))
	{
		// プレイヤー勝利
		if (enemy->hp <= 0)
		{
			*win = true;
		}

		// エネミー勝利
		else if(player->hp <= 0)
		{
			*win = false;
		}

		// ステージ変数のリザルトの前にセット
		SetStage(STAGE_GAME_END);

		// 画面遷移:リザルト
		SetFade(FADE_OUT);

	}

}


//*****************************************************************************
// CheckHitBC処理
//*****************************************************************************
bool CheckHitBC(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float radius1, float radius2)
{
	//距離を求める
	D3DXVECTOR3 temp = pos1 - pos2;
	float fTempLengthSq = D3DXVec3LengthSq(&temp);
	if (fTempLengthSq <= (radius1 + radius2)*(radius1 + radius2))
	{
		//当たりなら
		return true;
	}
	return false;
}

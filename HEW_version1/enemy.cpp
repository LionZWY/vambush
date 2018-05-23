//=============================================================================
//
// エネミー処理 [enemy.cpp]
// Author : 朱文渊
// プログラム作成日 : 2018/3/09
//=============================================================================
#include "enemy.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "field.h"
#include "enemy_gun.h"
#include "enemy_bullet.h"
#include "enemy_skillNor.h"
#include "enemy_skillDef.h"
#include "enemy_skillSup.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexEnemy(LPDIRECT3DDEVICE9 pDevice);
void SetVertexEnemy(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureEnemyW = NULL;	// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureEnemyS = NULL;	// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureEnemyA = NULL;	// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureEnemyD = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffEnemy = NULL;	// 頂点バッファインターフェースへのポインタ

ENEMY			enemyWk[1];
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY *enemy = enemyWk;

		enemy->pos = D3DXVECTOR3(50.0f, 7.0f, 0.0f);
		enemy->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		enemy->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		enemy->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		enemy->hp = ENEMY_HP_MAX;
		enemy->kill = 0;
		enemy->damage = false;
		enemy->norSk = true;
		enemy->timeSk = 0;
		enemy->defSk = true;
		enemy->timeDefSk = 0;
		enemy->supSk = false;


		// 影の設定
		enemy->shadowId = CreateShadow(D3DXVECTOR3(enemy->pos.x + 3.0f, 0.1f, enemy->pos.z - 6.0f), D3DXVECTOR2(2.0f,1.0f));
		enemy->SizeShadow = D3DXVECTOR2(15.0f,15.0f);
		enemy->colShadow = D3DXCOLOR(50.0f, 50.0f, 50.0f, 50.0f);

		// 頂点情報の作成
		MakeVertexEnemy(pDevice);

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
			TEXTURE_ENEMY_W,			// ファイルの名前
			&g_pD3DTextureEnemyW);	// 読み込むメモリー
									// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
			TEXTURE_ENEMY_S,			// ファイルの名前
			&g_pD3DTextureEnemyS);	// 読み込むメモリー
									// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
			TEXTURE_ENEMY_A,			// ファイルの名前
			&g_pD3DTextureEnemyA);	// 読み込むメモリー
									// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
			TEXTURE_ENEMY_D,			// ファイルの名前
			&g_pD3DTextureEnemyD);	// 読み込むメモリー
	


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemy(void)
{
	if(g_pD3DTextureEnemyW != NULL)
	{// テクスチャの開放
		g_pD3DTextureEnemyW->Release();
		g_pD3DTextureEnemyW = NULL;
	}
	if (g_pD3DTextureEnemyS != NULL)
	{// テクスチャの開放
		g_pD3DTextureEnemyS->Release();
		g_pD3DTextureEnemyS = NULL;
	}
	if (g_pD3DTextureEnemyA != NULL)
	{// テクスチャの開放
		g_pD3DTextureEnemyA->Release();
		g_pD3DTextureEnemyA = NULL;
	}
	if (g_pD3DTextureEnemyD != NULL)
	{// テクスチャの開放
		g_pD3DTextureEnemyD->Release();
		g_pD3DTextureEnemyD = NULL;
	}


	if(g_pD3DVtxBuffEnemy != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffEnemy->Release();
		g_pD3DVtxBuffEnemy = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXVECTOR3 rotCamera;
	ENEMY *enemy = enemyWk;
	ENEMYGUN *enemygun = GetEnemyGun();
	ENEMY_NORSKILL *enemynorSkill = GetEnemyNorSkill(0);
	ENEMY_SKILLDEF *enemyskillDef = GetEnemySkillDef(0);
	ENEMY_SUPSKILL *enemysupSkill = GetEnemySupSkill(0);

	//移動の更新
	{
		if ((GetKeyboardPress(DIK_W)) || (IsButtonPressed(1, BUTTON_UP)))
		{
			enemy->move.z += 0.3f;
		}
		else if ((GetKeyboardPress(DIK_S)) || (IsButtonPressed(1, BUTTON_DOWN)))
		{
			enemy->move.z -= 0.3f;
		}
		if ((GetKeyboardPress(DIK_A)) || (IsButtonPressed(1, BUTTON_LEFT)))
		{
			enemy->move.x -= 0.3f;
		}
		else if ((GetKeyboardPress(DIK_D)) || (IsButtonPressed(1, BUTTON_RIGHT)))
		{
			enemy->move.x += 0.3f;
		}

		//if (GetKeyboardPress(DIK_LSHIFT))
		//{
		//	enemy->rot.y -= D3DX_PI * 0.02f;
		//}
		//else if (GetKeyboardPress(DIK_RSHIFT))
		//{
		//	enemy->rot.y += D3DX_PI * 0.02f;
		//}

		//回転角度のリセット
		if (enemy->rot.y > D3DX_PI)
		{
			// 360度を超えたら360度を引く
			enemy->rot.y -= D3DX_PI * 2.0f;
		}
		else if (enemy->rot.y < D3DX_PI)
		{
			// 360度を超えたら360度を引く
			enemy->rot.y += D3DX_PI * 2.0f;
		}

		enemy->pos.x += enemy->move.x;
		enemy->pos.z += enemy->move.z;

		enemy->move.x += (0.0f - enemy->move.x) * RATE_REGIST_ENEMY;
		enemy->move.z += (0.0f - enemy->move.z) * RATE_REGIST_ENEMY;
	}

	//移動範囲の設定
	if (enemy->pos.x < (ENEMY_SIZE_X / 2) - FIELD_SCL_MAX_X)
	{
		enemy->pos.x = (ENEMY_SIZE_X / 2) - FIELD_SCL_MAX_X;
	}
	if (enemy->pos.x > FIELD_SCL_MAX_X - (ENEMY_SIZE_X / 2))
	{
		enemy->pos.x = FIELD_SCL_MAX_X - (ENEMY_SIZE_X / 2);
	}
	if (enemy->pos.z > FIELD_SCL_MAX_Z)
	{
		enemy->pos.z = FIELD_SCL_MAX_Z;
	}
	if (enemy->pos.z < (ENEMY_SIZE_Y / 2) - FIELD_SCL_MAX_Z)
	{
		enemy->pos.z = (ENEMY_SIZE_Y / 2) - FIELD_SCL_MAX_Z;
	}

	//攻撃処理
	//通常弾
	if ((GetKeyboardTrigger(DIK_RALT)) || (IsButtonTriggered(1, BUTTON_Z)))
	{

		PlaySound(SE_BULLET, E_DS8_FLAG_NONE);

		D3DXVECTOR3 pos;
		D3DXVECTOR3 move;
		D3DXVECTOR2 size;

		pos.x = enemy->pos.x - sinf(enemy->rot.y)* 2.0f;
		pos.y = enemy->pos.y;
		pos.z = enemy->pos.z - cosf(enemy->rot.y)* 2.0f;

		move.x = -sinf(enemygun->rot.y) * 7.5f;
		move.y = 0.0f;
		move.z = -cosf(enemygun->rot.y) * 7.5f;

		size.x = 10.0f;
		size.y = 10.0f;
		SetEnemyBullet(pos, move, size, 60 * 4);
	}

	//特殊弾03
	if (enemy->norSk == true)
	{
		if ((GetKeyboardTrigger(DIK_U)) || (IsButtonTriggered(1, BUTTON_Y)))
		{

			PlaySound(SE_WARM, E_DS8_FLAG_NONE);

			D3DXVECTOR3 pos;
			D3DXVECTOR3 move;
			D3DXVECTOR2 size;

			pos.x = enemy->pos.x;
			pos.y = enemy->pos.y + 2.0f;
			pos.z = enemy->pos.z;

			move.x = -sinf(enemygun->rot.y) * 0.03f;
			move.y = 0.0f;
			move.z = -cosf(enemygun->rot.y) * 0.03f;

			size.x = 8.0f;
			size.y = 8.0f;
			SetEnemyNorSkill(pos, move, size, 60 * 40, EB_TYPE_NORMAL);
			enemy->norSk = false;

		}
		enemy->timeSk = 0;
	}
	else
	{
		enemy->timeSk++;
		if (enemy->timeSk / 300)
		{
			enemy->norSk = true;
		}

		if (enemynorSkill->cnt == 0)
		{
			enemy->norSk = false;
		}

	}
	//特殊弾01
	if (enemy->defSk == true)
	{
		if ((GetKeyboardTrigger(DIK_V)) || (IsButtonTriggered(1, BUTTON_L)))
		{

			PlaySound(SE_CASCEDE, E_DS8_FLAG_NONE);

			D3DXVECTOR3 pos;
			D3DXVECTOR3 move;
			D3DXVECTOR2 size;
			int time = 0;

			pos.x = enemy->pos.x;
			pos.y = enemy->pos.y + 2.0f;
			pos.z = enemy->pos.z;

			move.x = -sinf(enemygun->rot.y) * 2.0f;
			move.y = 0.0f;
			move.z = -cosf(enemygun->rot.y) * 2.0f;

			size.x = 30.0f;
			size.y = 30.0f;

			SetEnemySkillDef(pos, move, size, 60 * 40);

			enemy->defSk = false;

		}
		enemy->timeDefSk = 0;
	}
	else
	{
		enemy->timeDefSk++;
		if (enemy->timeDefSk / 300)
		{
			enemy->defSk = true;
		}

		if (enemyskillDef->cnt == 0)
		{
			enemy->defSk = false;
		}

	}
	//特殊弾02
	if (enemy->supSk == true)
	{
		if ((GetKeyboardTrigger(DIK_P)) || (IsButtonTriggered(1, BUTTON_R)))
		{

			PlaySound(SE_FLAME, E_DS8_FLAG_NONE);

			D3DXVECTOR3 pos;
			D3DXVECTOR3 move;
			D3DXVECTOR2 size;

			pos.x = enemy->pos.x;
			pos.y = enemy->pos.y + 2.0f;
			pos.z = enemy->pos.z;

			move.x = -sinf(enemygun->rot.y) * 10.0f;
			move.y = 0.0f;					  
			move.z = -cosf(enemygun->rot.y) * 10.0f;

			size.x = 10.0f;
			size.y = 10.0f;
			SetEnemySupSkill(pos, move, size, 60 * 40);
			enemy->supSk = false;

		}
	}

	{// 影の設定
		SetPositionShadow(enemy->shadowId, D3DXVECTOR3(enemy->pos.x + 1.0f, 0.1f, enemy->pos.z - 6.0f));

		SetVertexShadow(enemy->shadowId, enemy->SizeShadow);
		SetColorShadow(enemy->shadowId, enemy->colShadow);
	}

	// 頂点情報の作成
	MakeVertexEnemy(pDevice);

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxscl, mtxTranslate,mtxRot;
	ENEMY *enemy = enemyWk;
	ENEMYGUN *enemygun = GetEnemyGun();

		// ラインティングを無効にする
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

		// ビューマトリックスを取得
		mtxView = GetMtxView();

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&enemy->world);

		// ポリゴンを正面に向ける
		enemy->world._11 = mtxView._11;
		enemy->world._12 = mtxView._21;
		enemy->world._13 = mtxView._31;
		enemy->world._22 = mtxView._22;
		enemy->world._23 = mtxView._32;
		enemy->world._33 = mtxView._33;
		enemy->world._32 = mtxView._23;
		enemy->world._31 = mtxView._13;
		enemy->world._21 = mtxView._12;

		// スケールを反映
		D3DXMatrixScaling(&mtxscl, enemy->scl.x,
			enemy->scl.y,
			enemy->scl.z);
		D3DXMatrixMultiply(&enemy->world,
			&enemy->world, &mtxscl);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, enemy->rot.y, enemy->rot.x, enemy->rot.z);
		D3DXMatrixMultiply(&enemy->world, &enemy->world, &mtxRot);


		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, enemy->pos.x,
			enemy->pos.y,
			enemy->pos.z);
		D3DXMatrixMultiply(&enemy->world,
			&enemy->world, &mtxTranslate);



		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &enemy->world);

		// 頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, g_pD3DVtxBuffEnemy, 0, sizeof(VERTEX_3D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		//テクスチャの更新
		if (((enemygun->rot.y > -D3DX_PI * 0.25f) && (enemygun->rot.y <= D3DX_PI * 0.25f)) || ((enemygun->rot.y < D3DX_PI * 0.25f) && (enemygun->rot.y >= -D3DX_PI * 0.25f)))
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_pD3DTextureEnemyS);
		}
		else if (((enemygun->rot.y > D3DX_PI * 0.25f) && (enemygun->rot.y <= D3DX_PI * 0.75f)) || ((enemygun->rot.y < -D3DX_PI * 1.25f) && (enemygun->rot.y >= -D3DX_PI * 1.75f)))
		{
			if ((enemygun->rot.y > D3DX_PI * 0.5f) || (enemygun->rot.y < -D3DX_PI * 1.5f))
			{
				// テクスチャの設定
				pDevice->SetTexture(0, g_pD3DTextureEnemyD);
			}
			else
			{
				// テクスチャの設定
				pDevice->SetTexture(0, g_pD3DTextureEnemyA);
			}
		}
		else if (((enemygun->rot.y > D3DX_PI * 0.75f) && (enemygun->rot.y <= D3DX_PI * 1.25f)) || ((enemygun->rot.y < -D3DX_PI * 0.75f) && (enemygun->rot.y >= -D3DX_PI * 1.25f)))
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_pD3DTextureEnemyW);
		}
		else if (((enemygun->rot.y > D3DX_PI * 1.25f) && (enemygun->rot.y <= D3DX_PI * 1.75f)) || ((enemygun->rot.y < -D3DX_PI * 0.25f) && (enemygun->rot.y >= -D3DX_PI * 0.75f)))
		{
			if ((enemygun->rot.y >= D3DX_PI * 1.5f) || (enemygun->rot.y <= -D3DX_PI * 0.5f))
			{
				// テクスチャの設定
				pDevice->SetTexture(0, g_pD3DTextureEnemyD);
			}
			else
			{
				// テクスチャの設定
				pDevice->SetTexture(0, g_pD3DTextureEnemyA);
			}

		}

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

		// ラインティングを有効にする
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
HRESULT MakeVertexEnemy(LPDIRECT3DDEVICE9 pDevice)
{
	ENEMY *enemy = enemyWk;
	ENEMYGUN *enemygun = GetEnemyGun();
	// オブジェクトの頂点バッファを生成
    if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
												FVF_VERTEX_3D,				// 使用する頂点フォーマット
												D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
												&g_pD3DVtxBuffEnemy,	// 頂点バッファインターフェースへのポインタ
												NULL)))						// NULLに設定
	{
        return E_FAIL;
	}

	{
		SetVertexEnemy();

		// 法線の設定
		enemy->vectex[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		enemy->vectex[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		enemy->vectex[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		enemy->vectex[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// 反射光の設定
		enemy->vectex[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		enemy->vectex[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		enemy->vectex[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		enemy->vectex[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		if (((enemygun->rot.y > D3DX_PI * 0.25f) && (enemygun->rot.y <= D3DX_PI * 0.75f)) || ((enemygun->rot.y < -D3DX_PI * 1.25f) && (enemygun->rot.y >= -D3DX_PI * 1.75f)))
		{
			// テクスチャ座標の設定
			enemy->vectex[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			enemy->vectex[3].tex = D3DXVECTOR2(0.0f, 0.0f);
			enemy->vectex[0].tex = D3DXVECTOR2(1.0f, 1.0f);
			enemy->vectex[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		}
		else
		{
			// テクスチャ座標の設定
			enemy->vectex[0].tex = D3DXVECTOR2(0.0f, 1.0f);
			enemy->vectex[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			enemy->vectex[2].tex = D3DXVECTOR2(1.0f, 1.0f);
			enemy->vectex[3].tex = D3DXVECTOR2(1.0f, 0.0f);
		}


		// 頂点データをアンロックする
		g_pD3DVtxBuffEnemy->Unlock();
	}

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexEnemy(void)
{
	ENEMY *enemy = enemyWk;
	{	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffEnemy->Lock(0, 0, (void**)&enemy->vectex, 0);

		enemy->vectex[0].vtx = D3DXVECTOR3(-ENEMY_SIZE_X / 2, -ENEMY_SIZE_X / 2, 0.0f);
		enemy->vectex[1].vtx = D3DXVECTOR3(-ENEMY_SIZE_X / 2, ENEMY_SIZE_X / 2, 0.0f);
		enemy->vectex[2].vtx = D3DXVECTOR3(ENEMY_SIZE_X / 2, -ENEMY_SIZE_X / 2, 0.0f);
		enemy->vectex[3].vtx = D3DXVECTOR3(ENEMY_SIZE_X / 2, ENEMY_SIZE_X / 2, 0.0f);

		//// 頂点データをアンロックする
		//g_pD3DVtxBuffEnemy->Unlock();
	}
}

ENEMY *GetEnemy(void)
{
	return enemyWk;
}
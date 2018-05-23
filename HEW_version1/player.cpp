//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : 朱文渊
// プログラム作成日 : 2018/3/09
//=============================================================================
#include "player.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "field.h"
#include "player_cursor.h"
#include "player_gun.h"
#include "player_bullet.h"
#include "player_skillNor.h"
#include "player_skillDef.h"
#include "player_skillSup.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexPlayer(LPDIRECT3DDEVICE9 pDevice);
void SetVertexPlayer(void);
void SetTexturePlayer(int cntPattern);
//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTexturePlayerW = NULL;	// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTexturePlayerS = NULL;	// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTexturePlayerA = NULL;	// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTexturePlayerD = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffPlayer = NULL;	// 頂点バッファインターフェースへのポインタ

PLAYER			playerWk[1];
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER *player = playerWk;

	player->pos = D3DXVECTOR3(-50.0f, 7.0f, 0.0f);
	player->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	player->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	player->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	player->hp = PLAYER_HP_MAX;
	player->kill = 0;
	player->damage = false;
	player->norSk = true;
	player->timeSk = 0;
	player->defSk = true;
	player->timeDefSk = 0;
	player->supSk = false;
	//player->patternAnim = 1;

	// 影の設定
	player->shadowId = CreateShadow(D3DXVECTOR3(player->pos.x + 3.0f,0.1f,player->pos.z - 6.0f),D3DXVECTOR2(2.0f,1.0f));
	player->SizeShadow = D3DXVECTOR2(10.0f,10.0f);
	player->colShadow = D3DXCOLOR(50.0f, 50.0f, 50.0f, 50.0f);

	// 頂点情報の作成
	MakeVertexPlayer(pDevice);
	


	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
								TEXTURE_PLAYER_W,			// ファイルの名前
								&g_pD3DTexturePlayerW);	// 読み込むメモリー
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
								TEXTURE_PLAYER_S,			// ファイルの名前
								&g_pD3DTexturePlayerS);	// 読み込むメモリー
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
								TEXTURE_PLAYER_A,			// ファイルの名前
								&g_pD3DTexturePlayerA);	// 読み込むメモリー
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
								TEXTURE_PLAYER_D,			// ファイルの名前
								&g_pD3DTexturePlayerD);	// 読み込むメモリー


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{
	if(g_pD3DTexturePlayerW != NULL)
	{// テクスチャの開放
		g_pD3DTexturePlayerW->Release();
		g_pD3DTexturePlayerW = NULL;
	}
	if (g_pD3DTexturePlayerS != NULL)
	{// テクスチャの開放
		g_pD3DTexturePlayerS->Release();
		g_pD3DTexturePlayerS = NULL;
	}
	if (g_pD3DTexturePlayerA != NULL)
	{// テクスチャの開放
		g_pD3DTexturePlayerA->Release();
		g_pD3DTexturePlayerA = NULL;
	}
	if (g_pD3DTexturePlayerD != NULL)
	{// テクスチャの開放
		g_pD3DTexturePlayerD->Release();
		g_pD3DTexturePlayerD = NULL;
	}

	if(g_pD3DVtxBuffPlayer != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffPlayer->Release();
		g_pD3DVtxBuffPlayer = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXVECTOR3 rotCamera;
	PLAYER *player = playerWk;
	PLAYERGUN *playergun = GetPlayerGun();

	PLAYER_NORSKILL *playernorSkill = GetPlayerNorSkill(0);
	PLAYER_SKILLDEF *playerskillDef = GetPlayerSkillDef(0);
	PLAYER_SUPSKILL *playersupSkill = GetPlayerSupSkill(0);

	//移動の更新
	{
		if ((GetKeyboardPress(DIK_UP)) || (IsButtonPressed(0, BUTTON_UP)))
		{
			player->move.z += 0.3f;
		}
		else if ((GetKeyboardPress(DIK_DOWN)) || (IsButtonPressed(0, BUTTON_DOWN)))
		{
			player->move.z -= 0.3f;
		}
		if ((GetKeyboardPress(DIK_LEFT)) || (IsButtonPressed(0, BUTTON_LEFT)))
		{
			player->move.x -= 0.3f;
		}
		else if ((GetKeyboardPress(DIK_RIGHT)) || (IsButtonPressed(0, BUTTON_RIGHT)))
		{
			player->move.x += 0.3f;
		}
	}

	//if (GetKeyboardPress(DIK_LSHIFT))
	//{
	//	player->rot.y -= D3DX_PI * 0.02f;
	//}
	//else if (GetKeyboardPress(DIK_RSHIFT))
	//{
	//	player->rot.y += D3DX_PI * 0.02f;
	//}

	if (player->rot.y > D3DX_PI)
	{
		// 360度を超えたら360度を引く
		player->rot.y -= D3DX_PI * 2.0f;
	}
	else if (player->rot.y < D3DX_PI)
	{
		// 360度を超えたら360度を引く
		player->rot.y += D3DX_PI * 2.0f;
	}

	player->pos.x += player->move.x;
	player->pos.z += player->move.z;

	player->move.x += (0.0f - player->move.x) * RATE_REGIST_PLAYER;
	player->move.z += (0.0f - player->move.z) * RATE_REGIST_PLAYER;


	if (player->pos.x < (PLAYER_SIZE_X / 2) - FIELD_SCL_MAX_X)
	{
		player->pos.x = (PLAYER_SIZE_X / 2) - FIELD_SCL_MAX_X;
	}
	if (player->pos.x > FIELD_SCL_MAX_X - (PLAYER_SIZE_X / 2))
	{
		player->pos.x = FIELD_SCL_MAX_X - (PLAYER_SIZE_X / 2);
	}
	if (player->pos.z > FIELD_SCL_MAX_Z)
	{
		player->pos.z = FIELD_SCL_MAX_Z;
	}
	if (player->pos.z < (PLAYER_SIZE_Y / 2)- FIELD_SCL_MAX_Z)
	{
		player->pos.z = (PLAYER_SIZE_Y / 2) - FIELD_SCL_MAX_Z;
	}

	//攻撃処理
	//通常弾
	if ((GetKeyboardTrigger(DIK_SPACE)) || (IsButtonTriggered(0, BUTTON_Z)))
	{

		PlaySound(SE_BULLET, E_DS8_FLAG_NONE);

		D3DXVECTOR3 pos;
		D3DXVECTOR3 move;
		D3DXVECTOR2 size;

		pos.x = player->pos.x - sinf(player->rot.y)* 2.0f;
		pos.y = player->pos.y;
		pos.z = player->pos.z - cosf(player->rot.y)* 2.0f;

		move.x = -sinf(playergun->rot.y) * 7.5f;
		move.y = 0.0f;
		move.z = -cosf(playergun->rot.y) * 7.5f;

		size.x = 10.0f;
		size.y = 10.0f;
		SetPlayerBullet(pos, move, size, 60 * 4);
	}

	//特殊弾03
	if (player->norSk == true)
	{
		if ((GetKeyboardTrigger(DIK_C)) || (IsButtonTriggered(0, BUTTON_Y)))
		{

			PlaySound(SE_WARM, E_DS8_FLAG_NONE);

			D3DXVECTOR3 pos;
			D3DXVECTOR3 move;
			D3DXVECTOR2 size;

			pos.x = player->pos.x;
			pos.y = player->pos.y + 2.0f;
			pos.z = player->pos.z;

			move.x = -sinf(playergun->rot.y) * 0.03f;
			move.y = 0.0f;
			move.z = -cosf(playergun->rot.y) * 0.03f;

			size.x = 8.0f;
			size.y = 8.0f;
			SetPlayerNorSkill(pos, move, size, 60 * 40, PB_TYPE_NORMAL);
			player->norSk = false;

		}
		player->timeSk = 0;
	}
	else
	{
		player->timeSk++;
		if (player->timeSk / 300)
		{
			player->norSk = true;
		}

		if (playernorSkill->cnt == 0)
		{
			player->norSk = false;
		}
	}
	//特殊弾01
	if (player->defSk == true)
	{
		if ((GetKeyboardTrigger(DIK_V)) || (IsButtonTriggered(0, BUTTON_L)))
		{

			PlaySound(SE_CASCEDE, E_DS8_FLAG_NONE);

			D3DXVECTOR3 pos;
			D3DXVECTOR3 move;
			D3DXVECTOR2 size;
			int time = 0;

			pos.x = player->pos.x;
			pos.y = player->pos.y + 2.0f;
			pos.z = player->pos.z;

			move.x = -sinf(playergun->rot.y) * 2.0f;
			move.y = 0.0f;					   
			move.z = -cosf(playergun->rot.y) * 2.0f;

			size.x = 30.0f;
			size.y = 30.0f;

			SetPlayerSkillDef(pos, move, size, 60 * 40);

			player->defSk = false;

		}
		player->timeDefSk = 0;
	}
	else
	{
		player->timeDefSk++;
		if (player->timeDefSk / 300)
		{
			player->defSk = true;
		}

		if (playerskillDef->cnt == 0)
		{
			player->defSk = false;
		}

	}
	//特殊弾02
	if (player->supSk == true)
	{
		if ((GetKeyboardTrigger(DIK_P)) || (IsButtonTriggered(0, BUTTON_R)))
		{

			PlaySound(SE_FLAME, E_DS8_FLAG_NONE);

			D3DXVECTOR3 pos;
			D3DXVECTOR3 move;
			D3DXVECTOR2 size;

			pos.x = player->pos.x;
			pos.y = player->pos.y + 2.0f;
			pos.z = player->pos.z;

			move.x = -sinf(playergun->rot.y) * 10.0f;
			move.y = 0.0f;
			move.z = -cosf(playergun->rot.y) * 10.0f;

			size.x = 10.0f;
			size.y = 10.0f;
			SetPlayerSupSkill(pos, move, size, 60 * 40);
			player->supSk = false;

		}
	}

	{// 影の設定
		SetPositionShadow(player->shadowId, D3DXVECTOR3(player->pos.x + 1.0f, 0.1f, player->pos.z - 6.0f));

		SetVertexShadow(player->shadowId, player->SizeShadow);
		SetColorShadow(player->shadowId, player->colShadow);
	}

	MakeVertexPlayer(pDevice);

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxscl, mtxTranslate,mtxRot;
	PLAYER *player = playerWk;
	PLAYERGUN *playergun = GetPlayerGun();
	

	// αテストを有効に
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 150);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// ラインティングを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ビューマトリックスを取得
	mtxView = GetMtxView();

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&player->world);

	// ポリゴンを正面に向ける
	player->world._11 = mtxView._11;
	player->world._12 = mtxView._21;
	player->world._13 = mtxView._31;
	player->world._22 = mtxView._22;
	player->world._23 = mtxView._32;
	player->world._33 = mtxView._33;
	player->world._32 = mtxView._23;
	player->world._31 = mtxView._13;
	player->world._21 = mtxView._12;

	// スケールを反映
	D3DXMatrixScaling(&mtxscl, player->scl.x,
		player->scl.y,
		player->scl.z);
	D3DXMatrixMultiply(&player->world,
		&player->world, &mtxscl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, player->rot.y, player->rot.x, player->rot.z);
	D3DXMatrixMultiply(&player->world, &player->world, &mtxRot);


	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, player->pos.x,
		player->pos.y,
		player->pos.z);
	D3DXMatrixMultiply(&player->world,
		&player->world, &mtxTranslate);



	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &player->world);

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pD3DVtxBuffPlayer, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	if (((playergun->rot.y > -D3DX_PI * 0.25f) && (playergun->rot.y <= D3DX_PI * 0.25f)) || ((playergun->rot.y < D3DX_PI * 0.25f) && (playergun->rot.y >= -D3DX_PI * 0.25f)))
	{
		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTexturePlayerS);
	}
	else if (((playergun->rot.y > D3DX_PI * 0.25f) && (playergun->rot.y <= D3DX_PI * 0.75f)) || ((playergun->rot.y < -D3DX_PI * 1.25f) && (playergun->rot.y >= -D3DX_PI * 1.75f)))
	{
		if ((playergun->rot.y > D3DX_PI * 0.5f) || (playergun->rot.y < -D3DX_PI * 1.5f))
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_pD3DTexturePlayerD);
		}
		else
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_pD3DTexturePlayerA);
		}
	}
	else if (((playergun->rot.y > D3DX_PI * 0.75f) && (playergun->rot.y <= D3DX_PI * 1.25f)) || ((playergun->rot.y < -D3DX_PI * 0.75f) && (playergun->rot.y >= -D3DX_PI * 1.25f)))
	{
		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTexturePlayerW);
	}
	else if (((playergun->rot.y > D3DX_PI * 1.25f) && (playergun->rot.y <= D3DX_PI * 1.75f)) || ((playergun->rot.y < -D3DX_PI * 0.25f) && (playergun->rot.y >= -D3DX_PI * 0.75f)))
	{
		if ((playergun->rot.y > D3DX_PI * 1.5f) || (playergun->rot.y < -D3DX_PI * 0.5f))
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_pD3DTexturePlayerD);
		}
		else
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_pD3DTexturePlayerA);
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
HRESULT MakeVertexPlayer(LPDIRECT3DDEVICE9 pDevice)
{
	PLAYER *player = playerWk;
	PLAYERGUN *playergun = GetPlayerGun();
	// オブジェクトの頂点バッファを生成
    if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
												FVF_VERTEX_3D,				// 使用する頂点フォーマット
												D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
												&g_pD3DVtxBuffPlayer,	// 頂点バッファインターフェースへのポインタ
												NULL)))						// NULLに設定
	{
        return E_FAIL;
	}

	{
		SetVertexPlayer();

		// 法線の設定
		player->vectex[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		player->vectex[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		player->vectex[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		player->vectex[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// 反射光の設定
		player->vectex[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		player->vectex[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		player->vectex[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		player->vectex[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		if (((playergun->rot.y > D3DX_PI * 0.25f) && (playergun->rot.y <= D3DX_PI * 0.75f)) || ((playergun->rot.y < -D3DX_PI * 1.25f) && (playergun->rot.y >= -D3DX_PI * 1.75f)))
		{
			// テクスチャ座標の設定
			player->vectex[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			player->vectex[3].tex = D3DXVECTOR2(0.0f, 0.0f);
			player->vectex[0].tex = D3DXVECTOR2(1.0f, 1.0f);
			player->vectex[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		}
		else
		{
			// テクスチャ座標の設定
			player->vectex[0].tex = D3DXVECTOR2(0.0f, 1.0f);
			player->vectex[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			player->vectex[2].tex = D3DXVECTOR2(1.0f, 1.0f);
			player->vectex[3].tex = D3DXVECTOR2(1.0f, 0.0f);
		}

		// 頂点データをアンロックする
		g_pD3DVtxBuffPlayer->Unlock();
	}

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexPlayer(void)
{
	PLAYER *player = playerWk;
	{	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffPlayer->Lock(0, 0, (void**)&player->vectex, 0);

		player->vectex[0].vtx = D3DXVECTOR3(-PLAYER_SIZE_X / 2, -PLAYER_SIZE_X / 2, 0.0f);
		player->vectex[1].vtx = D3DXVECTOR3(-PLAYER_SIZE_X / 2, PLAYER_SIZE_X / 2, 0.0f);
		player->vectex[2].vtx = D3DXVECTOR3(PLAYER_SIZE_X / 2, -PLAYER_SIZE_X / 2, 0.0f);
		player->vectex[3].vtx = D3DXVECTOR3(PLAYER_SIZE_X / 2, PLAYER_SIZE_X / 2, 0.0f);

		//// 頂点データをアンロックする
		//g_pD3DVtxBuffPlayer->Unlock();
	}
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTexturePlayer(int cntPattern)
{
	PLAYER *player = playerWk;

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y;

	player->vectex[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	player->vectex[1].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	player->vectex[2].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
	player->vectex[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
}


PLAYER *GetPlayer(void)
{
	return playerWk;
}
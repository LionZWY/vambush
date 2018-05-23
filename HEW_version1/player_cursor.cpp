//=============================================================================
//
// カーソル処理 [Pcursor.cpp]
// Author : 朱文渊
// プログラム作成日 : 2018/3/09
//=============================================================================
#include "player_cursor.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "field.h"
#include "player.h"
#include "checkhit.h"
#include "enemy.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_CURSOR		"data/TEXTURE/カーソル.png"	// 読み込むテクスチャファイル名
#define	VALUE_MOVE_CURSOR	(0.30f)							// 移動速度
#define	VALUE_JUMP				(10.0f)							// ジャンプ力
#define	VALUE_GRAVITY			(0.45f)							// 重力
#define	RATE_REGIST				(0.075f)						// 抵抗係数
#define	RATE_REFRECT			(-0.90f)						// 反射係数
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexCursorPlayer(LPDIRECT3DDEVICE9 pDevice);
void SetVertexCursorPlayer(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureCursorPlayer = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffCursorPlayer = NULL;	// 頂点バッファインターフェースへのポインタ

CURSOR_PLAYER			PcursorWk[1];
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitCursorPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CURSOR_PLAYER *Pcursor = PcursorWk;
	CAMERA *camera = GetCamera();
	PLAYER *player = GetPlayer();

	Pcursor->pos = D3DXVECTOR3(0.0f, 7.0f, 0.0f);
	Pcursor->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	Pcursor->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Pcursor->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Pcursor->size = D3DXVECTOR2(5.0f, 5.0f);
	Pcursor->lock = false;


	float cVecX, cVecZ;
	cVecX = camera->posEye.x - Pcursor->pos.x;
	cVecZ = camera->posEye.z - Pcursor->pos.z;
	Pcursor->PCtoEPDistance = (sqrtf(cVecX * cVecX + cVecZ * cVecZ));



	// 頂点情報の作成
	MakeVertexCursorPlayer(pDevice);
	


	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
								TEXTURE_CURSOR,			// ファイルの名前
								&g_pD3DTextureCursorPlayer);	// 読み込むメモリー

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitCursorPlayer(void)
{
	if(g_pD3DTextureCursorPlayer != NULL)
	{// テクスチャの開放
		g_pD3DTextureCursorPlayer->Release();
		g_pD3DTextureCursorPlayer = NULL;
	}

	if(g_pD3DVtxBuffCursorPlayer != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffCursorPlayer->Release();
		g_pD3DVtxBuffCursorPlayer = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateCursorPlayer(void)
{
	D3DXVECTOR3 rotCamera;
	CURSOR_PLAYER *Pcursor = PcursorWk;
	CAMERA *camera = GetCamera();
	PLAYER *player = GetPlayer();
	ENEMY *enemy = GetEnemy();

	float cVecX, cVecZ;
	cVecX = camera->posEye.x - Pcursor->pos.x;
	cVecZ = camera->posEye.z - Pcursor->pos.z;
	Pcursor->PCtoEPDistance = (sqrtf(cVecX * cVecX + cVecZ * cVecZ));

	if (Pcursor->lock == false)
	{
		if ((GetKeyboardPress(DIK_I)) || (IsButtonPressed(0, R_BUTTON_UP)))
		{
			//Pcursor->lock = false;
			Pcursor->move.z += 0.5f;
		}
		else if ((GetKeyboardPress(DIK_K)) || (IsButtonPressed(0, R_BUTTON_DOWN)))
		{
			//Pcursor->lock = false;
			Pcursor->move.z -= 0.5f;
		}
		if ((GetKeyboardPress(DIK_J)) || (IsButtonPressed(0, R_BUTTON_LEFT)))
		{
			//Pcursor->lock = false;
			Pcursor->move.x -= 0.5f;
		}
		else if ((GetKeyboardPress(DIK_L)) || (IsButtonPressed(0, R_BUTTON_RIGHT)))
		{
			//Pcursor->lock = false;
			Pcursor->move.x += 0.5f;
		}

		if ((GetKeyboardPress(DIK_O)) || (IsButtonTriggered(0, BUTTON_R3)))
		{
			Pcursor->lock = true;
		}
	}
	else if (Pcursor->lock == true)
	{
		Pcursor->pos.x = enemy->pos.x;
		Pcursor->pos.z = enemy->pos.z;
		if (IsButtonTriggered(0, BUTTON_R3))
		{
			Pcursor->lock = false;
		}
	}

	if (Pcursor->rot.y > D3DX_PI)
	{
		// 360度を超えたら360度を引く
		Pcursor->rot.y -= D3DX_PI * 2.0f;
	}
	else if (Pcursor->rot.y < D3DX_PI)
	{
		// 360度を超えたら360度を引く
		Pcursor->rot.y += D3DX_PI * 2.0f;
	}

	Pcursor->pos.x += Pcursor->move.x;
	Pcursor->pos.z += Pcursor->move.z;

	Pcursor->move.x += (0.0f - Pcursor->move.x) * RATE_REGIST;
	Pcursor->move.z += (0.0f - Pcursor->move.z) * RATE_REGIST;

	Pcursor->size.x = (camera->EyeToAtDistance / 50.0f + (Pcursor->pos.z * 0.005f) + 15.0f);
	Pcursor->size.y = (camera->EyeToAtDistance / 50.0f + (Pcursor->pos.z * 0.005f) + 15.0f);

	if (Pcursor->pos.x < (Pcursor->size.x / 2) - FIELD_SCL_MAX_X)
	{
		Pcursor->pos.x = (Pcursor->size.x / 2) - FIELD_SCL_MAX_X;
	}
	if (Pcursor->pos.x > FIELD_SCL_MAX_X - (Pcursor->size.x / 2))
	{
		Pcursor->pos.x = FIELD_SCL_MAX_X - (Pcursor->size.x / 2);
	}
	if (Pcursor->pos.z > FIELD_SCL_MAX_Z)
	{
		Pcursor->pos.z = FIELD_SCL_MAX_Z;
	}
	if (Pcursor->pos.z < (Pcursor->size.y / 2)- FIELD_SCL_MAX_Z)
	{
		Pcursor->pos.z = (Pcursor->size.y / 2) - FIELD_SCL_MAX_Z;
	}

	SetVertexCursorPlayer();

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawCursorPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxscl, mtxTranslate,mtxRot;
	CURSOR_PLAYER *Pcursor = PcursorWk;

	// αテストを有効に
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 150);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// ラインティングを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ビューマトリックスを取得
	mtxView = GetMtxView();

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&Pcursor->world);

	// ポリゴンを正面に向ける
	Pcursor->world._11 = mtxView._11;
	Pcursor->world._12 = mtxView._21;
	Pcursor->world._13 = mtxView._31;
	Pcursor->world._22 = mtxView._22;
	Pcursor->world._23 = mtxView._32;
	Pcursor->world._33 = mtxView._33;
	Pcursor->world._32 = mtxView._23;
	Pcursor->world._31 = mtxView._13;
	Pcursor->world._21 = mtxView._12;

	// スケールを反映
	D3DXMatrixScaling(&mtxscl, Pcursor->scl.x,
		Pcursor->scl.y,
		Pcursor->scl.z);
	D3DXMatrixMultiply(&Pcursor->world,
		&Pcursor->world, &mtxscl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, Pcursor->rot.y, Pcursor->rot.x, Pcursor->rot.z);
	D3DXMatrixMultiply(&Pcursor->world, &Pcursor->world, &mtxRot);


	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, Pcursor->pos.x,
		Pcursor->pos.y,
		Pcursor->pos.z);
	D3DXMatrixMultiply(&Pcursor->world,
		&Pcursor->world, &mtxTranslate);



	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &Pcursor->world);

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pD3DVtxBuffCursorPlayer, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureCursorPlayer);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	// ラインティングを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
HRESULT MakeVertexCursorPlayer(LPDIRECT3DDEVICE9 pDevice)
{
	CURSOR_PLAYER *Pcursor = PcursorWk;
	// オブジェクトの頂点バッファを生成
    if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
												FVF_VERTEX_3D,				// 使用する頂点フォーマット
												D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
												&g_pD3DVtxBuffCursorPlayer,	// 頂点バッファインターフェースへのポインタ
												NULL)))						// NULLに設定
	{
        return E_FAIL;
	}

	{
		SetVertexCursorPlayer();

		// 法線の設定
		Pcursor->vectex[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		Pcursor->vectex[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		Pcursor->vectex[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		Pcursor->vectex[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// 反射光の設定
		Pcursor->vectex[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		Pcursor->vectex[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		Pcursor->vectex[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		Pcursor->vectex[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		Pcursor->vectex[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		Pcursor->vectex[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		Pcursor->vectex[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		Pcursor->vectex[3].tex = D3DXVECTOR2(1.0f, 0.0f);


		// 頂点データをアンロックする
		g_pD3DVtxBuffCursorPlayer->Unlock();
	}

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexCursorPlayer(void)
{
	CURSOR_PLAYER *Pcursor = PcursorWk;
	{	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffCursorPlayer->Lock(0, 0, (void**)&Pcursor->vectex, 0);

		Pcursor->vectex[0].vtx = D3DXVECTOR3(-Pcursor->size.x / 2, -Pcursor->size.x / 2, 0.0f);
		Pcursor->vectex[1].vtx = D3DXVECTOR3(-Pcursor->size.x / 2, Pcursor->size.x / 2, 0.0f);
		Pcursor->vectex[2].vtx = D3DXVECTOR3(Pcursor->size.x / 2, -Pcursor->size.x / 2, 0.0f);
		Pcursor->vectex[3].vtx = D3DXVECTOR3(Pcursor->size.x / 2, Pcursor->size.x / 2, 0.0f);

		//// 頂点データをアンロックする
		//g_pD3DVtxBuffCursor->Unlock();
	}
}

CURSOR_PLAYER *GetCursorPlayer(void)
{
	return PcursorWk;
}

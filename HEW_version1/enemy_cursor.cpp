//=============================================================================
//
// カーソル処理 [Ecursor.cpp]
// Author : 朱文渊
// プログラム作成日 : 2018/3/09
//=============================================================================
#include "enemy_cursor.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "field.h"
#include "enemy.h"
#include "checkhit.h"
#include "player.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_CURSOR			"data/TEXTURE/カーソル敵.png"		// 読み込むテクスチャファイル名
#define	VALUE_MOVE_CURSOR		(0.30f)							// 移動速度
#define	VALUE_JUMP				(10.0f)							// ジャンプ力
#define	VALUE_GRAVITY			(0.45f)							// 重力
#define	RATE_REGIST				(0.075f)						// 抵抗係数
#define	RATE_REFRECT			(-0.90f)						// 反射係数
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexCursorEnemy(LPDIRECT3DDEVICE9 pDevice);
void SetVertexCursorEnemy(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureCursorEnemy = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffCursorEnemy = NULL;	// 頂点バッファインターフェースへのポインタ

CURSOR_ENEMY			EcursorWk[1];
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitCursorEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CURSOR_ENEMY *Ecursor = EcursorWk;
	CAMERA *camera = GetCamera();
	ENEMY *enemy = GetEnemy();

	Ecursor->pos = D3DXVECTOR3(10.0f, 7.0f, 0.0f);
	Ecursor->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	Ecursor->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Ecursor->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Ecursor->size = D3DXVECTOR2(5.0f, 5.0f);
	Ecursor->lock = false;

	//カメラの視点とカーソルの距離計算
	float cVecX, cVecZ;
	cVecX = camera->posEye.x - Ecursor->pos.x;
	cVecZ = camera->posEye.z - Ecursor->pos.z;
	Ecursor->ECtoEPDistance = (sqrtf(cVecX * cVecX + cVecZ * cVecZ));



	// 頂点情報の作成
	MakeVertexCursorEnemy(pDevice);
	


	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
								TEXTURE_CURSOR,			// ファイルの名前
								&g_pD3DTextureCursorEnemy);	// 読み込むメモリー

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitCursorEnemy(void)
{
	if(g_pD3DTextureCursorEnemy != NULL)
	{// テクスチャの開放
		g_pD3DTextureCursorEnemy->Release();
		g_pD3DTextureCursorEnemy = NULL;
	}

	if(g_pD3DVtxBuffCursorEnemy != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffCursorEnemy->Release();
		g_pD3DVtxBuffCursorEnemy = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateCursorEnemy(void)
{
	D3DXVECTOR3 rotCamera;
	CURSOR_ENEMY *Ecursor = EcursorWk;
	CAMERA *camera = GetCamera();
	ENEMY *enemy = GetEnemy();
	PLAYER *player = GetPlayer();

	//カメラの視点とカーソルの距離更新
	float cVecX, cVecZ;
	cVecX = camera->posEye.x - Ecursor->pos.x;
	cVecZ = camera->posEye.z - Ecursor->pos.z;
	Ecursor->ECtoEPDistance = (sqrtf(cVecX * cVecX + cVecZ * cVecZ));

	//カーソルロック処理
	if (Ecursor->lock == false)
	{
		if ((GetKeyboardPress(DIK_T)) || (IsButtonPressed(1, R_BUTTON_UP)))
		{
			//Ecursor->lock = false;
			Ecursor->move.z += 0.35f;
		}
		else if ((GetKeyboardPress(DIK_G)) || (IsButtonPressed(1, R_BUTTON_DOWN)))
		{
			//Ecursor->lock = false;
			Ecursor->move.z -= 0.35f;
		}
		if ((GetKeyboardPress(DIK_F)) || (IsButtonPressed(1, R_BUTTON_LEFT)))
		{
			//Ecursor->lock = false;
			Ecursor->move.x -= 0.35f;
		}
		else if ((GetKeyboardPress(DIK_H)) || (IsButtonPressed(1, R_BUTTON_RIGHT)))
		{
			//Ecursor->lock = false;
			Ecursor->move.x += 0.35f;
		}

		if ((GetKeyboardPress(DIK_O)) || (IsButtonTriggered(1, BUTTON_R3)))
		{
			Ecursor->lock = true;
		}
	}
	else if (Ecursor->lock == true)
	{
		Ecursor->pos.x = player->pos.x;
		Ecursor->pos.z = player->pos.z;
		if (IsButtonTriggered(1, BUTTON_R3))
		{
			Ecursor->lock = false;
		}
	}

	if (Ecursor->rot.y > D3DX_PI)
	{
		// 360度を超えたら360度を引く
		Ecursor->rot.y -= D3DX_PI * 2.0f;
	}
	else if (Ecursor->rot.y < D3DX_PI)
	{
		// 360度を超えたら360度を引く
		Ecursor->rot.y += D3DX_PI * 2.0f;
	}


	Ecursor->pos.x += Ecursor->move.x;
	Ecursor->pos.z += Ecursor->move.z;

	Ecursor->move.x += (0.0f - Ecursor->move.x) * RATE_REGIST;
	Ecursor->move.z += (0.0f - Ecursor->move.z) * RATE_REGIST;

	//カーソルサイズの更新
	Ecursor->size.x = (camera->EyeToAtDistance / 50.0f + (Ecursor->pos.z * 0.005f) + 15.0f);
	Ecursor->size.y = (camera->EyeToAtDistance / 50.0f + (Ecursor->pos.z * 0.005f) + 15.0f);

	if (Ecursor->pos.x < (Ecursor->size.x / 2) - FIELD_SCL_MAX_X)
	{
		Ecursor->pos.x = (Ecursor->size.x / 2) - FIELD_SCL_MAX_X;
	}
	if (Ecursor->pos.x > FIELD_SCL_MAX_X - (Ecursor->size.x / 2))
	{
		Ecursor->pos.x = FIELD_SCL_MAX_X - (Ecursor->size.x / 2);
	}
	if (Ecursor->pos.z > FIELD_SCL_MAX_Z)
	{
		Ecursor->pos.z = FIELD_SCL_MAX_Z;
	}
	if (Ecursor->pos.z < (Ecursor->size.y / 2)- FIELD_SCL_MAX_Z)
	{
		Ecursor->pos.z = (Ecursor->size.y / 2) - FIELD_SCL_MAX_Z;
	}

	SetVertexCursorEnemy();

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawCursorEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxscl, mtxTranslate,mtxRot;
	CURSOR_ENEMY *Ecursor = EcursorWk;

	// αテストを有効に
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 150);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// ラインティングを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ビューマトリックスを取得
	mtxView = GetMtxView();

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&Ecursor->world);

	// ポリゴンを正面に向ける
	Ecursor->world._11 = mtxView._11;
	Ecursor->world._12 = mtxView._21;
	Ecursor->world._13 = mtxView._31;
	Ecursor->world._22 = mtxView._22;
	Ecursor->world._23 = mtxView._32;
	Ecursor->world._33 = mtxView._33;
	Ecursor->world._32 = mtxView._23;
	Ecursor->world._31 = mtxView._13;
	Ecursor->world._21 = mtxView._12;

	// スケールを反映
	D3DXMatrixScaling(&mtxscl, Ecursor->scl.x,
		Ecursor->scl.y,
		Ecursor->scl.z);
	D3DXMatrixMultiply(&Ecursor->world,
		&Ecursor->world, &mtxscl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, Ecursor->rot.y, Ecursor->rot.x, Ecursor->rot.z);
	D3DXMatrixMultiply(&Ecursor->world, &Ecursor->world, &mtxRot);


	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, Ecursor->pos.x,
		Ecursor->pos.y,
		Ecursor->pos.z);
	D3DXMatrixMultiply(&Ecursor->world,
		&Ecursor->world, &mtxTranslate);



	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &Ecursor->world);

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pD3DVtxBuffCursorEnemy, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureCursorEnemy);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	// ラインティングを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
HRESULT MakeVertexCursorEnemy(LPDIRECT3DDEVICE9 pDevice)
{
	CURSOR_ENEMY *Ecursor = EcursorWk;
	// オブジェクトの頂点バッファを生成
    if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
												FVF_VERTEX_3D,				// 使用する頂点フォーマット
												D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
												&g_pD3DVtxBuffCursorEnemy,	// 頂点バッファインターフェースへのポインタ
												NULL)))						// NULLに設定
	{
        return E_FAIL;
	}

	{
		SetVertexCursorEnemy();

		// 法線の設定
		Ecursor->vectex[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		Ecursor->vectex[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		Ecursor->vectex[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		Ecursor->vectex[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// 反射光の設定
		Ecursor->vectex[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		Ecursor->vectex[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		Ecursor->vectex[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		Ecursor->vectex[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		Ecursor->vectex[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		Ecursor->vectex[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		Ecursor->vectex[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		Ecursor->vectex[3].tex = D3DXVECTOR2(1.0f, 0.0f);


		// 頂点データをアンロックする
		g_pD3DVtxBuffCursorEnemy->Unlock();
	}

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexCursorEnemy(void)
{
	CURSOR_ENEMY *Ecursor = EcursorWk;
	{	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffCursorEnemy->Lock(0, 0, (void**)&Ecursor->vectex, 0);

		Ecursor->vectex[0].vtx = D3DXVECTOR3(-Ecursor->size.x / 2, -Ecursor->size.x / 2, 0.0f);
		Ecursor->vectex[1].vtx = D3DXVECTOR3(-Ecursor->size.x / 2, Ecursor->size.x / 2, 0.0f);
		Ecursor->vectex[2].vtx = D3DXVECTOR3(Ecursor->size.x / 2, -Ecursor->size.x / 2, 0.0f);
		Ecursor->vectex[3].vtx = D3DXVECTOR3(Ecursor->size.x / 2, Ecursor->size.x / 2, 0.0f);

		//// 頂点データをアンロックする
		//g_pD3DVtxBuffCursor->Unlock();
	}
}

CURSOR_ENEMY *GetCursorEnemy(void)
{
	return EcursorWk;
}

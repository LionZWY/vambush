//=============================================================================
//
// メッシュ地面の処理 [field.cpp]
// Author : 眞戸原史也
// プログラム作成日 : 2018/3/09
//
//=============================================================================
#include "field.h"
#include "main.h"
#include "input.h"
#include "game.h"
#include "title.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************

bool					effectflagF;				// エフェクト用制御変数
float					effectF;					// エフェクト用変数

FIELD		fieldWk[FIELD_MAX];
float		wave=0.0f;

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT InitField(int type)
{

	// ポインタの初期化
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	FIELD *field = &fieldWk[0];

	// エフェクト関係の初期化
	effectflagF = true;				// true:プラスする false:マイナスする
	effectF = 0.0f;			// エフェクトのα値の初期化

	// 初起動時
	if (type == FIRST)
	{

	// 構造体最大数初期化処理
	for (int i = 0;i < FIELD_MAX;i++, field++)
	{

		// 頂点バッファインターフェースへのポインタと
		// インデックスバッファインターフェースへのポインタの初期化
		field->VtxField = NULL;
		field->IdxField = NULL;
		field->Texture = NULL;// テクスチャ読み込み場所

		 //背景
		if (i == FIELD_BG)
		{
			// ポリゴン表示位置の中心座標を設定
			field->pos = FIELD_BG_POS;
			field->rot = D3DXVECTOR3(0.0f,0.0f, 0.0f);

			// ブロック数の設定
			field->blockX = NUM_BG_BLOCK_X;
			field->blockZ = NUM_BG_BLOCK_Z;

			// 頂点数の設定
			field->vertex = (NUM_BG_BLOCK_X + 1) * (NUM_BG_BLOCK_Z + 1);

			// インデックス数の設定
			field->vertexIndex = (NUM_BG_BLOCK_X + 1) * 2 * NUM_BG_BLOCK_Z + (NUM_BG_BLOCK_Z - 1) * 2;

			// ポリゴン数の設定
			field->polygon = NUM_BG_BLOCK_X * NUM_BG_BLOCK_Z * 2 + (NUM_BG_BLOCK_Z - 1) * 4;

			// ブロックサイズの設定
			field->sizeX = SIZE_BG_BLOCK_X;
			field->sizeZ = SIZE_BG_BLOCK_Z;

			// テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
				TEXTURE_BG,						// ファイルの名前
				&field->Texture);				// 読み込むメモリー

		}

		// 背景エフェクト
		else if(i == FIELD_BG_EFFECT)
		{
			 // ポリゴン表示位置の中心座標を設定
			field->pos = FIELD_BG_POS;
			field->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// ブロック数の設定
			field->blockX = NUM_BG_BLOCK_X;
			field->blockZ = NUM_BG_BLOCK_Z;

			// 頂点数の設定
			field->vertex = (NUM_BG_BLOCK_X + 1) * (NUM_BG_BLOCK_Z + 1);

			// インデックス数の設定
			field->vertexIndex = (NUM_BG_BLOCK_X + 1) * 2 * NUM_BG_BLOCK_Z + (NUM_BG_BLOCK_Z - 1) * 2;

			// ポリゴン数の設定
			field->polygon = NUM_BG_BLOCK_X * NUM_BG_BLOCK_Z * 2 + (NUM_BG_BLOCK_Z - 1) * 4;

			// ブロックサイズの設定
			field->sizeX = SIZE_BG_BLOCK_X;
			field->sizeZ = SIZE_BG_BLOCK_Z;

			// テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
				TEXTURE_BG_EFFECT,				// ファイルの名前
				&field->Texture);				// 読み込むメモリー


		}

		// バトル
		else if (i == FIELD_BATTLE)
		{
			// ポリゴン表示位置の中心座標を設定
			field->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			field->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// ブロック数の設定
			field->blockX = FIELD_BG_NUM_BLOCK_X;
			field->blockZ = FIELD_BG_NUM_BLOCK_Z;

			// 頂点数の設定
			field->vertex = (FIELD_BG_NUM_BLOCK_X + 1) * (FIELD_BG_NUM_BLOCK_Z + 1);

			// インデックス数の設定
			field->vertexIndex = (FIELD_BG_NUM_BLOCK_X + 1) * 2 * FIELD_BG_NUM_BLOCK_Z + (FIELD_BG_NUM_BLOCK_Z - 1) * 2;

			// ポリゴン数の設定
			field->polygon = FIELD_BG_NUM_BLOCK_X * FIELD_BG_NUM_BLOCK_Z * 2 + (FIELD_BG_NUM_BLOCK_Z - 1) * 4;

			// ブロックサイズの設定
			field->sizeX = FIELD_BG_SIZE_BLOCK_X;
			field->sizeZ = FIELD_BG_SIZE_BLOCK_Z;

			// テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
				TEXTURE_BATTLE,					// ファイルの名前
				&field->Texture);				// 読み込むメモリー

		}

			// オブジェクトの頂点バッファを生成
			if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * field->vertex,	// 頂点データ用に確保するバッファサイズ(バイト単位)
				D3DUSAGE_WRITEONLY,					// 頂点バッファの使用法　
				FVF_VERTEX_3D,						// 使用する頂点フォーマット
				D3DPOOL_MANAGED,					// リソースのバッファを保持するメモリクラスを指定
				&field->VtxField,				// 頂点バッファインターフェースへのポインタ
				NULL)))								// NULLに設定
			{
				return E_FAIL;
			}

			// オブジェクトのインデックスバッファを生成
			if (FAILED(pDevice->CreateIndexBuffer(sizeof(WORD) * field->vertexIndex,			// 頂点データ用に確保するバッファサイズ(バイト単位)
				D3DUSAGE_WRITEONLY,					// 頂点バッファの使用法　
				D3DFMT_INDEX16,						// 使用するインデックスフォーマット
				D3DPOOL_MANAGED,					// リソースのバッファを保持するメモリクラスを指定
				&field->IdxField,				// インデックスバッファインターフェースへのポインタ
				NULL)))								// NULLに設定
			{
				return E_FAIL;
			}

			{
				//頂点バッファの中身を埋める
				VERTEX_3D *pVtx;

#if 0
				const float texSizeX = 1.0f / field->blockX;
				const float texSizeZ = 1.0f / field->blockZ;
#else
				const float texSizeX = 1.0f;
				const float texSizeZ = 1.0f;
#endif

				// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
				field->VtxField->Lock(0, 0, (void**)&pVtx, 0);

				for (int nCntVtxZ = 0; nCntVtxZ < (field->blockZ + 1); nCntVtxZ++)
				{
					for (int nCntVtxX = 0; nCntVtxX < (field->blockX + 1); nCntVtxX++)
					{
						// 頂点座標の設定
						pVtx[nCntVtxZ * (field->blockX + 1) + nCntVtxX].vtx.x = -(field->blockX / 2.0f) * field->sizeX + nCntVtxX * field->sizeX;
						pVtx[nCntVtxZ * (field->blockX + 1) + nCntVtxX].vtx.y = 0.0f;
						pVtx[nCntVtxZ * (field->blockX + 1) + nCntVtxX].vtx.z = (field->blockZ / 2.0f) * field->sizeZ - nCntVtxZ * field->sizeZ;

						// 背景
						if (i == FIELD_BG)
						{
							// 法線の設定
							pVtx[nCntVtxZ * (field->blockX + 1) + nCntVtxX].nor = D3DXVECTOR3(0.0f, 1.0, 0.0f);

							// 反射光の設定
							pVtx[nCntVtxZ * (field->blockX + 1) + nCntVtxX].diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
						}

						// 背景エフェクト
						else if (i == FIELD_BG_EFFECT)
						{
							// 法線の設定
							pVtx[nCntVtxZ * (field->blockX + 1) + nCntVtxX].nor = D3DXVECTOR3(0.0f, 1.0, 0.0f);

							// 反射光の設定
							pVtx[nCntVtxZ * (field->blockX + 1) + nCntVtxX].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						}

						// 背景バトル
						else if (i == FIELD_BATTLE)
						{
							// 法線の設定
							pVtx[nCntVtxZ * (field->blockX + 1) + nCntVtxX].nor = D3DXVECTOR3(0.0f, 1.0, 0.0f);

							// 反射光の設定
							pVtx[nCntVtxZ * (field->blockX + 1) + nCntVtxX].diffuse = FIELD_COLOR;
						}

						// テクスチャ座標の設定
						pVtx[nCntVtxZ * (field->blockX + 1) + nCntVtxX].tex.x = texSizeX * nCntVtxX;
						pVtx[nCntVtxZ * (field->blockX + 1) + nCntVtxX].tex.y = texSizeZ * nCntVtxZ;
					}
				}

				// 頂点データをアンロックする
				field->VtxField->Unlock();
			}

			{//インデックスバッファの中身を埋める
				WORD *pIdx;

				// インデックスデータの範囲をロックし、頂点バッファへのポインタを取得
				field->IdxField->Lock(0, 0, (void**)&pIdx, 0);

				int nCntIdx = 0;
				for (int nCntVtxZ = 0; nCntVtxZ < field->blockZ; nCntVtxZ++)
				{
					if (nCntVtxZ > 0)
					{// 縮退ポリゴンのためのダブりの設定
						pIdx[nCntIdx] = (nCntVtxZ + 1) * (field->blockX + 1);
						nCntIdx++;
					}

					for (int nCntVtxX = 0; nCntVtxX < (field->blockX + 1); nCntVtxX++)
					{
						pIdx[nCntIdx] = (nCntVtxZ + 1) * (field->blockX + 1) + nCntVtxX;
						nCntIdx++;
						pIdx[nCntIdx] = nCntVtxZ * (field->blockX + 1) + nCntVtxX;
						nCntIdx++;
					}

					if (nCntVtxZ < (field->blockZ - 1))
					{// 縮退ポリゴンのためのダブりの設定
						pIdx[nCntIdx] = nCntVtxZ * (field->blockX + 1) + field->blockX;
						nCntIdx++;
					}
				}

				// インデックスデータをアンロックする
				field->IdxField->Unlock();
			}
		}
	}


	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void UninitField(void)
{
	// ポインタの初期化
	FIELD *field = &fieldWk[0];

	// 構造体最大数処理
	for (int i = 0;i < FIELD_MAX;i++, field++)
	{

		if (field->VtxField!=NULL)
		{// 頂点バッファの開放
			field->VtxField->Release();
			field->VtxField = NULL;
		}

		if (field->IdxField != NULL)
		{// インデックスバッファの開放
			field->IdxField->Release();
			field->IdxField = NULL;
		}

		if (field->Texture)
		{// テクスチャの開放
			field->Texture->Release();
			field->Texture = NULL;
		}

	}

}

//=============================================================================
// 更新処理関数
//=============================================================================
void UpdateField(void)
{

	// ポインタの初期化
	FIELD *field = &fieldWk[0];

	// エフェクト処理
	// プラスフラグ
	if (effectflagF == true)
	{
		// エフェクトα値にFIELD_EFFECT_SPEEDを足す
		effectF += FIELD_EFFECT_SPEED;

		// エフェクトα値が最大
		if (effectF >= 1.0f)
		{
			// フラグをマイナスに
			effectflagF = false;
		}
	}

	// マイナスフラグ
	else if (effectflagF == false)
	{
		// エフェクトα値にFIELD_EFFECT_SPEEDを引く
		effectF -= FIELD_EFFECT_SPEED;

		// エフェクトα値が最小
		if (effectF <= 0.0f)
		{
			// フラグをプラスにに
			effectflagF = true;
		}

	}

	// 構造体最大数処理
	for (int i = 0;i < FIELD_MAX;i++, field++)
	{
		if (i == FIELD_BG_EFFECT)
		{

			//頂点バッファの中身を埋める
			VERTEX_3D *pVtx;

			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			field->VtxField->Lock(0, 0, (void**)&pVtx, 0);

			// 水面の波の処理
			// Z軸処理
			for (int nCntVtxZ = 0; nCntVtxZ < (field->blockZ + 1); nCntVtxZ++)
			{

				// X軸処理
				for (int nCntVtxX = 0; nCntVtxX < (field->blockX + 1); nCntVtxX++)
				{
					// 反射光の設定
					pVtx[nCntVtxZ * (field->blockX + 1) + nCntVtxX].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, effectF);

				}
			}
			// 頂点データをアンロックする
			field->VtxField->Unlock();
		}
	}

}

//=============================================================================
// 描画処理関数
//=============================================================================
void DrawField(void)
{
	// ポインタの初期化
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	FIELD *field = &fieldWk[0];

	//// レンダーステートパラメータの設定
	//pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);	// レンダーステートパラメータの設定


	D3DXMATRIX mtxRot, mtxTranslate;

	//// ラインティングを無効にする
	//pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);


	// 構造体最大数処理
	for (int i = 0;i < FIELD_MAX;i++, field++)
	{

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&field->world);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, field->rot.y, field->rot.x, field->rot.z);
		D3DXMatrixMultiply(&field->world, &field->world, &mtxRot);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, field->pos.x, field->pos.y, field->pos.z);
		D3DXMatrixMultiply(&field->world, &field->world, &mtxTranslate);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &field->world);

		// 頂点バッファをレンダリングパイプラインに設定
		pDevice->SetStreamSource(0, field->VtxField, 0, sizeof(VERTEX_3D));

		// インデックスバッファをレンダリングパイプラインに設定
		pDevice->SetIndices(field->IdxField);

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		// テクスチャの設定
		pDevice->SetTexture(0, field->Texture);

		// ポリゴンの描画
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, field->vertex, 0, field->polygon);
	}

	//// ラインティグを有効にする
	//pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);


	//// レンダーステートパラメータの設定
	//pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// 裏面をカリング

}


//=============================================================================
// 地形モデル取得関数
//=============================================================================
FIELD *GetField(int no)
{
	return(&fieldWk[no]);
}
//=============================================================================
//
// タイマー処理 [timer.cpp]
// Author : 眞戸原史也
// プログラム作成日 : 2018/3/09
//
//=============================================================================

#include "timer.h"				// マクロ＆構造体使用の為
#include "game.h"				// マクロ使用の為
#include "player.h"				// 構造体使用の為
#include "enemy.h"				// 同上
#include "sound.h"				// 関数使用の為
#include "fade.h"				// 同上
#include "result.h"				// 同上

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexTimer(LPDIRECT3DDEVICE9 pDevice, int no);	// 頂点作成関数
void SetTextureTimer(int idx, int number, int no);			// テクスチャ座標設定関数

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureTimer = NULL;			// テクスチャへのポインタ変数
bool					g_bEnableTimer;						// タイマー動作ON/OFF変数
bool					quickbgm;

TIMER					timerWk[NUM_MAX];					// タイマー構造体を最大数宣言

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT InitTimer(int type)
{

	// ポインタの初期化
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TIMER *timer = &timerWk[0];
	PLAYER *player = GetPlayer();
	ENEMY *enemy = GetEnemy();

	// タイマーを使用で初期化
	g_bEnableTimer = true;

	quickbgm = false;

	// 最大数初期化処理
	for (int i = 0;i < NUM_MAX;i++, timer++)
	{

		// 全てNULLで初期化
		timer->buff = NULL;

		// タイマー
		if (i == NUM_TIMER)
		{
			timer->use = true;								// 使用で初期化
			timer->pos = TIMER_BASE_POS;					// 位置の初期化
			timer->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 回転の初期化

			// タイマーの値の初期化
			timer->nummax = TIMER_MAX * FRAME_CNT;
		}

		// 必殺技ゲージプレイヤー
		else if (i == NUM_PLAYER_KILL)
		{
			timer->use = true;								// 使用で初期化
			timer->pos = TIMER_PLAYER_POS;					// 位置の初期化
			timer->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 回転の初期化

			// HPの初期化
			timer->nummax = player->kill;
		}

		// 必殺技ゲージエネミー
		else if (i == NUM_ENEMY_KILL)
		{
			timer->use = true;								// 使用で初期化
			timer->pos = TIMER_ENEMY_POS;				// 位置の初期化
			timer->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 回転の初期化

															// アクアスの初期化
			timer->nummax =enemy->kill;
		}


		// 頂点情報の作成
		MakeVertexTimer(pDevice,i);

	}

	// 初起動時
	if (type == FIRST)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
			TEXTURE_TIMER,					// ファイルの名前
			&g_pD3DTextureTimer);			// 読み込むメモリー
	}

	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void UninitTimer(void)
{

	// メモリの解放
	if(g_pD3DTextureTimer != NULL)
	{
		// テクスチャの開放
		g_pD3DTextureTimer->Release();
		g_pD3DTextureTimer = NULL;
	}
}

//=============================================================================
// 更新処理関数
//=============================================================================
void UpdateTimer(void)
{
	// ポインタの初期化
	TIMER *timer = &timerWk[0];
	PLAYER *player = GetPlayer();
	ENEMY *enemy = GetEnemy();
	bool *win = GetWinFlag();

	// 最大数更新処理
	for (int i = 0;i < NUM_MAX;i++, timer++)
	{

		// タイマー
		if (i == NUM_TIMER)
		{
			// タイマーがonだったら
			if (g_bEnableTimer)
			{
				// 持ち時間の減少
				timer->nummax--;

				// 60
				if ((timer->nummax / FRAME_CNT < 60) && (timer->nummax / FRAME_CNT > 30))
				{

					if (quickbgm == false)
					{

						StopSound(BGM_BATTLE);								// 通常戦闘BGMの停止
						PlaySound(BGM_QUICK, E_DS8_FLAG_NONE);		// リザルトBGMの再生
						quickbgm = true;
					}

					VERTEX_2D *pVtx;

					// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
					timer->buff->Lock(0, 0, (void**)&pVtx, 0);

					// 最大数作成
					for (int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++, pVtx += NUM_VERTEX)
					{

						// 反射光の設定
						pVtx[0].diffuse = D3DCOLOR_RGBA(255, 255, 0, 255);
						pVtx[1].diffuse = D3DCOLOR_RGBA(255, 255, 0, 255);
						pVtx[2].diffuse = D3DCOLOR_RGBA(255, 255, 0, 255);
						pVtx[3].diffuse = D3DCOLOR_RGBA(255, 255, 0, 255);

					}

					// 頂点データをアンロックする
					timer->buff->Unlock();

				}

			// 30
			if (timer->nummax / FRAME_CNT < 30)
			{
				VERTEX_2D *pVtx;

				// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
				timer->buff->Lock(0, 0, (void**)&pVtx, 0);

				// 最大数作成
				for (int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++, pVtx += NUM_VERTEX)
				{

					// 反射光の設定
					pVtx[0].diffuse = D3DCOLOR_RGBA(255, 0, 0, 255);
					pVtx[1].diffuse = D3DCOLOR_RGBA(255, 0, 0, 255);
					pVtx[2].diffuse = D3DCOLOR_RGBA(255, 0, 0, 255);
					pVtx[3].diffuse = D3DCOLOR_RGBA(255, 0, 0, 255);

				}

			// 頂点データをアンロックする
			timer->buff->Unlock();

			}



				// タイムアップ
				if (timer->nummax < 0)
				{
					// タイマーのストップ
					timer->nummax = 0;

					// hpを比べる
					if (player->hp > enemy->hp)
					{
						// プレイヤーの勝利
						*win = true;
					}

					else
					{

						// エネミ－勝利
						*win = false;

					}

					// ステージ変数のリザルトの前にセット
					SetStage(STAGE_GAME_END);

					// 画面遷移:リザルト
					SetFade(FADE_OUT);
				}

				// 持ち時間がある
				else if ((timer->nummax / FRAME_CNT) >= (int)(powf(10.0f, (float)(NUM_PLACE + 1))))
				{
					// １０の累乗ー１を代入
					timer->nummax = (int)(powf(DECIMAL_TEN, (float)(NUM_PLACE + 1))) - 1;
				}
			}

			// 表示桁最大数テクスチャ設定
			for (int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++)
			{
				// タイマー制御変数
				int number;		// 表示数値変数
				int time;		// 表示数値計算用変数

				// 現在の時間から５９を引く
				time = timer->nummax + FRAME_CNT-1;

				// 表示数値の決定
				number = ((time / FRAME_CNT) % (int)(powf(DECIMAL_TEN, (float)(NUM_PLACE - nCntPlace)))) / (int)(powf(DECIMAL_TEN, (float)(NUM_PLACE - nCntPlace - 1)));

			// 表示数値の反映
				SetTextureTimer(nCntPlace, number, i);
			}

		}

		// 必殺技ゲージプレイヤー
		else if (i == NUM_PLAYER_KILL)
		{

			// 現在の必殺技ゲージの値を保存
			timer->nummax = player->kill;

			if (player->kill == 100)
			{
				VERTEX_2D *pVtx;

				// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
				timer->buff->Lock(0, 0, (void**)&pVtx, 0);

				// 最大数作成
				for (int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++, pVtx += NUM_VERTEX)
				{

					// 反射光の設定
					pVtx[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

				}

				// 頂点データをアンロックする
				timer->buff->Unlock();


			}

			// 表示桁最大数テクスチャ設定
			for (int s = 0; s < NUM_PLACE; s++)
			{

				// 表示数値変数
				int number;

				// 三桁目
				if (s == NUM_THREE_DIGIT)
				{
					// 表示数値の決定
					number = timer->nummax / BASE_HUNDRED;

					// 表示数値の反映
					SetTextureTimer(s, number, i);
				}

				// 二桁目
				else if (s == NUM_DOUBLE_DIGIT)
				{
					// 表示数値の決定
					number = timer->nummax % BASE_HUNDRED / BASE_TEN;

					// 表示数値の反映
					SetTextureTimer(s, number, i);
				}

				// 一桁目
				else if (s == NUM_DIGIT)
				{
					// 表示数値の決定
					number = timer->nummax % BASE_HUNDRED% BASE_TEN / 1;

					// 表示数値の反映
					SetTextureTimer(s, number, i);
				}

			}

		}

		// 必殺技ゲージエネミー
		else if (i == NUM_ENEMY_KILL)
		{

			// 現在の必殺技ゲージの値を保存
			timer->nummax = enemy->kill;

			if (enemy->kill == 100)
			{
				VERTEX_2D *pVtx;

				// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
				timer->buff->Lock(0, 0, (void**)&pVtx, 0);

				// 最大数作成
				for (int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++, pVtx += NUM_VERTEX)
				{

					// 反射光の設定
					pVtx[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

				}

				// 頂点データをアンロックする
				timer->buff->Unlock();


			}


			// 表示桁最大数テクスチャ設定
			for (int s = 0; s < NUM_PLACE; s++)
			{

				// 表示数値変数
				int number;

				// 三桁目
				if (s == NUM_THREE_DIGIT)
				{
					// 表示数値の決定
					number = timer->nummax / BASE_HUNDRED;

					// 表示数値の反映
					SetTextureTimer(s, number, i);
				}

				// 二桁目
				else if (s == NUM_DOUBLE_DIGIT)
				{
					// 表示数値の決定
					number = timer->nummax % BASE_HUNDRED / BASE_TEN;

					// 表示数値の反映
					SetTextureTimer(s, number, i);
				}

				// 一桁目
				else if (s == NUM_DIGIT)
				{
					// 表示数値の決定
					number = timer->nummax % BASE_HUNDRED% BASE_TEN / 1;

					// 表示数値の反映
					SetTextureTimer(s, number, i);
				}

			}


		}


	}
}

//=============================================================================
// 描画処理関数
//=============================================================================
void DrawTimer(void)
{

	// ポインタの初期化
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TIMER *timer = &timerWk[0];

	// 最大数描画処理
	for (int i = 0;i < NUM_MAX;i++, timer++)
	{

		// 使用していたら
		if (timer->use == true)
		{

			// 頂点バッファをデバイスのデータストリームにバインド
			pDevice->SetStreamSource(0, timer->buff, 0, sizeof(VERTEX_2D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_2D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pD3DTextureTimer);

			// ポリゴンの描画
			for (int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++)
			{
				// レンダリング処理
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntPlace * NUM_VERTEX), NUM_POLYGON);
			}
		}
	}
}

//=============================================================================
// 頂点作成関数
//=============================================================================
HRESULT MakeVertexTimer(LPDIRECT3DDEVICE9 pDevice, int no)
{

	// ポインタの初期化
	TIMER *timer = &timerWk[no];

	// オブジェクトの頂点バッファを生成
    if( FAILED( pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * (NUM_VERTEX * NUM_PLACE + NUM_VERTEX),	// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,										// 頂点バッファの使用法　
												FVF_VERTEX_2D,											// 使用する頂点フォーマット
												D3DPOOL_MANAGED,										// リソースのバッファを保持するメモリクラスを指定
												&timer->buff,											// 頂点バッファインターフェースへのポインタ
												NULL)))													// NULLに設定
	{
        return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		timer->buff->Lock(0, 0, (void**)&pVtx, 0);

		// 最大数作成
		for(int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++, pVtx += NUM_VERTEX)
		{

			// タイマー
			if (no == NUM_TIMER)
			{
				// 頂点座標の設定
				pVtx[0].vtx = D3DXVECTOR3(TIMER_POS_X + nCntPlace * TIMER_SIZE_X + TIMER_INTERVAL_X, TIMER_POS_Y, 0.0f);
				pVtx[1].vtx = D3DXVECTOR3(TIMER_POS_X + nCntPlace * (TIMER_INTERVAL_X + TIMER_SIZE_X) + TIMER_SIZE_X, TIMER_POS_Y, 0.0f);
				pVtx[2].vtx = D3DXVECTOR3(TIMER_POS_X + nCntPlace * TIMER_SIZE_X + TIMER_INTERVAL_X, TIMER_POS_Y + TIMER_SIZE_Y, 0.0f);
				pVtx[3].vtx = D3DXVECTOR3(TIMER_POS_X + nCntPlace * (TIMER_INTERVAL_X + TIMER_SIZE_X) + TIMER_SIZE_X, TIMER_POS_Y + TIMER_SIZE_Y, 0.0f);

				// rhwの設定
				pVtx[0].rhw =
				pVtx[1].rhw =
				pVtx[2].rhw =
				pVtx[3].rhw = 1.0f;

				// 反射光の設定
				pVtx[0].diffuse = D3DCOLOR_RGBA(100, 255, 100, 255);
				pVtx[1].diffuse = D3DCOLOR_RGBA(100, 255, 100, 255);
				pVtx[2].diffuse = D3DCOLOR_RGBA(100, 255, 100, 255);
				pVtx[3].diffuse = D3DCOLOR_RGBA(100, 255, 100, 255);

				// テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

			}

			// 必殺技ゲージプレイヤー
			else if (no == NUM_PLAYER_KILL)
			{
				// 頂点座標の設定
				pVtx[0].vtx = D3DXVECTOR3(timer->pos.x + nCntPlace * KILL_SIZE_X + TIMER_INTERVAL_X, timer->pos.y, 0.0f);
				pVtx[1].vtx = D3DXVECTOR3(timer->pos.x + nCntPlace * (TIMER_INTERVAL_X + KILL_SIZE_X) + KILL_SIZE_X, timer->pos.y, 0.0f);
				pVtx[2].vtx = D3DXVECTOR3(timer->pos.x + nCntPlace * KILL_SIZE_X + TIMER_INTERVAL_X, timer->pos.y + KILL_SIZE_Y, 0.0f);
				pVtx[3].vtx = D3DXVECTOR3(timer->pos.x + nCntPlace * (TIMER_INTERVAL_X + KILL_SIZE_X) + KILL_SIZE_X, timer->pos.y + KILL_SIZE_Y, 0.0f);

				// rhwの設定
				pVtx[0].rhw =
					pVtx[1].rhw =
					pVtx[2].rhw =
					pVtx[3].rhw = 1.0f;

				// 反射光の設定
				pVtx[0].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
				pVtx[1].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
				pVtx[2].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
				pVtx[3].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);

				// テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

			}

			// 必殺技ゲージエネミー
			else if (no == NUM_ENEMY_KILL)
			{
				// 頂点座標の設定
				pVtx[0].vtx = D3DXVECTOR3(timer->pos.x + nCntPlace * KILL_SIZE_X + TIMER_INTERVAL_X, timer->pos.y, 0.0f);
				pVtx[1].vtx = D3DXVECTOR3(timer->pos.x + nCntPlace * (TIMER_INTERVAL_X + KILL_SIZE_X) + KILL_SIZE_X, timer->pos.y, 0.0f);
				pVtx[2].vtx = D3DXVECTOR3(timer->pos.x + nCntPlace * KILL_SIZE_X + TIMER_INTERVAL_X, timer->pos.y + KILL_SIZE_Y, 0.0f);
				pVtx[3].vtx = D3DXVECTOR3(timer->pos.x + nCntPlace * (TIMER_INTERVAL_X + KILL_SIZE_X) + KILL_SIZE_X, timer->pos.y + KILL_SIZE_Y, 0.0f);

				// rhwの設定
				pVtx[0].rhw =
					pVtx[1].rhw =
					pVtx[2].rhw =
					pVtx[3].rhw = 1.0f;

				// 反射光の設定
				pVtx[0].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
				pVtx[1].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
				pVtx[2].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
				pVtx[3].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);

				// テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

			}


		}

		// 頂点データをアンロックする
		timer->buff->Unlock();
	}

	return S_OK;
}

//=============================================================================
// テクスチャ座標設定関数
//=============================================================================
void SetTextureTimer(int idx, int number, int no)
{
	// ポインタの初期化
	TIMER *timer = &timerWk[no];

	//頂点バッファの中身を埋める
	VERTEX_2D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	timer->buff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点数分インクリメント
	pVtx += (idx * NUM_VERTEX);

	// 頂点座標の設定
	pVtx[0].tex = D3DXVECTOR2(number * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(number * 0.1f + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(number * 0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(number * 0.1f + 0.1f, 1.0f);

	// 頂点データをアンロックする
	timer->buff->Unlock();
}

//=============================================================================
// タイマー開始関数
//=============================================================================
void EnableTimer(bool bEnable)
{
	g_bEnableTimer = bEnable;
}

//=============================================================================
// タイマーリセット関数
//=============================================================================
void ResetTimer(int nTime)
{

	// ポインタの初期化
	TIMER *timer = &timerWk[0];

	// 渡された引数に一秒のフレーム数を掛ける
	timer->nummax = nTime * FRAME_CNT;
}


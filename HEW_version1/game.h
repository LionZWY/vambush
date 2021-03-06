//=============================================================================
//
// ゲーム画面処理 [game.h]
// Author : 眞戸原史也
// プログラム作成日 : 2018/3/09
//
//=============================================================================

// 多重インクルード防止の為
#ifndef _GAME_H_
#define _GAME_H_

// ライブラリ使用の為
#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define FIRST		(0)						// 初起動時
#define UPDATA		(1)						// 更新中
#define CREDIT		(2)						// クレジット表示

#define TITLE_GAME	(4)						// カメラの制御タイトル
#define GAME		(5)						// カメラの制御更新中

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitGame(int type);					// 初期化処理関数
void UninitGame(void);						// 終了処理関数
void UpdateGame(void);						// 更新処理関数
void DrawGame(void);						// 描画処理関数

bool *GetMenu(void);						// ポーズフラグ取得関数

#endif

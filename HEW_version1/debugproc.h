//=============================================================================
//
// デバッグ表示処理 [debugproc.h]
// Author : 眞戸原史也
// プログラム作成日 : 2018/3/09
//
//=============================================================================

// 多重インクルード防止の為
#ifndef _DEBUGPROC_H_
#define _DEBUGPROC_H_

// ライブラリ使用の為
#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define DEBUG_STR_MAX		(1024)			// デバッグ情報最大数
#define BUFF_MAX			(255)			// 配列最大数
#define AWK_MAX				(32)			// 配列最大数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitDebugProc(void);				// 初期化処理関数
void UninitDebugProc(void);					// 終了処理関数
void UpdateDebugProc(void);					// 更新処理関数
void DrawDebugProc(void);					// 描画処理関数
void PrintDebugProc(char *fmt,...);			// デバッグ表示の登録関数

#endif
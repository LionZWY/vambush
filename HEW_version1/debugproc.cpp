//=============================================================================
//
// デバッグ表示処理 [debugproc.cpp]
// Author : 眞戸原史也
// プログラム作成日 : 2018/3/09
//
//=============================================================================
#include "debugproc.h"		// メンテナンス向上の為
#include <stdio.h>			// 汎用関数使用の為

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPD3DXFONT	g_Font = NULL;							// フォントへのポインタ
char		g_aStrDebug[DEBUG_STR_MAX] = {"\0"};	// デバッグ情報

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT InitDebugProc(void)
{
	// ポインタの初期化
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 設定用変数を宣言
	HRESULT hr;

	// 情報表示用フォントを設定
	hr = D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
					OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_Font);

	// 情報クリア
	memset(g_aStrDebug, 0, sizeof g_aStrDebug);

	return hr;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void UninitDebugProc(void)
{
	// メモリの解放
	if(g_Font != NULL)
	{// 情報表示用フォントの開放
		g_Font->Release();
		g_Font = NULL;
	}
}

//=============================================================================
// 更新処理関数
//=============================================================================
void UpdateDebugProc(void)
{
}

//=============================================================================
// 描画処理関数
//=============================================================================
void DrawDebugProc(void)
{
	// 情報表示位置格納
	RECT rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

	// 情報表示
	g_Font->DrawText(NULL, g_aStrDebug, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0, 0, 0));

	// 情報クリア
	memset(g_aStrDebug, 0, sizeof g_aStrDebug);
}

//=============================================================================
// デバッグ表示の登録関数
//=============================================================================
void PrintDebugProc(char *fmt,...)
{
#if 0
	long *pParam;
	static char aBuf[256];

	pParam = (long*)&fmt;
	sprintf(aBuf, fmt, pParam[1], pParam[2], pParam[3], pParam[4],
									pParam[5], pParam[6], pParam[7], pParam[8],
									pParam[9], pParam[10], pParam[11], pParam[12]);
#else
	va_list list;					// 可変引数を処理する為に使用する変数
	char *pCur;						// ポインタを宣言
	char aBuf[BUFF_MAX]={"\0"};
	char aWk[AWK_MAX];

	// 可変引数にアクセスする前の初期処理
	va_start(list, fmt);

	pCur = fmt;

	for( ; *pCur; ++pCur)
	{
		if(*pCur != '%')
		{
			sprintf(aWk, "%c", *pCur);
		}
		else
		{
			pCur++;

			switch(*pCur)
			{
			case 'd':
				// 可変引数にアクセスしてその変数を取り出す処理
				sprintf(aWk, "%d", va_arg(list, int));
				break;

			case 'f':
				// 可変引数にアクセスしてその変数を取り出す処理
				sprintf(aWk, "%.2f", va_arg(list, double));		// double型で指定
				break;

			case 's':
				// 可変引数にアクセスしてその変数を取り出す処理
				sprintf(aWk, "%s", va_arg(list, char*));
				break;

			case 'c':
				// 可変引数にアクセスしてその変数を取り出す処理
				sprintf(aWk, "%c", va_arg(list, char));
				break;

			default:
				sprintf(aWk, "%c", *pCur);
				break;
			}
		}
		strcat(aBuf, aWk);
	}

	// 可変引数にアクセスした後の終了処理
	va_end(list);

	// 連結
	if((strlen(g_aStrDebug) + strlen(aBuf)) < sizeof g_aStrDebug - 1)
	{
		strcat(g_aStrDebug, aBuf);
	}
#endif
}

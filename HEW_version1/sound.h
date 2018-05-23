//=============================================================================
//
// サウンド処理 [sound.cpp]
// Author : 眞戸原史也
// プログラム作成日 : 2018/3/09
//
//=============================================================================

// 多重インクルード防止の為
#ifndef ___SOUND_H___
#define ___SOUND_H___

// ライブラリ使用＆の為
#include <dsound.h>			// ライブラリ使用の為
#include <tchar.h>			// 汎用テキスト使用の為
#include <windows.h>		// 下記インクルードのエラー防止の為
#include <mmsystem.h>		// 時間計測の為

//*****************************************************************************
// マクロ定義
//*****************************************************************************

// サウンド通しナンバーマクロ(sound.cppの順番と合わせる事)
enum
{
	BGM_TITLE,				// タイトルBGM
	BGM_CALL_START,			// スタートコール
	BGM_BATTLE,				// 通常戦闘BGM
	BGM_QUICK,				// 焦りBGM
	BGM_CALL_RESULT,		// リザルトBGM
	BGM_RESULT,				// リザルトBGM２

	SE_SERECT,				// カーソル移動SE
	SE_PUSH,				// カーソル決定SE
	SE_BULLET,				// 通常弾SE
	SE_WARM,				// 特殊弾１SE
	SE_CASCEDE,				// 特殊弾２SE
	SE_FLAME,				// 必殺技SE
	SE_HIT,					// ヒットSE

	SOUND_MAX			// 登録音最大数
};

// 再生用フラグマクロ
enum
{
	E_DS8_FLAG_NONE,	// 一回鳴らす
	E_DS8_FLAG_LOOP,	// DSBPLAY_LOOPING=1:ループ再生
	E_DS8_FLAG_MAX		// 再生フラグ最大数
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);									// 初期化処理関数
void UninitSound();												// 終了処理関数
LPDIRECTSOUNDBUFFER8 LoadSound(int no);							// ロード処理関数
void PlaySound(int no, int flag = 0);		// 再生処理関数
void StopSound(int no);					// 停止処理関数
bool IsPlaying(LPDIRECTSOUNDBUFFER8 pBuffer);					// 再生判定関数
void SetSound(int no);											// サウンド遷移制御関数


#endif
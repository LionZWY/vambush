//=============================================================================
//
// サウンド処理 [sound.cpp]
// Author : 眞戸原史也
// プログラム作成日 : 2018/3/09
//
//=============================================================================

#include "sound.h"		// マクロ＆構造体の使用の為
#include <dsound.h>		// 関数使用の為
#include "main.h"		// ライブラリ使用の為

// おまじない
#pragma comment ( lib, "dxguid.lib" )
#pragma comment ( lib, "dsound.lib" )
#pragma comment ( lib, "winmm.lib" )

//*****************************************************************************
// マクロ定義
//*****************************************************************************

// サウンドファイルのパス（sound.hの通しナンバーと順番を合わせる）
const TCHAR* c_soundFilename[] = {
	_T("data/BGM/機械BGM (online-audio-converter.com).wav"),
	_T("data/BGM/3.2.1...Go!SE (online-audio-converter.com).wav"),
	_T("data/BGM/アップスパイス (online-audio-converter.com).wav"),
	_T("data/BGM/残り30秒BGM・mp3.wav"),
	_T("data/BGM/jingle1 (online-audio-converter.com).wav"),
	_T("data/BGM/リザルトBGM.wav"),

	_T("data/SE/カーソル選択.wav"),
	_T("data/SE/決定SE.wav"),
	_T("data/SE/通常攻撃SE.wav"),
	_T("data/SE/ワームSE.wav"),
	_T("data/SE/カスケードSE.wav"),
	_T("data/SE/FLAME SE.wav"),
	_T("data/SE/食らうSE2.wav"),

};

//*****************************************************************************
// グローバル変数
//*****************************************************************************
IDirectSound8 *g_pDirectSound[SOUND_MAX];	// サウンドインターフェース

LPDIRECTSOUNDBUFFER8	BGM[SOUND_MAX];		// サウンド格納変数を登録音数宣言

//=============================================================================
// 初期化処理
//=============================================================================
// hWnd:ウィンドウハンドル
HRESULT InitSound(HWND hWnd)
{

	// 最大数初期化
	for (int i = 0;i < SOUND_MAX;i++)
	{
		// DirectSoundオブジェクトの作成
		if (FAILED(DirectSoundCreate8(NULL, &g_pDirectSound[i], NULL)))
		{
			return E_FAIL;
		}

		// 協調レベル設定 
		if (FAILED(g_pDirectSound[i]->SetCooperativeLevel(hWnd, DSSCL_PRIORITY)))
		{
			return E_FAIL;
		}
	}

	// BGMロードに登録音をロード
	BGM[BGM_TITLE] = LoadSound(BGM_TITLE);					// タイトルBGM
	BGM[BGM_CALL_START] = LoadSound(BGM_CALL_START);		// スタートコール
	BGM[BGM_BATTLE] = LoadSound(BGM_BATTLE);				// 通常戦闘BGM
	BGM[BGM_QUICK] = LoadSound(BGM_QUICK);					// 焦りBGM
	BGM[BGM_CALL_RESULT] = LoadSound(BGM_CALL_RESULT);		// リザルトBGM
	BGM[BGM_RESULT] = LoadSound(BGM_RESULT);				// リザルトBGM２

	// SEのロード
	BGM[SE_SERECT] = LoadSound(SE_SERECT);				// カーソル移動SE
	BGM[SE_PUSH] = LoadSound(SE_PUSH);					// カーソル決定SE
	BGM[SE_BULLET] = LoadSound(SE_BULLET);				// 通常弾SE
	BGM[SE_WARM] = LoadSound(SE_WARM);					// 特殊弾１SE
	BGM[SE_CASCEDE] = LoadSound(SE_CASCEDE);			// 特殊弾２SE
	BGM[SE_FLAME] = LoadSound(SE_FLAME);				// 必殺技SE
	BGM[SE_HIT] = LoadSound(SE_HIT);					// ヒットSE

	// タイトルBGM再生
	PlaySound(BGM_TITLE, E_DS8_FLAG_LOOP);

	return S_OK;
}

//=============================================================================
// 終了処理		メモリーの解放
//=============================================================================
void UninitSound()
{

	// 最大数終了処理
	for (int i = 0;i < SOUND_MAX;i++)
	{
		// メモリの解放
		if (g_pDirectSound[i] != NULL)
		{
			g_pDirectSound[i]->Release();
			g_pDirectSound[i] = NULL;
		}
	}
}

//=============================================================================
// ロード処理
// サウンドのロード
// no:サウンドナンバー（ヘッダに定義された列挙型定数）
//=============================================================================
LPDIRECTSOUNDBUFFER8 LoadSound(int no)
{
	// MMIO = マルチメディア入出力、の略。
	LPDIRECTSOUNDBUFFER  pBaseBuffer = NULL;	// 曲データの総合バッファ
	LPDIRECTSOUNDBUFFER8 pBuffer = NULL;		// 曲データのバッファ
	DSBUFFERDESC buff;							// バッファ設定構造体

	HMMIO hMmio = NULL;							// MMIOハンドル
	MMIOINFO mmioInfo;							// マルチメディアデータ構造体

	MMRESULT mmRes;								// MM処理結果格納変数
	MMCKINFO riffChunk, formatChunk, dataChunk;	// チャンクデータ構造体
	DWORD size;									// データサイズ格納用
	WAVEFORMATEX pcm;							// 曲データフォーマット構造体

	LPVOID pBlock;								// セカンダリバッファのデータ書き込み先アドレス
	DWORD  dwSize;								// セカンダリバッファのサイズ

												// 1.ハンドルをもとにファイルを開く
	memset(&mmioInfo, 0, sizeof(MMIOINFO));
	hMmio = mmioOpen((LPSTR)c_soundFilename[no], &mmioInfo, MMIO_READ);

	// 見つからなかったら異常終了
	if (!hMmio)
	{
		return NULL;
	}

	// 2.ファイル解析① RIFFチャンク検索
	riffChunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');				// 検索キーワード
	mmRes = mmioDescend(hMmio, &riffChunk, NULL, MMIO_FINDRIFF);	// キーワードをもとに検索

																	// 見つからなかったら異常終了
	if (mmRes != MMSYSERR_NOERROR)
	{
		// ファイルを閉じる
		mmioClose(hMmio, 0);
		return NULL;
	}

	// 3.ファイル解析② フォーマットチャンク検索
	formatChunk.ckid = mmioFOURCC('f', 'm', 't', ' ');						// 検索キーワード
	mmRes = mmioDescend(hMmio, &formatChunk, &riffChunk, MMIO_FINDCHUNK);	// キーワードをもとに検索

																			// 見つからなかったら異常終了
	if (mmRes != MMSYSERR_NOERROR)
	{
		// ファイルを閉じる
		mmioClose(hMmio, 0);
		return NULL;
	}

	// 検索情報をもとに読み込み
	size = mmioRead(hMmio, (HPSTR)&pcm, formatChunk.cksize);

	// 正しく読み込めなかったら異常終了
	if (size != formatChunk.cksize)
	{
		// ファイルを閉じる
		mmioClose(hMmio, 0);
		return NULL;
	}

	// チャンクからアセンド
	mmioAscend(hMmio, &formatChunk, 0);

	// 4.ファイル解析③ データチャンク検索
	dataChunk.ckid = mmioFOURCC('d', 'a', 't', 'a');					// 検索キーワード
	mmRes = mmioDescend(hMmio, &dataChunk, &riffChunk, MMIO_FINDCHUNK);	// キーワードをもとに検索

																		// 見つからなかったら異常終了
	if (mmRes != MMSYSERR_NOERROR)
	{
		// ファイルを閉じる
		mmioClose(hMmio, 0);
		return NULL;
	}

	// 5.データ読み込み
	char *pData = new char[dataChunk.cksize];					// 必要な大きさの領域を確保して
	size = mmioRead(hMmio, (HPSTR)pData, dataChunk.cksize);		// データを読み込む

																// 正しく読み込めなかったら異常終了
	if (size != dataChunk.cksize)
	{
		// 元の読み込み領域を消す
		delete[] pData;
		return NULL;
	}

	// 6.曲を読み込む「セカンダリバッファ」を用意
	ZeroMemory(&buff, sizeof(DSBUFFERDESC));		// まず初期化
	buff.dwSize = sizeof(DSBUFFERDESC);				// そこから各種設定
	buff.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS | DSBCAPS_LOCDEFER;
	buff.dwBufferBytes = size;
	buff.lpwfxFormat = &pcm;

	// 総合バッファを作る
	if (FAILED(g_pDirectSound[no]->CreateSoundBuffer(&buff, &pBaseBuffer, NULL)))
	{
		return NULL;
	}


	// サウンドバッファを取り出す
	if (FAILED(pBaseBuffer->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&pBuffer)))
	{
		return NULL;
	}

	// 取り出したら総合バッファを捨てる
	pBaseBuffer->Release();

	// 7.作られたセカンダリバッファにデータを転送
	// まずは書き込みできるようバッファをロック
	if (FAILED(pBuffer->Lock(0, 0, &pBlock, &dwSize, NULL, NULL, DSBLOCK_ENTIREBUFFER)))
	{
		return NULL;
	}

	memcpy(pBlock, pData, dwSize);	// データ転送
	delete[] pData;					// 元の読み込み領域を消す

									// バッファロック解除
	pBuffer->Unlock(pBlock, dwSize, 0, 0);

	// セカンダリバッファを返して完了
	return pBuffer;
}
//=============================================================================
// 再生処理関数
// pBuffer:音を鳴らしたいサウンドデータのセカンダリバッファ
// flag   :1(E_DS8_FLAG_LOOP)ならループ再生
//=============================================================================
void PlaySound(int no, int flag/*=0*/)
{	// 続きから鳴らすので、最初から鳴らしたい場合はSetCurrentPosition(0)をすること
	// 最初から再生
	BGM[no]->SetCurrentPosition(0);
	BGM[no]->Play(0, 0, flag);
}

//=============================================================================
// 停止処理関数
//=============================================================================
void StopSound(int no)
{
	DWORD status;
	BGM[no]->GetStatus(&status);
	if (status & DSBSTATUS_PLAYING)	// 鳴っていたら
	{
		BGM[no]->Stop();	// 意味的にはPauseになる。
	}
}

//=============================================================================
// 再生判定関数
// pBuffer:音を鳴らしたいサウンドデータのセカンダリバッファ
//=============================================================================
bool IsPlaying(LPDIRECTSOUNDBUFFER8 pBuffer)
{
	DWORD status;

	pBuffer->GetStatus(&status);
	if (status & DSBSTATUS_PLAYING)
	{
		return true;
	}
	return false;
}

//=============================================================================
// サウンド遷移制御関数
//=============================================================================
void SetSound(int no)
{

	// 再生判定
	switch (no)
	{
		// タイトル画面
	case STAGE_TITLE:
	{
		StopSound(BGM_BATTLE);							// 通常戦闘BGMの停止
		StopSound(BGM_CALL_RESULT);							// リザルトBGMの停止
		StopSound(BGM_RESULT);							// リザルトBGMの停止
		PlaySound(BGM_TITLE, E_DS8_FLAG_LOOP);		// タイトルBGMの再生
		break;
	}

	// ゲーム画面
	case STAGE_GAME:
	{
		StopSound(BGM_TITLE);							// タイトルBGMの停止
		StopSound(BGM_CALL_RESULT);						// リザルトBGMの停止
		StopSound(BGM_RESULT);							// リザルトBGMの停止
		PlaySound(BGM_BATTLE, E_DS8_FLAG_LOOP);		// 通常戦闘BGMの再生
		break;
	}

	// リザルト画面
	case STAGE_RESULT:
	{
		StopSound(BGM_BATTLE);								// 通常戦闘BGMの停止
		StopSound(BGM_QUICK);							// 通常戦闘BGMの停止
		PlaySound(BGM_CALL_RESULT, E_DS8_FLAG_NONE);		// リザルトBGMの再生
		break;
	}
	}
}


//=============================================================================
// BGM取得関数
//=============================================================================
LPDIRECTSOUNDBUFFER8 GetBgm(int no)
{
	return(BGM[no]);
}
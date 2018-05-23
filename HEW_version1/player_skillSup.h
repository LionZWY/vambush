//=============================================================================
//
// 弾処理 [playerSupSk.h]
// Author : 朱文渊
// プログラム作成日 : 2018/3/09
//=============================================================================
#ifndef _PLAYERSUPERSKILL_H_
#define _PLAYERSUPERSKILL_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_SUPSKILL_PLAYER			"data/TEXTURE/skill02.png"	// 読み込むテクスチャファイル名
#define	SUPSKILL_SIZE_X			(5.0f)							// ビルボードの幅
#define	SUPSKILL_SIZE_Y			(5.0f)							// ビルボードの高さ
#define	VALUE_MOVE_SUPSKILL		(3.0f)							// 移動速度

#define	MAX_SUPSKILL				(1)							// ビルボード最大数
//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
		D3DXMATRIX				world;
		D3DXVECTOR3				pos;		// 位置
		D3DXVECTOR3				rot;		// 回転
		D3DXVECTOR3				scl;		// スケール
		D3DXVECTOR3				move;		// 移動量
		D3DXVECTOR2				size;
		int						timer;				// タイマー
		int						nIdxShadow;			// 影ID
		bool					bUse;		// 使用しているかどうか
		bool					Track;

} PLAYER_SUPSKILL;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPlayerSupSkill(void);
void UninitPlayerSupSkill(void);
void UpdatePlayerSupSkill(void);
void DrawPlayerSupSkill(void);

int SetPlayerSupSkill(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 size, int timer);
void DeletePlayerSupSkill(int no);
PLAYER_SUPSKILL *GetPlayerSupSkill(int no);
#endif

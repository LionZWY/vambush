//=============================================================================
//
// 弾処理 [playerNorSk.h]
// Author : 朱文渊
// プログラム作成日 : 2018/3/09
//=============================================================================
#ifndef _PLAYERNORMALSKILL_H_
#define _PLAYERNORMALSKILL_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_NORSKILL_PLAYER			"data/TEXTURE/skill00.png"	// 読み込むテクスチャファイル名
#define	NORSKILL_SIZE_X			(5.0f)							// ビルボードの幅
#define	NORSKILL_SIZE_Y			(5.0f)							// ビルボードの高さ
#define	VALUE_MOVE_NORSKILL		(3.0f)							// 移動速度

#define	MAX_NORSKILL				(1)							// ビルボード最大数
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
		int cnt;
		int						nIdxShadow;			// 影ID
		bool					bUse;		// 使用しているかどうか
		bool					Track;

} PLAYER_NORSKILL;
typedef enum
{
	PB_TYPE_NORMAL,
	PB_TYPE_MAX

}PLAYER_NORSKILL_TYPE;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPlayerNorSkill(void);
void UninitPlayerNorSkill(void);
void UpdatePlayerNorSkill(void);
void DrawPlayerNorSkill(void);

int SetPlayerNorSkill(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 size, int timer, int type);
void DeletePlayerNorSkill(int no);
int GetPlayerNorSkillType(void);
PLAYER_NORSKILL *GetPlayerNorSkill(int no);
#endif

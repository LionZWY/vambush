//=============================================================================
//
// 弾処理 [playerskillDef.h]
// Author : 朱文渊 
// プログラム作成日 : 2018/3/09
//=============================================================================
#ifndef _PLAYERSKILLDEF_H_
#define _PLAYERSKILLDEF_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_SKILLDEF_PLAYER			"data/TEXTURE/skill01.png"	// 読み込むテクスチャファイル名
#define	SKILLDEF_SIZE_X			(15.0f)							// ビルボードの幅
#define	SKILLDEF_SIZE_Y			(15.0f)							// ビルボードの高さ
#define	VALUE_MOVE_SKILLDEF		(2.0f)							// 移動速度

#define	MAX_SKILLDEF				(5)							// ビルボード最大数
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
		int cnt;
		int						timer;				// タイマー
		int						nIdxShadow;			// 影ID
		bool					bUse;				// 使用しているかどうか
} PLAYER_SKILLDEF;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPlayerSkillDef(void);
void UninitPlayerSkillDef(void);
void UpdatePlayerSkillDef(void);
void DrawPlayerSkillDef(void);

int SetPlayerSkillDef(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 size, int timer);
void DeletePlayerSkillDef(int no);
int GetPlayerSkillDefType(void);
PLAYER_SKILLDEF *GetPlayerSkillDef(int no);
#endif

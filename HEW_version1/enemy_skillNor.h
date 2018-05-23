//=============================================================================
//
// 特殊弾03処理 [enemyNorSk.h]
// Author : 朱文渊
// プログラム作成日 : 2018/3/09
//=============================================================================
#ifndef _ENEMYNORMALSKILL_H_
#define _ENEMYNORMALSKILL_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_NORSKILL_ENEMY	"data/TEXTURE/skill00.png"		// 読み込むテクスチャファイル名
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
		int						timer;		// タイマー
		int						cnt;
		int						nIdxShadow;	// 影ID
		bool					bUse;		// 使用しているかどうか
		bool					Track;		// 追尾フラグ

} ENEMY_NORSKILL;
typedef enum
{
	EB_TYPE_NORMAL,
	EB_TYPE_MAX

}ENEMY_NORSKILL_TYPE;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEnemyNorSkill(void);
void UninitEnemyNorSkill(void);
void UpdateEnemyNorSkill(void);
void DrawEnemyNorSkill(void);

int SetEnemyNorSkill(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 size, int timer, int type);
void DeleteEnemyNorSkill(int no);
int GetEnemyNorSkillType(void);
ENEMY_NORSKILL *GetEnemyNorSkill(int no);
#endif

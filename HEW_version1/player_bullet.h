//=============================================================================
//
// 通常弾処理 [playerbullet.h]
// Author : 朱文渊
// プログラム作成日 : 2018/3/09
//=============================================================================
#ifndef _PLAYERBULLET_H_
#define _PLAYERBULLET_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_BULLET_PLAYER	"data/TEXTURE/bullet_red.png"	// 読み込むテクスチャファイル名
#define	BULLET_SIZE_X			(10.0f)							// ビルボードの幅
#define	BULLET_SIZE_Y			(10.0f)							// ビルボードの高さ
#define	VALUE_MOVE_BULLET		(2.0f)							// 移動速度

#define	MAX_BULLET				(128)							// ビルボード最大数
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
		bool					bUse;				// 使用しているかどうか
} PLAYER_BULLET;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPlayerBullet(void);
void UninitPlayerBullet(void);
void UpdatePlayerBullet(void);
void DrawPlayerBullet(void);

int SetPlayerBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 size, int timer);
void DeletePlayerBullet(int no);
int GetPlayerBulletType(void);
PLAYER_BULLET *GetPlayerBullet(int no);
#endif

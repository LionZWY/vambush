//=============================================================================
//
// �e���� [enemybullet.h]
// Author : �镶��
// �v���O�����쐬�� : 2018/3/09
//=============================================================================
#ifndef _ENEMYBULLET_H_
#define _ENEMYBULLET_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_BULLET_ENEMY	"data/TEXTURE/bullet_blue.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	BULLET_SIZE_X			(10.0f)							// �r���{�[�h�̕�
#define	BULLET_SIZE_Y			(10.0f)							// �r���{�[�h�̍���
#define	VALUE_MOVE_BULLET		(2.0f)							// �ړ����x

#define	MAX_BULLET				(128)							// �r���{�[�h�ő吔
//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXMATRIX				world;
	D3DXVECTOR3				pos;		// �ʒu
	D3DXVECTOR3				rot;		// ��]
	D3DXVECTOR3				scl;		// �X�P�[��
	D3DXVECTOR3				move;		// �ړ���
	D3DXVECTOR2				size;		// �T�C�Y
	int						timer;		// �^�C�}�[
	int						nIdxShadow;	// �eID
	bool					bUse;		// �g�p���Ă��邩�ǂ���
} ENEMY_BULLET;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEnemyBullet(void);
void UninitEnemyBullet(void);
void UpdateEnemyBullet(void);
void DrawEnemyBullet(void);

int SetEnemyBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 size, int timer);
void DeleteEnemyBullet(int no);
int GetEnemyBulletType(void);
ENEMY_BULLET *GetEnemyBullet(int no);
#endif

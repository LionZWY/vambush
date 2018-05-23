//=============================================================================
//
// �e���� [enemygun.h]
// Author : �镶��
// �v���O�����쐬�� : 2018/3/09
//=============================================================================
#ifndef _ENEMYGUN_H_
#define _ENEMYGUN_H_

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	ENEMYGUN_CAR		"data/MODEL/gun_2.x"						// �ǂݍ��ޏe��

#define	VALUE_MOVE				(5.0f)									// �ړ���					
#define VALUE_ROTATE_ENEMYGUN	(D3DX_PI * 0.05f)						// ��]��
#define ENEMYGUN_ROTTIME		(0.5f)									// ��]���x
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3			pos;				// �e�̈ʒu
	D3DXVECTOR3			rot;				// �e�̌���(��])
	D3DXVECTOR3			rotDest;			// ��]�ړI�ւ̍���
	float				diffRot;
	D3DXVECTOR3			scl;				// �e�̑傫��(�X�P�[��)
	D3DXVECTOR3			face;				// �e�̌���


	D3DXMATRIX			world;				// ���[���h�}�g���b�N�X

}ENEMYGUN;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEnemyGun(void);
void UninitEnemyGun(void);
void UpdateEnemyGun(void);
void DrawEnemyGun(void);
ENEMYGUN *GetEnemyGun(void);
#endif

//=============================================================================
//
// �e���� [playergun.h]
// Author : �镶��
// �v���O�����쐬�� : 2018/3/09
//=============================================================================
#ifndef _PLAYERGUN_H_
#define _PLAYERGUN_H_

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	PLAYERGUN_CAR		"data/MODEL/gun_1.x"							// �ǂݍ��ޏe��

#define	VALUE_MOVE		(5.0f)											// �ړ���
#define	VALUE_ROTATE	(D3DX_PI * 0.02f)								// ��]��
#define VALUE_ROTATE_PLAYERGUN	(D3DX_PI * 0.05f)
#define	NUM_LIGHT		(3)
#define PLAYERGUN_ROTTIME	(0.5f)
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

}PLAYERGUN;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayerGun(void);
void UninitPlayerGun(void);
void UpdatePlayerGun(void);
void DrawPlayerGun(void);
PLAYERGUN *GetPlayerGun(void);
#endif

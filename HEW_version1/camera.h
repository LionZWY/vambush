//=============================================================================
//
// �J�������� [camera.h]
// Author : �镶��
// �v���O�����쐬�� : 2018/3/09
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"


typedef struct 
{
	D3DXVECTOR3		posEye;				// �J�����̎��_
	D3DXVECTOR3		posAt;				// �J�����̒����_
	D3DXVECTOR3		vecUp;				// �J�����̏����
	D3DXVECTOR3		rot;				// �J�����̉�]
	float			EyeToAtDistance;	// �J�����̎��_�ƒ����_�̋���
	D3DXMATRIX		view;				// �r���[�}�g���b�N�X
	D3DXMATRIX		proj;				// �v���W�F�N�V�����}�g���b�N�X
	D3DXVECTOR3		PTPVec;				// �v���C���[�Ԃ̃x�N�g��
	float			PTPDistance;		// �v���C���[�Ԃ̋���

}CAMERA;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);

void SetCamera(void);
D3DXVECTOR3 GetRotCamera(void);
D3DXMATRIX GetMtxView(void);

CAMERA *GetCamera(void);
#endif

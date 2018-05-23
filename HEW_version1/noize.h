//=============================================================================
//
// �������� [noize.h]
// Author : �镶��
// �v���O�����쐬�� : 2018/3/09
//=============================================================================
#ifndef _NOIZE_H_
#define _NOIZE_H_

#include "main.h"

//**************************************
// ���
//**************************************
enum
{
	NOIZETYPE_NOIZE_PLAYER = 0,		// �v���C���[�̒e�̔���
	NOIZETYPE_NOIZE_ENEMY,			// �G�̒e�̔���
	NOIZETYPE_MAX
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitNoize(void);
void UninitNoize(void);
void UpdateNoize(void);
void DrawNoize(void);

int SetNoize(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nType);

#endif

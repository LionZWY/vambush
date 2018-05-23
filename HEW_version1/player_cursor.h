//=============================================================================
//
// �J�[�\������ [cursor.h]
// Author : �镶��
// �v���O�����쐬�� : 2018/3/09
//=============================================================================
#ifndef _CURSOR_PLAYER_H_
#define _CURSOR_PLAYER_H_

#include "main.h"

typedef struct 
{
	D3DXMATRIX				world;				// ���[���h�}�g���b�N�X
	D3DXVECTOR3				pos;				// �ʒu
	D3DXVECTOR3				scl;				// �X�P�[��
	D3DXVECTOR3				move;				// �ړ���
	D3DXVECTOR3				rot;				// ��]��
	int						shadowId;			// �eID
	float					SizeShadow;			// �e�̃T�C�Y
	D3DXCOLOR				colShadow;			// �e�̐F
	VERTEX_3D               *vectex;
	D3DXVECTOR2				size;				// �J�[�\���̃T�C�Y
	float					PCtoEPDistance;		// �J�[�\�����王�_�ւ̋���
	bool					lock;

}CURSOR_PLAYER;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitCursorPlayer(void);
void UninitCursorPlayer(void);
void UpdateCursorPlayer(void);
void DrawCursorPlayer(void);
CURSOR_PLAYER *GetCursorPlayer(void);
#endif

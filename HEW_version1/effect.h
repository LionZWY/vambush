//=============================================================================
//
// �G�t�F�N�g���� [effect.h]
// Author : �镶��
// �v���O�����쐬�� : 2018/3/09
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{

			D3DXMATRIX			world;
			D3DXVECTOR3			pos;		// �ʒu
			D3DXVECTOR3			rot;		// ��]
			D3DXVECTOR3			scl;		// �X�P�[��
			D3DXVECTOR3			move;		// �ړ���
			D3DXCOLOR			col;		// �F
			D3DXVECTOR2			size;
			int					timer;		// �^�C�}�[
			float				nDecAlpha;	// �����l
			bool				bUse;		// �g�p���Ă��邩�ǂ���
} EFFECT;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);

int SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, D3DXVECTOR2 size, int timer);

#endif

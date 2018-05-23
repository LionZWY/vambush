//=============================================================================
//
// �G�l�~�[���� [enemy.h]
// Author : �镶��
// �v���O�����쐬�� : 2018/3/09
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_ENEMY_W		"data/TEXTURE/enemy01.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_ENEMY_S		"data/TEXTURE/enemy02.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_ENEMY_A		"data/TEXTURE/enemy00.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_ENEMY_D		"data/TEXTURE/enemy03.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	ENEMY_SIZE_X		(20.0f)						// �r���{�[�h�̕�
#define	ENEMY_SIZE_Y		(20.0f)						// �r���{�[�h�̍���
#define	VALUE_MOVE_ENEMY	(0.30f)						// �ړ����x
#define	VALUE_JUMP_ENEMY			(10.0f)				// �W�����v��
#define	VALUE_GRAVITY_ENEMY			(0.45f)				// �d��
#define	RATE_REGIST_ENEMY			(0.075f)			// ��R�W��
#define	RATE_REFRECT_ENEMY			(-0.90f)			// ���ˌW��
#define ENEMY_HP_MAX				(150.0f)			// HP�ő�l
//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct 
{
	D3DXMATRIX				world;				// ���[���h�}�g���b�N�X
	D3DXVECTOR3				pos;				// �ʒu
	D3DXVECTOR3				scl;				// �X�P�[��
	D3DXVECTOR3				move;				// �ړ���
	D3DXVECTOR3				rot;				// ��]��
	int						hp;					// hp
	int						kill;				// �K�E�Z�Q�[�W
	int						shadowId;			// �eID
	D3DXVECTOR2				SizeShadow;			// �e�̃T�C�Y
	D3DXCOLOR				colShadow;			// �e�̐F
	VERTEX_3D               *vectex;			// ���_�o�b�t�@�ւ̃|�C���^
	bool					damage;				// �_���[�W�t���O
	bool					norSk;				// ����e�̃t���O
	int						timeSk;				// ����e�̃^�C���J�E���g
	bool					defSk;				// ����e�̃t���O
	int						timeDefSk;			// ����e�̃^�C���J�E���g
	bool					supSk;				// ����e�̃t���O
											

}ENEMY;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
ENEMY *GetEnemy(void);
#endif

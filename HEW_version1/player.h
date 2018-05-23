//=============================================================================
//
// �r���{�[�h���� [player.h]
// Author : �镶��
// �v���O�����쐬�� : 2018/3/09
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_PLAYER_W			"data/TEXTURE/player01.png"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_PLAYER_S			"data/TEXTURE/player02.png"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_PLAYER_A			"data/TEXTURE/player00.png"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_PLAYER_D			"data/TEXTURE/player03.png"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	PLAYER_SIZE_X				(20.0f)							// �r���{�[�h�̕�
#define	PLAYER_SIZE_Y				(20.0f)							// �r���{�[�h�̍���
#define	VALUE_MOVE_PLAYER			(0.30f)							// �ړ����x
#define	VALUE_JUMP_PLAYER			(10.0f)							// �W�����v��
#define	VALUE_GRAVITY_PLAYER		(0.45f)							// �d��
#define	RATE_REGIST_PLAYER			(0.075f)						// ��R�W��
#define	RATE_REFRECT_PLAYER			(-0.90f)						// ���ˌW��
#define PLAYER_HP_MAX				(150)							// HP�ő�l
#define TEXTURE_PATTERN_DIVIDE_X	(4)
#define TEXTURE_PATTERN_DIVIDE_Y	(3)
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
	bool					defSk;				// ����e�̃^�C���J�E���g
	int						timeDefSk;			// ����e�̃t���O
	int						timeSk;				// ����e�̃^�C���J�E���g
	bool					supSk;				// ����e�̃t���O

}PLAYER;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER *GetPlayer(void);
#endif

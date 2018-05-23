//=============================================================================
//
// CALL��ʏ��� [call.h]
// Author : ���ˌ��j��
// �v���O�����쐬�� : 2018/3/09
//
//=============================================================================

// ���d�C���N���[�h�h�~�̈�
#ifndef _CALL_H_
#define _CALL_H_

// ���C�u�������}�N���g�p�̈�
#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

#define START_TIME_CALL					(4)														// �J�n�܂ł̕b��

#define	CALL_BASE_TEXTURE				("data/TEXTURE/deg_number3.png")						// �ǂݍ��ރe�N�X�`���t�@�C����
#define	CALL_BASE_SIZE_X				(200/2.0f)											// �e�N�X�`���̕�
#define	CALL_BASE_SIZE_Y				(250/2)												// �e�N�X�`���̍���
#define CALL_BASE_POS					D3DXVECTOR3(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f,0.0f)			// HP�o�[���n�̈ʒu

#define CALL_ANIM_PATTERN_DIVIDE_X		(10)												// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define CALL_ANIM_PATTERN_DIVIDE_Y		(1)													// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define CALL_ANIM_PATTERN_NUM			(CALL_ANIM_PATTERN_DIVIDE_X*CALL_ANIM_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����

#define	CALL_BATTLE_TEXTURE				("data/TEXTURE/�o�g���X�^�[�g.png")						// �ǂݍ��ރe�N�X�`���t�@�C����
#define	CALL_BATTLE_SIZE_X				(600/2.0f)											// �e�N�X�`���̕�
#define	CALL_BATTLE_SIZE_Y				(300/2)												// �e�N�X�`���̍���



// �^�C�g���\���̐���}�N��
enum
{
	CALL_NUM,							// HP�o�[���n
	CALL_BATTLE,		

	CALL_MAX,								// CALL�\���̍ő吔
};

//=============================================================================
// �\���̐錾
//=============================================================================

// �^�C�g���\����
typedef struct
{

	bool use;											// �`�搧��ϐ� true:�g�p false:���g�p

	int						PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[�ϐ�

	D3DXVECTOR3				pos;						// ���W�i�[�ϐ�
	D3DXVECTOR3				rot;						// ��]�i�[�ϐ�

	LPDIRECT3DTEXTURE9		Texture;					// �e�N�X�`���ւ̃|�C���^
	VERTEX_2D				vertex[NUM_VERTEX];			// ���_���i�[���[�N

}CALL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitCall(int type);								// �����������֐�
void UninitCall(void);									// �I�������֐�
void UpdateCall(void);									// �X�V�����֐�
void DrawCall(void);										// �`�揈���֐�

void SetTextureCall(int no, int cntPattern);				// �e�N�X�`�����W�̐ݒ�
bool *GetStartFlag(void);

#endif

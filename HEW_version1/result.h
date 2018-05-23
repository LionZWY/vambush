//=============================================================================
//
// �^�C�g����ʏ��� [result.h]
// Author : ���ˌ��j��
// �v���O�����쐬�� : 2018/3/09
//
//=============================================================================

// ���d�C���N���[�h�h�~�̈�
#ifndef _RESULT_H_
#define _RESULT_H_

// �}�N�������C�u�����g�p�̈�
#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

#define RESULT_EFFECT_SPEED				(2)		// �_�ő��x���x
#define RESULT_SPEED					(3)		// �_�ő��x���x
#define RESULT_RANK_SPEED				(32.0f)	// �_�ő��x���x
#define RESULT_BGM_TIME					(9)		

#define	RESULT_BASE_TEXTURE				("data/TEXTURE/vambush_title01.png")						// �ǂݍ��ރe�N�X�`���t�@�C����
#define	RESULT_BASE_LIGHT_TEXTURE		("data/TEXTURE/vambush_title03.png")						// �ǂݍ��ރe�N�X�`���t�@�C����
#define	RESULT_BOAD_AI_TEXTURE			("data/TEXTURE/1Pwin00.png")								// �ǂݍ��ރe�N�X�`���t�@�C����
#define	RESULT_BOAD_VIRUS_TEXTURE		("data/TEXTURE/2Pwin00.png")								// �ǂݍ��ރe�N�X�`���t�@�C����

#define	RESULT_BASE_SIZE_X				(SCREEN_WIDTH/2.0f)											// �e�N�X�`���̕�
#define	RESULT_BASE_SIZE_Y				(SCREEN_HEIGHT/2.0f)										// �e�N�X�`���̍���
#define RESULT_BASE_POS					D3DXVECTOR3(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f,0.0f)		// ���l�̈ʒu

#define	RESULT_AI_TEXTURE				("data/TEXTURE/hew_player01.png")									// �ǂݍ��ރe�N�X�`���t�@�C����
#define	RESULT_AI_SIZE_X				(1300/2)														// �e�N�X�`���̕�
#define	RESULT_AI_SIZE_Y				(722/2)														// �e�N�X�`���̍���
#define RESULT_AI_POS					D3DXVECTOR3(641.0f,326.0f,0.0f)							// �T�t�̈ʒu

#define	RESULT_VIRUS_TEXTURE			("data/TEXTURE/hew_enemy00.png")							// �ǂݍ��ރe�N�X�`���t�@�C����
#define	RESULT_VIRUS_SIZE_X				(928/2)														// �e�N�X�`���̕�
#define	RESULT_VIRUS_SIZE_Y				(754/2)														// �e�N�X�`���̍���
#define RESULT_VIRUS_POS				D3DXVECTOR3(464.0f,370.0f,0.0f)								// �A�C�r�X�̈ʒu

#define	RESULT_AI_RANK_TEXTURE			("data/TEXTURE/1Pwin01.png")									// �ǂݍ��ރe�N�X�`���t�@�C����
#define	RESULT_VIRUS_RANK_TEXTURE		("data/TEXTURE/2Pwin01.png")									// �ǂݍ��ރe�N�X�`���t�@�C����

#define	RESULT_RANK_SIZE_X				(580/2)														// �e�N�X�`���̕�
#define	RESULT_RANK_SIZE_Y				(194/2)														// �e�N�X�`���̍���
#define RESULT_RANK_POS					D3DXVECTOR3(1280.0f,325.0f,0.0f)								// �]���̈ʒu

#define	RESULT_RANK_EFFECT_SIZE_X		(595/2)														// �e�N�X�`���̕�
#define	RESULT_RANK_EFFECT_SIZE_Y		(209/2)														// �e�N�X�`���̍���


#define	RESULT_BLACK_S_TEXTURE			("data/TEXTURE/window03.png")							// �ǂݍ��ރe�N�X�`���t�@�C����
#define	RESULT_BLACK_S_SIZE_X			(310/2)														// �e�N�X�`���̕�
#define	RESULT_BLACK_S_SIZE_Y			(318/2)														// �e�N�X�`���̍���
#define RESULT_BLACK_S_POS				D3DXVECTOR3(SCREEN_WIDTH/2.0f,500.0f,0.0f)					// �����j���[�̈ʒu

#define	RESULT_INIT_TEXTURE				("data/TEXTURE/���Ȃ���.png")								// �ǂݍ��ރe�N�X�`���t�@�C����
#define	RESULT_INIT_SIZE_X				(280/2)														// �e�N�X�`���̕�
#define	RESULT_INIT_SIZE_Y				(70/2)														// �e�N�X�`���̍���
#define RESULT_INIT_POS					D3DXVECTOR3(SCREEN_WIDTH/2.0f,445.,0.0f)					// ���Ȃ����̈ʒu

#define	RESULT_FINISH_TEXTURE			("data/TEXTURE/�����.png")									// �ǂݍ��ރe�N�X�`���t�@�C����
#define	RESULT_FINISH_SIZE_X			(180/2)														// �e�N�X�`���̕�
#define	RESULT_FINISH_SIZE_Y			(70/2)														// �e�N�X�`���̍���
#define RESULT_FINISH_POS				D3DXVECTOR3(SCREEN_WIDTH/2.0f,555.0f,0.0f)					// �����̈ʒu

#define	RESULT_ANY_EFFECT_SIZE_X		(290/2)														// �e�N�X�`���̕�
#define	RESULT_ANY_EFFECT_SIZE_Y		(80/2)														// �e�N�X�`���̍���
#define	RESULT_FINISH_EFFECT_SIZE_X		(190/2)														// �e�N�X�`���̕�
#define	RESULT_FINISH_EFFECT_SIZE_Y		(80/2)														// �e�N�X�`���̍���


// �^�C�g���\���̐���}�N��
enum
{
	RESULT_BASE,							// �w�i

	RESULT_BOAD_AI,							// �����t���O�v���C���[
	RESULT_AI,								// �v���C���[
	RESULT_AI_RANK,							// �]���v���C���[
	RESULT_AI_RANK_EFFECT,					// �G�t�F�N�g:�]���v���C���[

	RESULT_BOAD_VIRUS,						// �����t���O�E�C���X
	RESULT_VIRUS,							// �E�C���X
	RESULT_VIRUS_RANK,						// �]���E�C���X
	RESULT_VIRUS_RANK_EFFECT,				// �G�t�F�N�g:�]���E�C���X

	RESULT_BASE_LIGHT,						// �w�i�n�C���C�g

	RESULT_BLACK_S,							// �J�[�\���E�C���h�E�\��
	RESULT_INIT,							// UI:"���Ȃ���"
	RESULT_INIT_EFFECT,						// UI�G�t�F�N�g:"���Ȃ���"
	RESULT_FINISH,							// UI:"�����"
	RESULT_FINISH_EFFECT,					// UI�G�t�F�N�g:"�����"
	RESULT_MAX,								// �\���̍ő吔
};


// ���U���g�J�[�\������}�N��
enum
{
	RESULT_UI_INIT,					// UI:"���Ȃ���"
	RESULT_UI_FINISH,				// UI:"�����"
	RESULT_UI_MAX,					// UI�J�[�\���ő吔
};

//=============================================================================
// �\���̐錾
//=============================================================================

// �^�C�g���\����
typedef struct
{

	bool use;											// �`�搧��ϐ�

	D3DXVECTOR3				pos;						// ���W�i�[�ϐ�

	LPDIRECT3DTEXTURE9		Texture;					// �e�N�X�`���ւ̃|�C���^�ϐ�
	VERTEX_2D				vertex[NUM_VERTEX];			// ���_���i�[���[�N�ϐ�

}RESULT;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitResult(int type);							// �����������֐�
void UninitResult(void);								// �I�������֐�
void UpdateResult(void);								// �X�V�����֐�
void DrawResult(void);									// �`�揈���֐�
bool *GetWinFlag(void);									// �����t���O�擾�֐�

#endif

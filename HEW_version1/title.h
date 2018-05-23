//=============================================================================
//
// �^�C�g����ʏ��� [title.h]
// Author : ���ˌ��j��
// �v���O�����쐬�� : 2018/3/09
//
//=============================================================================


// ���d�C���N���[�h�h�~�̈�
#ifndef _TITLE_H_
#define _TITLE_H_

// �}�N�������C�u�����g�p�̈�
#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

#define INIT_EFFECT					(1)												// �G�t�F�N�g��RGB�̏����l
#define ALPHA_TEST					(125)											// �A���t�@�e�X�g�̃��̒l
#define ALPHA_BASE					(1)												// �e�N�X�`���̃��̒l
#define ALPHA_MAX					(255)											// ���̒l�̍ő�l
#define EFFECT_SPEED				(2)												// �_�ő��x���x

#define B_ALPHA_BASE				(0)												// �e�N�X�`���̃��̒l
#define B_ALPHA_MAX					(100)											// ���̒l�̍ő�l
#define B_EFFECT_SPEED				(1)												// �_�ő��x���x

#define	TITLE_BASE_TEXTURE			("data/TEXTURE/vambush_title01.png")					// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TITLE_BASE_SIZE_X			(SCREEN_WIDTH/2)											// �e�N�X�`���̕�
#define	TITLE_BASE_SIZE_Y			(SCREEN_HEIGHT/2)											// �e�N�X�`���̍���
#define TITLE_BASE_POS				D3DXVECTOR3(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f,0.0f)	// �^�C�g���w�i�̈ʒu

#define	TITLE_BASE_LIGHT_TEXTURE	("data/TEXTURE/vambush_title03.png")					// �ǂݍ��ރe�N�X�`���t�@�C����

#define	TITLE_EFFECT_TEXTURE		("data/TEXTURE/vambush_title00.png")					// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TITLE_EFFECT_SIZE_X			(880/2)													// �e�N�X�`���̕�
#define	TITLE_EFFECT_SIZE_Y			(732/2)													// �e�N�X�`���̍���
#define TITLE_EFFECT_POS			D3DXVECTOR3(637.0f,367.0f,0.0f)							// �^�C�g���w�i�G�t�F�N�g�̈ʒu

#define	TITLE_AI_TEXTURE			("data/TEXTURE/hew_player01.png")						// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TITLE_AI_SIZE_X				(552/2)													// �e�N�X�`���̕�
#define	TITLE_AI_SIZE_Y				(488/2)													// �e�N�X�`���̍���
#define TITLE_AI_POS				D3DXVECTOR3(1024.0f,508.0f,0.0f)							// �L�����N�^�[:AI�̈ʒu

#define	TITLE_VIRUS_TEXTURE			("data/TEXTURE/hew_enemy00.png")						// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TITLE_VIRUS_SIZE_X			(540/2)													// �e�N�X�`���̕�
#define	TITLE_VIRUS_SIZE_Y			(494/2)													// �e�N�X�`���̍���
#define TITLE_VIRUS_POS				D3DXVECTOR3(266.0f,198.0f,0.0f)							// �L�����N�^�[:�E�C���X�̈ʒu

#define	TITLE_LOGO_TEXTURE			("data/TEXTURE/vambush_titlelogo.png")					// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TITLE_LOGO_SIZE_X			(866/2)													// �e�N�X�`���̕�
#define	TITLE_LOGO_SIZE_Y			(280/2)													// �e�N�X�`���̍���
#define TITLE_LOGO_POS				D3DXVECTOR3(SCREEN_WIDTH/2.0f,324.0f,0.0f)			// �^�C�g�����S�̈ʒu

#define	TITLE_ANY_TEXTURE			("data/TEXTURE/PRESS_BUTTON.png")				// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TITLE_ANY_SIZE_X			(392/2)											// �e�N�X�`���̕�
#define	TITLE_ANY_SIZE_Y			(130/2)											// �e�N�X�`���̍���
#define TITLE_ANY_POS				D3DXVECTOR3(625.0f,557.0f,0.0f)					// UI:"�{�^���������Ă�"

#define	TITLE_START_TEXTURE			("data/TEXTURE/�͂��߂�.png")					// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TITLE_START_SIZE_X			(354/2)											// �e�N�X�`���̕�
#define	TITLE_START_SIZE_Y			(90/2)											// �e�N�X�`���̍���
#define TITLE_START_POS				D3DXVECTOR3(637.0f,506.0f,0.0f)		// UI:"�͂��߂�"

#define	TITLE_CREDIT_TEXTURE		("data/TEXTURE/�������.png")				// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TITLE_CREDIT_SIZE_X			(354/2)											// �^�C�g���̕�
#define	TITLE_CREDIT_SIZE_Y			(90/2)											// �^�C�g���̍���
#define TITLE_CREDIT_POS			D3DXVECTOR3(637.0f,610.0f,0.0f)					// UI:"�N���W�b�g"

#define	TITLE_BOAD_TEXTURE			("data/TEXTURE/������@.JPG")							// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TITLE_BOAD_SIZE_X			(1100/2)													// �e�N�X�`���̕�
#define	TITLE_BOAD_SIZE_Y			(650/2)														// �e�N�X�`���̍���
#define TITLE_BOAD_POS				D3DXVECTOR3(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f,0.0f)		// UI:"�N���W�b�gED"(�N���W�b�g�e�N�X�`��)

#define	TITLE_ANY_EFFECT_SIZE_X		(404/2)											// �e�N�X�`���̕�
#define	TITLE_ANY_EFFECT_SIZE_Y		(140/2)											// �e�N�X�`���̍���

#define	TITLE_START_EFFECT_SIZE_X	(364/2)											// �e�N�X�`���̕�
#define	TITLE_START_EFFECT_SIZE_Y	(100/2)											// �e�N�X�`���̍���


#define COLOR_WHITE					D3DCOLOR_RGBA(255, 255, 255, 255);				// UI�J�[�\���̐F:��
#define COLOR_YELLOW				D3DCOLOR_RGBA(255, 175, 0, 255);				// UI�J�[�\���̐F:���F
	#define COLOR_RED				D3DCOLOR_RGBA(255, 0, 0, 255);				// UI�J�[�\���̐F:�ԐF
	#define COLOR_BULE				D3DCOLOR_RGBA(0, 0, 255, 255);				// UI�J�[�\���̐F:�F

// �^�C�g���\���̐���}�N��
enum
{
	TITLE_BASE,						// �^�C�g���w�i
	TITLE_BASE_LIGHT,				// �n�C���C�g
	TITLE_EFFECT,					// �^�C�g���w�i�G�t�F�N�g
	TITLE_AI,						// �L�����N�^�[:AI
	TITLE_VIRUS,					// �L�����N�^�[:�E�C���X
	TITLE_LOGO,						// �^�C�g�����S

	TITLE_ANY,						// UI:"�{�^���������Ă�"
	TITLE_ANY_EFFECT,				// UI�G�t�F�N�g:"�{�^���������Ă�"
	TITLE_START,					// UI:"�͂��߂�"
	TITLE_START_EFFECT,				// UI�G�t�F�N�g:"�͂��߂�"
	TITLE_CREDIT,					// UI:"�������"
	TITLE_CREDIT_EFFECT,			// UI�G�t�F�N�g:"�������"

	TITLE_BOAD,						// UI:"�N���W�b�gED"(�N���W�b�g�e�N�X�`��)
	TITLE_MAX,						// �^�C�g���\���̍ő吔
};

// UI�J�[�\������}�N��
enum
{
	TITLE_UI_START,					// UI:"�͂��߂�"
	TITLE_UI_CREDIT,				// UI:"�N���W�b�g"
	TITLE_UI_MAX,					// UI�J�[�\���ő吔
};


//=============================================================================
// �\���̐錾
//=============================================================================

// �^�C�g���\����
typedef struct
{

	bool					use;						// �`�搧��ϐ�

	D3DXVECTOR3				pos;						// ���W�i�[�ϐ�

	LPDIRECT3DTEXTURE9		Texture;					// �e�N�X�`���ւ̃|�C���^�ϐ�
	VERTEX_2D				vertex[NUM_VERTEX];			// ���_���i�[���[�N�ϐ�

}TITLE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitTitle(int type);							// �����������֐�
void UninitTitle(void);									// �I�������֐�
void UpdateTitle(void);									// �X�V�����֐�
void DrawTitle(void);									// �`�揈���֐�

#endif

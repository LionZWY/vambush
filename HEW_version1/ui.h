//=============================================================================
//
// UI��ʏ��� [ui.h]
// Author : ���ˌ��j��
// �v���O�����쐬�� : 2018/3/09
//
//=============================================================================

// ���d�C���N���[�h�h�~�̈�
#ifndef _UI_H_
#define _UI_H_

// ���C�u�������}�N���g�p�̈�
#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

#define UI_EFFECT_BASE				(150)												// UI�G�t�F�N�g�̃��l
#define UI_EFFECT_SPEED				(5)													// �_�ő��x���x

#define	UI_BASE_TEXTURE				("data/TEXTURE/life_bg00.png")						// �ǂݍ��ރe�N�X�`���t�@�C����
#define	UI_BASE_SIZE_X				(1280/2.0f)											// �e�N�X�`���̕�
#define	UI_BASE_SIZE_Y				(232/2)												// �e�N�X�`���̍���
#define UI_BASE_POS					D3DXVECTOR3(SCREEN_WIDTH/2.0f,125.0f,0.0f)			// HP�o�[���n�̈ʒu

#define	UI_HP_TEXTURE				("data/TEXTURE/life_bar.png")						// �ǂݍ��ރe�N�X�`���t�@�C����
#define	UI_HP_FRAME_SIZE_X			(582/2)											// �e�N�X�`���̕�
#define	UI_HP_FRAME_SIZE_Y			(72/2)												// �e�N�X�`���̍���
#define UI_HP_FRAME_POS				D3DXVECTOR3(400.0f,59.0f,0.0f)						// �v���C���[HP�o�[�g�̈ʒu
#define UI_EHP_FRAME_POS			D3DXVECTOR3(931.0f,59.0f,0.0f)					// �G�l�~�|HP�o�[�g�̈ʒu

#define	UI_AI_TEXTURE				("data/TEXTURE/ui_player.png")						// �ǂݍ��ރe�N�X�`���t�@�C����
#define	UI_AI_SIZE_X				(148/2)												// �e�N�X�`���̕�
#define	UI_AI_SIZE_Y				(138/2)												// �e�N�X�`���̍���
#define UI_AI_POS					D3DXVECTOR3(64.0f,58.0f,0.0f)						// �L�����N�^�[:AI�̈ʒu

#define	UI_VIRUS_TEXTURE			("data/TEXTURE/ui_enemy.png")						// �ǂݍ��ރe�N�X�`���t�@�C����
#define	UI_VIRUS_SIZE_X				(140/2)												// �e�N�X�`���̕�
#define	UI_VIRUS_SIZE_Y				(134/2)												// �e�N�X�`���̍���
#define UI_VIRUSE_POS				D3DXVECTOR3(1207.0f,59.0f,0.0f)						// �L�����N�^�[:�E�C���X�̈ʒu

#define	UI_HP_SIZE_X				(435.0f)											// �e�N�X�`���̕�
#define	UI_HP_SIZE_Y				(60)												// �e�N�X�`���̍���
#define UI_HP_POS					D3DXVECTOR3(103.0f,29.0f,0.0f)						// HP�o�[�̈ʒu
#define UI_EHP_POS					D3DXVECTOR3(1177.0f,29.0f,0.0f)						// �G�l�~�|HP�o�[�̈ʒu

#define	UI_FRAME_TEXTURE			("data/TEXTURE/window01.png")						// �ǂݍ��ރe�N�X�`���t�@�C����
#define	UI_FRAME_SIZE_X				(198/2)												// �e�N�X�`���̕�
#define	UI_FRAME_SIZE_Y				(114/2)												// �e�N�X�`���̍���
#define UI_FRAME_POS				D3DXVECTOR3(640.0f,60.0f,0.0f)						// �^�C�}�[�̘g�̈ʒu

#define	UI_FRAME_AI_TEXTURE			("data/TEXTURE/window02.png")						// �ǂݍ��ރe�N�X�`���t�@�C����
#define	UI_FRAME_AI_SIZE_X			(296/2)												// �e�N�X�`���̕�
#define	UI_FRAME_AI_SIZE_Y			(206/2)												// �e�N�X�`���̍���
#define UI_FRAME_AI_POS				D3DXVECTOR3(155.0f,612.0f,0.0f)						// �Z�gAI�̈ʒu

#define	UI_FRAME_VIRUS_TEXTURE		("data/TEXTURE/window00.png")						// �ǂݍ��ރe�N�X�`���t�@�C����
#define UI_FRAME_VIRUS_POS			D3DXVECTOR3(1125.0f,612.0f,0.0f)					// �Z�g�E�C���X�̈ʒu


#define	UI_SKILL_A_TEXTURE			("data/TEXTURE/skill00_icon.png")						// �ǂݍ��ރe�N�X�`���t�@�C����
#define	UI_SKILL_B_TEXTURE			("data/TEXTURE/skill01_icon.png")						// �ǂݍ��ރe�N�X�`���t�@�C����
#define	UI_SKILL_C_TEXTURE			("data/TEXTURE/skill02_UI.png")						// �ǂݍ��ރe�N�X�`���t�@�C����

#define	UI_SKILL_SIZE_X				(42/2)												// �e�N�X�`���̕�
#define	UI_SKILL_SIZE_Y				(48/2)												// �e�N�X�`���̍���

#define	UI_SKILL_C_SIZE_X			(70/2)												// �e�N�X�`���̕�
#define	UI_SKILL_C_SIZE_Y			(82/2)												// �e�N�X�`���̍���

#define UI_SKILL_A_POS				D3DXVECTOR3(152.0f,547.0f,0.0f)						// �X�L��1�̈ʒu
#define UI_SKILL_B_POS				D3DXVECTOR3(152.0f,599.0f,0.0f)						// �X�L��2�̈ʒu
#define UI_SKILL_C_POS				D3DXVECTOR3(46.0f,665.0f,0.0f)						// �X�L��3�̈ʒu
#define UI_ESKILL_A_POS				D3DXVECTOR3(1122.0f,547.0f,0.0f)						// �X�L��1�̈ʒu
#define UI_ESKILL_B_POS				D3DXVECTOR3(1122.0f,599.0f,0.0f)						// �X�L��2�̈ʒu
#define UI_ESKILL_C_POS				D3DXVECTOR3(1016.0f,665.0f,0.0f)						// �X�L��3�̈ʒu

#define	UI_SKILL_KEY_TEXTURE		("data/TEXTURE/skill00_UI.png")						// �ǂݍ��ރe�N�X�`���t�@�C����
#define	UI_SKILL_BKEY_TEXTURE		("data/TEXTURE/skill01_UI.png")						// �ǂݍ��ރe�N�X�`���t�@�C����

#define	UI_SKILL_KEY_SIZE_X			(108/2)												// �e�N�X�`���̕�
#define	UI_SKILL_KEY_SIZE_Y			(32/2)												// �e�N�X�`���̍���
#define UI_SKILL_KEY_POS			D3DXVECTOR3(70.0f,545.0f,0.0f)						// �X�L��1�̈ʒu
#define UI_SKILL_BKEY_POS			D3DXVECTOR3(70.0f,597.0f,0.0f)						// �X�L��2�̈ʒu
#define UI_ESKILL_KEY_POS			D3DXVECTOR3(1040.0f,545.0f,0.0f)						// �X�L��1�̈ʒu
#define UI_ESKILL_BKEY_POS			D3DXVECTOR3(1040.0f,597.0f,0.0f)						// �X�L��2�̈ʒu

#define	UI_SKILL_CROSS_TEXTURE		("data/TEXTURE/deg_X.png")						// �ǂݍ��ރe�N�X�`���t�@�C����

#define	UI_SKILL_CROSS_SIZE_X		(28/2)												// �e�N�X�`���̕�
#define	UI_SKILL_CROSS_SIZE_Y		(28/2)												// �e�N�X�`���̍���
#define UI_SKILL_CROSS_POS			D3DXVECTOR3(199.0f,545.0f,0.0f)						// �X�L��1�̈ʒu
#define UI_SKILL_BCROSS_POS			D3DXVECTOR3(199.0f,597.0f,0.0f)						// �X�L��2�̈ʒu
#define UI_ESKILL_CROSS_POS			D3DXVECTOR3(1169.0f,545.0f,0.0f)						// �X�L��1�̈ʒu
#define UI_ESKILL_BCROSS_POS		D3DXVECTOR3(1169.0f,597.0f,0.0f)						// �X�L��2�̈ʒu

#define	UI_SKILL_NUM_TEXTURE		("data/TEXTURE/deg_number3.png")						// �ǂݍ��ރe�N�X�`���t�@�C����

#define	UI_SKILL_NUM_SIZE_X			(42/2)												// �e�N�X�`���̕�
#define	UI_SKILL_NUM_SIZE_Y			(64/2)												// �e�N�X�`���̍���
#define UI_SKILL_NUM_POS			D3DXVECTOR3(258.0f,546.0f,0.0f)						// �X�L��1�̈ʒu
#define UI_SKILL_BNUM_POS			D3DXVECTOR3(258.0f,601.0f,0.0f)						// �X�L��2�̈ʒu
#define UI_ESKILL_NUM_POS			D3DXVECTOR3(1228.0f,546.0f,0.0f)						// �X�L��1�̈ʒu
#define UI_ESKILL_BNUM_POS			D3DXVECTOR3(1228.0f,601.0f,0.0f)						// �X�L��2�̈ʒu

#define UI_ANIM_PATTERN_DIVIDE_X	(10)												// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define UI_ANIM_PATTERN_DIVIDE_Y	(1)													// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define UI_ANIM_PATTERN_NUM			(UI_ANIM_PATTERN_DIVIDE_X*UI_ANIM_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����

#define	UI_SKILL_PAR_TEXTURE		("data/TEXTURE/deg_percent.png")						// �ǂݍ��ރe�N�X�`���t�@�C����

#define	UI_SKILL_PAR_SIZE_X			(32/2)												// �e�N�X�`���̕�
#define	UI_SKILL_PAR_SIZE_Y			(44/2)												// �e�N�X�`���̍���
#define UI_SKILL_PAR_POS			D3DXVECTOR3(277.0f,678.0f,0.0f)						// �X�L��1�̈ʒu
#define UI_ESKILL_PAR_POS			D3DXVECTOR3(1247.0f,678.0f,0.0f)						// �X�L��1�̈ʒu


// �^�C�g���\���̐���}�N��
enum
{
	UI_BASE,							// HP�o�[���n
	UI_HP_FRAME,						// �v���C���[HP�o�[�g
	UI_EHP_FRAME,						// �G�l�~�|HP�o�[�g
	UI_HP,								// �v���C���[HP�o�[
	UI_HP_EFFECT,						// �v���C���[HP�o�[�G�t�F�N�g
	UI_EHP,								// �G�l�~�|HP�o�[
	UI_EHP_EFFECT,						// �G�l�~�|HP�o�[�G�t�F�N�g
	UI_AI,								// �L�����N�^�[:AI
	UI_VIRUS,							// �L�����N�^�[:�E�C���X

	UI_FRAME,							// �^�C�}�[�̘g
	UI_FRAME_AI,						// �Z�gAI
	UI_FRAME_VIRUS,						// �Z�g�E�C���X

	UI_SKILL_A,							// �X�L��1�A�C�R��
	UI_SKILL_KEY,						// �X�L��1�L�[
	UI_SKILL_CROSS,						// �X�L��1���Z�q
	UI_SKILL_NUM,						// �X�L��1����

	UI_SKILL_B,							// �X�L��2�A�C�R��
	UI_SKILL_BKEY,						// �X�L��2�L�[
	UI_SKILL_BCROSS,					// �X�L��2���Z�q
	UI_SKILL_BNUM,						// �X�L��2����

	UI_SKILL_C,							// �X�L��3�A�C�R��
	UI_SKILL_PAR,						// �X�L��3���Z�q

	UI_ESKILL_A,						// �X�L��1�A�C�R��
	UI_ESKILL_KEY,						// �X�L��1�L�[
	UI_ESKILL_CROSS,					// �X�L��1���Z�q
	UI_ESKILL_NUM,						// �X�L��1����

	UI_ESKILL_B,						// �X�L��2�A�C�R��
	UI_ESKILL_BKEY,						// �X�L��2�L�[
	UI_ESKILL_BCROSS,					// �X�L��2���Z�q
	UI_ESKILL_BNUM,						// �X�L��2����

	UI_ESKILL_C,						// �X�L��3�A�C�R��
	UI_ESKILL_PAR,						// �X�L��3���Z�q


	UI_MAX,								// UI�\���̍ő吔
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


	bool					effectflag;					// �G�t�F�N�g�p����ϐ�
	int						effect;						// �G�t�F�N�g�p�ϐ�

	LPDIRECT3DTEXTURE9		Texture;					// �e�N�X�`���ւ̃|�C���^
	VERTEX_2D				vertex[NUM_VERTEX];			// ���_���i�[���[�N

}UI;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitUi(int type);								// �����������֐�
void UninitUi(void);									// �I�������֐�
void UpdateUi(void);									// �X�V�����֐�
void DrawUi(void);										// �`�揈���֐�

void SetTextureUi(int no, int cntPattern);				// �e�N�X�`�����W�̐ݒ�

#endif

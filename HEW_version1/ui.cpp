//=============================================================================
//
// UI��ʏ��� [ui.cpp]
// Author : ���ˌ��j��
// �v���O�����쐬�� : 2018/3/09
//
//=============================================================================

#include "ui.h"							// �}�N�����\���̎g�p�̈�
#include "main.h"						// �}�N���g�p�̈�
#include "input.h"						// �֐��g�p�̈�
#include "game.h"						// ����
#include "player.h"						// �֐��g�p�̈�
#include "player_skillNor.h"
#include "player_skillDef.h"
#include "player_skillSup.h"
#include "enemy.h"						// ����
#include "enemy_skillNor.h"
#include "enemy_skillDef.h"
#include "enemy_skillSup.h"
#include "debugproc.h"					// ����(�f�o�b�O�p)
#include "title.h"						// �}�N���g�p�̈�

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexUi(int no);			// ���_�쐬�֐�
void SetVertexUiEffect(int no);			// �G�t�F�N�g�֐�

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************


UI uiWk[UI_MAX];						// �^�C�g���\���̍ő吔�錾

float Hsize,Esize;						// �Q�[�W����ϐ�

int oldHp,oldEhp;						// �X�V���씻��p�ϐ�

//float sizex, sizey;						// �f�o�b�O�p�e�N�X�`���ړ������ϐ�


//=============================================================================
// �����������֐�
//=============================================================================
HRESULT InitUi(int type)
{

	// �|�C���^�̏�����
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	UI *ui = &uiWk[0];

	// �Q�[�W����ϐ��̏�����
	Hsize = 0;			// �v���C���[HP�o�[
	Esize = 0;			// �G�l�~�|HP�o�[

	// �X�V���씻��p�ϐ��̏�����
	oldHp = PLAYER_HP_MAX;		// �v���C���[HP�o�[
	oldEhp = ENEMY_HP_MAX;		// �G�l�~�|HP�o�[

	//// �f�o�b�O�p�e�N�X�`���ړ������ϐ��̏�����
	//sizex = UI_SKILL_PAR_SIZE_X;
	//sizey = UI_SKILL_PAR_SIZE_Y;

	// �\���̍ő吔����������
	for(int i = 0; i < UI_MAX;i++, ui++)
	{
		ui->PatternAnim = 0;								// �A�j���p�^�[���ԍ��������_���ŏ�����
		ui->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ��]�̏�����
		ui->effect = UI_EFFECT_BASE;						// �G�t�F�N�g�̃��l�̏�����
		ui->effectflag = true;								// �S�Ďg�p�ŏ���

		// ���N����
		if (type == FIRST)
		{

			// �S��NULL�ŏ�����
			ui->Texture = NULL;

			// HP�o�[���n
			if (i == UI_BASE)
			{
				// �ʒu�̐ݒ�
				ui->use = true;						// �g�p�ŏ���
				ui->pos = UI_BASE_POS;				// HP�o�[���n�̈ʒu�̏�����

				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					UI_BASE_TEXTURE,				// �t�@�C���̖��O
					&ui->Texture);					// �ǂݍ��ރ������[
			}

			// HP�o�[�g
			else if (i == UI_HP_FRAME)
			{
				// �ʒu�̐ݒ�
				ui->use = true;						// �g�p�ŏ�����
				ui->pos = UI_HP_FRAME_POS;			// HP�o�[�̈ʒu�̏�����

													// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					UI_HP_TEXTURE,					// �t�@�C���̖��O
					&ui->Texture);					// �ǂݍ��ރ������[
			}

			// �G�l�~�|HP�o�[�g
			else if (i == UI_EHP_FRAME)
			{
				// �ʒu�̐ݒ�
				ui->use = true;						// �g�p�ŏ�����
				ui->pos = UI_EHP_FRAME_POS;			// HP�o�[�̈ʒu�̏�����

													// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					UI_HP_TEXTURE,					// �t�@�C���̖��O
					&ui->Texture);					// �ǂݍ��ރ������[
			}

			// HP�o�[
			else if (i == UI_HP)
			{
				// �ʒu�̐ݒ�
				ui->use = true;						// �g�p�ŏ�����
				ui->pos = UI_HP_POS;				// HP�o�[�̈ʒu�̏�����

				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					UI_HP_TEXTURE,					// �t�@�C���̖��O
					&ui->Texture);					// �ǂݍ��ރ������[
			}

			// HP�o�[�G�t�F�N�g
			else if (i == UI_HP_EFFECT)
			{
				// �ʒu�̐ݒ�
				ui->use = false;					// ���g�p�ŏ�����
				ui->pos = UI_HP_POS;				// HP�o�[�G�t�F�N�g�̈ʒu�̏�����

				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					UI_HP_TEXTURE,					// �t�@�C���̖��O
					&ui->Texture);					// �ǂݍ��ރ������[
			}

			// �G�l�~�|HP�o�[
			else if (i == UI_EHP)
			{
				// �ʒu�̐ݒ�
				ui->use = true;						// �g�p�ŏ�����
				ui->pos = UI_EHP_POS;				// HP�o�[�̈ʒu�̏�����

													// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					UI_HP_TEXTURE,					// �t�@�C���̖��O
					&ui->Texture);					// �ǂݍ��ރ������[
			}

			//�G�l�~�| HP�o�[�G�t�F�N�g
			else if (i == UI_EHP_EFFECT)
			{
				// �ʒu�̐ݒ�
				ui->use = false;					// ���g�p�ŏ�����
				ui->pos = UI_EHP_POS;				// HP�o�[�G�t�F�N�g�̈ʒu�̏�����

				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					UI_HP_TEXTURE,					// �t�@�C���̖��O
					&ui->Texture);					// �ǂݍ��ރ������[
			}

			// �L�����N�^�[:AI�̈ʒu
			else if (i == UI_AI)
			{
				// �ʒu�̐ݒ�
				ui->use = true;						// �g�p�ŏ���
				ui->pos = UI_AI_POS;				// �L�����N�^�[:AI�̈ʒu�̏�����

													// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					UI_AI_TEXTURE,					// �t�@�C���̖��O
					&ui->Texture);					// �ǂݍ��ރ������[
			}


			// �L�����N�^�[:�E�C���X�̈ʒu
			else if (i == UI_VIRUS)
			{
				// �ʒu�̐ݒ�
				ui->use = true;						// �g�p�ŏ���
				ui->pos = UI_VIRUSE_POS;			// �L�����N�^�[:�E�C���X�̈ʒu�̏�����

													// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					UI_VIRUS_TEXTURE,				// �t�@�C���̖��O
					&ui->Texture);					// �ǂݍ��ރ������[
			}


			// �^�C�}�[�̘g�̈ʒu
			else if (i == UI_FRAME)
			{
				// �ʒu�̐ݒ�
				ui->use = true;						// �g�p�ŏ���
				ui->pos = UI_FRAME_POS;				// �^�C�}�[�̘g�̈ʒu�̏�����

													// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					UI_FRAME_TEXTURE,				// �t�@�C���̖��O
					&ui->Texture);					// �ǂݍ��ރ������[
			}


			// �^�C�}�[�̘g�̈ʒu
			else if (i == UI_FRAME_AI)
			{
				// �ʒu�̐ݒ�
				ui->use = true;						// �g�p�ŏ���
				ui->pos = UI_FRAME_AI_POS;			// �^�C�}�[�̘g�̈ʒu�̏�����

													// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					UI_FRAME_AI_TEXTURE,				// �t�@�C���̖��O
					&ui->Texture);					// �ǂݍ��ރ������[
			}


			// �^�C�}�[�̘g�̈ʒu
			else if (i == UI_FRAME_VIRUS)
			{
				// �ʒu�̐ݒ�
				ui->use = true;						// �g�p�ŏ���
				ui->pos = UI_FRAME_VIRUS_POS;		// �^�C�}�[�̘g�̈ʒu�̏�����

				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					UI_FRAME_VIRUS_TEXTURE,			// �t�@�C���̖��O
					&ui->Texture);					// �ǂݍ��ރ������[
			}

			// �X�L��1�A�C�R���̘g�̈ʒu
			else if (i == UI_SKILL_A)
			{
				// �ʒu�̐ݒ�
				ui->use = true;						// �g�p�ŏ���
				ui->pos = UI_SKILL_A_POS;		// �X�L��1�A�C�R���̈ʒu�̏�����

													// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					UI_SKILL_A_TEXTURE,			// �t�@�C���̖��O
					&ui->Texture);					// �ǂݍ��ރ������[
			}

			// �X�L��2�A�C�R���̘g�̈ʒu
			else if (i == UI_SKILL_B)
			{
				// �ʒu�̐ݒ�
				ui->use = true;						// �g�p�ŏ���
				ui->pos = UI_SKILL_B_POS;		// �X�L��2�A�C�R���̈ʒu�̏�����

												// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					UI_SKILL_B_TEXTURE,			// �t�@�C���̖��O
					&ui->Texture);					// �ǂݍ��ރ������[
			}

			// �X�L��3�A�C�R���̘g�̈ʒu
			else if (i == UI_SKILL_C)
			{
				// �ʒu�̐ݒ�
				ui->use = true;						// �g�p�ŏ���
				ui->pos = UI_SKILL_C_POS;		// �X�L��3�A�C�R���̈ʒu�̏�����

												// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					UI_SKILL_C_TEXTURE,			// �t�@�C���̖��O
					&ui->Texture);					// �ǂݍ��ރ������[
			}

			// �X�L��1�A�C�R���̘g�̈ʒu
			else if (i == UI_ESKILL_A)
			{
				// �ʒu�̐ݒ�
				ui->use = true;						// �g�p�ŏ���
				ui->pos = UI_ESKILL_A_POS;		// �X�L��1�A�C�R���̈ʒu�̏�����

												// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					UI_SKILL_A_TEXTURE,			// �t�@�C���̖��O
					&ui->Texture);					// �ǂݍ��ރ������[
			}

			// �X�L��2�A�C�R���̘g�̈ʒu
			else if (i == UI_ESKILL_B)
			{
				// �ʒu�̐ݒ�
				ui->use = true;						// �g�p�ŏ���
				ui->pos = UI_ESKILL_B_POS;		// �X�L��2�A�C�R���̈ʒu�̏�����

												// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					UI_SKILL_B_TEXTURE,			// �t�@�C���̖��O
					&ui->Texture);					// �ǂݍ��ރ������[
			}

			// �X�L��3�A�C�R���̘g�̈ʒu
			else if (i == UI_ESKILL_C)
			{
				// �ʒu�̐ݒ�
				ui->use = true;						// �g�p�ŏ���
				ui->pos = UI_ESKILL_C_POS;		// �X�L��3�A�C�R���̈ʒu�̏�����

												// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					UI_SKILL_C_TEXTURE,			// �t�@�C���̖��O
					&ui->Texture);					// �ǂݍ��ރ������[
			}

			// �L�[�A�C�R���̘g�̈ʒu
			else if (i == UI_SKILL_KEY)
			{
				// �ʒu�̐ݒ�
				ui->use = true;						// �g�p�ŏ���
				ui->pos = UI_SKILL_KEY_POS;		// �L�[�A�C�R���̈ʒu�̏�����

												// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					UI_SKILL_KEY_TEXTURE,			// �t�@�C���̖��O
					&ui->Texture);					// �ǂݍ��ރ������[
			}

			// �L�[�A�C�R���̘g�̈ʒu
			else if (i == UI_SKILL_BKEY)
			{
				// �ʒu�̐ݒ�
				ui->use = true;						// �g�p�ŏ���
				ui->pos = UI_SKILL_BKEY_POS;		// �L�[�A�C�R���̈ʒu�̏�����

												// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					UI_SKILL_BKEY_TEXTURE,			// �t�@�C���̖��O
					&ui->Texture);					// �ǂݍ��ރ������[
			}

			// �L�[�A�C�R���̘g�̈ʒu
			else if (i == UI_ESKILL_KEY)
			{
				// �ʒu�̐ݒ�
				ui->use = true;						// �g�p�ŏ���
				ui->pos = UI_ESKILL_KEY_POS;		// �L�[�A�C�R���̈ʒu�̏�����

												// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					UI_SKILL_KEY_TEXTURE,			// �t�@�C���̖��O
					&ui->Texture);					// �ǂݍ��ރ������[
			}

			// �L�[�A�C�R���̘g�̈ʒu
			else if (i == UI_ESKILL_BKEY)
			{
				// �ʒu�̐ݒ�
				ui->use = true;						// �g�p�ŏ���
				ui->pos = UI_ESKILL_BKEY_POS;		// �L�[�A�C�R���̈ʒu�̏�����

													// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					UI_SKILL_BKEY_TEXTURE,			// �t�@�C���̖��O
					&ui->Texture);					// �ǂݍ��ރ������[
			}

			// ���Z�q�A�C�R���̘g�̈ʒu
			else if (i == UI_SKILL_CROSS)
			{
				// �ʒu�̐ݒ�
				ui->use = true;						// �g�p�ŏ���
				ui->pos = UI_SKILL_CROSS_POS;		// �L�[�A�C�R���̈ʒu�̏�����

												// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					UI_SKILL_CROSS_TEXTURE,			// �t�@�C���̖��O
					&ui->Texture);					// �ǂݍ��ރ������[
			}

			// ���Z�q�A�C�R���̘g�̈ʒu
			else if (i == UI_SKILL_BCROSS)
			{
				// �ʒu�̐ݒ�
				ui->use = true;						// �g�p�ŏ���
				ui->pos = UI_SKILL_BCROSS_POS;		// �L�[�A�C�R���̈ʒu�̏�����

													// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					UI_SKILL_CROSS_TEXTURE,			// �t�@�C���̖��O
					&ui->Texture);					// �ǂݍ��ރ������[
			}

			// ���Z�q�A�C�R���̘g�̈ʒu
			else if (i == UI_ESKILL_CROSS)
			{
				// �ʒu�̐ݒ�
				ui->use = true;						// �g�p�ŏ���
				ui->pos = UI_ESKILL_CROSS_POS;		// �L�[�A�C�R���̈ʒu�̏�����

													// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					UI_SKILL_CROSS_TEXTURE,			// �t�@�C���̖��O
					&ui->Texture);					// �ǂݍ��ރ������[
			}

			// ���Z�q�A�C�R���̘g�̈ʒu
			else if (i == UI_ESKILL_BCROSS)
			{
				// �ʒu�̐ݒ�
				ui->use = true;						// �g�p�ŏ���
				ui->pos = UI_ESKILL_BCROSS_POS;		// �L�[�A�C�R���̈ʒu�̏�����

													// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					UI_SKILL_CROSS_TEXTURE,			// �t�@�C���̖��O
					&ui->Texture);					// �ǂݍ��ރ������[
			}

			// �����A�C�R���̘g�̈ʒu
			else if (i == UI_SKILL_NUM)
			{
				// �ʒu�̐ݒ�
				ui->use = true;						// �g�p�ŏ���
				ui->pos = UI_SKILL_NUM_POS;			// �L�[�A�C�R���̈ʒu�̏�����

													// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					UI_SKILL_NUM_TEXTURE,			// �t�@�C���̖��O
					&ui->Texture);					// �ǂݍ��ރ������[
			}

			// �����A�C�R���̘g�̈ʒu
			else if (i == UI_SKILL_BNUM)
			{
				// �ʒu�̐ݒ�
				ui->use = true;						// �g�p�ŏ���
				ui->pos = UI_SKILL_BNUM_POS;		// �L�[�A�C�R���̈ʒu�̏�����

													// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					UI_SKILL_NUM_TEXTURE,			// �t�@�C���̖��O
					&ui->Texture);					// �ǂݍ��ރ������[
			}

			// �����A�C�R���̘g�̈ʒu
			else if (i == UI_ESKILL_NUM)
			{
				// �ʒu�̐ݒ�
				ui->use = true;						// �g�p�ŏ���
				ui->pos = UI_ESKILL_NUM_POS;		// �L�[�A�C�R���̈ʒu�̏�����

													// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					UI_SKILL_NUM_TEXTURE,			// �t�@�C���̖��O
					&ui->Texture);					// �ǂݍ��ރ������[
			}

			// �����A�C�R���̘g�̈ʒu
			else if (i == UI_ESKILL_BNUM)
			{
				// �ʒu�̐ݒ�
				ui->use = true;					// �g�p�ŏ���
				ui->pos = UI_ESKILL_BNUM_POS;		// �L�[�A�C�R���̈ʒu�̏�����

				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					UI_SKILL_NUM_TEXTURE,			// �t�@�C���̖��O
					&ui->Texture);					// �ǂݍ��ރ������[
			}

			// ���Z�q(�X�y�V����)�̘g�̈ʒu
			else if (i == UI_SKILL_PAR)
			{
				// �ʒu�̐ݒ�
				ui->use = true;						// �g�p�ŏ���
				ui->pos = UI_SKILL_PAR_POS;			// �L�[�A�C�R���̈ʒu�̏�����

													// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					UI_SKILL_PAR_TEXTURE,			// �t�@�C���̖��O
					&ui->Texture);					// �ǂݍ��ރ������[
			}

			/// ���Z�q(�X�y�V����)�̘g�̈ʒu
			else if (i == UI_ESKILL_PAR)
			{
				// �ʒu�̐ݒ�
				ui->use = true;					// �g�p�ŏ���
				ui->pos = UI_ESKILL_PAR_POS;		// �L�[�A�C�R���̈ʒu�̏�����

													// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					UI_SKILL_PAR_TEXTURE,			// �t�@�C���̖��O
					&ui->Texture);					// �ǂݍ��ރ������[
			}


		}

		// �Q�[���X�V��
		else if (type == UPDATA)
		{
			ui->use = true;		// �g�p�ŏ�����

			// UI�ōŏ��\��������̈ȊO�͖��g�p�ŏ�����
			// �v���C���[HP�o�[�G�t�F�N�g
			// �G�l�~�|HP�o�[�G�t�F�N�g
			if ((i == UI_HP_EFFECT)||(i == UI_EHP_EFFECT))
			{
				ui->use = false;					// ���g�p�ŏ�����
			}
		}

		// ���_���̍쐬
		MakeVertexUi(i);
	}

	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void UninitUi(void)
{
	// �|�C���^�̏�����
	UI *ui = &uiWk[0];

	// �\���̍ő吔�I������
	for (int i = 0; i < UI_MAX;i++, ui++)
	{

		// �e�N�X�`���̊J���o���Ă��Ȃ�������
		if (ui->Texture != NULL)
		{

			// �e�N�X�`���̊J��
			ui->Texture->Release();
			ui->Texture = NULL;
		}
	}

}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void UpdateUi(void)
{

	// �|�C���^�̏�����
	PLAYER *player = GetPlayer();
	ENEMY *enemy = GetEnemy();
	PLAYER_NORSKILL *playernorSkill = GetPlayerNorSkill(0);
	ENEMY_NORSKILL *enemynorSkill = GetEnemyNorSkill(0);
	PLAYER_SKILLDEF *playerskillDef = GetPlayerSkillDef(0);
	ENEMY_SKILLDEF *enemyskillDef = GetEnemySkillDef(0);
	PLAYER_SUPSKILL *playersupSkill = GetPlayerSupSkill(0);
	ENEMY_SUPSKILL *enemysupSkill = GetEnemySupSkill(0);


	// �g�p����\���̂̃|�C���^�̏�����
	UI *ui = &uiWk[0];
	UI *uiH = &uiWk[UI_HP_EFFECT];					// �v���C���[HP�o�[�G�t�F�N�g
	UI *uiE = &uiWk[UI_EHP_EFFECT];					// �G�l�~�|HP�o�[�G�t�F�N�g

	// HP�o�[�ɕω�
	if (oldHp != player->hp)
	{

		// HP�o�[�G�t�F�N�g���g�p��
		uiH->use = true;
		uiH->effectflag = true;

	}

	// HP�o�[�ɕω�
	if (oldEhp != enemy->hp)
	{

		// HP�o�[�G�t�F�N�g���g�p��
		uiE->use = true;
		uiE->effectflag = true;

	}

	// �X�L��1
	if (player->norSk == false)
	{

		UI *uiA = &uiWk[UI_SKILL_A];

		for (int i = UI_SKILL_A;i <= UI_SKILL_NUM;i++, uiA++)
		{
			// ���ˌ��̐ݒ�
			uiA->vertex[0].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
			uiA->vertex[1].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
			uiA->vertex[2].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
			uiA->vertex[3].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);

		}
	}
	else if (player->norSk == true)
	{
		UI *uiA = &uiWk[UI_SKILL_A];

		for (int i = UI_SKILL_A;i <= UI_SKILL_NUM;i++, uiA++)
		{
			// ���ˌ��̐ݒ�
			uiA->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			uiA->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			uiA->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			uiA->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		}

	}

	// �X�L��2
	if (player->defSk == false)
	{

		UI *uiB = &uiWk[UI_SKILL_B];

		for (int i = UI_SKILL_B;i <= UI_SKILL_BNUM;i++, uiB++)
		{
			// ���ˌ��̐ݒ�
			uiB->vertex[0].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
			uiB->vertex[1].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
			uiB->vertex[2].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
			uiB->vertex[3].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);

		}
	}
	else if (player->defSk == true)
	{
		UI *uiB = &uiWk[UI_SKILL_B];

		for (int i = UI_SKILL_B;i <= UI_SKILL_BNUM;i++, uiB++)
		{
			// ���ˌ��̐ݒ�
			uiB->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			uiB->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			uiB->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			uiB->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		}

	}

	// �X�L��3
	if (player->supSk == false)
	{

		UI *uiC = &uiWk[UI_SKILL_C];

		for (int i = UI_SKILL_C;i <= UI_SKILL_PAR;i++, uiC++)
		{
			// ���ˌ��̐ݒ�
			uiC->vertex[0].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
			uiC->vertex[1].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
			uiC->vertex[2].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
			uiC->vertex[3].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);

		}
	}
	else if (player->supSk == true)
	{
		UI *uiC = &uiWk[UI_SKILL_C];

		for (int i = UI_SKILL_C;i <= UI_SKILL_PAR;i++, uiC++)
		{
			// ���ˌ��̐ݒ�
			uiC->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			uiC->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			uiC->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			uiC->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		}

	}


	// �X�L��1
	if (enemy->norSk == false)
	{

		UI *uiEA = &uiWk[UI_ESKILL_A];

		for (int i = UI_ESKILL_A;i <= UI_ESKILL_NUM;i++, uiEA++)
		{
			// ���ˌ��̐ݒ�
			uiEA->vertex[0].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
			uiEA->vertex[1].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
			uiEA->vertex[2].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
			uiEA->vertex[3].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);

		}
	}
	else if (enemy->norSk ==true)
	{
		UI *uiEA = &uiWk[UI_ESKILL_A];

		for (int i = UI_ESKILL_A;i <= UI_ESKILL_NUM;i++, uiEA++)
		{
			// ���ˌ��̐ݒ�
			uiEA->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			uiEA->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			uiEA->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			uiEA->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		}

	}


	// �X�L��2
	if (enemy->defSk == false)
	{

		UI *uiEB = &uiWk[UI_ESKILL_B];

		for (int i = UI_ESKILL_B;i <= UI_ESKILL_BNUM;i++, uiEB++)
		{
			// ���ˌ��̐ݒ�
			uiEB->vertex[0].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
			uiEB->vertex[1].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
			uiEB->vertex[2].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
			uiEB->vertex[3].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);

		}
	}
	else if (enemy->defSk == true)
	{
		UI *uiEB = &uiWk[UI_ESKILL_B];

		for (int i = UI_ESKILL_B;i <= UI_ESKILL_BNUM;i++, uiEB++)
		{
			// ���ˌ��̐ݒ�
			uiEB->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			uiEB->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			uiEB->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			uiEB->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		}

	}

	// �X�L��3
	if (enemy->supSk == false)
	{

		UI *uiEC = &uiWk[UI_ESKILL_C];

		for (int i = UI_ESKILL_C;i <= UI_ESKILL_PAR;i++, uiEC++)
		{
			// ���ˌ��̐ݒ�
			uiEC->vertex[0].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
			uiEC->vertex[1].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
			uiEC->vertex[2].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
			uiEC->vertex[3].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);

		}
	}
	else if (enemy->supSk == true)
	{
		UI *uiEC = &uiWk[UI_ESKILL_C];

		for (int i = UI_ESKILL_C;i <= UI_ESKILL_PAR;i++, uiEC++)
		{
			// ���ˌ��̐ݒ�
			uiEC->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			uiEC->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			uiEC->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			uiEC->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		}

	}


	
	// �\���̍ő吔�X�V����
	for (int i = 0; i < UI_MAX;i++, ui++)
	{
		// �v���C���[HP�o�[�G�t�F�N�g
		// �G�l�~�|HP�o�[�G�t�F�N�g
		if ((i == UI_HP_EFFECT) || (i == UI_EHP_EFFECT))
		{

			// �g�p���Ă�����
			if (ui->use == true)
			{
				// �G�t�F�N�g����
				// �v���X�t���O
				if (ui->effectflag == true)
				{
					// �G�t�F�N�g���̒l��UI_EFFECT_SPEED�𑫂�
					ui->effect += UI_EFFECT_SPEED;

					// �G�t�F�N�g���l���ő�
					if (ui->effect > ALPHA_MAX)
					{
						// �t���O���}�C�i�X��
						ui->effectflag = false;

						// �G�t�F�N�g���l���ő�l�ɌŒ�
						ui->effect = ALPHA_MAX;
					}
				}

				// �}�C�i�X�t���O
				else if (ui->effectflag == false)
				{

					// �G�t�F�N�g���̒l��UI_EFFECT_SPEED������
					ui->effect -= UI_EFFECT_SPEED;

					// �G�t�F�N�g���l���ŏ�
					if (ui->effect < ALPHA_BASE)
					{
						// �t���O���v���X��
						ui->effectflag = true;

						// �������I���������̂𖢎g�p��
						ui->use = false;
					}

				}

			}
		}

		// �X�L��1�c�e
		if (i == UI_SKILL_NUM)
		{
			// �p�^�[���̐؂�ւ�
			ui->PatternAnim = playernorSkill->cnt;

			// �e�N�X�`�����W��ݒ�
			SetTextureUi(i, ui->PatternAnim);
		}

		// �X�L��2�c�e
		if (i == UI_SKILL_BNUM)
		{
			// �p�^�[���̐؂�ւ�
			ui->PatternAnim = playerskillDef->cnt;

			// �e�N�X�`�����W��ݒ�
			SetTextureUi(i, ui->PatternAnim);
		}

		// �X�L��1�c�e(�G)
		if (i == UI_ESKILL_NUM)
		{
			// �p�^�[���̐؂�ւ�
			ui->PatternAnim = enemynorSkill->cnt;

			// �e�N�X�`�����W��ݒ�
			SetTextureUi(i, ui->PatternAnim);
		}

		// �X�L��1�c�e(�G)
		if (i == UI_ESKILL_BNUM)
		{
			// �p�^�[���̐؂�ւ�
			ui->PatternAnim = enemyskillDef->cnt;

			// �e�N�X�`�����W��ݒ�
			SetTextureUi(i, ui->PatternAnim);
		}


//		// �f�o�b�O�p�ړ��g�又��
//		if (i == UI_SKILL_PAR)
//		{
//
//			// ��
//			if (GetKeyboardPress(DIK_V))
//			{
//				ui->pos.x--;
//			}
//
//			// �E
//			else if (GetKeyboardPress(DIK_B))
//			{
//				ui->pos.x++;
//			}
//
//			// ��
//			if (GetKeyboardPress(DIK_N))
//			{
//				ui->pos.y--;
//
//			}
//			// ��
//			else if (GetKeyboardPress(DIK_M))
//			{
//				ui->pos.y++;
//			}
//
//			// x�g��
//			if (GetKeyboardPress(DIK_I))
//			{
//				sizex++;
//			}
//
//			// x�k��
//			else if (GetKeyboardPress(DIK_O))
//			{
//				sizex--;
//			}
//
//			// Y�g��
//			if (GetKeyboardPress(DIK_K))
//			{
//				sizey++;
//
//			}
//			// Y�k��
//			else if (GetKeyboardPress(DIK_L))
//			{
//				sizey--;
//			}
//
//			// �f�o�b�N��
//#ifdef _DEBUG
//			// �f�o�b�N�\��
//			PrintDebugProc("�T�C�Y:x%f)\n", sizex*2);
//			PrintDebugProc("�T�C�Y:y%f)\n", sizey*2);
//			PrintDebugProc("���W:X %f)\n", ui->pos.x);
//			PrintDebugProc("���W:Y %f)\n", ui->pos.y);
//#endif
//		}


		// �G�t�F�N�g����
		SetVertexUiEffect(i);

	}

	// ���݂̃v���C���[HP�A�G�l�~�|HP�̒l��ۑ�
	oldHp = player->hp;
	oldEhp = enemy->hp;

}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void DrawUi(void)
{
	// �|�C���^�̏�����
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	UI *ui = &uiWk[0];
	
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);


	// �\���̍ő吔�I������
	for (int i = 0; i < UI_MAX;i++, ui++)
	{
		// �g�p���Ă�����
		if (ui->use == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, ui->Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, ui->vertex, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�쐬�֐�
//=============================================================================
HRESULT MakeVertexUi(int no)
{
	
	// �|�C���^�̏�����
	UI *ui = &uiWk[no];

	//  HP�o�[���n
	if (no==UI_BASE)
	{
		// ���_���W�̐ݒ�
		ui->vertex[0].vtx = D3DXVECTOR3(ui->pos.x - UI_BASE_SIZE_X, ui->pos.y - UI_BASE_SIZE_Y, 0.0f);
		ui->vertex[1].vtx = D3DXVECTOR3(ui->pos.x + UI_BASE_SIZE_X, ui->pos.y - UI_BASE_SIZE_Y, 0.0f);
		ui->vertex[2].vtx = D3DXVECTOR3(ui->pos.x - UI_BASE_SIZE_X, ui->pos.y + UI_BASE_SIZE_Y, 0.0f);
		ui->vertex[3].vtx = D3DXVECTOR3(ui->pos.x + UI_BASE_SIZE_X, ui->pos.y + UI_BASE_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		ui->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// HP�o�[�g
	else if ((no == UI_HP_FRAME)|| (no == UI_EHP_FRAME))
	{
		// ���_���W�̐ݒ�
		ui->vertex[0].vtx = D3DXVECTOR3(ui->pos.x - UI_HP_FRAME_SIZE_X, ui->pos.y - UI_HP_FRAME_SIZE_Y, 0.0f);
		ui->vertex[1].vtx = D3DXVECTOR3(ui->pos.x + UI_HP_FRAME_SIZE_X, ui->pos.y - UI_HP_FRAME_SIZE_Y, 0.0f);
		ui->vertex[2].vtx = D3DXVECTOR3(ui->pos.x - UI_HP_FRAME_SIZE_X, ui->pos.y + UI_HP_FRAME_SIZE_Y, 0.0f);
		ui->vertex[3].vtx = D3DXVECTOR3(ui->pos.x + UI_HP_FRAME_SIZE_X, ui->pos.y + UI_HP_FRAME_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		ui->vertex[0].diffuse = D3DCOLOR_RGBA(0, 0, 0, 255);
		ui->vertex[1].diffuse = D3DCOLOR_RGBA(0, 0, 0, 255);
		ui->vertex[2].diffuse = D3DCOLOR_RGBA(0, 0, 0, 255);
		ui->vertex[3].diffuse = D3DCOLOR_RGBA(0, 0, 0, 255);

	}

	// HP�o�[
	else if (no == UI_HP)
	{
		// ���_���W�̐ݒ�
		ui->vertex[0].vtx = D3DXVECTOR3(ui->pos.x , ui->pos.y , 0.0f);
		ui->vertex[1].vtx = D3DXVECTOR3(ui->pos.x + UI_HP_SIZE_X, ui->pos.y, 0.0f);
		ui->vertex[2].vtx = D3DXVECTOR3(ui->pos.x , ui->pos.y + UI_HP_SIZE_Y, 0.0f);
		ui->vertex[3].vtx = D3DXVECTOR3(ui->pos.x + UI_HP_SIZE_X, ui->pos.y + UI_HP_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		ui->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// HP�o�[�G�t�F�N�g
	else if (no == UI_EHP_EFFECT)
	{
		// ���_���W�̐ݒ�
		ui->vertex[0].vtx = D3DXVECTOR3(ui->pos.x, ui->pos.y, 0.0f);
		ui->vertex[1].vtx = D3DXVECTOR3(ui->pos.x + UI_HP_SIZE_X, ui->pos.y, 0.0f);
		ui->vertex[2].vtx = D3DXVECTOR3(ui->pos.x, ui->pos.y + UI_HP_SIZE_Y, 0.0f);
		ui->vertex[3].vtx = D3DXVECTOR3(ui->pos.x + UI_HP_SIZE_X, ui->pos.y + UI_HP_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		ui->vertex[0].diffuse = D3DCOLOR_RGBA(255, 0, 0, ui->effect);
		ui->vertex[1].diffuse = D3DCOLOR_RGBA(255, 0, 0, ui->effect);
		ui->vertex[2].diffuse = D3DCOLOR_RGBA(255, 0, 0, ui->effect);
		ui->vertex[3].diffuse = D3DCOLOR_RGBA(255, 0, 0, ui->effect);

	}

	// �G�l�~�|HP�o�[
	else if (no == UI_EHP)
	{
		// ���_���W�̐ݒ�
		ui->vertex[0].vtx = D3DXVECTOR3(ui->pos.x - UI_HP_SIZE_X, ui->pos.y, 0.0f);
		ui->vertex[1].vtx = D3DXVECTOR3(ui->pos.x, ui->pos.y, 0.0f);
		ui->vertex[2].vtx = D3DXVECTOR3(ui->pos.x - UI_HP_SIZE_X, ui->pos.y + UI_HP_SIZE_Y, 0.0f);
		ui->vertex[3].vtx = D3DXVECTOR3(ui->pos.x, ui->pos.y + UI_HP_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		ui->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// �G�l�~�|HP�o�[�G�t�F�N�g
	else if (no == UI_EHP_EFFECT)
	{

		// ���_���W�̐ݒ�
		ui->vertex[0].vtx = D3DXVECTOR3(ui->pos.x - UI_HP_SIZE_X, ui->pos.y, 0.0f);
		ui->vertex[1].vtx = D3DXVECTOR3(ui->pos.x, ui->pos.y, 0.0f);
		ui->vertex[2].vtx = D3DXVECTOR3(ui->pos.x - UI_HP_SIZE_X, ui->pos.y + UI_HP_SIZE_Y, 0.0f);
		ui->vertex[3].vtx = D3DXVECTOR3(ui->pos.x, ui->pos.y + UI_HP_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		ui->vertex[0].diffuse = D3DCOLOR_RGBA(0, 0, 255, ui->effect);
		ui->vertex[1].diffuse = D3DCOLOR_RGBA(0, 0, 255, ui->effect);
		ui->vertex[2].diffuse = D3DCOLOR_RGBA(0, 0, 255, ui->effect);
		ui->vertex[3].diffuse = D3DCOLOR_RGBA(0, 0, 255, ui->effect);

	}

	// �L�����N�^�[:AI
	else if (no == UI_AI)
	{
		// ���_���W�̐ݒ�
		ui->vertex[0].vtx = D3DXVECTOR3(ui->pos.x - UI_AI_SIZE_X, ui->pos.y - UI_AI_SIZE_Y, 0.0f);
		ui->vertex[1].vtx = D3DXVECTOR3(ui->pos.x + UI_AI_SIZE_X, ui->pos.y - UI_AI_SIZE_Y, 0.0f);
		ui->vertex[2].vtx = D3DXVECTOR3(ui->pos.x - UI_AI_SIZE_X, ui->pos.y + UI_AI_SIZE_Y, 0.0f);
		ui->vertex[3].vtx = D3DXVECTOR3(ui->pos.x + UI_AI_SIZE_X, ui->pos.y + UI_AI_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		ui->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// �L�����N�^�[:�E�C���X
	else if (no == UI_VIRUS)
	{
		// ���_���W�̐ݒ�
		ui->vertex[0].vtx = D3DXVECTOR3(ui->pos.x - UI_VIRUS_SIZE_X, ui->pos.y - UI_VIRUS_SIZE_Y, 0.0f);
		ui->vertex[1].vtx = D3DXVECTOR3(ui->pos.x + UI_VIRUS_SIZE_X, ui->pos.y - UI_VIRUS_SIZE_Y, 0.0f);
		ui->vertex[2].vtx = D3DXVECTOR3(ui->pos.x - UI_VIRUS_SIZE_X, ui->pos.y + UI_VIRUS_SIZE_Y, 0.0f);
		ui->vertex[3].vtx = D3DXVECTOR3(ui->pos.x + UI_VIRUS_SIZE_X, ui->pos.y + UI_VIRUS_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		ui->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// �^�C�}�[�̘g
	else if (no == UI_FRAME)
	{
		// ���_���W�̐ݒ�
		ui->vertex[0].vtx = D3DXVECTOR3(ui->pos.x - UI_FRAME_SIZE_X, ui->pos.y - UI_FRAME_SIZE_Y, 0.0f);
		ui->vertex[1].vtx = D3DXVECTOR3(ui->pos.x + UI_FRAME_SIZE_X, ui->pos.y - UI_FRAME_SIZE_Y, 0.0f);
		ui->vertex[2].vtx = D3DXVECTOR3(ui->pos.x - UI_FRAME_SIZE_X, ui->pos.y + UI_FRAME_SIZE_Y, 0.0f);
		ui->vertex[3].vtx = D3DXVECTOR3(ui->pos.x + UI_FRAME_SIZE_X, ui->pos.y + UI_FRAME_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		ui->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// �Z�gAI
	else if (no == UI_FRAME_AI)
	{
		// ���_���W�̐ݒ�
		ui->vertex[0].vtx = D3DXVECTOR3(ui->pos.x - UI_FRAME_AI_SIZE_X, ui->pos.y - UI_FRAME_AI_SIZE_Y, 0.0f);
		ui->vertex[1].vtx = D3DXVECTOR3(ui->pos.x + UI_FRAME_AI_SIZE_X, ui->pos.y - UI_FRAME_AI_SIZE_Y, 0.0f);
		ui->vertex[2].vtx = D3DXVECTOR3(ui->pos.x - UI_FRAME_AI_SIZE_X, ui->pos.y + UI_FRAME_AI_SIZE_Y, 0.0f);
		ui->vertex[3].vtx = D3DXVECTOR3(ui->pos.x + UI_FRAME_AI_SIZE_X, ui->pos.y + UI_FRAME_AI_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		ui->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 180);
		ui->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 180);
		ui->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 180);
		ui->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 180);

	}

	// �Z�g�E�C���X
	else if (no == UI_FRAME_VIRUS)
	{
		// ���_���W�̐ݒ�
		ui->vertex[0].vtx = D3DXVECTOR3(ui->pos.x - UI_FRAME_AI_SIZE_X, ui->pos.y - UI_FRAME_AI_SIZE_Y, 0.0f);
		ui->vertex[1].vtx = D3DXVECTOR3(ui->pos.x + UI_FRAME_AI_SIZE_X, ui->pos.y - UI_FRAME_AI_SIZE_Y, 0.0f);
		ui->vertex[2].vtx = D3DXVECTOR3(ui->pos.x - UI_FRAME_AI_SIZE_X, ui->pos.y + UI_FRAME_AI_SIZE_Y, 0.0f);
		ui->vertex[3].vtx = D3DXVECTOR3(ui->pos.x + UI_FRAME_AI_SIZE_X, ui->pos.y + UI_FRAME_AI_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		ui->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 180);
		ui->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 180);
		ui->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 180);
		ui->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 180);

	}

	// �X�L���A�C�R��
	else if ((no == UI_SKILL_A)|| (no == UI_SKILL_B) || (no == UI_ESKILL_A) || (no == UI_ESKILL_B))
	{
		// ���_���W�̐ݒ�
		ui->vertex[0].vtx = D3DXVECTOR3(ui->pos.x - UI_SKILL_SIZE_X, ui->pos.y - UI_SKILL_SIZE_Y, 0.0f);
		ui->vertex[1].vtx = D3DXVECTOR3(ui->pos.x + UI_SKILL_SIZE_X, ui->pos.y - UI_SKILL_SIZE_Y, 0.0f);
		ui->vertex[2].vtx = D3DXVECTOR3(ui->pos.x - UI_SKILL_SIZE_X, ui->pos.y + UI_SKILL_SIZE_Y, 0.0f);
		ui->vertex[3].vtx = D3DXVECTOR3(ui->pos.x + UI_SKILL_SIZE_X, ui->pos.y + UI_SKILL_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		ui->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// �X�L���A�C�R��
	else if ((no == UI_SKILL_C) || (no == UI_ESKILL_C))
	{
		// ���_���W�̐ݒ�
		ui->vertex[0].vtx = D3DXVECTOR3(ui->pos.x - UI_SKILL_C_SIZE_X, ui->pos.y - UI_SKILL_C_SIZE_Y, 0.0f);
		ui->vertex[1].vtx = D3DXVECTOR3(ui->pos.x + UI_SKILL_C_SIZE_X, ui->pos.y - UI_SKILL_C_SIZE_Y, 0.0f);
		ui->vertex[2].vtx = D3DXVECTOR3(ui->pos.x - UI_SKILL_C_SIZE_X, ui->pos.y + UI_SKILL_C_SIZE_Y, 0.0f);
		ui->vertex[3].vtx = D3DXVECTOR3(ui->pos.x + UI_SKILL_C_SIZE_X, ui->pos.y + UI_SKILL_C_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		ui->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// �L�[�A�C�R��
	else if ((no == UI_SKILL_KEY) || (no == UI_SKILL_BKEY) || (no == UI_ESKILL_KEY) || (no == UI_ESKILL_BKEY))
	{
		// ���_���W�̐ݒ�
		ui->vertex[0].vtx = D3DXVECTOR3(ui->pos.x - UI_SKILL_KEY_SIZE_X, ui->pos.y - UI_SKILL_KEY_SIZE_Y, 0.0f);
		ui->vertex[1].vtx = D3DXVECTOR3(ui->pos.x + UI_SKILL_KEY_SIZE_X, ui->pos.y - UI_SKILL_KEY_SIZE_Y, 0.0f);
		ui->vertex[2].vtx = D3DXVECTOR3(ui->pos.x - UI_SKILL_KEY_SIZE_X, ui->pos.y + UI_SKILL_KEY_SIZE_Y, 0.0f);
		ui->vertex[3].vtx = D3DXVECTOR3(ui->pos.x + UI_SKILL_KEY_SIZE_X, ui->pos.y + UI_SKILL_KEY_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		ui->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// ���Z�q
	else if ((no == UI_SKILL_CROSS) || (no == UI_SKILL_BCROSS) || (no == UI_ESKILL_CROSS) || (no == UI_ESKILL_BCROSS))
	{
		// ���_���W�̐ݒ�
		ui->vertex[0].vtx = D3DXVECTOR3(ui->pos.x - UI_SKILL_CROSS_SIZE_X, ui->pos.y - UI_SKILL_CROSS_SIZE_Y, 0.0f);
		ui->vertex[1].vtx = D3DXVECTOR3(ui->pos.x + UI_SKILL_CROSS_SIZE_X, ui->pos.y - UI_SKILL_CROSS_SIZE_Y, 0.0f);
		ui->vertex[2].vtx = D3DXVECTOR3(ui->pos.x - UI_SKILL_CROSS_SIZE_X, ui->pos.y + UI_SKILL_CROSS_SIZE_Y, 0.0f);
		ui->vertex[3].vtx = D3DXVECTOR3(ui->pos.x + UI_SKILL_CROSS_SIZE_X, ui->pos.y + UI_SKILL_CROSS_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		ui->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}


	// ����
	else if ((no == UI_SKILL_NUM) || (no == UI_SKILL_BNUM) || (no == UI_ESKILL_NUM) || (no == UI_ESKILL_BNUM))
	{
		// ���_���W�̐ݒ�
		ui->vertex[0].vtx = D3DXVECTOR3(ui->pos.x - UI_SKILL_NUM_SIZE_X, ui->pos.y - UI_SKILL_NUM_SIZE_Y, 0.0f);
		ui->vertex[1].vtx = D3DXVECTOR3(ui->pos.x + UI_SKILL_NUM_SIZE_X, ui->pos.y - UI_SKILL_NUM_SIZE_Y, 0.0f);
		ui->vertex[2].vtx = D3DXVECTOR3(ui->pos.x - UI_SKILL_NUM_SIZE_X, ui->pos.y + UI_SKILL_NUM_SIZE_Y, 0.0f);
		ui->vertex[3].vtx = D3DXVECTOR3(ui->pos.x + UI_SKILL_NUM_SIZE_X, ui->pos.y + UI_SKILL_NUM_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		ui->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// �X�L���A�C�R��
	else if ((no == UI_SKILL_PAR) || (no == UI_ESKILL_PAR))
	{
		// ���_���W�̐ݒ�
		ui->vertex[0].vtx = D3DXVECTOR3(ui->pos.x - UI_SKILL_PAR_SIZE_X, ui->pos.y - UI_SKILL_PAR_SIZE_Y, 0.0f);
		ui->vertex[1].vtx = D3DXVECTOR3(ui->pos.x + UI_SKILL_PAR_SIZE_X, ui->pos.y - UI_SKILL_PAR_SIZE_Y, 0.0f);
		ui->vertex[2].vtx = D3DXVECTOR3(ui->pos.x - UI_SKILL_PAR_SIZE_X, ui->pos.y + UI_SKILL_PAR_SIZE_Y, 0.0f);
		ui->vertex[3].vtx = D3DXVECTOR3(ui->pos.x + UI_SKILL_PAR_SIZE_X, ui->pos.y + UI_SKILL_PAR_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		ui->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		ui->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}



	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	ui->vertex[0].rhw =
	ui->vertex[1].rhw =
	ui->vertex[2].rhw =
	ui->vertex[3].rhw = 1.0f;


	// �e�N�X�`�����W�̐ݒ�
	ui->vertex[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	ui->vertex[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	ui->vertex[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	ui->vertex[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�ݒ�֐�
//=============================================================================
void SetTextureUi(int no, int cntPattern)
{

	// �|�C���^�̏�����
	UI *ui = &uiWk[no];

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % UI_ANIM_PATTERN_DIVIDE_X;
	int y = cntPattern / UI_ANIM_PATTERN_DIVIDE_Y;
	float sizeX = 1.0f / UI_ANIM_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / UI_ANIM_PATTERN_DIVIDE_Y;
	ui->vertex[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	ui->vertex[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	ui->vertex[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	ui->vertex[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}


//=============================================================================
// �G�t�F�N�g�֐�
//=============================================================================
void SetVertexUiEffect(int no)
{

	// �|�C���^�̏�����
	UI *ui = &uiWk[no];
	PLAYER *player = GetPlayer();
	ENEMY *enemy = GetEnemy();


	// //�f�o�b�O�p�e�N�X�`���X�V
	////// //HP�o�[
	//if (no == UI_SKILL_PAR)
	//{
	//	// ���_���W�̐ݒ�
	//	ui->vertex[0].vtx = D3DXVECTOR3(ui->pos.x - sizex, ui->pos.y - sizey, 0.0f);
	//	ui->vertex[1].vtx = D3DXVECTOR3(ui->pos.x + sizex, ui->pos.y - sizey, 0.0f);
	//	ui->vertex[2].vtx = D3DXVECTOR3(ui->pos.x - sizex, ui->pos.y + sizey, 0.0f);
	//	ui->vertex[3].vtx = D3DXVECTOR3(ui->pos.x + sizex, ui->pos.y + sizey, 0.0f);

	//}

	//// HP�o�[
	// if (no == UI_HP_FRAME)
	//{
	//	// ���_���W�̐ݒ�
	//	ui->vertex[0].vtx = D3DXVECTOR3(ui->pos.x, ui->pos.y, 0.0f);
	//	ui->vertex[1].vtx = D3DXVECTOR3(ui->pos.x + sizex, ui->pos.y, 0.0f);
	//	ui->vertex[2].vtx = D3DXVECTOR3(ui->pos.x, ui->pos.y + sizey, 0.0f);
	//	ui->vertex[3].vtx = D3DXVECTOR3(ui->pos.x + sizex, ui->pos.y + sizey, 0.0f);

	//}

	//// HP�o�[
	// if (no == UI_EHP)
	//{
	//	// ���_���W�̐ݒ�
	//	ui->vertex[0].vtx = D3DXVECTOR3(ui->pos.x - sizex, ui->pos.y, 0.0f);
	//	ui->vertex[1].vtx = D3DXVECTOR3(ui->pos.x, ui->pos.y, 0.0f);
	//	ui->vertex[2].vtx = D3DXVECTOR3(ui->pos.x - sizex, ui->pos.y + sizey, 0.0f);
	//	ui->vertex[3].vtx = D3DXVECTOR3(ui->pos.x, ui->pos.y + sizey, 0.0f);


	//}

	// HP�o�[
	if (no == UI_HP)
	{

		// ���݂�HP�Q�[�W����o��
		Hsize = (UI_HP_SIZE_X / PLAYER_HP_MAX)*player->hp;

		// ���_���W�̐ݒ�
		ui->vertex[0].vtx = D3DXVECTOR3(ui->pos.x, ui->pos.y, 0.0f);
		ui->vertex[1].vtx = D3DXVECTOR3(ui->pos.x + Hsize, ui->pos.y, 0.0f);
		ui->vertex[2].vtx = D3DXVECTOR3(ui->pos.x, ui->pos.y + UI_HP_SIZE_Y, 0.0f);
		ui->vertex[3].vtx = D3DXVECTOR3(ui->pos.x + Hsize, ui->pos.y + UI_HP_SIZE_Y, 0.0f);

	}

	// HP�o�[�G�t�F�N�g
	else if (no == UI_HP_EFFECT)
	{
		// ���݂�HP�Q�[�W����o��
		Hsize = (UI_HP_SIZE_X / PLAYER_HP_MAX)*player->hp;

		// ���_���W�̐ݒ�
		ui->vertex[0].vtx = D3DXVECTOR3(ui->pos.x, ui->pos.y, 0.0f);
		ui->vertex[1].vtx = D3DXVECTOR3(ui->pos.x + Hsize, ui->pos.y, 0.0f);
		ui->vertex[2].vtx = D3DXVECTOR3(ui->pos.x, ui->pos.y + UI_HP_SIZE_Y, 0.0f);
		ui->vertex[3].vtx = D3DXVECTOR3(ui->pos.x + Hsize, ui->pos.y + UI_HP_SIZE_Y, 0.0f);


		// ���ˌ��̐ݒ�
		ui->vertex[0].diffuse = D3DCOLOR_RGBA(255, 0, 0, ui->effect);
		ui->vertex[1].diffuse = D3DCOLOR_RGBA(255, 0, 0, ui->effect);
		ui->vertex[2].diffuse = D3DCOLOR_RGBA(255, 0, 0, ui->effect);
		ui->vertex[3].diffuse = D3DCOLOR_RGBA(255, 0, 0, ui->effect);

	}

	 // �G�l�~�|HP�o�[
	 if (no == UI_EHP)
	 {

	 	// ���݂�HP�Q�[�W����o��
	 	Esize = (UI_HP_SIZE_X / ENEMY_HP_MAX)*enemy->hp;

	 	// ���_���W�̐ݒ�
		ui->vertex[0].vtx = D3DXVECTOR3(ui->pos.x - Esize, ui->pos.y, 0.0f);
	 	ui->vertex[1].vtx = D3DXVECTOR3(ui->pos.x, ui->pos.y, 0.0f);
	 	ui->vertex[2].vtx = D3DXVECTOR3(ui->pos.x - Esize, ui->pos.y + UI_HP_SIZE_Y, 0.0f);
		ui->vertex[3].vtx = D3DXVECTOR3(ui->pos.x, ui->pos.y + UI_HP_SIZE_Y, 0.0f);

	 }

	 // �G�l�~�|HP�o�[�G�t�F�N�g
	else if (no == UI_EHP_EFFECT)
	{
		// ���݂�HP�Q�[�W����o��
		Esize = (UI_HP_SIZE_X / ENEMY_HP_MAX)*enemy->hp;

		// ���_���W�̐ݒ�
		ui->vertex[0].vtx = D3DXVECTOR3(ui->pos.x - Esize, ui->pos.y, 0.0f);
		ui->vertex[1].vtx = D3DXVECTOR3(ui->pos.x, ui->pos.y, 0.0f);
		ui->vertex[2].vtx = D3DXVECTOR3(ui->pos.x - Esize, ui->pos.y + UI_HP_SIZE_Y, 0.0f);
		ui->vertex[3].vtx = D3DXVECTOR3(ui->pos.x, ui->pos.y + UI_HP_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		ui->vertex[0].diffuse = D3DCOLOR_RGBA(0, 255, 255, ui->effect);
		ui->vertex[1].diffuse = D3DCOLOR_RGBA(0, 255, 255, ui->effect);
		ui->vertex[2].diffuse = D3DCOLOR_RGBA(0, 255, 255, ui->effect);
		ui->vertex[3].diffuse = D3DCOLOR_RGBA(0, 255, 255, ui->effect);

	}


}

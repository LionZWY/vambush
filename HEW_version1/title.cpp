//=============================================================================
//
// �^�C�g����ʏ��� [title.cpp]
// Author : ���ˌ��j��
// �v���O�����쐬�� : 2018/3/09
//
//=============================================================================

#include "title.h"					// �\���́��}�N���g�p�̈�
#include "main.h"					// �}�N���g�p�̈�
#include "input.h"					// �֐��g�p�̈�
#include "game.h"					// �֐����}�N���g�p�̈�
#include "debugproc.h"				// ����(�f�o�b�O�p)
#include "fade.h"					// �֐��g�p�̈�
#include "sound.h"					// ����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexTitle(int no);					// ���_�쐬�֐�
void SetVertexTitleEffect(int no);					// �G�t�F�N�g�֐�

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************


TITLE					titleWk[TITLE_MAX];			// �^�C�g���\���̍ő吔�錾

bool					effectflag;					// �G�t�F�N�g�p����ϐ�
int						effect;						// �G�t�F�N�g�p�ϐ�

bool					effectflagB;				// �G�t�F�N�g�p����ϐ�
int						effectB;					// �G�t�F�N�g�p�ϐ�

int						g_Alpha;					// ���e�X�g��臒l

int						serect;						// ��ʑJ�ڐ���ϐ�
int						titlecnt;					// �J�[�\������ϐ�

//float sizex, sizey;									// �f�o�b�O�p�e�N�X�`���ړ������ϐ�

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT InitTitle(int type)
{

	// �|�C���^�̏�����
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TITLE *title = &titleWk[0];

	// �G�t�F�N�g�֌W�̏�����
	effectflag = true;				// true:�v���X���� false:�}�C�i�X����
	effect=INIT_EFFECT;				// �G�t�F�N�g�̃��l�̏�����

	effectflagB = false;			// true:�v���X���� false:�}�C�i�X����
	effectB = B_ALPHA_MAX;			// �G�t�F�N�g�̃��l�̏�����


	// ��ʐ���ϐ��̏�����
	serect = 0;
	titlecnt = 0;

	// �A���t�@�e�X�g�̒l�̐ݒ�
	g_Alpha = ALPHA_TEST;

	//// �f�o�b�O�p�e�N�X�`���ړ������ϐ��̏�����
	//sizex = TITLE_LOGO_SIZE_X;
	//sizey = TITLE_LOGO_SIZE_Y;

	// �\���̍ő吔����������
	for(int i = 0; i < TITLE_MAX;i++, title++)
	{

		// ���N����
		if (type == FIRST)
		{

			// �S��NULL�ŏ�����
			title->Texture = NULL;

			// �^�C�g������
			if (i == TITLE_BASE)
			{
				// �ʒu�̐ݒ�
				title->use = true;					// true:�g�p false:���g�p �g�p�ŏ�����
				title->pos = TITLE_BASE_POS;		// �^�C�g���w�i�̈ʒu�̏�����

				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					TITLE_BASE_TEXTURE,				// �t�@�C���̖��O
					&title->Texture);				// �ǂݍ��ރ������[
			}

			// �^�C�g���w�i�n�C���C�g
			if (i == TITLE_BASE_LIGHT)
			{
				// �ʒu�̐ݒ�
				title->use = true;					// true:�g�p false:���g�p �g�p�ŏ�����
				title->pos = TITLE_BASE_POS;		// �^�C�g���w�i�n�C���C�g�̈ʒu�̏�����

													// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					TITLE_BASE_LIGHT_TEXTURE,		// �t�@�C���̖��O
					&title->Texture);				// �ǂݍ��ރ������[
			}


			// �^�C�g���w�i�G�t�F�N�g
			else if (i == TITLE_EFFECT)
			{
				// �ʒu�̐ݒ�
				title->use = true;					// �g�p�ŏ�����
				title->pos = TITLE_EFFECT_POS;		// �^�C�g���w�i�G�t�F�N�g�̈ʒu�̏�����

				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					TITLE_EFFECT_TEXTURE,			// �t�@�C���̖��O
					&title->Texture);				// �ǂݍ��ރ������[
			}


			// �L�����N�^�[:AI
			else if (i == TITLE_AI)
			{
				// �ʒu�̐ݒ�
				title->use = true;					// �g�p�ŏ�����
				title->pos = TITLE_AI_POS;			// �L�����N�^�[:AI�̈ʒu�̏�����

													// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					TITLE_AI_TEXTURE,				// �t�@�C���̖��O
					&title->Texture);				// �ǂݍ��ރ������[
			}

			// �L�����N�^�[:�E�C���X
			else if (i == TITLE_VIRUS)
			{
				// �ʒu�̐ݒ�
				title->use = true;					// �g�p�ŏ�����
				title->pos = TITLE_VIRUS_POS;		// �L�����N�^�[:�E�C���X�̈ʒu�̏�����

													// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					TITLE_VIRUS_TEXTURE,			// �t�@�C���̖��O
					&title->Texture);				// �ǂݍ��ރ������[
			}


			// �^�C�g�����S
			else if (i == TITLE_LOGO)
			{
				// �ʒu�̐ݒ�
				title->use = true;					// �g�p�ŏ�����
				title->pos = TITLE_LOGO_POS;		// �^�C�g���㕔�̈ʒu�̏�����

				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					TITLE_LOGO_TEXTURE,				// �t�@�C���̖��O
					&title->Texture);				// �ǂݍ��ރ������[
			}


			// UI:"�{�^���������Ă�"
			// UI�G�t�F�N�g:"�{�^���������Ă�"
			else if ((i == TITLE_ANY)||(i == TITLE_ANY_EFFECT))
			{
				// �ʒu�̐ݒ�
				title->use = true;					// �g�p�ŏ�����
				title->pos = TITLE_ANY_POS;			// UI:"�{�^���������Ă�"��UI�G�t�F�N�g:"�{�^���������Ă�"�̈ʒu�̏�����


				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					TITLE_ANY_TEXTURE,				// �t�@�C���̖��O
					&title->Texture);				// �ǂݍ��ރ������[
			}

			// UI:"�͂��߂�"
			// UI�G�t�F�N�g:"�͂��߂�"
			else if ((i == TITLE_START) || (i == TITLE_START_EFFECT))
			{
				// �ʒu�̐ݒ�
				title->use = false;					// ���g�p�ŏ�����
				title->pos = TITLE_START_POS;		// UI:"�͂��߂�"��UI�G�t�F�N�g:"�͂��߂�"�̈ʒu�̏�����

				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					TITLE_START_TEXTURE,			// �t�@�C���̖��O
					&title->Texture);				// �ǂݍ��ރ������[
			}

			// UI:"�͂��߂�"
			// UI�G�t�F�N�g:"�͂��߂�"
			else if ((i == TITLE_CREDIT) || (i == TITLE_CREDIT_EFFECT))
			{
				// �ʒu�̐ݒ�
				title->use = false;					// ���g�p�ŏ�����
				title->pos = TITLE_CREDIT_POS;		// UI:"�N���W�b�g"��UI�G�t�F�N�g:"�N���W�b�g"�̈ʒu�̏�����

				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					TITLE_CREDIT_TEXTURE,			// �t�@�C���̖��O
					&title->Texture);				// �ǂݍ��ރ������[
			}

			// UI:"�N���W�b�gED"(�N���W�b�g�e�N�X�`��)
			else if (i == TITLE_BOAD)
			{
				// �ʒu�̐ݒ�
				title->use = false;					// ���g�p�ŏ�����
				title->pos = TITLE_BOAD_POS;		// UI:"�N���W�b�gED"(�N���W�b�g�e�N�X�`��)�̈ʒu�̏�����

				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					TITLE_BOAD_TEXTURE,				// �t�@�C���̖��O
					&title->Texture);				// �ǂݍ��ރ������[
			}
		}

		// �Q�[���X�V��
		else if (type == UPDATA)
		{
			// �ЂƂ܂��g�p�ŏ�����
			title->use = true;

			// �^�C�g���ōŏ��\��������̈ȊO�͖��g�p�ŏ�����
			// UI:"�͂��߂�"
			// UI�G�t�F�N�g:"�͂��߂�"
			// UI:"�N���W�b�g"
			// UI�G�t�F�N�g:"�N���W�b�g"
			// UI:"�N���W�b�gED"(�N���W�b�g�e�N�X�`��)
			if ((i == TITLE_START) || (i == TITLE_START_EFFECT) || (i == TITLE_CREDIT) || (i == TITLE_CREDIT_EFFECT)||(i == TITLE_BOAD))
			{
				title->use = false;		// ���g�p
			}
		}

		// ���_���̍쐬
		MakeVertexTitle(i);
	}

	return S_OK;
}
//=============================================================================
// �I�������֐�
//=============================================================================
void UninitTitle(void)
{
	// �|�C���^�̏�����
	TITLE *title = &titleWk[0];

	// �\���̍ő吔�I������
	for (int i = 0; i < TITLE_MAX;i++, title++)
	{

		// �e�N�X�`���̊J���o���Ă��Ȃ�������
		if (title->Texture != NULL)
		{

			// �e�N�X�`���̊J��
			title->Texture->Release();
			title->Texture = NULL;
		}
	}

}
//=============================================================================
// �X�V�����֐�
//=============================================================================
void UpdateTitle(void)
{

	// �|�C���^�̏�����
	TITLE *title = &titleWk[0];

	// �G�t�F�N�g����
	// �v���X�t���O
	if (effectflag == true)
	{
		// �G�t�F�N�g���l��EFFECT_SPEED�𑫂�
		effect += EFFECT_SPEED;

		// �G�t�F�N�g���l���ő�
		if (effect == ALPHA_MAX)
		{
			// �t���O���}�C�i�X��
			effectflag = false;
		}
	}

	// �}�C�i�X�t���O
	else if (effectflag == false)
	{
		// �G�t�F�N�g���l��EFFECT_SPEED������
		effect -= EFFECT_SPEED;

		// �G�t�F�N�g���l���ŏ�
		if (effect == ALPHA_BASE)
		{
			// �t���O���v���X�ɂ�
			effectflag = true;
		}

	}

	// �G�t�F�N�g����
	// �v���X�t���O
	if (effectflagB == true)
	{
		// �G�t�F�N�g���l��EFFECT_SPEED�𑫂�
		effectB += B_EFFECT_SPEED;

		// �G�t�F�N�g���l���ő�
		if (effectB == ALPHA_MAX)
		{
			// �t���O���}�C�i�X��
			effectflagB = false;
		}
	}

	// �}�C�i�X�t���O
	else if (effectflagB == false)
	{
		// �G�t�F�N�g���l��EFFECT_SPEED������
		effectB -= B_EFFECT_SPEED;

		// �G�t�F�N�g���l���ŏ�
		if (effectB == B_ALPHA_BASE)
		{
			// �t���O���v���X�ɂ�
			effectflagB = true;
		}

	}


	// �A�j���[�V����
	// �\���̍ő吔�X�V����
	for (int i = 0; i < TITLE_MAX;i++, title++)
	{

		//		//	 �f�o�b�O�p�ړ��g�又��
		//		if (i == TITLE_START)
		//		{
		//
		//			// ��
		//			if (GetKeyboardPress(DIK_V))
		//			{
		//				title->pos.x--;
		//			}
		//
		//			// �E
		//			else if (GetKeyboardPress(DIK_B))
		//			{
		//				title->pos.x++;
		//			}
		//
		//			// ��
		//			if (GetKeyboardPress(DIK_N))
		//			{
		//				title->pos.y--;
		//
		//			}
		//			// ��
		//			else if (GetKeyboardPress(DIK_M))
		//			{
		//				title->pos.y++;
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
		//			PrintDebugProc("���W:X %f)\n", title->pos.x);
		//			PrintDebugProc("���W:Y %f)\n", title->pos.y);
		//#endif
		//		}

		// �G�t�F�N�g����
		SetVertexTitleEffect(i);
	}

	// �X�e�[�W�J�ڏ���
	// ���N����
	if (serect == FIRST)
	{

		// Enter��������A�X�e�[�W��؂�ւ���
		if ((GetKeyboardTrigger(DIK_A))||(IsButtonTriggered(0, BUTTON_START)))
		{

			// �J�[�\������SE�̍Đ�
			PlaySound(SE_PUSH, E_DS8_FLAG_NONE);

			// �|�C���^�̏�����
			TITLE *title = &titleWk[TITLE_ANY];

			// UI�����̍X�V����
			for (int i = TITLE_ANY;i < TITLE_MAX;i++, title++)
			{

				// �ŏ��ɕ\��������̂��g�p
				if ((i == TITLE_START) || (i == TITLE_START_EFFECT) || (i == TITLE_CREDIT))
				{
					title->use = true;
				}

				// ����ȊO�𖢎g�p
				else
				{
					title->use = false;
				}

			}

			// �Z���N�gUI�̕\��
			serect = UPDATA;
		}
	}

	// �Z���N�gUI�̕\����
	else if(serect == UPDATA)
	{
		// �g�p����\���̂̃|�C���^�̏�����
		TITLE *titles = &titleWk[TITLE_START];						// UI:"�͂��߂�"
		TITLE *titleS = &titleWk[TITLE_START_EFFECT];				// UI�G�t�F�N�g:"�͂��߂�"
		TITLE *titlec = &titleWk[TITLE_CREDIT];						// UI:"�N���W�b�g"
		TITLE *titleC = &titleWk[TITLE_CREDIT_EFFECT];				// UI�G�t�F�N�g:"�N���W�b�g"

		// �J�[�\���ړ�
		switch (titlecnt)
		{

		// UI:"�͂��߂�"�̏���
		case TITLE_UI_START:
		{

			// UI�G�t�F�N�g:"�͂��߂�"���g�p��
			titleS->use = true;

			// UI�G�t�F�N�g:"�N���W�b�g"�𖢎g�p��
			titleC->use = false;

			// UI:"�͂��߂�"�̐F��ω�
			titles->vertex[0].diffuse = COLOR_RED;
			titles->vertex[1].diffuse = COLOR_BULE;
			titles->vertex[2].diffuse = COLOR_BULE;
			titles->vertex[3].diffuse = COLOR_BULE;

			// UI:"�N���W�b�g"�̐F�����ɖ߂�
			titlec->vertex[0].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
			titlec->vertex[1].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
			titlec->vertex[2].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
			titlec->vertex[3].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);

			// Enter�܂��́~�{�^������������A�X�e�[�W��؂�ւ���
			if ((GetKeyboardTrigger(DIK_RETURN)) || (IsButtonTriggered(0, BUTTON_C)))
			{

				// �J�[�\������SE�̍Đ�
				PlaySound(SE_PUSH, E_DS8_FLAG_NONE);

				// ��ʑJ��:�Q�[��
				SetFade(FADE_OUT);

			}

			// W�܂��́��X�e�B�b�N����������A�J�[�\���ړ�
			if ((GetKeyboardTrigger(DIK_W)) || (IsButtonTriggered(0, BUTTON_UP)))
			{

				// �J�[�\���I��SE�̍Đ�
				PlaySound(SE_SERECT, E_DS8_FLAG_NONE);

				// �J�[�\������Ɉړ�
				titlecnt--;
			}

			// S�܂��́��X�e�B�b�N����������A�J�[�\���ړ�
			else if ((GetKeyboardTrigger(DIK_S)) || (IsButtonTriggered(0, BUTTON_DOWN)))
			{

				// �J�[�\���I��SE�̍Đ�
				PlaySound(SE_SERECT, E_DS8_FLAG_NONE);

				// �J�[�\�������Ɉړ�
				titlecnt++;
			}

			break;
		}

		// UI:"�N���W�b�g"�̏���
		case TITLE_UI_CREDIT:
		{

			// UI�G�t�F�N�g:"�N���W�b�g"���g�p��
			titleC->use = true;

			// UI:"�N���W�b�g"�̐F�����F��
			titlec->vertex[0].diffuse = COLOR_RED;
			titlec->vertex[1].diffuse = COLOR_BULE;
			titlec->vertex[2].diffuse = COLOR_BULE;
			titlec->vertex[3].diffuse = COLOR_BULE;

			// UI:"�͂��߂�"�̐F�����ɖ߂�
			titles->vertex[0].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
			titles->vertex[1].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
			titles->vertex[2].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
			titles->vertex[3].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);

			// UI�G�t�F�N�g:"�͂��߂�"�𖢎g�p��
			titleS->use = false;

			// Enter�܂��́~�{�^������������A�N���W�b�g��\��
			if ((GetKeyboardTrigger(DIK_RETURN)) || (IsButtonTriggered(0, BUTTON_C)))
			{

				// �J�[�\������SE�̍Đ�
				PlaySound(SE_PUSH, E_DS8_FLAG_NONE);

				// �J�[�\������ϐ����N���W�b�g��
				serect = CREDIT;

			}

			// W�܂��́��X�e�B�b�N����������A�J�[�\���ړ�
			if ((GetKeyboardTrigger(DIK_W)) || (IsButtonTriggered(0, BUTTON_UP)))
			{

				// �J�[�\���I��SE�̍Đ�
				PlaySound(SE_SERECT, E_DS8_FLAG_NONE);

				// �J�[�\������Ɉړ�
				titlecnt--;
			}

			// S�܂��́��X�e�B�b�N����������A�J�[�\���ړ�
			else if ((GetKeyboardTrigger(DIK_S)) || (IsButtonTriggered(0, BUTTON_DOWN)))
			{

				// �J�[�\���I��SE�̍Đ�
				PlaySound(SE_SERECT, E_DS8_FLAG_NONE);

				// �J�[�\�������Ɉړ�
				titlecnt++;
			}

			break;
		}

		}

		// �J�[�\�����[�v�ړ�����
		// UI:"�͂��߂�"�Ł����͎�
		if (titlecnt < TITLE_UI_START)
		{
			// UI:"�N���W�b�g"�Ɉړ�
			titlecnt = TITLE_UI_MAX - 1;
		}

		// UI:"�N���W�b�g"�Ł����͎�
		else if (titlecnt > TITLE_UI_MAX - 1)
		{
			// UI:"�͂��߂�"�Ɉړ�
			titlecnt = TITLE_UI_START;
		}
	}

	// UI:"�N���W�b�gED"(�N���W�b�g�e�N�X�`��)
	else if (serect == CREDIT)
	{

		// �g�p����\���̂̃|�C���^�̏����� UI:"�N���W�b�gED"(�N���W�b�g�e�N�X�`��)
		TITLE *titleB = &titleWk[TITLE_BOAD];

		// UI:"�N���W�b�gED"(�N���W�b�g�e�N�X�`��)��\��
		titleB ->use= true;

		// Enter�܂��́~�{�^������������A�J�[�\���I���ɖ߂�
		if ((GetKeyboardTrigger(DIK_RETURN)) || (IsButtonTriggered(0, BUTTON_C)))
		{

			// �J�[�\������SE�̍Đ�
			PlaySound(SE_PUSH, E_DS8_FLAG_NONE);

			titleB->use = false;			// UI:"�N���W�b�gED"(�N���W�b�g�e�N�X�`��)���\��
			serect = UPDATA;				// �O�̃J�[�\���I�������ɖ߂�
			titlecnt = TITLE_UI_START;		// �J�[�\���������ʒu�ɖ߂�
		}

	}


}
//=============================================================================
// �`�揈���֐�
//=============================================================================
void DrawTitle(void)
{
	// �|�C���^�̏�����
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TITLE *title = &titleWk[0];
	
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ���e�X�g��L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, g_Alpha);		 //�����F�ϐ����l
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);//����:�傫��������

	// �\���̍ő吔�I������
	for (int i = 0; i < TITLE_MAX;i++, title++)
	{

		// �e�N�X�`���g�p��
		if (title->use == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, title->Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, title->vertex, sizeof(VERTEX_2D));
		}
	}

	// ���e�X�g�𖳌���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

//#ifdef _DEBUG
//	// �f�o�b�O���b�Z�[�W�\��
//	DrawDebugProc();
//#endif

}

//=============================================================================
// ���_�̍쐬�֐�
//=============================================================================
HRESULT MakeVertexTitle(int no)
{
	
	// �|�C���^�̏�����
	TITLE *title = &titleWk[no];

	// �^�C�g���w�i�Ȃ�
	if ((no==TITLE_BASE)|| (no == TITLE_BASE_LIGHT))
	{
		// ���_���W�̐ݒ�
		title->vertex[0].vtx = D3DXVECTOR3(title->pos.x - TITLE_BASE_SIZE_X, title->pos.y - TITLE_BASE_SIZE_Y, 0.0f);
		title->vertex[1].vtx = D3DXVECTOR3(title->pos.x + TITLE_BASE_SIZE_X, title->pos.y - TITLE_BASE_SIZE_Y, 0.0f);
		title->vertex[2].vtx = D3DXVECTOR3(title->pos.x - TITLE_BASE_SIZE_X, title->pos.y + TITLE_BASE_SIZE_Y, 0.0f);
		title->vertex[3].vtx = D3DXVECTOR3(title->pos.x + TITLE_BASE_SIZE_X, title->pos.y + TITLE_BASE_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		title->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 180);
		title->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 180);
		title->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 180);
		title->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 180);

	}

	// �^�C�g���w�i�G�t�F�N�g
	else if (no == TITLE_EFFECT)
	{
		// ���_���W�̐ݒ�
		title->vertex[0].vtx = D3DXVECTOR3(title->pos.x - TITLE_EFFECT_SIZE_X, title->pos.y - TITLE_EFFECT_SIZE_Y, 0.0f);
		title->vertex[1].vtx = D3DXVECTOR3(title->pos.x + TITLE_EFFECT_SIZE_X, title->pos.y - TITLE_EFFECT_SIZE_Y, 0.0f);
		title->vertex[2].vtx = D3DXVECTOR3(title->pos.x - TITLE_EFFECT_SIZE_X, title->pos.y + TITLE_EFFECT_SIZE_Y, 0.0f);
		title->vertex[3].vtx = D3DXVECTOR3(title->pos.x + TITLE_EFFECT_SIZE_X, title->pos.y + TITLE_EFFECT_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		title->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 180);
		title->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 180);
		title->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 180);
		title->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 180);
	}

	// �L�����N�^�[:AI
	else if (no == TITLE_AI)
	{
		// ���_���W�̐ݒ�
		title->vertex[0].vtx = D3DXVECTOR3(title->pos.x - TITLE_AI_SIZE_X, title->pos.y - TITLE_AI_SIZE_Y, 0.0f);
		title->vertex[1].vtx = D3DXVECTOR3(title->pos.x + TITLE_AI_SIZE_X, title->pos.y - TITLE_AI_SIZE_Y, 0.0f);
		title->vertex[2].vtx = D3DXVECTOR3(title->pos.x - TITLE_AI_SIZE_X, title->pos.y + TITLE_AI_SIZE_Y, 0.0f);
		title->vertex[3].vtx = D3DXVECTOR3(title->pos.x + TITLE_AI_SIZE_X, title->pos.y + TITLE_AI_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		title->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// �L�����N�^�[:�E�C���X
	else if (no == TITLE_VIRUS)
	{
		// ���_���W�̐ݒ�
		title->vertex[0].vtx = D3DXVECTOR3(title->pos.x - TITLE_VIRUS_SIZE_X, title->pos.y - TITLE_VIRUS_SIZE_Y, 0.0f);
		title->vertex[1].vtx = D3DXVECTOR3(title->pos.x + TITLE_VIRUS_SIZE_X, title->pos.y - TITLE_VIRUS_SIZE_Y, 0.0f);
		title->vertex[2].vtx = D3DXVECTOR3(title->pos.x - TITLE_VIRUS_SIZE_X, title->pos.y + TITLE_VIRUS_SIZE_Y, 0.0f);
		title->vertex[3].vtx = D3DXVECTOR3(title->pos.x + TITLE_VIRUS_SIZE_X, title->pos.y + TITLE_VIRUS_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		title->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}


	// �^�C�g�����S
	else if (no == TITLE_LOGO)
	{
		// ���_���W�̐ݒ�
		title->vertex[0].vtx = D3DXVECTOR3(title->pos.x - TITLE_LOGO_SIZE_X, title->pos.y - TITLE_LOGO_SIZE_Y, 0.0f);
		title->vertex[1].vtx = D3DXVECTOR3(title->pos.x + TITLE_LOGO_SIZE_X, title->pos.y - TITLE_LOGO_SIZE_Y, 0.0f);
		title->vertex[2].vtx = D3DXVECTOR3(title->pos.x - TITLE_LOGO_SIZE_X, title->pos.y + TITLE_LOGO_SIZE_Y, 0.0f);
		title->vertex[3].vtx = D3DXVECTOR3(title->pos.x + TITLE_LOGO_SIZE_X, title->pos.y + TITLE_LOGO_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		title->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}


	// UI:"�{�^���������Ă�"
	else if (no == TITLE_ANY)
	{
		// ���_���W�̐ݒ�
		title->vertex[0].vtx = D3DXVECTOR3(title->pos.x - TITLE_ANY_SIZE_X, title->pos.y - TITLE_ANY_SIZE_Y, 0.0f);
		title->vertex[1].vtx = D3DXVECTOR3(title->pos.x + TITLE_ANY_SIZE_X, title->pos.y - TITLE_ANY_SIZE_Y, 0.0f);
		title->vertex[2].vtx = D3DXVECTOR3(title->pos.x - TITLE_ANY_SIZE_X, title->pos.y + TITLE_ANY_SIZE_Y, 0.0f);
		title->vertex[3].vtx = D3DXVECTOR3(title->pos.x + TITLE_ANY_SIZE_X, title->pos.y + TITLE_ANY_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		title->vertex[0].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		title->vertex[1].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		title->vertex[2].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		title->vertex[3].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);

	}


	// UI�G�t�F�N�g:"�{�^���������Ă�"
	else if (no == TITLE_ANY_EFFECT)
	{
		// ���_���W�̐ݒ�
		title->vertex[0].vtx = D3DXVECTOR3(title->pos.x - TITLE_ANY_EFFECT_SIZE_X, title->pos.y - TITLE_ANY_EFFECT_SIZE_Y, 0.0f);
		title->vertex[1].vtx = D3DXVECTOR3(title->pos.x + TITLE_ANY_EFFECT_SIZE_X, title->pos.y - TITLE_ANY_EFFECT_SIZE_Y, 0.0f);
		title->vertex[2].vtx = D3DXVECTOR3(title->pos.x - TITLE_ANY_EFFECT_SIZE_X, title->pos.y + TITLE_ANY_EFFECT_SIZE_Y, 0.0f);
		title->vertex[3].vtx = D3DXVECTOR3(title->pos.x + TITLE_ANY_EFFECT_SIZE_X, title->pos.y + TITLE_ANY_EFFECT_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		title->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, effect);
		title->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, effect);
		title->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, effect);
		title->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, effect);

	}

	// UI:"�͂��߂�"
	else if (no == TITLE_START)
	{
		// ���_���W�̐ݒ�
		title->vertex[0].vtx = D3DXVECTOR3(title->pos.x - TITLE_START_SIZE_X, title->pos.y - TITLE_START_SIZE_Y, 0.0f);
		title->vertex[1].vtx = D3DXVECTOR3(title->pos.x + TITLE_START_SIZE_X, title->pos.y - TITLE_START_SIZE_Y, 0.0f);
		title->vertex[2].vtx = D3DXVECTOR3(title->pos.x - TITLE_START_SIZE_X, title->pos.y + TITLE_START_SIZE_Y, 0.0f);
		title->vertex[3].vtx = D3DXVECTOR3(title->pos.x + TITLE_START_SIZE_X, title->pos.y + TITLE_START_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		title->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255,255, 255);
		title->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255,255, 255);
		title->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255,255, 255);
		title->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255,255, 255);

	}


	// UI�G�t�F�N�g:"�͂��߂�"
	else if (no == TITLE_START_EFFECT)
	{
		// ���_���W�̐ݒ�
		title->vertex[0].vtx = D3DXVECTOR3(title->pos.x - TITLE_START_EFFECT_SIZE_X, title->pos.y - TITLE_START_EFFECT_SIZE_Y, 0.0f);
		title->vertex[1].vtx = D3DXVECTOR3(title->pos.x + TITLE_START_EFFECT_SIZE_X, title->pos.y - TITLE_START_EFFECT_SIZE_Y, 0.0f);
		title->vertex[2].vtx = D3DXVECTOR3(title->pos.x - TITLE_START_EFFECT_SIZE_X, title->pos.y + TITLE_START_EFFECT_SIZE_Y, 0.0f);
		title->vertex[3].vtx = D3DXVECTOR3(title->pos.x + TITLE_START_EFFECT_SIZE_X, title->pos.y + TITLE_START_EFFECT_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		title->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, effect);
		title->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, effect);
		title->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, effect);
		title->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, effect);

	}


	// UI:"�N���W�b�g"
	else if (no == TITLE_CREDIT)
	{
		// ���_���W�̐ݒ�
		title->vertex[0].vtx = D3DXVECTOR3(title->pos.x - TITLE_CREDIT_SIZE_X, title->pos.y - TITLE_CREDIT_SIZE_Y, 0.0f);
		title->vertex[1].vtx = D3DXVECTOR3(title->pos.x + TITLE_CREDIT_SIZE_X, title->pos.y - TITLE_CREDIT_SIZE_Y, 0.0f);
		title->vertex[2].vtx = D3DXVECTOR3(title->pos.x - TITLE_CREDIT_SIZE_X, title->pos.y + TITLE_CREDIT_SIZE_Y, 0.0f);
		title->vertex[3].vtx = D3DXVECTOR3(title->pos.x + TITLE_CREDIT_SIZE_X, title->pos.y + TITLE_CREDIT_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		title->vertex[0].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		title->vertex[1].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		title->vertex[2].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		title->vertex[3].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);

	}

	// UI�G�t�F�N�g:"�N���W�b�g"
	else if (no == TITLE_CREDIT_EFFECT)
	{
		// ���_���W�̐ݒ�
		title->vertex[0].vtx = D3DXVECTOR3(title->pos.x - TITLE_START_EFFECT_SIZE_X, title->pos.y - TITLE_START_EFFECT_SIZE_Y, 0.0f);
		title->vertex[1].vtx = D3DXVECTOR3(title->pos.x + TITLE_START_EFFECT_SIZE_X, title->pos.y - TITLE_START_EFFECT_SIZE_Y, 0.0f);
		title->vertex[2].vtx = D3DXVECTOR3(title->pos.x - TITLE_START_EFFECT_SIZE_X, title->pos.y + TITLE_START_EFFECT_SIZE_Y, 0.0f);
		title->vertex[3].vtx = D3DXVECTOR3(title->pos.x + TITLE_START_EFFECT_SIZE_X, title->pos.y + TITLE_START_EFFECT_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		title->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, effect);
		title->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, effect);
		title->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, effect);
		title->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, effect);

	}

	// UI:"�N���W�b�gED"(�N���W�b�g�e�N�X�`��)
	else if (no == TITLE_BOAD)
	{
		// ���_���W�̐ݒ�
		title->vertex[0].vtx = D3DXVECTOR3(title->pos.x - TITLE_BOAD_SIZE_X, title->pos.y - TITLE_BOAD_SIZE_Y, 0.0f);
		title->vertex[1].vtx = D3DXVECTOR3(title->pos.x + TITLE_BOAD_SIZE_X, title->pos.y - TITLE_BOAD_SIZE_Y, 0.0f);
		title->vertex[2].vtx = D3DXVECTOR3(title->pos.x - TITLE_BOAD_SIZE_X, title->pos.y + TITLE_BOAD_SIZE_Y, 0.0f);
		title->vertex[3].vtx = D3DXVECTOR3(title->pos.x + TITLE_BOAD_SIZE_X, title->pos.y + TITLE_BOAD_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		title->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		title->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}


	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	title->vertex[0].rhw =
	title->vertex[1].rhw =
	title->vertex[2].rhw =
	title->vertex[3].rhw = 1.0f;


	// �e�N�X�`�����W�̐ݒ�
	title->vertex[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	title->vertex[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	title->vertex[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	title->vertex[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// �G�t�F�N�g�֐�
//=============================================================================
void SetVertexTitleEffect(int no)
{

	// �|�C���^�̏�����
	TITLE *title = &titleWk[no];



	// �f�o�b�O�p�e�N�X�`���X�V
	// HP�o�[
	//if (no == TITLE_START)
	//{
	//	// ���_���W�̐ݒ�
	//	title->vertex[0].vtx = D3DXVECTOR3(title->pos.x - sizex, title->pos.y - sizey, 0.0f);
	//	title->vertex[1].vtx = D3DXVECTOR3(title->pos.x + sizex, title->pos.y - sizey, 0.0f);
	//	title->vertex[2].vtx = D3DXVECTOR3(title->pos.x - sizex, title->pos.y + sizey, 0.0f);
	//	title->vertex[3].vtx = D3DXVECTOR3(title->pos.x + sizex, title->pos.y + sizey, 0.0f);

	//}


	// �ύX���ꂽ�G�t�F�N�g�̃��l�̐ݒ�
	// �^�C�g���w�i
	if (no == TITLE_BASE_LIGHT)
	{

		 //���ˌ��̐ݒ�
		title->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, effectB);
		title->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, effectB);
		title->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, effectB);
		title->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, effectB);

	}

	// UI�G�t�F�N�g:"�{�^���������Ă�"
	 if (no == TITLE_ANY_EFFECT)
	{

		// ���ˌ��̐ݒ�
		title->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, effect);
		title->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, effect);
		title->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, effect);
		title->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, effect);

	}

	 // UI�G�t�F�N�g:"�͂��߂�"
	 if (no == TITLE_START_EFFECT)
	 {

		 // ���ˌ��̐ݒ�
		 title->vertex[0].diffuse = D3DCOLOR_RGBA(255, 0, 0, effect);
		 title->vertex[1].diffuse = D3DCOLOR_RGBA(0, 0, 255, effect);
		 title->vertex[2].diffuse = D3DCOLOR_RGBA(255, 0, 0, effect);
		 title->vertex[3].diffuse = D3DCOLOR_RGBA(0, 0, 255, effect);

	 }

	 // UI�G�t�F�N�g:"�������"
	 if (no == TITLE_CREDIT_EFFECT)
	 {

		 // ���ˌ��̐ݒ�
		 title->vertex[0].diffuse = D3DCOLOR_RGBA(255, 0, 0, effect);
		 title->vertex[1].diffuse = D3DCOLOR_RGBA(0, 0, 255, effect);
		 title->vertex[2].diffuse = D3DCOLOR_RGBA(255, 0, 0, effect);
		 title->vertex[3].diffuse = D3DCOLOR_RGBA(0, 0, 255, effect);

	 }

}

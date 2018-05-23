//=============================================================================
//
// �^�C�g����ʏ��� [result.cpp]
// Author : ���ˌ��j��
// �v���O�����쐬�� : 2018/3/09
//
//=============================================================================
#include "result.h"				// �\���́��}�N���g�p�̈�
#include "main.h"				// �}�N���g�p�̈�
#include "input.h"				// �֐��g�p�̈�
#include "game.h"				// �֐����}�N���g�p�̈�
#include "debugproc.h"			// �֐��g�p�̈�(�f�o�b�O�p)
#include "sound.h"				// �֐��g�p�̈�
#include "fade.h"				// ����
#include "title.h"				// �}�N���g�p�̈�
#include "timer.h"				// ����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexResult(int no);					// ���_�쐬�֐�
void SetVertexResultEffect(int no);					// �G�t�F�N�g�֐�

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************


RESULT resultWk[RESULT_MAX];						// �^�C�g���\���̍ő吔�錾

bool resultflag;									// �G�t�F�N�g�p����ϐ�
int resulteffect;									// �G�t�F�N�g�p�ϐ�
int resulteffectB;									// �G�t�F�N�g�p�ϐ�

int resultserect;									// ��ʑJ�ڐ���ϐ�
int resultcnt;										// �J�[�\������ϐ�

float rankpos;

int bgmcnt;

bool winflag;										// �����t���O

//float sizex, sizey;								// �f�o�b�O�p�e�N�X�`���ړ������ϐ�


//=============================================================================
// �����������֐�
//=============================================================================
HRESULT InitResult(int type)
{

	// �|�C���^�̏�����
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	RESULT *result = &resultWk[0];

	// �G�t�F�N�g�֌W�̏�����
	resultflag = true;				// true:�v���X���� false:�}�C�i�X����
	resulteffect = INIT_EFFECT;		// �G�t�F�N�g�̃��l�̏�����

	// �����t���O�̏�����
	winflag = true;

	// ��ʐ���ϐ��̏�����
	resultserect = 0;
	resultcnt = 0;

	resulteffectB = 0;

	bgmcnt = RESULT_BGM_TIME*FRAME_CNT;

	// �X�N���[���T�C�Y
	rankpos = SCREEN_WIDTH;

	//// �f�o�b�O�p�e�N�X�`���ړ������ϐ��̏�����
	//sizex = RESULT_RANK_SIZE_X;
	//sizey = RESULT_RANK_SIZE_Y;

	// �\���̍ő吔����������
	for (int i = 0; i < RESULT_MAX;i++, result++)
	{

		// ���N����
		if (type == FIRST)
		{

			// �S��NULL�ŏ�����
			result->Texture = NULL;

			// �w�i
			if (i == RESULT_BASE)
			{
				// �ʒu�̐ݒ�
				result->use = true;					// �g�p�ŏ�����
				result->pos = RESULT_BASE_POS;		// �w�i�̈ʒu

				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					RESULT_BASE_TEXTURE,			// �t�@�C���̖��O
					&result->Texture);				// �ǂݍ��ރ������[
			}

			// �w�i
			else if (i == RESULT_BASE_LIGHT)
			{
				// �ʒu�̐ݒ�
				result->use = true;					// �g�p�ŏ�����
				result->pos = RESULT_BASE_POS;		// �w�i�̈ʒu

													// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					RESULT_BASE_LIGHT_TEXTURE,			// �t�@�C���̖��O
					&result->Texture);				// �ǂݍ��ރ������[
			}



			// �����t���O�v���C���[
			else if (i == RESULT_BOAD_AI)
			{
				// �ʒu�̐ݒ�
				result->use = false;					// �g�p�ŏ�����
				result->pos = RESULT_BASE_POS;		// ���U���g�{�[�h�̈ʒu

				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					RESULT_BOAD_AI_TEXTURE,			// �t�@�C���̖��O
					&result->Texture);				// �ǂݍ��ރ������[
			}

			// �����t���O�E�C���X
			else if (i == RESULT_BOAD_VIRUS)
			{
				// �ʒu�̐ݒ�
				result->use = false;					// �g�p�ŏ�����
				result->pos = RESULT_BASE_POS;		// ���U���g�{�[�h�̈ʒu

				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					RESULT_BOAD_VIRUS_TEXTURE,		// �t�@�C���̖��O
					&result->Texture);				// �ǂݍ��ރ������[
			}

			// �����v���C���[
			else if (i == RESULT_AI)
			{
				// �ʒu�̐ݒ�
				result->use = false;					// �g�p�ŏ�����
				result->pos = RESULT_AI_POS;		// ���U���g�{�[�h�̈ʒu

				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					RESULT_AI_TEXTURE,			// �t�@�C���̖��O
					&result->Texture);				// �ǂݍ��ރ������[
			}

			// �����E�C���X
			else if (i == RESULT_VIRUS)
			{
				// �ʒu�̐ݒ�
				result->use = false;					// �g�p�ŏ�����
				result->pos = RESULT_VIRUS_POS;		// ���U���g�{�[�h�̈ʒu

													// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					RESULT_VIRUS_TEXTURE,		// �t�@�C���̖��O
					&result->Texture);				// �ǂݍ��ރ������[
			}

			// �]���v���C���[
			else if (i == RESULT_AI_RANK)
			{
				// �ʒu�̐ݒ�
				result->use = false;						// �g�p�ŏ�����
				result->pos = RESULT_RANK_POS;			// �]���̈ʒu

				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
					RESULT_AI_RANK_TEXTURE,				// �t�@�C���̖��O
					&result->Texture);					// �ǂݍ��ރ������[
			}

			// �G�t�F�N�g:�]���v���C���[
			else if (i == RESULT_AI_RANK_EFFECT)
			{
				// �ʒu�̐ݒ�
				result->use = false;						// �g�p�ŏ�����
				result->pos = RESULT_RANK_POS;			// �G�t�F�N�g:�]���̈ʒu

				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
					RESULT_AI_RANK_TEXTURE,				// �t�@�C���̖��O
					&result->Texture);					// �ǂݍ��ރ������[
			}

			// �]���E�C���X
			else if (i == RESULT_VIRUS_RANK)
			{
				// �ʒu�̐ݒ�
				result->use = false;						// �g�p�ŏ�����
				result->pos = RESULT_RANK_POS;			// �]���̈ʒu

														// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
					RESULT_VIRUS_RANK_TEXTURE,				// �t�@�C���̖��O
					&result->Texture);					// �ǂݍ��ރ������[
			}

			// �G�t�F�N�g:�]���E�C���X
			else if (i == RESULT_VIRUS_RANK_EFFECT)
			{
				// �ʒu�̐ݒ�
				result->use = false;						// �g�p�ŏ�����
				result->pos = RESULT_RANK_POS;			// �G�t�F�N�g:�]���̈ʒu

														// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
					RESULT_VIRUS_RANK_TEXTURE,				// �t�@�C���̖��O
					&result->Texture);					// �ǂݍ��ރ������[
			}


			// �����j���[
			else if (i == RESULT_BLACK_S)
			{
				// �ʒu�̐ݒ�
				result->use = false;					// ���g�p�ŏ�����
				result->pos = RESULT_BLACK_S_POS;		// �����j���[�̈ʒu

				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
					RESULT_BLACK_S_TEXTURE,				// �t�@�C���̖��O
					&result->Texture);					// �ǂݍ��ރ������[
			}

			// UI:"���Ȃ���"
			// UI�G�t�F�N�g:"���Ȃ���"
			else if ((i == RESULT_INIT) || (i == RESULT_INIT_EFFECT))
			{
				// �ʒu�̐ݒ�
				result->use = false;					// ���g�p�ŏ�����
				result->pos = RESULT_INIT_POS;			// UI:"���Ȃ���" UI�G�t�F�N�g:"���Ȃ���"�̈ʒu

				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
					RESULT_INIT_TEXTURE,				// �t�@�C���̖��O
					&result->Texture);					// �ǂݍ��ރ������[
			}

			// UI:"�����"
			// UI�G�t�F�N�g:"�����"
			else if ((i == RESULT_FINISH) || (i == RESULT_FINISH_EFFECT))
			{
				// �ʒu�̐ݒ�
				result->use = false;					// ���g�p�ŏ�����
				result->pos = RESULT_FINISH_POS;		// UI:"�����" UI�G�t�F�N�g:"�����"�̈ʒu

				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
					RESULT_FINISH_TEXTURE,				// �t�@�C���̖��O
					&result->Texture);					// �ǂݍ��ރ������[
			}
		}

		// �Q�[���X�V��
		else if (type == UPDATA)
		{
			// ���j���[�ōŏ��\��������̈ȊO�͖��g�p�ŏ�����
			if ((i == RESULT_BASE) || (i == RESULT_BASE_LIGHT))
			{
				result->use = true;					// ���g�p�ŏ�����
			}

			else
			{
				result->use = false;							// �g�p�ŏ�����
			}
		}


		// ���_���̍쐬
		MakeVertexResult(i);
	}

	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void UninitResult(void)
{
	// �|�C���^�̏�����
	RESULT *result = &resultWk[0];

	// �\���̍ő吔�I������
	for (int i = 0; i < RESULT_MAX;i++, result++)
	{

		// �e�N�X�`���̊J���o���Ă��Ȃ�������
		if (result->Texture != NULL)
		{

			// �e�N�X�`���̊J��
			result->Texture->Release();
			result->Texture = NULL;
		}
	}

}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void UpdateResult(void)
{

	// �|�C���^�̏�����
	RESULT *result = &resultWk[0];
	RESULT *resultLight = &resultWk[RESULT_BASE_LIGHT];
	RESULT *resultAi = &resultWk[RESULT_BOAD_AI];
	RESULT *resultVirus = &resultWk[RESULT_BOAD_VIRUS];


	// �w�i����
	if (winflag == true)
	{
		resultAi->use = true;
	}
	else if (winflag == false)
	{
		resultVirus->use = true;
	}


	// �G�t�F�N�g���l���ő�
	if (resulteffectB >= ALPHA_MAX)
	{
		// �t���O���}�C�i�X��
		resulteffectB = ALPHA_MAX;
		resultLight->use = false;
		if (winflag == true)
		{

			for (int i = RESULT_BOAD_AI;i <= RESULT_AI_RANK_EFFECT;i++, resultAi++)
			{
				resultAi->use = true;
			}
		}

		else if (winflag == false)
		{
			for (int i = RESULT_BOAD_VIRUS;i <= RESULT_VIRUS_RANK_EFFECT;i++, resultVirus++)
			{
				resultVirus->use = true;
			}

		}

	}

	else if (resulteffectB < ALPHA_MAX)
	{
		// �G�t�F�N�g���l��EFFECT_SPEED�𑫂�
		resulteffectB += RESULT_SPEED;

	}


	// �G�t�F�N�g����
	if (resultflag == true)
	{
		// �G�t�F�N�g���l��EFFECT_SPEED�𑫂�
		resulteffect += RESULT_EFFECT_SPEED;

		// �G�t�F�N�g���l���ő�
		if (resulteffect == ALPHA_MAX)
		{
			// �t���O���}�C�i�X��
			resultflag = false;
		}
	}

	// �}�C�i�X�t���O
	else if (resultflag == false)
	{
		// �G�t�F�N�g���l��EFFECT_SPEED������
		resulteffect -= RESULT_EFFECT_SPEED;

		// �G�t�F�N�g���l���ŏ�
		if (resulteffect == ALPHA_BASE)
		{
			// �t���O���v���X��
			resultflag = true;
		}

	}

	// �A�j���[�V����
	// �\���̍ő吔�X�V����
	for (int i = 0; i < RESULT_MAX;i++, result++)
	{

		if ((i == RESULT_AI_RANK) || (i == RESULT_VIRUS_RANK))
		{
			if (result->use == true)
			{
				rankpos -= RESULT_RANK_SPEED;

				if (rankpos < SCREEN_WIDTH / 2)
				{
					rankpos = SCREEN_WIDTH / 2;
				}
			}
		}

		// //�f�o�b�O�p�ړ��g�又��
		//if (i == RESULT_VIRUS)
		//		{
		//
		//			// ��
		//			if (GetKeyboardPress(DIK_V))
		//			{
		//				result->pos.x--;
		//			}
		//			// �E
		//			else if (GetKeyboardPress(DIK_B))
		//			{
		//				result->pos.x++;
		//			}
		//
		//			// ��
		//			if (GetKeyboardPress(DIK_N))
		//			{
		//				result->pos.y--;
		//
		//			}
		//			// ��
		//			else if (GetKeyboardPress(DIK_M))
		//			{
		//				result->pos.y++;
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
		//			PrintDebugProc("���W:X %f)\n", result->pos.x);
		//			PrintDebugProc("���W:Y %f)\n", result->pos.y);
		//#endif
		//		}


		// �G�t�F�N�g����
		SetVertexResultEffect(i);

	}


	bgmcnt--;
	if (bgmcnt == 0)
	{
		StopSound(BGM_CALL_RESULT);							// �ʏ�퓬BGM�̒�~
		PlaySound(BGM_RESULT, E_DS8_FLAG_LOOP);		// ���U���gBGM�̍Đ�

	}

	// ���U���g�J�ڏ���
	// ����
	if (resultserect == FIRST)
	{

		// Enter��������A�X�e�[�W��؂�ւ���
		if ((GetKeyboardTrigger(DIK_A)) || (IsButtonTriggered(0, BUTTON_START)))
		{

			// �J�[�\������SE�̍Đ�
			PlaySound(SE_PUSH, E_DS8_FLAG_NONE);

			// �|�C���^�̏�����
			RESULT *result = &resultWk[RESULT_BLACK_S];

			// ���U���g�J�[�\�������̍X�V����
			for (int i = RESULT_BLACK_S;i < RESULT_MAX;i++, result++)
			{
				// �ŏ��ɕ\�����Ȃ����̂𖢎g�p
				if (i == RESULT_FINISH_EFFECT)
				{
					result->use = false;
				}

				// �ŏ��ɕ\��������̂��g�p
				else
				{
					result->use = true;
				}
			}

			// �Z���N�gUI�̕\��
			resultserect = UPDATA;
		}
	}

	// �Z���N�gUI�̕\����
	else if (resultserect == UPDATA)
	{

		// �g�p����\���̂̃|�C���^�̏�����
		RESULT *resultS = &resultWk[RESULT_INIT_EFFECT];
		RESULT *results = &resultWk[RESULT_INIT];
		RESULT *resultC = &resultWk[RESULT_FINISH_EFFECT];
		RESULT *resultc = &resultWk[RESULT_FINISH];

		// �Z���N�g���j���[�̕\����
		switch (resultcnt)
		{

			// UI:"���Ȃ���"�̏���
		case RESULT_UI_INIT:
		{

			// UI�G�t�F�N�g:"���Ȃ���"�̏���
			resultS->use = true;

			// UI�G�t�F�N�g:"�����"�𖢎g�p��
			resultC->use = false;

			// UI:"���Ȃ���"�̐F�����F��
			results->vertex[0].diffuse = D3DCOLOR_RGBA(255, 0, 0, 255);
			results->vertex[1].diffuse = D3DCOLOR_RGBA(0, 0, 255, 255);
			results->vertex[2].diffuse = D3DCOLOR_RGBA(0, 0, 255, 255);
			results->vertex[3].diffuse = D3DCOLOR_RGBA(0, 0, 255, 255);

			// UI:"�����"�̐F�����ɖ߂�
			resultc->vertex[0].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
			resultc->vertex[1].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
			resultc->vertex[2].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
			resultc->vertex[3].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);

			// Enter�܂��́~�{�^������������A�Q�[����������
			if ((GetKeyboardTrigger(DIK_RETURN)) || (IsButtonTriggered(0, BUTTON_C)))
			{

				// �J�[�\������SE�̍Đ�
				PlaySound(SE_PUSH, E_DS8_FLAG_NONE);

				InitGame(UPDATA);				// �Q�[���̍ď���������
				SetStage(STAGE_TITLE);			// �X�e�[�W�ϐ��̏�����
				SetFade(FADE_OUT);				// ��ʑJ��:�Q�[��
			}

			// �~�{�^�����������獕���U���g���\��
			if (IsButtonTriggered(0, BUTTON_B))
			{

				// �J�[�\������SE�̍Đ�
				PlaySound(SE_PUSH, E_DS8_FLAG_NONE);

				// �|�C���^�̏�����
				RESULT *result = &resultWk[RESULT_BLACK_S];

				// �����U���g�ȉ���S�Ĕ�\����
				for (int i = RESULT_BLACK_S;i < RESULT_MAX;i++, result++)
				{
					result->use = false;			// ���\��

				}

				// ����ɖ߂�
				resultserect = FIRST;
			}

			// W�܂��́��X�e�B�b�N����������A�J�[�\���ړ�
			else if ((GetKeyboardTrigger(DIK_W)) || (IsButtonTriggered(0, BUTTON_UP)))
			{

				// �J�[�\���I��SE�̍Đ�
				PlaySound(SE_SERECT, E_DS8_FLAG_NONE);

				// �J�[�\������Ɉړ�
				resultcnt--;
			}

			// S�܂��́��X�e�B�b�N����������A�J�[�\���ړ�
			else if ((GetKeyboardTrigger(DIK_S)) || (IsButtonTriggered(0, BUTTON_DOWN)))
			{

				// �J�[�\���I��SE�̍Đ�
				PlaySound(SE_SERECT, E_DS8_FLAG_NONE);

				// �J�[�\�������Ɉړ�
				resultcnt++;
			}

			break;
		}

		// UI:"�����"�̏���
		case RESULT_UI_FINISH:
		{

			// UI�G�t�F�N�g:"�����"���g�p��
			resultC->use = true;

			// UI�G�t�F�N�g:"���Ȃ���"�𖢎g�p��
			resultS->use = false;

			// UI�G�t�F�N�g:"�����"�̐F�����F��
			resultc->vertex[0].diffuse = D3DCOLOR_RGBA(255, 0, 0, 255);
			resultc->vertex[1].diffuse = D3DCOLOR_RGBA(0, 0, 255, 255);
			resultc->vertex[2].diffuse = D3DCOLOR_RGBA(0, 0, 255, 255);
			resultc->vertex[3].diffuse = D3DCOLOR_RGBA(0, 0, 255, 255);

			// UI�G�t�F�N�g:"���Ȃ���"�̐F�����ɖ߂�
			results->vertex[0].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
			results->vertex[1].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
			results->vertex[2].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
			results->vertex[3].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);


			// Enter�܂��́Z�{�^������������A�X�e�[�W��؂�ւ���
			if ((GetKeyboardTrigger(DIK_RETURN)) || (IsButtonTriggered(0, BUTTON_C)))
			{

				// �J�[�\������SE�̍Đ�
				PlaySound(SE_PUSH, E_DS8_FLAG_NONE);

				InitGame(UPDATA);				// �Q�[���̍ď���������
				SetFade(FADE_OUT);				// ��ʑJ��:�^�C�g��

			}


				// �~�{�^�����������獕���U���g���\��
				if (IsButtonTriggered(0, BUTTON_B))
				{

					// �J�[�\������SE�̍Đ�
					PlaySound(SE_PUSH, E_DS8_FLAG_NONE);

					// �|�C���^�̏�����
					RESULT *result = &resultWk[RESULT_BLACK_S];

					// �����U���g�ȉ���S�Ĕ�\����
					for (int i = RESULT_BLACK_S;i < RESULT_MAX;i++, result++)
					{
						result->use = false;			// ���\��

					}

					// ����ɖ߂�
					resultserect = FIRST;
				}


				// W�܂��́��X�e�B�b�N����������A�J�[�\���ړ�
				else if ((GetKeyboardTrigger(DIK_W)) || (IsButtonTriggered(0, BUTTON_UP)))
				{

					// �J�[�\���I��SE�̍Đ�
					PlaySound(SE_SERECT, E_DS8_FLAG_NONE);

					// �J�[�\������Ɉړ�
					resultcnt--;
				}

				// S�܂��́��X�e�B�b�N����������A�J�[�\���ړ�
				else if ((GetKeyboardTrigger(DIK_S)) || (IsButtonTriggered(0, BUTTON_DOWN)))
				{


					// �J�[�\���I��SE�̍Đ�
					PlaySound(SE_SERECT, E_DS8_FLAG_NONE);

					// �J�[�\�������Ɉړ�
					resultcnt++;
				}

				break;

		}

		}
	}

	// �J�[�\�����[�v�ړ�����
	// UI:"���Ȃ���"�Ł����͎�
	if (resultcnt < RESULT_UI_INIT)
	{
		// UI:"�����"�Ɉړ�
		resultcnt = RESULT_UI_MAX - 1;
	}

	// UI:"�����"�Ł����͎�
	if (resultcnt > RESULT_UI_MAX - 1)
	{
		// UI:"���Ȃ���"�Ɉړ�
		resultcnt = RESULT_UI_INIT;
	}

}
//=============================================================================
// �`�揈���֐�
//=============================================================================
void DrawResult(void)
{
	// �|�C���^�̏�����
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	RESULT *result = &resultWk[0];

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	 // �\���̍ő吔�I������
	for (int i = 0; i < RESULT_MAX;i++, result++)
	{
		if (result->use == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, result->Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, result->vertex, sizeof(VERTEX_2D));
		}
	}

//#ifdef _DEBUG
//	// �f�o�b�O���b�Z�[�W�\��
//	DrawDebugProc();
//#endif

}

//=============================================================================
// ���_�̍쐬�֐�
//=============================================================================
HRESULT MakeVertexResult(int no)
{

	// �|�C���^�̏�����
	RESULT *result = &resultWk[no];

	// �w�i
	if ((no == RESULT_BASE)||(no == RESULT_BASE_LIGHT))
	{
		// ���_���W�̐ݒ�
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_BASE_SIZE_X, result->pos.y - RESULT_BASE_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_BASE_SIZE_X, result->pos.y - RESULT_BASE_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_BASE_SIZE_X, result->pos.y + RESULT_BASE_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_BASE_SIZE_X, result->pos.y + RESULT_BASE_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// �����t���O�v���C���[
	if (no == RESULT_BOAD_AI)
	{
		// ���_���W�̐ݒ�
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_BASE_SIZE_X, result->pos.y - RESULT_BASE_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_BASE_SIZE_X, result->pos.y - RESULT_BASE_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_BASE_SIZE_X, result->pos.y + RESULT_BASE_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_BASE_SIZE_X, result->pos.y + RESULT_BASE_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// �w�i
	if (no == RESULT_BOAD_VIRUS
		)
	{
		// ���_���W�̐ݒ�
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_BASE_SIZE_X, result->pos.y - RESULT_BASE_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_BASE_SIZE_X, result->pos.y - RESULT_BASE_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_BASE_SIZE_X, result->pos.y + RESULT_BASE_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_BASE_SIZE_X, result->pos.y + RESULT_BASE_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// �w�i
	if (no == RESULT_AI)
	{
		// ���_���W�̐ݒ�
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_AI_SIZE_X, result->pos.y - RESULT_AI_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_AI_SIZE_X, result->pos.y - RESULT_AI_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_AI_SIZE_X, result->pos.y + RESULT_AI_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_AI_SIZE_X, result->pos.y + RESULT_AI_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 120);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 120);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 120);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 120);

	}



	// �w�i
	if (no == RESULT_VIRUS)
	{
		// ���_���W�̐ݒ�
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_VIRUS_SIZE_X, result->pos.y - RESULT_VIRUS_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_VIRUS_SIZE_X, result->pos.y - RESULT_VIRUS_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_VIRUS_SIZE_X, result->pos.y + RESULT_VIRUS_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_VIRUS_SIZE_X, result->pos.y + RESULT_VIRUS_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 120);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 120);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 120);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 120);

	}

	// �]��
	else if ((no == RESULT_AI_RANK)||(no == RESULT_VIRUS_RANK))
	{
		// ���_���W�̐ݒ�
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_RANK_SIZE_X, result->pos.y - RESULT_RANK_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_RANK_SIZE_X, result->pos.y - RESULT_RANK_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_RANK_SIZE_X, result->pos.y + RESULT_RANK_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_RANK_SIZE_X, result->pos.y + RESULT_RANK_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 0, 0, 255);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(0, 0, 255, 255);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(0, 0, 255, 255);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(0, 0, 255, 255);

	}

	// �G�t�F�N�g:�]��
	else if ((no == RESULT_AI_RANK_EFFECT)||(no == RESULT_VIRUS_RANK_EFFECT))
	{
		// ���_���W�̐ݒ�
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_RANK_EFFECT_SIZE_X, result->pos.y - RESULT_RANK_EFFECT_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_RANK_EFFECT_SIZE_X, result->pos.y - RESULT_RANK_EFFECT_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_RANK_EFFECT_SIZE_X, result->pos.y + RESULT_RANK_EFFECT_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_RANK_EFFECT_SIZE_X, result->pos.y + RESULT_RANK_EFFECT_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 175, 0, 255);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 175, 0, 255);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 175, 0, 255);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 175, 0, 255);

	}

	// �����j���[
	else if (no == RESULT_BLACK_S)
	{
		// ���_���W�̐ݒ�
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_BLACK_S_SIZE_X, result->pos.y - RESULT_BLACK_S_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_BLACK_S_SIZE_X, result->pos.y - RESULT_BLACK_S_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_BLACK_S_SIZE_X, result->pos.y + RESULT_BLACK_S_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_BLACK_S_SIZE_X, result->pos.y + RESULT_BLACK_S_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}


	// UI:"���Ȃ���"
	else if (no == RESULT_INIT)
	{
		// ���_���W�̐ݒ�
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_INIT_SIZE_X, result->pos.y - RESULT_INIT_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_INIT_SIZE_X, result->pos.y - RESULT_INIT_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_INIT_SIZE_X, result->pos.y + RESULT_INIT_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_INIT_SIZE_X, result->pos.y + RESULT_INIT_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		result->vertex[0].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);

	}


	// UI�G�t�F�N�g:"���Ȃ���"
	else if (no == RESULT_INIT_EFFECT)
	{
		// ���_���W�̐ݒ�
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_ANY_EFFECT_SIZE_X, result->pos.y - RESULT_ANY_EFFECT_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_ANY_EFFECT_SIZE_X, result->pos.y - RESULT_ANY_EFFECT_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_ANY_EFFECT_SIZE_X, result->pos.y + RESULT_ANY_EFFECT_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_ANY_EFFECT_SIZE_X, result->pos.y + RESULT_ANY_EFFECT_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// UI:"�����"
	else if (no == RESULT_FINISH)
	{
		// ���_���W�̐ݒ�
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_FINISH_SIZE_X, result->pos.y - RESULT_FINISH_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_FINISH_SIZE_X, result->pos.y - RESULT_FINISH_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_FINISH_SIZE_X, result->pos.y + RESULT_FINISH_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_FINISH_SIZE_X, result->pos.y + RESULT_FINISH_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}

	// UI�G�t�F�N�g:"�����"
	else if (no == RESULT_FINISH_EFFECT)
	{
		// ���_���W�̐ݒ�
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_FINISH_EFFECT_SIZE_X, result->pos.y - RESULT_FINISH_EFFECT_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_FINISH_EFFECT_SIZE_X, result->pos.y - RESULT_FINISH_EFFECT_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_FINISH_EFFECT_SIZE_X, result->pos.y + RESULT_FINISH_EFFECT_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_FINISH_EFFECT_SIZE_X, result->pos.y + RESULT_FINISH_EFFECT_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}


	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	result->vertex[0].rhw =
	result->vertex[1].rhw =
	result->vertex[2].rhw =
	result->vertex[3].rhw = 1.0f;


	// �e�N�X�`�����W�̐ݒ�
	result->vertex[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	result->vertex[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	result->vertex[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	result->vertex[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}
//=============================================================================
// �G�t�F�N�g�֐�
//=============================================================================
void SetVertexResultEffect(int no)
{

	// �|�C���^�̏�����
	RESULT *result = &resultWk[no];


	//// �f�o�b�O�p�e�N�X�`���X�V
	//// �{�^���������Ă�:�G�t�F�N�g
	//if (no == RESULT_VIRUS)
	//{

	//	// ���_���W�̐ݒ�
	//	result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - sizex, result->pos.y - sizey, 0.0f);
	//	result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + sizex, result->pos.y - sizey, 0.0f);
	//	result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - sizex, result->pos.y + sizey, 0.0f);
	//	result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + sizex, result->pos.y + sizey, 0.0f);

	//}

	// �G�t�F�N�g:�]��
	if ((no == RESULT_BASE_LIGHT) || (no == RESULT_BOAD_AI) || (no == RESULT_BOAD_VIRUS))
	{

		// ���ˌ��̐ݒ�
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, resulteffectB);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, resulteffectB);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, resulteffectB);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, resulteffectB);

	}

	// �G�t�F�N�g:�]��
	if ((no == RESULT_AI_RANK)||(no == RESULT_VIRUS_RANK))
	{

		result->pos.x = rankpos;

		// ���_���W�̐ݒ�
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_RANK_SIZE_X, result->pos.y - RESULT_RANK_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_RANK_SIZE_X, result->pos.y - RESULT_RANK_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_RANK_SIZE_X, result->pos.y + RESULT_RANK_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_RANK_SIZE_X, result->pos.y + RESULT_RANK_SIZE_Y, 0.0f);

	}

	// �G�t�F�N�g:�]��
	if ((no == RESULT_AI_RANK_EFFECT)||(no == RESULT_VIRUS_RANK_EFFECT))
	{
		result->pos.x = rankpos;

		// ���_���W�̐ݒ�
		result->vertex[0].vtx = D3DXVECTOR3(result->pos.x - RESULT_RANK_EFFECT_SIZE_X, result->pos.y - RESULT_RANK_EFFECT_SIZE_Y, 0.0f);
		result->vertex[1].vtx = D3DXVECTOR3(result->pos.x + RESULT_RANK_EFFECT_SIZE_X, result->pos.y - RESULT_RANK_EFFECT_SIZE_Y, 0.0f);
		result->vertex[2].vtx = D3DXVECTOR3(result->pos.x - RESULT_RANK_EFFECT_SIZE_X, result->pos.y + RESULT_RANK_EFFECT_SIZE_Y, 0.0f);
		result->vertex[3].vtx = D3DXVECTOR3(result->pos.x + RESULT_RANK_EFFECT_SIZE_X, result->pos.y + RESULT_RANK_EFFECT_SIZE_Y, 0.0f);


		// ���ˌ��̐ݒ�
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 0, 0, resulteffect);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(0, 0, 255, resulteffect);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 0, 0, resulteffect);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(0, 0, 255, resulteffect);


	}

	// UI�G�t�F�N�g:"���Ȃ���"
	 if (no == RESULT_INIT_EFFECT)
	{

		// ���ˌ��̐ݒ�
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 0, 0, resulteffect);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(0, 0, 255, resulteffect);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 0, 0, resulteffect);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(0, 0, 255, resulteffect);

	}

	// UI�G�t�F�N�g:"�����"
	else if (no == RESULT_FINISH_EFFECT)
	{

		// ���ˌ��̐ݒ�
		result->vertex[0].diffuse = D3DCOLOR_RGBA(255, 0, 0, resulteffect);
		result->vertex[1].diffuse = D3DCOLOR_RGBA(0, 0, 255, resulteffect);
		result->vertex[2].diffuse = D3DCOLOR_RGBA(255, 0, 0, resulteffect);
		result->vertex[3].diffuse = D3DCOLOR_RGBA(0, 0, 255, resulteffect);

	}

}


//=============================================================================
// x�����t���O�擾�֐�
//=============================================================================
bool *GetWinFlag(void)
{
	return (&winflag);
}
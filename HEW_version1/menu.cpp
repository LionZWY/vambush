//=============================================================================
//
// �|�[�Y���j���[���� [menu.cpp]
// Author : ���ˌ��j��
// �v���O�����쐬�� : 2018/3/09
//
//=============================================================================

#include "menu.h"						// �\���́��}�N���g�p�̈�
#include "main.h"						// �}�N���g�p�̈�
#include "input.h"						// �֐��g�p�̈�
#include "game.h"						// �֐����}�N���g�p�̈�
#include "debugproc.h"					// �֐��g�p�̈�(�f�o�b�O�p)
#include "sound.h"						// �֐��g�p�̈�
#include "fade.h"						// �֐����}�N���g�p�̈�
#include "title.h"						// �}�N���g�p�̈�

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexMenu(int no);			// ���_�쐬�֐�
void SetVertexMenuEffect(int no);		// �G�t�F�N�g�֐�

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

MENU menuWk[MENU_MAX];					// ���j���[�\���̍ő吔�錾

bool menueffectflag;					// �G�t�F�N�g�p����ϐ�
int menueffect;							// �G�t�F�N�g�p�ϐ�
int menucnt;							// ��ʐ���ϐ�

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT InitMenu(int type)
{

	// �|�C���^�̏�����
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MENU *menu = &menuWk[0];

	// �G�t�F�N�g�֌W�̏�����
	menueffectflag = true;				// true:�v���X���� false:�}�C�i�X����
	menueffect= INIT_EFFECT;			// �G�t�F�N�g�̃��l�̏�����

	// ��ʐ���ϐ��̏�����
	menucnt = 0;

	// �\���̍ő吔����������
	for(int i = 0; i < MENU_MAX;i++, menu++)
	{

		// ���N����
		if (type == FIRST)
		{

			// �S��NULL�ŏ�����
			menu->Texture = NULL;

			// ���j���[�Ó]
			if (i == MENU_BASE)
			{
				// �ʒu�̐ݒ�
				menu->use = true;					// true:�g�p false:���g�p �g�p�ŏ�����
				menu->pos = MENU_BASE_POS;			// ���j���[�Ó]�̈ʒu�̏�����

			}

			// �����j���[
			else if (i == MENU_BLACK)
			{
				// �ʒu�̐ݒ�
				menu->use = true;					// true:�g�p false:���g�p �g�p�ŏ�����
				menu->pos = MENU_BLACK_POS;			// �����j���[�̈ʒu�̏�����


				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					MENU_BLACK_TEXTURE,				// �t�@�C���̖��O
					&menu->Texture);				// �ǂݍ��ރ������[

			}

			// UI:"�Â���"
			else if (i == MENU_ANY)
			{
				// �ʒu�̐ݒ�
				menu->use = true;					// true:�g�p false:���g�p �g�p�ŏ�����
				menu->pos = MENU_ANY_POS;			// UI:"�Â���",UI�G�t�F�N�g:"�Â���"�̈ʒu�̏�����

				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					MENU_ANY_TEXTURE,				// �t�@�C���̖��O
					&menu->Texture);				// �ǂݍ��ރ������[
			}

			// UI:"�Â���"
			else if (i == MENU_ANY_EFFECT)
			{
				// �ʒu�̐ݒ�
				menu->use = true;					// true:�g�p false:���g�p �g�p�ŏ�����
				menu->pos = MENU_ANY_POS;			// UI:"�Â���",UI�G�t�F�N�g:"�Â���"�̈ʒu�̏�����

													// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					MENU_ANY_TEXTURE,				// �t�@�C���̖��O
					&menu->Texture);				// �ǂݍ��ރ������[
			}

			// UI:"���Ȃ���"
			// UI�G�t�F�N�g:"���Ȃ���"
			else if (i == MENU_INIT)
			{
				// �ʒu�̐ݒ�
				menu->use = true;					// true:�g�p false:���g�p �g�p�ŏ�����
				menu->pos = MENU_INIT_POS;			// UI:"���Ȃ���"�̈ʒu�̏�����

				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					MENU_INIT_TEXTURE,				// �t�@�C���̖��O
					&menu->Texture);				// �ǂݍ��ރ������[
			}

			// UI�G�t�F�N�g:"���Ȃ���"
			else if (i == MENU_INIT_EFFECT)
			{
				// �ʒu�̐ݒ�
				menu->use = false;					// true:�g�p false:���g�p �g�p�ŏ�����
				menu->pos = MENU_INIT_POS;			// UI:"���Ȃ���"�̈ʒu�̏�����

				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					MENU_INIT_TEXTURE,				// �t�@�C���̖��O
					&menu->Texture);				// �ǂݍ��ރ������[
			}


			// UI:"�����"
			else if (i == MENU_FINISH) 
			{
				// �ʒu�̐ݒ�
				menu->use = true;					// true:�g�p false:���g�p �g�p�ŏ�����
				menu->pos = MENU_FINISH_POS;		// ���j���[�Ó]�̈ʒu�̏�����

				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					MENU_FINISH_TEXTURE,			// �t�@�C���̖��O
					&menu->Texture);				// �ǂݍ��ރ������[
			}

			// UI�G�t�F�N�g:"�����"
			else if (i == MENU_FINISH_EFFECT)
			{
				// �ʒu�̐ݒ�
				menu->use = false;					// true:�g�p false:���g�p �g�p�ŏ�����
				menu->pos = MENU_FINISH_POS;		// ���j���[�Ó]�̈ʒu�̏�����

				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					MENU_FINISH_TEXTURE,			// �t�@�C���̖��O
					&menu->Texture);				// �ǂݍ��ރ������[
			}

		}

		// ���_���̍쐬
		MakeVertexMenu(i);
	}

	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void UninitMenu(void)
{
	// �|�C���^�̏�����
	MENU *menu = &menuWk[0];

	// �\���̍ő吔�I������
	for (int i = 0; i < MENU_MAX;i++, menu++)
	{

		// �e�N�X�`���̊J���o���Ă��Ȃ�������
		if (menu->Texture != NULL)
		{

			// �e�N�X�`���̊J��
			menu->Texture->Release();
			menu->Texture = NULL;
		}
	}

}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void UpdateMenu(void)
{

	// �|�C���^�̏�����
	MENU *menu = &menuWk[0];

	// ���݂̃��j���[�t���O���m�F
	bool *flag = GetMenu();

	// �G�t�F�N�g����
	// �v���X�t���O
	if (menueffectflag==true)
	{

		// �G�t�F�N�g���l��EFFECT_MENU_SPEED�𑫂�
		menueffect += EFFECT_MENU_SPEED;

		// �G�t�F�N�g���l���ő�
		if (menueffect == ALPHA_MAX)
		{
			// �t���O���}�C�i�X��
			menueffectflag = false;
		}
	}

	// �}�C�i�X�t���O
	else if (menueffectflag == false)
	{
		// �G�t�F�N�g���l��EFFECT_MENU_SPEED������
		menueffect-= EFFECT_MENU_SPEED;

		// �G�t�F�N�g���l���ŏ�
		if (menueffect == ALPHA_BASE)
		{
			// �t���O���v���X�ɂ�
			menueffectflag = true;
		}

	}


	// �\���̍ő吔�X�V����
	for (int i = 0; i < MENU_MAX;i++, menu++)
	{

		// �G�t�F�N�g����
		SetVertexMenuEffect(i);

	}

	MENU *menuAny = &menuWk[MENU_ANY];
	MENU *menuAnyef = &menuWk[MENU_ANY_EFFECT];
	MENU *menuInit = &menuWk[MENU_INIT];
	MENU *menuInitef = &menuWk[MENU_INIT_EFFECT];
	MENU *menuFin = &menuWk[MENU_FINISH];
	MENU *menuFinef = &menuWk[MENU_FINISH_EFFECT];


	// �Z���N�g���j���[�̕\����
	switch (menucnt)
	{
	// UI:"�Â���"�̏���
	case MENU_UI_ANY:
	{
		// UI:"�Â���"���g�p��
		menuAnyef->use = true;

		// UI:"���Ȃ���"�𖢎g�p��
		menuInitef->use = false;

		// UI:"�����"�𖢎g�p��
		menuFinef->use = false;

		// UI:"�Â���"�̐F�����F��
		menuAny->vertex[0].diffuse = D3DCOLOR_RGBA(255, 0, 0, 255);
		menuAny->vertex[1].diffuse = D3DCOLOR_RGBA(0, 0, 255, 255);
		menuAny->vertex[2].diffuse = D3DCOLOR_RGBA(0, 0, 255, 255);
		menuAny->vertex[3].diffuse = D3DCOLOR_RGBA(0, 0, 255, 255);

		// UI:"���Ȃ���"�̐F�����ɖ߂�
		menuInit->vertex[0].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		menuInit->vertex[1].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		menuInit->vertex[2].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		menuInit->vertex[3].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);

		// UI:"�����"�̐F�����ɖ߂�
		menuFin->vertex[0].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		menuFin->vertex[1].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		menuFin->vertex[2].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		menuFin->vertex[3].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);


		// Enter�܂��́~�{�^������������A���j���[�����
		if ((GetKeyboardTrigger(DIK_RETURN)) || (IsButtonTriggered(0, BUTTON_C)))
		{

			// �J�[�\������SE�̍Đ�
			PlaySound(SE_PUSH, E_DS8_FLAG_NONE);

			// ���j���[�����
			*flag = false;
		}

		// W�܂��́��X�e�B�b�N����������A�J�[�\���ړ�
		else if ((GetKeyboardTrigger(DIK_W)) || (IsButtonTriggered(0, BUTTON_UP)))
		{

			// �J�[�\���I��SE�̍Đ�
			PlaySound(SE_SERECT, E_DS8_FLAG_NONE);

			// �J�[�\������Ɉړ�
			menucnt--;
		}

		// S�܂��́��X�e�B�b�N����������A�J�[�\���ړ�
		else if ((GetKeyboardTrigger(DIK_S)) || (IsButtonTriggered(0, BUTTON_DOWN)))
		{

			// �J�[�\���I��SE�̍Đ�
			PlaySound(SE_SERECT, E_DS8_FLAG_NONE);

			// �J�[�\�������Ɉړ�
			menucnt++;
		}

		break;
	}

	// UI:"���Ȃ���"�̏���
	case MENU_UI_INIT:
	{
		// UI:"���Ȃ���"���g�p��
		menuInitef->use = true;

		// UI:"�Â���𖢎g�p��
		menuAnyef->use = false;

		// UI:"�����"�𖢎g�p��
		menuFinef->use = false;

		// UI:"���Ȃ���"�̐F�����F��
		menuInit->vertex[0].diffuse = D3DCOLOR_RGBA(255, 0, 0, 255);
		menuInit->vertex[1].diffuse = D3DCOLOR_RGBA(0, 0, 255, 255);
		menuInit->vertex[2].diffuse = D3DCOLOR_RGBA(0, 0, 255, 255);
		menuInit->vertex[3].diffuse = D3DCOLOR_RGBA(0, 0, 255, 255);

		// UI:"�Â���"�̐F�����ɖ߂�
		menuAny->vertex[0].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		menuAny->vertex[1].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		menuAny->vertex[2].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		menuAny->vertex[3].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);

		// UI:"�����"�̐F�����ɖ߂�
		menuFin->vertex[0].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		menuFin->vertex[1].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		menuFin->vertex[2].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		menuFin->vertex[3].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);

		// Enter�܂��́~�{�^������������A�Q�[����������
		if ((GetKeyboardTrigger(DIK_RETURN)) || (IsButtonTriggered(0, BUTTON_C)))
		{

			// �J�[�\������SE�̍Đ�
			PlaySound(SE_PUSH, E_DS8_FLAG_NONE);

			InitGame(UPDATA);				// �Q�[���̍ď���������
			SetStage(STAGE_TITLE);			// �X�e�[�W�ϐ��̏�����
			SetFade(FADE_OUT);				// ��ʑJ��:�Q�[��
		}

		// W�܂��́��X�e�B�b�N����������A�J�[�\���ړ�
		else if ((GetKeyboardTrigger(DIK_W)) || (IsButtonTriggered(0, BUTTON_UP)))
		{

			// �J�[�\���I��SE�̍Đ�
			PlaySound(SE_SERECT, E_DS8_FLAG_NONE);

			// �J�[�\������Ɉړ�
			menucnt--;
		}

		// S�܂��́��X�e�B�b�N����������A�J�[�\���ړ�
		else if ((GetKeyboardTrigger(DIK_S)) || (IsButtonTriggered(0, BUTTON_DOWN)))
		{

			// �J�[�\���I��SE�̍Đ�
			PlaySound(SE_SERECT, E_DS8_FLAG_NONE);

			// �J�[�\�������Ɉړ�
			menucnt++;
		}

		break;
	}

	// UI:"�����"�̏���
	case MENU_UI_FINISH:
	{

		// UI:"�����"���g�p��
		menuFinef->use = true;

		// UI:"���Ȃ���"�𖢎g�p��
		menuInitef->use = false;

		// UI:"�Â���"�𖢎g�p��
		menuAnyef->use = false;


		// UI:"�����"�̐F�����F��
		menuFin->vertex[0].diffuse = D3DCOLOR_RGBA(255, 0, 0, 255);
		menuFin->vertex[1].diffuse = D3DCOLOR_RGBA(0, 0, 255, 255);
		menuFin->vertex[2].diffuse = D3DCOLOR_RGBA(0, 0, 255, 255);
		menuFin->vertex[3].diffuse = D3DCOLOR_RGBA(0, 0, 255, 255);

		// UI:"���Ȃ���"�̐F�����ɖ߂�
		menuInit->vertex[0].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		menuInit->vertex[1].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		menuInit->vertex[2].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		menuInit->vertex[3].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);

		// UI:"�Â���"�̐F�����ɖ߂�
		menuAny->vertex[0].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		menuAny->vertex[1].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		menuAny->vertex[2].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		menuAny->vertex[3].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);

		// Enter��������A�X�e�[�W��؂�ւ���
		if ((GetKeyboardTrigger(DIK_RETURN)) || (IsButtonTriggered(0, BUTTON_C)))
		{
			// �J�[�\������SE�̍Đ�
			PlaySound(SE_PUSH, E_DS8_FLAG_NONE);
			InitGame(UPDATA);				// �Q�[���̍ď���������
			SetStage(STAGE_RESULT);			// �X�e�[�W�ϐ��̃��U���g�̑O�ɃZ�b�g
			SetFade(FADE_OUT);					// ��ʑJ��:���U���g

		}

		// W�܂��́��X�e�B�b�N����������A�J�[�\���ړ�
		else if ((GetKeyboardTrigger(DIK_W)) || (IsButtonTriggered(0, BUTTON_UP)))
		{

			// �J�[�\���I��SE�̍Đ�
			PlaySound(SE_SERECT, E_DS8_FLAG_NONE);

			// �J�[�\������Ɉړ�
			menucnt--;
		}

		// S�܂��́��X�e�B�b�N����������A�J�[�\���ړ�
		else if ((GetKeyboardTrigger(DIK_S)) || (IsButtonTriggered(0, BUTTON_DOWN)))
		{

			// �J�[�\���I��SE�̍Đ�
			PlaySound(SE_SERECT, E_DS8_FLAG_NONE);

			// �J�[�\�������Ɉړ�
			menucnt++;
		}

		break;
	}
	}

	// �J�[�\�����[�v�ړ�����
	// UI:"�Â���"�Ł����͎�
	if (menucnt < MENU_UI_ANY)
	{
		// UI:"�����"�Ɉړ�
		menucnt = MENU_UI_MAX - 1;
	}

	// UI:"�����"�Ł����͎�
	if (menucnt > MENU_UI_MAX - 1)
	{
		// UI:"�Â���""�Ɉړ�
		menucnt = MENU_UI_ANY;
	}

}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void DrawMenu(void)
{
	// �|�C���^�̏�����
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MENU *menu = &menuWk[0];
	
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);


	// �\���̍ő吔�I������
	for (int i = 0; i < MENU_MAX;i++, menu++)
	{

		// �g�p��ԂȂ�`�悷��
		if (menu->use == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, menu->Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, menu->vertex, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬�֐�
//=============================================================================
HRESULT MakeVertexMenu(int no)
{
	
	// �|�C���^�̏�����
	MENU *menu = &menuWk[no];

	// ���j���[�Ó]
	if (no==MENU_BASE)
	{
		// ���_���W�̐ݒ�
		menu->vertex[0].vtx = D3DXVECTOR3(menu->pos.x - MENU_BASE_SIZE_X, menu->pos.y - MENU_BASE_SIZE_Y, 0.0f);
		menu->vertex[1].vtx = D3DXVECTOR3(menu->pos.x + MENU_BASE_SIZE_X, menu->pos.y - MENU_BASE_SIZE_Y, 0.0f);
		menu->vertex[2].vtx = D3DXVECTOR3(menu->pos.x - MENU_BASE_SIZE_X, menu->pos.y + MENU_BASE_SIZE_Y, 0.0f);
		menu->vertex[3].vtx = D3DXVECTOR3(menu->pos.x + MENU_BASE_SIZE_X, menu->pos.y + MENU_BASE_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		menu->vertex[0].diffuse = D3DCOLOR_RGBA(0, 0, 0, 150);
		menu->vertex[1].diffuse = D3DCOLOR_RGBA(0, 0, 0, 150);
		menu->vertex[2].diffuse = D3DCOLOR_RGBA(0, 0, 0, 150);
		menu->vertex[3].diffuse = D3DCOLOR_RGBA(0, 0, 0, 150);

	}

	// �����j���[
	if (no == MENU_BLACK)
	{
		// ���_���W�̐ݒ�
		menu->vertex[0].vtx = D3DXVECTOR3(menu->pos.x - MENU_BLACK_SIZE_X, menu->pos.y - MENU_BLACK_SIZE_Y, 0.0f);
		menu->vertex[1].vtx = D3DXVECTOR3(menu->pos.x + MENU_BLACK_SIZE_X, menu->pos.y - MENU_BLACK_SIZE_Y, 0.0f);
		menu->vertex[2].vtx = D3DXVECTOR3(menu->pos.x - MENU_BLACK_SIZE_X, menu->pos.y + MENU_BLACK_SIZE_Y, 0.0f);
		menu->vertex[3].vtx = D3DXVECTOR3(menu->pos.x + MENU_BLACK_SIZE_X, menu->pos.y + MENU_BLACK_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		menu->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		menu->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		menu->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		menu->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}


	// UI:"�Â���"
	else if (no == MENU_ANY)
	{
		// ���_���W�̐ݒ�
		menu->vertex[0].vtx = D3DXVECTOR3(menu->pos.x - MENU_ANY_SIZE_X, menu->pos.y - MENU_ANY_SIZE_Y, 0.0f);
		menu->vertex[1].vtx = D3DXVECTOR3(menu->pos.x + MENU_ANY_SIZE_X, menu->pos.y - MENU_ANY_SIZE_Y, 0.0f);
		menu->vertex[2].vtx = D3DXVECTOR3(menu->pos.x - MENU_ANY_SIZE_X, menu->pos.y + MENU_ANY_SIZE_Y, 0.0f);
		menu->vertex[3].vtx = D3DXVECTOR3(menu->pos.x + MENU_ANY_SIZE_X, menu->pos.y + MENU_ANY_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		menu->vertex[0].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		menu->vertex[1].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		menu->vertex[2].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		menu->vertex[3].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);

	}


	// UI�G�t�F�N�g:"�Â���"
	else if (no == MENU_ANY_EFFECT)
	{
		// ���_���W�̐ݒ�
		menu->vertex[0].vtx = D3DXVECTOR3(menu->pos.x - MENU_ANY_EFFECT_SIZE_X, menu->pos.y - MENU_ANY_EFFECT_SIZE_Y, 0.0f);
		menu->vertex[1].vtx = D3DXVECTOR3(menu->pos.x + MENU_ANY_EFFECT_SIZE_X, menu->pos.y - MENU_ANY_EFFECT_SIZE_Y, 0.0f);
		menu->vertex[2].vtx = D3DXVECTOR3(menu->pos.x - MENU_ANY_EFFECT_SIZE_X, menu->pos.y + MENU_ANY_EFFECT_SIZE_Y, 0.0f);
		menu->vertex[3].vtx = D3DXVECTOR3(menu->pos.x + MENU_ANY_EFFECT_SIZE_X, menu->pos.y + MENU_ANY_EFFECT_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		menu->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, menueffect);
		menu->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, menueffect);
		menu->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, menueffect);
		menu->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, menueffect);

	}


	// UI:"���Ȃ���"
	else if (no == MENU_INIT)
	{
		// ���_���W�̐ݒ�
		menu->vertex[0].vtx = D3DXVECTOR3(menu->pos.x - MENU_INIT_SIZE_X, menu->pos.y - MENU_INIT_SIZE_Y, 0.0f);
		menu->vertex[1].vtx = D3DXVECTOR3(menu->pos.x + MENU_INIT_SIZE_X, menu->pos.y - MENU_INIT_SIZE_Y, 0.0f);
		menu->vertex[2].vtx = D3DXVECTOR3(menu->pos.x - MENU_INIT_SIZE_X, menu->pos.y + MENU_INIT_SIZE_Y, 0.0f);
		menu->vertex[3].vtx = D3DXVECTOR3(menu->pos.x + MENU_INIT_SIZE_X, menu->pos.y + MENU_INIT_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		menu->vertex[0].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		menu->vertex[1].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		menu->vertex[2].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		menu->vertex[3].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);

	}


	// UI�G�t�F�N�g:"���Ȃ���"
	else if (no == MENU_INIT_EFFECT)
	{
		// ���_���W�̐ݒ�
		menu->vertex[0].vtx = D3DXVECTOR3(menu->pos.x - MENU_INIT_EFFECT_SIZE_X, menu->pos.y - MENU_INIT_EFFECT_SIZE_Y, 0.0f);
		menu->vertex[1].vtx = D3DXVECTOR3(menu->pos.x + MENU_INIT_EFFECT_SIZE_X, menu->pos.y - MENU_INIT_EFFECT_SIZE_Y, 0.0f);
		menu->vertex[2].vtx = D3DXVECTOR3(menu->pos.x - MENU_INIT_EFFECT_SIZE_X, menu->pos.y + MENU_INIT_EFFECT_SIZE_Y, 0.0f);
		menu->vertex[3].vtx = D3DXVECTOR3(menu->pos.x + MENU_INIT_EFFECT_SIZE_X, menu->pos.y + MENU_INIT_EFFECT_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		menu->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, menueffect);
		menu->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, menueffect);
		menu->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, menueffect);
		menu->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, menueffect);

	}

	// UI:"�����"
	else if (no == MENU_FINISH)
	{
		// ���_���W�̐ݒ�
		menu->vertex[0].vtx = D3DXVECTOR3(menu->pos.x - MENU_FINISH_SIZE_X, menu->pos.y - MENU_FINISH_SIZE_Y, 0.0f);
		menu->vertex[1].vtx = D3DXVECTOR3(menu->pos.x + MENU_FINISH_SIZE_X, menu->pos.y - MENU_FINISH_SIZE_Y, 0.0f);
		menu->vertex[2].vtx = D3DXVECTOR3(menu->pos.x - MENU_FINISH_SIZE_X, menu->pos.y + MENU_FINISH_SIZE_Y, 0.0f);
		menu->vertex[3].vtx = D3DXVECTOR3(menu->pos.x + MENU_FINISH_SIZE_X, menu->pos.y + MENU_FINISH_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		menu->vertex[0].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		menu->vertex[1].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		menu->vertex[2].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);
		menu->vertex[3].diffuse = D3DCOLOR_RGBA(150, 150, 150, 255);

	}


	// UI�G�t�F�N�g:"�����"
	else if (no == MENU_FINISH_EFFECT)
	{
		// ���_���W�̐ݒ�
		menu->vertex[0].vtx = D3DXVECTOR3(menu->pos.x - MENU_FINISH_EFFECT_SIZE_X, menu->pos.y - MENU_FINISH_EFFECT_SIZE_Y, 0.0f);
		menu->vertex[1].vtx = D3DXVECTOR3(menu->pos.x + MENU_FINISH_EFFECT_SIZE_X, menu->pos.y - MENU_FINISH_EFFECT_SIZE_Y, 0.0f);
		menu->vertex[2].vtx = D3DXVECTOR3(menu->pos.x - MENU_FINISH_EFFECT_SIZE_X, menu->pos.y + MENU_FINISH_EFFECT_SIZE_Y, 0.0f);
		menu->vertex[3].vtx = D3DXVECTOR3(menu->pos.x + MENU_FINISH_EFFECT_SIZE_X, menu->pos.y + MENU_FINISH_EFFECT_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		menu->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, menueffect);
		menu->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, menueffect);
		menu->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, menueffect);
		menu->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, menueffect);

	}

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	menu->vertex[0].rhw =
	menu->vertex[1].rhw =
	menu->vertex[2].rhw =
	menu->vertex[3].rhw = 1.0f;


	// �e�N�X�`�����W�̐ݒ�
	menu->vertex[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	menu->vertex[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	menu->vertex[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	menu->vertex[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// �G�t�F�N�g�֐�
//=============================================================================
void SetVertexMenuEffect(int no)
{

	// �|�C���^�̏�����
	MENU *menu = &menuWk[no];

	// UI�G�t�F�N�g:"�Â���"
	 if (no == MENU_ANY_EFFECT)
	{

		// ���ˌ��̐ݒ�
		menu->vertex[0].diffuse = D3DCOLOR_RGBA(255, 0, 0, menueffect);
		menu->vertex[1].diffuse = D3DCOLOR_RGBA(0, 0, 255, menueffect);
		menu->vertex[2].diffuse = D3DCOLOR_RGBA(255, 0, 0, menueffect);
		menu->vertex[3].diffuse = D3DCOLOR_RGBA(0, 0, 255, menueffect);

	}

	 // UI�G�t�F�N�g:"���Ȃ���"
	 if (no == MENU_INIT_EFFECT)
	 {

		 // ���ˌ��̐ݒ�
		 menu->vertex[0].diffuse = D3DCOLOR_RGBA(255, 0, 0, menueffect);
		 menu->vertex[1].diffuse = D3DCOLOR_RGBA(0, 0, 255, menueffect);
		 menu->vertex[2].diffuse = D3DCOLOR_RGBA(255, 0, 0, menueffect);
		 menu->vertex[3].diffuse = D3DCOLOR_RGBA(0, 0, 255, menueffect);

	 }


	 // UI�G�t�F�N�g:"�����"
	 if (no == MENU_FINISH_EFFECT)
	 {

		 // ���ˌ��̐ݒ�
		menu->vertex[0].diffuse = D3DCOLOR_RGBA(255, 0, 0, menueffect);
		menu->vertex[1].diffuse = D3DCOLOR_RGBA(0, 0, 255, menueffect);
		menu->vertex[2].diffuse = D3DCOLOR_RGBA(255, 0, 0, menueffect);
		menu->vertex[3].diffuse = D3DCOLOR_RGBA(0, 0, 255, menueffect);


	 }

}

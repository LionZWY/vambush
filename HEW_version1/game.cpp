//=============================================================================
//
// �Q�[����ʏ��� [game.cpp]
// Author : ���ˌ��j��
// �v���O�����쐬�� : 2018/3/09
//
//=============================================================================

#include "game.h"				// �}�N���g�p�̈�
#include "input.h"				// �֐��g�p�̈�
#include "light.h"				// ����
#include "camera.h"				// ����
#include "field.h"				// ����
#include "shadow.h"				// ����
#include "player.h"				// ����
#include "player_gun.h"			// ����
#include "player_cursor.h"		// ����
#include "player_bullet.h"		// ����
#include "player_skillNor.h"	// ����
#include "player_skillDef.h"	// ����
#include "player_skillSup.h"	// ����
#include "enemy.h"				// ����
#include "enemy_gun.h"			// ����
#include "enemy_cursor.h"		// ����
#include "enemy_bullet.h"		// ����
#include "enemy_skillNor.h"		// ����
#include "enemy_skillDef.h"		// ����
#include "enemy_skillSup.h"		// ����
#include "effect.h"				// ����
#include "noize.h"				// ����
#include "checkhit.h"			// ����
#include "ui.h"					// ����
#include "timer.h"				// ����
#include "debugproc.h"			// ����
#include "sound.h"				// ����
#include "fade.h"				// ����
#include "call.h"				// ����
#include "title.h"				// ����
#include "menu.h"				// ����
#include "result.h"				// ����

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************

bool menuflag;						// �|�[�Y���j���[����ϐ�

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT InitGame(int type)
{
	
	// �|�[�Y�t���O�̏�����(false:���g�p)
	menuflag = false;

	// ���C�g�̏���������
	InitLight();

	// �J�����̏���������
	InitCamera();

	// �n�ʂ̏�����
	InitField(type);
		
	// shadow�̏���������
	InitShadow();

	// �v���C���[�̏���������
	InitPlayer();

	// �v���C���[�K���̏���������
	InitPlayerGun();

	// �G�l�~�[�̏���������
	InitEnemy();

	// �G�l�~�[�K���̏���������
	InitEnemyGun();

	// �v���C���[�J�[�\���̏���������
	InitCursorPlayer();

	// �G�l�~�[�J�[�\���̏���������
	InitCursorEnemy();

	// �e�̏���������
	InitPlayerBullet();
	InitEnemyBullet();

	// �e(���[��)�̏���������
	InitPlayerNorSkill();
	InitEnemyNorSkill();

	// �e(�J�X�P�[�h)�̏���������
	InitPlayerSkillDef();
	InitEnemySkillDef();

	// �e(�X�y�V����)�̏���������
	InitPlayerSupSkill();
	InitEnemySupSkill();

	// �G�t�F�N�g�̏���������
	InitEffect();

	// �q�b�g�G�t�F�N�g�̏���������
	InitNoize();

	// UI�̏���������
	InitUi(type);

	// �^�C�}�[����������
	InitTimer(type);

	// �f�o�b�O���b�Z�[�W�̏���������
	InitDebugProc();

	// �t�F�[�h�̏���������
	InitFade();

	// �R�[���̏���������
	InitCall(type);

	// �^�C�g���̏���������
	InitTitle(type);

	// ���j���[�̏���������
	InitMenu(type);

	// ���U���g�̏���������
	InitResult(type);

	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void UninitGame(void)
{

	// ���͂̏I������
	UninitInput();

	// ���C�g�̏I������
	UninitLight();

	// �J�����̏I������
	UninitCamera();

	// �n�ʂ̏I������
	UninitField();

	// shadow�̏I������
	UninitShadow();

	// �v���C���[�̏I������
	UninitPlayer();

	// �v���C���[�K���̏I������
	UninitPlayerGun();

	// �G�l�~�[�̏I������
	UninitEnemy();

	// �G�l�~�[�K���̏I������
	UninitEnemyGun();

	// �v���C���[�J�[�\���̏I������
	UninitCursorPlayer();

	// �G�l�~�[�J�[�\���̏I������
	UninitCursorEnemy();

	// �e�̏I������
	UninitPlayerBullet();
	UninitEnemyBullet();

	// �e(���[��)�̏I������
	UninitPlayerNorSkill();
	UninitEnemyNorSkill();

	// �e(�J�X�P�[�h)�̏I������
	UninitPlayerSkillDef();
	UninitEnemySkillDef();

	// �e(�X�y�V����)�̏I������
	UninitPlayerSupSkill();
	UninitEnemySupSkill();

	// �G�t�F�N�g�̏I������
	UninitEffect();

	// �q�b�g�G�t�F�N�g�̏I������
	UninitNoize();

	// UI�̏I������
	UninitUi();

	// �^�C�}�[�̏I������
	UninitTimer();

	// �f�o�b�O���b�Z�[�W�̏I������
	UninitDebugProc();

	// �T�E���h�̏I������
	UninitSound();

	// �t�F�[�h�̏I������
	UninitFade();

	// �R�[���̏I������
	UninitCall();

	// �^�C�g���̏I������
	UninitTitle();

	// ���j���[�̏I������
	UninitMenu();

	// ���U���g�̏I������
	UninitResult();
	
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void UpdateGame(void)
{


	bool *start = GetStartFlag();

	if (*start == false)
	{

		// ���C�g�̍X�V����
		UpdateLight();

		// �J�����̍X�V����
		UpdateCamera();

		// �n�`�̍X�V����
		UpdateField();

		// shadow�̍X�V����
		UpdateShadow();

		UpdateCall();

		// UI�̍X�V����
		UpdateUi();

	}

	else if(*start == true)
	{

		// G����������|�[�Y
		if ((GetKeyboardPress(DIK_G)) || (IsButtonTriggered(0, BUTTON_START)))
		{
			menuflag = true;				// �|�[�Y�̃t���O���g�p��
		}



		// �Q�[����
		if (menuflag == false)
		{

			// ���C�g�̍X�V����
			UpdateLight();

			// �J�����̍X�V����
			UpdateCamera();

			// �n�`�̍X�V����
			UpdateField();

			// shadow�̍X�V����
			UpdateShadow();

			// �v���C���[�̍X�V����
			UpdatePlayer();

			// �v���C���[�K���̍X�V����
			UpdatePlayerGun();

			//�@�G�l�~�[�̍X�V����
			UpdateEnemy();

			// �G�l�~�[�K���̍X�V����
			UpdateEnemyGun();

			// �v���C���[�J�[�\���̍X�V����
			UpdateCursorPlayer();

			// �G�l�~�[�J�[�\���̍X�V����
			UpdateCursorEnemy();

			// �e�̍X�V����
			UpdatePlayerBullet();
			UpdateEnemyBullet();

			// �e(���[��)�̍X�V����
			UpdatePlayerNorSkill();
			UpdateEnemyNorSkill();

			// �e(�J�X�P�[�h)�̍X�V����
			UpdatePlayerSkillDef();
			UpdateEnemySkillDef();

			// �e(�X�y�V����)�̍X�V����
			UpdatePlayerSupSkill();
			UpdateEnemySupSkill();

			// �G�t�F�N�g�̍X�V����
			UpdateEffect();

			// �q�b�g�G�t�F�N�g�̍X�V����
			UpdateNoize();

			// UI�̍X�V����
			UpdateUi();

			// �^�C�}�[�̍X�V����
			UpdateTimer();

			// �����蔻�菈��
			CheckHitPaE();

		}

		// �|�[�Y���j���[��
		else if (menuflag == true)
		{
			// �|�[�Y���j���[�̍X�V����
			UpdateMenu();
		}
	}
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void DrawGame(void)
{

	// �J�����̐ݒ菈��
	SetCamera();

	// �n�`�̕`�揈��
	DrawField();

	// shadow�̕`�揈��
	DrawShadow();

	// �v���C���[�̕`�揈��
	DrawPlayer();

	// �v���C���[�K���̕`�揈��
	DrawPlayerGun();

	// �G�l�~�[�̕`�揈��
	DrawEnemy();

	// �G�l�~�[�K���̕`�揈��
	DrawEnemyGun();

	// �v���C���[�J�[�\���̕`�揈��
	DrawCursorPlayer();

	// �G�l�~�[�J�[�\���̕`�揈��
	DrawCursorEnemy();

	// �e�̕`�揈��
	DrawPlayerBullet();
	DrawEnemyBullet();

	// �e(���[��)�̕`�揈��
	DrawPlayerNorSkill();
	DrawEnemyNorSkill();

	// �e(�J�X�P�[�h)�̕`�揈��
	DrawPlayerSkillDef();
	DrawEnemySkillDef();

	// �e(�X�y�V����)�̕`�揈��
	DrawPlayerSupSkill();
	DrawEnemySupSkill();

	// �G�t�F�N�g�̕`�揈��
	DrawEffect();

	// �q�b�g�G�t�F�N�g�̕`�揈��
	DrawNoize();

	// UI�̕`��
	DrawUi();

	// �^�C�}�[�̕`��
	DrawTimer();

	// �R�[���̕`�揈��
	DrawCall();

	// �|�[�Y���j���[��
	if (menuflag == true)
	{
		// ���j���[�̕`�揈��
		DrawMenu();
	}


//#ifdef _DEBUG
//	// �f�o�b�O���b�Z�[�W�\��
//	DrawDebugProc();
//#endif
}

//=============================================================================
// �|�[�Y�t���O�擾�֐�
//=============================================================================
bool *GetMenu(void)
{
	return(&menuflag);
}

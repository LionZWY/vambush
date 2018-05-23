//=============================================================================
//
// �^�C�}�[���� [timer.h]
// Author : ���ˌ��j��
// �v���O�����쐬�� : 2018/3/09
//
//=============================================================================

// ���d�C���N���[�h�h�~�̈�
#ifndef _TIMER_H_
#define _TIMER_H_

// ���C�u���C���}�N���̎g�p�̈�
#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

#define FRAME_CNT			(60)								// ��b�̃t���[����
#define DECIMAL_TEN			(10.0f)								// �P�O�i���̊
#define BASE_HUNDRED		(100)								// �P�O�O
#define BASE_TEN			(10)								// �P�O
#define TIME_DRAW_MAX		(999)								// �\���ő吔

#define	NUM_PLACE			(3)									// �^�C�}�[�̌���

#define	TEXTURE_TIMER		"data/TEXTURE/deg_number3.png"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TIMER_SIZE_X		(60.0f)								// �^�C�}�[�̐����̕�
#define	TIMER_SIZE_Y		(95.0f)								// �^�C�}�[�̐����̍���
#define	TIMER_INTERVAL_X	(0.0f)								// �^�C�}�[�̐����̕\���Ԋu

#define	TIMER_BASE_POS		D3DXVECTOR3(0.0f, 0.0f, 0.0f)		// �^�C�}�[�̊�{�ʒu
#define	TIMER_POS_X			(SCREEN_WIDTH/2 - ((TIMER_SIZE_X * NUM_PLACE + TIMER_INTERVAL_X * (NUM_PLACE - 1)) / 2) )	// �^�C�}�[�̕\����ʒu�w���W
#define	TIMER_POS_Y			(12.0f)																						// �^�C�}�[�̕\����ʒu�x���W

#define TIMER_MAX			(180)								// �^�C�}�[�̃X�^�[�g�̒l

#define	KILL_SIZE_X			(60.0f)								// �K�E�Z�Q�[�W�̐����̕�
#define	KILL_SIZE_Y			(90.0f)								// �K�E�Z�Q�[�W�̐����̍���

#define	TIMER_PLAYER_POS	D3DXVECTOR3(80.0f, 620.0f, 0.0f)		// �K�E�Z�Q�[�W�v���C���[�̊�{�ʒu
#define	NUM_PLAYER_POS_X	(SCREEN_WIDTH - ((NUM_HP_SIZE_X * NUM_PLACE + TIMER_INTERVAL_X * (NUM_PLACE - 1)) / 2) )	// HP�̕\����ʒu�w���W
#define	NUM_PLAYER_POS_Y	(80.0f)																						// HP�̕\����ʒu�x���W

#define	TIMER_ENEMY_POS		D3DXVECTOR3(1050.0f, 620.0f, 0.0f)		// �K�E�Z�Q�[�W�G�l�~�[�̊�{�ʒu
#define	NUM_ENEMY_POS_X		(SCREEN_WIDTH - ((NUM_HP_SIZE_X * NUM_PLACE + TIMER_INTERVAL_X * (NUM_PLACE - 1)) / 2) )	// HP�̕\����ʒu�w���W
#define	NUM_ENEMY_POS_Y		(80.0f)																						// HP�̕\����ʒu�x���W



// �^�C�}�[����}�N��
enum
{
	NUM_TIMER,			// �^�C�}�[
	NUM_PLAYER_KILL,	// �K�E�Z�Q�[�W�v���C���[
	NUM_ENEMY_KILL,		// �K�E�Z�Q�[�W�G�l�~�[
	NUM_MAX,			// �}�N���ő吔
};

// ������}�N��
enum
{
	NUM_THREE_DIGIT,	// �O����
	NUM_DOUBLE_DIGIT,	// �񌅖�
	NUM_DIGIT,			// �ꌅ��
	NUM_DIGIT_MAX,		// �}�N���ő吔
};


//=============================================================================
// �\���̐錾
//=============================================================================

// �^�C�g���\����
typedef struct
{

	bool					use;			// �`�搧��ϐ� true:�g�p false:���g�p

	D3DXVECTOR3				pos;			// ���W�i�[�ϐ�
	D3DXVECTOR3				rot;			// ��]�i�[�ϐ�

	int						nummax;			// ���l�i�[�ϐ�

	LPDIRECT3DVERTEXBUFFER9 buff;			// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^�ϐ�

}TIMER;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitTimer(int type);				// �����������֐�
void UninitTimer(void);						// �I�������֐�
void UpdateTimer(void);						// �X�V�����֐�
void DrawTimer(void);						// �`�揈���֐�

void EnableTimer(bool bEnable);				// �^�C�}�[�J�n�֐�
void ResetTimer(int nTime = TIME_DRAW_MAX);	// �^�C�}�[���Z�b�g�֐�

#endif

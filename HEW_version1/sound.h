//=============================================================================
//
// �T�E���h���� [sound.cpp]
// Author : ���ˌ��j��
// �v���O�����쐬�� : 2018/3/09
//
//=============================================================================

// ���d�C���N���[�h�h�~�̈�
#ifndef ___SOUND_H___
#define ___SOUND_H___

// ���C�u�����g�p���̈�
#include <dsound.h>			// ���C�u�����g�p�̈�
#include <tchar.h>			// �ėp�e�L�X�g�g�p�̈�
#include <windows.h>		// ���L�C���N���[�h�̃G���[�h�~�̈�
#include <mmsystem.h>		// ���Ԍv���̈�

//*****************************************************************************
// �}�N����`
//*****************************************************************************

// �T�E���h�ʂ��i���o�[�}�N��(sound.cpp�̏��Ԃƍ��킹�鎖)
enum
{
	BGM_TITLE,				// �^�C�g��BGM
	BGM_CALL_START,			// �X�^�[�g�R�[��
	BGM_BATTLE,				// �ʏ�퓬BGM
	BGM_QUICK,				// �ł�BGM
	BGM_CALL_RESULT,		// ���U���gBGM
	BGM_RESULT,				// ���U���gBGM�Q

	SE_SERECT,				// �J�[�\���ړ�SE
	SE_PUSH,				// �J�[�\������SE
	SE_BULLET,				// �ʏ�eSE
	SE_WARM,				// ����e�PSE
	SE_CASCEDE,				// ����e�QSE
	SE_FLAME,				// �K�E�ZSE
	SE_HIT,					// �q�b�gSE

	SOUND_MAX			// �o�^���ő吔
};

// �Đ��p�t���O�}�N��
enum
{
	E_DS8_FLAG_NONE,	// ���炷
	E_DS8_FLAG_LOOP,	// DSBPLAY_LOOPING=1:���[�v�Đ�
	E_DS8_FLAG_MAX		// �Đ��t���O�ő吔
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);									// �����������֐�
void UninitSound();												// �I�������֐�
LPDIRECTSOUNDBUFFER8 LoadSound(int no);							// ���[�h�����֐�
void PlaySound(int no, int flag = 0);		// �Đ������֐�
void StopSound(int no);					// ��~�����֐�
bool IsPlaying(LPDIRECTSOUNDBUFFER8 pBuffer);					// �Đ�����֐�
void SetSound(int no);											// �T�E���h�J�ڐ���֐�


#endif
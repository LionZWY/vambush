//=============================================================================
//
// �T�E���h���� [sound.cpp]
// Author : ���ˌ��j��
// �v���O�����쐬�� : 2018/3/09
//
//=============================================================================

#include "sound.h"		// �}�N�����\���̂̎g�p�̈�
#include <dsound.h>		// �֐��g�p�̈�
#include "main.h"		// ���C�u�����g�p�̈�

// ���܂��Ȃ�
#pragma comment ( lib, "dxguid.lib" )
#pragma comment ( lib, "dsound.lib" )
#pragma comment ( lib, "winmm.lib" )

//*****************************************************************************
// �}�N����`
//*****************************************************************************

// �T�E���h�t�@�C���̃p�X�isound.h�̒ʂ��i���o�[�Ə��Ԃ����킹��j
const TCHAR* c_soundFilename[] = {
	_T("data/BGM/�@�BBGM (online-audio-converter.com).wav"),
	_T("data/BGM/3.2.1...Go!SE (online-audio-converter.com).wav"),
	_T("data/BGM/�A�b�v�X�p�C�X (online-audio-converter.com).wav"),
	_T("data/BGM/�c��30�bBGM�Emp3.wav"),
	_T("data/BGM/jingle1 (online-audio-converter.com).wav"),
	_T("data/BGM/���U���gBGM.wav"),

	_T("data/SE/�J�[�\���I��.wav"),
	_T("data/SE/����SE.wav"),
	_T("data/SE/�ʏ�U��SE.wav"),
	_T("data/SE/���[��SE.wav"),
	_T("data/SE/�J�X�P�[�hSE.wav"),
	_T("data/SE/FLAME SE.wav"),
	_T("data/SE/�H�炤SE2.wav"),

};

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
IDirectSound8 *g_pDirectSound[SOUND_MAX];	// �T�E���h�C���^�[�t�F�[�X

LPDIRECTSOUNDBUFFER8	BGM[SOUND_MAX];		// �T�E���h�i�[�ϐ���o�^�����錾

//=============================================================================
// ����������
//=============================================================================
// hWnd:�E�B���h�E�n���h��
HRESULT InitSound(HWND hWnd)
{

	// �ő吔������
	for (int i = 0;i < SOUND_MAX;i++)
	{
		// DirectSound�I�u�W�F�N�g�̍쐬
		if (FAILED(DirectSoundCreate8(NULL, &g_pDirectSound[i], NULL)))
		{
			return E_FAIL;
		}

		// �������x���ݒ� 
		if (FAILED(g_pDirectSound[i]->SetCooperativeLevel(hWnd, DSSCL_PRIORITY)))
		{
			return E_FAIL;
		}
	}

	// BGM���[�h�ɓo�^�������[�h
	BGM[BGM_TITLE] = LoadSound(BGM_TITLE);					// �^�C�g��BGM
	BGM[BGM_CALL_START] = LoadSound(BGM_CALL_START);		// �X�^�[�g�R�[��
	BGM[BGM_BATTLE] = LoadSound(BGM_BATTLE);				// �ʏ�퓬BGM
	BGM[BGM_QUICK] = LoadSound(BGM_QUICK);					// �ł�BGM
	BGM[BGM_CALL_RESULT] = LoadSound(BGM_CALL_RESULT);		// ���U���gBGM
	BGM[BGM_RESULT] = LoadSound(BGM_RESULT);				// ���U���gBGM�Q

	// SE�̃��[�h
	BGM[SE_SERECT] = LoadSound(SE_SERECT);				// �J�[�\���ړ�SE
	BGM[SE_PUSH] = LoadSound(SE_PUSH);					// �J�[�\������SE
	BGM[SE_BULLET] = LoadSound(SE_BULLET);				// �ʏ�eSE
	BGM[SE_WARM] = LoadSound(SE_WARM);					// ����e�PSE
	BGM[SE_CASCEDE] = LoadSound(SE_CASCEDE);			// ����e�QSE
	BGM[SE_FLAME] = LoadSound(SE_FLAME);				// �K�E�ZSE
	BGM[SE_HIT] = LoadSound(SE_HIT);					// �q�b�gSE

	// �^�C�g��BGM�Đ�
	PlaySound(BGM_TITLE, E_DS8_FLAG_LOOP);

	return S_OK;
}

//=============================================================================
// �I������		�������[�̉��
//=============================================================================
void UninitSound()
{

	// �ő吔�I������
	for (int i = 0;i < SOUND_MAX;i++)
	{
		// �������̉��
		if (g_pDirectSound[i] != NULL)
		{
			g_pDirectSound[i]->Release();
			g_pDirectSound[i] = NULL;
		}
	}
}

//=============================================================================
// ���[�h����
// �T�E���h�̃��[�h
// no:�T�E���h�i���o�[�i�w�b�_�ɒ�`���ꂽ�񋓌^�萔�j
//=============================================================================
LPDIRECTSOUNDBUFFER8 LoadSound(int no)
{
	// MMIO = �}���`���f�B�A���o�́A�̗��B
	LPDIRECTSOUNDBUFFER  pBaseBuffer = NULL;	// �ȃf�[�^�̑����o�b�t�@
	LPDIRECTSOUNDBUFFER8 pBuffer = NULL;		// �ȃf�[�^�̃o�b�t�@
	DSBUFFERDESC buff;							// �o�b�t�@�ݒ�\����

	HMMIO hMmio = NULL;							// MMIO�n���h��
	MMIOINFO mmioInfo;							// �}���`���f�B�A�f�[�^�\����

	MMRESULT mmRes;								// MM�������ʊi�[�ϐ�
	MMCKINFO riffChunk, formatChunk, dataChunk;	// �`�����N�f�[�^�\����
	DWORD size;									// �f�[�^�T�C�Y�i�[�p
	WAVEFORMATEX pcm;							// �ȃf�[�^�t�H�[�}�b�g�\����

	LPVOID pBlock;								// �Z�J���_���o�b�t�@�̃f�[�^�������ݐ�A�h���X
	DWORD  dwSize;								// �Z�J���_���o�b�t�@�̃T�C�Y

												// 1.�n���h�������ƂɃt�@�C�����J��
	memset(&mmioInfo, 0, sizeof(MMIOINFO));
	hMmio = mmioOpen((LPSTR)c_soundFilename[no], &mmioInfo, MMIO_READ);

	// ������Ȃ�������ُ�I��
	if (!hMmio)
	{
		return NULL;
	}

	// 2.�t�@�C����͇@ RIFF�`�����N����
	riffChunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');				// �����L�[���[�h
	mmRes = mmioDescend(hMmio, &riffChunk, NULL, MMIO_FINDRIFF);	// �L�[���[�h�����ƂɌ���

																	// ������Ȃ�������ُ�I��
	if (mmRes != MMSYSERR_NOERROR)
	{
		// �t�@�C�������
		mmioClose(hMmio, 0);
		return NULL;
	}

	// 3.�t�@�C����͇A �t�H�[�}�b�g�`�����N����
	formatChunk.ckid = mmioFOURCC('f', 'm', 't', ' ');						// �����L�[���[�h
	mmRes = mmioDescend(hMmio, &formatChunk, &riffChunk, MMIO_FINDCHUNK);	// �L�[���[�h�����ƂɌ���

																			// ������Ȃ�������ُ�I��
	if (mmRes != MMSYSERR_NOERROR)
	{
		// �t�@�C�������
		mmioClose(hMmio, 0);
		return NULL;
	}

	// �����������Ƃɓǂݍ���
	size = mmioRead(hMmio, (HPSTR)&pcm, formatChunk.cksize);

	// �������ǂݍ��߂Ȃ�������ُ�I��
	if (size != formatChunk.cksize)
	{
		// �t�@�C�������
		mmioClose(hMmio, 0);
		return NULL;
	}

	// �`�����N����A�Z���h
	mmioAscend(hMmio, &formatChunk, 0);

	// 4.�t�@�C����͇B �f�[�^�`�����N����
	dataChunk.ckid = mmioFOURCC('d', 'a', 't', 'a');					// �����L�[���[�h
	mmRes = mmioDescend(hMmio, &dataChunk, &riffChunk, MMIO_FINDCHUNK);	// �L�[���[�h�����ƂɌ���

																		// ������Ȃ�������ُ�I��
	if (mmRes != MMSYSERR_NOERROR)
	{
		// �t�@�C�������
		mmioClose(hMmio, 0);
		return NULL;
	}

	// 5.�f�[�^�ǂݍ���
	char *pData = new char[dataChunk.cksize];					// �K�v�ȑ傫���̗̈���m�ۂ���
	size = mmioRead(hMmio, (HPSTR)pData, dataChunk.cksize);		// �f�[�^��ǂݍ���

																// �������ǂݍ��߂Ȃ�������ُ�I��
	if (size != dataChunk.cksize)
	{
		// ���̓ǂݍ��ݗ̈������
		delete[] pData;
		return NULL;
	}

	// 6.�Ȃ�ǂݍ��ށu�Z�J���_���o�b�t�@�v��p��
	ZeroMemory(&buff, sizeof(DSBUFFERDESC));		// �܂�������
	buff.dwSize = sizeof(DSBUFFERDESC);				// ��������e��ݒ�
	buff.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS | DSBCAPS_LOCDEFER;
	buff.dwBufferBytes = size;
	buff.lpwfxFormat = &pcm;

	// �����o�b�t�@�����
	if (FAILED(g_pDirectSound[no]->CreateSoundBuffer(&buff, &pBaseBuffer, NULL)))
	{
		return NULL;
	}


	// �T�E���h�o�b�t�@�����o��
	if (FAILED(pBaseBuffer->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&pBuffer)))
	{
		return NULL;
	}

	// ���o�����瑍���o�b�t�@���̂Ă�
	pBaseBuffer->Release();

	// 7.���ꂽ�Z�J���_���o�b�t�@�Ƀf�[�^��]��
	// �܂��͏������݂ł���悤�o�b�t�@�����b�N
	if (FAILED(pBuffer->Lock(0, 0, &pBlock, &dwSize, NULL, NULL, DSBLOCK_ENTIREBUFFER)))
	{
		return NULL;
	}

	memcpy(pBlock, pData, dwSize);	// �f�[�^�]��
	delete[] pData;					// ���̓ǂݍ��ݗ̈������

									// �o�b�t�@���b�N����
	pBuffer->Unlock(pBlock, dwSize, 0, 0);

	// �Z�J���_���o�b�t�@��Ԃ��Ċ���
	return pBuffer;
}
//=============================================================================
// �Đ������֐�
// pBuffer:����炵�����T�E���h�f�[�^�̃Z�J���_���o�b�t�@
// flag   :1(E_DS8_FLAG_LOOP)�Ȃ烋�[�v�Đ�
//=============================================================================
void PlaySound(int no, int flag/*=0*/)
{	// ��������炷�̂ŁA�ŏ�����炵�����ꍇ��SetCurrentPosition(0)�����邱��
	// �ŏ�����Đ�
	BGM[no]->SetCurrentPosition(0);
	BGM[no]->Play(0, 0, flag);
}

//=============================================================================
// ��~�����֐�
//=============================================================================
void StopSound(int no)
{
	DWORD status;
	BGM[no]->GetStatus(&status);
	if (status & DSBSTATUS_PLAYING)	// ���Ă�����
	{
		BGM[no]->Stop();	// �Ӗ��I�ɂ�Pause�ɂȂ�B
	}
}

//=============================================================================
// �Đ�����֐�
// pBuffer:����炵�����T�E���h�f�[�^�̃Z�J���_���o�b�t�@
//=============================================================================
bool IsPlaying(LPDIRECTSOUNDBUFFER8 pBuffer)
{
	DWORD status;

	pBuffer->GetStatus(&status);
	if (status & DSBSTATUS_PLAYING)
	{
		return true;
	}
	return false;
}

//=============================================================================
// �T�E���h�J�ڐ���֐�
//=============================================================================
void SetSound(int no)
{

	// �Đ�����
	switch (no)
	{
		// �^�C�g�����
	case STAGE_TITLE:
	{
		StopSound(BGM_BATTLE);							// �ʏ�퓬BGM�̒�~
		StopSound(BGM_CALL_RESULT);							// ���U���gBGM�̒�~
		StopSound(BGM_RESULT);							// ���U���gBGM�̒�~
		PlaySound(BGM_TITLE, E_DS8_FLAG_LOOP);		// �^�C�g��BGM�̍Đ�
		break;
	}

	// �Q�[�����
	case STAGE_GAME:
	{
		StopSound(BGM_TITLE);							// �^�C�g��BGM�̒�~
		StopSound(BGM_CALL_RESULT);						// ���U���gBGM�̒�~
		StopSound(BGM_RESULT);							// ���U���gBGM�̒�~
		PlaySound(BGM_BATTLE, E_DS8_FLAG_LOOP);		// �ʏ�퓬BGM�̍Đ�
		break;
	}

	// ���U���g���
	case STAGE_RESULT:
	{
		StopSound(BGM_BATTLE);								// �ʏ�퓬BGM�̒�~
		StopSound(BGM_QUICK);							// �ʏ�퓬BGM�̒�~
		PlaySound(BGM_CALL_RESULT, E_DS8_FLAG_NONE);		// ���U���gBGM�̍Đ�
		break;
	}
	}
}


//=============================================================================
// BGM�擾�֐�
//=============================================================================
LPDIRECTSOUNDBUFFER8 GetBgm(int no)
{
	return(BGM[no]);
}
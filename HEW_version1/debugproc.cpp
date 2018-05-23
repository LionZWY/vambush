//=============================================================================
//
// �f�o�b�O�\������ [debugproc.cpp]
// Author : ���ˌ��j��
// �v���O�����쐬�� : 2018/3/09
//
//=============================================================================
#include "debugproc.h"		// �����e�i���X����̈�
#include <stdio.h>			// �ėp�֐��g�p�̈�

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPD3DXFONT	g_Font = NULL;							// �t�H���g�ւ̃|�C���^
char		g_aStrDebug[DEBUG_STR_MAX] = {"\0"};	// �f�o�b�O���

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT InitDebugProc(void)
{
	// �|�C���^�̏�����
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �ݒ�p�ϐ���錾
	HRESULT hr;

	// ���\���p�t�H���g��ݒ�
	hr = D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
					OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_Font);

	// ���N���A
	memset(g_aStrDebug, 0, sizeof g_aStrDebug);

	return hr;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void UninitDebugProc(void)
{
	// �������̉��
	if(g_Font != NULL)
	{// ���\���p�t�H���g�̊J��
		g_Font->Release();
		g_Font = NULL;
	}
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void UpdateDebugProc(void)
{
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void DrawDebugProc(void)
{
	// ���\���ʒu�i�[
	RECT rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

	// ���\��
	g_Font->DrawText(NULL, g_aStrDebug, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0, 0, 0));

	// ���N���A
	memset(g_aStrDebug, 0, sizeof g_aStrDebug);
}

//=============================================================================
// �f�o�b�O�\���̓o�^�֐�
//=============================================================================
void PrintDebugProc(char *fmt,...)
{
#if 0
	long *pParam;
	static char aBuf[256];

	pParam = (long*)&fmt;
	sprintf(aBuf, fmt, pParam[1], pParam[2], pParam[3], pParam[4],
									pParam[5], pParam[6], pParam[7], pParam[8],
									pParam[9], pParam[10], pParam[11], pParam[12]);
#else
	va_list list;					// �ψ�������������ׂɎg�p����ϐ�
	char *pCur;						// �|�C���^��錾
	char aBuf[BUFF_MAX]={"\0"};
	char aWk[AWK_MAX];

	// �ψ����ɃA�N�Z�X����O�̏�������
	va_start(list, fmt);

	pCur = fmt;

	for( ; *pCur; ++pCur)
	{
		if(*pCur != '%')
		{
			sprintf(aWk, "%c", *pCur);
		}
		else
		{
			pCur++;

			switch(*pCur)
			{
			case 'd':
				// �ψ����ɃA�N�Z�X���Ă��̕ϐ������o������
				sprintf(aWk, "%d", va_arg(list, int));
				break;

			case 'f':
				// �ψ����ɃA�N�Z�X���Ă��̕ϐ������o������
				sprintf(aWk, "%.2f", va_arg(list, double));		// double�^�Ŏw��
				break;

			case 's':
				// �ψ����ɃA�N�Z�X���Ă��̕ϐ������o������
				sprintf(aWk, "%s", va_arg(list, char*));
				break;

			case 'c':
				// �ψ����ɃA�N�Z�X���Ă��̕ϐ������o������
				sprintf(aWk, "%c", va_arg(list, char));
				break;

			default:
				sprintf(aWk, "%c", *pCur);
				break;
			}
		}
		strcat(aBuf, aWk);
	}

	// �ψ����ɃA�N�Z�X������̏I������
	va_end(list);

	// �A��
	if((strlen(g_aStrDebug) + strlen(aBuf)) < sizeof g_aStrDebug - 1)
	{
		strcat(g_aStrDebug, aBuf);
	}
#endif
}

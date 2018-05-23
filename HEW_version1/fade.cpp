//=============================================================================
//
// �t�F�[�h���� [fade.cpp]
// Author : ���ˌ��j��
// �v���O�����쐬�� : 2018/3/09
//
//=============================================================================
#include "fade.h"					// �}�N���g�p�̈�
#include "main.h"					// ����
#include "game.h"					// ����
#include "camera.h"					// �֐��g�p�̈�
#include "sound.h"					// ����

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	FADE_RATE		(0.02f)		// �t�F�[�h�W��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexFade(LPDIRECT3DDEVICE9 pDevice);		// ���_�쐬�֐�
void SetColor(D3DCOLOR col);							// �F�ݒ�֐�

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_p3DTextureFade = NULL;	// �e�N�X�`���ւ̃|�C���^�ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffFade = NULL;	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^�ϐ�

D3DXCOLOR				g_color;					// �F�i�[�ϐ�
FADE					g_fade = FADE_IN;			// ��Ԋi�[�ϐ�

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT InitFade(void)
{
	// �|�C���^�̏�����
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���̐ݒ�
	MakeVertexFade(pDevice);

	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void UninitFade(void)
{
	if(g_p3DTextureFade != NULL)
	{// �e�N�X�`���̊J��
		g_p3DTextureFade->Release();
	}

	if(g_pD3DVtxBuffFade != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffFade->Release();
	}
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void UpdateFade(void)
{
	// �t�F�[�h����
	if(g_fade != FADE_NONE)
	{
		// �t�F�[�h������
		if(g_fade == FADE_OUT)
		{
			// �t�F�[�h�A�E�g����
			g_color.a += FADE_RATE;		// ���l�����Z���ĉ�ʂ������Ă���

			// �t�F�[�h�A�E�g�I��
			if(g_color.a >= 1.0f)
			{

				// �t�F�[�h�C�������ɐ؂�ւ�
				g_color.a = 1.0f;
				SetFade(FADE_IN);

				//// ���݂̃��[�h���擾
				int *mode = GetStage();

				// ���[�h���P�i�߂�
				*mode = ((*mode + 1) % STAGE_MAX);

				// �Q�[���J�����ɐ؂�ւ�
				if (*mode == STAGE_GAME)
				{
					InitCamera();
				}

				// ���[�h��ݒ�
				SetStage(*mode);

				// ���[�h���̉��y�̓K��
				int sound = *mode;

				// ���y��ݒ�
				SetSound(sound);
			}

			// �F��ݒ�
			SetColor(g_color);
		}

		// �t�F�[�h�C������
		else if(g_fade == FADE_IN)
		{
			
			// ���l�����Z���ĉ�ʂ𕂂��オ�点��
			g_color.a -= FADE_RATE;

			// �t�F�[�h�C���I��
			if(g_color.a <= 0.0f)
			{
				// �t�F�[�h�����I��
				g_color.a = 0.0f;
				SetFade(FADE_NONE);
			}

			// �F��ݒ�
			SetColor(g_color);
		}
	}
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void DrawFade(void)
{

	// �|�C���^�̏�����
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pD3DVtxBuffFade, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//=============================================================================
// ���_�쐬�֐�
//=============================================================================
HRESULT MakeVertexFade(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
    if( FAILED( pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,		// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
												D3DUSAGE_WRITEONLY,				// ���_�o�b�t�@�̎g�p�@�@
												FVF_VERTEX_2D,					// �g�p���钸�_�t�H�[�}�b�g
												D3DPOOL_MANAGED,				// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
												&g_pD3DVtxBuffFade,				// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
												NULL)))							// NULL�ɐݒ�
	{
        return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

		// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
		pVtx[0].rhw =
		pVtx[1].rhw =
		pVtx[2].rhw =
		pVtx[3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		g_color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[0].diffuse = g_color;
		pVtx[1].diffuse = g_color;
		pVtx[2].diffuse = g_color;
		pVtx[3].diffuse = g_color;

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);	

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffFade->Unlock();
	}

	return S_OK;
}

//=============================================================================
// �F�ݒ�֐�
//=============================================================================
void SetColor(D3DCOLOR col)
{
	VERTEX_2D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pD3DVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	// ���ˌ��̐ݒ�
	pVtx[0].diffuse = col;
	pVtx[1].diffuse = col;
	pVtx[2].diffuse = col;
	pVtx[3].diffuse = col;

	// ���_�f�[�^���A�����b�N����
	g_pD3DVtxBuffFade->Unlock();
}

//=============================================================================
// �t�F�[�h��Ԑݒ�֐�
//=============================================================================
void SetFade(FADE fade)
{
	g_fade = fade;
}

//=============================================================================
// �t�F�[�h��Ԏ擾�֐�
//=============================================================================
FADE GetFade(void)
{
	return g_fade;
}

//=============================================================================
//
// �������� [noize.cpp]
// Author : �镶��
// �v���O�����쐬�� : 2018/3/09
//=============================================================================
#include "noize.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_NOIZE		"data/TEXTURE/noize_eff.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	NOIZE_SIZE_X		(50.0f)							// �r���{�[�h�̕�
#define	NOIZE_SIZE_Y		(50.0f)							// �r���{�[�h�̍���
#define	VALUE_MOVE_NOIZE	(2.0f)							// �ړ����x

#define	MAX_NOIZE			(128)							// �r���{�[�h�ő吔

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 rot;		// ��]
	D3DXVECTOR3 scale;		// �X�P�[��
	D3DXCOLOR col;			// �F
	float fSizeX;			// ��
	float fSizeY;			// ����
	int nCounter;			// �J�E���^�[
	int nPattern;			// �p�^�[��No.
	int nType;				// ���
	bool bUse;				// �g�p���Ă��邩�ǂ���
} NOIZE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexNoize(LPDIRECT3DDEVICE9 pDevice);
void SetVertexNoize(int nIdxBullet, float fSizeX, float fSizeY);
void SetColorNoize(int nIdxNoize, D3DXCOLOR col);
void SetTextureNoize(int nIdxNoize, int nPattern);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureNoize = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffNoize = NULL;	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

D3DXMATRIX				g_mtxWorldNoize;			// ���[���h�}�g���b�N�X

NOIZE				g_aNoize[MAX_NOIZE];	// �������[�N

//=============================================================================
// ����������
//=============================================================================
HRESULT InitNoize(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���̍쐬
	MakeVertexNoize(pDevice);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
								TEXTURE_NOIZE,			// �t�@�C���̖��O
								&g_pD3DTextureNoize);	// �ǂݍ��ރ������[

	for(int nCntNoize = 0; nCntNoize < MAX_NOIZE; nCntNoize++)
	{
		g_aNoize[nCntNoize].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aNoize[nCntNoize].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aNoize[nCntNoize].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_aNoize[nCntNoize].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aNoize[nCntNoize].fSizeX = NOIZE_SIZE_X;
		g_aNoize[nCntNoize].fSizeY = NOIZE_SIZE_Y;
		g_aNoize[nCntNoize].nCounter = 0;
		g_aNoize[nCntNoize].nPattern = 0;
		g_aNoize[nCntNoize].nType = NOIZETYPE_NOIZE_PLAYER;
		g_aNoize[nCntNoize].bUse = false;
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitNoize(void)
{
	if(g_pD3DTextureNoize != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureNoize->Release();
		g_pD3DTextureNoize = NULL;
	}

	if(g_pD3DVtxBuffNoize != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffNoize->Release();
		g_pD3DVtxBuffNoize = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateNoize(void)
{
	D3DXVECTOR3 rotCamera;
	CAMERA *camera = GetCamera();

	// �J�����̉�]���擾
	rotCamera = camera->rot;

	for(int nCntNoize = 0; nCntNoize < MAX_NOIZE; nCntNoize++)
	{
		if(g_aNoize[nCntNoize].bUse)
		{
			g_aNoize[nCntNoize].nCounter--;
			if((g_aNoize[nCntNoize].nCounter % 4) == 0)
			{
				g_aNoize[nCntNoize].nPattern++;
				if(g_aNoize[nCntNoize].nPattern >= 6)
				{
					g_aNoize[nCntNoize].bUse = false;
				}
				else
				{
					// �e�N�X�`�����W�̐ݒ�
					SetTextureNoize(nCntNoize, g_aNoize[nCntNoize].nPattern);
				}
			}

			// ���_���W�̐ݒ�
			g_aNoize[nCntNoize].fSizeX += 0.50f;
			g_aNoize[nCntNoize].fSizeY += 0.50f;
			SetVertexNoize(nCntNoize, g_aNoize[nCntNoize].fSizeX, g_aNoize[nCntNoize].fSizeY);

			if(g_aNoize[nCntNoize].nPattern >= 2)
			{
				// ���_�J���[�̐ݒ�
				g_aNoize[nCntNoize].col.a -= 0.02f;
				if(g_aNoize[nCntNoize].col.a < 0.0f)
				{
					g_aNoize[nCntNoize].col.a = 0.0f;
				}
				SetColorNoize(nCntNoize, g_aNoize[nCntNoize].col);
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawNoize(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView,mtxScale,mtxTranslate;

	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);				// Z��r�Ȃ�

	for(int nCntNoize = 0; nCntNoize < MAX_NOIZE; nCntNoize++)
	{
		if(g_aNoize[nCntNoize].bUse)
		{

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldNoize);

			// �r���[�}�g���b�N�X���擾
			mtxView = GetMtxView();

			g_mtxWorldNoize._11 = mtxView._11;
			g_mtxWorldNoize._12 = mtxView._21;
			g_mtxWorldNoize._13 = mtxView._31;
			g_mtxWorldNoize._21 = mtxView._12;
			g_mtxWorldNoize._22 = mtxView._22;
			g_mtxWorldNoize._23 = mtxView._32;
			g_mtxWorldNoize._31 = mtxView._13;
			g_mtxWorldNoize._32 = mtxView._23;
			g_mtxWorldNoize._33 = mtxView._33;

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxScale, g_aNoize[nCntNoize].scale.x, g_aNoize[nCntNoize].scale.y, g_aNoize[nCntNoize].scale.z);
			D3DXMatrixMultiply(&g_mtxWorldNoize, &g_mtxWorldNoize, &mtxScale);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, g_aNoize[nCntNoize].pos.x, g_aNoize[nCntNoize].pos.y, g_aNoize[nCntNoize].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldNoize, &g_mtxWorldNoize, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldNoize);

			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, g_pD3DVtxBuffNoize, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pD3DTextureNoize);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntNoize * 3), NUM_POLYGON);

			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		}
	}

	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);				// Z��r����
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
HRESULT MakeVertexNoize(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
    if( FAILED( pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * MAX_NOIZE,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
												D3DUSAGE_WRITEONLY,							// ���_�o�b�t�@�̎g�p�@�@
												FVF_VERTEX_3D,								// �g�p���钸�_�t�H�[�}�b�g
												D3DPOOL_MANAGED,							// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
												&g_pD3DVtxBuffNoize,					// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
												NULL)))										// NULL�ɐݒ�
	{
        return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffNoize->Lock(0, 0, (void**)&pVtx, 0);

		for(int nCntNoize = 0; nCntNoize < MAX_NOIZE; nCntNoize++, pVtx += 4)
		{
			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(-NOIZE_SIZE_X / 2, -NOIZE_SIZE_Y / 2, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(NOIZE_SIZE_X / 2, -NOIZE_SIZE_Y / 2, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(-NOIZE_SIZE_X / 2, NOIZE_SIZE_Y / 2, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(NOIZE_SIZE_X / 2, NOIZE_SIZE_Y / 2, 0.0f);

			// �@���̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[1].vtx = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[2].vtx = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[3].vtx = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

			// ���ˌ��̐ݒ�
			pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffNoize->Unlock();
	}

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexNoize(int nIdxNoize, float fSizeX, float fSizeY)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffNoize->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxNoize * 4);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(-fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-fSizeX / 2, fSizeY / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(fSizeX / 2, fSizeY / 2, 0.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffNoize->Unlock();
	}
}

//=============================================================================
// ���_�J���[�̐ݒ�
//=============================================================================
void SetColorNoize(int nIdxNoize, D3DXCOLOR col)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffNoize->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxNoize * 4);

		// ���_���W�̐ݒ�
		pVtx[0].diffuse =
		pVtx[1].diffuse =
		pVtx[2].diffuse =
		pVtx[3].diffuse = col;

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffNoize->Unlock();
	}
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureNoize(int nIdxNoize, int nPattern)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffNoize->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxNoize * 4);

		// ���_���W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(nPattern * (float)(1.0f / 6), 0.0f);
		pVtx[1].tex = D3DXVECTOR2((nPattern + 1) * (float)(1.0f / 6), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(nPattern * (float)(1.0f / 6), 1.0f);
		pVtx[3].tex = D3DXVECTOR2((nPattern + 1) * (float)(1.0f / 6), 1.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffNoize->Unlock();
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
int SetNoize(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nType)
{
	int nIdxNoize = -1;

	for(int nCntNoize = 0; nCntNoize < MAX_NOIZE; nCntNoize++)
	{
		if(!g_aNoize[nCntNoize].bUse)
		{
			g_aNoize[nCntNoize].pos = pos;
			g_aNoize[nCntNoize].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aNoize[nCntNoize].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_aNoize[nCntNoize].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_aNoize[nCntNoize].fSizeX = fSizeX;
			g_aNoize[nCntNoize].fSizeY = fSizeY;
			g_aNoize[nCntNoize].nCounter = 0;
			g_aNoize[nCntNoize].nPattern = 0;
			g_aNoize[nCntNoize].nType = nType;
			g_aNoize[nCntNoize].bUse = true;

			// ���_���W�̐ݒ�
			SetVertexNoize(nCntNoize, fSizeX, fSizeY);

			if(g_aNoize[nCntNoize].nType == NOIZETYPE_NOIZE_PLAYER)
			{
				g_aNoize[nCntNoize].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); 
			}
			else if(g_aNoize[nCntNoize].nType == NOIZETYPE_NOIZE_ENEMY)
			{
				g_aNoize[nCntNoize].col = D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f); 
			}
			SetColorNoize(nCntNoize, g_aNoize[nCntNoize].col);

			// �e�N�X�`�����W�̐ݒ�
			SetTextureNoize(nCntNoize, 0);

			nIdxNoize = nCntNoize;

			break;
		}
	}

	return nIdxNoize;
}

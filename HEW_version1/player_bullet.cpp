//=============================================================================
//
// �ʏ�e���� [playerplayerbullet.cpp]
// Author : �镶��
// �v���O�����쐬�� : 2018/3/09
//=============================================================================
#include "player_bullet.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "effect.h"
#include "player.h"
#include "field.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexPlayerBullet(LPDIRECT3DDEVICE9 pDevice);
void SetVertexPlayerBullet(int nIdxBullet, D3DXVECTOR2 size);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTexturePlayerBullet = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffPlayerBullet	= NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

PLAYER_BULLET					playerbulletWk[MAX_BULLET];			// �e���[�N
//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayerBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER_BULLET *playerbullet = playerbulletWk;

	// ���_���̍쐬
	MakeVertexPlayerBullet(pDevice);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
								TEXTURE_BULLET_PLAYER,				// �t�@�C���̖��O
								&g_pD3DTexturePlayerBullet);	// �ǂݍ��ރ������[

													

	for(int i = 0; i < MAX_BULLET; i++, playerbullet++)
	{
		playerbullet->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		playerbullet->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		playerbullet->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		playerbullet->move = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		playerbullet->size.x = BULLET_SIZE_X;
		playerbullet->size.y = BULLET_SIZE_Y;
		playerbullet->timer = 0;
		playerbullet->bUse = false;
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayerBullet(void)
{
	if(g_pD3DTexturePlayerBullet != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTexturePlayerBullet->Release();
		g_pD3DTexturePlayerBullet = NULL;
	}

	if(g_pD3DVtxBuffPlayerBullet != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffPlayerBullet->Release();
		g_pD3DVtxBuffPlayerBullet = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayerBullet(void)
{
	D3DXVECTOR3 rotCamera;
	PLAYER_BULLET *playerbullet = playerbulletWk;


	// �J�����̉�]���擾
	rotCamera = GetRotCamera();

 for(int i = 0; i < MAX_BULLET; i++, playerbullet++)
	{
		if(playerbullet->bUse)
		{
			playerbullet->pos.x += playerbullet->move.x;
			playerbullet->pos.z += playerbullet->move.z;

			playerbullet->timer--;
			if(playerbullet->timer <= 0)
			{
				ReleaseShadow(playerbullet->nIdxShadow);
				playerbullet->bUse = false;
			}
			else
			{
				// �e�̈ʒu�ݒ�
				SetPositionShadow(playerbullet->nIdxShadow, D3DXVECTOR3(playerbullet->pos.x, 0.1f, playerbullet->pos.z));


				// �G�t�F�N�g�̐ݒ�
				SetEffect(playerbullet->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(0.85f, 0.05f, 0.15f, 0.50f), D3DXVECTOR2(16.0f, 16.0f), 10);
				SetEffect(playerbullet->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(0.65f, 0.10f, 0.10f, 0.30f), D3DXVECTOR2(12.0f, 12.0f), 10);
				SetEffect(playerbullet->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(0.45f, 0.15f, 0.05f, 0.20f), D3DXVECTOR2(6.0f, 6.0f), 10);


			}

			D3DXVECTOR2	size;
			size.x = 8.0f + (playerbullet->pos.y - 4.0f) * 0.05f;
			if(size.x < 8.0f)
			{
				size.x = 8.0f;
			}
			size.y = 8.0f + (playerbullet->pos.y - 4.0f) * 0.05f;
			if(size.y < 8.0f)
			{
				size.y = 8.0f;
			}

			SetVertexShadow(playerbullet->nIdxShadow, size);

			float colA = (200.0f - (playerbullet->pos.y - 4.0f)) / 400.0f;
			if(colA < 0.0f)
			{
				colA = 0.0f;
			}
			SetColorShadow(playerbullet->nIdxShadow, D3DXCOLOR(1.0f, 1.0f, 1.0f, colA));

			if (playerbullet->pos.x < (BULLET_SIZE_X / 2) - FIELD_SCL_MAX_X)
			{
				DeletePlayerBullet(i);
			}
			if (playerbullet->pos.x > FIELD_SCL_MAX_X - (BULLET_SIZE_X / 2))
			{
				DeletePlayerBullet(i);
			}
			if (playerbullet->pos.z > FIELD_SCL_MAX_Z)
			{
				DeletePlayerBullet(i);
			}
			if (playerbullet->pos.z < (BULLET_SIZE_Y / 2) - FIELD_SCL_MAX_Z)
			{
				DeletePlayerBullet(i);
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayerBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView,mtxscl,mtxTranslate;
	PLAYER_BULLET *playerbullet = playerbulletWk;

	// ���C�e�B���O�𖳌���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���e�X�g��L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

 for(int i = 0; i < MAX_BULLET; i++, playerbullet++)
	{
		if(playerbullet->bUse)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&playerbullet->world);

			// �r���[�}�g���b�N�X���擾
			mtxView = GetMtxView();

			playerbullet->world._11 = mtxView._11;
			playerbullet->world._12 = mtxView._21;
			playerbullet->world._13 = mtxView._31;
			playerbullet->world._21 = mtxView._12;
			playerbullet->world._22 = mtxView._22;
			playerbullet->world._23 = mtxView._32;
			playerbullet->world._31 = mtxView._13;
			playerbullet->world._32 = mtxView._23;
			playerbullet->world._33 = mtxView._33;

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxscl, playerbullet->scl.x, playerbullet->scl.y, playerbullet->scl.z);
			D3DXMatrixMultiply(&playerbullet->world, &playerbullet->world, &mtxscl);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, playerbullet->pos.x, playerbullet->pos.y, playerbullet->pos.z);
			D3DXMatrixMultiply(&playerbullet->world, &playerbullet->world, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &playerbullet->world);

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, g_pD3DVtxBuffPlayerBullet, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pD3DTexturePlayerBullet);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (i * 4), NUM_POLYGON);
		}
	}

	// ���C�e�B���O��L����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}

//=============================================================================
// ���_���̍쐬
//=============================================================================
HRESULT MakeVertexPlayerBullet(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
    if( FAILED( pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * MAX_BULLET,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
												D3DUSAGE_WRITEONLY,							// ���_�o�b�t�@�̎g�p�@�@
												FVF_VERTEX_3D,								// �g�p���钸�_�t�H�[�}�b�g
												D3DPOOL_MANAGED,							// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
												&g_pD3DVtxBuffPlayerBullet,						// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
												NULL)))										// NULL�ɐݒ�
	{
        return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffPlayerBullet->Lock(0, 0, (void**)&pVtx, 0);

		for(int i = 0; i < MAX_BULLET; i++, pVtx += 4)
		{
			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(-BULLET_SIZE_X / 2, -BULLET_SIZE_Y / 2, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(BULLET_SIZE_X / 2, -BULLET_SIZE_Y / 2, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(-BULLET_SIZE_X / 2, BULLET_SIZE_Y / 2, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(BULLET_SIZE_X / 2, BULLET_SIZE_Y / 2, 0.0f);

			// �@���̐ݒ�
			pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

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
		g_pD3DVtxBuffPlayerBullet->Unlock();
	}

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexPlayerBullet(int nIdxPlayerBullet, D3DXVECTOR2 size)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffPlayerBullet->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxPlayerBullet * 4);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(-size.x / 2, -size.y / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-size.x / 2, size.y / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(size.x / 2, -size.y / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(size.x / 2, size.y / 2, 0.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffPlayerBullet->Unlock();
	}
}

//=============================================================================
// �e�̐ݒ�
//=============================================================================
int SetPlayerBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 size, int timer)
{
	PLAYER_BULLET *playerbullet = playerbulletWk;

	int nIdxPlayerBullet = -1;

	playerbullet = GetPlayerBullet(0);
 for(int i = 0; i < MAX_BULLET; i++, playerbullet++)
	{
		if(!playerbullet->bUse)
		{

			playerbullet->pos = pos;
			playerbullet->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			playerbullet->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			playerbullet->move = move;
			playerbullet->size.x = size.x;
			playerbullet->size.y = size.y;
			playerbullet->timer = timer;
			playerbullet->bUse = true;

			// �e�̐ݒ�
			playerbullet->nIdxShadow = CreateShadow(pos, D3DXVECTOR2(8.0f, 8.0f));		// �e�̐ݒ�

			// ���_���W�̐ݒ�
			SetVertexPlayerBullet(i, size);

			nIdxPlayerBullet = i;

			break;
		}
	}

	return nIdxPlayerBullet;
}

//=============================================================================
// �e�̍폜
//=============================================================================
void DeletePlayerBullet(int nIdxPlayerBullet)
{
	if(nIdxPlayerBullet >= 0 && nIdxPlayerBullet < MAX_BULLET)
	{
		ReleaseShadow(playerbulletWk[nIdxPlayerBullet].nIdxShadow);
		playerbulletWk[nIdxPlayerBullet].bUse = false;
	}
}


PLAYER_BULLET *GetPlayerBullet(int no)
{
	return(&playerbulletWk[no]);
}
//=============================================================================
//
// �e���� [playerskillDef.cpp]
// Author : �镶��
// �v���O�����쐬�� : 2018/3/09
//=============================================================================
#include "player_skillDef.h"
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
HRESULT MakeVertexPlayerSkillDef(LPDIRECT3DDEVICE9 pDevice);
void SetVertexPlayerSkillDef(int nIdxSkillDef, D3DXVECTOR2 size);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTexturePlayerSkillDef = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffPlayerSkillDef	= NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

PLAYER_SKILLDEF					playerskillDefWk[MAX_SKILLDEF];			// �e���[�N
//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayerSkillDef(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER_SKILLDEF *playerskillDef = playerskillDefWk;

	// ���_���̍쐬
	MakeVertexPlayerSkillDef(pDevice);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
								TEXTURE_SKILLDEF_PLAYER,				// �t�@�C���̖��O
								&g_pD3DTexturePlayerSkillDef);	// �ǂݍ��ރ������[

													

	for(int i = 0; i < MAX_SKILLDEF; i++, playerskillDef++)
	{
		playerskillDef->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		playerskillDef->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		playerskillDef->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		playerskillDef->move = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		playerskillDef->size.x = SKILLDEF_SIZE_X;
		playerskillDef->size.y = SKILLDEF_SIZE_Y;
		playerskillDef->timer = 0;
		playerskillDef->cnt = 3;
		playerskillDef->bUse = false;
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayerSkillDef(void)
{
	if(g_pD3DTexturePlayerSkillDef != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTexturePlayerSkillDef->Release();
		g_pD3DTexturePlayerSkillDef = NULL;
	}

	if(g_pD3DVtxBuffPlayerSkillDef != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffPlayerSkillDef->Release();
		g_pD3DVtxBuffPlayerSkillDef = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayerSkillDef(void)
{
	D3DXVECTOR3 rotCamera;
	PLAYER_SKILLDEF *playerskillDef = playerskillDefWk;


	// �J�����̉�]���擾
	rotCamera = GetRotCamera();

 for(int i = 0; i < MAX_SKILLDEF; i++, playerskillDef++)
	{
		if(playerskillDef->bUse)
		{
			playerskillDef->pos.x += playerskillDef->move.x;
			playerskillDef->pos.z += playerskillDef->move.z;

			playerskillDef->timer--;
			if(playerskillDef->timer <= 0)
			{
				ReleaseShadow(playerskillDef->nIdxShadow);
				playerskillDef->bUse = false;
			}
			else
			{
				// �e�̈ʒu�ݒ�
				SetPositionShadow(playerskillDef->nIdxShadow, D3DXVECTOR3(playerskillDef->pos.x, 0.1f, playerskillDef->pos.z));


				// �G�t�F�N�g�̐ݒ�
				SetEffect(playerskillDef->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(0.85f, 0.05f, 0.15f, 0.50f), D3DXVECTOR2(32.0f, 32.0f), 10);
				SetEffect(playerskillDef->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(0.65f, 0.10f, 0.10f, 0.30f), D3DXVECTOR2(20.0f, 20.0f), 10);
				SetEffect(playerskillDef->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(0.45f, 0.15f, 0.05f, 0.20f), D3DXVECTOR2(6.0f, 6.0f), 10);


			}

			D3DXVECTOR2	size;
			size.x = 8.0f + (playerskillDef->pos.y - 4.0f) * 0.05f;
			if(size.x < 8.0f)
			{
				size.x = 8.0f;
			}
			size.y = 8.0f + (playerskillDef->pos.y - 4.0f) * 0.05f;
			if(size.y < 8.0f)
			{
				size.y = 8.0f;
			}

			SetVertexShadow(playerskillDef->nIdxShadow, size);

			float colA = (200.0f - (playerskillDef->pos.y - 4.0f)) / 400.0f;
			if(colA < 0.0f)
			{
				colA = 0.0f;
			}
			SetColorShadow(playerskillDef->nIdxShadow, D3DXCOLOR(1.0f, 1.0f, 1.0f, colA));

			if (playerskillDef->pos.x < (SKILLDEF_SIZE_X / 2) - FIELD_SCL_MAX_X)
			{
				DeletePlayerSkillDef(i);
			}
			if (playerskillDef->pos.x > FIELD_SCL_MAX_X - (SKILLDEF_SIZE_X / 2))
			{
				DeletePlayerSkillDef(i);
			}
			if (playerskillDef->pos.z > FIELD_SCL_MAX_Z)
			{
				DeletePlayerSkillDef(i);
			}
			if (playerskillDef->pos.z < (SKILLDEF_SIZE_Y / 2) - FIELD_SCL_MAX_Z)
			{
				DeletePlayerSkillDef(i);
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayerSkillDef(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView,mtxscl,mtxTranslate;
	PLAYER_SKILLDEF *playerskillDef = playerskillDefWk;

	// ���C�e�B���O�𖳌���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���e�X�g��L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

 for(int i = 0; i < MAX_SKILLDEF; i++, playerskillDef++)
	{
		if(playerskillDef->bUse)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&playerskillDef->world);

			// �r���[�}�g���b�N�X���擾
			mtxView = GetMtxView();

			playerskillDef->world._11 = mtxView._11;
			playerskillDef->world._12 = mtxView._21;
			playerskillDef->world._13 = mtxView._31;
			playerskillDef->world._21 = mtxView._12;
			playerskillDef->world._22 = mtxView._22;
			playerskillDef->world._23 = mtxView._32;
			playerskillDef->world._31 = mtxView._13;
			playerskillDef->world._32 = mtxView._23;
			playerskillDef->world._33 = mtxView._33;

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxscl, playerskillDef->scl.x, playerskillDef->scl.y, playerskillDef->scl.z);
			D3DXMatrixMultiply(&playerskillDef->world, &playerskillDef->world, &mtxscl);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, playerskillDef->pos.x, playerskillDef->pos.y, playerskillDef->pos.z);
			D3DXMatrixMultiply(&playerskillDef->world, &playerskillDef->world, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &playerskillDef->world);

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, g_pD3DVtxBuffPlayerSkillDef, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pD3DTexturePlayerSkillDef);

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
HRESULT MakeVertexPlayerSkillDef(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
    if( FAILED( pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * MAX_SKILLDEF,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
												D3DUSAGE_WRITEONLY,							// ���_�o�b�t�@�̎g�p�@�@
												FVF_VERTEX_3D,								// �g�p���钸�_�t�H�[�}�b�g
												D3DPOOL_MANAGED,							// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
												&g_pD3DVtxBuffPlayerSkillDef,						// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
												NULL)))										// NULL�ɐݒ�
	{
        return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffPlayerSkillDef->Lock(0, 0, (void**)&pVtx, 0);

		for(int i = 0; i < MAX_SKILLDEF; i++, pVtx += 4)
		{
			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(-SKILLDEF_SIZE_X / 2, -SKILLDEF_SIZE_Y / 2, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(SKILLDEF_SIZE_X / 2, -SKILLDEF_SIZE_Y / 2, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(-SKILLDEF_SIZE_X / 2, SKILLDEF_SIZE_Y / 2, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(SKILLDEF_SIZE_X / 2, SKILLDEF_SIZE_Y / 2, 0.0f);

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
		g_pD3DVtxBuffPlayerSkillDef->Unlock();
	}

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexPlayerSkillDef(int nIdxPlayerSkillDef, D3DXVECTOR2 size)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffPlayerSkillDef->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxPlayerSkillDef * 4);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(-size.x / 2, -size.y / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-size.x / 2, size.y / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(size.x / 2, -size.y / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(size.x / 2, size.y / 2, 0.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffPlayerSkillDef->Unlock();
	}
}

//=============================================================================
// �e�̐ݒ�
//=============================================================================
int SetPlayerSkillDef(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 size, int timer)
{
	PLAYER_SKILLDEF *playerskillDef = playerskillDefWk;

	int nIdxPlayerSkillDef = -1;

	playerskillDef = GetPlayerSkillDef(0);
 for(int i = 0; i < MAX_SKILLDEF; i++, playerskillDef++)
	{
		if(!playerskillDef->bUse)
		{

			playerskillDef->pos = pos;
			playerskillDef->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			playerskillDef->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			playerskillDef->move = move;
			playerskillDef->size.x = size.x;
			playerskillDef->size.y = size.y;
			playerskillDef->timer = timer;
			playerskillDef->cnt --;
			playerskillDef->bUse = true;

			// �e�̐ݒ�
			playerskillDef->nIdxShadow = CreateShadow(pos, D3DXVECTOR2(8.0f, 8.0f));		// �e�̐ݒ�

			// ���_���W�̐ݒ�
			SetVertexPlayerSkillDef(i, size);

			nIdxPlayerSkillDef = i;

			break;
		}
	}

	return nIdxPlayerSkillDef;
}

//=============================================================================
// �e�̍폜
//=============================================================================
void DeletePlayerSkillDef(int nIdxPlayerSkillDef)
{
	if(nIdxPlayerSkillDef >= 0 && nIdxPlayerSkillDef < MAX_SKILLDEF)
	{
		ReleaseShadow(playerskillDefWk[nIdxPlayerSkillDef].nIdxShadow);
		playerskillDefWk[nIdxPlayerSkillDef].bUse = false;
	}
}


PLAYER_SKILLDEF *GetPlayerSkillDef(int no)
{
	return(&playerskillDefWk[no]);
}
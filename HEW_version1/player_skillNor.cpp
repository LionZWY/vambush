//=============================================================================
//
// �e���� [playerNorSk.cpp]
// Author : �镶��
// �v���O�����쐬�� : 2018/3/09
//=============================================================================
#include "player_skillNor.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "effect.h"
#include "player.h"
#include "field.h"
#include "checkhit.h"
#include "enemy.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexPlayerNorSkill(LPDIRECT3DDEVICE9 pDevice);
void SetVertexPlayerNorSkill(int nIdxNorSkill, D3DXVECTOR2 size);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTexturePlayerNorSkill1 = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffPlayerNorSkill	= NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

PLAYER_NORSKILL					playernorSkillWk[MAX_NORSKILL];			// �e���[�N
int						playernorSkillType;
LPDIRECT3DTEXTURE9		TexturePlayerPlayerNorSkill;
//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayerNorSkill(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER_NORSKILL *playernorSkill = playernorSkillWk;

	// ���_���̍쐬
	MakeVertexPlayerNorSkill(pDevice);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
								TEXTURE_NORSKILL_PLAYER,				// �t�@�C���̖��O
								&g_pD3DTexturePlayerNorSkill1);	// �ǂݍ��ރ������[

													

	for(int i = 0; i < MAX_NORSKILL; i++, playernorSkill++)
	{
		playernorSkill->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		playernorSkill->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		playernorSkill->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		playernorSkill->move = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		playernorSkill->size.x = NORSKILL_SIZE_X;
		playernorSkill->size.y = NORSKILL_SIZE_Y;
		playernorSkill->timer = 0;
		playernorSkill->cnt = 3;
		playernorSkill->bUse = false;
		playernorSkill->Track = true;
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayerNorSkill(void)
{
	if(g_pD3DTexturePlayerNorSkill1 != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTexturePlayerNorSkill1->Release();
		g_pD3DTexturePlayerNorSkill1 = NULL;
	}

	if(g_pD3DVtxBuffPlayerNorSkill != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffPlayerNorSkill->Release();
		g_pD3DVtxBuffPlayerNorSkill = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayerNorSkill(void)
{
	D3DXVECTOR3 rotCamera;
	PLAYER_NORSKILL *playernorSkill = playernorSkillWk;
	PLAYER *player = GetPlayer();
	ENEMY *enemy = GetEnemy();


	// �J�����̉�]���擾
	rotCamera = GetRotCamera();

 for(int i = 0; i < MAX_NORSKILL; i++, playernorSkill++)
	{
		if(playernorSkill->bUse)
		{

			if (playernorSkill->Track)
			{

				playernorSkill->rot.y = atan2(enemy->pos.x - playernorSkill->pos.x, enemy->pos.z - playernorSkill->pos.z);
				playernorSkill->rot.y -= D3DX_PI;
				playernorSkill->move.x = -sinf(playernorSkill->rot.y)*3.0f;
				playernorSkill->move.z = -cosf(playernorSkill->rot.y)*3.0f;
				if (CheckHitBC(playernorSkill->pos, enemy->pos, 2.0f, 20.0f))
				{
					playernorSkill->Track = false;

				}
		
			}
			else if (playernorSkill->Track == false)
			{
				playernorSkill->move.x = -sinf(playernorSkill->rot.y)*3.0f;
				playernorSkill->move.z = -cosf(playernorSkill->rot.y)*3.0f;
			}

			playernorSkill->pos.x += playernorSkill->move.x;
			playernorSkill->pos.z += playernorSkill->move.z;

			playernorSkill->timer--;
			if(playernorSkill->timer <= 0)
			{
				ReleaseShadow(playernorSkill->nIdxShadow);
				playernorSkill->bUse = false;
			}
			else
			{
				// �e�̈ʒu�ݒ�
				SetPositionShadow(playernorSkill->nIdxShadow, D3DXVECTOR3(playernorSkill->pos.x, 0.1f, playernorSkill->pos.z));


				// �G�t�F�N�g�̐ݒ�
				SetEffect(playernorSkill->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(0.85f, 0.05f, 0.15f, 0.50f), D3DXVECTOR2(8.0f, 8.0f), 10);
				SetEffect(playernorSkill->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(0.65f, 0.10f, 0.10f, 0.30f), D3DXVECTOR2(6.0f, 6.0f), 10);
				SetEffect(playernorSkill->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(0.45f, 0.15f, 0.05f, 0.20f), D3DXVECTOR2(3.0f, 3.0f), 10);


			}

			D3DXVECTOR2	size;
			size.x = 8.0f + (playernorSkill->pos.y - 4.0f) * 0.05f;
			if(size.x < 8.0f)
			{
				size.x = 8.0f;
			}
			size.y = 8.0f + (playernorSkill->pos.y - 4.0f) * 0.05f;
			if(size.y < 8.0f)
			{
				size.y = 8.0f;
			}

			SetVertexShadow(playernorSkill->nIdxShadow, size);

			float colA = (200.0f - (playernorSkill->pos.y - 4.0f)) / 400.0f;
			if(colA < 0.0f)
			{
				colA = 0.0f;
			}
			SetColorShadow(playernorSkill->nIdxShadow, D3DXCOLOR(1.0f, 1.0f, 1.0f, colA));

			if (playernorSkill->pos.x < (NORSKILL_SIZE_X / 2) - FIELD_SCL_MAX_X)
			{
				DeletePlayerNorSkill(i);
			}
			if (playernorSkill->pos.x > FIELD_SCL_MAX_X - (NORSKILL_SIZE_X / 2))
			{
				DeletePlayerNorSkill(i);
			}
			if (playernorSkill->pos.z > FIELD_SCL_MAX_Z)
			{
				DeletePlayerNorSkill(i);
			}
			if (playernorSkill->pos.z < (NORSKILL_SIZE_Y / 2) - FIELD_SCL_MAX_Z)
			{
				DeletePlayerNorSkill(i);
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayerNorSkill(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView,mtxscl,mtxTranslate;
	PLAYER_NORSKILL *playernorSkill = playernorSkillWk;

	// ���C�e�B���O�𖳌���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���e�X�g��L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

 for(int i = 0; i < MAX_NORSKILL; i++, playernorSkill++)
	{
		if(playernorSkill->bUse)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&playernorSkill->world);

			// �r���[�}�g���b�N�X���擾
			mtxView = GetMtxView();

			playernorSkill->world._11 = mtxView._11;
			playernorSkill->world._12 = mtxView._21;
			playernorSkill->world._13 = mtxView._31;
			playernorSkill->world._21 = mtxView._12;
			playernorSkill->world._22 = mtxView._22;
			playernorSkill->world._23 = mtxView._32;
			playernorSkill->world._31 = mtxView._13;
			playernorSkill->world._32 = mtxView._23;
			playernorSkill->world._33 = mtxView._33;

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxscl, playernorSkill->scl.x, playernorSkill->scl.y, playernorSkill->scl.z);
			D3DXMatrixMultiply(&playernorSkill->world, &playernorSkill->world, &mtxscl);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, playernorSkill->pos.x, playernorSkill->pos.y, playernorSkill->pos.z);
			D3DXMatrixMultiply(&playernorSkill->world, &playernorSkill->world, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &playernorSkill->world);

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, g_pD3DVtxBuffPlayerNorSkill, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, TexturePlayerPlayerNorSkill);

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
HRESULT MakeVertexPlayerNorSkill(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
    if( FAILED( pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * MAX_NORSKILL,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
												D3DUSAGE_WRITEONLY,							// ���_�o�b�t�@�̎g�p�@�@
												FVF_VERTEX_3D,								// �g�p���钸�_�t�H�[�}�b�g
												D3DPOOL_MANAGED,							// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
												&g_pD3DVtxBuffPlayerNorSkill,						// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
												NULL)))										// NULL�ɐݒ�
	{
        return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffPlayerNorSkill->Lock(0, 0, (void**)&pVtx, 0);

		for(int i = 0; i < MAX_NORSKILL; i++, pVtx += 4)
		{
			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(-NORSKILL_SIZE_X / 2, -NORSKILL_SIZE_Y / 2, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(NORSKILL_SIZE_X / 2, -NORSKILL_SIZE_Y / 2, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(-NORSKILL_SIZE_X / 2, NORSKILL_SIZE_Y / 2, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(NORSKILL_SIZE_X / 2, NORSKILL_SIZE_Y / 2, 0.0f);

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
		g_pD3DVtxBuffPlayerNorSkill->Unlock();
	}

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexPlayerNorSkill(int nIdxPlayerNorSkill, D3DXVECTOR2 size)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffPlayerNorSkill->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxPlayerNorSkill * 4);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(-size.x / 2, -size.y / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-size.x / 2, size.y / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(size.x / 2, -size.y / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(size.x / 2, size.y / 2, 0.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffPlayerNorSkill->Unlock();
	}
}

//=============================================================================
// �e�̐ݒ�
//=============================================================================
int SetPlayerNorSkill(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 size, int timer,int type)
{
	PLAYER_NORSKILL *playernorSkill = playernorSkillWk;
	playernorSkillType = type;

	switch (type)
	{
	case PB_TYPE_NORMAL:
		TexturePlayerPlayerNorSkill = g_pD3DTexturePlayerNorSkill1;
		break;
	}

	int nIdxPlayerNorSkill = -1;

	playernorSkill = GetPlayerNorSkill(0);
 for(int i = 0; i < MAX_NORSKILL; i++, playernorSkill++)
	{
		if(!playernorSkill->bUse)
		{

			playernorSkill->pos = pos;
			playernorSkill->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			playernorSkill->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			playernorSkill->move = move;
			playernorSkill->size.x = size.x;
			playernorSkill->size.y = size.y;
			playernorSkill->timer = timer;
			playernorSkill->cnt --;
			playernorSkill->bUse = true;
			playernorSkill->Track = true;

			// �e�̐ݒ�
			playernorSkill->nIdxShadow = CreateShadow(pos, D3DXVECTOR2(8.0f, 8.0f));		// �e�̐ݒ�

			// ���_���W�̐ݒ�
			SetVertexPlayerNorSkill(i, size);

			nIdxPlayerNorSkill = i;

			break;
		}
	}

	return nIdxPlayerNorSkill;
}

//=============================================================================
// �e�̍폜
//=============================================================================
void DeletePlayerNorSkill(int nIdxPlayerNorSkill)
{
	if(nIdxPlayerNorSkill >= 0 && nIdxPlayerNorSkill < MAX_NORSKILL)
	{
		ReleaseShadow(playernorSkillWk[nIdxPlayerNorSkill].nIdxShadow);
		playernorSkillWk[nIdxPlayerNorSkill].bUse = false;
	}
}

int GetPlayerNorSkillType(void)
{
	return playernorSkillType;
}

PLAYER_NORSKILL *GetPlayerNorSkill(int no)
{
	return(&playernorSkillWk[no]);
}


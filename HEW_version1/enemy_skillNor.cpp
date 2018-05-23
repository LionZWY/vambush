//=============================================================================
//
// ����e03���� [enemyNorSk.cpp]
// Author : �镶��
// �v���O�����쐬�� : 2018/3/09
//=============================================================================
#include "enemy_skillNor.h"
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
HRESULT MakeVertexEnemyNorSkill(LPDIRECT3DDEVICE9 pDevice);
void SetVertexEnemyNorSkill(int nIdxNorSkill, D3DXVECTOR2 size);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureEnemyNorSkill1 = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffEnemyNorSkill	= NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

ENEMY_NORSKILL			enemynorSkillWk[MAX_NORSKILL];			// �e���[�N
int						enemynorSkillType;						// �e�̃^�C�v
LPDIRECT3DTEXTURE9		TextureEnemyEnemyNorSkill;				// �e�N�X�`���ւ̃|�C���^
//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemyNorSkill(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY_NORSKILL *enemynorSkill = enemynorSkillWk;

	// ���_���̍쐬
	MakeVertexEnemyNorSkill(pDevice);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
								TEXTURE_NORSKILL_ENEMY,				// �t�@�C���̖��O
								&g_pD3DTextureEnemyNorSkill1);	// �ǂݍ��ރ������[

													

	for(int i = 0; i < MAX_NORSKILL; i++, enemynorSkill++)
	{
		enemynorSkill->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		enemynorSkill->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		enemynorSkill->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		enemynorSkill->move = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		enemynorSkill->size.x = NORSKILL_SIZE_X;
		enemynorSkill->size.y = NORSKILL_SIZE_Y;
		enemynorSkill->timer = 0;
		enemynorSkill->cnt=3;
		enemynorSkill->bUse = false;
		enemynorSkill->Track = true;
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemyNorSkill(void)
{
	if(g_pD3DTextureEnemyNorSkill1 != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureEnemyNorSkill1->Release();
		g_pD3DTextureEnemyNorSkill1 = NULL;
	}

	if(g_pD3DVtxBuffEnemyNorSkill != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffEnemyNorSkill->Release();
		g_pD3DVtxBuffEnemyNorSkill = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemyNorSkill(void)
{
	D3DXVECTOR3 rotCamera;
	ENEMY_NORSKILL *enemynorSkill = enemynorSkillWk;
	PLAYER *player = GetPlayer();
	ENEMY *enemy = GetEnemy();


	// �J�����̉�]���擾
	rotCamera = GetRotCamera();

 for(int i = 0; i < MAX_NORSKILL; i++, enemynorSkill++)
	{
		if(enemynorSkill->bUse)
		{

			if (enemynorSkill->Track)
			{

				enemynorSkill->rot.y = atan2(player->pos.x - enemynorSkill->pos.x, player->pos.z - enemynorSkill->pos.z);
				enemynorSkill->rot.y -= D3DX_PI;
				enemynorSkill->move.x = -sinf(enemynorSkill->rot.y)*3.0f;
				enemynorSkill->move.z = -cosf(enemynorSkill->rot.y)*3.0f;
				if (CheckHitBC(enemynorSkill->pos, player->pos, 2.0f, 20.0f))
				{
					enemynorSkill->Track = false;

				}
		
			}
			else if (enemynorSkill->Track == false)
			{
				enemynorSkill->move.x = -sinf(enemynorSkill->rot.y)*3.0f;
				enemynorSkill->move.z = -cosf(enemynorSkill->rot.y)*3.0f;
			}

			enemynorSkill->pos.x += enemynorSkill->move.x;
			enemynorSkill->pos.z += enemynorSkill->move.z;

			enemynorSkill->timer--;
			if(enemynorSkill->timer <= 0)
			{
				ReleaseShadow(enemynorSkill->nIdxShadow);
				enemynorSkill->bUse = false;
			}
			else
			{
				// �e�̈ʒu�ݒ�
				SetPositionShadow(enemynorSkill->nIdxShadow, D3DXVECTOR3(enemynorSkill->pos.x, 0.1f, enemynorSkill->pos.z));


				// �G�t�F�N�g�̐ݒ�
				SetEffect(enemynorSkill->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(0.65f, 0.05f, 0.85f, 0.50f), D3DXVECTOR2(8.0f, 8.0f), 10);
				SetEffect(enemynorSkill->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(0.05f, 0.85f, 0.65f, 0.30f), D3DXVECTOR2(6.0f, 6.0f), 10);
				SetEffect(enemynorSkill->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(0.05f, 0.45f, 0.45f, 0.20f), D3DXVECTOR2(3.0f, 3.0f), 10);


			}

			D3DXVECTOR2	size;
			size.x = 8.0f + (enemynorSkill->pos.y - 4.0f) * 0.05f;
			if(size.x < 8.0f)
			{
				size.x = 8.0f;
			}
			size.y = 8.0f + (enemynorSkill->pos.y - 4.0f) * 0.05f;
			if(size.y < 8.0f)
			{
				size.y = 8.0f;
			}

			SetVertexShadow(enemynorSkill->nIdxShadow, size);

			float colA = (200.0f - (enemynorSkill->pos.y - 4.0f)) / 400.0f;
			if(colA < 0.0f)
			{
				colA = 0.0f;
			}
			SetColorShadow(enemynorSkill->nIdxShadow, D3DXCOLOR(1.0f, 1.0f, 1.0f, colA));

			if (enemynorSkill->pos.x < (NORSKILL_SIZE_X / 2) - FIELD_SCL_MAX_X)
			{
				DeleteEnemyNorSkill(i);
			}
			if (enemynorSkill->pos.x > FIELD_SCL_MAX_X - (NORSKILL_SIZE_X / 2))
			{
				DeleteEnemyNorSkill(i);
			}
			if (enemynorSkill->pos.z > FIELD_SCL_MAX_Z)
			{
				DeleteEnemyNorSkill(i);
			}
			if (enemynorSkill->pos.z < (NORSKILL_SIZE_Y / 2) - FIELD_SCL_MAX_Z)
			{
				DeleteEnemyNorSkill(i);
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemyNorSkill(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView,mtxscl,mtxTranslate;
	ENEMY_NORSKILL *enemynorSkill = enemynorSkillWk;

	// ���C�e�B���O�𖳌���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���e�X�g��L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

 for(int i = 0; i < MAX_NORSKILL; i++, enemynorSkill++)
	{
		if(enemynorSkill->bUse)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&enemynorSkill->world);

			// �r���[�}�g���b�N�X���擾
			mtxView = GetMtxView();

			enemynorSkill->world._11 = mtxView._11;
			enemynorSkill->world._12 = mtxView._21;
			enemynorSkill->world._13 = mtxView._31;
			enemynorSkill->world._21 = mtxView._12;
			enemynorSkill->world._22 = mtxView._22;
			enemynorSkill->world._23 = mtxView._32;
			enemynorSkill->world._31 = mtxView._13;
			enemynorSkill->world._32 = mtxView._23;
			enemynorSkill->world._33 = mtxView._33;

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxscl, enemynorSkill->scl.x, enemynorSkill->scl.y, enemynorSkill->scl.z);
			D3DXMatrixMultiply(&enemynorSkill->world, &enemynorSkill->world, &mtxscl);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, enemynorSkill->pos.x, enemynorSkill->pos.y, enemynorSkill->pos.z);
			D3DXMatrixMultiply(&enemynorSkill->world, &enemynorSkill->world, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &enemynorSkill->world);

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, g_pD3DVtxBuffEnemyNorSkill, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, TextureEnemyEnemyNorSkill);

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
HRESULT MakeVertexEnemyNorSkill(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
    if( FAILED( pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * MAX_NORSKILL,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
												D3DUSAGE_WRITEONLY,							// ���_�o�b�t�@�̎g�p�@�@
												FVF_VERTEX_3D,								// �g�p���钸�_�t�H�[�}�b�g
												D3DPOOL_MANAGED,							// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
												&g_pD3DVtxBuffEnemyNorSkill,						// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
												NULL)))										// NULL�ɐݒ�
	{
        return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffEnemyNorSkill->Lock(0, 0, (void**)&pVtx, 0);

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
		g_pD3DVtxBuffEnemyNorSkill->Unlock();
	}

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexEnemyNorSkill(int nIdxEnemyNorSkill, D3DXVECTOR2 size)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffEnemyNorSkill->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxEnemyNorSkill * 4);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(-size.x / 2, -size.y / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-size.x / 2, size.y / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(size.x / 2, -size.y / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(size.x / 2, size.y / 2, 0.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffEnemyNorSkill->Unlock();
	}
}

//=============================================================================
// �e�̐ݒ�
//=============================================================================
int SetEnemyNorSkill(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 size, int timer,int type)
{
	ENEMY_NORSKILL *enemynorSkill = enemynorSkillWk;
	enemynorSkillType = type;

	switch (type)
	{
	case EB_TYPE_NORMAL:
		TextureEnemyEnemyNorSkill = g_pD3DTextureEnemyNorSkill1;
		break;
	}

	int nIdxEnemyNorSkill = -1;

	enemynorSkill = GetEnemyNorSkill(0);
 for(int i = 0; i < MAX_NORSKILL; i++, enemynorSkill++)
	{
		if(!enemynorSkill->bUse)
		{

			enemynorSkill->pos = pos;
			enemynorSkill->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			enemynorSkill->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			enemynorSkill->move = move;
			enemynorSkill->size.x = size.x;
			enemynorSkill->size.y = size.y;
			enemynorSkill->timer = timer;
			enemynorSkill->cnt--;
			enemynorSkill->bUse = true;
			enemynorSkill->Track = true;

			// �e�̐ݒ�
			enemynorSkill->nIdxShadow = CreateShadow(pos, D3DXVECTOR2(8.0f, 8.0f));		// �e�̐ݒ�

			// ���_���W�̐ݒ�
			SetVertexEnemyNorSkill(i, size);

			nIdxEnemyNorSkill = i;

			break;
		}
	}

	return nIdxEnemyNorSkill;
}

//=============================================================================
// �e�̍폜
//=============================================================================
void DeleteEnemyNorSkill(int nIdxEnemyNorSkill)
{
	if(nIdxEnemyNorSkill >= 0 && nIdxEnemyNorSkill < MAX_NORSKILL)
	{
		ReleaseShadow(enemynorSkillWk[nIdxEnemyNorSkill].nIdxShadow);
		enemynorSkillWk[nIdxEnemyNorSkill].bUse = false;
	}
}

int GetEnemyNorSkillType(void)
{
	return enemynorSkillType;
}

ENEMY_NORSKILL *GetEnemyNorSkill(int no)
{
	return(&enemynorSkillWk[no]);
}


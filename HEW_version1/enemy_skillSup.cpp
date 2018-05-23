//=============================================================================
//
// ����e02���� [enemySupSk.cpp]
// Author : �镶��
// �v���O�����쐬�� : 2018/3/09
//=============================================================================
#include "enemy_skillSup.h"
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
HRESULT MakeVertexEnemySupSkill(LPDIRECT3DDEVICE9 pDevice);
void SetVertexEnemySupSkill(int nIdxSupSkill, D3DXVECTOR2 size);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureEnemySupSkill = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffEnemySupSkill	= NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

ENEMY_SUPSKILL			enemysupSkillWk[MAX_SUPSKILL];			// �e���[�N
LPDIRECT3DTEXTURE9		TextureEnemyEnemySupSkill;
//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemySupSkill(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY_SUPSKILL *enemysupSkill = enemysupSkillWk;

	// ���_���̍쐬
	MakeVertexEnemySupSkill(pDevice);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
								TEXTURE_SUPSKILL_ENEMY,				// �t�@�C���̖��O
								&g_pD3DTextureEnemySupSkill);	// �ǂݍ��ރ������[

													

	for(int i = 0; i < MAX_SUPSKILL; i++, enemysupSkill++)
	{
		enemysupSkill->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		enemysupSkill->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		enemysupSkill->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		enemysupSkill->move = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		enemysupSkill->size.x = SUPSKILL_SIZE_X;
		enemysupSkill->size.y = SUPSKILL_SIZE_Y;
		enemysupSkill->timer = 0;
		enemysupSkill->bUse = false;
		enemysupSkill->Track = true;
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemySupSkill(void)
{
	if(g_pD3DTextureEnemySupSkill != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureEnemySupSkill->Release();
		g_pD3DTextureEnemySupSkill = NULL;
	}

	if(g_pD3DVtxBuffEnemySupSkill != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffEnemySupSkill->Release();
		g_pD3DVtxBuffEnemySupSkill = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemySupSkill(void)
{
	D3DXVECTOR3 rotCamera;
	ENEMY_SUPSKILL *enemysupSkill = enemysupSkillWk;
	PLAYER *player = GetPlayer();
	ENEMY *enemy = GetEnemy();


	// �J�����̉�]���擾
	rotCamera = GetRotCamera();

 for(int i = 0; i < MAX_SUPSKILL; i++, enemysupSkill++)
	{
		if(enemysupSkill->bUse)
		{

			if (enemysupSkill->Track)
			{

				enemysupSkill->rot.y = atan2(player->pos.x - enemysupSkill->pos.x, player->pos.z - enemysupSkill->pos.z);
				enemysupSkill->rot.y -= D3DX_PI;
				enemysupSkill->move.x = -sinf(enemysupSkill->rot.y)*4.0f;
				enemysupSkill->move.z = -cosf(enemysupSkill->rot.y)*4.0f;
				if (CheckHitBC(enemysupSkill->pos, player->pos, 2.0f, 30.0f))
				{
					enemysupSkill->Track = false;

				}
		
			}
			else if (enemysupSkill->Track == false)
			{
				enemysupSkill->move.x = -sinf(enemysupSkill->rot.y)*4.0f;
				enemysupSkill->move.z = -cosf(enemysupSkill->rot.y)*4.0f;
			}

			enemysupSkill->pos.x += enemysupSkill->move.x;
			enemysupSkill->pos.z += enemysupSkill->move.z;

			enemysupSkill->timer--;
			if(enemysupSkill->timer <= 0)
			{
				ReleaseShadow(enemysupSkill->nIdxShadow);
				enemysupSkill->bUse = false;
			}
			else
			{
				// �e�̈ʒu�ݒ�
				SetPositionShadow(enemysupSkill->nIdxShadow, D3DXVECTOR3(enemysupSkill->pos.x, 0.1f, enemysupSkill->pos.z));


				// �G�t�F�N�g�̐ݒ�
				SetEffect(enemysupSkill->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(0.65f, 0.05f, 0.85f, 0.50f), D3DXVECTOR2(15.0f, 15.0f), 10);
				SetEffect(enemysupSkill->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(0.05f, 0.85f, 0.65f, 0.30f), D3DXVECTOR2(8.0f, 8.0f), 10);
				SetEffect(enemysupSkill->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(0.05f, 0.45f, 0.45f, 0.20f), D3DXVECTOR2(4.0f, 4.0f), 10);


			}

			D3DXVECTOR2	size;
			size.x = 8.0f + (enemysupSkill->pos.y - 4.0f) * 0.05f;
			if(size.x < 8.0f)
			{
				size.x = 8.0f;
			}
			size.y = 8.0f + (enemysupSkill->pos.y - 4.0f) * 0.05f;
			if(size.y < 8.0f)
			{
				size.y = 8.0f;
			}

			SetVertexShadow(enemysupSkill->nIdxShadow, size);

			float colA = (200.0f - (enemysupSkill->pos.y - 4.0f)) / 400.0f;
			if(colA < 0.0f)
			{
				colA = 0.0f;
			}
			SetColorShadow(enemysupSkill->nIdxShadow, D3DXCOLOR(1.0f, 1.0f, 1.0f, colA));

			if (enemysupSkill->pos.x < (SUPSKILL_SIZE_X / 2) - FIELD_SCL_MAX_X)
			{
				DeleteEnemySupSkill(i);
			}
			if (enemysupSkill->pos.x > FIELD_SCL_MAX_X - (SUPSKILL_SIZE_X / 2))
			{
				DeleteEnemySupSkill(i);
			}
			if (enemysupSkill->pos.z > FIELD_SCL_MAX_Z)
			{
				DeleteEnemySupSkill(i);
			}
			if (enemysupSkill->pos.z < (SUPSKILL_SIZE_Y / 2) - FIELD_SCL_MAX_Z)
			{
				DeleteEnemySupSkill(i);
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemySupSkill(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView,mtxscl,mtxTranslate;
	ENEMY_SUPSKILL *enemysupSkill = enemysupSkillWk;

	// ���C�e�B���O�𖳌���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���e�X�g��L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

 for(int i = 0; i < MAX_SUPSKILL; i++, enemysupSkill++)
	{
		if(enemysupSkill->bUse)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&enemysupSkill->world);

			// �r���[�}�g���b�N�X���擾
			mtxView = GetMtxView();

			enemysupSkill->world._11 = mtxView._11;
			enemysupSkill->world._12 = mtxView._21;
			enemysupSkill->world._13 = mtxView._31;
			enemysupSkill->world._21 = mtxView._12;
			enemysupSkill->world._22 = mtxView._22;
			enemysupSkill->world._23 = mtxView._32;
			enemysupSkill->world._31 = mtxView._13;
			enemysupSkill->world._32 = mtxView._23;
			enemysupSkill->world._33 = mtxView._33;

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxscl, enemysupSkill->scl.x, enemysupSkill->scl.y, enemysupSkill->scl.z);
			D3DXMatrixMultiply(&enemysupSkill->world, &enemysupSkill->world, &mtxscl);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, enemysupSkill->pos.x, enemysupSkill->pos.y, enemysupSkill->pos.z);
			D3DXMatrixMultiply(&enemysupSkill->world, &enemysupSkill->world, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &enemysupSkill->world);

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, g_pD3DVtxBuffEnemySupSkill, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pD3DTextureEnemySupSkill);

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
HRESULT MakeVertexEnemySupSkill(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
    if( FAILED( pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * MAX_SUPSKILL,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
												D3DUSAGE_WRITEONLY,							// ���_�o�b�t�@�̎g�p�@�@
												FVF_VERTEX_3D,								// �g�p���钸�_�t�H�[�}�b�g
												D3DPOOL_MANAGED,							// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
												&g_pD3DVtxBuffEnemySupSkill,						// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
												NULL)))										// NULL�ɐݒ�
	{
        return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffEnemySupSkill->Lock(0, 0, (void**)&pVtx, 0);

		for(int i = 0; i < MAX_SUPSKILL; i++, pVtx += 4)
		{
			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(-SUPSKILL_SIZE_X / 2, -SUPSKILL_SIZE_Y / 2, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(SUPSKILL_SIZE_X / 2, -SUPSKILL_SIZE_Y / 2, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(-SUPSKILL_SIZE_X / 2, SUPSKILL_SIZE_Y / 2, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(SUPSKILL_SIZE_X / 2, SUPSKILL_SIZE_Y / 2, 0.0f);

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
		g_pD3DVtxBuffEnemySupSkill->Unlock();
	}

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexEnemySupSkill(int nIdxEnemySupSkill, D3DXVECTOR2 size)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffEnemySupSkill->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxEnemySupSkill * 4);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(-size.x / 2, -size.y / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-size.x / 2, size.y / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(size.x / 2, -size.y / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(size.x / 2, size.y / 2, 0.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffEnemySupSkill->Unlock();
	}
}

//=============================================================================
// �e�̐ݒ�
//=============================================================================
int SetEnemySupSkill(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 size, int timer)
{
	ENEMY_SUPSKILL *enemysupSkill = enemysupSkillWk;

	int nIdxEnemySupSkill = -1;

	enemysupSkill = GetEnemySupSkill(0);
 for(int i = 0; i < MAX_SUPSKILL; i++, enemysupSkill++)
	{
		if(!enemysupSkill->bUse)
		{

			enemysupSkill->pos = pos;
			enemysupSkill->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			enemysupSkill->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			enemysupSkill->move = move;
			enemysupSkill->size.x = size.x;
			enemysupSkill->size.y = size.y;
			enemysupSkill->timer = timer;
			enemysupSkill->bUse = true;
			enemysupSkill->Track = true;

			// �e�̐ݒ�
			enemysupSkill->nIdxShadow = CreateShadow(pos, D3DXVECTOR2(8.0f, 8.0f));		// �e�̐ݒ�

			// ���_���W�̐ݒ�
			SetVertexEnemySupSkill(i, size);

			nIdxEnemySupSkill = i;

			break;
		}
	}

	return nIdxEnemySupSkill;
}

//=============================================================================
// �e�̍폜
//=============================================================================
void DeleteEnemySupSkill(int nIdxEnemySupSkill)
{
	if(nIdxEnemySupSkill >= 0 && nIdxEnemySupSkill < MAX_SUPSKILL)
	{
		ReleaseShadow(enemysupSkillWk[nIdxEnemySupSkill].nIdxShadow);
		enemysupSkillWk[nIdxEnemySupSkill].bUse = false;
	}
}

ENEMY_SUPSKILL *GetEnemySupSkill(int no)
{
	return(&enemysupSkillWk[no]);
}


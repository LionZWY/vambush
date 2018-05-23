//=============================================================================
//
// ����e01���� [enemyskillDef.cpp]
// Author : �镶��
// �v���O�����쐬�� : 2018/3/09
//=============================================================================
#include "enemy_skillDef.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "effect.h"
#include "enemy.h"
#include "field.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexEnemySkillDef(LPDIRECT3DDEVICE9 pDevice);
void SetVertexEnemySkillDef(int nIdxSkillDef, D3DXVECTOR2 size);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureEnemySkillDef = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffEnemySkillDef	= NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

ENEMY_SKILLDEF					enemyskillDefWk[MAX_SKILLDEF];			// �e���[�N
//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemySkillDef(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY_SKILLDEF *enemyskillDef = enemyskillDefWk;

	// ���_���̍쐬
	MakeVertexEnemySkillDef(pDevice);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
								TEXTURE_SKILLDEF_ENEMY,				// �t�@�C���̖��O
								&g_pD3DTextureEnemySkillDef);	// �ǂݍ��ރ������[

													

	for(int i = 0; i < MAX_SKILLDEF; i++, enemyskillDef++)
	{
		enemyskillDef->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		enemyskillDef->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		enemyskillDef->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		enemyskillDef->move = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		enemyskillDef->size.x = SKILLDEF_SIZE_X;
		enemyskillDef->size.y = SKILLDEF_SIZE_Y;
		enemyskillDef->timer = 0;
		enemyskillDef->cnt = 3;
		enemyskillDef->bUse = false;
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemySkillDef(void)
{
	if(g_pD3DTextureEnemySkillDef != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureEnemySkillDef->Release();
		g_pD3DTextureEnemySkillDef = NULL;
	}

	if(g_pD3DVtxBuffEnemySkillDef != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffEnemySkillDef->Release();
		g_pD3DVtxBuffEnemySkillDef = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemySkillDef(void)
{
	D3DXVECTOR3 rotCamera;
	ENEMY_SKILLDEF *enemyskillDef = enemyskillDefWk;


	// �J�����̉�]���擾
	rotCamera = GetRotCamera();

 for(int i = 0; i < MAX_SKILLDEF; i++, enemyskillDef++)
	{
		if(enemyskillDef->bUse)
		{
			enemyskillDef->pos.x += enemyskillDef->move.x;
			enemyskillDef->pos.z += enemyskillDef->move.z;

			enemyskillDef->timer--;
			if(enemyskillDef->timer <= 0)
			{
				ReleaseShadow(enemyskillDef->nIdxShadow);
				enemyskillDef->bUse = false;
			}
			else
			{
				// �e�̈ʒu�ݒ�
				SetPositionShadow(enemyskillDef->nIdxShadow, D3DXVECTOR3(enemyskillDef->pos.x, 0.1f, enemyskillDef->pos.z));


				// �G�t�F�N�g�̐ݒ�
				SetEffect(enemyskillDef->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(0.65f, 0.05f, 0.85f, 0.50f), D3DXVECTOR2(35.0f, 35.0f), 10);
				SetEffect(enemyskillDef->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(0.05f, 0.85f, 0.65f, 0.30f), D3DXVECTOR2(20.0f, 20.0f), 10);
				SetEffect(enemyskillDef->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(0.05f, 0.45f, 0.45f, 0.20f), D3DXVECTOR2(6.0f, 6.0f), 10);


			}

			//�e�̃T�C�Y�̍X�V
			D3DXVECTOR2	size;
			size.x = 8.0f + (enemyskillDef->pos.y - 4.0f) * 0.05f;
			if(size.x < 8.0f)
			{
				size.x = 8.0f;
			}
			size.y = 8.0f + (enemyskillDef->pos.y - 4.0f) * 0.05f;
			if(size.y < 8.0f)
			{
				size.y = 8.0f;
			}

			SetVertexShadow(enemyskillDef->nIdxShadow, size);

			float colA = (200.0f - (enemyskillDef->pos.y - 4.0f)) / 400.0f;
			if(colA < 0.0f)
			{
				colA = 0.0f;
			}
			SetColorShadow(enemyskillDef->nIdxShadow, D3DXCOLOR(1.0f, 1.0f, 1.0f, colA));


			//�͈͊O�ɏo�������
			if (enemyskillDef->pos.x < (SKILLDEF_SIZE_X / 2) - FIELD_SCL_MAX_X)
			{
				DeleteEnemySkillDef(i);
			}
			if (enemyskillDef->pos.x > FIELD_SCL_MAX_X - (SKILLDEF_SIZE_X / 2))
			{
				DeleteEnemySkillDef(i);
			}
			if (enemyskillDef->pos.z > FIELD_SCL_MAX_Z)
			{
				DeleteEnemySkillDef(i);
			}
			if (enemyskillDef->pos.z < (SKILLDEF_SIZE_Y / 2) - FIELD_SCL_MAX_Z)
			{
				DeleteEnemySkillDef(i);
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemySkillDef(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView,mtxscl,mtxTranslate;
	ENEMY_SKILLDEF *enemyskillDef = enemyskillDefWk;

	// ���C�e�B���O�𖳌���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���e�X�g��L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

 for(int i = 0; i < MAX_SKILLDEF; i++, enemyskillDef++)
	{
		if(enemyskillDef->bUse)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&enemyskillDef->world);

			// �r���[�}�g���b�N�X���擾
			mtxView = GetMtxView();

			enemyskillDef->world._11 = mtxView._11;
			enemyskillDef->world._12 = mtxView._21;
			enemyskillDef->world._13 = mtxView._31;
			enemyskillDef->world._21 = mtxView._12;
			enemyskillDef->world._22 = mtxView._22;
			enemyskillDef->world._23 = mtxView._32;
			enemyskillDef->world._31 = mtxView._13;
			enemyskillDef->world._32 = mtxView._23;
			enemyskillDef->world._33 = mtxView._33;

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxscl, enemyskillDef->scl.x, enemyskillDef->scl.y, enemyskillDef->scl.z);
			D3DXMatrixMultiply(&enemyskillDef->world, &enemyskillDef->world, &mtxscl);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, enemyskillDef->pos.x, enemyskillDef->pos.y, enemyskillDef->pos.z);
			D3DXMatrixMultiply(&enemyskillDef->world, &enemyskillDef->world, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &enemyskillDef->world);

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, g_pD3DVtxBuffEnemySkillDef, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pD3DTextureEnemySkillDef);

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
HRESULT MakeVertexEnemySkillDef(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
    if( FAILED( pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * MAX_SKILLDEF,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
												D3DUSAGE_WRITEONLY,							// ���_�o�b�t�@�̎g�p�@�@
												FVF_VERTEX_3D,								// �g�p���钸�_�t�H�[�}�b�g
												D3DPOOL_MANAGED,							// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
												&g_pD3DVtxBuffEnemySkillDef,						// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
												NULL)))										// NULL�ɐݒ�
	{
        return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffEnemySkillDef->Lock(0, 0, (void**)&pVtx, 0);

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
		g_pD3DVtxBuffEnemySkillDef->Unlock();
	}

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexEnemySkillDef(int nIdxEnemySkillDef, D3DXVECTOR2 size)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffEnemySkillDef->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxEnemySkillDef * 4);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(-size.x / 2, -size.y / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-size.x / 2, size.y / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(size.x / 2, -size.y / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(size.x / 2, size.y / 2, 0.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffEnemySkillDef->Unlock();
	}
}

//=============================================================================
// �e�̐ݒ�
//=============================================================================
int SetEnemySkillDef(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 size, int timer)
{
	ENEMY_SKILLDEF *enemyskillDef = enemyskillDefWk;

	int nIdxEnemySkillDef = -1;

	enemyskillDef = GetEnemySkillDef(0);
 for(int i = 0; i < MAX_SKILLDEF; i++, enemyskillDef++)
	{
		if(!enemyskillDef->bUse)
		{

			enemyskillDef->pos = pos;
			enemyskillDef->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			enemyskillDef->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			enemyskillDef->move = move;
			enemyskillDef->size.x = size.x;
			enemyskillDef->size.y = size.y;
			enemyskillDef->timer = timer;
			enemyskillDef->cnt --;
			enemyskillDef->bUse = true;

			// �e�̐ݒ�
			enemyskillDef->nIdxShadow = CreateShadow(pos, D3DXVECTOR2(8.0f, 8.0f));		// �e�̐ݒ�

			// ���_���W�̐ݒ�
			SetVertexEnemySkillDef(i, size);

			nIdxEnemySkillDef = i;

			break;
		}
	}

	return nIdxEnemySkillDef;
}

//=============================================================================
// �e�̍폜
//=============================================================================
void DeleteEnemySkillDef(int nIdxEnemySkillDef)
{
	if(nIdxEnemySkillDef >= 0 && nIdxEnemySkillDef < MAX_SKILLDEF)
	{
		ReleaseShadow(enemyskillDefWk[nIdxEnemySkillDef].nIdxShadow);
		enemyskillDefWk[nIdxEnemySkillDef].bUse = false;
	}
}

//=============================================================================
// �e�̎擾
//=============================================================================
ENEMY_SKILLDEF *GetEnemySkillDef(int no)
{
	return(&enemyskillDefWk[no]);
}
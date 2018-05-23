//=============================================================================
//
// �e���� [enemybullet.cpp]
// Author : �镶��
// �v���O�����쐬�� : 2018/3/09
//=============================================================================
#include "enemy_bullet.h"
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
HRESULT MakeVertexEnemyBullet(LPDIRECT3DDEVICE9 pDevice);
void SetVertexEnemyBullet(int nIdxBullet, D3DXVECTOR2 size);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureEnemyBullet1 = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffEnemyBullet = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

ENEMY_BULLET					enemybulletWk[MAX_BULLET];			// �e���[�N
int						enemybulletType;
LPDIRECT3DTEXTURE9		TextureEnemyEnemyBullet;
//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemyBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY_BULLET *enemybullet = enemybulletWk;

	// ���_���̍쐬
	MakeVertexEnemyBullet(pDevice);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
		TEXTURE_BULLET_ENEMY,				// �t�@�C���̖��O
		&g_pD3DTextureEnemyBullet1);	// �ǂݍ��ރ������[



	for (int i = 0; i < MAX_BULLET; i++, enemybullet++)
	{
		enemybullet->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		enemybullet->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		enemybullet->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		enemybullet->move = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		enemybullet->size.x = BULLET_SIZE_X;
		enemybullet->size.y = BULLET_SIZE_Y;
		enemybullet->timer = 0;
		enemybullet->bUse = false;
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemyBullet(void)
{
	if (g_pD3DTextureEnemyBullet1 != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureEnemyBullet1->Release();
		g_pD3DTextureEnemyBullet1 = NULL;
	}

	if (g_pD3DVtxBuffEnemyBullet != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffEnemyBullet->Release();
		g_pD3DVtxBuffEnemyBullet = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemyBullet(void)
{
	D3DXVECTOR3 rotCamera;
	ENEMY_BULLET *enemybullet = enemybulletWk;


	// �J�����̉�]���擾
	rotCamera = GetRotCamera();

	for (int i = 0; i < MAX_BULLET; i++, enemybullet++)
	{
		if (enemybullet->bUse)
		{
			enemybullet->pos.x += enemybullet->move.x;
			enemybullet->pos.z += enemybullet->move.z;

			enemybullet->timer--;
			if (enemybullet->timer <= 0)
			{
				ReleaseShadow(enemybullet->nIdxShadow);
				enemybullet->bUse = false;
			}
			else
			{
				// �e�̈ʒu�ݒ�
				SetPositionShadow(enemybullet->nIdxShadow, D3DXVECTOR3(enemybullet->pos.x, 0.1f, enemybullet->pos.z));

				// �G�t�F�N�g�̐ݒ�
				SetEffect(enemybullet->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(0.65f, 0.05f, 0.85f, 0.50f), D3DXVECTOR2(16.0f, 16.0f), 10);
				SetEffect(enemybullet->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(0.05f, 0.85f, 0.65f, 0.30f), D3DXVECTOR2(12.0f, 12.0f), 10);
				SetEffect(enemybullet->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(0.05f, 0.45f, 0.45f, 0.20f), D3DXVECTOR2(6.0f, 6.0f), 10);
			}

			D3DXVECTOR2	size;
			size.x = 8.0f + (enemybullet->pos.y - 4.0f) * 0.05f;
			if (size.x < 8.0f)
			{
				size.x = 8.0f;
			}
			size.y = 8.0f + (enemybullet->pos.y - 4.0f) * 0.05f;
			if (size.y < 8.0f)
			{
				size.y = 8.0f;
			}

			SetVertexShadow(enemybullet->nIdxShadow, size);

			float colA = (200.0f - (enemybullet->pos.y - 4.0f)) / 400.0f;
			if (colA < 0.0f)
			{
				colA = 0.0f;
			}
			SetColorShadow(enemybullet->nIdxShadow, D3DXCOLOR(1.0f, 1.0f, 1.0f, colA));

			if (enemybullet->pos.x < (BULLET_SIZE_X / 2) - FIELD_SCL_MAX_X)
			{
				DeleteEnemyBullet(i);
			}
			if (enemybullet->pos.x > FIELD_SCL_MAX_X - (BULLET_SIZE_X / 2))
			{
				DeleteEnemyBullet(i);
			}
			if (enemybullet->pos.z > FIELD_SCL_MAX_Z)
			{
				DeleteEnemyBullet(i);
			}
			if (enemybullet->pos.z < (BULLET_SIZE_Y / 2) - FIELD_SCL_MAX_Z)
			{
				DeleteEnemyBullet(i);
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemyBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxscl, mtxTranslate;
	ENEMY_BULLET *enemybullet = enemybulletWk;

	// ���C�e�B���O�𖳌���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���e�X�g��L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (int i = 0; i < MAX_BULLET; i++, enemybullet++)
	{
		if (enemybullet->bUse)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&enemybullet->world);

			// �r���[�}�g���b�N�X���擾
			mtxView = GetMtxView();

			enemybullet->world._11 = mtxView._11;
			enemybullet->world._12 = mtxView._21;
			enemybullet->world._13 = mtxView._31;
			enemybullet->world._21 = mtxView._12;
			enemybullet->world._22 = mtxView._22;
			enemybullet->world._23 = mtxView._32;
			enemybullet->world._31 = mtxView._13;
			enemybullet->world._32 = mtxView._23;
			enemybullet->world._33 = mtxView._33;

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxscl, enemybullet->scl.x, enemybullet->scl.y, enemybullet->scl.z);
			D3DXMatrixMultiply(&enemybullet->world, &enemybullet->world, &mtxscl);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, enemybullet->pos.x, enemybullet->pos.y, enemybullet->pos.z);
			D3DXMatrixMultiply(&enemybullet->world, &enemybullet->world, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &enemybullet->world);

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, g_pD3DVtxBuffEnemyBullet, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pD3DTextureEnemyBullet1);

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
HRESULT MakeVertexEnemyBullet(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * MAX_BULLET,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,							// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_3D,								// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,							// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffEnemyBullet,						// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))										// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffEnemyBullet->Lock(0, 0, (void**)&pVtx, 0);

		for (int i = 0; i < MAX_BULLET; i++, pVtx += 4)
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
		g_pD3DVtxBuffEnemyBullet->Unlock();
	}

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexEnemyBullet(int nIdxEnemyBullet, D3DXVECTOR2 size)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffEnemyBullet->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxEnemyBullet * 4);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(-size.x / 2, -size.y / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-size.x / 2, size.y / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(size.x / 2, -size.y / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(size.x / 2, size.y / 2, 0.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffEnemyBullet->Unlock();
	}
}

//=============================================================================
// �e�̐ݒ�
//=============================================================================
int SetEnemyBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 size, int timer)
{
	ENEMY_BULLET *enemybullet = enemybulletWk;

	int nIdxEnemyBullet = -1;

	enemybullet = GetEnemyBullet(0);
	for (int i = 0; i < MAX_BULLET; i++, enemybullet++)
	{
		if (!enemybullet->bUse)
		{

			enemybullet->pos = pos;
			enemybullet->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			enemybullet->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			enemybullet->move = move;
			enemybullet->size.x = size.x;
			enemybullet->size.y = size.y;
			enemybullet->timer = timer;
			enemybullet->bUse = true;

			// �e�̐ݒ�
			enemybullet->nIdxShadow = CreateShadow(pos, D3DXVECTOR2(8.0f, 8.0f));		// �e�̐ݒ�

																						// ���_���W�̐ݒ�
			SetVertexEnemyBullet(i, size);

			nIdxEnemyBullet = i;

			break;
		}
	}

	return nIdxEnemyBullet;
}

//=============================================================================
// �e�̍폜
//=============================================================================
void DeleteEnemyBullet(int nIdxEnemyBullet)
{
	if (nIdxEnemyBullet >= 0 && nIdxEnemyBullet < MAX_BULLET)
	{
		ReleaseShadow(enemybulletWk[nIdxEnemyBullet].nIdxShadow);
		enemybulletWk[nIdxEnemyBullet].bUse = false;
	}
}

int GetEnemyBulletType(void)
{
	return enemybulletType;
}

ENEMY_BULLET *GetEnemyBullet(int no)
{
	return(&enemybulletWk[no]);
}
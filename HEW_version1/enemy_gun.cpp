//=============================================================================
//
// �e���� [enemygun.cpp]
// Author : �镶��
// �v���O�����쐬�� : 2018/3/09
//=============================================================================
#include "enemy_gun.h"
#include "input.h"
#include "camera.h"
#include "field.h"
#include "enemy.h"
#include "enemy_cursor.h"


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTextureEnemyGun;		// �e�N�X�`���ւ̃|�C���^

LPD3DXMESH			g_pD3DXMeshEnemyGun;		// ���b�V�����ւ̃|�C���^
LPD3DXBUFFER		g_pD3DXBuffMatEnemyGun;	// �}�e���A�����ւ̃|�C���^
DWORD				g_nNumMatEnemyGun;			// �}�e���A�����̐�

ENEMYGUN				enemygunWK[1];
//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemyGun(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMYGUN *enemygun = enemygunWK;
	ENEMY *enemy = GetEnemy();


	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	enemygun->pos = D3DXVECTOR3(enemy->pos.x, enemy->pos.y, enemy->pos.z);
	enemygun->rot = D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f);
	enemygun->rotDest = D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f);
	enemygun->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	enemygun->face = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
	enemygun->face = enemygun->face - enemygun->pos;

	// ���f���֌W�̏�����
	g_pD3DTextureEnemyGun = NULL;
	g_pD3DXMeshEnemyGun = NULL;
	g_pD3DXBuffMatEnemyGun = NULL;
	g_nNumMatEnemyGun = 0;

	//X�t�@�C���̓ǂݍ���
	if (FAILED(D3DXLoadMeshFromX(ENEMYGUN_CAR,	//���f���f�[�^
		D3DXMESH_SYSTEMMEM,								//�g�p���郁�����̃I�v�V����
		pDevice,										//�f�o�C�X
		NULL,											//���g�p
		&g_pD3DXBuffMatEnemyGun,							//�}�e���A���f�[�^�ւ̃|�C���^
		NULL,											//���g�p
		&g_nNumMatEnemyGun,								//D3DXMATERIAL�\���̂̐�
		&g_pD3DXMeshEnemyGun)))							//���b�V���f�[�^�ւ̃|�C���^
	{
		return E_FAIL;
	}

	

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemyGun(void)
{
	if(g_pD3DTextureEnemyGun != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureEnemyGun->Release();
		g_pD3DTextureEnemyGun = NULL;
	}

	if(g_pD3DXMeshEnemyGun != NULL)
	{// ���b�V���̊J��
		g_pD3DXMeshEnemyGun->Release();
		g_pD3DXMeshEnemyGun = NULL;
	}

	if(g_pD3DXBuffMatEnemyGun != NULL)
	{// �}�e���A���̊J��
		g_pD3DXBuffMatEnemyGun->Release();
		g_pD3DXBuffMatEnemyGun = NULL;
	}
}

//=============================================================================
// �X�V���� 
//=============================================================================
void UpdateEnemyGun(void)
{
	CAMERA *camera = GetCamera();
	ENEMYGUN *enemygun = enemygunWK;
	ENEMY *enemy = GetEnemy();
	CURSOR_ENEMY *Pcursor = GetCursorEnemy();

	//�ʒu�̍X�V
	enemygun->pos = enemy->pos;

	//��]�̍X�V
	enemygun->rotDest.y = atan2(Pcursor->pos.x - enemygun->pos.x, Pcursor->pos.z - enemygun->pos.z);
	enemygun->rotDest.y -= D3DX_PI;

	enemygun->diffRot = enemygun->rotDest.y - enemygun->rot.y;
	if (enemygun->diffRot > D3DX_PI)
	{
		enemygun->diffRot -= D3DX_PI*2.0f;
	}
	if (enemygun->diffRot < -D3DX_PI)
	{
		enemygun->diffRot += D3DX_PI*2.0f;
	}

	enemygun->rot.y += enemygun->diffRot*ENEMYGUN_ROTTIME;
	if (enemygun->rot.y > D3DX_PI)
	{
		// 360�x�𒴂�����360�x������
		enemygun->rot.y -= D3DX_PI * 2.0f;
	}
	if (enemygun->rot.y < -D3DX_PI)
	{
		// 360�x�𒴂�����360�x������
		enemygun->rot.y += D3DX_PI * 2.0f;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemyGun(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	ENEMYGUN *enemygun = enemygunWK;
	CAMERA *camera = GetCamera();

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&enemygun->world);

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, enemygun->scl.x, enemygun->scl.y, enemygun->scl.z);
	D3DXMatrixMultiply(&enemygun->world, &enemygun->world, &mtxScl);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, enemygun->rot.y, enemygun->rot.x, enemygun->rot.z);
	D3DXMatrixMultiply(&enemygun->world, &enemygun->world, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, enemygun->pos.x, enemygun->pos.y, enemygun->pos.z);
	D3DXMatrixMultiply(&enemygun->world, &enemygun->world, &mtxTranslate);


	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &enemygun->world);

	// ���f���̕`��

	//���݂̃}�e���A����ۑ�
	pDevice->GetMaterial(&matDef);

	//�}�e���A�����ւ̃|�C���^���擾
	pD3DXMat = (D3DXMATERIAL*)g_pD3DXBuffMatEnemyGun->GetBufferPointer();

	for (int i = 0;i < (int)g_nNumMatEnemyGun;i++)
	{
		pDevice->SetMaterial(&pD3DXMat[i].MatD3D);	//�}�e���A���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureEnemyGun);	//�e�N�X�`���̐ݒ�
		g_pD3DXMeshEnemyGun->DrawSubset(i);
	}

	//�}�e���A�������ɖ߂�
	pDevice->SetMaterial(&matDef);


}


ENEMYGUN *GetEnemyGun(void)
{
	return enemygunWK;
}

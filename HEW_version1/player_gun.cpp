//=============================================================================
//
// ���f������ [playergun.cpp]
// Author : �镶��
// �v���O�����쐬�� : 2018/3/09
//=============================================================================
#include "player_gun.h"
#include "input.h"
#include "camera.h"
#include "field.h"
#include "player.h"
#include "player_cursor.h"


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTexturePlayerGun;		// �e�N�X�`���ւ̃|�C���^

LPD3DXMESH			g_pD3DXMeshPlayerGun;		// ���b�V�����ւ̃|�C���^
LPD3DXBUFFER		g_pD3DXBuffMatPlayerGun;	// �}�e���A�����ւ̃|�C���^
DWORD				g_nNumMatPlayerGun;			// �}�e���A�����̐�

PLAYERGUN				playergunWK[1];
//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayerGun(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYERGUN *playergun = playergunWK;
	PLAYER *player = GetPlayer();


	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	playergun->pos = D3DXVECTOR3(player->pos.x, player->pos.y, player->pos.z);
	playergun->rot = D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f);
	playergun->rotDest = D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f);
	playergun->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	playergun->face = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	playergun->face = playergun->face - playergun->pos;

	// ���f���֌W�̏�����
	g_pD3DTexturePlayerGun = NULL;
	g_pD3DXMeshPlayerGun = NULL;
	g_pD3DXBuffMatPlayerGun = NULL;
	g_nNumMatPlayerGun = 0;

	//X�t�@�C���̓ǂݍ���
	if (FAILED(D3DXLoadMeshFromX(PLAYERGUN_CAR,	//���f���f�[�^
		D3DXMESH_SYSTEMMEM,								//�g�p���郁�����̃I�v�V����
		pDevice,										//�f�o�C�X
		NULL,											//���g�p
		&g_pD3DXBuffMatPlayerGun,							//�}�e���A���f�[�^�ւ̃|�C���^
		NULL,											//���g�p
		&g_nNumMatPlayerGun,								//D3DXMATERIAL�\���̂̐�
		&g_pD3DXMeshPlayerGun)))							//���b�V���f�[�^�ւ̃|�C���^
	{
		return E_FAIL;
	}

	

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayerGun(void)
{
	if(g_pD3DTexturePlayerGun != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTexturePlayerGun->Release();
		g_pD3DTexturePlayerGun = NULL;
	}

	if(g_pD3DXMeshPlayerGun != NULL)
	{// ���b�V���̊J��
		g_pD3DXMeshPlayerGun->Release();
		g_pD3DXMeshPlayerGun = NULL;
	}

	if(g_pD3DXBuffMatPlayerGun != NULL)
	{// �}�e���A���̊J��
		g_pD3DXBuffMatPlayerGun->Release();
		g_pD3DXBuffMatPlayerGun = NULL;
	}
}

//=============================================================================
// �X�V���� 
//=============================================================================
void UpdatePlayerGun(void)
{
	CAMERA *camera = GetCamera();
	PLAYERGUN *playergun = playergunWK;
	PLAYER *player = GetPlayer();
	CURSOR_PLAYER *Pcursor = GetCursorPlayer();

	playergun->pos = player->pos;

	//D3DXVECTOR3 vecEM;
	//vecEM = Pcursor->pos - playergun->pos;
	//D3DXVECTOR3 vec;
	//D3DXVec3Cross(&vec, &playergun->face, &vecEM);
	//if (vec.y > 0)
	//{
	//	playergun->face.x = playergun->face.x*cosf(-VALUE_ROTATE_PLAYERGUN) - playergun->face.z*sinf(-VALUE_ROTATE_PLAYERGUN);
	//	playergun->face.z = playergun->face.z*cosf(-VALUE_ROTATE_PLAYERGUN) + playergun->face.x*sinf(-VALUE_ROTATE_PLAYERGUN);
	//	playergun->rotDest.y += VALUE_ROTATE_PLAYERGUN;
	//	if (playergun->rotDest.y > D3DX_PI)
	//	{
	//		// 360�x�𒴂�����360�x������
	//		playergun->rotDest.y -= D3DX_PI * 2.0f;
	//	}

	//}
	//else if (vec.y < 0)
	//{
	//	playergun->face.x = playergun->face.x*cosf(VALUE_ROTATE_PLAYERGUN) - playergun->face.z*sinf(VALUE_ROTATE_PLAYERGUN);
	//	playergun->face.z = playergun->face.z*cosf(VALUE_ROTATE_PLAYERGUN) + playergun->face.x*sinf(VALUE_ROTATE_PLAYERGUN);
	//	playergun->rotDest.y -= VALUE_ROTATE_PLAYERGUN;
	//	if (playergun->rotDest.y < -D3DX_PI)
	//	{
	//		// 360�x�𒴂�����360�x������
	//		playergun->rotDest.y += D3DX_PI * 2.0f;
	//	}
	//}
	//else if (vec.y == 0)
	//{
	//	playergun->face.x = playergun->face.x;
	//	playergun->face.z = playergun->face.z;
	//}

	playergun->rotDest.y = atan2(Pcursor->pos.x - playergun->pos.x, Pcursor->pos.z - playergun->pos.z);
	playergun->rotDest.y -= D3DX_PI;

	playergun->diffRot = playergun->rotDest.y - playergun->rot.y;
	if (playergun->diffRot > D3DX_PI)
	{
		playergun->diffRot -= D3DX_PI*2.0f;
	}
	if (playergun->diffRot < -D3DX_PI)
	{
		playergun->diffRot += D3DX_PI*2.0f;
	}

	playergun->rot.y += playergun->diffRot*PLAYERGUN_ROTTIME;
	if (playergun->rot.y > D3DX_PI)
	{
		// 360�x�𒴂�����360�x������
		playergun->rot.y -= D3DX_PI * 2.0f;
	}
	if (playergun->rot.y < -D3DX_PI)
	{
		// 360�x�𒴂�����360�x������
		playergun->rot.y += D3DX_PI * 2.0f;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayerGun(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	PLAYERGUN *playergun = playergunWK;
	CAMERA *camera = GetCamera();


	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&playergun->world);


	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, playergun->scl.x, playergun->scl.y, playergun->scl.z);
	D3DXMatrixMultiply(&playergun->world, &playergun->world, &mtxScl);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, playergun->rot.y, playergun->rot.x, playergun->rot.z);
	D3DXMatrixMultiply(&playergun->world, &playergun->world, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, playergun->pos.x, playergun->pos.y, playergun->pos.z);
	D3DXMatrixMultiply(&playergun->world, &playergun->world, &mtxTranslate);


	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &playergun->world);

	// ���f���̕`��

	//���݂̃}�e���A����ۑ�
	pDevice->GetMaterial(&matDef);

	//�}�e���A�����ւ̃|�C���^���擾
	pD3DXMat = (D3DXMATERIAL*)g_pD3DXBuffMatPlayerGun->GetBufferPointer();

	for (int i = 0;i < (int)g_nNumMatPlayerGun;i++)
	{
		pDevice->SetMaterial(&pD3DXMat[i].MatD3D);	//�}�e���A���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTexturePlayerGun);	//�e�N�X�`���̐ݒ�
		g_pD3DXMeshPlayerGun->DrawSubset(i);
	}

	//�}�e���A�������ɖ߂�
	pDevice->SetMaterial(&matDef);


}


PLAYERGUN *GetPlayerGun(void)
{
	return playergunWK;
}

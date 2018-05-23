//=============================================================================
//
// �e���� [playerSupSk.cpp]
// Author : �镶��
// �v���O�����쐬�� : 2018/3/09
//=============================================================================
#include "player_skillSup.h"
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
HRESULT MakeVertexPlayerSupSkill(LPDIRECT3DDEVICE9 pDevice);
void SetVertexPlayerSupSkill(int nIdxSupSkill, D3DXVECTOR2 size);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTexturePlayerSupSkill = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffPlayerSupSkill	= NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

PLAYER_SUPSKILL			playersupSkillWk[MAX_SUPSKILL];			// �e���[�N
LPDIRECT3DTEXTURE9		TexturePlayerPlayerSupSkill;
//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayerSupSkill(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER_SUPSKILL *playersupSkill = playersupSkillWk;

	// ���_���̍쐬
	MakeVertexPlayerSupSkill(pDevice);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
								TEXTURE_SUPSKILL_PLAYER,				// �t�@�C���̖��O
								&g_pD3DTexturePlayerSupSkill);	// �ǂݍ��ރ������[

													

	for(int i = 0; i < MAX_SUPSKILL; i++, playersupSkill++)
	{
		playersupSkill->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		playersupSkill->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		playersupSkill->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		playersupSkill->move = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		playersupSkill->size.x = SUPSKILL_SIZE_X;
		playersupSkill->size.y = SUPSKILL_SIZE_Y;
		playersupSkill->timer = 0;
		playersupSkill->bUse = false;
		playersupSkill->Track = true;
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayerSupSkill(void)
{
	if(g_pD3DTexturePlayerSupSkill != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTexturePlayerSupSkill->Release();
		g_pD3DTexturePlayerSupSkill = NULL;
	}

	if(g_pD3DVtxBuffPlayerSupSkill != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffPlayerSupSkill->Release();
		g_pD3DVtxBuffPlayerSupSkill = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayerSupSkill(void)
{
	D3DXVECTOR3 rotCamera;
	PLAYER_SUPSKILL *playersupSkill = playersupSkillWk;
	PLAYER *player = GetPlayer();
	ENEMY *enemy = GetEnemy();


	// �J�����̉�]���擾
	rotCamera = GetRotCamera();

 for(int i = 0; i < MAX_SUPSKILL; i++, playersupSkill++)
	{
		if(playersupSkill->bUse)
		{

			if (playersupSkill->Track)
			{

				playersupSkill->rot.y = atan2(enemy->pos.x - playersupSkill->pos.x, enemy->pos.z - playersupSkill->pos.z);
				playersupSkill->rot.y -= D3DX_PI;
				playersupSkill->move.x = -sinf(playersupSkill->rot.y)*4.0f;
				playersupSkill->move.z = -cosf(playersupSkill->rot.y)*4.0f;
				if (CheckHitBC(playersupSkill->pos, enemy->pos, 2.0f, 30.0f))
				{
					playersupSkill->Track = false;

				}
		
			}
			else if (playersupSkill->Track == false)
			{
				playersupSkill->move.x = -sinf(playersupSkill->rot.y)*4.0f;
				playersupSkill->move.z = -cosf(playersupSkill->rot.y)*4.0f;
			}

			playersupSkill->pos.x += playersupSkill->move.x;
			playersupSkill->pos.z += playersupSkill->move.z;

			playersupSkill->timer--;
			if(playersupSkill->timer <= 0)
			{
				ReleaseShadow(playersupSkill->nIdxShadow);
				playersupSkill->bUse = false;
			}
			else
			{
				// �e�̈ʒu�ݒ�
				SetPositionShadow(playersupSkill->nIdxShadow, D3DXVECTOR3(playersupSkill->pos.x, 0.1f, playersupSkill->pos.z));


				// �G�t�F�N�g�̐ݒ�
				SetEffect(playersupSkill->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(0.85f, 0.05f, 0.15f, 0.50f), D3DXVECTOR2(15.0f, 15.0f), 10);
				SetEffect(playersupSkill->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(0.65f, 0.10f, 0.10f, 0.30f), D3DXVECTOR2(8.0f, 8.0f), 10);
				SetEffect(playersupSkill->pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(0.45f, 0.15f, 0.05f, 0.20f), D3DXVECTOR2(4.0f, 4.0f), 10);

			}

			D3DXVECTOR2	size;
			size.x = 8.0f + (playersupSkill->pos.y - 4.0f) * 0.05f;
			if(size.x < 8.0f)
			{
				size.x = 8.0f;
			}
			size.y = 8.0f + (playersupSkill->pos.y - 4.0f) * 0.05f;
			if(size.y < 8.0f)
			{
				size.y = 8.0f;
			}

			SetVertexShadow(playersupSkill->nIdxShadow, size);

			float colA = (200.0f - (playersupSkill->pos.y - 4.0f)) / 400.0f;
			if(colA < 0.0f)
			{
				colA = 0.0f;
			}
			SetColorShadow(playersupSkill->nIdxShadow, D3DXCOLOR(1.0f, 1.0f, 1.0f, colA));

			if (playersupSkill->pos.x < (SUPSKILL_SIZE_X / 2) - FIELD_SCL_MAX_X)
			{
				DeletePlayerSupSkill(i);
			}
			if (playersupSkill->pos.x > FIELD_SCL_MAX_X - (SUPSKILL_SIZE_X / 2))
			{
				DeletePlayerSupSkill(i);
			}
			if (playersupSkill->pos.z > FIELD_SCL_MAX_Z)
			{
				DeletePlayerSupSkill(i);
			}
			if (playersupSkill->pos.z < (SUPSKILL_SIZE_Y / 2) - FIELD_SCL_MAX_Z)
			{
				DeletePlayerSupSkill(i);
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayerSupSkill(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView,mtxscl,mtxTranslate;
	PLAYER_SUPSKILL *playersupSkill = playersupSkillWk;

	// ���C�e�B���O�𖳌���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���e�X�g��L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

 for(int i = 0; i < MAX_SUPSKILL; i++, playersupSkill++)
	{
		if(playersupSkill->bUse)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&playersupSkill->world);

			// �r���[�}�g���b�N�X���擾
			mtxView = GetMtxView();

			playersupSkill->world._11 = mtxView._11;
			playersupSkill->world._12 = mtxView._21;
			playersupSkill->world._13 = mtxView._31;
			playersupSkill->world._21 = mtxView._12;
			playersupSkill->world._22 = mtxView._22;
			playersupSkill->world._23 = mtxView._32;
			playersupSkill->world._31 = mtxView._13;
			playersupSkill->world._32 = mtxView._23;
			playersupSkill->world._33 = mtxView._33;

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxscl, playersupSkill->scl.x, playersupSkill->scl.y, playersupSkill->scl.z);
			D3DXMatrixMultiply(&playersupSkill->world, &playersupSkill->world, &mtxscl);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, playersupSkill->pos.x, playersupSkill->pos.y, playersupSkill->pos.z);
			D3DXMatrixMultiply(&playersupSkill->world, &playersupSkill->world, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &playersupSkill->world);

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, g_pD3DVtxBuffPlayerSupSkill, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pD3DTexturePlayerSupSkill);

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
HRESULT MakeVertexPlayerSupSkill(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
    if( FAILED( pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * MAX_SUPSKILL,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
												D3DUSAGE_WRITEONLY,							// ���_�o�b�t�@�̎g�p�@�@
												FVF_VERTEX_3D,								// �g�p���钸�_�t�H�[�}�b�g
												D3DPOOL_MANAGED,							// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
												&g_pD3DVtxBuffPlayerSupSkill,						// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
												NULL)))										// NULL�ɐݒ�
	{
        return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffPlayerSupSkill->Lock(0, 0, (void**)&pVtx, 0);

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
		g_pD3DVtxBuffPlayerSupSkill->Unlock();
	}

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexPlayerSupSkill(int nIdxPlayerSupSkill, D3DXVECTOR2 size)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffPlayerSupSkill->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxPlayerSupSkill * 4);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(-size.x / 2, -size.y / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-size.x / 2, size.y / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(size.x / 2, -size.y / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(size.x / 2, size.y / 2, 0.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffPlayerSupSkill->Unlock();
	}
}

//=============================================================================
// �e�̐ݒ�
//=============================================================================
int SetPlayerSupSkill(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 size, int timer)
{
	PLAYER_SUPSKILL *playersupSkill = playersupSkillWk;

	int nIdxPlayerSupSkill = -1;

	playersupSkill = GetPlayerSupSkill(0);
 for(int i = 0; i < MAX_SUPSKILL; i++, playersupSkill++)
	{
		if(!playersupSkill->bUse)
		{

			playersupSkill->pos = pos;
			playersupSkill->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			playersupSkill->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			playersupSkill->move = move;
			playersupSkill->size.x = size.x;
			playersupSkill->size.y = size.y;
			playersupSkill->timer = timer;
			playersupSkill->bUse = true;
			playersupSkill->Track = true;

			// �e�̐ݒ�
			playersupSkill->nIdxShadow = CreateShadow(pos, D3DXVECTOR2(8.0f, 8.0f));		// �e�̐ݒ�

			// ���_���W�̐ݒ�
			SetVertexPlayerSupSkill(i, size);

			nIdxPlayerSupSkill = i;

			break;
		}
	}

	return nIdxPlayerSupSkill;
}

//=============================================================================
// �e�̍폜
//=============================================================================
void DeletePlayerSupSkill(int nIdxPlayerSupSkill)
{
	if(nIdxPlayerSupSkill >= 0 && nIdxPlayerSupSkill < MAX_SUPSKILL)
	{
		ReleaseShadow(playersupSkillWk[nIdxPlayerSupSkill].nIdxShadow);
		playersupSkillWk[nIdxPlayerSupSkill].bUse = false;
	}
}

PLAYER_SUPSKILL *GetPlayerSupSkill(int no)
{
	return(&playersupSkillWk[no]);
}


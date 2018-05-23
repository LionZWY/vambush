//=============================================================================
//
// �J�[�\������ [Pcursor.cpp]
// Author : �镶��
// �v���O�����쐬�� : 2018/3/09
//=============================================================================
#include "player_cursor.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "field.h"
#include "player.h"
#include "checkhit.h"
#include "enemy.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_CURSOR		"data/TEXTURE/�J�[�\��.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	VALUE_MOVE_CURSOR	(0.30f)							// �ړ����x
#define	VALUE_JUMP				(10.0f)							// �W�����v��
#define	VALUE_GRAVITY			(0.45f)							// �d��
#define	RATE_REGIST				(0.075f)						// ��R�W��
#define	RATE_REFRECT			(-0.90f)						// ���ˌW��
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexCursorPlayer(LPDIRECT3DDEVICE9 pDevice);
void SetVertexCursorPlayer(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureCursorPlayer = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffCursorPlayer = NULL;	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

CURSOR_PLAYER			PcursorWk[1];
//=============================================================================
// ����������
//=============================================================================
HRESULT InitCursorPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CURSOR_PLAYER *Pcursor = PcursorWk;
	CAMERA *camera = GetCamera();
	PLAYER *player = GetPlayer();

	Pcursor->pos = D3DXVECTOR3(0.0f, 7.0f, 0.0f);
	Pcursor->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	Pcursor->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Pcursor->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Pcursor->size = D3DXVECTOR2(5.0f, 5.0f);
	Pcursor->lock = false;


	float cVecX, cVecZ;
	cVecX = camera->posEye.x - Pcursor->pos.x;
	cVecZ = camera->posEye.z - Pcursor->pos.z;
	Pcursor->PCtoEPDistance = (sqrtf(cVecX * cVecX + cVecZ * cVecZ));



	// ���_���̍쐬
	MakeVertexCursorPlayer(pDevice);
	


	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
								TEXTURE_CURSOR,			// �t�@�C���̖��O
								&g_pD3DTextureCursorPlayer);	// �ǂݍ��ރ������[

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitCursorPlayer(void)
{
	if(g_pD3DTextureCursorPlayer != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureCursorPlayer->Release();
		g_pD3DTextureCursorPlayer = NULL;
	}

	if(g_pD3DVtxBuffCursorPlayer != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffCursorPlayer->Release();
		g_pD3DVtxBuffCursorPlayer = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateCursorPlayer(void)
{
	D3DXVECTOR3 rotCamera;
	CURSOR_PLAYER *Pcursor = PcursorWk;
	CAMERA *camera = GetCamera();
	PLAYER *player = GetPlayer();
	ENEMY *enemy = GetEnemy();

	float cVecX, cVecZ;
	cVecX = camera->posEye.x - Pcursor->pos.x;
	cVecZ = camera->posEye.z - Pcursor->pos.z;
	Pcursor->PCtoEPDistance = (sqrtf(cVecX * cVecX + cVecZ * cVecZ));

	if (Pcursor->lock == false)
	{
		if ((GetKeyboardPress(DIK_I)) || (IsButtonPressed(0, R_BUTTON_UP)))
		{
			//Pcursor->lock = false;
			Pcursor->move.z += 0.5f;
		}
		else if ((GetKeyboardPress(DIK_K)) || (IsButtonPressed(0, R_BUTTON_DOWN)))
		{
			//Pcursor->lock = false;
			Pcursor->move.z -= 0.5f;
		}
		if ((GetKeyboardPress(DIK_J)) || (IsButtonPressed(0, R_BUTTON_LEFT)))
		{
			//Pcursor->lock = false;
			Pcursor->move.x -= 0.5f;
		}
		else if ((GetKeyboardPress(DIK_L)) || (IsButtonPressed(0, R_BUTTON_RIGHT)))
		{
			//Pcursor->lock = false;
			Pcursor->move.x += 0.5f;
		}

		if ((GetKeyboardPress(DIK_O)) || (IsButtonTriggered(0, BUTTON_R3)))
		{
			Pcursor->lock = true;
		}
	}
	else if (Pcursor->lock == true)
	{
		Pcursor->pos.x = enemy->pos.x;
		Pcursor->pos.z = enemy->pos.z;
		if (IsButtonTriggered(0, BUTTON_R3))
		{
			Pcursor->lock = false;
		}
	}

	if (Pcursor->rot.y > D3DX_PI)
	{
		// 360�x�𒴂�����360�x������
		Pcursor->rot.y -= D3DX_PI * 2.0f;
	}
	else if (Pcursor->rot.y < D3DX_PI)
	{
		// 360�x�𒴂�����360�x������
		Pcursor->rot.y += D3DX_PI * 2.0f;
	}

	Pcursor->pos.x += Pcursor->move.x;
	Pcursor->pos.z += Pcursor->move.z;

	Pcursor->move.x += (0.0f - Pcursor->move.x) * RATE_REGIST;
	Pcursor->move.z += (0.0f - Pcursor->move.z) * RATE_REGIST;

	Pcursor->size.x = (camera->EyeToAtDistance / 50.0f + (Pcursor->pos.z * 0.005f) + 15.0f);
	Pcursor->size.y = (camera->EyeToAtDistance / 50.0f + (Pcursor->pos.z * 0.005f) + 15.0f);

	if (Pcursor->pos.x < (Pcursor->size.x / 2) - FIELD_SCL_MAX_X)
	{
		Pcursor->pos.x = (Pcursor->size.x / 2) - FIELD_SCL_MAX_X;
	}
	if (Pcursor->pos.x > FIELD_SCL_MAX_X - (Pcursor->size.x / 2))
	{
		Pcursor->pos.x = FIELD_SCL_MAX_X - (Pcursor->size.x / 2);
	}
	if (Pcursor->pos.z > FIELD_SCL_MAX_Z)
	{
		Pcursor->pos.z = FIELD_SCL_MAX_Z;
	}
	if (Pcursor->pos.z < (Pcursor->size.y / 2)- FIELD_SCL_MAX_Z)
	{
		Pcursor->pos.z = (Pcursor->size.y / 2) - FIELD_SCL_MAX_Z;
	}

	SetVertexCursorPlayer();

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawCursorPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxscl, mtxTranslate,mtxRot;
	CURSOR_PLAYER *Pcursor = PcursorWk;

	// ���e�X�g��L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 150);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// ���C���e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// �r���[�}�g���b�N�X���擾
	mtxView = GetMtxView();

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&Pcursor->world);

	// �|���S���𐳖ʂɌ�����
	Pcursor->world._11 = mtxView._11;
	Pcursor->world._12 = mtxView._21;
	Pcursor->world._13 = mtxView._31;
	Pcursor->world._22 = mtxView._22;
	Pcursor->world._23 = mtxView._32;
	Pcursor->world._33 = mtxView._33;
	Pcursor->world._32 = mtxView._23;
	Pcursor->world._31 = mtxView._13;
	Pcursor->world._21 = mtxView._12;

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxscl, Pcursor->scl.x,
		Pcursor->scl.y,
		Pcursor->scl.z);
	D3DXMatrixMultiply(&Pcursor->world,
		&Pcursor->world, &mtxscl);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, Pcursor->rot.y, Pcursor->rot.x, Pcursor->rot.z);
	D3DXMatrixMultiply(&Pcursor->world, &Pcursor->world, &mtxRot);


	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, Pcursor->pos.x,
		Pcursor->pos.y,
		Pcursor->pos.z);
	D3DXMatrixMultiply(&Pcursor->world,
		&Pcursor->world, &mtxTranslate);



	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &Pcursor->world);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pD3DVtxBuffCursorPlayer, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureCursorPlayer);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	// ���C���e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
HRESULT MakeVertexCursorPlayer(LPDIRECT3DDEVICE9 pDevice)
{
	CURSOR_PLAYER *Pcursor = PcursorWk;
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
    if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
												D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
												FVF_VERTEX_3D,				// �g�p���钸�_�t�H�[�}�b�g
												D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
												&g_pD3DVtxBuffCursorPlayer,	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
												NULL)))						// NULL�ɐݒ�
	{
        return E_FAIL;
	}

	{
		SetVertexCursorPlayer();

		// �@���̐ݒ�
		Pcursor->vectex[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		Pcursor->vectex[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		Pcursor->vectex[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		Pcursor->vectex[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// ���ˌ��̐ݒ�
		Pcursor->vectex[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		Pcursor->vectex[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		Pcursor->vectex[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		Pcursor->vectex[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		Pcursor->vectex[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		Pcursor->vectex[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		Pcursor->vectex[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		Pcursor->vectex[3].tex = D3DXVECTOR2(1.0f, 0.0f);


		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffCursorPlayer->Unlock();
	}

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexCursorPlayer(void)
{
	CURSOR_PLAYER *Pcursor = PcursorWk;
	{	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffCursorPlayer->Lock(0, 0, (void**)&Pcursor->vectex, 0);

		Pcursor->vectex[0].vtx = D3DXVECTOR3(-Pcursor->size.x / 2, -Pcursor->size.x / 2, 0.0f);
		Pcursor->vectex[1].vtx = D3DXVECTOR3(-Pcursor->size.x / 2, Pcursor->size.x / 2, 0.0f);
		Pcursor->vectex[2].vtx = D3DXVECTOR3(Pcursor->size.x / 2, -Pcursor->size.x / 2, 0.0f);
		Pcursor->vectex[3].vtx = D3DXVECTOR3(Pcursor->size.x / 2, Pcursor->size.x / 2, 0.0f);

		//// ���_�f�[�^���A�����b�N����
		//g_pD3DVtxBuffCursor->Unlock();
	}
}

CURSOR_PLAYER *GetCursorPlayer(void)
{
	return PcursorWk;
}

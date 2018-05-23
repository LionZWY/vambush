//=============================================================================
//
// �J�[�\������ [Ecursor.cpp]
// Author : �镶��
// �v���O�����쐬�� : 2018/3/09
//=============================================================================
#include "enemy_cursor.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "field.h"
#include "enemy.h"
#include "checkhit.h"
#include "player.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_CURSOR			"data/TEXTURE/�J�[�\���G.png"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	VALUE_MOVE_CURSOR		(0.30f)							// �ړ����x
#define	VALUE_JUMP				(10.0f)							// �W�����v��
#define	VALUE_GRAVITY			(0.45f)							// �d��
#define	RATE_REGIST				(0.075f)						// ��R�W��
#define	RATE_REFRECT			(-0.90f)						// ���ˌW��
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexCursorEnemy(LPDIRECT3DDEVICE9 pDevice);
void SetVertexCursorEnemy(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureCursorEnemy = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffCursorEnemy = NULL;	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

CURSOR_ENEMY			EcursorWk[1];
//=============================================================================
// ����������
//=============================================================================
HRESULT InitCursorEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CURSOR_ENEMY *Ecursor = EcursorWk;
	CAMERA *camera = GetCamera();
	ENEMY *enemy = GetEnemy();

	Ecursor->pos = D3DXVECTOR3(10.0f, 7.0f, 0.0f);
	Ecursor->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	Ecursor->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Ecursor->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Ecursor->size = D3DXVECTOR2(5.0f, 5.0f);
	Ecursor->lock = false;

	//�J�����̎��_�ƃJ�[�\���̋����v�Z
	float cVecX, cVecZ;
	cVecX = camera->posEye.x - Ecursor->pos.x;
	cVecZ = camera->posEye.z - Ecursor->pos.z;
	Ecursor->ECtoEPDistance = (sqrtf(cVecX * cVecX + cVecZ * cVecZ));



	// ���_���̍쐬
	MakeVertexCursorEnemy(pDevice);
	


	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
								TEXTURE_CURSOR,			// �t�@�C���̖��O
								&g_pD3DTextureCursorEnemy);	// �ǂݍ��ރ������[

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitCursorEnemy(void)
{
	if(g_pD3DTextureCursorEnemy != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureCursorEnemy->Release();
		g_pD3DTextureCursorEnemy = NULL;
	}

	if(g_pD3DVtxBuffCursorEnemy != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffCursorEnemy->Release();
		g_pD3DVtxBuffCursorEnemy = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateCursorEnemy(void)
{
	D3DXVECTOR3 rotCamera;
	CURSOR_ENEMY *Ecursor = EcursorWk;
	CAMERA *camera = GetCamera();
	ENEMY *enemy = GetEnemy();
	PLAYER *player = GetPlayer();

	//�J�����̎��_�ƃJ�[�\���̋����X�V
	float cVecX, cVecZ;
	cVecX = camera->posEye.x - Ecursor->pos.x;
	cVecZ = camera->posEye.z - Ecursor->pos.z;
	Ecursor->ECtoEPDistance = (sqrtf(cVecX * cVecX + cVecZ * cVecZ));

	//�J�[�\�����b�N����
	if (Ecursor->lock == false)
	{
		if ((GetKeyboardPress(DIK_T)) || (IsButtonPressed(1, R_BUTTON_UP)))
		{
			//Ecursor->lock = false;
			Ecursor->move.z += 0.35f;
		}
		else if ((GetKeyboardPress(DIK_G)) || (IsButtonPressed(1, R_BUTTON_DOWN)))
		{
			//Ecursor->lock = false;
			Ecursor->move.z -= 0.35f;
		}
		if ((GetKeyboardPress(DIK_F)) || (IsButtonPressed(1, R_BUTTON_LEFT)))
		{
			//Ecursor->lock = false;
			Ecursor->move.x -= 0.35f;
		}
		else if ((GetKeyboardPress(DIK_H)) || (IsButtonPressed(1, R_BUTTON_RIGHT)))
		{
			//Ecursor->lock = false;
			Ecursor->move.x += 0.35f;
		}

		if ((GetKeyboardPress(DIK_O)) || (IsButtonTriggered(1, BUTTON_R3)))
		{
			Ecursor->lock = true;
		}
	}
	else if (Ecursor->lock == true)
	{
		Ecursor->pos.x = player->pos.x;
		Ecursor->pos.z = player->pos.z;
		if (IsButtonTriggered(1, BUTTON_R3))
		{
			Ecursor->lock = false;
		}
	}

	if (Ecursor->rot.y > D3DX_PI)
	{
		// 360�x�𒴂�����360�x������
		Ecursor->rot.y -= D3DX_PI * 2.0f;
	}
	else if (Ecursor->rot.y < D3DX_PI)
	{
		// 360�x�𒴂�����360�x������
		Ecursor->rot.y += D3DX_PI * 2.0f;
	}


	Ecursor->pos.x += Ecursor->move.x;
	Ecursor->pos.z += Ecursor->move.z;

	Ecursor->move.x += (0.0f - Ecursor->move.x) * RATE_REGIST;
	Ecursor->move.z += (0.0f - Ecursor->move.z) * RATE_REGIST;

	//�J�[�\���T�C�Y�̍X�V
	Ecursor->size.x = (camera->EyeToAtDistance / 50.0f + (Ecursor->pos.z * 0.005f) + 15.0f);
	Ecursor->size.y = (camera->EyeToAtDistance / 50.0f + (Ecursor->pos.z * 0.005f) + 15.0f);

	if (Ecursor->pos.x < (Ecursor->size.x / 2) - FIELD_SCL_MAX_X)
	{
		Ecursor->pos.x = (Ecursor->size.x / 2) - FIELD_SCL_MAX_X;
	}
	if (Ecursor->pos.x > FIELD_SCL_MAX_X - (Ecursor->size.x / 2))
	{
		Ecursor->pos.x = FIELD_SCL_MAX_X - (Ecursor->size.x / 2);
	}
	if (Ecursor->pos.z > FIELD_SCL_MAX_Z)
	{
		Ecursor->pos.z = FIELD_SCL_MAX_Z;
	}
	if (Ecursor->pos.z < (Ecursor->size.y / 2)- FIELD_SCL_MAX_Z)
	{
		Ecursor->pos.z = (Ecursor->size.y / 2) - FIELD_SCL_MAX_Z;
	}

	SetVertexCursorEnemy();

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawCursorEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxscl, mtxTranslate,mtxRot;
	CURSOR_ENEMY *Ecursor = EcursorWk;

	// ���e�X�g��L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 150);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// ���C���e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// �r���[�}�g���b�N�X���擾
	mtxView = GetMtxView();

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&Ecursor->world);

	// �|���S���𐳖ʂɌ�����
	Ecursor->world._11 = mtxView._11;
	Ecursor->world._12 = mtxView._21;
	Ecursor->world._13 = mtxView._31;
	Ecursor->world._22 = mtxView._22;
	Ecursor->world._23 = mtxView._32;
	Ecursor->world._33 = mtxView._33;
	Ecursor->world._32 = mtxView._23;
	Ecursor->world._31 = mtxView._13;
	Ecursor->world._21 = mtxView._12;

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxscl, Ecursor->scl.x,
		Ecursor->scl.y,
		Ecursor->scl.z);
	D3DXMatrixMultiply(&Ecursor->world,
		&Ecursor->world, &mtxscl);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, Ecursor->rot.y, Ecursor->rot.x, Ecursor->rot.z);
	D3DXMatrixMultiply(&Ecursor->world, &Ecursor->world, &mtxRot);


	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, Ecursor->pos.x,
		Ecursor->pos.y,
		Ecursor->pos.z);
	D3DXMatrixMultiply(&Ecursor->world,
		&Ecursor->world, &mtxTranslate);



	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &Ecursor->world);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pD3DVtxBuffCursorEnemy, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureCursorEnemy);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	// ���C���e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
HRESULT MakeVertexCursorEnemy(LPDIRECT3DDEVICE9 pDevice)
{
	CURSOR_ENEMY *Ecursor = EcursorWk;
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
    if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
												D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
												FVF_VERTEX_3D,				// �g�p���钸�_�t�H�[�}�b�g
												D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
												&g_pD3DVtxBuffCursorEnemy,	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
												NULL)))						// NULL�ɐݒ�
	{
        return E_FAIL;
	}

	{
		SetVertexCursorEnemy();

		// �@���̐ݒ�
		Ecursor->vectex[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		Ecursor->vectex[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		Ecursor->vectex[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		Ecursor->vectex[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// ���ˌ��̐ݒ�
		Ecursor->vectex[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		Ecursor->vectex[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		Ecursor->vectex[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		Ecursor->vectex[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		Ecursor->vectex[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		Ecursor->vectex[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		Ecursor->vectex[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		Ecursor->vectex[3].tex = D3DXVECTOR2(1.0f, 0.0f);


		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffCursorEnemy->Unlock();
	}

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexCursorEnemy(void)
{
	CURSOR_ENEMY *Ecursor = EcursorWk;
	{	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffCursorEnemy->Lock(0, 0, (void**)&Ecursor->vectex, 0);

		Ecursor->vectex[0].vtx = D3DXVECTOR3(-Ecursor->size.x / 2, -Ecursor->size.x / 2, 0.0f);
		Ecursor->vectex[1].vtx = D3DXVECTOR3(-Ecursor->size.x / 2, Ecursor->size.x / 2, 0.0f);
		Ecursor->vectex[2].vtx = D3DXVECTOR3(Ecursor->size.x / 2, -Ecursor->size.x / 2, 0.0f);
		Ecursor->vectex[3].vtx = D3DXVECTOR3(Ecursor->size.x / 2, Ecursor->size.x / 2, 0.0f);

		//// ���_�f�[�^���A�����b�N����
		//g_pD3DVtxBuffCursor->Unlock();
	}
}

CURSOR_ENEMY *GetCursorEnemy(void)
{
	return EcursorWk;
}

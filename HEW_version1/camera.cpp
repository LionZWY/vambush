//=============================================================================
//
// �J�������� [camera.cpp]
// Author : �镶��
// �v���O�����쐬�� : 2018/3/09
//
//=============================================================================
#include "camera.h"
#include "input.h"
#include "enemy.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	CAM_POS_P_X			(0.0f)					// �J�����̎��_�����ʒu(X���W)
#define	CAM_POS_P_Y			(150.0f)				// �J�����̎��_�����ʒu(Y���W)
#define	CAM_POS_P_Z			(0.0f)					// �J�����̎��_�����ʒu(Z���W)
#define	CAM_POS_R_X			(0.0f)					// �J�����̒����_�����ʒu(X���W)
#define	CAM_POS_R_Y			(0.0f)					// �J�����̒����_�����ʒu(Y���W)
#define	CAM_POS_R_Z			(0.0f)					// �J�����̒����_�����ʒu(Z���W)
#define	VIEW_ANGLE			(D3DXToRadian(45.0f))							// �r���[���ʂ̎���p
#define	VIEW_ASPECT			((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// �r���[���ʂ̃A�X�y�N�g��
#define	VIEW_NEAR_Z			(10.0f)											// �r���[���ʂ�NearZ�l
#define	VIEW_FAR_Z			(5000.0f)										// �r���[���ʂ�FarZ�l
#define	VALUE_MOVE_CAMERA	(2.0f)											// �J�����̈ړ���
#define	VALUE_ROTATE_CAMERA	(D3DX_PI * 0.01f)								// �J�����̉�]��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

CAMERA				cameraWk[1];
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************


//=============================================================================
// �J�����̏���������
//=============================================================================
HRESULT InitCamera(void)
{
	CAMERA *camera = cameraWk;
	PLAYER *player = GetPlayer();
	ENEMY *enemy = GetEnemy();

	camera->posEye = D3DXVECTOR3(CAM_POS_P_X, CAM_POS_P_Y, CAM_POS_P_Z);
	camera->posAt = D3DXVECTOR3(CAM_POS_R_X, CAM_POS_R_X, CAM_POS_R_X);
	camera->vecUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	camera->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�G�l�~�[�ƃv���C���[�̋���
	float pVecX, pVecZ;
	pVecX = enemy->pos.x - player->pos.x;
	pVecZ = enemy->pos.z - player->pos.z;
	camera->PTPDistance = (sqrtf(pVecX * pVecX + pVecZ * pVecZ));

	//�J�������_�ƒ����_�̋���
	float fVecX,fVecZ;
	fVecX = camera->posEye.x - camera->posAt.x;
	fVecZ = camera->posEye.z - camera->posAt.z;
	camera->EyeToAtDistance = sqrtf(fVecX * fVecX + fVecZ * fVecZ);



	return S_OK;
}

//=============================================================================
// �J�����̏I������
//=============================================================================
void UninitCamera(void)
{

}

//=============================================================================
// �J�����̍X�V����
//=============================================================================
void UpdateCamera(void)
{
	CAMERA *camera = cameraWk;
	PLAYER *player = GetPlayer();
	ENEMY *enemy = GetEnemy();

	//�G�l�~�[�ƃv���C���[�̋����̍X�V
	float pVecX, pVecZ;
	pVecX = enemy->pos.x - player->pos.x;
	pVecZ = enemy->pos.z - player->pos.z;
	camera->PTPDistance = (sqrtf(pVecX * pVecX + pVecZ * pVecZ));
	camera->PTPVec = enemy->pos - player->pos;
	camera->PTPVec /= D3DXVec3Length(&camera->PTPVec);

	//�J�������_�ƒ����_�̋����̍X�V
	float fVecX, fVecZ;
	fVecX = camera->posEye.x - camera->posAt.x;
	fVecZ = camera->posEye.z - camera->posAt.z;
	camera->EyeToAtDistance = sqrtf(fVecX * fVecX + fVecZ * fVecZ);


	//�����_�Ǝ��_�̍X�V����
	if (GetKeyboardPress(DIK_Y))
	{// ���_�ړ��u��v
		camera->posEye.y += VALUE_MOVE_CAMERA;
	}
	if (GetKeyboardPress(DIK_N))
	{// ���_�ړ��u���v
		camera->posEye.y -= VALUE_MOVE_CAMERA;
	}

	if (player->pos == enemy->pos)
	{
		camera->posAt.x = player->pos.x;
		camera->posAt.z = player->pos.z;
	}
	else
	{
		camera->posAt.x = player->pos.x + camera->PTPVec.x * (camera->PTPDistance / 2);
		camera->posAt.z = player->pos.z + camera->PTPVec.z * (camera->PTPDistance / 2);
	}

	camera->posEye.x = camera->posAt.x - sinf(camera->rot.y) * camera->PTPDistance;
	if ((camera->PTPDistance >= 100.0f) && (camera->PTPDistance <= 630.0f))
	{

		camera->posEye.z = camera->posAt.z - cosf(camera->rot.y) * camera->PTPDistance;
		camera->posEye.y = camera->PTPDistance;
	}
	else
	{
		camera->posEye.z = camera->posAt.z - cosf(camera->rot.y) * camera->EyeToAtDistance;
		if (camera->PTPDistance < 300.0f)
		{
			camera->posEye.y = 100.0f;
		}
		else
		{
			camera->posEye.y = 630.0f;
		}
	}

}

//=============================================================================
// �J�����̐ݒ菈��
//=============================================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice(); 
	CAMERA *camera = cameraWk;

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&camera->view);

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&camera->view, 
						&camera->posEye,		// �J�����̎��_
						&camera->posAt,			// �J�����̒����_
						&camera->vecUp);		// �J�����̏����

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &camera->view);


	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&camera->proj);

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&camera->proj,
								VIEW_ANGLE,			// �r���[���ʂ̎���p
								VIEW_ASPECT,		// �r���[���ʂ̃A�X�y�N�g��
								VIEW_NEAR_Z,		// �r���[���ʂ�NearZ�l
								VIEW_FAR_Z);		// �r���[���ʂ�FarZ�l

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &camera->proj);
}

//=============================================================================
// �J�����̌����̎擾
//=============================================================================
D3DXVECTOR3 GetRotCamera(void)
{
	CAMERA *camera = cameraWk;

	return camera->rot;
}

//=============================================================================
// �r���[�}�g���b�N�X�̎擾
//=============================================================================
D3DXMATRIX GetMtxView(void)
{
	CAMERA *camera = cameraWk;

	return camera->view;
}

CAMERA *GetCamera(void)
{
	return cameraWk;
}
//=============================================================================
//
// �G�l�~�[���� [enemy.cpp]
// Author : �镶��
// �v���O�����쐬�� : 2018/3/09
//=============================================================================
#include "enemy.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "field.h"
#include "enemy_gun.h"
#include "enemy_bullet.h"
#include "enemy_skillNor.h"
#include "enemy_skillDef.h"
#include "enemy_skillSup.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexEnemy(LPDIRECT3DDEVICE9 pDevice);
void SetVertexEnemy(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureEnemyW = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureEnemyS = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureEnemyA = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureEnemyD = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffEnemy = NULL;	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

ENEMY			enemyWk[1];
//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY *enemy = enemyWk;

		enemy->pos = D3DXVECTOR3(50.0f, 7.0f, 0.0f);
		enemy->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		enemy->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		enemy->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		enemy->hp = ENEMY_HP_MAX;
		enemy->kill = 0;
		enemy->damage = false;
		enemy->norSk = true;
		enemy->timeSk = 0;
		enemy->defSk = true;
		enemy->timeDefSk = 0;
		enemy->supSk = false;


		// �e�̐ݒ�
		enemy->shadowId = CreateShadow(D3DXVECTOR3(enemy->pos.x + 3.0f, 0.1f, enemy->pos.z - 6.0f), D3DXVECTOR2(2.0f,1.0f));
		enemy->SizeShadow = D3DXVECTOR2(15.0f,15.0f);
		enemy->colShadow = D3DXCOLOR(50.0f, 50.0f, 50.0f, 50.0f);

		// ���_���̍쐬
		MakeVertexEnemy(pDevice);

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
			TEXTURE_ENEMY_W,			// �t�@�C���̖��O
			&g_pD3DTextureEnemyW);	// �ǂݍ��ރ������[
									// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
			TEXTURE_ENEMY_S,			// �t�@�C���̖��O
			&g_pD3DTextureEnemyS);	// �ǂݍ��ރ������[
									// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
			TEXTURE_ENEMY_A,			// �t�@�C���̖��O
			&g_pD3DTextureEnemyA);	// �ǂݍ��ރ������[
									// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
			TEXTURE_ENEMY_D,			// �t�@�C���̖��O
			&g_pD3DTextureEnemyD);	// �ǂݍ��ރ������[
	


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemy(void)
{
	if(g_pD3DTextureEnemyW != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureEnemyW->Release();
		g_pD3DTextureEnemyW = NULL;
	}
	if (g_pD3DTextureEnemyS != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureEnemyS->Release();
		g_pD3DTextureEnemyS = NULL;
	}
	if (g_pD3DTextureEnemyA != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureEnemyA->Release();
		g_pD3DTextureEnemyA = NULL;
	}
	if (g_pD3DTextureEnemyD != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureEnemyD->Release();
		g_pD3DTextureEnemyD = NULL;
	}


	if(g_pD3DVtxBuffEnemy != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffEnemy->Release();
		g_pD3DVtxBuffEnemy = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXVECTOR3 rotCamera;
	ENEMY *enemy = enemyWk;
	ENEMYGUN *enemygun = GetEnemyGun();
	ENEMY_NORSKILL *enemynorSkill = GetEnemyNorSkill(0);
	ENEMY_SKILLDEF *enemyskillDef = GetEnemySkillDef(0);
	ENEMY_SUPSKILL *enemysupSkill = GetEnemySupSkill(0);

	//�ړ��̍X�V
	{
		if ((GetKeyboardPress(DIK_W)) || (IsButtonPressed(1, BUTTON_UP)))
		{
			enemy->move.z += 0.3f;
		}
		else if ((GetKeyboardPress(DIK_S)) || (IsButtonPressed(1, BUTTON_DOWN)))
		{
			enemy->move.z -= 0.3f;
		}
		if ((GetKeyboardPress(DIK_A)) || (IsButtonPressed(1, BUTTON_LEFT)))
		{
			enemy->move.x -= 0.3f;
		}
		else if ((GetKeyboardPress(DIK_D)) || (IsButtonPressed(1, BUTTON_RIGHT)))
		{
			enemy->move.x += 0.3f;
		}

		//if (GetKeyboardPress(DIK_LSHIFT))
		//{
		//	enemy->rot.y -= D3DX_PI * 0.02f;
		//}
		//else if (GetKeyboardPress(DIK_RSHIFT))
		//{
		//	enemy->rot.y += D3DX_PI * 0.02f;
		//}

		//��]�p�x�̃��Z�b�g
		if (enemy->rot.y > D3DX_PI)
		{
			// 360�x�𒴂�����360�x������
			enemy->rot.y -= D3DX_PI * 2.0f;
		}
		else if (enemy->rot.y < D3DX_PI)
		{
			// 360�x�𒴂�����360�x������
			enemy->rot.y += D3DX_PI * 2.0f;
		}

		enemy->pos.x += enemy->move.x;
		enemy->pos.z += enemy->move.z;

		enemy->move.x += (0.0f - enemy->move.x) * RATE_REGIST_ENEMY;
		enemy->move.z += (0.0f - enemy->move.z) * RATE_REGIST_ENEMY;
	}

	//�ړ��͈͂̐ݒ�
	if (enemy->pos.x < (ENEMY_SIZE_X / 2) - FIELD_SCL_MAX_X)
	{
		enemy->pos.x = (ENEMY_SIZE_X / 2) - FIELD_SCL_MAX_X;
	}
	if (enemy->pos.x > FIELD_SCL_MAX_X - (ENEMY_SIZE_X / 2))
	{
		enemy->pos.x = FIELD_SCL_MAX_X - (ENEMY_SIZE_X / 2);
	}
	if (enemy->pos.z > FIELD_SCL_MAX_Z)
	{
		enemy->pos.z = FIELD_SCL_MAX_Z;
	}
	if (enemy->pos.z < (ENEMY_SIZE_Y / 2) - FIELD_SCL_MAX_Z)
	{
		enemy->pos.z = (ENEMY_SIZE_Y / 2) - FIELD_SCL_MAX_Z;
	}

	//�U������
	//�ʏ�e
	if ((GetKeyboardTrigger(DIK_RALT)) || (IsButtonTriggered(1, BUTTON_Z)))
	{

		PlaySound(SE_BULLET, E_DS8_FLAG_NONE);

		D3DXVECTOR3 pos;
		D3DXVECTOR3 move;
		D3DXVECTOR2 size;

		pos.x = enemy->pos.x - sinf(enemy->rot.y)* 2.0f;
		pos.y = enemy->pos.y;
		pos.z = enemy->pos.z - cosf(enemy->rot.y)* 2.0f;

		move.x = -sinf(enemygun->rot.y) * 7.5f;
		move.y = 0.0f;
		move.z = -cosf(enemygun->rot.y) * 7.5f;

		size.x = 10.0f;
		size.y = 10.0f;
		SetEnemyBullet(pos, move, size, 60 * 4);
	}

	//����e03
	if (enemy->norSk == true)
	{
		if ((GetKeyboardTrigger(DIK_U)) || (IsButtonTriggered(1, BUTTON_Y)))
		{

			PlaySound(SE_WARM, E_DS8_FLAG_NONE);

			D3DXVECTOR3 pos;
			D3DXVECTOR3 move;
			D3DXVECTOR2 size;

			pos.x = enemy->pos.x;
			pos.y = enemy->pos.y + 2.0f;
			pos.z = enemy->pos.z;

			move.x = -sinf(enemygun->rot.y) * 0.03f;
			move.y = 0.0f;
			move.z = -cosf(enemygun->rot.y) * 0.03f;

			size.x = 8.0f;
			size.y = 8.0f;
			SetEnemyNorSkill(pos, move, size, 60 * 40, EB_TYPE_NORMAL);
			enemy->norSk = false;

		}
		enemy->timeSk = 0;
	}
	else
	{
		enemy->timeSk++;
		if (enemy->timeSk / 300)
		{
			enemy->norSk = true;
		}

		if (enemynorSkill->cnt == 0)
		{
			enemy->norSk = false;
		}

	}
	//����e01
	if (enemy->defSk == true)
	{
		if ((GetKeyboardTrigger(DIK_V)) || (IsButtonTriggered(1, BUTTON_L)))
		{

			PlaySound(SE_CASCEDE, E_DS8_FLAG_NONE);

			D3DXVECTOR3 pos;
			D3DXVECTOR3 move;
			D3DXVECTOR2 size;
			int time = 0;

			pos.x = enemy->pos.x;
			pos.y = enemy->pos.y + 2.0f;
			pos.z = enemy->pos.z;

			move.x = -sinf(enemygun->rot.y) * 2.0f;
			move.y = 0.0f;
			move.z = -cosf(enemygun->rot.y) * 2.0f;

			size.x = 30.0f;
			size.y = 30.0f;

			SetEnemySkillDef(pos, move, size, 60 * 40);

			enemy->defSk = false;

		}
		enemy->timeDefSk = 0;
	}
	else
	{
		enemy->timeDefSk++;
		if (enemy->timeDefSk / 300)
		{
			enemy->defSk = true;
		}

		if (enemyskillDef->cnt == 0)
		{
			enemy->defSk = false;
		}

	}
	//����e02
	if (enemy->supSk == true)
	{
		if ((GetKeyboardTrigger(DIK_P)) || (IsButtonTriggered(1, BUTTON_R)))
		{

			PlaySound(SE_FLAME, E_DS8_FLAG_NONE);

			D3DXVECTOR3 pos;
			D3DXVECTOR3 move;
			D3DXVECTOR2 size;

			pos.x = enemy->pos.x;
			pos.y = enemy->pos.y + 2.0f;
			pos.z = enemy->pos.z;

			move.x = -sinf(enemygun->rot.y) * 10.0f;
			move.y = 0.0f;					  
			move.z = -cosf(enemygun->rot.y) * 10.0f;

			size.x = 10.0f;
			size.y = 10.0f;
			SetEnemySupSkill(pos, move, size, 60 * 40);
			enemy->supSk = false;

		}
	}

	{// �e�̐ݒ�
		SetPositionShadow(enemy->shadowId, D3DXVECTOR3(enemy->pos.x + 1.0f, 0.1f, enemy->pos.z - 6.0f));

		SetVertexShadow(enemy->shadowId, enemy->SizeShadow);
		SetColorShadow(enemy->shadowId, enemy->colShadow);
	}

	// ���_���̍쐬
	MakeVertexEnemy(pDevice);

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxscl, mtxTranslate,mtxRot;
	ENEMY *enemy = enemyWk;
	ENEMYGUN *enemygun = GetEnemyGun();

		// ���C���e�B���O�𖳌��ɂ���
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

		// �r���[�}�g���b�N�X���擾
		mtxView = GetMtxView();

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&enemy->world);

		// �|���S���𐳖ʂɌ�����
		enemy->world._11 = mtxView._11;
		enemy->world._12 = mtxView._21;
		enemy->world._13 = mtxView._31;
		enemy->world._22 = mtxView._22;
		enemy->world._23 = mtxView._32;
		enemy->world._33 = mtxView._33;
		enemy->world._32 = mtxView._23;
		enemy->world._31 = mtxView._13;
		enemy->world._21 = mtxView._12;

		// �X�P�[���𔽉f
		D3DXMatrixScaling(&mtxscl, enemy->scl.x,
			enemy->scl.y,
			enemy->scl.z);
		D3DXMatrixMultiply(&enemy->world,
			&enemy->world, &mtxscl);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, enemy->rot.y, enemy->rot.x, enemy->rot.z);
		D3DXMatrixMultiply(&enemy->world, &enemy->world, &mtxRot);


		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTranslate, enemy->pos.x,
			enemy->pos.y,
			enemy->pos.z);
		D3DXMatrixMultiply(&enemy->world,
			&enemy->world, &mtxTranslate);



		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &enemy->world);

		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, g_pD3DVtxBuffEnemy, 0, sizeof(VERTEX_3D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		//�e�N�X�`���̍X�V
		if (((enemygun->rot.y > -D3DX_PI * 0.25f) && (enemygun->rot.y <= D3DX_PI * 0.25f)) || ((enemygun->rot.y < D3DX_PI * 0.25f) && (enemygun->rot.y >= -D3DX_PI * 0.25f)))
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pD3DTextureEnemyS);
		}
		else if (((enemygun->rot.y > D3DX_PI * 0.25f) && (enemygun->rot.y <= D3DX_PI * 0.75f)) || ((enemygun->rot.y < -D3DX_PI * 1.25f) && (enemygun->rot.y >= -D3DX_PI * 1.75f)))
		{
			if ((enemygun->rot.y > D3DX_PI * 0.5f) || (enemygun->rot.y < -D3DX_PI * 1.5f))
			{
				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pD3DTextureEnemyD);
			}
			else
			{
				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pD3DTextureEnemyA);
			}
		}
		else if (((enemygun->rot.y > D3DX_PI * 0.75f) && (enemygun->rot.y <= D3DX_PI * 1.25f)) || ((enemygun->rot.y < -D3DX_PI * 0.75f) && (enemygun->rot.y >= -D3DX_PI * 1.25f)))
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pD3DTextureEnemyW);
		}
		else if (((enemygun->rot.y > D3DX_PI * 1.25f) && (enemygun->rot.y <= D3DX_PI * 1.75f)) || ((enemygun->rot.y < -D3DX_PI * 0.25f) && (enemygun->rot.y >= -D3DX_PI * 0.75f)))
		{
			if ((enemygun->rot.y >= D3DX_PI * 1.5f) || (enemygun->rot.y <= -D3DX_PI * 0.5f))
			{
				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pD3DTextureEnemyD);
			}
			else
			{
				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pD3DTextureEnemyA);
			}

		}

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

		// ���C���e�B���O��L���ɂ���
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
HRESULT MakeVertexEnemy(LPDIRECT3DDEVICE9 pDevice)
{
	ENEMY *enemy = enemyWk;
	ENEMYGUN *enemygun = GetEnemyGun();
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
    if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
												D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
												FVF_VERTEX_3D,				// �g�p���钸�_�t�H�[�}�b�g
												D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
												&g_pD3DVtxBuffEnemy,	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
												NULL)))						// NULL�ɐݒ�
	{
        return E_FAIL;
	}

	{
		SetVertexEnemy();

		// �@���̐ݒ�
		enemy->vectex[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		enemy->vectex[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		enemy->vectex[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		enemy->vectex[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// ���ˌ��̐ݒ�
		enemy->vectex[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		enemy->vectex[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		enemy->vectex[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		enemy->vectex[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		if (((enemygun->rot.y > D3DX_PI * 0.25f) && (enemygun->rot.y <= D3DX_PI * 0.75f)) || ((enemygun->rot.y < -D3DX_PI * 1.25f) && (enemygun->rot.y >= -D3DX_PI * 1.75f)))
		{
			// �e�N�X�`�����W�̐ݒ�
			enemy->vectex[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			enemy->vectex[3].tex = D3DXVECTOR2(0.0f, 0.0f);
			enemy->vectex[0].tex = D3DXVECTOR2(1.0f, 1.0f);
			enemy->vectex[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		}
		else
		{
			// �e�N�X�`�����W�̐ݒ�
			enemy->vectex[0].tex = D3DXVECTOR2(0.0f, 1.0f);
			enemy->vectex[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			enemy->vectex[2].tex = D3DXVECTOR2(1.0f, 1.0f);
			enemy->vectex[3].tex = D3DXVECTOR2(1.0f, 0.0f);
		}


		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffEnemy->Unlock();
	}

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexEnemy(void)
{
	ENEMY *enemy = enemyWk;
	{	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffEnemy->Lock(0, 0, (void**)&enemy->vectex, 0);

		enemy->vectex[0].vtx = D3DXVECTOR3(-ENEMY_SIZE_X / 2, -ENEMY_SIZE_X / 2, 0.0f);
		enemy->vectex[1].vtx = D3DXVECTOR3(-ENEMY_SIZE_X / 2, ENEMY_SIZE_X / 2, 0.0f);
		enemy->vectex[2].vtx = D3DXVECTOR3(ENEMY_SIZE_X / 2, -ENEMY_SIZE_X / 2, 0.0f);
		enemy->vectex[3].vtx = D3DXVECTOR3(ENEMY_SIZE_X / 2, ENEMY_SIZE_X / 2, 0.0f);

		//// ���_�f�[�^���A�����b�N����
		//g_pD3DVtxBuffEnemy->Unlock();
	}
}

ENEMY *GetEnemy(void)
{
	return enemyWk;
}
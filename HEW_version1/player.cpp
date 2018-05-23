//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : �镶��
// �v���O�����쐬�� : 2018/3/09
//=============================================================================
#include "player.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "field.h"
#include "player_cursor.h"
#include "player_gun.h"
#include "player_bullet.h"
#include "player_skillNor.h"
#include "player_skillDef.h"
#include "player_skillSup.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexPlayer(LPDIRECT3DDEVICE9 pDevice);
void SetVertexPlayer(void);
void SetTexturePlayer(int cntPattern);
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTexturePlayerW = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTexturePlayerS = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTexturePlayerA = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTexturePlayerD = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffPlayer = NULL;	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

PLAYER			playerWk[1];
//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER *player = playerWk;

	player->pos = D3DXVECTOR3(-50.0f, 7.0f, 0.0f);
	player->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	player->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	player->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	player->hp = PLAYER_HP_MAX;
	player->kill = 0;
	player->damage = false;
	player->norSk = true;
	player->timeSk = 0;
	player->defSk = true;
	player->timeDefSk = 0;
	player->supSk = false;
	//player->patternAnim = 1;

	// �e�̐ݒ�
	player->shadowId = CreateShadow(D3DXVECTOR3(player->pos.x + 3.0f,0.1f,player->pos.z - 6.0f),D3DXVECTOR2(2.0f,1.0f));
	player->SizeShadow = D3DXVECTOR2(10.0f,10.0f);
	player->colShadow = D3DXCOLOR(50.0f, 50.0f, 50.0f, 50.0f);

	// ���_���̍쐬
	MakeVertexPlayer(pDevice);
	


	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
								TEXTURE_PLAYER_W,			// �t�@�C���̖��O
								&g_pD3DTexturePlayerW);	// �ǂݍ��ރ������[
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
								TEXTURE_PLAYER_S,			// �t�@�C���̖��O
								&g_pD3DTexturePlayerS);	// �ǂݍ��ރ������[
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
								TEXTURE_PLAYER_A,			// �t�@�C���̖��O
								&g_pD3DTexturePlayerA);	// �ǂݍ��ރ������[
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
								TEXTURE_PLAYER_D,			// �t�@�C���̖��O
								&g_pD3DTexturePlayerD);	// �ǂݍ��ރ������[


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{
	if(g_pD3DTexturePlayerW != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTexturePlayerW->Release();
		g_pD3DTexturePlayerW = NULL;
	}
	if (g_pD3DTexturePlayerS != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTexturePlayerS->Release();
		g_pD3DTexturePlayerS = NULL;
	}
	if (g_pD3DTexturePlayerA != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTexturePlayerA->Release();
		g_pD3DTexturePlayerA = NULL;
	}
	if (g_pD3DTexturePlayerD != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTexturePlayerD->Release();
		g_pD3DTexturePlayerD = NULL;
	}

	if(g_pD3DVtxBuffPlayer != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffPlayer->Release();
		g_pD3DVtxBuffPlayer = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXVECTOR3 rotCamera;
	PLAYER *player = playerWk;
	PLAYERGUN *playergun = GetPlayerGun();

	PLAYER_NORSKILL *playernorSkill = GetPlayerNorSkill(0);
	PLAYER_SKILLDEF *playerskillDef = GetPlayerSkillDef(0);
	PLAYER_SUPSKILL *playersupSkill = GetPlayerSupSkill(0);

	//�ړ��̍X�V
	{
		if ((GetKeyboardPress(DIK_UP)) || (IsButtonPressed(0, BUTTON_UP)))
		{
			player->move.z += 0.3f;
		}
		else if ((GetKeyboardPress(DIK_DOWN)) || (IsButtonPressed(0, BUTTON_DOWN)))
		{
			player->move.z -= 0.3f;
		}
		if ((GetKeyboardPress(DIK_LEFT)) || (IsButtonPressed(0, BUTTON_LEFT)))
		{
			player->move.x -= 0.3f;
		}
		else if ((GetKeyboardPress(DIK_RIGHT)) || (IsButtonPressed(0, BUTTON_RIGHT)))
		{
			player->move.x += 0.3f;
		}
	}

	//if (GetKeyboardPress(DIK_LSHIFT))
	//{
	//	player->rot.y -= D3DX_PI * 0.02f;
	//}
	//else if (GetKeyboardPress(DIK_RSHIFT))
	//{
	//	player->rot.y += D3DX_PI * 0.02f;
	//}

	if (player->rot.y > D3DX_PI)
	{
		// 360�x�𒴂�����360�x������
		player->rot.y -= D3DX_PI * 2.0f;
	}
	else if (player->rot.y < D3DX_PI)
	{
		// 360�x�𒴂�����360�x������
		player->rot.y += D3DX_PI * 2.0f;
	}

	player->pos.x += player->move.x;
	player->pos.z += player->move.z;

	player->move.x += (0.0f - player->move.x) * RATE_REGIST_PLAYER;
	player->move.z += (0.0f - player->move.z) * RATE_REGIST_PLAYER;


	if (player->pos.x < (PLAYER_SIZE_X / 2) - FIELD_SCL_MAX_X)
	{
		player->pos.x = (PLAYER_SIZE_X / 2) - FIELD_SCL_MAX_X;
	}
	if (player->pos.x > FIELD_SCL_MAX_X - (PLAYER_SIZE_X / 2))
	{
		player->pos.x = FIELD_SCL_MAX_X - (PLAYER_SIZE_X / 2);
	}
	if (player->pos.z > FIELD_SCL_MAX_Z)
	{
		player->pos.z = FIELD_SCL_MAX_Z;
	}
	if (player->pos.z < (PLAYER_SIZE_Y / 2)- FIELD_SCL_MAX_Z)
	{
		player->pos.z = (PLAYER_SIZE_Y / 2) - FIELD_SCL_MAX_Z;
	}

	//�U������
	//�ʏ�e
	if ((GetKeyboardTrigger(DIK_SPACE)) || (IsButtonTriggered(0, BUTTON_Z)))
	{

		PlaySound(SE_BULLET, E_DS8_FLAG_NONE);

		D3DXVECTOR3 pos;
		D3DXVECTOR3 move;
		D3DXVECTOR2 size;

		pos.x = player->pos.x - sinf(player->rot.y)* 2.0f;
		pos.y = player->pos.y;
		pos.z = player->pos.z - cosf(player->rot.y)* 2.0f;

		move.x = -sinf(playergun->rot.y) * 7.5f;
		move.y = 0.0f;
		move.z = -cosf(playergun->rot.y) * 7.5f;

		size.x = 10.0f;
		size.y = 10.0f;
		SetPlayerBullet(pos, move, size, 60 * 4);
	}

	//����e03
	if (player->norSk == true)
	{
		if ((GetKeyboardTrigger(DIK_C)) || (IsButtonTriggered(0, BUTTON_Y)))
		{

			PlaySound(SE_WARM, E_DS8_FLAG_NONE);

			D3DXVECTOR3 pos;
			D3DXVECTOR3 move;
			D3DXVECTOR2 size;

			pos.x = player->pos.x;
			pos.y = player->pos.y + 2.0f;
			pos.z = player->pos.z;

			move.x = -sinf(playergun->rot.y) * 0.03f;
			move.y = 0.0f;
			move.z = -cosf(playergun->rot.y) * 0.03f;

			size.x = 8.0f;
			size.y = 8.0f;
			SetPlayerNorSkill(pos, move, size, 60 * 40, PB_TYPE_NORMAL);
			player->norSk = false;

		}
		player->timeSk = 0;
	}
	else
	{
		player->timeSk++;
		if (player->timeSk / 300)
		{
			player->norSk = true;
		}

		if (playernorSkill->cnt == 0)
		{
			player->norSk = false;
		}
	}
	//����e01
	if (player->defSk == true)
	{
		if ((GetKeyboardTrigger(DIK_V)) || (IsButtonTriggered(0, BUTTON_L)))
		{

			PlaySound(SE_CASCEDE, E_DS8_FLAG_NONE);

			D3DXVECTOR3 pos;
			D3DXVECTOR3 move;
			D3DXVECTOR2 size;
			int time = 0;

			pos.x = player->pos.x;
			pos.y = player->pos.y + 2.0f;
			pos.z = player->pos.z;

			move.x = -sinf(playergun->rot.y) * 2.0f;
			move.y = 0.0f;					   
			move.z = -cosf(playergun->rot.y) * 2.0f;

			size.x = 30.0f;
			size.y = 30.0f;

			SetPlayerSkillDef(pos, move, size, 60 * 40);

			player->defSk = false;

		}
		player->timeDefSk = 0;
	}
	else
	{
		player->timeDefSk++;
		if (player->timeDefSk / 300)
		{
			player->defSk = true;
		}

		if (playerskillDef->cnt == 0)
		{
			player->defSk = false;
		}

	}
	//����e02
	if (player->supSk == true)
	{
		if ((GetKeyboardTrigger(DIK_P)) || (IsButtonTriggered(0, BUTTON_R)))
		{

			PlaySound(SE_FLAME, E_DS8_FLAG_NONE);

			D3DXVECTOR3 pos;
			D3DXVECTOR3 move;
			D3DXVECTOR2 size;

			pos.x = player->pos.x;
			pos.y = player->pos.y + 2.0f;
			pos.z = player->pos.z;

			move.x = -sinf(playergun->rot.y) * 10.0f;
			move.y = 0.0f;
			move.z = -cosf(playergun->rot.y) * 10.0f;

			size.x = 10.0f;
			size.y = 10.0f;
			SetPlayerSupSkill(pos, move, size, 60 * 40);
			player->supSk = false;

		}
	}

	{// �e�̐ݒ�
		SetPositionShadow(player->shadowId, D3DXVECTOR3(player->pos.x + 1.0f, 0.1f, player->pos.z - 6.0f));

		SetVertexShadow(player->shadowId, player->SizeShadow);
		SetColorShadow(player->shadowId, player->colShadow);
	}

	MakeVertexPlayer(pDevice);

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxscl, mtxTranslate,mtxRot;
	PLAYER *player = playerWk;
	PLAYERGUN *playergun = GetPlayerGun();
	

	// ���e�X�g��L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 150);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// ���C���e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// �r���[�}�g���b�N�X���擾
	mtxView = GetMtxView();

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&player->world);

	// �|���S���𐳖ʂɌ�����
	player->world._11 = mtxView._11;
	player->world._12 = mtxView._21;
	player->world._13 = mtxView._31;
	player->world._22 = mtxView._22;
	player->world._23 = mtxView._32;
	player->world._33 = mtxView._33;
	player->world._32 = mtxView._23;
	player->world._31 = mtxView._13;
	player->world._21 = mtxView._12;

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxscl, player->scl.x,
		player->scl.y,
		player->scl.z);
	D3DXMatrixMultiply(&player->world,
		&player->world, &mtxscl);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, player->rot.y, player->rot.x, player->rot.z);
	D3DXMatrixMultiply(&player->world, &player->world, &mtxRot);


	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, player->pos.x,
		player->pos.y,
		player->pos.z);
	D3DXMatrixMultiply(&player->world,
		&player->world, &mtxTranslate);



	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &player->world);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pD3DVtxBuffPlayer, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	if (((playergun->rot.y > -D3DX_PI * 0.25f) && (playergun->rot.y <= D3DX_PI * 0.25f)) || ((playergun->rot.y < D3DX_PI * 0.25f) && (playergun->rot.y >= -D3DX_PI * 0.25f)))
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTexturePlayerS);
	}
	else if (((playergun->rot.y > D3DX_PI * 0.25f) && (playergun->rot.y <= D3DX_PI * 0.75f)) || ((playergun->rot.y < -D3DX_PI * 1.25f) && (playergun->rot.y >= -D3DX_PI * 1.75f)))
	{
		if ((playergun->rot.y > D3DX_PI * 0.5f) || (playergun->rot.y < -D3DX_PI * 1.5f))
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pD3DTexturePlayerD);
		}
		else
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pD3DTexturePlayerA);
		}
	}
	else if (((playergun->rot.y > D3DX_PI * 0.75f) && (playergun->rot.y <= D3DX_PI * 1.25f)) || ((playergun->rot.y < -D3DX_PI * 0.75f) && (playergun->rot.y >= -D3DX_PI * 1.25f)))
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTexturePlayerW);
	}
	else if (((playergun->rot.y > D3DX_PI * 1.25f) && (playergun->rot.y <= D3DX_PI * 1.75f)) || ((playergun->rot.y < -D3DX_PI * 0.25f) && (playergun->rot.y >= -D3DX_PI * 0.75f)))
	{
		if ((playergun->rot.y > D3DX_PI * 1.5f) || (playergun->rot.y < -D3DX_PI * 0.5f))
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pD3DTexturePlayerD);
		}
		else
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pD3DTexturePlayerA);
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
HRESULT MakeVertexPlayer(LPDIRECT3DDEVICE9 pDevice)
{
	PLAYER *player = playerWk;
	PLAYERGUN *playergun = GetPlayerGun();
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
    if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
												D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
												FVF_VERTEX_3D,				// �g�p���钸�_�t�H�[�}�b�g
												D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
												&g_pD3DVtxBuffPlayer,	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
												NULL)))						// NULL�ɐݒ�
	{
        return E_FAIL;
	}

	{
		SetVertexPlayer();

		// �@���̐ݒ�
		player->vectex[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		player->vectex[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		player->vectex[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		player->vectex[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// ���ˌ��̐ݒ�
		player->vectex[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		player->vectex[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		player->vectex[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		player->vectex[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		if (((playergun->rot.y > D3DX_PI * 0.25f) && (playergun->rot.y <= D3DX_PI * 0.75f)) || ((playergun->rot.y < -D3DX_PI * 1.25f) && (playergun->rot.y >= -D3DX_PI * 1.75f)))
		{
			// �e�N�X�`�����W�̐ݒ�
			player->vectex[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			player->vectex[3].tex = D3DXVECTOR2(0.0f, 0.0f);
			player->vectex[0].tex = D3DXVECTOR2(1.0f, 1.0f);
			player->vectex[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		}
		else
		{
			// �e�N�X�`�����W�̐ݒ�
			player->vectex[0].tex = D3DXVECTOR2(0.0f, 1.0f);
			player->vectex[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			player->vectex[2].tex = D3DXVECTOR2(1.0f, 1.0f);
			player->vectex[3].tex = D3DXVECTOR2(1.0f, 0.0f);
		}

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffPlayer->Unlock();
	}

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexPlayer(void)
{
	PLAYER *player = playerWk;
	{	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffPlayer->Lock(0, 0, (void**)&player->vectex, 0);

		player->vectex[0].vtx = D3DXVECTOR3(-PLAYER_SIZE_X / 2, -PLAYER_SIZE_X / 2, 0.0f);
		player->vectex[1].vtx = D3DXVECTOR3(-PLAYER_SIZE_X / 2, PLAYER_SIZE_X / 2, 0.0f);
		player->vectex[2].vtx = D3DXVECTOR3(PLAYER_SIZE_X / 2, -PLAYER_SIZE_X / 2, 0.0f);
		player->vectex[3].vtx = D3DXVECTOR3(PLAYER_SIZE_X / 2, PLAYER_SIZE_X / 2, 0.0f);

		//// ���_�f�[�^���A�����b�N����
		//g_pD3DVtxBuffPlayer->Unlock();
	}
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTexturePlayer(int cntPattern)
{
	PLAYER *player = playerWk;

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y;

	player->vectex[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	player->vectex[1].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	player->vectex[2].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
	player->vectex[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
}


PLAYER *GetPlayer(void)
{
	return playerWk;
}
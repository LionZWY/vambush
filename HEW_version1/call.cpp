//=============================================================================
//
// CALL��ʏ��� [call.cpp]
// Author : ���ˌ��j��
// �v���O�����쐬�� : 2018/3/09
//
//=============================================================================

#include "call.h"						// �}�N�����\���̎g�p�̈�
#include "main.h"						// �}�N���g�p�̈�
#include "game.h"						// ����
#include "title.h"						// ����
#include "debugproc.h"					// ����(�f�o�b�O�p)
#include "sound.h"						// �֐��g�p�̈�
#include "timer.h"						// �}�N���g�p�̈�

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexCall(int no);			// ���_�쐬�֐�
void SetVertexCallEffect(int no);			// �G�t�F�N�g�֐�

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

CALL callWk[CALL_MAX];						// �^�C�g���\���̍ő吔�錾

int start_cnt;

bool start_flag;
bool start_bgm;

//float sizex, sizey;						// �f�o�b�O�p�e�N�X�`���ړ������ϐ�

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT InitCall(int type)
{

	// �|�C���^�̏�����
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CALL *call = &callWk[0];

	start_flag = false;
	start_bgm = false;
	start_cnt = START_TIME_CALL*FRAME_CNT;

	//// �f�o�b�O�p�e�N�X�`���ړ������ϐ��̏�����
	//sizex = CALL_SKILL_PAR_SIZE_X;
	//sizey = CALL_SKILL_PAR_SIZE_Y;

	// �\���̍ő吔����������
	for(int i = 0; i < CALL_MAX;i++, call++)
	{
		call->PatternAnim = 3;								// �A�j���p�^�[���ԍ��������_���ŏ�����
		call->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ��]�̏�����

		// ���N����
		if (type == FIRST)
		{

			// �S��NULL�ŏ�����
			call->Texture = NULL;

			// HP�o�[���n
			if (i == CALL_NUM)
			{
				// �ʒu�̐ݒ�
				call->use = true;						// �g�p�ŏ���
				call->pos = CALL_BASE_POS;				// HP�o�[���n�̈ʒu�̏�����

				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					CALL_BASE_TEXTURE,				// �t�@�C���̖��O
					&call->Texture);					// �ǂݍ��ރ������[
			}

			// HP�o�[���n
			if (i == CALL_BATTLE)
			{
				// �ʒu�̐ݒ�
				call->use = false;						// �g�p�ŏ���
				call->pos = CALL_BASE_POS;				// HP�o�[���n�̈ʒu�̏�����

														// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
					CALL_BATTLE_TEXTURE,				// �t�@�C���̖��O
					&call->Texture);					// �ǂݍ��ރ������[
			}



			// ���_���̍쐬
			MakeVertexCall(i);
		}

		else if (type == UPDATA)
		{
			// HP�o�[���n
			if (i == CALL_NUM)
			{
				// �ʒu�̐ݒ�
				call->use = true;						// �g�p�ŏ���
			}

			// HP�o�[���n
			if (i == CALL_BATTLE)
			{
				// �ʒu�̐ݒ�
				call->use = false;						// �g�p�ŏ���
			}

		}
	}

	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void UninitCall(void)
{
	// �|�C���^�̏�����
	CALL *call = &callWk[0];

	// �\���̍ő吔�I������
	for (int i = 0; i < CALL_MAX;i++, call++)
	{

		// �e�N�X�`���̊J���o���Ă��Ȃ�������
		if (call->Texture != NULL)
		{

			// �e�N�X�`���̊J��
			call->Texture->Release();
			call->Texture = NULL;
		}
	}

}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void UpdateCall(void)
{

	// �|�C���^�̏�����
	CALL *call = &callWk[CALL_NUM];
	CALL *callB = &callWk[CALL_BATTLE];

	int Bcnt;
	Bcnt = 0;

	// �Q�[���X�^�[�g��
	if (start_bgm == false)
	{
		// �X�^�[�g�R�[���Đ�
		PlaySound(BGM_CALL_START, E_DS8_FLAG_NONE);

		// �t���O���g�p�ɕω�
		start_bgm = true;
	}

	// ���t���[���f�N�������g
	start_cnt--;

	// �t���[����b���ɒ���
	Bcnt= start_cnt / FRAME_CNT;
	
	// �p�^�[���̐؂�ւ�
	call->PatternAnim = Bcnt;

	// �e�N�X�`�����W��ݒ�
	SetTextureCall(CALL_NUM, call->PatternAnim);

	if (Bcnt == 0)
	{
		call->use = false;
	}

	if (call->use == false)
	{
		callB->use = true;
	}

	if (start_cnt == 0)
	{
		callB->use = false;
		start_flag = true;
	}


//		// �f�o�b�O�p�ړ��g�又��
//		if (i == CALL_SKILL_PAR)
//		{
//
//			// ��
//			if (GetKeyboardPress(DIK_V))
//			{
//				call->pos.x--;
//			}
//
//			// �E
//			else if (GetKeyboardPress(DIK_B))
//			{
//				call->pos.x++;
//			}
//
//			// ��
//			if (GetKeyboardPress(DIK_N))
//			{
//				call->pos.y--;
//
//			}
//			// ��
//			else if (GetKeyboardPress(DIK_M))
//			{
//				call->pos.y++;
//			}
//
//			// x�g��
//			if (GetKeyboardPress(DIK_I))
//			{
//				sizex++;
//			}
//
//			// x�k��
//			else if (GetKeyboardPress(DIK_O))
//			{
//				sizex--;
//			}
//
//			// Y�g��
//			if (GetKeyboardPress(DIK_K))
//			{
//				sizey++;
//
//			}
//			// Y�k��
//			else if (GetKeyboardPress(DIK_L))
//			{
//				sizey--;
//			}
//
//			// �f�o�b�N��
//#ifdef _DEBUG
//			// �f�o�b�N�\��
//			PrintDebugProc("�T�C�Y:x%f)\n", sizex*2);
//			PrintDebugProc("�T�C�Y:y%f)\n", sizey*2);
//			PrintDebugProc("���W:X %f)\n", call->pos.x);
//			PrintDebugProc("���W:Y %f)\n", call->pos.y);
//#endif
//		}


}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void DrawCall(void)
{
	// �|�C���^�̏�����
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CALL *call = &callWk[0];
	
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);


	// �\���̍ő吔�I������
	for (int i = 0; i < CALL_MAX;i++, call++)
	{
		// �g�p���Ă�����
		if (call->use == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, call->Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, call->vertex, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�쐬�֐�
//=============================================================================
HRESULT MakeVertexCall(int no)
{
	
	// �|�C���^�̏�����
	CALL *call = &callWk[no];

	//  HP�o�[���n
	if (no==CALL_NUM)
	{
		// ���_���W�̐ݒ�
		call->vertex[0].vtx = D3DXVECTOR3(call->pos.x - CALL_BASE_SIZE_X, call->pos.y - CALL_BASE_SIZE_Y, 0.0f);
		call->vertex[1].vtx = D3DXVECTOR3(call->pos.x + CALL_BASE_SIZE_X, call->pos.y - CALL_BASE_SIZE_Y, 0.0f);
		call->vertex[2].vtx = D3DXVECTOR3(call->pos.x - CALL_BASE_SIZE_X, call->pos.y + CALL_BASE_SIZE_Y, 0.0f);
		call->vertex[3].vtx = D3DXVECTOR3(call->pos.x + CALL_BASE_SIZE_X, call->pos.y + CALL_BASE_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		call->vertex[0].diffuse = COLOR_RED;
		call->vertex[1].diffuse = COLOR_BULE;
		call->vertex[2].diffuse = COLOR_RED;
		call->vertex[3].diffuse = COLOR_BULE;

	}

	//  HP�o�[���n
	if (no == CALL_BATTLE)
	{
		// ���_���W�̐ݒ�
		call->vertex[0].vtx = D3DXVECTOR3(call->pos.x - CALL_BATTLE_SIZE_X, call->pos.y - CALL_BATTLE_SIZE_Y, 0.0f);
		call->vertex[1].vtx = D3DXVECTOR3(call->pos.x + CALL_BATTLE_SIZE_X, call->pos.y - CALL_BATTLE_SIZE_Y, 0.0f);
		call->vertex[2].vtx = D3DXVECTOR3(call->pos.x - CALL_BATTLE_SIZE_X, call->pos.y + CALL_BATTLE_SIZE_Y, 0.0f);
		call->vertex[3].vtx = D3DXVECTOR3(call->pos.x + CALL_BATTLE_SIZE_X, call->pos.y + CALL_BATTLE_SIZE_Y, 0.0f);

		// ���ˌ��̐ݒ�
		call->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		call->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		call->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		call->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}


	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	call->vertex[0].rhw =
	call->vertex[1].rhw =
	call->vertex[2].rhw =
	call->vertex[3].rhw = 1.0f;


	// �e�N�X�`�����W�̐ݒ�
	call->vertex[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	call->vertex[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	call->vertex[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	call->vertex[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�ݒ�֐�
//=============================================================================
void SetTextureCall(int no, int cntPattern)
{

	// �|�C���^�̏�����
	CALL *call = &callWk[no];

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % CALL_ANIM_PATTERN_DIVIDE_X;
	int y = cntPattern / CALL_ANIM_PATTERN_DIVIDE_Y;
	float sizeX = 1.0f / CALL_ANIM_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / CALL_ANIM_PATTERN_DIVIDE_Y;
	call->vertex[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	call->vertex[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	call->vertex[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	call->vertex[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}


//=============================================================================
// �X�^�[�g�t���O�擾�֐�
//=============================================================================
bool *GetStartFlag(void)
{
	return(&start_flag);
}

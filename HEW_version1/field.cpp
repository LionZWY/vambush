//=============================================================================
//
// ���b�V���n�ʂ̏��� [field.cpp]
// Author : ���ˌ��j��
// �v���O�����쐬�� : 2018/3/09
//
//=============================================================================
#include "field.h"
#include "main.h"
#include "input.h"
#include "game.h"
#include "title.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

bool					effectflagF;				// �G�t�F�N�g�p����ϐ�
float					effectF;					// �G�t�F�N�g�p�ϐ�

FIELD		fieldWk[FIELD_MAX];
float		wave=0.0f;

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT InitField(int type)
{

	// �|�C���^�̏�����
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	FIELD *field = &fieldWk[0];

	// �G�t�F�N�g�֌W�̏�����
	effectflagF = true;				// true:�v���X���� false:�}�C�i�X����
	effectF = 0.0f;			// �G�t�F�N�g�̃��l�̏�����

	// ���N����
	if (type == FIRST)
	{

	// �\���̍ő吔����������
	for (int i = 0;i < FIELD_MAX;i++, field++)
	{

		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^��
		// �C���f�b�N�X�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^�̏�����
		field->VtxField = NULL;
		field->IdxField = NULL;
		field->Texture = NULL;// �e�N�X�`���ǂݍ��ݏꏊ

		 //�w�i
		if (i == FIELD_BG)
		{
			// �|���S���\���ʒu�̒��S���W��ݒ�
			field->pos = FIELD_BG_POS;
			field->rot = D3DXVECTOR3(0.0f,0.0f, 0.0f);

			// �u���b�N���̐ݒ�
			field->blockX = NUM_BG_BLOCK_X;
			field->blockZ = NUM_BG_BLOCK_Z;

			// ���_���̐ݒ�
			field->vertex = (NUM_BG_BLOCK_X + 1) * (NUM_BG_BLOCK_Z + 1);

			// �C���f�b�N�X���̐ݒ�
			field->vertexIndex = (NUM_BG_BLOCK_X + 1) * 2 * NUM_BG_BLOCK_Z + (NUM_BG_BLOCK_Z - 1) * 2;

			// �|���S�����̐ݒ�
			field->polygon = NUM_BG_BLOCK_X * NUM_BG_BLOCK_Z * 2 + (NUM_BG_BLOCK_Z - 1) * 4;

			// �u���b�N�T�C�Y�̐ݒ�
			field->sizeX = SIZE_BG_BLOCK_X;
			field->sizeZ = SIZE_BG_BLOCK_Z;

			// �e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
				TEXTURE_BG,						// �t�@�C���̖��O
				&field->Texture);				// �ǂݍ��ރ������[

		}

		// �w�i�G�t�F�N�g
		else if(i == FIELD_BG_EFFECT)
		{
			 // �|���S���\���ʒu�̒��S���W��ݒ�
			field->pos = FIELD_BG_POS;
			field->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// �u���b�N���̐ݒ�
			field->blockX = NUM_BG_BLOCK_X;
			field->blockZ = NUM_BG_BLOCK_Z;

			// ���_���̐ݒ�
			field->vertex = (NUM_BG_BLOCK_X + 1) * (NUM_BG_BLOCK_Z + 1);

			// �C���f�b�N�X���̐ݒ�
			field->vertexIndex = (NUM_BG_BLOCK_X + 1) * 2 * NUM_BG_BLOCK_Z + (NUM_BG_BLOCK_Z - 1) * 2;

			// �|���S�����̐ݒ�
			field->polygon = NUM_BG_BLOCK_X * NUM_BG_BLOCK_Z * 2 + (NUM_BG_BLOCK_Z - 1) * 4;

			// �u���b�N�T�C�Y�̐ݒ�
			field->sizeX = SIZE_BG_BLOCK_X;
			field->sizeZ = SIZE_BG_BLOCK_Z;

			// �e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
				TEXTURE_BG_EFFECT,				// �t�@�C���̖��O
				&field->Texture);				// �ǂݍ��ރ������[


		}

		// �o�g��
		else if (i == FIELD_BATTLE)
		{
			// �|���S���\���ʒu�̒��S���W��ݒ�
			field->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			field->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// �u���b�N���̐ݒ�
			field->blockX = FIELD_BG_NUM_BLOCK_X;
			field->blockZ = FIELD_BG_NUM_BLOCK_Z;

			// ���_���̐ݒ�
			field->vertex = (FIELD_BG_NUM_BLOCK_X + 1) * (FIELD_BG_NUM_BLOCK_Z + 1);

			// �C���f�b�N�X���̐ݒ�
			field->vertexIndex = (FIELD_BG_NUM_BLOCK_X + 1) * 2 * FIELD_BG_NUM_BLOCK_Z + (FIELD_BG_NUM_BLOCK_Z - 1) * 2;

			// �|���S�����̐ݒ�
			field->polygon = FIELD_BG_NUM_BLOCK_X * FIELD_BG_NUM_BLOCK_Z * 2 + (FIELD_BG_NUM_BLOCK_Z - 1) * 4;

			// �u���b�N�T�C�Y�̐ݒ�
			field->sizeX = FIELD_BG_SIZE_BLOCK_X;
			field->sizeZ = FIELD_BG_SIZE_BLOCK_Z;

			// �e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
				TEXTURE_BATTLE,					// �t�@�C���̖��O
				&field->Texture);				// �ǂݍ��ރ������[

		}

			// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
			if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * field->vertex,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
				D3DUSAGE_WRITEONLY,					// ���_�o�b�t�@�̎g�p�@�@
				FVF_VERTEX_3D,						// �g�p���钸�_�t�H�[�}�b�g
				D3DPOOL_MANAGED,					// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
				&field->VtxField,				// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
				NULL)))								// NULL�ɐݒ�
			{
				return E_FAIL;
			}

			// �I�u�W�F�N�g�̃C���f�b�N�X�o�b�t�@�𐶐�
			if (FAILED(pDevice->CreateIndexBuffer(sizeof(WORD) * field->vertexIndex,			// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
				D3DUSAGE_WRITEONLY,					// ���_�o�b�t�@�̎g�p�@�@
				D3DFMT_INDEX16,						// �g�p����C���f�b�N�X�t�H�[�}�b�g
				D3DPOOL_MANAGED,					// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
				&field->IdxField,				// �C���f�b�N�X�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
				NULL)))								// NULL�ɐݒ�
			{
				return E_FAIL;
			}

			{
				//���_�o�b�t�@�̒��g�𖄂߂�
				VERTEX_3D *pVtx;

#if 0
				const float texSizeX = 1.0f / field->blockX;
				const float texSizeZ = 1.0f / field->blockZ;
#else
				const float texSizeX = 1.0f;
				const float texSizeZ = 1.0f;
#endif

				// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
				field->VtxField->Lock(0, 0, (void**)&pVtx, 0);

				for (int nCntVtxZ = 0; nCntVtxZ < (field->blockZ + 1); nCntVtxZ++)
				{
					for (int nCntVtxX = 0; nCntVtxX < (field->blockX + 1); nCntVtxX++)
					{
						// ���_���W�̐ݒ�
						pVtx[nCntVtxZ * (field->blockX + 1) + nCntVtxX].vtx.x = -(field->blockX / 2.0f) * field->sizeX + nCntVtxX * field->sizeX;
						pVtx[nCntVtxZ * (field->blockX + 1) + nCntVtxX].vtx.y = 0.0f;
						pVtx[nCntVtxZ * (field->blockX + 1) + nCntVtxX].vtx.z = (field->blockZ / 2.0f) * field->sizeZ - nCntVtxZ * field->sizeZ;

						// �w�i
						if (i == FIELD_BG)
						{
							// �@���̐ݒ�
							pVtx[nCntVtxZ * (field->blockX + 1) + nCntVtxX].nor = D3DXVECTOR3(0.0f, 1.0, 0.0f);

							// ���ˌ��̐ݒ�
							pVtx[nCntVtxZ * (field->blockX + 1) + nCntVtxX].diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
						}

						// �w�i�G�t�F�N�g
						else if (i == FIELD_BG_EFFECT)
						{
							// �@���̐ݒ�
							pVtx[nCntVtxZ * (field->blockX + 1) + nCntVtxX].nor = D3DXVECTOR3(0.0f, 1.0, 0.0f);

							// ���ˌ��̐ݒ�
							pVtx[nCntVtxZ * (field->blockX + 1) + nCntVtxX].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						}

						// �w�i�o�g��
						else if (i == FIELD_BATTLE)
						{
							// �@���̐ݒ�
							pVtx[nCntVtxZ * (field->blockX + 1) + nCntVtxX].nor = D3DXVECTOR3(0.0f, 1.0, 0.0f);

							// ���ˌ��̐ݒ�
							pVtx[nCntVtxZ * (field->blockX + 1) + nCntVtxX].diffuse = FIELD_COLOR;
						}

						// �e�N�X�`�����W�̐ݒ�
						pVtx[nCntVtxZ * (field->blockX + 1) + nCntVtxX].tex.x = texSizeX * nCntVtxX;
						pVtx[nCntVtxZ * (field->blockX + 1) + nCntVtxX].tex.y = texSizeZ * nCntVtxZ;
					}
				}

				// ���_�f�[�^���A�����b�N����
				field->VtxField->Unlock();
			}

			{//�C���f�b�N�X�o�b�t�@�̒��g�𖄂߂�
				WORD *pIdx;

				// �C���f�b�N�X�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
				field->IdxField->Lock(0, 0, (void**)&pIdx, 0);

				int nCntIdx = 0;
				for (int nCntVtxZ = 0; nCntVtxZ < field->blockZ; nCntVtxZ++)
				{
					if (nCntVtxZ > 0)
					{// �k�ރ|���S���̂��߂̃_�u��̐ݒ�
						pIdx[nCntIdx] = (nCntVtxZ + 1) * (field->blockX + 1);
						nCntIdx++;
					}

					for (int nCntVtxX = 0; nCntVtxX < (field->blockX + 1); nCntVtxX++)
					{
						pIdx[nCntIdx] = (nCntVtxZ + 1) * (field->blockX + 1) + nCntVtxX;
						nCntIdx++;
						pIdx[nCntIdx] = nCntVtxZ * (field->blockX + 1) + nCntVtxX;
						nCntIdx++;
					}

					if (nCntVtxZ < (field->blockZ - 1))
					{// �k�ރ|���S���̂��߂̃_�u��̐ݒ�
						pIdx[nCntIdx] = nCntVtxZ * (field->blockX + 1) + field->blockX;
						nCntIdx++;
					}
				}

				// �C���f�b�N�X�f�[�^���A�����b�N����
				field->IdxField->Unlock();
			}
		}
	}


	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void UninitField(void)
{
	// �|�C���^�̏�����
	FIELD *field = &fieldWk[0];

	// �\���̍ő吔����
	for (int i = 0;i < FIELD_MAX;i++, field++)
	{

		if (field->VtxField!=NULL)
		{// ���_�o�b�t�@�̊J��
			field->VtxField->Release();
			field->VtxField = NULL;
		}

		if (field->IdxField != NULL)
		{// �C���f�b�N�X�o�b�t�@�̊J��
			field->IdxField->Release();
			field->IdxField = NULL;
		}

		if (field->Texture)
		{// �e�N�X�`���̊J��
			field->Texture->Release();
			field->Texture = NULL;
		}

	}

}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void UpdateField(void)
{

	// �|�C���^�̏�����
	FIELD *field = &fieldWk[0];

	// �G�t�F�N�g����
	// �v���X�t���O
	if (effectflagF == true)
	{
		// �G�t�F�N�g���l��FIELD_EFFECT_SPEED�𑫂�
		effectF += FIELD_EFFECT_SPEED;

		// �G�t�F�N�g���l���ő�
		if (effectF >= 1.0f)
		{
			// �t���O���}�C�i�X��
			effectflagF = false;
		}
	}

	// �}�C�i�X�t���O
	else if (effectflagF == false)
	{
		// �G�t�F�N�g���l��FIELD_EFFECT_SPEED������
		effectF -= FIELD_EFFECT_SPEED;

		// �G�t�F�N�g���l���ŏ�
		if (effectF <= 0.0f)
		{
			// �t���O���v���X�ɂ�
			effectflagF = true;
		}

	}

	// �\���̍ő吔����
	for (int i = 0;i < FIELD_MAX;i++, field++)
	{
		if (i == FIELD_BG_EFFECT)
		{

			//���_�o�b�t�@�̒��g�𖄂߂�
			VERTEX_3D *pVtx;

			// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
			field->VtxField->Lock(0, 0, (void**)&pVtx, 0);

			// ���ʂ̔g�̏���
			// Z������
			for (int nCntVtxZ = 0; nCntVtxZ < (field->blockZ + 1); nCntVtxZ++)
			{

				// X������
				for (int nCntVtxX = 0; nCntVtxX < (field->blockX + 1); nCntVtxX++)
				{
					// ���ˌ��̐ݒ�
					pVtx[nCntVtxZ * (field->blockX + 1) + nCntVtxX].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, effectF);

				}
			}
			// ���_�f�[�^���A�����b�N����
			field->VtxField->Unlock();
		}
	}

}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void DrawField(void)
{
	// �|�C���^�̏�����
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	FIELD *field = &fieldWk[0];

	//// �����_�[�X�e�[�g�p�����[�^�̐ݒ�
	//pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);	// �����_�[�X�e�[�g�p�����[�^�̐ݒ�


	D3DXMATRIX mtxRot, mtxTranslate;

	//// ���C���e�B���O�𖳌��ɂ���
	//pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);


	// �\���̍ő吔����
	for (int i = 0;i < FIELD_MAX;i++, field++)
	{

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&field->world);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, field->rot.y, field->rot.x, field->rot.z);
		D3DXMatrixMultiply(&field->world, &field->world, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTranslate, field->pos.x, field->pos.y, field->pos.z);
		D3DXMatrixMultiply(&field->world, &field->world, &mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &field->world);

		// ���_�o�b�t�@�������_�����O�p�C�v���C���ɐݒ�
		pDevice->SetStreamSource(0, field->VtxField, 0, sizeof(VERTEX_3D));

		// �C���f�b�N�X�o�b�t�@�������_�����O�p�C�v���C���ɐݒ�
		pDevice->SetIndices(field->IdxField);

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, field->Texture);

		// �|���S���̕`��
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, field->vertex, 0, field->polygon);
	}

	//// ���C���e�B�O��L���ɂ���
	//pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);


	//// �����_�[�X�e�[�g�p�����[�^�̐ݒ�
	//pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// ���ʂ��J�����O

}


//=============================================================================
// �n�`���f���擾�֐�
//=============================================================================
FIELD *GetField(int no)
{
	return(&fieldWk[no]);
}
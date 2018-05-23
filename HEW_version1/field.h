//=============================================================================
//
// ���b�V���n�ʂ̏��� [field.h]
// Name : GP11B243 30 ���ˌ��j��
// �v���O�����쐬��:2018/1/25
//
//=============================================================================
#ifndef _FIELD_H_
#define _FIELD_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

#define FIELD_EFFECT_SPEED		(0.025f)							// �_�ő��x���x

#define	TEXTURE_BG				"data/TEXTURE/battlebg00.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_BG_EFFECT		"data/TEXTURE/battlebg01.png"	// �ǂݍ��ރe�N�X�`���t�@�C����

#define FIELD_BG_POS			D3DXVECTOR3(0.0f,-100.0f,0.0f)		// �n�ʏ������W
#define FIELD_BG_ROT			D3DXVECTOR3(0.0f,0.0f,0.0f)		// �n�ʏ�����]
#define NUM_BG_BLOCK_X			(20)							// �n�ʃ|���S����X
#define NUM_BG_BLOCK_Z			(20)							// �n�ʃ|���S����Z
#define SIZE_BG_BLOCK_X			(240.0f)							// �n�ʃ|���S���T�C�YX
#define SIZE_BG_BLOCK_Z			(240.0f)							// �n�ʃ|���S���T�C�YZ

#define	TEXTURE_BATTLE			"data/TEXTURE/battlebg02.png"	// �ǂݍ��ރe�N�X�`���t�@�C����

#define FIELD_BG_NUM_BLOCK_X	(13)							// �n�ʃ|���S����X
#define FIELD_BG_NUM_BLOCK_Z	(8)								// �n�ʃ|���S����Z
#define FIELD_BG_SIZE_BLOCK_X	(60.0f)							// �n�ʃ|���S���T�C�YX
#define FIELD_BG_SIZE_BLOCK_Z	(60.0f)							// �n�ʃ|���S���T�C�YZ

#define FIELD_SCL_MAX_X			((FIELD_BG_NUM_BLOCK_X * FIELD_BG_SIZE_BLOCK_X) / 2)
#define FIELD_SCL_MAX_Z			((FIELD_BG_NUM_BLOCK_Z * FIELD_BG_SIZE_BLOCK_Z) / 2)

#define FIELD_COLOR				D3DXCOLOR(1.0f,1.0f,1.0f,0.6f)	// �n�ʂ̐F


// �t�B�[���h�p�\���̎��ʃ}�N��
enum
{
	FIELD_BG,			// �w�i
	FIELD_BG_EFFECT,	// �w�i�G�t�F�N�g
	FIELD_BATTLE,		// �o�g��
	FIELD_MAX,			// �\���̍ő吔
};


//=============================================================================
// �\���̐錾
//=============================================================================

typedef struct // �t�B�[���h�\����
{
	D3DXMATRIX		world;						// ���[���h�}�g���b�N�X
	D3DXVECTOR3		pos;						// �|���S���\���ʒu�̒��S���W
	D3DXVECTOR3		rot;						// �|���S���̉�]�p

	int				blockX, blockZ;				// �u���b�N��
	int				vertex;						// �����_��	
	int				vertexIndex;				// ���C���f�b�N�X��
	int				polygon;					// ���|���S����
	float			sizeX, sizeZ;				// �u���b�N�T�C�Y

	LPDIRECT3DTEXTURE9		Texture;			// �e�N�X�`���ǂݍ��ݏꏊ
	LPDIRECT3DVERTEXBUFFER9 VtxField;			// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9	IdxField;			// �C���f�b�N�X�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

}FIELD;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitField(int type);				// �����������֐�
void UninitField(void);						// �I�������֐�
void UpdateField(void);						// �X�V�����֐�
void DrawField(void);						// �`�揈���֐�

FIELD *GetField(int no);

#endif

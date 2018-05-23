//=============================================================================
//
// �e���� [playerNorSk.h]
// Author : �镶��
// �v���O�����쐬�� : 2018/3/09
//=============================================================================
#ifndef _PLAYERNORMALSKILL_H_
#define _PLAYERNORMALSKILL_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_NORSKILL_PLAYER			"data/TEXTURE/skill00.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	NORSKILL_SIZE_X			(5.0f)							// �r���{�[�h�̕�
#define	NORSKILL_SIZE_Y			(5.0f)							// �r���{�[�h�̍���
#define	VALUE_MOVE_NORSKILL		(3.0f)							// �ړ����x

#define	MAX_NORSKILL				(1)							// �r���{�[�h�ő吔
//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
		D3DXMATRIX				world;
		D3DXVECTOR3				pos;		// �ʒu
		D3DXVECTOR3				rot;		// ��]
		D3DXVECTOR3				scl;		// �X�P�[��
		D3DXVECTOR3				move;		// �ړ���
		D3DXVECTOR2				size;
		int						timer;				// �^�C�}�[
		int cnt;
		int						nIdxShadow;			// �eID
		bool					bUse;		// �g�p���Ă��邩�ǂ���
		bool					Track;

} PLAYER_NORSKILL;
typedef enum
{
	PB_TYPE_NORMAL,
	PB_TYPE_MAX

}PLAYER_NORSKILL_TYPE;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayerNorSkill(void);
void UninitPlayerNorSkill(void);
void UpdatePlayerNorSkill(void);
void DrawPlayerNorSkill(void);

int SetPlayerNorSkill(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 size, int timer, int type);
void DeletePlayerNorSkill(int no);
int GetPlayerNorSkillType(void);
PLAYER_NORSKILL *GetPlayerNorSkill(int no);
#endif

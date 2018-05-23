//=============================================================================
//
// �e���� [playerskillDef.h]
// Author : �镶�� 
// �v���O�����쐬�� : 2018/3/09
//=============================================================================
#ifndef _PLAYERSKILLDEF_H_
#define _PLAYERSKILLDEF_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_SKILLDEF_PLAYER			"data/TEXTURE/skill01.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	SKILLDEF_SIZE_X			(15.0f)							// �r���{�[�h�̕�
#define	SKILLDEF_SIZE_Y			(15.0f)							// �r���{�[�h�̍���
#define	VALUE_MOVE_SKILLDEF		(2.0f)							// �ړ����x

#define	MAX_SKILLDEF				(5)							// �r���{�[�h�ő吔
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
		int cnt;
		int						timer;				// �^�C�}�[
		int						nIdxShadow;			// �eID
		bool					bUse;				// �g�p���Ă��邩�ǂ���
} PLAYER_SKILLDEF;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayerSkillDef(void);
void UninitPlayerSkillDef(void);
void UpdatePlayerSkillDef(void);
void DrawPlayerSkillDef(void);

int SetPlayerSkillDef(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 size, int timer);
void DeletePlayerSkillDef(int no);
int GetPlayerSkillDefType(void);
PLAYER_SKILLDEF *GetPlayerSkillDef(int no);
#endif

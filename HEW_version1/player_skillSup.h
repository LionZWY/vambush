//=============================================================================
//
// �e���� [playerSupSk.h]
// Author : �镶��
// �v���O�����쐬�� : 2018/3/09
//=============================================================================
#ifndef _PLAYERSUPERSKILL_H_
#define _PLAYERSUPERSKILL_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_SUPSKILL_PLAYER			"data/TEXTURE/skill02.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	SUPSKILL_SIZE_X			(5.0f)							// �r���{�[�h�̕�
#define	SUPSKILL_SIZE_Y			(5.0f)							// �r���{�[�h�̍���
#define	VALUE_MOVE_SUPSKILL		(3.0f)							// �ړ����x

#define	MAX_SUPSKILL				(1)							// �r���{�[�h�ő吔
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
		int						nIdxShadow;			// �eID
		bool					bUse;		// �g�p���Ă��邩�ǂ���
		bool					Track;

} PLAYER_SUPSKILL;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayerSupSkill(void);
void UninitPlayerSupSkill(void);
void UpdatePlayerSupSkill(void);
void DrawPlayerSupSkill(void);

int SetPlayerSupSkill(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 size, int timer);
void DeletePlayerSupSkill(int no);
PLAYER_SUPSKILL *GetPlayerSupSkill(int no);
#endif

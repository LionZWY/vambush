//=============================================================================
//
// �^�C�}�[���� [timer.cpp]
// Author : ���ˌ��j��
// �v���O�����쐬�� : 2018/3/09
//
//=============================================================================

#include "timer.h"				// �}�N�����\���̎g�p�̈�
#include "game.h"				// �}�N���g�p�̈�
#include "player.h"				// �\���̎g�p�̈�
#include "enemy.h"				// ����
#include "sound.h"				// �֐��g�p�̈�
#include "fade.h"				// ����
#include "result.h"				// ����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexTimer(LPDIRECT3DDEVICE9 pDevice, int no);	// ���_�쐬�֐�
void SetTextureTimer(int idx, int number, int no);			// �e�N�X�`�����W�ݒ�֐�

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureTimer = NULL;			// �e�N�X�`���ւ̃|�C���^�ϐ�
bool					g_bEnableTimer;						// �^�C�}�[����ON/OFF�ϐ�
bool					quickbgm;

TIMER					timerWk[NUM_MAX];					// �^�C�}�[�\���̂��ő吔�錾

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT InitTimer(int type)
{

	// �|�C���^�̏�����
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TIMER *timer = &timerWk[0];
	PLAYER *player = GetPlayer();
	ENEMY *enemy = GetEnemy();

	// �^�C�}�[���g�p�ŏ�����
	g_bEnableTimer = true;

	quickbgm = false;

	// �ő吔����������
	for (int i = 0;i < NUM_MAX;i++, timer++)
	{

		// �S��NULL�ŏ�����
		timer->buff = NULL;

		// �^�C�}�[
		if (i == NUM_TIMER)
		{
			timer->use = true;								// �g�p�ŏ�����
			timer->pos = TIMER_BASE_POS;					// �ʒu�̏�����
			timer->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ��]�̏�����

			// �^�C�}�[�̒l�̏�����
			timer->nummax = TIMER_MAX * FRAME_CNT;
		}

		// �K�E�Z�Q�[�W�v���C���[
		else if (i == NUM_PLAYER_KILL)
		{
			timer->use = true;								// �g�p�ŏ�����
			timer->pos = TIMER_PLAYER_POS;					// �ʒu�̏�����
			timer->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ��]�̏�����

			// HP�̏�����
			timer->nummax = player->kill;
		}

		// �K�E�Z�Q�[�W�G�l�~�[
		else if (i == NUM_ENEMY_KILL)
		{
			timer->use = true;								// �g�p�ŏ�����
			timer->pos = TIMER_ENEMY_POS;				// �ʒu�̏�����
			timer->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ��]�̏�����

															// �A�N�A�X�̏�����
			timer->nummax =enemy->kill;
		}


		// ���_���̍쐬
		MakeVertexTimer(pDevice,i);

	}

	// ���N����
	if (type == FIRST)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
			TEXTURE_TIMER,					// �t�@�C���̖��O
			&g_pD3DTextureTimer);			// �ǂݍ��ރ������[
	}

	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void UninitTimer(void)
{

	// �������̉��
	if(g_pD3DTextureTimer != NULL)
	{
		// �e�N�X�`���̊J��
		g_pD3DTextureTimer->Release();
		g_pD3DTextureTimer = NULL;
	}
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void UpdateTimer(void)
{
	// �|�C���^�̏�����
	TIMER *timer = &timerWk[0];
	PLAYER *player = GetPlayer();
	ENEMY *enemy = GetEnemy();
	bool *win = GetWinFlag();

	// �ő吔�X�V����
	for (int i = 0;i < NUM_MAX;i++, timer++)
	{

		// �^�C�}�[
		if (i == NUM_TIMER)
		{
			// �^�C�}�[��on��������
			if (g_bEnableTimer)
			{
				// �������Ԃ̌���
				timer->nummax--;

				// 60
				if ((timer->nummax / FRAME_CNT < 60) && (timer->nummax / FRAME_CNT > 30))
				{

					if (quickbgm == false)
					{

						StopSound(BGM_BATTLE);								// �ʏ�퓬BGM�̒�~
						PlaySound(BGM_QUICK, E_DS8_FLAG_NONE);		// ���U���gBGM�̍Đ�
						quickbgm = true;
					}

					VERTEX_2D *pVtx;

					// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
					timer->buff->Lock(0, 0, (void**)&pVtx, 0);

					// �ő吔�쐬
					for (int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++, pVtx += NUM_VERTEX)
					{

						// ���ˌ��̐ݒ�
						pVtx[0].diffuse = D3DCOLOR_RGBA(255, 255, 0, 255);
						pVtx[1].diffuse = D3DCOLOR_RGBA(255, 255, 0, 255);
						pVtx[2].diffuse = D3DCOLOR_RGBA(255, 255, 0, 255);
						pVtx[3].diffuse = D3DCOLOR_RGBA(255, 255, 0, 255);

					}

					// ���_�f�[�^���A�����b�N����
					timer->buff->Unlock();

				}

			// 30
			if (timer->nummax / FRAME_CNT < 30)
			{
				VERTEX_2D *pVtx;

				// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
				timer->buff->Lock(0, 0, (void**)&pVtx, 0);

				// �ő吔�쐬
				for (int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++, pVtx += NUM_VERTEX)
				{

					// ���ˌ��̐ݒ�
					pVtx[0].diffuse = D3DCOLOR_RGBA(255, 0, 0, 255);
					pVtx[1].diffuse = D3DCOLOR_RGBA(255, 0, 0, 255);
					pVtx[2].diffuse = D3DCOLOR_RGBA(255, 0, 0, 255);
					pVtx[3].diffuse = D3DCOLOR_RGBA(255, 0, 0, 255);

				}

			// ���_�f�[�^���A�����b�N����
			timer->buff->Unlock();

			}



				// �^�C���A�b�v
				if (timer->nummax < 0)
				{
					// �^�C�}�[�̃X�g�b�v
					timer->nummax = 0;

					// hp���ׂ�
					if (player->hp > enemy->hp)
					{
						// �v���C���[�̏���
						*win = true;
					}

					else
					{

						// �G�l�~�|����
						*win = false;

					}

					// �X�e�[�W�ϐ��̃��U���g�̑O�ɃZ�b�g
					SetStage(STAGE_GAME_END);

					// ��ʑJ��:���U���g
					SetFade(FADE_OUT);
				}

				// �������Ԃ�����
				else if ((timer->nummax / FRAME_CNT) >= (int)(powf(10.0f, (float)(NUM_PLACE + 1))))
				{
					// �P�O�̗ݏ�[�P����
					timer->nummax = (int)(powf(DECIMAL_TEN, (float)(NUM_PLACE + 1))) - 1;
				}
			}

			// �\�����ő吔�e�N�X�`���ݒ�
			for (int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++)
			{
				// �^�C�}�[����ϐ�
				int number;		// �\�����l�ϐ�
				int time;		// �\�����l�v�Z�p�ϐ�

				// ���݂̎��Ԃ���T�X������
				time = timer->nummax + FRAME_CNT-1;

				// �\�����l�̌���
				number = ((time / FRAME_CNT) % (int)(powf(DECIMAL_TEN, (float)(NUM_PLACE - nCntPlace)))) / (int)(powf(DECIMAL_TEN, (float)(NUM_PLACE - nCntPlace - 1)));

			// �\�����l�̔��f
				SetTextureTimer(nCntPlace, number, i);
			}

		}

		// �K�E�Z�Q�[�W�v���C���[
		else if (i == NUM_PLAYER_KILL)
		{

			// ���݂̕K�E�Z�Q�[�W�̒l��ۑ�
			timer->nummax = player->kill;

			if (player->kill == 100)
			{
				VERTEX_2D *pVtx;

				// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
				timer->buff->Lock(0, 0, (void**)&pVtx, 0);

				// �ő吔�쐬
				for (int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++, pVtx += NUM_VERTEX)
				{

					// ���ˌ��̐ݒ�
					pVtx[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

				}

				// ���_�f�[�^���A�����b�N����
				timer->buff->Unlock();


			}

			// �\�����ő吔�e�N�X�`���ݒ�
			for (int s = 0; s < NUM_PLACE; s++)
			{

				// �\�����l�ϐ�
				int number;

				// �O����
				if (s == NUM_THREE_DIGIT)
				{
					// �\�����l�̌���
					number = timer->nummax / BASE_HUNDRED;

					// �\�����l�̔��f
					SetTextureTimer(s, number, i);
				}

				// �񌅖�
				else if (s == NUM_DOUBLE_DIGIT)
				{
					// �\�����l�̌���
					number = timer->nummax % BASE_HUNDRED / BASE_TEN;

					// �\�����l�̔��f
					SetTextureTimer(s, number, i);
				}

				// �ꌅ��
				else if (s == NUM_DIGIT)
				{
					// �\�����l�̌���
					number = timer->nummax % BASE_HUNDRED% BASE_TEN / 1;

					// �\�����l�̔��f
					SetTextureTimer(s, number, i);
				}

			}

		}

		// �K�E�Z�Q�[�W�G�l�~�[
		else if (i == NUM_ENEMY_KILL)
		{

			// ���݂̕K�E�Z�Q�[�W�̒l��ۑ�
			timer->nummax = enemy->kill;

			if (enemy->kill == 100)
			{
				VERTEX_2D *pVtx;

				// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
				timer->buff->Lock(0, 0, (void**)&pVtx, 0);

				// �ő吔�쐬
				for (int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++, pVtx += NUM_VERTEX)
				{

					// ���ˌ��̐ݒ�
					pVtx[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

				}

				// ���_�f�[�^���A�����b�N����
				timer->buff->Unlock();


			}


			// �\�����ő吔�e�N�X�`���ݒ�
			for (int s = 0; s < NUM_PLACE; s++)
			{

				// �\�����l�ϐ�
				int number;

				// �O����
				if (s == NUM_THREE_DIGIT)
				{
					// �\�����l�̌���
					number = timer->nummax / BASE_HUNDRED;

					// �\�����l�̔��f
					SetTextureTimer(s, number, i);
				}

				// �񌅖�
				else if (s == NUM_DOUBLE_DIGIT)
				{
					// �\�����l�̌���
					number = timer->nummax % BASE_HUNDRED / BASE_TEN;

					// �\�����l�̔��f
					SetTextureTimer(s, number, i);
				}

				// �ꌅ��
				else if (s == NUM_DIGIT)
				{
					// �\�����l�̌���
					number = timer->nummax % BASE_HUNDRED% BASE_TEN / 1;

					// �\�����l�̔��f
					SetTextureTimer(s, number, i);
				}

			}


		}


	}
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void DrawTimer(void)
{

	// �|�C���^�̏�����
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TIMER *timer = &timerWk[0];

	// �ő吔�`�揈��
	for (int i = 0;i < NUM_MAX;i++, timer++)
	{

		// �g�p���Ă�����
		if (timer->use == true)
		{

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, timer->buff, 0, sizeof(VERTEX_2D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_2D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pD3DTextureTimer);

			// �|���S���̕`��
			for (int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++)
			{
				// �����_�����O����
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntPlace * NUM_VERTEX), NUM_POLYGON);
			}
		}
	}
}

//=============================================================================
// ���_�쐬�֐�
//=============================================================================
HRESULT MakeVertexTimer(LPDIRECT3DDEVICE9 pDevice, int no)
{

	// �|�C���^�̏�����
	TIMER *timer = &timerWk[no];

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
    if( FAILED( pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * (NUM_VERTEX * NUM_PLACE + NUM_VERTEX),	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
												D3DUSAGE_WRITEONLY,										// ���_�o�b�t�@�̎g�p�@�@
												FVF_VERTEX_2D,											// �g�p���钸�_�t�H�[�}�b�g
												D3DPOOL_MANAGED,										// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
												&timer->buff,											// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
												NULL)))													// NULL�ɐݒ�
	{
        return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		timer->buff->Lock(0, 0, (void**)&pVtx, 0);

		// �ő吔�쐬
		for(int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++, pVtx += NUM_VERTEX)
		{

			// �^�C�}�[
			if (no == NUM_TIMER)
			{
				// ���_���W�̐ݒ�
				pVtx[0].vtx = D3DXVECTOR3(TIMER_POS_X + nCntPlace * TIMER_SIZE_X + TIMER_INTERVAL_X, TIMER_POS_Y, 0.0f);
				pVtx[1].vtx = D3DXVECTOR3(TIMER_POS_X + nCntPlace * (TIMER_INTERVAL_X + TIMER_SIZE_X) + TIMER_SIZE_X, TIMER_POS_Y, 0.0f);
				pVtx[2].vtx = D3DXVECTOR3(TIMER_POS_X + nCntPlace * TIMER_SIZE_X + TIMER_INTERVAL_X, TIMER_POS_Y + TIMER_SIZE_Y, 0.0f);
				pVtx[3].vtx = D3DXVECTOR3(TIMER_POS_X + nCntPlace * (TIMER_INTERVAL_X + TIMER_SIZE_X) + TIMER_SIZE_X, TIMER_POS_Y + TIMER_SIZE_Y, 0.0f);

				// rhw�̐ݒ�
				pVtx[0].rhw =
				pVtx[1].rhw =
				pVtx[2].rhw =
				pVtx[3].rhw = 1.0f;

				// ���ˌ��̐ݒ�
				pVtx[0].diffuse = D3DCOLOR_RGBA(100, 255, 100, 255);
				pVtx[1].diffuse = D3DCOLOR_RGBA(100, 255, 100, 255);
				pVtx[2].diffuse = D3DCOLOR_RGBA(100, 255, 100, 255);
				pVtx[3].diffuse = D3DCOLOR_RGBA(100, 255, 100, 255);

				// �e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

			}

			// �K�E�Z�Q�[�W�v���C���[
			else if (no == NUM_PLAYER_KILL)
			{
				// ���_���W�̐ݒ�
				pVtx[0].vtx = D3DXVECTOR3(timer->pos.x + nCntPlace * KILL_SIZE_X + TIMER_INTERVAL_X, timer->pos.y, 0.0f);
				pVtx[1].vtx = D3DXVECTOR3(timer->pos.x + nCntPlace * (TIMER_INTERVAL_X + KILL_SIZE_X) + KILL_SIZE_X, timer->pos.y, 0.0f);
				pVtx[2].vtx = D3DXVECTOR3(timer->pos.x + nCntPlace * KILL_SIZE_X + TIMER_INTERVAL_X, timer->pos.y + KILL_SIZE_Y, 0.0f);
				pVtx[3].vtx = D3DXVECTOR3(timer->pos.x + nCntPlace * (TIMER_INTERVAL_X + KILL_SIZE_X) + KILL_SIZE_X, timer->pos.y + KILL_SIZE_Y, 0.0f);

				// rhw�̐ݒ�
				pVtx[0].rhw =
					pVtx[1].rhw =
					pVtx[2].rhw =
					pVtx[3].rhw = 1.0f;

				// ���ˌ��̐ݒ�
				pVtx[0].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
				pVtx[1].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
				pVtx[2].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
				pVtx[3].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);

				// �e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

			}

			// �K�E�Z�Q�[�W�G�l�~�[
			else if (no == NUM_ENEMY_KILL)
			{
				// ���_���W�̐ݒ�
				pVtx[0].vtx = D3DXVECTOR3(timer->pos.x + nCntPlace * KILL_SIZE_X + TIMER_INTERVAL_X, timer->pos.y, 0.0f);
				pVtx[1].vtx = D3DXVECTOR3(timer->pos.x + nCntPlace * (TIMER_INTERVAL_X + KILL_SIZE_X) + KILL_SIZE_X, timer->pos.y, 0.0f);
				pVtx[2].vtx = D3DXVECTOR3(timer->pos.x + nCntPlace * KILL_SIZE_X + TIMER_INTERVAL_X, timer->pos.y + KILL_SIZE_Y, 0.0f);
				pVtx[3].vtx = D3DXVECTOR3(timer->pos.x + nCntPlace * (TIMER_INTERVAL_X + KILL_SIZE_X) + KILL_SIZE_X, timer->pos.y + KILL_SIZE_Y, 0.0f);

				// rhw�̐ݒ�
				pVtx[0].rhw =
					pVtx[1].rhw =
					pVtx[2].rhw =
					pVtx[3].rhw = 1.0f;

				// ���ˌ��̐ݒ�
				pVtx[0].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
				pVtx[1].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
				pVtx[2].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);
				pVtx[3].diffuse = D3DCOLOR_RGBA(100, 100, 100, 255);

				// �e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

			}


		}

		// ���_�f�[�^���A�����b�N����
		timer->buff->Unlock();
	}

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�ݒ�֐�
//=============================================================================
void SetTextureTimer(int idx, int number, int no)
{
	// �|�C���^�̏�����
	TIMER *timer = &timerWk[no];

	//���_�o�b�t�@�̒��g�𖄂߂�
	VERTEX_2D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	timer->buff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�����C���N�������g
	pVtx += (idx * NUM_VERTEX);

	// ���_���W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(number * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(number * 0.1f + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(number * 0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(number * 0.1f + 0.1f, 1.0f);

	// ���_�f�[�^���A�����b�N����
	timer->buff->Unlock();
}

//=============================================================================
// �^�C�}�[�J�n�֐�
//=============================================================================
void EnableTimer(bool bEnable)
{
	g_bEnableTimer = bEnable;
}

//=============================================================================
// �^�C�}�[���Z�b�g�֐�
//=============================================================================
void ResetTimer(int nTime)
{

	// �|�C���^�̏�����
	TIMER *timer = &timerWk[0];

	// �n���ꂽ�����Ɉ�b�̃t���[�������|����
	timer->nummax = nTime * FRAME_CNT;
}


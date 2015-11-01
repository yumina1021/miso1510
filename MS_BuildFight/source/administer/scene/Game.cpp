//=============================================================================
//
// MS_BuildFight [CGame.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#include <process.h>

#include "Game.h"

#include "../Renderer.h"
#include "../Input.h"
#include "../Maneger.h"
#include "../Sound.h"
#include "../Debugproc.h"

#include "../../form/form2D.h"
#include "../../form/form3D.h"
#include "../../form/formX.h"
#include "../../form/formBillBoard.h"

#include "../../module/field/Dome.h"
#include "../../module/field/Domeunder.h"
#include "../../module/field/Field.h"

#include "../../module/ui/Effect.h"
#include "../../module/ui/Icon.h"
#include "../../module/ui/Score.h"
#include "../../module/ui/Timer.h"
#include "../../module/ui/Lock.h"
#include "../../module/ui/Count.h"
#include "../../module/ui/Gauge.h"
#include "../../module/ui/BackGround.h"
#include "../../module/ui/CharPicture.h"

#include "../../module/robot/PlayerM.h"
#include "../../module/robot/EnemyM.h"
#include "../../module/robot/PlayerGun1.h"

#include "../../module/etc/Fade.h"
#include "../../module/etc/Ball.h"
#include "../../module/etc/LocusEffect.h"

#include "../../exten_common.h"

#define PLAYER_MAX	(2)	//�v���C���[��
#define SHOT_RIMIT	(0.001f)
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
//�V�[��
CPlayerM *CGame::m_pPlayer[2] = { NULL ,NULL};
CEnemyM *CGame::m_pEnemy = NULL;
CBall*	CGame::m_pBall[2];

int CGame::m_nGameStartCount = 0;
bool CGame::m_bReplayFlag =false;
bool CGame::m_bVsSelectFlag = false;
int	CGame::m_nPlayerNum;
int	CGame::m_nSwitchCount;

key2Con K2CList[8]={
	{DIK_Z, COMMAND_SHOT},
	{DIK_X, COMMAND_ATTACK},
	{DIK_SPACE, COMMAND_JUMP},
	{DIK_V, COMMAND_OVER},
	{DIK_W, COMMAND_UP},
	{DIK_S, COMMAND_DOWN},
	{DIK_D, COMMAND_RIGHT},
	{DIK_A, COMMAND_LEFT}
};
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGame :: CGame(void)
{
	m_pMeshField = NULL;
	m_pform3D = NULL;
	m_pScore = NULL;
	m_pCountBoost = NULL;

	m_pTimer = NULL;
	m_pCountBullet = NULL;
	m_pCountOver = NULL;

	m_pGauge = NULL;
	m_pGaugeEnemy = NULL;

	m_pBackGround = NULL;
	m_pFade = NULL;
	m_pCharPicture[2] = {};

	m_pEffect[15] = {};
	m_pLocusEffect[19] = {};

	m_pIcon = NULL;
	m_pIconEnemy = NULL;

	m_pBall[1] = {};
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGame :: ~CGame(void)
{
}

//=============================================================================
// ������
//=============================================================================
HRESULT CGame::Init(LPDIRECT3DDEVICE9 pDevice)
{
	m_bVsSelectFlag = CScene::GetVSFlag();
	m_bReplayFlag = CScene::GetReplayFlag();

	//�n�ʂ̍쐬
	m_pMeshField = CMeshField::Create(pDevice, 6, D3DXVECTOR3(0, 0, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100, 100, 50, 50);

	//��̍쐬
	m_pDome = CDome::Create(pDevice, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//��̍쐬
	m_pDome2 = CDomeU::Create(pDevice, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//�Q�[�W�̍쐬
	m_pGauge = CGauge::Create(pDevice, D3DXVECTOR3(143.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);

	//�G�Q�[�W�̍쐬
	m_pGaugeEnemy = CGauge::Create(pDevice, D3DXVECTOR3(171.0f, 121.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), true);

	//���̃G�t�F�N�g�\��
	for (int i = 0; i < 20; i++)
	{
		m_pLocusEffect[i] = CLocusEffect::Create(pDevice, NULL, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	//�C���^�[�t�F�[�X��ʂ̍쐬
	InitUI(pDevice);

	//�L�����N�^�[�̍쐬
	m_nPnum = CScene::GetFrame();
	m_nEnum = CScene::GetEnemy();

	m_pPlayer[0] = CPlayerM::Create(pDevice, 0,D3DXVECTOR3(0, 100, 250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_pPlayer[0]->SetVsFlag(m_bVsSelectFlag);

	m_pPlayer[1] = CPlayerM::Create(pDevice, 0, D3DXVECTOR3(0, 100, -450.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_pPlayer[1]->SetVsFlag(m_bVsSelectFlag);
	//m_pEnemy = CEnemyM::Create(pDevice, m_nEnum, D3DXVECTOR3(0, 50, -200.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f), !m_bVsSelectFlag);

	m_pBall[0] = CBall::Create(pDevice, 0, D3DXVECTOR3(0.0f, 50.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pBall[1] = CBall::Create(pDevice, 0, D3DXVECTOR3(0.0f, 50.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//�G�t�F�N�g�̍쐬

	m_pEffect[m_nPnum] = CEffect::Create(pDevice, (EffectNum)m_nPnum, D3DXVECTOR3(650.0f, 375.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pEffect[(m_nEnum + 5)] = CEffect::Create(pDevice, (EffectNum)(m_nEnum + 5), D3DXVECTOR3(650.0f, 375.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_pEffect[10] = CEffect::Create(pDevice, effect000, D3DXVECTOR3(650.0f, 375.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pEffect[11] = CEffect::Create(pDevice, effect002, D3DXVECTOR3(650.0f, 375.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pEffect[12]=CEffect::Create(pDevice,Gtimeout,D3DXVECTOR3(650.0f,375.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f));

	m_pEffect[13]=CEffect::Create(pDevice,Gready,D3DXVECTOR3(650.0f,375.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f));
	m_pEffect[14]=CEffect::Create(pDevice,Gstart,D3DXVECTOR3(650.0f,375.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f));

	m_pEffect[15] = CEffect::Create(pDevice, effect003, D3DXVECTOR3(650.0f, 375.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//Pause
	//�w�i�̍쐬
	m_pBackGround=CBackGround::Create(pDevice,BACKGROUND_GAME);

	//�����̔z�u
	m_pCharPicture[0]=CCharPicture::Create(pDevice,p_continue,D3DXVECTOR3(1100.0f,450.0f,0.0f),400,100);
	m_pCharPicture[1]=CCharPicture::Create(pDevice,p_retry,D3DXVECTOR3(1100.0f,550.0f,0.0f),400,100);
	m_pCharPicture[2]=CCharPicture::Create(pDevice,p_quit,D3DXVECTOR3(1100.0f,650.0f,0.0f),400,100);

	//�t�F�[�h�̍쐬
	m_pFade=CFade::Create(pDevice,1);

	//�T�E���h�擾�̍쐬
	CSound *pSound;
	pSound = CManager::GetSound();

	m_bChangeFlag=false;
	m_nCount=0;

	m_fDiffuse=1.0f;

	m_nTimerPlus=0;

	m_nClearType=0;

	m_bJudge = false;

	m_nSwitchCount = 0;

	m_nPlayerNum = 0;

	m_nTurnCount = 0;

	//�T�E���h�Đ��̍쐬
	//pSound->Play(SOUND_LABEL_BGM001);

	CManager::SetgameEndFlag(true);

	m_nGameStartCount=0;

	// ��M�X���b�h�J�n
	m_pFade->StartFade(FADE_OUT,50,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));

	return S_OK;
}
//=============================================================================
// �������X���b�h
//=============================================================================
unsigned __stdcall CGame :: InitSet( LPVOID Param )
{
	return 0;
}
//=============================================================================
// �I��
//=============================================================================
void CGame :: Uninit(void)
{
	//�T�E���h�擾�̍쐬
	CSound *pSound;
	pSound = CManager::GetSound();

	//�T�E���h�Đ��̍쐬
	pSound->Stop();

	//�V�[����S�ďI��
	Cform::ReleaseAll();
}
//=============================================================================
// �X�V
//=============================================================================
void CGame :: Update(void)
{
	//�L�[�{�[�h�C���v�b�g�̎󂯎��
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//�X�V�{��
	if (!m_bChangeFlag)
	{
		switch (m_nSwitchCount)
		{
		case 0:		TurnStart();
			break;
		case 1:		ShotStart();
			break;
		case 2:		BallMove();
			break;
		case 3:		Judge();
			break;
		case 4:		charachange();
			break;
		}
	}

	CDebugProc::Print(" X = %f\n Y = %f\n Z = %f\n", m_MovePow.x, m_MovePow.y, m_MovePow.z);

	//�G�X�P�[�v�L�[�������ꂽ�ꍇ�^�o�L�[�������ꂽ���|�[�Y��ʂ�
	if(pInputKeyboard->GetKeyTrigger(DIK_P)&&!m_bChangeFlag&&!m_bReplayFlag)
	{
		if(!CManager::GetpauseFlag())
		{
			CManager::SetpauseFlag(true);
		}else
		{
			CManager::SetpauseFlag(false);
			m_nCount=0;
		}
	}

	//�|�[�Y��ON�̏ꍇ
	if(CManager::GetpauseFlag())
	{
		//�T�E���h�擾�̍쐬
		CSound *pSound;
		pSound = CManager::GetSound();

		//�G���^�[�L�[�������ꂽ�ꍇ
		if(pInputKeyboard->GetKeyTrigger(DIK_RETURN)||pInputKeyboard->GetKeyTrigger(DIK_Z))
		{
			//�J�[�\���������Ă���R�}���h�𔭓�
			switch(m_nCount)
			{
				//�X�^�[�g
				case 0 :	m_bChangeFlag=false;
							CManager::SetpauseFlag(false);
							break;
				//�R���t�B�O
				case 1 :	m_bChangeFlag=true;
							//pSound->Play(SOUND_LABEL_SE_SELECT001);
							CManager::SetpauseFlag(false);
							m_pFade->StartFade(FADE_IN,100,D3DXCOLOR(1.0f,1.0f,1.0f,0.0f));
		
							break;
				//�G���h
				case 2 :	m_bChangeFlag=true;
							//pSound->Play(SOUND_LABEL_SE_SELECT001);
							CManager::SetpauseFlag(false);
							m_pFade->StartFade(FADE_IN,100,D3DXCOLOR(1.0f,1.0f,1.0f,0.0f));
							break;

				default : break;
			}
		}
		else if(m_bChangeFlag!=true)
		{
			if(pInputKeyboard->GetKeyTrigger(DIK_W)||pInputKeyboard->GetKeyTrigger(DIK_Y))
			{
				m_pCharPicture[m_nCount]->SetDiffuse(1.0f,1.0f,1.0f,1.0f);
				m_nCount--;
				//pSound->Play(SOUND_LABEL_SE_SELECT000);
				if(m_nCount<0)
				{
					m_nCount=2;
				}
			}else if(pInputKeyboard->GetKeyTrigger(DIK_S)||pInputKeyboard->GetKeyTrigger(DIK_DOWN))
			{
				m_pCharPicture[m_nCount]->SetDiffuse(1.0f,1.0f,1.0f,1.0f);
				m_nCount++;
				//pSound->Play(SOUND_LABEL_SE_SELECT000);
				if(m_nCount>2)
				{
					m_nCount=0;
				}
			}
		}

		m_fDiffuse-=0.01f;

		if(m_fDiffuse<0.5f)
		{
			m_fDiffuse=1.0f;
		}

		m_pCharPicture[m_nCount]->SetDiffuse(m_fDiffuse,m_fDiffuse,m_fDiffuse,1.0f);
	}else 
	{
		m_nTimerPlus++;
		//���ԍX�V
		m_nTimerCount++;

		//�^�C�}�[�ɐݒ�
		if(m_nTimerCount>60)
		{
			m_pTimer->AddTimer(-1);
			m_nTimerCount=0;
		}
	}

	//�t�F�[�h�C�����I�������
	if(m_pFade->GetFade()==FADE_IN_END)
	{
		if(m_bReplayFlag==false)
		{
			pInputKeyboard->Save();
		}

		m_pFade->StartFade(FADE_OUT,50,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));

		if(m_bVsSelectFlag==false)
		{
			//�J�[�\���������Ă���R�}���h�𔭓�
			switch(m_nCount)
			{
				case 0 :	CScene::SetTime(m_pTimer->GetTimer()*100);
							CScene::SetScore(m_nClearType*20000);
							CManager::SetgameEndFlag(false);
							CManager::Setnight0PlayFlag(true);
							CManager::SetAfterScene(PHASETYPE_RESULT);
							break;

				case 1 :	//���̃t�F�[�Y��ς���
							CSound *pSound;
							pSound = CManager::GetSound();
							//�T�E���h�Đ��̍쐬
							//pSound->Stop(SOUND_LABEL_BGM001);
							Restart();
							m_bChangeFlag=false;
							break;
				//�G���h
				case 2 :	//���̃t�F�[�Y��ς���
							CManager::SetAfterScene(PHASETYPE_TITLE);
							break;

				default : 	//���̃t�F�[�Y��ς���
							CManager::SetAfterScene(PHASETYPE_RESULT);
							break;
			}
	}else
		{
			CScene::SetTime(m_pTimer->GetTimer()*100);
			CScene::SetScore(m_nClearType*20000);
			CManager::SetgameEndFlag(false);
			CManager::Setnight0PlayFlag(true);
			CManager::SetAfterScene(PHASETYPE_VSEND);
		}
	}
}
//=============================================================================
// �`��
//=============================================================================
void CGame :: Draw(void)
{
	if (CManager::GetpauseFlag())
	{
		m_pBackGround->Draw();

		//�����̔z�u
		for (int i = 0; i < 3; i++)
		{
			m_pCharPicture[i]->Draw();
		}
	}
	else
	{
		m_pDome->Draw();
		m_pDome2->Draw();

		m_pGauge->Draw();
		m_pGaugeEnemy->Draw();

		//���̃G�t�F�N�g�\��
		for (int i = 0; i < 20; i++)
		{
			m_pLocusEffect[i]->Draw();
		}

		m_pBall[0]->Draw();
		m_pBall[1]->Draw();

		m_pUI->Draw();
		m_pScore->Draw();
		m_pCountBullet->Draw();
		m_pCountOver->Draw();
		m_pCountBoost->Draw();
		m_pTimer->Draw();

		m_pEffect[m_nPnum]->Draw();
		m_pEffect[(m_nEnum + 5)]->Draw();

		for (int i = 10; i < 16; i++)
		{
			m_pEffect[i]->Draw();
		}
	}

	//�t�F�[�h�̍쐬
	m_pFade->Draw();

}
//=============================================================================
// �ĊJ
//=============================================================================
void CGame :: Restart(void)
{
	//�L�����N�^�[�̍쐬
	m_pPlayer[0]->Restart(D3DXVECTOR3(0, 30, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pPlayer[1]->Restart(D3DXVECTOR3(0, 30, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pEnemy->Restart(D3DXVECTOR3(0,30,-200.0f),D3DXVECTOR3(0.0f,3.14f,0.0f));

	//�^�C�}�[�i���ԁj�̍쐬
	m_nTimerCount=0;
	m_pTimer->ResetTimer(TIMER_MAX);

	//�Q�[�W�̍쐬
	m_pGauge->ResetGauge(SCORE_G_MAX);
	m_pGaugeEnemy->ResetGauge(SCORE_G_MAX);

	//�T�E���h�擾�̍쐬
	CSound *pSound;
	pSound = CManager::GetSound();

	m_bChangeFlag=false;
	m_nCount=0;

	m_fDiffuse=1.0f;

	m_nGameStartCount=0;
	CManager::SetgameEndFlag(true);

	//�T�E���h�Đ��̍쐬
	//pSound->Play(SOUND_LABEL_BGM001);
}
void CGame::SetTimer(int time)
{
	//���Ԃ̕ύX
	m_pTimer->ResetTimer(time);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//�^�[���J�n
void CGame::TurnStart()
{
	//�n�܂�܂�
	if (m_nGameStartCount > 60)
	{
		if (m_nPlayerNum == 0)
		{
			m_nTurnCount++;
		}
		m_MovePow = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_pEffect[13]->SetViewFlag(true, 30);
		CManager::SetgameEndFlag(false);
		m_shotrot = D3DXVECTOR3(0, 0, 0);
		m_nSwitchCount++;
	}

	m_nGameStartCount++;
}
//���ł��J�n
void CGame::ShotStart()
{
	//�L�[�{�[�h�C���v�b�g�̎󂯎��
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	m_pEffect[10]->SetViewFlag(true, 1);

	//�e�̃X�s�[�h����
	if (pInputKeyboard->GetKeyPress(DIK_Q))
	{
		m_MovePow.y+=1.0f;
	}
	else if (pInputKeyboard->GetKeyPress(DIK_A))
	{
		m_MovePow.y -= 1.0f;
	}
	if (pInputKeyboard->GetKeyPress(DIK_W))
	{
		m_MovePow.x += 1.0f;
	}
	else if (pInputKeyboard->GetKeyPress(DIK_S))
	{
		m_MovePow.x -= 1.0f;
	}
	if (pInputKeyboard->GetKeyPress(DIK_E))
	{
		m_MovePow.z += 1.0f;
	}
	else if (pInputKeyboard->GetKeyPress(DIK_D))
	{
		m_MovePow.z -= 1.0f;
	}

	if (pInputKeyboard->GetKeyPress(DIK_RIGHT))
	{
		D3DXVECTOR3 work = m_pPlayer[m_nPlayerNum]->GetPos();
		D3DXVECTOR3 ball = m_pBall[m_nPlayerNum]->GetPos();
		m_shotrot.y += D3DX_PI * 0.05f;
		m_shotrot.y = Rotation_Normalizer(m_shotrot.y);
		work.x = ball.x - sinf(m_shotrot.y)*750.0f;
		work.z = ball.z - cosf(m_shotrot.y)*750.0f;
		work.y = m_pPlayer[m_nPlayerNum]->GetPos().y;
		m_pPlayer[m_nPlayerNum]->SetPos(work);
	}
	else if (pInputKeyboard->GetKeyPress(DIK_LEFT))
	{
		D3DXVECTOR3 work = m_pPlayer[m_nPlayerNum]->GetPos();
		D3DXVECTOR3 ball = m_pBall[m_nPlayerNum]->GetPos();
		m_shotrot.y -= D3DX_PI * 0.05f;
		m_shotrot.y = Rotation_Normalizer(m_shotrot.y);
		work.x = ball.x - sinf(m_shotrot.y)*750.0f;
		work.z = ball.z - cosf(m_shotrot.y)*750.0f;
		work.y = m_pPlayer[m_nPlayerNum]->GetPos().y;
		m_pPlayer[m_nPlayerNum]->SetPos(work);
	}

	if (pInputKeyboard->GetKeyPress(DIK_UP))
	{
		D3DXVECTOR3 work = m_pPlayer[m_nPlayerNum]->GetPos();
		D3DXVECTOR3 ball = m_pBall[m_nPlayerNum]->GetPos();
		m_shotrot.x += D3DX_PI * 0.01f;
		m_shotrot.x = Rotation_Normalizer(m_shotrot.x);
		work.x = work.x;
		work.z = work.z;
		work.y = ball.y - sinf(m_shotrot.x)*750.0f;
		m_pPlayer[m_nPlayerNum]->SetPos(work);
	}
	else if (pInputKeyboard->GetKeyPress(DIK_DOWN))
	{
		D3DXVECTOR3 work = m_pPlayer[m_nPlayerNum]->GetPos();
		D3DXVECTOR3 ball = m_pBall[m_nPlayerNum]->GetPos();
		m_shotrot.x -= D3DX_PI * 0.01f;
		m_shotrot.x = Rotation_Normalizer(m_shotrot.x);
		work.x = work.x;
		work.z = work.z;
		work.y = ball.y - sinf(m_shotrot.x)*750.0f;
		m_pPlayer[m_nPlayerNum]->SetPos(work);
	}
	//���@�X�s�[�h���߂����玟
	if (pInputKeyboard->GetKeyTrigger(DIK_RETURN))
	{
		m_nSwitchCount++;
	}
}
//�e�ړ�
void CGame::BallMove()
{
	//�X�s�[�h�ɂ���ċ����ړ�
	D3DXVECTOR3 pos = m_pBall[m_nPlayerNum]->GetPos();

	pos += m_MovePow;

	m_MovePow *= 0.5;

	m_pBall[m_nPlayerNum]->SetPos(pos);

	if (m_MovePow.x < SHOT_RIMIT && m_MovePow.y < SHOT_RIMIT && m_MovePow.z < SHOT_RIMIT)
	{
		m_pEffect[11]->SetViewFlag(true, 30);
		m_nSwitchCount++;
	}
}
//���ʔ���
void CGame::Judge()
{
	m_pEffect[12]->SetViewFlag(true, 1);

	//�����S�[��������I��
	if ((m_pBall[0]->GetGoalFlag() || m_pBall[1]->GetGoalFlag()) && !m_bJudge)
	{
		m_bJudge = true;
	}

	//�I������  �^�[�����F���Ԍo�߁F�S�[��������
	if ((m_nTurnCount>5) || (m_pTimer->GetTimer() <= 0) || (m_bJudge) && !(m_bChangeFlag))
	{
		CManager::SetgameEndFlag(true);

		m_nClearType = 2;

		//�u�r���[�h�Ȃ�
		if (m_bVsSelectFlag == true)
		{
			CScene::SetVSFlag(false);
		}

		m_pFade->StartFade(FADE_IN, 500, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_nCount = 0;
		m_bChangeFlag = true;
	}

	//�L�[�{�[�h�C���v�b�g�̎󂯎��
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//���@����Ȃ��������
	if (pInputKeyboard->GetKeyTrigger(DIK_RETURN))
	{
		m_nSwitchCount++;
	}
}
//�L�����ύX
void CGame::charachange()	
{
	//�v���C���[�؂芷��
	m_nPlayerNum++;

	//�v���C���[���S�������
	if (m_nPlayerNum >= PLAYER_MAX)
	{
		m_nPlayerNum = 0;
	}

	m_pEffect[15]->SetViewFlag(true, 30);

	m_nSwitchCount=0;
}
void CGame::InitUI(LPDIRECT3DDEVICE9 pDevice)
{

	m_nIFtype = rand() % 2;
	m_pUI = Cform2D::Create(pDevice, "data/TEXTURE/gage5.png", D3DXVECTOR3(650, 375, 0.0f), D3DXVECTOR3(0, 0, 0.0f));
	//5�ԃQ�[�W
	//�X�R�A�̍쐬
	m_pScore = CScore::Create(pDevice, D3DXVECTOR3(430.0f, 565.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 35, 55);		//�̗�
	m_pCountBullet = CCount::Create(pDevice, D3DXVECTOR3(1040.0f, 265.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10);	//�e
	m_pCountOver = CCount::Create(pDevice, D3DXVECTOR3(1040.0f, 383.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 750);	//�X�L��
	m_pCountBoost = CCount::Create(pDevice, D3DXVECTOR3(835.0f, 565.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100);	//�u�[�X�g
	//�^�C�}�[�i���ԁj�̍쐬
	m_pTimer = CTimer::Create(pDevice, D3DXVECTOR3(1035.0f, 35.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_nTimerCount = 0;
}
/////////////EOF////////////
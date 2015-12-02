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
#include "../../module/ui/Scenario.h"

#include "../../module/robot/PlayerM.h"
#include "../../module/robot/EnemyM.h"
#include "../../module/robot/PlayerGun1.h"

#include "../../module/etc/Fade.h"
#include "../../module/etc/Ball.h"
#include "../../module/etc/Goal.h"
#include "../../module/etc/LocusEffect.h"

#include "../Debugproc.h"
#include "../../exten_common.h"

#define PLAYER_MAX	(2)	//�v���C���[��
#define SHOT_RIMIT	(0.05f)
#define PLAYER_DISTANCE	(100.0f)
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
//�V�[��
CPlayerM *CGame::m_pPlayer[2] = { NULL ,NULL};
CBall*	CGame::m_pBall[2];

int CGame::m_nGameStartCount = 0;
bool CGame::m_bReplayFlag =false;
bool CGame::m_bVsSelectFlag = false;
int	CGame::m_nPlayerNum;
int	CGame::m_nSwitchCount;
bool g_wiishot;
int g_movelimit;
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

	m_pCountPar = NULL;
	m_pCountShot = NULL;

	m_pBackGround = NULL;
	m_pFade = NULL;
	m_pCharPicture[2] = {};

	m_pEffect[8] = {};
	m_pLocusEffect[19] = {};

	m_pIcon = NULL;
	m_pIconEnemy = NULL;

	m_pScenario = NULL;

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

	//���̃G�t�F�N�g�\��
	for (int i = 0; i < 20; i++)
	{
		m_pLocusEffect[i] = CLocusEffect::Create(pDevice, NULL, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	//�C���^�[�t�F�[�X��ʂ̍쐬
	InitUI(pDevice);

	//�L�����N�^�[�̍쐬
	ModelInit(pDevice);

	//�G�t�F�N�g�̍쐬
	m_pEffect[0] = CEffect::Create(pDevice, circuit_wall, D3DXVECTOR3(650.0f, 375.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pEffect[1] = CEffect::Create(pDevice, circuit_circle, D3DXVECTOR3(650.0f, 375.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 300, 300);
	m_pEffect[2] = CEffect::Create(pDevice, gage, D3DXVECTOR3(650.0f, 375.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pEffect[3] = CEffect::Create(pDevice, action, D3DXVECTOR3(650.0f, 375.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pEffect[4] = CEffect::Create(pDevice, ready1, D3DXVECTOR3(650.0f, 375.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pEffect[5] = CEffect::Create(pDevice, ready2, D3DXVECTOR3(650.0f, 375.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pEffect[6] = CEffect::Create(pDevice, please_shot, D3DXVECTOR3(650.0f, 375.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pEffect[7] = CEffect::Create(pDevice, shot_ball, D3DXVECTOR3(650.0f, 375.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pEffect[8] = CEffect::Create(pDevice, judge_timeout, D3DXVECTOR3(650.0f, 375.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//�V�i���I
	m_pScenario = CScenario::Create(pDevice, (CScenario::Character)m_nPnum, false);

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

	m_nSwitchCount = START_PHASE;

	m_nPlayerNum = 0;

	m_nTurnCount = 0;

	g_movelimit = 0;

	//�T�E���h�Đ��̍쐬
	//pSound->Play(SOUND_LABEL_BGM001);

	CManager::SetgameEndFlag(true);

	m_nGameStartCount=0;

	m_pEffect[2]->SetView(true);

	// ��M�X���b�h�J�n
	m_pFade->StartFade(FADE_OUT,50,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),CManager::GetSelectChar(0));

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

	m_pScenario->Uninit();
	delete m_pScenario;
	m_pScenario = NULL;

	m_pGoal->Uninit();
	delete m_pGoal;
	m_pGoal = NULL;

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

	m_pGoal->Update();

	//�X�V�{��
	if (!m_bChangeFlag)
	{
		switch (m_nSwitchCount)
		{
		case START_PHASE:	TurnStart();
			break;
		case SCENARIO_PHASE: GameScenario();
			break;
		case ANGLE_PHASE:	AngleDecision();
			break;
		case POWER_PHASE:	PowerDecision();
			break;
		case MOVE_PHASE:	BallMove();
			break;
		case JUDGE_PHASE:	Judge();
			break;
		case END_PHASE:		End();
			break;
		case CHANGE_PHASE:	charachange();
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
							m_pFade->StartFade(FADE_IN,100,D3DXCOLOR(1.0f,1.0f,1.0f,0.0f),CManager::GetSelectChar(0));
		
							break;
				//�G���h
				case 2 :	m_bChangeFlag=true;
							//pSound->Play(SOUND_LABEL_SE_SELECT001);
							CManager::SetpauseFlag(false);
							m_pFade->StartFade(FADE_IN,100,D3DXCOLOR(1.0f,1.0f,1.0f,0.0f),CManager::GetSelectChar(0));
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

		m_pFade->StartFade(FADE_OUT,50,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),CManager::GetSelectChar(0));

		if(m_bVsSelectFlag==false)
		{
			//�J�[�\���������Ă���R�}���h�𔭓�
			switch(m_nCount)
			{
				case 0 :	CScene::SetTime(0);
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
			CScene::SetTime(0);
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

		//���̃G�t�F�N�g�\��
		for (int i = 0; i < 20; i++)
		{
			m_pLocusEffect[i]->Draw();
		}

		m_pBall[0]->Draw();
		m_pBall[1]->Draw();

		m_pGoal->Draw();

		for (int i = 0; i < 9; i++)
		{
			m_pEffect[i]->Draw();
		}
		m_pCountPar->Draw();
		m_pScore->Draw();
		m_pScenario->Draw();
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

	//�^�C�}�[�i���ԁj�̍쐬
	m_nTimerCount=0;

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
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//�^�[���J�n
void CGame::TurnStart()
{
	//�L�[�{�[�h�C���v�b�g�̎󂯎��
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	WiiRemote *wiicon = CManager::GetWii(0);
	//�v���C���[�X�^�[�g�\��
	if (m_nGameStartCount == 0)
	{
		if (m_nPlayerNum == 0)
		{
			m_pScore->AddScore(1);
			m_nTurnCount++;
		}

		switch (m_nPlayerNum)
		{
		case 0:	m_pEffect[4]->FadeIn(60, CEffect::RIGHT);
			break;
		case 1:	m_pEffect[5]->FadeIn(60, CEffect::RIGHT);
			break;
		}
		CManager::SetgameEndFlag(false);
		m_MovePow = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_shotrot = D3DXVECTOR3(-2.4f, 0, 0);
	}

	m_nGameStartCount++;

	//�n�܂�܂�
	if (m_nGameStartCount > 60)
	{
		if (pInputKeyboard->GetKeyTrigger(DIK_RETURN) || wiicon->GetKeyTrigger(WII_BUTTOM_A))
		{
			m_nGameStartCount = 0;
			switch (m_nPlayerNum)
			{
			case 0:	m_pEffect[4]->FadeOut(60, CEffect::LEFT);
				m_pEffect[2]->SetView(false);
				m_nSwitchCount = SCENARIO_PHASE;
				break;
			case 1:	m_pEffect[5]->FadeOut(60, CEffect::LEFT);
				m_nSwitchCount = ANGLE_PHASE;
				break;
			}
		}
	}
}
//�����V�i���I
void CGame::GameScenario()
{
	//�L�[�{�[�h�C���v�b�g�̎󂯎��
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();
	WiiRemote *wiicon = CManager::GetWii(0);

	static CScenario::GameAffair affair;

	//�v���C���[�X�^�[�g�\��
	if (m_nGameStartCount == 0)
	{
		if (m_nTurnCount != 1)
		{

			D3DXVECTOR3 posBall, goal;

			goal = m_pGoal->GetPos();

			posBall = m_pBall[0]->GetPos();
			float Distance1 = (float)sqrt((double)(posBall.x - goal.x)*(double)(posBall.x - goal.x) + (double)(posBall.y - goal.y)*(double)(posBall.y - goal.y) + (double)(posBall.z - goal.z)*(double)(posBall.z - goal.z));
			posBall = m_pBall[1]->GetPos();
			float Distance2 = (float)sqrt((double)(posBall.x - goal.x)*(double)(posBall.x - goal.x) + (double)(posBall.y - goal.y)*(double)(posBall.y - goal.y) + (double)(posBall.z - goal.z)*(double)(posBall.z - goal.z));

			if (Distance1 > Distance2){ affair = CScenario::AFFAIR_WIN; }
			else if (Distance1 < Distance2){ affair = CScenario::AFFAIR_LOSE; }
			if (Distance1 + 50 > Distance2&&Distance1 - 50 < Distance2){ affair = CScenario::AFFAIR_HALF; }
		}
		else
		{
			affair = CScenario::AFFAIR_START;
		}

		m_pScenario->SetScenarioEndFlag(false);
		m_pScenario->SetViewFlag(true,0);
		m_pScenario->GameScenario(m_nGameStartCount, affair);

		m_nGameStartCount++;
		m_MovePow = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_shotrot = D3DXVECTOR3(-2.4f, 0, 0);
	}

	//�V�i���I���I��������
	if (m_pScenario->GetScenarioEndFlag())
	{
		//�G���^�[�����ďI��
		if (pInputKeyboard->GetKeyTrigger(DIK_RETURN) || wiicon->GetKeyTrigger(WII_BUTTOM_A))
		{
			m_nGameStartCount = 0;
			m_pScenario->SetViewFlag(false, 0);
			m_pEffect[2]->SetView(true);
			m_nSwitchCount = ANGLE_PHASE;
		}
	}
	else
	{
		//�G���^�[�����Ď��̃V�i���I
		if (pInputKeyboard->GetKeyTrigger(DIK_RETURN) || wiicon->GetKeyTrigger(WII_BUTTOM_A))
		{
			m_pScenario->GameScenario(m_nGameStartCount, affair);
			m_nGameStartCount++;
		}
	}
}
//�p�x����J�n
void CGame::AngleDecision()
{
	//�L�[�{�[�h�C���v�b�g�̎󂯎��
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();
	WiiRemote *wiicon = CManager::GetWii(0);

	m_pEffect[0]->SetView(true);
	m_pEffect[1]->SetView(true);

	float z = m_pEffect[1]->GetRot().z;

	z+=0.01f;

	m_pEffect[1]->SetRot(0.0f, 0.0f, z);

	D3DXVECTOR2 len = m_pEffect[1]->GetLengthWH();

	len.x += 2.0f;
	len.y += 2.0f;

	if (len.x > POLYGON_WIDTH){ len.x = 100.0f; }
	if (len.y > POLYGON_HEIGHT){ len.y = 100.0f; }

	m_pEffect[1]->SetLength(len.x, len.y);

	D3DXVECTOR3 work = m_pPlayer[m_nPlayerNum]->GetPos();
	D3DXVECTOR3 ball = m_pBall[m_nPlayerNum]->GetPos();
	if (pInputKeyboard->GetKeyPress(DIK_RIGHT) || wiicon->GetKeyPress(WII_BUTTOM_RIGHT))
	{
		m_shotrot.y += D3DX_PI * 0.01f;
		m_shotrot.y = Rotation_Normalizer(m_shotrot.y);
	}
	else if (pInputKeyboard->GetKeyPress(DIK_LEFT) || wiicon->GetKeyPress(WII_BUTTOM_LEFT))
	{
		m_shotrot.y -= D3DX_PI * 0.01f;
		m_shotrot.y = Rotation_Normalizer(m_shotrot.y);
	}

	bool rotlimit_x_max = m_shotrot.x - D3DX_PI / 4.0f < 3.14f;
	bool rotlimit_x_min = m_shotrot.x > 0.3f;
	if (pInputKeyboard->GetKeyPress(DIK_UP) || wiicon->GetKeyPress(WII_BUTTOM_UP))
	{
		if (g_movelimit > -48)
		{
			g_movelimit--;
			m_shotrot.x -= D3DX_PI * 0.01f;
			m_shotrot.x = Rotation_Normalizer(m_shotrot.x);
		}
	}
	else if (pInputKeyboard->GetKeyPress(DIK_DOWN) || wiicon->GetKeyPress(WII_BUTTOM_DOWN))
	{
		if (g_movelimit < 50)
		{
			g_movelimit++;
			m_shotrot.x += D3DX_PI * 0.01f;
			m_shotrot.x = Rotation_Normalizer(m_shotrot.x);
		}
	}
	CDebugProc::Print("shotrot::x%f y%f z%f", m_shotrot.x, m_shotrot.y, m_shotrot.z);
	work.x = ball.x -((sinf(m_shotrot.y) + cosf(m_shotrot.y))
					* (cosf(-m_shotrot.x) - sinf(-m_shotrot.x)))*PLAYER_DISTANCE;
	
	work.z = ball.z -((cosf(m_shotrot.y) - sinf(m_shotrot.y))
					* (sinf(m_shotrot.x) + cosf(m_shotrot.x)))*PLAYER_DISTANCE;
	
	work.y = ball.y - ((cosf(m_shotrot.x) - sinf(m_shotrot.x))
					)*PLAYER_DISTANCE;
	m_pPlayer[m_nPlayerNum]->SetPos(work);
	//���@�X�s�[�h���߂����玟
	if (pInputKeyboard->GetKeyTrigger(DIK_RETURN) || wiicon->GetKeyTrigger(WII_BUTTOM_A))
	{
		//�x�N�g���̊֐��Ăԏꏊ
		m_PowerShot = CheckVector(ball, work);
		m_pEffect[0]->SetView(false);
		m_pEffect[1]->SetView(false);
		m_pEffect[6]->FadeInAfterCount(20, CEffect::UP_LEFT, 50);
		m_nSwitchCount = POWER_PHASE;
		g_wiishot = false;
	}

}
//�ł͂̌���
void CGame:: PowerDecision()
{
	//�L�[�{�[�h�C���v�b�g�̎󂯎��
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();
	WiiRemote *wiicon = CManager::GetWii(0);
	//�e�̃X�s�[�h����
	if (pInputKeyboard->GetKeyPress(DIK_Q))
	{
		m_MovePow.y += 1.0f;
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

	//���@�ł͂����߂����玟
	if (pInputKeyboard->GetKeyTrigger(DIK_RETURN))
	{
		m_pEffect[7]->FadeInAfterCount(20, CEffect::UP_LEFT, 50);
		m_nSwitchCount = MOVE_PHASE;
		m_pBall[m_nPlayerNum]->AddForce(m_MovePow.x*m_PowerShot);
		m_pBall[m_nPlayerNum]->SetMoveFlag(true);
	}
	//���@�ł͂����߂����玟
	if (g_wiishot&&wiicon->GetWiiYaw() <-80.0f)
	{
		float power = (abs(wiicon->GetWiiPlusSpeed().x))*0.01f;
		m_pEffect[7]->FadeInAfterCount(20, CEffect::UP_LEFT, 50);
		m_nSwitchCount = MOVE_PHASE;
		m_pBall[m_nPlayerNum]->AddForce(power*m_PowerShot);
		m_pBall[m_nPlayerNum]->SetMoveFlag(true);
	}
	if (wiicon->GetKeyTrigger(WII_BUTTOM_A))
	{
		wiicon->SetResetFlag(true); 
		g_wiishot = true;
	}
	if (wiicon->GetKeyRelease(WII_BUTTOM_A)){
		wiicon->SetResetFlag(true);
		g_wiishot = false;
	}
}
//�e�ړ�
void CGame::BallMove()
{
	D3DXVECTOR3 velocity = m_pBall[m_nPlayerNum]->GetVelocity();
	ObjHitCheck();
	if (abs(velocity.x) < SHOT_RIMIT && abs(velocity.y) < SHOT_RIMIT && abs(velocity.z) < SHOT_RIMIT)
	{
		m_pBall[m_nPlayerNum]->SetVelocity(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		m_nSwitchCount = JUDGE_PHASE;
		m_pBall[m_nPlayerNum]->SetMoveFlag(false);
		g_movelimit = 0;
	}
}
//���ʔ���
void CGame::Judge()
{
	WiiRemote *wiicon = CManager::GetWii(0);
	ObjHitCheck();
	//�����S�[��������I��
	if ((m_pBall[0]->GetGoalFlag() && m_pBall[1]->GetGoalFlag()) && !m_bJudge)
	{
		m_bJudge = true;
	}

	//�I������  �^�[�����F���Ԍo�߁F�S�[��������
	if ((m_nTurnCount>5) || (m_bJudge) && !(m_bChangeFlag))
	{
		m_pEffect[8]->SetView(true);
		CManager::SetgameEndFlag(true);

		m_nClearType = 2;

		//�u�r���[�h�Ȃ�
		if (m_bVsSelectFlag == true)
		{
			CScene::SetVSFlag(false);
		}

		m_pFade->StartFade(FADE_IN, 500, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f),CManager::GetSelectChar(0));
		m_nCount = 0;
		m_bChangeFlag = true;
	}

	//�L�[�{�[�h�C���v�b�g�̎󂯎��
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//���@����Ȃ��������
	if (pInputKeyboard->GetKeyTrigger(DIK_RETURN) || wiicon->GetKeyTrigger(WII_BUTTOM_A))
	{
		m_nSwitchCount = END_PHASE;
	}
}
void CGame::End()
{
	WiiRemote *wiicon = CManager::GetWii(0);
	//�L�[�{�[�h�C���v�b�g�̎󂯎��
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//���@����Ȃ��������
	if (pInputKeyboard->GetKeyTrigger(DIK_RETURN) || wiicon->GetKeyTrigger(WII_BUTTOM_A))
	{
		m_nSwitchCount = CHANGE_PHASE;
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

	m_nSwitchCount = START_PHASE;
}
void CGame::InitUI(LPDIRECT3DDEVICE9 pDevice)
{
	m_nIFtype = rand() % 2;
	m_pUI = Cform2D::Create(pDevice, "data/TEXTURE/gage5.png", D3DXVECTOR3(650, 375, 0.0f), D3DXVECTOR3(0, 0, 0.0f),1300,750);
	//5�ԃQ�[�W
	//�X�R�A�̍쐬
	m_pCountPar = CCount::Create(pDevice, D3DXVECTOR3(240.0f, 45.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);	//�e
	m_pCountShot = CCount::Create(pDevice, D3DXVECTOR3(50.0f, 100.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);	//�X�L��
	m_pScore = CScore::Create(pDevice, D3DXVECTOR3(60.0f, 70.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 60, 110);		//�̗�
	//m_pGauge = CGauge::Create(pDevice, D3DXVECTOR3(680.0f, 700.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),true);
	m_nTimerCount = 0;
}
//�v���C���[�ƃ{�[���̃x�N�g�����Z�o
D3DXVECTOR3 CGame::CheckVector(D3DXVECTOR3 ball, D3DXVECTOR3 player)
{
	D3DXVECTOR3 Vector;
	Vector = ball - player;
	D3DXVec3Normalize(&Vector, &Vector);

	return Vector;
}
//
void CGame::ModelInit(LPDIRECT3DDEVICE9 pDevice)
{
	m_nPnum = CScene::GetFrame();
	m_nEnum = CScene::GetEnemy();

	m_pPlayer[0] = CPlayerM::Create(pDevice, 0, D3DXVECTOR3(0, 100, 250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_pPlayer[0]->SetVsFlag(m_bVsSelectFlag);

	m_pPlayer[1] = CPlayerM::Create(pDevice, 0, D3DXVECTOR3(0, 100, -450.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_pPlayer[1]->SetVsFlag(m_bVsSelectFlag);

	m_pBall[0] = CBall::Create(pDevice, m_nPnum, D3DXVECTOR3(0.0f, 100.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pBall[1] = CBall::Create(pDevice, m_nEnum, D3DXVECTOR3(0.0f, 100.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	ObjectInit(pDevice);
}
//
void CGame::ObjectInit(LPDIRECT3DDEVICE9 pDevice)
{
	// �t�@�C���ǂ݂��݂Ɍ�ɕύX
	m_pGoal = CGoal::Create(pDevice, 0, D3DXVECTOR3(0.0f, 500.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}
// �����蔻��
void CGame::ObjHitCheck()
{
	// �Ƃ肠�����S�[���Ƃ̓����蔻��̂�
	D3DXVECTOR3 ball = m_pBall[m_nPlayerNum]->GetPos();
	D3DXVECTOR3 obj = m_pGoal->GetPos();
	if (SphireHit(ball, 10.0f, obj, 10.0f))
	{
		if (m_nSwitchCount == JUDGE_PHASE)
		{
			m_pBall[m_nPlayerNum]->SetGoalFlag(true);
			CDebugProc::Print("�J�b�v�C������\n");
		}
	}
}
//
// OBB vs ��
//
bool CGame::ColOBBs(D3DXVECTOR3 objpos, D3DXVECTOR3 objsize, D3DXVECTOR3 objrot, D3DXVECTOR3 sphire_pos, float sphire_length)
{

	OBB obb;
	D3DXMATRIX matRot;
	D3DXMatrixRotationYawPitchRoll(&matRot, objrot.y, objrot.x, objrot.z);
	obb.SetDirect(0, D3DXVECTOR3(matRot._11, matRot._12, matRot._13));
	obb.SetDirect(1, D3DXVECTOR3(matRot._21, matRot._22, matRot._23));
	obb.SetDirect(2, D3DXVECTOR3(matRot._31, matRot._32, matRot._33));
	//obb1.SetPos_W(m_pos + m_speed);
	obb.SetPos_W(objpos);

	obb.SetLen_W(0, objsize.x);
	obb.SetLen_W(1, objsize.y);
	obb.SetLen_W(2, objsize.z);

	D3DXVECTOR3 Vec(0, 0, 0);   // �ŏI�I�ɒ��������߂�x�N�g��
	float length;
	// �e���ɂ��Ă͂ݏo�������̃x�N�g�����Z�o
	for (int i = 0; i<3; i++)
	{
		FLOAT L = obb.GetLen_W(i);
		if (L <= 0) continue;  // L=0�͌v�Z�ł��Ȃ�
		FLOAT s = D3DXVec3Dot(&(sphire_pos - obb.GetPos_W()), &obb.GetDirect(i)) / L;

		// s�̒l����A�͂ݏo��������������΂��̃x�N�g�������Z
		s = fabs(s);
		if (s > 1)	Vec += (1 - s)*L*obb.GetDirect(i);   // �͂ݏo���������̃x�N�g���Z�o
	}

	length = D3DXVec3Length(&Vec);   // �������o��

	return length < sphire_length;
}





/////////////EOF////////////
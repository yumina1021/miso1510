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
#include "../../module/ui/CharPicture.h"
#include "../../module/ui/Scenario.h"

#include "../../module/robot/PlayerM.h"

#include "../../module/etc/Fade.h"
#include "../../module/etc/Ball.h"
#include "../../module/etc/Goal.h"
#include "../../module/etc/LocusEffect.h"

#include "../../module/Gimmick/Gimmick.h"
#include "../../module/Gimmick/Magnet.h"

#include "../Debugproc.h"
#include "../../exten_common.h"
#include "../../module/etc/Camera.h"
#include "../../module/ui/Number.h"

#include "../Texture.h"
#include "../../module/etc/ShotEffect.h"

#include "../../module/ui/BlowShot.h"

#include "../../module/ui/Cupin.h"
#include "../../module/ui/Map.h"

#define PLAYER_MAX	(2)	//�v���C���[��
#define SHOT_RIMIT	(0.05f)
#define PLAYER_DISTANCE	(100.0f)
#define EFFECT_MAX	(13)
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

D3DXVECTOR3		CGame::m_PowerShot;
D3DXVECTOR3		CGame::m_playercamera;

bool g_wiishot;
bool g_cupinflag;
float g_movelimit;
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
char* g_fieldname[]
{
	"data/MAP/save.mof",
	"data/MAP/save.mof",
	"data/MAP/save.mof",
	"data/MAP/save.mof"
};
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGame :: CGame(void)
{
	m_pMeshField = NULL;
	m_pform3D = NULL;
	m_pScore = NULL;

	m_pBackGround = NULL;
	m_pFade = NULL;
	m_pCharPicture[2] = {};

	m_pEffect[10] = {};
	m_pLocusEffect[19] = {};

	m_pIcon = NULL;
	m_pIconEnemy = NULL;

	m_pScenario[0] = NULL;
	m_pScenario[1] = NULL;
	m_bcursol = false;
	m_playercamera = D3DXVECTOR3(0.f, 0.0f, 0.f);
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

	CCamera* pTmpCamera = CManager::GetCamera();
	pTmpCamera->Init();
	//�n�ʂ̍쐬
	m_pMeshField = CMeshField::Create(pDevice, 6, D3DXVECTOR3(0, 0, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100, 100, 50, 50);

	//��̍쐬
	m_pDome = CDome::Create(pDevice, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//��̍쐬
	m_pDome2 = CDomeU::Create(pDevice, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//���̃G�t�F�N�g�\��
	for (int i = 0; i < 20; i++)
	{
		m_pLocusEffect[i] = CLocusEffect::Create(pDevice, TEXTURE_STAR, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	for (int i = 0; i < SHOT_EFFECT; i++)
	{
		m_pShotEffect[i] = CShotEffect::Create(pDevice, TEXTURE_STAR, D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0));
	}
	//�C���^�[�t�F�[�X��ʂ̍쐬
	InitUI(pDevice);

	//�L�����N�^�[�̍쐬
	ModelInit(pDevice);

	//�G�t�F�N�g�̍쐬
	m_pEffect[0] = CEffect::Create(pDevice, circuit_wall, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pEffect[1] = CEffect::Create(pDevice, circuit_wall2, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_pEffect[2] = CEffect::Create(pDevice, circuit_circle, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 300, 300);
	m_pEffect[3] = CEffect::Create(pDevice, gage, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pEffect[4] = CEffect::Create(pDevice, ready1, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pEffect[5] = CEffect::Create(pDevice, ready2, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pEffect[6] = CEffect::Create(pDevice, (EffectNum)(please_shot_rosa + m_nPnum), D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pEffect[7] = CEffect::Create(pDevice, (EffectNum)(shot_ball_rosa + m_nPnum), D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_pEffect[8] = CEffect::Create(pDevice, (EffectNum)(please_shot_rosa + m_nEnum), D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pEffect[9] = CEffect::Create(pDevice, (EffectNum)(shot_ball_rosa + m_nEnum), D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_pEffect[10] = CEffect::Create(pDevice, judge_timeout, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_pEffect[11] = CEffect::Create(pDevice, (EffectNum)(game_rosa + m_nPnum), D3DXVECTOR3(SCREEN_WIDTH / 2+80.0f, SCREEN_HEIGHT -100, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH-100, 200);
	m_pEffect[12] = CEffect::Create(pDevice, (EffectNum)(game_rosa + m_nEnum), D3DXVECTOR3(-400, 100, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH-100, 200);

	//�V�i���I
	m_pScenario[0] = CScenario::Create(pDevice, (CScenario::Character)m_nPnum, false);
	m_pScenario[1] = CScenario::Create(pDevice, (CScenario::Character)m_nEnum, false);

	//Pause
	//�w�i�̍쐬
	//m_pBackGround=CBackGround::Create(pDevice,BACKGROUND_GAME);

	//�����̔z�u
	m_pCharPicture[0]=CCharPicture::Create(pDevice,p_continue,D3DXVECTOR3(1100.0f,450.0f,0.0f),400,100);
	m_pCharPicture[1]=CCharPicture::Create(pDevice,p_retry,D3DXVECTOR3(1100.0f,550.0f,0.0f),400,100);
	m_pCharPicture[2]=CCharPicture::Create(pDevice,p_quit,D3DXVECTOR3(1100.0f,650.0f,0.0f),400,100);

	//�t�F�[�h�̍쐬
	m_pFade=CFade::Create(pDevice,1);

	m_pBlowEffect = CBlowShot::Create(pDevice, m_nPnum, m_nEnum);

	m_pCupin = CCupin::Create(pDevice);
	float length_n = 100.0f;
	//m_pgoalnavi[0] = Cform2D::Create(pDevice, TEXTURE_LOSER, D3DXVECTOR3(SCREEN_WIDTH / 2, length_n, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), length_n, length_n);
	//m_pgoalnavi[1] = Cform2D::Create(pDevice, TEXTURE_LOSER, D3DXVECTOR3(length_n, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI / 2), length_n, length_n);
	//m_pgoalnavi[2] = Cform2D::Create(pDevice, TEXTURE_LOSER, D3DXVECTOR3(SCREEN_WIDTH - length_n, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI / 2), length_n, length_n);
	//m_pgoalnavi[3] = Cform2D::Create(pDevice, TEXTURE_LOSER, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - length_n, 0.0f), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI), length_n, length_n);

	m_pgoalnavi[0] = Cform2D::Create(pDevice, TEXTURE_GOAL_NAVI, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - length_n * 2.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), length_n * 2, length_n);
	m_pgoalnavi[1] = Cform2D::Create(pDevice, TEXTURE_GOAL_NAVI, D3DXVECTOR3(SCREEN_WIDTH / 2 - length_n * 2.0f, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI / 2), length_n * 2, length_n);
	m_pgoalnavi[2] = Cform2D::Create(pDevice, TEXTURE_GOAL_NAVI, D3DXVECTOR3(SCREEN_WIDTH / 2 + length_n * 2.0f, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI / 2), length_n * 2, length_n);
	m_pgoalnavi[3] = Cform2D::Create(pDevice, TEXTURE_GOAL_NAVI, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + length_n * 2.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI), length_n * 2, length_n);
	for (int i = 0; i < 4; i++)
	{
		m_bnaviFlag[i] = false;
	}
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


	//�T�E���h�Đ��̍쐬
	pSound->Play(SOUND_LABEL_BGM002);

	CManager::SetgameEndFlag(true);

	m_nGameStartCount=0;

	m_pEffect[3]->SetView(true);
	m_pEffect[11]->SetView(true);
	m_pEffect[12]->SetView(true);

	D3DXVECTOR3 gpos = m_pGoal->GetPos();
	D3DXVECTOR3 bpos = m_pBall[0]->GetPos();
	m_fCupDistance[0] = (abs(D3DXVec3Length(&(bpos - gpos))) / 10);
	m_pCountDistance[0]->ResetCount((int)m_fCupDistance[0]);

	bpos = m_pBall[1]->GetPos();
	m_fCupDistance[1] = (abs(D3DXVec3Length(&(bpos - gpos))) / 10);
	m_pCountDistance[1]->ResetCount((int)m_fCupDistance[1]);

	// ��M�X���b�h�J�n
	m_pFade->StartFade(FADE_OUT,50,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),CManager::GetSelectChar(0));

	CManager::SetWin(PLAYER_DRAW);

	m_fnavimove = 0.0f;

	m_bBlowFlag = 0.0f;

	m_pMap->SetDrawFlag(false);
	m_bLichtBlow = false;
	m_bLilaBlow = false;
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

	for (int i = 0; i < 2; i++)
	{
		m_pScenario[i]->Uninit();
		delete m_pScenario[i];
		m_pScenario[i] = NULL;
	}

	delete[] m_pGimmick_stage;
	m_pGoal->Uninit();
	delete m_pGoal;
	m_pGoal = NULL;

	m_pBlowEffect->Uninit();
	delete m_pBlowEffect;
	m_pCupin->Uninit();
	delete m_pCupin;
	m_pMap->Uninit();
	delete m_pMap;

	delete m_nStageinfo;
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
	WiiRemote *wiicon = CManager::GetWii(m_nPlayerNum);
	for (int i = 0; i < SHOT_EFFECT; i++)
	{
		m_pShotEffect[i]->Update();
	}
	m_pCupin->Update();
	if (pInputKeyboard->GetKeyTrigger(DIK_I) || wiicon->GetKeyTrigger(WII_BUTTOM_1))
	{
		m_pMap->MapChagePlus();
	}
	if (pInputKeyboard->GetKeyTrigger(DIK_O) || wiicon->GetKeyTrigger(WII_BUTTOM_2))
	{
		m_pMap->MapChageMinus();
	}
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
		case CUPIN_PHASE:	CupIn();
			break;
		case END_PHASE:		End();
			break;
		case CHANGE_PHASE:	charachange();
			break;
		}
	}
	m_pBlowEffect->Update();


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
	m_pMap->Update();
}
//=============================================================================
// �`��
//=============================================================================
void CGame :: Draw(void)
{
	if (CManager::GetpauseFlag())
	{
		//m_pBackGround->Draw();

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


		if (m_bcursol)m_cursol->Draw();
		m_pGoal->Draw();
		for (int i = 0; i < m_nGimmickmax; i++)
		{
			m_pGimmick_stage[i]->Draw();
		}
		m_pBall[0]->Draw();
		m_pBall[1]->Draw();

		if ((m_nSwitchCount == POWER_PHASE) || (m_nSwitchCount == MOVE_PHASE) || (m_nSwitchCount == JUDGE_PHASE || (m_nSwitchCount == END_PHASE)))m_pPlayer[m_nPlayerNum]->Draw();

		if ((m_nSwitchCount == POWER_PHASE) || (m_nSwitchCount == MOVE_PHASE))
		{
			for (int i = 0; i < SHOT_EFFECT; i++)
			{
				m_pShotEffect[i]->Draw();
			}
		}
		m_pMap->Draw();
		m_pCupin->Draw();
		for (int i = 0; i < EFFECT_MAX; i++)
		{
			m_pEffect[i]->Draw();
		}

		m_pCountDistance[0]->Draw();
		m_pCountDistance[1]->Draw();

		m_pScore->Draw();
		m_pScenario[m_nPlayerNum]->Draw();
		m_pBlowEffect->Draw();

		for (int i = 0; i < 4; i++)
		{
			if (m_bnaviFlag[i])m_pgoalnavi[i]->Draw();
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

	WiiRemote *wiicon = CManager::GetWii(m_nPlayerNum);
	//�v���C���[�X�^�[�g�\��
	if (m_nGameStartCount == 0)
	{
		if (m_nPlayerNum == 0)
		{
			m_nTurnCount++;
		}

		m_pScore->ResetScore(m_nTurnCount);
		if (m_pGoal->GetMagnet() == N){ m_pGoal->SetMagnet(S); }
		else{ m_pGoal->SetMagnet(N); }

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
		m_vecrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_playerrot_x = m_shotrot.x;

	}

	m_nGameStartCount++;

	//�n�܂�܂�
	if (m_nGameStartCount > 60)
	{
		if (pInputKeyboard->GetKeyTrigger(DIK_RETURN) || wiicon->GetKeyTrigger(WII_BUTTOM_A))
		{
			m_bBlowFlag = false;
			m_nGameStartCount = 0;
			m_pBall[m_nPlayerNum]->SetAlpha(0.3f);
			D3DXVECTOR3 vec;
			for (int i = 0; i < SHOT_EFFECT; i++)
			{
				vec.x = mersenne_twister_f32(-1.0f, 1.0f);
				vec.y = mersenne_twister_f32(-1.0f, 1.0f);
				vec.z = mersenne_twister_f32(-1.0f, 1.0f);
				m_pShotEffect[i]->SetRandVector(vec);
			}

			switch (m_nPlayerNum)
			{
			case 0:	m_pEffect[4]->FadeOut(60, CEffect::LEFT);
				m_pEffect[3]->SetView(false);
				m_pEffect[11]->SetView(false);
				m_pEffect[12]->SetView(false);
				m_pScore->SetViewFlag(false);
				m_pCountDistance[0]->SetViewFlag(false);
				m_pCountDistance[1]->SetViewFlag(false);

				m_nSwitchCount = SCENARIO_PHASE;
				break;
			case 1:	m_pEffect[5]->FadeOut(60, CEffect::LEFT);
				m_pEffect[3]->SetView(false);
				m_pEffect[11]->SetView(false);
				m_pEffect[12]->SetView(false);
				m_pScore->SetViewFlag(false);
				m_pCountDistance[0]->SetViewFlag(false);
				m_pCountDistance[1]->SetViewFlag(false);

				m_nSwitchCount = SCENARIO_PHASE;
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
	WiiRemote *wiicon = CManager::GetWii(m_nPlayerNum);

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

		m_pScenario[m_nPlayerNum]->SetScenarioEndFlag(false);
		m_pScenario[m_nPlayerNum]->SetViewFlag(true,0);
		m_pScenario[m_nPlayerNum]->GameScenario(m_nGameStartCount, affair);

		m_nGameStartCount++;
		m_MovePow = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_shotrot = D3DXVECTOR3(-2.4f, 0, 0);
	}

	//�V�i���I���I��������
	if (m_pScenario[m_nPlayerNum]->GetScenarioEndFlag())
	{
		//�G���^�[�����ďI��
		if (pInputKeyboard->GetKeyTrigger(DIK_RETURN) || wiicon->GetKeyTrigger(WII_BUTTOM_A))
		{
			m_pMap->SetDrawFlag(true);
			m_nGameStartCount = 0;
			m_pScenario[m_nPlayerNum]->SetViewFlag(false, 0);
			if (m_pBall[m_nPlayerNum]->GetMagnet() == S){ m_pEffect[0]->SetView(true); }
			else{ m_pEffect[1]->SetView(true); }
			m_pEffect[3]->SetView(true);
			m_pEffect[11]->SetView(true);
			m_pEffect[12]->SetView(true);
			m_pScore->SetViewFlag(true);
			m_pCountDistance[0]->SetViewFlag(true);
			m_pCountDistance[1]->SetViewFlag(true);
			g_movelimit = 0;
			m_nSwitchCount = ANGLE_PHASE;
			m_bcursolmove = 0.0f;
		}
	}
	else
	{
		//�G���^�[�����Ď��̃V�i���I
		if (pInputKeyboard->GetKeyTrigger(DIK_RETURN) || wiicon->GetKeyTrigger(WII_BUTTOM_A))
		{
			m_pScenario[m_nPlayerNum]->GameScenario(m_nGameStartCount, affair);
			m_nGameStartCount++;
		}
	}
}
//�p�x����J�n
void CGame::AngleDecision()
{
	//�L�[�{�[�h�C���v�b�g�̎󂯎��
	m_bcursol = true;
	
	m_bcursolmove += 25.0f;
	if (m_bcursolmove > 500.0f)
	{
		m_bcursolmove = 0.0f;
	}
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();
	WiiRemote *wiicon = CManager::GetWii(m_nPlayerNum);

	m_pEffect[2]->SetView(true);

	float z = m_pEffect[2]->GetRot().z;

	z+=0.01f;

	m_pEffect[2]->SetRot(0.0f, 0.0f, z);

	D3DXVECTOR2 len = m_pEffect[2]->GetLengthWH();

	len.x += 2.0f;
	len.y += 2.0f;

	if (len.x > POLYGON_WIDTH){ len.x = 100.0f; }
	if (len.y > POLYGON_HEIGHT){ len.y = 100.0f; }

	m_pEffect[2]->SetLength(len.x, len.y);

	//���ɐؑ�
	if (pInputKeyboard->GetKeyTrigger(DIK_SPACE))
	{
		if (m_pBall[m_nPlayerNum]->GetMagnet() == N){ m_pBall[m_nPlayerNum]->SetMagnet(S); m_pEffect[0]->SetView(true); m_pEffect[1]->SetView(false); }
		else{ m_pBall[m_nPlayerNum]->SetMagnet(N); m_pEffect[0]->SetView(false); m_pEffect[1]->SetView(true); }
	}

	if (wiicon->GetKeyTrigger(WII_BUTTOM_PLUS))
	{
		m_pBall[m_nPlayerNum]->SetMagnet(S);
		m_pEffect[0]->SetView(true);
		m_pEffect[1]->SetView(false);
	}
	if (wiicon->GetKeyTrigger(WII_BUTTOM_MINUS))
	{
		m_pBall[m_nPlayerNum]->SetMagnet(N);
		m_pEffect[0]->SetView(false);
		m_pEffect[1]->SetView(true);
	}

	D3DXVECTOR3 work = m_pPlayer[m_nPlayerNum]->GetPos();
	D3DXVECTOR3 ball = m_pBall[m_nPlayerNum]->GetPos();
	if (pInputKeyboard->GetKeyPress(DIK_RIGHT) || wiicon->GetKeyPress(WII_BUTTOM_RIGHT))
	{
		m_shotrot.y += D3DX_PI * 0.005f;
		m_vecrot.y += D3DX_PI * 0.005f;
		m_shotrot.y = Rotation_Normalizer(m_shotrot.y);
		m_vecrot.y = Rotation_Normalizer(m_vecrot.y);
	}
	else if (pInputKeyboard->GetKeyPress(DIK_LEFT) || wiicon->GetKeyPress(WII_BUTTOM_LEFT))
	{
		m_shotrot.y -= D3DX_PI * 0.005f;
		m_vecrot.y -= D3DX_PI * 0.005f;
		m_shotrot.y = Rotation_Normalizer(m_shotrot.y);
		m_vecrot.y = Rotation_Normalizer(m_vecrot.y);
	}

	bool rotlimit_x_max = (int)g_movelimit > -48;
	bool rotlimit_x_min = (int)g_movelimit < 50;
	if (pInputKeyboard->GetKeyPress(DIK_UP) || wiicon->GetKeyPress(WII_BUTTOM_UP))
	{
		if (rotlimit_x_max)
		{
			g_movelimit -= 1.0f * 0.5f;
			m_shotrot.x -= D3DX_PI * 0.005f;
			m_vecrot.x -= D3DX_PI * 0.005f;
			m_playerrot_x += D3DX_PI * 0.01f;
			m_shotrot.x = Rotation_Normalizer(m_shotrot.x);
			m_vecrot.x = Rotation_Normalizer(m_vecrot.x);
			m_playerrot_x = Rotation_Normalizer(m_playerrot_x);
		}
	}
	else if (pInputKeyboard->GetKeyPress(DIK_DOWN) || wiicon->GetKeyPress(WII_BUTTOM_DOWN))
	{
		if (rotlimit_x_min)
		{
			g_movelimit += 1.0f * 0.5f;
			m_shotrot.x += D3DX_PI * 0.005f;
			m_vecrot.x += D3DX_PI * 0.005f;
			m_playerrot_x -= D3DX_PI * 0.01f;
			m_shotrot.x = Rotation_Normalizer(m_shotrot.x);
			m_vecrot.x = Rotation_Normalizer(m_vecrot.x);
			m_playerrot_x = Rotation_Normalizer(m_playerrot_x);
		}
	}
	float work_x = (sinf(m_shotrot.y) + cosf(m_shotrot.y)) * (cosf(-m_shotrot.x) - sinf(-m_shotrot.x));
	float work_z = (cosf(m_shotrot.y) - sinf(m_shotrot.y)) * (sinf(m_shotrot.x) + cosf(m_shotrot.x))  ;
	float work_xp = (sinf(m_shotrot.y + D3DX_PI * 0.5f) + cosf(m_shotrot.y + D3DX_PI * 0.5f));
	float work_zp = (cosf(m_shotrot.y + D3DX_PI * 0.5f) - sinf(m_shotrot.y + D3DX_PI * 0.5f));
	float work_xpp = (sinf(m_shotrot.y - D3DX_PI) + cosf(m_shotrot.y - D3DX_PI)) * (cosf(-m_shotrot.x - D3DX_PI) - sinf(-m_shotrot.x - D3DX_PI));
	float work_zpp = (cosf(m_shotrot.y - D3DX_PI) - sinf(m_shotrot.y - D3DX_PI)) * (sinf(m_shotrot.x - D3DX_PI) + cosf(m_shotrot.x - D3DX_PI));
	work.x = ball.x - work_x * PLAYER_DISTANCE;
	
	work.z = ball.z - work_z *PLAYER_DISTANCE;
	
	work.y = ball.y - ((cosf(m_shotrot.x) - sinf(m_shotrot.x)))*(PLAYER_DISTANCE + 100);
	D3DXVECTOR3 work_p;

	m_playercamera = work;	
	work_p.x = ball.x + work_xp * 20.0f - work_xpp * 10.0f;

	work_p.z = ball.z + work_zp * 20.0f - work_zpp * 10.0f;

	work_p.y = ball.y + ((cosf(m_playerrot_x) - sinf(m_playerrot_x))) * 10.0f;
	m_PowerShot = CheckVector(ball, work);
	// �J�[�\���̕\��
	m_cursol->SetPos(ball + m_PowerShot * m_bcursolmove);
	m_cursol->SetRotReal(D3DXVECTOR3(m_vecrot.x, m_vecrot.y + D3DX_PI / 4, 0.0f));
	m_pPlayer[m_nPlayerNum]->SetRot(D3DXVECTOR3(m_vecrot.x + D3DX_PI  * 0.005f * sinf(m_vecrot.x),
												m_vecrot.y + D3DX_PI  * 0.5f - D3DX_PI  * 0.225f * cosf(m_vecrot.x),
												D3DX_PI  * 0.25f * sinf(m_vecrot.x)));
	m_pPlayer[m_nPlayerNum]->SetPos(work_p);


	// �S�[���ʒu����
	D3DXVECTOR3 goal_vec;
	goal_vec = CheckVector(m_pGoal->GetPos(), ball);
	m_fnavimove += 0.1f;

	m_fnavimove = Rotation_Normalizer(m_fnavimove);

	for (int i = 0; i < 4; i++)
	{
		D3DXVECTOR3 nevi_pos = m_pgoalnavi[i]->GetPos();
		switch ((i))
		{
		case 0: nevi_pos.y -= sinf(m_fnavimove) * 5; break;
		case 1: nevi_pos.x -= sinf(m_fnavimove) * 5; break;
		case 2: nevi_pos.x += sinf(m_fnavimove) * 5; break;
		case 3: nevi_pos.y += sinf(m_fnavimove) * 5; break;
		default:
			break;
		}
		m_pgoalnavi[i]->SetPos(nevi_pos);
	}

	D3DXVECTOR3 cross;
	D3DXVec3Cross(&cross, &goal_vec, &m_PowerShot);

	if (cross.z > 0.0f){ m_bnaviFlag[2] = true; m_bnaviFlag[1] = false; }
	else if (cross.z < 0.0f){ m_bnaviFlag[2] = false; m_bnaviFlag[1] = true; }
	else{ m_bnaviFlag[2] = false; m_bnaviFlag[1] = false; }

	if (goal_vec.y - m_PowerShot.y> 0.2f){ m_bnaviFlag[0] = true; m_bnaviFlag[3] = false; }
	else if (goal_vec.y - m_PowerShot.y < -0.2f){ m_bnaviFlag[0] = false; m_bnaviFlag[3] = true; }
	else{ m_bnaviFlag[0] = false; m_bnaviFlag[3] = false; }

	if (calcRaySphere(ball, m_PowerShot, m_pGoal->GetPos(), m_fCupDistance[m_nPlayerNum] * 5.0f))
	{
		for (int i = 0; i < 4; i++)
		{
			m_bnaviFlag[i] = false;
		}
	}

	if (pInputKeyboard->GetKeyTrigger(DIK_RETURN) || wiicon->GetKeyTrigger(WII_BUTTOM_A))
	{
		for (int i = 0; i < 4; i++)
		{
			m_bnaviFlag[i] = false;
		}
		m_pBall[m_nPlayerNum]->SetAlpha(1.0f);
		//�x�N�g���̊֐��Ăԏꏊ
		m_pEffect[0]->SetView(false);
		m_pEffect[1]->SetView(false);
		m_pEffect[2]->SetView(false);
		if (m_nPlayerNum == 0)
		{
			m_pEffect[6]->FadeInAfterCount(20, CEffect::UP_LEFT, 50);
		}
		else
		{
			m_pEffect[8]->FadeInAfterCount(20, CEffect::UP_LEFT, 50);
		}
		m_nSwitchCount = POWER_PHASE;
		g_wiishot = false;
		m_bcursol = false;
	}
}
//�ł͂̌���
void CGame:: PowerDecision()
{
	//�L�[�{�[�h�C���v�b�g�̎󂯎��
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();
	WiiRemote *wiicon = CManager::GetWii(m_nPlayerNum);
	D3DXVECTOR3 ball = m_pBall[m_nPlayerNum]->GetPos();
	//�T�E���h�擾�̍쐬
	CSound *pSound;
	pSound = CManager::GetSound();
	//�e�̃X�s�[�h����
	if (pInputKeyboard->GetKeyPress(DIK_W))
	{
		m_MovePow.x += 1.0f;
	}
	else if (pInputKeyboard->GetKeyPress(DIK_S))
	{
		m_MovePow.x -= 1.0f;
	}

	if ((pInputKeyboard->GetKeyPress(DIK_K) || wiicon->GetKeyTrigger(WII_BUTTOM_DOWN)) && !m_bBlowFlag)
	{
		m_pBlowEffect->SetFlag(true, m_nPlayerNum);
		m_bBlowFlag = true;
	}
	if (pInputKeyboard->GetKeyPress(DIK_C))
	{
		m_pCupin->SetFlag(true);
		m_pCupin->SetDrawFlag(true);
	}
	if (pInputKeyboard->GetKeyPress(DIK_V))
	{
		m_pCupin->SetFlag(false);
		m_pCupin->SetDrawFlag(false);
	}
	//���@�ł͂����߂����玟
	if (pInputKeyboard->GetKeyTrigger(DIK_RETURN) && !m_pBlowEffect->GetFlag(m_nPlayerNum))
	{
		m_pBall[m_nPlayerNum]->SetShotNum(m_pBall[m_nPlayerNum]->GetShotNum() + 1);
		m_bStageflag[m_nPlayerNum] = false;
		m_bStageflagcount[m_nPlayerNum] = 0;
		for (int i = 0; i < SHOT_EFFECT; i++)
		{
			m_pShotEffect[i]->SetFlag(true);
			m_pShotEffect[i]->SetVector(-m_PowerShot);
			m_pShotEffect[i]->SetPos(ball);
		}
		if (m_nPlayerNum == 0)
		{
			m_pEffect[7]->FadeInAfterCount(20, CEffect::UP_LEFT, 50);
		}
		else
		{
			m_pEffect[9]->FadeInAfterCount(20, CEffect::UP_LEFT, 50);
		}
		pSound->Play(SOUND_LABEL_SE_SHOT);
		m_nSwitchCount = MOVE_PHASE;
		m_pBall[m_nPlayerNum]->SetCircle(m_PowerShot);
		m_pBall[m_nPlayerNum]->AddForce(m_MovePow.x*m_PowerShot);
		m_pBall[m_nPlayerNum]->SetMoveFlag(true);
	}
	//���@�ł͂����߂����玟
	//if (g_wiishot&&wiicon->GetWiiYaw() <-40.0f)
	if (g_wiishot&&abs(wiicon->GetWiiYaw()) > 40.0f && !m_pBlowEffect->GetFlag(m_nPlayerNum))
	{
		m_pBall[m_nPlayerNum]->SetShotNum(m_pBall[m_nPlayerNum]->GetShotNum() + 1);
		for (int i = 0; i < SHOT_EFFECT; i++)
		{
			m_pShotEffect[i]->SetFlag(true);
			m_pShotEffect[i]->SetVector(-m_PowerShot);
			m_pShotEffect[i]->SetPos(ball);
		}
		float power = (abs(wiicon->GetWiiPlusSpeed().x))*0.01f;
		if (m_nPlayerNum == 0)
		{
			m_pEffect[7]->FadeInAfterCount(20, CEffect::UP_LEFT, 50);
		}
		else
		{
			m_pEffect[9]->FadeInAfterCount(20, CEffect::UP_LEFT, 50);
		}
		pSound->Play(SOUND_LABEL_SE_SHOT);

		m_nSwitchCount = MOVE_PHASE;
		if (m_bLichtBlow)
		{
			power *= 0.5f;
		}
		m_pBall[m_nPlayerNum]->AddForce(power*m_PowerShot);
		m_pBall[m_nPlayerNum]->SetMoveFlag(true);
	}
	if (wiicon->GetKeyTrigger(WII_BUTTOM_A))
	{
		wiicon->SetResetFlag(true);
		m_pPlayer[m_nPlayerNum]->SetMotion(MOTIONTYPE_SHOT);
		g_wiishot = true;
	}
	if (wiicon->GetKeyPress(WII_BUTTOM_A))
	{
		float y = wiicon->GetWiiYaw();
		y = abs(y);
		m_pPlayer[m_nPlayerNum]->SetMotionRatio(y);
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
	D3DXVECTOR3 bpos = m_pBall[m_nPlayerNum]->GetPos();
	D3DXVECTOR3 gpos = m_pGoal->GetPos();
	m_fCupDistance[m_nPlayerNum] = abs(D3DXVec3Length(&(bpos - gpos))) / 10;
	m_pCountDistance[0]->ResetCount((int)m_fCupDistance[m_nPlayerNum]);
	if (abs(velocity.x) < SHOT_RIMIT && abs(velocity.y) < SHOT_RIMIT && abs(velocity.z) < SHOT_RIMIT)
	{
		m_pBall[0]->SetVelocity(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		m_pBall[1]->SetVelocity(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		m_nSwitchCount = JUDGE_PHASE;
		m_pBall[0]->SetMoveFlag(false);
		m_pBall[1]->SetMoveFlag(false);
		for (int i = 0; i < SHOT_EFFECT; i++)
		{
			m_pShotEffect[i]->SetFlag(false);
		}
		m_pBlowEffect->SetFlag(false, m_nPlayerNum);
		m_bBlowFlag = false;
	}
}
//���ʔ���
void CGame::Judge()
{
	WiiRemote *wiicon = CManager::GetWii(m_nPlayerNum);
	ObjHitCheck();	//�_���}��

	//�����S�[��������I��
	if ((m_pBall[0]->GetGoalFlag() && m_pBall[1]->GetGoalFlag()) && !m_bJudge)
	{
		m_bJudge = true;
	}
	
	m_pCountDistance[0]->ResetCount((int)m_fCupDistance[m_nPlayerNum]);

	//�L�[�{�[�h�C���v�b�g�̎󂯎��
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//���@����Ȃ��������
	if (pInputKeyboard->GetKeyTrigger(DIK_RETURN) || wiicon->GetKeyTrigger(WII_BUTTOM_A))
	{
		m_nSwitchCount = END_PHASE;		
		if (m_pBall[m_nPlayerNum]->GetGoalFlag())
		{
			m_nSwitchCount = CUPIN_PHASE;
			m_fCupDistance[m_nPlayerNum] = 0.0f;
			m_pCountDistance[0]->ResetCount((int)m_fCupDistance[m_nPlayerNum]);
			m_pCupin->SetDrawFlag(true);
			m_pCupin->SetFlag(true);
			g_cupinflag = false;
		}
	}
}
void CGame::CupIn()
{
	WiiRemote *wiicon = CManager::GetWii(m_nPlayerNum);
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();
	if (!m_pCupin->GetFlag() && !g_cupinflag)
	{
		m_pScenario[m_nPlayerNum]->SetScenarioEndFlag(false);
		m_pScenario[m_nPlayerNum]->SetViewFlag(true, 0);
		m_pScenario[m_nPlayerNum]->GameScenario(m_nGameStartCount, CScenario::AFFAIR_CUPIN);
		g_cupinflag = true;
	}
	//�V�i���I���I��������
	if (m_pScenario[m_nPlayerNum]->GetScenarioEndFlag() && g_cupinflag)
	{
		//�G���^�[�����ďI��
		if (pInputKeyboard->GetKeyTrigger(DIK_RETURN) || wiicon->GetKeyTrigger(WII_BUTTOM_A))
		{
			m_nGameStartCount = 0;
			m_pScenario[m_nPlayerNum]->SetViewFlag(false, 0);
			m_pGoal->Sethit(0.0f);
			m_nSwitchCount = END_PHASE;
			m_pCupin->SetDrawFlag(false);
			m_pCupin->SetFlag(false);
			g_cupinflag = false;
		}
	}
	else
	{
		//�G���^�[�����Ď��̃V�i���I
		if (pInputKeyboard->GetKeyTrigger(DIK_RETURN) || wiicon->GetKeyTrigger(WII_BUTTOM_A))
		{
			m_nGameStartCount++;
			m_pScenario[m_nPlayerNum]->GameScenario(m_nGameStartCount, CScenario::AFFAIR_CUPIN);
		}
	}
}
void CGame::End()
{
	//�L�[�{�[�h�C���v�b�g�̎󂯎��
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();
	WiiRemote *wiicon = CManager::GetWii(m_nPlayerNum);
	bool endflag = false;
	//�I������  �^�[�����F���Ԍo�߁F�S�[��������
	if ((m_nTurnCount>5) || (m_bJudge) && !(m_bChangeFlag))
	{
		m_pEffect[10]->SetView(true);

		m_nClearType = 2;
		//�u�r���[�h�Ȃ�
		if (m_bVsSelectFlag == true)
		{
			CScene::SetVSFlag(false);
		}
		if (m_pBall[0]->GetShotNum() < m_pBall[1]->GetShotNum())
		{
			CManager::SetWin(PLAYER1_WIN);
		}
		else if (m_pBall[0]->GetShotNum() > m_pBall[1]->GetShotNum())
		{
			CManager::SetWin(PLAYER2_WIN);
		}
		else
		{
			CManager::SetWin(PLAYER_DRAW);
		}
		m_nCount = 0;
		endflag = true;
	}

	//���@����Ȃ��������
	if (pInputKeyboard->GetKeyTrigger(DIK_RETURN) || wiicon->GetKeyTrigger(WII_BUTTOM_A))
	{
		m_bLichtBlow = false;
		m_bLilaBlow = false;
		if (m_bBlowFlag && m_pPlayer[m_nPlayerNum]->GetType() == 1)
		{
			m_bLilaBlow = true;
		}
		if (m_bBlowFlag && m_pPlayer[m_nPlayerNum]->GetType() == 2)
		{
			m_bLichtBlow = true;
		}
		m_pMap->SetDrawFlag(false);
		if (endflag)
		{
			m_bChangeFlag = true;
			CManager::SetgameEndFlag(true);
			m_pFade->StartFade(FADE_IN, 500, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), CManager::GetSelectChar(0));
		} else{
		m_pGoal->Sethit(0.0f);
		m_nSwitchCount = CHANGE_PHASE;
		}
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

	if (m_pBall[m_nPlayerNum]->GetGoalFlag())
	{
		if (m_nPlayerNum == 0)
		{
			m_nTurnCount++;
			m_nPlayerNum = 1;
		}
		else
		{
			m_nPlayerNum = 0;
		}
	}

	if (m_nPlayerNum==0)
	{
		m_pEffect[11]->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2 + 80.0f, SCREEN_HEIGHT - 100, 0.0f));
		m_pEffect[12]->SetPos(D3DXVECTOR3(-400, 100, 0.0f));

		m_pCountDistance[0]->ResetCount((int)m_fCupDistance[0]);
		m_pCountDistance[1]->ResetCount((int)m_fCupDistance[1]);
	}
	else if (m_nPlayerNum == 1)
	{
		m_pEffect[12]->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2 + 80.0f, SCREEN_HEIGHT - 100, 0.0f));
		m_pEffect[11]->SetPos(D3DXVECTOR3(-400, 100, 0.0f));

		m_pCountDistance[0]->ResetCount((int)m_fCupDistance[1]);
		m_pCountDistance[1]->ResetCount((int)m_fCupDistance[0]);
	}

	m_nSwitchCount = START_PHASE;
}
void CGame::InitUI(LPDIRECT3DDEVICE9 pDevice)
{
	m_nIFtype = rand() % 2;
	m_pUI = Cform2D::Create(pDevice, TEXTURE_GAGE, D3DXVECTOR3(650, 375, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 1300, 750);
	//5�ԃQ�[�W
	//�X�R�A�̍쐬
	float pos = 500;
	float length = 35.0f; 
	float scl = 6.0f;
	m_pScore = CScore::Create(pDevice, D3DXVECTOR3(1000.0f, 45.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 60, 110);		//�̗�
	m_pCountDistance[0] = CCount::Create(pDevice, D3DXVECTOR3(SCREEN_WIDTH / 2-60, SCREEN_HEIGHT - 100, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),0, 60, 110);
	m_pCountDistance[1] = CCount::Create(pDevice, D3DXVECTOR3(SCREEN_WIDTH / 4-60, 20, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),0, 35, 70);
	m_nTimerCount = 0;
	m_fCupDistance[0] = 0.0f;
	m_fCupDistance[1] = 0.0f;
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
	m_nPnum = CManager::GetSelectChar(0);
	m_nEnum = CManager::GetSelectChar(1);
	ObjectInit(pDevice);
	m_startpos[0] = D3DXVECTOR3(0.0f, 300.0f, 400.0f);
	m_startpos[1] = D3DXVECTOR3(400.0f, -300.0f, 0.0f);

	m_pPlayer[0] = CPlayerM::Create(pDevice, m_nPnum, D3DXVECTOR3(0, 0, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_pPlayer[1] = CPlayerM::Create(pDevice, m_nEnum, D3DXVECTOR3(0, 0, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));


	m_pBall[0] = CBall::Create(pDevice, m_nPnum, m_startpos[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pBall[1] = CBall::Create(pDevice, m_nEnum, m_startpos[1], D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_cursol = CformX::Create(pDevice, "data/MODEL/cursol.x", D3DXVECTOR3(0.0f, 100.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));


	// hack load�ꏊ������
	m_pMap = CMap::Create(pDevice, m_pBall, m_pGoal, m_cursol, m_nPnum, m_nEnum);


	LoadGiimick(pDevice);

	m_pBall[0]->SetPos(m_startpos[0]);
	m_pBall[1]->SetPos(m_startpos[1]);




}
//
void CGame::ObjectInit(LPDIRECT3DDEVICE9 pDevice)
{
	// �t�@�C���ǂ݂��݂Ɍ�ɕύX
	m_pGoal = CGoal::Create(pDevice, 0, D3DXVECTOR3(0.0f, 600.0f,0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pGoal->SetMagnet(S);

	// �Ƃ肠�����}�b�N�X�͂�����
}
// �����蔻��
void CGame::ObjHitCheck()
{
	// �Ƃ肠�����S�[���Ƃ̓����蔻��̂�
	D3DXVECTOR3 ball = m_pBall[m_nPlayerNum]->GetPos();
	D3DXVECTOR3 obj = m_pGoal->GetPos();
	D3DXVECTOR3 size;
	D3DXVECTOR3 rot;
	m_nTurnCount;
	if (SphireHit(ball, 20.0f, obj, 10.0f))
	{
		m_pGoal->Sethit(1.0f);
		if (m_nSwitchCount == JUDGE_PHASE)
		{
			m_pBall[m_nPlayerNum]->SetGoalFlag(true);
		}
		if (m_bLilaBlow)
		{
			D3DXVECTOR3 vecball = m_pBall[m_nPlayerNum]->GetVelocity();
			m_pBall[0]->SetVelocity(-vecball);
		}
	}
	else
	{
		m_pGoal->Sethit(0.5f);
	}

	Magnet();
	if (m_bBlowFlag && m_pPlayer[m_nPlayerNum]->GetType() == 0)
	{
		return;
	}
	if (m_nTurnCount != 1)
	{
		D3DXVECTOR3 ball1 = m_pBall[0]->GetPos();
		D3DXVECTOR3 ball2 = m_pBall[1]->GetPos();
		if (SphireHit(ball1, 20.0f, ball2, 20.0f))
		{
			// ball1 -> ball2
			D3DXVECTOR3 vec = CheckVector(ball2, ball1);
			D3DXVECTOR3 vecball = m_pBall[m_nPlayerNum]->GetVelocity();
			if (m_nPlayerNum == 0)
			{
				m_pBall[1]->AddForce(vecball * 0.5f + vec);
				m_pBall[1]->SetMoveFlag(true);
				m_pBall[0]->SetVelocity(vecball * 0.5f - vec);
			}
			else
			{
				m_pBall[0]->AddForce(vecball * 0.5f - vec);
				m_pBall[0]->SetMoveFlag(true);
				m_pBall[1]->SetVelocity(vecball * 0.5f + vec);
			}
		}
	}
	bool stageflag = false;
	for (int i = 0; i < m_nStagenum && !stageflag; i++)
	{
		if (SphireHit(ball, 20.0f, m_nStageinfo[i].pos, m_nStageinfo[i].size))
		{
			stageflag = true;
		}
	}
	if (m_bStageflag[m_nPlayerNum])
	{
		m_bStageflagcount[m_nPlayerNum] ++;
		if (m_bStageflagcount[m_nPlayerNum] > 0)
		{
			m_bStageflag[m_nPlayerNum] = false;
			m_bStageflagcount[m_nPlayerNum] = 0;
		}
	}
	if (!stageflag && !m_bStageflag[m_nPlayerNum])
	{
		D3DXVECTOR3 vecball = m_pBall[m_nPlayerNum]->GetVelocity();
		m_pBall[m_nPlayerNum]->SetVelocity(-vecball);
		m_bStageflag[m_nPlayerNum] = true;
		m_bStageflagcount[m_nPlayerNum] = 0;
	}
	// �Ƃ肠�����M�~�b�N�Ƃ̓����蔻��
	for (int i = 0; i < m_nGimmickmax; i++)
	{
		obj = m_pGimmick_stage[i]->GetPos();
		size = m_pGimmick_stage[i]->GetSize();
		D3DXVECTOR3 vector = m_pBall[m_nPlayerNum]->GetVelocity();
		D3DXVECTOR3 rot = m_pGimmick_stage[i]->GetRot();
		switch (m_pGimmick_stage[i]->GetGimmickType())
		{
		case GIMMICK_CUBE:
			m_pBall[m_nPlayerNum]->AddForce(
				MagnetMove(N, ball,
				N,
				obj));
			break;
		case GIMMICK_CLOUD:
			if (ColOBBs(obj, size, rot, ball, 5.0f))
			{
				vector.y = vector.y*0.3f;
				vector.x = vector.x*0.3f;
				vector.z = vector.z*0.3f;
				m_pBall[m_nPlayerNum]->SetVelocity(vector);
			}
			break;
		case GIMMICK_CROW:
			if (ColOBBs(obj, size, rot, ball, 5.0f))
			{
				if (obj.y + size.y < ball.y || obj.y - size.y > ball.y)vector.y = -vector.y * 0.5f;
				if (obj.x + size.x < ball.x || obj.x - size.x > ball.x)vector.x = -vector.x * 0.5f;
				if (obj.z + size.z < ball.z || obj.z - size.z > ball.z)vector.z = -vector.z * 0.5f;
				m_pBall[m_nPlayerNum]->SetVelocity(vector);
			}
			break;
		case GIMMICK_UFO:
			break;
		case GIMMICK_WIND:
			if (ColOBBs(obj, size, rot, ball, 5.0f))
			{
				vector.x = 1.0f * rot.x;
				vector.y = 1.0f * rot.y;
				vector.z = 1.0f * rot.z;
				m_pBall[m_nPlayerNum]->AddForce(vector);
			}
			break;
		case GIMMICK_TORNADO:
			if (ColOBBs(obj, size, rot, ball, 5.0f))
			{
				vector.x = mersenne_twister_f32(-1.5f, 1.5f);
				vector.z = mersenne_twister_f32(-1.5f, 1.5f);
				vector.y = mersenne_twister_f32(0.0f, 2.0f);
				m_pBall[m_nPlayerNum]->AddForce(vector);
			}
			break;
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
void CGame::Magnet(void)
{
	D3DXVECTOR3 ballpos = m_pBall[m_nPlayerNum]->GetPos();
	NS ballns = m_pBall[m_nPlayerNum]->GetMagnet();
	if (m_bLilaBlow)
	{
		return;
	}
	m_pBall[m_nPlayerNum]->AddForce(
		MagnetMove(ballns, ballpos,
		m_pGoal->GetMagnet(),
		m_pGoal->GetPos()));

	if (m_bBlowFlag && m_pPlayer[m_nPlayerNum]->GetType() == 0)
	{
		return;
	}
	//if (m_nMoveCount < 100)
	{
		//�M�~�b�N���J�E���g
		for (int i = 0; i < m_nGimmickmax; i++)
		{
			//UFO�Ȃ��
			if (m_pGimmick_stage[i]->GetGimmickType() == GIMMICK_UFO)
			{
				m_pBall[m_nPlayerNum]->AddForce(
					MagnetMove(ballns, ballpos,
					m_pGimmick_stage[i]->GetMagnet(),
					m_pGimmick_stage[i]->GetPos()));
			}
		}
	}
}
void CGame::LoadGiimick(LPDIRECT3DDEVICE9 pDevice)
{

	int stage_id = CManager::GetSelectMap();
	char defDif[MAX_PATH] = { NULL };
	FILE *fp;
	fp = fopen(g_fieldname[stage_id], "rb");
	int loadnum;
	fscanf(fp, "%d\n", &loadnum);
	fseek(fp, 0, SEEK_SET);
	fseek(fp, sizeof(int), SEEK_SET);

	m_nStageinfo = new STAGE_INFO[loadnum];
	m_nStagenum = loadnum;
	m_pMap->SetMapFieldNum(loadnum);
	for (int n = 0; n < loadnum; n++)
	{
		int type = 0;
		float special = 0;
		D3DXVECTOR3 pos;
		D3DXVECTOR3 size;
		D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		fscanf(fp, "%f,%f,%f\n", &pos.x, &pos.y, &pos.z);
		fscanf(fp, "%f,%f,%f\n", &size.x, &size.y, &size.z);
		m_nStageinfo[n].pos = pos;
		m_nStageinfo[n].size = size.x;
		m_pMap->SetMapFieldPos(n,pos,size.x);
	}
	fclose(fp);
	fp = fopen("data/MAP/test.sto", "rb");
	fscanf(fp, "%d\n", &loadnum);
	fseek(fp, 0, SEEK_SET);
	fseek(fp, sizeof(int), SEEK_SET);
	m_pGimmick_stage = new CGimmick*[loadnum - 3];
	m_nGimmickmax = loadnum - 3;
	int numgimmick = 0;
	for (int n = 0; n < loadnum; n++)
	{
		char name[256];
		char fname[256];
		int type;
		float special;
		D3DXVECTOR3 pos;
		D3DXVECTOR3 size;
		D3DXVECTOR3 rot;
		D3DXVECTOR3 scale;
		fscanf(fp, "%s\n", &name);
		fscanf(fp, "%d\n", &type);
		fscanf(fp, "%f,%f,%f\n", &pos.x, &pos.y, &pos.z);
		fscanf(fp, "%f,%f,%f\n", &size.x, &size.y, &size.z);
		fscanf(fp, "%f,%f,%f\n", &rot.x, &rot.y, &rot.z);
		fscanf(fp, "%f\n", &scale.x);
		fscanf(fp, "%f\n", &special);
		sprintf(fname, "%s", strstr(name, "object"));
		scale.y = scale.z = scale.x;
		if (type < GIMMICK_MAX)
		{
			m_pGimmick_stage[numgimmick] = CGimmick::Create(pDevice, (GIMMICKTYPE)type, (MOVETYPE)((int)special), pos, size);
			if (type == GIMMICK_UFO)
			{
				m_pGimmick_stage[numgimmick]->SetMagnet(N);
			}

			numgimmick++;
		}
		else
		{
			if (type == GIMMICK_MAX)
			{ 
				m_startpos[0] = pos; 
			}
			else if (type =- GIMMICK_MAX + 1)
			{
				m_startpos[1] = pos; 
			}
			else
			{
				m_goalpos = pos;
			}

		}
	}
	fclose(fp);
}

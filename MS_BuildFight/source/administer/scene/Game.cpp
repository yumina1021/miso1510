//=============================================================================
//
// MS_BuildFight [CGame.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// マクロ定義
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

#define PLAYER_MAX	(2)	//プレイヤー数
#define SHOT_RIMIT	(0.05f)
#define PLAYER_DISTANCE	(100.0f)
#define EFFECT_MAX	(13)
//*****************************************************************************
// グローバル変数
//*****************************************************************************
//シーン
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
int g_movelimit;
int g_distancecount;
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
// コンストラクタ
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

	m_pGimmick[12] = {};
}
//=============================================================================
// デストラクタ
//=============================================================================
CGame :: ~CGame(void)
{
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CGame::Init(LPDIRECT3DDEVICE9 pDevice)
{
	m_bVsSelectFlag = CScene::GetVSFlag();
	m_bReplayFlag = CScene::GetReplayFlag();

	CCamera* pTmpCamera = CManager::GetCamera();
	pTmpCamera->Init();
	//地面の作成
	m_pMeshField = CMeshField::Create(pDevice, 6, D3DXVECTOR3(0, 0, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100, 100, 50, 50);

	//空の作成
	m_pDome = CDome::Create(pDevice, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//空の作成
	m_pDome2 = CDomeU::Create(pDevice, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//剣のエフェクト表示
	for (int i = 0; i < 20; i++)
	{
		m_pLocusEffect[i] = CLocusEffect::Create(pDevice, NULL, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	//インターフェース画面の作成
	InitUI(pDevice);

	//キャラクターの作成
	ModelInit(pDevice);

	//エフェクトの作成
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

	//シナリオ
	m_pScenario[0] = CScenario::Create(pDevice, (CScenario::Character)m_nPnum, false);
	m_pScenario[1] = CScenario::Create(pDevice, (CScenario::Character)m_nEnum, false);

	//Pause
	//背景の作成
	//m_pBackGround=CBackGround::Create(pDevice,BACKGROUND_GAME);

	//文字の配置
	m_pCharPicture[0]=CCharPicture::Create(pDevice,p_continue,D3DXVECTOR3(1100.0f,450.0f,0.0f),400,100);
	m_pCharPicture[1]=CCharPicture::Create(pDevice,p_retry,D3DXVECTOR3(1100.0f,550.0f,0.0f),400,100);
	m_pCharPicture[2]=CCharPicture::Create(pDevice,p_quit,D3DXVECTOR3(1100.0f,650.0f,0.0f),400,100);

	//フェードの作成
	m_pFade=CFade::Create(pDevice,1);

	//サウンド取得の作成
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

	//サウンド再生の作成
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

	// 受信スレッド開始
	m_pFade->StartFade(FADE_OUT,50,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),CManager::GetSelectChar(0));

	CManager::SetWin(PLAYER_DRAW);
	return S_OK;
}
//=============================================================================
// 初期化スレッド
//=============================================================================
unsigned __stdcall CGame :: InitSet( LPVOID Param )
{
	return 0;
}
//=============================================================================
// 終了
//=============================================================================
void CGame :: Uninit(void)
{
	//サウンド取得の作成
	CSound *pSound;
	pSound = CManager::GetSound();

	//サウンド再生の作成
	pSound->Stop();

	for (int i = 0; i < 2; i++)
	{
		m_pScenario[i]->Uninit();
		delete m_pScenario[i];
		m_pScenario[i] = NULL;
	}
	m_pGoal->Uninit();
	delete m_pGoal;
	m_pGoal = NULL;

	//m_pGimmick->Uninit();
	//delete m_pGimmick;
	//m_pGimmick = NULL;

	//シーンを全て終了
	Cform::ReleaseAll();
}
//=============================================================================
// 更新
//=============================================================================
void CGame :: Update(void)
{
	//キーボードインプットの受け取り
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	m_pGoal->Update();


	//更新本体
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

	//エスケープキーが押された場合／Ｐキーが押された時ポーズ画面へ
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

	//ポーズがONの場合
	if(CManager::GetpauseFlag())
	{
		//サウンド取得の作成
		CSound *pSound;
		pSound = CManager::GetSound();

		//エンターキーが押された場合
		if(pInputKeyboard->GetKeyTrigger(DIK_RETURN)||pInputKeyboard->GetKeyTrigger(DIK_Z))
		{
			//カーソルが合っているコマンドを発動
			switch(m_nCount)
			{
				//スタート
				case 0 :	m_bChangeFlag=false;
							CManager::SetpauseFlag(false);
							break;
				//コンフィグ
				case 1 :	m_bChangeFlag=true;
							//pSound->Play(SOUND_LABEL_SE_SELECT001);
							CManager::SetpauseFlag(false);
							m_pFade->StartFade(FADE_IN,100,D3DXCOLOR(1.0f,1.0f,1.0f,0.0f),CManager::GetSelectChar(0));
		
							break;
				//エンド
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
		//時間更新
		m_nTimerCount++;

		//タイマーに設定
		if(m_nTimerCount>60)
		{
			m_nTimerCount=0;
		}
	}

	//フェードインが終わったら
	if(m_pFade->GetFade()==FADE_IN_END)
	{
		if(m_bReplayFlag==false)
		{
			pInputKeyboard->Save();
		}

		m_pFade->StartFade(FADE_OUT,50,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),CManager::GetSelectChar(0));

		if(m_bVsSelectFlag==false)
		{
			//カーソルが合っているコマンドを発動
			switch(m_nCount)
			{
				case 0 :	CScene::SetTime(0);
							CScene::SetScore(m_nClearType*20000);
							CManager::SetgameEndFlag(false);
							CManager::Setnight0PlayFlag(true);
							CManager::SetAfterScene(PHASETYPE_RESULT);
							break;

				case 1 :	//次のフェーズを変える
							CSound *pSound;
							pSound = CManager::GetSound();
							//サウンド再生の作成
							//pSound->Stop(SOUND_LABEL_BGM001);
							Restart();
							m_bChangeFlag=false;
							break;
				//エンド
				case 2 :	//次のフェーズを変える
							CManager::SetAfterScene(PHASETYPE_TITLE);
							break;

				default : 	//次のフェーズを変える
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
// 描画
//=============================================================================
void CGame :: Draw(void)
{
	if (CManager::GetpauseFlag())
	{
		//m_pBackGround->Draw();

		//文字の配置
		for (int i = 0; i < 3; i++)
		{
			m_pCharPicture[i]->Draw();
		}
	}
	else
	{
		m_pDome->Draw();
		m_pDome2->Draw();

		//剣のエフェクト表示
		for (int i = 0; i < 20; i++)
		{
			m_pLocusEffect[i]->Draw();
		}


		if (m_bcursol)m_cursol->Draw();
		m_pGoal->Draw();
		for (int i = 0; i < m_GimmickMax; i++)
		{
			m_pGimmick[i]->Draw();
		}
		m_pBall[0]->Draw();
		m_pBall[1]->Draw();

		if ((m_nSwitchCount == POWER_PHASE) || (m_nSwitchCount == MOVE_PHASE) || (m_nSwitchCount == JUDGE_PHASE || (m_nSwitchCount == END_PHASE)))m_pPlayer[m_nPlayerNum]->Draw();

		for (int i = 0; i < EFFECT_MAX; i++)
		{
			m_pEffect[i]->Draw();
		}

		m_pCountDistance[0]->Draw();
		m_pCountDistance[1]->Draw();

		m_pScore->Draw();
		m_pScenario[m_nPlayerNum]->Draw();
	}

	//フェードの作成
	m_pFade->Draw();

}
//=============================================================================
// 再開
//=============================================================================
void CGame :: Restart(void)
{
	//キャラクターの作成
	m_pPlayer[0]->Restart(D3DXVECTOR3(0, 30, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pPlayer[1]->Restart(D3DXVECTOR3(0, 30, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//タイマー（時間）の作成
	m_nTimerCount=0;

	//サウンド取得の作成
	CSound *pSound;
	pSound = CManager::GetSound();

	m_bChangeFlag=false;
	m_nCount=0;

	m_fDiffuse=1.0f;

	m_nGameStartCount=0;
	CManager::SetgameEndFlag(true);

	//サウンド再生の作成
	//pSound->Play(SOUND_LABEL_BGM001);
}
void CGame::SetTimer(int time)
{
	//時間の変更
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//ターン開始
void CGame::TurnStart()
{
	//キーボードインプットの受け取り
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	WiiRemote *wiicon = CManager::GetWii(m_nPlayerNum);
	//プレイヤースタート表示
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

	//始まります
	if (m_nGameStartCount > 60)
	{
		if (pInputKeyboard->GetKeyTrigger(DIK_RETURN) || wiicon->GetKeyTrigger(WII_BUTTOM_A))
		{
			m_nGameStartCount = 0;
			m_pBall[m_nPlayerNum]->SetAlpha(0.3f);
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
//少しシナリオ
void CGame::GameScenario()
{
	//キーボードインプットの受け取り
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();
	WiiRemote *wiicon = CManager::GetWii(m_nPlayerNum);

	static CScenario::GameAffair affair;

	//プレイヤースタート表示
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

	//シナリオが終了したら
	if (m_pScenario[m_nPlayerNum]->GetScenarioEndFlag())
	{
		//エンター押して終了
		if (pInputKeyboard->GetKeyTrigger(DIK_RETURN) || wiicon->GetKeyTrigger(WII_BUTTOM_A))
		{
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
		//エンター押して次のシナリオ
		if (pInputKeyboard->GetKeyTrigger(DIK_RETURN) || wiicon->GetKeyTrigger(WII_BUTTOM_A))
		{
			m_pScenario[m_nPlayerNum]->GameScenario(m_nGameStartCount, affair);
			m_nGameStartCount++;
		}
	}
}
//角度決定開始
void CGame::AngleDecision()
{
	//キーボードインプットの受け取り
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

	//磁極切替
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
		m_shotrot.y += D3DX_PI * 0.01f;
		m_vecrot.y += D3DX_PI * 0.01f;
		m_shotrot.y = Rotation_Normalizer(m_shotrot.y);
		m_vecrot.y = Rotation_Normalizer(m_vecrot.y);
	}
	else if (pInputKeyboard->GetKeyPress(DIK_LEFT) || wiicon->GetKeyPress(WII_BUTTOM_LEFT))
	{
		m_shotrot.y -= D3DX_PI * 0.01f;
		m_vecrot.y -= D3DX_PI * 0.01f;
		m_shotrot.y = Rotation_Normalizer(m_shotrot.y);
		m_vecrot.y = Rotation_Normalizer(m_vecrot.y);
	}

	bool rotlimit_x_max = g_movelimit > -48;
	bool rotlimit_x_min = g_movelimit < 50;
	if (pInputKeyboard->GetKeyPress(DIK_UP) || wiicon->GetKeyPress(WII_BUTTOM_UP))
	{
		if (rotlimit_x_max)
		{
			g_movelimit--;
			m_shotrot.x -= D3DX_PI * 0.01f;
			m_vecrot.x -= D3DX_PI * 0.01f;
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
			g_movelimit++;
			m_shotrot.x += D3DX_PI * 0.01f;
			m_vecrot.x += D3DX_PI * 0.01f;
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
	// カーソルの表示
	m_cursol->SetPos(ball + m_PowerShot * m_bcursolmove);
	m_cursol->SetRotReal(D3DXVECTOR3(m_vecrot.x, m_vecrot.y + D3DX_PI / 4, 0.0f));
	m_pPlayer[m_nPlayerNum]->SetRot(D3DXVECTOR3(m_vecrot.x + D3DX_PI  * 0.005f * sinf(m_vecrot.x),
												m_vecrot.y + D3DX_PI  * 0.5f - D3DX_PI  * 0.225f * cosf(m_vecrot.x),
												D3DX_PI  * 0.25f * sinf(m_vecrot.x)));
	m_pPlayer[m_nPlayerNum]->SetPos(work_p);
	if (pInputKeyboard->GetKeyTrigger(DIK_RETURN) || wiicon->GetKeyTrigger(WII_BUTTOM_A))
	{
		m_pBall[m_nPlayerNum]->SetAlpha(1.0f);
		//ベクトルの関数呼ぶ場所
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
//打つ力の決定
void CGame:: PowerDecision()
{
	//キーボードインプットの受け取り
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();
	WiiRemote *wiicon = CManager::GetWii(m_nPlayerNum);
	D3DXVECTOR3 ball = m_pBall[m_nPlayerNum]->GetPos();
	//サウンド取得の作成
	CSound *pSound;
	pSound = CManager::GetSound();
	//弾のスピード調節
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

	//仮　打つ力を決めたから次
	if (pInputKeyboard->GetKeyTrigger(DIK_RETURN))
	{
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
	//仮　打つ力を決めたから次
	if (g_wiishot&&wiicon->GetWiiYaw() <-40.0f)
	{
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
//弾移動
void CGame::BallMove()
{
	D3DXVECTOR3 velocity = m_pBall[m_nPlayerNum]->GetVelocity();
	Magnet();
	ObjHitCheck();
	if (abs(velocity.x) < SHOT_RIMIT && abs(velocity.y) < SHOT_RIMIT && abs(velocity.z) < SHOT_RIMIT)
	{
		m_pBall[m_nPlayerNum]->SetVelocity(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		m_nSwitchCount = JUDGE_PHASE;
		m_pBall[m_nPlayerNum]->SetMoveFlag(false);
		D3DXVECTOR3 bpos = m_pBall[m_nPlayerNum]->GetPos();
		D3DXVECTOR3 gpos = m_pGoal->GetPos();
		m_fCupDistance[m_nPlayerNum] = abs(D3DXVec3Length(&(bpos - gpos))) / 10;
		m_pCountDistance[0]->ResetCount((int)m_fCupDistance[m_nPlayerNum]);
	}
}
//結果判定
void CGame::Judge()
{
	WiiRemote *wiicon = CManager::GetWii(m_nPlayerNum);
	ObjHitCheck();
	//もしゴールしたら終了
	if ((m_pBall[0]->GetGoalFlag() && m_pBall[1]->GetGoalFlag()) && !m_bJudge)
	{
		m_bJudge = true;
	}

	//終了判定  ターン数：時間経過：ゴール入った
	if ((m_nTurnCount>5) || (m_bJudge) && !(m_bChangeFlag))
	{
		m_pEffect[10]->SetView(true);
		CManager::SetgameEndFlag(true);

		m_nClearType = 2;

		//ＶＳモードなら
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
		m_pFade->StartFade(FADE_IN, 500, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f),CManager::GetSelectChar(0));
		m_nCount = 0;
		m_bChangeFlag = true;
	}

	m_pCountDistance[0]->ResetCount((int)m_fCupDistance[m_nPlayerNum]);

	//キーボードインプットの受け取り
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//仮　入らなかった交代
	if (pInputKeyboard->GetKeyTrigger(DIK_RETURN) || wiicon->GetKeyTrigger(WII_BUTTOM_A))
	{
		m_nSwitchCount = END_PHASE;
	}
}
void CGame::End()
{
	//キーボードインプットの受け取り
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();
	WiiRemote *wiicon = CManager::GetWii(m_nPlayerNum);

	//仮　入らなかった交代
	if (pInputKeyboard->GetKeyTrigger(DIK_RETURN) || wiicon->GetKeyTrigger(WII_BUTTOM_A))
	{
		m_pGoal->Sethit(0.0f);
		m_nSwitchCount = CHANGE_PHASE;
	}

}
//キャラ変更
void CGame::charachange()
{
	//プレイヤー切り換え
	m_nPlayerNum++;

	//プレイヤーが全部回った
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
	//5番ゲージ
	//スコアの作成
	float pos = 500;
	float length = 35.0f; 
	float scl = 6.0f;
	m_pScore = CScore::Create(pDevice, D3DXVECTOR3(1000.0f, 45.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 60, 110);		//体力
	m_pCountDistance[0] = CCount::Create(pDevice, D3DXVECTOR3(SCREEN_WIDTH / 2-60, SCREEN_HEIGHT - 100, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),0, 60, 110);
	m_pCountDistance[1] = CCount::Create(pDevice, D3DXVECTOR3(SCREEN_WIDTH / 4-60, 20, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),0, 35, 70);
	m_nTimerCount = 0;
	m_fCupDistance[0] = 0.0f;
	m_fCupDistance[1] = 0.0f;
}
//プレイヤーとボールのベクトルを算出
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

	m_pPlayer[0] = CPlayerM::Create(pDevice, m_nPnum , D3DXVECTOR3(0, 0, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_pPlayer[1] = CPlayerM::Create(pDevice, m_nEnum , D3DXVECTOR3(0, 0, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));


	m_pBall[0] = CBall::Create(pDevice, m_nPnum, D3DXVECTOR3(0.0f, 100.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pBall[1] = CBall::Create(pDevice, m_nEnum, D3DXVECTOR3(0.0f, 100.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_cursol = CformX::Create(pDevice, "data/MODEL/cursol.x", D3DXVECTOR3(0.0f, 100.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}
//
void CGame::ObjectInit(LPDIRECT3DDEVICE9 pDevice)
{
	// ファイル読みこみに後に変更
	m_pGoal = CGoal::Create(pDevice, 0, D3DXVECTOR3(0.0f, 600.0f,600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pGoal->SetMagnet(S);

	m_pGimmick[0] = CGimmick::Create(pDevice, GIMMICK_CUBE, MOVETYPE_STOP, D3DXVECTOR3(400.0f, 400.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pGimmick[0]->SetSize(D3DXVECTOR3(50.0f, 50.0f, 50.0f));
	m_pGimmick[1] = CGimmick::Create(pDevice, GIMMICK_TORNADO, MOVETYPE_STOP, D3DXVECTOR3(-400.0f, 100.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pGimmick[1]->SetSize(D3DXVECTOR3(50.0f, 50.0f, 50.0f));
	m_pGimmick[2] = CGimmick::Create(pDevice, GIMMICK_UFO, MOVETYPE_SLIDE, D3DXVECTOR3(0.0f, 0.0f, 400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pGimmick[2]->SetSize(D3DXVECTOR3(30.0f, 30.0f, 30.0f));
	m_pGimmick[2]->SetMagnet(N);
	// とりあえずマックスはここで
	m_GimmickMax = 3;
}
// 当たり判定
void CGame::ObjHitCheck()
{
	// とりあえずゴールとの当たり判定のみ
	D3DXVECTOR3 ball = m_pBall[m_nPlayerNum]->GetPos();
	D3DXVECTOR3 obj = m_pGoal->GetPos();
	D3DXVECTOR3 size;
	D3DXVECTOR3 rot;
	if (SphireHit(ball, 20.0f, obj, 10.0f))
	{
		m_pGoal->Sethit(1.0f);
		if (m_nSwitchCount == JUDGE_PHASE)
		{
			m_pBall[m_nPlayerNum]->SetGoalFlag(true);
		}
	}
	else
	{
		m_pGoal->Sethit(0.5f);
	}
	// とりあえずギミックとの当たり判定
	for (int i = 0; i < m_GimmickMax; i++)
	{
		obj = m_pGimmick[i]->GetPos();
		size = m_pGimmick[i]->GetSize();
		D3DXVECTOR3 vector = m_pBall[m_nPlayerNum]->GetVelocity();
		D3DXVECTOR3 rot = m_pGimmick[i]->GetRot();
		switch (m_pGimmick[i]->GetGimmickType())
		{
		case GIMMICK_CUBE:
			if (ColOBBs(obj, size, rot, ball, 5.0f))
			{
				if (obj.y + size.y < ball.y || obj.y - size.y > ball.y)
				{
					vector.y = -vector.y;
				}
				if (obj.x + size.x < ball.x || obj.x - size.x > ball.x)
				{
					vector.x = -vector.x;
				}
				if (obj.z + size.z < ball.z || obj.z - size.z > ball.z)
				{
					vector.z = -vector.z;
				}
				m_pBall[m_nPlayerNum]->SetVelocity(vector);
			}
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
// OBB vs 球
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

	D3DXVECTOR3 Vec(0, 0, 0);   // 最終的に長さを求めるベクトル
	float length;
	// 各軸についてはみ出た部分のベクトルを算出
	for (int i = 0; i<3; i++)
	{
		FLOAT L = obb.GetLen_W(i);
		if (L <= 0) continue;  // L=0は計算できない
		FLOAT s = D3DXVec3Dot(&(sphire_pos - obb.GetPos_W()), &obb.GetDirect(i)) / L;

		// sの値から、はみ出した部分があればそのベクトルを加算
		s = fabs(s);
		if (s > 1)	Vec += (1 - s)*L*obb.GetDirect(i);   // はみ出した部分のベクトル算出
	}
	length = D3DXVec3Length(&Vec);   // 長さを出力
	return length < sphire_length;
}
void CGame::Magnet(void)
{
	D3DXVECTOR3 ballpos = m_pBall[m_nPlayerNum]->GetPos();
	NS ballns = m_pBall[m_nPlayerNum]->GetMagnet();

	m_pBall[m_nPlayerNum]->AddForce(
		MagnetMove(ballns, ballpos,
		m_pGoal->GetMagnet(),
		m_pGoal->GetPos()));

	//if (m_nMoveCount < 100)
	{
		//ギミック数カウント
		for (int i = 0; i < m_GimmickMax; i++)
		{
			//UFOならば
			if (m_pGimmick[i]->GetGimmickType() == GIMMICK_UFO)
			{
				m_pBall[m_nPlayerNum]->AddForce(
					MagnetMove(ballns, ballpos,
					m_pGimmick[i]->GetMagnet(),
					m_pGimmick[i]->GetPos()));
			}
		}
	}
}
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
#include "../../module/ui/BackGround.h"
#include "../../module/ui/CharPicture.h"

#include "../../module/robot/PlayerM.h"
#include "../../module/robot/EnemyM.h"
#include "../../module/robot/PlayerGun1.h"

#include "../../module/etc/Fade.h"
#include "../../module/etc/Ball.h"
#include "../../module/etc/LocusEffect.h"

#include "../Debugproc.h"
#include "../../exten_common.h"

#define PLAYER_MAX	(2)	//プレイヤー数
#define SHOT_RIMIT	(0.001f)
#define PLAYER_DISTANCE	(100.0f)
//*****************************************************************************
// グローバル変数
//*****************************************************************************
//シーン
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
// コンストラクタ
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

	//地面の作成
	m_pMeshField = CMeshField::Create(pDevice, 6, D3DXVECTOR3(0, 0, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100, 100, 50, 50);

	//空の作成
	m_pDome = CDome::Create(pDevice, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//空の作成
	m_pDome2 = CDomeU::Create(pDevice, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//ゲージの作成
	m_pGauge = CGauge::Create(pDevice, D3DXVECTOR3(143.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);

	//敵ゲージの作成
	m_pGaugeEnemy = CGauge::Create(pDevice, D3DXVECTOR3(171.0f, 121.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), true);

	//剣のエフェクト表示
	for (int i = 0; i < 20; i++)
	{
		m_pLocusEffect[i] = CLocusEffect::Create(pDevice, NULL, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	//インターフェース画面の作成
	InitUI(pDevice);

	//キャラクターの作成
	m_nPnum = CScene::GetFrame();
	m_nEnum = CScene::GetEnemy();

	m_pPlayer[0] = CPlayerM::Create(pDevice, 0,D3DXVECTOR3(0, 100, 250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_pPlayer[0]->SetVsFlag(m_bVsSelectFlag);

	m_pPlayer[1] = CPlayerM::Create(pDevice, 0, D3DXVECTOR3(0, 100, -450.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_pPlayer[1]->SetVsFlag(m_bVsSelectFlag);
	//m_pEnemy = CEnemyM::Create(pDevice, m_nEnum, D3DXVECTOR3(0, 50, -200.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f), !m_bVsSelectFlag);

	m_pBall[0] = CBall::Create(pDevice, 0, D3DXVECTOR3(0.0f, 100.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pBall[1] = CBall::Create(pDevice, 0, D3DXVECTOR3(0.0f, 100.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//エフェクトの作成

	m_pEffect[m_nPnum] = CEffect::Create(pDevice, (EffectNum)m_nPnum, D3DXVECTOR3(650.0f, 375.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pEffect[(m_nEnum + 5)] = CEffect::Create(pDevice, (EffectNum)(m_nEnum + 5), D3DXVECTOR3(650.0f, 375.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_pEffect[10] = CEffect::Create(pDevice, effect000, D3DXVECTOR3(650.0f, 375.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pEffect[11] = CEffect::Create(pDevice, effect002, D3DXVECTOR3(650.0f, 375.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pEffect[12]=CEffect::Create(pDevice,Gtimeout,D3DXVECTOR3(650.0f,375.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f));

	m_pEffect[13]=CEffect::Create(pDevice,Gready,D3DXVECTOR3(650.0f,375.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f));
	m_pEffect[14]=CEffect::Create(pDevice,Gstart,D3DXVECTOR3(650.0f,375.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f));

	m_pEffect[15] = CEffect::Create(pDevice, effect003, D3DXVECTOR3(650.0f, 375.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//Pause
	//背景の作成
	m_pBackGround=CBackGround::Create(pDevice,BACKGROUND_GAME);

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
	//pSound->Play(SOUND_LABEL_BGM001);

	CManager::SetgameEndFlag(true);

	m_nGameStartCount=0;

	// 受信スレッド開始
	m_pFade->StartFade(FADE_OUT,50,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));

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

	//更新本体
	if (!m_bChangeFlag)
	{
		switch (m_nSwitchCount)
		{
		case START_PHASE:	TurnStart();
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
							m_pFade->StartFade(FADE_IN,100,D3DXCOLOR(1.0f,1.0f,1.0f,0.0f));
		
							break;
				//エンド
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
		//時間更新
		m_nTimerCount++;

		//タイマーに設定
		if(m_nTimerCount>60)
		{
			m_pTimer->AddTimer(-1);
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

		m_pFade->StartFade(FADE_OUT,50,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));

		if(m_bVsSelectFlag==false)
		{
			//カーソルが合っているコマンドを発動
			switch(m_nCount)
			{
				case 0 :	CScene::SetTime(m_pTimer->GetTimer()*100);
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
			CScene::SetTime(m_pTimer->GetTimer()*100);
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
		m_pBackGround->Draw();

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

		m_pGauge->Draw();
		m_pGaugeEnemy->Draw();

		//剣のエフェクト表示
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
	m_pEnemy->Restart(D3DXVECTOR3(0,30,-200.0f),D3DXVECTOR3(0.0f,3.14f,0.0f));

	//タイマー（時間）の作成
	m_nTimerCount=0;
	m_pTimer->ResetTimer(TIMER_MAX);

	//ゲージの作成
	m_pGauge->ResetGauge(SCORE_G_MAX);
	m_pGaugeEnemy->ResetGauge(SCORE_G_MAX);

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
	m_pTimer->ResetTimer(time);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//ターン開始
void CGame::TurnStart()
{
	//始まります
	if (m_nGameStartCount > 60)
	{
		if (m_nPlayerNum == 0)
		{
			m_nTurnCount++;
		}
		m_MovePow = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_pEffect[13]->SetViewFlag(true, 30);
		CManager::SetgameEndFlag(false);
		m_shotrot = D3DXVECTOR3(-2.4f, 0, 0);
		m_nSwitchCount = ANGLE_PHASE;
	}

	m_nGameStartCount++;
}
//角度決定開始
void CGame::AngleDecision()
{
	//キーボードインプットの受け取り
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	m_pEffect[10]->SetViewFlag(true, 1);

	D3DXVECTOR3 work = m_pPlayer[m_nPlayerNum]->GetPos();
	D3DXVECTOR3 ball = m_pBall[m_nPlayerNum]->GetPos();
	if (pInputKeyboard->GetKeyPress(DIK_RIGHT))
	{
		m_shotrot.y += D3DX_PI * 0.01f;
		m_shotrot.y = Rotation_Normalizer(m_shotrot.y);
	}
	else if (pInputKeyboard->GetKeyPress(DIK_LEFT))
	{
		m_shotrot.y -= D3DX_PI * 0.01f;
		m_shotrot.y = Rotation_Normalizer(m_shotrot.y);
	}

	bool rotlimit_x_max = m_shotrot.x - D3DX_PI / 4.0f < 3.14f;
	bool rotlimit_x_min = m_shotrot.x > 0.3f;
	if (pInputKeyboard->GetKeyPress(DIK_UP))
	{
		if (true)
		{
			m_shotrot.x -= D3DX_PI * 0.01f;
			m_shotrot.x = Rotation_Normalizer(m_shotrot.x);
		}
	}
	else if (pInputKeyboard->GetKeyPress(DIK_DOWN))
	{
		if (true)
		{
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
	//仮　スピード決めたから次
	if (pInputKeyboard->GetKeyTrigger(DIK_RETURN))
	{
		//ベクトルの関数呼ぶ場所
		m_PowerShot = CheckVector(ball, work);
		m_nSwitchCount = POWER_PHASE;
	}

}
//打つ力の決定
void CGame:: PowerDecision()
{
	//キーボードインプットの受け取り
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();
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
		m_nSwitchCount=MOVE_PHASE;
	}
}
//弾移動
void CGame::BallMove()
{
	//スピードによって球が移動
	D3DXVECTOR3 pos = m_pBall[m_nPlayerNum]->GetPos();
	// hack プレイヤーと弾の角度から発射向きを算出
	pos += m_MovePow.x*m_PowerShot;

	m_MovePow *= 0.5;

	m_pBall[m_nPlayerNum]->SetPos(pos);

	if (m_MovePow.x < SHOT_RIMIT && m_MovePow.y < SHOT_RIMIT && m_MovePow.z < SHOT_RIMIT)
	{
		m_pEffect[11]->SetViewFlag(true, 30);
		m_nSwitchCount = JUDGE_PHASE;
	}
}
//結果判定
void CGame::Judge()
{
	m_pEffect[12]->SetViewFlag(true, 1);

	//もしゴールしたら終了
	if ((m_pBall[0]->GetGoalFlag() || m_pBall[1]->GetGoalFlag()) && !m_bJudge)
	{
		m_bJudge = true;
	}

	//終了判定  ターン数：時間経過：ゴール入った
	if ((m_nTurnCount>5) || (m_pTimer->GetTimer() <= 0) || (m_bJudge) && !(m_bChangeFlag))
	{
		CManager::SetgameEndFlag(true);

		m_nClearType = 2;

		//ＶＳモードなら
		if (m_bVsSelectFlag == true)
		{
			CScene::SetVSFlag(false);
		}

		m_pFade->StartFade(FADE_IN, 500, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_nCount = 0;
		m_bChangeFlag = true;
	}

	//キーボードインプットの受け取り
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//仮　入らなかった交代
	if (pInputKeyboard->GetKeyTrigger(DIK_RETURN))
	{
		m_nSwitchCount = END_PHASE;
	}
}
void CGame::End()
{
	//キーボードインプットの受け取り
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//仮　入らなかった交代
	if (pInputKeyboard->GetKeyTrigger(DIK_RETURN))
	{
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

	m_pEffect[15]->SetViewFlag(true, 30);

	m_nSwitchCount = START_PHASE;
}
void CGame::InitUI(LPDIRECT3DDEVICE9 pDevice)
{

	m_nIFtype = rand() % 2;
	m_pUI = Cform2D::Create(pDevice, "data/TEXTURE/gage5.png", D3DXVECTOR3(650, 375, 0.0f), D3DXVECTOR3(0, 0, 0.0f),1300,750);
	//5番ゲージ
	//スコアの作成
	m_pScore = CScore::Create(pDevice, D3DXVECTOR3(430.0f, 565.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 35, 55);		//体力
	m_pCountBullet = CCount::Create(pDevice, D3DXVECTOR3(1040.0f, 265.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10);	//弾
	m_pCountOver = CCount::Create(pDevice, D3DXVECTOR3(1040.0f, 383.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 750);	//スキル
	m_pCountBoost = CCount::Create(pDevice, D3DXVECTOR3(835.0f, 565.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100);	//ブースト
	//タイマー（時間）の作成
	m_pTimer = CTimer::Create(pDevice, D3DXVECTOR3(1035.0f, 35.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_nTimerCount = 0;
}
//プレイヤーとボールのベクトルを算出
D3DXVECTOR3 CGame::CheckVector(D3DXVECTOR3 ball, D3DXVECTOR3 player)
{
	D3DXVECTOR3 Vector;
	Vector = ball - player;
	D3DXVec3Normalize(&Vector, &Vector);

	return Vector;
}





/////////////EOF////////////
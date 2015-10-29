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
#include "../netClient.h"
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
#include "../../module/etc/LocusEffect.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
//シーン
CPlayerM *CGame::m_pPlayer = NULL;
CEnemyM *CGame::m_pEnemy = NULL;

int CGame::m_nGameStartCount = 0;
bool CGame::m_bReplayFlag =false;
bool CGame::m_bVsSelectFlag = false;


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
	m_nIFtype=rand()%2;

	m_pUI = Cform2D::Create(pDevice, "data/TEXTURE/gage5.png", D3DXVECTOR3(650, 375, 0.0f), D3DXVECTOR3(0, 0, 0.0f));
	//5番ゲージ
	//スコアの作成
	m_pScore=CScore::Create(pDevice,D3DXVECTOR3(430.0f,565.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),35,55);		//体力
	m_pCountBullet=CCount::Create(pDevice,D3DXVECTOR3(1040.0f,265.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),10);	//弾
	m_pCountOver=CCount::Create(pDevice,D3DXVECTOR3(1040.0f,383.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),750);	//スキル
	m_pCountBoost=CCount::Create(pDevice,D3DXVECTOR3(835.0f,565.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),100);	//ブースト
	//タイマー（時間）の作成
	m_pTimer=CTimer::Create(pDevice,D3DXVECTOR3(1035.0f,35.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f));

	m_nTimerCount=0;

	//キャラクターの作成
	m_nPnum = CScene::GetFrame();
	m_nEnum = CScene::GetEnemy();

	m_pPlayer = CPGunNight1::Create(pDevice, D3DXVECTOR3(0, 50, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);

	m_pPlayer->SetVsFlag(m_bVsSelectFlag);

	m_pEnemy = CEnemyM::Create(pDevice, m_nEnum, D3DXVECTOR3(0, 50, -200.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f), !m_bVsSelectFlag);

	//エフェクトの作成

	m_pEffect[m_nPnum] = CEffect::Create(pDevice, (EffectNum)m_nPnum, D3DXVECTOR3(650.0f, 375.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pEffect[(m_nEnum + 5)] = CEffect::Create(pDevice, (EffectNum)(m_nEnum + 5), D3DXVECTOR3(650.0f, 375.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_pEffect[10] = CEffect::Create(pDevice, effect000, D3DXVECTOR3(650.0f, 375.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pEffect[11] = CEffect::Create(pDevice, effect002, D3DXVECTOR3(650.0f, 375.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pEffect[12]=CEffect::Create(pDevice,Gtimeout,D3DXVECTOR3(650.0f,375.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f));

	m_pEffect[13]=CEffect::Create(pDevice,Gready,D3DXVECTOR3(650.0f,375.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f));
	m_pEffect[14]=CEffect::Create(pDevice,Gstart,D3DXVECTOR3(650.0f,375.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f));

	m_pEffect[15] = CEffect::Create(pDevice, GReplay, D3DXVECTOR3(650.0f, 375.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

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

	m_bJudge = true;

	m_nSwitchCount = 0;

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

	//エスケープキーが押された場合／Ｐキーが押された時ポーズ画面へ
	if((pInputKeyboard->GetKeyTrigger(DIK_P)||pInputKeyboard->GetKeyTrigger(DIK_ESCAPE))&&!m_bChangeFlag&&!m_bReplayFlag)
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
			if(pInputKeyboard->GetKeyTrigger(DIK_W)||pInputKeyboard->GetKeyTrigger(DIK_UP))
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

			DATA data;
			data.ID = DATA_TYPE_TIME;

			data.Time.Time = m_pTimer->GetTimer();

			CNetClient::SendData( data );
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

		m_pPlayer->Draw();
		//m_pEnemy->Draw();

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
	m_pPlayer->Restart(D3DXVECTOR3(0,30,200.0f),D3DXVECTOR3(0.0f,0.0f,0.0f));
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
	if (m_nGameStartCount <= 180)
	{
		if (m_nGameStartCount == 60)
		{
			m_pEffect[13]->SetViewFlag(true, 120);
		}
		if (m_nGameStartCount == 180)
		{
			m_pEffect[14]->SetViewFlag(true, 10);
			CManager::SetgameEndFlag(false);
			m_nSwitchCount++;
		}
		m_nGameStartCount++;
	}
}
//球打ち開始
void CGame::ShotStart()
{
	//キーボードインプットの受け取り
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	m_pEffect[10]->SetViewFlag(true, 120);
	if (pInputKeyboard->GetKeyTrigger(DIK_RETURN))
	{
		m_nSwitchCount++;
	}
}
//弾移動
void CGame::BallMove()
{
	//キーボードインプットの受け取り
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	m_pEffect[11]->SetViewFlag(true, 120);

	if (pInputKeyboard->GetKeyTrigger(DIK_RETURN))
	{
		m_nSwitchCount++;
	}
}
//結果判定
void CGame::Judge()
{
	//終了判定
	if ((m_pTimer->GetTimer() <= 0)||(m_bJudge) && !(m_bChangeFlag))
	{
		CManager::SetgameEndFlag(true);

		m_pEffect[12]->SetViewFlag(true, 33);
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

}
//キャラ変更
void CGame::charachange()	
{
	//キーボードインプットの受け取り
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	m_pEffect[11]->SetViewFlag(true, 120);

	if (pInputKeyboard->GetKeyTrigger(DIK_RETURN))
	{
		m_nSwitchCount=0;
	}
}
/////////////EOF////////////
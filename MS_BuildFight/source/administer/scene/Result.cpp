//=============================================================================
//
// MS_BuildFight [CResult.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#include <stdio.h>

#include "Result.h"

#include "../Input.h"
#include "../Maneger.h"
#include "../Sound.h"
#include "../../module/etc/Camera.h"

#include "../../module/etc/Fade.h"
#include "../../module/ui/ResultScore.h"
#include "../../module/field/Dome.h"


#include "../../form/formX.h"
#include "../../form/form3D.h"
#include "../../form/form2D.h"

#include "../../module/etc/Ball.h"

#include "../../module/ui/Scenario.h"

#include "../../exten_common.h"
#include "../Texture.h"
//*****************************************************************************
// 定数
//*****************************************************************************
#define SCORE_X	(1000)
#define SCORE_Y	(100)

const float CAMERA_POS_X(0.0f);
const float CAMERA_POS_Y(0.0f);
const float CAMERA_POS_Z(-3500.0f);

//*****************************************************************************
// 静的変数
//*****************************************************************************
const int CResult::m_apTextureName[] =
{
	TEXTURE_RED,
	TEXTURE_BLUE,
	TEXTURE_STAR,
	TEXTURE_ARROW

};

//ご褒美CG用
const int g_RewardTexture[][2] =
{
	{TEXTURE_R_LILA_WIN,				//リーラ
	 TEXTURE_R_LILA_LOSE },

	{TEXTURE_R_ROSA_WIN,			//ローザ
	 TEXTURE_R_ROSA_LOSE },

	{TEXTURE_R_LICHT_WIN,			//リヒト
	 TEXTURE_R_LICHT_LOSE },

	{TEXTURE_R_JIJI_WIN,			//じいちゃん
	 TEXTURE_R_JIJI_LOSE },
};

//立ち絵表示用
const int g_StandTexture[][4] =
{
	{ TEXTURE_C_LILA_WARA,
	  TEXTURE_C_LILA_NAKI,
	  TEXTURE_C_LILA_NORMAL,
	  TEXTURE_C_LILA_DO },
	  
	{ TEXTURE_C_ROSA_WARA,
	  TEXTURE_C_ROSA_NAKI,
	  TEXTURE_C_ROSA_NORMAL,
	  TEXTURE_C_ROSA_DO },

	{ TEXTURE_C_NAVI_WARA,
	  TEXTURE_C_NAVI_NAKI,
	  TEXTURE_C_NAVI_NORMAL,
	  TEXTURE_C_NAVI_DO },

	{ TEXTURE_C_LICHT_WARA,
	  TEXTURE_C_LICHT_NAKI,
	  TEXTURE_C_LICHT_NORMAL,
	  TEXTURE_C_LICHT_DO },
};

LPDIRECT3DDEVICE9 CResult::m_pD3DDevice = NULL;		// デバイスのポインタ


//=============================================================================
// コンストラクタ
//=============================================================================
CResult :: CResult(void)
{
	for (int i = 0; i < 8; i++){m_pform3D[i] = NULL;}
	for (int i = 0; i < 2; i++){ m_pform2D[i] = NULL; }
	for (int i = 0; i < CRACKER_MAX; i++) { m_pPaperCracker[i] = NULL; } 
	for (int i = 0; i < BLIZZARD_MAX; i++){ m_pPaperBlizzard[i] = NULL; }

	m_pBackGround		= NULL;
	m_pFade				= NULL;
	m_pBall				= NULL;
	m_pScenerio[0]		= NULL;
	m_pScenerio[1]		= NULL;
	m_pManager			= NULL;
	m_pSound			= NULL;

	m_cnt				= 0;
	m_ButtonCounter		= 0;
	m_Timer				= 0;
	m_MaxSpeed			= 50;
	m_pRescore[3]		= { };
	m_ResultType		= LOSE_TYPE;

	m_CrackerFlag		= 
	m_BlizzardFlag		= 
	m_AfterRewardFlag	= false;

	m_Speed				= 1.0f;
	m_SlideSpeed		= 30.0f;
	m_LauncherSpeed[0] = 10.0f;
	m_LauncherSpeed[1] = 10.0f;
	m_Alpha[0]			= 0.0f;
	m_Alpha[1]			= 0.0f;

}
//=============================================================================
// デストラクタ
//=============================================================================
CResult :: ~CResult(void)
{
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CResult :: Init(LPDIRECT3DDEVICE9 pDevice)
{
	// カメラの取得
	CCamera* pTmpCamera = CManager::GetCamera();
	pTmpCamera->Init();
	pTmpCamera->SetPosP(D3DXVECTOR3(CAMERA_POS_X, CAMERA_POS_Y, CAMERA_POS_Z));

	m_pD3DDevice = m_pManager->GetDevice();

	//サウンド取得の作成
	m_pSound = CManager::GetSound();

	//最初に表示する勝敗のやつ
	//1Pが負けたかどうかで勝敗が決定される
	switch (m_pManager->GetWin())
	{
		case PLAYER1_WIN:
			Win();
			break;
		case PLAYER2_WIN:
			Lose();
			break;
		case PLAYER_DRAW:
			TieGame();
			break;
	}

	//背景の作成
	//m_pBackGround=CBackGround::Create(pDevice,BACKGROUND_RESULT);



	//シナリオ
	m_pScenerio[0] = CScenario::Create(pDevice, (CScenario::Character)m_pManager->GetSelectChar(0), false);
	m_pScenerio[1] = CScenario::Create(pDevice, (CScenario::Character)m_pManager->GetSelectChar(1), false);




	//サウンド再生の作成
	m_pSound->Play(SOUND_LABEL_BGM003);

	int time=CScene::GetTime();
	int score=CScene::GetScore();

	FILE *pFile;

	int scoreone=time+score;
	int rankone=0;
	int ranktwo=0;
	int rankthree=0;

	//ランクファイルのオープン
	fopen_s(&pFile, "data/SAVE/rankfile.dat", "rb");
	{
		if(pFile)
		{
			fread(&rankone,sizeof(int),1,pFile);
			fread(&ranktwo,sizeof(int),1,pFile);
			fread(&rankthree,sizeof(int),1,pFile);

			fclose(pFile);
		}
	}

	//ランクファイルの中身とスコアを比較
	//スコアの方が少ない場合
	if(rankone>scoreone)
	{
		if(ranktwo>scoreone)
		{
			if(rankthree>scoreone)
			{
				rankthree=rankthree;
			}
			else
			{
				rankthree=scoreone;
			}
		}else
		{
			rankthree=ranktwo;
			ranktwo=scoreone;
		}
	}
	else
	//スコアの方が多い場合
	if(rankone<scoreone)
	{
		rankthree=ranktwo;
		ranktwo=rankone;
		rankone=scoreone;
	}
	fopen_s(&pFile, "data/SAVE/rankfile.dat", "wb");
	if(pFile)
	{
		fwrite(&rankone,sizeof(int),1,pFile);
		fwrite(&ranktwo,sizeof(int),1,pFile);
		fwrite(&rankthree,sizeof(int),1,pFile);

		fclose(pFile);
	}

	//背景生成
	//m_pform3D[0] = Cform3D::Create(m_pD3DDevice, TEXTURE_S_7, D3DXVECTOR3(0.0f, 0.0f, 400.0f), D3DXVECTOR3(-D3DX_PI / 2.0f, -D3DX_PI / 2.0f, -D3DX_PI / 2.0f*3.0f), 3250, 5900);
	m_pform3D[0] = Cform3D::Create(m_pD3DDevice, TEXTURE_BACKGTROUND, D3DXVECTOR3(SCREEN_WIDTH / 2 - 630, SCREEN_HEIGHT / 2 - 350, 100.0f), D3DXVECTOR3(-D3DX_PI / 2.0f, -D3DX_PI / 2.0f, -D3DX_PI / 2.0f*3.0f), 5500, 3000);

	m_pform2D[0] = Cform2D::Create(m_pManager->GetDevice(), g_RewardTexture[m_pManager->GetSelectChar(0)][0], D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT);
	m_pform2D[1] = Cform2D::Create(m_pManager->GetDevice(), g_RewardTexture[m_pManager->GetSelectChar(1)][1], D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT);
	m_pform2D[0]->SetDiffuse(255.0f, 255.0f, 255.0f, m_Alpha[0]);
	m_pform2D[1]->SetDiffuse(255.0f, 255.0f, 255.0f, m_Alpha[1]);

	//スコア表示
	m_pRescore[0] = CReScore::Create(pDevice, scoreone, D3DXVECTOR3(SCORE_X, SCORE_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pRescore[1] = CReScore::Create(pDevice, rankone, D3DXVECTOR3(SCORE_X, SCORE_Y+150.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pRescore[2] = CReScore::Create(pDevice, ranktwo, D3DXVECTOR3(SCORE_X, SCORE_Y + (150.0f*2), 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pRescore[3] = CReScore::Create(pDevice, rankthree, D3DXVECTOR3(SCORE_X, SCORE_Y + (150.0f * 3), 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//フェードの作成
	m_pFade=CFade::Create(pDevice,1);

	m_pFade->StartFade(FADE_OUT,50,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),CManager::GetSelectChar(0));



	return S_OK;
}
//=============================================================================
// 終了
//=============================================================================
void CResult :: Uninit(void)
{
	//サウンド取得の作成
	CSound *pSound;
	pSound = CManager::GetSound();


	for (int i = 0; i < 2; i++)
	{
		m_pScenerio[i]->Uninit();
		delete m_pScenerio[i];
		m_pScenerio[i] = NULL;
	}

	//サウンド再生の作成
	pSound->Stop();

	//シーンを全て終了
	Cform::ReleaseAll();
}
//=============================================================================
// 更新
//=============================================================================
void CResult::Update(void)
{
	_UpdateTimer();				//効果音再生タイマーの更新
	_UpdateCracker();			//紙噴射の更新
	_UpdatePaperBlizzard();		//紙吹雪の更新
	_UpdateFlag();				//描画フラグの更新
	_UpdateFade();				//フェードの更新
	_UpdateWinningOrLosing();
	_UpdateLauncher();


}
//=============================================================================
// 描画
//=============================================================================
void CResult :: Draw(void)
{
	m_pD3DDevice = CManager::GetDevice();

	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//キャラと背景描画
	for (int i = 0; i < 8; i++)
	{
		if (m_pform3D[i]){ m_pform3D[i]->Draw(); }
	}


	//紙噴射描画
	if (m_CrackerFlag == true)
	{
		for (int i = 0; i < CRACKER_MAX; i++)
		{
			if (m_pPaperCracker[i])
			{
				m_pPaperCracker[i]->Draw();
			}
		}
	}

	//紙吹雪描画
	if (m_BlizzardFlag == true)
	{
		for (int i = 0; i < BLIZZARD_MAX; i++)
		{
			m_pPaperBlizzard[i]->Draw();

		}
	}


	//ご褒美CG用描画
	for (int i = 0; i < 2; i++)
	{
		if (m_pform2D[i]){ m_pform2D[i]->Draw(); }
	}

	//
	for (int i = 0; i < 2; i++)
	{
		if (m_pScenerio[i]){ m_pScenerio[i]->Draw(); }
	}


	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);			// 裏面をカリング


	//フェード
	m_pFade->Draw();
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<
//勝利時
//<<<<<<<<<<<<<<<<<<<<<<<<<<
void CResult::Win()
{
	PaperCracker(0.0f, 600.0f);
	PaperBlizzard(0.0f, 1700.0f);

	m_pform3D[1] = Cform3D::Create(m_pManager->GetDevice(), TEXTURE_WINER, D3DXVECTOR3(2400.0f, 1000.0f, 50.0f), D3DXVECTOR3(D3DX_PI / 2.0f*3.0f, 0.0f, 0.0f), 1600, 600);							//Win表示
	m_pform3D[2] = Cform3D::Create(m_pManager->GetDevice(), TEXTURE_LOSER, D3DXVECTOR3(-2600.0f, 1000.0f, 50.0f), D3DXVECTOR3(D3DX_PI / 2.0f*3.0f, 0.0f, 0.0f), 1600, 600);							//Lose表示
	//m_pform3D[3] = Cform3D::Create(m_pManager->GetDevice(), "data/TEXTURE/Light.png", D3DXVECTOR3(1300.0f, 0.0f, 0.0f),	 D3DXVECTOR3(0.0f, D3DX_PI / 2.0f*3.0f, -D3DX_PI / 2.0f*3.0f), 3000, 800);			//スポットライト表示
	m_pform3D[4] = Cform3D::Create(m_pManager->GetDevice(), g_StandTexture[m_pManager->GetSelectChar(0)][0], D3DXVECTOR3(1400.0f, -500.0f, 0.0f),  D3DXVECTOR3(D3DX_PI /2.0f*3.0f, 0.0f, 0.0f), 2280, 2007);	//敗者表示
	m_pform3D[5] = Cform3D::Create(m_pManager->GetDevice(), g_StandTexture[m_pManager->GetSelectChar(1)][1], D3DXVECTOR3(-1400.0f, -500.0f, 0.0f), D3DXVECTOR3(D3DX_PI /2.0f*3.0f, 0.0f, 0.0f), 2280, 2007);	//勝者表示
	m_pform3D[6] = Cform3D::Create(m_pManager->GetDevice(), TEXTURE_CRACKER, D3DXVECTOR3(2500.0f, -1500.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 2.0f*3.0f, 0.0f, 0.0f), 750, 750);							//クラッカー表示
	m_pform3D[7] = Cform3D::Create(m_pManager->GetDevice(), TEXTURE_CRACKER, D3DXVECTOR3(-700.0f, -1500.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 2.0f*3.0f, D3DX_PI*3.0f, 0.0f), 750, 750);					//クラッカー表示


	m_ResultType = MAX_TYPE;
	m_CrackerFlag = false;
	m_BlizzardFlag = false;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<
//負け
//<<<<<<<<<<<<<<<<<<<<<<<<<<
void CResult::Lose()
{
	PaperCracker(-1000.0f, -700.0f);
	PaperBlizzard(-1700.0f, 0.0f);
	m_pform3D[1] = Cform3D::Create(m_pManager->GetDevice(), TEXTURE_LOSER, D3DXVECTOR3(2400.0f, 1000.0f, 50.0f), D3DXVECTOR3(D3DX_PI / 2.0f*3.0f, 0.0f, 0.0f), 1600, 600);								//Lose表示
	m_pform3D[2] = Cform3D::Create(m_pManager->GetDevice(), TEXTURE_WINER, D3DXVECTOR3(-2500.0f, 1000.0f, 50.0f), D3DXVECTOR3(D3DX_PI / 2.0f*3.0f, 0.0f, 0.0f), 1600, 600);								//Win表示
	//m_pform3D[3] = Cform3D::Create(m_pManager->GetDevice(), "data/TEXTURE/Light.png", D3DXVECTOR3(-1300.0f, 0.0f, 0.0f),	 D3DXVECTOR3(0.0f, D3DX_PI / 2.0f*3.0f, -D3DX_PI / 2.0f*3.0f), 3000, 800);				//スポットライト表示
	m_pform3D[4] = Cform3D::Create(m_pManager->GetDevice(), g_StandTexture[m_pManager->GetSelectChar(0)][1], D3DXVECTOR3(1400.0f, -500.0f, 0.0f),  D3DXVECTOR3(D3DX_PI / 2.0f*3.0f, 0.0f, 0.0f), 2280, 2007);		//勝者表示
	m_pform3D[5] = Cform3D::Create(m_pManager->GetDevice(), g_StandTexture[m_pManager->GetSelectChar(1)][0], D3DXVECTOR3(-1400.0f, -500.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 2.0f*3.0f, 0.0f, 0.0f), 2280, 2007);		//敗者表示
	m_pform3D[6] = Cform3D::Create(m_pManager->GetDevice(), TEXTURE_CRACKER, D3DXVECTOR3(0.0f, -1500.0f, 0.0f),     D3DXVECTOR3(D3DX_PI / 2.0f*3.0f, 0.0f, 0.0f), 750, 750);								//クラッカー表示
	m_pform3D[7] = Cform3D::Create(m_pManager->GetDevice(), TEXTURE_CRACKER, D3DXVECTOR3(-2400.0f, -1500.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 2.0f*3.0f, D3DX_PI*3.0f, 0.0f), 750, 750);						//クラッカー表示
	m_ResultType = MAX_TYPE;
	m_CrackerFlag = false;
	m_BlizzardFlag = false;
}
//<<<<<<<<<<<<<<<<<<<<<<<<<<
//引き分け
//<<<<<<<<<<<<<<<<<<<<<<<<<<
void CResult::TieGame()
{
	//PaperCracker(-200.0f, 200.0f);
	PaperBlizzard(-800.0f, 800.0f);
	m_pform3D[1] = Cform3D::Create(m_pManager->GetDevice(), TEXTURE_DRAW, D3DXVECTOR3(0.0f, 1000.0f, 50.0f), D3DXVECTOR3(D3DX_PI / 2.0f*3.0f, 0.0f, 0.0f), 1600, 600);															//ドロー表示
	m_pform3D[2] = Cform3D::Create(m_pManager->GetDevice(), g_StandTexture[m_pManager->GetSelectChar(0)][1], D3DXVECTOR3(1400.0f, -500.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 2.0f*3.0f, 0.0f, 0.0f), 2280, 2007);		//顔表示
	m_pform3D[3] = Cform3D::Create(m_pManager->GetDevice(), g_StandTexture[m_pManager->GetSelectChar(1)][1], D3DXVECTOR3(-1400.0f, -500.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 2.0f*3.0f, 0.0f, 0.0f), 2280, 2007);	//顔表示2
	m_ResultType = MAX_TYPE;
	m_CrackerFlag = false;
	m_BlizzardFlag = false;
}
//<<<<<<<<<<<<<<<<<<<<<<<<<<
//紙噴射の生成
//<<<<<<<<<<<<<<<<<<<<<<<<<<
void CResult::PaperCracker(float min, float max)
{
	for (int i = 0; i < CRACKER_MAX; i++)
	{
		if (i < CRACKER_MAX / 2)
		{
			//左側
			m_pPaperCracker[i] = Cform3D::Create(m_pManager->GetDevice(), m_apTextureName[mersenne_twister_u16(0, 3)], D3DXVECTOR3(mersenne_twister_u16(min, min + 1500.0f), mersenne_twister_u16(-600, 50), mersenne_twister_f32(-300.0f, -250.0f)), D3DXVECTOR3(-D3DX_PI / 2.0f, 0.0f, 0.0f), 200.0f, 200.0f);
			m_CrackerVector[i] = D3DXVECTOR3(mersenne_twister_f32(1.0f, 4.0f), -2.0f,0.0f);
		}
		else
		{
			//右側
			m_pPaperCracker[i] = Cform3D::Create(m_pManager->GetDevice(), m_apTextureName[mersenne_twister_u16(0, 3)], D3DXVECTOR3(mersenne_twister_u16(max - 1500.0f, max), mersenne_twister_u16(-600, 50), mersenne_twister_f32(-300.0f, -250.0f)), D3DXVECTOR3(-D3DX_PI / 2.0f, 0.0f, 0.0f), 200.0f, 200.0f);
			m_CrackerVector[i] = D3DXVECTOR3(mersenne_twister_f32(-3.0f, -1.0f), -2.0f,0.0f);
		}
		D3DXVec3Normalize(&m_CrackerVector[i], &m_CrackerVector[i]);
	}
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<
//紙吹雪生成
//<<<<<<<<<<<<<<<<<<<<<<<<<<
void CResult::PaperBlizzard(float min, float max)
{
	for (int i = 0; i < BLIZZARD_MAX; i++)
	{
		m_pPaperBlizzard[i] = Cform3D::Create(m_pManager->GetDevice(), m_apTextureName[mersenne_twister_u16(0, 3)], D3DXVECTOR3(mersenne_twister_u16(min, max), mersenne_twister_u16(1500, 1900), mersenne_twister_f32(250.0f, 300.0f)), D3DXVECTOR3(-D3DX_PI / 2.0f, 0.0f, 0.0f), 150.0f, 150.0f);
		m_BlizzardVector[i] = D3DXVECTOR3(mersenne_twister_f32(-1.0f, 1.0f), 1.0f,0.0f);
		D3DXVec3Normalize(&m_BlizzardVector[i], &m_BlizzardVector[i]);

	}
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<
//紙噴射の更新
//<<<<<<<<<<<<<<<<<<<<<<<<<<
void CResult::_UpdateCracker(void)
{
	float G = 0.001f;		//重力
	float Power = 8.0f;		//上がる力
	D3DXVECTOR3 Speed = D3DXVECTOR3(0.0f, 0.0f,0.0f);
	D3DXVECTOR3 Pos = D3DXVECTOR3(0.0f, 0.0f,0.0f);
	D3DXVECTOR3 Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < CRACKER_MAX; i++)
	{
		Pos.z += m_CrackerVector[i].z*10.0f;
	}
	if (m_CrackerFlag == true)
	{
		//紙噴射関係の挙動
		for (int i = 0; i < CRACKER_MAX; i++)
		{
			if (m_pPaperCracker[i])
			{
				Pos = m_pPaperCracker[i]->GetPos();
				Rot = m_pPaperCracker[i]->GetRot();
				Pos.y -= G;
				Pos.y -= m_CrackerVector[i].y * m_MaxSpeed;
				Rot.x += mersenne_twister_f32(0.01f, 0.13f);
				Rot.y -= mersenne_twister_f32(0.01f, 0.04f);
				Rot.z += mersenne_twister_f32(0.01f, 0.09f);


				if (m_MaxSpeed >= 0.0f)
				{
					Pos.x += m_CrackerVector[i].x * m_MaxSpeed;
				}
				else
				{
					Pos.x += m_CrackerVector[i].x*5.0f;
				}
				m_pPaperCracker[i]->SetPos(Pos.x, Pos.y, Pos.z);
				m_pPaperCracker[i]->SetRot(Rot.x, Rot.y, Rot.z);
			}
		}
		m_MaxSpeed -= 1.0f;
	}
}
//<<<<<<<<<<<<<<<<<<<<<<<<<<
//フェードの更新
//<<<<<<<<<<<<<<<<<<<<<<<<<<
void CResult::_UpdateFade(void)
{
	//キーボードインプットの受け取り
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();
	WiiRemote* Player1 = CManager::GetWii(0);		//1P


	if ((pInputKeyboard->GetKeyTrigger(DIK_RETURN) || pInputKeyboard->GetKeyTrigger(DIK_Z) || Player1->GetKeyTrigger(WII_BUTTOM_A)) && m_ButtonCounter == 0)
	{
		m_ButtonCounter += 1;
		//m_pSound->Play(SOUND_LABEL_SE_SENI);
		m_pSound->PlayVoice(0,VOICE_LABEL_SE_WIN);
		m_pScenerio[0]->SetScenarioEndFlag(false);
		m_pScenerio[0]->SetViewFlag(true,0);
		m_pScenerio[0]->ResultScenario(0);

	}
	else if ((pInputKeyboard->GetKeyTrigger(DIK_RETURN) || pInputKeyboard->GetKeyTrigger(DIK_Z) || Player1->GetKeyTrigger(WII_BUTTOM_A)) && m_ButtonCounter == 1)
	{
		m_ButtonCounter += 1;
		m_pScenerio[0]->SetViewFlag(false, 0);

		m_pScenerio[1]->SetScenarioEndFlag(false);
		m_pScenerio[1]->SetViewFlag(true, 0);
		m_pScenerio[1]->ResultScenario(0);

		//m_pSound->Play(SOUND_LABEL_SE_SENI);

	}
	else if ((pInputKeyboard->GetKeyTrigger(DIK_RETURN) || pInputKeyboard->GetKeyTrigger(DIK_Z) || Player1->GetKeyTrigger(WII_BUTTOM_A)) && m_ButtonCounter == 2)
	{
		m_ButtonCounter += 1;
		m_pScenerio[1]->SetViewFlag(false, 0);

		//m_pSound->Play(SOUND_LABEL_SE_SENI);

	}
	else if ((pInputKeyboard->GetKeyTrigger(DIK_RETURN) || pInputKeyboard->GetKeyTrigger(DIK_Z) || Player1->GetKeyTrigger(WII_BUTTOM_A)) && m_ButtonCounter == 3)
	{
		m_ButtonCounter += 1;
		m_AfterRewardFlag = true;
	}

	if (m_ButtonCounter == 1)
	{
		m_Alpha[0] += 0.03f;

		if (m_Alpha[0] > 255.0f)
		{
			m_Alpha[0] = 255.0f;
		}
		m_pform2D[0]->SetDiffuse(255.0f, 255.0f, 255.0f, m_Alpha[0]);
	}

	if (m_ButtonCounter == 2)
	{
		m_Alpha[1] += 0.03f;

		if (m_Alpha[1] > 255.0f)
		{
			m_Alpha[1] = 255.0f;
		}
		m_pform2D[1]->SetDiffuse(255.0f, 255.0f, 255.0f, m_Alpha[1]);


	}

	if (m_ButtonCounter == 3)
	{
		m_Alpha[0] -= 0.05f;
		m_Alpha[1] -= 0.01f;
		if (m_Alpha[0] < 0.0f)
		{
			m_Alpha[0] = 0.0f;
		}
		if (m_Alpha[1] < 0.0f)
		{
			m_Alpha[1] = 0.0f;
		}

		m_pform2D[0]->SetDiffuse(255.0f, 255.0f, 255.0f, m_Alpha[0]);
		m_pform2D[1]->SetDiffuse(255.0f, 255.0f, 255.0f, m_Alpha[1]);

	}

	//フェードの開始
	else if ((pInputKeyboard->GetKeyTrigger(DIK_RETURN) || pInputKeyboard->GetKeyTrigger(DIK_Z) || Player1->GetKeyTrigger(WII_BUTTOM_A)) && m_AfterRewardFlag == true && m_ButtonCounter==4)
	{
		CSound *pSound;
		pSound = CManager::GetSound();
		m_pFade->StartFade(FADE_IN, 100, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), CManager::GetSelectChar(0));
	}

	//フェードインが終わったら
	if (m_pFade->GetFade() == FADE_IN_END)
	{
		//次のフェーズを変える
		CManager::SetAfterScene(PHASETYPE_TITLE);

	}




}

//<<<<<<<<<<<<<<<<<<<<<<<<<<
//紙吹雪の更新
//<<<<<<<<<<<<<<<<<<<<<<<<<<
void CResult::_UpdatePaperBlizzard(void)
{
	D3DXVECTOR3 Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//紙吹雪関係の挙動
	for (int i = 0; i < BLIZZARD_MAX; i++)
	{
		Rot = m_pPaperBlizzard[i]->GetRot();
		Rot.x += mersenne_twister_f32(0.01f, 0.13f);
		Rot.y += mersenne_twister_f32(0.01f, 0.08f);
		Rot.z += mersenne_twister_f32(0.01f, 0.07f);

		float Length = m_pPaperBlizzard[i]->GetLength();
		D3DXVECTOR3 Pos = m_pPaperBlizzard[i]->GetPos();
		Pos -=10.0f*m_BlizzardVector[i] * mersenne_twister_f32(0.02f, 1.0f);
		m_pPaperBlizzard[i]->SetPos(D3DXVECTOR3(Pos.x, Pos.y, 0));		//座標設定
		m_pPaperBlizzard[i]->SetRot(Rot.x,Rot.y,Rot.z);					//角度設定

		Length += mersenne_twister_f32(-1.0f, 1.0f);
		if (Length > 15.0f){ Length = 15.0f; }
		else if (Length < 19.0f){ Length = 19.0f; }
		m_pPaperBlizzard[i]->SetLength(Length);
	}
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<
//紙吹雪の描画フラグの更新
//<<<<<<<<<<<<<<<<<<<<<<<<<<
void CResult::_UpdateFlag(void)
{
	m_cnt++;
	if (m_cnt >170)
	{

		m_BlizzardFlag = true;
		m_CrackerFlag = true;
		m_cnt = 0;

	}
}
//<<<<<<<<<<<<<<<<<<<<<<<<<<
//効果音再生タイミングの更新
//<<<<<<<<<<<<<<<<<<<<<<<<<<
void CResult::_UpdateTimer(void)
{
	m_Timer++;
	if (m_Timer == 150)
	{
		//m_pSound->Play(SOUND_LABEL_SE_TRUMPET);
	}

}

//<<<<<<<<<<<<<<<<<<<<<<<<<<
//Win,Lose画像の更新
//<<<<<<<<<<<<<<<<<<<<<<<<<<
void CResult::_UpdateWinningOrLosing(void)
{
	if (m_pform3D[1])
	{
		D3DXVECTOR3 Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		Pos = m_pform3D[1]->GetPos();
		Pos.y += m_Speed;
		Pos.x -= m_SlideSpeed;
		if (Pos.x < 1400)
		{
			m_SlideSpeed = 0.0f;
		}
		if (Pos.y > 1100 || Pos.y < 900)
		{
			m_Speed *= -1.0f;
		}
		m_pform3D[1]->SetPos(Pos.x, Pos.y, Pos.z);
	}

	if (m_pform3D[2])
	{
		D3DXVECTOR3 Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		Pos = m_pform3D[2]->GetPos();
		Pos.y += m_Speed;
		Pos.x += m_SlideSpeed;

		if (Pos.x > -1600)
		{
			m_SlideSpeed = 0.0f;
		}
		if (Pos.y > 1100 || Pos.y < 900)
		{
			m_Speed *= -1.0f;
		}

		m_pform3D[2]->SetPos(Pos.x, Pos.y, Pos.z);
	}

}

//<<<<<<<<<<<<<<<<<<<<<<<<<<
//クラッカー発射装置画像の更新
//<<<<<<<<<<<<<<<<<<<<<<<<<<
void CResult::_UpdateLauncher(void)
{
	switch (m_pManager->GetWin())
	{
		case PLAYER1_WIN:
			_UpdateWinLauncher();
			break;
		case PLAYER2_WIN:
			_UpdateLoseLauncher();
			break;
		case PLAYER_DRAW:
			_UpdateTieGameLauncher();
			break;
	}
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<
//クラッカー発射装置勝利時の更新
//<<<<<<<<<<<<<<<<<<<<<<<<<<
void CResult::_UpdateWinLauncher(void)
{
	if (m_pform3D[6])
	{
		D3DXVECTOR3 Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		Pos = m_pform3D[6]->GetPos();
		Pos.y += m_LauncherSpeed[0];
		Pos.x -= m_LauncherSpeed[0];
		if (Pos.x < 1800 && Pos.y > -800)
		{
			m_LauncherSpeed[0] = 0.0f;
		}

		if (m_CrackerFlag == true)
		{
			m_LauncherSpeed[0] = 10.0f;
			Pos.y -= m_LauncherSpeed[0];
			Pos.x += m_LauncherSpeed[0];
			if (Pos.x < 2500 && Pos.y > -2700)
			{
				m_LauncherSpeed[0] = 0.0f;
			}
		}
		m_pform3D[6]->SetPos(Pos.x, Pos.y, Pos.z);
	}

	if (m_pform3D[7])
	{
		D3DXVECTOR3 Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		Pos = m_pform3D[7]->GetPos();

		if (Pos.x > 0 && Pos.y > -800)
		{
			m_LauncherSpeed[1] = 0.0f;
		}
		if (m_CrackerFlag == true)
		{
			m_LauncherSpeed[1] = -10.0f;

			if (Pos.x < -2500 && Pos.y < -2700)
			{
				m_LauncherSpeed[1] = 0.0f;
			}
		}
		Pos.y += m_LauncherSpeed[1];
		Pos.x += m_LauncherSpeed[1];
		m_pform3D[7]->SetPos(Pos.x, Pos.y, Pos.z);
	}

}

//<<<<<<<<<<<<<<<<<<<<<<<<<<
//クラッカー発射装置敗北時の更新
//<<<<<<<<<<<<<<<<<<<<<<<<<<
void CResult::_UpdateLoseLauncher(void)
{
	if (m_pform3D[6])
	{
		D3DXVECTOR3 Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		Pos = m_pform3D[6]->GetPos();
		Pos.y += m_LauncherSpeed[0];
		Pos.x -= m_LauncherSpeed[0];
		if (Pos.x < 1200 && Pos.y > -800)
		{
			m_LauncherSpeed[0] = 0.0f;
		}

		if (m_CrackerFlag == true)
		{
			m_LauncherSpeed[0] = 10.0f;
			Pos.y -= m_LauncherSpeed[0];
			Pos.x += m_LauncherSpeed[0];
			if (Pos.x < 2700 && Pos.y > -2500)
			{
				m_LauncherSpeed[0] = 0.0f;
			}
		}
		m_pform3D[6]->SetPos(Pos.x, Pos.y, Pos.z);
	}

	if (m_pform3D[7])
	{
		D3DXVECTOR3 Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		Pos = m_pform3D[7]->GetPos();

		if (Pos.x > -2400 && Pos.y > -800)
		{
			m_LauncherSpeed[1] = 0.0f;
		}
		if (m_CrackerFlag == true)
		{
			m_LauncherSpeed[1] = -10.0f;

			if (Pos.x < -1500 && Pos.y < -2700)
			{
				m_LauncherSpeed[1] = 0.0f;
			}
		}
		Pos.y += m_LauncherSpeed[1];
		Pos.x += m_LauncherSpeed[1];
		m_pform3D[7]->SetPos(Pos.x, Pos.y, Pos.z);
	}

}

//<<<<<<<<<<<<<<<<<<<<<<<<<<
//クラッカー発射装置引き分け時の更新
//<<<<<<<<<<<<<<<<<<<<<<<<<<
void CResult::_UpdateTieGameLauncher(void)
{

}




/////////////EOF////////////
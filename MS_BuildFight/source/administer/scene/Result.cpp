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
#include "../../module/ui/BackGround.h"
#include "../../module/ui/ResultScore.h"


#include "../../form/formX.h"
#include "../../form/form3D.h"

#include "../../module/etc/Ball.h"

#include "../../module/ui/Scenario.h"

#include "../../exten_common.h"
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
const LPSTR CResult::m_apTextureName[] =
{
	"data/TEXTURE/Red.png",
	"data/TEXTURE/Blue.png",
	"data/TEXTURE/Star.png",
	"data/TEXTURE/Arrow.png"

};
const LPSTR g_StandTexture[][4] =
{
	{"data/TEXTURE/character/lila/do.png",
	 "data/TEXTURE/character/lila/naki.png",
	 "data/TEXTURE/character/lila/wara.png",
	 "data/TEXTURE/character/lila/do.png" },

	{"data/TEXTURE/character/lila/do.png",
	 "data/TEXTURE/character/lila/naki.png",
	 "data/TEXTURE/character/lila/wara.png",
	 "data/TEXTURE/character/lila/do.png" },

	{"data/TEXTURE/character/lila/do.png",
	 "data/TEXTURE/character/lila/naki.png",
	 "data/TEXTURE/character/lila/wara.png",
	 "data/TEXTURE/character/lila/do.png" },

	{"data/TEXTURE/character/lila/do.png",
	 "data/TEXTURE/character/lila/naki.png",
	 "data/TEXTURE/character/lila/wara.png",
	 "data/TEXTURE/character/lila/do.png" },
};

LPDIRECT3DDEVICE9 CResult::m_pD3DDevice = NULL;		// デバイスのポインタ


//=============================================================================
// コンストラクタ
//=============================================================================
CResult :: CResult(void)
{
	for (int i = 0; i < 6; i++){m_pform3D[i] = NULL;}
	for (int i = 0; i < CRACKER_MAX; i++) { m_pPaperCracker[i] = NULL; }
	for (int i = 0; i < BLIZZARD_MAX; i++){ m_pPaperBlizzard[i] = NULL; }

	m_pBackGround	= NULL;
	m_pFade			= NULL;
	m_pBall			= NULL;
	m_pScenerio		= NULL;
	m_pManager		= NULL;
	m_cnt			= 0;
	m_MaxSpeed		= 50;
	m_pRescore[3]	= { };
	m_ResultType	= LOSE_TYPE;
	m_CrackerFlag   = false;
	m_BlizzardFlag	= false;


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
	pTmpCamera->SetPosP(D3DXVECTOR3(CAMERA_POS_X, CAMERA_POS_Y, CAMERA_POS_Z));


	//最初に表示する勝敗のやつ
	//1Pが負けたかどうかで勝敗が決定される
	TieGame();

	D3DXVECTOR3 Camera = pTmpCamera->GetPosP();

	//背景の作成
	m_pBackGround=CBackGround::Create(pDevice,BACKGROUND_RESULT);



	//シナリオ
	//m_pScenerio = CScenario::Create(pDevice,true);

	//サウンド取得の作成
	CSound *pSound;
	pSound = CManager::GetSound();

	//サウンド再生の作成
	//pSound->Play(SOUND_LABEL_BGM002);

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
	m_pform3D[0] = Cform3D::Create(m_pManager->GetDevice(), "data/TEXTURE/sky004.jpg", D3DXVECTOR3(0.0f, 0.0f, 400.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2.0f*3.0f, -D3DX_PI / 2.0f*3.0f), 3250, 5900);

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

	//m_pScenerio->Uninit();
	//delete m_pScenerio;


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
	_UpdateCracker();			//紙噴射の更新
	_UpdatePaperBlizzard();		//紙吹雪の更新
	_UpdateFlag();				//描画フラグの更新
	_UpdateFade();				//フェードの更新

}
//=============================================================================
// 描画
//=============================================================================
void CResult :: Draw(void)
{
	m_pD3DDevice = CManager::GetDevice();

	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//キャラと背景描画
	for (int i = 0; i < 6; i++)
	{
		if (m_pform3D[i]){ m_pform3D[i]->Draw(); }
	}

	//紙噴射描画
	if (m_CrackerFlag == true)
	{
		for (int i = 0; i < CRACKER_MAX; i++)
		{
			m_pPaperCracker[i]->Draw();
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
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);			// 裏面をカリング


	//フェード
	m_pFade->Draw();
}
//勝利時
void CResult::Win()
{
	PaperCracker(0.0f, 400.0f);
	PaperBlizzard(0.0f, 1700.0f);
	m_pform3D[1] = Cform3D::Create(m_pManager->GetDevice(), "data/TEXTURE/Winer.png", D3DXVECTOR3(1400.0f, 1000.0f, 50.0f),  D3DXVECTOR3(0.0f, D3DX_PI / 2.0f*3.0f, -D3DX_PI / 2.0f*3.0f), 600, 1600);						//Win表示
	m_pform3D[2] = Cform3D::Create(m_pManager->GetDevice(), "data/TEXTURE/Loser.png", D3DXVECTOR3(-1600.0f, 1000.0f, 50.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2.0f*3.0f, -D3DX_PI / 2.0f*3.0f), 600, 1600);						//Lose表示
	m_pform3D[3] = Cform3D::Create(m_pManager->GetDevice(), "data/TEXTURE/Light.png", D3DXVECTOR3(-1300.0f, 0.0f, 0.0f),	 D3DXVECTOR3(0.0f, D3DX_PI / 2.0f*3.0f, -D3DX_PI / 2.0f*3.0f), 3000, 800);						//スポットライト表示
	m_pform3D[4] = Cform3D::Create(m_pManager->GetDevice(), g_StandTexture[m_pManager->GetSelectChar(0)][0], D3DXVECTOR3(1400.0f, -400.0f, 0.0f),  D3DXVECTOR3(0.0f, D3DX_PI / 2.0f*3.0f, -D3DX_PI / 2.0f*3.0f), 2280, 2307);	//敗者表示
	m_pform3D[5] = Cform3D::Create(m_pManager->GetDevice(), g_StandTexture[m_pManager->GetSelectChar(1)][1], D3DXVECTOR3(-1400.0f, -400.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2.0f*3.0f, -D3DX_PI / 2.0f*3.0f), 2280, 2307);	//勝者表示
	m_ResultType = MAX_TYPE;
	m_CrackerFlag = false;
	m_BlizzardFlag = false;
}
//敗北時
void CResult::Lose()
{
	PaperCracker(-400.0f, 0.0f);
	PaperBlizzard(-1700.0f, 0.0f);
	m_pform3D[1] = Cform3D::Create(m_pManager->GetDevice(), "data/TEXTURE/Loser.png", D3DXVECTOR3(1400.0f, 1000.0f, 50.0f),  D3DXVECTOR3(0.0f, D3DX_PI / 2.0f*3.0f, -D3DX_PI / 2.0f*3.0f), 600, 1600);								//Lose表示
	m_pform3D[2] = Cform3D::Create(m_pManager->GetDevice(), "data/TEXTURE/Winer.png", D3DXVECTOR3(-1800.0f, 1000.0f, 50.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2.0f*3.0f, -D3DX_PI / 2.0f*3.0f), 600, 1600);								//Win表示
	m_pform3D[3] = Cform3D::Create(m_pManager->GetDevice(), "data/TEXTURE/Light.png", D3DXVECTOR3(-1300.0f, 0.0f, 0.0f),	 D3DXVECTOR3(0.0f, D3DX_PI / 2.0f*3.0f, -D3DX_PI / 2.0f*3.0f), 3000, 800);								//スポットライト表示
	m_pform3D[4] = Cform3D::Create(m_pManager->GetDevice(), g_StandTexture[m_pManager->GetSelectChar(0)][2], D3DXVECTOR3(1400.0f,  -400.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2.0f*3.0f, -D3DX_PI / 2.0f*3.0f), 2280, 2307);			//勝者表示
	m_pform3D[5] = Cform3D::Create(m_pManager->GetDevice(), g_StandTexture[m_pManager->GetSelectChar(1)][1], D3DXVECTOR3(-1400.0f, -400.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2.0f*3.0f, -D3DX_PI / 2.0f*3.0f), 2280, 2307);			//敗者表示
	m_ResultType = MAX_TYPE;
	m_CrackerFlag = false;
	m_BlizzardFlag = false;
}
//引き分け	
void CResult::TieGame()
{
	PaperCracker(-200.0f, 200.0f);
	PaperBlizzard(-800.0f, 800.0f);
	m_pform3D[1] = Cform3D::Create(m_pManager->GetDevice(), "data/TEXTURE/Draw.png", D3DXVECTOR3(0.0f, 1000.0f, 50.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2.0f*3.0f, -D3DX_PI / 2.0f*3.0f), 600, 1600);															//ドロー表示
	m_pform3D[2] = Cform3D::Create(m_pManager->GetDevice(), g_StandTexture[m_pManager->GetSelectChar(0)][0], D3DXVECTOR3(1400.0f, -400.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2.0f*3.0f, -D3DX_PI / 2.0f*3.0f), 2280, 2307);		//顔表示
	m_pform3D[3] = Cform3D::Create(m_pManager->GetDevice(), g_StandTexture[m_pManager->GetSelectChar(1)][1], D3DXVECTOR3(-1400.0f, -400.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2.0f*3.0f, -D3DX_PI / 2.0f*3.0f), 2280, 2307);	//顔表示2
	m_ResultType = MAX_TYPE;
	m_CrackerFlag = false;
	m_BlizzardFlag = false;
}
//紙噴射
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

//紙吹雪
void CResult::PaperBlizzard(float min, float max)
{
	for (int i = 0; i < BLIZZARD_MAX; i++)
	{
		m_pPaperBlizzard[i] = Cform3D::Create(m_pManager->GetDevice(), m_apTextureName[mersenne_twister_u16(0, 3)], D3DXVECTOR3(mersenne_twister_u16(min, max), mersenne_twister_u16(1500, 1900), mersenne_twister_f32(-300.0f, -250.0f)), D3DXVECTOR3(-D3DX_PI / 2.0f, 0.0f, 0.0f), 150.0f, 150.0f);
		m_BlizzardVector[i] = D3DXVECTOR3(mersenne_twister_f32(-1.0f, 1.0f), 1.0f,0.0f);
		D3DXVec3Normalize(&m_BlizzardVector[i], &m_BlizzardVector[i]);
	}
}

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
		m_MaxSpeed -= 1.0f;
	}
}

void CResult::_UpdateFade(void)
{
	//キーボードインプットの受け取り
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();
	WiiRemote* Player1 = CManager::GetWii(0);		//1P


	//フェードの開始
	if (pInputKeyboard->GetKeyTrigger(DIK_RETURN) || pInputKeyboard->GetKeyTrigger(DIK_Z) || Player1->GetKeyTrigger(WII_BUTTOM_A))
	{
		CSound *pSound;
		pSound = CManager::GetSound();
		//pSound->Play(SOUND_LABEL_SE_SELECT001);
		m_pFade->StartFade(FADE_IN, 100, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f),CManager::GetSelectChar(0));
	}

	//フェードインが終わったら
	if (m_pFade->GetFade() == FADE_IN_END)
	{
		//次のフェーズを変える
		CManager::SetAfterScene(PHASETYPE_TITLE);
	}

}

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

void CResult::_UpdateFlag(void)
{
	m_cnt++;
	if (m_cnt > 100)
	{
		m_BlizzardFlag = true;
		m_CrackerFlag = true;
		m_cnt = 0;
	}
}

/////////////EOF////////////
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

#include "../../module/etc/Fade.h"
#include "../../module/ui/BackGround.h"
#include "../../module/ui/ResultScore.h"

#include "../../form/formX.h"

#include "../../module/etc/Ball.h"

#include "../../module/ui/Scenario.h"

#include "../../exten_common.h"
//*****************************************************************************
// 定数
//*****************************************************************************
#define SCORE_X	(1000)
#define SCORE_Y	(100)
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

//=============================================================================
// コンストラクタ
//=============================================================================
CResult :: CResult(void)
{
	for (int i = 0; i < 5; i++){m_pform2D[i] = NULL;}
	for (int i = 0; i < BLIZZARD_MAX; i++){ m_pPaperBlizzard[i] = NULL; }
	m_pBackGround	= NULL;
	m_pFade			= NULL;
	m_pBall			= NULL;
	m_pScenerio		= NULL;
	m_pManager		= NULL;
	m_a				= 2.0f;
	m_cnt			= 0;
	m_MaxSpeed		= 50;
	m_pRescore[3]	= { };
	m_ResultType = LOSE_TYPE;
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
	m_pBall = CBall::Create(pDevice, 0,D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//最初に表示する勝敗のやつ
	Lose();

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

	//スコア表示
	m_pRescore[0] = CReScore::Create(pDevice, scoreone, D3DXVECTOR3(SCORE_X, SCORE_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pRescore[1] = CReScore::Create(pDevice, rankone, D3DXVECTOR3(SCORE_X, SCORE_Y+150.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pRescore[2] = CReScore::Create(pDevice, ranktwo, D3DXVECTOR3(SCORE_X, SCORE_Y + (150.0f*2), 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pRescore[3] = CReScore::Create(pDevice, rankthree, D3DXVECTOR3(SCORE_X, SCORE_Y + (150.0f * 3), 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//フェードの作成
	m_pFade=CFade::Create(pDevice,1);

	m_pFade->StartFade(FADE_OUT,50,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));

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
	_UpdateFade();		//フェードの更新

	if (m_BlizzardFlag == true)
	{

		_UpdateBlizzard();	//紙吹雪の更新
	}
	m_cnt++;

	if (m_cnt > 300)
	{
		m_BlizzardFlag = true;
		m_cnt = 0;
	}


}
//=============================================================================
// 描画
//=============================================================================
void CResult :: Draw(void)
{

	//m_pScenerio->Draw();

	//背景
	//m_pBackGround->Draw();

	//リザルト
	//m_pRescore[0]->Draw();
	//m_pRescore[1]->Draw();/
	//m_pRescore[2]->Draw();
	//m_pRescore[3]->Draw();
	for (int i = 0; i < 5; i++)
	{
		if (m_pform2D[i]){ m_pform2D[i]->Draw(); }
	}
	if (m_BlizzardFlag == true)
	{
		//紙吹雪の描画
		for (int i = 0; i < BLIZZARD_MAX; i++)
		{
			m_pPaperBlizzard[i]->Draw();
		}
	}
	
	//フェード
	m_pFade->Draw();
}
//勝利時
void CResult::Win()
{
	PaperBlizzard(0,200);
	m_pform2D[2] = Cform2D::Create(m_pManager->GetDevice(), "data/TEXTURE/Winer.png", D3DXVECTOR3(300, 100, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 400, 200);						//Win表示
	m_pform2D[1] = Cform2D::Create(m_pManager->GetDevice(), "data/TEXTURE/Loser.png", D3DXVECTOR3(900, 100, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 400, 200);						//Lose表示
	m_pform2D[0] = Cform2D::Create(m_pManager->GetDevice(), "data/TEXTURE/Light.png", D3DXVECTOR3(300, 0, 0.0f),   D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200, 1800);						//スポットライト表示
	m_pform2D[3] = Cform2D::Create(m_pManager->GetDevice(), "data/TEXTURE/Enemyeffect000.png", D3DXVECTOR3(-200, 600, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1280, 752);				//敗者表示
	m_pform2D[4] = Cform2D::Create(m_pManager->GetDevice(), "data/TEXTURE/character/enisi/にへら.png", D3DXVECTOR3(890, 500, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1366, 768);		//勝者表示
	m_ResultType = MAX_TYPE;
	m_BlizzardFlag = false;
}
//敗北時
void CResult::Lose()
{

	PaperBlizzard(800, 1000);
	m_pform2D[2] = Cform2D::Create(m_pManager->GetDevice(), "data/TEXTURE/Loser.png", D3DXVECTOR3(300, 100, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 400, 200);						//Lose表示
	m_pform2D[1] = Cform2D::Create(m_pManager->GetDevice(), "data/TEXTURE/Winer.png", D3DXVECTOR3(900, 100, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 400, 200);						//Win表示
	m_pform2D[0] = Cform2D::Create(m_pManager->GetDevice(), "data/TEXTURE/Light.png", D3DXVECTOR3(900, 0, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200, 1800);						//スポットライト表示
	m_pform2D[4] = Cform2D::Create(m_pManager->GetDevice(), "data/TEXTURE/character/enisi/にへら.png", D3DXVECTOR3(300, 500, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1366, 768);		//勝者表示
	m_pform2D[3] = Cform2D::Create(m_pManager->GetDevice(), "data/TEXTURE/Enemyeffect001.png", D3DXVECTOR3(600, 600, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1280, 752);				//敗者表示
	m_ResultType = MAX_TYPE;
	m_BlizzardFlag = false;


}
//引き分け
void CResult::TieGame()
{
	//PaperBlizzard();
	m_pform2D[0] = Cform2D::Create(m_pManager->GetDevice(), "data/TEXTURE/Draw.png", D3DXVECTOR3(600, 100, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 400, 200);					//ドロー表示
	m_pform2D[1] = Cform2D::Create(m_pManager->GetDevice(), "data/TEXTURE/Enemyeffect000.png", D3DXVECTOR3(-200, 600, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1280, 752);		//顔表示
	m_pform2D[2] = Cform2D::Create(m_pManager->GetDevice(), "data/TEXTURE/Enemyeffect001.png", D3DXVECTOR3(700, 600, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1280, 752);		//顔表示2
	m_ResultType = MAX_TYPE;
	m_BlizzardFlag = false;


}
//紙吹雪
void CResult::PaperBlizzard(float min,float max)
{

	for (int i = 0; i < BLIZZARD_MAX; i++)
	{
		if (i < BLIZZARD_MAX / 2)
		{
			m_pPaperBlizzard[i] = Cform2D::Create(m_pManager->GetDevice(), m_apTextureName[mersenne_twister_u16(0, 3)], D3DXVECTOR3(mersenne_twister_u16(min, min+150), mersenne_twister_u16(700, 850), 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100, 100);
			m_Vector[i] = D3DXVECTOR2(mersenne_twister_f32(1.0f, 6.0f), -2.0f);
		}
		else
		{
			m_pPaperBlizzard[i] = Cform2D::Create(m_pManager->GetDevice(), m_apTextureName[mersenne_twister_u16(0, 3)], D3DXVECTOR3(mersenne_twister_u16(max-150, max), mersenne_twister_u16(700, 850), 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100, 100);
			m_Vector[i] = D3DXVECTOR2(mersenne_twister_f32(-6.0f, -1.0f), -2.0f);

		}
		D3DXVec2Normalize(&m_Vector[i], &m_Vector[i]);
	}
	
	///フラグ作ってリザルト入ってすぐ発射しないようにする
}

void CResult::_UpdateBlizzard(void)
{
	float G = 0.02f;		//重力
	float Power = 8.0f;		//上がる力
	D3DXVECTOR2 Speed = D3DXVECTOR2(0.0f, 0.0f);
	D3DXVECTOR2 Pos = D3DXVECTOR2(0.0f, 0.0f);


	//紙吹雪関係の挙動
	for (int i = 0; i < BLIZZARD_MAX; i++)
	{
		D3DXVECTOR2 Pos = m_pPaperBlizzard[i]->GetPos();
		Pos.y += G;
		Pos.y += m_Vector[i].y * m_MaxSpeed + 2.0f;

		if (m_MaxSpeed >= 0.0f){ Pos.x += m_Vector[i].x * m_MaxSpeed; }
		else
		{
			Pos.x += m_Vector[i].x*20.0f;
		}
		m_pPaperBlizzard[i]->SetPos(Pos.x, Pos.y, 0.0f);
	}

	m_MaxSpeed -= 1.6f;

}

void CResult::_UpdateFade(void)
{
	//キーボードインプットの受け取り
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();


	//フェードの開始
	if (pInputKeyboard->GetKeyTrigger(DIK_RETURN) || pInputKeyboard->GetKeyTrigger(DIK_Z))
	{
		CSound *pSound;
		pSound = CManager::GetSound();
		//pSound->Play(SOUND_LABEL_SE_SELECT001);
		m_pFade->StartFade(FADE_IN, 100, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	}

	//フェードインが終わったら
	if (m_pFade->GetFade() == FADE_IN_END)
	{
		//次のフェーズを変える
		CManager::SetAfterScene(PHASETYPE_TITLE);
	}

}
/////////////EOF////////////
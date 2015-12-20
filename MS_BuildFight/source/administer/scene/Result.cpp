//=============================================================================
//
// MS_BuildFight [CResult.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// �}�N����`
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
#include "../../module/field/Dome.h"


#include "../../form/formX.h"
#include "../../form/form3D.h"
#include "../../form/form2D.h"

#include "../../module/etc/Ball.h"

#include "../../module/ui/Scenario.h"

#include "../../exten_common.h"
//*****************************************************************************
// �萔
//*****************************************************************************
#define SCORE_X	(1000)
#define SCORE_Y	(100)

const float CAMERA_POS_X(0.0f);
const float CAMERA_POS_Y(0.0f);
const float CAMERA_POS_Z(-3500.0f);

//*****************************************************************************
// �ÓI�ϐ�
//*****************************************************************************
const LPSTR CResult::m_apTextureName[] =
{
	"data/TEXTURE/Red.png",
	"data/TEXTURE/Blue.png",
	"data/TEXTURE/Star.png",
	"data/TEXTURE/Arrow.png"

};

//���J��CG�p
const LPSTR g_RewardTexture[][2] =
{
	{ "data/TEXTURE/result/ccc.png",				//���[��
	"data/TEXTURE/result/ddd.jpg" },

	{ "data/TEXTURE/result/rosa_win.jpg",			//���[�U
	"data/TEXTURE/result/rosa_win.jpg", },

	{ "data/TEXTURE/result/jiityaaan.jpg",			//���������
	"data/TEXTURE/result/jiityaaan.jpg", },

	{"data/TEXTURE/result/licht_win.jpg",			//���q�g
	 "data/TEXTURE/result/licht_win.jpg" },
};

//�����G�\���p
const LPSTR g_StandTexture[][4] =
{
	{ "data/TEXTURE/character/lila/wara.png",
	"data/TEXTURE/character/lila/naki.png",
	"data/TEXTURE/character/lila/normal.png",
	"data/TEXTURE/character/lila/do.png" },

	{ "data/TEXTURE/character/rosa/wara.png",
	"data/TEXTURE/character/rosa/naki.png",
	"data/TEXTURE/character/rosa/normal.png",
	"data/TEXTURE/character/rosa/do.png" },

	{"data/TEXTURE/character/navi/wara.png",
	 "data/TEXTURE/character/navi/normal.png",
	 "data/TEXTURE/character/navi/wara.png",
	 "data/TEXTURE/character/navi/normal.png" },

	 { "data/TEXTURE/character/licht/wara.png",
	 "data/TEXTURE/character/licht/naki.png",
	 "data/TEXTURE/character/licht/normal.png",
	 "data/TEXTURE/character/licht/do.png" },

};

LPDIRECT3DDEVICE9 CResult::m_pD3DDevice = NULL;		// �f�o�C�X�̃|�C���^


//=============================================================================
// �R���X�g���N�^
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
// �f�X�g���N�^
//=============================================================================
CResult :: ~CResult(void)
{
}

//=============================================================================
// ������
//=============================================================================
HRESULT CResult :: Init(LPDIRECT3DDEVICE9 pDevice)
{
	// �J�����̎擾
	CCamera* pTmpCamera = CManager::GetCamera();
	pTmpCamera->Init();
	pTmpCamera->SetPosP(D3DXVECTOR3(CAMERA_POS_X, CAMERA_POS_Y, CAMERA_POS_Z));

	m_pD3DDevice = m_pManager->GetDevice();

	//�T�E���h�擾�̍쐬
	m_pSound = CManager::GetSound();

	//�ŏ��ɕ\�����鏟�s�̂��
	//1P�����������ǂ����ŏ��s�����肳���
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

	//�w�i�̍쐬
	m_pBackGround=CBackGround::Create(pDevice,BACKGROUND_RESULT);



	//�V�i���I
	m_pScenerio[0] = CScenario::Create(pDevice, (CScenario::Character)m_pManager->GetSelectChar(0), false);
	m_pScenerio[1] = CScenario::Create(pDevice, (CScenario::Character)m_pManager->GetSelectChar(1), false);




	//�T�E���h�Đ��̍쐬
	m_pSound->Play(SOUND_LABEL_BGM003);

	int time=CScene::GetTime();
	int score=CScene::GetScore();

	FILE *pFile;

	int scoreone=time+score;
	int rankone=0;
	int ranktwo=0;
	int rankthree=0;

	//�����N�t�@�C���̃I�[�v��
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

	//�����N�t�@�C���̒��g�ƃX�R�A���r
	//�X�R�A�̕������Ȃ��ꍇ
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
	//�X�R�A�̕��������ꍇ
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

	//�w�i����
	m_pform3D[0] = Cform3D::Create(m_pD3DDevice, "data/TEXTURE/sky004.jpg", D3DXVECTOR3(0.0f, 0.0f, 400.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2.0f*3.0f, -D3DX_PI / 2.0f*3.0f), 3250, 5900);

	m_pform2D[0] = Cform2D::Create(m_pManager->GetDevice(), g_RewardTexture[m_pManager->GetSelectChar(0)][0], D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT);
	m_pform2D[1] = Cform2D::Create(m_pManager->GetDevice(), g_RewardTexture[m_pManager->GetSelectChar(1)][1], D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT);
	m_pform2D[0]->SetDiffuse(255.0f, 255.0f, 255.0f, m_Alpha[0]);
	m_pform2D[1]->SetDiffuse(255.0f, 255.0f, 255.0f, m_Alpha[1]);

	//�X�R�A�\��
	m_pRescore[0] = CReScore::Create(pDevice, scoreone, D3DXVECTOR3(SCORE_X, SCORE_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pRescore[1] = CReScore::Create(pDevice, rankone, D3DXVECTOR3(SCORE_X, SCORE_Y+150.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pRescore[2] = CReScore::Create(pDevice, ranktwo, D3DXVECTOR3(SCORE_X, SCORE_Y + (150.0f*2), 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pRescore[3] = CReScore::Create(pDevice, rankthree, D3DXVECTOR3(SCORE_X, SCORE_Y + (150.0f * 3), 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//�t�F�[�h�̍쐬
	m_pFade=CFade::Create(pDevice,1);

	m_pFade->StartFade(FADE_OUT,50,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),CManager::GetSelectChar(0));



	return S_OK;
}
//=============================================================================
// �I��
//=============================================================================
void CResult :: Uninit(void)
{
	//�T�E���h�擾�̍쐬
	CSound *pSound;
	pSound = CManager::GetSound();


	for (int i = 0; i < 2; i++)
	{
		m_pScenerio[i]->Uninit();
		delete m_pScenerio[i];
		m_pScenerio[i] = NULL;
	}

	//�T�E���h�Đ��̍쐬
	pSound->Stop();

	//�V�[����S�ďI��
	Cform::ReleaseAll();
}
//=============================================================================
// �X�V
//=============================================================================
void CResult::Update(void)
{
	_UpdateTimer();				//���ʉ��Đ��^�C�}�[�̍X�V
	_UpdateCracker();			//�����˂̍X�V
	_UpdatePaperBlizzard();		//������̍X�V
	_UpdateFlag();				//�`��t���O�̍X�V
	_UpdateFade();				//�t�F�[�h�̍X�V
	_UpdateWinningOrLosing();
	_UpdateLauncher();


}
//=============================================================================
// �`��
//=============================================================================
void CResult :: Draw(void)
{
	m_pD3DDevice = CManager::GetDevice();

	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//�L�����Ɣw�i�`��
	for (int i = 0; i < 8; i++)
	{
		if (m_pform3D[i]){ m_pform3D[i]->Draw(); }
	}


	//�����˕`��
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

	//������`��
	if (m_BlizzardFlag == true)
	{
		for (int i = 0; i < BLIZZARD_MAX; i++)
		{
			m_pPaperBlizzard[i]->Draw();

		}
	}


	//���J��CG�p�`��
	for (int i = 0; i < 2; i++)
	{
		if (m_pform2D[i]){ m_pform2D[i]->Draw(); }
	}

	//
	for (int i = 0; i < 2; i++)
	{
		if (m_pScenerio[i]){ m_pScenerio[i]->Draw(); }
	}


	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);			// ���ʂ��J�����O


	//�t�F�[�h
	m_pFade->Draw();
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<
//������
//<<<<<<<<<<<<<<<<<<<<<<<<<<
void CResult::Win()
{
	PaperCracker(0.0f, 600.0f);
	PaperBlizzard(0.0f, 1700.0f);

	m_pform3D[1] = Cform3D::Create(m_pManager->GetDevice(), "data/TEXTURE/Winer.png", D3DXVECTOR3(2400.0f, 1000.0f, 50.0f),  D3DXVECTOR3(D3DX_PI / 2.0f*3.0f, 0.0f, 0.0f), 1600, 600);							//Win�\��
	m_pform3D[2] = Cform3D::Create(m_pManager->GetDevice(), "data/TEXTURE/Loser.png", D3DXVECTOR3(-2600.0f, 1000.0f, 50.0f), D3DXVECTOR3(D3DX_PI / 2.0f*3.0f, 0.0f, 0.0f), 1600, 600);							//Lose�\��
	//m_pform3D[3] = Cform3D::Create(m_pManager->GetDevice(), "data/TEXTURE/Light.png", D3DXVECTOR3(1300.0f, 0.0f, 0.0f),	 D3DXVECTOR3(0.0f, D3DX_PI / 2.0f*3.0f, -D3DX_PI / 2.0f*3.0f), 3000, 800);			//�X�|�b�g���C�g�\��
	m_pform3D[4] = Cform3D::Create(m_pManager->GetDevice(), g_StandTexture[m_pManager->GetSelectChar(0)][0], D3DXVECTOR3(1400.0f, -500.0f, 0.0f),  D3DXVECTOR3(D3DX_PI /2.0f*3.0f, 0.0f, 0.0f), 2280, 2007);	//�s�ҕ\��
	m_pform3D[5] = Cform3D::Create(m_pManager->GetDevice(), g_StandTexture[m_pManager->GetSelectChar(1)][1], D3DXVECTOR3(-1400.0f, -500.0f, 0.0f), D3DXVECTOR3(D3DX_PI /2.0f*3.0f, 0.0f, 0.0f), 2280, 2007);	//���ҕ\��
	m_pform3D[6] = Cform3D::Create(m_pManager->GetDevice(), "data/TEXTURE/cracker.png", D3DXVECTOR3(2500.0f, -1500.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 2.0f*3.0f, 0.0f, 0.0f), 750, 750);							//�N���b�J�[�\��
	m_pform3D[7] = Cform3D::Create(m_pManager->GetDevice(), "data/TEXTURE/cracker.png", D3DXVECTOR3(-700.0f, -1500.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 2.0f*3.0f, D3DX_PI*3.0f, 0.0f), 750, 750);					//�N���b�J�[�\��


	m_ResultType = MAX_TYPE;
	m_CrackerFlag = false;
	m_BlizzardFlag = false;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<
//����
//<<<<<<<<<<<<<<<<<<<<<<<<<<
void CResult::Lose()
{
	PaperCracker(-1000.0f, -700.0f);
	PaperBlizzard(-1700.0f, 0.0f);
	m_pform3D[1] = Cform3D::Create(m_pManager->GetDevice(), "data/TEXTURE/Loser.png", D3DXVECTOR3(2400.0f, 1000.0f, 50.0f),  D3DXVECTOR3(D3DX_PI / 2.0f*3.0f, 0.0f, 0.0f), 1600, 600);								//Lose�\��
	m_pform3D[2] = Cform3D::Create(m_pManager->GetDevice(), "data/TEXTURE/Winer.png", D3DXVECTOR3(-2500.0f, 1000.0f, 50.0f), D3DXVECTOR3(D3DX_PI / 2.0f*3.0f, 0.0f, 0.0f), 1600, 600);								//Win�\��
	//m_pform3D[3] = Cform3D::Create(m_pManager->GetDevice(), "data/TEXTURE/Light.png", D3DXVECTOR3(-1300.0f, 0.0f, 0.0f),	 D3DXVECTOR3(0.0f, D3DX_PI / 2.0f*3.0f, -D3DX_PI / 2.0f*3.0f), 3000, 800);				//�X�|�b�g���C�g�\��
	m_pform3D[4] = Cform3D::Create(m_pManager->GetDevice(), g_StandTexture[m_pManager->GetSelectChar(0)][1], D3DXVECTOR3(1400.0f, -500.0f, 0.0f),  D3DXVECTOR3(D3DX_PI / 2.0f*3.0f, 0.0f, 0.0f), 2280, 2007);		//���ҕ\��
	m_pform3D[5] = Cform3D::Create(m_pManager->GetDevice(), g_StandTexture[m_pManager->GetSelectChar(1)][0], D3DXVECTOR3(-1400.0f, -500.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 2.0f*3.0f, 0.0f, 0.0f), 2280, 2007);		//�s�ҕ\��
	m_pform3D[6] = Cform3D::Create(m_pManager->GetDevice(), "data/TEXTURE/cracker.png", D3DXVECTOR3(0.0f, -1500.0f, 0.0f),     D3DXVECTOR3(D3DX_PI / 2.0f*3.0f, 0.0f, 0.0f), 750, 750);								//�N���b�J�[�\��
	m_pform3D[7] = Cform3D::Create(m_pManager->GetDevice(), "data/TEXTURE/cracker.png", D3DXVECTOR3(-2400.0f, -1500.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 2.0f*3.0f, D3DX_PI*3.0f, 0.0f), 750, 750);						//�N���b�J�[�\��
	m_ResultType = MAX_TYPE;
	m_CrackerFlag = false;
	m_BlizzardFlag = false;
}
//<<<<<<<<<<<<<<<<<<<<<<<<<<
//��������
//<<<<<<<<<<<<<<<<<<<<<<<<<<
void CResult::TieGame()
{
	//PaperCracker(-200.0f, 200.0f);
	PaperBlizzard(-800.0f, 800.0f);
	m_pform3D[1] = Cform3D::Create(m_pManager->GetDevice(), "data/TEXTURE/Draw.png", D3DXVECTOR3(0.0f, 1000.0f, 50.0f), D3DXVECTOR3(D3DX_PI / 2.0f*3.0f, 0.0f, 0.0f), 1600, 600);															//�h���[�\��
	m_pform3D[2] = Cform3D::Create(m_pManager->GetDevice(), g_StandTexture[m_pManager->GetSelectChar(0)][1], D3DXVECTOR3(1400.0f, -500.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 2.0f*3.0f, 0.0f, 0.0f), 2280, 2007);		//��\��
	m_pform3D[3] = Cform3D::Create(m_pManager->GetDevice(), g_StandTexture[m_pManager->GetSelectChar(1)][1], D3DXVECTOR3(-1400.0f, -500.0f, 0.0f), D3DXVECTOR3(D3DX_PI / 2.0f*3.0f, 0.0f, 0.0f), 2280, 2007);	//��\��2
	m_ResultType = MAX_TYPE;
	m_CrackerFlag = false;
	m_BlizzardFlag = false;
}
//<<<<<<<<<<<<<<<<<<<<<<<<<<
//�����˂̐���
//<<<<<<<<<<<<<<<<<<<<<<<<<<
void CResult::PaperCracker(float min, float max)
{
	for (int i = 0; i < CRACKER_MAX; i++)
	{
		if (i < CRACKER_MAX / 2)
		{
			//����
			m_pPaperCracker[i] = Cform3D::Create(m_pManager->GetDevice(), m_apTextureName[mersenne_twister_u16(0, 3)], D3DXVECTOR3(mersenne_twister_u16(min, min + 1500.0f), mersenne_twister_u16(-600, 50), mersenne_twister_f32(-300.0f, -250.0f)), D3DXVECTOR3(-D3DX_PI / 2.0f, 0.0f, 0.0f), 200.0f, 200.0f);
			m_CrackerVector[i] = D3DXVECTOR3(mersenne_twister_f32(1.0f, 4.0f), -2.0f,0.0f);
		}
		else
		{
			//�E��
			m_pPaperCracker[i] = Cform3D::Create(m_pManager->GetDevice(), m_apTextureName[mersenne_twister_u16(0, 3)], D3DXVECTOR3(mersenne_twister_u16(max - 1500.0f, max), mersenne_twister_u16(-600, 50), mersenne_twister_f32(-300.0f, -250.0f)), D3DXVECTOR3(-D3DX_PI / 2.0f, 0.0f, 0.0f), 200.0f, 200.0f);
			m_CrackerVector[i] = D3DXVECTOR3(mersenne_twister_f32(-3.0f, -1.0f), -2.0f,0.0f);
		}
		D3DXVec3Normalize(&m_CrackerVector[i], &m_CrackerVector[i]);
	}
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<
//�����ᐶ��
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
//�����˂̍X�V
//<<<<<<<<<<<<<<<<<<<<<<<<<<
void CResult::_UpdateCracker(void)
{
	float G = 0.001f;		//�d��
	float Power = 8.0f;		//�オ���
	D3DXVECTOR3 Speed = D3DXVECTOR3(0.0f, 0.0f,0.0f);
	D3DXVECTOR3 Pos = D3DXVECTOR3(0.0f, 0.0f,0.0f);
	D3DXVECTOR3 Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < CRACKER_MAX; i++)
	{
		Pos.z += m_CrackerVector[i].z*10.0f;
	}
	if (m_CrackerFlag == true)
	{
		//�����ˊ֌W�̋���
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
//�t�F�[�h�̍X�V
//<<<<<<<<<<<<<<<<<<<<<<<<<<
void CResult::_UpdateFade(void)
{
	//�L�[�{�[�h�C���v�b�g�̎󂯎��
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

	//�t�F�[�h�̊J�n
	else if ((pInputKeyboard->GetKeyTrigger(DIK_RETURN) || pInputKeyboard->GetKeyTrigger(DIK_Z) || Player1->GetKeyTrigger(WII_BUTTOM_A)) && m_AfterRewardFlag == true && m_ButtonCounter==4)
	{
		CSound *pSound;
		pSound = CManager::GetSound();
		m_pFade->StartFade(FADE_IN, 100, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), CManager::GetSelectChar(0));
	}

	//�t�F�[�h�C�����I�������
	if (m_pFade->GetFade() == FADE_IN_END)
	{
		//���̃t�F�[�Y��ς���
		CManager::SetAfterScene(PHASETYPE_TITLE);

	}




}

//<<<<<<<<<<<<<<<<<<<<<<<<<<
//������̍X�V
//<<<<<<<<<<<<<<<<<<<<<<<<<<
void CResult::_UpdatePaperBlizzard(void)
{
	D3DXVECTOR3 Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//������֌W�̋���
	for (int i = 0; i < BLIZZARD_MAX; i++)
	{
		Rot = m_pPaperBlizzard[i]->GetRot();
		Rot.x += mersenne_twister_f32(0.01f, 0.13f);
		Rot.y += mersenne_twister_f32(0.01f, 0.08f);
		Rot.z += mersenne_twister_f32(0.01f, 0.07f);

		float Length = m_pPaperBlizzard[i]->GetLength();
		D3DXVECTOR3 Pos = m_pPaperBlizzard[i]->GetPos();
		Pos -=10.0f*m_BlizzardVector[i] * mersenne_twister_f32(0.02f, 1.0f);
		m_pPaperBlizzard[i]->SetPos(D3DXVECTOR3(Pos.x, Pos.y, 0));		//���W�ݒ�
		m_pPaperBlizzard[i]->SetRot(Rot.x,Rot.y,Rot.z);					//�p�x�ݒ�

		Length += mersenne_twister_f32(-1.0f, 1.0f);
		if (Length > 15.0f){ Length = 15.0f; }
		else if (Length < 19.0f){ Length = 19.0f; }
		m_pPaperBlizzard[i]->SetLength(Length);
	}
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<
//������̕`��t���O�̍X�V
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
//���ʉ��Đ��^�C�~���O�̍X�V
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
//Win,Lose�摜�̍X�V
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
//�N���b�J�[���ˑ��u�摜�̍X�V
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
//�N���b�J�[���ˑ��u�������̍X�V
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
//�N���b�J�[���ˑ��u�s�k���̍X�V
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
//�N���b�J�[���ˑ��u�����������̍X�V
//<<<<<<<<<<<<<<<<<<<<<<<<<<
void CResult::_UpdateTieGameLauncher(void)
{

}




/////////////EOF////////////
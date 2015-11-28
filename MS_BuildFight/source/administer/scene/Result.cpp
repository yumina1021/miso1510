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

#include "../../module/etc/Fade.h"
#include "../../module/ui/BackGround.h"
#include "../../module/ui/ResultScore.h"

#include "../../form/formX.h"

#include "../../module/etc/Ball.h"

#include "../../module/ui/Scenario.h"

#include "../../exten_common.h"
//*****************************************************************************
// �萔
//*****************************************************************************
#define SCORE_X	(1000)
#define SCORE_Y	(100)

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

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CResult :: CResult(void)
{
	for (int i = 0; i < 6; i++){m_pform2D[i] = NULL;}
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
	m_pBall = CBall::Create(pDevice, 0,D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//�ŏ��ɕ\�����鏟�s�̂��
	Lose();

	//�w�i�̍쐬
	m_pBackGround=CBackGround::Create(pDevice,BACKGROUND_RESULT);

	//�V�i���I
	//m_pScenerio = CScenario::Create(pDevice,true);

	//�T�E���h�擾�̍쐬
	CSound *pSound;
	pSound = CManager::GetSound();

	//�T�E���h�Đ��̍쐬
	//pSound->Play(SOUND_LABEL_BGM002);

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
	m_pform2D[0] = Cform2D::Create(m_pManager->GetDevice(), "data/TEXTURE/sky004.jpg", D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),3900, 2250);

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

	//m_pScenerio->Uninit();
	//delete m_pScenerio;


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
	_UpdateCracker();			//�����˂̍X�V
	_UpdatePaperBlizzard();		//������̍X�V
	_UpdateFlag();				//�`��t���O�̍X�V
	_UpdateFade();				//�t�F�[�h�̍X�V

}
//=============================================================================
// �`��
//=============================================================================
void CResult :: Draw(void)
{

	//�L�����Ɣw�i�`��
	for (int i = 0; i < 6; i++)
	{
		if (m_pform2D[i]){ m_pform2D[i]->Draw(); }
	}
	//�����˕`��
	if (m_CrackerFlag == true)
	{
		for (int i = 0; i < CRACKER_MAX; i++)
		{
			m_pPaperCracker[i]->Draw();
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
	//�t�F�[�h
	m_pFade->Draw();
}
//������
void CResult::Win()
{
	PaperCracker(0, 200);
	PaperBlizzard(0, 200);
	m_pform2D[1] = Cform2D::Create(m_pManager->GetDevice(), "data/TEXTURE/Winer.png", D3DXVECTOR3(300, 100, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 400, 200);							//Win�\��
	m_pform2D[2] = Cform2D::Create(m_pManager->GetDevice(), "data/TEXTURE/Loser.png", D3DXVECTOR3(900, 100, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 400, 200);							//Lose�\��
	m_pform2D[3] = Cform2D::Create(m_pManager->GetDevice(), "data/TEXTURE/Light.png", D3DXVECTOR3(300, 0, 0.0f),   D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200, 1800);							//�X�|�b�g���C�g�\��
	m_pform2D[4] = Cform2D::Create(m_pManager->GetDevice(), g_StandTexture[m_pManager->GetSelectChar(0)][0], D3DXVECTOR3(-200, 600, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1280, 752);		//�s�ҕ\��
	m_pform2D[5] = Cform2D::Create(m_pManager->GetDevice(), g_StandTexture[m_pManager->GetSelectChar(1)][1], D3DXVECTOR3(890, 500, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1366, 768);		//���ҕ\��
	m_ResultType = MAX_TYPE;
	m_CrackerFlag = false;
	m_BlizzardFlag = false;
}
//�s�k��
void CResult::Lose()
{
	PaperCracker(800, 1000);
	PaperBlizzard(700, 1000);
	m_pform2D[1] = Cform2D::Create(m_pManager->GetDevice(), "data/TEXTURE/Loser.png", D3DXVECTOR3(300, 100, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 400, 200);							//Lose�\��
	m_pform2D[2] = Cform2D::Create(m_pManager->GetDevice(), "data/TEXTURE/Light.png", D3DXVECTOR3(900, 0, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200, 1800);								//�X�|�b�g���C�g�\��
	m_pform2D[3] = Cform2D::Create(m_pManager->GetDevice(), "data/TEXTURE/Winer.png", D3DXVECTOR3(900, 100, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 400, 200);							//Win�\��
	m_pform2D[4] = Cform2D::Create(m_pManager->GetDevice(), g_StandTexture[m_pManager->GetSelectChar(0)][2], D3DXVECTOR3(300, 500, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 500, 750);			//���ҕ\��
	m_pform2D[5] = Cform2D::Create(m_pManager->GetDevice(), g_StandTexture[m_pManager->GetSelectChar(1)][1], D3DXVECTOR3(900, 500, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 500, 750);			//�s�ҕ\��
	m_ResultType = MAX_TYPE;
	m_CrackerFlag = false;
	m_BlizzardFlag = false;
}
//��������
void CResult::TieGame()
{
	//PaperBlizzard();
	m_pform2D[1] = Cform2D::Create(m_pManager->GetDevice(), "data/TEXTURE/Draw.png", D3DXVECTOR3(600, 100, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 400, 200);								//�h���[�\��
	m_pform2D[2] = Cform2D::Create(m_pManager->GetDevice(), g_StandTexture[m_pManager->GetSelectChar(0)][0], D3DXVECTOR3(-200, 600, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1280, 752);		//��\��
	m_pform2D[3] = Cform2D::Create(m_pManager->GetDevice(), g_StandTexture[m_pManager->GetSelectChar(1)][1], D3DXVECTOR3(700, 600, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1280, 752);		//��\��2
	m_ResultType = MAX_TYPE;
	m_CrackerFlag = false;
	m_BlizzardFlag = false;
}
//������
void CResult::PaperCracker(float min, float max)
{
	for (int i = 0; i < CRACKER_MAX; i++)
	{
		if (i < CRACKER_MAX / 2)
		{
			m_pPaperCracker[i] = Cform2D::Create(m_pManager->GetDevice(), m_apTextureName[mersenne_twister_u16(0, 3)], D3DXVECTOR3(mersenne_twister_u16(min, min + 150), mersenne_twister_u16(700, 850), 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f);
			m_CrackerVector[i] = D3DXVECTOR2(mersenne_twister_f32(1.0f, 4.0f), -2.0f);
		}
		else
		{
			m_pPaperCracker[i] = Cform2D::Create(m_pManager->GetDevice(), m_apTextureName[mersenne_twister_u16(0, 3)], D3DXVECTOR3(mersenne_twister_u16(max - 150, max), mersenne_twister_u16(700, 850), 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f);
			m_CrackerVector[i] = D3DXVECTOR2(mersenne_twister_f32(-4.0f, -1.0f), -2.0f);
		}
		D3DXVec2Normalize(&m_CrackerVector[i], &m_CrackerVector[i]);
	}
}

void CResult::PaperBlizzard(float min, float max)
{
	for (int i = 0; i < BLIZZARD_MAX; i++)
	{
		m_pPaperBlizzard[i] = Cform2D::Create(m_pManager->GetDevice(), m_apTextureName[mersenne_twister_u16(0, 3)], D3DXVECTOR3(mersenne_twister_u16(min, max), mersenne_twister_u16(-300, -50), 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 70.0f, 50.0f);
		m_BlizzardVector[i] = D3DXVECTOR2(mersenne_twister_f32(-1.0f, 1.0f), 1.0f);
		D3DXVec2Normalize(&m_BlizzardVector[i], &m_BlizzardVector[i]);
	}
}

void CResult::_UpdateCracker(void)
{
	float G = 0.02f;		//�d��
	float Power = 8.0f;		//�オ���
	D3DXVECTOR2 Speed = D3DXVECTOR2(0.0f, 0.0f);
	D3DXVECTOR2 Pos = D3DXVECTOR2(0.0f, 0.0f);

	if (m_CrackerFlag == true)
	{
		//�����ˊ֌W�̋���
		for (int i = 0; i < CRACKER_MAX; i++)
		{
			D3DXVECTOR2 Pos = m_pPaperCracker[i]->GetPos();
			Pos.y += G;
			Pos.y += m_CrackerVector[i].y * m_MaxSpeed + 2.0f;

			if (m_MaxSpeed >= 0.0f){ Pos.x += m_CrackerVector[i].x * m_MaxSpeed; }
			else
			{
				Pos.x += m_CrackerVector[i].x*20.0f;
			}
			m_pPaperCracker[i]->SetPos(Pos.x, Pos.y, 0.0f);
		}
		m_MaxSpeed -= 1.6f;
	}
}

void CResult::_UpdateFade(void)
{
	//�L�[�{�[�h�C���v�b�g�̎󂯎��
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();
	WiiRemote* Player1 = CManager::GetWii(0);		//1P


	//�t�F�[�h�̊J�n
	if (pInputKeyboard->GetKeyTrigger(DIK_RETURN) || pInputKeyboard->GetKeyTrigger(DIK_Z) || Player1->GetKeyTrigger(WII_BUTTOM_A))
	{
		CSound *pSound;
		pSound = CManager::GetSound();
		//pSound->Play(SOUND_LABEL_SE_SELECT001);
		m_pFade->StartFade(FADE_IN, 100, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f),CManager::GetSelectChar(0));
	}

	//�t�F�[�h�C�����I�������
	if (m_pFade->GetFade() == FADE_IN_END)
	{
		//���̃t�F�[�Y��ς���
		CManager::SetAfterScene(PHASETYPE_TITLE);
	}

}

void CResult::_UpdatePaperBlizzard(void)
{
	//������֌W�̋���
	for (int i = 0; i < BLIZZARD_MAX; i++)
	{
		float Length = m_pPaperBlizzard[i]->GetLength();
		D3DXVECTOR2 Pos = m_pPaperBlizzard[i]->GetPos();
		Pos += 2.0f*m_BlizzardVector[i] * mersenne_twister_f32(0.01f, 1.0f);
		m_pPaperBlizzard[i]->SetPos(D3DXVECTOR3(Pos.x, Pos.y, 0));

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
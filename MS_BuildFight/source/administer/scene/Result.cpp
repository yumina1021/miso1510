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
	"data/TEXTURE/Yellow.png",
	"data/TEXTURE/Rainbow.png"

};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CResult :: CResult(void)
{
	for (int i = 0; i < 5; i++)
	{
		m_pform2D[i] = NULL;

	}
	for (int i = 0; i < BLIZZARD_MAX; i++){ m_pPaperBlizzard[i] = NULL; }
	m_pBackGround = NULL;
	m_pFade = NULL;
	m_pRescore[3] = { };
	m_pBall = NULL;
	m_ResultType = WIN_TYPE;
	m_pScenerio = NULL;
	m_pManager = NULL;
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

	//�X�R�A�\��
	m_pRescore[0] = CReScore::Create(pDevice, scoreone, D3DXVECTOR3(SCORE_X, SCORE_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pRescore[1] = CReScore::Create(pDevice, rankone, D3DXVECTOR3(SCORE_X, SCORE_Y+150.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pRescore[2] = CReScore::Create(pDevice, ranktwo, D3DXVECTOR3(SCORE_X, SCORE_Y + (150.0f*2), 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pRescore[3] = CReScore::Create(pDevice, rankthree, D3DXVECTOR3(SCORE_X, SCORE_Y + (150.0f * 3), 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//�t�F�[�h�̍쐬
	m_pFade=CFade::Create(pDevice,1);

	m_pFade->StartFade(FADE_OUT,50,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));

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
void CResult :: Update(void)
{
	//�L�[�{�[�h�C���v�b�g�̎󂯎��
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//m_pScenerio->Update(pInputKeyboard);



	D3DXVECTOR3 pos = m_pBall->GetPos();
	if (pInputKeyboard->GetKeyTrigger(DIK_A))
	{
		pos.x++;
	}
	if (pInputKeyboard->GetKeyTrigger(DIK_D))
	{
		pos.x--;
	}
	m_pBall->SetPos(pos);

	/*//���@���U���g�̕\���ؑ�
	if (pInputKeyboard->GetKeyTrigger(DIK_F1))
	{
		m_ResultType = WIN_TYPE;
		for (int i = 0; i < 2;i++)
		if (m_pform2D[i]){m_pform2D[i]->Uninit();}
	}
	if (pInputKeyboard->GetKeyTrigger(DIK_F2))
	{
		m_ResultType = LOSE_TYPE;
		for (int i = 0; i < 2; i++)
		if (m_pform2D[i]){ m_pform2D[i]->Uninit(); }
	}	
	if (pInputKeyboard->GetKeyTrigger(DIK_F3))
	{
		m_ResultType = TIEGAME_TYPE;
		for (int i = 0; i < 2; i++)
		if (m_pform2D[i]){ m_pform2D[i]->Uninit(); }
	}
	
	switch (m_ResultType)
	{
		case WIN_TYPE:	Win();
			break;
		case LOSE_TYPE:	Lose();
			break;
		case TIEGAME_TYPE:	TieGame();
			break;
	}*/

	//������֌W�̋���
	for (int i = 0; i < BLIZZARD_MAX; i++)
	{
		float Length = m_pPaperBlizzard[i]->GetLength();
		D3DXVECTOR2 Pos = m_pPaperBlizzard[i]->GetPos();
		Pos += 2.0f*m_Vector[i] * mersenne_twister_f32(0.01f,1.0f);
		m_pPaperBlizzard[i]->SetPos(D3DXVECTOR3(Pos.x, Pos.y, 0));
		Length += mersenne_twister_f32(-1.0f, 1.0f);
		if (Length > 1.0f){ Length = 1.0f; }
		else if (Length < 5.0f){ Length = 5.0f; }
		m_pPaperBlizzard[i]->SetLength(Length);
	}

	//�t�F�[�h�̊J�n
	if(pInputKeyboard->GetKeyTrigger(DIK_RETURN)||pInputKeyboard->GetKeyTrigger(DIK_Z))
	{
		CSound *pSound;
		pSound = CManager::GetSound();
		//pSound->Play(SOUND_LABEL_SE_SELECT001);
		m_pFade->StartFade(FADE_IN,100,D3DXCOLOR(1.0f,1.0f,1.0f,0.0f));
	}

	//�t�F�[�h�C�����I�������
	if(m_pFade->GetFade()==FADE_IN_END)
	{
		//���̃t�F�[�Y��ς���
		CManager::SetAfterScene(PHASETYPE_TITLE);
	}
}
//=============================================================================
// �`��
//=============================================================================
void CResult :: Draw(void)
{

	//m_pScenerio->Draw();

	//�w�i
	//m_pBackGround->Draw();

	//���U���g
	//m_pRescore[0]->Draw();
	//m_pRescore[1]->Draw();
	//m_pRescore[2]->Draw();
	//m_pRescore[3]->Draw();
	for (int i = 0; i < 5; i++)
	{
		if (m_pform2D[i]){ m_pform2D[i]->Draw(); }
	}
	for (int i = 0; i < BLIZZARD_MAX; i++)
	{
		m_pPaperBlizzard[i]->Draw();
	}
	
	
	//�t�F�[�h
	m_pFade->Draw();
}
//������
void CResult::Win()
{
	PaperBlizzard(0,200);
	m_pform2D[2] = Cform2D::Create(m_pManager->GetDevice(), "data/TEXTURE/Winer.png", D3DXVECTOR3(300, 100, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 400, 200);						//Win�\��
	m_pform2D[1] = Cform2D::Create(m_pManager->GetDevice(), "data/TEXTURE/Loser.png", D3DXVECTOR3(900, 100, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 400, 200);						//Lose�\��
	m_pform2D[0] = Cform2D::Create(m_pManager->GetDevice(), "data/TEXTURE/Light.png", D3DXVECTOR3(300, 0, 0.0f),   D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200, 1800);						//�X�|�b�g���C�g�\��
	m_pform2D[3] = Cform2D::Create(m_pManager->GetDevice(), "data/TEXTURE/Enemyeffect000.png", D3DXVECTOR3(-200, 600, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1280, 752);				//�s�ҕ\��
	m_pform2D[4] = Cform2D::Create(m_pManager->GetDevice(), "data/TEXTURE/character/enisi/�ɂւ�.png", D3DXVECTOR3(890, 500, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1366, 768);		//���ҕ\��
	m_ResultType = MAX_TYPE;
}
//�s�k��
void CResult::Lose()
{
	PaperBlizzard(700,1000);
	m_pform2D[2] = Cform2D::Create(m_pManager->GetDevice(), "data/TEXTURE/Loser.png", D3DXVECTOR3(300, 100, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 400, 200);						//Lose�\��
	m_pform2D[1] = Cform2D::Create(m_pManager->GetDevice(), "data/TEXTURE/Winer.png", D3DXVECTOR3(900, 100, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 400, 200);						//Win�\��
	m_pform2D[0] = Cform2D::Create(m_pManager->GetDevice(), "data/TEXTURE/Light.png", D3DXVECTOR3(900, 0, 0.0f),   D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200, 1800);						//�X�|�b�g���C�g�\��
	m_pform2D[4] = Cform2D::Create(m_pManager->GetDevice(), "data/TEXTURE/character/enisi/�ɂւ�.png", D3DXVECTOR3(300, 500, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1366, 768);		//���ҕ\��
	m_pform2D[3] = Cform2D::Create(m_pManager->GetDevice(), "data/TEXTURE/Enemyeffect001.png", D3DXVECTOR3(600, 600, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1280, 752);				//�s�ҕ\��
	m_ResultType = MAX_TYPE;
}
//��������
void CResult::TieGame()
{
	//PaperBlizzard();
	m_pform2D[0] = Cform2D::Create(m_pManager->GetDevice(), "data/TEXTURE/Draw.png", D3DXVECTOR3(600, 100, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 400, 200);					//�h���[�\��
	m_pform2D[1] = Cform2D::Create(m_pManager->GetDevice(), "data/TEXTURE/Enemyeffect000.png", D3DXVECTOR3(-200, 600, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1280, 752);		//��\��
	m_pform2D[2] = Cform2D::Create(m_pManager->GetDevice(), "data/TEXTURE/Enemyeffect001.png", D3DXVECTOR3(700, 600, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1280, 752);		//��\��2
	m_ResultType = MAX_TYPE;

}
//������
void CResult::PaperBlizzard(float min,float max)
{
	for (int i = 0; i < BLIZZARD_MAX; i++)
	{
		m_pPaperBlizzard[i] = Cform2D::Create(m_pManager->GetDevice(), m_apTextureName[mersenne_twister_u16(0, 3)], D3DXVECTOR3(mersenne_twister_u16(min, max), mersenne_twister_u16(-300, -50), 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20, 10);
		m_Vector[i] = D3DXVECTOR2(mersenne_twister_f32(-1.0f, 1.0f), 1.0f);
		D3DXVec2Normalize(&m_Vector[i], &m_Vector[i]);
	}
	




}

/////////////EOF////////////
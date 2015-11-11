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
//*****************************************************************************
// �萔
//*****************************************************************************
#define SCORE_X	(1000)
#define SCORE_Y	(100)

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CResult :: CResult(void)
{
	m_pBackGround = NULL;
	m_pFade = NULL;
	m_pRescore[3] = { };

	m_pBall = NULL;

	m_pScenerio = NULL;
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

	//�w�i�̍쐬
	m_pBackGround=CBackGround::Create(pDevice,BACKGROUND_RESULT);

	//�V�i���I
	m_pScenerio = CScenario::Create(pDevice,true);

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

	m_pScenerio->Uninit();
	delete m_pScenerio;

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

	m_pScenerio->Update(pInputKeyboard);

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

	m_pScenerio->Draw();

	//�w�i
	//m_pBackGround->Draw();

	//���U���g
	//m_pRescore[0]->Draw();
	//m_pRescore[1]->Draw();
	//m_pRescore[2]->Draw();
	//m_pRescore[3]->Draw();

	//�t�F�[�h
	m_pFade->Draw();
}
/////////////EOF////////////
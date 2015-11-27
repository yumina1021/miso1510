//=============================================================================
//
// MS_BuildFight [CVsend.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#include "Vsend.h"

#include "../Input.h"
#include "../Maneger.h"
#include "../Sound.h"

#include "../../module/etc/Fade.h"

#include "../../module/ui/BackGround.h"
#include "../../module/ui/ResultScore.h"
#include "../../module/ui/Effect.h"
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
CBackGround *CVsend::m_pBackGround = NULL;
CFade		*CVsend::m_pFade=NULL;
CEffect		*CVsend::m_pEffect = NULL;
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CVsend :: CVsend(void)
{
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CVsend :: ~CVsend(void)
{
}

//=============================================================================
// ������
//=============================================================================
HRESULT CVsend :: Init(LPDIRECT3DDEVICE9 pDevice)
{
	//�w�i�̍쐬
	m_pBackGround=CBackGround::Create(pDevice,BACKGROUND_VSEND);

	//�T�E���h�擾�̍쐬
	CSound *pSound;
	pSound = CManager::GetSound();

	//�T�E���h�Đ��̍쐬
	//pSound->Play(SOUND_LABEL_BGM002);

	int time=CScene::GetTime();
	int score=CScene::GetScore();
	bool vs = CScene::GetVSFlag();

	if(vs==true)
	{
		m_pEffect = CEffect::Create(pDevice, action, D3DXVECTOR3(650.0f, 375.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}else
	{
		m_pEffect = CEffect::Create(pDevice, action, D3DXVECTOR3(650.0f, 375.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	m_pEffect->SetView(true);

	//CReScore::Create(pDevice,score,D3DXVECTOR3(SCREEN_WIDTH/2,450.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f));

	//�t�F�[�h�̍쐬
	m_pFade=CFade::Create(pDevice,1);

	m_pFade->StartFade(FADE_OUT,50,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),CManager::GetSelectChar(0));

	return S_OK;
}
//=============================================================================
// �I��
//=============================================================================
void CVsend :: Uninit(void)
{
	//�T�E���h�擾�̍쐬
	CSound *pSound;
	pSound = CManager::GetSound();

	//�T�E���h�Đ��̍쐬
	pSound->Stop();

	//�V�[����S�ďI��
	Cform::ReleaseAll();
}
//=============================================================================
// �X�V
//=============================================================================
void CVsend :: Update(void)
{
	//�L�[�{�[�h�C���v�b�g�̎󂯎��
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//�t�F�[�h�̊J�n
	if(pInputKeyboard->GetKeyTrigger(DIK_RETURN)||pInputKeyboard->GetKeyTrigger(DIK_Z))
	{
		CSound *pSound;
		pSound = CManager::GetSound();
		//pSound->Play(SOUND_LABEL_SE_SELECT001);
		m_pFade->StartFade(FADE_IN,100,D3DXCOLOR(1.0f,1.0f,1.0f,0.0f),CManager::GetSelectChar(0));
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
void CVsend :: Draw(void)
{

}
/////////////EOF////////////
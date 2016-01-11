//=============================================================================
//
// MS_BuildFight [CTutorial.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#include "Tutorial.h"

#include "../Input.h"
#include "../Maneger.h"
#include "../Sound.h"

#include "../../module/etc/Fade.h"

#include "../../module/ui/CharPicture.h"
#include "../../module/ui/Effect.h"
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTutorial :: CTutorial(void)
{
	//m_pBackGround = NULL;
	m_pFade = NULL;
	m_pEffect[7] = { };
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTutorial :: ~CTutorial(void)
{
}

//=============================================================================
// ������
//=============================================================================
HRESULT CTutorial :: Init(LPDIRECT3DDEVICE9 pDevice)
{
	//�w�i�̍쐬
	//m_pBackGround=CBackGround::Create(pDevice,BACKGROUND_TUTORIAL);

	//�����̔z�u
	m_pEffect[0] = CEffect::Create(pDevice, Tutoriale, D3DXVECTOR3(650.0f, 375.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pEffect[2] = CEffect::Create(pDevice, Tutoriale, D3DXVECTOR3(650.0f, 375.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pEffect[3] = CEffect::Create(pDevice, Tutoriale, D3DXVECTOR3(650.0f, 375.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pEffect[1] = CEffect::Create(pDevice, Tutoriale, D3DXVECTOR3(650.0f, 375.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pEffect[4] = CEffect::Create(pDevice, Tutoriale, D3DXVECTOR3(650.0f, 375.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pEffect[5] = CEffect::Create(pDevice, Tutoriale, D3DXVECTOR3(650.0f, 375.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pEffect[6] = CEffect::Create(pDevice, Tutoriale, D3DXVECTOR3(650.0f, 375.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pEffect[7] = CEffect::Create(pDevice, Tutoriale, D3DXVECTOR3(650.0f, 375.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//�t�F�[�h�̍쐬
	m_pFade=CFade::Create(pDevice,1);

	//�T�E���h�擾�̍쐬
	CSound *pSound;
	pSound = CManager::GetSound();

	//�T�E���h�Đ��̍쐬
	//pSound->Play(SOUND_LABEL_BGM003);

	m_nCount=0;

	m_pFade->StartFade(FADE_OUT,50,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),CManager::GetSelectChar(0));

	return S_OK;
}
//=============================================================================
// �I��
//=============================================================================
void CTutorial :: Uninit(void)
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
void CTutorial :: Update(void)
{
	//�T�E���h�擾�̍쐬
	CSound *pSound;
	pSound = CManager::GetSound();

	//�L�[�{�[�h�C���v�b�g�̎󂯎��
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//�G���^�[�L�[�������ꂽ�ꍇ
	if(pInputKeyboard->GetKeyTrigger(DIK_RETURN)||pInputKeyboard->GetKeyTrigger(DIK_Z))
	{
		m_pEffect[m_nCount-1]->SetView(false);
		//pSound->Play(SOUND_LABEL_SE_SELECT000);
		if(m_nCount>=7)
		{
			//pSound->Play(SOUND_LABEL_SE_SELECT001);
			m_pFade->StartFade(FADE_IN,100,D3DXCOLOR(1.0f,1.0f,1.0f,0.0f),CManager::GetSelectChar(0));
		}else
		{
			m_nCount++;
		}
	}
	//�G�X�P�[�v�L�[�������ꂽ�ꍇ
	if(pInputKeyboard->GetKeyTrigger(DIK_ESCAPE))
	{
		m_pFade->StartFade(FADE_IN,100,D3DXCOLOR(1.0f,1.0f,1.0f,0.0f),CManager::GetSelectChar(0));
	}

	m_pEffect[m_nCount]->SetView(true);

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
void CTutorial :: Draw(void)
{
	//m_pBackGround->Draw();

	m_pEffect[0]->Draw();
	m_pEffect[2]->Draw();
	m_pEffect[3]->Draw();
	m_pEffect[1]->Draw();
	m_pEffect[4]->Draw();
	m_pEffect[5]->Draw();
	m_pEffect[6]->Draw();
	m_pEffect[7]->Draw();

	m_pFade->Draw();

}
/////////////EOF////////////
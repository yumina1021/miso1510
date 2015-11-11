//=============================================================================
//
// MS_BuildFight [CTitle.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#include "Title.h"
#include "../Input.h"
#include "../Maneger.h"
#include "../Sound.h"

#include "../../module/ui/BackGround.h"
#include "../../module/ui/CharPicture.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

#define MENU_X	(SCREEN_WIDTH/2)	//���j���[��X�ʒu
#define MENU_Y	(450.0f)			//���j���[��Y�ʒu

#define MENU_WIDTH	(400)			//���j���[�̉��T�C�Y
#define MENU_HEIGHT	(100)			//���j���[�̏c�T�C�Y

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTitle :: CTitle(void)
{
	m_pBackGround = NULL;
	m_pFade = NULL;
	m_pCharPicture[0] = { };
	m_pCharPicture[1] = { };
	m_pCharPicture[2] = { };
	m_pCharPicture[3] = { };
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTitle :: ~CTitle(void)
{
}

//=============================================================================
// ������
//=============================================================================
HRESULT CTitle :: Init(LPDIRECT3DDEVICE9 pDevice)
{
	//�w�i�̍쐬
	m_pBackGround=CBackGround::Create(pDevice,BACKGROUND_TITLE);

	//�����̔z�u
	m_pCharPicture[0] = CCharPicture::Create(pDevice, t_stert, D3DXVECTOR3(MENU_X, 450.0f, 0.0f), MENU_WIDTH, MENU_HEIGHT);
	m_pCharPicture[1] = CCharPicture::Create(pDevice, t_vs, D3DXVECTOR3(MENU_X, MENU_Y + 75.0f, 0.0f), MENU_WIDTH, MENU_HEIGHT);
	m_pCharPicture[2] = CCharPicture::Create(pDevice, t_tutorial, D3DXVECTOR3(MENU_X, MENU_Y + (75.0f * 2), 0.0f), MENU_WIDTH, MENU_HEIGHT);
	m_pCharPicture[3] = CCharPicture::Create(pDevice, t_end, D3DXVECTOR3(MENU_X, MENU_Y + (75.0f * 3), 0.0f), MENU_WIDTH, MENU_HEIGHT);

	//�t�F�[�h�̍쐬
	m_pFade=CFade::Create(pDevice,1);

	//�T�E���h�擾�̍쐬
	CSound *pSound;
	pSound = CManager::GetSound();

	//�T�E���h�Đ��̍쐬
	//pSound->Play(SOUND_LABEL_BGM000);

	m_bChangeFlag=false;
	m_nCursor=0;

	m_fDiffuse=1.0f;

	m_pFade->StartFade(FADE_OUT,50,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));

	return S_OK;
}
//=============================================================================
// �I��
//=============================================================================
void CTitle :: Uninit(void)
{
	//�T�E���h�擾�̍쐬
	CSound *pSound;
	pSound = CManager::GetSound();

	//�T�E���h�Đ��̍쐬
	//pSound->Stop();
	//�V�[����S�ďI��
	Cform::ReleaseAll();
}
//=============================================================================
// �X�V
//=============================================================================
void CTitle :: Update(void)
{
	KeyCommand();

	m_pCharPicture[m_nCursor]->SetDiffuse(m_fDiffuse,m_fDiffuse,m_fDiffuse,1.0f);

	//�t�F�[�h�C�����I�������
	if(m_pFade->GetFade()==FADE_IN_END)
	{
		if(m_nCursor==0||m_nCursor==1)
		{
			//���̃t�F�[�Y��ς���
			CScene::SetReplayFlag(false);
			CManager::SetAfterScene(PHASETYPE_SELECT);
		}else if(m_nCursor==2)
		{
			//���̃t�F�[�Y��ς���
			CManager::SetAfterScene(PHASETYPE_RESULT);
		}
	}
}
//=============================================================================
// �`��
//=============================================================================
void CTitle :: Draw(void)
{
	m_pBackGround->Draw();

	//����
	m_pCharPicture[0]->Draw();
	m_pCharPicture[1]->Draw();
	m_pCharPicture[2]->Draw();
	m_pCharPicture[3]->Draw();

	//�t�F�[�h
	m_pFade->Draw();

}
//=============================================================================
// ����
//=============================================================================
void CTitle::KeyCommand(void)
{

	//�T�E���h�擾�̍쐬
	CSound *pSound;
	pSound = CManager::GetSound();

	//�L�[�{�[�h�C���v�b�g�̎󂯎��
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//�G���^�[�L�[�������ꂽ�ꍇ
	if (pInputKeyboard->GetKeyTrigger(DIK_RETURN) || pInputKeyboard->GetKeyTrigger(DIK_Z))
	{
		//�J�[�\���������Ă���R�}���h�𔭓�
		switch (m_nCursor)
		{
			//�X�^�[�g
		case 0:	m_bChangeFlag = true;
			//pSound->Play(SOUND_LABEL_SE_SELECT001);
			if (m_pFade->GetPlayFade() == false)
			{
				m_pFade->StartFade(FADE_IN, 100, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
				CScene::SetVSFlag(false);
			}
			break;
			//VS
		case 1:	m_bChangeFlag = true;
			//pSound->Play(SOUND_LABEL_SE_SELECT001);
			if (m_pFade->GetPlayFade() == false)
			{
				m_pFade->StartFade(FADE_IN, 100, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
				CScene::SetVSFlag(true);
			}
			break;
			//�R���t�B�O
		case 2:	m_bChangeFlag = true;
			//pSound->Play(SOUND_LABEL_SE_SELECT001);
			if (m_pFade->GetPlayFade() == false)
			{
				m_pFade->StartFade(FADE_IN, 100, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			}
			break;
			//�G���h
		case 3:	m_bChangeFlag = false;
			//pSound->Play(SOUND_LABEL_SE_SELECT001);
			GameEnd();
			break;

		default: break;
		}
	}
	else if (m_bChangeFlag != true)
	{
		if (pInputKeyboard->GetKeyTrigger(DIK_W) || pInputKeyboard->GetKeyTrigger(DIK_UP))
		{
			m_pCharPicture[m_nCursor]->SetDiffuse(1.0f, 1.0f, 1.0f, 1.0f);
			m_nCursor--;
			//pSound->Play(SOUND_LABEL_SE_SELECT000);
			if (m_nCursor<0)
			{
				m_nCursor = 3;
			}
		}
		else if (pInputKeyboard->GetKeyTrigger(DIK_S) || pInputKeyboard->GetKeyTrigger(DIK_DOWN))
		{
			m_pCharPicture[m_nCursor]->SetDiffuse(1.0f, 1.0f, 1.0f, 1.0f);
			m_nCursor++;
			//pSound->Play(SOUND_LABEL_SE_SELECT000);
			if (m_nCursor>3)
			{
				m_nCursor = 0;
			}
		}
	}
	if (pInputKeyboard->GetKeyTrigger(DIK_F5))
	{
		if (CManager::Getnight0PlayFlag() == true)
		{
			CManager::Setnight0PlayFlag(false);
		}
		else
		{
			CManager::Setnight0PlayFlag(true);
		}
	}

	m_fDiffuse -= 0.01f;

	if (m_fDiffuse<0.5f)
	{
		m_fDiffuse = 1.0f;
	}
}
/////////////EOF////////////
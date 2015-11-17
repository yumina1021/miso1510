//=============================================================================
//
// MS_BuildFight [CGameClear.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#include "GameClear.h"

#include "../Input.h"
#include "../Maneger.h"
#include "../Sound.h"

#include "../../module/etc/Fade.h"

#include "../../module/ui/CharPicture.h"
#include "../../module/ui/Effect.h"
#include "../../module/ui/BackGround.h"
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
CBackGround *CGameClear::m_pBackGround = NULL;
CFade *CGameClear::m_pFade=NULL;
CEffect *CGameClear::m_pEffect[] = {};
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGameClear :: CGameClear(void)
{
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGameClear :: ~CGameClear(void)
{
}

//=============================================================================
// ������
//=============================================================================
HRESULT CGameClear :: Init(LPDIRECT3DDEVICE9 pDevice)
{
	//�w�i�̍쐬
	m_pBackGround=CBackGround::Create(pDevice,BACKGROUND_GAMECLEAR);

	//�����̔z�u
	m_pEffect[0] = CEffect::Create(pDevice, ready1, D3DXVECTOR3(650.0f, 375.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pEffect[1] = CEffect::Create(pDevice, ready1, D3DXVECTOR3(650.0f, 375.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_pEffect[0]->SetView(true);
	m_pEffect[1]->SetView(true);

	//�t�F�[�h�̍쐬
	m_pFade=CFade::Create(pDevice,1);

	//�T�E���h�擾�̍쐬
	CSound *pSound;
	pSound = CManager::GetSound();

	//�T�E���h�Đ��̍쐬
	//pSound->Play(SOUND_LABEL_BGM002);

	m_nCount=0;

	m_pFade->StartFade(FADE_OUT,50,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));

	return S_OK;
}
//=============================================================================
// �I��
//=============================================================================
void CGameClear :: Uninit(void)
{
	//�T�E���h�擾�̍쐬
	CSound *pSound;
	pSound = CManager::GetSound();

	//�T�E���h�Đ��̍쐬
	//pSound->Stop(SOUND_LABEL_BGM002);

	//�V�[����S�ďI��
	Cform::ReleaseAll();
}
//=============================================================================
// �X�V
//=============================================================================
void CGameClear :: Update(void)
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
		m_pEffect[0]->SetView(false);
		//pSound->Play(SOUND_LABEL_SE_SELECT000);

		if(m_nCount>=1)
		{
			//pSound->Play(SOUND_LABEL_SE_SELECT001);
			m_pFade->StartFade(FADE_IN,100,D3DXCOLOR(0.0f,0.0f,0.0f,0.0f));
		}else
		{
			m_nCount++;
		}
	}

	//�t�F�[�h�C�����I�������
	if(m_pFade->GetFade()==FADE_IN_END)
	{
		//���̃t�F�[�Y��ς���
		CScene::SetEnemy(3);
		CManager::SetAfterScene(PHASETYPE_GAME);
	}
}
//=============================================================================
// �`��
//=============================================================================
void CGameClear :: Draw(void)
{

}
/////////////EOF////////////
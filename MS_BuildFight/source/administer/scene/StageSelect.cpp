//=============================================================================
//
// MS_BuildFight [CStageSelect.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#include "StageSelect.h"

#include "../Input.h"
#include "../Maneger.h"
#include "../Sound.h"

#include "../../module/etc/Fade.h"
#include "../../module/ui/BackGround.h"
#include "../../module/ui/CharPicture.h"
#include "../../module/ui/Effect.h"

#include "../../administer/Debugproc.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
const float CURSOR_MOVE_COFF(10.0f);
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CStageSelect :: CStageSelect(void)
{

	m_pBackGround = NULL;
	m_pFade = NULL;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CStageSelect :: ~CStageSelect(void)
{
}

//=============================================================================
// ������
//=============================================================================
HRESULT CStageSelect :: Init(LPDIRECT3DDEVICE9 pDevice)
{
	//�w�i�̍쐬
	m_pBackGround=CBackGround::Create(pDevice,BACKGROUND_SELECT);

	//�t�F�[�h�̍쐬
	m_pFade=CFade::Create(pDevice,1);

	//�T�E���h�擾�̍쐬
	CSound *pSound;
	pSound = CManager::GetSound();

	//�T�E���h�Đ��̍쐬
	//pSound->Play(SOUND_LABEL_BGM004);

	m_bChangeFlag=false;
	m_nCursor=0;

	m_fDiffuse=1.0f;

	m_bVsSelectFlag = CScene::GetVSFlag();

	m_bTitleBackFlag=false;

	m_pFade->StartFade(FADE_OUT,50,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
	m_bSendData=false;
	m_bChangeFlag = false;
	return S_OK;
}
//=============================================================================
// �I��
//=============================================================================
void CStageSelect :: Uninit(void)
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
void CStageSelect :: Update(void)
{
	//�T�E���h�擾�̍쐬
	CSound *pSound;
	pSound = CManager::GetSound();	

	//�L�[�{�[�h�C���v�b�g�̎󂯎��
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	m_fDiffuse-=0.01f;

	if(m_fDiffuse<0.5f)
	{
		m_fDiffuse=1.0f;
	}

	UpdateFade();
	//�G���^�[�L�[�������ꂽ�ꍇ
	if ((pInputKeyboard->GetKeyTrigger(DIK_RETURN) && m_bChangeFlag == false))
	{

		// �J�ڏ���
		m_bChangeFlag = true;

		// �I�������L������ۑ�
		CScene::SetFrame(m_nCursor);
		//pSound->PlayVoice(m_nCursor,VOICE_LABEL_SE_START);

		if (m_bVsSelectFlag == false)
		{
			CScene::SetEnemy(rand() % 3);
			if (m_pFade->GetPlayFade() == false)
			{
				//pSound->Play(SOUND_LABEL_SE_SELECT001);
				m_pFade->StartFade(FADE_IN, 100, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			}
		}
	}

#ifdef _DEBUG


#endif


}
//=============================================================================
// �`��
//=============================================================================
void CStageSelect :: Draw(void)
{
	m_pBackGround->Draw();



	//�t�F�[�h�̍쐬
	m_pFade->Draw();
}
//=============================================================================
// �t�F�[�h�̍X�V
//=============================================================================
void CStageSelect::UpdateFade(void)
{
	if (m_bChangeFlag == true)
	{
		//pSound->Play(SOUND_LABEL_SE_SELECT002);
		m_pFade->StartFade(FADE_IN, 100, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_bChangeFlag = false;
	}

	//�t�F�[�h�C�����I�������
	if (m_pFade->GetFade() == FADE_IN_END)
	{
		if (m_bTitleBackFlag == false)
		{
			//���̃t�F�[�Y��ς���
			CManager::SetAfterScene(PHASETYPE_GAME);
		}
		else
		{
			//���̃t�F�[�Y��ς���
			CManager::SetAfterScene(PHASETYPE_TITLE);
		}
	}
}
//=============================================================================
// �J�[���ړ��ł̑I��
//=============================================================================
bool CStageSelect::HitChkRect(const D3DXVECTOR3& paramPos1,
							const D3DXVECTOR3& paramPos2,
							const D3DXVECTOR3& paramLen1,
							const D3DXVECTOR3& paramLen2){

	if (abs(paramPos1.x - paramPos2.x) < (paramLen1.x * 0.5f + paramLen2.x * 0.5f) //���̔���
		&& abs(paramPos1.y - paramPos2.y) < (paramLen1.y * 0.5f + paramLen2.y * 0.5f)) //�c�̔���
	{

		// ��������
		return true;

	}

	// �������ĂȂ�
	return false;

}
/////////////EOF////////////
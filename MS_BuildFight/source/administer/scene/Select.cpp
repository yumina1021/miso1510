//=============================================================================
//
// MS_BuildFight [CSelect.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#include "Select.h"

#include "../Input.h"
#include "../Maneger.h"
#include "../Sound.h"

#include "../../module/etc/Fade.h"
#include "../../module/ui/BackGround.h"
#include "../../module/ui/CharPicture.h"
#include "../../module/ui/Effect.h"
#include "../../module/ui/Button.h"
#include "../../module/ui/Cursor.h"

#include "../../administer/Debugproc.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CSelect :: CSelect(void):
m_nType(SELECT_TYPE::TYPE_BUTTON),
m_bChangeFlag(false),
m_nCursor(0),
m_bVsSelectFlag(CScene::GetVSFlag()),
m_bTitleBackFlag(false),
m_bSendData(false)
{

	m_pBackGround = NULL;
	m_pFade = NULL;
	m_pCharPicture[CHARCTER_TYPE::TYPE_MAX] = {};

}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSelect :: ~CSelect(void)
{
}

//=============================================================================
// ������
//=============================================================================
HRESULT CSelect :: Init(LPDIRECT3DDEVICE9 pDevice)
{
	//�w�i�̍쐬
	m_pBackGround=CBackGround::Create(pDevice,BACKGROUND_SELECT);

	//�����̔z�u
	m_pCharPicture[CHARCTER_TYPE::TYPE_1] = CButton::Create(pDevice, s_0, D3DXVECTOR3(325.0f, 187.5f, 0.0f), 650, 375);
	m_pCharPicture[CHARCTER_TYPE::TYPE_2] = CButton::Create(pDevice, s_1, D3DXVECTOR3(975.0f, 187.5f, 0.0f), 650, 375);
	m_pCharPicture[CHARCTER_TYPE::TYPE_3] = CButton::Create(pDevice, s_2, D3DXVECTOR3(325.0f, 562.5f, 0.0f), 650, 375);
	m_pCharPicture[CHARCTER_TYPE::TYPE_4] = CButton::Create(pDevice, s_3, D3DXVECTOR3(975.0f, 562.5f, 0.0f), 650, 375);
	m_pCursor = CCursor::Create(pDevice, s_4, D3DXVECTOR3(1000.0f, 600.0f, 0.0f), 128, 128);

	// �I����Ԃɂ��Ă���
	m_pCharPicture[m_nCursor]->SetButtonState(BUTTON_STATE::SELECTED);

	//�t�F�[�h�̍쐬
	m_pFade=CFade::Create(pDevice,1);
	m_pFade->StartFade(FADE_OUT, 50, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//�T�E���h�擾�̍쐬
	CSound *pSound;
	pSound = CManager::GetSound();

	//�T�E���h�Đ��̍쐬
	//pSound->Play(SOUND_LABEL_BGM004);

<<<<<<< HEAD
	m_bChangeFlag=false;
	m_nCursor=0;

	m_fDiffuse=1.0f;

	m_bVsSelectFlag = CScene::GetVSFlag();

	m_bTitleBackFlag=false;

	m_pFade->StartFade(FADE_OUT,50,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
	m_bSendData=false;
	m_bChangeFlag = false;
=======
>>>>>>> origin/sakai_work
	return S_OK;
}
//=============================================================================
// �I��
//=============================================================================
void CSelect :: Uninit(void)
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
void CSelect :: Update(void)
{
	//�T�E���h�擾�̍쐬
	CSound *pSound;
	pSound = CManager::GetSound();	

	// �ꎞ�I�ɕۑ�
	int tmpCursorOld = m_nCursor;

	//�L�[�{�[�h�C���v�b�g�̎󂯎��
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//F1�L�[�������ꂽ�ꍇ
	if (pInputKeyboard->GetKeyTrigger(DIK_1)
		&& m_bChangeFlag == false)
	{
		m_nType = SELECT_TYPE::TYPE_BUTTON;

	}
	else if (pInputKeyboard->GetKeyTrigger(DIK_2)
		&& m_bChangeFlag == false)
	{
		m_pCursor->SetTime(0.0f);
		m_nType = SELECT_TYPE::TYPE_CURSOR;

	}
	// �{�^���I��
	if (m_nType == SELECT_TYPE::TYPE_BUTTON)
	{
		SelectByButton();
<<<<<<< HEAD
=======
		m_pCursor->SyncCharPos(m_pCharPicture[m_nCursor]->GetPos());

>>>>>>> origin/sakai_work
	}
	// �J�[�\���ړ�
	else if (m_nType == SELECT_TYPE::TYPE_CURSOR)
	{
		SelectByCursor();

	}

	UpdateFade();

	// �Ⴄ�{�^���Ɉڂ�����
	if (tmpCursorOld != m_nCursor)
	{
		CButton::ChangeSelectButtonState(m_pCharPicture[tmpCursorOld], m_pCharPicture[m_nCursor]);

	}

#ifdef _DEBUG

	CDebugProc::Print("�I�𒆂̃{�^��:%d\n", m_nCursor);
	CDebugProc::Print("���[�h�I��:%d\n ��0:�{�^�� 1:�J�[�\��", m_nType);

#endif


}
//=============================================================================
// �`��
//=============================================================================
void CSelect :: Draw(void)
{
	m_pBackGround->Draw();

	for (int i = 0; i < CHARCTER_TYPE::TYPE_MAX; i++)
	{
		m_pCharPicture[i]->Draw();
	}

	m_pCursor->Draw();

	//�t�F�[�h�̍쐬
	m_pFade->Draw();
}
//=============================================================================
// �t�F�[�h�̍X�V
//=============================================================================
void CSelect::UpdateFade(void)
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
			CManager::SetAfterScene(PHASETYPE_STAGE_SELECT);
		}
		else
		{
			//���̃t�F�[�Y��ς���
			CManager::SetAfterScene(PHASETYPE_TITLE);
		}
	}
}
//=============================================================================
// �L�[�{�[�h�ł̑I��
//=============================================================================
void CSelect::SelectByButton(void)
{

	//�L�[�{�[�h�C���v�b�g�̎󂯎��
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//�G���^�[�L�[�������ꂽ�ꍇ
	if ((pInputKeyboard->GetKeyTrigger(DIK_RETURN) && m_bChangeFlag == false))
	{

		m_pCursor->SetTime(0.0f);
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
	else if (m_bChangeFlag != true)
	{
		if (pInputKeyboard->GetKeyTrigger(DIK_W) || pInputKeyboard->GetKeyTrigger(DIK_UP))
		{
			m_pCursor->SetTime(0.0f);

			// �I����Ԃ������
			//pSound->Play(SOUND_LABEL_SE_SELECT000);

			// �e�z�u�ɂ���Ĉړ�����
			if (m_nCursor == TYPE_1
				|| m_nCursor == TYPE_2)
			{

				m_nCursor += 2;

			}
			else
			{
				m_nCursor -= 2;

			}

		}
		else if (pInputKeyboard->GetKeyTrigger(DIK_S) || pInputKeyboard->GetKeyTrigger(DIK_DOWN))
		{
			m_pCursor->SetTime(0.0f);

			//pSound->Play(SOUND_LABEL_SE_SELECT000);

			// �e�z�u�ɂ���Ĉړ�����
			if (m_nCursor == TYPE_1
				|| m_nCursor == TYPE_2){

				m_nCursor += 2;

			}
			else
			{

				m_nCursor -= 2;

			}
		}
		if (pInputKeyboard->GetKeyTrigger(DIK_A) || pInputKeyboard->GetKeyTrigger(DIK_LEFT))
		{
			m_pCursor->SetTime(0.0f);

			//pSound->Play(SOUND_LABEL_SE_SELECT000);

			// �e�z�u�ɂ���Ĉړ�����
			if (m_nCursor == TYPE_1
				|| m_nCursor == TYPE_3)
			{

				m_nCursor++;

			}
			else
			{
				m_nCursor--;

			}

		}
		else if (pInputKeyboard->GetKeyTrigger(DIK_D) || pInputKeyboard->GetKeyTrigger(DIK_RIGHT))
		{
			m_pCursor->SetTime(0.0f);
			//pSound->Play(SOUND_LABEL_SE_SELECT000);

			// �e�z�u�ɂ���Ĉړ�����
			if (m_nCursor == TYPE_1
				|| m_nCursor == TYPE_3)
			{

				m_nCursor++;

			}
			else
			{
				m_nCursor--;

			}
		}
	}
}
//=============================================================================
// �J�[���ړ��ł̑I��
//=============================================================================
void CSelect::SelectByCursor(void){

	// �ϐ���`
	D3DXVECTOR3 tmpCurPos = m_pCursor->GetPos();
	D3DXVECTOR3 tmpCharPos(0.0f, 0.0f, 0.0f);
	bool tmpOnFlg(false);
	D3DXVECTOR3 tmpCursorLen(0.0f, 0.0f, 0.0f);

	//�L�[�{�[�h�C���v�b�g�̎󂯎��
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//���ׂẴL�������ڂ�ΏۂɌ���
	for (int i = 0; i < CHARCTER_TYPE::TYPE_MAX; i++)
	{

		// ���W�̎擾
		tmpCharPos = m_pCharPicture[i]->GetPos();

		// ��`�ł̂����蔻��
		if (CCursor::HitChkRect(tmpCurPos, tmpCharPos, m_pCursor->GetLen(), m_pCharPicture[i]->GetLen()))
		{

			// �������Ă��邱�Ƃ��L�^
			tmpOnFlg = true;
		
			// �I�𒆂̃J�[�\���̍X�V
			m_nCursor = i;

			break;
		}
		else{


		}
	}
<<<<<<< HEAD
	// ���N���b�N������
	if (pInputKeyboard->GetKeyTrigger(DIK_RETURN))
=======
	// ����{�^������������
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
>>>>>>> origin/sakai_work
	{

		// �ǂꂩ�̃L�����{�^���ɏ�������Ă�����
		if (tmpOnFlg)
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

	}// if
	else if (m_bChangeFlag != true)
	{
		m_pCursor->MoveByKeybord();
	}


#ifdef _DEBUG

	CDebugProc::Print("�}�E�X���WX:%f\n", tmpCurPos.x);
	CDebugProc::Print("�}�E�X���WY:%f\n", tmpCurPos.y);

#endif

}// SelectByCursor


/////////////EOF////////////
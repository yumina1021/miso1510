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

#include "../wiicon/wiimote.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
const int MAX_PLAYER(2);
const float CHAR_BUTTON_WIDTH(650.0f);
const float CHAR_BUTTON_HEIGHT(375.0f);

const float CURSOR_WIDTH(128.0f);
const float CURSOR_HEIGHT(128.0f);
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CSelect :: CSelect(void):
m_nType(SELECT_TYPE::TYPE_BUTTON),
m_bChangeFlag(false),
m_bVsSelectFlag(false),
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
	m_pCharPicture[CHARCTER_TYPE::TYPE_1] = CButton::Create(pDevice, s_0, D3DXVECTOR3(325.0f, 187.5f, 0.0f), CHAR_BUTTON_WIDTH, CHAR_BUTTON_HEIGHT);
	m_pCharPicture[CHARCTER_TYPE::TYPE_2] = CButton::Create(pDevice, s_1, D3DXVECTOR3(975.0f, 187.5f, 0.0f), CHAR_BUTTON_WIDTH, CHAR_BUTTON_HEIGHT);
	m_pCharPicture[CHARCTER_TYPE::TYPE_3] = CButton::Create(pDevice, s_2, D3DXVECTOR3(325.0f, 562.5f, 0.0f), CHAR_BUTTON_WIDTH, CHAR_BUTTON_HEIGHT);
	m_pCharPicture[CHARCTER_TYPE::TYPE_4] = CButton::Create(pDevice, s_3, D3DXVECTOR3(975.0f, 562.5f, 0.0f), CHAR_BUTTON_WIDTH, CHAR_BUTTON_HEIGHT);
	m_pLogo = CButton::Create(pDevice, s_6, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), 900, 100);

	m_Select[0].pCursor = CCursor::Create(pDevice, s_4, D3DXVECTOR3(1000.0f, 600.0f, 0.0f), CURSOR_WIDTH, CURSOR_HEIGHT);
	m_Select[1].pCursor = CCursor::Create(pDevice, s_5, D3DXVECTOR3(200.0f, 600.0f, 0.0f), CURSOR_WIDTH, CURSOR_HEIGHT);

	m_OnCursorPos[CHARCTER_TYPE::TYPE_1] = D3DXVECTOR3(587.0f, 310.0f, 0.0f);
	m_OnCursorPos[CHARCTER_TYPE::TYPE_2] = D3DXVECTOR3(715.0f, 310.0f, 0.0f);
	m_OnCursorPos[CHARCTER_TYPE::TYPE_3] = D3DXVECTOR3(587.0f, 450.0f, 0.0f);
	m_OnCursorPos[CHARCTER_TYPE::TYPE_4] = D3DXVECTOR3(715.0f, 450.0f, 0.0f);
	m_Select[0].nSelect = 0;
	m_Select[1].nSelect = 1;

	m_Select[0].bDecisionFlg = false;
	m_Select[1].bDecisionFlg = false;

	// �I����Ԃɂ��Ă���
	m_pCharPicture[m_Select[0].nSelect]->SetButtonState(BUTTON_STATE::SELECTED);
	m_pCharPicture[m_Select[1].nSelect]->SetButtonState(BUTTON_STATE::SELECTED);

	//�t�F�[�h�̍쐬
	m_pFade=CFade::Create(pDevice,1);
	m_pFade->StartFade(FADE_OUT, 50, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),CManager::GetSelectChar(0));

	//�T�E���h�擾�̍쐬
	CSound *pSound;
	pSound = CManager::GetSound();

	//�T�E���h�Đ��̍쐬
	//pSound->Play(SOUND_LABEL_BGM004);

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
	int tmpCursorOld[2];

	for (int i = 0; i < MAX_PLAYER; i++)
	{

		tmpCursorOld[i] = m_Select[i].nSelect;

	}

	UpdateFade();

	//�L�[�{�[�h�C���v�b�g�̎󂯎��
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	////F1�L�[�������ꂽ�ꍇ
	//if (pInputKeyboard->GetKeyTrigger(DIK_1)
	//	&& m_bChangeFlag == false)
	//{
	//	m_nType = SELECT_TYPE::TYPE_BUTTON;

	//}
	//else if (pInputKeyboard->GetKeyTrigger(DIK_2)
	//	&& m_bChangeFlag == false)
	//{
	//	m_pCursor->SetTime(0.0f);
	//	m_nType = SELECT_TYPE::TYPE_CURSOR;

	//}
	// �{�^���I��
	if (m_nType == SELECT_TYPE::TYPE_BUTTON)
	{
		// 1P�̑���
		SelectByKeyboardPlayer1();
		m_Select[0].pCursor->SyncCharPos(m_OnCursorPos[m_Select[0].nSelect]);

		// 2P�̑���
		SelectByKeyboardPlayer2();
		m_Select[1].pCursor->SyncCharPos(m_OnCursorPos[m_Select[1].nSelect]);

		
	}
	// �J�[�\���ړ�
	else if (m_nType == SELECT_TYPE::TYPE_CURSOR)
	{
		// �Ƃ肠�����R�����g�A�E�g�Ō���ǂ����邩���߂�
		//SelectByCursor();

	}

	// �Ⴄ�{�^���Ɉڂ�����
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		if (tmpCursorOld[i] != m_Select[i].nSelect)
		{
			CButton::ChangeSelectButtonState(m_pCharPicture[tmpCursorOld[i]], m_pCharPicture[m_Select[i].nSelect]);

		}

		// �I����Ԃɂ��Ă���
		m_pCharPicture[m_Select[i].nSelect]->SetButtonState(BUTTON_STATE::SELECTED);

	}
#ifdef _DEBUG

	CDebugProc::Print("�v���C���[�I�𒆂̃{�^��:%d\n", m_Select[0].nSelect);
	CDebugProc::Print("�I�𒆂̃{�^��:%d\n", m_Select[1].nSelect);
	CDebugProc::Print("�v���C���[1�͂v�`�r�c�ňړ��łd�m�s�d�q�Ō���\n");
	CDebugProc::Print("�v���C���[2�́��������ňړ��łr�d�k�d�b�s�Ō���\n");

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

	// 
	for (int i = 0; i < MAX_CURSOR; i++)
	{

		m_Select[i].pCursor->Draw();

	}

	m_pLogo->Draw();

	//�t�F�[�h�̍쐬
	m_pFade->Draw();
}
//=============================================================================
// �t�F�[�h�̍X�V
//=============================================================================
void CSelect::UpdateFade(void)
{
	//if (m_bChangeFlag == true)
	//{
	//	//pSound->Play(SOUND_LABEL_SE_SELECT002);
	//	m_pFade->StartFade(FADE_IN, 100, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f),CManager::GetSelectChar(0));
	//	m_bChangeFlag = false;
	//}

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
void CSelect::SelectByKeyboardPlayer2(void)
{

	// Wii�R���̎擾
	WiiRemote* pTmpPad = CManager::GetWii(1);

	// 
	if (m_bChangeFlag){ return; }

	//�L�[�{�[�h�C���v�b�g�̎󂯎��
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//�G���^�[�L�[�������ꂽ�ꍇ
	if ((pInputKeyboard->GetKeyTrigger(DIK_SPACE)) || pTmpPad->GetKeyTrigger(WII_BUTTOM_A))
	{

		// �I�����ꂽ�ꍇ�̓X�L�b�v
		if (m_Select[1].bDecisionFlg){ return; }

		// ��`�ł̂����蔻��
		if (CCursor::HitChkRect(m_Select[1].pCursor->GetPos(),
			m_pCharPicture[m_Select[1].nSelect]->GetPos(),
			m_Select[1].pCursor->GetLen(),
			m_pCharPicture[m_Select[1].nSelect]->GetLen()))
		{

			if ((m_Select[0].bDecisionFlg
				&& m_Select[0].nSelect != m_Select[1].nSelect)
				|| !m_Select[0].bDecisionFlg)
			{

				m_Select[1].pCursor->SetTime(0.0f);
				CheckSelectAllCorsor(1);

				//pSound->PlayVoice(m_Select[1].nSelect,VOICE_LABEL_SE_START);

			}

		}



	}
	else if (pInputKeyboard->GetKeyTrigger(DIK_UP) || pTmpPad->GetKeyTrigger(WII_BUTTOM_UP))
	{
		m_Select[1].pCursor->SetTime(0.0f);

		// �I����Ԃ������
		//pSound->Play(SOUND_LABEL_SE_SELECT000);

		// �e�z�u�ɂ���Ĉړ�����
		if (m_Select[1].nSelect == TYPE_1
			|| m_Select[1].nSelect == TYPE_2)
		{

			m_Select[1].nSelect += 2;

		}
		else
		{
			m_Select[1].nSelect -= 2;

		}

	}
	else if (pInputKeyboard->GetKeyTrigger(DIK_DOWN) || pTmpPad->GetKeyTrigger(WII_BUTTOM_DOWN))
	{
		m_Select[1].pCursor->SetTime(0.0f);

		//pSound->Play(SOUND_LABEL_SE_SELECT000);

		// �e�z�u�ɂ���Ĉړ�����
		if (m_Select[1].nSelect == TYPE_1
			|| m_Select[1].nSelect == TYPE_2){

			m_Select[1].nSelect += 2;

		}
		else
		{

			m_Select[1].nSelect -= 2;

		}
	}
	else if (pInputKeyboard->GetKeyTrigger(DIK_LEFT) || pTmpPad->GetKeyTrigger(WII_BUTTOM_LEFT))
	{
		m_Select[1].pCursor->SetTime(0.0f);

		//pSound->Play(SOUND_LABEL_SE_SELECT000);

		// �e�z�u�ɂ���Ĉړ�����
		if (m_Select[1].nSelect == TYPE_1
			|| m_Select[1].nSelect == TYPE_3)
		{

			m_Select[1].nSelect++;

		}
		else
		{
			m_Select[1].nSelect--;

		}

	}
	else if (pInputKeyboard->GetKeyTrigger(DIK_RIGHT) || pTmpPad->GetKeyTrigger(WII_BUTTOM_RIGHT))
	{
		m_Select[1].pCursor->SetTime(0.0f);
		//pSound->Play(SOUND_LABEL_SE_SELECT000);

		// �e�z�u�ɂ���Ĉړ�����
		if (m_Select[1].nSelect == TYPE_1
			|| m_Select[1].nSelect == TYPE_3)
		{

			m_Select[1].nSelect++;

		}
		else
		{
			m_Select[1].nSelect--;

		}
	}
}
//=============================================================================
// �L�[�{�[�h�ł̑I��
//=============================================================================
void CSelect::SelectByKeyboardPlayer1(void)
{

	// Wii�R���̎擾
	WiiRemote* pTmpPad = CManager::GetWii(0);

	// 
	if (m_bChangeFlag){ return; }

	//�L�[�{�[�h�C���v�b�g�̎󂯎��
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//�G���^�[�L�[�������ꂽ�ꍇ
	if ((pInputKeyboard->GetKeyTrigger(DIK_RETURN)) || pTmpPad->GetKeyTrigger(WII_BUTTOM_A))
	{

		// �I�����ꂽ�ꍇ�̓X�L�b�v
		if (m_Select[0].bDecisionFlg){ return; }

		// ��`�ł̂����蔻��
		if (CCursor::HitChkRect(m_Select[0].pCursor->GetPos(),
			m_pCharPicture[m_Select[0].nSelect]->GetPos(),
			m_Select[0].pCursor->GetLen(),
			m_pCharPicture[m_Select[0].nSelect]->GetLen()))
		{

			if ((m_Select[1].bDecisionFlg
				&& m_Select[1].nSelect != m_Select[0].nSelect)
				|| !m_Select[1].bDecisionFlg)
			{
				m_Select[0].pCursor->SetTime(0.0f);
				CheckSelectAllCorsor(0);

				//pSound->PlayVoice(m_Select[0].nSelect,VOICE_LABEL_SE_START);
			}
		}


		
	}
	else if (pInputKeyboard->GetKeyTrigger(DIK_W) || pTmpPad->GetKeyTrigger(WII_BUTTOM_UP))
	{
		m_Select[0].pCursor->SetTime(0.0f);

		// �I����Ԃ������
		//pSound->Play(SOUND_LABEL_SE_SELECT000);

		// �e�z�u�ɂ���Ĉړ�����
		if (m_Select[0].nSelect == TYPE_1
			|| m_Select[0].nSelect == TYPE_2)
		{

			m_Select[0].nSelect += 2;

		}
		else
		{
			m_Select[0].nSelect -= 2;

		}

	}
	else if (pInputKeyboard->GetKeyTrigger(DIK_S) || pTmpPad->GetKeyTrigger(WII_BUTTOM_DOWN))
	{
		m_Select[0].pCursor->SetTime(0.0f);

		//pSound->Play(SOUND_LABEL_SE_SELECT000);

		// �e�z�u�ɂ���Ĉړ�����
		if (m_Select[0].nSelect == TYPE_1
			|| m_Select[0].nSelect == TYPE_2){

			m_Select[0].nSelect += 2;

		}
		else
		{

			m_Select[0].nSelect -= 2;

		}
	}
	else if (pInputKeyboard->GetKeyTrigger(DIK_A) || pTmpPad->GetKeyTrigger(WII_BUTTOM_LEFT))
	{
		m_Select[0].pCursor->SetTime(0.0f);

		//pSound->Play(SOUND_LABEL_SE_SELECT000);

		// �e�z�u�ɂ���Ĉړ�����
		if (m_Select[0].nSelect == TYPE_1
			|| m_Select[0].nSelect == TYPE_3)
		{

			m_Select[0].nSelect++;

		}
		else
		{
			m_Select[0].nSelect--;

		}

	}
	else if (pInputKeyboard->GetKeyTrigger(DIK_D) || pTmpPad->GetKeyTrigger(WII_BUTTOM_RIGHT))
	{
		m_Select[0].pCursor->SetTime(0.0f);
		//pSound->Play(SOUND_LABEL_SE_SELECT000);

		// �e�z�u�ɂ���Ĉړ�����
		if (m_Select[0].nSelect == TYPE_1
			|| m_Select[0].nSelect == TYPE_3)
		{

			m_Select[0].nSelect++;

		}
		else
		{
			m_Select[0].nSelect--;

		}
	}
}
//=============================================================================
// �S�Ẵv���C���[���L���������肵�����ǂ����̃t���O
//=============================================================================
void CSelect::CheckSelectAllCorsor(int nParamDecisionCursor){

	// �S�Ẵv���C���[���I��������������
	if (m_Select[0].bDecisionFlg
		|| m_Select[1].bDecisionFlg)
	{
		// �J�ڏ���
		m_bChangeFlag = true;

		// �e�L�����N�^�[�̌���
		CManager::SetSelectChar(0, m_Select[0].nSelect);
		CManager::SetSelectChar(1, m_Select[1].nSelect);

		// �I�������L������ۑ�
		m_pFade->StartFade(FADE_IN, 100, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f),CManager::GetSelectChar(0));

	}
	else
	{
		m_Select[nParamDecisionCursor].bDecisionFlg = true;

	}

}
//=============================================================================
// �J�[���ړ��ł̑I��
// �����Ή��̓}�E�X�ł͓���̂łƂ肠�����R�����g�A�E�g
//=============================================================================
void CSelect::SelectByCursor(void){

//	// �ϐ���`
//	D3DXVECTOR3 tmpCurPos[MAX_CURSOR];
//	D3DXVECTOR3 tmpCharPos(0.0f, 0.0f, 0.0f);
//	bool tmpOnFlg(false);
//	D3DXVECTOR3 tmpCursorLen(0.0f, 0.0f, 0.0f);
//
//	tmpCurPos[0] = m_Select[0].pCursor->GetPos();
//	tmpCurPos[1] = m_Select[1].pCursor->GetPos();
//
//	//�L�[�{�[�h�C���v�b�g�̎󂯎��
//	CInputKeyboard *pInputKeyboard;
//	pInputKeyboard = CManager::GetInputKeyboard();
//
//	//���ׂẴL�������ڂ�ΏۂɌ���
//	for (int i = 0; i < CHARCTER_TYPE::TYPE_MAX; i++)
//	{
//
//		// ���W�̎擾
//		tmpCharPos = m_pCharPicture[i]->GetPos();
//
//		// ��`�ł̂����蔻��
//		if (CCursor::HitChkRect(tmpCurPos, tmpCharPos, m_pCursor->GetLen(), m_pCharPicture[i]->GetLen()))
//		{
//
//			// �������Ă��邱�Ƃ��L�^
//			tmpOnFlg = true;
//		
//			// �I�𒆂̃J�[�\���̍X�V
//			m_Select[0].nSelect = i;
//
//			break;
//		}
//		else{
//
//
//		}
//	}
//	// ����{�^������������
//	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
//	{
//
//		// �ǂꂩ�̃L�����{�^���ɏ�������Ă�����
//		if (tmpOnFlg)
//		{
//			// �J�ڏ���
//			m_bChangeFlag = true;
//
//			// �I�������L������ۑ�
//			CScene::SetFrame(m_Select[0].nSelect);
//			//pSound->PlayVoice(m_Select[0].nSelect,VOICE_LABEL_SE_START);
//
//			if (m_bVsSelectFlag == false)
//			{
//				CScene::SetEnemy(rand() % 3);
//				if (m_pFade->GetPlayFade() == false)
//				{
//					//pSound->Play(SOUND_LABEL_SE_SELECT001);
//					m_pFade->StartFade(FADE_IN, 100, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f),CManager::GetSelectChar(0));
//				}
//			}
//		}
//
//	}// if
//	else if (m_bChangeFlag != true)
//	{
//		m_pCursor->MoveByKeybord();
//	}
//
//
//#ifdef _DEBUG
//
//	CDebugProc::Print("�}�E�X���WX:%f\n", tmpCurPos.x);
//	CDebugProc::Print("�}�E�X���WY:%f\n", tmpCurPos.y);
//
//#endif

}// SelectByCursor

/////////////EOF////////////
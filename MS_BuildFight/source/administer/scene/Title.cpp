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
#include "../../module/ui/Button.h"
#include "../../module/ui/Cursor.h"

#include "../../administer/Debugproc.h"

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
CTitle :: CTitle(void) : 
m_bChangeFlag(false),
m_nCursor(GAME_START),
m_fDiffuse(1.0f),
m_nType(SELECT_TYPE::TYPE_BUTTON)
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
	m_pCharPicture[GAME_START] = CButton::Create(pDevice, t_stert, D3DXVECTOR3(MENU_X, 450.0f, 0.0f), MENU_WIDTH, MENU_HEIGHT);
	m_pCharPicture[VS_MODE] = CButton::Create(pDevice, t_vs, D3DXVECTOR3(MENU_X, MENU_Y + 75.0f, 0.0f), MENU_WIDTH, MENU_HEIGHT);
	m_pCharPicture[TUTORIAL] = CButton::Create(pDevice, t_tutorial, D3DXVECTOR3(MENU_X, MENU_Y + (75.0f * 2), 0.0f), MENU_WIDTH, MENU_HEIGHT);
	m_pCharPicture[GAME_END] = CButton::Create(pDevice, t_end, D3DXVECTOR3(MENU_X, MENU_Y + (75.0f * 3), 0.0f), MENU_WIDTH, MENU_HEIGHT);
	m_pCursor = CCursor::Create(pDevice, s_4, D3DXVECTOR3(1000.0f, 600.0f, 0.0f), 32, 32);

	// �I����Ԃɂ��Ă���
	m_pCharPicture[m_nCursor]->SetButtonState(BUTTON_STATE::SELECTED);

	//�t�F�[�h�̍쐬
	m_pFade=CFade::Create(pDevice,1);

	//�T�E���h�擾�̍쐬
	CSound *pSound;
	pSound = CManager::GetSound();

	//�T�E���h�Đ��̍쐬
	//pSound->Play(SOUND_LABEL_BGM000);

	
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
	//�L�[�{�[�h�C���v�b�g�̎󂯎��
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();
	
	// �ꎞ�I�ɕۑ�
	int tmpCursorOld = m_nCursor;

	UpdateFade();

	// F1�L�[�������ꂽ�ꍇ
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
		KeyCommand();
		m_pCursor->SyncCharPos(m_pCharPicture[m_nCursor]->GetPos());

	}
	// �J�[�\���ړ�
	else if (m_nType == SELECT_TYPE::TYPE_CURSOR)
	{
			SelectByCursor();
	}

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
void CTitle :: Draw(void)
{
	m_pBackGround->Draw();
	m_pCursor->Draw();
	//����
	for (int i = 0; i < MAX; i++)
	{

		m_pCharPicture[i]->Draw();

	}

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
	if (pInputKeyboard->GetKeyTrigger(DIK_RETURN))
	{

		ChangeState();

	}
	else if (m_bChangeFlag != true)
	{

		if (pInputKeyboard->GetKeyTrigger(DIK_W) || pInputKeyboard->GetKeyTrigger(DIK_UP))
		{
			m_nCursor--;
			//pSound->Play(SOUND_LABEL_SE_SELECT000);
			if (m_nCursor < GAME_START)
			{
				m_nCursor = GAME_END;
			}

		}
		else if (pInputKeyboard->GetKeyTrigger(DIK_S) || pInputKeyboard->GetKeyTrigger(DIK_DOWN))
		{
			m_nCursor++;
			//pSound->Play(SOUND_LABEL_SE_SELECT000);

			if (m_nCursor > GAME_END)
			{
				m_nCursor = GAME_START;
			}
		}
	}

}
//=============================================================================
// �J�[���ړ��ł̑I��
//=============================================================================
void CTitle::SelectByCursor(void){

	// �ϐ���`
	D3DXVECTOR3 tmpCurPos = m_pCursor->GetPos();
	D3DXVECTOR3 tmpCharPos(0.0f, 0.0f, 0.0f);
	bool tmpOnFlg(false);
	D3DXVECTOR3 tmpCursorLen(0.0f, 0.0f, 0.0f);

	//�L�[�{�[�h�C���v�b�g�̎󂯎��
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//���ׂẴL�������ڂ�ΏۂɌ���
	for (int i = 0; i < MAX; i++)
	{

		// ���W�̎擾
		tmpCharPos = m_pCharPicture[i]->GetPos();

		// ��`�ł̂����蔻��
		if (CCursor::HitChkRect(tmpCurPos, tmpCharPos, m_pCursor->GetLen(), m_pCharPicture[i]->GetLen()))
		{

			// �������Ă��邱�Ƃ��L�^
			tmpOnFlg = true;

			// �I����Ԃ������
			m_pCharPicture[m_nCursor]->SetButtonState(BUTTON_STATE::PUSH_OFF);

			// �I�𒆂̃J�[�\���̍X�V
			m_nCursor = i;

			// �I����Ԃɂ��Ă���
			m_pCharPicture[m_nCursor]->SetButtonState(BUTTON_STATE::SELECTED);

			break;
		}
		else{


		}
	}
	// ����{�^������������
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{

		ChangeState();

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
//=============================================================================
// ��Ԃ̑J��
//=============================================================================
void CTitle::ChangeState(){

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
//=============================================================================
// 
//=============================================================================
void CTitle::UpdateFade(void)
{

	//�t�F�[�h�C�����I�������
	if (m_pFade->GetFade() == FADE_IN_END)
	{
		if (m_nCursor == 0 || m_nCursor == 1)
		{
			//���̃t�F�[�Y��ς���
			CScene::SetReplayFlag(false);
			CManager::SetAfterScene(PHASETYPE_SELECT);
		}
		else if (m_nCursor == 2)
		{
			//���̃t�F�[�Y��ς���
			CManager::SetAfterScene(PHASETYPE_TUTRIAL);
		}
	}
}
/////////////EOF////////////
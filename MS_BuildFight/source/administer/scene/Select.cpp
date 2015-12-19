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
#include "../../module/etc/Camera.h"

#include "../../module/field/Domeunder.h"
#include "../../module/field/Dome.h"

#include "../../form/form3D.h"
#include "../../form/formX.h"
#include "../../module/robot/PlayerM.h"

#include "../../administer/Debugproc.h"

#include "../wiicon/wiimote.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
const float CHAR_BUTTON_WIDTH(300.0f);
const float CHAR_BUTTON_HEIGHT(162.0f);

const float CHAR_NAME_WIDTH(325.0f);
const float CHAR_NAME_HEIGHT(187.5f);

const float CURSOR_WIDTH(100.0f);
const float CURSOR_HEIGHT(100.0f);

const float CAMERA_POS_X(0.0f);
const float CAMERA_POS_Y(0.0f);
const float CAMERA_POS_Z(-200.0f);
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CSelect::CSelect(void) :
m_nType(SELECT_TYPE::TYPE_BUTTON),
m_bChangeFlag(false),
m_bVsSelectFlag(false),
m_bTitleBackFlag(false),
m_bSendData(false)
{

	m_pBackGround = NULL;
	m_pFade = NULL;
	m_pCharPicture[CHARCTER_TYPE::TYPE_MAX] = {};

	// �J�����̎擾
	CCamera* pTmpCamera = CManager::GetCamera();

	pTmpCamera->SetPosP(D3DXVECTOR3(CAMERA_POS_X, CAMERA_POS_Y, CAMERA_POS_Z));

	pTmpCamera->SetRotCamera(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pTmpCamera->SetPosR(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
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
HRESULT CSelect::Init(LPDIRECT3DDEVICE9 pDevice)
{
	LPSTR pModName[CHARCTER_TYPE::TYPE_MAX]
	{

		"data/MODEL/stage1.x",
			"data/MODEL/stage2.x",
			"data/MODEL/stage3.x",
			"data/MODEL/stage4.x",


	};

	LPSTR pCharNameTex[CHARCTER_TYPE::TYPE_MAX]
	{

		"data/TEXTURE/CharcterName1.png",
			"data/TEXTURE/CharcterName2.png",
			"data/TEXTURE/CharcterName3.png",
			"data/TEXTURE/CharcterName4.png",


	};

	//��̍쐬
	m_pDome = CDome::Create(pDevice, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//��̍쐬
	m_pDome2 = CDomeU::Create(pDevice, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//�T�E���h�擾�̍쐬
	CSound *pSound;
	pSound = CManager::GetSound();

	//�T�E���h�Đ��̍쐬
	//pSound->Play(SOUND_LABEL_BGM004);

	//�w�i�̍쐬
	m_pBackGround = Cform3D::Create(pDevice, "data/TEXTURE/Select.png", D3DXVECTOR3(0.0f, 0.0f, 406.0f), D3DXVECTOR3(-D3DX_PI / 2.0f, 0.0f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT);
	m_pBackGround->SetDiffuse(1.0f, 1.0f, 1.0f, 0.6f);

	float fScreenWidthHalf((float)SCREEN_WIDTH / 2.0f);
	float fScreenHeightHalf((float)SCREEN_HEIGHT / 2.0f);
	float fCharPicWidthHalf(CHAR_BUTTON_WIDTH / 2.0f);
	float fCharPicHeightHalf(CHAR_BUTTON_HEIGHT / 2.0f);

	// �L�����摜
	m_pCharPicture[CHARCTER_TYPE::TYPE_1] = CButton::Create(pDevice, s_0, D3DXVECTOR3(fScreenWidthHalf - fCharPicWidthHalf, fScreenHeightHalf - fCharPicHeightHalf, 0.0f), CHAR_BUTTON_WIDTH, CHAR_BUTTON_HEIGHT);
	m_pCharPicture[CHARCTER_TYPE::TYPE_2] = CButton::Create(pDevice, s_1, D3DXVECTOR3(fScreenWidthHalf + fCharPicWidthHalf, fScreenHeightHalf - fCharPicHeightHalf, 0.0f), CHAR_BUTTON_WIDTH, CHAR_BUTTON_HEIGHT);
	m_pCharPicture[CHARCTER_TYPE::TYPE_3] = CButton::Create(pDevice, s_2, D3DXVECTOR3(fScreenWidthHalf - fCharPicWidthHalf, fScreenHeightHalf + fCharPicHeightHalf, 0.0f), CHAR_BUTTON_WIDTH, CHAR_BUTTON_HEIGHT);
	m_pCharPicture[CHARCTER_TYPE::TYPE_4] = CButton::Create(pDevice, s_3, D3DXVECTOR3(fScreenWidthHalf + fCharPicWidthHalf, fScreenHeightHalf + fCharPicHeightHalf, 0.0f), CHAR_BUTTON_WIDTH, CHAR_BUTTON_HEIGHT);

	// ���莞�ɕ\������摜
	m_pSelectCfm[0] = Cform2D::Create(pDevice, "data/TEXTURE/SelectPlayer1.png", D3DXVECTOR3(fScreenWidthHalf + fCharPicWidthHalf, fScreenHeightHalf + fCharPicHeightHalf, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CHAR_BUTTON_WIDTH, CHAR_BUTTON_HEIGHT);
	m_pSelectCfm[1] = Cform2D::Create(pDevice, "data/TEXTURE/SelectPlayer2.png", D3DXVECTOR3(fScreenWidthHalf - fCharPicWidthHalf, fScreenHeightHalf + fCharPicHeightHalf, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CHAR_BUTTON_WIDTH, CHAR_BUTTON_HEIGHT);

	// �L�����摜
	m_SelectCfmPos[CHARCTER_TYPE::TYPE_1] = D3DXVECTOR3(fScreenWidthHalf - fCharPicWidthHalf, fScreenHeightHalf - fCharPicHeightHalf, 0.0f);
	m_SelectCfmPos[CHARCTER_TYPE::TYPE_2] = D3DXVECTOR3(fScreenWidthHalf + fCharPicWidthHalf, fScreenHeightHalf - fCharPicHeightHalf, 0.0f);
	m_SelectCfmPos[CHARCTER_TYPE::TYPE_3] = D3DXVECTOR3(fScreenWidthHalf - fCharPicWidthHalf, fScreenHeightHalf + fCharPicHeightHalf, 0.0f);
	m_SelectCfmPos[CHARCTER_TYPE::TYPE_4] = D3DXVECTOR3(fScreenWidthHalf + fCharPicWidthHalf, fScreenHeightHalf + fCharPicHeightHalf, 0.0f);

	// �O�g�t���[��
	m_pCharFrame[CHARCTER_TYPE::TYPE_1] = Cform2D::Create(pDevice, "data/TEXTURE/CharFrame.png", D3DXVECTOR3(fScreenWidthHalf - fCharPicWidthHalf, fScreenHeightHalf - fCharPicHeightHalf, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CHAR_BUTTON_WIDTH, CHAR_BUTTON_HEIGHT);
	m_pCharFrame[CHARCTER_TYPE::TYPE_2] = Cform2D::Create(pDevice, "data/TEXTURE/CharFrame.png", D3DXVECTOR3(fScreenWidthHalf + fCharPicWidthHalf, fScreenHeightHalf - fCharPicHeightHalf, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CHAR_BUTTON_WIDTH, CHAR_BUTTON_HEIGHT);
	m_pCharFrame[CHARCTER_TYPE::TYPE_3] = Cform2D::Create(pDevice, "data/TEXTURE/CharFrame.png", D3DXVECTOR3(fScreenWidthHalf - fCharPicWidthHalf, fScreenHeightHalf + fCharPicHeightHalf, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CHAR_BUTTON_WIDTH, CHAR_BUTTON_HEIGHT);
	m_pCharFrame[CHARCTER_TYPE::TYPE_4] = Cform2D::Create(pDevice, "data/TEXTURE/CharFrame.png", D3DXVECTOR3(fScreenWidthHalf + fCharPicWidthHalf, fScreenHeightHalf + fCharPicHeightHalf, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CHAR_BUTTON_WIDTH, CHAR_BUTTON_HEIGHT);
	//m_pCharFrame[CHARCTER_TYPE::TYPE_1]->SetDiffuse(1.0f, 0.0f, 0.0f, 1.0f);

	// �I�������L�����̃��f��
	m_pCharModPlayer1[CHARCTER_TYPE::TYPE_1] = CPlayerM::Create(pDevice, 0, D3DXVECTOR3(-53.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 8.0f, 0.0f));
	m_pCharModPlayer1[CHARCTER_TYPE::TYPE_2] = CPlayerM::Create(pDevice, 1, D3DXVECTOR3(-53.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 8.0f, 0.0f));
	m_pCharModPlayer1[CHARCTER_TYPE::TYPE_3] = CPlayerM::Create(pDevice, 2, D3DXVECTOR3(-53.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 8.0f, 0.0f));
	m_pCharModPlayer1[CHARCTER_TYPE::TYPE_4] = CPlayerM::Create(pDevice, 3, D3DXVECTOR3(-53.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 8.0f, 0.0f));
	m_pCharModPlayer2[CHARCTER_TYPE::TYPE_1] = CPlayerM::Create(pDevice, 0, D3DXVECTOR3(53.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, D3DX_PI / 9.0f, 0.0f));
	m_pCharModPlayer2[CHARCTER_TYPE::TYPE_2] = CPlayerM::Create(pDevice, 1, D3DXVECTOR3(53.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, D3DX_PI / 9.0f, 0.0f));
	m_pCharModPlayer2[CHARCTER_TYPE::TYPE_3] = CPlayerM::Create(pDevice, 2, D3DXVECTOR3(53.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, D3DX_PI / 9.0f, 0.0f));
	m_pCharModPlayer2[CHARCTER_TYPE::TYPE_4] = CPlayerM::Create(pDevice, 3, D3DXVECTOR3(53.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, D3DX_PI / 9.0f, 0.0f));

	// �O�g�t���[��
	m_pCharNamePlayer1[CHARCTER_TYPE::TYPE_1] = Cform2D::Create(pDevice, pCharNameTex[CHARCTER_TYPE::TYPE_1], D3DXVECTOR3(200.0f, 650.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CHAR_NAME_WIDTH, CHAR_NAME_HEIGHT);
	m_pCharNamePlayer1[CHARCTER_TYPE::TYPE_2] = Cform2D::Create(pDevice, pCharNameTex[CHARCTER_TYPE::TYPE_2], D3DXVECTOR3(200.0f, 650.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CHAR_NAME_WIDTH, CHAR_NAME_HEIGHT);
	m_pCharNamePlayer1[CHARCTER_TYPE::TYPE_3] = Cform2D::Create(pDevice, pCharNameTex[CHARCTER_TYPE::TYPE_3], D3DXVECTOR3(200.0f, 650.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CHAR_NAME_WIDTH, CHAR_NAME_HEIGHT);
	m_pCharNamePlayer1[CHARCTER_TYPE::TYPE_4] = Cform2D::Create(pDevice, pCharNameTex[CHARCTER_TYPE::TYPE_4], D3DXVECTOR3(200.0f, 650.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CHAR_NAME_WIDTH, CHAR_NAME_HEIGHT);
	m_pCharNamePlayer2[CHARCTER_TYPE::TYPE_1] = Cform2D::Create(pDevice, pCharNameTex[CHARCTER_TYPE::TYPE_1], D3DXVECTOR3(1100.0f, 650.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CHAR_NAME_WIDTH, CHAR_NAME_HEIGHT);
	m_pCharNamePlayer2[CHARCTER_TYPE::TYPE_2] = Cform2D::Create(pDevice, pCharNameTex[CHARCTER_TYPE::TYPE_2], D3DXVECTOR3(1100.0f, 650.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CHAR_NAME_WIDTH, CHAR_NAME_HEIGHT);
	m_pCharNamePlayer2[CHARCTER_TYPE::TYPE_3] = Cform2D::Create(pDevice, pCharNameTex[CHARCTER_TYPE::TYPE_3], D3DXVECTOR3(1100.0f, 650.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CHAR_NAME_WIDTH, CHAR_NAME_HEIGHT);
	m_pCharNamePlayer2[CHARCTER_TYPE::TYPE_4] = Cform2D::Create(pDevice, pCharNameTex[CHARCTER_TYPE::TYPE_4], D3DXVECTOR3(1100.0f, 650.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CHAR_NAME_WIDTH, CHAR_NAME_HEIGHT);

	// �L�����I��p���S
	m_pLogo = CButton::Create(pDevice, s_6, D3DXVECTOR3(SCREEN_WIDTH / 2, 100.0f, 0.0f), 500, 100);

	// �J�[�\��
	m_Select[0].pCursor = CCursor::Create(pDevice, s_4, D3DXVECTOR3(1000.0f, 600.0f, 0.0f), CURSOR_WIDTH, CURSOR_HEIGHT);
	m_Select[1].pCursor = CCursor::Create(pDevice, s_5, D3DXVECTOR3(200.0f, 600.0f, 0.0f), CURSOR_WIDTH, CURSOR_HEIGHT);

	// �J�[�\���̖ڕW���W
	m_OnCursorPos[CHARCTER_TYPE::TYPE_1] = D3DXVECTOR3(587.0f, 310.0f, 0.0f);
	m_OnCursorPos[CHARCTER_TYPE::TYPE_2] = D3DXVECTOR3(715.0f, 310.0f, 0.0f);
	m_OnCursorPos[CHARCTER_TYPE::TYPE_3] = D3DXVECTOR3(587.0f, 450.0f, 0.0f);
	m_OnCursorPos[CHARCTER_TYPE::TYPE_4] = D3DXVECTOR3(715.0f, 450.0f, 0.0f);

	// �I�𒆂̍���
	m_Select[0].nSelect = 0;
	m_Select[1].nSelect = 1;
	m_Select[0].bDecisionFlg = false;
	m_Select[1].bDecisionFlg = false;

	// �I����Ԃɂ��Ă���
	m_pCharPicture[m_Select[0].nSelect]->SetButtonState(BUTTON_STATE::SELECTED);
	m_pCharPicture[m_Select[1].nSelect]->SetButtonState(BUTTON_STATE::SELECTED);

	//�t�F�[�h�̍쐬
	m_pFade = CFade::Create(pDevice, 1);
	m_pFade->StartFade(FADE_OUT, 50, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CManager::GetSelectChar(0));

	return S_OK;
}
//=============================================================================
// �I��
//=============================================================================
void CSelect::Uninit(void)
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
void CSelect::Update(void)
{
	//�T�E���h�擾�̍쐬
	CSound *pSound;
	pSound = CManager::GetSound();

	// �ꎞ�I�ɕۑ�
	int tmpCursorOld[2];

	for (int i = 0; i < MAX_PLAYER; i++)
	{

		tmpCursorOld[i] = m_Select[i].nSelect;

		CheckSelectAllCorsor(i);
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
	// �L�����N�^�[�\���p���f��
	m_pCharModPlayer1[m_Select[0].nSelect]->Update();
	m_pCharModPlayer2[m_Select[1].nSelect]->Update();

#ifdef _DEBUG

	CDebugProc::Print("�v���C���[�I�𒆂̃{�^��:%d\n", m_Select[0].nSelect);
	CDebugProc::Print("�I�𒆂̃{�^��:%d\n", m_Select[1].nSelect);
	CDebugProc::Print("�v���C���[1�͂v�`�r�c�ňړ��łd�m�s�d�q�Ō���\n");
	CDebugProc::Print("�v���C���[2�́��������ňړ��łr�d�k�d�b�s�Ō���\n");
	CDebugProc::Print("�I�𒆂̃{�^��:%f\n", m_pCharModPlayer1[0]->GetRot().y);
	CDebugProc::Print("�I�𒆂̃{�^��:%f\n", m_pCharModPlayer2[0]->GetRot().y);

#endif


}
//=============================================================================
// �`��
//=============================================================================
void CSelect::Draw(void)
{

	m_pDome->Draw();
	m_pDome2->Draw();

	// �L�����N�^�[�\���p���f��
	m_pCharModPlayer1[m_Select[0].nSelect]->Draw();
	m_pCharModPlayer2[m_Select[1].nSelect]->Draw();

	// �w�i
	m_pBackGround->Draw();

	// �L�����N�^�[���\���p
	m_pCharNamePlayer1[m_Select[0].nSelect]->Draw();
	m_pCharNamePlayer2[m_Select[1].nSelect]->Draw();


	// �I��p�L�����摜
	for (int i = 0; i < CHARCTER_TYPE::TYPE_MAX; i++)
	{
		m_pCharPicture[i]->Draw();

	}

	// �I��p�L�����摜
	for (int i = 0; i < MAX_PLAYER; i++)
	{

		if (m_Select[i].bDecisionFlg)
		{
			m_pSelectCfm[i]->Draw();
		}

	}

	// �I��p�L�����摜
	for (int i = 0; i < CHARCTER_TYPE::TYPE_MAX; i++)
	{
		m_pCharFrame[i]->Draw();

	}
	// �J�[�\��
	for (int i = 0; i < MAX_CURSOR; i++)
	{

		m_Select[i].pCursor->Draw();

	}


	// �L�����I����ʃ��S
	m_pLogo->Draw();

	//�t�F�[�h�̍쐬
	m_pFade->Draw();
}
//=============================================================================
// �t�F�[�h�̍X�V
//=============================================================================
void CSelect::UpdateFade(void)
{
	if (m_bChangeFlag
		&& m_pFade->GetFade() == FADE_NONE)
	{
		//pSound->Play(SOUND_LABEL_SE_SELECT002);
		// �I�������L������ۑ�
		//m_pFade->StartFade(FADE_IN, 100, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), CManager::GetSelectChar(0));
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

		// �G���^�[�L�[���������ꍇ
		ChkSelectButton(1);
		m_pSelectCfm[1]->SetPos(m_SelectCfmPos[m_Select[1].nSelect]);


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

		if (!m_Select[0].bDecisionFlg)
		{

			// 
			ChkSelectButton(0);

			m_pSelectCfm[0]->SetPos(m_SelectCfmPos[m_Select[0].nSelect]);

		}
		else
		{

		}

	}
	else if ((pInputKeyboard->GetKeyTrigger(DIK_BACKSPACE)) || pTmpPad->GetKeyTrigger(WII_BUTTOM_A))
	{
		m_Select[0].bDecisionFlg = false;

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
// 
//=============================================================================
void CSelect::ChkSelectButton(int nParamSelectCursor)
{

	// �I�����ꂽ�ꍇ�̓X�L�b�v
	if (m_Select[nParamSelectCursor].bDecisionFlg){ return; }

	// ��`�ł̂����蔻��
	if (CCursor::HitChkRect(m_Select[nParamSelectCursor].pCursor->GetPos(),
		m_pCharPicture[m_Select[nParamSelectCursor].nSelect]->GetPos(),
		m_Select[nParamSelectCursor].pCursor->GetLen(),
		m_pCharPicture[m_Select[nParamSelectCursor].nSelect]->GetLen()))
	{

		// ���ɑI������Ă��Ȃ��ꍇ
		if (m_Select[1].nSelect != m_Select[0].nSelect)
		{

			// 
			m_Select[nParamSelectCursor].pCursor->SetTime(0.0f);
			CheckSelectAllCorsor(nParamSelectCursor);

			//pSound->PlayVoice(m_Select[0].nSelect,VOICE_LABEL_SE_START);

			m_Select[nParamSelectCursor].bDecisionFlg = true;

		}

	}

}
//=============================================================================
// �S�Ẵv���C���[���L���������肵�����ǂ����̃t���O
//=============================================================================
void CSelect::CheckSelectAllCorsor(int nParamDecisionCursor)
{

	if (m_bChangeFlag){ return; }

	// �S�Ẵv���C���[���I��������������
	if (m_Select[nParamDecisionCursor].bDecisionFlg
		&& m_Select[nParamDecisionCursor - 1].bDecisionFlg)
	{

		// �J�ڏ���
		m_bChangeFlag = true;

		// �����Ԃɂ���
		m_Select[nParamDecisionCursor].bDecisionFlg = true;

		// �e�L�����N�^�[�̌���
		CManager::SetSelectChar(0, m_Select[0].nSelect);
		CManager::SetSelectChar(1, m_Select[1].nSelect);

		m_pFade->StartFade(FADE_IN, 100, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), CManager::GetSelectChar(0));

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
//=============================================================================
// ���K��
//=============================================================================
int CSelect::NomalizeSelectPlayer(int nParamVal)
{
	// �e�z�u�ɂ���Ĉړ�����
	if (nParamVal < 0)
	{

		return MAX_PLAYER - 1;

	}
	else
	{

		return 0;

	}

}
/////////////EOF////////////
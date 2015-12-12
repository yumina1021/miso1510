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
#include "../../module/ui/Button.h"
#include "../../module/ui/Cursor.h"

#include "../../module/etc/Camera.h"
#include "../../module/field/Dome.h"
#include "../../module/field/Field.h"
#include "../../module/field/meshfielddata.h"
#include "../../module/field/Domeunder.h"
#include "../../form/formX.h"
#include "../../form/form2D.h"
#include "../../module/robot/PlayerM.h"

#include "../wiicon/wiimote.h"

#include "../../administer/Debugproc.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
const float CAMERA_POS_X(0.0f);
const float CAMERA_POS_Y(0.0f);
const float CAMERA_POS_Z(-5000.0f);
const float MENU_WIDTH(400.0f);			//���j���[�̉��T�C�Y
const float MENU_HEIGHT(100.0f);			//���j���[�̏c�T�C�Y
const float MENU_X((float)SCREEN_WIDTH / 2.0f - MENU_WIDTH / 2.0f);	//���j���[��X�ʒu
const float MENU_Y(675.0f);			//���j���[��Y�ʒu

const float CHAR_POS_X((float)SCREEN_WIDTH / 2.0f);
const float CHAR_POS_Y(300.0f);
const float CHAR_WIDTH(450.0f);
const float CHAR_HEIGHT(600.0f);

const int LOGO_WIDTH(800.0f);			//���j���[�̉��T�C�Y
const int LOGO_HEIGHT(250.0f);			//���j���[�̏c�T�C�Y

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
	m_pMenueButton[0] = { };
	m_pMenueButton[1] = { };
	m_pMenueButton[2] = { };
	m_pMenueButton[3] = { };

	// �J�����̎擾
	CCamera* pTmpCamera = CManager::GetCamera();

	pTmpCamera->SetPosP(D3DXVECTOR3(CAMERA_POS_X, CAMERA_POS_Y, CAMERA_POS_Z));

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
	//m_pBackGround=CBackGround::Create(pDevice,BACKGROUND_TITLE);

	m_pLogo = CButton::Create(pDevice, s_7, D3DXVECTOR3(SCREEN_WIDTH / 2, 500.0f, 0.0f), LOGO_WIDTH, LOGO_HEIGHT);
	m_pLogo->SetDiffuse(0.0f, 0.0f, 1.0f, 1.0f);

	//��̍쐬
	m_pDome = CDome::Create(pDevice, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//��̍쐬
	m_pDome2 = CDomeU::Create(pDevice, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//�����̔z�u
	m_pMenueButton[GAME_START] = CButton::Create(pDevice, t_stert, D3DXVECTOR3(MENU_X - 10.0f, MENU_Y, 0.0f), MENU_WIDTH, MENU_HEIGHT);
	m_pMenueButton[GAME_END] = CButton::Create(pDevice, t_end, D3DXVECTOR3(MENU_X + MENU_WIDTH + 10.0f, MENU_Y, 0.0f), MENU_WIDTH, MENU_HEIGHT);
	m_pCursor[0] = CCursor::Create(pDevice, s_4, D3DXVECTOR3(1000.0f, 600.0f, 0.0f), 64, 64);
	m_pCursor[1] = CCursor::Create(pDevice, s_4, D3DXVECTOR3(200.0f, 600.0f, 0.0f), 64, 64);

	// ���S�p�L�����N�^�[
	//m_pCharcterPic[0] = Cform2D::Create(pDevice, "data/TEXTURE/Rosa.png", D3DXVECTOR3(CHAR_POS_X, CHAR_POS_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CHAR_WIDTH, CHAR_HEIGHT);
	//m_pCharcterPic[1] = Cform2D::Create(pDevice, "data/TEXTURE/Lila.png", D3DXVECTOR3(CHAR_POS_X - CHAR_WIDTH, CHAR_POS_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CHAR_WIDTH, CHAR_HEIGHT);
	//m_pCharcterPic[2] = Cform2D::Create(pDevice, "data/TEXTURE/Licht.png", D3DXVECTOR3(CHAR_POS_X + CHAR_WIDTH, CHAR_POS_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CHAR_WIDTH, CHAR_HEIGHT);

	// �I����Ԃɂ��Ă���
	m_pMenueButton[m_nCursor]->SetButtonState(BUTTON_STATE::SELECTED);

	//�T�E���h�擾�̍쐬
	CSound *pSound;
	pSound = CManager::GetSound();

	//�T�E���h�Đ��̍쐬
	//pSound->Play(SOUND_LABEL_BGM000);


	//�t�F�[�h�̍쐬
	m_pFade = CFade::Create(pDevice, 1);
	m_pFade->StartFade(FADE_OUT,50,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),CManager::GetSelectChar(0));

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

	//LookAround();
	CCamera* pTmpCamera = CManager::GetCamera();
	D3DXVECTOR3 fTmpRot = pTmpCamera->GetRotCamera();
	D3DXVECTOR3 fTmpPosR = pTmpCamera->GetPosR();
	D3DXVECTOR3 fTmpPosP = pTmpCamera->GetPosP();

	fTmpRot.y -= (D3DX_PI / 180.0f);

	// �J�������_�E
	fTmpPosR.x = fTmpPosP.x + sinf(fTmpRot.y / 180.0f * D3DX_PI) * -5000.0f;
	fTmpPosR.z = fTmpPosP.z + cosf(fTmpRot.y / 180.0f * D3DX_PI) * 5000.0f;

	pTmpCamera->SetRotCamera(fTmpRot);
	pTmpCamera->SetPosR(fTmpPosR);
	
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
		m_pCursor[0]->SetTime(0.0f);
		m_nType = SELECT_TYPE::TYPE_CURSOR;

	}
	// �{�^���I��
	if (m_nType == SELECT_TYPE::TYPE_BUTTON)
	{
		KeyCommand();
		m_pCursor[0]->SyncCharPos(m_pMenueButton[m_nCursor]->GetPos());

	}
	// �J�[�\���ړ�
	else if (m_nType == SELECT_TYPE::TYPE_CURSOR)
	{
			SelectByCursor();
	}

	// �Ⴄ�{�^���Ɉڂ�����
	if (tmpCursorOld != m_nCursor)
	{
		CButton::ChangeSelectButtonState(m_pMenueButton[tmpCursorOld], m_pMenueButton[m_nCursor]);

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
	//m_pBackGround->Draw();

	m_pDome->Draw();
	m_pDome2->Draw();

	m_pMenueButton[GAME_START]->Draw();
	m_pMenueButton[GAME_END]->Draw();

	//����
	for (int i = 0; i < 2; i++)
	{

		m_pCursor[i]->Draw();

	}

	for (int i = 0; i < 3; i++)
	{

		//m_pCharcterPic[i]->Draw();

	}

	m_pLogo->Draw();

	//�t�F�[�h
	m_pFade->Draw();

}
//=============================================================================
// ����
//=============================================================================
void CTitle::KeyCommand(void)
{

	// Wii�R���̎擾
	WiiRemote* pTmpPad = CManager::GetWii(0);

	//�T�E���h�擾�̍쐬
	CSound *pSound;
	pSound = CManager::GetSound();

	//�L�[�{�[�h�C���v�b�g�̎󂯎��
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//�G���^�[�L�[�������ꂽ�ꍇ
	if (pInputKeyboard->GetKeyTrigger(DIK_RETURN) || pTmpPad->GetKeyTrigger(WII_BUTTOM_A))
	{

		ChangeState();

	}
	else if (m_bChangeFlag != true)
	{

		if (pInputKeyboard->GetKeyTrigger(DIK_D) || pTmpPad->GetKeyTrigger(WII_BUTTOM_RIGHT))
		{
			m_nCursor--;
			//pSound->Play(SOUND_LABEL_SE_SELECT000);
			if (m_nCursor < GAME_START)
			{
				m_nCursor = GAME_END;
			}

		}
		else if (pInputKeyboard->GetKeyTrigger(DIK_A) || pTmpPad->GetKeyTrigger(WII_BUTTOM_LEFT))
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
	D3DXVECTOR3 tmpCurPos = m_pCursor[0]->GetPos();
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
		tmpCharPos = m_pMenueButton[i]->GetPos();

		// ��`�ł̂����蔻��
		if (CCursor::HitChkRect(tmpCurPos, tmpCharPos, m_pCursor[0]->GetLen(), m_pMenueButton[i]->GetLen()))
		{

			// �������Ă��邱�Ƃ��L�^
			tmpOnFlg = true;

			// �I����Ԃ������
			m_pMenueButton[m_nCursor]->SetButtonState(BUTTON_STATE::PUSH_OFF);

			// �I�𒆂̃J�[�\���̍X�V
			m_nCursor = i;

			// �I����Ԃɂ��Ă���
			m_pMenueButton[m_nCursor]->SetButtonState(BUTTON_STATE::SELECTED);

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
		m_pCursor[0]->MoveByKeybord();
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
	case 0: m_bChangeFlag = true;
		//pSound->Play(SOUND_LABEL_SE_SELECT001);
		if (m_pFade->GetPlayFade() == false)
		{
			m_pFade->StartFade(FADE_IN, 100, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f),CManager::GetSelectChar(0));
			CScene::SetVSFlag(false);
		}
		break;
		//�G���h
	case 1:	m_bChangeFlag = false;
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
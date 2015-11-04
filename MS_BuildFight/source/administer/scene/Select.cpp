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
CSelect :: CSelect(void):
m_nType(SELECT_TYPE::TYPE_BUTTON)
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
	m_pCharPicture[CHARCTER_TYPE::TYPE_1] = CCharPicture::Create(pDevice, s_0, D3DXVECTOR3(325.0f, 187.5f, 0.0f), 650, 375);
	m_pCharPicture[CHARCTER_TYPE::TYPE_2] = CCharPicture::Create(pDevice, s_1, D3DXVECTOR3(975.0f, 187.5f, 0.0f), 650, 375);
	m_pCharPicture[CHARCTER_TYPE::TYPE_3] = CCharPicture::Create(pDevice, s_2, D3DXVECTOR3(325.0f, 562.5f, 0.0f), 650, 375);
	m_pCharPicture[CHARCTER_TYPE::TYPE_4] = CCharPicture::Create(pDevice, s_3, D3DXVECTOR3(975.0f, 562.5f, 0.0f), 650, 375);
	m_pCursor = CCharPicture::Create(pDevice, s_4, D3DXVECTOR3(1000.0f, 600.0f, 0.0f), 128, 128);

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

	//�L�[�{�[�h�C���v�b�g�̎󂯎��
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//�G���^�[�L�[�������ꂽ�ꍇ
	if (pInputKeyboard->GetKeyTrigger(DIK_F1)
		&& m_bChangeFlag == false)
	{
		m_nType = SELECT_TYPE::TYPE_BUTTON;

	}
	else if (pInputKeyboard->GetKeyTrigger(DIK_F2)
		&& m_bChangeFlag == false)
	{
		m_nType = SELECT_TYPE::TYPE_CURSOR;

	}
	// �{�^���I��
	if (m_nType == SELECT_TYPE::TYPE_BUTTON)
	{
		SelectByButton();
	}
	// �J�[�\���ړ�
	else if (m_nType == SELECT_TYPE::TYPE_CURSOR)
	{
		SelectByCursor();

	}

	m_fDiffuse-=0.01f;

	if(m_fDiffuse<0.5f)
	{
		m_fDiffuse=1.0f;
	}

	m_pCharPicture[m_nCursor]->SetDiffuse(m_fDiffuse,m_fDiffuse,m_fDiffuse,1.0f);

	UpdateFade();

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
// �L�[�{�[�h�ł̑I��
//=============================================================================
void CSelect::SelectByButton(void)
{

	//�L�[�{�[�h�C���v�b�g�̎󂯎��
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//�G���^�[�L�[�������ꂽ�ꍇ
	if ((pInputKeyboard->GetKeyTrigger(DIK_RETURN) || pInputKeyboard->GetKeyTrigger(DIK_Z)) && m_bChangeFlag == false)
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
	else if (m_bChangeFlag != true)
	{
		if (pInputKeyboard->GetKeyTrigger(DIK_W) || pInputKeyboard->GetKeyTrigger(DIK_UP))
		{
			m_pCharPicture[m_nCursor]->SetDiffuse(1.0f, 1.0f, 1.0f, 1.0f);
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
			m_pCharPicture[m_nCursor]->SetDiffuse(1.0f, 1.0f, 1.0f, 1.0f);
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
			m_pCharPicture[m_nCursor]->SetDiffuse(1.0f, 1.0f, 1.0f, 1.0f);
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
			m_pCharPicture[m_nCursor]->SetDiffuse(1.0f, 1.0f, 1.0f, 1.0f);
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
	POINT tmpCurPos;
	D3DXVECTOR3 tmpPos = m_pCursor->GetPos();
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
		if (HitChkRect(tmpPos, tmpCharPos, m_pCursor->GetLen(), m_pCharPicture[i]->GetLen()))
		{

			// �������Ă��邱�Ƃ��L�^
			tmpOnFlg = true;
		
			// �I�𒆂���O�ꂽ���ڂ̃��l��������
			m_pCharPicture[m_nCursor]->SetDiffuse(1.0f, 1.0f, 1.0f, 1.0f);

			// �I�𒆂̃J�[�\���̍X�V
			m_nCursor = i;
			break;
		}
		else{


		}
	}
	// ���N���b�N������
	if (pInputKeyboard->GetKeyTrigger(DIK_RETURN))
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
		if (pInputKeyboard->GetKeyPress(DIK_W) || pInputKeyboard->GetKeyPress(DIK_UP))
		{

			tmpPos.y -= CURSOR_MOVE_COFF;

		}
		else if (pInputKeyboard->GetKeyPress(DIK_S) || pInputKeyboard->GetKeyPress(DIK_DOWN))
		{
			tmpPos.y += CURSOR_MOVE_COFF;

		}
		if (pInputKeyboard->GetKeyPress(DIK_A) || pInputKeyboard->GetKeyPress(DIK_LEFT))
		{

			tmpPos.x -= CURSOR_MOVE_COFF;

		}
		else if (pInputKeyboard->GetKeyPress(DIK_D) || pInputKeyboard->GetKeyPress(DIK_RIGHT))
		{
			tmpPos.x += CURSOR_MOVE_COFF;

		}
	}
	// �J�[�\���̍��W�̍X�V
	m_pCursor->SetPos(tmpPos);

#ifdef _DEBUG

	CDebugProc::Print("�}�E�X���WX:%f\n", tmpPos.x);
	CDebugProc::Print("�}�E�X���WY:%f\n", tmpPos.y);

#endif

}// SelectByCursor
//=============================================================================
// �J�[���ړ��ł̑I��
//=============================================================================
bool CSelect::HitChkRect(const D3DXVECTOR3& paramPos1,
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
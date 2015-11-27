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
#include "../../module/ui/Cursor.h"
#include "../../module/ui/Button.h"

#include "../../module/etc/Ball.h"
#include "../../module/field/Field.h"

#include "../../administer/Debugproc.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
const float CURSOR_MOVE_COFF(10.0f);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
float cnt = 0.0f;
D3DXVECTOR3 tmpRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CStageSelect::CStageSelect(void):
m_fTime(0.0f),
m_nState(STATE::NORMAL)
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

	m_playerData[0].pCursor = CCursor::Create(pDevice, s_4, D3DXVECTOR3(1000.0f, 600.0f, 0.0f), 128, 128);
	m_playerData[0].nSelectNum = 0;

	m_playerData[1].pCursor = CCursor::Create(pDevice, s_4, D3DXVECTOR3(400.0f, 600.0f, 0.0f), 128, 128);
	m_playerData[1].nSelectNum = 0;

	m_fDiffuse=1.0f;

	m_bVsSelectFlag = CScene::GetVSFlag();

	m_bTitleBackFlag=false;

	m_pFade->StartFade(FADE_OUT,50,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),CManager::GetSelectChar(0));
	m_bSendData=false;

	float fTmpRad = (D3DX_PI * 2.0f) / MAX_BALL;
	float tmpRot((D3DX_PI * 2.0f));

	for (int i = 0; i < MAX_BALL; i++)
	{
		m_Obj[i].pDispObj = CBall::Create(pDevice, 0, D3DXVECTOR3(0.0f, 100.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		m_Obj[i].fLenCoff = fTmpRad * static_cast<float>(i);
		m_Obj[i].fLenCoffDest = m_Obj[i].fLenCoff;
		m_Obj[i].nDestCnt = i;

		D3DXVECTOR3 tmpObjPos;
		tmpObjPos = m_Obj[i].pDispObj->GetPos();

		//		// �q���O���p�̌W�����C�[�W���O�Ȑ��ŋ��߂�
		m_Obj[i].fLenCoff = CCursor::EsasingNone(m_Obj[i].fLenCoff, m_Obj[m_Obj[i].nDestCnt].fLenCoffDest, m_fTime);

		// ���_0�𒆐S�Ƃ��ĉq���O���p�̍��W�����߂�
		tmpObjPos.x = 0.0f + sinf(m_Obj[i].fLenCoff) * 100.0f;
		tmpObjPos.y = -20.0f;
		tmpObjPos.z = 0.0f + cosf(m_Obj[i].fLenCoff) * -100.0f;

		// ���W���X�V
		m_Obj[i].pDispObj->SetPos(tmpObjPos);
	}

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

	//���݂̏�Ԃɂ���ĕ���
	switch (m_nState)
	{
	case STATE::NORMAL:

		// �{�^���ŃX�e�[�W��I��
		SelectByButton();

		break;

	case STATE::SATELLITE_ORBIT:

		// �q���O������
		UpdateSelectObject();

		break;

	case STATE::CHANGE_SCENE:
		UpdateFade();

		break;
	default:
		break;
	}


	
#ifdef _DEBUG

	CDebugProc::Print("�I�𒆂̃{�^��:%d\n", m_playerData[0].nSelectNum);

#endif
}
//=============================================================================
// �`��
//=============================================================================
void CStageSelect :: Draw(void)
{
	//m_pBackGround->Draw();

	for (int i = 0; i < MAX_BALL; i++)
	{

		m_Obj[i].pDispObj->Draw();

	}

	for (int i = 0; i < 2; i++)
	{
		m_playerData[i].pCursor->Draw();

	}
	//�t�F�[�h�̍쐬
	m_pFade->Draw();
}
//=============================================================================
// �`��
//=============================================================================
void CStageSelect::UpdateSelectObject()
{
	D3DXVECTOR3 tmpObjPos;

	for (int i = 0; i < MAX_BALL; i++)
	{

		tmpObjPos = m_Obj[i].pDispObj->GetPos();

		//		// �q���O���p�̌W�����C�[�W���O�Ȑ��ŋ��߂�
		m_Obj[i].fLenCoff = CCursor::EsasingNone(m_Obj[i].fLenCoff, m_Obj[m_Obj[i].nDestCnt].fLenCoffDest, m_fTime);

		// ���_0�𒆐S�Ƃ��ĉq���O���p�̍��W�����߂�
		tmpObjPos.x = 0.0f + sinf(m_Obj[i].fLenCoff) * 100.0f;
		tmpObjPos.y = 0.0f;
		tmpObjPos.z = 0.0f + cosf(m_Obj[i].fLenCoff) * -100.0f;

		// ���W���X�V
		m_Obj[i].pDispObj->SetPos(tmpObjPos);

#ifdef _DEBUG

		//CDebugProc::Print("X���W:%f\n", tmpObjPos.x);
		//CDebugProc::Print("Z���W:%f\n", tmpObjPos.z);
		CDebugProc::Print("�q���O���p�̌W��:%f\n", m_Obj[i].fLenCoff);

#endif

	}

	// �C�[�W���O�Ȑ��p�^�C�}�[�̍X�V
	if (m_fTime >= 1.0f)
	{
		m_fTime = 0.0f;

		m_nState = STATE::NORMAL;

		for (int i = 0; i < MAX_BALL; i++)
		{
			m_Obj[i].fLenCoff = m_Obj[m_Obj[i].nDestCnt].fLenCoffDest;
		}
	}
	else
	{
		m_fTime += 0.025f;
	}

}
//=============================================================================
// �t�F�[�h�̍X�V
//=============================================================================
void CStageSelect::UpdateFade(void)
{
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
void CStageSelect::SelectByButton(void)
{

	//�T�E���h�擾�̍쐬
	CSound *pSound;
	pSound = CManager::GetSound();

	//�L�[�{�[�h�C���v�b�g�̎󂯎��
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	float fTmpRad = (D3DX_PI * 2.0f) / MAX_BALL;
	float tmpRot((D3DX_PI * 2.0f));

	//�G���^�[�L�[�������ꂽ�ꍇ
	if ((pInputKeyboard->GetKeyTrigger(DIK_RETURN)))
	{

		// �J�ڏ���
		m_nState = STATE::CHANGE_SCENE;

		// �I�������}�b�v��ۑ�
		CManager::SetSelectMap(m_playerData[0].nSelectNum);

		m_pFade->StartFade(FADE_IN, 100, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f),CManager::GetSelectChar(0));
		//pSound->PlayVoice(m_playerData[0].nSelectNum,VOICE_LABEL_SE_START);

	}
	else if (pInputKeyboard->GetKeyTrigger(DIK_A) || pInputKeyboard->GetKeyTrigger(DIK_LEFT))
	{

		//pSound->Play(SOUND_LABEL_SE_SELECT000);

		m_playerData[0].nSelectNum--;
		NomalizeSelectObject(m_playerData[0].nSelectNum);

		for (int i = 0; i < MAX_BALL; i++)
		{
			m_Obj[i].nDestCnt--;
			NomalizeSelectObject(m_Obj[i].nDestCnt);
			
			if (m_Obj[i].fLenCoff <= 0.0f)
			{
				m_Obj[i].fLenCoff = tmpRot;
			}
		}
		m_fTime = 0.0f;

		m_nState = STATE::SATELLITE_ORBIT;

	}
	else if (pInputKeyboard->GetKeyTrigger(DIK_D) || pInputKeyboard->GetKeyTrigger(DIK_RIGHT))
	{
		//pSound->Play(SOUND_LABEL_SE_SELECT000);

		m_playerData[0].nSelectNum++;
		NomalizeSelectObject(m_playerData[0].nSelectNum);

		for (int i = 0; i < MAX_BALL; i++)
		{
			m_Obj[i].nDestCnt++;
			NomalizeSelectObject(m_Obj[i].nDestCnt);

			if (m_Obj[i].fLenCoff >= tmpRot - fTmpRad)
			{
				m_Obj[i].fLenCoff = 0.0f - fTmpRad;
			}


		}
		m_fTime = 0.0f;

		m_nState = STATE::SATELLITE_ORBIT;

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
//=============================================================================
// ���K��
//=============================================================================
void CStageSelect::NomalizeSelectObject(int& nParamVal)
{
	// �e�z�u�ɂ���Ĉړ�����
	if (nParamVal < 0)
	{

		nParamVal = MAX_BALL - 1;

	}
	else if (nParamVal >= MAX_BALL)
	{

		nParamVal = 0;

	}

}////////////EOF////////////
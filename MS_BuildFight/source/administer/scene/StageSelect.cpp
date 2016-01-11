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
#include "../../module/ui/CharPicture.h"
#include "../../module/ui/Effect.h"
#include "../../module/ui/Cursor.h"
#include "../../module/ui/Button.h"

#include "../../module/etc/Camera.h"

#include "../../module/field/Domeunder.h"
#include "../../module/field/Dome.h"

#include "../../module/etc/Ball.h"
#include "../../form/formX.h"
#include "../../form/form3D.h"
#include "../../form/form2D.h"
#include "../../module/field/Field.h"

#include "../../module/robot/PlayerM.h"

#include "../../administer/Debugproc.h"

#include "../wiicon/wiimote.h"

#include "../../administer/Texture.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
const float CURSOR_MOVE_COFF(10.0f);
const float STAGE_DIST_CENT(300.0f);
const float CAMERA_POS_X(0.0f);
const float CAMERA_POS_Y(0.0f);
const float CAMERA_POS_Z(-500.0f);

const float NAME_POS_X(650.0f);
const float NAME_POS_Y(550.0f);
const float NAME_WIDTH(450.0f);
const float NAME_HEIGHT(150.0f);

const float STAR_OFFSET(0.0f);
const float STAR_POS_Y(NAME_POS_Y + 90.0f);
const float STAR_WIDTH(64.0f);
const float STAR_HEIGHT(64.0f);

LPSTR pModName[MAX_STAGE]
{

	"data/MODEL/stage1.x",
		"data/MODEL/stage2.x",
		"data/MODEL/stage3.x",
		"data/MODEL/stage4.x",

};

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
float cnt = 0.0f;
D3DXVECTOR3 tmpRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CStageSelect::CStageSelect(void) :
m_fTime(0.0f),
m_nState(STATE::NORMAL)
{
	m_pBackGround = NULL;
	m_pFade = NULL;

	// �J�����̎擾
	CCamera* pTmpCamera = CManager::GetCamera();

	pTmpCamera->SetPosP(D3DXVECTOR3(CAMERA_POS_X, CAMERA_POS_Y, CAMERA_POS_Z));

}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CStageSelect :: ~CStageSelect(void)
{
}
int selectStageOld = 0;

//=============================================================================
// ������
//=============================================================================
HRESULT CStageSelect::Init(LPDIRECT3DDEVICE9 pDevice)
{
	//�T�E���h�擾�̍쐬
	CSound *pSound;
	pSound = CManager::GetSound();

	//�T�E���h�Đ��̍쐬
	//pSound->Play(SOUND_LABEL_BGM001);

	//��̍쐬
	m_pDome = CDome::Create(pDevice, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//��̍쐬
	m_pDome2 = CDomeU::Create(pDevice, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// �L�����I��p���S
	m_pLogo = CButton::Create(pDevice, s_6, D3DXVECTOR3(SCREEN_WIDTH / 2, 100.0f, 0.0f), 900, 100);

	//�w�i�̍쐬
	m_pBackGround = Cform3D::Create(pDevice, TEXTURE_SELECT, D3DXVECTOR3(0.0f, 0.0f, 350.0f), D3DXVECTOR3(-D3DX_PI / 2.0f, 0.0f, 0.0f), SCREEN_WIDTH-30, SCREEN_HEIGHT-15);
	m_pBackGround->SetDiffuse(1.0f, 1.0f, 1.0f, 0.6f);

	//�t�F�[�h�̍쐬
	m_pFade = CFade::Create(pDevice, 1);

	// �J�[�\���̍쐬
	m_playerData[0].pCursor = CCursor::Create(pDevice, s_4, D3DXVECTOR3(1000.0f, 600.0f, 0.0f), 128, 128);
	m_playerData[1].pCursor = CCursor::Create(pDevice, s_5, D3DXVECTOR3(400.0f, 600.0f, 0.0f), 128, 128);
	m_playerData[0].nSelectNum = 0;
	m_playerData[1].nSelectNum = 0;

	// �X�e�[�W��
	m_pStageName[0] = CCharPicture::Create(pDevice, sn1, D3DXVECTOR3(NAME_POS_X, NAME_POS_Y, 0.0f), NAME_WIDTH, NAME_HEIGHT);
	m_pStageName[1] = CCharPicture::Create(pDevice, sn2, D3DXVECTOR3(NAME_POS_X, NAME_POS_Y, 0.0f), NAME_WIDTH, NAME_HEIGHT);
	m_pStageName[2] = CCharPicture::Create(pDevice, sn3, D3DXVECTOR3(NAME_POS_X, NAME_POS_Y, 0.0f), NAME_WIDTH, NAME_HEIGHT);
	m_pStageName[3] = CCharPicture::Create(pDevice, sn4, D3DXVECTOR3(NAME_POS_X, NAME_POS_Y, 0.0f), NAME_WIDTH, NAME_HEIGHT);

	// �ϐ���`
	float fTmpRad((D3DX_PI * 2.0f) / MAX_STAGE);
	float tmpRot((D3DX_PI * 2.0f));
	D3DXVECTOR3 tmpObjPos;
	int nlevelArray[MAX_STAGE]{1, 3, 6, 10};

	// �S�ẴX�e�[�W�𐶐�
	for (int i = 0; i < MAX_STAGE; i++)
	{

		// ����
		m_Obj[i].pDispObj = CformX::Create(pDevice, pModName[i], D3DXVECTOR3(0.0f, 100.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		// �e�l�̐ݒ�
		m_Obj[i].fLenCoff = fTmpRad * static_cast<float>(i);
		m_Obj[i].fLenCoffDest = m_Obj[i].fLenCoff;
		m_Obj[i].nDestCnt = i;
		tmpObjPos = m_Obj[i].pDispObj->GetPos();

		// �q���O���p�̌W�����C�[�W���O�Ȑ��ŋ��߂�
		m_Obj[i].fLenCoff = CCursor::EsasingNone(m_Obj[i].fLenCoff, m_Obj[m_Obj[i].nDestCnt].fLenCoffDest, m_fTime);

		// ���_0�𒆐S�Ƃ��ĉq���O���p�̍��W�����߂�
		tmpObjPos.x = 0.0f + sinf(m_Obj[i].fLenCoff) * STAGE_DIST_CENT;
		tmpObjPos.y = 0.0f;
		tmpObjPos.z = 0.0f + cosf(m_Obj[i].fLenCoff) * -STAGE_DIST_CENT;

		// ���W���X�V
		m_Obj[i].pDispObj->SetPos(tmpObjPos);

		// ��Փx�̐ݒ�
		m_Obj[i].nlevel = nlevelArray[i];

	}

	int levelCnt(1);
	float posX(0.0f);
	D3DXCOLOR tmpCol;

	// ��Փx�����p�́�
	for (int i = 0; i < MAX_LEVEL; i++)
	{
		// ���W�̌v�Z
		posX = (NAME_POS_X - NAME_WIDTH * 0.25f) + STAR_WIDTH * i;

		// ����
		m_pLevelStar[i] = CCharPicture::Create(pDevice, ls, D3DXVECTOR3(posX, STAR_POS_Y, 0.0f), STAR_WIDTH, STAR_HEIGHT);

		// �F�t��
		// ����
		if (levelCnt > 3 && levelCnt < 8)
		{
			tmpCol = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		}
		else if (levelCnt > 7)
		{
			tmpCol = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		}
		else
		{
			tmpCol = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
		}

		m_pLevelStar[i]->SetDiffuse(tmpCol.r, tmpCol.g, tmpCol.b, tmpCol.a);
		m_pLevelStar[i]->SetDiff(tmpCol);

		levelCnt++;

	}
	// �t�F�[�h�A�E�g�̊J�n
	m_pFade->StartFade(FADE_OUT, 50, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CManager::GetSelectChar(0));

	return S_OK;
}
//=============================================================================
// �I��
//=============================================================================
void CStageSelect::Uninit(void)
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
void CStageSelect::Update(void)
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

		// �t�F�[�h�̍X�V
		UpdateFade();

		break;
	default:
		break;
	}

	// �S�ẴX�e�[�W
	for (int i = 0; i < MAX_STAGE; i++)
	{
		m_pStageName[i]->ChangeGuiState(m_pStageName[i]->GetGuiMode());;

		// ��Փx�����p�́�
		for (int j = 0; j < m_Obj[selectStageOld].nlevel; j++)
		{

			m_pLevelStar[j]->ChangeGuiState(m_pLevelStar[j]->GetGuiMode());

		}
	}
#ifdef _DEBUG

	CDebugProc::Print("�I�𒆂̃{�^��:%d\n", m_playerData[0].nSelectNum);

#endif
}

//=============================================================================
// �`��
//=============================================================================
void CStageSelect::Draw(void)
{

	m_pDome->Draw();
	m_pDome2->Draw();

	// �w�i�̕`��
	m_pBackGround->Draw();


	// �S�ẴX�e�[�W
	for (int i = 0; i < MAX_STAGE; i++)
	{

		// �`��
		m_Obj[i].pDispObj->Draw();

	}

	// �S�ẴJ�[�\��
	for (int i = 0; i < 2; i++)
	{

		// �`��
		m_playerData[i].pCursor->Draw();

	}

	// ��Փx�ݒ�p�́�
	for (int i = 0; i < m_Obj[selectStageOld].nlevel; i++)
	{
		m_pLevelStar[i]->Draw();
	}

	// ���S
	m_pLogo->Draw();

	// ���ݑI�𒆂̃X�e�[�W��
	m_pStageName[selectStageOld]->Draw();

	//�t�F�[�h
	m_pFade->Draw();

}
float tmpTime = 0.0f;
//=============================================================================
// �`��
//=============================================================================
void CStageSelect::UpdateSelectObject()
{
	D3DXVECTOR3 tmpObjPos;

	// �S�ẴX�e�[�W
	for (int i = 0; i < MAX_STAGE; i++)
	{

		// ���W�̎擾
		tmpObjPos = m_Obj[i].pDispObj->GetPos();

		// �q���O���p�̌W�����C�[�W���O�Ȑ��ŋ��߂�
		m_Obj[i].fLenCoff = CCursor::EsasingNone(m_Obj[i].fLenCoff, m_Obj[m_Obj[i].nDestCnt].fLenCoffDest, m_fTime);

		// ���_0�𒆐S�Ƃ��ĉq���O���p�̍��W�����߂�
		tmpObjPos.x = 0.0f + sinf(m_Obj[i].fLenCoff) * STAGE_DIST_CENT;
		tmpObjPos.y = 0.0f;
		tmpObjPos.z = 0.0f + cosf(m_Obj[i].fLenCoff) * -STAGE_DIST_CENT;

		// ���W���X�V
		m_Obj[i].pDispObj->SetPos(tmpObjPos);

		// 
		tmpTime = CCursor::EsasingNone(tmpTime, 1.0f, m_fTime);

		// �S�ẴX�e�[�W
		m_pStageName[i]->SetDiffuse(1.0f, 1.0f, 1.0f, 1.0f - tmpTime);
		m_pStageName[i]->SetDiff(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - tmpTime));
		m_pStageName[i]->ChangeGuiState(GUI_MODE::GRADUALLY_DESELECT);

#ifdef _DEBUG

		//CDebugProc::Print("X���W:%f\n", tmpObjPos.x);
		//CDebugProc::Print("Z���W:%f\n", tmpObjPos.z);
		CDebugProc::Print("�q���O���p�̌W��:%f\n", m_Obj[i].fLenCoff);

#endif

	}

	int levelCnt(1);
	D3DXCOLOR tmpCol;
	// ��Փx�����p�́�
	for (int j = 0; j < MAX_LEVEL; j++)
	{

		tmpCol = m_pLevelStar[j]->GetDiff();
		m_pLevelStar[j]->SetDiffuse(tmpCol.r, tmpCol.g, tmpCol.b, 1.0f - tmpTime);
		m_pLevelStar[j]->SetDiff(D3DXCOLOR(tmpCol.r, tmpCol.g, tmpCol.b, 1.0f - tmpTime));
		m_pStageName[j]->ChangeGuiState(GUI_MODE::GRADUALLY_DESELECT);

	}

	// �C�[�W���O�Ȑ��p�^�C�}�[�̍X�V
	if (m_fTime >= 1.0f)
	{
		m_fTime = 0.0f;

		m_nState = STATE::NORMAL;

		for (int i = 0; i < MAX_STAGE; i++)
		{
			m_Obj[i].fLenCoff = m_Obj[m_Obj[i].nDestCnt].fLenCoffDest;
			m_pStageName[i]->ChangeGuiState(GUI_MODE::GRADUALLY_SELECT);
			tmpTime = 0.0f;
		}

		// ��Փx�����p�́�
		for (int j = 0; j < MAX_LEVEL; j++)
		{

			m_pStageName[j]->ChangeGuiState(GUI_MODE::GRADUALLY_SELECT);

		}

		selectStageOld = m_playerData[0].nSelectNum;


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
		//���̃t�F�[�Y��ς���
		CManager::SetAfterScene(PHASETYPE_GAME);
	}

}
//=============================================================================
// �L�[�{�[�h�ł̑I��
//=============================================================================
void CStageSelect::SelectByButton(void)
{

	// Wii�R���̎擾
	WiiRemote* pTmpPad = CManager::GetWii(1);

	//�T�E���h�擾�̍쐬
	CSound *pSound;
	pSound = CManager::GetSound();

	//�L�[�{�[�h�C���v�b�g�̎󂯎��
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	float fTmpRad = (D3DX_PI * 2.0f) / MAX_STAGE;
	float tmpRot((D3DX_PI * 2.0f));

	//�G���^�[�L�[�������ꂽ�ꍇ
	if (pInputKeyboard->GetKeyTrigger(DIK_RETURN) || pTmpPad->GetKeyTrigger(WII_BUTTOM_A))
	{

		// �J�ڏ���
		pSound->Play(SOUND_LABEL_SE_SELECT002);
		m_nState = STATE::CHANGE_SCENE;

		// �I�������}�b�v��ۑ�
		CManager::SetSelectMap(m_playerData[0].nSelectNum);

		m_pFade->StartFade(FADE_IN, 100, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), CManager::GetSelectChar(0));
		//pSound->PlayVoice(m_playerData[0].nSelectNum,VOICE_LABEL_SE_START);

	}
	else if (pInputKeyboard->GetKeyTrigger(DIK_A) || pInputKeyboard->GetKeyTrigger(DIK_LEFT) || pTmpPad->GetKeyTrigger(WII_BUTTOM_LEFT))
	{

		//pSound->Play(SOUND_LABEL_SE_SELECT000);
		selectStageOld = m_playerData[0].nSelectNum;

		m_playerData[0].nSelectNum--;
		NomalizeSelectObject(m_playerData[0].nSelectNum);

		for (int i = 0; i < MAX_STAGE; i++)
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
	else if (pInputKeyboard->GetKeyTrigger(DIK_D) || pInputKeyboard->GetKeyTrigger(DIK_RIGHT) || pTmpPad->GetKeyTrigger(WII_BUTTOM_RIGHT))
	{
		//pSound->Play(SOUND_LABEL_SE_SELECT000);
		selectStageOld = m_playerData[0].nSelectNum;

		m_playerData[0].nSelectNum++;
		NomalizeSelectObject(m_playerData[0].nSelectNum);

		for (int i = 0; i < MAX_STAGE; i++)
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

		nParamVal = MAX_STAGE - 1;

	}
	else if (nParamVal >= MAX_STAGE)
	{

		nParamVal = 0;

	}

}
////////////EOF////////////
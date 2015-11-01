//=============================================================================
//
// MS_BuildFight [CScenario.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#include "Scenario.h"
#include "Character.h"
#include "../../form/form2D.h"

#include "../../administer/Input.h"
//*****************************************************************************
// �ÓI�ϐ�
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScenario :: CScenario()
{
	m_nCount=0;
	m_ViewFlag=false;
	m_CCharacter = NULL;
	m_window = NULL;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScenario :: ~CScenario(void)
{
}
//=============================================================================
// ����
//=============================================================================
CScenario *CScenario::Create(LPDIRECT3DDEVICE9 pDevice,bool viewflag)
{
	CScenario *pScenario;

	pScenario = new CScenario();
	pScenario->Init(pDevice, viewflag);

	return pScenario;
}
//=============================================================================
// ������
//=============================================================================
HRESULT CScenario::Init(LPDIRECT3DDEVICE9 pDevice, bool viewflag)
{
	m_pDevice = pDevice;

	m_ViewFlag = viewflag;

	//�t�B�[���h�̏�����
	m_CCharacter = CCharacter::Create(m_pDevice, 0, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_window = Cform2D::Create(pDevice, "data/TEXTURE/window.png", D3DXVECTOR3(SCREEN_WIDTH / 2, 650.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1300, 200);

	return S_OK;
}
//=============================================================================
// �I��
//=============================================================================
void CScenario :: Uninit(void)
{
	//�l�X�ȃI�u�W�F�N�g�̏I���i�J���j����
	//m_CCharacter->Uninit();
	//m_window->Uninit();
}
//=============================================================================
// �X�V
//=============================================================================
void CScenario::Update(CInputKeyboard* input)
{
	//�L�[�{�[�h�C���v�b�g�̎󂯎��
	if (input->GetKeyTrigger(DIK_1))
	{
		m_CCharacter->SetCharaType(smile);
	}
	if (input->GetKeyTrigger(DIK_2))
	{
		m_CCharacter->SetCharaType(smile2);
	}
	if (input->GetKeyTrigger(DIK_3))
	{
		m_CCharacter->SetCharaType(star);
	}

	m_CCharacter->Update();
}
//=============================================================================
// �`��
//=============================================================================
void CScenario :: Draw(void)
{
	if(m_ViewFlag)
	{
		m_CCharacter->Draw();

		m_window->Draw();
	}
}
/////////////EOF////////////
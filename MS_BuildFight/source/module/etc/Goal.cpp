//=============================================================================
//
// MS_BuildFight [CGoal.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#include "Goal.h"
#include "../../exten_common.h"
//*****************************************************************************
// �ÓI�ϐ�
//*****************************************************************************
const LPSTR CGoal::m_ModelName[]=
{
	"data/MODEL/goal.x",
	"data/MODEL/goal_ling.x",

};
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGoal :: CGoal()
{
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGoal :: ~CGoal(void)
{
}
//=============================================================================
// CGoal����
//=============================================================================
CGoal *CGoal::Create(LPDIRECT3DDEVICE9 pDevice, int nType, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{

	CGoal *pformX;

	pformX = new CGoal();
	pformX->Init(pDevice, nType, pos, rot);

	return pformX;
}
//=============================================================================
// ������
//=============================================================================
HRESULT CGoal::Init(LPDIRECT3DDEVICE9 pDevice, int nType, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//�f�o�C�X�̎擾
	m_pDevice=pDevice;

	m_pGoal = new CformX;
	m_pGoal -> Init(m_pDevice,m_ModelName[0],NULL);
	m_pGoal->SetPos(pos);
	m_pGoal->SetRot(rot);

	m_pGoalLing = new CformX;
	m_pGoalLing->Init(m_pDevice, m_ModelName[1], NULL);
	m_pGoalLing->SetPos(pos);
	m_pGoalLing->SetRot(rot);

	m_bViewFlag = true;

	m_bGoal = false;

	m_nRotChangeCount = 800;

	m_fChangerot = 0.0f;
	
	Create_VS("source/shader/basicVS.hlsl", "VS", &shaderSet[0].vs, &shaderSet[0].vsc, m_pDevice);
	Create_PS("source/shader/basicPS.hlsl", "PS_GOAL", &shaderSet[0].ps, &shaderSet[0].psc, m_pDevice);

	Create_VS("source/shader/basicVS.hlsl", "VS_GOAL_LING", &shaderSet[1].vs, &shaderSet[1].vsc, m_pDevice);
	Create_PS("source/shader/basicPS.hlsl", "PS_GOAL_LING", &shaderSet[1].ps, &shaderSet[1].psc, m_pDevice);

	m_pGoal->SetShader(shaderSet[0]);
	m_pGoalLing->SetShader(shaderSet[1]);

	return S_OK;
}
//=============================================================================
// �I��
//=============================================================================
void CGoal :: Uninit(void)
{
	//�l�X�ȃI�u�W�F�N�g�̏I���i�J���j����
}
//=============================================================================
// �X�V
//=============================================================================
void CGoal :: Update(void)
{
	D3DXVECTOR3 rot = m_pGoalLing->GetRot();

	if (m_nRotChangeCount > 800)
	{
		m_fChangerot = mersenne_twister_f32(0.1f, 0.3f);

		m_nRotChangeCount = 0;
	}

	rot.x += m_fChangerot;
	rot.y += m_fChangerot*m_fChangerot;
	rot.z += m_fChangerot;

	m_pGoalLing->SetRot(rot);

	m_nRotChangeCount++;

	//�X�V�Ăяo��
	m_pGoal->Update();
	m_pGoalLing->Update();
}
//=============================================================================
// �`��
//=============================================================================
void CGoal :: Draw(void)
{
	if (m_bViewFlag)
	{
		m_pGoal->Draw();
		m_pGoalLing->Draw();
	}
}
/////////////EOF////////////
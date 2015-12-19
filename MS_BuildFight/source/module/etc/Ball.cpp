//=============================================================================
//
// MS_BuildFight [CBall.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#include "Ball.h"
#include "LocusEffect.h"
#include "../../exten_common.h"
#include "../../administer/Debugproc.h"
//*****************************************************************************
// �ÓI�ϐ�
//*****************************************************************************
const LPSTR CBall::m_ModelName[]=
{
	"data/MODEL/ball.x",
	"data/MODEL/ball.x",
	"data/MODEL/ball.x",
	"data/MODEL/ball.x",
	"data/MODEL/ball.x",
};
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBall :: CBall():CformX(OBJTYPE_X,4)
{
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBall :: ~CBall(void)
{
}
//=============================================================================
// CBall����
//=============================================================================
CBall *CBall::Create(LPDIRECT3DDEVICE9 pDevice,int nType,D3DXVECTOR3 movePos,D3DXVECTOR3 moveRot)
{

	CBall *pformX;

	pformX = new CBall();
	pformX->Init(pDevice,nType);
	pformX->SetPos(movePos);
	pformX->SetRot(moveRot);

	return pformX;
}
//=============================================================================
// ������
//=============================================================================
HRESULT CBall :: Init(LPDIRECT3DDEVICE9 pDevice,int nType)
{
	//�f�o�C�X�̎擾
	m_pDevice=pDevice;

	//�����̏�����
	CformX::Init(m_pDevice,m_ModelName[nType],NULL);

	m_bViewFlag = true;

	m_bGoal = false;

	//�G�t�F�N�g�ǉ�
	m_pLocusEffect = CLocusEffect::Create(pDevice, NULL, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pLocusEffect->SetFlag(true);

	//�s�N�Z���V�F�[�_�[�p�ɕϊ�1
	switch (nType)
	{
	case 0:Create_PS("source/shader/basicPS.hlsl", "PS_BALL_ROSA", &shaderSet.ps, &shaderSet.psc, m_pDevice);break;
	case 1:Create_PS("source/shader/basicPS.hlsl", "PS_BALL_LIRA", &shaderSet.ps, &shaderSet.psc, m_pDevice);break;
	case 2:Create_PS("source/shader/basicPS.hlsl", "PS_BALL_THEME", &shaderSet.ps, &shaderSet.psc, m_pDevice);break;
	case 3:Create_PS("source/shader/basicPS.hlsl", "PS_BALL_HAGE", &shaderSet.ps, &shaderSet.psc, m_pDevice); break;
	default:Create_PS("source/shader/basicPS.hlsl", "PS_DIFFUSE", &shaderSet.ps, &shaderSet.psc, m_pDevice); break;
	}

	//�o�[�e�b�N�X�V�F�[�_�[�p�ɕϊ�1
	Create_VS("source/shader/basicVS.hlsl", "VS", &shaderSet.vs, &shaderSet.vsc, m_pDevice);

	CformX::SetShader(shaderSet);

	shot_num = 0;

	m_MovVelocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_RotVelocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_CircleVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_Mass = 1.0f;
	m_MOI = 100.0f;
	m_MovResist = 0.02f;
	m_RotResist = 0.02f;
	m_alpha = 0.4f;

	CformX::SetTexture("data/TEXTURE/tama.jpg", 0);

	m_bmove = false;
	return S_OK;
}
//=============================================================================
// �I��
//=============================================================================
void CBall :: Uninit(void)
{
	//�l�X�ȃI�u�W�F�N�g�̏I���i�J���j����

	CformX::Uninit();

}
//=============================================================================
// �X�V
//=============================================================================
void CBall :: Update(void)
{
	if (m_bmove)
	{
		m_MovVelocity -= m_MovVelocity * m_MovResist;
		m_RotVelocity -= m_RotVelocity * m_RotResist;

		D3DXVECTOR3 pos = CformX::GetPos();
		D3DXVECTOR3 rot = CformX::GetRot();
		rot -= D3DXVECTOR3(m_CircleVec.z + m_CircleVec.y, m_CircleVec.x, 0.0f) * (m_MovVelocity.x + m_MovVelocity.y + m_MovVelocity.z) * 15.0f;
		pos += m_MovVelocity;
		CformX::SetPos(pos);
		CformX::SetRot(rot);
		//�G�t�F�N�g�ɍ��W�ݒ�
		m_pLocusEffect->SetPosBuffer(CformX::GetPos());
		m_pLocusEffect->SetPos(CformX::GetPos());
	}
	CDebugProc::Print("velocity::x:%fy:%f:z:%f\n", m_MovVelocity.x, m_MovVelocity.y, m_MovVelocity.z);
	//�X�V�Ăяo��
	CformX::Update();
}
//=============================================================================
// �`��
//=============================================================================
void CBall :: Draw(void)
{
	shaderSet.psc->SetFloatArray(m_pDevice, "g_ballalpha", (float*)&m_alpha, 1);
	if (m_bViewFlag)
	{
		m_pLocusEffect->Draw();
		CformX::Draw();
	}
}
//=============================================================================
// �������Z
//=============================================================================
void CBall::AddForce(D3DXVECTOR3 Force, D3DXVECTOR3 Position)
{
	m_MovVelocity += Force / m_Mass;
	D3DXVECTOR3 vec, torq;
	vec = Position - CformX::GetPos();
	D3DXVec3Cross(&torq, &vec, &Force);
	m_RotVelocity += torq / m_MOI;
}
//=============================================================================
// �������Z
//=============================================================================
void CBall::AddForce(D3DXVECTOR3 force)
{
	D3DXVECTOR3 acc;
	acc = force / m_Mass;
	m_MovVelocity += acc;
}
/////////////EOF////////////
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
//*****************************************************************************
// �ÓI�ϐ�
//*****************************************************************************
const LPSTR CBall::m_ModelName[]=
{
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

	HRESULT hr;
	LPD3DXBUFFER err;
	LPD3DXBUFFER code;

	//�s�N�Z���V�F�[�_�[�p�ɕϊ�
	hr = D3DXCompileShaderFromFile("source/shader/basicPS.hlsl", NULL, NULL, "PS_DIFFUSE", "ps_2_0", 0, &code, &err, &shaderSet.psc);

	if (FAILED(hr))
	{
		MessageBox(NULL, (LPCSTR)err->GetBufferPointer(), "D3DXCompileShaderFromFile", MB_OK);
		err->Release();
		return false;
	}
	//�V�F�[�_�[�̓o�^
	hr = pDevice->CreatePixelShader((DWORD*)code->GetBufferPointer(), &shaderSet.ps);

	if (FAILED(hr))
	{
		MessageBox(NULL, "FAILED", "CreatePixelShader", MB_OK);
		return false;
	}

	//�o�[�e�b�N�X�V�F�[�_�[�p�ɕϊ�1
	hr = D3DXCompileShaderFromFile("source/shader/basicVS.hlsl", NULL, NULL, "VS", "vs_2_0", 0, &code, &err, &shaderSet.vsc);
	if (FAILED(hr))
	{
		MessageBox(NULL, (LPCSTR)err->GetBufferPointer(), "D3DXCompileShaderFromFile", MB_OK);
		err->Release();
		return false;
	}
	//�V�F�[�_�[�̓o�^
	hr = pDevice->CreateVertexShader((DWORD*)code->GetBufferPointer(), &shaderSet.vs);
	if (FAILED(hr))
	{
		MessageBox(NULL, "FAILED", "CreateVertexShader", MB_OK);
		return false;
	}

	CformX::SetShader(shaderSet);

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
	//�X�V�Ăяo��
	CformX::Update();
}
//=============================================================================
// �`��
//=============================================================================
void CBall :: Draw(void)
{
	if (m_bViewFlag)
	{
		CformX::Draw();
	}
}
/////////////EOF////////////
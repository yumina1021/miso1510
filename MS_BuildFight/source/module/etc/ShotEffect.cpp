//=============================================================================
//
// MS_BuildFight [LocusEffect.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#include "ShotEffect.h"
#include "Camera.h"
#include "../../exten_common.h"
#include "../../administer/Maneger.h"
#include "../../administer/Texture.h"
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CShotEffect :: CShotEffect(OBJTYPE objtype,int nPriority) : Cform3D()
{
	m_Rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_vector = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CShotEffect :: ~CShotEffect(void)
{
}
//=============================================================================
// CShotEffect����
//=============================================================================
CShotEffect *CShotEffect::Create(LPDIRECT3DDEVICE9 pDevice,int pTexName,D3DXVECTOR3 pos,D3DXVECTOR3 rot)
{
	CShotEffect *pLocusEffect;

	pLocusEffect = new CShotEffect();
	pLocusEffect->Init(pDevice,pTexName);
	pLocusEffect->SetPos(pos);

	return pLocusEffect;
}
//=============================================================================
// ������
//=============================================================================
HRESULT CShotEffect :: Init(LPDIRECT3DDEVICE9 pDevice,int pTexName)
{
	m_pDevice = pDevice;
	Cform3D::Init(pDevice,pTexName,10.0f,10.0f);
	return S_OK;
}
//=============================================================================
// �I��
//=============================================================================
void CShotEffect :: Uninit(void)
{
	Cform3D::Uninit();
}
//=============================================================================
// �X�V
//=============================================================================
void CShotEffect :: Update(void)
{
	if (m_bFlag)
	{
		m_Pos += m_vector + m_vectorrand;
		m_Rot.x += 0.01f;
		m_Rot.y += 0.01f;
	}
	else
	{

	}
	Cform3D::SetPos(m_Pos);
	Cform3D::SetRot(m_Rot);
	Cform3D::Update();
}
//=============================================================================
// �`��
//=============================================================================
void CShotEffect::Draw(void)
{
	if (m_bFlag)
	{
		m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		Cform3D::Draw2();
		m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	}
}

//=============================================================================
// �Z�b�g
//=============================================================================
//void CShotEffect :: SetPosBuffer(D3DXVECTOR3 pos1,D3DXVECTOR3 pos2,D3DXMATRIX mtxWorld)
void CShotEffect :: SetPosBuffer(D3DXVECTOR3 pos)
{
}
/////////////EOF////////////
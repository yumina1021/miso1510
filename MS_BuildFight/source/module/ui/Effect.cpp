//=============================================================================
//
// MS_BuildFight [CEffect.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#include "Effect.h"
//*****************************************************************************
// �ÓI�ϐ�
//*****************************************************************************
const LPSTR CEffect::m_apTextureName[]=
{
	"data/TEXTURE/circuit.png",
	"data/TEXTURE/effect002.png",
	"data/TEXTURE/effect003.png",
	"data/TEXTURE/effect000.png",
	"data/TEXTURE/effect010.png",
	"data/TEXTURE/Enemyeffect001.png",
	"data/TEXTURE/Enemyeffect002.png",
	"data/TEXTURE/Enemyeffect003.png",
	"data/TEXTURE/Enemyeffect000.png",
	"data/TEXTURE/Enemyeffect010.png",
	"data/TEXTURE/tutrial001.png",
	"data/TEXTURE/tutrial002.png",
	"data/TEXTURE/tutrial003.jpg",
	"data/TEXTURE/tutrial004.jpg",
	"data/TEXTURE/tutrial005.jpg",
	"data/TEXTURE/tutrial006.png",
	"data/TEXTURE/tutrial007.png",
	"data/TEXTURE/tutrial008.png",
	"data/TEXTURE/Selecteffect001.png",
	"data/TEXTURE/Selecteffect002.png",
	"data/TEXTURE/Selecteffect003.png",
	"data/TEXTURE/Selecteffect000.png",
	"data/TEXTURE/Selecteffect010.png",
	"data/TEXTURE/Selecteffect999.png",
	"data/TEXTURE/Selecteffect999-1.png",
	"data/TEXTURE/matching.png",
	"data/TEXTURE/ready.png",
	"data/TEXTURE/action.png",
	"data/TEXTURE/win.png",
	"data/TEXTURE/lose.png",
	"data/TEXTURE/timeout.png",
	"data/TEXTURE/replay.png",
	"data/TEXTURE/GameClear2.jpg",
	"data/TEXTURE/GameClear3.jpg"
};
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEffect :: CEffect():Cform2D(OBJTYPE_2D,7)
{
	m_nCount=1;
	m_ViewFlag=false;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEffect :: ~CEffect(void)
{
}
//=============================================================================
// CEffect����
//=============================================================================
CEffect *CEffect::Create(LPDIRECT3DDEVICE9 pDevice,EffectNum nType,D3DXVECTOR3 movePos,D3DXVECTOR3 moveRot)
{
	CEffect *pform2D;

	pform2D = new CEffect();
	pform2D->Init(pDevice,nType,movePos,moveRot);

	return pform2D;
}
//=============================================================================
// ������
//=============================================================================
HRESULT CEffect :: Init(LPDIRECT3DDEVICE9 pDevice,EffectNum nType,D3DXVECTOR3 pos,D3DXVECTOR3 rot)
{
	m_pDevice = pDevice;
	//�t�B�[���h�̏�����
	Cform2D::Init(m_pDevice,m_apTextureName[(int)nType],pos,rot,1300,750);
	return S_OK;
}
//=============================================================================
// �I��
//=============================================================================
void CEffect :: Uninit(void)
{
	//�l�X�ȃI�u�W�F�N�g�̏I���i�J���j����
	Cform2D::Uninit();
}
//=============================================================================
// �X�V
//=============================================================================
void CEffect :: Update(void)
{
	if(m_ViewFlag)
	{
		//�X�V�Ăяo��
		Cform2D::Update();

		if(m_nCount<0)
		{
			m_nCount=0;
			m_ViewFlag=false;
		}else
		{
			m_nCount--;
		}
	}
}
//=============================================================================
// �`��
//=============================================================================
void CEffect :: Draw(void)
{
	if(m_ViewFlag)
	{
		Cform2D::Draw();
	}
}
/////////////EOF////////////
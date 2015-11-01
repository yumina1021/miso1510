//=============================================================================
//
// MS_BuildFight [CCharacter.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#include "Character.h"
//*****************************************************************************
// �ÓI�ϐ�
//*****************************************************************************
const LPSTR CCharacter::m_apTextureName[]=
{
	"data/TEXTURE/character/enisi/�ʏ�.png",
	"data/TEXTURE/character/enisi/�Ί�.png",
	"data/TEXTURE/character/enisi/�Ί�J��.png",
	"data/TEXTURE/character/enisi/�_�l�X�^�C��.png",
	"data/TEXTURE/character/enisi/�ɂւ�.png",
	"data/TEXTURE/character/enisi/�Ƃ�.png",
	"data/TEXTURE/character/enisi/����[��.png",
	"data/TEXTURE/character/enisi/�n�[�g��.png",
	"data/TEXTURE/character/enisi/�͂��.png",
	"data/TEXTURE/character/enisi/����.png",
	"data/TEXTURE/character/enisi/����.png",
	"data/TEXTURE/character/enisi/�{��.png",
	"data/TEXTURE/character/enisi/�ڕ�.png",
	"data/TEXTURE/character/enisi/�ܖ�.png"
};
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCharacter :: CCharacter():Cform2D(OBJTYPE_2D,7)
{
	m_nCount=1;
	m_ViewFlag=true;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCharacter :: ~CCharacter(void)
{
}
//=============================================================================
// CCharacter����
//=============================================================================
CCharacter *CCharacter::Create(LPDIRECT3DDEVICE9 pDevice, int nType, D3DXVECTOR3 movePos, D3DXVECTOR3 moveRot)
{
	CCharacter *pform2D;

	pform2D = new CCharacter();
	pform2D->Init(pDevice,nType,movePos,moveRot);

	return pform2D;
}
//=============================================================================
// ������
//=============================================================================
HRESULT CCharacter::Init(LPDIRECT3DDEVICE9 pDevice, int nType, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_pDevice = pDevice;
	//�t�B�[���h�̏�����
	Cform2D::Init(m_pDevice,m_apTextureName[(int)nType],pos,rot,1300,750);
	return S_OK;
}
//=============================================================================
// �I��
//=============================================================================
void CCharacter :: Uninit(void)
{
	//�l�X�ȃI�u�W�F�N�g�̏I���i�J���j����
	Cform2D::Uninit();
}
//=============================================================================
// �X�V
//=============================================================================
void CCharacter :: Update(void)
{
	if(m_ViewFlag)
	{
		//�X�V�Ăяo��
		Cform2D::Update();

		//�G�ύX
		if (m_charaType != m_charaTypeOld)
		{
			Cform2D::SetTexture(m_apTextureName[(int)m_charaType]);
		}

		m_charaTypeOld = m_charaType;
	}
}
//=============================================================================
// �`��
//=============================================================================
void CCharacter :: Draw(void)
{
	if(m_ViewFlag)
	{
		Cform2D::Draw();
	}
}
/////////////EOF////////////
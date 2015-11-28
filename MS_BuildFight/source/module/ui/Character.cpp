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
#include <string>

#define CHARA_ROSA_TEXTURE		"data/TEXTURE/character/rosa/"
#define CHARA_LILA_TEXTURE		"data/TEXTURE/character/lila/"
#define CHARA_OJYO_TEXTURE		"data/TEXTURE/character/ojyo/"
#define CHARA_TUORIAL_TEXTURE	"data/TEXTURE/character/tutorial/"

//*****************************************************************************
// �ÓI�ϐ�
//*****************************************************************************
const LPSTR CCharacter::m_apTextureName[] =
{
	"normal.png",
	"wara.png",
	"do.png",
	"naki.png"
};
/*
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
*/
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

	nType = 1;

	m_facialType = FACIAL_SMILE;
	m_facialTypeOld = m_facialType;

	switch (nType)
	{
		case 0:m_nCharaPas = CHARA_ROSA_TEXTURE; break;
		case 1:m_nCharaPas = CHARA_LILA_TEXTURE; break;
		case 2:m_nCharaPas = CHARA_OJYO_TEXTURE; break;
		case 3:m_nCharaPas = CHARA_TUORIAL_TEXTURE; break;
	}

	for (int i = 0; i < FACE_MAX; i++)
	{
		std::string str1 = m_nCharaPas;
		std::string str2 = m_apTextureName[i];
		str1 += str2;
		D3DXCreateTextureFromFile(m_pDevice, (char *)str1.c_str(), &m_pTexture[i]);
	}

	//�t�B�[���h�̏�����
	Cform2D::Init2(m_pDevice, m_pTexture[m_facialType], pos, rot, 500, 750);
	return S_OK;
}
//=============================================================================
// �I��
//=============================================================================
void CCharacter :: Uninit(void)
{
	//�l�X�ȃI�u�W�F�N�g�̏I���i�J���j����
	Cform2D::Uninit2();
	for (int i = 0; i < FACE_MAX; i++)
	{
		if (m_pTexture[i] != NULL)
		{
			m_pTexture[i]->Release();
			m_pTexture[i] = NULL;
		}
	}
}
//=============================================================================
// �X�V
//=============================================================================
void CCharacter :: Update(void)
{
	//�X�V�Ăяo��
	Cform2D::Update();

	//�G�ύX
	if (m_facialType != m_facialTypeOld)
	{
		if (m_facialType != FACIAL_NONE)
		{
			m_ViewFlag = true;

			Cform2D::SetTexture(m_pTexture[m_facialType]);
		}
		else
		{
			m_ViewFlag = false;
		}
	}

	m_facialTypeOld = m_facialType;
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
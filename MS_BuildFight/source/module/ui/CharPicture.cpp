//=============================================================================
//
// MS_BuildFight [CCharPicture.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#include "CharPicture.h"
//*****************************************************************************
// �ÓI�ϐ�
//*****************************************************************************
const LPSTR CCharPicture::m_apTextureName[]=
{
	"data/TEXTURE/t_start.png",
	"data/TEXTURE/t_vs.png",
	"data/TEXTURE/t_tutorial.png",
	"data/TEXTURE/t_end.png",

	"data/TEXTURE/s_0.png",
	"data/TEXTURE/s_1.png",
	"data/TEXTURE/s_2.png",
	"data/TEXTURE/s_3.png",
	"data/TEXTURE/s_4.png",
	"data/TEXTURE/s_5.png",
	"data/TEXTURE/s_6.png",
	"data/TEXTURE/n_b.png",
	"data/TEXTURE/s_99.png",

	"data/TEXTURE/p_continue.png",
	"data/TEXTURE/p_retry.png",
	"data/TEXTURE/p_quit.png"

};
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCharPicture :: CCharPicture():Cform2D(OBJTYPE_PAUSE,7),
m_Len(0.0f, 0.0f, 0.0f)
{
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCharPicture :: ~CCharPicture(void)
{
}
//=============================================================================
// CCharPicture����
//=============================================================================
CCharPicture *CCharPicture::Create(LPDIRECT3DDEVICE9 pDevice,PictureNum nType,D3DXVECTOR3 pos,float fwidth,float fheight)
{
	CCharPicture *pform2D;

	pform2D = new CCharPicture();
	pform2D->Init(pDevice,nType,pos,fwidth,fheight);

	return pform2D;
}
//=============================================================================
// ������
//=============================================================================
HRESULT CCharPicture :: Init(LPDIRECT3DDEVICE9 pDevice,PictureNum nType,D3DXVECTOR3 pos,float fwidth,float fheight)
{
	m_pDevice = pDevice;
	//�t�B�[���h�̏�����
	Cform2D::Init(m_pDevice,m_apTextureName[(int)nType],pos,D3DXVECTOR3(0.0f,0.0f,0.0f),fwidth,fheight);
	m_Len = D3DXVECTOR3(fwidth, fheight, 0.0f);
	return S_OK;
}
//=============================================================================
// �I��
//=============================================================================
void CCharPicture :: Uninit(void)
{
	//�l�X�ȃI�u�W�F�N�g�̏I���i�J���j����
	Cform2D::Uninit();
}
//=============================================================================
// �X�V
//=============================================================================
void CCharPicture :: Update(void)
{
	Cform2D::Update();
}
//=============================================================================
// �`��
//=============================================================================
void CCharPicture :: Draw(void)
{
	Cform2D::Draw();
}
/////////////EOF////////////
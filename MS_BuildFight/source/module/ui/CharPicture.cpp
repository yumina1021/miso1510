//=============================================================================
//
// MS_BuildFight [CCharPicture.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#include "CharPicture.h"
//*****************************************************************************
// 静的変数
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
// コンストラクタ
//=============================================================================
CCharPicture :: CCharPicture():Cform2D(OBJTYPE_PAUSE,7)
{
}
//=============================================================================
// デストラクタ
//=============================================================================
CCharPicture :: ~CCharPicture(void)
{
}
//=============================================================================
// CCharPicture生成
//=============================================================================
CCharPicture *CCharPicture::Create(LPDIRECT3DDEVICE9 pDevice,PictureNum nType,D3DXVECTOR3 pos,float fwidth,float fheight)
{
	CCharPicture *pform2D;

	pform2D = new CCharPicture();
	pform2D->Init(pDevice,nType,pos,fwidth,fheight);

	return pform2D;
}
//=============================================================================
// 初期化
//=============================================================================
HRESULT CCharPicture :: Init(LPDIRECT3DDEVICE9 pDevice,PictureNum nType,D3DXVECTOR3 pos,float fwidth,float fheight)
{
	m_pDevice = pDevice;
	//フィールドの初期化
	Cform2D::Init(m_pDevice,m_apTextureName[(int)nType],pos,D3DXVECTOR3(0.0f,0.0f,0.0f),fwidth,fheight);
	return S_OK;
}
//=============================================================================
// 終了
//=============================================================================
void CCharPicture :: Uninit(void)
{
	//様々なオブジェクトの終了（開放）処理
	Cform2D::Uninit();
}
//=============================================================================
// 更新
//=============================================================================
void CCharPicture :: Update(void)
{
	Cform2D::Update();
}
//=============================================================================
// 描画
//=============================================================================
void CCharPicture :: Draw(void)
{
	Cform2D::Draw();
}
/////////////EOF////////////
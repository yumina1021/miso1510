//=============================================================================
//
// MS_BuildFight [CCharacter.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#include "Character.h"
#include "../../administer/Texture.h"
#include <string>

#define CHARA_ROSA_TEXTURE		"data/TEXTURE/character/rosa/"	//0
#define CHARA_LILA_TEXTURE		"data/TEXTURE/character/lila/"	//1
#define CHARA_OJYO_TEXTURE		"data/TEXTURE/character/licht/"	//2
#define CHARA_TUORIAL_TEXTURE	"data/TEXTURE/character/navi/"	//3

//*****************************************************************************
// 静的変数
//*****************************************************************************
const int CCharacter::m_apTextureName[][4] =
{
	{ TEXTURE_C_ROSA_NORMAL,
	  TEXTURE_C_ROSA_WARA,
	  TEXTURE_C_ROSA_DO,
	  TEXTURE_C_ROSA_NAKI },

	{ TEXTURE_C_LILA_NORMAL,
	  TEXTURE_C_LILA_WARA,
	  TEXTURE_C_LILA_DO,
	  TEXTURE_C_LILA_NAKI },

	{ TEXTURE_C_LICHT_NORMAL,
	  TEXTURE_C_LICHT_WARA,
	  TEXTURE_C_LICHT_DO,
	  TEXTURE_C_LICHT_NAKI },

	{ TEXTURE_C_NAVI_NORMAL,
	  TEXTURE_C_NAVI_WARA,
	  TEXTURE_C_NAVI_DO,
	  TEXTURE_C_NAVI_NAKI },
};
/*
const LPSTR CCharacter::m_apTextureName[]=
{
	"data/TEXTURE/character/enisi/通常.png",
	"data/TEXTURE/character/enisi/笑顔.png",
	"data/TEXTURE/character/enisi/笑顔開口.png",
	"data/TEXTURE/character/enisi/神様スタイル.png",
	"data/TEXTURE/character/enisi/にへら.png",
	"data/TEXTURE/character/enisi/照れ.png",
	"data/TEXTURE/character/enisi/きらーん.png",
	"data/TEXTURE/character/enisi/ハート目.png",
	"data/TEXTURE/character/enisi/はわわ.png",
	"data/TEXTURE/character/enisi/驚き.png",
	"data/TEXTURE/character/enisi/困り.png",
	"data/TEXTURE/character/enisi/怒り.png",
	"data/TEXTURE/character/enisi/目閉じ.png",
	"data/TEXTURE/character/enisi/涙目.png"
};
*/
//=============================================================================
// コンストラクタ
//=============================================================================
CCharacter :: CCharacter():Cform2D(OBJTYPE_2D,7)
{
	m_nCount=1;
	m_ViewFlag=true;
}
//=============================================================================
// デストラクタ
//=============================================================================
CCharacter :: ~CCharacter(void)
{
}
//=============================================================================
// CCharacter生成
//=============================================================================
CCharacter *CCharacter::Create(LPDIRECT3DDEVICE9 pDevice, int nType, D3DXVECTOR3 movePos, D3DXVECTOR3 moveRot)
{
	CCharacter *pform2D;

	pform2D = new CCharacter();
	pform2D->Init(pDevice,nType,movePos,moveRot);

	return pform2D;
}
//=============================================================================
// 初期化
//=============================================================================
HRESULT CCharacter::Init(LPDIRECT3DDEVICE9 pDevice, int nType, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_pDevice = pDevice;

	m_facialType = FACIAL_SMILE;
	m_facialTypeOld = m_facialType;

	m_charid = nType;


	if (nType == 0)
	{
		//フィールドの初期化
		Cform2D::Init(m_pDevice, m_apTextureName[m_charid][m_facialType], pos, rot, 625, 750);
	}
	else
	{
		//フィールドの初期化
		Cform2D::Init(m_pDevice, m_apTextureName[m_charid][m_facialType], pos, rot, 500, 750);
	}
	return S_OK;
}
//=============================================================================
// 終了
//=============================================================================
void CCharacter :: Uninit(void)
{
	//様々なオブジェクトの終了（開放）処理
	Cform2D::Uninit2();
	//for (int i = 0; i < FACE_MAX; i++)
	//{
	//	if (m_pTexture[i] != NULL)
	//	{
	//		m_pTexture[i]->Release();
	//		m_pTexture[i] = NULL;
	//	}
	//}
}
//=============================================================================
// 更新
//=============================================================================
void CCharacter :: Update(void)
{
	//更新呼び出し
	Cform2D::Update();

	//絵変更
	if (m_facialType != m_facialTypeOld)
	{
		if (m_facialType != FACIAL_NONE)
		{
			m_ViewFlag = true;

			Cform2D::SetTexture(m_apTextureName[m_charid][m_facialType]);
		}
		else
		{
			m_ViewFlag = false;
		}
	}

	m_facialTypeOld = m_facialType;
}
//=============================================================================
// 描画
//=============================================================================
void CCharacter :: Draw(void)
{
	if(m_ViewFlag)
	{
		Cform2D::Draw();
	}
}
/////////////EOF////////////
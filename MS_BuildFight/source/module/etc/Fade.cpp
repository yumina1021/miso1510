//=============================================================================
//
// MS_BuildFight [CFade.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#include "Fade.h"
//*****************************************************************************
// 静的変数
//*****************************************************************************
const LPSTR CFade::m_apTextureName[]=
{
	"data/TEXTURE/loading001.jpg"
};
//=============================================================================
// コンストラクタ
//=============================================================================
CFade :: CFade():Cform2D(OBJTYPE_2D,7)
{
}
//=============================================================================
// デストラクタ
//=============================================================================
CFade :: ~CFade(void)
{
}
//=============================================================================
// CFade生成
//=============================================================================
CFade *CFade::Create(LPDIRECT3DDEVICE9 pDevice,int type)
{
	CFade *pform2D;

	pform2D = new CFade();
	pform2D->Init(pDevice,type);

	return pform2D;
}
//=============================================================================
// 初期化
//=============================================================================
HRESULT CFade :: Init(LPDIRECT3DDEVICE9 pDevice,int type)
{
	m_pDevice = pDevice;
	//フィールドの初期化
	if(type==0)
	{
		Cform2D::Init(m_pDevice,NULL,D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),SCREEN_WIDTH,SCREEN_HEIGHT);
	}else
	{
		Cform2D::Init(m_pDevice,m_apTextureName[0],D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),SCREEN_WIDTH,SCREEN_HEIGHT);
	}

	m_bfade=false;
	m_color=D3DXCOLOR(1.0f,1.0f,1.0f,0.0f);
	m_fAlpha=0.0f;
	m_nCount=0;

	return S_OK;
}
//=============================================================================
// 終了
//=============================================================================
void CFade :: Uninit(void)
{
	//様々なオブジェクトの終了（開放）処理
	Cform2D::Uninit();
}
//=============================================================================
// 更新
//=============================================================================
void CFade :: Update(void)
{
	if(m_bfade)
	{
		switch(m_fadeType)
		{
			case FADE_IN:
						//アルファを255に進めていく
						m_fAlpha+=1.0f/m_nCount;

						if(m_fAlpha>=1.0f)
						{
							m_fAlpha=1.0f;
						}

						m_nCount--;

						//時間がたったらフェードアウトに
						if(m_nCount<=0)
						{
							m_fadeType=FADE_IN_END;
							m_nCount=0;
						}
						break;
			case FADE_IN_END:
						break;
			case FADE_OUT:
						//アルファを0に進めていく
						m_fAlpha-=1.0f/m_nCount;

						if(m_fAlpha<=0.0f)
						{
							m_fAlpha=0.0f;
						}

						m_nCount--;

						if(m_nCount<=0)
						{
							m_fadeType=FADE_OUT_END;
							m_nCount=0;
						}
						break;
			case FADE_OUT_END:
						m_fAlpha=0.0f;
						m_fadeType=FADE_NONE;
						m_bfade=false;
						break;
		}

		m_color.a=m_fAlpha;

		Cform2D::SetDiffuse(m_color.r,m_color.g,m_color.b,m_color.a);

		Cform2D::Update();
	}
}
//=============================================================================
// 描画
//=============================================================================
void CFade :: Draw(void)
{
	if(m_bfade)
	{
		Cform2D::Draw();
	}
}

void CFade ::StartFade(FADEMODE fade,int nCount,D3DXCOLOR color)
{
	m_fadeType=fade;
	m_nCount=nCount;
	m_color=color;
	m_fAlpha=m_color.a;
	m_bfade=true;
}
/////////////EOF////////////
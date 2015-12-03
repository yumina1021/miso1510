//=============================================================================
//
// MS_BuildFight [CCount.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#include "Count.h"
#include "Number.h"
//=============================================================================
// コンストラクタ
//=============================================================================
CCount :: CCount(int nPriority) : Cform(OBJTYPE_2D,nPriority)
{
	//ポリゴンの回転値初期化
	for(int i=0;i<COUNT_FIGURE_MAX;i++)
	{
		m_pNumber[i]=NULL;
	}
}
//=============================================================================
// デストラクタ
//=============================================================================
CCount :: ~CCount(void)
{
}
//=============================================================================
// CCount生成
//=============================================================================
CCount *CCount::Create(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 pos,D3DXVECTOR3 rot,int initCnt)
{
	CCount *pCount;

	pCount = new CCount();
	pCount->Init(pDevice,pos,rot,initCnt);

	return pCount;
}
//=============================================================================
// 初期化
//=============================================================================
HRESULT CCount :: Init(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 pos,D3DXVECTOR3 rot,int initCnt)
{
	m_pDevice=pDevice;

	m_Pos=pos;
	m_Rot=rot;

	m_nCount=initCnt;

	m_bViewFlag = true;

	for(int i=0;i<COUNT_FIGURE_MAX;i++)
	{
		m_pNumber[i]=CNumber::Create(m_pDevice,D3DXVECTOR3(m_Pos.x+(i*30),m_Pos.y+27,m_Pos.z),D3DXCOLOR(0.0f,0.0f,1.0f,1.0f),35,70);
	}

	ResetCount(m_nCount);

	return S_OK;
}
//=============================================================================
// 終了
//=============================================================================
void CCount :: Uninit(void)
{
	//様々なオブジェクトの終了（開放）処理
	for(int i=0;i<COUNT_FIGURE_MAX;i++)
	{
		m_pNumber[i]->Uninit();
	}

	Cform::Release();
}
//=============================================================================
// 更新
//=============================================================================
void CCount :: Update(void)
{
	for(int i=0;i<COUNT_FIGURE_MAX;i++)
	{
		m_pNumber[i]->Update();
	}
}
//=============================================================================
// 描画
//=============================================================================
void CCount :: Draw(void)
{
	if (m_bViewFlag)
	{
		for (int i = 0; i<COUNT_FIGURE_MAX; i++)
		{
			m_pNumber[i]->Draw();
		}
	}
}
//=============================================================================
// ポリゴン加算関数
//=============================================================================
void CCount :: AddCount(int nValue)
{
	//保管管理用
	int nCountlock;

	//点数の加算
	m_nCount+=nValue;

	//範囲チェック
	if(m_nCount>SCORE_MAX)
	{
		m_nCount=SCORE_MAX;
	}else
	if(m_nCount<0)
	{
		m_nCount=0;
	}

	nCountlock=m_nCount;

	//点数挿入
	for(int i=COUNT_FIGURE_MAX;i>0;i--)
	{
		float nNumber;

		if(nCountlock!=0)
		{
			nNumber=(float)((nCountlock%((int)pow(10.0f,i)))/(int)pow(10.0f,i-1));
		}
		else
		{
			nNumber=0;
		}

		nNumber/=10;

		m_pNumber[COUNT_FIGURE_MAX-i]->SetNumber(nNumber);
	}
}

void CCount :: ResetCount(int nSet)
{
	//保管管理用
	int nCountlock=0;

	m_nCount=nSet;

	nCountlock=m_nCount;

	//点数挿入
	for(int i=COUNT_FIGURE_MAX;i>0;i--)
	{
		float nNumber;

		if(nCountlock!=0)
		{
			nNumber=(float)((nCountlock%((int)pow(10.0f,i)))/(int)pow(10.0f,i-1));
		}
		else
		{
			nNumber=0;
		}

		nNumber/=10;

		m_pNumber[COUNT_FIGURE_MAX-i]->SetNumber(nNumber);
	}
}
void CCount::ChangeColor(D3DXCOLOR color)
{
	for(int i=0;i<COUNT_FIGURE_MAX;i++)
	{
		m_pNumber[i]->SetColor(color);
	}
}

/////////////EOF////////////
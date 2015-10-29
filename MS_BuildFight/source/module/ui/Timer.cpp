//=============================================================================
//
// MS_BuildFight [CTimer.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#include "Timer.h"
#include "Number.h"
//=============================================================================
// コンストラクタ
//=============================================================================
CTimer :: CTimer(int nPriority) : Cform(OBJTYPE_TIMER,nPriority)
{
	//ポリゴンの回転値初期化
	for(int i=0;i<FIGURE_MAX;i++)
	{
		m_pNumber[i]=NULL;
	}
}
//=============================================================================
// デストラクタ
//=============================================================================
CTimer :: ~CTimer(void)
{
}
//=============================================================================
// CTimer生成
//=============================================================================
CTimer *CTimer::Create(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 pos,D3DXVECTOR3 rot)
{
	CTimer *pTimer;

	pTimer = new CTimer();
	pTimer->Init(pDevice,pos,rot);

	return pTimer;
}
//=============================================================================
// 初期化
//=============================================================================
HRESULT CTimer :: Init(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 pos,D3DXVECTOR3 rot)
{
	m_pDevice=pDevice;

	m_Pos=pos;
	m_Rot=rot;

	m_nTimer=TIMER_MAX;

	for(int i=0;i<FIGURE_MAX;i++)
	{
		m_pNumber[i]=CNumber::Create(m_pDevice,D3DXVECTOR3(m_Pos.x+(i*30),m_Pos.y+25,m_Pos.z),D3DXCOLOR(0.0f,0.0f,1.0f,1.0f),30,50);
	}

	ResetTimer(m_nTimer);

	return S_OK;
}
//=============================================================================
// 終了
//=============================================================================
void CTimer :: Uninit(void)
{
	//様々なオブジェクトの終了（開放）処理
	for(int i=0;i<FIGURE_MAX;i++)
	{
		m_pNumber[i]->Uninit();
	}

	Cform::Release();
}
//=============================================================================
// 更新
//=============================================================================
void CTimer :: Update(void)
{
	for(int i=0;i<FIGURE_MAX;i++)
	{
		m_pNumber[i]->Update();
	}
}
//=============================================================================
// 描画
//=============================================================================
void CTimer :: Draw(void)
{
	for(int i=0;i<FIGURE_MAX;i++)
	{
		m_pNumber[i]->Draw();
	}
}
//=============================================================================
// ポリゴン加算関数
//=============================================================================
void CTimer :: AddTimer(int nValue)
{
	//保管管理用
	int nTimerlock;

	//点数の加算
	m_nTimer+=nValue;

	//範囲チェック
	if(m_nTimer>TIMER_MAX)
	{
		m_nTimer=TIMER_MAX;
	}else
	if(m_nTimer<0)
	{
		m_nTimer=0;
	}

	nTimerlock=m_nTimer;

	//点数挿入
	for(int i=FIGURE_MAX;i>0;i--)
	{
		float nNumber;

		if(nTimerlock!=0)
		{
			nNumber=(float)((nTimerlock%((int)pow(10.0f,i)))/(int)pow(10.0f,i-1));
		}
		else
		{
			nNumber=0;
		}

		nNumber/=10;

		m_pNumber[FIGURE_MAX-i]->SetNumber(nNumber);
	}
}

void CTimer :: ResetTimer(int nSet)
{
	//保管管理用
	int nTimerlock=0;

	m_nTimer=nSet;

	nTimerlock=m_nTimer;

	//点数挿入
	for(int i=FIGURE_MAX;i>0;i--)
	{
		float nNumber;

		if(nTimerlock!=0)
		{
			nNumber=(float)((nTimerlock%((int)pow(10.0f,i)))/(int)pow(10.0f,i-1));
		}
		else
		{
			nNumber=0;
		}

		nNumber/=10;

		m_pNumber[FIGURE_MAX-i]->SetNumber(nNumber);
	}
}
/////////////EOF////////////
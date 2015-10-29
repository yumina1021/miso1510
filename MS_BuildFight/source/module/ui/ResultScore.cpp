//=============================================================================
//
// MS_BuildFight [CReScore.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#include "ResultScore.h"
#include "Number.h"
//=============================================================================
// コンストラクタ
//=============================================================================
CReScore :: CReScore(int nPriority) : Cform(OBJTYPE_2D,nPriority)
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
CReScore :: ~CReScore(void)
{
}
//=============================================================================
// CReScore生成
//=============================================================================
CReScore *CReScore::Create(LPDIRECT3DDEVICE9 pDevice,int score,D3DXVECTOR3 pos,D3DXVECTOR3 rot)
{
	CReScore *pReScore;

	pReScore = new CReScore();
	pReScore->Init(pDevice,score,pos,rot);

	return pReScore;
}
//=============================================================================
// 初期化
//=============================================================================
HRESULT CReScore :: Init(LPDIRECT3DDEVICE9 pDevice,int score,D3DXVECTOR3 pos,D3DXVECTOR3 rot)
{
	m_pDevice=pDevice;

	m_Pos=pos;
	m_Rot=rot;

	m_nReScore=score;

	for(int i=0;i<FIGURE_MAX;i++)
	{
		m_pNumber[i]=CNumber::Create(m_pDevice,D3DXVECTOR3(m_Pos.x+(i*60),m_Pos.y+30,m_Pos.z),D3DXCOLOR(0.0f,0.0f,1.0f,1.0f),70,100);
	}

	ResetReScore(m_nReScore);

	return S_OK;
}
//=============================================================================
// 終了
//=============================================================================
void CReScore :: Uninit(void)
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
void CReScore :: Update(void)
{
	for(int i=0;i<FIGURE_MAX;i++)
	{
		m_pNumber[i]->Update();
	}
}
//=============================================================================
// 描画
//=============================================================================
void CReScore :: Draw(void)
{
	for(int i=0;i<FIGURE_MAX;i++)
	{
		m_pNumber[i]->Draw();
	}
}
//=============================================================================
// ポリゴン加算関数
//=============================================================================
void CReScore :: AddReScore(int nValue)
{
	//保管管理用
	int nReScorelock;

	//点数の加算
	m_nReScore+=nValue;

	//範囲チェック
	if(m_nReScore>SCORE_MAX)
	{
		m_nReScore=SCORE_MAX;
	}else
	if(m_nReScore<0)
	{
		m_nReScore=0;
	}

	nReScorelock=m_nReScore;

	//点数挿入
	for(int i=FIGURE_MAX;i>0;i--)
	{
		float nNumber;

		if(nReScorelock!=0)
		{
			nNumber=(float)((nReScorelock%((int)pow(10.0f,i)))/(int)pow(10.0f,i-1));
		}
		else
		{
			nNumber=0;
		}

		nNumber/=10;

		m_pNumber[FIGURE_MAX-i]->SetNumber(nNumber);
	}
}

void CReScore :: ResetReScore(int nSet)
{
	//保管管理用
	int nReScorelock=0;

	m_nReScore=nSet;

	nReScorelock=m_nReScore;

	//点数挿入
	for(int i=FIGURE_MAX;i>0;i--)
	{
		float nNumber;

		if(nReScorelock!=0)
		{
			nNumber=(float)((nReScorelock%((int)pow(10.0f,i)))/(int)pow(10.0f,i-1));
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
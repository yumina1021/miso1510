//=============================================================================
//
// MS_BuildFight [CScore.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#include "Score.h"
#include "Number.h"
//=============================================================================
// コンストラクタ
//=============================================================================
CScore :: CScore(int nPriority) : Cform(OBJTYPE_2D,nPriority)
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
CScore :: ~CScore(void)
{
}
//=============================================================================
// CScore生成
//=============================================================================
CScore *CScore::Create(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 pos,D3DXVECTOR3 rot,int width,int height)
{
	CScore *pScore;

	pScore = new CScore();
	pScore->Init(pDevice,pos,rot,width,height);

	return pScore;
}
//=============================================================================
// 初期化
//=============================================================================
HRESULT CScore :: Init(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 pos,D3DXVECTOR3 rot,int width,int height)
{
	m_pDevice=pDevice;

	m_Pos=pos;
	m_Rot=rot;

	m_nScore=900;

	for(int i=0;i<FIGURE_MAX;i++)
	{
		m_pNumber[i] = CNumber::Create(m_pDevice, D3DXVECTOR3(m_Pos.x + (i*(width*0.9f)), m_Pos.y + 30, m_Pos.z), D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), (float)width, (float)height);
	}

	ResetScore(m_nScore);

	return S_OK;
}
//=============================================================================
// 終了
//=============================================================================
void CScore :: Uninit(void)
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
void CScore :: Update(void)
{
	for(int i=0;i<FIGURE_MAX;i++)
	{
		m_pNumber[i]->Update();
	}
}
//=============================================================================
// 描画
//=============================================================================
void CScore :: Draw(void)
{
	for(int i=0;i<FIGURE_MAX;i++)
	{
		m_pNumber[i]->Draw();
	}
}
//=============================================================================
// ポリゴン加算関数
//=============================================================================
void CScore :: AddScore(int nValue)
{
	//保管管理用
	int nScorelock;

	//点数の加算
	m_nScore+=nValue;

	//範囲チェック
	if(m_nScore>SCORE_MAX)
	{
		m_nScore=SCORE_MAX;
	}else
	if(m_nScore<0)
	{
		m_nScore=0;
	}

	nScorelock=m_nScore;

	//点数挿入
	for(int i=FIGURE_MAX;i>0;i--)
	{
		float nNumber;

		if(nScorelock!=0)
		{
			nNumber=(float)((nScorelock%((int)pow(10.0f,i)))/(int)pow(10.0f,i-1));
		}
		else
		{
			nNumber=0;
		}

		nNumber/=10;

		m_pNumber[FIGURE_MAX-i]->SetNumber(nNumber);
	}
}

void CScore :: ResetScore(int nSet)
{
	//保管管理用
	int nScorelock=0;

	m_nScore=nSet;

	nScorelock=m_nScore;

	//点数挿入
	for(int i=FIGURE_MAX;i>0;i--)
	{
		float nNumber;

		if(nScorelock!=0)
		{
			nNumber=(float)((nScorelock%((int)pow(10.0f,i)))/(int)pow(10.0f,i-1));
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
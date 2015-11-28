//=============================================================================
//
// MS_BuildFight [CScore.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#include "Score.h"
#include "Number.h"
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScore :: CScore(int nPriority) : Cform(OBJTYPE_2D,nPriority)
{
	//�|���S���̉�]�l������
	for(int i=0;i<FIGURE_MAX;i++)
	{
		m_pNumber[i]=NULL;
	}
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScore :: ~CScore(void)
{
}
//=============================================================================
// CScore����
//=============================================================================
CScore *CScore::Create(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 pos,D3DXVECTOR3 rot,int width,int height)
{
	CScore *pScore;

	pScore = new CScore();
	pScore->Init(pDevice,pos,rot,width,height);

	return pScore;
}
//=============================================================================
// ������
//=============================================================================
HRESULT CScore :: Init(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 pos,D3DXVECTOR3 rot,int width,int height)
{
	m_pDevice=pDevice;

	m_Pos=pos;
	m_Rot=rot;

	m_nScore=0;

	m_bViewFlag = true;

	for(int i=0;i<FIGURE_MAX;i++)
	{
		m_pNumber[i] = CNumber::Create(m_pDevice, D3DXVECTOR3(m_Pos.x + (i*(width*0.9f)), m_Pos.y + 30, m_Pos.z), D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), (float)width, (float)height);
	}

	ResetScore(m_nScore);

	return S_OK;
}
//=============================================================================
// �I��
//=============================================================================
void CScore :: Uninit(void)
{
	//�l�X�ȃI�u�W�F�N�g�̏I���i�J���j����
	for(int i=0;i<FIGURE_MAX;i++)
	{
		m_pNumber[i]->Uninit();
	}

	Cform::Release();
}
//=============================================================================
// �X�V
//=============================================================================
void CScore :: Update(void)
{
	for(int i=0;i<FIGURE_MAX;i++)
	{
		m_pNumber[i]->Update();
	}
}
//=============================================================================
// �`��
//=============================================================================
void CScore :: Draw(void)
{
	if (m_bViewFlag)
	{
		for (int i = 0; i<FIGURE_MAX; i++)
		{
			m_pNumber[i]->Draw();
		}
	}
}
//=============================================================================
// �|���S�����Z�֐�
//=============================================================================
void CScore :: AddScore(int nValue)
{
	//�ۊǊǗ��p
	int nScorelock;

	//�_���̉��Z
	m_nScore+=nValue;

	//�͈̓`�F�b�N
	if(m_nScore>SCORE_MAX)
	{
		m_nScore=SCORE_MAX;
	}else
	if(m_nScore<0)
	{
		m_nScore=0;
	}

	nScorelock=m_nScore;

	//�_���}��
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
	//�ۊǊǗ��p
	int nScorelock=0;

	m_nScore=nSet;

	nScorelock=m_nScore;

	//�_���}��
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
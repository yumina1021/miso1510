//=============================================================================
//
// MS_BuildFight [CCount.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#include "Count.h"
#include "Number.h"
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCount :: CCount(int nPriority) : Cform(OBJTYPE_2D,nPriority)
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
CCount :: ~CCount(void)
{
}
//=============================================================================
// CCount����
//=============================================================================
CCount *CCount::Create(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 pos,D3DXVECTOR3 rot,int initCnt)
{
	CCount *pCount;

	pCount = new CCount();
	pCount->Init(pDevice,pos,rot,initCnt);

	return pCount;
}
//=============================================================================
// ������
//=============================================================================
HRESULT CCount :: Init(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 pos,D3DXVECTOR3 rot,int initCnt)
{
	m_pDevice=pDevice;

	m_Pos=pos;
	m_Rot=rot;

	m_nCount=initCnt;

	for(int i=0;i<FIGURE_MAX;i++)
	{
		m_pNumber[i]=CNumber::Create(m_pDevice,D3DXVECTOR3(m_Pos.x+(i*30),m_Pos.y+27,m_Pos.z),D3DXCOLOR(0.0f,0.0f,1.0f,1.0f),35,55);
	}

	ResetCount(m_nCount);

	return S_OK;
}
//=============================================================================
// �I��
//=============================================================================
void CCount :: Uninit(void)
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
void CCount :: Update(void)
{
	for(int i=0;i<FIGURE_MAX;i++)
	{
		m_pNumber[i]->Update();
	}
}
//=============================================================================
// �`��
//=============================================================================
void CCount :: Draw(void)
{
	for(int i=0;i<FIGURE_MAX;i++)
	{
		m_pNumber[i]->Draw();
	}
}
//=============================================================================
// �|���S�����Z�֐�
//=============================================================================
void CCount :: AddCount(int nValue)
{
	//�ۊǊǗ��p
	int nCountlock;

	//�_���̉��Z
	m_nCount+=nValue;

	//�͈̓`�F�b�N
	if(m_nCount>SCORE_MAX)
	{
		m_nCount=SCORE_MAX;
	}else
	if(m_nCount<0)
	{
		m_nCount=0;
	}

	nCountlock=m_nCount;

	//�_���}��
	for(int i=FIGURE_MAX;i>0;i--)
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

		m_pNumber[FIGURE_MAX-i]->SetNumber(nNumber);
	}
}

void CCount :: ResetCount(int nSet)
{
	//�ۊǊǗ��p
	int nCountlock=0;

	m_nCount=nSet;

	nCountlock=m_nCount;

	//�_���}��
	for(int i=FIGURE_MAX;i>0;i--)
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

		m_pNumber[FIGURE_MAX-i]->SetNumber(nNumber);
	}
}
void CCount::ChangeColor(D3DXCOLOR color)
{
	for(int i=0;i<FIGURE_MAX;i++)
	{
		m_pNumber[i]->SetColor(color);
	}
}

/////////////EOF////////////
//=============================================================================
//
// MS_BuildFight [CGauge.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#include "Gauge.h"
#include "Bar.h"
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGauge :: CGauge(int nPriority) : Cform(OBJTYPE_2D,nPriority)
{
	//�|���S���̉�]�l������
	for(int i=0;i<FIGURE_G_MAX;i++)
	{
		m_pBar[i]=NULL;
	}
	m_bEtype=false;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGauge :: ~CGauge(void)
{
}
//=============================================================================
// CGauge����
//=============================================================================
CGauge *CGauge::Create(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 pos,D3DXVECTOR3 rot,bool Etype)
{
	CGauge *pGauge;

	pGauge = new CGauge();
	pGauge->Init(pDevice,pos,rot,Etype);

	return pGauge;
}
//=============================================================================
// ������
//=============================================================================
HRESULT CGauge :: Init(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 pos,D3DXVECTOR3 rot,bool Etype)
{
	m_pDevice=pDevice;

	m_Pos=pos;
	m_Rot=rot;

	m_nGauge=3000;

	m_bEtype=Etype;

	for(int i=0;i<FIGURE_G_MAX;i++)
	{
		if(m_bEtype)
		{
			m_pBar[i]=CBar::Create(m_pDevice,D3DXVECTOR3(m_Pos.x+(i*60),m_Pos.y,m_Pos.z),D3DXCOLOR(0.8f,0.1f,0.4f,1.0f),90,20);
		}else
		{
			m_pBar[i]=CBar::Create(m_pDevice,D3DXVECTOR3(m_Pos.x+(i*60),m_Pos.y,m_Pos.z),D3DXCOLOR(0.1f,0.8f,0.4f,1.0f),90,20);
		}
	}

	m_nGaugeFigure=FIGURE_G_MAX;

	ResetGauge(m_nGauge);

	m_fView=FIGURE_G_MAX;


	return S_OK;
}
//=============================================================================
// �I��
//=============================================================================
void CGauge :: Uninit(void)
{
	//�l�X�ȃI�u�W�F�N�g�̏I���i�J���j����
	for(int i=0;i<FIGURE_G_MAX;i++)
	{
		m_pBar[i]->Uninit();
	}

	Cform::Release();
}
//=============================================================================
// �X�V
//=============================================================================
void CGauge :: Update(void)
{
	for(int i=0;i<m_nGaugeFigure;i++)
	{
		m_pBar[i]->Update();
	}


}
//=============================================================================
// �`��
//=============================================================================
void CGauge :: Draw(void)
{
	for(int i=0;i<m_nGaugeFigure;i++)
	{
		m_pBar[i]->Draw();
	}
}
//=============================================================================
// �|���S�����Z�֐�
//=============================================================================
void CGauge :: AddGauge(int nValue)
{
	//�ۊǊǗ��p
	int nGaugelock;

	//�_���̉��Z
	m_nGauge+=nValue;

	//�͈̓`�F�b�N
	if(m_nGauge>SCORE_G_MAX)
	{
		m_nGauge=SCORE_G_MAX;
	}else
	if(m_nGauge<0)
	{
		m_nGauge=0;
	}

	nGaugelock=m_nGauge;

	m_fView=(float)nGaugelock/500;
	m_fView+=0.9f;

	if(m_nGaugeFigure<m_fView)
	{
		m_nGaugeFigure-=1;
	}else if(m_nGaugeFigure>m_fView)
	{
		if(FIGURE_G_MAX>m_fView)
		{
			m_nGaugeFigure=(int)m_fView;
		}
	}
}

void CGauge :: ResetGauge(int nSet)
{
	//�ۊǊǗ��p
	int nGaugelock=0;

	m_nGauge=nSet;

	nGaugelock=m_nGauge;

	int m_fView;

	m_fView=nGaugelock/500;

	if(FIGURE_G_MAX>m_fView)
	{
		m_nGaugeFigure=m_fView;
	}else
	{
		m_nGaugeFigure=FIGURE_G_MAX;
	}
}
/////////////EOF////////////
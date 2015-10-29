//=============================================================================
//
// MS_BuildFight [CTimer.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#include "Timer.h"
#include "Number.h"
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTimer :: CTimer(int nPriority) : Cform(OBJTYPE_TIMER,nPriority)
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
CTimer :: ~CTimer(void)
{
}
//=============================================================================
// CTimer����
//=============================================================================
CTimer *CTimer::Create(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 pos,D3DXVECTOR3 rot)
{
	CTimer *pTimer;

	pTimer = new CTimer();
	pTimer->Init(pDevice,pos,rot);

	return pTimer;
}
//=============================================================================
// ������
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
// �I��
//=============================================================================
void CTimer :: Uninit(void)
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
void CTimer :: Update(void)
{
	for(int i=0;i<FIGURE_MAX;i++)
	{
		m_pNumber[i]->Update();
	}
}
//=============================================================================
// �`��
//=============================================================================
void CTimer :: Draw(void)
{
	for(int i=0;i<FIGURE_MAX;i++)
	{
		m_pNumber[i]->Draw();
	}
}
//=============================================================================
// �|���S�����Z�֐�
//=============================================================================
void CTimer :: AddTimer(int nValue)
{
	//�ۊǊǗ��p
	int nTimerlock;

	//�_���̉��Z
	m_nTimer+=nValue;

	//�͈̓`�F�b�N
	if(m_nTimer>TIMER_MAX)
	{
		m_nTimer=TIMER_MAX;
	}else
	if(m_nTimer<0)
	{
		m_nTimer=0;
	}

	nTimerlock=m_nTimer;

	//�_���}��
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
	//�ۊǊǗ��p
	int nTimerlock=0;

	m_nTimer=nSet;

	nTimerlock=m_nTimer;

	//�_���}��
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
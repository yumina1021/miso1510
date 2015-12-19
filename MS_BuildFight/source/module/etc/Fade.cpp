//=============================================================================
//
// MS_BuildFight [CFade.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#include "Fade.h"
//*****************************************************************************
// �ÓI�ϐ�
//*****************************************************************************
const LPSTR CFade::m_apTextureName[]=
{
	"data/TEXTURE/loading1.jpg",
	"data/TEXTURE/loading2.jpg",
	"data/TEXTURE/loading3.jpg",
};
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CFade :: CFade():Cform2D(OBJTYPE_2D,7)
{
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CFade :: ~CFade(void)
{
}
//=============================================================================
// CFade����
//=============================================================================
CFade *CFade::Create(LPDIRECT3DDEVICE9 pDevice,int type)
{
	CFade *pform2D;

	pform2D = new CFade();
	pform2D->Init(pDevice,type);

	return pform2D;
}
//=============================================================================
// ������
//=============================================================================
HRESULT CFade :: Init(LPDIRECT3DDEVICE9 pDevice,int type)
{
	m_pDevice = pDevice;
	//�t�B�[���h�̏�����

	Cform2D::Init(m_pDevice,m_apTextureName[0],D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),SCREEN_WIDTH,SCREEN_HEIGHT);

	m_bfade=false;
	m_color=D3DXCOLOR(1.0f,1.0f,1.0f,0.0f);
	m_fAlpha=0.0f;
	m_nCount=0;

	return S_OK;
}
//=============================================================================
// �I��
//=============================================================================
void CFade :: Uninit(void)
{
	//�l�X�ȃI�u�W�F�N�g�̏I���i�J���j����
	Cform2D::Uninit();
}
//=============================================================================
// �X�V
//=============================================================================
void CFade :: Update(void)
{
	if(m_bfade)
	{
		switch(m_fadeType)
		{
			case FADE_IN:
						//�A���t�@��255�ɐi�߂Ă���
						m_fAlpha+=1.0f/m_nCount;

						if(m_fAlpha>=1.0f)
						{
							m_fAlpha=1.0f;
						}

						m_nCount--;

						//���Ԃ���������t�F�[�h�A�E�g��
						if(m_nCount<=0)
						{
							m_fadeType=FADE_IN_END;
							m_nCount=0;
						}
						break;
			case FADE_IN_END:
						break;
			case FADE_OUT:
						//�A���t�@��0�ɐi�߂Ă���
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
// �`��
//=============================================================================
void CFade :: Draw(void)
{
	if(m_bfade)
	{
		Cform2D::Draw();
	}
}

void CFade ::StartFade(FADEMODE fade,int nCount,D3DXCOLOR color, int type)
{
	Cform2D::SetTexture(m_apTextureName[rand()%3]);
	m_fadeType=fade;
	m_nCount=nCount;
	m_color=color;
	m_fAlpha=m_color.a;
	m_bfade=true;
}
/////////////EOF////////////
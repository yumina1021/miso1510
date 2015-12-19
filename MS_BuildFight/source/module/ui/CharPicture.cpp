//=============================================================================
//
// MS_BuildFight [CCharPicture.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#include "CharPicture.h"
//*****************************************************************************
// �ÓI�ϐ�
//*****************************************************************************
const LPSTR CCharPicture::m_apTextureName[] =
{
	"data/TEXTURE/t_start.png",
	"data/TEXTURE/t_vs.png",
	"data/TEXTURE/t_tutorial.png",
	"data/TEXTURE/t_end.png",

	"data/TEXTURE/s_0.png",
	"data/TEXTURE/s_1.png",
	"data/TEXTURE/s_2.png",
	"data/TEXTURE/s_3.png",
	"data/TEXTURE/s_4.png",
	"data/TEXTURE/s_5.png",
	"data/TEXTURE/s_6.png",
	"data/TEXTURE/s_7.png",
	"data/TEXTURE/s_8.png",
	"data/TEXTURE/n_b.png",
	"data/TEXTURE/s_99.png",

	"data/TEXTURE/LevelStar.png",
	"data/TEXTURE/StageName1.png",
	"data/TEXTURE/StageName2.png",
	"data/TEXTURE/StageName3.png",
	"data/TEXTURE/StageName4.png",

	"data/TEXTURE/p_continue.png",
	"data/TEXTURE/p_retry.png",
	"data/TEXTURE/p_quit.png"

};
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCharPicture::CCharPicture() :Cform2D(OBJTYPE_PAUSE, 7),
m_Len(0.0f, 0.0f, 0.0f),
m_FadeCoff(0.02f),
m_Mode(GUI_MODE::NORMAL),
m_NowFade(GUI_FADE::FADE_NONE),
m_Diff(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))
{
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCharPicture :: ~CCharPicture(void)
{
}
//=============================================================================
// CCharPicture����
//=============================================================================
CCharPicture *CCharPicture::Create(LPDIRECT3DDEVICE9 pDevice, PictureNum nType, D3DXVECTOR3 pos, float fwidth, float fheight)
{
	CCharPicture *pform2D;

	pform2D = new CCharPicture();
	pform2D->Init(pDevice, nType, pos, fwidth, fheight);

	return pform2D;
}
//=============================================================================
// ������
//=============================================================================
HRESULT CCharPicture::Init(LPDIRECT3DDEVICE9 pDevice, PictureNum nType, D3DXVECTOR3 pos, float fwidth, float fheight)
{
	m_pDevice = pDevice;
	//�t�B�[���h�̏�����
	Cform2D::Init(m_pDevice, m_apTextureName[(int)nType], pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), fwidth, fheight);
	m_Len = D3DXVECTOR3(fwidth, fheight, 0.0f);
	return S_OK;
}
//=============================================================================
// �I��
//=============================================================================
void CCharPicture::Uninit(void)
{
	//�l�X�ȃI�u�W�F�N�g�̏I���i�J���j����
	Cform2D::Uninit();
}
//=============================================================================
// �X�V
//=============================================================================
void CCharPicture::Update(void)
{
	Cform2D::Update();
}
//=============================================================================
// �`��
//=============================================================================
void CCharPicture::Draw(void)
{
	Cform2D::Draw();
}
//=============================================================================
// FunctionName: ChangeGuiState
// Param: void
// ReturnValue: void
// Content: Gui�̏�Ԃɂ���ĕω�������
//=============================================================================
void CCharPicture::ChangeGuiState(GUI_MODE paramMode){

	// �J�ڏ�Ԃ̍X�V
	m_Mode = paramMode;

	// �w�肳�ꂽ��Ԃɂ���ĕ���
	switch (paramMode)
	{

		// �ʏ��Ԃ̏ꍇ
	case GUI_MODE::NORMAL:

		// ���l�����ς���
		m_Diff.a = 1.0f;

		// �F����ݒ�
		SetDiffuse(m_Diff.r, m_Diff.g, m_Diff.b, m_Diff.a);

		// ����𔲂���
		break;

		// �_�ŏ��
	case GUI_MODE::FLASH:

		// �`�J�`�J������
		Flash();

		// ����𔲂���
		break;

		// �_�ŏ��
	case GUI_MODE::DESELECT:

		// �|���S�������X�ɕs�����ɂ���
		m_Diff.a += m_FadeCoff;

		// �������l���ő傾������
		if (m_Diff.a >= 1.0f)
		{
			m_Diff.a = 1.0f;

			// �ʏ��ԂɑJ��
			m_Mode = GUI_MODE::NORMAL;

		}

		// ���_�̐F�̕ύX
		SetDiffuse(m_Diff.a, m_Diff.a, m_Diff.a, 1.0f);

		// ����𔲂���
		break;

		// �\�����������Ȃ����
	case GUI_MODE::HIDE:

		// ���l�����ς���
		m_Diff.a = 0.0f;

		// �F����ݒ�
		SetDiffuse(m_Diff.r, m_Diff.g, m_Diff.b, m_Diff.a);

		// ����𔲂���
		break;

		// �\�����������Ȃ����
	case GUI_MODE::GRADUALLY_DESELECT:



		// ����𔲂���
		break;
		// �\�����������Ȃ����
	case GUI_MODE::GRADUALLY_SELECT:

		// �|���S�������X�ɕs�����ɂ���
		m_Diff.a += m_FadeCoff;

		// �������l���ő傾������
		if (m_Diff.a >= 1.0f)
		{
			m_Diff.a = 1.0f;

			// �ʏ��ԂɑJ��
			m_Mode = GUI_MODE::NORMAL;

		}

		// ���_�̐F�̕ύX
		SetDiffuse(m_Diff.r, m_Diff.g, m_Diff.b, m_Diff.a);

		// ����𔲂���
		break;
		// ��L�ȊO�̏ꍇ
	default:

		// ����𔲂���
		break;

	}// switch


}// ChangeGuiState
//=============================================================================
// FunctionName: Flash
// Param: void
// ReturnValue: void
// Content: �`�J�`�J�_�ł��鏈��
//=============================================================================
void CCharPicture::Flash(void){

	// �t�F�[�h�̏�ԑJ�ڂ̊Ǘ�
	switch (m_NowFade)
	{

		// �t�F�[�h�C���̏�Ԃ̏ꍇ
	case GUI_FADE::FADE_IN:

		// �|���S�������X�ɓ����ɂ���
		m_Diff.a -= m_FadeCoff;

		// �X�C�b�`�𔲂���
		break;

		// �t�F�[�h�A�E�g�̏�Ԃ̏ꍇ
	case GUI_FADE::FADE_OUT:

		// �|���S�������X�ɕs�����ɂ���
		m_Diff.a += m_FadeCoff;

		// �X�C�b�`�𔲂���
		break;

	}// swithch

	// �������l���ő傾������
	if (m_Diff.a >= 1.0f)
	{

		// �t�F�[�h�������~�߂�
		m_NowFade = GUI_FADE::FADE_IN;

		// �������l���ŏ���������
	}
	else if (m_Diff.a <= 0.5f)
	{

		// �t�F�[�h�������~�߂�
		m_NowFade = GUI_FADE::FADE_OUT;

	}// if

	// ���_�̐F�̕ύX
	SetDiffuse(m_Diff.a, m_Diff.a, m_Diff.a, 1.0f);

}// Flash
/////////////EOF////////////
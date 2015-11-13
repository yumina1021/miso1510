//=============================================================================
//
// MS_BuildFight [CButton.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#include "Button.h"

//*****************************************************************************
// �ÓI�ϐ�
//*****************************************************************************
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CButton::CButton() :CCharPicture()
{
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CButton :: ~CButton(void)
{
}
//=============================================================================
// CButton����
//=============================================================================
CButton *CButton::Create(LPDIRECT3DDEVICE9 pDevice,PictureNum nType,D3DXVECTOR3 pos,float fwidth,float fheight)
{
	CButton *pform2D;

	pform2D = new CButton();
	pform2D->Init(pDevice,nType,pos,fwidth,fheight);

	return pform2D;
}
//=============================================================================
// ������
//=============================================================================
HRESULT CButton :: Init(LPDIRECT3DDEVICE9 pDevice,PictureNum nType,D3DXVECTOR3 pos,float fwidth,float fheight)
{
	//�t�B�[���h�̏�����
	CCharPicture::Init(pDevice, nType, pos, fwidth, fheight);

	return S_OK;
}
//=============================================================================
// �I��
//=============================================================================
void CButton :: Uninit(void)
{
	//�l�X�ȃI�u�W�F�N�g�̏I���i�J���j����
	CCharPicture::Uninit();
}
//=============================================================================
// �X�V
//=============================================================================
void CButton :: Update(void)
{

	switch (state)
	{

		// �I������Ă��Ȃ��ꍇ
	case BUTTON_STATE::PUSH_OFF:

		// Gui�̏�Ԃ̍X�V
		ChangeGuiState(GUI_MODE::NORMAL);

		// ����𔲂���
		break;

	case BUTTON_STATE::SELECTED:

		// Gui�̏�Ԃ̍X�V
		ChangeGuiState(GUI_MODE::FLASH);

		// ����𔲂���
		break;

	case BUTTON_STATE::DESELECT:

		if (GetGuiMode() == GUI_MODE::NORMAL)
		{

			state = BUTTON_STATE::PUSH_OFF;

		}
		else
		{
			ChangeGuiState(GUI_MODE::DESELECT);

		}
		// ����𔲂���
		break;


	case BUTTON_STATE::PUSH_ON:

		// Gui�̏�Ԃ̍X�V
		ChangeGuiState(GUI_MODE::NORMAL);

		// ����𔲂���
		break;

	case BUTTON_STATE::HIDE:

		// Gui�̏�Ԃ̍X�V
		ChangeGuiState(GUI_MODE::HIDE);

		// ����𔲂���
		break;

		// ��L�ȊO�̏����̏ꍇ
	default:

		// ����𔲂���
		break;
	}

	CCharPicture::Update();
}
//=============================================================================
// �`��
//=============================================================================
void CButton::Draw(void)
{
	CCharPicture::Draw();
}

//=============================================================================
// �`��
//=============================================================================
void CButton::ChangeSelectButtonState(CButton* paramDeselectPtr, CButton* paramSelectPtr){
	
	paramDeselectPtr->SetButtonState(BUTTON_STATE::DESELECT);
	paramSelectPtr->SetButtonState(BUTTON_STATE::SELECTED);


}

/////////////EOF////////////
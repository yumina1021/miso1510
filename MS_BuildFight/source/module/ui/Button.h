//=============================================================================
//
// MS_BuildFight [CButton.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CBUTTON_H_
#define _CBUTTON_H_
//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "CharPicture.h"

//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************

//*****************************************************************************
// �}�N����`
//*****************************************************************************
enum class BUTTON_STATE : unsigned short
{
	PUSH_OFF = 0,	// ������Ă��Ȃ�
	SELECTED,		// �I��
	DESELECT,		// 
	PUSH_ON,		// �����Ă���
	HIDE,			// 

};
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CButton : public CCharPicture
{
	public:
		CButton();		//�R���X�g���N�^
		~CButton(void);	//�f�X�g���N�^

		static CButton *Create(LPDIRECT3DDEVICE9 pDevice,
			PictureNum nType,
			D3DXVECTOR3 pos,
			float fwidth,
			float fheight);

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice,
						PictureNum nType,
						D3DXVECTOR3 pos,
						float fwidth,
						float fheight);	// ������
		void Uninit(void);				// �I��
		void Update(void);				// �X�V
		void Draw(void);				// �`��

		void SetButtonState(BUTTON_STATE paramState){ state = paramState; };// �{�^���̏�Ԃ̑J��
		static void ChangeSelectButtonState(CButton* paramDeselectPtr, CButton* paramSelectPtr);
	private:
		BUTTON_STATE	state;
		float			m_fDiffuse;
};

#endif

/////////////EOF////////////
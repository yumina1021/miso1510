//=============================================================================
//
// MS_BuildFight [CCharPicture.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CCHARPICTURE_H_
#define _CCHARPICTURE_H_
//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "../../form/form2D.h"
//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************

//*****************************************************************************
// �}�N����`
//*****************************************************************************
typedef enum
{
	t_stert=0,
	t_vs,
	t_tutorial,
	t_end,
	s_0,
	s_1,
	s_2,
	s_3,
	s_4,
	s_5,
	s_6,
	n_b,
	s_99,
	p_continue,
	p_retry,
	p_quit,
	num_max
}PictureNum;

// ��ԑJ�ڗp�̃��[�h
enum class GUI_MODE : unsigned short{

	NORMAL = 0,	// �ʏ�
	FLASH,		// �I��
	HIDE,		// �B��
	DESELECT,	// �{�^���̑I�������p�ɓ��ʂɍ��

};

enum class GUI_FADE : unsigned short{

	FADE_NONE = 0,
	FADE_IN,
	FADE_OUT,
	FADE_MAX,

};
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CCharPicture  : public Cform2D
{
	public:
		CCharPicture();//�R���X�g���N�^
		~CCharPicture(void);//�f�X�g���N�^

		static CCharPicture *Create(LPDIRECT3DDEVICE9 pDevice,
									PictureNum nType,
									D3DXVECTOR3 pos,
									float fwidth,
									float fheight);// ����

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice,
			PictureNum nType,
			D3DXVECTOR3 pos,
			float fwidth,
			float fheight);								// ������
		void Uninit(void);								// �I��
		void Update(void);								// �X�V
		void Draw(void);								// �`��
		D3DXVECTOR3 GetLen(void){ return m_Len; };		// �����̎擾
		void ChangeGuiState(GUI_MODE paramMode);		// ��ԑJ��
		void Flash(void);								// �`�J�`�J
		const GUI_MODE& GetGuiMode(){ return m_Mode; };	// GUI�̏�Ԃ��擾

	private:
		LPDIRECT3DDEVICE9	m_pDevice;				// pDevice�I�u�W�F�N�g(�`��ɕK�v)
		int					m_nCount;				// �t�F�[�h����
		static const LPSTR	m_apTextureName[];		// �e�N�X�`���[
		D3DXVECTOR3			m_Len;					// ����
		D3DXCOLOR			m_Diff;					// �F
		GUI_MODE			m_Mode;					// ��ԑJ�ڗp�̃��[�h
		GUI_FADE			m_NowFade;				// �`�J�`�J�����邽�߂̃t�F�[�h��Ԏ��ʗp
		float				m_FadeCoff;				// �t�F�[�h�̌W��

};

#endif

/////////////EOF////////////
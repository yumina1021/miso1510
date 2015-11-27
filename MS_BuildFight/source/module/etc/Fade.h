//=============================================================================
//
// MS_BuildFight [CFade.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CFADE_H_
#define _CFADE_H_
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
	FADE_NONE =0,	//���Ȃ�
	FADE_IN,		//�C��
	FADE_IN_END,	//�C���I��
	FADE_OUT,		//�A�E�g
	FADE_OUT_END,	//�A�E�g�I��
	FADE_MAX
}FADEMODE;
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CFade  : public Cform2D
{
	public:
		CFade();//�R���X�g���N�^
		~CFade(void);//�f�X�g���N�^

		static CFade *Create(LPDIRECT3DDEVICE9 pDevice,int type);

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice,int type);//������
		void Uninit(void);//�I��
		void Update(void);//�X�V
		void Draw(void);//�`��

		void StartFade(FADEMODE fade,int nCount,D3DXCOLOR color, int type);

		void SetFade(FADEMODE fade){m_fadeType=fade;};
		FADEMODE GetFade(void){return m_fadeType;};
		bool GetPlayFade(void){return m_bfade;};

	private:
		LPDIRECT3DDEVICE9	m_pDevice;				// pDevice�I�u�W�F�N�g(�`��ɕK�v)
		int					m_nCount;				//�t�F�[�h����
		static const LPSTR	m_apTextureName[];		//�e�N�X�`���[
		bool				m_bfade;				//�t�F�[�h���Ă��邩
		FADEMODE			m_fadeType;				//�t�F�[�h�̏��
		float				m_fAlpha;				//�A���t�@�l
		D3DXCOLOR			m_color;				//�F
};

#endif

/////////////EOF////////////
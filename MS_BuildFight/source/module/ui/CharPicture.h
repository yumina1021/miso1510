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
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CCharPicture  : public Cform2D
{
	public:
		CCharPicture();//�R���X�g���N�^
		~CCharPicture(void);//�f�X�g���N�^

		static CCharPicture *Create(LPDIRECT3DDEVICE9 pDevice,PictureNum nType,D3DXVECTOR3 pos,float fwidth,float fheight);

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice,PictureNum nType,D3DXVECTOR3 pos,float fwidth,float fheight);//������
		void Uninit(void);//�I��
		void Update(void);//�X�V
		void Draw(void);//�`��
		D3DXVECTOR3 GetLen(void){ return m_Len; };

	private:
		LPDIRECT3DDEVICE9	m_pDevice;				// pDevice�I�u�W�F�N�g(�`��ɕK�v)
		int					m_nCount;				//�t�F�[�h����
		static const LPSTR	m_apTextureName[];		//�e�N�X�`���[
		D3DXVECTOR3			m_Len;

};

#endif

/////////////EOF////////////
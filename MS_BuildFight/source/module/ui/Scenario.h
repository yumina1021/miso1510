//=============================================================================
//
// MS_BuildFight [CScenario.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CSCENARIO_H_
#define _CSCENARIO_H_
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
class CCharacter;
class Cform2D;
class CInputKeyboard;
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CScenario
{
	public:
		CScenario();//�R���X�g���N�^
		~CScenario(void);//�f�X�g���N�^

		static CScenario *Create(LPDIRECT3DDEVICE9 pDevice, bool viewflag);

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice, bool viewflag);//������
		void Uninit(void);//�I��
		void Update(CInputKeyboard* input);//�X�V
		void Draw(void);//�`��
		void SetViewFlag(bool change,int time){m_ViewFlag=change;m_nCount=time;};

	private:
		LPDIRECT3DDEVICE9	m_pDevice;				// pDevice�I�u�W�F�N�g(�`��ɕK�v)
		int					m_nCount;
		bool				m_ViewFlag;
		CCharacter*			m_CCharacter;
		Cform2D*			m_window;
};

#endif

/////////////EOF////////////
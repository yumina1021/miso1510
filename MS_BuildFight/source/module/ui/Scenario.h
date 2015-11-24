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
#include "text_box.h"
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
		enum Character
		{
			CHARA_ROSA = 0,
			CHARA_LILA,
			CHARA_OJYOU,
			CHARA_TUTORIAL,
			CHARA_ALL
		};
		enum GameAffair
		{
			AFFAIR_START = 0,
			AFFAIR_WIN,
			AFFAIR_LOSE,
			AFFAIR_HALF,
			AFFAIR_ALL
		};

		CScenario();//�R���X�g���N�^
		~CScenario(void);//�f�X�g���N�^

		static CScenario *Create(LPDIRECT3DDEVICE9 pDevice, Character chara, bool viewflag);

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice, Character chara, bool viewflag);//������
		void Uninit(void);//�I��
		void Update(CInputKeyboard* input);//�X�V
		void Draw(void);//�`��

		void SetViewFlag(bool change, int start){ m_ViewFlag = change; m_nCount = start; };
		void SetScenarioEndFlag(bool change){ m_bScenarioEndFlag = change; };
		bool GetScenarioEndFlag(void){ return m_bScenarioEndFlag; };
		void GameScenario(int count, GameAffair affair);

	private:
		LPDIRECT3DDEVICE9	m_pDevice;				// pDevice�I�u�W�F�N�g(�`��ɕK�v)
		int					m_nCount;
		bool				m_ViewFlag;
		CCharacter*			m_CCharacter;
		Cform2D*			m_window;
		TextBox*			m_textbox;
		Character			m_charaType;
		GameAffair			m_affair;
		bool				m_bScenarioEndFlag;
};

#endif

/////////////EOF////////////
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
// インクルードファイル
//*****************************************************************************
#include "../../form/form2D.h"
#include "text_box.h"
//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************

//*****************************************************************************
// マクロ定義
//*****************************************************************************
class CCharacter;
class Cform2D;
class CInputKeyboard;
//*****************************************************************************
// クラス定義
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
			AFFAIR_CUPIN,
			AFFAIR_ALL
		};

		CScenario();//コンストラクタ
		~CScenario(void);//デストラクタ

		static CScenario *Create(LPDIRECT3DDEVICE9 pDevice, Character chara, bool viewflag);

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice, Character chara, bool viewflag);//初期化
		void Uninit(void);//終了
		void Update(CInputKeyboard* input);//更新
		void Draw(void);//描画

		void SetViewFlag(bool change, int start){ m_ViewFlag = change; m_nCount = start; };
		void SetScenarioEndFlag(bool change){ m_bScenarioEndFlag = change; };
		bool GetScenarioEndFlag(void){ return m_bScenarioEndFlag; };
		void GameScenario(int count, GameAffair affair);
		void ResultScenario(int count);

	private:
		LPDIRECT3DDEVICE9	m_pDevice;				// pDeviceオブジェクト(描画に必要)
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
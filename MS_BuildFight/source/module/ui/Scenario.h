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
		CScenario();//コンストラクタ
		~CScenario(void);//デストラクタ

		static CScenario *Create(LPDIRECT3DDEVICE9 pDevice, bool viewflag);

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice, bool viewflag);//初期化
		void Uninit(void);//終了
		void Update(CInputKeyboard* input);//更新
		void Draw(void);//描画
		void SetViewFlag(bool change,int time){m_ViewFlag=change;m_nCount=time;};

	private:
		LPDIRECT3DDEVICE9	m_pDevice;				// pDeviceオブジェクト(描画に必要)
		int					m_nCount;
		bool				m_ViewFlag;
		CCharacter*			m_CCharacter;
		Cform2D*			m_window;
};

#endif

/////////////EOF////////////
//=============================================================================
//
// MS_BuildFight [CTitle.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CTITLE_H_
#define _CTITLE_H_
//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
// 列挙体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CBackGround;	//前方宣言
class CFade;
class CButton;
class CCharPicture;
class CCursor;
class CDome;
class CDomeU;
class CMeshField;
class Cform2D;
class CTitle  : public CScene
{
	enum SELECT_TYPE
	{
		TYPE_BUTTON = 0,
		TYPE_CURSOR,

	};

	enum BUTTON_TYPE : int
	{
		GAME_START = 0,
		GAME_END,
		MAX,

	};

	public:
		CTitle(void);			//コンストラクタ
		~CTitle(void);			//デストラクタ

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice);		//初期化
		void Uninit(void);					//終了
		void Update(void);					//更新
		void Draw(void);					//描画
		void LookAround();

	private:
		void KeyCommand(void);				//入力系
		void SelectByCursor(void);
		void ChangeState(void);
		void UpdateFade();

		CBackGround*	m_pBackGround;		//背景
		CFade*			m_pFade;			//フェード
		CButton*		m_pMenueButton[MAX];//メニュー用画像
		CDome*			m_pDome;
		CDomeU*			m_pDome2;
		CMeshField*		m_pMeshField;
		Cform2D*		m_pLogo;
		Cform2D*		m_pCharcterPic[3];
		int				m_nCursor;			//カーソル
		bool			m_bChangeFlag;		//シーン切替フラグ
		float			m_fDiffuse;			//メニューアニメーション用
		SELECT_TYPE		m_nType;
		CCursor*		m_pCursor[2];			//メニュー用

};

#endif

/////////////EOF////////////
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
		VS_MODE,
		TUTORIAL,
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
	private:
		void KeyCommand(void);				//入力系
<<<<<<< HEAD
=======
		void SelectByCursor(void);
		void ChangeState(void);
		void UpdateFade();
>>>>>>> origin/sakai_work

		CBackGround*	m_pBackGround;		//背景
		CFade*			m_pFade;			//フェード
		CButton*		m_pCharPicture[MAX];//メニュー用画像

		int				m_nCursor;			//カーソル
		bool			m_bChangeFlag;		//シーン切替フラグ
		float			m_fDiffuse;			//メニューアニメーション用
		SELECT_TYPE		m_nType;
		CCursor*		m_pCursor;			//メニュー用

};

#endif

/////////////EOF////////////
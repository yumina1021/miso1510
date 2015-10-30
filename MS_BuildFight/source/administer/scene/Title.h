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
// クラス定義
//*****************************************************************************
class CBackGround;	//前方宣言
class CFade;
class CCharPicture;


class CTitle  : public CScene
{
	public:
		CTitle(void);			//コンストラクタ
		~CTitle(void);			//デストラクタ

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice);		//初期化
		void Uninit(void);					//終了
		void Update(void);					//更新
		void Draw(void);					//描画
	private:
		void KeyCommand(void);				//入力系

		CBackGround*	m_pBackGround;		//背景
		CFade*			m_pFade;			//フェード
		CCharPicture*	m_pCharPicture[4];	//メニュー用画像

		int				m_nCursor;			//カーソル
		bool			m_bChangeFlag;		//シーン切替フラグ
		float			m_fDiffuse;			//メニューアニメーション用
};

#endif

/////////////EOF////////////
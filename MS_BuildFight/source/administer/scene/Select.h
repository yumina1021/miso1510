//=============================================================================
//
// MS_BuildFight [CSelect.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CSELECT_H_
#define _CSELECT_H_
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
class CEffect;

class CSelect  : public CScene
{
	public:
		CSelect(void);			//コンストラクタ
		~CSelect(void);			//デストラクタ

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice);//初期化
		void Uninit(void);						//終了
		void Update(void);						//更新
		void Draw(void);						//描画
	private:
		CBackGround*		m_pBackGround;		//背景
		CFade*				m_pFade;			//フェード
		CCharPicture*		m_pCharPicture[5];	//メニュー用
		CEffect*			m_pEffect[6];		//キャラエフェクト

		int					m_nCursor;			//カーソル
		bool				m_bChangeFlag;		//切り換えフラグ
		float				m_fDiffuse;			//アニメーション用
		bool				m_bVsSelectFlag;	//VSモード用
		bool				m_bTitleBackFlag;	//タイトルに行きました
		bool				m_bSendData;		//相手データが送られた
};

#endif

/////////////EOF////////////
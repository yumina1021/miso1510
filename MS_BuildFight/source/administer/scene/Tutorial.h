//=============================================================================
//
// MS_BuildFight [CTutorial.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CTUTORIAL_H_
#define _CTUTORIAL_H_
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

class CTutorial  : public CScene
{
	public:
		CTutorial(void);			//コンストラクタ
		~CTutorial(void);			//デストラクタ

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice);//初期化
		void Uninit(void);						//終了
		void Update(void);						//更新
		void Draw(void);						//描画
	private:
		CBackGround*	m_pBackGround;			//背景
		CFade*			m_pFade;				//フェード
		CEffect*		m_pEffect[8];			//エフェクト
		int				m_nCount;				//表示カウント
};

#endif

/////////////EOF////////////
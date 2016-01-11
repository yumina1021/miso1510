//=============================================================================
//
// MS_BuildFight [CGameClear.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CGAMECLEAR_H_
#define _CGAMECLEAR_H_
//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "scene.h"
//*****************************************************************************
// クラス定義
//*****************************************************************************
//class CBackGround;	//前方宣言
class CFade;
class CCharPicture;
class CEffect;

class CGameClear  : public CScene
{
	public:
		CGameClear(void);			//コンストラクタ
		~CGameClear(void);			//デストラクタ

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice);		//初期化
		void Uninit(void);				//終了
		void Update(void);			//更新
		void Draw(void);				//描画
	private:
		//static CBackGround*		m_pBackGround;
		static CFade*			m_pFade;
		static CEffect*			m_pEffect[3];		//エフェクトのポインター
		int						m_nCount;
};

#endif

/////////////EOF////////////
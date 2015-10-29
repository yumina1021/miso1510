//=============================================================================
//
// MS_BuildFight [CVsend.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CVSEND_H_
#define _CVSEND_H_
//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "scene.h"
//*****************************************************************************
// クラス定義
//*****************************************************************************
class CBackGround;	//前方宣言
class CEffect;
class CFade;

class CVsend  : public CScene
{
	public:
		CVsend(void);			//コンストラクタ
		~CVsend(void);			//デストラクタ

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice);		//初期化
		void Uninit(void);		//終了
		void Update(void);		//更新
		void Draw(void);		//描画
	private:
		static CBackGround* m_pBackGround;
		static CFade*		m_pFade;
		static CEffect*		m_pEffect;
};

#endif

/////////////EOF////////////
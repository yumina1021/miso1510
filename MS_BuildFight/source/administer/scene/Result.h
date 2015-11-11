//=============================================================================
//
// MS_BuildFight [CResult.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CRESULT_H_
#define _CRESULT_H_
//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "scene.h"
//*****************************************************************************
// クラス定義
//*****************************************************************************
class CBackGround;	//前方宣言
class CFade;
class CReScore;
class CBall;
class CScenario;

class CResult  : public CScene
{
	public:
		CResult(void);			//コンストラクタ
		~CResult(void);			//デストラクタ

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice);//初期化
		void Uninit(void);						//終了
		void Update(void);						//更新
		void Draw(void);						//描画
	private:
		CBackGround* m_pBackGround;				//背景
		CFade*		m_pFade;					//フェード
		CReScore*	m_pRescore[4];				//スコア用
		CBall*		m_pBall;					//フォーム
		CScenario*	m_pScenerio;				//シナリオ
};

#endif

/////////////EOF////////////
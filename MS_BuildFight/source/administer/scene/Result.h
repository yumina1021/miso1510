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
class Cform2D;
class CManager;

#define BLIZZARD_MAX (500)		//紙吹雪の枚数

enum RESULT_TYPE
{
	WIN_TYPE = 0,
	LOSE_TYPE,
	TIEGAME_TYPE,
	MAX_TYPE,
};

class CResult  : public CScene
{
	public:
		CResult(void);			//コンストラクタ
		~CResult(void);			//デストラクタ

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice);//初期化
		void Uninit(void);						//終了
		void Update(void);						//更新
		void Draw(void);						//描画

		void Win();			//勝利
		void Lose();		//敗北
		void TieGame();		//引き分け
		void PaperBlizzard(float min,float max);	//紙吹雪
	private:
		CBackGround* m_pBackGround;				//背景
		CFade*		m_pFade;					//フェード
		CReScore*	m_pRescore[4];				//スコア用
		CBall*		m_pBall;					//フォーム
		Cform2D*	m_pform2D[5];					//2D表示用
		Cform2D*	m_pPaperBlizzard[BLIZZARD_MAX];
		CScenario*	m_pScenerio;				//シナリオ
		CManager*	m_pManager;					//マネージャー
		LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuff;	//頂点情報格納ワーク(動的)
		D3DXVECTOR2 m_Vector[BLIZZARD_MAX];		//紙吹雪の向き
		RESULT_TYPE m_ResultType;				//勝敗
		static const LPSTR	m_apTextureName[];	//紙吹雪のテクスチャ

};

#endif

/////////////EOF////////////
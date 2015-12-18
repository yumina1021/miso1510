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
class Cform3D;
class CManager;
class CformX;
class CDome;
class CSound;

#define CRACKER_MAX  (50)		//紙噴射の枚数
#define BLIZZARD_MAX (50)		//紙吹雪の枚数

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
		void PaperCracker(float min, float max);	//紙噴射
		void PaperBlizzard(float min, float max);	//紙吹雪

	private:
		void _UpdateCracker(void);
		void _UpdateFade(void);
		void _UpdatePaperBlizzard(void);
		void _UpdateFlag(void);
		void _UpdateTimer(void);
		void _UpdateWinningOrLosing(void);

		static LPDIRECT3DDEVICE9	m_pD3DDevice;			// pDeviceオブジェクト(描画に必要)

		CBackGround* m_pBackGround;						//背景
		CFade*		m_pFade;							//フェード
		CReScore*	m_pRescore[4];						//スコア用
		CBall*		m_pBall;							//フォーム
		Cform3D*	m_pform3D[6];						//3D表示用
		CScenario*	m_pScenerio;						//シナリオ
		CManager*	m_pManager;							//マネージャー
		LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuff;			//頂点情報格納ワーク(動的)
		D3DXVECTOR3 m_CrackerVector[CRACKER_MAX];		//紙吹雪の向き
		Cform3D*	m_pPaperCracker[CRACKER_MAX];
		RESULT_TYPE m_ResultType;						//勝敗
		static const LPSTR	m_apTextureName[];			//紙吹雪のテクスチャ
		int m_cnt;
		float m_MaxSpeed;
		float m_SlideSpeed;
		float m_Speed;									//画像の動く速度
		bool m_CrackerFlag;								//紙噴射開始フラグ
		bool m_BlizzardFlag;							//紙吹雪開始フラグ
		bool m_AfterRewardFlag;							//ご褒美CG出し終わったフラグ
		D3DXVECTOR3 m_BlizzardVector[BLIZZARD_MAX];		//紙吹雪の向き
		Cform3D*	m_pPaperBlizzard[BLIZZARD_MAX];		//紙噴射
		Cform2D* m_pform2D[2];								//ご褒美CG用
		int m_ButtonCounter;	
		float m_Alpha[2];									//ご褒美CGのアルファ値
		CSound *m_pSound;
		int m_Timer;

};

#endif

/////////////EOF////////////
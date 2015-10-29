//=============================================================================
//
// MS_BuildFight [CGame.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CGAME_H_
#define _CGAME_H_
//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "scene.h"
//*****************************************************************************
// クラス定義
//*****************************************************************************
class CMeshField;	//前方宣言
class Cform3D;
class CPlayerM;
class CEnemyM;
class CSound;
class CEffect;
class CScore;
class CTimer;
class CCount;
class CGauge;
class CBackGround;
class CFade;
class CCharPicture;
class CLocusEffect;
class CIcon;
class CDome;
class CDomeU;


class CGame  : public CScene
{
	public:
		CGame(void);			//コンストラクタ
		~CGame(void);			//デストラクタ

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice);	//初期化
		static unsigned __stdcall InitSet( LPVOID Param );	//初期化
		void Uninit(void);							//終了
		void Update(void);							//更新
		void Draw(void);							//描画
		void Restart(void);							//再開

		static CPlayerM *GetPlayer(void){ return m_pPlayer; };
		static CEnemyM *GetEnemy(int iD){ return m_pEnemy; };
		static int GetStartCount(void){ return m_nGameStartCount; };
		static void SetStartCount(int nchange){ m_nGameStartCount = nchange; };
		static bool	GetReplay(void){ return m_bReplayFlag; };
		static bool	GetVs(void){ return m_bReplayFlag; };

		CMeshField *GetMeshField(void){ return m_pMeshField; };
		Cform3D *Getform3D(void){ return m_pform3D; };
		CEffect *GetEffect(int id){ return m_pEffect[id]; };
		CScore *GetScore(void){ return m_pScore; };
		CTimer *GetTimer(void){ return m_pTimer; };
		CCount *GetCountBullet(void){ return m_pCountBullet; };
		CCount *GetCountBoost(void){ return m_pCountBoost; };
		CCount *GetCountOver(void){ return m_pCountOver; };
		CGauge *GetGauge(void){ return m_pGauge; };
		CGauge *GetGaugeEnemy(void){ return m_pGaugeEnemy; };
		CLocusEffect *GetLocusEffect(int i){return m_pLocusEffect[i];};
		CIcon *GetIcon(void){return m_pIcon;};
		CIcon *GetIconEnemy(void){return m_pIconEnemy;};

		void SetTimer(int time);

	private:
		void TurnStart();	//ターン開始
		void ShotStart();	//球打ち開始
		void BallMove();	//弾移動
		void Judge();		//結果判定
		void charachange();	//キャラ変更

		CMeshField*		m_pMeshField;		//メッシュフィールドのポインタ
		Cform3D*		m_pform3D;			//メッシュフィールドのポインタ
		static CPlayerM* m_pPlayer;			//プレイヤーのポインタ
		static CEnemyM*	 m_pEnemy;			//エネミーのポインタ
		CEffect*		m_pEffect[16];		//エフェクトのポインター
		CScore*			m_pScore;			//スコアのポインター
		CCount*			m_pCountBoost;		//カウントのポインター
		CTimer*			m_pTimer;			//タイマーのポインター
		CCount*			m_pCountBullet;		//カウントのポインター
		CCount*			m_pCountOver;		//カウントのポインター
		CGauge*			m_pGauge;			//ゲージのポインター
		CGauge*			m_pGaugeEnemy;		//ゲージのポインター
		CBackGround*	m_pBackGround;
		CFade*			m_pFade;
		CCharPicture*	m_pCharPicture[3];
		CLocusEffect*	m_pLocusEffect[20];	//エフェクトのポインター
		CIcon*			m_pIconEnemy;
		CIcon*			m_pIcon;
		CDome*			m_pDome;
		CDomeU*			m_pDome2;
		Cform2D*		m_pUI;

		int				m_nCount;
		int				m_nClearType;
		int				m_nCursor;
		bool			m_bChangeFlag;
		float			m_fDiffuse;
		int				m_nTimerCount;
		static int		m_nGameStartCount;
		static bool		m_bVsSelectFlag;
		static bool		m_bReplayFlag;
		int				m_nTimerPlus;
		int				m_nIFtype;
		int				m_nEnum;
		int				m_nPnum;
		bool			m_bJudge;
		int				m_nTurnCount;
		int				m_nSwitchCount;

};

#endif

/////////////EOF////////////
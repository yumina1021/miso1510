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
class CBall;
class CGoal;

enum GAME_PHASE
{
	START_PHASE = 0,
	ANGLE_PHASE,
	POWER_PHASE,
	MOVE_PHASE,
	JUDGE_PHASE,
	END_PHASE,
	CHANGE_PHASE,
	MAX_PHASE,
};

class CGame  : public CScene
{
	public:
		CGame(void);			//コンストラクタ
		~CGame(void);			//デストラクタ

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice);	//初期化
		void InitUI(LPDIRECT3DDEVICE9 pDevice);
		static unsigned __stdcall InitSet( LPVOID Param );	//初期化
		void Uninit(void);							//終了
		void Update(void);							//更新
		void Draw(void);							//描画
		void Restart(void);							//再開

		static CPlayerM *GetPlayer(int id){ return m_pPlayer[id]; };
		static int GetStartCount(void){ return m_nGameStartCount; };
		static void SetStartCount(int nchange){ m_nGameStartCount = nchange; };
		static bool	GetReplay(void){ return m_bReplayFlag; };
		static bool	GetVs(void){ return m_bReplayFlag; };
		static CBall *GetBall(int i){ return m_pBall[i]; };
		static int GetPlayerCount(void){ return m_nPlayerNum; };
		static int GetPhase(void){ return m_nSwitchCount; };

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

		static bool SphireHit(D3DXVECTOR3 a, float al, D3DXVECTOR3 b, float bl){
			return (b.x - a.x) * (b.x - a.x) +
				(b.x - a.x) * (b.x - a.x) +
				(b.x - a.x) * (b.x - a.x) <= (al + bl) * (al + bl);}
	private:
<<<<<<< HEAD
=======
		void ModelInit(LPDIRECT3DDEVICE9 pDevice);
		void ObjectInit(LPDIRECT3DDEVICE9 pDevice);
>>>>>>> ohashi_work
		void TurnStart();		//ターン開始
		void AngleDecision();	//角度決定開始
		void PowerDecision();	//打つ力の決定
		void BallMove();		//弾移動
		void Judge();			//結果判定
		void End();				//終了
		void charachange();		//キャラ変更
<<<<<<< HEAD
=======
		void ObjHitCheck();
>>>>>>> ohashi_work
		D3DXVECTOR3 CheckVector(D3DXVECTOR3 ball, D3DXVECTOR3 player);		//ベクトル算出

		CMeshField*		m_pMeshField;		//メッシュフィールドのポインタ
		Cform3D*		m_pform3D;			//メッシュフィールドのポインタ
		static CPlayerM* m_pPlayer[2];			//プレイヤーのポインタ
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
		static CBall*	m_pBall[2];
		CGoal*			m_pGoal;

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
		static int		m_nPlayerNum;
		int				m_nIFtype;
		int				m_nEnum;
		int				m_nPnum;
		bool			m_bJudge;
		int				m_nTurnCount;
		static int		m_nSwitchCount;
		D3DXVECTOR3		m_MovePow;
		D3DXVECTOR3		m_shotrot;
		D3DXVECTOR3		m_PowerShot;
};

#endif

/////////////EOF////////////
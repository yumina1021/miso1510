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
class CScenario;
class CformX;
class CNumber;

class CShotEffect;
class CGimmick;
class CBlowShot;
class CCupin;
class CMap;

enum GAME_PHASE
{
	START_PHASE = 0,
	SCENARIO_PHASE,
	ANGLE_PHASE,
	POWER_PHASE,
	MOVE_PHASE,
	JUDGE_PHASE,
	CUPIN_PHASE,
	END_PHASE,
	CHANGE_PHASE,
	MAX_PHASE,
};

class OBB
{
protected:
	D3DXVECTOR3 m_Pos;				// 位置
	D3DXVECTOR3 m_NormaDirect[3];	// 方向ベクトル
	FLOAT m_fLength[3];				// 各軸方向の長さ

public:
	D3DXVECTOR3 GetDirect(int elem){ return m_NormaDirect[elem]; };	// 指定軸番号の方向ベクトルを取得
	FLOAT GetLen_W(int elem){ return m_fLength[elem]; };			// 指定軸方向の長さを取得
	D3DXVECTOR3 GetPos_W(){ return m_Pos; };				// 位置を取得
	void SetDirect(int elem, D3DXVECTOR3 normal){ m_NormaDirect[elem] = normal; };	// 指定軸番号の方向ベクトルを取得
	void SetLen_W(int elem, float length){ m_fLength[elem] = length; };			// 指定軸方向の長さを取得
	void SetPos_W(D3DXVECTOR3 pos){ m_Pos = pos; };				// 位置を取得
};
typedef struct
{
	D3DXVECTOR3 pos;	// 各モデルのキー要素
	float size;	// 各モデルのキー要素
} STAGE_INFO;
#define SHOT_EFFECT	(16)
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
		CLocusEffect *GetLocusEffect(int i){return m_pLocusEffect[i];};
		CIcon *GetIcon(void){return m_pIcon;};
		CIcon *GetIconEnemy(void){ return m_pIconEnemy; };
		D3DXVECTOR3 GetFieldPos(int id){ return m_nStageinfo[id].pos; }
		float GetFieldsize(int id){ return m_nStageinfo[id].size; }
		int GetFieldNum(){ return m_nStagenum; }
		void SetTimer(int time);
		static bool	GetBallFlag(int id){ return g_boalflag[id]; };

		static bool SphireHit(D3DXVECTOR3 a, float al, D3DXVECTOR3 b, float bl){
			return (b.x - a.x) * (b.x - a.x) +
				(b.y - a.y) * (b.y - a.y) +
				(b.z - a.z) * (b.z - a.z) <= (al + bl) * (al + bl);}
		static bool ColOBBs(D3DXVECTOR3 objpos, D3DXVECTOR3 objsize, D3DXVECTOR3 objrot, D3DXVECTOR3 sphire_pos, float sphire_length);
		static D3DXVECTOR3 GetVectorShot(void){ return m_PowerShot; }
		static D3DXVECTOR3 GetPlayerCamera(void){ return m_playercamera; }
		static bool calcRaySphere(
			D3DXVECTOR3 l,
			D3DXVECTOR3 v,
			D3DXVECTOR3 p,
			float r) {
			p.x = p.x - l.x;
			p.y = p.y - l.y;
			p.z = p.z - l.z;

			float A = v.x * v.x + v.y * v.y + v.z * v.z;
			float B = v.x * p.x + v.y * p.y + v.z * p.z;
			float C = p.x * p.x + p.y * p.y + p.z * p.z - r * r;

			if (A == 0.0f)
				return false; // レイの長さが0

			float s = B * B - A * C;
			if (s < 0.0f)
				return false; // 衝突していない

			s = sqrtf(s);
			float a1 = (B - s) / A;
			float a2 = (B + s) / A;

			if (a1 < 0.0f || a2 < 0.0f)
			return false; // レイの反対で衝突

			return true;
		}
	private:
		void ModelInit(LPDIRECT3DDEVICE9 pDevice);
		void ObjectInit(LPDIRECT3DDEVICE9 pDevice);
		void TurnStart();		//ターン開始
		void GameScenario();	//茶番
		void AngleDecision();	//角度決定開始
		void PowerDecision();	//打つ力の決定
		void BallMove();		//弾移動
		void Judge();			//結果判定
		void CupIn();			//結果判定
		void End();				//終了
		void charachange();		//キャラ変更
		void ObjHitCheck();
		void Magnet();
		void LoadGiimick(LPDIRECT3DDEVICE9 pDevice);

		D3DXVECTOR3 CheckVector(D3DXVECTOR3 ball, D3DXVECTOR3 player);		//ベクトル算出

		CMeshField*		m_pMeshField;		//メッシュフィールドのポインタ
		Cform3D*		m_pform3D;			//メッシュフィールドのポインタ
		static CPlayerM* m_pPlayer[2];			//プレイヤーのポインタ
		CEffect*		m_pEffect[13];		//エフェクトのポインター
		CScore*			m_pScore;			//スコアのポインター
		CCount*			m_pCountDistance[2];//距離ポインター

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
		CGauge*			m_pGauge;
		CScenario*		m_pScenario[2];
		CformX*			m_cursol;
		Cform2D*		m_pgoalnavi[4];
		CShotEffect*	m_pShotEffect[SHOT_EFFECT];
		CBlowShot*		m_pBlowEffect;
		CCupin*			m_pCupin;
		CMap*			m_pMap;

		CGimmick**		m_pGimmick_stage;

		int				m_nCount;
		int				m_nClearType;
		int				m_nCursor;
		bool			m_bChangeFlag;
		float			m_fDiffuse;
		float			m_fCupDistance[2];
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
		D3DXVECTOR3		m_vecrot;
		D3DXVECTOR3		m_startpos[2];
		D3DXVECTOR3		m_goalpos;
		float			m_playerrot_x;
		static D3DXVECTOR3		m_PowerShot;
		bool			m_bcursol;
		float			m_bcursolmove;
		static D3DXVECTOR3		m_playercamera;

		float			m_fnavimove;
		bool			m_bnaviFlag[4];
		int				m_nStagenum;
		int				m_nGimmickmax;
		STAGE_INFO*		m_nStageinfo;
		bool			m_bBlowFlag;
		bool			m_bStageflag[2];
		int				m_bStageflagcount[2];
		bool			m_bLilaBlow;
		bool			m_bLichtBlow;
		static bool g_boalflag[2];
};

#endif

/////////////EOF////////////
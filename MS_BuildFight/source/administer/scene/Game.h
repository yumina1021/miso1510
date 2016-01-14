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
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "scene.h"
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CMeshField;	//�O���錾
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
	D3DXVECTOR3 m_Pos;				// �ʒu
	D3DXVECTOR3 m_NormaDirect[3];	// �����x�N�g��
	FLOAT m_fLength[3];				// �e�������̒���

public:
	D3DXVECTOR3 GetDirect(int elem){ return m_NormaDirect[elem]; };	// �w�莲�ԍ��̕����x�N�g�����擾
	FLOAT GetLen_W(int elem){ return m_fLength[elem]; };			// �w�莲�����̒������擾
	D3DXVECTOR3 GetPos_W(){ return m_Pos; };				// �ʒu���擾
	void SetDirect(int elem, D3DXVECTOR3 normal){ m_NormaDirect[elem] = normal; };	// �w�莲�ԍ��̕����x�N�g�����擾
	void SetLen_W(int elem, float length){ m_fLength[elem] = length; };			// �w�莲�����̒������擾
	void SetPos_W(D3DXVECTOR3 pos){ m_Pos = pos; };				// �ʒu���擾
};
typedef struct
{
	D3DXVECTOR3 pos;	// �e���f���̃L�[�v�f
	float size;	// �e���f���̃L�[�v�f
} STAGE_INFO;
#define SHOT_EFFECT	(16)
class CGame  : public CScene
{
	public:
		CGame(void);			//�R���X�g���N�^
		~CGame(void);			//�f�X�g���N�^

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice);	//������
		void InitUI(LPDIRECT3DDEVICE9 pDevice);
		static unsigned __stdcall InitSet( LPVOID Param );	//������
		void Uninit(void);							//�I��
		void Update(void);							//�X�V
		void Draw(void);							//�`��
		void Restart(void);							//�ĊJ

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
		CIcon *GetIconEnemy(void){return m_pIconEnemy;};

		void SetTimer(int time);

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
				return false; // ���C�̒�����0

			float s = B * B - A * C;
			if (s < 0.0f)
				return false; // �Փ˂��Ă��Ȃ�

			s = sqrtf(s);
			float a1 = (B - s) / A;
			float a2 = (B + s) / A;

			if (a1 < 0.0f || a2 < 0.0f)
			return false; // ���C�̔��΂ŏՓ�

			return true;
		}
	private:
		void ModelInit(LPDIRECT3DDEVICE9 pDevice);
		void ObjectInit(LPDIRECT3DDEVICE9 pDevice);
		void TurnStart();		//�^�[���J�n
		void GameScenario();	//����
		void AngleDecision();	//�p�x����J�n
		void PowerDecision();	//�ł͂̌���
		void BallMove();		//�e�ړ�
		void Judge();			//���ʔ���
		void CupIn();			//���ʔ���
		void End();				//�I��
		void charachange();		//�L�����ύX
		void ObjHitCheck();
		void Magnet();
		void LoadGiimick(LPDIRECT3DDEVICE9 pDevice);

		D3DXVECTOR3 CheckVector(D3DXVECTOR3 ball, D3DXVECTOR3 player);		//�x�N�g���Z�o

		CMeshField*		m_pMeshField;		//���b�V���t�B�[���h�̃|�C���^
		Cform3D*		m_pform3D;			//���b�V���t�B�[���h�̃|�C���^
		static CPlayerM* m_pPlayer[2];			//�v���C���[�̃|�C���^
		CEffect*		m_pEffect[13];		//�G�t�F�N�g�̃|�C���^�[
		CScore*			m_pScore;			//�X�R�A�̃|�C���^�[
		CCount*			m_pCountDistance[2];//�����|�C���^�[

		CBackGround*	m_pBackGround;
		CFade*			m_pFade;
		CCharPicture*	m_pCharPicture[3];
		CLocusEffect*	m_pLocusEffect[20];	//�G�t�F�N�g�̃|�C���^�[
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

		CGimmick*		m_pGimmick[10];
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
		int				m_GimmickMax;
		static int		m_nSwitchCount;
		D3DXVECTOR3		m_MovePow;
		D3DXVECTOR3		m_shotrot;
		D3DXVECTOR3		m_vecrot;
		D3DXVECTOR3		m_startpos[2];
		float		m_playerrot_x;
		static D3DXVECTOR3		m_PowerShot;
		bool			m_bcursol;
		float			m_bcursolmove;
		static D3DXVECTOR3		m_playercamera;

		float			m_fnavimove;
		bool			m_bnaviFlag[4];
		bool			m_bBlowShot;
		int				m_nStagenum;
		STAGE_INFO*		m_nStageinfo;
};

#endif

/////////////EOF////////////
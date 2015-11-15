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
typedef struct STAGE_STATE
{
	D3DXVECTOR3 position;
	float length;
};
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
				   (b.y - a.y) * (b.y - a.y) +
				   (b.z - a.z) * (b.z - a.z) <= (al + bl) * (al + bl);}
	private:
		void ModelInit(LPDIRECT3DDEVICE9 pDevice);
		void ObjectInit(LPDIRECT3DDEVICE9 pDevice);
		void TurnStart();		//�^�[���J�n
		void AngleDecision();	//�p�x����J�n
		void PowerDecision();	//�ł͂̌���
		void BallMove();		//�e�ړ�
		void Judge();			//���ʔ���
		void End();				//�I��
		void charachange();		//�L�����ύX
		void ObjHitCheck();
		void ShotCountAdd(int);
		D3DXVECTOR3 CheckVector(D3DXVECTOR3 ball, D3DXVECTOR3 player);		//�x�N�g���Z�o

		CMeshField*		m_pMeshField;		//���b�V���t�B�[���h�̃|�C���^
		Cform3D*		m_pform3D;			//���b�V���t�B�[���h�̃|�C���^
		static CPlayerM* m_pPlayer[2];			//�v���C���[�̃|�C���^
		CEffect*		m_pEffect[16];		//�G�t�F�N�g�̃|�C���^�[
		CScore*			m_pScore;			//�X�R�A�̃|�C���^�[
		CCount*			m_pCountBoost;		//�J�E���g�̃|�C���^�[
		CTimer*			m_pTimer;			//�^�C�}�[�̃|�C���^�[
		CCount*			m_pCountBullet;		//�J�E���g�̃|�C���^�[
		CCount*			m_pCountOver;		//�J�E���g�̃|�C���^�[
		CGauge*			m_pGauge;			//�Q�[�W�̃|�C���^�[
		CGauge*			m_pGaugeEnemy;		//�Q�[�W�̃|�C���^�[
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
		STAGE_STATE**	m_stagestate;
};

#endif

/////////////EOF////////////
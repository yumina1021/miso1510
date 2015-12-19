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
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "scene.h"
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CBackGround;	//�O���錾
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

#define CRACKER_MAX  (50)		//�����˂̖���
#define BLIZZARD_MAX (50)		//������̖���

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
		CResult(void);			//�R���X�g���N�^
		~CResult(void);			//�f�X�g���N�^

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice);//������
		void Uninit(void);						//�I��
		void Update(void);						//�X�V
		void Draw(void);						//�`��

		void Win();			//����
		void Lose();		//�s�k
		void TieGame();		//��������
		void PaperCracker(float min, float max);	//������
		void PaperBlizzard(float min, float max);	//������

	private:
		void _UpdateCracker(void);
		void _UpdateFade(void);
		void _UpdatePaperBlizzard(void);
		void _UpdateFlag(void);
		void _UpdateTimer(void);
		void _UpdateWinningOrLosing(void);
		void _UpdateLauncher(void);
		void _UpdateWinLauncher(void);
		void _UpdateLoseLauncher(void);
		void _UpdateTieGameLauncher(void);


		static LPDIRECT3DDEVICE9	m_pD3DDevice;			// pDevice�I�u�W�F�N�g(�`��ɕK�v)

		CBackGround* m_pBackGround;						//�w�i
		CFade*		m_pFade;							//�t�F�[�h
		CReScore*	m_pRescore[4];						//�X�R�A�p
		CBall*		m_pBall;							//�t�H�[��
		Cform3D*	m_pform3D[8];						//3D�\���p
		CScenario*	m_pScenerio;						//�V�i���I
		CManager*	m_pManager;							//�}�l�[�W���[
		LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuff;			//���_���i�[���[�N(���I)
		D3DXVECTOR3 m_CrackerVector[CRACKER_MAX];		//������̌���
		Cform3D*	m_pPaperCracker[CRACKER_MAX];
		RESULT_TYPE m_ResultType;						//���s
		static const LPSTR	m_apTextureName[];			//������̃e�N�X�`��
		int m_cnt;
		float m_MaxSpeed;
		float m_SlideSpeed;								//Win,Lose�̉摜�̈ړ����x
		float m_LauncherSpeed[2];							//�N���b�J�[���ˑ��u�̑��x

		float m_Speed;									//�摜�̓������x
		bool m_CrackerFlag;								//�����ˊJ�n�t���O
		bool m_BlizzardFlag;							//������J�n�t���O
		bool m_AfterRewardFlag;							//���J��CG�o���I������t���O
		D3DXVECTOR3 m_BlizzardVector[BLIZZARD_MAX];		//������̌���
		Cform3D*	m_pPaperBlizzard[BLIZZARD_MAX];		//������
		Cform2D* m_pform2D[2];								//���J��CG�p
		int m_ButtonCounter;	
		float m_Alpha[2];									//���J��CG�̃A���t�@�l
		CSound *m_pSound;
		int m_Timer;

};

#endif

/////////////EOF////////////
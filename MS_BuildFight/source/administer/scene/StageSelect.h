//=============================================================================
//
// MS_BuildFight [CStageSelect.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CSTAGE_SELECT_H_
#define _CSTAGE_SELECT_H_
//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
// 
//*****************************************************************************
const int MAX_BALL(4);


//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CBackGround;	//�O���錾
class CFade;
class CCharPicture;
class CEffect;
class CBall;
class CMeshField;	//�O���錾
class CCursor;
class CButton;

//*****************************************************************************
// �񋓑̒�`
//*****************************************************************************
struct DISP_PLAY_STAGE
{
	CBall*	pDispObj;
	float	fLenCoff;
	int		nDestCnt;
	float	fLenCoffDest;

};

class CStageSelect  : public CScene
{
	
	public:

		enum class STATE
		{
			NORMAL,
			SATELLITE_ORBIT,
			CHANGE_SCENE,
		};
		enum BUTTON_TYPE
		{
			LEFT = 0,
			RIGHT,
			BUTTON_TYPE_MAX,
		};


		struct PLAYER_DATA
		{
			int	nSelectNum;			//�I�𒆂̔ԍ�
			CCursor* pCursor;		// �J�[�\�\���p�̃|�C���^
		};

		CStageSelect(void);			//�R���X�g���N�^
		~CStageSelect(void);			//�f�X�g���N�^

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice);//������
		void Uninit(void);						//�I��
		void Update(void);						//�X�V
		void Draw(void);						//�`��
		void SelectByButton(void);				//�L�[�{�[�h�ł̑I��
		void SelectByCursor(void);				//�J�[���ړ��ł̑I��
		void UpdateFade(void);					//�t�F�[�h�̍X�V
		void UpdateSelectObject(void);			//�I���Ɏg���I�u�W�F�N�g�̍X�V

		static void NomalizeSelectObject(int& nParamVal);//�I���Ɏg���I�u�W�F�N�g�̍X�V
		
		bool HitChkRect(const D3DXVECTOR3& paramPos1,
			const D3DXVECTOR3& paramPos2,
			const D3DXVECTOR3& paramLen1,
			const D3DXVECTOR3& paramLen2);

	private:
		CBackGround*		m_pBackGround;		//�w�i
		CFade*				m_pFade;			//�t�F�[�h
		CMeshField*			m_pMeshField;		//���b�V���t�B�[���h�̃|�C���^
		DISP_PLAY_STAGE		m_Obj[MAX_BALL];
		float				m_fDiffuse;			//�A�j���[�V�����p
		bool				m_bVsSelectFlag;	//VS���[�h�p
		bool				m_bTitleBackFlag;	//�^�C�g���ɍs���܂���
		bool				m_bSendData;		//����f�[�^������ꂽ
		int					m_nCursorNum;		
		float				m_fTime;
		STATE				m_nState;
		PLAYER_DATA			m_playerData[2];

};

#endif

/////////////EOF////////////
//=============================================================================
//
// MS_BuildFight [CSelect.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CSELECT_H_
#define _CSELECT_H_
//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "scene.h"

const int MAX_CURSOR(2);
const int MAX_PLAYER(2);

//*****************************************************************************
// �񋓑̒�`
//*****************************************************************************
enum CHARCTER_TYPE
{
	TYPE_1 = 0,
	TYPE_2,
	TYPE_3,
	TYPE_4,
	TYPE_MAX,

};
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CBackGround;	//�O���錾
class CFade;
class CCharPicture;
class CEffect;
class CButton;
class CCursor;
class Cform3D;
class Cform2D;
class CformX;
class CDome;
class CDomeU;
class CPlayerM;
class CSelect : public CScene
{

	enum class STATE
	{
		NORMAL,
		SELECT_BUTTON,
		SELECT_CUSOR,
		CHANGE_SCENE,

	};

	enum SELECT_TYPE
	{
		TYPE_BUTTON = 0,
		TYPE_CURSOR,

	};

	struct SELECT_CURSOR
	{
		int			nSelect;	//�J�[�\��
		CCursor*	pCursor;	//���j���[�p
		bool		bDecisionFlg;
	};
public:
	CSelect(void);			//�R���X�g���N�^
	~CSelect(void);			//�f�X�g���N�^

	HRESULT Init(LPDIRECT3DDEVICE9 pDevice);//������
	void Uninit(void);						//�I��
	void Update(void);						//�X�V
	void Draw(void);						//�`��

	void SelectByKeyboardPlayer1(void);		//�L�[�{�[�h�ł̑I��
	void SelectByKeyboardPlayer2(void);		//�L�[�{�[�h�ł̑I��
	void SelectByCursor(void);				//�J�[���ړ��ł̑I��
	void UpdateFade(void);					//�t�F�[�h�̍X�V
	void ChangeButton(void);				// �{�^���̑J��
	void CheckSelectAllCorsor(int nParamDecisionCursor);// �S�J�[�\�����I���������ǂ����̌���
	void CheckSelectOverlapCorsor(int nParamDecisionCursor);// �d�������J�[�\�������邩�ǂ����̌���
	void ChkSelectButton(int nParamSelectCursor);
	int NomalizeSelectPlayer(int nParamVal);

private:
	Cform3D*		m_pBackGround;								//�w�i
	CFade*			m_pFade;									//�t�F�[�h
	CButton*		m_pCharPicture[CHARCTER_TYPE::TYPE_MAX];	//���j���[�p
	Cform2D*		m_pCharFrame[CHARCTER_TYPE::TYPE_MAX];	//���j���[�p
	CCharPicture*	m_pLogo;									//���j���[�p
	CPlayerM*		m_pCharModPlayer1[CHARCTER_TYPE::TYPE_MAX];
	CPlayerM*		m_pCharModPlayer2[CHARCTER_TYPE::TYPE_MAX];
	Cform2D*		m_pCharNamePlayer1[CHARCTER_TYPE::TYPE_MAX];
	Cform2D*		m_pCharNamePlayer2[CHARCTER_TYPE::TYPE_MAX];
	Cform2D*		m_pPlayerPic[MAX_PLAYER];
	Cform2D*		m_pSelectCfm[MAX_PLAYER];

	CDome*			m_pDome;
	CDomeU*			m_pDome2;

	bool			m_bChangeFlag;		//�؂芷���t���O
	float			m_fDiffuse;			//�A�j���[�V�����p
	bool			m_bVsSelectFlag;	//VS���[�h�p
	bool			m_bTitleBackFlag;	//�^�C�g���ɍs���܂���
	bool			m_bSendData;		//����f�[�^������ꂽ
	SELECT_TYPE		m_nType;
	SELECT_CURSOR	m_Select[2];
	D3DXVECTOR3		m_OnCursorPos[CHARCTER_TYPE::TYPE_MAX];
	D3DXVECTOR3		m_SelectCfmPos[CHARCTER_TYPE::TYPE_MAX];

};

#endif

/////////////EOF////////////
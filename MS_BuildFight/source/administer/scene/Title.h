//=============================================================================
//
// MS_BuildFight [CTitle.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CTITLE_H_
#define _CTITLE_H_
//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
// �񋓑̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CBackGround;	//�O���錾
class CFade;
class CButton;
class CCharPicture;
class CCursor;

class CTitle  : public CScene
{
	enum SELECT_TYPE
	{
		TYPE_BUTTON = 0,
		TYPE_CURSOR,

	};

	enum BUTTON_TYPE : int
	{
		GAME_START = 0,
		//VS_MODE,
		//TUTORIAL,
		//GAME_END,
		MAX,

	};

	public:
		CTitle(void);			//�R���X�g���N�^
		~CTitle(void);			//�f�X�g���N�^

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice);		//������
		void Uninit(void);					//�I��
		void Update(void);					//�X�V
		void Draw(void);					//�`��
	private:
		void KeyCommand(void);				//���͌n
		void SelectByCursor(void);
		void ChangeState(void);
		void UpdateFade();

		CBackGround*	m_pBackGround;		//�w�i
		CFade*			m_pFade;			//�t�F�[�h
		CButton*		m_pCharPicture[MAX];//���j���[�p�摜

		int				m_nCursor;			//�J�[�\��
		bool			m_bChangeFlag;		//�V�[���ؑփt���O
		float			m_fDiffuse;			//���j���[�A�j���[�V�����p
		SELECT_TYPE		m_nType;
		CCursor*		m_pCursor;			//���j���[�p

};

#endif

/////////////EOF////////////
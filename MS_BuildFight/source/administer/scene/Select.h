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
enum SELECT_TYPE
{
	TYPE_BUTTON = 0,
	TYPE_CURSOR,

};
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CBackGround;	//�O���錾
class CFade;
class CCharPicture;
class CEffect;

class CSelect  : public CScene
{
	public:
		CSelect(void);			//�R���X�g���N�^
		~CSelect(void);			//�f�X�g���N�^

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice);//������
		void Uninit(void);						//�I��
		void Update(void);						//�X�V
		void Draw(void);						//�`��
		void SelectByButton(void);				//�L�[�{�[�h�ł̑I��
		void SelectByCursor(void);				//�J�[���ړ��ł̑I��
		void UpdateFade(void);					//�t�F�[�h�̍X�V

		bool HitChkRect(const D3DXVECTOR3& paramPos1,
			const D3DXVECTOR3& paramPos2,
			const D3DXVECTOR3& paramLen1,
			const D3DXVECTOR3& paramLen2);

	private:
		CBackGround*		m_pBackGround;		//�w�i
		CFade*				m_pFade;			//�t�F�[�h
		CCharPicture*		m_pCharPicture[CHARCTER_TYPE::TYPE_MAX];	//���j���[�p
		CCharPicture*		m_pCursor;	//���j���[�p

		int					m_nCursor;			//�J�[�\��
		bool				m_bChangeFlag;		//�؂芷���t���O
		float				m_fDiffuse;			//�A�j���[�V�����p
		bool				m_bVsSelectFlag;	//VS���[�h�p
		bool				m_bTitleBackFlag;	//�^�C�g���ɍs���܂���
		bool				m_bSendData;		//����f�[�^������ꂽ
		SELECT_TYPE			m_nType;
};

#endif

/////////////EOF////////////
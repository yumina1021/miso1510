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
	private:
		CBackGround*		m_pBackGround;		//�w�i
		CFade*				m_pFade;			//�t�F�[�h
		CCharPicture*		m_pCharPicture[5];	//���j���[�p
		CEffect*			m_pEffect[6];		//�L�����G�t�F�N�g

		int					m_nCursor;			//�J�[�\��
		bool				m_bChangeFlag;		//�؂芷���t���O
		float				m_fDiffuse;			//�A�j���[�V�����p
		bool				m_bVsSelectFlag;	//VS���[�h�p
		bool				m_bTitleBackFlag;	//�^�C�g���ɍs���܂���
		bool				m_bSendData;		//����f�[�^������ꂽ
};

#endif

/////////////EOF////////////
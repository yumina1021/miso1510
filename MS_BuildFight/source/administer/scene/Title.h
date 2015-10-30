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
// �N���X��`
//*****************************************************************************
class CBackGround;	//�O���錾
class CFade;
class CCharPicture;


class CTitle  : public CScene
{
	public:
		CTitle(void);			//�R���X�g���N�^
		~CTitle(void);			//�f�X�g���N�^

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice);		//������
		void Uninit(void);					//�I��
		void Update(void);					//�X�V
		void Draw(void);					//�`��
	private:
		void KeyCommand(void);				//���͌n

		CBackGround*	m_pBackGround;		//�w�i
		CFade*			m_pFade;			//�t�F�[�h
		CCharPicture*	m_pCharPicture[4];	//���j���[�p�摜

		int				m_nCursor;			//�J�[�\��
		bool			m_bChangeFlag;		//�V�[���ؑփt���O
		float			m_fDiffuse;			//���j���[�A�j���[�V�����p
};

#endif

/////////////EOF////////////
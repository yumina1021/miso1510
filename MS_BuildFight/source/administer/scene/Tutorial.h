//=============================================================================
//
// MS_BuildFight [CTutorial.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CTUTORIAL_H_
#define _CTUTORIAL_H_
//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "scene.h"
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CFade;
class CCharPicture;
class CEffect;

class CTutorial  : public CScene
{
	public:
		CTutorial(void);			//�R���X�g���N�^
		~CTutorial(void);			//�f�X�g���N�^

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice);//������
		void Uninit(void);						//�I��
		void Update(void);						//�X�V
		void Draw(void);						//�`��
	private:
		//CBackGround*	m_pBackGround;			//�w�i
		CFade*			m_pFade;				//�t�F�[�h
		CEffect*		m_pEffect[8];			//�G�t�F�N�g
		int				m_nCount;				//�\���J�E���g
};

#endif

/////////////EOF////////////
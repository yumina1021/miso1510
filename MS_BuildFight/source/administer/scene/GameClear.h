//=============================================================================
//
// MS_BuildFight [CGameClear.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CGAMECLEAR_H_
#define _CGAMECLEAR_H_
//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "scene.h"
//*****************************************************************************
// �N���X��`
//*****************************************************************************
//class CBackGround;	//�O���錾
class CFade;
class CCharPicture;
class CEffect;

class CGameClear  : public CScene
{
	public:
		CGameClear(void);			//�R���X�g���N�^
		~CGameClear(void);			//�f�X�g���N�^

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice);		//������
		void Uninit(void);				//�I��
		void Update(void);			//�X�V
		void Draw(void);				//�`��
	private:
		//static CBackGround*		m_pBackGround;
		static CFade*			m_pFade;
		static CEffect*			m_pEffect[2];		//�G�t�F�N�g�̃|�C���^�[
		int						m_nCount;
};

#endif

/////////////EOF////////////
//=============================================================================
//
// MS_BuildFight [CVsend.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CVSEND_H_
#define _CVSEND_H_
//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "scene.h"
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CBackGround;	//�O���錾
class CEffect;
class CFade;

class CVsend  : public CScene
{
	public:
		CVsend(void);			//�R���X�g���N�^
		~CVsend(void);			//�f�X�g���N�^

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice);		//������
		void Uninit(void);		//�I��
		void Update(void);		//�X�V
		void Draw(void);		//�`��
	private:
		static CBackGround* m_pBackGround;
		static CFade*		m_pFade;
		static CEffect*		m_pEffect;
};

#endif

/////////////EOF////////////
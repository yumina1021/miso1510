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

class CResult  : public CScene
{
	public:
		CResult(void);			//�R���X�g���N�^
		~CResult(void);			//�f�X�g���N�^

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice);//������
		void Uninit(void);						//�I��
		void Update(void);						//�X�V
		void Draw(void);						//�`��
	private:
		CBackGround* m_pBackGround;				//�w�i
		CFade*		m_pFade;					//�t�F�[�h
		CReScore*	m_pRescore[4];				//�X�R�A�p
		CBall*		m_pBall;					//�t�H�[��
		CScenario*	m_pScenerio;				//�V�i���I
};

#endif

/////////////EOF////////////
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
class Cform2D;
class CManager;

#define BLIZZARD_MAX (500)		//������̖���

enum RESULT_TYPE
{
	WIN_TYPE = 0,
	LOSE_TYPE,
	TIEGAME_TYPE,
	MAX_TYPE,
};

class CResult  : public CScene
{
	public:
		CResult(void);			//�R���X�g���N�^
		~CResult(void);			//�f�X�g���N�^

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice);//������
		void Uninit(void);						//�I��
		void Update(void);						//�X�V
		void Draw(void);						//�`��

		void Win();			//����
		void Lose();		//�s�k
		void TieGame();		//��������
		void PaperBlizzard(float min,float max);	//������
	private:
		CBackGround* m_pBackGround;				//�w�i
		CFade*		m_pFade;					//�t�F�[�h
		CReScore*	m_pRescore[4];				//�X�R�A�p
		CBall*		m_pBall;					//�t�H�[��
		Cform2D*	m_pform2D[5];					//2D�\���p
		Cform2D*	m_pPaperBlizzard[BLIZZARD_MAX];
		CScenario*	m_pScenerio;				//�V�i���I
		CManager*	m_pManager;					//�}�l�[�W���[
		LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuff;	//���_���i�[���[�N(���I)
		D3DXVECTOR2 m_Vector[BLIZZARD_MAX];		//������̌���
		RESULT_TYPE m_ResultType;				//���s
		static const LPSTR	m_apTextureName[];	//������̃e�N�X�`��

};

#endif

/////////////EOF////////////
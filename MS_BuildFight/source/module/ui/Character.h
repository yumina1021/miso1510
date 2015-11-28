//=============================================================================
//
// MS_BuildFight [CCharacter.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CCHARACTER_H_
#define _CCHARACTER_H_
//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "../../form/form2D.h"
//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************

//*****************************************************************************
// �}�N����`
//*****************************************************************************
typedef enum
{
	FACIAL_NORMAL = 0,
	FACIAL_SMILE,
	FACIAL_ANGERY,
	FACIAL_SAD,
	FACIAL_NONE,
	FACIAL_Max
}FasialType;
typedef enum
{
	FACE_NORMAL = 0,
	FACE_SMILE,
	FACE_ANGERY,
	FACE_SAD,
	FACE_MAX
}FaceType;
/*
typedef enum
{
	FACIAL_NORMAL = 0,
	FACIAL_SMILE,
	FACIAL_SMILE2,
	FACIAL_SMILE3,
	FACIAL_SMILE4,
	FACIAL_SHY,
	FACIAL_STAR,
	FACIAL_HEART,
	FACIAL_HAWAWA,
	FACIAL_SURPRISE,
	FACIAL_TROUBLE,
	FACIAL_ANGERY,
	FACIAL_SEEL,
	FACIAL_SAD,
	FACIAL_Max
}FasialType;
*/
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CCharacter  : public Cform2D
{
	public:
		CCharacter();//�R���X�g���N�^
		~CCharacter(void);//�f�X�g���N�^

		static CCharacter *Create(LPDIRECT3DDEVICE9 pDevice,int nType,D3DXVECTOR3 movePos,D3DXVECTOR3 moveRot);

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice,int nType,D3DXVECTOR3 pos,D3DXVECTOR3 rot);//������
		void Uninit(void);//�I��
		void Update(void);//�X�V
		void Draw(void);//�`��
		void SetViewFlag(bool change,int time){m_ViewFlag=change;m_nCount=time;};

		void SetFacialType(FasialType type){ m_facialType = type; };
		FasialType GetFacialType(void){ return m_facialType; };

	private:
		LPDIRECT3DDEVICE9	m_pDevice;				// pDevice�I�u�W�F�N�g(�`��ɕK�v)
		int					m_nCount;
		LPDIRECT3DTEXTURE9	m_pTexture[FACE_MAX];
		static const LPSTR	m_apTextureName[];
		bool				m_ViewFlag;
		FasialType			m_facialType;
		FasialType			m_facialTypeOld;
		char*				m_nCharaPas;
};

#endif

/////////////EOF////////////
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
	normal = 0,
	smile,
	smile2,
	smile3,
	smile4,
	smile5,
	shy,
	star,
	heart,
	hawawa,
	suprise,
	trouble,
	angery,
	seel,
	sad,
	ScenarioMax
}CharacterType;
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
		void SetCharaType(CharacterType type){ m_charaType = type; };
		CharacterType GetCharaType(void){ return m_charaType; };

	private:
		LPDIRECT3DDEVICE9	m_pDevice;				// pDevice�I�u�W�F�N�g(�`��ɕK�v)
		int					m_nCount;
		static const LPSTR	m_apTextureName[];
		bool				m_ViewFlag;
		CharacterType		m_charaType;
		CharacterType		m_charaTypeOld;
};

#endif

/////////////EOF////////////
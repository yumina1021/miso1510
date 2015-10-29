//=============================================================================
//
// MS_BuildFight [CBackGround.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CBACKGROUND_H_
#define _CBACKGROUND_H_
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
	BACKGROUND_TITLE=0,
	BACKGROUND_TUTORIAL,
	BACKGROUND_SELECT,
	BACKGROUND_LOAD,
	BACKGROUND_GAME,
	BACKGROUND_GAMECLEAR,
	BACKGROUND_VSEND,
	BACKGROUND_RESULT
}BACKGROUNDTYPE;
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CBackGround  : public Cform2D
{
	public:
		CBackGround();//�R���X�g���N�^
		~CBackGround(void);//�f�X�g���N�^

		static CBackGround *Create(LPDIRECT3DDEVICE9 pDevice,BACKGROUNDTYPE Type);

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice,BACKGROUNDTYPE Type);//������
		void Uninit(void);//�I��
		void Update(void);//�X�V
		void Draw(void);//�`��

	private:
		LPDIRECT3DDEVICE9	m_pDevice;				// pDevice�I�u�W�F�N�g(�`��ɕK�v)
		int					m_nCount;				//�t�F�[�h����
		static const LPSTR	m_apTextureName[];		//�e�N�X�`���[
};

#endif

/////////////EOF////////////
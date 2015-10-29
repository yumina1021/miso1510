//=============================================================================
//
// MS_BuildFight [CLock.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CLOCK_H_
#define _CLOCK_H_
//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "../../form/formBillBoard.h"
//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************

//*****************************************************************************
// �}�N����`
//*****************************************************************************
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CLock  : public CformBillBoard
{
	public:
		CLock();//�R���X�g���N�^
		~CLock(void);//�f�X�g���N�^

		static CLock *Create(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 pos,D3DXVECTOR3 rot);

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 pos,D3DXVECTOR3 rot);//������
		void Uninit(void);//�I��
		void Update(void);//�X�V
		void Draw(void);//�`��

		void SetTextureNum(int change){m_nTextureNum=change;};

	private:
		LPDIRECT3DDEVICE9		m_pDevice;
		static const LPSTR		m_apTextureName[];
		int						m_nTextureNum;
};

#endif

/////////////EOF////////////
//=============================================================================
//
// MS_BuildFight [CCursor.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CCURSOR_H_
#define _CCURSOR_H_
//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "CharPicture.h"

//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CCursor : public CCharPicture
{
	public:
		CCursor();		//�R���X�g���N�^
		~CCursor(void);	//�f�X�g���N�^

		static CCursor *Create(LPDIRECT3DDEVICE9 pDevice,
			PictureNum nType,
			D3DXVECTOR3 pos,
			float fwidth,
			float fheight);

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice,
						PictureNum nType,
						D3DXVECTOR3 pos,
						float fwidth,
						float fheight);	// ������
		void Uninit(void);				// �I��
		void Update(void);				// �X�V
		void Draw(void);				// �`��

		void MoveByKeybord(void);					// 
		void AddForce(void);						// 
		void SyncCharPos(D3DXVECTOR3 paramSyncPos);	// �L�����̍��W�Ɠ���������
		void SetTime(float paramTime){ m_Time = paramTime; };	// �L�����̍��W�Ɠ���������

		static void RadianRot(float& paramRot);
		static D3DXVECTOR3 EsasingNone(D3DXVECTOR3 paramMinPos,
										D3DXVECTOR3 paramMaxPos,
										float paramTime);
		
		static bool HitChkRect(const D3DXVECTOR3& paramPos1,
			const D3DXVECTOR3& paramPos2,
			const D3DXVECTOR3& paramLen1,
			const D3DXVECTOR3& paramLen2);
	private:
		D3DXVECTOR3 m_fVelocity;
		float m_fDiffuse;
		bool m_bUseWiiPad;
		float m_Time;

};

#endif

/////////////EOF////////////
//=============================================================================
//
// MS_BuildFight [Dome.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CDOME_H_
#define _CDOME_H_
//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "../../form/form3D.h"
//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SUM_INDEX(X,Z)	((X+1)*(Z-1)+((X+1)*(Z+1))+(Z-1)*2)
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CDome  : public Cform3D
{
	public:
		CDome(int nPriority = 3);//�R���X�g���N�^
		~CDome(void);//�f�X�g���N�^

		static CDome *Create(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 pos,D3DXVECTOR3 rot);

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice);//������
		void Uninit(void);//�I��
		void Update(void);//�X�V
		void Draw(void);//�`��

		void SetPos(D3DXVECTOR3 pos){m_Pos=pos;};
		void SetPos(float fx,float fy,float fz){m_Pos.x=fx;m_Pos.y=fy;m_Pos.z=fz;};
		D3DXVECTOR3 GetPos(void){return m_Pos;};
		void SetRot(D3DXVECTOR3 rot){m_Rot=rot;};
		void SetRot(float fx,float fy,float fz){m_Rot.x=fx;m_Rot.y=fy;m_Rot.z=fz;};
		D3DXVECTOR3 GetRot(void){return m_Rot;};
		void SetMtxView (D3DXMATRIX changeMtx){m_MtxView=changeMtx;};
		void SetRotCamera (D3DXVECTOR3 rotCamera){};

	private:
		LPDIRECT3DTEXTURE9		m_pD3DTex;			//�e�N�X�`���\���p
		LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuff;		//���_���i�[���[�N(���I)
		LPDIRECT3DDEVICE9		m_pDevice;			// pDevice�I�u�W�F�N�g(�`��ɕK�v)
		LPDIRECT3DINDEXBUFFER9  m_pD3DIndexBuff;	// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^

		D3DXMATRIX				m_mtxWorld;			// ���[���h�}�g���b�N�X		
		D3DXMATRIX				m_MtxView;			//�r���[�}�g���N�X

		D3DXVECTOR3				m_Pos;				//�ʒu
		D3DXVECTOR3				m_Rot;				//����
		D3DXVECTOR3				m_Scl;				//�傫��

		int		m_nNumVertex;						// �����_��
		int		m_nNumVertexIndex;					// ���_�̑��C���f�b�N�X��

		LPDIRECT3DPIXELSHADER9 _ps;			//�s�N�Z���V�F�[�_�[
		LPD3DXCONSTANTTABLE    _psc;		//�s�N�Z���V�F�[�_�[�p�R���X�^���g�e�[�u��
		LPDIRECT3DVERTEXSHADER9 _vs;		//�o�[�e�b�N�X�V�F�[�_�[
		LPD3DXCONSTANTTABLE    _vsc;		//�o�[�e�b�N�X�V�F�[�_�[�p�R���X�^���g�e�[�u��

};

#endif

/////////////EOF////////////
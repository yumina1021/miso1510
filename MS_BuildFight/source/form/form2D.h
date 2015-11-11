//=============================================================================
//
// MS_BuildFight [form2D.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CFORM2D_H_
#define _CFORM2D_H_
//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "form.h"
//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define POINT_MAX			(4)
#define POLYGON_WIDTH		(300)
#define POLYGON_HEIGHT		(400)
#define POLYGON_FIRST_X		(0)
#define POLYGON_FIRST_Y		(0)
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Cform2D  : public Cform
{
	public:
		Cform2D(OBJTYPE objtype=OBJTYPE_2D,int nPriority=7);//�R���X�g���N�^
		~Cform2D(void);//�f�X�g���N�^

		static Cform2D *Create(LPDIRECT3DDEVICE9 pDevice, LPSTR pFileName, D3DXVECTOR3 pos, D3DXVECTOR3 rot, float width, float height);

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice,LPSTR pFileName,D3DXVECTOR3 pos,D3DXVECTOR3 rot,float width,float height);//������
		void Uninit(void);//�I��
		void Update(void);//�X�V
		void Draw(void);//�`��

		void SetDiffuse(float r,float g,float b,float a);
		void SetTexture(LPSTR pFileName);

		void SetPos(D3DXVECTOR3 pos){m_Pos=pos;};
		void SetPos(float fx,float fy,float fz){m_Pos.x=fx;m_Pos.y=fy;m_Pos.z=fz;};
		D3DXVECTOR3 GetPos(void){return m_Pos;};
		void SetRot(D3DXVECTOR3 rot){m_Rot=rot;};
		void SetRot(float fx,float fy,float fz){m_Rot.x=fx;m_Rot.y=fy;m_Rot.z=fz;};
		D3DXVECTOR3 GetRot(void){return m_Rot;};

	private:
		LPDIRECT3DTEXTURE9  	m_pD3DTex;		//�e�N�X�`���\���p
		LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuff;	//���_���i�[���[�N(���I)
		LPDIRECT3DDEVICE9		m_pDevice;		// pDevice�I�u�W�F�N�g(�`��ɕK�v)	

		D3DXVECTOR3				m_Pos;			//�ʒu
		D3DXVECTOR3				m_Rot;			//����

		float					m_fLength;		//�|���S���Ίp���̒���
		float					m_fAngle;		//�|���S���Ίp���̊p�x
};

#endif

/////////////EOF////////////
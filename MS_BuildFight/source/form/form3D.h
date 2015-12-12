//=============================================================================
//
// MS_BuildFight [form3D.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CSCENE3D_H_
#define _CSCENE3D_H_
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
#define TEXTURE_SIZE_X		(50)	// �e�N�X�`���̕�
#define TEXTURE_SIZE_Y		(50)	// �e�N�X�`���̍���
#define	NUM_VERTEX			(4)		// ���_��
#define	NUM_POLYGON			(2)		// �|���S����
#define SUM_INDEX(X,Z) ((X+1)*(Z-1)+((X+1)*(Z+1))+(Z-1)*2)
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Cform3D  : public Cform
{
	public:
		Cform3D(int nPriority = 4);//�R���X�g���N�^
		~Cform3D(void);//�f�X�g���N�^

		static Cform3D *Create(LPDIRECT3DDEVICE9 pDevice,LPSTR pTexName,D3DXVECTOR3 pos,D3DXVECTOR3 rot);
		static Cform3D *Create(LPDIRECT3DDEVICE9 pDevice, LPSTR pTexName, D3DXVECTOR3 pos, D3DXVECTOR3 rot, float width, float height);


		HRESULT Init(LPDIRECT3DDEVICE9 pDevice,LPSTR pTexName);//������
		HRESULT Init(LPDIRECT3DDEVICE9 pDevice, LPSTR pTexName, float fTexSizeX, float fTexSizeY);
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
		void SetRotCamera (D3DXVECTOR3 rotCamera){m_RotCamera=rotCamera;};
		void SetTexture(LPDIRECT3DTEXTURE9 pTex){m_pD3DTex=pTex;};
	
		float GetHeight(D3DXVECTOR3 pos, D3DXVECTOR3 *pNormal);
		float GetHeightPolygon(const D3DXVECTOR3& P0, const D3DXVECTOR3& P1, const D3DXVECTOR3& P2,
											D3DXVECTOR3 pos, D3DXVECTOR3 *pNormal = NULL);

		void SetLength(float width, float height);
		D3DXVECTOR2 GetLengthWH(void){ return D3DXVECTOR2(m_fLength, m_fAngle); };
		void SetLength(float length){ m_fLength = length; };
		float GetLength(void){ return m_fLength; };
		void SetDiffuse(float r, float g, float b, float a);





	protected:
		LPDIRECT3DTEXTURE9  	m_pD3DTex;			//�e�N�X�`���\���p
		LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuff;		//���_���i�[���[�N(���I)
		LPDIRECT3DDEVICE9		m_pDevice;			// pDevice�I�u�W�F�N�g(�`��ɕK�v)

		D3DXMATRIX				m_MtxView;			//�r���[�}�g���N�X

		D3DXVECTOR3				m_Pos;				//�ʒu
		D3DXVECTOR3				m_Rot;				//����

		D3DXVECTOR3				m_Scl;				//�傫��
		float m_fLength;						// �|���S���̒��S���璸�_�܂ł̒���
		float m_fAngle;							// �|���S���ƒ��_�����񂾒����̌X��
		D3DXVECTOR3				m_RotCamera;

};

#endif

/////////////EOF////////////
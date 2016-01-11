//=============================================================================
//
// MS_BuildFight [LocusEffect.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CSHOTEFFECT_H_
#define _CSHOTEFFECT_H_
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
#define TEXTURE_SIZE_X		(50)	// �e�N�X�`���̕�
#define TEXTURE_SIZE_Y		(50)	// �e�N�X�`���̍���
#define	NUM_VERTEX			(4)		// ���_��
#define	NUM_POLYGON			(2)		// �|���S����
#define SUM_INDEX(X,Z) ((X+1)*(Z-1)+((X+1)*(Z+1))+(Z-1)*2)
#define BUFFER_MAX			(240)
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CShotEffect : public Cform3D
{
	public:
		CShotEffect(OBJTYPE objtype = OBJTYPE_3D,int nPriority = 7);//�R���X�g���N�^
		~CShotEffect(void);//�f�X�g���N�^

		static CShotEffect *Create(LPDIRECT3DDEVICE9 pDevice,int pTexName,D3DXVECTOR3 pos,D3DXVECTOR3 rot);

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice,int pTexName);//������
		void Uninit(void);//�I��
		void Update(void);//�X�V
		void Draw(void);//�`��

		void SetPos(D3DXVECTOR3 pos){m_Pos=pos;};
		void SetPos(float fx,float fy,float fz){m_Pos.x=fx;m_Pos.y=fy;m_Pos.z=fz;};
		D3DXVECTOR3 GetPos(void){return m_Pos;};

		void SetRot(D3DXVECTOR3 rot){m_Rot=rot;};
		void SetRot(float fx,float fy,float fz){m_Rot.x=fx;m_Rot.y=fy;m_Rot.z=fz;};
		D3DXVECTOR3 GetRot(void){return m_Rot;};

		void SetPosBuffer(D3DXVECTOR3 pos);
		
		void SetVector(D3DXVECTOR3 rotCamera){ m_vector = rotCamera; };
		void SetRandVector(D3DXVECTOR3 rotCamera){ m_vectorrand = rotCamera; };
	
		bool GetFlag(void){ return m_bFlag; }
		void SetFlag(bool change){ m_bFlag = change; };

		float GetHeight(D3DXVECTOR3 pos, D3DXVECTOR3 *pNormal);
		float GetHeightPolygon(const D3DXVECTOR3& P0, const D3DXVECTOR3& P1, const D3DXVECTOR3& P2,
											D3DXVECTOR3 pos, D3DXVECTOR3 *pNormal = NULL);
	protected:
		//LPDIRECT3DTEXTURE9  	m_pD3DTex;			//�e�N�X�`���\���p
		LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuff;		//���_���i�[���[�N(���I)
		LPDIRECT3DDEVICE9		m_pDevice;			// pDevice�I�u�W�F�N�g(�`��ɕK�v)


		D3DXVECTOR3				m_Pos;				//�ʒu
		D3DXVECTOR3				m_Rot;				//����

		D3DXVECTOR3				m_Scl;				//�傫��
		float m_fLength;						// �|���S���̒��S���璸�_�܂ł̒���
		float m_fAngle;							// �|���S���ƒ��_�����񂾒����̌X��

		int m_texid;
	private :
		D3DXMATRIX  mtxWorld;
		D3DXVECTOR3 m_vector;
		D3DXVECTOR3 m_vectorrand;
		bool		m_bFlag;
		SHADER_SET	shaderSet;				//�V�F�[�_�[���


};

#endif

/////////////EOF////////////
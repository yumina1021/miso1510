//=============================================================================
//
// MS_BuildFight [formX.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CSCENEX_H_
#define _CSCENEX_H_
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
#define TEXTURE_MAX		(4)
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CformX  : public Cform
{
	public:
		CformX(OBJTYPE objType=OBJTYPE_X,int nPriority=5);//�R���X�g���N�^
		~CformX(void);//�f�X�g���N�^

		static CformX *Create(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 pos,D3DXVECTOR3 rot,bool set,bool enemy);
		static CformX *Create(LPDIRECT3DDEVICE9 pDevice, LPSTR pModNameStr, D3DXVECTOR3 pos, D3DXVECTOR3 rot);

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice,LPSTR pFileName,int pTexName);//������
		void Uninit(void);//�I��
		void Update(void);//�X�V
		void Draw(void);//�`��

		void SetPos(D3DXVECTOR3 pos){m_Pos=pos;};
		void SetPos(float fx,float fy,float fz){m_Pos.x=fx;m_Pos.y=fy;m_Pos.z=fz;};
		D3DXVECTOR3 GetPos(void){ return m_Pos; };
		void SetRotReal(D3DXVECTOR3 rot){ m_Rot = rot; };
		void SetRot(D3DXVECTOR3 rot){m_rotDestModel=rot;};
		void SetRot(float fx,float fy,float fz){m_rotDestModel.x=fx;m_rotDestModel.y=fy;m_rotDestModel.z=fz;};
		D3DXVECTOR3 GetRot(void){return m_Rot;};
		void SetScl(D3DXVECTOR3 scl){m_Scl=scl;};
		void SetScl(float fx,float fy,float fz){m_Pos.x=fx;m_Pos.y=fy;m_Pos.z=fz;};
		D3DXVECTOR3 GetScl(void){return m_Scl;};
		void SetMtxView (D3DXMATRIX changeMtx){m_MtxView=changeMtx;};
		D3DXMATRIX GetMtxView (void){return m_MtxView;};
		D3DXVECTOR3 GetRotCamera (void){return m_RotCamera;};
		void SetRotCamera (D3DXVECTOR3 rotCamera){m_RotCamera=rotCamera;};
		void SetTexture(int pTexName,int num);
		void SetTextureNum(int num){nTextureNum=num;};
		void SetViewFlag(bool	change){m_bDeathFlag=change;};
		void ResetCount(int nCount){m_nDeathCount=nCount;};
		
		void SetShader(SHADER_SET shader)
		{
			if (m_shader.ps != NULL)m_shader.ps->Release();
			if (m_shader.psc != NULL)m_shader.psc->Release();
			if (m_shader.vs != NULL)m_shader.vs->Release();
			if (m_shader.vsc != NULL)m_shader.vsc->Release();
			m_shader = shader;
		};

	protected:
		LPD3DXMESH			m_pD3DXMeshModel;		//���b�V�����ւ̃|�C���^
	private:

		//LPDIRECT3DTEXTURE9	m_pD3DTex[TEXTURE_MAX];	//�e�N�X�`���\���p
		LPDIRECT3DCUBETEXTURE9 m_pD3DTextureCube;	// �e�N�X�`���ǂݍ��ݏꏊ

		LPDIRECT3DDEVICE9	m_pDevice;				// pDevice�I�u�W�F�N�g(�`��ɕK�v)	

		D3DXMATRIX			m_MtxView;				//�r���[�}�g���N�X
		D3DXMATRIX			m_mtxWorld;				// ���[���h�}�g���b�N�X

		LPD3DXBUFFER		m_pD3DXBuffMatModel;	//�}�e���A�����ւ̃|�C���^
		DWORD				m_nNumMatModel;			//�}�e���A�����̐�

		D3DXVECTOR3			m_Pos;					//�ʒu
		D3DXVECTOR3			m_Rot;					//����
		D3DXVECTOR3			m_Scl;					//�傫��

		D3DXVECTOR3			m_RotCamera;			//�J�����̌���

		D3DXVECTOR3			m_rotDestModel;			//�ړI�̌���

		int					nTextureNum;			//�e�N�X�`���[�̔ԍ�

		bool				m_bDeathFlag;
		int					m_nDeathCount;

		bool				m_bEnemyFlag;

		SHADER_SET			m_shader;
		int					m_texid;

};

#endif

/////////////EOF////////////
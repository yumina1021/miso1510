//=============================================================================
//
// MS_BuildFight [Field.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_
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
#define NUM_TEXTURE		(2)		// �e�N�X�`���̑���
//*********************************************************
// ���b�V���n�ʃN���X
//*********************************************************
class CMeshField : public Cform3D
{
public:
	CMeshField(int nPriority = 3);
	~CMeshField(void);

	static CMeshField *Create(LPDIRECT3DDEVICE9 pDevice,int nType, D3DXVECTOR3 pos, D3DXVECTOR3 rot,
								int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ);

	HRESULT Init(LPDIRECT3DDEVICE9 pDevice,int nType, D3DXVECTOR3 pos, D3DXVECTOR3 rot,
								int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ);
	void Uninit(void);
	void Update(void);
	void Draw(int pTexture);

	void SetPos(float x, float y, float z){ m_Pos.x = x; m_Pos.y = y; m_Pos.z = z; }
	void SetPos(D3DXVECTOR3 pos){ m_Pos = pos; }
	D3DXVECTOR3 GetPos(void){ return m_Pos; }

	void SetRot(float x, float y, float z){ m_Rot.x = x; m_Rot.y = y; m_Rot.z = z;}
	void SetRot(D3DXVECTOR3 rot){ m_Rot = rot; }
	D3DXVECTOR3 GetRot(void){ return m_Rot; }

	void SetMtxView (D3DXMATRIX changeMtx){m_MtxView=changeMtx;};
	void SetRotCamera (D3DXVECTOR3 rotCamera){};

	void SetColor(D3DXCOLOR col);

	float GetHeight(D3DXVECTOR3 pos, D3DXVECTOR3 *pNormal = NULL);
	float GetHeightPolygon(D3DXVECTOR3 *pVtx0, D3DXVECTOR3 *pVtx1, D3DXVECTOR3 *pVtx2,
											D3DXVECTOR3 pos, D3DXVECTOR3 *pNormal = NULL);

private:
	//LPDIRECT3DTEXTURE9		m_pD3DTex;		// �e�N�X�`���ǂݍ��ݏꏊ
	LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuff;	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9		m_pDevice;		// pDevice�I�u�W�F�N�g(�`��ɕK�v)
	LPDIRECT3DINDEXBUFFER9	m_pD3DIndexBuff;	// �C���f�b�N�X�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

	D3DXMATRIX				m_mtxWorld;			// ���[���h�}�g���b�N�X		
	D3DXMATRIX				m_MtxView;			//�r���[�}�g���N�X

	D3DMATERIAL9			m_material;				// �}�e���A��

	D3DXVECTOR3				m_Pos;			// �|���S���\���ʒu�̒��S���W
	D3DXVECTOR3				m_Rot;			// �|���S���̉�]�p
	D3DXVECTOR3				m_Scl;			//�傫��

	bool m_bTransParent;					// ���������ǂ���

	D3DXVECTOR3 *m_pBuffNormal;

	int m_nNumBlockX;
	int m_nNumBlockZ;
	int m_nNumVertex;
	int m_nNumVertexIndex;
	int m_nNumPolygon;
	float m_fSizeBlockX;
	float m_fSizeBlockZ;

	static const float m_aHeightFiled[33][33];

	LPDIRECT3DPIXELSHADER9 _ps;			//�s�N�Z���V�F�[�_�[
	LPD3DXCONSTANTTABLE    _psc;		//�s�N�Z���V�F�[�_�[�p�R���X�^���g�e�[�u��
	LPDIRECT3DVERTEXSHADER9 _vs[2];		//�o�[�e�b�N�X�V�F�[�_�[
	LPD3DXCONSTANTTABLE    _vsc[2];		//�o�[�e�b�N�X�V�F�[�_�[�p�R���X�^���g�e�[�u��

};

#endif

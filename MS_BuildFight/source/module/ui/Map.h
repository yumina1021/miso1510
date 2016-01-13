//=============================================================================
//
// CScene2D���� [CScene2D.h]
// Author : Tomoki Ohashi
//
//=============================================================================
#ifndef _CMAP_H_
#define _CMAP_H_
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "../../form/form2D.h"
//=============================================================================
// �O���錾
//=============================================================================
class CBall;
class CGoal;
//=============================================================================
// �N���X��`
//=============================================================================
class CMap
{
//=============================================================================
// ���J�����o
//=============================================================================
public:
	CMap();										// �R���X�g���N�^
	~CMap();										// �f�X�g���N�^
	HRESULT Init(LPDIRECT3DDEVICE9 device, CBall* ball[2], CGoal* goal);				// ������
	void Uninit();									// ���
	void Update();									// �X�V
	void Draw();									// �`��
	void MapChagePlus(){ vecfactor++; }
	void MapChageMinus(){ vecfactor++; }
	void MapChageSet(int id){ vecfactor = id; }

	static CMap* Create(LPDIRECT3DDEVICE9 device, CBall* ball[2], CGoal* goal);
//=============================================================================
// ����J�����o
//=============================================================================
private:
	void SetVertexPolygon();				// ���W�ݒ�

	LPDIRECT3DDEVICE9	m_pDevice;				// pDevice�I�u�W�F�N�g(�`��ɕK�v)

	int vecfactor;
	CBall* m_pBall[2];
	CGoal* m_pGoal;
	Cform2D* m_player[2];
	Cform2D* m_goal;
	Cform2D* m_flame;
	D3DXVECTOR3 m_mappos;
};// class CMap
#endif	_CMAP_H_

// EOF
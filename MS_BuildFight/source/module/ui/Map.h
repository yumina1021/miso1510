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
class CformX;
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
	HRESULT Init(LPDIRECT3DDEVICE9 device, CBall* ball[2], CGoal* goal, CformX* cursol, int player1, int player2);				// ������
	void Uninit();									// ���
	void Update();									// �X�V
	void Draw();									// �`��
	void SetMapFieldNum(int num);
	void SetMapFieldPos(int id, D3DXVECTOR3 pos, float map_size);
	void MapChagePlus(){ vecfactor++; }
	void MapChageMinus(){ vecfactor++; }
	void MapChageSet(int id){ vecfactor = id; }
	void SetDrawFlag(bool tf){ m_bDrawFlag = tf; }

	static CMap* Create(LPDIRECT3DDEVICE9 device, CBall* ball[2], CGoal* goal, CformX* cursol, int player1, int player2);
//=============================================================================
// ����J�����o
//=============================================================================
private:
	void SetVertexPolygon();				// ���W�ݒ�

	LPDIRECT3DDEVICE9	m_pDevice;				// pDevice�I�u�W�F�N�g(�`��ɕK�v)

	int vecfactor;
	CBall* m_pBall[2];
	CGoal* m_pGoal;
	CformX* m_pCursol;
	D3DXVECTOR3* m_fieldpos;
	Cform2D* m_player[2];
	Cform2D** m_Field;
	Cform2D* m_goal;
	Cform2D* m_flame;
	Cform2D* m_cursol;
	D3DXVECTOR3 m_mappos;

	bool m_bDrawFlag;
	int m_fieldnum;
};// class CMap
#endif	_CMAP_H_

// EOF
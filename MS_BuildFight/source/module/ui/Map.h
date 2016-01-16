//=============================================================================
//
// CScene2D処理 [CScene2D.h]
// Author : Tomoki Ohashi
//
//=============================================================================
#ifndef _CMAP_H_
#define _CMAP_H_
//=============================================================================
// インクルード
//=============================================================================
#include "../../form/form2D.h"
//=============================================================================
// 前方宣言
//=============================================================================
class CBall;
class CGoal;
class CformX;
//=============================================================================
// クラス定義
//=============================================================================
class CMap
{
//=============================================================================
// 公開メンバ
//=============================================================================
public:
	CMap();										// コンストラクタ
	~CMap();										// デストラクタ
	HRESULT Init(LPDIRECT3DDEVICE9 device, CBall* ball[2], CGoal* goal, CformX* cursol);				// 初期化
	void Uninit();									// 解放
	void Update();									// 更新
	void Draw();									// 描画
	void SetMapFieldNum(int num);
	void SetMapFieldPos(int id, D3DXVECTOR3 pos, float map_size);
	void MapChagePlus(){ vecfactor++; }
	void MapChageMinus(){ vecfactor++; }
	void MapChageSet(int id){ vecfactor = id; }

	static CMap* Create(LPDIRECT3DDEVICE9 device, CBall* ball[2], CGoal* goal, CformX* cursol);
//=============================================================================
// 非公開メンバ
//=============================================================================
private:
	void SetVertexPolygon();				// 座標設定

	LPDIRECT3DDEVICE9	m_pDevice;				// pDeviceオブジェクト(描画に必要)

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

	int m_fieldnum;
};// class CMap
#endif	_CMAP_H_

// EOF
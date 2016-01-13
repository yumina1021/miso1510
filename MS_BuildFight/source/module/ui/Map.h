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
	HRESULT Init(LPDIRECT3DDEVICE9 device, CBall* ball[2], CGoal* goal);				// 初期化
	void Uninit();									// 解放
	void Update();									// 更新
	void Draw();									// 描画
	void MapChagePlus(){ vecfactor++; }
	void MapChageMinus(){ vecfactor++; }
	void MapChageSet(int id){ vecfactor = id; }

	static CMap* Create(LPDIRECT3DDEVICE9 device, CBall* ball[2], CGoal* goal);
//=============================================================================
// 非公開メンバ
//=============================================================================
private:
	void SetVertexPolygon();				// 座標設定

	LPDIRECT3DDEVICE9	m_pDevice;				// pDeviceオブジェクト(描画に必要)

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
//=============================================================================
//
// MS_BuildFight [CGoal.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CGOAL_H_
#define _CGOAL_H_
//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "../../form/formX.h"
//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_MAX		(1)
//*****************************************************************************
// クラス定義
//*****************************************************************************
class CGoal
{
	public:
		CGoal();//コンストラクタ
		~CGoal(void);//デストラクタ

		static CGoal *Create(LPDIRECT3DDEVICE9 pDevice,int nType,D3DXVECTOR3 pos,D3DXVECTOR3 rot);

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice, int nType, D3DXVECTOR3 pos, D3DXVECTOR3 rot);//初期化
		void Uninit(void);//終了
		void Update(void);//更新
		void Draw(void);//描画
		void SetViewFlag(bool change){ m_bViewFlag = change; };

		void SetGoalFlag(bool change){ m_bGoal = change; };
		bool GetGoalFlag(void){ return m_bGoal; };

		D3DXVECTOR3 GetPos(void){ return m_pGoal->GetPos(); };

	private:
		CformX*				m_pGoal;
		CformX*				m_pGoalLing;

		LPDIRECT3DDEVICE9	m_pDevice;				// pDeviceオブジェクト(描画に必要)
		static const LPSTR	m_ModelName[];			//Modelの名前配列
		bool				m_bViewFlag;			//表示フラグ
		SHADER_SET			shaderSet[2];			//シェーダー情報
		bool				m_bGoal;				//ゴールした判定
		int					m_nRotChangeCount;
		float				m_fChangerot;
};

#endif

/////////////EOF////////////
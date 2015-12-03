//=============================================================================
//
// MS_BuildFight [CBall.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CBUILDING_H_
#define _CBUILDING_H_
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
class CLocusEffect;
//*****************************************************************************
// クラス定義
//*****************************************************************************
class CBall  : public CformX
{
	public:
		CBall();//コンストラクタ
		~CBall(void);//デストラクタ

		static CBall *Create(LPDIRECT3DDEVICE9 pDevice,int nType,D3DXVECTOR3 pos,D3DXVECTOR3 rot);

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice,int nType);//初期化
		void Uninit(void);//終了
		void Update(void);//更新
		void Draw(void);//描画
		void SetViewFlag(bool change){ m_bViewFlag = change; };

		void SetGoalFlag(bool change){ m_bGoal = change; };
		bool GetGoalFlag(void){ return m_bGoal; };

		void SetShotNum(int num){ shot_num = num; };
		int GetShotNum(void){ return shot_num; };

		void AddForce(D3DXVECTOR3 Force, D3DXVECTOR3 Position);
		void AddForce(D3DXVECTOR3 Force);

		D3DXVECTOR3 GetVelocity(void){ return m_MovVelocity; }
		void SetVelocity(D3DXVECTOR3 vel){ m_MovVelocity = vel; }

		void SetMoveFlag(bool mov){ m_bmove = mov; };
	private:
		LPDIRECT3DDEVICE9	m_pDevice;				// pDeviceオブジェクト(描画に必要)
		static const LPSTR	m_ModelName[];			//Modelの名前配列
		bool				m_bViewFlag;			//表示フラグ
		SHADER_SET			shaderSet;				//シェーダー情報
		bool				m_bGoal;				//ゴールした判定
		CLocusEffect*		m_pLocusEffect;
		int					shot_num;

		float m_Mass;
		float m_MOI;
		float m_MovResist;
		float m_RotResist;
		D3DXVECTOR3 m_MovVelocity;
		D3DXVECTOR3 m_RotVelocity;
		bool m_bmove;
};

#endif

/////////////EOF////////////
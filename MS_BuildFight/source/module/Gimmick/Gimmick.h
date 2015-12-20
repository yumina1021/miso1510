//=============================================================================
//
// MS_BuildFight [Gimmick.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CGIMMICK_H_
#define _CGIMMICK_H_
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
//オブジェクトの種類
typedef enum
{
	GIMMICK_CUBE=0,		//四角の不動の金属物体
	GIMMICK_CLOUD,		//積乱雲
	GIMMICK_CROW,		//カラス
	GIMMICK_UFO,		//UFO
	GIMMICK_WIND,		//風
	GIMMICK_TORNADO,	//竜巻
	GIMMICK_MAX,
}GIMMICKTYPE;

typedef enum
{
	MOVETYPE_STOP=0,	//停止
	MOVETYPE_UPDOWN,	//上下移動
	MOVETYPE_SLIDE,		//スライド
	MOVETYPE_MAX
}MOVETYPE;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CGimmick : public CformX
{
	public:
		CGimmick();						//コンストラクタ
		~CGimmick(void);		//デストラクタ
	
		static CGimmick *Create(LPDIRECT3DDEVICE9 pDevice, GIMMICKTYPE GimmickType,MOVETYPE MoveType, D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	
		HRESULT Init(LPDIRECT3DDEVICE9 pDevice, int nType, MOVETYPE MoveType);			//初期化
		void Uninit(void);											//終了
		void Update(void);											//更新
		void Draw(void);											//描画
		void SetViewFlag(bool change){ m_bViewFlag = change; };

		void SetSize(D3DXVECTOR3 Size){ m_Size = Size; };
		D3DXVECTOR3 GetSize(void){ return m_Size; };

		void SetPos(D3DXVECTOR3 Pos){ m_Pos = Pos; };
		D3DXVECTOR3 GetPos(void){ return m_Pos; };


		void SetGimmickType(GIMMICKTYPE GimmickType){ m_GimmickType = GimmickType; };
		GIMMICKTYPE GetGimmickType(void){ return m_GimmickType; };

		void SetMoveType(MOVETYPE MoveType){ m_MoveType = MoveType; };
		MOVETYPE GetMoveType(void){ return m_MoveType; };

		void SetMagnet(NS mag){ m_nsMagnet = mag; };
		NS GetMagnet(void){ return  m_nsMagnet; };
	private:
		void _UpdateObject(void);
		void _UpdateCube(void);
		void _UpdateCloud(void);
		void _UpdateCrow(void);
		void _UpdateUFO(void);
		void _UpdateWind(void);
		void _UpdateTornado(void);

		//四角の物体の移動関係
		void UpdateCubeMoveStop(void);
		void UpdateCubeMoveSlide(void);
		void UpdateCubeMoveUpDown(void);

		//雲の移動関係
		void UpdateCloudMoveStop(void);
		void UpdateCloudMoveSlide(void);
		void UpdateCloudMoveUpDown(void);

		//カラスの移動関係
		void UpdateCrowMoveStop(void);
		void UpdateCrowMoveSlide(void);
		void UpdateCrowMoveUpDown(void);

		//UFOの移動関係
		void UpdateUFOMoveStop(void);
		void UpdateUFOMoveSlide(void);
		void UpdateUFOMoveUpDown(void);

		//風
		void UpdateWindMoveStop(void);
		void UpdateWindMoveSlide(void);
		void UpdateWindMoveUpDown(void);

		//竜巻
		void UpdateTornadoMoveStop(void);
		void UpdateTornadoMoveSlide(void);
		void UpdateTornadoMoveUpDown(void);

		LPDIRECT3DDEVICE9	m_pDevice;				// pDeviceオブジェクト(描画に必要)
		static const LPSTR	m_ModelName[];			//Modelの名前配列
		bool				m_bViewFlag;			//表示フラグ
		GIMMICKTYPE			m_GimmickType;
		MOVETYPE			m_MoveType;
		D3DXVECTOR3			m_Size;
		D3DXVECTOR3			m_Pos;
		D3DXVECTOR3			m_Rot;
		D3DXVECTOR3			m_Scl;
		float				m_Speed;				//速度
		D3DXVECTOR3			m_Work;
		NS					m_nsMagnet;
};

#endif

/////////////EOF////////////
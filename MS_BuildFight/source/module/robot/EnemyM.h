//=============================================================================
//
// MS_BuildFight [CEnemyM.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CENEMYM_H_
#define _CENEMYM_H_
//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "Model.h"
#include "../../form/form.h"
//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	VALUE_MOVE_PLAYER		(2.0f)				// プレイヤーの移動量
#define	VALUE_MOVE_ENEMY		(4.0f)				// プレイヤーの移動量
#define	VALUE_TURBO_PLAYER		(4.0f)				// プレイヤーの移動量
#define	VALUE_MOVE_PLAYER_AIR	(2.0f)				// プレイヤーの移動量(ジャンプ中)
#define	RATE_MOVE_PLAYER		(0.20f)				// 移動慣性係数
#define	VALUE_ROTATE_PLAYER		(D3DX_PI * 0.05f)	// 回転速度
#define	RATE_ROTATE_PLAYER		(0.20f)				// 回転慣性係数
#define VALUE_JUMP				(6.65f)				// ジャンプ値

typedef enum
{
	MOVE_UP =0,
	MOVE_DOWN,
	MOVE_RIGHT,
	MOVE_LEFT,
	MOVE_STAY,
	MOVE_JUMP,
	MOVE_OVERLOAD,
	MOVE_SHOOT,
	MOVE_MAX
}MOVE;

class CSound;
class CInputKeyboard;
class CformX;
class CPlayerM;
//*****************************************************************************
// クラス定義
//*****************************************************************************
class CEnemyM  : public Cform
{
	public:
		CEnemyM(int nPriority = 6);//コンストラクタ
		~CEnemyM(void);//デストラクタ

		static CEnemyM *Create(LPDIRECT3DDEVICE9 pDevice,int nTypeModel,D3DXVECTOR3 pos,D3DXVECTOR3 rot,bool CPU);

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice,int nTypeModel,D3DXVECTOR3 pos, D3DXVECTOR3 rot,bool CPU);//初期化
		void Uninit(void);//終了
		void Update(void);//更新
		void Draw(void);//描画
		void Restart(D3DXVECTOR3 pos,D3DXVECTOR3 rot);

		void SetPos(D3DXVECTOR3 pos){m_Pos=pos;};
		void SetPos(float fx,float fy,float fz){m_Pos.x=fx;m_Pos.y=fy;m_Pos.z=fz;};
		D3DXVECTOR3 GetPos(void){return m_Pos;};

		void SetRot(D3DXVECTOR3 rot){m_Rot=rot;};
		void SetRot(float fx,float fy,float fz){m_Rot.x=fx;m_Rot.y=fy;m_Rot.z=fz;};
		D3DXVECTOR3 GetRot(void){return m_Rot;};

		void SetMtxView (D3DXMATRIX changeMtx){};
		D3DXVECTOR3 GetRotCamera (void){return m_RotCamera;};
		void SetRotCamera (D3DXVECTOR3 rotCamera){m_RotCamera=rotCamera;};

		void SetTexture(LPSTR pTexName,int num);
		void SetTextureNum(int num){m_nTextureNum=num;};
		int GetTextureNum(void){return m_nTextureNum;};

		D3DXVECTOR3 GetMove(void){return m_Move;};

		bool IsFinishMotion(void){ return m_bFinishMotion;}

		void SetMotion(MOTIONTYPE motionType);

		int GetType(void){return m_nType;};
	private:

		void UpdateMotion(void);
		float lerp(float a,float b,float per){return (a*per)+(b*(1-per));};
		D3DXVECTOR3 lerpVec(D3DXVECTOR3 a,D3DXVECTOR3 b,float per);

		LPDIRECT3DDEVICE9	m_pDevice;			// pDeviceオブジェクト(描画に必要)

		D3DXVECTOR3		m_Pos;					//位置
		D3DXVECTOR3		m_PosOld;				//前回位置

		D3DXVECTOR3		m_Rot;					//向き
		D3DXVECTOR3		m_rotDestModel;			//目的の向き
		D3DXVECTOR3		m_Move;					// 現在の移動量

		D3DXVECTOR3		m_RotCamera;			//カメラの向き
		bool			m_bJump;				// ジャンプ中かどうか

		MOTIONTYPE		m_motionType;			// モーションタイプ
		int				m_nEffectFinishCount;	//エフェクト終了カウント

		bool			m_bCPUFlag;				//自動移動フラグ
		MOVE			m_move;					//モデルの移動パターン

		int				m_moveCnt;				//移動カウント

		CModel				*m_apModel[MODELPARTS_MAX];	// モデルへのポインタ
		LPDIRECT3DTEXTURE9	m_pD3DTex[TEXTURE_MAX];		//テクスチャ表示用
		int					m_nTextureNum;				//テクスチャーの番号

		D3DXMATRIX		m_mtxWorld;				// ワールドマトリックス

		float			m_fHeightField;			// 地面の高さ

		int				m_nNumModel;			// モデル数

		int				m_nNumKey;				// キーの数
		KEY_INFO		*m_pKeyInfo;			// キーへのポインタ

		int				m_nKey;					// キーNo.
		int				m_nCountMotion;			// モーションカウンタ

		bool			m_bLoopMotion;			// ループモーションかどうか

		bool			m_bMotion;				// モーションしているかどうか
		bool			m_bFinishMotion;		// モーションが終了しているかどうか

		bool			m_bPause;				// ポーズON/OFF
		bool			m_bDispDebug;			// デバッグ表示ON/OFF
		int				m_nType;				//タイプ保存用

		float			m_fPosHightPlus;

		D3DXVECTOR3		m_Min;
		D3DXVECTOR3		m_Max;
};

#endif

/////////////EOF////////////
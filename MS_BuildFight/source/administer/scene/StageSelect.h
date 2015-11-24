//=============================================================================
//
// MS_BuildFight [CStageSelect.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CSTAGE_SELECT_H_
#define _CSTAGE_SELECT_H_
//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
// 
//*****************************************************************************
const int MAX_BALL(4);


//*****************************************************************************
// クラス定義
//*****************************************************************************
class CBackGround;	//前方宣言
class CFade;
class CCharPicture;
class CEffect;
class CBall;
class CMeshField;	//前方宣言
class CCursor;
class CButton;

//*****************************************************************************
// 列挙体定義
//*****************************************************************************
struct DISP_PLAY_STAGE
{
	CBall*	pDispObj;
	float	fLenCoff;
	int		nDestCnt;
	float	fLenCoffDest;

};

class CStageSelect  : public CScene
{
	
	public:

		enum class STATE
		{
			NORMAL,
			SATELLITE_ORBIT,
			CHANGE_SCENE,
		};
		enum BUTTON_TYPE
		{
			LEFT = 0,
			RIGHT,
			BUTTON_TYPE_MAX,
		};


		struct PLAYER_DATA
		{
			int	nSelectNum;			//選択中の番号
			CCursor* pCursor;		// カーソ表示用のポインタ
		};

		CStageSelect(void);			//コンストラクタ
		~CStageSelect(void);			//デストラクタ

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice);//初期化
		void Uninit(void);						//終了
		void Update(void);						//更新
		void Draw(void);						//描画
		void SelectByButton(void);				//キーボードでの選択
		void SelectByCursor(void);				//カール移動での選択
		void UpdateFade(void);					//フェードの更新
		void UpdateSelectObject(void);			//選択に使うオブジェクトの更新

		static void NomalizeSelectObject(int& nParamVal);//選択に使うオブジェクトの更新
		
		bool HitChkRect(const D3DXVECTOR3& paramPos1,
			const D3DXVECTOR3& paramPos2,
			const D3DXVECTOR3& paramLen1,
			const D3DXVECTOR3& paramLen2);

	private:
		CBackGround*		m_pBackGround;		//背景
		CFade*				m_pFade;			//フェード
		CMeshField*			m_pMeshField;		//メッシュフィールドのポインタ
		DISP_PLAY_STAGE		m_Obj[MAX_BALL];
		float				m_fDiffuse;			//アニメーション用
		bool				m_bVsSelectFlag;	//VSモード用
		bool				m_bTitleBackFlag;	//タイトルに行きました
		bool				m_bSendData;		//相手データが送られた
		int					m_nCursorNum;		
		float				m_fTime;
		STATE				m_nState;
		PLAYER_DATA			m_playerData[2];

};

#endif

/////////////EOF////////////
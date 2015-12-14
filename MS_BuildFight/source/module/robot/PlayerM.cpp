//=============================================================================
//
// MS_BuildFight [CPlayerM.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#include "PlayerM.h"
#include "Model.h"
#include "robotmotiondata.h"

#include "../field/Field.h"

#include "../etc/Camera.h"

#include "../../administer/Input.h"
#include "../../administer/Maneger.h"
#include "../../administer/debugproc.h"
#include "../../administer/Sound.h"

#include "../../administer/scene/Game.h"

#include "../../exten_common.h"
//*****************************************************************************
// 静的変数
//*****************************************************************************

#define SHOT_MOTION_COUNT_MAX	(80)
//=============================================================================
// コンストラクタ
//=============================================================================
CPlayerM :: CPlayerM(OBJTYPE objtype,int nPriority) : Cform(objtype,nPriority)
{
	for(int nCntModel = 0; nCntModel < MODELPARTS_MAX; nCntModel++)
	{
		m_apModel[nCntModel] = NULL;
	}

	m_pD3DTex=NULL;
}
//=============================================================================
// デストラクタ
//=============================================================================
CPlayerM :: ~CPlayerM(void)
{
}
//=============================================================================
// CPlayerM生成
//=============================================================================
CPlayerM *CPlayerM::Create(LPDIRECT3DDEVICE9 pDevice,int nTypeModel,D3DXVECTOR3 movePos,D3DXVECTOR3 moveRot)
{
	CPlayerM *pformX;

	pformX = new CPlayerM();
	pformX->Init(pDevice,nTypeModel,movePos,moveRot,false);

	return pformX;
}
//=============================================================================
// 初期化
//=============================================================================
HRESULT CPlayerM :: Init(LPDIRECT3DDEVICE9 pDevice,int nTypeModel,D3DXVECTOR3 pos, D3DXVECTOR3 rot,bool CPU)
{
	//デバイスの取得
	m_pDevice=pDevice;

	//タイプの保存
	m_nType=nTypeModel;

	for(int nCntModel = 0; nCntModel < MODELPARTS_MAX; nCntModel++)
	{
		m_apModel[nCntModel] = CModel::Create(pDevice,nCntModel,nTypeModel*12,
			D3DXVECTOR3(g_aKeyDef[nCntModel][0], g_aKeyDef[nCntModel][1], g_aKeyDef[nCntModel][2]),
			D3DXVECTOR3(g_aKeyDef[nCntModel][3], g_aKeyDef[nCntModel][4], g_aKeyDef[nCntModel][5]));
	}

	// モデルパーツ階層構造設定
	m_apModel[0]->SetParent(NULL);			// [0]体   → (親)NULL
	m_apModel[1]->SetParent(m_apModel[0]);	// [1]頭   → (親)[0]体
	m_apModel[2]->SetParent(m_apModel[0]);	// [2]右腕 → (親)[0]体
	m_apModel[3]->SetParent(m_apModel[2]);	// [3]右手 → (親)[2]右腕
	m_apModel[4]->SetParent(m_apModel[3]);	// [3]右手 → (親)[2]右腕
	m_apModel[5]->SetParent(m_apModel[0]);	// [4]左腕 → (親)[0]体
	m_apModel[6]->SetParent(m_apModel[5]);	// [5]左手 → (親)[4]左腕
	m_apModel[7]->SetParent(m_apModel[6]);	// [5]左手 → (親)[4]左腕
	m_apModel[8]->SetParent(m_apModel[0]);	// [6]右腿 → (親)[0]体
	m_apModel[9]->SetParent(m_apModel[8]);	// [7]右足 → (親)[6]右足
	m_apModel[10]->SetParent(m_apModel[0]);	// [8]左腿 → (親)[0]体
	m_apModel[11]->SetParent(m_apModel[10]);	// [9]左足 → (親)[8]左足

	m_Pos = pos;
	m_PosOld = pos;
	m_Rot = rot;
	m_rotDestModel = rot;
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//パーツ総数を格納
	m_nNumModel = MODELPARTS_MAX;

	m_nNumKey = 0;
	m_pKeyInfo = NULL;
	m_nKey = 0;

	m_nCountMotion = 0;

	m_fShotMotionRatio = 0.0f;
	m_nShotMotionCntPlus = 0;

	m_bLoopMotion = false;

	m_bMotion = false;
	m_bFinishMotion = false;

	m_bPause = false;

	m_bDispDebug = true;

	m_Min=D3DXVECTOR3(-30.0f,-20.0f,-30.0f);
	m_Max=D3DXVECTOR3(30.0f,20.0f,30.0f);

	// アニメーション設定
	SetMotion(MOTIONTYPE_NEUTRAL);

	//ピクセルシェーダー用に変換1
	Create_PS("source/shader/basicPS.hlsl", "PS", &shaderSet.ps, &shaderSet.psc,m_pDevice);

	//バーテックスシェーダー用に変換1
	Create_VS("source/shader/basicVS.hlsl", "VS", &shaderSet.vs, &shaderSet.vsc, m_pDevice);

	//テクスチャ作る
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/chara.png", &m_pD3DTex);

	return S_OK;
}
//=============================================================================
// 終了
//=============================================================================
void CPlayerM :: Uninit(void)
{
	//様々なオブジェクトの終了（開放）処理

	// モデルの開放
	for(int nCntModel = 0; nCntModel < MODELPARTS_MAX; nCntModel++)
	{
		if(m_apModel[nCntModel])
		{
			m_apModel[nCntModel]->Uninit();
			delete m_apModel[nCntModel];
			m_apModel[nCntModel] = NULL;
		}
	}

	if(m_pKeyInfo)
	{
		m_pKeyInfo = NULL;
	}

	m_pD3DTex->Release();
	m_pD3DTex = NULL;

	if (shaderSet.ps != NULL)	shaderSet.ps->Release();
	if (shaderSet.psc != NULL)	shaderSet.psc->Release();
	if (shaderSet.vs != NULL)	shaderSet.vs->Release();
	if (shaderSet.vsc != NULL)	shaderSet.vsc->Release();
	Cform::Release();

}
void CPlayerM :: Restart(D3DXVECTOR3 pos,D3DXVECTOR3 rot)
{
	m_Pos = pos;
	m_PosOld = pos;
	m_Rot = rot;
	m_rotDestModel = rot;
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_nNumKey = 0;
	m_pKeyInfo = NULL;
	m_nKey = 0;
	m_nCountMotion = 0;
	m_bLoopMotion = false;

	m_bMotion = false;
	m_bFinishMotion = false;

	m_bPause = false;

	m_bDispDebug = true;

	// アニメーション設定
	SetMotion(MOTIONTYPE_NEUTRAL);


}
//=============================================================================
// 更新
//=============================================================================
void CPlayerM :: Update(void)
{
	//サウンドの取得
	CSound	*pSound;
	pSound = CManager::GetSound();

	//キーボードの取得
	CInputKeyboard	*pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//法線（まだ未使用）
	D3DXVECTOR3 normal;

	//変数定義
	float fDiffRotY=0;


	if (m_bPause == false)
	{
		//// 目的の角度までの差分
		//fDiffRotY = Rotation_Normalizer(m_rotDestModel.y - m_Rot.y);

		//// 目的の角度まで慣性をかける
		//m_Rot.y +=fDiffRotY * RATE_ROTATE_PLAYER;

		//m_Rot.y = Rotation_Normalizer(m_Rot.y);

		//// 位置移動
		//m_Pos.x += m_Move.x;
		//m_Pos.z += m_Move.z;

		//m_Move.x += (0.0f - m_Move.x) * REGIST_MOVE;
		//m_Move.z += (0.0f - m_Move.z) * REGIST_MOVE;

		if((m_motionType == MOTIONTYPE_SHOT && IsFinishMotion() == true))
		{// ショットモーション終了
			// ニュートラルモーション再生
			SetMotion(MOTIONTYPE_NEUTRAL);
		}
		
		CDebugProc::Print("現在のモーション：%d,Key数：%d\n", m_motionType,m_nKey);
		CDebugProc::Print("割合：%f\n", m_fShotMotionRatio);


		if (pInputKeyboard->GetKeyPress(DIK_U))
		{
			m_fShotMotionRatio = 0.0f;
			m_nShotMotionCntPlus = 0;
			SetMotion(MOTIONTYPE_SHOT);
		}

		if (pInputKeyboard->GetKeyPress(DIK_I))
		{
			m_fShotMotionRatio ++;
		}
		if (pInputKeyboard->GetKeyPress(DIK_O))
		{
			m_fShotMotionRatio --;
		}

		// アニメーション更新
		if (m_motionType == MOTIONTYPE_SHOT)
		{
			UpdateShotMotion();
		}
		else
		{
			UpdateMotion();
		}
		
	}

}
//=============================================================================
// 描画
//=============================================================================
void CPlayerM::Draw(void)
{
	D3DXMATRIX mtxScale, mtxRot, mtxTranslate;

	CCamera* pCamera = CManager::GetCamera();

	//SetRotCamera(pCamera->GetRotCamera());

	//SetMtxView(pCamera->GetMtxView());

	//// ワールドマトリックスの初期化
	//D3DXMatrixIdentity(&m_mtxWorld);

	//// 回転を反映
	//D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Rot.y, m_Rot.x, m_Rot.z);
	//D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//// 移動を反映
	//D3DXMatrixTranslation(&mtxTranslate, m_Pos.x, m_Pos.y, m_Pos.z);
	//D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTranslate);

	// ワールドマトリックスの設定

	CDebugProc::Print("PlayerM%f,%f,%f\n", m_Pos.x, m_Pos.y, m_Pos.z);
	CDebugProc::Print("PlayerM%f,%f,%f\n", m_Rot.x, m_Rot.y, m_Rot.z);
	// モデルパーツの描画
	m_apModel[0]->SetPosOrg(m_Pos);
	m_apModel[0]->SetRotOrg(m_Rot);
	for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
	{
		if (m_apModel[nCntModel])
		{
			m_apModel[nCntModel]->Draw(m_pD3DTex, &shaderSet, pCamera);
		}
	}
}
//=============================================================================
// モーション設定
//=============================================================================
void CPlayerM::SetMotion(MOTIONTYPE motionType)
{

	switch(motionType)
	{
	case MOTIONTYPE_NEUTRAL:
		m_pKeyInfo = &g_aKeyNeutral[0];
		m_nNumKey = sizeof g_aKeyNeutral / sizeof(KEY_INFO);
		m_bLoopMotion = true;
		break;

	case MOTIONTYPE_SHOT:
		m_pKeyInfo = &g_aKeyShot[0];
		m_nNumKey = sizeof g_aKeyShot / sizeof(KEY_INFO);
		m_bLoopMotion = false;
		break;
	}

	m_motionType = motionType;
	m_nKey = 0;
	
	m_nCountMotion = 0;
	m_bMotion = true;
	m_bFinishMotion = false;

	// 初期値設定
	for(int nCntModel = 0; nCntModel < MODELPARTS_MAX; nCntModel++)
	{
		m_apModel[nCntModel]->SetPos(m_pKeyInfo->aKey[nCntModel].fPosX,
											m_pKeyInfo->aKey[nCntModel].fPosY,
											m_pKeyInfo->aKey[nCntModel].fPosZ);

		m_apModel[nCntModel]->SetRot(m_pKeyInfo->aKey[nCntModel].fRotX,
											m_pKeyInfo->aKey[nCntModel].fRotY,
											m_pKeyInfo->aKey[nCntModel].fRotZ);
	}
}

//=============================================================================
// モーション更新
//=============================================================================
void CPlayerM::UpdateMotion(void)
{
	if(m_bMotion == true)
	{// モーションあり
		for(int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
		{
			if(m_apModel[nCntModel])
			{// モデルあり

				KEY *pKey, *pKeyNext;
				float fDiffMotion;
				float fRateMotion;

				float fPosX, fPosY, fPosZ;
				float fRotX, fRotY, fRotZ;

				// 現在のキー
				pKey = &m_pKeyInfo[m_nKey].aKey[nCntModel];
				// 次のキー
				pKeyNext = &m_pKeyInfo[((m_nKey + 1) % m_nNumKey)].aKey[nCntModel];
				// 現在のキーの再生フレーム全体に対する相対値
				fRateMotion = (float)m_nCountMotion / (float)m_pKeyInfo[m_nKey].nFrame;

				// X移動
				fDiffMotion = pKeyNext->fPosX - pKey->fPosX;
				fPosX = (pKey->fPosX + (fDiffMotion * fRateMotion));

				// Y移動
				fDiffMotion = pKeyNext->fPosY - pKey->fPosY;
				fPosY = pKey->fPosY + (fDiffMotion * fRateMotion);

				// Z移動
				fDiffMotion = pKeyNext->fPosZ - pKey->fPosZ;
				fPosZ = pKey->fPosZ + (fDiffMotion * fRateMotion);

				// X回転
				fDiffMotion = Rotation_Normalizer(pKeyNext->fRotX - pKey->fRotX);


				fRotX = Rotation_Normalizer(pKey->fRotX + (fDiffMotion * fRateMotion));

				// Y回転
				fDiffMotion = Rotation_Normalizer(pKeyNext->fRotY - pKey->fRotY);

				fRotY = Rotation_Normalizer(pKey->fRotY + (fDiffMotion * fRateMotion));

				// Z回転
				fDiffMotion = Rotation_Normalizer(pKeyNext->fRotZ - pKey->fRotZ);

				fRotZ = Rotation_Normalizer(pKey->fRotZ + (fDiffMotion * fRateMotion));

				// 位置(オフセット)を設定
				m_apModel[nCntModel]->SetPos(fPosX, fPosY, fPosZ);

				// 回転を設定
				m_apModel[nCntModel]->SetRot(fRotX, fRotY, fRotZ);
			}
		}

		m_nCountMotion++;

		if(m_nCountMotion > m_pKeyInfo[m_nKey].nFrame)
		{// キーの再生フレーム数に達した
			if(m_bLoopMotion == false && (m_nKey + 2) >= m_nNumKey)
			{// 単発モーションで最終キーに達した
				m_bFinishMotion = true;
				m_nCountMotion = m_pKeyInfo[(m_nNumKey - 1)].nFrame;
			}
			else
			{
				m_nKey = (m_nKey + 1) % m_nNumKey;
				m_nCountMotion = 0;
			}	
		}
	}
}
//=============================================================================
// 打つモーション更新
//=============================================================================
void CPlayerM::UpdateShotMotion(void)
{
	if (m_bMotion == true)
	{// モーションあり
		for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
		{
			if (m_apModel[nCntModel])
			{// モデルあり

				KEY *pKey, *pKeyNext;
				float fDiffMotion;
				float fRateMotion;

				float fPosX, fPosY, fPosZ;
				float fRotX, fRotY, fRotZ;

				// 現在のキー
				pKey = &m_pKeyInfo[m_nKey].aKey[nCntModel];
				// 次のキー
				pKeyNext = &m_pKeyInfo[((m_nKey + 1) % m_nNumKey)].aKey[nCntModel];

				// 現在のキーの再生フレーム全体に対する相対値
				fRateMotion = (m_fShotMotionRatio - m_nShotMotionCntPlus) / (float)m_pKeyInfo[m_nKey].nFrame;

				// X移動
				fDiffMotion = pKeyNext->fPosX - pKey->fPosX;
				fPosX = (pKey->fPosX + (fDiffMotion * fRateMotion));

				// Y移動
				fDiffMotion = pKeyNext->fPosY - pKey->fPosY;
				fPosY = pKey->fPosY + (fDiffMotion * fRateMotion);

				// Z移動
				fDiffMotion = pKeyNext->fPosZ - pKey->fPosZ;
				fPosZ = pKey->fPosZ + (fDiffMotion * fRateMotion);

				// X回転
				fDiffMotion = Rotation_Normalizer(pKeyNext->fRotX - pKey->fRotX);

				fRotX = Rotation_Normalizer(pKey->fRotX + (fDiffMotion * fRateMotion));

				// Y回転
				fDiffMotion = Rotation_Normalizer(pKeyNext->fRotY - pKey->fRotY);

				fRotY = Rotation_Normalizer(pKey->fRotY + (fDiffMotion * fRateMotion));

				// Z回転
				fDiffMotion = Rotation_Normalizer(pKeyNext->fRotZ - pKey->fRotZ);

				fRotZ = Rotation_Normalizer(pKey->fRotZ + (fDiffMotion * fRateMotion));

				// 位置(オフセット)を設定
				m_apModel[nCntModel]->SetPos(fPosX, fPosY, fPosZ);

				// 回転を設定
				m_apModel[nCntModel]->SetRot(fRotX, fRotY, fRotZ);
			}
		}

		if (m_fShotMotionRatio < 0.0f)
		{
			m_fShotMotionRatio = 0.0f;
		}

		// キーの再生フレーム数に達した
		if (m_fShotMotionRatio > m_pKeyInfo[m_nKey].nFrame + m_nShotMotionCntPlus)
		{
			if (m_fShotMotionRatio > SHOT_MOTION_COUNT_MAX)
			{
				m_fShotMotionRatio = SHOT_MOTION_COUNT_MAX;
				m_bFinishMotion = true;
				m_nCountMotion = m_pKeyInfo[(m_nNumKey - 1)].nFrame;
			}
			else
			{
				m_nKey = (m_nKey + 1) % m_nNumKey;
				m_nShotMotionCntPlus = m_fShotMotionRatio;
			}
		}

		//もしモーションが戻ったら
		if (m_nShotMotionCntPlus > m_fShotMotionRatio)
		{
			m_nKey = (m_nKey - 1) % m_nNumKey;
			m_fShotMotionRatio = m_nShotMotionCntPlus;
			m_nShotMotionCntPlus = 0.0f;
		}
	}
}

D3DXVECTOR3 CPlayerM ::lerpVec(D3DXVECTOR3 a,D3DXVECTOR3 b,float per)
{
	D3DXVECTOR3 c;

	c.x=lerp(a.x,b.x,per);
	c.y=lerp(a.y,b.y,per);
	c.z=lerp(a.z,b.z,per);

	return c;
}

/////////////EOF////////////
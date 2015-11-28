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
#include "robotmotiondataGN3.h"
#include "EnemyM.h"

#include "../field/Field.h"

#include "../etc/LocusEffect.h"
#include "../etc/Camera.h"

#include "../ui/Score.h"
#include "../ui/Gauge.h"
#include "../ui/Icon.h"

#include "../../form/formX.h"

#include "../../administer/Input.h"
#include "../../administer/Maneger.h"
#include "../../administer/debugproc.h"
#include "../../administer/Sound.h"

#include "../../administer/scene/Game.h"

#include "../../exten_common.h"
//*****************************************************************************
// 静的変数
//*****************************************************************************
#define	VS_MAX				(2)						// VSの数
#define	PS_MAX				(2)						// PSの数
//=============================================================================
// コンストラクタ
//=============================================================================
CPlayerM :: CPlayerM(OBJTYPE objtype,int nPriority) : Cform(objtype,nPriority)
{
	for(int nCntModel = 0; nCntModel < MODELPARTS_MAX; nCntModel++)
	{
		m_apModel[nCntModel] = NULL;
	}
	for(int i=0;i<TEXTURE_MAX;i++)
	{
		m_pD3DTex[i]=NULL;
	}
	
	m_nTextureNum=0;
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

	m_bJump = false;
	m_fHeightField = 0.0f;

	//パーツ総数を格納
	m_nNumModel = MODELPARTS_MAX;

	m_nNumKey = 0;
	m_pKeyInfo = NULL;
	m_nKey = 0;

	m_nCountMotion = 0;

	m_bLoopMotion = false;

	m_bMotion = false;
	m_bFinishMotion = false;

	m_bPause = false;

	m_bDispDebug = true;

	m_bCPUFlag=CPU;
	m_moveCnt=0;

	m_fPosHightPlus=0.0f;

	m_Min=D3DXVECTOR3(-30.0f,-20.0f,-30.0f);
	m_Max=D3DXVECTOR3(30.0f,20.0f,30.0f);


	// アニメーション設定
	SetMotion(MOTIONTYPE_NEUTRAL);


	//ピクセルシェーダー用に変換1
	Create_PS("source/shader/basicPS.hlsl", "PS_DIFFUSE", &shaderSet.ps, &shaderSet.psc,m_pDevice);

	//バーテックスシェーダー用に変換1
	Create_VS("source/shader/basicVS.hlsl", "VS", &shaderSet.vs, &shaderSet.vsc, m_pDevice);

	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/toumei3.png", &m_pD3DTex[m_nTextureNum]);

	return S_OK;
}
//=============================================================================
// 終了
//=============================================================================
void CPlayerM :: Uninit(void)
{
	//様々なオブジェクトの終了（開放）処理

	//if(m_pShadow)
	//{
	//	m_pShadow->Uninit();
	//	m_pShadow = NULL;
	//}

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

	// テクスチャの開放
	for(int i=0;i<TEXTURE_MAX;i++)
	{
		if(m_pD3DTex[i]!=NULL)
		{
			m_pD3DTex[i]->Release();
			m_pD3DTex[i]=NULL;
		}
	}

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

	m_bJump = false;
	m_fHeightField = 0.0f;

	m_nNumKey = 0;
	m_pKeyInfo = NULL;
	m_nKey = 0;
	m_nCountMotion = 0;
	m_bLoopMotion = false;

	m_bMotion = false;
	m_bFinishMotion = false;

	m_bPause = false;

	m_bDispDebug = true;

	m_moveCnt=0;

	m_fPosHightPlus=0.0f;

	m_nEffectFinishCount=0;

	SetTextureNum(0);

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
		// 目的の角度までの差分
		fDiffRotY = Rotation_Normalizer(m_rotDestModel.y - m_Rot.y);

		// 目的の角度まで慣性をかける
		m_Rot.y +=fDiffRotY * RATE_ROTATE_PLAYER;

		m_Rot.y = Rotation_Normalizer(m_Rot.y);

		// 重力をかける
		//m_Move.y -= GRAVITY * 0.05f;

		float Distance = 0.0f;
		//Distance = (float)sqrt((double)(m_Pos.x - enemypos.x)*(double)(m_Pos.x - enemypos.x) + (double)(m_Pos.y - enemypos.y)*(double)(m_Pos.y - enemypos.y) + (double)(m_Pos.z - enemypos.z)*(double)(m_Pos.z - enemypos.z));

		// 位置移動
		m_Pos.x += m_Move.x;
		//m_Pos.y += m_Move.y;
		m_Pos.z += m_Move.z;

		m_Move.x += (0.0f - m_Move.x) * REGIST_MOVE;
		m_Move.z += (0.0f - m_Move.z) * REGIST_MOVE;

		//フィールドとの当たり判定
		m_fHeightField = 0.0f;


		if(m_bJump == false)
		{
			if(m_Move.x <= 0.005f && m_Move.x >= -0.005f
			&& m_Move.z <= 0.005f && m_Move.z >= -0.005f)
			{
				if(m_motionType == MOTIONTYPE_RUN
				|| m_motionType == MOTIONTYPE_TURBO
				|| (m_motionType == MOTIONTYPE_LANDING && IsFinishMotion() == true))
				{// 走りモーション/着地モーション終了
					// ニュートラルモーション再生
					SetMotion(MOTIONTYPE_NEUTRAL);
				}

				//向きの設定（常に自機の方に向くように）
				//m_rotDestModel.y = atan2f((m_Pos.x-enemypos.x),(m_Pos.z-enemypos.z));
			}
			else
			{
				if(pInputKeyboard->GetKeyPress(DIK_T))
				{
					//飛行モーション再生
					SetMotion(MOTIONTYPE_TURBO);
				}else
				if(m_motionType == MOTIONTYPE_NEUTRAL
				|| m_motionType == MOTIONTYPE_TURBO
				|| m_motionType == MOTIONTYPE_LANDING)
				{
					// 走りモーション再生
					SetMotion(MOTIONTYPE_RUN);
				}
			}
		}

		if (pInputKeyboard->GetKeyPress(DIK_F6))
		{
			SetMotion(MOTIONTYPE_DOWN);
		}

		if((m_motionType == MOTIONTYPE_PUNCH_W && IsFinishMotion() == true)
		|| (m_motionType == MOTIONTYPE_PUNCH_S && IsFinishMotion() == true))
		{// パンチモーション終了
			// ニュートラルモーション再生
			SetMotion(MOTIONTYPE_NEUTRAL);
		}

		if((m_motionType == MOTIONTYPE_KICK_W && IsFinishMotion() == true)
		|| (m_motionType == MOTIONTYPE_KICK_S && IsFinishMotion() == true))
		{// キックモーション終了
			// ニュートラルモーション再生
			SetMotion(MOTIONTYPE_NEUTRAL);
		}

		if((m_motionType == MOTIONTYPE_SHOT && IsFinishMotion() == true)
		||(m_motionType == MOTIONTYPE_DAMAGE && IsFinishMotion() == true))
		{// ショットモーション終了
			// ニュートラルモーション再生
			SetMotion(MOTIONTYPE_NEUTRAL);
		}

		if((m_motionType == MOTIONTYPE_OVER_LOAD && IsFinishMotion() == true)
		||(m_motionType == MOTIONTYPE_OVER_LOAD2 && IsFinishMotion() == true))
		{// スキルモーション終了
			// ニュートラルモーション再生
			SetMotion(MOTIONTYPE_NEUTRAL);
		}

		if(m_motionType == MOTIONTYPE_DOWN && IsFinishMotion() == true)
		{// ダウンモーション終了
			// ニュートラルモーション再生
			SetMotion(MOTIONTYPE_NEUTRAL);
		}

		if((m_motionType == MOTIONTYPE_ATTACK && IsFinishMotion() == true)
		||(m_motionType == MOTIONTYPE_ATTACKDAMEGE && IsFinishMotion() == true))
		{// アタックモーション終了
			// ニュートラルモーション再生
			m_bJump=true;
			SetMotion(MOTIONTYPE_JUMP);
		}
		
		// アニメーション更新
		UpdateMotion();
	}

}
//=============================================================================
// 描画
//=============================================================================
void CPlayerM::Draw(void)
{
	D3DXMATRIX mtxScale, mtxRot, mtxTranslate;

	CCamera* pCamera = CManager::GetCamera();

	SetRotCamera(pCamera->GetRotCamera());

	SetMtxView(pCamera->GetMtxView());

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Rot.y, m_Rot.x, m_Rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, m_Pos.x, m_Pos.y, m_Pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTranslate);

	// ワールドマトリックスの設定
	m_pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);


	CDebugProc::Print("%f,%f,%f\n", m_Pos.x, m_Pos.y, m_Pos.z);
	// モデルパーツの描画
	for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
	{
		if (m_apModel[nCntModel])
		{
			//m_apModel[nCntModel]->Draw(m_pD3DTex[m_nTextureNum], &shaderSet, pCamera);
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

	case MOTIONTYPE_RUN:
		m_pKeyInfo = &g_aKeyRun[0];
		m_nNumKey = sizeof g_aKeyRun / sizeof(KEY_INFO);
		m_bLoopMotion = true;
		break;

	case MOTIONTYPE_JUMP:
		m_pKeyInfo = &g_aKeyJump[0];
		m_nNumKey = sizeof g_aKeyJump / sizeof(KEY_INFO);
		m_bLoopMotion = false;
		break;

	case MOTIONTYPE_LANDING:
		m_pKeyInfo = &g_aKeyLanding[0];
		m_nNumKey = sizeof g_aKeyLanding / sizeof(KEY_INFO);
		m_bLoopMotion = false;
		break;

	case MOTIONTYPE_PUNCH_W:
		m_pKeyInfo = &g_aKeyPunchW[0];
		m_nNumKey = sizeof g_aKeyPunchW / sizeof(KEY_INFO);
		m_bLoopMotion = false;
		break;

	case MOTIONTYPE_PUNCH_S:
		m_pKeyInfo = &g_aKeyPunchS[0];
		m_nNumKey = sizeof g_aKeyPunchS / sizeof(KEY_INFO);
		m_bLoopMotion = false;
		break;

	case MOTIONTYPE_KICK_W:
		m_pKeyInfo = &g_aKeyKickW[0];
		m_nNumKey = sizeof g_aKeyKickW / sizeof(KEY_INFO);
		m_bLoopMotion = false;
		break;

	case MOTIONTYPE_KICK_S:
		m_pKeyInfo = &g_aKeyKickS[0];
		m_nNumKey = sizeof g_aKeyKickS / sizeof(KEY_INFO);
		m_bLoopMotion = false;
		break;

	case MOTIONTYPE_SHOT:
		m_pKeyInfo = &g_aKeyShot[0];
		m_nNumKey = sizeof g_aKeyShot / sizeof(KEY_INFO);
		m_bLoopMotion = false;
		break;

	case MOTIONTYPE_OVER_LOAD:
		m_pKeyInfo = &g_aKeyOverLoad[0];
		m_nNumKey = sizeof g_aKeyOverLoad / sizeof(KEY_INFO);
		m_bLoopMotion = false;
		break;

	case MOTIONTYPE_OVER_LOAD2:
		m_pKeyInfo = &g_aKeyOverLoad2[0];
		m_nNumKey = sizeof g_aKeyOverLoad2 / sizeof(KEY_INFO);
		m_bLoopMotion = false;
		break;

	case MOTIONTYPE_TURBO:
		m_pKeyInfo = &g_aKeyTurbo[0];
		m_nNumKey = sizeof g_aKeyTurbo / sizeof(KEY_INFO);
		m_bLoopMotion = false;
		break;

	case MOTIONTYPE_DAMAGE:
		m_pKeyInfo = &g_aKeyDamage[0];
		m_nNumKey = sizeof g_aKeyDamage / sizeof(KEY_INFO);
		m_bLoopMotion = false;
		break;

	case MOTIONTYPE_DOWN:
		m_pKeyInfo = &g_aKeyDown[0];
		m_nNumKey = sizeof g_aKeyDown / sizeof(KEY_INFO);
		m_bLoopMotion = false;
		break;

	case MOTIONTYPE_ATTACK:
		m_pKeyInfo = &g_aKeyAttack[0];
		m_nNumKey = sizeof g_aKeyAttack / sizeof(KEY_INFO);
		m_bLoopMotion = false;
		break;

	case MOTIONTYPE_ATTACKDAMEGE:
		m_pKeyInfo = &g_aKeyAttackDamage[0];
		m_nNumKey = sizeof g_aKeyAttackDamage / sizeof(KEY_INFO);
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
				if((nCntModel==0)&&((m_motionType==MOTIONTYPE_ATTACK)||(m_motionType==MOTIONTYPE_ATTACKDAMEGE)))
				{
					m_Pos.x+=fPosX;
					m_Pos.y=fPosY;
					m_Pos.z+=fPosZ;
				}
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
void CPlayerM ::SetTexture(LPSTR pTexName,int num)
{
	if(pTexName!=NULL)
	{
		D3DXCreateTextureFromFile(m_pDevice,pTexName,&m_pD3DTex[num]);
	}else
	{
		m_pD3DTex[num]=NULL;
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
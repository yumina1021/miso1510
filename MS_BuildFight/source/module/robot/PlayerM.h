//=============================================================================
//
// MS_BuildFight [CPlayerM.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CPLAYERM_H_
#define _CPLAYERM_H_
//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "Model.h"
#include "PlayerBace.h"

#include "../../form/form.h"
#include "../../common.h"
//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************

//*****************************************************************************
// �}�N����`
//*****************************************************************************
class CSound;
class CInputKeyboard;
class CformX;
class CEnemyM;
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CPlayerM  : public Cform
{
	public:
		CPlayerM(OBJTYPE objtype = OBJTYPE_PLAYERM,int nPriority = 5);//�R���X�g���N�^
		~CPlayerM(void);//�f�X�g���N�^

		static CPlayerM *Create(LPDIRECT3DDEVICE9 pDevice,int nTypeModel,D3DXVECTOR3 pos,D3DXVECTOR3 rot);

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice,int nTypeModel,D3DXVECTOR3 pos, D3DXVECTOR3 rot,bool CPU);//������
		void Uninit(void);//�I��
		void Update(void);//�X�V
		void Draw(void);//�`��
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

		void SetVsFlag(bool set){ m_bVsFlag = set;};
	protected:

		D3DXVECTOR3 GetPosSword(void){ return m_apModel[4]->GetPos(); };
		D3DXVECTOR3 GetRotSword(void){ return m_apModel[4]->GetRot(); };

		LPDIRECT3DDEVICE9	m_pDevice;			// pDevice�I�u�W�F�N�g(�`��ɕK�v)

		D3DXVECTOR3		m_Pos;					//�ʒu
		D3DXVECTOR3		m_PosOld;				//�O��ʒu

		D3DXVECTOR3		m_Rot;					//����
		D3DXVECTOR3		m_rotDestModel;			//�ړI�̌���
		D3DXVECTOR3		m_Move;					// ���݂̈ړ���

		D3DXVECTOR3		m_RotCamera;			//�J�����̌���
		bool			m_bJump;				// �W�����v�����ǂ���

		MOTIONTYPE		m_motionType;			// ���[�V�����^�C�v
		int				m_nEffectFinishCount;	//�G�t�F�N�g�I���J�E���g

		bool			m_bCPUFlag;				//�����ړ��t���O

		int				m_moveCnt;				//�ړ��J�E���g

		bool			m_bVsFlag;
		SHADER_SET		shaderSet;

	private:
		void UpdateMotion(void);
		void ShaderSet(void);

		float lerp(float a,float b,float per){return (a*per)+(b*(1-per));};

		D3DXVECTOR3 lerpVec(D3DXVECTOR3 a,D3DXVECTOR3 b,float per);

		CModel				*m_apModel[MODELPARTS_MAX];	// ���f���ւ̃|�C���^
		LPDIRECT3DTEXTURE9	m_pD3DTex[TEXTURE_MAX];		//�e�N�X�`���\���p
		int					m_nTextureNum;				//�e�N�X�`���[�̔ԍ�

		D3DXMATRIX		m_mtxWorld;				// ���[���h�}�g���b�N�X

		float			m_fHeightField;			// �n�ʂ̍���

		int				m_nNumModel;			// ���f����

		int				m_nNumKey;				// �L�[�̐�
		KEY_INFO		*m_pKeyInfo;			// �L�[�ւ̃|�C���^

		int				m_nKey;					// �L�[No.
		int				m_nCountMotion;			// ���[�V�����J�E���^

		bool			m_bLoopMotion;			// ���[�v���[�V�������ǂ���

		bool			m_bMotion;				// ���[�V�������Ă��邩�ǂ���
		bool			m_bFinishMotion;		// ���[�V�������I�����Ă��邩�ǂ���

		bool			m_bPause;				// �|�[�YON/OFF
		bool			m_bDispDebug;			// �f�o�b�O�\��ON/OFF
		int				m_nType;				//�^�C�v�ۑ��p

		float			m_fPosHightPlus;

		D3DXVECTOR3		m_Min;
		D3DXVECTOR3		m_Max;

};

#endif

/////////////EOF////////////
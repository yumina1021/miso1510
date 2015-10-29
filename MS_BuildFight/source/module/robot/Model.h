//=============================================================================
//
// MS_BuildFight [Model.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CMODEL_H_
#define _CMODEL_H_
//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "../../common.h"
//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************
class CCamera;
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_MAX		(2)
#define	PLAYER_WIDTH	(10.0f)		// �v���C���[�̕�
#define	PLAYER_HEIGHT	(10.0f)		// �v���C���[�̍���
#define	PLAYER_RADIUS	(10.0f)		// �v���C���[�̔��a
#define PLAYER_SIZE		(20)
#define TEXTURE_MAX		(4)
// ���f���p�[�c
typedef enum
{
	MODELPARTS_BODY = 0,	// [0]��
	MODELPARTS_HEAD,		// [1]��
	MODELPARTS_RIGHTARM,	// [2]�E�r
	MODELPARTS_RIGHTHAND,	// [3]�E��
	MODELPARTS_RIGHTFINGER,	// [4]�E�w
	MODELPARTS_LETTARM,		// [5]���r
	MODELPARTS_LETTHAND,	// [6]����
	MODELPARTS_LETTFINGER,	// [7]�E�w
	MODELPARTS_RIGHTLEG,	// [8]�E��
	MODELPARTS_RIGHTFOOT,	// [9]�E��
	MODELPARTS_LEFTLEG,		// [10]����
	MODELPARTS_LEFTFOOT,	// [11]����
	MODELPARTS_MAX
} MODELPARTS;

// ���[�V�����̎��
typedef enum
{
	MOTIONTYPE_NEUTRAL = 0,	// [0]�j���[�g����
	MOTIONTYPE_RUN,			// [1]����
	MOTIONTYPE_JUMP,		// [2]�W�����v
	MOTIONTYPE_LANDING,		// [3]���n
	MOTIONTYPE_PUNCH_W,		// [4]�p���`(��)
	MOTIONTYPE_PUNCH_S,		// [5]�p���`(��)
	MOTIONTYPE_KICK_W,		// [6]�L�b�N(��)
	MOTIONTYPE_KICK_S,		// [7]�L�b�N(��)
	MOTIONTYPE_SHOT,		// [8]�V���b�g
	MOTIONTYPE_OVER_LOAD,	// [9]�X�L������
	MOTIONTYPE_OVER_LOAD2,	// [10]�X�L������
	MOTIONTYPE_TURBO,		// [11]�^�[�{
	MOTIONTYPE_DAMAGE,		// [12]�_���[�W
	MOTIONTYPE_DOWN,		// [13]�_���[�W
	MOTIONTYPE_ATTACK,		// [12]�A�^�b�N
	MOTIONTYPE_ATTACKDAMEGE,// [12]����_���[�W
	MOTIONTYPE_MAX
} MOTIONTYPE;

//*********************************************************
// �L�[�v�f
//*********************************************************
typedef struct
{
	float fPosX;	// X���ʒu
	float fPosY;	// Y���ʒu
	float fPosZ;	// Z���ʒu
	float fRotX;	// X����]
	float fRotY;	// Y����]
	float fRotZ;	// Z����]
} KEY;
//*********************************************************
// �L�[���
//*********************************************************
typedef struct
{
	int nFrame;					// �Đ��t���[��
	KEY aKey[MODELPARTS_MAX];	// �e���f���̃L�[�v�f
} KEY_INFO;
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CModel
{
	public:
		CModel(void);//�R���X�g���N�^
		~CModel(void);//�f�X�g���N�^

		static CModel *Create(LPDIRECT3DDEVICE9 pDevice,int nType,int nModelNum,D3DXVECTOR3 pos,D3DXVECTOR3 rot);

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice,int nType,int nModelNum);//������
		void Uninit(void);//�I��
		void Update(void);//�X�V
		void Draw(LPDIRECT3DTEXTURE9 pD3DTex, SHADER_SET* shader,CCamera* camera);//�`��

		void SetPos(D3DXVECTOR3 pos){m_Pos=pos;};
		void SetPos(float fx,float fy,float fz){m_Pos.x=fx;m_Pos.y=fy;m_Pos.z=fz;};
		D3DXVECTOR3 GetPos(void){return m_Pos;};

		void SetRot(D3DXVECTOR3 rot){m_Rot=rot;};
		void SetRot(float fx,float fy,float fz){m_Rot.x=fx;m_Rot.y=fy;m_Rot.z=fz;};
		D3DXVECTOR3 GetRot(void){return m_Rot;};

		HRESULT SetModel(const char *pFilename);

		void EnableDisp(bool bDisp){ m_bDisp = bDisp; };
		D3DXMATRIX GetMtxWorld(void){ return m_mtxWorld; };

		D3DXVECTOR3 *GetVtxMin(void){ return &m_vtxMin; };
		D3DXVECTOR3 *GetVtxMax(void){ return &m_vtxMax; };

		LPD3DXBUFFER GetMatBuff(void){ return m_pD3DXBuffMatModel; };

		D3DXVECTOR3 GetRotCamera(void){ return m_RotCamera; };

		void SetParent(CModel *pModel){ m_pParent = pModel; };
		void SetChild(CModel *pModel){ m_pChild = pModel; };

		void SetMtxView (D3DXMATRIX changeMtx){};
		void SetRotCamera (D3DXVECTOR3 rotCamera){};

	private:
		LPDIRECT3DDEVICE9	m_pDevice;				//pDevice�I�u�W�F�N�g(�`��ɕK�v)	

		D3DXMATRIX			m_MtxView;				//�r���[�}�g���N�X

		LPD3DXMESH			m_pD3DXMeshModel;		//���b�V�����ւ̃|�C���^
		LPD3DXBUFFER		m_pD3DXBuffMatModel;	//�}�e���A�����ւ̃|�C���^
		DWORD				m_nNumMatModel;			//�}�e���A�����̐�

		D3DXMATRIX			m_mtxWorld;				//���[���h�}�g���b�N�X

		D3DXVECTOR3			m_vtxMin;				//���_�̍ŏ��l
		D3DXVECTOR3			m_vtxMax;				//���_�̍ő�l

		D3DXVECTOR3			m_Pos;					//�ʒu
		D3DXVECTOR3			m_Rot;					//����
		D3DXVECTOR3			m_Scl;					//�傫��

		D3DXVECTOR3			m_RotCamera;			//�J�����̌���

		D3DXVECTOR3			m_rotDestModel;			//�ړI�̌���

		bool				m_bTransParent;			//������ON/OFF
		bool				m_bDisp;				//�\��ON/OFF

		CModel				*m_pParent;				//�e���f���ւ̃|�C���^	
		CModel				*m_pChild;				//�q���f���ւ̃|�C���^

		static const char	*m_apModelName[];
};

#endif

/////////////EOF////////////
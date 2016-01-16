//=============================================================================
// FileName : Live2DModel.h
// Author�FSHUN SAKAI
// ���e�F�|���S���֘A�̏���
//=============================================================================
#ifndef _LIVE_2D_MODEL_H_
#define _LIVE_2D_MODEL_H_
//*****************************************************************************
// Include
//*****************************************************************************
#include "include\Live2D.h"
#include "include\Live2DModelD3D.h"
#include "include\util/UtSystem.h"
#include "L2DEyeBlink.h"
#include "L2DPose.h"
#include "L2DPhysics.h"
#include "L2DExpressionMotion.h"
#include "L2DMotionManager.h"
#include "include\motion\Live2DMotion.h"
#include "../common.h"

//*****************************************************************************
// Macro
//*****************************************************************************
static const int MAX_LOAD_EX(20);
static const int MAX_LOAD_MOTION(20);

//*****************************************************************************
// Enum
//*****************************************************************************

//*****************************************************************************
// NameSpace
//*****************************************************************************
using namespace live2d;
using namespace live2d::framework;

//*****************************************************************************
// class
//*****************************************************************************
class Live2DModel
{
public:
	enum MODEL_TYPE
	{
		ROSA = 0,
		LILA,
		LICHT,
		NAVI,
	};
	//=============================================================================
	// FunctionName: Constructor
	// Param: void
	// ReturnValue: void
	// Content: �S�Ẵ����o�ϐ��͂����ŏ����������Ă�������
	//=============================================================================
	Live2DModel();
	//=============================================================================
	// FunctionName: Destructor
	// Param: void
	// ReturnValue: void
	// Content: �e�퓮�I�Ɋm�ۂ����o�b�t�@�Ȃǂ̊J���������s��
	//=============================================================================
	~Live2DModel();

	//=============================================================================
	// FuncName: Init
	// ParamValue: DirectX�f�o�C�X
	// Content: ������
	//=============================================================================
	bool Init(MODEL_TYPE paramType, LPDIRECT3DDEVICE9 paramDevice);

	//=============================================================================
	// FunctionName: Update
	// Param: �Ȃ�
	// ReturnValue: void
	// Content: �X�V
	//=============================================================================
	void Update();

	//=============================================================================
	// FunctionName: Draw
	// Param: DirectX�f�o�C�X
	// ReturnValue: void
	// Content: �`��
	//=============================================================================
	void Draw(LPDIRECT3DDEVICE9 paramDevice);

	//=============================================================================
	// FunctionName: TalkStart
	// Param: void
	// ReturnValue: void
	// Content: ���p�N�̍X�V
	//=============================================================================
	void TalkStart(){ talkStartFlg = true; };

	//=============================================================================
	// FunctionName: TalkStart
	// Param: void
	// ReturnValue: void
	// Content: ���p�N�̍X�V
	//=============================================================================
	void TalkEnd();


	//=============================================================================
	// Setter
	//=============================================================================
	void SetPos(D3DXVECTOR3 paramPos){ pos = paramPos; };
	void SetScl(D3DXVECTOR3 paramScl){ scl = paramScl; };

	//=============================================================================
	// Getter
	//=============================================================================
	D3DXVECTOR3 GetPos(){ return pos; };
	D3DXVECTOR3 GetScl(){ return scl; };

private:
	//=============================================================================
	// FunctionName: SetupMatrix
	// Param: DirectX�f�o�C�X
	// ReturnValue: void
	// Content: �`��ɕK�v�ȍs��̏���
	//=============================================================================
	void SetupMatrix(LPDIRECT3DDEVICE9 paramDevice);// �s��̏���

	//=============================================================================
	// FunctionName: DrawMod
	// Param: DirectX�f�o�C�X
	// ReturnValue: void
	// Content: Live2D���f���̕`��
	//=============================================================================
	void DrawMod(LPDIRECT3DDEVICE9 paramDevice);

	//=============================================================================
	// FunctionName: LoadFile
	// Param: �ǂݍ��ރt�@�C���̃p�X
	// Param: �擾�����t�@�C���̃T�C�Y�i�Q�ƂŌĂяo�����֐��ɓn���j
	// ReturnValue: �ǂݍ��񂾃t�@�C���̐擪�A�h���X
	// Content: Live2D�֌W�̃t�@�C���̓ǂݍ���
	//=============================================================================
	unsigned char* LoadFile(const char* paramFilePath, int &refFileSize);

	//=============================================================================
	// FunctionName: CreatePose
	// Param: �ǂݍ��ރt�@�C���̃p�X
	// ReturnValue: ��������
	// Content: Live2D�̃|�[�Y�̐���
	//=============================================================================
	L2DPose* CreatePose(const char* paramFilePath);

	//=============================================================================
	// FunctionName: CreatePose
	// Param: �ǂݍ��ރt�@�C���̃p�X
	// ReturnValue: ��������
	// Content: Live2D�̃|�[�Y�̐���
	//=============================================================================
	L2DPhysics* CreatePysics(const char* paramFilePath);

	//=============================================================================
	// FunctionName: CreatePose
	// Param: �ǂݍ��ރt�@�C���̃p�X
	// ReturnValue: ���[�V�����̃|�C���^
	// Content: Live2D�̃��[�V�����̐���
	//=============================================================================
	AMotion* CreateMotion(const char* paramFilePath, const int paramCnt);

	//=============================================================================
	// FunctionName: CreateExMotion
	// Param: �ǂݍ��ރt�@�C���̃p�X
	// ReturnValue: �|�C���^
	// Content: Live2D�̕\��[�V�����̐���
	//=============================================================================
	L2DExpressionMotion* CreateExMotion(const char* paramFilePath, const int paramCnt);

	//=============================================================================
	// FunctionName: LoadTexture
	// Param: �ǂݍ��ރe�N�X�`���̃p�X
	// Param: DirectX�f�o�C�X
	// Param: �e�N�X�`���̃C���f�b�N�X
	// ReturnValue: �ǂݍ��݌���
	// Content: �e�N�X�`���̓ǂݍ���
	//=============================================================================
	bool LoadTexture(const LPCWSTR paramFilePath, LPDIRECT3DDEVICE9 paramDevice, int paramTexNum);

	//=============================================================================
	// FunctionName: LoadCharcterTexture
	// Param: ���f���p�̃e�N�X�`���̃C���f�b�N�X
	// Param: DirectX�f�o�C�X
	// ReturnValue: �ǂݍ��݌���
	// Content: �e�N�X�`���̓ǂݍ���
	//=============================================================================
	bool LoadCharcterTexture(MODEL_TYPE paramtype, LPDIRECT3DDEVICE9 paramDevice);

	//=============================================================================
	// FunctionName: CreateCharcterExMotion
	// Param: �\��[�V�����p�̃C���f�b�N�X
	// ReturnValue: �ǂݍ��݌���
	// Content: �L�����ʂ̕\��[�V�����̐���
	//=============================================================================
	bool CreateCharcterExMotion(MODEL_TYPE paramtype);

	//=============================================================================
	// FunctionName: CreateCharctexMotion
	// Param: ���[�V�����p�̃C���f�b�N�X
	// ReturnValue: �ǂݍ��݌���
	// Content: �L�����ʂ̃��[�V�����̐���
	//=============================================================================
	bool CreateCharcterMotion(MODEL_TYPE paramtype);

	//=============================================================================
	// FunctionName: UpdateTalk
	// Param: void
	// ReturnValue: void
	// Content: ���p�N�̍X�V
	//=============================================================================
	void UpdateTalk();

	//=============================================================================
	// FunctionName: EsasingNone
	// Param: �ŏ��l
	// Param: �ő�l
	// Param: �W���p�̎���
	// ReturnValue: ��Ԍ��ʂ̐��l
	// Content: �C�[�W���O
	//=============================================================================
	float EsasingNone(float paramMin, float paramMax, float paramTime);

	LPDIRECT3DTEXTURE9 tex[3];

	l2d_int64 startTimeMSec;
	Live2DModelD3D* live2DModelPtr;
	L2DEyeBlink* eyeBlinkPtr;
	L2DPose* posePtr;
	L2DPhysics*	physicsPtr;
	L2DExpressionMotion* exMotionPtr[MAX_LOAD_EX];
	AMotion* motionPtr[MAX_LOAD_MOTION];
	L2DMotionManager motionMgr;
	MODEL_TYPE type;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 scl;
	int createMotionCnt;
	int createExMotionCnt;
	bool talkStartFlg;
	float mouthCoff;

	SHADER_SET				shader;


};

#endif// _LIVE2D_MODEL_H_
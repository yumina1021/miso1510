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

//*****************************************************************************
// Macro
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
	bool Init(LPDIRECT3DDEVICE9 paramDevice);

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
	AMotion* CreateMotion(const char* paramFilePath);

	//=============================================================================
	// FunctionName: CreateExMotion
	// Param: �ǂݍ��ރt�@�C���̃p�X
	// ReturnValue: �|�C���^
	// Content: Live2D�̕\��[�V�����̐���
	//=============================================================================
	L2DExpressionMotion* CreateExMotion(const char* paramFilePath);

	//=============================================================================
	// FunctionName: LoadTexture
	// Param: �ǂݍ��ރe�N�X�`���̃p�X
	// ReturnValue: �ǂݍ��݌���
	// Content: �e�N�X�`���̓ǂݍ���
	//=============================================================================
	bool LoadTexture(const LPCWSTR paramFilePath, LPDIRECT3DDEVICE9 paramDevice, int paramTexNum);

	l2d_int64 startTimeMSec;
	Live2DModelD3D* live2DModel;
	L2DEyeBlink* eyeBlink;
	L2DPose* pose;
	L2DPhysics*	physics;
	L2DExpressionMotion* exMotion1;
	L2DExpressionMotion* exMotion2;
	L2DMotionManager* motionMgr;
	AMotion* motion1;
	AMotion* motion2;
};

#endif// _LIVE2D_MODEL_H_
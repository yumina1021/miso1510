//============================================================================
// FileName: gameEntity.cpp
// Author: SHUN SAKAI
// Content: �Q�[�����ɑ��݂���I�u�W�F�N�g
//============================================================================
//*****************************************************************************
// Include
//*****************************************************************************
#include "Live2DModel.h"
#include "../administer/finalize.hpp"
#include "../administer/entityFactory.hpp"

#include <stdio.h>

//*****************************************************************************
// Macro
//*****************************************************************************
const float PI(3.14f);

// ���[�V�����̗D��x�萔
static const int PRIORITY_NONE = 0;
static const int PRIORITY_IDLE = 1;
static const int PRIORITY_NORMAL = 2;
static const int PRIORITY_FORCE = 3;



//*****************************************************************************
// GlobalArea
//*****************************************************************************
const LPCWSTR TEXTURES[] = {
	L"data\\res\\haru\\haru_01.1024\\texture_00.png",
	L"data\\res\\haru\\haru_01.1024\\texture_01.png",
	L"data\\res\\haru\\haru_01.1024\\texture_02.png",
	NULL,
};

//=============================================================================
// Constructor
//=============================================================================
Live2DModel::Live2DModel(){

	// �J�n���Ԃ̎擾
	startTimeMSec = live2d::UtSystem::getUserTimeMSec();

}// Live2DModel
//=============================================================================
// Destructor
//=============================================================================
Live2DModel::~Live2DModel(){

	
	SafeDelete(live2DModel);
	SafeDelete(eyeBlink);
	SafeDelete(pose);
	SafeDelete(physics);
	SafeDelete(exMotion1);
	SafeDelete(exMotion2);
	SafeDelete(motionMgr);
	SafeDelete(motion1);
	SafeDelete(motion2);

}// ~Live2DModel
//=============================================================================
// Init
//=============================================================================
bool Live2DModel::Init(LPDIRECT3DDEVICE9 paramDevice)
{

	// ���f���̃��[�h
	live2DModel = Live2DModelD3D::loadModel("data\\res\\haru\\haru_01.moc");

	// �e�N�X�`���̃��[�h
	for (int i = 0; i < 10; i++){
		if (!TEXTURES[i]) break;

		LoadTexture(TEXTURES[i], paramDevice, i);

	}// for

	// ���[�V�����Ǘ�
	motionMgr = new L2DMotionManager();

	// �ڃp�`
	eyeBlink = new L2DEyeBlink();

	// �|�[�Y
	pose = CreatePose("data\\res\\haru\\haru.pose.json");

	// �������Z�i���j
	physics = CreatePysics("data\\res\\haru\\haru.physics.json");


	// �ҋ@���[�V����
	motion1 = CreateMotion("data\\res\\haru\\motions\\idle_00.mtn");

	// �^�b�`���[�V����
	motion2 = CreateMotion("data\\res\\haru\\motions\\tapBody_00.mtn");

	// �\��
	exMotion1 = CreateExMotion("data\\res\\haru\\expressions\\f05.exp.json");

	// �\��
	exMotion2 = CreateExMotion("data\\res\\haru\\expressions\\f01.exp.json");

	// ����
	return S_OK;

}// Init
//=============================================================================
// FunctionName: LoadTexture
// Param: �ǂݍ��ރe�N�X�`���̃p�X
// ReturnValue: �ǂݍ��݌���
// Content: �e�N�X�`���̓ǂݍ���
//=============================================================================
bool Live2DModel::LoadTexture(const LPCWSTR paramFilePath, LPDIRECT3DDEVICE9 paramDevice, int paramTexNum){

	// �ϐ��錾
	LPDIRECT3DTEXTURE9 tex;
	bool tmpFlg = false;

	// �e�N�X�`���摜��DirextX�ł̕\���p�ɕϊ�
	if (SUCCEEDED(D3DXCreateTextureFromFileExW(paramDevice
		, paramFilePath
		, 0	//width 
		, 0	//height
		, 0	//mipmap //( 0�Ȃ犮�S�ȃ~�b�v�}�b�v�`�F�[���j
		, 0	//Usage
		, D3DFMT_A8R8G8B8
		, D3DPOOL_MANAGED
		, D3DX_FILTER_LINEAR
		, D3DX_FILTER_BOX
		, 0
		, NULL
		, NULL
		, &tex))){

		// �ϊ�������������Z�b�g
		live2DModel->setTexture(paramTexNum, tex);
		tmpFlg = true;

	}// if

	// ���ʂ�Ԃ�
	return tmpFlg;

}// LoadTexture
//=============================================================================
// CreatePose
//=============================================================================
L2DPose* Live2DModel::CreatePose(const char* paramFilePath){

	// �ϐ��錾
	unsigned char* buf = nullptr;
	int size = 0;
	L2DPose* tmpPosePtr = nullptr;

	// �t�@�C���̃��[�h
	buf = LoadFile(paramFilePath, size);

	// �|�[�Y�̓ǂݍ���
	tmpPosePtr = L2DPose::load(buf, (int)size);

	// �擾���Ɋm�ۂ����o�b�t�@�̊J��
	SafeDeleteArray(buf);

	// ���������|�[�Y��Ԃ�
	return tmpPosePtr;

}// CreatePose
//=============================================================================
// CreatePysics
//=============================================================================
L2DPhysics* Live2DModel::CreatePysics(const char* paramFilePath){

	// �ϐ��錾
	unsigned char* buf = nullptr;
	int size = 0;
	L2DPhysics*	tmpPhysicsPtr = nullptr;

	// �t�@�C���̃��[�h
	buf = LoadFile(paramFilePath, size);

	// �|�[�Y�̓ǂݍ���
	tmpPhysicsPtr = L2DPhysics::load(buf, (int)size);

	// �擾���Ɋm�ۂ����o�b�t�@�̊J��
	SafeDeleteArray(buf);

	// ���������������Z��Ԃ�
	return tmpPhysicsPtr;

}// CreatePysics
//=============================================================================
// CreateMotion
//=============================================================================
AMotion* Live2DModel::CreateMotion(const char* paramFilePath){

	// �ϐ��錾
	unsigned char* buf = nullptr;
	int size = 0;
	AMotion* tmpMotionPtr = nullptr;

	// �t�@�C���̃��[�h
	buf = LoadFile(paramFilePath, size);

	// �|�[�Y�̓ǂݍ���
	tmpMotionPtr = Live2DMotion::loadMotion(buf, (int)size);

	// �擾���Ɋm�ۂ����o�b�t�@�̊J��
	SafeDeleteArray(buf);

	// �����������[�V������Ԃ�
	return tmpMotionPtr;

}// CreateMotion
//=============================================================================
// CreateMotion
//=============================================================================
L2DExpressionMotion* Live2DModel::CreateExMotion(const char* paramFilePath){

	// �ϐ��錾
	unsigned char* buf = nullptr;
	int size = 0;
	L2DExpressionMotion* tmpExtionPtr = nullptr;

	// �t�@�C���̃��[�h
	buf = LoadFile(paramFilePath, size);

	// �|�[�Y�̓ǂݍ���
	tmpExtionPtr = L2DExpressionMotion::loadJson(buf, (int)size);

	// �擾���Ɋm�ۂ����o�b�t�@�̊J��
	SafeDeleteArray(buf);

	// ���������\��[�V������Ԃ�
	return tmpExtionPtr;

}// CreateMotion
//=============================================================================
// LoadFile
//=============================================================================
unsigned char* Live2DModel::LoadFile(const char* paramFilePath, int &refFileSize){

	// �ϐ��錾
	FILE *fp = nullptr;
	unsigned char* buf = nullptr;

	// �t�@�C���I�[�v��
	fopen_s(&fp, paramFilePath, "rb");

	// �T�C�Y���擾
	fseek(fp, 0, SEEK_END);
	refFileSize = ftell(fp);

	// �t�@�C���̓ǂݍ���
	buf = Factory::CreateArray<unsigned char>(refFileSize);
	fseek(fp, 0, SEEK_SET);

	// �ǂݍ��񂾑傫������v���Ȃ��ꍇ
	if ((int)fread(buf, sizeof(char), refFileSize, fp) != refFileSize){

		// ���b�Z�[�WBOX�̕\��
		MessageBox(NULL, "�t�@�C���̓ǂݍ��݂Ŏ��s�Ȃ̂�", "���s", MB_OK);

		// �m�ۂ����������̊J��
		SafeDeleteArray(buf);

	}// if

	// �t�@�C���N���[�Y
	fclose(fp);

	// �l��Ԃ�
	return buf;

}// LoadFile
//=============================================================================
// Update
//=============================================================================
void Live2DModel::Update(void)
{
	eyeBlink->setParam(live2DModel);// �ڃp�`

	if (GetAsyncKeyState('E') & 0x8000)
	{
		motionMgr->startMotionPrio(motion1, false, PRIORITY_IDLE);


	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		motionMgr->startMotionPrio(motion2, false, PRIORITY_NORMAL);


	}
	if (GetAsyncKeyState('W') & 0x8000)
	{
		motionMgr->startMotionPrio(exMotion1, false, PRIORITY_NORMAL);
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{

		motionMgr->startMotionPrio(exMotion2, false, PRIORITY_NORMAL);


	}

}
//=============================================================================
// Draw
//=============================================================================
void Live2DModel::Draw(LPDIRECT3DDEVICE9 paramDevice)
{

	// �`��̑O�ɍs��̏���
	SetupMatrix(paramDevice);

	// ���f���̕`��
	DrawMod(paramDevice);

}
//=============================================================================
// DrawMod
//=============================================================================
void Live2DModel::DrawMod(LPDIRECT3DDEVICE9 paramDevice){

	// �ċz�Ȃ�
	LDint64	 timeMSec = live2d::UtSystem::getUserTimeMSec() - startTimeMSec;
	double t = (timeMSec / 1000.0) * 2 * 3.14159;//2*Pi*t
	live2DModel->setParamFloat("PARAM_BREATH", (float)(0.5f + 0.5f * sin(t / 3.2345)), 1);// 0~1 �܂Ŏ����I�ɐݒ�B���[�V�������㏑���B

	// �������Z�Ńp�����[�^�X�V
	if (physics != NULL)physics->updateParam(live2DModel);

	// �|�[�Y�̐ݒ�
	if (pose != NULL)pose->updateParam(live2DModel);

	// ���[�V�����̍X�V
	motionMgr->updateParam(live2DModel);

	live2DModel->setDevice(paramDevice);
	live2DModel->update();
	live2DModel->draw();

	D3DXMATRIXA16 Identity;
	D3DXMatrixIdentity(&Identity);
	paramDevice->SetTransform(D3DTS_PROJECTION, &Identity);
	paramDevice->SetTransform(D3DTS_VIEW, &Identity);
	paramDevice->SetTransform(D3DTS_WORLD, &Identity);

}
//=============================================================================
// SetupMatrix
//=============================================================================
void Live2DModel::SetupMatrix(LPDIRECT3DDEVICE9 paramDevice){

	// Set up world matrix
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);

	D3DXMATRIX Ortho2D;
	D3DXMATRIX Identity;

	int w, h;
	w = 1300;
	h = 750;

	float raito = (float)(h / w);

	float modelWidth = live2DModel->getModelImpl()->getCanvasWidth();
	float modelHeight = live2DModel->getModelImpl()->getCanvasHeight();

	D3DXMatrixOrthoLH(&Ortho2D, modelHeight, -modelHeight * h / w, -1.0f, 1.0f);

	D3DXMatrixIdentity(&Identity);

	paramDevice->SetTransform(D3DTS_PROJECTION, &Ortho2D);
	paramDevice->SetTransform(D3DTS_VIEW, &Identity);
	paramDevice->SetTransform(D3DTS_WORLD, &Identity);


	// --- ���W�ϊ�
	// ���݂�Live2D���f���́A�摜�̂悤�ɉ�������(0,0,w,h)�ɔz�u�����
	// �Z���^�����O�Ə㉺�t�]���K�v
	D3DXMATRIXA16 world, scale, trans;
	D3DXMatrixIdentity(&world);
	D3DXMatrixIdentity(&scale);
	D3DXMatrixIdentity(&trans);


	D3DXMatrixTranslation(&trans, -modelWidth / 2, -modelHeight / 2, 0);
	D3DXMatrixScaling(&scale, 0.5f, 0.5f, 1.0f);
	world = trans *world * scale;

	paramDevice->SetTransform(D3DTS_WORLD, &world);

}// SetupMatrix
// EOF
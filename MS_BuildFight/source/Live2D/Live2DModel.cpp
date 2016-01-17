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
#include "../administer/Input.h"
#include "../exten_common.h"

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
const char* USE_MODEL[] = {
	"data\\res\\haru\\haru_01.moc",
	"data\\res\\haru\\haru_02.moc",
	"data\\res\\haru\\haru_01.moc",
	NULL,
};
const char* POSE[] = {
	"data\\res\\haru\\haru.pose.json",
	"data\\res\\haru\\haru.pose.json",
	"data\\res\\haru\\haru.pose.json",
	NULL,
};
const char* PHYSICS[] = {
	"data\\res\\haru\\haru.physics.json",
	"data\\res\\haru\\haru.physics.json",
	"data\\res\\haru\\haru.physics.json",
	NULL,
};
const LPCWSTR TEXTURES1[] = {
	L"data\\res\\haru\\haru_01.1024\\texture_00.png",
	L"data\\res\\haru\\haru_01.1024\\texture_01.png",
	L"data\\res\\haru\\haru_01.1024\\texture_02.png",
	NULL,
};

const LPCWSTR TEXTURES2[] = {
	L"data\\res\\haru\\haru_02.1024\\texture_00.png",
	L"data\\res\\haru\\haru_02.1024\\texture_01.png",
	L"data\\res\\haru\\haru_02.1024\\texture_02.png",
	NULL,
};
const LPCWSTR TEXTURES3[] = {
	L"data\\res\\haru\\haru_01.1024\\texture_00.png",
	L"data\\res\\haru\\haru_01.1024\\texture_01.png",
	L"data\\res\\haru\\haru_01.1024\\texture_02.png",
	NULL,
};
const char* EX_MOTION1[] = {
	"data\\res\\haru\\expressions\\f01.exp.json",
	"data\\res\\haru\\expressions\\f02.exp.json",
	"data\\res\\haru\\expressions\\f03.exp.json",
	"data\\res\\haru\\expressions\\f04.exp.json",
	"data\\res\\haru\\expressions\\f05.exp.json",
	"data\\res\\haru\\expressions\\f06.exp.json",
	"data\\res\\haru\\expressions\\f07.exp.json",
	"data\\res\\haru\\expressions\\f08.exp.json",
	NULL,
};

const char* EX_MOTION2[] = {
	"data\\res\\haru\\expressions\\f01.exp.json",
	"data\\res\\haru\\expressions\\f02.exp.json",
	"data\\res\\haru\\expressions\\f03.exp.json",
	"data\\res\\haru\\expressions\\f04.exp.json",
	"data\\res\\haru\\expressions\\f05.exp.json",
	"data\\res\\haru\\expressions\\f06.exp.json",
	"data\\res\\haru\\expressions\\f07.exp.json",
	"data\\res\\haru\\expressions\\f08.exp.json",
	NULL,
};
const char* EX_MOTION3[] = {
	"data\\res\\haru\\expressions\\f01.exp.json",
	"data\\res\\haru\\expressions\\f02.exp.json",
	"data\\res\\haru\\expressions\\f03.exp.json",
	"data\\res\\haru\\expressions\\f04.exp.json",
	"data\\res\\haru\\expressions\\f05.exp.json",
	"data\\res\\haru\\expressions\\f06.exp.json",
	"data\\res\\haru\\expressions\\f07.exp.json",
	"data\\res\\haru\\expressions\\f08.exp.json",
	NULL,
};
const char* MOTION1[] = {
	"data\\res\\haru\\motions\\idle_00.mtn",
	"data\\res\\haru\\motions\\idle_01.mtn",
	"data\\res\\haru\\motions\\idle_02.mtn",
	"data\\res\\haru\\motions\\tapBody_01.mtn",
	"data\\res\\haru\\motions\\tapBody_02.mtn",
	"data\\res\\haru\\motions\\tapBody_03.mtn",
	"data\\res\\haru\\motions\\tapBody_04.mtn",
	"data\\res\\haru\\motions\\tapBody_05.mtn",
	"data\\res\\haru\\motions\\tapBody_06.mtn",
	"data\\res\\haru\\motions\\tapBody_07.mtn",
	"data\\res\\haru\\motions\\tapBody_08.mtn",
	"data\\res\\haru\\motions\\tapBody_09.mtn",
	NULL,
};

const char* MOTION2[] = {
	"data\\res\\haru\\motions\\idle_00.mtn",
	"data\\res\\haru\\motions\\idle_01.mtn",
	"data\\res\\haru\\motions\\idle_02.mtn",
	"data\\res\\haru\\motions\\tapBody_01.mtn",
	"data\\res\\haru\\motions\\tapBody_02.mtn",
	"data\\res\\haru\\motions\\tapBody_03.mtn",
	"data\\res\\haru\\motions\\tapBody_04.mtn",
	"data\\res\\haru\\motions\\tapBody_05.mtn",
	"data\\res\\haru\\motions\\tapBody_06.mtn",
	"data\\res\\haru\\motions\\tapBody_07.mtn",
	"data\\res\\haru\\motions\\tapBody_08.mtn",
	"data\\res\\haru\\motions\\tapBody_09.mtn",
	NULL,
};
const char* MOTION3[] = {
	"data\\res\\haru\\motions\\idle_00.mtn",
	"data\\res\\haru\\motions\\idle_01.mtn",
	"data\\res\\haru\\motions\\idle_02.mtn",
	"data\\res\\haru\\motions\\tapBody_01.mtn",
	"data\\res\\haru\\motions\\tapBody_02.mtn",
	"data\\res\\haru\\motions\\tapBody_03.mtn",
	"data\\res\\haru\\motions\\tapBody_04.mtn",
	"data\\res\\haru\\motions\\tapBody_05.mtn",
	"data\\res\\haru\\motions\\tapBody_06.mtn",
	"data\\res\\haru\\motions\\tapBody_07.mtn",
	"data\\res\\haru\\motions\\tapBody_08.mtn",
	"data\\res\\haru\\motions\\tapBody_09.mtn",
	NULL,
};
//=============================================================================
// Constructor
//=============================================================================
Live2DModel::Live2DModel():
startTimeMSec(0),
live2DModelPtr(nullptr),
eyeBlinkPtr(nullptr),
posePtr(nullptr),
physicsPtr(nullptr),
pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
scl(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
createMotionCnt(0),
createExMotionCnt(0),
talkStartFlg(false),
mouthCoff(0.0f),
drawFlg(false){

	// �J�n���Ԃ̎擾
	startTimeMSec = live2d::UtSystem::getUserTimeMSec();

}// Live2DModel
//=============================================================================
// Destructor
//=============================================================================
Live2DModel::~Live2DModel(){

	
	SafeDelete(live2DModelPtr);
	SafeDelete(eyeBlinkPtr);
	SafeDelete(posePtr);
	SafeDelete(physicsPtr);


	for (int i = 0; i < createMotionCnt; i++)
	{
		SafeDelete(motionPtr[i]);

	}
	for (int i = 0; i < createExMotionCnt; i++)
	{
		SafeDelete(exMotionPtr[i]);

	}

	for (int i = 0; i < 3; i++)
	{

		//SafeRelease(tex[i]);

	}

}// ~Live2DModel
//=============================================================================
// Init
//=============================================================================
bool Live2DModel::Init(MODEL_TYPE paramType, LPDIRECT3DDEVICE9 paramDevice)
{

	// ���f���̃��[�h
	live2DModelPtr = Live2DModelD3D::loadModel(USE_MODEL[paramType]);
	
	// �L�����̃e�N�X�`���̃��[�h
	LoadCharcterTexture(paramType, paramDevice);

	// �ڃp�`
	eyeBlinkPtr = Factory::Create<L2DEyeBlink>();

	// �|�[�Y
	posePtr = CreatePose(POSE[paramType]);

	// �������Z�i���j
	physicsPtr = CreatePysics(PHYSICS[paramType]);

	// �ҋ@���[�V����
	CreateCharcterMotion(paramType);

	// �\��
	CreateCharcterExMotion(paramType);

	// ����
	return true;

}// Init
//=============================================================================
// FunctionName: LoadTexture
// Param: �ǂݍ��ރe�N�X�`���̃p�X
// ReturnValue: �ǂݍ��݌���
// Content: �e�N�X�`���̓ǂݍ���
//=============================================================================
bool Live2DModel::LoadCharcterTexture(MODEL_TYPE paramtype, LPDIRECT3DDEVICE9 paramDevice){

	switch (paramtype)
	{
	case ROSA:

		// �e�N�X�`���̃��[�h
		for (int i = 0; i < 10; i++){
			if (!TEXTURES1[i]) break;

			if (!LoadTexture(TEXTURES1[i], paramDevice, i)){ break; };

		}// for

		break;
	case LILA:
		// �e�N�X�`���̃��[�h
		for (int i = 0; i < 10; i++){
			if (!TEXTURES2[i]) break;

			if (!LoadTexture(TEXTURES2[i], paramDevice, i)){ break; };

		}// for

		break;
	case LICHT:
		// �e�N�X�`���̃��[�h
		for (int i = 0; i < 10; i++){
			if (!TEXTURES3[i]) break;

			if (!LoadTexture(TEXTURES3[i], paramDevice, i)){ break; };

		}// for

		break;
	default:
		break;
	}

	return true;

}// LoadCharcterTexture
//=============================================================================
// FunctionName: LoadTexture
//=============================================================================
bool Live2DModel::LoadTexture(const LPCWSTR paramFilePath, LPDIRECT3DDEVICE9 paramDevice, int paramTexNum){

	// �ϐ��錾
	bool tmpFlg = false;

	// �e�N�X�`���摜��DirextX�ł̕\���p�ɕϊ�
	if (FAILED(D3DXCreateTextureFromFileExW(paramDevice
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
		, &tex[paramTexNum]))){

	}else{

		// �ϊ�������������Z�b�g
		live2DModelPtr->setTexture(paramTexNum, tex[paramTexNum]);
		tmpFlg = true;

	}

	// ���ʂ�Ԃ�
	return tmpFlg;


}// LoadTexture
//=============================================================================
// CreateCharcterExMotion
//=============================================================================
bool Live2DModel::CreateCharcterExMotion(MODEL_TYPE paramtype){

	// �ϐ��錾
	int cnt = 0;
	switch (paramtype){
	case ROSA:

		// �e�N�X�`���̃��[�h
		for (cnt = 0; cnt < MAX_LOAD_EX; cnt++){
			if (!EX_MOTION1[cnt]) break;

			exMotionPtr[cnt] = CreateExMotion(EX_MOTION1[cnt], cnt);

		}// for

		break;
	case LILA:
		// �e�N�X�`���̃��[�h
		for (cnt = 0; cnt < MAX_LOAD_EX; cnt++){
			if (!EX_MOTION2[cnt]) break;

			exMotionPtr[cnt] = CreateExMotion(EX_MOTION1[cnt], cnt);

		}// for

		break;
	case LICHT:
		// �e�N�X�`���̃��[�h
		for (cnt = 0; cnt < MAX_LOAD_EX; cnt++){
			if (!EX_MOTION3[cnt]) break;

			exMotionPtr[cnt] = CreateExMotion(EX_MOTION1[cnt], cnt);

		}// for

		break;
	default:
		break;
	}

	createExMotionCnt = cnt;

	return true;

}// CreateCharcterExMotion
//=============================================================================
// CreateCharcterExMotion
//=============================================================================
bool Live2DModel::CreateCharcterMotion(MODEL_TYPE paramtype){

	// �ϐ��錾
	int cnt = 0;

	switch (paramtype){
	case ROSA:

		// �e�N�X�`���̃��[�h
		for (cnt = 0; cnt < MAX_LOAD_MOTION; cnt++){
			if (!MOTION1[cnt]) break;

			motionPtr[cnt] = CreateMotion(MOTION1[cnt], cnt);

		}// for

		break;
	case LILA:
		// �e�N�X�`���̃��[�h
		for (cnt = 0; cnt < MAX_LOAD_MOTION; cnt++){
			if (!MOTION2[cnt]) break;

			motionPtr[cnt] = CreateMotion(MOTION2[cnt], cnt);

		}// for

		break;
	case LICHT:
		// �e�N�X�`���̃��[�h
		for (cnt = 0; cnt < MAX_LOAD_MOTION; cnt++){
			if (!MOTION3[cnt]) break;

			motionPtr[cnt] = CreateMotion(MOTION3[cnt], cnt);

		}// for

		break;
	default:
		break;
	}

	// �������������L�^
	createMotionCnt = cnt;

	return true;

}// CreateCharcterExMotion
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
AMotion* Live2DModel::CreateMotion(const char* paramFilePath, const int paramCnt){

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
L2DExpressionMotion* Live2DModel::CreateExMotion(const char* paramFilePath, const int paramCnt){

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
void Live2DModel::Update(){

	// �ڃp�`
	eyeBlinkPtr->setParam(live2DModelPtr);

	// ���[�V�����̍X�V
	UpdateMotion();

	// �ċz�Ȃ�
	LDint64	 timeMSec = live2d::UtSystem::getUserTimeMSec() - startTimeMSec;
	double t = (timeMSec / 1000.0) * 2 * 3.14159;//2*Pi*t
	live2DModelPtr->setParamFloat("PARAM_BREATH", (float)(0.5f + 0.5f * sin(t / 3.2345)), 1);// 0~1 �܂Ŏ����I�ɐݒ�B���[�V�������㏑���B

	// �������Z�Ńp�����[�^�X�V
	if (physicsPtr)
		physicsPtr->updateParam(live2DModelPtr);

	// �|�[�Y�̐ݒ�
	if (posePtr)
		posePtr->updateParam(live2DModelPtr);

	// ���[�V�����̍X�V
	motionMgr.updateParam(live2DModelPtr);

	// ���p�N
	if (talkStartFlg)
		UpdateTalk();

	// ���f���̍X�V
	live2DModelPtr->update();

}// Update
//=============================================================================
// Draw
//=============================================================================
void Live2DModel::Draw(LPDIRECT3DDEVICE9 paramDevice)
{

	// �`��̑O�ɍs��̏���
	SetupMatrix(paramDevice);

	// ���f���̕`��
	DrawMod(paramDevice);

	// �����_�����O�X�e�[�g�p�����[�^�̐ݒ�
	paramDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// ���ʂ��J�����O
	paramDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Z�o�b�t�@���g�p
	paramDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// ���u�����h���s��
	paramDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	paramDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��

	// �T���v���[�X�e�[�g�p�����[�^�̐ݒ�
	paramDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(U�l)��ݒ�
	paramDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(V�l)��ݒ�
	paramDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���k���t�B���^���[�h��ݒ�
	paramDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���g��t�B���^���[�h��ݒ�

	// �e�N�X�`���X�e�[�W�X�e�[�g�p�����[�^�̐ݒ�
	paramDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// �A���t�@�u�����f�B���O����
	paramDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// �ŏ��̃A���t�@����
	paramDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// �Q�Ԗڂ̃A���t�@����
}
//=============================================================================
// DrawMod
//=============================================================================
void Live2DModel::DrawMod(LPDIRECT3DDEVICE9 paramDevice){


	live2DModelPtr->setDevice(paramDevice);
	live2DModelPtr->draw();

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
	w = SCREEN_WIDTH;
	h = SCREEN_HEIGHT;

	float raito = (float)(h / w);

	float modelWidth = live2DModelPtr->getModelImpl()->getCanvasWidth();
	float modelHeight = live2DModelPtr->getModelImpl()->getCanvasHeight();

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


	D3DXMatrixTranslation(&trans, -modelWidth / 2, -modelHeight / 2 + 600, 0.0f);
	D3DXMatrixScaling(&scale, scl.x, scl.y, 1.0f);
	world = trans *world * scale;

	paramDevice->SetTransform(D3DTS_WORLD, &world);

}// SetupMatrix
//=============================================================================
// EsasingNone
//=============================================================================
float Live2DModel::EsasingNone(float paramMin, float paramMax, float paramTime){

	float tmpRet(0.0f);

	if (paramTime < 0.5f){

		// �񎟋Ȑ�
		tmpRet = (2.0 * paramTime) * (2.0 * paramTime) * 0.5f;

	}else{

		tmpRet = -((2.0 * paramTime - 2.0f) * (2.0 * paramTime - 2.0f)) * 0.5f + 1.0f;

	}// else

	return (paramMax - paramMin) * tmpRet + paramMin;

}// EsasingNone
//=============================================================================
// UpdateTalk
//=============================================================================
void Live2DModel::UpdateTalk(){

	live2DModelPtr->setParamFloat("PARAM_MOUTH_OPEN_Y", EsasingNone(0.0f, 0.8f, mouthCoff), 0.8f);

	if (mouthCoff > 1.0f)
	{
		mouthCoff = 0.0f;

	}else{

		mouthCoff += 0.05f;

	}// else


}// UpdateTalk
//=============================================================================
// TalkStart
//=============================================================================
void Live2DModel::TalkEnd(){

	// ���p�N���Ă���ꍇ�̂ݒ�~
	if (!talkStartFlg){ return; }

	// �e��l�̏�����
	talkStartFlg = false;
	mouthCoff = 0.0f;

	// ���p�N�̍X�V
	UpdateTalk();

}// TalkEnd
//=============================================================================
// TalkStart
//=============================================================================
void Live2DModel::TalkStart(){

	// ���p�N���Ă��Ȃ��ꍇ�̂݊J�n
	if (talkStartFlg){ return; }

	// ���p�N�J�n
	talkStartFlg = true;

}// TalkStart
//=============================================================================
// SetMotion
//=============================================================================
void Live2DModel::SetMotion(int pramMotionState){

	motionMgr.startMotionPrio(motionPtr[pramMotionState], false, PRIORITY_NORMAL);

}// SetMotion
//=============================================================================
// SetExMotion
//=============================================================================
void Live2DModel::SetExMotion(int pramMotionState){

	exMotionMgr.startMotion(exMotionPtr[pramMotionState], false);

}// SetMotion
//=============================================================================
// UpdateMotion
//=============================================================================
void Live2DModel::UpdateMotion(){

	// �O��Z�[�u���ꂽ��Ԃ����[�h
	live2DModelPtr->loadParam();

	// ���[�V�������I�����Ă�����
	if (motionMgr.isFinished()){

		// ���[�V�����̍Đ����Ȃ��ꍇ�A�ҋ@���[�V�����̒����烉���_���ōĐ�����
		//startRandomMotion(MOTION_GROUP_IDLE, PRIORITY_IDLE);
		motionMgr.startMotionPrio(motionPtr[0], false, PRIORITY_IDLE);

	}else{

		motionMgr.updateParam(live2DModelPtr);// ���[�V�������X�V

	}// else

	// ��Ԃ�ۑ�
	live2DModelPtr->saveParam();

}// UpdateMotion
// EOF
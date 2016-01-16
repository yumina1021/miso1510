/**
 *
 *  You can modify and use this source freely
 *  only for the development of application related Live2D.
 *
 *  (c) Live2D Inc. All rights reserved.
 */
#pragma once


//Live2D lib
#include "include/motion/AMotion.h"
#include "include/util/Json.h"
#include "include/ALive2DModel.h"
#include "include/util/UtFile.h"
#include <string>
#include <vector>

namespace live2d
{
	namespace framework
	{
		struct L2DExpressionParam
		{
			std::string pid;
			//int index=-1;
			int type;
			float value;
			
		};
		
		class L2DExpressionMotion : public AMotion
		{
		private:
			static const char EXPRESSION_DEFAULT[];// ���\��ݒ�t�@�C���̃f�t�H���g�l�v�f�̃L�[
			static const int TYPE_ADD;// �ʏ�B�w��̒l�𑫂����킹��
			static const int TYPE_MULT;// �w��̒l���|�����킹��
			static const int TYPE_SET;// �w��̒l���㏑������
			
			std::vector<L2DExpressionParam> paramList;
			
		public:
			virtual ~L2DExpressionMotion(void){}
			
			// �ǂݍ���
			static L2DExpressionMotion* loadJson( const void *buf ,int size ) ;
			static L2DExpressionMotion* loadJson(const std::string & filepath );
			static void loadExpressionJsonV09(
											  live2d::LDMap<live2d::LDString, AMotion*>& expressions ,
											  const void *buf ,int size ) ;
			
			static L2DExpressionMotion* loadJsonV09( live2d::Value &defaultExpr , live2d::Value &expr ) ;
			
			// �X�V
			virtual void updateParamExe(
										live2d::ALive2DModel * model , l2d_int64 timeMSec ,
										float weight , MotionQueueEnt *motionQueueEnt ) ;
		};
	}
}
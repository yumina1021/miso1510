/**
 *
 *  You can modify and use this source freely
 *  only for the development of application related Live2D.
 *
 *  (c) Live2D Inc. All rights reserved.
 */
#pragma once

//Live2D lib
#include "include\ALive2DModel.h"
#include "include\motion/AMotion.h"
#include "include\motion/MotionQueueManager.h"

namespace live2d
{
	namespace framework
	{
		class L2DMotionManager : public MotionQueueManager
		{
			typedef MotionQueueManager super;
		public:
			L2DMotionManager();
			virtual ~L2DMotionManager(){}
			
		private:
			int currentPriority;//  ���ݍĐ����̃��[�V�����̗D��x
			int reservePriority;//  �Đ��\��̃��[�V�����̗D��x�B�Đ�����0�ɂȂ�B���[�V�����t�@�C����ʃX���b�h�œǂݍ��ނƂ��̋@�\�B
			
		public:
			//  �Đ����̃��[�V�����̗D��x
			int getCurrentPriority(){return currentPriority;}
			
			//  �\�񒆂̃��[�V�����̗D��x
			int getReservePriority(){return reservePriority;}
			
			//  ���[�V������\�񂷂�
			void setReservePriority( int val ){reservePriority=val;}
			
			//  ���[�V�����J�n
			int startMotionPrio( live2d::AMotion* motion, bool isDelete, int priority );
			
			bool updateParam(live2d::ALive2DModel* model);
			
			bool reserveMotion(int priority);
		};
	}
}

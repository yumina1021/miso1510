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
#include "include\util/UtSystem.h"
#include "include\util/Json.h"
#include "include\model/ModelImpl.h"
#include <vector>

namespace live2d
{
	namespace framework
	{
		/*
		 * �p�[�c�C���f�b�N�X��ێ�����N���X�B
		 * �p�[�c�ɂ̓p�[�cID�ƃ��[�V��������ݒ肷��p�[�c�p�����[�^ID������B
		 * ������Őݒ肷�邱�Ƃ��ł��邪�A�C���f�b�N�X���擾���Ă���ݒ肵���ق��������B
		 */
		struct L2DPartsParam{
		public:
			L2DPartsParam(){}
			L2DPartsParam(const L2DPartsParam &v)
			{
				partsID=v.partsID;
				
				std::vector<L2DPartsParam>::const_iterator ite;
				for (ite=v.link.begin(); ite!=v.link.end(); ite++) {
					link.push_back(*ite);
				}
			}
			L2DPartsParam& operator=(const L2DPartsParam& v)
			{
				partsID=v.partsID;
				
				std::vector<L2DPartsParam>::const_iterator ite;
				for (ite=v.link.begin(); ite!=v.link.end(); ite++) {
					link.push_back(*ite);
				}
				return (*this);
			}
			live2d::LDString partsID;
			int paramIndex;
			int partsIndex;
			std::vector<L2DPartsParam> link;// �A������p�[�c
			
			void initIndex(live2d::ALive2DModel* model)
			{
				live2d::LDString visibleParamID=live2d::LDString("VISIBLE:")+partsID;
				paramIndex=model->getParamIndex(visibleParamID.c_str());
				
				partsIndex=model->getPartsDataIndex(partsID.c_str());
				model->setParamFloat(paramIndex, 1);
			}
		};
		class L2DPose
		{
		private:
			std::vector< L2DPartsParam > partsGroups;
			std::vector<int> groupRows;
			l2d_int64 lastTime;
			live2d::ALive2DModel* lastModel;// �p�����[�^�C���f�b�N�X������������Ă邩�ǂ����̃`�F�b�N�p�B
		public:
			L2DPose();
			~L2DPose(){}
			static L2DPose* load(const void* buf,int size );
			void initParam(live2d::ALive2DModel* model);
			void copyOpacityOtherParts(live2d::ALive2DModel* model);
			void normalizePartsOpacityGroup( live2d::ALive2DModel* model, float deltaTimeSec , int offset,int rouCount);
			void updateParam(live2d::ALive2DModel* model);
		};
	}
}
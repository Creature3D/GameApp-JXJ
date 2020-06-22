/**********************************************************************
*
*	�ļ�:	   appMethod5.cpp
*
*	����:	   
*
*	����:	   ��ѩ��
*					  
*
**********************************************************************/
#include <rbody/Creature3D/CreBody.h>
#include <JXJ/appMethod5.h>
#include <JXJ/appDataParam.h>
#include <JXJ/appMethod.h>
#include <JXJ/appMsg.h>
#include <JXJ/appPackets.h>
#include <CRUI/crWidgetExtend.h>
#include <CRNetApp/appNetLogic.h>
#include <CRNetApp/appGlobalHandle.h>
#include <CRProducer/crViewer.h>
#include <CRProducer/crSceneHandler.h>
#include <CRUtil/crAcceptGIVisitor.h>
#include <CRDataBase/crDataBaseManager.h>
#include <CRNetApp/appDBUpdate2.h>
#include <CRNetApp/appDBQuery2.h>
#include <CRIOManager/crLoadManager.h>
#include <CRNetApp/appNodeCallbacks.h>
#include <CREncapsulation/crGameDices.h>
#include <JXJ/appData5.h>
#include <stdlib.h>
#include <JXJ/appDBQuery.h>
#include <CRIOManager/crLoadManager.h>

using namespace CRCore;
using namespace CRNetApp;
using namespace CREncapsulation;
using namespace JXJ;
using namespace CRDataBase;
using namespace CRNet;
using namespace CRUI;
using namespace CRIOManager;

/////////////////////////////////////////
//
//GeneralTips
//TIPS
//
/////////////////////////////////////////

GeneralTips::GeneralTips(std::string m_tipsCanvas, CRCore::crWidgetNode *m_this)	
{
	tips = crFilterRenderManager::getInstance()->findCanvas(m_tipsCanvas);
	this->m_this = m_this;
}
GeneralTips::GeneralTips(std::string m_tipsCanvas)	
{
	tips = crFilterRenderManager::getInstance()->findCanvas(m_tipsCanvas);
}
void GeneralTips::setText(std::string m_tipsTextWidget, std::string textStr)
{
	if(tips)
	{
		tipsText = dynamic_cast<crStaticTextWidgetNode *>(tips->getWidget(m_tipsTextWidget));
		if(tipsText )
		{
			tipsText->setString(textStr);
		}
	}
}
void GeneralTips::setText(std::string m_tipsTextWidget, std::string textStr, crVector4 textColor)
{
	if(tips)
	{
		tipsText = dynamic_cast<crStaticTextWidgetNode *>(tips->getWidget(m_tipsTextWidget));
		if(tipsText )
		{
			tipsText->setColor(textColor);
			tipsText->setString(textStr);
		}
	}
}
void GeneralTips::setImgage(std::string m_tipsImgWidget, std::string imgStr)
{
	if(tips && m_this)
	{
		tipsImg = dynamic_cast<crImageBoxWidgetNode *>(tips->getWidget(m_tipsImgWidget));
		if(tipsText )
		{
			tipsImg->setImageName(imgStr);
		}
	}
}
void GeneralTips::setTipUpper()
{
	if(tips && m_this)
	{
		const crBoundingBox &btnbox = m_this->getBoundBox();
		const crMatrix &mat = m_this->getParentCanvas()->getMatrix();
		float posx = btnbox.m_min[0];
		float posy = (btnbox.m_min[1]+1.5f*(btnbox.m_max[1]-btnbox.m_min[1]));
		crVector2 mouse(crVector2(posx,posy));
		tips->setMatrix(crMatrix::translate(mouse[0],mouse[1],0.0f) * mat);
		crFilterRenderManager::getInstance()->showCanvas(tips,true);
	}
}
void GeneralTips::setTipRight()
{
	if(tips && m_this)
	{
		const crBoundingBox &iconbox = m_this->getBoundBox();
		const crBoundingBox &tip = tips->getBoundBox(); 
		float posx = (tip.m_max[0]-tip.m_min[0])*0.5;
		float posy = (tip.m_max[1]-tip.m_min[1])*0.5;
		crVector3 pos(iconbox.m_max[0],iconbox.m_max[1],0.0f);
		/////////////////////////////////////////
		crVector3 pos2(iconbox.m_min[0] ,iconbox.m_min[1],0.0f);
		float posx2,posy2;
		posx2 = iconbox.m_max[0];
		posy2 = iconbox.m_max[1] - posy;

		crVector2 mouse(crVector2(posx2,posy2));
		tips->setMatrix(crMatrix::translate(mouse[0],mouse[1],0.0f));
		crFilterRenderManager::getInstance()->showCanvas(tips,true);
	}
}

void GeneralTips::setTipAuto()
{
	if(tips && m_this)
	{
		if(m_this->getParentCanvas())
		{
			const crMatrix &mat = m_this->getParentCanvas()->getMatrix();//////////////////////////////////// m_this->getParentCanvas()
			const crBoundingBox &iconbox = m_this->getBoundBox();
			const crBoundingBox &tip = tips->getBoundBox();
			float posx = (tip.m_max[0]-tip.m_min[0])*0.5;
			float posy = (tip.m_max[1]-tip.m_min[1])*0.5;
			crVector3 pos(iconbox.m_max[0],iconbox.m_max[1],0.0f);
			pos = pos * mat;
			/////////////////////////////////////////
			crVector3 pos2(iconbox.m_min[0] ,iconbox.m_min[1],0.0f);
			pos2 = pos2 * mat;
			float posx2,posy2;
			/////////////////////////////////////////
			if (pos2[0] >= 0)
			{
				posx2 = pos2[0] - posx;
			}
			else
			{
				posx2 = pos[0] + posx;
			}
			if (pos2[1] >= 0)//
			{
				posy2 = pos[1] - posy;
			}
			else
			{
				posy2 = pos2[1] + posy;
			}
			crVector2 mouse(crVector2(posx2,posy2));
			/////////////////////////////////////////
			tips->setMatrix(crMatrix::translate(mouse[0],mouse[1],0.0f)/* * mat*/);
			tips->setCanFocus(false);
			crFilterRenderManager::getInstance()->showCanvas(tips,true);
		}
	}
}


/////////////////////////////////////////
//
//crJXJUIOficialRankBestLevelTipMethod
//������õĹ�ְ�Ѿ�����߼�����껬����Ǩ��ť��ʾ "�Ѿ�����߼���"
//
/////////////////////////////////////////
crJXJUIOficialRankBestLevelTipMethod::crJXJUIOficialRankBestLevelTipMethod()
{
}
crJXJUIOficialRankBestLevelTipMethod::crJXJUIOficialRankBestLevelTipMethod(const crJXJUIOficialRankBestLevelTipMethod& handle):
	crMethod(handle),
	m_tipsCanvas(handle.m_tipsCanvas),
	m_tipsTextWidget(handle.m_tipsTextWidget)
{
}
void crJXJUIOficialRankBestLevelTipMethod::inputParam(int i, void *param)
{
	switch(i) 
	{
	case 0:
		if(param == 0)
		{//�ͷ�
			m_this = NULL;
		}
		break;
	case 1:
		m_this = (crWidgetNode*)param;
		break;
	}
}
void crJXJUIOficialRankBestLevelTipMethod::addParam(int i, const std::string& str)
{
	switch(i) 
	{
	case 0:
		m_tipsCanvas = str;
		break;
	case 1:
		m_tipsTextWidget = str;
		break;

	}
}

void crJXJUIOficialRankBestLevelTipMethod::operator()(crHandle &handle)
{
	crPlayerGameData *myPlayer = crMyPlayerData::getInstance()->getPlayerGameData();
	if(myPlayer)
	{
		ref_ptr<crTableIO> postTab = crGlobalHandle::gData()->gGlobalTable(WCHDATA_JXJGovPostTab);
		void *param;
		crData *data = myPlayer->getMainRole()->getDataClass();
		if(postTab.valid() && data)
		{
			data->getParam(WCHDATA_JXJGovPost,param);
			unsigned char post = *(unsigned char*)param;
			int rowcount = postTab->getRowCount();
			if(post == rowcount) 
			{
				GeneralTips generalTips(m_tipsCanvas, m_this);
				std::string str = "�Ѿ�����߼���";
				generalTips.setText(m_tipsTextWidget, str);
				generalTips.setTipUpper();
			}
		}
	}
}

/////////////////////////////////////////
//
//crJXJSelectCharacterPowerOnShowMethod
//���ν�����Ϸʱ���������������������
//
/////////////////////////////////////////
crJXJSelectCharacterPowerOnShowMethod::crJXJSelectCharacterPowerOnShowMethod()
{
}
crJXJSelectCharacterPowerOnShowMethod::crJXJSelectCharacterPowerOnShowMethod(const crJXJSelectCharacterPowerOnShowMethod& handle):
	crMethod(handle),
	m_PowerRaidoCanvas(handle.m_PowerRaidoCanvas)
{
}
void crJXJSelectCharacterPowerOnShowMethod::inputParam(int i, void *param)
{
	switch(i) 
	{
	case 0:
		if(param == 0)
		{//�ͷ�
			m_this = NULL;
		}
		break;
	case 1:
		m_this = (crCanvasNode*)param;
		break;
	}
}
void crJXJSelectCharacterPowerOnShowMethod::addParam(int i, const std::string& str)
{
	switch(i) 
	{
	case 0:
		m_PowerRaidoCanvas = str;
		break;
	case 1:
	case 2:
	case 3:
		m_radio[i - 1] = str;
		break;
	}
}

void crJXJSelectCharacterPowerOnShowMethod::operator()(crHandle &handle)
{
	void* param;
	int powerNum = 0;
	bool isLoseCountry = false;
	int shiliid = c_startShiliID;
	crRadioGroupWidgetNode *radio = dynamic_cast<crRadioGroupWidgetNode *>(m_this->getWidget(m_PowerRaidoCanvas));
	//crRadioWidgetNode *wu = dynamic_cast<crRadioWidgetNode *>(m_this->getWidget(m_Wu));
	//if(wu)
	//	wu->setVisiable(false);
	if (radio)
	{
		//int i = 0;
		//crPlayerGameData *myPlayer = crMyPlayerData::getInstance()->getPlayerGameData();
		//for (i = 0;i < 3; ++i)
		//{
		//	isLoseCountry = false;
		//	shiliid = c_startShiliID + i;
		//	myPlayer->doEvent(WCH_JXJCheckCountryLose,MAKECREPARAM(&isLoseCountry,&shiliid));
		//	if (isLoseCountry)
		//	{
		//		break;
		//	}
		//}loseshiliid
		int i = -1;
		crData *brainData = crBrain::getInstance()->getDataClass();
		brainData->getParam(WCHDATA_JXJQueryLoseShiliID,param);
		crVector2ub loseshiliid = *(crVector2ub *)param;
		for( int j = 0; j<2; j++)
		{
			if (loseshiliid[j] > 0)
			{
				i = loseshiliid[j] - c_startShiliID;
				if (i < 3 && i >= 0)
				{
					crRadioWidgetNode *radio = dynamic_cast<crRadioWidgetNode *>(m_this->getWidget(m_radio[i]));
					if (radio)
					{
						radio->setEnable(false);
					}
				}
			}
		}
		////��0,1,2�������ȡһ����
		//CRCore::rangei r(0,3);
		//do 
		//{
		//	//CRCore::rangei r(0,2);
		//	powerNum = r.get_random();
		//	//��RadioGroupWidget�ؼ���ʾѡ�г��е�����
		//	//�ų��������ѡ��
		//	if(powerNum == loseshiliid[0]-c_startShiliID)
		//		continue;
		//	if(powerNum == loseshiliid[1]-c_startShiliID)
		//		continue;
		//	break;
		//} while (1);
		//radio->select(powerNum);
		radio->select(3);
		radio->doEvent(WCH_UI_SelectChange);
	}

}

/////////////////////////////////////////
//
//crJXJUINationIntroduceInfoMethod
//��ɫѡ����Ϣ��ʾ
//
/////////////////////////////////////////
crJXJUINationIntroduceInfoMethod::crJXJUINationIntroduceInfoMethod()
{
}
crJXJUINationIntroduceInfoMethod::crJXJUINationIntroduceInfoMethod(const crJXJUINationIntroduceInfoMethod& handle):
	crMethod(handle),
	m_infoSwitch(handle.m_infoSwitch)
{
}
void crJXJUINationIntroduceInfoMethod::inputParam(int i, void *param)
{
	switch(i) 
	{
	case 0:
		if(param == 0)
		{//�ͷ�
			m_this = NULL;
		}
		break;
	case 1:
		m_this = (crRadioGroupWidgetNode *)param;
		break;
	}
}
void crJXJUINationIntroduceInfoMethod::addParam(int i, const std::string& str)
{
	switch(i) 
	{
	case 0:
		m_infoSwitch = str;
		break;
	}
}

void crJXJUINationIntroduceInfoMethod::operator()(crHandle &handle)
{
	crCanvasNode *canvas = m_this->getParentCanvas();
	if(canvas)
	{
		crMultiSwitch *infosw = dynamic_cast<crMultiSwitch *>(canvas->getChildNode(m_infoSwitch));
		if(infosw)
			infosw->setActiveSwitchSet(m_this->getSelect());
	}
}

///////////////////////////////////////////
////
////crJXJUIBattleTroopsTypeTipMethod
////ս������������ʾ��Ϣ
////
///////////////////////////////////////////
//crJXJUIBattleTroopsTypeTipMethod::crJXJUIBattleTroopsTypeTipMethod():
//	m_index_1(0),
//	m_index_2(0)
//{
//}
//crJXJUIBattleTroopsTypeTipMethod::crJXJUIBattleTroopsTypeTipMethod(const crJXJUIBattleTroopsTypeTipMethod& handle):
//	crMethod(handle),
//	m_tipsCanvas(handle.m_tipsCanvas),
//	m_tipsTroopsNameWidget(handle.m_tipsTroopsNameWidget),
//	m_tipsTroopsFeatureWidget(handle.m_tipsTroopsFeatureWidget),
//	m_index_1(handle.m_index_1),
//	m_index_2(handle.m_index_2)
//{
//}
//void crJXJUIBattleTroopsTypeTipMethod::inputParam(int i, void *param)
//{
//	switch(i) 
//	{
//	case 0:
//		if(param == 0)
//		{//�ͷ�
//			m_this = NULL;
//		}
//		break;
//	case 1:
//		m_this = (crWidgetNode*)param;
//		break;
//	}
//}
//void crJXJUIBattleTroopsTypeTipMethod::addParam(int i, const std::string& str)
//{
//	switch(i) 
//	{
//	case 0:
//		m_tipsCanvas = str;
//		break;
//	case 1:
//		m_tipsTroopsNameWidget = str;
//		break;
//	case 2:
//		m_tipsTroopsFeatureWidget = str;
//		break;
//	case 3:
//		m_index_1 = atoi(str.c_str());//0 stands for left formation troops, and 1 stands for right formation troops.2 stands for barracks troops.
//		break;
//	case 4:
//		m_index_2 = atoi(str.c_str());//widget num 
//		break;
//	}
//}
//
//void crJXJUIBattleTroopsTypeTipMethod::operator()(crHandle &handle)
//{
//	crCanvasNode *tips = crFilterRenderManager::getInstance()->findCanvas(m_tipsCanvas);
//	if(tips)
//	{
//		crStaticTextWidgetNode *tipsTroopName = dynamic_cast<crStaticTextWidgetNode *>(tips->getWidget(m_tipsTroopsNameWidget));
//		crHypertextWidgetNode *tipsTroopFeature = dynamic_cast<crHypertextWidgetNode *>(tips->getWidget(m_tipsTroopsFeatureWidget));
//		CREncapsulation::crTableIO::StrVec	record;// record extracting	
//		CREncapsulation::ref_ptr<crTableIO> troops_table = CRNetApp::crGlobalHandle::gData()->gGlobalTable(WCHDATA_JXJTroopsTab);	// troops look-up table 
//
//		if(tipsTroopName && tipsTroopFeature)
//		{
//			void *param;
//			//datas
//			CRCore::crCanvasNode *parent_canvas	= m_this->getParentCanvas(); // formation canvas entity
//			if(!parent_canvas)return;
//			CRCore::crData *canvas_data = parent_canvas->getDataClass();
//			if(!canvas_data)return;
//			//get troops type id
//			int abstractid = -1;
//			if (m_index_1 == 3)//��ȡ����ѡ�о��ӵ�id
//			{
//				CRPhysics::crCamera *camera = CRPhysics::crCameraManager::getInstance()->getMainCamera();
//				if(camera)
//				{
//					crData *cameraData = camera->getAttachedNode()->getDataClass();
//					if(cameraData)
//					{
//						CRCore::ScopedLock<crData> lock(*cameraData);
//						cameraData->getParam(WCHDATA_SelectMyRoleVec,param);
//						SelectMyRoleVec *selectMyRoles = (SelectMyRoleVec *)param;
//						if(!selectMyRoles->empty())
//						{
//							crRole *role = (*selectMyRoles)[0].get();
//							if(role) abstractid = role->getAbstractItemID();
//						}
//					}
//				}
//			}
//			else if(m_index_1 == 4)//��ȡ�������Ͼ���id
//			{
//				crMyPlayerData *me = crMyPlayerData::getInstance();
//				if(me)
//				{
//					crRole *role = me->getLoadedRoleByIndex(m_index_2);
//					if(role) abstractid = role->getAbstractItemID();
//				}
//			}
//			if(abstractid<=0 || troops_table->queryOneRecord(0, crArgumentParser::appItoa(abstractid), record) < 0)
//			{
//				return;
//			}
//			//����
//			int nameindex = troops_table->getTitleIndex("name");//��ȡtroops.tab����name���ڵ���
//			std::string name = record[nameindex];
//			if(tipsTroopName)tipsTroopName->setString(name);
//
//			//˵��
//			int infoid = troops_table->getTitleIndex("˵��");
//			if(tipsTroopFeature)
//			{
//				std::string file = record[infoid];
//				if(!file.empty())
//				{
//					file = crMyPlayerData::getInstance()->getSelectedGame()->getTextDir() + file;
//					if(tipsTroopFeature)tipsTroopFeature->setHypertext(file);
//				}
//				else
//				{
//					if(tipsTroopFeature)tipsTroopFeature->clearText();
//				}
//			}
//			
//			//������ʾ����ʾλ��
//			const crMatrix &mat = m_this->getParentCanvas()->getMatrix();
//			const crBoundingBox &iconbox = m_this->getBoundBox();
//			const crBoundingBox &tip = tips->getBoundBox();
//			float posx = (tip.m_max[0]-tip.m_min[0])*0.5;
//			float posy = (tip.m_max[1]-tip.m_min[1])*0.5;
//			crVector3 pos(iconbox.m_max[0],iconbox.m_max[1],0.0f);
//			pos = pos * mat;
//			/////////////////////////////////////////
//			crVector3 pos2(iconbox.m_min[0] ,iconbox.m_min[1],0.0f);
//			pos2 = pos2 * mat;
//			float posx2,posy2;
//			/////////////////////////////////////////
//			if (pos2[0] >= 0)
//			{
//				posx2 = pos2[0] - posx;
//			}
//			else
//			{
//				posx2 = pos[0] + posx;
//			}
//			if (pos2[1] >= 0)
//			{
//				posy2 = pos[1] - posy;
//			}
//			else
//			{
//				posy2 = pos2[1] + posy;
//			}
//			crVector2 mouse(crVector2(posx2,posy2));
//			/////////////////////////////////////////
//			tips->setMatrix(crMatrix::translate(mouse[0],mouse[1],0.0f)/* * mat*/);
//			tips->setCanFocus(false);
//			crFilterRenderManager::getInstance()->showCanvas(tips,true);
//		}
//	}
//}
/////////////////////////////////////////
//
//crJXJUITroopsTypeTipMethod
//���������������ʾ��Ϣ
//
/////////////////////////////////////////
crJXJUITroopsTypeTipMethod::crJXJUITroopsTypeTipMethod():
	m_index_1(0),
	m_index_2(0)
{
}
crJXJUITroopsTypeTipMethod::crJXJUITroopsTypeTipMethod(const crJXJUITroopsTypeTipMethod& handle):
	crMethod(handle),
	m_tipsCanvas(handle.m_tipsCanvas),
	m_tipsTroopsNameWidget(handle.m_tipsTroopsNameWidget),
	m_armyTypeRadio(handle.m_armyTypeRadio),
	m_index_1(handle.m_index_1),
	m_index_2(handle.m_index_2)
{
}
void crJXJUITroopsTypeTipMethod::inputParam(int i, void *param)
{
	switch(i) 
	{
	case 0:
		if(param == 0)
		{//�ͷ�
			m_this = NULL;
		}
		break;
	case 1:
		m_this = (crWidgetNode*)param;
		break;
	case 2:
		if(param)
		{
			CREPARAM& param64 = *(CREPARAM*)param;
			m_ea = (CRProducer::crGUIEventAdapter*)(LOCREPARAM(param64));
		}
		else
		{
			m_ea = NULL;
		}
		break;
	}
}
void crJXJUITroopsTypeTipMethod::addParam(int i, const std::string& str)
{
	switch(i) 
	{
	case 0:
		m_tipsCanvas = str;
		break;
	case 1:
		m_tipsTroopsNameWidget = str;
		break;
	case 2:
		m_tipsZhanliinput[0] = str;
		break;
	case 3:
		m_tipsZhanliinput[1] = str;
		break;
	case 4:
		m_index_1 = atoi(str.c_str());//0 stands for left formation troops, and 1 stands for right formation troops.2 stands for barracks troops.
		break;
	case 5:
		m_index_2 = atoi(str.c_str());//widget num 
		break;
	case 6:
		m_armyTypeRadio = str;
		break; 
	case 7:
		m_infoCanvas = str;
		break; 
	case 8:
		m_infoInput = str;
		break; 
	case 9:
		m_infoBK = str;
		break; 
	case 10:
		m_infoDi = str;
		break; 
	//case 4:
	//	m_tipsTroopsArmorWidget = str;
	//	break;
	//case 5:
	//	m_tipsTroopsMoveWidget = str;
	//	break;
	//case 6:
	//	m_tipsTroopsFireRateWidget = str;
	//	break;
	//case 7:
	//	m_tipsTroopsCritWidget = str;
	//	break;
	//case 8:
	//	m_tipsTroopsBlockWidget = str;
	//	break;
	//case 9:
	//	m_tipsTroopsDuckWidget = str;
	//	break;
	//case 10:
	//	m_tipsTroopsRangeWidget = str;
	//	break;
	//case 11:
	//	m_tipsTroopsFeatureWidget = str;
	//	break;
	//case 12:
	//	m_tipsTroopsOneWidget = str;
	//	break;
	//case 13:
	//	m_tipsTroopsBarrackWidget = str;
	//	break;
	//case 14:
	//	m_tipsTroopsMoneyWidget = str;	
	//	break;
	//case 15:
	//	m_tipsTroopsFoodWidget = str;	
	//	break;
	//case 16:
	//	m_tipsTroopsEquipWidget = str;
	//	break;
	}
}

void crJXJUITroopsTypeTipMethod::operator()(crHandle &handle)
{
	crCanvasNode *tips = crFilterRenderManager::getInstance()->findCanvas(m_tipsCanvas);
	crCanvasNode *infoCanvas = crFilterRenderManager::getInstance()->findCanvas(m_infoCanvas);
	if(tips && infoCanvas)
	{
		crStaticTextWidgetNode *tipsTroopName = dynamic_cast<crStaticTextWidgetNode *>(tips->getWidget(m_tipsTroopsNameWidget));

		crHypertextWidgetNode *infoinput = dynamic_cast<crHypertextWidgetNode *>(infoCanvas->getWidget(m_infoInput));
		crMatrixTransform *infobk = dynamic_cast<crMatrixTransform *>(infoCanvas->getChildNode(m_infoBK));
		crMatrixTransform *infodi = dynamic_cast<crMatrixTransform *>(infoCanvas->getChildNode(m_infoDi));

		//crHypertextWidgetNode *infoinput = dynamic_cast<crHypertextWidgetNode *>(tips->getWidget(m_infoInput));
		//crMatrixTransform *infobk = dynamic_cast<crMatrixTransform *>(tips->getChildNode(m_infoBK));
		//crMatrixTransform *infodi = dynamic_cast<crMatrixTransform *>(tips->getChildNode(m_infoDi));

		//if(tipsTroopName && tipsTroopLife && tipsTroopAttack && tipsTroopArmor && tipsTroopMove && tipsTroopFireRate && tipsTroopCrit && tipsTroopBlock && tipsTroopDuck && tipsTroopRange && tipsTroopFeature && tipsTroopOne && tipsTroopBarrack && tipsTroopMoney &&tipsTroopFood )
		// troops tables
		CREncapsulation::crTableIO::StrVec	record,record5,recordtech;// record extracting	
		ref_ptr<crTableIO> troops_table = CRNetApp::crGlobalHandle::gData()->gGlobalTable(WCHDATA_JXJTroopsTab);	// troops look-up table 
		ref_ptr<crTableIO> TroopsTechTab = CRNetApp::crGlobalHandle::gData()->gGlobalTable(WCHDATA_JXJTroopsTechTab);	// troops look-up table 
		//int abid = itemtab->getTitleIndex("abstractid");

		if(tipsTroopName)
		{
			void *param;
			//datas
			ref_ptr<crListControlWidgetNode> armylist = NULL;
			ref_ptr<crListControlNode> selectNode = NULL;
			CRCore::crCanvasNode *parent_canvas	= m_this->getParentCanvas(); // formation canvas entity
			if(!parent_canvas)return;
			CRCore::crData *canvas_data = parent_canvas->getDataClass();
			if(!canvas_data)return;
			//get troops type id
			int abstractid = -1;
			unsigned short armyCount = 0;
			crVector2i equips = crVector2i(-1,-1);
			if (m_index_1 == 0)
			{
				canvas_data->getParam(WCHDATA_JXJArmsCells, param);//���������ľ���id
				int	*arms = (int *)param;
				if(arms)
				{
					abstractid = arms[m_index_2];
				}
			}
			else if (m_index_1 == 1)
			{
				canvas_data->getParam(WCHDATA_JXJTempFormationVec, param);
				if (param)
				{
					FormationInfoVec *tempformation	= (FormationInfoVec *)param;//����ȡ�Ҳ���Ӿ��ӵ�id
					if (m_index_2 < tempformation->size() && (*tempformation)[m_index_2]!=NULL)
					{
						abstractid = (*tempformation)[m_index_2]->getAbstractID();
						armyCount = (*tempformation)[m_index_2]->getCount();
						equips = (*tempformation)[m_index_2]->getEquips();
					}
				}
			}
			else if (m_index_1 == 2)//��ȡ��Ӫ���ӵ�id
			{
				crRadioGroupWidgetNode *radioGroup = dynamic_cast<crRadioGroupWidgetNode *>(m_this->getParentWidget());
				int index = radioGroup->getRadioIndex(dynamic_cast<crRadioWidgetNode *>(m_this));

				//void *param;
				//crData *data = crBrain::getInstance()->getDataClass();
				////data->getParam(WCHDATA_JXJCurSelRecruitArmAID,param);
				//data->getParam(WCHDATA_JXJCurRecruitArmID,param);
				//int row = *(int *)param + index;
				//crRadioGroupWidgetNode *armyTypeRadioGroup = dynamic_cast<crRadioGroupWidgetNode *>(parent_canvas->getWidget(m_armyTypeRadio));
				//int armType = armyTypeRadioGroup->getSelect();
				//crTableIO::DataVec recordVec;
				//troops_table->queryRecords(2,crArgumentParser::appItoa(armType),recordVec);
				//if(row < recordVec.size())	
				//{
				//	abstractid = atoi(recordVec[row][0].c_str());
				//}
				void *param;
				crData *data = crBrain::getInstance()->getDataClass();
				//data->getParam(WCHDATA_JXJCurSelRecruitArmAID,param);
				data->getParam(WCHDATA_JXJRecruitArmyVec,param);
				RecruitArmyVec *recruitarmyvec = (RecruitArmyVec *)param;
				if (index < recruitarmyvec->size())
				{
					abstractid = (*recruitarmyvec)[index];
				}
			}
			else if (m_index_1 == 3)//��ȡ����ѡ�о��ӵ�id
			{
				ref_ptr<CRPhysics::crCamera> camera = CRPhysics::crCameraManager::getInstance()->getMainCamera();
				if(camera.valid())
				{
					crData *cameraData = camera->getAttachedNode()->getDataClass();
					if(cameraData)
					{
						CRCore::ScopedLock<crData> lock(*cameraData);
						cameraData->getParam(WCHDATA_SelectMyRoleVec,param);
						SelectMyRoleVec *selectMyRoles = (SelectMyRoleVec *)param;
						if(!selectMyRoles->empty())
						{
							crRole *role = (*selectMyRoles)[0].get();
							if(role) abstractid = role->getAbstractItemID();
						}
					}
				}
			}
			else if(m_index_1 == 4)//��ȡ�������Ͼ���id
			{
				crMyPlayerData *me = crMyPlayerData::getInstance();
				if(me)
				{
					crRole *role = me->getLoadedRoleByIndex(m_index_2);
					if(role) abstractid = role->getAbstractItemID();
				}
			}
			else if(m_index_1 == 5)//��ȡ�����Ƽ����ľ���ID
			{
				int armytype = 0;
				int armyTypeIndex = troops_table->getTitleIndex("����");
				int iconNameIndex = troops_table->getTitleIndex("iconname");
				ref_ptr<crRadioGroupWidgetNode> armyTypeRadioGroup = dynamic_cast<crRadioGroupWidgetNode *>(parent_canvas->getWidget(m_armyTypeRadio));
				if(armyTypeRadioGroup.valid())armytype = armyTypeRadioGroup->getSelect();
				std::string iconname = m_this->getName();
				if(troops_table->queryOneRecord(armyTypeIndex, crArgumentParser::appItoa(armytype), iconNameIndex,iconname,record5) >= 0)
				{
					abstractid = atoi(record5[0].c_str());
				}

			}
			else if(m_index_1 == 6)//��ȡ������ID
			{
				armylist = dynamic_cast<crListControlWidgetNode *>(m_this);
				if (armylist.valid())
				{
					selectNode = armylist->getSelectNode();
					if (selectNode.valid())
					{
						abstractid = selectNode->getData();
					}
				}
			}
			if(abstractid<=0 || troops_table->queryOneRecord(0, crArgumentParser::appItoa(abstractid), record) < 0)
			{
				return;
			}
			int canRecruitIndex = troops_table->getTitleIndex("����ļ");
			if(m_index_1 == 2 && record[canRecruitIndex] == "0")//��Ӫ������ʾ������ļ�ı���tips
			{
				return;
			}
			int nameindex = troops_table->getTitleIndex("name");//��ȡtroops.tab����name���ڵ���
			std::string name = record[nameindex];
			if(tipsTroopName)tipsTroopName->setString(name);

			ItemMap itemMap;	
			ItemMap itemMap2;	
			ItemMap itemMap3;		
			rcfg::ConfigScript cfg_script(&itemMap);
			rcfg::ConfigScript cfg_script2(&itemMap2);
			rcfg::ConfigScript cfg_script3(&itemMap3);
			gethypertext(abstractid,cfg_script,cfg_script2,cfg_script3);
			if (infoinput)
			{
				infoinput->setHypertext(cfg_script);
				infoinput->setHypertext(cfg_script2,true);
				infoinput->setHypertext(cfg_script3,true);
			}
			///////////��������
			float charactersize = infoinput->getCharacterSize();
			float boxYlength = infobk->getChild(0)->getBoundBox().yLength()/**crDisplaySettings::instance()->getUIViewScale()[1]*/;
			infobk->getChild(0)->getBoundBox().center();
			infoinput->updateData();
			const crBoundingBox &bbox = infoinput->getTextObject()->getBoundBox();
			const crBoundingBox &bbox2 = infoinput->getBoundBox();
			float texheight = 0.0f;
			float needmove = 0.0f;
			if(bbox.valid())
			{
				texheight = bbox.yLength();
				float factor = crDisplaySettings::instance()->getUIPixelMeter() * crDisplaySettings::instance()->getUIHeightScale()/crDisplaySettings::instance()->getUIScaleFactor();
				texheight *= factor;
				charactersize *= factor*c_tipsoffsets;
				
				if(texheight<boxYlength) texheight = boxYlength;
				float scale = texheight/boxYlength;

				needmove = texheight-boxYlength;/*/crDisplaySettings::instance()->getUIViewScale()[1]*/

				const crBoundingBox &tipsbb = tips->getBoundBox();
				crVector3 centerTansTar = infoinput->getBound().center();

				float tmpLength = bbox2.yLength();
				if(infodi)
				{
					float diYlength = infodi->getChild(0)->getBoundBox().yLength();
					//centerTansTar[1] += 0.5f * (tmpLength - texheight) + 0.0625 * diYlength;
					centerTansTar[1] += 0.5f * (tmpLength - texheight) + 0.125f * diYlength;
				}
				else
					centerTansTar[1] += 0.5f * (tmpLength - texheight);
				// Դ���ĵ�
				crVector3 centerTansSrc = infobk->getChild(0)->getBoundBox().center();
				// ��Դ���ĵ�ƽ�Ƶ�ԭ��
				crMatrix put_mat = crMatrix::translate(centerTansSrc);
				crMatrix inv_put = crMatrix::inverse(put_mat);
				crMatrix rotmat;
				rotmat.postMult(inv_put);
				rotmat.postMult(crMatrix::scale(1.0f,scale,1.0f));
				rotmat.postMult(crMatrix::translate(centerTansTar));
				if(infobk)infobk->setMatrix(rotmat);

				if(infodi)
				{
					float diYlength = infodi->getChild(0)->getBoundBox().yLength();
					//needmove = diYlength*0.5f*(scale-1.0f) - needmove;
					//needmove = boxYlength - texheight;
					needmove = boxYlength - texheight + diYlength * 0.125;
					infodi->setMatrix(crMatrix::translate(0.0f,needmove/*+c_tipsoffsets[2]*scale*/,0.0f));
				}

				//infobk->setMatrix(crMatrix::scale(1.0f,scale/*m_expandnum*/,1.0f) * crMatrix::translate(0.0f,-needmove*0.5 - charactersize/*+c_tipsoffsets*scale*/,0.0f));
				//if(infobk)infobk->setMatrix(crMatrix::scale(1.0f,scale/*m_expandnum*/,1.0f) * crMatrix::translate(0.0f,-needmove - texheight * 0.5 - charactersize * 0.5/*+c_tipsoffsets[1]*scale*/,0.0f));
				// Ŀ�����ĵ�
				//crVector3 centerTansTar = bbox.center(); //infoinput->getBound().center();
				//centerTansTar *= crDisplaySettings::instance()->getUIPixelMeter() * crDisplaySettings::instance()->getUIHeightScale()*c_tipsoffsets;

				//const crBoundingBox &tipsbb = tips->getBoundBox();
				//crVector3 centerTansTar = infoinput->getBound().center();

				//float tmpLength = bbox2.yLength();
				////tmpLength = bbox2.yLength() 
				////	* crDisplaySettings::instance()->getUIPixelMeter() 
				////	* crDisplaySettings::instance()->getUIHeightScale()*c_tipsoffsets;

				//centerTansTar[1] += 0.5 * (tmpLength - texheight) + tipsbb.yLength();
				//// Դ���ĵ�
				//crVector3 centerTansSrc = infobk->getChild(0)->getBoundBox().center();
				//// ��Դ���ĵ�ƽ�Ƶ�ԭ��
				//crMatrix put_mat = crMatrix::translate(centerTansSrc);
				//crMatrix inv_put = crMatrix::inverse(put_mat);
				//crMatrix rotmat;
				//rotmat.postMult(inv_put);
				//rotmat.postMult(crMatrix::scale(1.0f,scale,1.0f));
				//rotmat.postMult(crMatrix::translate(centerTansTar));
				//if(infobk)infobk->setMatrix(rotmat);
				////if(infobk)infobk->setMatrix(crMatrix::scale(1.0f,scale/*m_expandnum*/,1.0f));

				////needmove = texheight/crDisplaySettings::instance()->getUIViewScale()[1];
				//if(infodi)
				//{
				//	//crVector3 centerTansTar = infoinput->getBound().center();
				//	//crVector3 centerTansTar = infodi->getBound().center();
				//	//float diYlength = infodi->getChild(0)->getBoundBox().yLength();
				//	//needmove = diYlength* 0.5 * (scale-1.0f) - needmove;
				//	//needmove = centerTansTar[1] - 0.5 * texheight;
				//	//needmove = tipsbb.center()[1] - texheight + tipsbb.yLength();
				//	needmove = boxYlength - texheight + tipsbb.yLength();

				//	//crMatrix put_mat = crMatrix::translate(infodi->getBoundBox().center());
				//	//crMatrix inv_put = crMatrix::inverse(put_mat);
				//	crMatrix rotmat;
				//	//rotmat.postMult(inv_put);
				//	rotmat.postMult(crMatrix::translate(0.0f,needmove,0.0f));
				//	//std::cout << "-----------------" << std::endl;
				//	//std::cout << needmove << std::endl;
				//	//std::cout << "-----------------" << std::endl;
				//	infodi->setMatrix(rotmat);
				//	//infodi->setMatrix(crMatrix::translate(0.0f,needmove/*+c_tipsoffsets[2]*scale*/,0.0f));
				//}
			}
			else
			{
				if(infobk)infobk->setMatrix(crMatrix::scale(1.0f,1.0f/*m_expandnum*/,1.0f) * crMatrix::translate(0.0f,0.0f,0.0f));
				if(infodi) infodi->setMatrix(crMatrix::translate(0.0f,0.0f,0.0f));
			}

			//RoleDataAttrTab
			//ref_ptr<crTableIO> itemtab = crGlobalHandle::gData()->gGlobalTable(WCHDATA_JXJItemTab);
			//CREncapsulation::crTableIO::StrVec	recordData,itemrecord;
			//CREncapsulation::ref_ptr<crTableIO> role_data_table = CRNetApp::crGlobalHandle::gData()->gGlobalTable(WCHDATA_RoleDataAttrTab);	// troops data look-up table
			//std::string attackRange;
			//if(role_data_table->queryOneRecord(0, crArgumentParser::appItoa(abstractid), recordData) >= 0)
			//{
			//	if(m_index_1 == 1)
			//	{
			//		float outParam = 0.0f;
			//		float extra = 0.0f;

			//		ref_ptr<crRole>role = new crRole;
			//		role->setAbstractItemID(abstractid);
			//		role->getAbstractItem()->setScript("JXJ/script/bot/JXJRole.cfg");
			//		role->setItemtype(crInstanceItem::Npc);
			//		role->loadItemData(PlayerStream);
			//		crData *roleData = role->getDataClass();
			//		if(roleData)
			//		{
			//			roleData->inputParam(WCHDATA_JXJArmyCount,&armyCount);
			//			roleData->excHandle(MAKECREPARAM(WCH_LockData,1));
			//			roleData->getParam(WCHDATA_EquipOnMap,param);
			//			EquipOnMap *equipOnMap = (EquipOnMap *)param;
			//			if(equips[0]>0)
			//			{
			//				if(itemtab->queryOneRecord(0,crArgumentParser::appItoa(equips[0]),itemrecord) >= 0)
			//					equipOnMap->insert(std::make_pair(atoi(itemrecord[abid].c_str()),0));
			//			}
			//			if(equips[1]>0)
			//			{
			//				if(itemtab->queryOneRecord(0,crArgumentParser::appItoa(equips[1]),itemrecord) >= 0)
			//					equipOnMap->insert(std::make_pair(atoi(itemrecord[abid].c_str()),0));
			//			}
			//			roleData->excHandle(MAKECREPARAM(WCH_LockData,0));

			//			//�����츳
			//			m_this->doEvent(WCH_JXJSetInborn,MAKECREPARAM(role.get(),&equips));
			//		}
			//		int lifeindex = role_data_table->getTitleIndex("HP");
			//		std::string life = crArgumentParser::appItoa((int)atof(recordData[lifeindex].c_str()));
			//		role->doEvent(WCH_GetHP,MAKECREPARAM(&outParam,NULL));
			//		extra = outParam-atof(recordData[lifeindex].c_str());
			//		if(extra>=1.0f)
			//			life+=std::string("(+")+crArgumentParser::appItoa((int)extra)+std::string(")");
			//		if(tipsTroopLife)tipsTroopLife->setString(life);
			//		int attackindex = role_data_table->getTitleIndex("������");
			//		std::string attack = crArgumentParser::appItoa((int)atof(recordData[attackindex].c_str()));
			//		
			//		role->doEvent(WCH_GetDamage,MAKECREPARAM(&outParam,NULL));
			//		extra = outParam-atof(recordData[attackindex].c_str());
			//		if(extra>=1.0f)
			//			attack+=std::string("(+")+crArgumentParser::appItoa((int)extra)+std::string(")");

			//		if(tipsTroopAttack)tipsTroopAttack->setString(attack);

			//		int armorindex = role_data_table->getTitleIndex("����");
			//		std::string armor = crArgumentParser::appItoa((int)atof(recordData[armorindex].c_str()));
			//		role->doEvent(WCH_GetDefend,MAKECREPARAM(&outParam,NULL));
			//		extra = outParam-atof(recordData[armorindex].c_str());
			//		if(extra>=1.0f)
			//			armor+=std::string("(+")+crArgumentParser::appItoa((int)extra)+std::string(")");
			//		if(tipsTroopArmor)tipsTroopArmor->setString(armor);

			//		int moveindex = role_data_table->getTitleIndex("�ƶ��ٶ�");
			//		std::string move = recordData[moveindex];
			//		role->doEvent(WCH_GetSpeed,MAKECREPARAM(&outParam,NULL));
			//		float speed = atof(record[moveindex].c_str());
			//		speed /= crGlobalHandle::gData()->gUnitScale();
			//		extra = outParam-speed;
			//		if(extra>=1.0f)
			//			move+=std::string("(+")+crArgumentParser::appItoa((int)extra)+std::string(")");
			//		if(tipsTroopMove)tipsTroopMove->setString(move);

			//		int critindex = role_data_table->getTitleIndex("����");
			//		std::string crit = recordData[critindex];
			//		role->doEvent(MAKEINT64(WCH_GetCrit,NULL),MAKECREPARAM(&outParam,NULL));
			//		extra = outParam-atof(recordData[critindex].c_str());
			//		if(extra>=1.0f)
			//			crit+=std::string("(+")+crArgumentParser::appItoa((int)extra)+std::string(")");
			//		if(tipsTroopCrit)tipsTroopCrit->setString(crit);

			//		int blockindex = role_data_table->getTitleIndex("��");
			//		std::string block = recordData[blockindex];
			//		role->doEvent(MAKEINT64(WCH_GetParry,NULL),MAKECREPARAM(&outParam,NULL));
			//		extra = outParam-atof(recordData[blockindex].c_str());
			//		if(extra>=1.0f)
			//			block+=std::string("(+")+crArgumentParser::appItoa((int)extra)+std::string(")");
			//		if(tipsTroopBlock)tipsTroopBlock->setString(block);

			//		int duckindex = role_data_table->getTitleIndex("����");
			//		std::string duck = recordData[duckindex];
			//		role->doEvent(MAKEINT64(WCH_GetDodge,NULL),MAKECREPARAM(&outParam,NULL));
			//		extra = outParam-atof(recordData[duckindex].c_str());
			//		if(extra>=1.0f)
			//			duck+=std::string("(+")+crArgumentParser::appItoa((int)extra)+std::string(")");
			//		if(tipsTroopDuck)tipsTroopDuck->setString(duck);
			//	}
			//	int attackRangeIndex = role_data_table->getTitleIndex("attackid");
			//	attackRange = recordData[attackRangeIndex];
			//}
			//������ʾ����ʾλ��
			crVector2 mouse;
			if ((m_index_1 == 6) && selectNode.valid() && armylist.valid())
			{
				crVector4f rect = selectNode->getRect();
				crVector4f rectoffset = armylist->getRectOffset();
				const crBoundingBox &tipsbb = tips->getBoundBox();
				float posx = (tipsbb.m_max[0]-tipsbb.m_min[0])*0.5;
				float posy = (tipsbb.m_max[1]-tipsbb.m_min[1])*0.5;
				//const crMatrix &mat = crListControlWidgetNode::getMvpwNode()->getMatrix();
				CRCore::crMatrixTransform *m_mvpwNode = armylist->getMvpwNode();
				const crMatrix &mat = m_mvpwNode->getMatrix() * m_this->getParentCanvas()->getMatrix();
				//crMatrix invmat = crMatrix::inverse(mat);
				crVector3 pos(rect[2] + rect[0] + rectoffset[0],rect[1] - rect[3] - rectoffset[1],0.0f);
				crVector3 ipos = pos * mat;
				/////////////////////////////////////////
				crVector3 pos2(rect[0] ,rect[1],0.0f);
				crVector3 ipos2 = pos2 * mat;
				float posx2,posy2;
				/////////////////////////////////////////
				if (ipos2[0] >= 0)
				{
					posx2 = ipos2[0] - posx;
				}
				else
				{
					posx2 = ipos[0] + posx;
				}
				if (ipos2[1] >= 0)
				{
					posy2 = ipos2[1] - posy;
				}
				else
				{
					posy2 = ipos2[1] + posy;
				}
				if((abs(posy2)+posy)>1.0f)
				{
					if (posy2 >= 0)
					{
						posy2 -= posy;
					}
					else
					{
						posy2 += posy;
					}
				}
				mouse = crVector2(posx2,posy2);
			}
			else
			{
				const crMatrix &mat = m_this->getParentCanvas()->getMatrix();
				const crBoundingBox &iconbox = m_this->getBoundBox();
				const crBoundingBox &tip = tips->getBoundBox();
				float posx = (tip.m_max[0]-tip.m_min[0])*0.5;
				float posy = (tip.m_max[1]-tip.m_min[1])*0.5;
				crVector3 pos(iconbox.m_max[0],iconbox.m_max[1],0.0f);
				pos = pos * mat;
				/////////////////////////////////////////
				crVector3 pos2(iconbox.m_min[0] ,iconbox.m_min[1],0.0f);
				pos2 = pos2 * mat;
				float posx2,posy2;
				/////////////////////////////////////////
				if (pos2[0] >= 0)
				{
					posx2 = pos2[0] - posx;
				}
				else
				{
					posx2 = pos[0] + posx;
				}
				if (pos2[1] >= 0)
				{
					posy2 = pos[1] - posy;
				}
				else
				{
					posy2 = pos2[1] + posy;
				}
				mouse = crVector2(posx2,posy2);
			}
			/////////////////////////////////////////
			tips->setMatrix(crMatrix::translate(mouse[0],mouse[1],0.0f)/* * mat*/);
			infoCanvas->setMatrix(crMatrix::translate(mouse[0],mouse[1],0.0f));//(crMatrix::translate(mouse[0],mouse[1]-posy*2.0f-tipsCanvas->getBoundBox().yLength()*0.5f,0.0f));
			tips->setCanFocus(false);
			infoCanvas->setCanFocus(false);
			crFilterRenderManager::getInstance()->showCanvas(infoCanvas,true);
			crFilterRenderManager::getInstance()->showCanvas(tips,true);
		}
	}
}
void crJXJUITroopsTypeTipMethod::gethypertext(int abstractid,rcfg::ConfigScript& output, rcfg::ConfigScript& output2, rcfg::ConfigScript& output3)
{
	//˵��		// troops tables
	void *param;
	ref_ptr<crTableIO> itemtab = crGlobalHandle::gData()->gGlobalTable(WCHDATA_JXJItemTab);
	int abid = itemtab->getTitleIndex("abstractid");
	CRCore::crCanvasNode *parent_canvas	= m_this->getParentCanvas(); // formation canvas entity
	CRCore::crData *canvas_data = parent_canvas->getDataClass();
	CREncapsulation::crTableIO::StrVec	record,record5,recordtech;// record extracting	
	ref_ptr<crTableIO> troops_table = CRNetApp::crGlobalHandle::gData()->gGlobalTable(WCHDATA_JXJTroopsTab);	// troops look-up table 
	ref_ptr<crTableIO> TroopsTechTab = CRNetApp::crGlobalHandle::gData()->gGlobalTable(WCHDATA_JXJTroopsTechTab);	// troops look-up table 
	int infoid = troops_table->getTitleIndex("˵��");
	int troopstypeindex = troops_table->getTitleIndex("����");
	int shanbi = 0;
	std::string file;
	std::string addOne;
	std::string equipID;
	std::string needtechstring;
	std::string tipsTroopMoneyString, tipsTroopIronString, tipsTroopFoodString, tipsTroopHorseString, tipsTroopTimerString, tipsTroopLeadershipString,tipsTroopwoodString;
	int troopstype = 0;
	if(troops_table->queryOneRecord(0, crArgumentParser::appItoa(abstractid), record) >= 0)
	{
		troopstype = atoi(record[troopstypeindex].c_str());
		 file = record[infoid];
		std::vector< int > needtechvec;
		//TroopsTechTab
		//int barrackindex = troops_table->getTitleIndex("��Ӫ�ȼ�");
		//std::string barrack = record[barrackindex];
		//std::string tipsTroopBarrackString = "��Ӫ" + barrack + "��";
		int techneedindex = troops_table->getTitleIndex("�������ID");
		crArgumentParser::appAtoVec(record[techneedindex].c_str(),needtechvec);
		int nameindex = TroopsTechTab->getTitleIndex("name");
		for (int i = 0; i < needtechvec.size(); ++i)
		{
			if (TroopsTechTab->queryOneRecord(0,crArgumentParser::appItoa(needtechvec[i]),recordtech) >= 0)
			{
				needtechstring += recordtech[nameindex] + " " + "1��\n";
			}
		}
		int moneyindex = troops_table->getTitleIndex("ͭǮ");
		std::string money = record[moneyindex];
		tipsTroopMoneyString = "ͭǮ��" + money;
		int ironindex = troops_table->getTitleIndex("����");
		tipsTroopIronString = "����" + record[ironindex];
		int foodindex = troops_table->getTitleIndex("��ʳ");
		std::string food = record[foodindex];
		tipsTroopFoodString = "��ʳ��" + food;
		if(food.size() == 1)
			tipsTroopFoodString = tipsTroopFoodString + "  ";
		else if(food.size() == 2)
			tipsTroopFoodString = tipsTroopFoodString + " ";

		int horseindex = troops_table->getTitleIndex("��ƥ");
		tipsTroopHorseString = "��ƥ��" + record[horseindex];

		int equipindex = troops_table->getTitleIndex("װ��ID");
		equipID = record[equipindex];
		int canRecruitIndex = troops_table->getTitleIndex("����ļ");
		if(record[canRecruitIndex] == "1")
		{
			addOne = "\n\n������ļ��Ҫ\n";
		}
		else if(record[canRecruitIndex] == "0" )
		{
			addOne = "�˱��ֲ����ڱ�Ӫ��ļ\n";
		}
		int timeindex = troops_table->getTitleIndex("ʱ��");
		tipsTroopTimerString = "ʱ�䣺" + record[timeindex] + " ";
		int leadershipindex = troops_table->getTitleIndex("�쵼��");
		tipsTroopLeadershipString = "�쵼����" + record[leadershipindex];
		int woodindex = troops_table->getTitleIndex("ľ��");
		tipsTroopwoodString = "ľ�ģ�" + record[woodindex];

	}

	int shengming = 0;
	int hujia = 0;
	//RoleDataAttrTab
	CREncapsulation::crTableIO::StrVec	recordData,itemrecord;	
	ref_ptr<crTableIO> role_data_table = CRNetApp::crGlobalHandle::gData()->gGlobalTable(WCHDATA_RoleDataAttrTab);	// troops data look-up table
	std::string attackRange,attackRange2;
	std::string life,attack,armor,move,crit,block,duck,atttackspeed;
	std::string range,fireRateCD,fireRateYC,fireRate;
	std::string attackinfostr;
	int armyCount = 0;
	crVector2i equips;
	crVector4 color_life = COLOR_BLACK,
		color_attack = COLOR_BLACK,
		color_armor = COLOR_BLACK,
		color_move = COLOR_BLACK,
		color_block = COLOR_BLACK,
		color_crit = COLOR_BLACK,
		color_shanbi = COLOR_BLACK,
		color_range = COLOR_BLACK;
	if(role_data_table->queryOneRecord(0, crArgumentParser::appItoa(abstractid), recordData) >= 0)
	{
		if (troopstype == JXJTroopsType_Qixie)
		{
			attackinfostr = "���ǹ��� ";
		}
		else
		{
			attackinfostr = "������ ";
		}
		int lifeindex = role_data_table->getTitleIndex("HP");
		int attackindex = role_data_table->getTitleIndex("������");
		int armorindex = role_data_table->getTitleIndex("����");
		int moveindex = role_data_table->getTitleIndex("�ƶ��ٶ�");
		int critindex = role_data_table->getTitleIndex("����");
		int attackspeedindex = role_data_table->getTitleIndex("�����ٶ�");
		int blockindex = role_data_table->getTitleIndex("��");
		int duckindex = role_data_table->getTitleIndex("����");
		int attackRangeIndex = role_data_table->getTitleIndex("attackid");

		int lifeint = atoi( recordData[lifeindex].c_str());
		life = "���� " + crArgumentParser::appItoa(lifeint);
		if(lifeint >= 1000)
			life = life + " ";
		else
			life = life + "  ";

		lifeint = atoi( recordData[attackindex].c_str());
		attack = attackinfostr + crArgumentParser::appItoa(lifeint);
		int hujiaint = atoi( recordData[armorindex].c_str());
		armor = "���� " + crArgumentParser::appItoa(hujiaint);
		if(hujiaint < 100)
			armor = armor + " ";

		move = "���� " + crArgumentParser::appItoa(atoi(recordData[moveindex].c_str()));
		crit = "���� " + crArgumentParser::appItoa(atoi(recordData[critindex].c_str()));
		if(recordData[critindex].size() == 2)
			crit = crit + "   ";
		else
			crit = crit + "  ";
		block = "�� " + crArgumentParser::appItoa(atoi(recordData[blockindex].c_str()));
		shanbi = atoi(recordData[duckindex].c_str());
		duck = "���� " + crArgumentParser::appItoa(shanbi);

		float outParam = 0.0f;
		float extra = 0.0f;

		ref_ptr<crRole>role;
		if(m_index_1 == 1)
		{
			canvas_data->getParam(WCHDATA_JXJTempFormationVec, param);
			FormationInfoVec *tempformation	= (FormationInfoVec *)param;//����ȡ�Ҳ���Ӿ��ӵ�id
			if (m_index_2 < tempformation->size() && (*tempformation)[m_index_2]!=NULL)
			{
				armyCount = (*tempformation)[m_index_2]->getCount();
				equips = (*tempformation)[m_index_2]->getEquips();
			}
			
			canvas_data->excHandle(MAKECREPARAM(WCH_LockData,1));
			canvas_data->getParam(WCHDATA_JXJFormationTempRoleMap,param);
			TempRoleMap *roleMap = (TempRoleMap *)param;
			TempRoleMap::iterator itr_info = roleMap->find(m_index_2);
			if(itr_info!=roleMap->end())
			{
				role = itr_info->second.get();
			}
			canvas_data->excHandle(MAKECREPARAM(WCH_LockData,0));
			
// 			role->setAbstractItemID(abstractid);
// 			role->getAbstractItem()->setScript("JXJ/script/bot/JXJRole.cfg");
// 			role->setItemtype(crInstanceItem::Npc);
// 			role->loadItemData(PlayerStream);
// 			crData *roleData = role->getDataClass();
// 			if(roleData)
// 			{
// 				roleData->inputParam(WCHDATA_JXJArmyCount,&armyCount);
// 				roleData->excHandle(MAKECREPARAM(WCH_LockData,1));
// 				roleData->getParam(WCHDATA_EquipOnMap,param);
// 				EquipOnMap *equipOnMap = (EquipOnMap *)param;
// 				if(equips[0]>0)
// 				{
// 					if(itemtab->queryOneRecord(0,crArgumentParser::appItoa(equips[0]),itemrecord) >= 0)
// 						equipOnMap->insert(std::make_pair(atoi(itemrecord[abid].c_str()),0));
// 				}
// 				if(equips[1]>0)
// 				{
// 					if(itemtab->queryOneRecord(0,crArgumentParser::appItoa(equips[1]),itemrecord) >= 0)
// 						equipOnMap->insert(std::make_pair(atoi(itemrecord[abid].c_str()),0));
// 				}
// 				roleData->excHandle(MAKECREPARAM(WCH_LockData,0));
// 
// 				//�����츳
// 				m_this->doEvent(WCH_JXJSetInborn,MAKECREPARAM(role.get(),&equips));
// 			}

			if(role.valid())
			{
				//crMyPlayerData::getInstance()->getPlayerGameData()->doEvent(WCH_JXJSetInborn,MAKECREPARAM(role.get(),&equips));

				//life = "���� " + crArgumentParser::appItoa((int)atof(recordData[lifeindex].c_str()));
				outParam = 0.0f;
				role->doEvent(WCH_GetHP,MAKECREPARAM(&outParam,NULL));
				extra = outParam-atof(recordData[lifeindex].c_str());
				life = "���� " + crArgumentParser::appItoa(int(outParam));
				shengming  = (int)outParam;
				if(shengming >= 1000)
					life = life + " ";
				else
					life = life + "  ";
				if(extra>=1.0f)
				{
					//life+=std::string("(+")+crArgumentParser::appItoa((int)extra)+std::string(")");
					color_life = COLOR_GREEN;
				}
				//attack ="������ " + crArgumentParser::appItoa((int)atof(recordData[attackindex].c_str()));

				outParam = 0.0f;
				role->doEvent(WCH_GetDamage,MAKECREPARAM(&outParam,NULL));
				extra = outParam-atof(recordData[attackindex].c_str());
				attack = attackinfostr + crArgumentParser::appItoa(int(outParam));
				if(extra>=1.0f)
				{
					//attack+=std::string("(+")+crArgumentParser::appItoa((int)extra)+std::string(")");
					color_attack = COLOR_GREEN;
				}


				//armor = "���� " + crArgumentParser::appItoa((int)atof(recordData[armorindex].c_str()));
				outParam = 0.0f;
				role->doEvent(WCH_GetDefend,MAKECREPARAM(&outParam,NULL));
				extra = outParam-atof(recordData[armorindex].c_str());
				armor = "���� " + crArgumentParser::appItoa(int(outParam));
				hujia = (int)outParam;
				if(hujia < 100)
					armor = armor + " ";
				if(extra>=1.0f)
				{
					//armor+=std::string("(+")+crArgumentParser::appItoa((int)extra)+std::string(")");
					color_armor = COLOR_GREEN;
				}

				//recordData[moveindex];
				outParam = 0.0f;
				role->doEvent(WCH_GetSpeed,MAKECREPARAM(&outParam,NULL));
				float speed = atof(recordData[moveindex].c_str());
				speed /= crGlobalHandle::gData()->gUnitScale();
				//move = "���� " + crArgumentParser::appItoa((int)speed);
				extra = outParam-speed;
				move = "���� " + crArgumentParser::appItoa(int(outParam));
				if(extra>=1.0f)
				{
					//move+=std::string("(+")+crArgumentParser::appItoa((int)extra)+std::string(")");
					color_move = COLOR_GREEN;
				}

				//crit = "���� " + recordData[critindex];
				outParam = 0.0f;
				role->doEvent(MAKEINT64(WCH_GetCrit,NULL),MAKECREPARAM(&outParam,NULL));
				extra = outParam-atof(recordData[critindex].c_str());
				crit = "���� " + crArgumentParser::appItoa(int(outParam));
				int baoji = (int)outParam;
				if(baoji < 100)
					crit = crit + "   ";
				else
					crit = crit + "  ";
				if(extra>=1.0f)
				{
					//crit+=std::string("(+")+crArgumentParser::appItoa((int)extra)+std::string(")");
					color_crit = COLOR_GREEN;
				}

				//block = "�� " + recordData[blockindex];
				outParam = 0.0f;
				role->doEvent(MAKEINT64(WCH_GetParry,NULL),MAKECREPARAM(&outParam,NULL));
				extra = outParam-atof(recordData[blockindex].c_str());
				block = "�� " + crArgumentParser::appItoa(int(outParam));
				if(extra>=1.0f)
				{
					//block+=std::string("(+")+crArgumentParser::appItoa((int)extra)+std::string(")");
					color_block = COLOR_GREEN;
				}

				shanbi = atoi(recordData[duckindex].c_str());
				//duck = "���� " + crArgumentParser::appItoa(shanbi);
				outParam = 0.0f;
				role->doEvent(MAKEINT64(WCH_GetDodge,NULL),MAKECREPARAM(&outParam,NULL));
				extra = outParam-atof(recordData[duckindex].c_str());
				duck = "���� " + crArgumentParser::appItoa(int(outParam));
				if(extra>=1.0f)
				{
					//duck+=std::string("(+")+crArgumentParser::appItoa((int)extra)+std::string(")");
					color_shanbi = COLOR_GREEN;
				}
			}
		}
		attackRange = "��� " + recordData[attackRangeIndex];
		attackRange2 = recordData[attackRangeIndex];
		//SkillDataAttrTab
		float baserange = 0.0f;
		CREncapsulation::crTableIO::StrVec	recordSkill;	
		ref_ptr<crTableIO> role_skill_table = CRNetApp::crGlobalHandle::gData()->gGlobalTable(WCHDATA_SkillDataAttrTab);	// troops data look-up table 
		if(role_skill_table->queryOneRecord(0, attackRange2, recordSkill) >= 0)
		{
			int rangeindex = role_skill_table->getTitleIndex("ʹ�ð뾶");
			int cdindex = role_skill_table->getTitleIndex("CD");
			if (m_index_1 == 1 && role.valid())
			{
				baserange = atof(recordSkill[rangeindex].c_str());
				outParam = 0.0f;
				role->doEvent(MAKEINT64(WCH_GetAttackDist,NULL),MAKECREPARAM(&outParam,NULL));
				extra = outParam;// -atof(recordSkill[rangeindex].c_str());
				range = "�������� " + crArgumentParser::appItoa(int(baserange) + int(extra));
				if(extra>=1.0f)
				{
					range+=std::string("(+")+crArgumentParser::appItoa((int)extra)+std::string(")");
					color_range = COLOR_GREEN;
				}
			}
			else
			{
				range ="�������� " + recordSkill[rangeindex];
			}
			//if(rangeindex>0)
			//{
			//	float rangef = atof(record[rangeindex].c_str());
			//	//range = CRCore::maximum(range,crGlobalHandle::gData()->gMinItemUseRange());
			//	rangef /= crGlobalHandle::gData()->gUnitScale();
			//	unsigned short itemUseRange = (unsigned short)rangef;
			//}
	
			float cdtime = atof(recordSkill[cdindex].c_str());
			float cdreduce = 0.0f;
			if(role.valid())
			{
				role->doEvent(WCH_GetSkillCD,MAKECREPARAM(&cdreduce,NULL));
				if(cdreduce<=-1.0f)
					cdreduce = -0.99f; 
				cdtime = cdtime/(1.0f+cdreduce);
				float cdtimeextra = cdreduce/cdtime;
				char buf[64];
				sprintf(buf,"%.2f\0",1.0f/cdtime);
				fireRate = buf;//crArgumentParser::trim(buf);
				atttackspeed = "���� " + fireRate;
				if(fireRate.size() == 3)
					atttackspeed = atttackspeed + "  ";
				else if(fireRate.size() == 4)
					atttackspeed = atttackspeed + " ";
			}
			else
			{
				int fireRateCDindex = role_skill_table->getTitleIndex("CD");
				fireRateCD = recordSkill[fireRateCDindex];
				int fireRateYCindex = role_skill_table->getTitleIndex("����");
				fireRateYC = recordSkill[fireRateYCindex];
				float fireRateInt = atof(fireRateCD.c_str())+atof(fireRateYC.c_str());
				char buf[64];
				sprintf(buf,"%.2f\0",1.0f/fireRateInt);
				fireRate = buf;//crArgumentParser::trim(buf);
				atttackspeed = "���� " + fireRate;
				if(fireRate.size() == 3)
					atttackspeed = atttackspeed + "  ";
				else if(fireRate.size() == 4)
					atttackspeed = atttackspeed + " ";
			}
			//role->doEvent(MAKEINT64(WCH_GetSkillCD,1),MAKECREPARAM(&cdreduce,NULL));

			
			//atttackspeed = fireRateCD;
			//std::string fireRate = crArgumentParser::appFtoa(1.0f/fireRateInt);
			//if(tipsTroopFireRate)tipsTroopFireRate->setString(fireRate);
		}

	}
	std::vector<float>v_i;
	//rcfg::ConfigScript cfg_scriptinfo;
	//ItemMap itemMap;
	//rcfg::ConfigScript cfg_script(&itemMap);
	//ItemMap itemMap2;
	//rcfg::ConfigScript cfg_script2(&itemMap2);
	if(!file.empty())
	{
		file = crMyPlayerData::getInstance()->getSelectedGame()->getTextDir() + file;
		if(!crScriptLoadManager::getInstance()->loadConfigScript(output2,file))
		{
			CRCore::notify(CRCore::FATAL)<<"setHypertext(): file open error,"<<file<<std::endl;
			return;
		}
	}

	//TroopsEquipTab
	//CREncapsulation::crTableIO::StrVec	recordEquip;
	//CREncapsulation::ref_ptr<crTableIO> equip_tab = CRNetApp::crGlobalHandle::gData()->gGlobalTable(WCHDATA_JXJTroopsEquipTab);
	//if(equip_tab->queryOneRecord(0,equipID,recordEquip) >= 0)
	//{
	//	int equipindex = equip_tab->getTitleIndex("name");
	//	std::string equip = recordEquip[equipindex];
	//	if(tipsTroopEquip)
	//	{
	//		std::string tipsTroopEquipString = equip + "��1";
	//		tipsTroopEquip->setString(tipsTroopEquipString);
	//	}
	//}
	//std::vector<float>v_i;
	
	int index = 1;
	output.Add("Hypertext");
	output.Push("Hypertext");

	output.Add("Content");
	output.Push("Content",index++);
	v_i.clear();
	v_i.push_back(color_life[0]);
	v_i.push_back(color_life[1]);
	v_i.push_back(color_life[2]);
	v_i.push_back(color_life[3]);
	output.Add("Color",v_i);
	output.Add("Text",life+ "     ");
	output.Pop();

	output.Add("Content");
	output.Push("Content",index++);
	v_i.clear();
	v_i.push_back(color_attack[0]);
	v_i.push_back(color_attack[1]);
	v_i.push_back(color_attack[2]);
	v_i.push_back(color_attack[3]);
	output.Add("Color",v_i);
	output.Add("Text",attack+ "\n");
	output.Pop();

	output.Add("Content");
	output.Push("Content",index++);
	v_i.clear();
	v_i.push_back(color_armor[0]);
	v_i.push_back(color_armor[1]);
	v_i.push_back(color_armor[2]);
	v_i.push_back(color_armor[3]);
	output.Add("Color",v_i);
	output.Add("Text",armor+ "       ");
	output.Pop();

	output.Add("Content");
	output.Push("Content",index++);
	v_i.clear();
	v_i.push_back(color_move[0]);
	v_i.push_back(color_move[1]);
	v_i.push_back(color_move[2]);
	v_i.push_back(color_move[3]);
	output.Add("Color",v_i);
	output.Add("Text",move+ "\n");
	output.Pop();

	output.Add("Content");
	output.Push("Content",index++);
	v_i.clear();
	v_i.push_back(color_attack[0]);
	v_i.push_back(color_attack[1]);
	v_i.push_back(color_attack[2]);
	v_i.push_back(color_attack[3]);
	output.Add("Color",v_i);
	output.Add("Text",atttackspeed+ "     ");
	output.Pop();

	output.Add("Content");
	output.Push("Content",index++);
	v_i.clear();
	v_i.push_back(color_block[0]);
	v_i.push_back(color_block[1]);
	v_i.push_back(color_block[2]);
	v_i.push_back(color_block[3]);
	output.Add("Color",v_i);
	output.Add("Text",block+ "\n");
	output.Pop();

	output.Add("Content");
	output.Push("Content",index++);
	v_i.clear();
	v_i.push_back(color_crit[0]);
	v_i.push_back(color_crit[1]);
	v_i.push_back(color_crit[2]);
	v_i.push_back(color_crit[3]);
	output.Add("Color",v_i);
	output.Add("Text",crit+ "     ");
	output.Pop();

	output.Add("Content");
	output.Push("Content",index++);
	v_i.clear();
	v_i.push_back(color_shanbi[0]);
	v_i.push_back(color_shanbi[1]);
	v_i.push_back(color_shanbi[2]);
	v_i.push_back(color_shanbi[3]);
	output.Add("Color",v_i);
	output.Add("Text",duck+ "\n");
	output.Pop();

	output.Add("Content");
	output.Push("Content",index++);
	v_i.clear();
	v_i.push_back(color_range[0]);
	v_i.push_back(color_range[1]);
	v_i.push_back(color_range[2]);
	v_i.push_back(color_range[3]);
	output.Add("Color",v_i);
	output.Add("Text",range+ "\n");
	output.Pop();

	output.Pop();

	output3.Add("Hypertext");
	output3.Push("Hypertext");
	output3.Add("Content");
	output3.Push("Content");
	output3.Add("Text",addOne + "\n"+ tipsTroopMoneyString + "        " + tipsTroopIronString + "\n" + tipsTroopFoodString + "      " + tipsTroopHorseString + "\n" + tipsTroopTimerString + "      " + tipsTroopwoodString + "\n" +tipsTroopLeadershipString + "\n" + needtechstring );
	output3.Pop();
	output3.Pop();

	//cfg_script.Write("1111111");
};

/////////////////////////////////////////
//
//crJXJUICDTimeTipMethod
//��������������ˢ��ʱ�����ʾ
//
/////////////////////////////////////////
crJXJUICDTimeTipMethod::crJXJUICDTimeTipMethod():
	m_this(NULL),
	m_btnindex(0)
{
	m_buildinginputnamevec.push_back("SpeedUp1_Input");
	m_buildinginputnamevec.push_back("SpeedUp2_Input");
	m_buildinginputnamevec.push_back("SpeedUp3_Input");
	m_buildinginputnamevec.push_back("SpeedUp4_Input");
	m_recruitinputnamevec.push_back("SpeedUp5_Input");
	m_recruitinputnamevec.push_back("SpeedUp6_Input");
	m_recruitinputnamevec.push_back("SpeedUp7_Input");
	m_recruitinputnamevec.push_back("SpeedUp8_Input");
}

crJXJUICDTimeTipMethod::crJXJUICDTimeTipMethod(const crJXJUICDTimeTipMethod& handle):
	crMethod(handle),
	m_tipsCanvas(handle.m_tipsCanvas),
	m_tipsTextWidget(handle.m_tipsTextWidget),
	m_btnindex(handle.m_btnindex)
{
}
void crJXJUICDTimeTipMethod::inputParam(int i, void *param)
{
	switch(i) 
	{
	case 0:
		if(param == 0)
		{//�ͷ�
			m_this = NULL;
		}
		break;
	case 1:
		m_this = (crWidgetNode*)param;
		break;
	}
}
void crJXJUICDTimeTipMethod::addParam(int i, const std::string& str)
{
	switch(i) 
	{
	case 0:
		m_tipsCanvas = str;
		break;
	case 1:
		m_tipsTextWidget = str;
		break;
	case 2:
		m_index = atoi(str.c_str());
		break;
	case 3:
		m_btnindex = atoi(str.c_str());
		break;
	}
}

void crJXJUICDTimeTipMethod::operator()(crHandle &handle)
{
	void *param;
	crPlayerGameData *myPlayer = crMyPlayerData::getInstance()->getPlayerGameData();
	if (myPlayer)
	{
		crData *data = myPlayer->getDataClass();
		data->getParam(WCHDATA_JXJVipLv,param);
		unsigned char viplv = *(unsigned char *)param;
		//��ȡ��Ҫ������Ϣ�����
		crCanvasNode *tips = crFilterRenderManager::getInstance()->findCanvas(m_tipsCanvas);
		//��ȡ��Ҫ������Ϣ�Ŀؼ�
		if(!tips)return;
		crHypertextWidgetNode *tipsText = dynamic_cast<crHypertextWidgetNode *>(tips->getWidget(m_tipsTextWidget));
		crStaticTextWidgetNode *widgetText = dynamic_cast<crStaticTextWidgetNode *>(m_this);
		ref_ptr<crTableIO> hintTable = crGlobalHandle::gData()->gGlobalTable(WCHDATA_JXJHintTab);
		ref_ptr<crTableIO> viplvtab = crGlobalHandle::gData()->gGlobalTable(WCHDATA_JXJVipLevelTab);
		int timeindex = hintTable->getTitleIndex("ʱ����");
		crTableIO::StrVec record;
		int priceindex = hintTable->getTitleIndex("price");
		if(tipsText && priceindex >= 0)
		{			
			int cdhintid;
			std::string str,price;
			if(m_index == 0)
				cdhintid = WCHDATA_JXJBuyBuildingTimeHint;
			else if(m_index == 1)
				cdhintid = WCHDATA_JXJBuyRecruitTimeHint;
			if (hintTable->queryOneRecord(0, crArgumentParser::appItoa(cdhintid), timeindex, crArgumentParser::appItoa(m_btnindex-1), record) >= 0)
			{
				price = record[priceindex];
			}
			int id = cdhintid == WCHDATA_JXJBuyBuildingTimeHint ? WCHDATA_JXJBuildingTimes : WCHDATA_JXJRecruitTimes;
			data->getParam(id, param);
			int maxcount = 0;
			crVector4i timers = *(crVector4i *)param;
			for (int i = 0; i < 4; ++i)
			{
				if (timers[i] >= 0)
				{
					maxcount++;
				}
			}
			//���VIP�ȼ�
			std::string vipstr;
			int nextmaxcount = 0;
			int vip = 0;
			//if (cdhintid == WCHDATA_JXJBuyBuildingTimeHint)
			//{
			//	maxcount = (int)(atoi(crGlobalHandle::gData()->gGameGlobalValue(WCHDATA_JXJBuildingTimeBarMaxCount,viplv).c_str()));
			//}4
			//else if (cdhintid == WCHDATA_JXJBuyRecruitTimeHint)
			//{
			//	maxcount = (int)(atoi(crGlobalHandle::gData()->gGameGlobalValue(WCHDATA_JXJRecruitTimeBarMaxCount,viplv).c_str()));
			//}
			for (int i = 0; i <= viplvtab->getRowCount(); ++i)
			{
				nextmaxcount = 0;
				vipstr.clear();
				if (cdhintid == WCHDATA_JXJBuyBuildingTimeHint)
				{
					nextmaxcount = (int)(atoi(crGlobalHandle::gData()->gGameGlobalValue(WCHDATA_JXJBuildingTimeBarMaxCount,i).c_str()));
				}
				else if (cdhintid == WCHDATA_JXJBuyRecruitTimeHint)
				{
					nextmaxcount = (int)(atoi(crGlobalHandle::gData()->gGameGlobalValue(WCHDATA_JXJRecruitTimeBarMaxCount,i).c_str()));
				}
				if (nextmaxcount == m_btnindex/*maxcount*/)
				{//����CD��ȫ�����ţ��������ռ�����ֵ
					vip = i;
					vipstr = "   ��ҪVIP"+crArgumentParser::appItoa(i)+",";
					break;
				}
			}
			/*str = vipstr + "����";
			std::string str1 = price +"Ԫ��";*/

			str = "���/Ԫ��������VIP"+crArgumentParser::appItoa(vip)+"��ѿ�����";

			std::vector<float>v_i;
			ItemMap itemMap;
			rcfg::ConfigScript cfg_script(&itemMap);

			cfg_script.Add("Hypertext");
			cfg_script.Push("Hypertext");
			int index = 1;
			cfg_script.Add("Content");
			cfg_script.Push("Content", index++);
			v_i.clear();
			v_i.push_back(0.0f);
			v_i.push_back(0.0f);
			v_i.push_back(0.0f);
			v_i.push_back(255.0f);
			cfg_script.Add("Color", v_i);
			cfg_script.Add("Text", "����");
			cfg_script.Pop();

			cfg_script.Add("Content");
			cfg_script.Push("Content", index++);
			v_i.clear();
			v_i.push_back(140.0);
			v_i.push_back(40.0);
			v_i.push_back(40.0);
			v_i.push_back(255.0);
			cfg_script.Add("Color", v_i);
			cfg_script.Add("Text", price);
			cfg_script.Pop();

			cfg_script.Add("Content");
			cfg_script.Push("Content", index++);
			v_i.clear();
			v_i.push_back(0.0f);
			v_i.push_back(0.0f);
			v_i.push_back(0.0f);
			v_i.push_back(255.0f);
			cfg_script.Add("Color", v_i);
			cfg_script.Add("Text", str);
			cfg_script.Pop();

			/*cfg_script.Add("Content");
			cfg_script.Push("Content", 2);
			v_i.clear();
			v_i.push_back(140.0f);
			v_i.push_back(40.0f);
			v_i.push_back(40.0f);
			v_i.push_back(255.0f);
			cfg_script.Add("Color", v_i);
			cfg_script.Add("Text", str1);
			cfg_script.Pop();*/

			cfg_script.Pop();
			tipsText->setHypertext(cfg_script);
			//tipsText->setString(str);
			tips->setCanFocus(false);
			if(widgetText)widgetText->setColor(crVector4(255.0,255.0,0.0,255.0)/255.0);
			//����������ʾλ��
			if (m_btnindex == 0)
			{
				const crBoundingBox &btnbox = m_this->getBoundBox();
				const crMatrix &mat = m_this->getParentCanvas()->getMatrix();
				float posx = btnbox.m_min[0];
				float posy = (btnbox.m_min[1]+1.5f*(btnbox.m_max[1]-btnbox.m_min[1]));
				crVector2 mouse(crVector2(posx,posy));
				tips->setMatrix(crMatrix::translate(mouse[0],mouse[1],0.0f) * mat);
				crFilterRenderManager::getInstance()->showCanvas(tips,true);
			}
			else
			{
				const crBoundingBox &btnbox = m_this->getBoundBox();
				const crBoundingBox &tipsbox = tips->getBoundBox();
				const crMatrix &mat = m_this->getParentCanvas()->getMatrix();
				float posx = btnbox.m_min[0];
				float posy = (btnbox.m_min[1] - tipsbox.yLength()/2);
				////////////
				crVector2 mouse(crVector2(posx,posy));
				tips->setMatrix(crMatrix::translate(mouse[0],mouse[1],0.0f) * mat);
				crFilterRenderManager::getInstance()->showCanvas(tips,true);
			}

		}
	}
}

/////////////////////////////////////////
//
//crJXJUICDTimeColorTipMethod
//��������������ˢ��ʱ�����ʾ
//
/////////////////////////////////////////
crJXJUICDTimeColorTipMethod::crJXJUICDTimeColorTipMethod():
	m_this(NULL)
{
}

crJXJUICDTimeColorTipMethod::crJXJUICDTimeColorTipMethod(const crJXJUICDTimeColorTipMethod& handle):
	crMethod(handle)
{
}
void crJXJUICDTimeColorTipMethod::inputParam(int i, void *param)
{
	switch(i) 
	{
	case 0:
		if(param == 0)
		{//�ͷ�
			m_this = NULL;
		}
		break;
	case 1:
		m_this = (crWidgetNode*)param;
		break;
	}
}
void crJXJUICDTimeColorTipMethod::addParam(int i, const std::string& str)
{
}

void crJXJUICDTimeColorTipMethod::operator()(crHandle &handle)
{
	crStaticTextWidgetNode *widgetText = dynamic_cast<crStaticTextWidgetNode *>(m_this);
	if(widgetText)
	{	
		widgetText->setColor(crVector4(255.0,255.0,255.0,255.0)/255.0);
	}
}
///////////////////////////////////////
//
//crJXJXueTiaoColorMethod
//Ѫ����ɫ�ı�
//
///////////////////////////////////////
crJXJXueTiaoColorMethod::crJXJXueTiaoColorMethod():m_this(NULL){}
crJXJXueTiaoColorMethod::crJXJXueTiaoColorMethod(const crJXJXueTiaoColorMethod &handle):
	crMethod(handle),
	m_this(NULL),
	m_canvas(handle.m_canvas),
	m_progress_F1(handle.m_progress_F1),
	m_progress_F2(handle.m_progress_F2),
	m_progress_F3(handle.m_progress_F3)
{
}

void crJXJXueTiaoColorMethod::inputParam(int i, void *param)
{
	switch (i)
	{
	case 0:
		if(param == 0)
		{
			m_this = NULL;
		}
		break;
	case 1:
		m_this = (crCanvasNode*)param;
		break;
	}
}

void crJXJXueTiaoColorMethod::addParam(int i, const std::string& str)
{
	switch (i)
	{
	case 0:
		m_progress_F1 = str;
		break;
	case 1:
		m_progress_F2 = str;
		break;
	case 2:
		m_progress_F3 = str;
		break;
	case 3:
		m_progress_F1_1 = str;
		break;
	case 4:
		m_progress_F1_2 = str;
		break;
	case 5:
		m_progress_F1_3 = str;
		break;
	case 6:
		m_progress_F2_1 = str;
		break;
	case 7:
		m_progress_F2_2 = str;
		break;
	case 8:
		m_progress_F2_3 = str;
		break;
	case 9:
		m_progress_F3_1 = str;
		break;
	case 10:
		m_progress_F3_2 = str;
		break;
	case 11:
		m_progress_F3_3 = str;
		break;
	case 12:
		m_strarmyCount_F1 = str;
		break;
	case 13:
		m_strarmyCount_F2 = str;
		break;
	case 14:
		m_strarmyCount_F3 = str;
		break;
	}
}

void crJXJXueTiaoColorMethod::operator()(crHandle &handle)
{
	crFilterRenderManager::getInstance()->showCanvas(m_this,true);
	crMultiSwitch *switch_f1 = dynamic_cast<crMultiSwitch *>(m_this->getChildNode(m_progress_F1));
	crMultiSwitch *switch_f2 = dynamic_cast<crMultiSwitch *>(m_this->getChildNode(m_progress_F2));
	crMultiSwitch *switch_f3 = dynamic_cast<crMultiSwitch *>(m_this->getChildNode(m_progress_F3));

	crProgressWidgetNode *progress_f1_1 = dynamic_cast<crProgressWidgetNode *>(m_this->getWidget(m_progress_F1_1));
	crProgressWidgetNode *progress_f1_2 = dynamic_cast<crProgressWidgetNode *>(m_this->getWidget(m_progress_F1_2));
	crProgressWidgetNode *progress_f1_3 = dynamic_cast<crProgressWidgetNode *>(m_this->getWidget(m_progress_F1_3));
	crProgressWidgetNode *progress_f2_1 = dynamic_cast<crProgressWidgetNode *>(m_this->getWidget(m_progress_F2_1));
	crProgressWidgetNode *progress_f2_2 = dynamic_cast<crProgressWidgetNode *>(m_this->getWidget(m_progress_F2_2));
	crProgressWidgetNode *progress_f2_3 = dynamic_cast<crProgressWidgetNode *>(m_this->getWidget(m_progress_F2_3));
	crProgressWidgetNode *progress_f3_1 = dynamic_cast<crProgressWidgetNode *>(m_this->getWidget(m_progress_F3_1));
	crProgressWidgetNode *progress_f3_2 = dynamic_cast<crProgressWidgetNode *>(m_this->getWidget(m_progress_F3_2));
	crProgressWidgetNode *progress_f3_3 = dynamic_cast<crProgressWidgetNode *>(m_this->getWidget(m_progress_F3_3));

	crStaticTextWidgetNode * text_F1 = dynamic_cast<crStaticTextWidgetNode *>(m_this->getWidget(m_strarmyCount_F1));
	crStaticTextWidgetNode * text_F2 = dynamic_cast<crStaticTextWidgetNode *>(m_this->getWidget(m_strarmyCount_F2));
	crStaticTextWidgetNode * text_F3 = dynamic_cast<crStaticTextWidgetNode *>(m_this->getWidget(m_strarmyCount_F3));

	void *param = NULL;
	std::string iconfile1,iconfile2,iconfile3;
	/*unsigned short*/int armyCount,rtArmyCount;


	ref_ptr<crTableIO> troopsTab = crGlobalHandle::gData()->gGlobalTable(WCHDATA_JXJTroopsTab);
	crMyPlayerData *me = crMyPlayerData::getInstance();
	crRole *role = me->getLoadedRoleByIndex(0);//0,1,2
	crRole *role1 = me->getLoadedRoleByIndex(1);
	crRole *role2 = me->getLoadedRoleByIndex(2);
	int itemid1 = role->getAbstractItemID();

	crData *data = role->getDataClass();

	//int iconid = troopsTab->getTitleIndex("icon");
	//int iconid1 = troopsTab->getTitleIndex("icon��");

	//crTableIO::StrVec record1;
	//troopsTab->queryOneRecord(0,crArgumentParser::appItoa(itemid1),record1);

	char text[64];

	if (role)
	{
		crData *roledata = role->getDataClass();
		void *param;
		roledata->getParam(WCHDATA_JXJArmyCount,param);
		armyCount = *(/*unsigned short*/int *)param;
		roledata->getParam(WCHDATA_JXJRTArmyCount,param);
		rtArmyCount = *(/*unsigned short*/int *)param;

		if(switch_f1) 
		{
			float curProgress = rtArmyCount/(float)armyCount;
			if(curProgress >= 0.7)
			{
				switch_f1->setActiveSwitchSet(0);
				progress_f1_1->setProgress(rtArmyCount/(float)armyCount);
			}
			else if(curProgress < 0.7 && curProgress >= 0.3)
			{
				switch_f1->setActiveSwitchSet(1);
				progress_f1_2->setProgress(rtArmyCount/(float)armyCount);
			}
			else if(curProgress < 0.3)
			{
				switch_f1->setActiveSwitchSet(2);
				progress_f1_3->setProgress(rtArmyCount/(float)armyCount);
			}
		}

		sprintf_s(text, 64, "%d/%d\0", rtArmyCount, armyCount);
		if (text_F1)
			text_F1->setString(std::string(text));
	}
	if (role1)
	{
		crData *roledata = role1->getDataClass();
		void *param;
		roledata->getParam(WCHDATA_JXJArmyCount,param);
		armyCount = *(/*unsigned short*/int *)param;
		roledata->getParam(WCHDATA_JXJRTArmyCount,param);
		rtArmyCount = *(/*unsigned short*/int *)param;

		if(switch_f2) 
		{
			float curProgress = rtArmyCount/(float)armyCount;
			if(curProgress >= 0.7)
			{
				switch_f2->setActiveSwitchSet(0);
				progress_f2_1->setProgress(rtArmyCount/(float)armyCount);
			}
			else if(curProgress < 0.7 && curProgress >= 0.3)
			{
				switch_f2->setActiveSwitchSet(1);
				progress_f2_2->setProgress(rtArmyCount/(float)armyCount);
			}
			else if(curProgress < 0.3)
			{
				switch_f2->setActiveSwitchSet(2);
				progress_f2_3->setProgress(rtArmyCount/(float)armyCount);
			}
		}
		sprintf_s(text, 64, "%d/%d\0", rtArmyCount, armyCount);
		if (text_F2)
			text_F2->setString(std::string(text));
	}
	if (role2)
	{
		crData *roledata = role2->getDataClass();
		void *param;
		roledata->getParam(WCHDATA_JXJArmyCount,param);
		armyCount = *(/*unsigned short*/int *)param;
		roledata->getParam(WCHDATA_JXJRTArmyCount,param);
		rtArmyCount = *(/*unsigned short*/int *)param;
			
		if(switch_f3) 
		{
			float curProgress = rtArmyCount/(float)armyCount;
			if(curProgress >= 0.7)
			{
				switch_f3->setActiveSwitchSet(0);
				progress_f3_1->setProgress(rtArmyCount/(float)armyCount);
			}
			else if(curProgress < 0.7 && curProgress >= 0.3)
			{
				switch_f3->setActiveSwitchSet(1);
				progress_f3_2->setProgress(rtArmyCount/(float)armyCount);
			}
			else if(curProgress < 0.3)
			{
				switch_f3->setActiveSwitchSet(2);
				progress_f3_3->setProgress(rtArmyCount/(float)armyCount);
			}
		}
		sprintf_s(text, 64, "%d/%d\0", rtArmyCount, armyCount);
		if (text_F3)
			text_F3->setString(std::string(text));
	}		
		
}

/////////////////////////////////////////
//
//crJXJFubenDropTipsMethod
//����������ƷTips
//
/////////////////////////////////////////
crJXJFubenDropTipsMethod::crJXJFubenDropTipsMethod():
	m_this(NULL),
	m_index(0)
{
}
crJXJFubenDropTipsMethod::crJXJFubenDropTipsMethod(const crJXJFubenDropTipsMethod& handle):
	crMethod(handle),
	m_tips(handle.m_tips),
	m_name(handle.m_name),
	m_info1(handle.m_info1),
	m_info2(handle.m_info2),
	m_itemlv(handle.m_itemlv),
	m_itemicon(handle.m_itemicon),
	m_itemequipon(handle.m_itemequipon),
	m_canvas(handle.m_canvas),
	m_colorred(handle.m_colorred),
	m_infocanvas(handle.m_infocanvas),
	m_infobk(handle.m_infobk),
	m_infodi(handle.m_infodi),
	m_offsets(handle.m_offsets),
	m_index(handle.m_index),
	m_this(NULL)
{
}
void crJXJFubenDropTipsMethod::inputParam(int i, void *param)
{
	switch(i) 
	{
	case 0:
		if(param == 0)
		{//�ͷ�
			m_this = NULL;
		}
		break;
	case 1:
		m_this = (crWidgetNode*)param;
		break;
	}
}
void crJXJFubenDropTipsMethod::addParam(int i, const std::string& str)
{
	switch(i) 
	{
	case 0:
		m_tips = str;
		break;
	case 1:
		m_name = str;
		break;
	case 2:
		m_info1 = str;//�ƺ�
		break;
	case 3:
		m_info2 = str;//����
		break;
	case 4:
		m_itemlv = str;//�ȼ�
		break;
	case 5:
		m_itemicon = str;//ͼƬ
		break;
	case 6:
		m_itemequipon = str;//�Ƿ���װ��
		break;
	case 7:
		m_canvas = str;
		break;
	case 8:
		m_infocanvas = str;//���ı�������
		break;
	case 9:
		m_infobk = str;//���ı�����
		break;
	case 10:
		m_infodi = str;
		break;
	case 11:
		crArgumentParser::appAtoVec(str,m_offsets);
		break;
	case 12:
		crArgumentParser::appAtoVec(str,m_colorred);//red
		m_colorred /= 255.0f;
		break;
	case 13:
		m_index = atoi(str.c_str());
		break;
	//case 11:
	//	m_expandnum = atof(str.c_str());
	//	break;
	}
}

void crJXJFubenDropTipsMethod::operator()(crHandle &handle)
{
	crCanvasNode *tipsCanvas = crFilterRenderManager::getInstance()->findCanvas(m_tips);
	crCanvasNode *canvas = m_this->getParentCanvas();
	crCanvasNode *infocanvas = crFilterRenderManager::getInstance()->findCanvas(m_infocanvas);
	crPlayerGameData *playerData = crMyPlayerData::getInstance()->getPlayerGameData();
	if(canvas && tipsCanvas && infocanvas && playerData)
	{
		crData *canvasData = canvas->getDataClass();
		void *param;	
		if(canvasData)
		{
			crStaticTextWidgetNode *name = dynamic_cast<crStaticTextWidgetNode *>(tipsCanvas->getWidget(m_name));
			//crStaticTextWidgetNode *info1 = dynamic_cast<crStaticTextWidgetNode *>(tipsCanvas->getWidget(m_info1));
			crStaticTextWidgetNode *itemlv = dynamic_cast<crStaticTextWidgetNode *>(tipsCanvas->getWidget(m_itemlv));
			crImageBoxWidgetNode *itemicon = dynamic_cast<crImageBoxWidgetNode *>(tipsCanvas->getWidget(m_itemicon));
			crStaticTextWidgetNode *itemequipon = dynamic_cast<crStaticTextWidgetNode *>(tipsCanvas->getWidget(m_itemequipon));
			//
			crHypertextWidgetNode *info2 = dynamic_cast<crHypertextWidgetNode *>(infocanvas->getWidget(m_info2));
			crMatrixTransform *infobk = dynamic_cast<crMatrixTransform *>(infocanvas->getChildNode(m_infobk));
			crMatrixTransform *infodi = dynamic_cast<crMatrixTransform *>(infocanvas->getChildNode(m_infodi));
			crVector4f colormode[8];//white,green,blue,purple,orange
			ref_ptr<crTableIO> qualitytab = crGlobalHandle::gData()->gGlobalTable(WCHDATA_JXJQualityTab);
			crTableIO::StrVec colorrecord;
			int qualityindex = qualitytab->getTitleIndex("color");
			for (int i =0; i<8;i++)
			{
				if (qualitytab->queryOneRecord(0,crArgumentParser::appItoa(i),colorrecord) >= 0)
				{
					if (qualityindex>=0)
					{
						crArgumentParser::appAtoVec(colorrecord[qualityindex],colormode[i]);
						colormode[i] /= 255.0f;
					}
				}
			}
			crRole *mainRole = playerData->getMainRole();
			crData *roleData=NULL;
			if(mainRole)
				roleData = mainRole->getDataClass();
			if(roleData)
				roleData->getParam(WCHDATA_Level,param);
			unsigned char rolelv = *(unsigned char *)param;

			int itemid = 0;
			int equipmagic = 0;
			canvasData->getParam(WCHDATA_JXJFubenRewardDropVec,param);
			FubenDropRewardVec fubenDropItems = *(FubenDropRewardVec *)param;
			if (m_index >= fubenDropItems.size())
				return;
			itemid = fubenDropItems[m_index].second[0];
			//canvasData->getParam(WCHDATA_JXJFubenDropItemChooseId,param);
			//itemid = *(int*)param;

			ref_ptr<crTableIO> lordequiptab = crGlobalHandle::gData()->gGlobalTable(WCHDATA_JXJLordEquipTab);
			//int tnameindex = lordequiptab->getTitleIndex("�ƺ�");

			ref_ptr<crTableIO> itemtab = crGlobalHandle::gData()->gGlobalTable(WCHDATA_JXJItemTab);
			int iconindex = itemtab->getTitleIndex("icon");
			
			int nameindex = itemtab->getTitleIndex("name");
			int typeindex = itemtab->getTitleIndex("����");
			int colorindex = itemtab->getTitleIndex("Ʒ��");
			int needlvindex = itemtab->getTitleIndex("����ȼ�");
			//int shuxingindex = itemtab->getTitleIndex("��Ʒ����");
			
			crTableIO::StrVec record,lordrecord;
			if (itemtab->queryOneRecord(0,crArgumentParser::appItoa(itemid),record) >= 0)
			{
				int colormodeid = atoi(record[colorindex].c_str());
				if(name)
				{
					name->setColor(colormode[colormodeid]);
					name->setBackdropType(CRText::crText::OUTLINE);
					//name->setBackdropOffset(crVector2f(0.008f,0.008f));
					//name->setBackdropColor(colormode[colormodeid]);
					
					name->setString(record[nameindex]);
				}
				std::string file;
				if (itemlv)
				{
					if (rolelv < atoi(record[needlvindex].c_str()))//����ȼ�����ʱ��ʾ����
					{
						itemlv->setColor(FCOLOR_RED);
						if (itemequipon)
						{
							itemequipon->setColor(FCOLOR_RED);
						}
					}
					else
					{
						itemlv->setColor(colormode[0]);
						if (itemequipon)
						{
							itemequipon->setColor(colormode[1]);
						}
					}
					itemlv->setString(record[needlvindex]);
				}
				if (itemicon)
				{
					itemicon->setImageName(record[iconindex]);
				}
				if (itemequipon)
				{
					std::string str;// = "δʹ��";
					if (atoi(record[typeindex].c_str()) == IT_Equip)
					{
						str = "δװ��";
					}
					itemequipon->setString(str);
				}
				if(info2)
				{
					ItemMap itemMap;
					rcfg::ConfigScript outscript(&itemMap);
					crVector2i item(itemid,equipmagic);
					playerData->doEvent(WCH_JXJCreateItemTips,MAKECREPARAM(&item,&outscript));
					info2->setHypertext(outscript);
				}

				
				///////////��������
				float boxYlength = infobk->getChild(0)->getBoundBox().yLength()/**crDisplaySettings::instance()->getUIViewScale()[1]*/;
				info2->updateData();
				const crBoundingBox &bbox = info2->getTextObject()->getBoundBox();
				const crBoundingBox &bbox2 = info2->getBoundBox();
				float texheight = 0.0f;
				float needmove = 0.0f;
				if(bbox.valid())
				{
					texheight = bbox.yLength();
					texheight *= crDisplaySettings::instance()->getUIPixelMeter() * crDisplaySettings::instance()->getUIHeightScale()/crDisplaySettings::instance()->getUIScaleFactor();
					if(texheight<boxYlength) texheight = boxYlength;
					float scale = texheight/boxYlength;
					float needmove ;
					const crBoundingBox &tipsbb = tipsCanvas->getBoundBox();
					crVector3 centerTansTar = info2->getBound().center();

					float tmpLength = bbox2.yLength();
					if(infodi)
					{
						float diYlength = infodi->getChild(0)->getBoundBox().yLength();
						//centerTansTar[1] += 0.5f * (tmpLength - texheight) + 0.25 * diYlength;
						centerTansTar[1] += 0.5f * (tmpLength - texheight) + 0.125f * diYlength;
						//centerTansTar[1] += 0.5f * (tmpLength - texheight);
					}
					else
						centerTansTar[1] += 0.5f * (tmpLength - texheight);
					// Դ���ĵ�
					crVector3 centerTansSrc = infobk->getChild(0)->getBoundBox().center();
					// ��Դ���ĵ�ƽ�Ƶ�ԭ��
					crMatrix put_mat = crMatrix::translate(centerTansSrc);
					crMatrix inv_put = crMatrix::inverse(put_mat);
					crMatrix rotmat;
					rotmat.postMult(inv_put);
					rotmat.postMult(crMatrix::scale(1.0f,scale,1.0f));
					rotmat.postMult(crMatrix::translate(centerTansTar));
					if(infobk)infobk->setMatrix(rotmat);

					if(infodi)
					{
						float diYlength = infodi->getChild(0)->getBoundBox().yLength();
						//needmove = diYlength*0.5f*(scale-1.0f) - needmove;
						needmove = boxYlength - texheight + diYlength * 0.5;
						//needmove = boxYlength - texheight;
						infodi->setMatrix(crMatrix::translate(0.0f,needmove/*+c_tipsoffsets[2]*scale*/,0.0f));
					}
					//needmove = texheight-boxYlength;/*/crDisplaySettings::instance()->getUIViewScale()[1]*/
					//infobk->setMatrix(crMatrix::scale(1.0f,scale/*m_expandnum*/,1.0f) * crMatrix::translate(0.0f,needmove/*+c_tipsoffsets[1]*scale*/,0.0f));
					////needmove = texheight/crDisplaySettings::instance()->getUIViewScale()[1];
					//if(infodi)
					//{
					//	float diYlength = infodi->getChild(0)->getBoundBox().yLength();
					//	needmove = diYlength*0.5f*(scale-1.0f) - needmove;
					//	infodi->setMatrix(crMatrix::translate(0.0f,needmove/*+c_tipsoffsets[2]*scale*/,0.0f));
					//}
				}
				else
				{
					infobk->setMatrix(crMatrix::scale(1.0f,1.0f/*m_expandnum*/,1.0f) * crMatrix::translate(0.0f,0.0f,0.0f));
					if(infodi) infodi->setMatrix(crMatrix::translate(0.0f,0.0f,0.0f));
				}

				//������ʾ����ʾλ��
				const crMatrix &mat = m_this->getParentCanvas()->getMatrix();
				const crBoundingBox &iconbox = m_this->getBoundBox();
				const crBoundingBox &tip = tipsCanvas->getBoundBox();
				float posx = (tip.m_max[0]-tip.m_min[0])*0.5;
				float posy = (tip.m_max[1]-tip.m_min[1])*0.5;
				crVector3 pos(iconbox.m_max[0],iconbox.m_max[1],0.0f);
				pos = pos * mat;
				/////////////////////////////////////////
				crVector3 pos2(iconbox.m_min[0] ,iconbox.m_min[1],0.0f);
				pos2 = pos2 * mat;
				float posx2,posy2;
				/////////////////////////////////////////
				if (pos2[0] >= 0)
				{
					posx2 = pos2[0] - posx;
				}
				else
				{
					posx2 = pos[0] + posx;
				}
				if (pos2[1] >= 0)
				{
					posy2 = pos[1] - posy;
				}
				else
				{
					posy2 = pos2[1] + posy;
				}
				crVector2 mouse(crVector2(posx2,posy2));
				/////////////////////////////////////////

				tipsCanvas->setMatrix(crMatrix::translate(mouse[0],mouse[1],0.0f));
				tipsCanvas->setCanFocus(false);
				infocanvas->setCanFocus(false);
				//infobk->setMatrix(crMatrix::scale(1.0f,m_expandnum,1.0f) * crMatrix::translate(0,(infobk->getChild(0)->getBoundBox().yLength()*0.5f),0.0f));
				infocanvas->setMatrix(crMatrix::translate(mouse[0],mouse[1],0.0f));
				tipsCanvas->setCanvasPos(CANVAS_TOPMOST);
				infocanvas->setCanvasPos(CANVAS_TOPMOST);
				crFilterRenderManager::getInstance()->showCanvas(infocanvas,true);
				crFilterRenderManager::getInstance()->showCanvas(tipsCanvas,true);
			}			
		}
	}
}
/////////////////////////////////////////
//
//TwoLevelMenuButton
//��չ���Ķ༶��ť[�ɾ�UI]
//
/////////////////////////////////////////
//���췽������Ҫ���ݣ�button vector��crCheckBoxWidgetNode��ť�ؼ��б�,�洢��canvasData�еİ�ť�б���Ϣ������1.����[����ͼƬ��string=��������] 2.�����ȼ� 3.����װ�������洢��ťͼƬ�ı���ǰ�û�������İ�ť����
TwoLevelMenuButton::TwoLevelMenuButton(std::vector<crCheckBoxWidgetNode*> ButtonVec, CanvasIconVec *accomplishBtnIcon, crTableIO *picture_table, int index)
{
	this->ButtonVec = ButtonVec;
	this->picture_table = picture_table;	// troops data look-up table
	this->accomplishBtnIcon = accomplishBtnIcon;

	indexBtn = accomplishBtnIcon->at(index).first;//��ǰ�û��������ť��ͼƬ��������Ҫ���óɸ���
	this->index = index;

	titleOne = "1";//��ʾһ��ͼ�꣨����������һ��ͼ�꣬�����ȼ��Ƕ���ͼ�꣩��picture_table��һ��ͼ�꣬����������һ�У���parentId�е�ֵ��titleOne��Ҳ����1
}
//չ��һ��ͼ��
int TwoLevelMenuButton::expandFirstLevel(int parentIndex, int pictureTabIdIndex, crTableIO::DataVec iconRecords)
{
	//���������µ�һ��ͼ�꣬�Ͳ����¶�����ť��ɾ���ɶ���ͼ��
	if(index < accomplishBtnIcon->size() && index <accomplishBtnIcon->size() && accomplishBtnIcon->at(index).second == titleOne)
	{
		//��������һ����ťûչ��
		if(index == accomplishBtnIcon->size()-1 || (index < accomplishBtnIcon->size()-1 && accomplishBtnIcon->at(index).first != accomplishBtnIcon->at(index+1).second))
		{
			//���������ť
			for(int i = 0; i<iconRecords.size(); ++i)
			{
				int tmpIndex = this->index+1+i;
				accomplishBtnIcon->insert(accomplishBtnIcon->begin()+tmpIndex,std::make_pair(iconRecords[i][pictureTabIdIndex],iconRecords[i][parentIndex]));
			}
		}
		//����ɵĶ�����ť,���»�ȡindexֵ
		bool isChangeIndex = true;
		int eraseN = 0;
		for(CanvasIconVec::iterator itr = accomplishBtnIcon->begin(); itr != accomplishBtnIcon->end();)
		{
			if(eraseN <= 0 && (*itr).first == indexBtn)
			{
				isChangeIndex = false;
			}
			if((*itr).second != titleOne && (*itr).second != indexBtn)
			{
				itr = accomplishBtnIcon->erase(itr);
				++eraseN;
			}
			else
			{
				++itr;
			}
		}
		if(isChangeIndex)
		{
			int currIndex = index;
			currIndex -= eraseN;
			if(currIndex >=0)
			{
				index = currIndex;
			}
		}
	}
	return index;
}
//class�ڲ����������ֵ�ʹ�á���Ҫ���ݵĲ����У����ֿؼ���������Ϣ������������δ��ʾ�ģ�һ�����maxsize��ֵ�������������ʾ����������
int TwoLevelMenuButton::scrollInfo(crScrollBarWidgetNode *chapterscroll, int rowcount, int maxsize)
{	
	int row = -1;//�������ʾ�ĵ�һ����Ϣ���ܼ�¼�ĵڼ���
	if(chapterscroll && rowcount>=0)
	{
		int m_value = chapterscroll->getValue();//��ǰ���ֵ�λ�ã����ڼ���row
		if (chapterscroll)
		{
			if (rowcount <=  maxsize)//�����Ҫ��ʾ����Ϣ��������ϵ��������Ͳ���Ҫʹ�ù���
			{
				chapterscroll->setValue(0.0f);
				chapterscroll->setEnable(false);
				//chapterscroll->setRange(0,rowcount - count - maxsize);
			}
			else
			{
				chapterscroll->setEnable(true);
				chapterscroll->setRange(0,rowcount - maxsize);
				chapterscroll->setLineValue(1.0f);
				chapterscroll->setPageValue(maxsize);
			}
		}
		if (chapterscroll)//�����Ҫ���֣��ͼ���row
		{
			row = (int)(chapterscroll->getValue() + 0.5);
		}
	}
	return row;
}
//�����ť����ʾ�����ϸ��Ϣ���ɾ���塣
//��Ҫ���ݵĲ����У�accomplish_table����¼�Ҳ���ϸ��Ϣ��vector���������ʾ��Ϣ�����������titleIndex������¼���ⰴť�����һ�����Ƕ�����ť(��ȡ��ϸ��Ϣ�ķ�ʽ�в��)�����ֿؼ�
int TwoLevelMenuButton::showButtonInfo(crTableIO * accomplish_table,std::vector<ImgAndTextInfo> imgAndTextVec, int totalItemNum, int titleIndex, crScrollBarWidgetNode *chapterscroll)
{
	std::string fubenString= "����";
	int iconIndex = accomplish_table->getTitleIndex("icon");
	int idIndex = accomplish_table->getTitleIndex("id");
	int nameIndex = accomplish_table->getTitleIndex("Name");
	int infoIndex = accomplish_table->getTitleIndex("˵��");
	int textIndex = accomplish_table->getTitleIndex("HyperText");
	int pointIndex = accomplish_table->getTitleIndex("�ɾ�");
	int title1Index = accomplish_table->getTitleIndex("title1");
	int title2Index = accomplish_table->getTitleIndex("title2");
	int stepsIndex = accomplish_table->getTitleIndex("Steps");
	int beizhuIndex = accomplish_table->getTitleIndex("��ע");

	int pictureTabIdIndex = picture_table->getTitleIndex("id");
	int nameTitleIndex = picture_table->getTitleIndex("title");
	int chapterIconIndex = picture_table->getTitleIndex("chaptericon");
	int iconHighlightedIndex = picture_table->getTitleIndex("chaptericon����");
	int parentIndex = picture_table->getTitleIndex("parentId");

	if(titleIndex == 1)
	{
		titleIndex = title1Index;
	}
	else if(titleIndex == 2)
	{
		titleIndex = title2Index;
	}
	
	unsigned short id;
	CREncapsulation::crTableIO::StrVec	record, accomplishTabRecord;
	crTableIO::DataVec accomplishTabRecords;
	std::string nameTitle;
	//���ұ��ⰴť�б���Ӧ��ͼƬ
	if(picture_table->queryOneRecord(pictureTabIdIndex,indexBtn,record) >= 0)
	{
		nameTitle = record[nameTitleIndex];
	}
	//���ҳɾ͵ı�����Ϣ
	accomplish_table->queryRecords(titleIndex, nameTitle, accomplishTabRecords);
	int rowcount = accomplishTabRecords.size();

	chapterscroll->setEnable(false);//��ʼ�����ֵ�״̬Ϊ����ʾ
	int row = 0;//��ʼ��Ϊ�ӵ�һ�п�ʼ��ʾ��Ϣ
	if(accomplishTabRecords.size()>totalItemNum)
	{
		chapterscroll->setEnable(true);
		row = scrollInfo(chapterscroll, rowcount, totalItemNum);//��Ҫ������������£���õ�ǰ����ϸ�ɾ���Ϣ�ӵڼ�����ʼ��ʾ
	}
	//��������*chapterscrollֻ�������в�ͬ
	//for(int i = 0; i<accomplishTabRecords.size() && i < totalItemNum; ++i )
	//{    ImgAndTextInfo tmpImgAndText = imgAndTextVec.at(i);
	
	//�ӹ������ϵ�����Ŀ��ʼ��ʾ��ϸ��Ϣ  if( (row����-1��ʾ����Ҫ��������������Ҫ��ʾ�ļ�¼���С����������ʾ������) ���ߣ���Ҫ����������ô�������ϵ��׾�Ҫֹͣ��
	if((row <= 0 && accomplishTabRecords.size()<=totalItemNum)|| row < accomplishTabRecords.size() - totalItemNum + 1 )
	{
		for(int i = row; i < row + totalItemNum; ++i )
		{
			//�����ǰ��accomplishTabRecords��Ϣ�������ڵ�����������ʾ������
			if(i < accomplishTabRecords.size())
			{
				//tmpImgAndText�Ǵ洢��ϸ��Ϣ��ʾ�Ŀؼ��б������ڳɾ�������ǰ���һ��ͼƬ����ĸ���̬�ı���
				ImgAndTextInfo tmpImgAndText = imgAndTextVec.at(i - row);
				std::vector<crStaticTextWidgetNode *>tmpTextVec = tmpImgAndText.getItemVec();
				std::string tmpStr = accomplishTabRecords[i][nameIndex];
				crStaticTextWidgetNode *tmpText = tmpTextVec.at(0);
				crMultiSwitch *backboardswitch = tmpImgAndText.getItemSw();
				crNode *childnode = tmpImgAndText.getChildNode();

				//��ʾ���ֺ���ɫ����
				if(tmpText)
				{
					tmpText->setColor(crVector4(230.0,150.0,40.0,255.0)/255.0);
					tmpText->setString(tmpStr);
				}

				tmpStr = accomplishTabRecords[i][infoIndex];
				tmpText = tmpTextVec.at(1);
				if(tmpText)
				{
					tmpText->setColor(crVector4(230.0,150.0,40.0,255.0)/255.0);
					tmpText->setString(tmpStr);
				}

				tmpStr = " "+accomplishTabRecords[i][pointIndex];
				tmpText = tmpTextVec.at(4);
				if(tmpText)
				{
					//tmpText->setColor(crVector4(230.0,150.0,40.0,255.0)/255.0);
					tmpText->setString(tmpStr);
				}

				id = atoi(accomplishTabRecords[i][idIndex].c_str());
				std::string notestr = accomplishTabRecords[i][beizhuIndex];

				stepFubenShow(id, tmpText, tmpTextVec, backboardswitch,notestr);

				crImageBoxWidgetNode *tmpImg = tmpImgAndText.getItemImg();
				if(tmpImg)
				{
					tmpImg->setVisiable(true);
					tmpImg->setImageName(accomplishTabRecords[i][iconIndex]);
				}
				if(childnode)
				{
					childnode->setVisiable(true);
				}
			}
			else//�����Ҫ��ʾ������ ���� ��������ɵ�������ʣ��������Ŀ��ʾ�յı���ͼƬ
			{
				imgAndTextVec.at(i - row).clearItem("T_Achievement_Backboard.img");//ʣ����Ŀ�ı���ͼ�����Դӽű�����
			}
		}
	}
	return 0;
}
//�ɾ͵Ĳ�����ʾ���ɾ���塣��Ҫ�Ĳ����У���ʾ������ı���Ŀؼ����洢�ɾ���ϸ��Ϣ �ؼ� ��vector
int TwoLevelMenuButton::stepFubenShow(int id, crStaticTextWidgetNode *tmpText, std::vector<crStaticTextWidgetNode *> tmpTextVec,crMultiSwitch *tempSwitch,std::string& notestr)
{
	std::string tmpStr;
	void *param;
	unsigned int step =  0;
	unsigned int stepCount = 0;
	bool AchivementComplete;

	crPlayerGameData *playerData = crMyPlayerData::getInstance()->getPlayerGameData();
	if(playerData)
	{
		crRole *mainRole = playerData->getMainRole();
		if(mainRole)
		{
			crJXJAccomplish *mainRoleAccomplish;
			crData *mainRoleData = mainRole->getDataClass();
			//��AccomplishMap�ж�ȡ�ɾͲ�����Ϣ
			mainRoleData->getParam(WCHDATA_JXJAccomplishMap,param);
			AccomplishMap *accomplishMap = (AccomplishMap*)param;
			//for(AccomplishMap::iterator itr = accomplishMap->begin(); itr != accomplishMap->end(); ++itr)
			AccomplishMap::iterator itr = accomplishMap->find(id);
			if(itr != accomplishMap->end())
			{
				mainRoleAccomplish  = itr->second.get();
				AchivementComplete = itr->second->getComplete();
				stepCount = itr->second->getStepCount();
				if (stepCount == 255)
				{
					CRCore::crVector4i notevec;
					crArgumentParser::appAtoVec(notestr,notevec);
					stepCount = notevec[0];
					step = itr->second->getLardgeStep();
				}
				else
				{
					step = itr->second->getStep();
				}
			}
		}
	}
	//if (stepCount >= 255)
	//{
	//	CRCore::crVector4i notevec;
	//	crArgumentParser::appAtoVec(notestr,notevec);
	//	stepCount = notevec[0];
	//	if(playerData && playerData->getDataClass())
	//	{
	//		ref_ptr<crData> playergdata = playerData->getDataClass();
	//		if (notevec[1] > 0)
	//		{
	//			if(notevec[2] == 0)
	//			{
	//				playergdata->getParam(notevec[1],param);
	//				step = *(int *)param;
	//			}
	//			else if(notevec[2] <= 4)
	//			{
	//				playergdata->getParam(notevec[1],param);
	//				crVector4i cbingxi = *(crVector4i *)param;
	//				step = cbingxi[notevec[2] - 1];
	//			}
	//			else
	//			{
	//				playergdata->getParam(notevec[1],param);
	//				std::map<int,CRCore::crVector3i> troopsinfomap = *(std::map<int,CRCore::crVector3i> *)param;
	//				std::map<int,CRCore::crVector3i>::iterator troopinfoitr = troopsinfomap.find(notevec[2]);
	//				if(troopinfoitr != troopsinfomap.end())
	//					step = troopinfoitr->second[notevec[3]];
	//			}
	//		}
	//	}
	//}

	if(AchivementComplete)//����ɾʹ��
	{
		tmpStr = crArgumentParser::appItoa(stepCount)+"/"+crArgumentParser::appItoa(stepCount);
		tmpText = tmpTextVec.at(2);
		tmpText->setColor(crVector4(230.0, 150.0, 40.0, 255.0) / 255.0);
		tmpText->setString(tmpStr);
		//tmpStr = "";
		//tmpText = tmpTextVec.at(2);
		//tmpText->setString(tmpStr);

		tmpStr = "�����";
		tmpText = tmpTextVec.at(3);
		tmpText->setColor(crVector4(230.0,150.0,40.0,255.0)/255.0);
		tmpText->setString(tmpStr);
		if (tempSwitch)
		{
			tempSwitch->setActiveSwitchSet(1);
		}
	}
	else//����ɾ�δ���
	{
		tmpStr = crArgumentParser::appItoa(step)+"/"+crArgumentParser::appItoa(stepCount);
		tmpText = tmpTextVec.at(2);
		tmpText->setColor(crVector4(230.0,150.0,40.0,255.0)/255.0);
		tmpText->setString(tmpStr);

		tmpStr = "δ���";
		tmpText = tmpTextVec.at(3);
		tmpText->setColor(crVector4(230.0,150.0,40.0,255.0)/255.0);
		tmpText->setString(tmpStr);
		if (tempSwitch)
		{
			tempSwitch->setActiveSwitchSet(0);
		}
	}
	return 0;
}
//��picture table���ȡ��Ҫ��ʾ������ϵİ�ťͼƬ
int TwoLevelMenuButton::showButtonImg()
{
	CREncapsulation::crTableIO::StrVec	recordPicture;
	int iconIndex = picture_table->getTitleIndex("chaptericon");
	int iconHighlightedIndex = picture_table->getTitleIndex("chaptericon����");
	
	for(int i = 0;  i<accomplishBtnIcon->size() && i<ButtonVec.size(); ++i)
	{
		int pictureTabIdIndex = picture_table->getTitleIndex("id");
		if(picture_table->queryOneRecord(pictureTabIdIndex, accomplishBtnIcon->at(i).first, recordPicture) >= 0)
		{
			crStateSet *state_set = dynamic_cast<crObject *>(dynamic_cast<crGroup *>((ButtonVec[i]->getChild(0)))->getChild(0))->getDrawable(0)->getStateSet();
			if(state_set)
			{
				crTexture2D *texture_2d = dynamic_cast<CRCore::crTexture2D *>(state_set->getTextureAttribute(0,crStateAttribute::TEXTURE));
				if(texture_2d)
				{
					//��������ťû��ѡ�У�����ʾ��ͨͼƬ
					if(accomplishBtnIcon->at(i).first != indexBtn)
					{
						texture_2d->setImage(0,texture_2d->getImageDataRequestHandler()->requestImageFile(recordPicture[iconIndex],texture_2d));
					}
					else//�����ѡ���ˣ���ʾ������ťͼƬ
					{
						//ButtonVec.at(i)->select(1);
						texture_2d->setImage(0,texture_2d->getImageDataRequestHandler()->requestImageFile(recordPicture[iconHighlightedIndex],texture_2d));
					}
				}
			}
		}
	}
	for(int i = 0; i<accomplishBtnIcon->size() && i< ButtonVec.size(); ++i)
	{
		ButtonVec.at(i)->setEnable(true);
	}
	for(int i = accomplishBtnIcon->size(); i < ButtonVec.size(); ++i)
	{
		ButtonVec.at(i)->setEnable(false);
	}
	return 0;
}
/////////////////////////////////////////
//
//ImgAndTextInfo
//һ�������Ϣ[�ɾ�UI]
//
/////////////////////////////////////////
//�ڳɾ�����У������洢��һ��ͼƬ�ؼ�crImageBoxWidgetNode�����ĸ���̬�ı���crStaticTextWidgetNode��std::vector<ImgAndTextInfo>��size��5���洢������Ϣ
ImgAndTextInfo::ImgAndTextInfo(crNode *childnodex,crImageBoxWidgetNode *itemImg, std::vector<crStaticTextWidgetNode*> itemVct,crMultiSwitch *itemSw)
{
	this->itemImg = itemImg;
	this->itemVct = itemVct;
	this->m_backboardsw = itemSw;
	this->childnode = childnodex;
}
crImageBoxWidgetNode* ImgAndTextInfo::getItemImg()
{
	return this->itemImg;
}
std::vector<crStaticTextWidgetNode*> ImgAndTextInfo::getItemVec()
{
	return this->itemVct;
}
crMultiSwitch* ImgAndTextInfo::getItemSw()
{
	return this->m_backboardsw;
}
crNode* ImgAndTextInfo::getChildNode()
{
	return this->childnode;
}
//������һ����ʾ��Ϣ��ͼƬ���óɱ���ͼƬ�������ı�������Ϊ�ա���Ҫ���ݵĲ���������ͼ
int  ImgAndTextInfo::clearItem(std::string backgroundImg)
{
	std::string clearStr = "";
	for(int num = 0; num < itemVct.size(); ++num)
	{
		crStaticTextWidgetNode *tmpText = itemVct.at(num);
		if(tmpText)
		{
			tmpText->setString(clearStr);
		}
	}
	if(itemImg)
	{
		itemImg->setVisiable(false);
		itemImg->setImageName(backgroundImg);
	}
	if (m_backboardsw)
	{
		m_backboardsw->setActiveSwitchSet(2);
	}
	if(childnode)
	{
		childnode->setVisiable(false);
	}
	return 0;
}
/////////////////////////////////////////
//
//crJXJUIAchievementUpdateMethod
//�ɾ������ϸ��Ϣ��ʾ[UI]
//
/////////////////////////////////////////
crJXJUIAchievementUpdateMethod::crJXJUIAchievementUpdateMethod():
	m_totalBtnNum(0),
	m_totalItemNum(0),
	m_OneItemNum(0)
{
}
crJXJUIAchievementUpdateMethod::crJXJUIAchievementUpdateMethod(const crJXJUIAchievementUpdateMethod& handle):
	crMethod(handle),
	m_OneItemNum(handle.m_OneItemNum),
	m_totalBtnNum(handle.m_totalBtnNum),
	m_totalItemNum(handle.m_totalItemNum),
	m_progressbar(handle.m_progressbar)
{
	for(int i = 0; i < 25; ++i)
	{
		if(i < 10)
		{
			m_Button[i] = handle.m_Button[i];
		}
		if(i < 5)
		{
			m_icon[i] = handle.m_icon[i];
			m_backbordsw[i] = handle.m_backbordsw[i];
		}
		if(i < 3)
		{
			m_infoinput[i] = handle.m_infoinput[i];
		}
		m_input[i] = handle.m_input[i];
	}
}
void crJXJUIAchievementUpdateMethod::inputParam(int i, void *param)
{
	switch(i) 
	{
	case 0:
		if(param == 0)
		{//�ͷ�
			m_this = NULL;
		}
		break;
	case 1:
		m_this = (crCanvasNode*)param;
		break;
	}
}
void crJXJUIAchievementUpdateMethod::addParam(int i, const std::string& str)
{
	switch(i) 
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		m_Button[i] = str;
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
		m_icon[i-10] = str;
		break;
	case 15:
	case 16:
	case 17:
	case 18:
	case 19:
	case 20:
	case 21:
	case 22:
	case 23:
	case 24:
	case 25:
	case 26:
	case 27:
	case 28:
	case 29:
	case 30:
	case 31:
	case 32:
	case 33:
	case 34:
	case 35:
	case 36:
	case 37:
	case 38:
	case 39:
		m_input[i-15] = str;
		break;
	case 40:
		m_totalBtnNum = atoi(str.c_str());
		break;
	case 41:
		m_totalItemNum = atoi(str.c_str());
		break;
	case 42:
		m_OneItemNum = atoi(str.c_str());
		break;
	case 43:
		m_scroll = str;
		break;
	case 44:
	case 45:
	case 46:
		m_infoinput[i - 44] = str;
		break;
	case 47:
		m_progressbar = str;
		break;
	case 48:
	case 49:
	case 50:
	case 51:
	case 52:
		m_backbordsw[i - 48] = str;
		break;
	}
}
void crJXJUIAchievementUpdateMethod::operator()(crHandle &handle)
{
	crPlayerGameData *playerData = crMyPlayerData::getInstance()->getPlayerGameData();
	if(playerData)
	{
		crRole *mainRole = playerData->getMainRole();
		if(mainRole)
		{
			crData *mainRoleData = mainRole->getDataClass();
			if (mainRoleData && m_this)
			{
				int stepCount = -1;
				int step = -1;
				int stepID = -1;
				int index = 0;
				crTableIO::StrVec recordPicture, accomplishTabRecord;
				crTableIO::DataVec iconRecords;
				ref_ptr<crTableIO> picture_table = CRNetApp::crGlobalHandle::gData()->gGlobalTable(WCHDATA_JXJAccomplishPictureTab);
				int parentIndex = picture_table->getTitleIndex("parentId");
				int pictureTabIdIndex = picture_table->getTitleIndex("id");
				ref_ptr<crTableIO> accomplish_table = CRNetApp::crGlobalHandle::gData()->gGlobalTable(WCHDATA_JXJAccomplishTab);
				int iconIndex = accomplish_table->getTitleIndex("icon");
				int accomplishidIndex = accomplish_table->getTitleIndex("id");
				accomplish_table->queryOneRecord(accomplishidIndex, crArgumentParser::appItoa(0), accomplishTabRecord);
				//�ɾ������ϸ��Ϣ�Ŀؼ� vector
				std::vector<crCheckBoxWidgetNode*> ButtonVec;
				crImageBoxWidgetNode *itemImg;
				ref_ptr<crMultiSwitch> backboardsw = NULL;
				crWidgetNode *childnode = NULL;
				std::vector<ImgAndTextInfo> imgAndTextVec;
				for(int i = 0; i < m_totalBtnNum; ++i)
				{
					crCheckBoxWidgetNode *button = dynamic_cast<crCheckBoxWidgetNode *>(m_this->getWidget(m_Button[i]));
					if(button)ButtonVec.push_back(button);
					ButtonVec.at(i)->select(0);
				}
				for(int i = 0; i < m_totalItemNum; ++i)
				{
					std::vector<crStaticTextWidgetNode*> itemVct;
					itemImg =  dynamic_cast<crImageBoxWidgetNode *>(m_this->getWidget(m_icon[i]));
					backboardsw =  dynamic_cast<crMultiSwitch *>(m_this->getChildNode(m_backbordsw[i]));
					for(int n = 0; n < m_OneItemNum; ++n)
					{
						int tmpN = i * m_OneItemNum + n;
						crStaticTextWidgetNode *item = dynamic_cast<crStaticTextWidgetNode *>(m_this->getWidget(m_input[tmpN]));
						if(item)
							itemVct.push_back(item);
					}
					if(itemImg)
					{
						imgAndTextVec.push_back(ImgAndTextInfo(childnode,itemImg, itemVct,backboardsw.get()));
						//����Ҳ����������ͼƬ
						itemImg->setImageName("T_Achievement_Backboard.img");
					}
				}
			
				std::string titleOne = "1";
				CanvasIconVec *accomplishBtnIcon;
				crData *canvasData = m_this->getDataClass();
				if (canvasData)
				{
					void *param;
					canvasData->getParam(WCHDATA_JXJAccomplishCanvasIcon,param);
					accomplishBtnIcon = (CanvasIconVec*) param;
					canvasData->getParam(WCHDATA_JXJAccomplishBtnIndex,param);
					index = *(int *)param;
				}
				if(accomplishBtnIcon->size()>0)
				{
					TwoLevelMenuButton menuButton(ButtonVec, accomplishBtnIcon, picture_table.get(), index);
					picture_table->queryRecords(parentIndex,accomplishBtnIcon->at(index).first,iconRecords);//parentIndex�к���һ�����ݵ���accomplishBtnIcon.at(m_index).first�������д���records��
					
					crScrollBarWidgetNode *chapterscroll = dynamic_cast<crScrollBarWidgetNode *>(m_this->getWidget(m_scroll));
					
					int index = menuButton.expandFirstLevel(parentIndex, pictureTabIdIndex, iconRecords);
	
					if(m_this)
					{
						crData *canvasData = m_this->getDataClass();
						if(canvasData)
						{
							canvasData->inputParam(WCHDATA_JXJAccomplishBtnIndex,&index);
						}
					}
					//�����һ����ť
					if(index < accomplishBtnIcon->size() && index <accomplishBtnIcon->size() && accomplishBtnIcon->at(index).second == titleOne)
					{
						if(iconRecords.size() == 0)//������һ����ťû�ж�����ť����չ��һ����Ϣ
						{
							//menuButton.expandFirstLevel(parentIndex, pictureTabIdIndex, iconRecords);
							menuButton.showButtonInfo(accomplish_table.get(), imgAndTextVec, m_totalItemNum, 1, chapterscroll);
						}	
						if(iconRecords.size() > 0)//������һ����ť�ж�����ť��������Ҳ���Ϣ
						{
							menuButton.showButtonInfo(accomplish_table.get(), imgAndTextVec, m_totalItemNum, 2, chapterscroll);
							if((index+1) < ButtonVec.size() && (index+1) <accomplishBtnIcon->size())
							{
								TwoLevelMenuButton menuButton2(ButtonVec, accomplishBtnIcon, picture_table.get(), index+1);
								menuButton2.showButtonInfo(accomplish_table.get(), imgAndTextVec, m_totalItemNum, 2, chapterscroll);
							}
						}
					}
					//�������˶�����ť��ֱ����ʾ��ϸ��Ϣ
					else if(index < ButtonVec.size() && index <accomplishBtnIcon->size() && accomplishBtnIcon->at(index).second != titleOne )
					{
						menuButton.showButtonInfo(accomplish_table.get(), imgAndTextVec, m_totalItemNum, 2, chapterscroll);
					}
					//��ʾ��ťͼƬ
					menuButton.showButtonImg();
				}	

				//�ܳɾ͵㣬��ɳɾ�������ɽ��ȣ���������ʾ
				int chengjiupointindex = accomplish_table->getTitleIndex("�ɾ�");
				crTableIO::StrVec chengjiurecord;
				std::string tmpStr;
				void *param;
				bool AchivementComplete;
				int totalchengjiupoint = 0;
				int completecount = 0;
				int chengjiutotalcount = 0;
				int completepercent = 0;

				ref_ptr<crProgressWidgetNode> progressbar = dynamic_cast<crProgressWidgetNode *>(m_this->getWidget(m_progressbar));
				ref_ptr<crStaticTextWidgetNode> infoinput[3] = {NULL};
				for (int i = 0; i < 3; ++i)
				{
					infoinput[i] = dynamic_cast<crStaticTextWidgetNode *>(m_this->getWidget(m_infoinput[i]));
					if(infoinput[i].valid())infoinput[i]->clearString();
				}
				mainRoleData->getParam(WCHDATA_JXJAccomplishMap,param);
				AccomplishMap *accomplishMap = (AccomplishMap*)param;
				for (AccomplishMap::iterator itr = accomplishMap->begin();
					itr != accomplishMap->end();
					++itr)
				{
					AchivementComplete = itr->second->isComplete();
					if(AchivementComplete && accomplish_table->queryOneRecord(0,crArgumentParser::appItoa(itr->first),chengjiurecord) >= 0)
					{
						completecount++;
						totalchengjiupoint += atoi(chengjiurecord[chengjiupointindex].c_str());
					}
				}
				chengjiutotalcount = accomplish_table->getRowCount();
				if (chengjiutotalcount <= 0)
				{
					chengjiutotalcount = 1;
				}
				completepercent = completecount * 100 / chengjiutotalcount;
				if (infoinput[0].valid())
				{
					infoinput[0]->setString(crArgumentParser::appItoa(totalchengjiupoint));
				}
				if (infoinput[1].valid())
				{
					infoinput[1]->setString(crArgumentParser::appItoa(completecount) + "/" + crArgumentParser::appItoa(chengjiutotalcount));
				}
				if (infoinput[2].valid())
				{
					infoinput[2]->setString(crArgumentParser::appItoa(completepercent) + "%");
				}
				if (progressbar.valid())
				{
					progressbar->setProgress((float)completepercent/100.0f);
				}
			}
		}
	}
}

/////////////////////////////////////////
//
//crJXJUIAchievementUpdateNewMethod
//�ɾ������ϸ��Ϣ��ʾ[UI]�°�
//
/////////////////////////////////////////
crJXJUIAchievementUpdateNewMethod::crJXJUIAchievementUpdateNewMethod():
	m_totalBtnNum(0),
	m_totalItemNum(0),
	m_OneItemNum(0)
{
}
crJXJUIAchievementUpdateNewMethod::crJXJUIAchievementUpdateNewMethod(const crJXJUIAchievementUpdateNewMethod& handle):
	crMethod(handle),
	m_OneItemNum(handle.m_OneItemNum),
	m_totalBtnNum(handle.m_totalBtnNum),
	m_totalItemNum(handle.m_totalItemNum),
	m_shopscroll(handle.m_shopscroll),
	m_zonglansw(handle.m_zonglansw),
	m_guozhanid(handle.m_guozhanid),
	m_lingzhuid(handle.m_lingzhuid),
	m_fengdiid(handle.m_fengdiid),
	m_jiangkaid(handle.m_jiangkaid),
	m_fubenid(handle.m_fubenid),
	m_strVipImage(handle.m_strVipImage),
	m_strFoodImage(handle.m_strFoodImage),
	m_strWoodImage(handle.m_strWoodImage),
	m_strIronImage(handle.m_strIronImage),
	m_strHorseImage(handle.m_strHorseImage),
	m_strCopperImage(handle.m_strCopperImage),
	m_strGiftGoldImage(handle.m_strGiftGoldImage),
	m_strExpImage(handle.m_strExpImage),
	m_strAchievementImage(handle.m_strAchievementImage),
	m_strContributeImage(handle.m_strContributeImage),
	m_strExploitImage(handle.m_strExploitImage),
	m_strZhanquanImage(handle.m_strZhanquanImage)
{
	for(int i = 0; i < 35; ++i)
	{
		if(i < 11)
		{
			m_Button[i] = handle.m_Button[i];
		}
		if(i < 7)
		{
			m_icon[i] = handle.m_icon[i];
			m_backbordsw[i] = handle.m_backbordsw[i];
		}
		if(i < 2)
		{
			m_infoinput[i] = handle.m_infoinput[i];
		}
		if (i < 10)
		{
			m_buybtn[i] = handle.m_buybtn[i];
			m_pricetext[i] = handle.m_pricetext[i];
			m_imagebox[i] = handle.m_imagebox[i];
			m_commodityc[i] = handle.m_commodityc[i];
		}
		if (i < 6)
		{
			m_progressbar[i] = handle.m_progressbar[i];
			m_progresstext[i] = handle.m_progresstext[i];
		}
		if (i < 5)
		{
			m_dalytarget[i] = handle.m_dalytarget[i];
		}
		m_input[i] = handle.m_input[i];
	}
}
void crJXJUIAchievementUpdateNewMethod::inputParam(int i, void *param)
{
	switch(i) 
	{
	case 0:
		if(param == 0)
		{//�ͷ�
			m_this = NULL;
		}
		break;
	case 1:
		m_this = (crCanvasNode*)param;
		break;
	}
}
void crJXJUIAchievementUpdateNewMethod::addParam(int i, const std::string& str)
{
	switch(i) 
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
		m_Button[i] = str;
		break;
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
	case 16:
	case 17:
		m_icon[i-11] = str;
		break;
	case 18:
	case 19:
	case 20:
	case 21:
	case 22:
	case 23:
	case 24:
	case 25:
	case 26:
	case 27:
	case 28:
	case 29:
	case 30:
	case 31:
	case 32:
	case 33:
	case 34:
	case 35:
	case 36:
	case 37:
	case 38:
	case 39:
	case 40:
	case 41:
	case 42:
	case 43:
	case 44:
	case 45:
	case 46:
	case 47:
	case 48:
	case 49:
	case 50:
	case 51:
	case 52:
		m_input[i-18] = str;
		break;
	case 53:
		m_totalBtnNum = atoi(str.c_str());
		break;
	case 54:
		m_totalItemNum = atoi(str.c_str());
		break;
	case 55:
		m_OneItemNum = atoi(str.c_str());
		break;
	case 56:
		m_scroll = str;
		break;
	case 57:
	case 58:
		m_infoinput[i - 57] = str;
		break;
	case 59:
	case 60:
	case 61:
	case 62:
	case 63:
	case 64:
	case 65:
		m_backbordsw[i - 59] = str;
		break;
	case 66:
	case 67:
	case 68:
	case 69:
	case 70:
	case 71:
		m_progressbar[i - 66] = str;
		break;
	case 72:
	case 73:
	case 74:
	case 75:
	case 76:
	case 77:
		m_progresstext[i - 72] = str;
		break;
	case 78:
	case 79:
	case 80:
	case 81:
	case 82:
		m_dalytarget[i - 78] = str;
		break;
	case 83:
	case 84:
	case 85:
	case 86:
	case 87:
	case 88:
	case 89:
	case 90:
	case 91:
	case 92:
		m_buybtn[i - 83] = str;
		break;
	case 93:
	case 94:
	case 95:
	case 96:
	case 97:
	case 98:
	case 99:
	case 100:
	case 101:
	case 102:
		m_pricetext[i - 93] = str;
		break;
	case 103:
	case 104:
	case 105:
	case 106:
	case 107:
	case 108:
	case 109:
	case 110:
	case 111:
	case 112:
		m_imagebox[i - 103] = str;
		break;
	case 113:
		m_shopscroll = str;
		break;
	case 114:
		m_zonglansw = str;
		break;
	case 115:
		crArgumentParser::appAtoVec(str,m_guozhanid);
		break;
	case 116:
		crArgumentParser::appAtoVec(str,m_lingzhuid);
		break;
	case 117:
		crArgumentParser::appAtoVec(str,m_fengdiid);
		break;
	case 118:
		crArgumentParser::appAtoVec(str,m_jiangkaid);
		break;
	case 119:
		crArgumentParser::appAtoVec(str,m_fubenid);
		break;
	case 120: 
		m_strFoodImage = str;//����
		break;
	case 121:
		m_strWoodImage = str;//ľ��
		break;
	case 122:
		m_strIronImage = str;//����
		break;
	case 123: 
		m_strHorseImage = str;//��ƥ
		break;
	case 124: 
		m_strCopperImage = str;//ͭǮ
		break;
	case 125: 
		m_strExpImage = str;//����
		break;
	case 126: 
		m_strExploitImage = str;//��ѫ
		break;
	case 127: 
		m_strGiftGoldImage = str;//���
		break;
	case 128: 
		m_strContributeImage = str;//���ҹ���
		break;
	case 129: 
		m_strAchievementImage = str;//ս��
		break;
	case 130: 
		m_strVipImage = str;//vip����
		break;
	case 131: 
		m_strZhanquanImage = str;//սȯ
		break;
	case 132:
	case 133:
	case 134:
	case 135:
	case 136:
	case 137:
	case 138:
		m_childnode[i - 132] = str;
		break;
	case 139:
	case 140:
	case 141:
	case 142:
	case 143:
	case 144:
	case 145:
	case 146:
	case 147:
	case 148:
		m_commodityc[i - 139] = str;
		break;
		
	}
}
void crJXJUIAchievementUpdateNewMethod::operator()(crHandle &handle)
{
	crPlayerGameData *playerData = crMyPlayerData::getInstance()->getPlayerGameData();
	if(playerData)
	{
		crRole *mainRole = playerData->getMainRole();
		if(mainRole)
		{
			crData *mainRoleData = mainRole->getDataClass();
			if (mainRoleData)
			{
				crData *data = playerData->getDataClass();
				void *param;
				CRCore::ScopedLock<crData> lock1(*data);
				CRCore::ScopedLock<crData> lock2(*mainRoleData);
				data->getParam(WCHDATA_JXJAchieveShopMap,param);
				AchieveShopMap *achieveShopMap = (AchieveShopMap *)param;

				int stepCount = -1;
				int step = -1;
				int stepID = -1;
				int index = 0;
				crTableIO::StrVec recordPicture, accomplishTabRecord;
				crTableIO::DataVec iconRecords;
				ref_ptr<crTableIO> picture_table = CRNetApp::crGlobalHandle::gData()->gGlobalTable(WCHDATA_JXJAccomplishPictureTab);
				int parentIndex = picture_table->getTitleIndex("parentId");
				int pictureTabIdIndex = picture_table->getTitleIndex("id");
				ref_ptr<crTableIO> accomplish_table = CRNetApp::crGlobalHandle::gData()->gGlobalTable(WCHDATA_JXJAccomplishTab);
				int iconIndex = accomplish_table->getTitleIndex("icon");
				int accomplishidIndex = accomplish_table->getTitleIndex("id");
				accomplish_table->queryOneRecord(accomplishidIndex, crArgumentParser::appItoa(0), accomplishTabRecord);
				//�ɾ������ϸ��Ϣ�Ŀؼ� vector
				std::vector<crCheckBoxWidgetNode*> ButtonVec;
				crImageBoxWidgetNode *itemImg;
				ref_ptr<crMultiSwitch> backboardsw = NULL;
				crNode *childnode;
				std::vector<ImgAndTextInfo> imgAndTextVec;
				for(int i = 0; i < m_totalBtnNum; ++i)
				{
					crCheckBoxWidgetNode *button = dynamic_cast<crCheckBoxWidgetNode *>(m_this->getWidget(m_Button[i]));
					if(button)ButtonVec.push_back(button);
					ButtonVec.at(i)->select(0);
				}
				for(int i = 0; i < m_totalItemNum; ++i)
				{
					std::vector<crStaticTextWidgetNode*> itemVct;
					childnode = dynamic_cast<crNode *>(m_this->getChildNode(m_childnode[i]));
					itemImg =  dynamic_cast<crImageBoxWidgetNode *>(m_this->getWidget(m_icon[i]));
					backboardsw =  dynamic_cast<crMultiSwitch *>(m_this->getChildNode(m_backbordsw[i]));
					for(int n = 0; n < m_OneItemNum; ++n)
					{
						int tmpN = i * m_OneItemNum + n;
						crStaticTextWidgetNode *item = dynamic_cast<crStaticTextWidgetNode *>(m_this->getWidget(m_input[tmpN]));
						if(item)
							itemVct.push_back(item);
					}
					if(itemImg)
					{
						imgAndTextVec.push_back(ImgAndTextInfo(childnode,itemImg, itemVct,backboardsw.get()));
						//����Ҳ����������ͼƬ
						itemImg->setImageName("T_Achievement_Backboard.img");
						itemImg->setVisiable(false);
					}
				}

				std::string titleOne = "1";
				CanvasIconVec *accomplishBtnIcon;
				crData *canvasData = m_this->getDataClass();
				if (canvasData)
				{
					void *param;
					canvasData->getParam(WCHDATA_JXJAccomplishCanvasIcon,param);
					accomplishBtnIcon = (CanvasIconVec*) param;
					canvasData->getParam(WCHDATA_JXJAccomplishBtnIndex,param);
					index = *(int *)param;
				}

				ref_ptr<crMultiSwitch> zonglansw = dynamic_cast<crMultiSwitch *>(m_this->getChildNode(m_zonglansw));
				if (zonglansw.valid())
				{
					if(index == 0)
						zonglansw->setActiveSwitchSet(1);
					else 
						zonglansw->setActiveSwitchSet(0);
				}

				if (index != 0)
				{
					if(accomplishBtnIcon->size()>0)
					{
						TwoLevelMenuButton menuButton(ButtonVec, accomplishBtnIcon, picture_table.get(), index);
						picture_table->queryRecords(parentIndex,accomplishBtnIcon->at(index).first,iconRecords);//parentIndex�к���һ�����ݵ���accomplishBtnIcon.at(m_index).first�������д���records��

						crScrollBarWidgetNode *chapterscroll = dynamic_cast<crScrollBarWidgetNode *>(m_this->getWidget(m_scroll));

						int index = menuButton.expandFirstLevel(parentIndex, pictureTabIdIndex, iconRecords);

						if(m_this)
						{
							crData *canvasData = m_this->getDataClass();
							if(canvasData)
							{
								canvasData->inputParam(WCHDATA_JXJAccomplishBtnIndex,&index);
							}
						}
						//�����һ����ť
						if(index < accomplishBtnIcon->size() && index <accomplishBtnIcon->size() && accomplishBtnIcon->at(index).second == titleOne)
						{
							if(iconRecords.size() == 0)//������һ����ťû�ж�����ť����չ��һ����Ϣ
							{
								//menuButton.expandFirstLevel(parentIndex, pictureTabIdIndex, iconRecords);
								menuButton.showButtonInfo(accomplish_table.get(), imgAndTextVec, m_totalItemNum, 1, chapterscroll);
							}	
							if(iconRecords.size() > 0)//������һ����ť�ж�����ť��������Ҳ���Ϣ
							{
								menuButton.showButtonInfo(accomplish_table.get(), imgAndTextVec, m_totalItemNum, 2, chapterscroll);
								if((index+1) < ButtonVec.size() && (index+1) <accomplishBtnIcon->size())
								{
									TwoLevelMenuButton menuButton2(ButtonVec, accomplishBtnIcon, picture_table.get(), index+1);
									menuButton2.showButtonInfo(accomplish_table.get(), imgAndTextVec, m_totalItemNum, 2, chapterscroll);
								}
							}
						}
						//�������˶�����ť��ֱ����ʾ��ϸ��Ϣ
						else if(index < ButtonVec.size() && index <accomplishBtnIcon->size() && accomplishBtnIcon->at(index).second != titleOne )
						{
							menuButton.showButtonInfo(accomplish_table.get(), imgAndTextVec, m_totalItemNum, 2, chapterscroll);
						}
						//��ʾ��ťͼƬ
						menuButton.showButtonImg();
					}	
				}
				else
				{
					crTableIO::DataVec recordsParanet;
					picture_table->queryRecords(parentIndex,crArgumentParser::appItoa(1),recordsParanet);
					accomplishBtnIcon->clear();
					for(int i = 0; i<recordsParanet.size(); ++i)
					{
						accomplishBtnIcon->push_back(std::make_pair(recordsParanet[i][0],recordsParanet[i][parentIndex]));
					}
					TwoLevelMenuButton menuButton(ButtonVec, accomplishBtnIcon, picture_table.get(), index);
					menuButton.showButtonImg();

					//�ܳɾ͵㣬��ɳɾ�������ɽ��ȣ���������ʾ
					int chengjiupointindex = accomplish_table->getTitleIndex("�ɾ�");
					crTableIO::StrVec chengjiurecord;
					std::string tmpStr;
					void *param;
					bool AchivementComplete;
					int achieveid = 0;
					int totalfinish[12] = {0};
					int finishachievepoint = 0;

					mainRoleData->getParam(WCHDATA_JXJAccomplishPoint,param);
					unsigned short accpoint = *(unsigned short *)param;

					mainRoleData->getParam(WCHDATA_JXJAccomplishMap,param);
					AccomplishMap *accomplishMap = (AccomplishMap*)param;
					for (AccomplishMap::iterator itr = accomplishMap->begin();
						itr != accomplishMap->end();
						++itr)
					{
						AchivementComplete = itr->second->getComplete();
						achieveid = (int)itr->first;
						if(accomplish_table->queryOneRecord(0,crArgumentParser::appItoa(itr->first),chengjiurecord) >= 0)
						{
							if (achieveid>=m_guozhanid[0] && achieveid<=m_guozhanid[1])
							{
								totalfinish[0] += atoi(chengjiurecord[chengjiupointindex].c_str());
								if(AchivementComplete)
									totalfinish[1] += atoi(chengjiurecord[chengjiupointindex].c_str());
							}
							else if (achieveid>=m_lingzhuid[0] && achieveid<=m_lingzhuid[1])
							{
								totalfinish[2] += atoi(chengjiurecord[chengjiupointindex].c_str());
								if(AchivementComplete)
									totalfinish[3] += atoi(chengjiurecord[chengjiupointindex].c_str());
							}
							else if (achieveid>=m_fengdiid[0] && achieveid<=m_fengdiid[1])
							{
								totalfinish[4] += atoi(chengjiurecord[chengjiupointindex].c_str());
								if(AchivementComplete)
									totalfinish[5] += atoi(chengjiurecord[chengjiupointindex].c_str());
							}
							else if (achieveid>=m_jiangkaid[0] && achieveid<=m_jiangkaid[1])
							{
								totalfinish[6] += atoi(chengjiurecord[chengjiupointindex].c_str());
								if(AchivementComplete)
									totalfinish[7] += atoi(chengjiurecord[chengjiupointindex].c_str());
							}
							else if (achieveid>=m_fubenid[0] && achieveid<=m_fubenid[1])
							{
								totalfinish[8] += atoi(chengjiurecord[chengjiupointindex].c_str());
								if(AchivementComplete)
									totalfinish[9] += atoi(chengjiurecord[chengjiupointindex].c_str());
							}
						}
					}
					totalfinish[10] = totalfinish[0] + totalfinish[2] + totalfinish[4] + totalfinish[6] + totalfinish[8];
					totalfinish[11] = totalfinish[1] + totalfinish[3] + totalfinish[5] + totalfinish[7] + totalfinish[9];
					finishachievepoint = totalfinish[11];

					int completepercent = 0;
					ref_ptr<crProgressWidgetNode> progressbar[6]= {NULL};
					ref_ptr<crStaticTextWidgetNode> progrestext[6] = {NULL};
					for (int i = 0; i < 6; ++i)
					{
						progressbar[i] = dynamic_cast<crProgressWidgetNode *>(m_this->getWidget(m_progressbar[i]));
						progrestext[i] = dynamic_cast<crStaticTextWidgetNode *>(m_this->getWidget(m_progresstext[i]));
						if(progrestext[i].valid() && progressbar[i].valid())
						{
							completepercent = totalfinish[i*2+1] * 100 / totalfinish[i*2];
							progrestext[i]->setString(crArgumentParser::appItoa(totalfinish[i*2+1]) + "/" + crArgumentParser::appItoa(totalfinish[i*2]));
							progressbar[i]->setProgress((float)completepercent/100.0f);
						}
					}
					progrestext[5]->setString(crArgumentParser::appItoa(accpoint) + "/" + crArgumentParser::appItoa(totalfinish[10]));

					
					int dailypoints = 0;
					unsigned char daycount = 0;
					int mytotalhuoyuedu = 0;
					crPlayerGameData *myPlayer = crMyPlayerData::getInstance()->getPlayerGameData();
					if (myPlayer && myPlayer->getDataClass())
					{
						crData *playerData = myPlayer->getDataClass();
						/*playerData->getParam(WCHDATA_JXJUsedAchievePoints,param);
						usedpoints = *(int*)param;*/
						playerData->getParam(WCHDATA_JXJAchievePointsCount,param);
						dailypoints = *(int*)param;
						//accpoint += dailypoints;
						playerData->getParam(WCHDATA_JXJFinishHuoYueDuDayCount,param);
						daycount = *(unsigned char*)param;

						
						int totalhuoyuedu = 0;
						unsigned char curstep = 0;
						unsigned char totalstep = 0;
						unsigned short perhuoyuedu = 0;
						crTableIO::StrVec hydrecord;
						ref_ptr<crTableIO>HuoyueduTab = crGlobalHandle::gData()->gGlobalTable(WCHDATA_JXJHuoyueduTab);
						crData *mainroledata = myPlayer->getMainRole()->getDataClass();
						CRCore::ScopedLock<crData> lock(*mainroledata);
						mainroledata->getParam(WCHDATA_Level, param);
						unsigned char mylv = *(unsigned char *)param;
						mainroledata->getParam(WCHDATA_JXJHuoyueduMap, param);
						HuoyueduMap *huoyuedumap = (HuoyueduMap *)param;
						for (HuoyueduMap::iterator hyditr = huoyuedumap->begin();
							hyditr != huoyuedumap->end();
							++hyditr)
						{
							if (HuoyueduTab->queryOneRecord(0, crArgumentParser::appItoa(hyditr->first), hydrecord) >= 0)
							{
								if (hyditr->second->getNeedlv() <= mylv)
								{
									curstep = hyditr->second->getStep();
									totalstep = hyditr->second->getStepCount();
									perhuoyuedu = hyditr->second->getPoint();
									mytotalhuoyuedu += curstep * perhuoyuedu;
									totalhuoyuedu += totalstep * perhuoyuedu;
								}
							}
						}
					}
					//int havepoints = accpoint - usedpoints;

					//ÿ��Ŀ��
					crStaticTextWidgetNode *totalachevejifen = dynamic_cast<crStaticTextWidgetNode *>(m_this->getWidget(m_infoinput[0]));
					int targetcount = atoi(crGlobalHandle::gData()->gGameGlobalValue(WCHDATA_JXJHuoYueDuTargetCount).c_str());
					std::string mubiaotext = "�����Ծ�ȴﵽ" + crArgumentParser::appItoa(targetcount) + "��";
					int daycountnew = 0;	
					if (mytotalhuoyuedu >= targetcount)
					{
						if(daycount>=7)
							daycountnew = 7;
						else
							daycountnew = daycount;
					}
					else
					{
						if(daycount>=7)
							daycountnew = 7;
						else
							daycountnew = daycount + 1;
					}
					ref_ptr<crTableIO> continuehuoyuedutab = crGlobalHandle::gData()->gGlobalTable(WCHDATA_JXJContinueHuoYueDuTab);
					std::vector<std::string> continuerecord;

					ref_ptr<crStaticTextWidgetNode> dalytargettext[5] = {NULL};
					for (int i=0; i<5; i++)
					{
						dalytargettext[i] = dynamic_cast<crStaticTextWidgetNode *>(m_this->getWidget(m_dalytarget[i]));
					}
					if(dalytargettext[0].valid())
						dalytargettext[0]->setString(mubiaotext);
					if(dalytargettext[1].valid())
						dalytargettext[1]->setString(crArgumentParser::appItoa(mytotalhuoyuedu));
					if(dalytargettext[2].valid())
						dalytargettext[2]->setString(crArgumentParser::appItoa(daycount));

					if (continuehuoyuedutab->queryOneRecord(0,crArgumentParser::appItoa(daycountnew),continuerecord)>=0)
					{
						if(dalytargettext[3].valid())
							dalytargettext[3]->setString(continuerecord[1]);
					}

					if(dalytargettext[4].valid())
					{
						std::string iscomplet;
						if (mytotalhuoyuedu >= targetcount)
						{
							iscomplet = "�����";
							dalytargettext[4]->setColor(CRCore::crVector4(0.0,255.0,0.0,255.0));
							dalytargettext[4]->setString(iscomplet);
						}
						else
						{
							iscomplet = "δ���";
							dalytargettext[4]->setColor(CRCore::crVector4(255.0,0.0,0.0,255.0));
							dalytargettext[4]->setString(iscomplet);
						}
					}
					if (totalachevejifen)
						totalachevejifen->setString(crArgumentParser::appItoa(dailypoints));
					//�ɾ��̵�
					//crData *mainroledata = myPlayer->getMainRole()->getDataClass();
					mainRoleData->getParam(WCHDATA_Level, param);
					unsigned char mylv = *(unsigned char *)param;

					int val = 0;
					int intprice = 0;
					int needlv = 0;
					int thingtype = 0;
					std::string commodityc;
					std::string strImageName;
					crTableIO::StrVec itemrecord;
					crVector3i countvec;
					ref_ptr<crImageBoxWidgetNode > imageBox[10] = {NULL};
					ref_ptr<crStaticTextWidgetNode > priceInput[10] = {NULL};
					ref_ptr<crStaticTextWidgetNode > countInput[10] = {NULL};
					ref_ptr<crButtonWidgetNode> gouMaiBtn[10] = {NULL};
					ref_ptr<crScrollBarWidgetNode>  shopscroll = dynamic_cast<crScrollBarWidgetNode *>(m_this->getWidget(m_shopscroll));
					ref_ptr<crTableIO> equipTab = crGlobalHandle::gData()->gGlobalTable(WCHDATA_JXJTroopsEquipTab);
					int eIconIndex = equipTab->getTitleIndex("icon");
					ref_ptr<crTableIO> itemtab = crGlobalHandle::gData()->gGlobalTable(WCHDATA_JXJItemTab);
					int iconIdx = itemtab->getTitleIndex("icon"); 
					ref_ptr<crTableIO> achieveshoptab = crGlobalHandle::gData()->gGlobalTable(WCHDATA_JXJAchieveShopTab);
					std::string danJia = "�̵�۸�";
					int countindex = achieveshoptab->getTitleIndex("����");
					int dengjiindex = achieveshoptab->getTitleIndex("�ȼ�");
					int typeindex = achieveshoptab->getTitleIndex("����");
					int priceindex = achieveshoptab->getTitleIndex("�̵�۸�");
					int buycountindex = achieveshoptab->getTitleIndex("�������");
					int achieveindex = achieveshoptab->getTitleIndex("�ɾ�����");
					crTableIO::StrVec achieverecord;
					int cRow = achieveshoptab->getRowCount();
					if (shopscroll.valid())
					{
						/*if (cRow < 10)
						{
						shopscroll->setEnable(false);
						}
						else
						{
						shopscroll->setEnable(true);
						int crows = cRow%5==0? cRow/5 : cRow/5+1;
						shopscroll->setRange(0, crows-2);
						shopscroll->setLineValue(1.0f);
						shopscroll->setPageValue(1.0f);
						}*/
						val = shopscroll->getValue();
					}
					int id = 0;
					int index = 0;
					int buycount = 0;
					//int achieveid = 0;
					int shopid = 0;
					bool canbuy = true;
					for (unsigned char i = 0; i < 10; ++ i) 
					{
						imageBox[i] = dynamic_cast<crImageBoxWidgetNode *>(m_this->getWidget(m_imagebox[i]));
						gouMaiBtn[i] = dynamic_cast<crButtonWidgetNode *>(m_this->getWidget(m_buybtn[i]));
						priceInput[i] = dynamic_cast<crStaticTextWidgetNode *>(m_this->getWidget(m_pricetext[i]));
						countInput[i] = dynamic_cast<crStaticTextWidgetNode *>(m_this->getWidget(m_commodityc[i]));
						if (gouMaiBtn[i].valid())
							gouMaiBtn[i]->setEnable(false);
						if (imageBox[i].valid())
							imageBox[i]->setVisiable(false);
						if (priceInput[i].valid())
							priceInput[i]->clearString();
						if (countInput[i].valid())
							countInput[i]->clearString();
						index = i + 5 * val;
						if (index < cRow)
						{
							//for (int j=0;j<4;j++)
							//{
							//	achieverecord[j] = achieveshoptab->getData(i+5*val,j);
							//}
							achieverecord = achieveshoptab->getDataVec()[index];
							thingtype = atoi(achieverecord[typeindex].c_str());
								
							switch (thingtype)
							{
							case T_Food:
								strImageName = m_strFoodImage;
								break;
							case T_Wood:
								strImageName = m_strWoodImage;
								break;
							case T_Iron:
								strImageName = m_strIronImage;
								break;
							case T_Horse:
								strImageName = m_strHorseImage;
								break;
							case T_Copper:
								strImageName = m_strCopperImage;
								break;
							case T_Exp:
								strImageName = m_strExpImage;
								break;
							case T_Achievement:
								strImageName = m_strAchievementImage;
								break;
							case T_Giftgold:
								strImageName = m_strGiftGoldImage;
								break;
							case T_VIPExp:
								strImageName = m_strVipImage;
								break;
							case T_TroopsEquip:
								{
									crArgumentParser::appAtoVec(achieverecord[countindex],countvec);
									if(equipTab->queryOneRecord(0,crArgumentParser::appItoa(countvec[0]),itemrecord)>=0)
									{
										strImageName = itemrecord[eIconIndex];
									}											
								}
								break;
							case T_Item:
								{
									crArgumentParser::appAtoVec(achieverecord[countindex],countvec);
									if(itemtab->queryOneRecord(0,crArgumentParser::appItoa(countvec[0]),itemrecord)>=0)
									{
										strImageName = itemrecord[iconIdx];
									}
								}
								break;
							case T_Contribute:
								strImageName = m_strContributeImage;
								break;
							case T_Exploit:
								strImageName = m_strExploitImage;
								break;
							case T_Zhanquan:
								strImageName = m_strZhanquanImage;
								break;
							}
		
							canbuy = true;
							do 
							{
								intprice = atoi(achieverecord[priceindex].c_str());
								if(dailypoints < intprice)
								{
									canbuy = false;
									break;
								}
								needlv = atoi(achieverecord[dengjiindex].c_str());
								if(mylv < needlv)
								{
									canbuy = false;
									break;
								}
								buycount = atoi(achieverecord[buycountindex].c_str());
								if(buycount>0)
								{
									AchieveShopMap::iterator itr = achieveShopMap->find(index);
									if(itr != achieveShopMap->end())
									{
										if(buycount<=itr->second)
										{
											canbuy = false;
											break;
										}
									}
								}
								achieveid = atoi(achieverecord[achieveindex].c_str());
								if(achieveid>0)
								{
									AccomplishMap::iterator itr = accomplishMap->find(achieveid);
									if(itr == accomplishMap->end() || !itr->second->isComplete())
									{
										canbuy = false;
										break;
									}
								}
							} while (0);

							if (thingtype==T_Item)
								commodityc = crArgumentParser::appItoa(countvec[2]);
							else
								commodityc = achieverecord[countindex];

							if (priceInput[i].valid())	
								priceInput[i]->setString(achieverecord[priceindex]);

							if (countInput[i].valid())	
								countInput[i]->setString(commodityc);

							if (imageBox[i].valid())
							{
								crData *uidata = imageBox[i]->getDataClass();
								if (uidata)
								{
									id = atoi(achieverecord[0].c_str());
									uidata->inputParam(WCHDATA_JXJUIID, &id);
								}
								imageBox[i]->setVisiable(true);
								imageBox[i]->setImageName(strImageName);
							}
							if (gouMaiBtn[i].valid())
							{
								gouMaiBtn[i]->setVisiable(true);
								gouMaiBtn[i]->setEnable(canbuy);
								//if(dailypoints >= intprice && mylv >= needlv)
								//	gouMaiBtn[i]->setEnable(true);
								//else
								//	gouMaiBtn[i]->setEnable(false);
							}
						}
					}
				}
			}
		}
	}
}
/////////////////////////////////////////
//
//crJXJChengjiuButtonInitMethod
//�ɾͰ�ť��ʼ��[UI]
//
/////////////////////////////////////////
crJXJChengjiuButtonInitMethod::crJXJChengjiuButtonInitMethod()
{
}
crJXJChengjiuButtonInitMethod::crJXJChengjiuButtonInitMethod(const crJXJChengjiuButtonInitMethod& handle):
	crMethod(handle)
{
}
void crJXJChengjiuButtonInitMethod::inputParam(int i, void *param)
{
	switch(i) 
	{
	case 0:
		if(param == 0)
		{//�ͷ�
			m_this = NULL;
		}
		break;
	case 1:
		m_this = (crCanvasNode*)param;
		break;
	}
}
void crJXJChengjiuButtonInitMethod::addParam(int i, const std::string& str)
{
	switch(i) 
	{
	case 0:
		m_Button[i] = str;
		break;
	case 1:
		m_Button[i] = str;
		break;
	case 2:
		m_Button[i] = str;
		break;
	case 3:
		m_Button[i] = str;
		break;
	case 4:
		m_Button[i] = str;
		break;
	case 5:
		m_Button[i] = str;
		break;
	case 6:
		m_Button[i] = str;
		break;
	case 7:
		m_Button[i] = str;
		break;
	case 8:
		m_Button[i] = str;
		break;
	case 9:
		m_Button[i] = str;
		break;
	case 10:
		m_Button[i] = str;
		break;
	case 11:
		m_totalBtnNum = atoi(str.c_str());
		break;
	case 12:
		m_img[0] = str;
		break;
	case 13:
		m_img[1] = str;
		break;
	case 14:
		m_img[2] = str;
		break;
	case 15:
		m_img[3] = str;
		break;
	case 16:
		m_img[4] = str;
		break;
	}
}

void crJXJChengjiuButtonInitMethod::operator()(crHandle &handle)
{
	if (m_this)
	{
		std::vector<crCheckBoxWidgetNode*> ButtonVct;
		//�ѳɾ�����ϵ���ϸ��Ϣ �ؼ� ����vector
		for(int i = 0; i < m_totalBtnNum; ++i)
		{
			crCheckBoxWidgetNode *button = dynamic_cast<crCheckBoxWidgetNode *>(m_this->getWidget(m_Button[i]));
			if(button)ButtonVct.push_back(button);
		}

		CREncapsulation::crTableIO::StrVec	recordPicture;

		crTableIO::DataVec recordsParanet;
		ref_ptr<crTableIO> picture_table = CRNetApp::crGlobalHandle::gData()->gGlobalTable(WCHDATA_JXJAccomplishPictureTab);	// troops data look-up table

		int parentIndex = picture_table->getTitleIndex("parentId");
		int idIndex = picture_table->getTitleIndex("id");
		int iconIndex = picture_table->getTitleIndex("chaptericon");
		int iconHighlightedIndex = picture_table->getTitleIndex("chaptericon����");

		void *param;
		picture_table->queryRecords(parentIndex,crArgumentParser::appItoa(1),recordsParanet);
		crData *canvasData = m_this->getDataClass();
		if (canvasData)
		{
			//ȡ�����ڳɾ����canvas data�е�һ������ʼ������ť��Ϣ
			canvasData->getParam(WCHDATA_JXJAccomplishCanvasIcon,param);
			CanvasIconVec *accomplishBtnIcon = (CanvasIconVec *)param;
			accomplishBtnIcon->clear();

			//����һ��ͼ��
			for(int i = 0; i<recordsParanet.size(); ++i)
			{
				accomplishBtnIcon->push_back(std::make_pair(recordsParanet[i][idIndex],recordsParanet[i][parentIndex]));
				if(i<ButtonVct.size())
				{
					//ͼƬ
					crStateSet *state_set = dynamic_cast<crObject *>(dynamic_cast<crGroup *>((ButtonVct[i]->getChild(0)))->getChild(0))->getDrawable(0)->getStateSet();
					if(state_set)
					{
						crTexture2D *texture_2d = dynamic_cast<CRCore::crTexture2D *>(state_set->getTextureAttribute(0,crStateAttribute::TEXTURE));
						if(texture_2d)
						{
							texture_2d->setImage(0,texture_2d->getImageDataRequestHandler()->requestImageFile(recordsParanet[i][iconIndex],texture_2d));
						}
					}
				}
			}
			//��Ҫ��ʾ�İ�ť
			for(int i = 0; i<accomplishBtnIcon->size() && i < ButtonVct.size(); ++i)
			{
				ButtonVct.at(i)->setEnable(true);
			}
			//����Ҫ��ʾ�İ�ť
			for(int i = accomplishBtnIcon->size(); i < ButtonVct.size(); ++i)
			{
				ButtonVct.at(i)->setEnable(false);
			}
		}

	}

}
/////////////////////////////////////////
//
//crJXJChengjiuButtonMethod
//�ɾͰ�ťת��[UI]
//
/////////////////////////////////////////
crJXJChengjiuButtonMethod::crJXJChengjiuButtonMethod():
	m_index(0)
{
}
crJXJChengjiuButtonMethod::crJXJChengjiuButtonMethod(const crJXJChengjiuButtonMethod& handle):
	crMethod(handle)
{
}
void crJXJChengjiuButtonMethod::inputParam(int i, void *param)
{
	switch(i) 
	{
	case 0:
		if(param == 0)
		{//�ͷ�
			m_this = NULL;
		}
		break;
	case 1:
		m_this = (crWidgetNode*)param;
		break;
	}
}
void crJXJChengjiuButtonMethod::addParam(int i, const std::string& str)
{
	switch(i) 
	{
	case 0:
		m_index = atoi(str.c_str());
		break;
	}
}

void crJXJChengjiuButtonMethod::operator()(crHandle &handle)
{
	crCanvasNode *canvas = m_this->getParentCanvas();
	if(canvas)
	{
		crData *canvasData = canvas->getDataClass();
		if(canvasData)
		{
			//��������ĳɾͱ��⣨��ఴť��indexֵ����WCHDATA_JXJAccomplishBtnIndex
			canvasData->inputParam(WCHDATA_JXJAccomplishBtnIndex,&m_index);
		}
	}
}
int achievementTabInfo(crTableIO * accomplish_table, crTableIO *picture_table, std::vector<ImgAndTextInfo> imgAndTextVec)
{
	return 0;
}

/////////////////////////////////////////
//
//crJXJUIAchievementPromptMethod
//�ɾ͵���С��[UI]
//
/////////////////////////////////////////
crJXJUIAchievementPromptMethod::crJXJUIAchievementPromptMethod()
{
}
crJXJUIAchievementPromptMethod::crJXJUIAchievementPromptMethod(const crJXJUIAchievementPromptMethod& handle):
	crMethod(handle),
	m_tipsCanvas(handle.m_tipsCanvas),
	m_icon(handle.m_icon),
	m_input1(handle.m_input1),
	m_input2(handle.m_input2),
	m_sequence(handle.m_sequence)
{
}
void crJXJUIAchievementPromptMethod::inputParam(int i, void *param)
{
	switch(i) 
	{
	case 0:
		if(param == 0)
		{//�ͷ�
			m_this = NULL;
		}
		break;
	case 1:
		m_this = (crCanvasNode*)param;
		break;
	}
}
void crJXJUIAchievementPromptMethod::addParam(int i, const std::string& str)
{
	switch(i) 
	{
	case 0:
		m_tipsCanvas = str;
		break;
	case 1:
		m_icon = str;
		break;
	case 2:
		m_input1 = str;
		break;
	case 3:
		m_input2 = str;
		break;
	case 4:
		m_sequence = str;
		break;
	}
}

void crJXJUIAchievementPromptMethod::operator()(crHandle &handle)
{
	if (m_this)
	{
		void *param;
		unsigned short accid = 0;
		crPlayerGameData *playerData = crMyPlayerData::getInstance()->getPlayerGameData();
		crImageBoxWidgetNode *icon = dynamic_cast<crImageBoxWidgetNode *>(m_this->getChildNode(m_icon));
		crStaticTextWidgetNode *input1 = dynamic_cast<crStaticTextWidgetNode *>(m_this->getChildNode(m_input1));
		crStaticTextWidgetNode *input2 = dynamic_cast<crStaticTextWidgetNode *>(m_this->getChildNode(m_input2));
		if(playerData)
		{
			ref_ptr<crSequence> sequence = dynamic_cast<crSequence *>(m_this->getChildNode(m_sequence));
			if(sequence.valid()/* && sequence->getMode() == crSequence::STOP*/)
			{
				sequence->setDuration(0.1f, 1);
				sequence->startEffect();//
			}
			crRole *mainRole = playerData->getMainRole();
			if(mainRole)
			{
				unsigned short accomplishid = 0;
				//class crJXJMainRoleData   unsigned short m_accomplishPoint;//��õĳɾ͵�����
				crData *canvasdata = m_this->getDataClass();
				if (canvasdata)
				{
					canvasdata -> getParam(WCHDATA_JXJCurAccomplishID,param);
					accomplishid = *(unsigned short *)param;
				}
				if (accomplishid > 0)
				{
					crData *mainRoleData = mainRole->getDataClass();
					//mainRoleData->
					mainRoleData->getParam(WCHDATA_JXJAccomplishMap,param);
					AccomplishMap* accomplishMap = (AccomplishMap*)param;
					AccomplishMap::iterator fitr = accomplishMap->find(accomplishid);
					if (fitr!=accomplishMap->end())
					{
						if (fitr->second->isComplete())
						{
							accid = fitr->second->getID();
							ref_ptr<crTableIO> accomplish_table = CRNetApp::crGlobalHandle::gData()->gGlobalTable(WCHDATA_JXJAccomplishTab);
							int idIndex = accomplish_table->getTitleIndex("id");
							int iconIndex = accomplish_table->getTitleIndex("icon");
							int nameIndex = accomplish_table->getTitleIndex("Name");
							int pointIndex = accomplish_table->getTitleIndex("�ɾ�");
							CREncapsulation::crTableIO::StrVec	record;
							accomplish_table->queryOneRecord(idIndex,crArgumentParser::appItoa(accid),record);
							std::string nameStr = record[nameIndex];
							std::string iconStr = record[iconIndex];
							std::string pointStr = record[pointIndex];
							if(icon)icon->setImageName(iconStr);
							if(input1)input1->setString(nameStr);
							if(input2)input2->setString(pointStr);
							//GeneralTips achivementPrompt(m_tipsCanvas);
							//achivementPrompt.setText(m_tipsTextWidget,nameStr,crVector4(255.0,255.0,0.0,255.0)/255.0);
							//achivementPrompt.setText(m_tipsTextPointWidget,pointStr,crVector4(255.0,255.0,0.0,255.0)/255.0);
						}
					}
				}
				else
				{
					crFilterRenderManager::getInstance()->closeCanvas(m_this);
				}
			}
		}
	}
}

/////////////////////////////////////////
//
//crJXJUIResourceCardTimeTipMethod
//��Դ�ӳɿ�ʣ��ʱ��tips
//
/////////////////////////////////////////
crJXJUIResourceCardTimeTipMethod::crJXJUIResourceCardTimeTipMethod()
{
}
crJXJUIResourceCardTimeTipMethod::crJXJUIResourceCardTimeTipMethod(const crJXJUIResourceCardTimeTipMethod& handle):
	crMethod(handle),
	m_tipsCanvas(handle.m_tipsCanvas),
	m_tipsTextWidget(handle.m_tipsTextWidget),
	m_index(0),
	m_extsw(handle.m_extsw)
{
}
void crJXJUIResourceCardTimeTipMethod::inputParam(int i, void *param)
{
	switch(i) 
	{
	case 0:
		if(param == 0)
		{//�ͷ�
			m_this = NULL;
		}
		break;
	case 1:
		m_this = (crWidgetNode*)param;
		break;
	}
}
void crJXJUIResourceCardTimeTipMethod::addParam(int i, const std::string& str)
{
	switch(i) 
	{
	case 0:
		m_tipsCanvas = str;
		break;
	case 1:
		m_tipsTextWidget = str;
		break;
	case 2:
		m_index = atoi(str.c_str());//enum JXJThingType {T_Food = 1, T_Wood, T_Iron, T_Horse,...}
		break;
	case 3:
		m_extsw = str;
		break;
	}
}

void crJXJUIResourceCardTimeTipMethod::operator()(crHandle &handle)
{
	crCanvasNode *tips = crFilterRenderManager::getInstance()->findCanvas(m_tipsCanvas);
	if(!tips)return;
	crStaticTextWidgetNode *tipsText = dynamic_cast<crStaticTextWidgetNode *>(tips->getWidget(m_tipsTextWidget));
	crData *playerData = crMyPlayerData::getInstance()->getPlayerGameData()->getDataClass();
	if(tipsText && playerData)
	{
		int index = m_index;
		if(!m_extsw.empty())
		{
			ref_ptr<crCanvasNode> canvas = m_this->getParentCanvas();
			crMultiSwitch *sw = dynamic_cast<crMultiSwitch *>(canvas->getChildNode(m_extsw));
			if(sw->getActiveSwitchSet() == 5)
			{
				index = T_CopperExtraProduce+m_index;
			}
		}
		//crVector4s percent;
		void *param;
		playerData->excHandle(MAKECREPARAM(WCH_LockData,1));
		playerData->getParam(WCHDATA_JXJExtraProduceMap,param);
		ExtraProduceMap *extraProduceMap = (ExtraProduceMap *)param;
			 
		ExtraProduceMap::iterator itr = extraProduceMap->find(index);
		std::string str = "";
		tipsText->setString(str);
		if (itr != extraProduceMap->end())//�������ָ������Դ�ӳɿ���¼map��
		{
			int timer = itr->second->timer();
			int percent = 0;// = itr->second->getPercent();
			crTableIO::StrVec ResAddBuildingrecord;
			ref_ptr<crTableIO> ResAddBuildingTab = crGlobalHandle::gData()->gGlobalTable(WCHDATA_JXJResAddBuildingTab);
			int buildinglvindex = ResAddBuildingTab->getTitleIndex("lv");
			int addindex = ResAddBuildingTab->getTitleIndex("�ӳ�");
			if (index>=T_Food && index<=T_Horse)
			{
				int buildingid = 0;
				if (timer > 0)
				{
					switch (itr->first)
					{
					case T_Food:
						buildingid = WCHDATA_JXJShuichelv;
						break;
					case T_Wood:
						buildingid = WCHDATA_JXJGongshelv;
						break;
					case T_Iron:
						buildingid = WCHDATA_JXJRonglulv;
						break;
					case T_Horse:
						buildingid = WCHDATA_JXJMochuanlv;
						break;
					default:
						break;
					}
					playerData->getParam(buildingid, param);
					unsigned char buildinglv = *(unsigned char *)param;
					if (ResAddBuildingTab->queryOneRecord(0, crArgumentParser::appItoa(buildingid), buildinglvindex, crArgumentParser::appItoa(buildinglv), ResAddBuildingrecord) >= 0)
						percent += atoi(ResAddBuildingrecord[addindex].c_str());
				}
			}
			else
			{
				percent = itr->second->getPercent();
			}

			int hour = timer/3600;
			int t = timer%3600;
			int minute = t/60;
			int s = t%60;
			//tipsText->setString("�ӳɿ�ʣ��ʱ�䣺"+crArgumentParser::appItoa(hour)+"Сʱ"+crArgumentParser::appItoa(minute)+":"+crArgumentParser::appItoa(s));
			if(hour>0)
			{
				tipsText->setString("�ӳ�:"+crArgumentParser::appItoa(percent)+"%,ʣ��:"+crArgumentParser::appItoa(hour)+":"+crArgumentParser::appItoa(minute));
			}
			else if(minute>0)
			{
				tipsText->setString("�ӳ�:"+crArgumentParser::appItoa(percent)+"%,ʣ��:0:"+ crArgumentParser::appItoa(minute)/*+"����"*/);
			}
			else if(s>0)
			{
				str = "�ӳ�:"+crArgumentParser::appItoa(percent)+"%,ʣ��:0:0";//"ʱ������1����";
				tipsText->setString(str);
			}
			tips->setCanFocus(false);

			//����������ʾλ��
			const crBoundingBox &iconbox = m_this->getBoundBox();
			const crBoundingBox &tip = tips->getBoundBox();
			float posx = (tip.m_max[0]-tip.m_min[0])*0.5;
			float posy = (tip.m_max[1]-tip.m_min[1])*0.5;
			crVector3 pos(iconbox.m_max[0],iconbox.m_max[1],0.0f);
			/////////////////////////////////////////
			crVector3 pos2(iconbox.m_min[0] ,iconbox.m_min[1],0.0f);
			float posx2,posy2;
			posx2 = iconbox.m_max[0];
			posy2 = iconbox.m_max[1] - posy;

			crVector2 mouse(crVector2(posx2,posy2));
			tips->setMatrix(crMatrix::translate(mouse[0],mouse[1],0.0f));
			crFilterRenderManager::getInstance()->showCanvas(tips,true);
		}
		playerData->excHandle(MAKECREPARAM(WCH_LockData,0));
	}
}

/////////////////////////////////////////
//
//crJXJUIBattleBuffTipsMethod
//ս����buff tips
//
/////////////////////////////////////////
//crJXJUIBattleBuffTipsMethod::crJXJUIBattleBuffTipsMethod()
//{
//}
//crJXJUIBattleBuffTipsMethod::crJXJUIBattleBuffTipsMethod(const crJXJUIBattleBuffTipsMethod& handle):
//	crMethod(handle),
//	m_tipsCanvas(handle.m_tipsCanvas),
//	m_tipsTextWidget(handle.m_tipsTextWidget),
//	m_indexRow(0),
//	m_indexCol(0)
//{
//}
//void crJXJUIBattleBuffTipsMethod::inputParam(int i, void *param)
//{
//	switch(i) 
//	{
//	case 0:
//		if(param == 0)
//		{//�ͷ�
//			m_this = NULL;
//		}
//		break;
//	case 1:
//		m_this = (crWidgetNode*)param;
//		break;
//	}
//}
//void crJXJUIBattleBuffTipsMethod::addParam(int i, const std::string& str)
//{
//	switch(i) 
//	{
//	case 0:
//		m_tipsCanvas = str;
//		break;
//	case 1:
//		m_tipsTextWidget = str;
//		break;
//	case 2:
//		m_indexRow = atoi(str.c_str());//enum JXJThingType {T_Food = 1, T_Wood, T_Iron, T_Horse,...}
//		break;
//	case 3:
//		m_indexCol = atoi(str.c_str());//enum JXJThingType {T_Food = 1, T_Wood, T_Iron, T_Horse,...}
//		break;
//	}
//}
//
//void crJXJUIBattleBuffTipsMethod::operator()(crHandle &handle)
//{
//	void *param;
//	crTableIO::StrVec record;
//	std::string bufferText;
//
//	crMyPlayerData *me = crMyPlayerData::getInstance();
//	ref_ptr<crTableIO> dataAttrTab = crGlobalHandle::gData()->gGlobalTable(WCHDATA_SkillDataAttrTab);
//	if(me && dataAttrTab)
//	{
//		int targetIndex = dataAttrTab->getTitleIndex("Ŀ��Buf");
//		int index = dataAttrTab->getTitleIndex("Buffer����");
//		int j = 0;
//		crRole *role = me->getLoadedRoleByIndex(m_indexRow);
//		if(role)
//		{
//			crData *data = role->getDataClass();
//			if(data)
//			{
//				data->getParam(WCHDATA_ExtraData,param);
//				if(param)
//				{
//					crData *extraData = (crData *)param;
//					extraData->excHandle(MAKECREPARAM(WCH_LockData,1));
//					extraData->getParam(WCHDATA_ExtraIDMap,param);
//					ExtraIDMap *extraIDMap = (ExtraIDMap *)param;
//					for( ExtraIDMap::iterator itr = extraIDMap->begin();
//						itr != extraIDMap->end();
//						++itr,j++ )
//					{
//						if(j == m_indexCol)
//						{
//							std::string extraValue = crArgumentParser::appItoa(itr->first)+std::string("|")+crArgumentParser::appItoa(itr->second);
//							if(index>=0)
//							{
//								if(dataAttrTab->queryOneRecord(targetIndex,extraValue,record))
//								{
//									bufferText = record[index];
//									if(j<8 && !bufferText.empty())
//									{
//										GeneralTips generalTips(m_tipsCanvas, m_this);
//										generalTips.setText(m_tipsTextWidget, bufferText);
//										generalTips.setTipRight();
//									}
//								}
//							}
//						}
//					}
//					extraData->excHandle(MAKECREPARAM(WCH_LockData,0));
//				}
//			}
//		}
//	}
//}

/////////////////////////////////////////
//
//crJXJUIJunLingTimesTipMethod
//ʣ�����������ʾ
//
/////////////////////////////////////////
crJXJUIJunLingTimesTipMethod::crJXJUIJunLingTimesTipMethod()
{
}
crJXJUIJunLingTimesTipMethod::crJXJUIJunLingTimesTipMethod(const crJXJUIJunLingTimesTipMethod& handle):
	crMethod(handle),
	m_tipsCanvas(handle.m_tipsCanvas),
	m_tipsTextWidget(handle.m_tipsTextWidget)
{
}
void crJXJUIJunLingTimesTipMethod::inputParam(int i, void *param)
{
	switch(i) 
	{
	case 0:
		if(param == 0)
		{//�ͷ�
			m_this = NULL;
		}
		break;
	case 1:
		m_this = (crWidgetNode*)param;
		break;
	}
}
void crJXJUIJunLingTimesTipMethod::addParam(int i, const std::string& str)
{
	switch(i) 
	{
	case 0:
		m_tipsCanvas = str;
		break;
	case 1:
		m_tipsTextWidget = str;
		break;

	}
}

void crJXJUIJunLingTimesTipMethod::operator()(crHandle &handle)
{
	//GeneralTips generalTips(m_tipsCanvas, m_this);
	ref_ptr<crCanvasNode> tips = crFilterRenderManager::getInstance()->findCanvas(m_tipsCanvas);
	if(!tips.valid())
		return;

	ref_ptr<crHypertextWidgetNode>  tipsText = dynamic_cast< crHypertextWidgetNode  *>(tips->getWidget(m_tipsTextWidget));

	void *param;
	crPlayerGameData *playerData = crMyPlayerData::getInstance()->getPlayerGameData();
	if(playerData)
	{
		crData *data = playerData->getDataClass();
		int goldneed = 0;//perprice * totalcount;
		crTableIO::StrVec record;
		ref_ptr<crTableIO>junlingcosttab = crGlobalHandle::gData()->gGlobalTable(WCHDATA_JXJJunlingCostTab);
		data->getParam(WCHDATA_JXJBuyJunlingTimer,param);
		unsigned short timer = *(unsigned short *)param;
		//data->getParam(WCHDATA_JXJBuyJunlingCount,param);
		//unsigned char count = *(unsigned char *)param;
		data->getParam(WCHDATA_JXJTechBuyJunlingLv, param);
		unsigned char techjunlinglv = *(unsigned char *)param;
		int totalpriceindex = 0; 
		if (techjunlinglv == 0)
		{
			totalpriceindex = junlingcosttab->getTitleIndex("����۸�");
		}
		else
		{
			totalpriceindex = junlingcosttab->getTitleIndex("�Ƽ��۸�");
		}
		
		int id = timer + 1; 
		if (id < 1)
		{
			id = 1;
		}
		if(junlingcosttab->queryOneRecord(0,crArgumentParser::appItoa(id),record) >= 0)
		{
			goldneed = atoi(record[totalpriceindex].c_str());
		}

		std::vector<float>v_i;
		ItemMap itemMap;
		rcfg::ConfigScript cfg_script(&itemMap);

		cfg_script.Add("Hypertext");
		cfg_script.Push("Hypertext");

		cfg_script.Add("Content");
		cfg_script.Push("Content", 1);
		v_i.clear();
		v_i.push_back(0.0f);
		v_i.push_back(0.0f);
		v_i.push_back(0.0f);
		v_i.push_back(255.0f);
		cfg_script.Add("Color", v_i);
		cfg_script.Add("Text", "    ����");
		cfg_script.Pop();

		cfg_script.Add("Content");
		cfg_script.Push("Content", 2);
		v_i.clear();
		v_i.push_back(140.0f);
		v_i.push_back(40.0f);
		v_i.push_back(40.0f);
		v_i.push_back(255.0f);
		cfg_script.Add("Color", v_i);
		char tmpText[32];
		sprintf(tmpText, "%d���/Ԫ��\0", goldneed);
		cfg_script.Add("Text", tmpText);
		cfg_script.Pop();

		cfg_script.Add("Content");
		cfg_script.Push("Content", 3);
		v_i.clear();
		v_i.push_back(0.0f);
		v_i.push_back(0.0f);
		v_i.push_back(0.0f);
		v_i.push_back(255.0f);
		cfg_script.Add("Color", v_i);

		//if(data)
		//{
			data->getParam(WCHDATA_JXJBuyJunlingCount,param);
			unsigned char count = *(unsigned char *)param;
			std::string str = "�������,ʣ��" + crArgumentParser::appItoa(count) + "��";
			//generalTips.setText(m_tipsTextWidget, str,crVector4(0,0,0,255));
			//generalTips.setTipAuto();
		//}
		cfg_script.Add("Text", str);
		cfg_script.Pop();

		cfg_script.Pop();
		//cfg_script.Write("tipstest.cfg");
		if(tipsText.valid()) tipsText->setHypertext(cfg_script);

		const crBoundingBox &btnbox = m_this->getBoundBox();
		const crBoundingBox &tipsbox = tips->getBoundBox();
		const crMatrix &mat = m_this->getParentCanvas()->getMatrix();
		float posx = btnbox.m_min[0];
		float posy = (btnbox.m_min[1] - tipsbox.yLength()/2);
		////////////
		crVector2 mouse(crVector2(posx,posy));
		tips->setMatrix(crMatrix::translate(mouse[0],mouse[1],0.0f) * mat);
		crFilterRenderManager::getInstance()->showCanvas(tips.get(),true);
	}
}

/////////////////////////////////////////
//
//crJXJUIMailTipMethod
//�ʼ�������Ʒ��ʾ
//
/////////////////////////////////////////
crJXJUIMailTipMethod::crJXJUIMailTipMethod()
{
}
crJXJUIMailTipMethod::crJXJUIMailTipMethod(const crJXJUIMailTipMethod& handle):
	crMethod(handle)
{
}
void crJXJUIMailTipMethod::inputParam(int i, void *param)
{
	switch(i) 
	{
	case 0:
		if(param == 0)
		{//�ͷ�
			m_this = NULL;
		}
		break;
	case 1:
		m_this = (crCanvasNode*)param;
		break;
	case 2:
		if(param)
		{
			CREPARAM& param64 = *(CREPARAM*)param;
			m_itemid = (int *)(LOCREPARAM(param64));
			m_index = (int )(HICREPARAM(param64));
		}
		else
		{
			m_itemid = NULL;
			m_index = -1;
		}
		break;
	}
}
void crJXJUIMailTipMethod::addParam(int i, const std::string& str)
{
	switch(i) 
	{
	case 0:
		m_mailinput = str;
		break;
	}
}

void crJXJUIMailTipMethod::operator()(crHandle &handle)
{
	if(m_this)
	{
		crData *brainData = crBrain::getInstance()->getDataClass();
		if(brainData)
		{
			RewardItemVec *itemVec = NULL;
			void *param;
			brainData->getParam(WCHDATA_JXJRecvMailVec,param);
			JXJRecvMailVec *mailvec = (JXJRecvMailVec *)param;
			brainData->getParam(WCHDATA_JXJRecvMailCacheMap,param);
			MailCacheMap *mailbodymap = (MailCacheMap *)param;
			brainData->getParam(WCHDATA_JXJCheckMailIndex,param);
			unsigned char mailindex = *(unsigned char *)param;
			if( mailindex < mailvec->size() && (*mailvec)[mailindex]!=NULL)
			{	
				int mailid = (*mailvec)[mailindex]->getID();

				MailCacheMap::iterator itr = mailbodymap->find(mailid);
				if (itr!=mailbodymap->end())
				{
					rcfg::ConfigScript outscript;
					crHypertextWidgetNode *bodyinput = dynamic_cast<crHypertextWidgetNode *>(m_this->getWidget(m_mailinput));
					CRCore::ref_ptr<CRCore::crStreamBuf> bodystream = itr->second->getBody();
					crGlobalHandle::getInstance()->getStreamScript(bodystream.get(),outscript);
					if (bodyinput)
					{
						crData *bodydata = bodyinput->getDataClass();
						if (bodydata)
						{
							bodydata->getParam(WCHDATA_JXJGiftsPackItemInfo,param);
							itemVec = (RewardItemVec *)param;
						}
						if(m_index < itemVec->size())
							*m_itemid = (*itemVec)[m_index]->getItemID();
					}
				}
			}	
		}
	}
}

/////////////////////////////////////////
//
//crJXJGetOnlineRewardIDCaseMethod
//
/////////////////////////////////////////
crJXJGetOnlineRewardIDCaseMethod::crJXJGetOnlineRewardIDCaseMethod(){}
crJXJGetOnlineRewardIDCaseMethod::crJXJGetOnlineRewardIDCaseMethod(const crJXJGetOnlineRewardIDCaseMethod& handle):
	crMethod(handle)
{
}
void crJXJGetOnlineRewardIDCaseMethod::inputParam(int i, void *param)
{
	switch(i) 
	{
	case 0:
		if(param == 0)
		{//�ͷ�
			m_this = NULL;
		}
		break;
	case 1:
		m_this = (crWidgetNode*)param;
		break;
	}
}
void crJXJGetOnlineRewardIDCaseMethod::addParam(int i, const std::string& str)
{
	switch(i) 
	{
	case 0:
		m_rewardInput = atoi(str.c_str());
		break;
	}
}
void crJXJGetOnlineRewardIDCaseMethod::operator()(crHandle &handle)
{
	int _case = 2;//0���ߣ�1������2����
	//m_rewardInput = 0;

	crTableIO::StrVec record,itemrecord;

	ref_ptr<crTableIO> olRewardTab = crGlobalHandle::gData()->gGlobalTable(WCHDATA_JXJOnlineRewardTab);
	int giftGoldIndex = olRewardTab->getTitleIndex("���");
	int item1index = olRewardTab->getTitleIndex("����1");
	int item2index = olRewardTab->getTitleIndex("����2");
	int item3index = olRewardTab->getTitleIndex("����3");
	ref_ptr<crTableIO> itemtab = crGlobalHandle::gData()->gGlobalTable(WCHDATA_JXJItemTab);
	int typeindex = itemtab->getTitleIndex("����");
	void *param;
	crMyPlayerData *myPalyer = crMyPlayerData::getInstance();
	myPalyer->getPlayerGameData()->getDataClass()->getParam(WCHDATA_JXJOnlineRewardCount,param);
	unsigned char count = *(unsigned char *)param;
	int currIndex = 0;
	if(m_rewardInput == 0)
	{
		currIndex = giftGoldIndex;
	}
	else if(m_rewardInput == 1)
	{
		currIndex = item1index;
	}
	else if(m_rewardInput == 2)
	{
		currIndex = item2index;
	}
	else if (m_rewardInput == 3)
	{
		currIndex = item3index;
	}
	if(olRewardTab->queryOneRecord(0,crArgumentParser::appItoa(count),record) >= 0)
	{
		if(giftGoldIndex >=0 && m_rewardInput== 0)
		{
			int count = atoi(record[giftGoldIndex].c_str());
			if(count == 0)
				currIndex = item1index;
		}

		crVector3i vec3;
		crArgumentParser::appAtoVec(record[currIndex], vec3);
		if(currIndex >0)
		{
			if(itemtab->queryOneRecord(0, crArgumentParser::appItoa(vec3[0]), itemrecord) >= 0)
			{
				int itemTypeId = atoi(itemrecord[typeindex].c_str());
				if(itemTypeId == IT_Jiangka)
				{
					_case = 1;
				}
				else
				{
					_case = 0;
				}
			}
		}
	}
	handle.outputParam(0,&_case);
}
/////////////////////////////////////////
//
//crJXJUIBattleInspireTipMethod
//ս������tips
//
/////////////////////////////////////////
crJXJUIBattleInspireTipMethod::crJXJUIBattleInspireTipMethod():
	m_str(0),
	m_itemId(0)
{
}

crJXJUIBattleInspireTipMethod::crJXJUIBattleInspireTipMethod(const crJXJUIBattleInspireTipMethod& handle):
	crMethod(handle),
	m_tips(handle.m_tips),
	m_tipstext(handle.m_tipstext),
	m_str(handle.m_str),
	m_itemId(handle.m_itemId)
{
}
void crJXJUIBattleInspireTipMethod::inputParam(int i, void *param)
{
	switch(i) 
	{
	case 0:
		if(param == 0)
		{//�ͷ�
			m_this = NULL;
		}
		break;
	case 1:
		m_this = (crWidgetNode*)param;
		break;
	}
}
void crJXJUIBattleInspireTipMethod::addParam(int i, const std::string& str)
{
	switch(i) 
	{
	case 0:
		m_strBt = str;
		break;
	case 1:
		m_tips = str;
		break;
	case 2:
		m_tipstext = str;
		break;
	case 3:
		m_str = atoi(str.c_str());
		break;
	case 4:
		m_itemId = atoi(str.c_str());
		break;
	default:
		break;
	}
}

void crJXJUIBattleInspireTipMethod::operator()(crHandle &handle)
{
	std::string strInfo;
	void *param;
	crCanvasNode *tips = crFilterRenderManager::getInstance()->findCanvas(m_tips);
	crCanvasNode *parentCanvas = m_this->getParentCanvas();
	crPlayerGameData *myPlayer = crMyPlayerData::getInstance()->getPlayerGameData();
	crData *playerData = myPlayer?myPlayer->getDataClass():NULL;
	if(tips && parentCanvas && playerData)
	{
		std::vector<float>v_i;
		ItemMap itemMap;
		rcfg::ConfigScript cfg_script(&itemMap);
		crButtonWidgetNode * bt = dynamic_cast<crButtonWidgetNode *>(parentCanvas->getWidget(m_strBt));
		//crStaticTextWidgetNode *tipstext = dynamic_cast<crStaticTextWidgetNode *>(tips->getWidget(m_tipstext));
		ref_ptr<crHypertextWidgetNode>  tipsText = dynamic_cast< crHypertextWidgetNode  *>(tips->getWidget(m_tipstext));
		if(tipsText.valid() && bt)
		{
			playerData->getParam(WCHDATA_JXJVipLv,param);
			unsigned char vipLevel = *(unsigned char *)param;
			playerData->getParam(WCHDATA_JXJInspireLevel,param);
			unsigned char inspireLv = *(unsigned char *)param;
			int canInspireCount = atoi(crGlobalHandle::gData()->gGameGlobalValue(WCHDATA_JXJBattleInspireMaxCount, vipLevel).c_str());

			if(canInspireCount>0 && inspireLv<canInspireCount )
			{
				int inspireCost = atoi(crGlobalHandle::gData()->gGameGlobalValue(WCHDATA_JXJBattleInspireCost, inspireLv+1).c_str());
				int inspireExtra = atoi(crGlobalHandle::gData()->gGameGlobalValue(WCHDATA_JXJInspireExtraPercent, inspireLv+1).c_str());

				//��ⱳ�������еĹ���������
				playerData->excHandle(MAKECREPARAM(WCH_LockData,1));
				playerData->getParam(WCHDATA_JXJItemBagVec, param);
				JXJItemBagVec *itembagvec = (JXJItemBagVec *)param;
				int itemcount = 0;
				for (JXJItemBagVec::iterator itemitr = itembagvec->begin();
					itemitr != itembagvec->end();
					++itemitr)
				{
					if (itemitr->get())
					{
						if (m_itemId == itemitr->get()->getItemID())
						{
							itemcount = (int)itemitr->get()->getItemCount();
							break;
						}
					}
				}
				playerData->excHandle(MAKECREPARAM(WCH_LockData,0));
				//str = "����Ԫ��" + crArgumentParser::appItoa(inspireCost) + "��\n����Ѫ��������" + crArgumentParser::appItoa(inspireExtra/10.0f) + "%";
				char tmpText[32];
				if (itemcount >= 1)
				{
					sprintf(tmpText, "1���ܽ���\0");
				}
				else
				{
					sprintf(tmpText, "%d���/Ԫ��\0",inspireCost);
				}
				cfg_script.Add("Hypertext");
				cfg_script.Push("Hypertext");

				cfg_script.Add("Content");
				cfg_script.Push("Content", 1);
				v_i.clear();
				v_i.push_back(0.0f);
				v_i.push_back(0.0f);
				v_i.push_back(0.0f);
				v_i.push_back(255.0f);
				cfg_script.Add("Color", v_i);
				cfg_script.Add("Text", "  ����");
				cfg_script.Pop();

				cfg_script.Add("Content");
				cfg_script.Push("Content", 2);
				v_i.clear();
				v_i.push_back(140.0f);
				v_i.push_back(40.0f);
				v_i.push_back(40.0f);
				v_i.push_back(255.0f);
				cfg_script.Add("Color", v_i);
				cfg_script.Add("Text", tmpText);
				cfg_script.Pop();

				cfg_script.Add("Content");
				cfg_script.Push("Content", 3);
				v_i.clear();
				v_i.push_back(0.0f);
				v_i.push_back(0.0f);
				v_i.push_back(0.0f);
				v_i.push_back(255.0f);
				cfg_script.Add("Color", v_i);
				cfg_script.Add("Text", "����2%Ѫ���͹���");
				cfg_script.Pop();

				cfg_script.Pop();
				tipsText->setHypertext(cfg_script);
			}
			else
			{
				cfg_script.Add("Hypertext");
				cfg_script.Push("Hypertext");

				cfg_script.Add("Content");
				cfg_script.Push("Content", 1);
				v_i.clear();
				v_i.push_back(0.0f);
				v_i.push_back(0.0f);
				v_i.push_back(0.0f);
				v_i.push_back(255.0f);
				cfg_script.Add("Color", v_i);
				cfg_script.Add("Text", "���������꣬����vip�����Ӵ���");
				cfg_script.Pop();

				cfg_script.Pop();
				tipsText->setHypertext(cfg_script);
				//str = "��Ҫ���vip�ȼ�����ʹ��\n����Ѫ��������";
			}


			//if(!str.empty())
			//{
				//tipstext->setString(str);
				const crBoundingBox &btnbox = bt->getBoundBox();
				const crBoundingBox &tipsbox = tips->getBoundBox();
				//const crMatrix &mat = m_this->getParentCanvas()->getMatrix();
				float posx = btnbox.center().x()-btnbox.xLength()*0.5f+tipsbox.xLength()*0.5 - 0.3;
				float posy = btnbox.center().y()-btnbox.yLength()*0.5 - 0.05;
				//float posy = (btnbox.m_min[1]+1.5f*(btnbox.m_max[1]-btnbox.m_min[1]));
				////////////
				//crVector2 mouse(crVector2(posx,posy));
				tips->setMatrix(crMatrix::translate(posx,posy,0.0f));
				crFilterRenderManager::getInstance()->showCanvas(tips,true);
			//}
		}
	}
}

/////////////////////////////////////////
//
//crJXJUICopyBattleUserTipMethod
//ս������tips
//
/////////////////////////////////////////
crJXJUICopyBattleUserTipMethod::crJXJUICopyBattleUserTipMethod()
{
}

crJXJUICopyBattleUserTipMethod::crJXJUICopyBattleUserTipMethod(const crJXJUICopyBattleUserTipMethod& handle):
	crMethod(handle),
	m_tips(handle.m_tips),
	m_tipstext(handle.m_tipstext)
{
}
void crJXJUICopyBattleUserTipMethod::inputParam(int i, void *param)
{
	switch(i) 
	{
	case 0:
		if(param == 0)
		{//�ͷ�
			m_this = NULL;
		}
		break;
	case 1:
		m_this = (crWidgetNode*)param;
		break;
	}
}
void crJXJUICopyBattleUserTipMethod::addParam(int i, const std::string& str)
{
	switch(i) 
	{
	case 0:
		m_tips = str;
		break;
	case 1:
		m_tipstext = str;
		break;
	}
}

void crJXJUICopyBattleUserTipMethod::operator()(crHandle &handle)
{
	crCanvasNode *tips = crFilterRenderManager::getInstance()->findCanvas(m_tips);
	if(tips)
	{
		crStaticTextWidgetNode *tipstext = dynamic_cast<crStaticTextWidgetNode *>(tips->getWidget(m_tipstext));
		if(tipstext)
		{
			std::string str = "����С����";

			if(tipstext)tipstext->setString(str);
			const crBoundingBox &btnbox = m_this->getBoundBox();
			const crBoundingBox &tipsbox = tips->getBoundBox();
			const crMatrix &mat = m_this->getParentCanvas()->getMatrix();
			float posx = btnbox.m_min[0];
			float posy = (btnbox.m_min[1] - tipsbox.yLength()/2);
			//float posy = (btnbox.m_min[1]+1.5f*(btnbox.m_max[1]-btnbox.m_min[1]));
			////////////
			crVector2 mouse(crVector2(posx,posy));
			tips->setMatrix(crMatrix::translate(mouse[0],mouse[1],0.0f) * mat);
			crFilterRenderManager::getInstance()->showCanvas(tips,true);
		}
	}
}

/////////////////////////////////////////
//
//crJXJUIHuigouTipMethod
//�ع���Ʒtips
//
/////////////////////////////////////////
crJXJUIHuigouTipMethod::crJXJUIHuigouTipMethod()
{
}

crJXJUIHuigouTipMethod::crJXJUIHuigouTipMethod(const crJXJUIHuigouTipMethod& handle):
	crMethod(handle),
	m_tips(handle.m_tips),
	m_tipstext(handle.m_tipstext)
{
}
void crJXJUIHuigouTipMethod::inputParam(int i, void *param)
{
	switch(i) 
	{
	case 0:
		if(param == 0)
		{//�ͷ�
			m_this = NULL;
		}
		break;
	case 1:
		m_this = (crWidgetNode*)param;
		break;
	}
}
void crJXJUIHuigouTipMethod::addParam(int i, const std::string& str)
{
	switch(i) 
	{
	case 0:
		m_tips = str;
		break;
	case 1:
		m_tipstext = str;
		break;
	case 2:
		m_index = atoi(str.c_str());
	}
}

void crJXJUIHuigouTipMethod::operator()(crHandle &handle)
{
	crCanvasNode *tips = crFilterRenderManager::getInstance()->findCanvas(m_tips);
	if(tips)
	{
		crStaticTextWidgetNode *tipstext = dynamic_cast<crStaticTextWidgetNode *>(tips->getWidget(m_tipstext));
		if(tipstext)
		{
			std::string str = "";
			crTableIO::StrVec record;
			int id = 0;
			int itemCount = 0;
			crPlayerGameData *myPlayer = crMyPlayerData::getInstance()->getPlayerGameData();
			if(myPlayer)
			{
				crData *data = myPlayer->getDataClass();
				if(data)
				{
					void *param;
					data->getParam(WCHDATA_JXJSaleItemList,param);
					JXJSaleItemList *saleitemlist = (JXJSaleItemList*)param;
					JXJSaleItemList::iterator itr;
					int i = 0;
					for(itr = saleitemlist->begin();itr!=saleitemlist->end();++itr,++i)
					{
						if (i == m_index && (*itr)->getItemCount()>0)
						{
							id = (*itr)->getItemID();
							itemCount = (*itr)->getItemCount();

							ref_ptr<crTableIO> item_tab = crGlobalHandle::gData()->gGlobalTable(WCHDATA_JXJItemTab);
							int huigouPriceIndex = item_tab->getTitleIndex("�ع��۸�");
							int nameIndex = item_tab->getTitleIndex("name");
							item_tab->queryOneRecord(0,crArgumentParser::appItoa(id),record);
							str += "\n";
							str += record[nameIndex];//����
							str += " *";
							str += crArgumentParser::appItoa(itemCount);//����
							str += "\n �ع��۸�";
							str += record[huigouPriceIndex];
							str += "ͭǮ/��";
							if(tipstext)tipstext->setString(str);
							const crBoundingBox &btnbox = m_this->getBoundBox();
							const crBoundingBox &tipsbox = tips->getBoundBox();
							const crMatrix &mat = m_this->getParentCanvas()->getMatrix();
							float posx = btnbox.m_min[0];
							float posy = (btnbox.m_min[1] - tipsbox.yLength()/2);
							//float posy = (btnbox.m_min[1]+1.5f*(btnbox.m_max[1]-btnbox.m_min[1]));
							////////////
							crVector2 mouse(crVector2(posx,posy));
							tips->setMatrix(crMatrix::translate(mouse[0],mouse[1],0.0f) * mat);
							crFilterRenderManager::getInstance()->showCanvas(tips,true);
						}
					}
				}
			}
		}
	}
}
/////////////////////////////////////////
//
//crJXJUIAppointCardTipMethod
//ί�ν���tips
//
/////////////////////////////////////////
crJXJUIAppointCardTipMethod::crJXJUIAppointCardTipMethod()
{
}

crJXJUIAppointCardTipMethod::crJXJUIAppointCardTipMethod(const crJXJUIAppointCardTipMethod& handle):
	crMethod(handle),
	m_tips(handle.m_tips),
	m_tipstext(handle.m_tipstext)
{
}
void crJXJUIAppointCardTipMethod::inputParam(int i, void *param)
{
	switch(i) 
	{
	case 0:
		if(param == 0)
		{//�ͷ�
			m_this = NULL;
		}
		break;
	case 1:
		m_this = (crWidgetNode*)param;
		break;
	}
}
void crJXJUIAppointCardTipMethod::addParam(int i, const std::string& str)
{
	switch(i) 
	{
	case 0:
		m_tips = str;
		break;
	case 1:
		m_tipstext = str;
		break;
	}
}

void crJXJUIAppointCardTipMethod::operator()(crHandle &handle)
{
	crCanvasNode *tips = crFilterRenderManager::getInstance()->findCanvas(m_tips);
	if(tips)
	{
		crStaticTextWidgetNode *tipstext = dynamic_cast<crStaticTextWidgetNode *>(tips->getWidget(m_tipstext));
		if(tipstext)
		{
			std::string str = "��������������ǲ";

			if(tipstext)tipstext->setString(str);
			const crBoundingBox &btnbox = m_this->getBoundBox();
			const crBoundingBox &tipsbox = tips->getBoundBox();
			const crMatrix &mat = m_this->getParentCanvas()->getMatrix();
			float posx = btnbox.m_min[0];
			float posy = (btnbox.m_min[1] - tipsbox.yLength()/2);
			//float posy = (btnbox.m_min[1]+1.5f*(btnbox.m_max[1]-btnbox.m_min[1]));
			////////////
			crVector2 mouse(crVector2(posx,posy));
			tips->setMatrix(crMatrix::translate(mouse[0],mouse[1],0.0f) * mat);
			crFilterRenderManager::getInstance()->showCanvas(tips,true);
		}
	}
}

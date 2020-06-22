/**********************************************************************
*
*	�ļ�:	   appMethod7.cpp
*
*	����:	   
*
*	����:	    
*					  
* 
**********************************************************************/
#include <rbody/Creature3D/CreBody.h>
#include <JXJ/appMethod7.h>
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

using namespace CRCore;
using namespace CRNetApp;
using namespace CREncapsulation;
using namespace JXJ;
using namespace CRDataBase;
using namespace CRNet;
using namespace CRUI;


///////////////////////////////////////////
////
////crJXJAccomplishZhengzhantianxiaWinCountMethod
////�ɾ�-����-��ս����ʤ������
////
///////////////////////////////////////////
//crJXJAccomplishZhengzhantianxiaWinCountMethod::crJXJAccomplishZhengzhantianxiaWinCountMethod():
//	m_this(NULL),
//	m_mode(0),
//	m_time(0)
//{
//}
//crJXJAccomplishZhengzhantianxiaWinCountMethod::crJXJAccomplishZhengzhantianxiaWinCountMethod(const crJXJAccomplishZhengzhantianxiaWinCountMethod& handle):
//	crMethod(handle),
//	m_this(NULL),
//	m_mode(handle.m_mode),
//	m_canvas(handle.m_canvas),
//	m_time(handle.m_time)
//{
//}
//void crJXJAccomplishZhengzhantianxiaWinCountMethod::inputParam(int i, void *param)
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
//		m_this = (crJXJAccomplish*)param;
//		break;
//	}
//}
//void crJXJAccomplishZhengzhantianxiaWinCountMethod::addParam(int i, const std::string& str)
//{
//	switch(i)
//	{
//	case 0:
//		m_mode = atoi(str.c_str());
//		break;
//	case 1:
//		m_canvas = str;
//		break;
//	case 2:
//		m_time = atoi(str.c_str());
//		break;
//	}
//}
//void crJXJAccomplishZhengzhantianxiaWinCountMethod::operator()(crHandle &handle)
//{
//	CRNetApp::crPlayerGameData *myPlayer = crMyPlayerData::getInstance()->getPlayerGameData();
//	if(myPlayer)
//	{
//		CRCore::crData *playerData = myPlayer->getDataClass();
//		CRCore::crData *mainroledata = myPlayer->getMainRole()->getDataClass();
//		if(mainroledata)
//		{
//			void *param;
//			mainroledata->getParam(WCHDATA_JXJAccomplishMap,param);
//			AccomplishMap *accomplishMap = (AccomplishMap*)param;
//
//			CREncapsulation::crTableIO *accomplish_tab = crGlobalHandle::gData()->gGlobalTable(WCHDATA_JXJAccomplishTab);
//			if(accomplish_tab)
//			{
//				int AchievementIdIndex = accomplish_tab->getTitleIndex("id");
//				int remarkIndex = accomplish_tab->getTitleIndex("��ע");
//				int titleOneIndex = accomplish_tab->getTitleIndex("title1");
//
//				crTableIO::StrVec record;
//				crTableIO::DataVec ZhouRecords;
//				int nameIndex = accomplish_tab->getTitleIndex("Name");
//
//				//�����ݵ�ͨ��
//				accomplish_tab->queryRecords(titleOneIndex, "����", remarkIndex, crArgumentParser::appItoa(2), ZhouRecords);//����1��title1��һ���е���"����"���У�����2����ע��һ���е���"0"���С��������lordLvRecords��
//
//				mainroledata->excHandle(MAKECREPARAM(WCH_LockData,1));
//
//				AccomplishMap::iterator itr;
//				//for(AccomplishMap::iterator itr = accomplishMap->begin(); itr != accomplishMap->end(); ++itr)
//				if(accomplishMap && ZhouRecords.size() > 0)
//				{
//					for(int i = 0; i < ZhouRecords.size(); ++i)
//					{
//						std::string zhouName = ZhouRecords[i][nameIndex].substr(0,4);//��Ҫname�е�������ʽΪ��"����"+"����"
//						unsigned char zhouStep = searchZhouFubenPassNum(zhouName);
//						int achievementId = atoi(ZhouRecords[i][AchievementIdIndex].c_str());
//						itr = accomplishMap->find(achievementId);
//						if(!itr->second->isComplete())
//						{
//							itr->second->setStep(zhouStep);
//						}
//					}
//				}
//				mainroledata->excHandle(MAKECREPARAM(WCH_LockData,0));	
//			}
//		}
//	}
//}
//
//bool crJXJAccomplishZhengzhantianxiaWinCountMethod::isFubenPass(int fubenId)
//{
//	bool isComplete = false;
//
//	CRNetApp::crPlayerGameData *myPlayer = crMyPlayerData::getInstance()->getPlayerGameData();
//	if(myPlayer)
//	{
//		CRCore::crData *playerData = myPlayer->getDataClass();
//		if(playerData)
//		{
//			void *param;
//			playerData->excHandle(MAKECREPARAM(WCH_LockData,1));
//			playerData->getParam(WCHDATA_JXJFubenProgressMap,param);
//			FubenProgressMap *fubenProgressMap = (FubenProgressMap *)param;
//			FubenProgressMap::iterator itr = fubenProgressMap->find(fubenId);
//			if(itr != fubenProgressMap->end())
//			{
//				isComplete = itr->second->getComplete();
//			}
//			playerData->excHandle(MAKECREPARAM(WCH_LockData,0));
//		}
//	}
//	return isComplete; 
//}
//unsigned char crJXJAccomplishZhengzhantianxiaWinCountMethod::searchZhouFubenPassNum(std::string zhouName)
//{
//	unsigned char ZhoufubenPassNum = 0;
//	CRNetApp::crPlayerGameData *myPlayer = crMyPlayerData::getInstance()->getPlayerGameData();
//	if(myPlayer)
//	{
//		CRCore::crData *playerData = myPlayer->getDataClass();
//		if(playerData)
//		{
//			int passcount = 0;
//			int m_zhouPassNum = 0;
//			CREncapsulation::crTableIO *chapter_table = CRNetApp::crGlobalHandle::gData()->gGlobalTable(WCHDATA_JXJChapterTab);
//			int nameIndex = chapter_table->getTitleIndex("��ע");
//			int idIndex = chapter_table->getTitleIndex("id");
//			crTableIO::StrVec record;
//			chapter_table->queryOneRecord(nameIndex, zhouName, record);//ͨ����������chapterId
//			std::string chapterId = record[idIndex];
//
//			CREncapsulation::crTableIO *fuben_table = CRNetApp::crGlobalHandle::gData()->gGlobalTable(WCHDATA_JXJFubenTab);
//			int chapteridIndex = fuben_table->getTitleIndex("chapterid");
//			int fubenIdIndex = fuben_table->getTitleIndex("id");//����id
//
//			crTableIO::DataVec records;
//			fuben_table->queryRecords(chapteridIndex, chapterId, records);
//
//			ZhoufubenPassNum = 0;//һ��������ͨ���ĸ���������
//			for(int i = 0; i < records.size(); ++i)
//			{
//				int fubenId = atoi((records[i][fubenIdIndex]).c_str());
//				if(isFubenPass(fubenId))
//				{
//					ZhoufubenPassNum++;
//				}
//			}
//		}
//	}
//	return ZhoufubenPassNum;
//}
//
///////////////////////////////////////////
////
////crJXJAccomplishQueryLordMethod
////�ɾ�-����
////
///////////////////////////////////////////
//crJXJAccomplishQueryLordMethod::crJXJAccomplishQueryLordMethod():
//	m_this(NULL),
//	m_mode(0),
//	m_time(0)
//{
//}
//crJXJAccomplishQueryLordMethod::crJXJAccomplishQueryLordMethod(const crJXJAccomplishQueryLordMethod& handle):
//	crMethod(handle),
//	m_this(NULL),
//	m_mode(handle.m_mode),
//	m_canvas(handle.m_canvas),
//	m_time(handle.m_time)
//{
//}
//void crJXJAccomplishQueryLordMethod::inputParam(int i, void *param)
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
//		m_this = (crJXJAccomplish*)param;
//		break;
//	}
//}
//void crJXJAccomplishQueryLordMethod::addParam(int i, const std::string& str)
//{
//	switch(i)
//	{
//	case 0:
//		m_mode = atoi(str.c_str());
//		break;
//	case 1:
//		m_canvas = str;
//		break;
//	case 2:
//		m_time = atoi(str.c_str());
//		break;
//	}
//}
//void crJXJAccomplishQueryLordMethod::operator()(crHandle &handle)
//{
//	CRNetApp::crPlayerGameData *myPlayer = crMyPlayerData::getInstance()->getPlayerGameData();
//	if(myPlayer)
//	{
//		CRCore::crData *playerData = myPlayer->getDataClass();
//		CRCore::crData *mainroledata = myPlayer->getMainRole()->getDataClass();
//		if(mainroledata)
//		{
//			void *param;
//			mainroledata->getParam(WCHDATA_JXJAccomplishMap,param);
//			AccomplishMap *accomplishMap = (AccomplishMap*)param;
//
//			CREncapsulation::crTableIO *accomplish_tab = crGlobalHandle::gData()->gGlobalTable(WCHDATA_JXJAccomplishTab);
//			if(accomplish_tab)
//			{
//				int AchievementIdIndex = accomplish_tab->getTitleIndex("id");
//				int remarkIndex = accomplish_tab->getTitleIndex("��ע");
//				int titleOneIndex = accomplish_tab->getTitleIndex("title1");
//
//				crTableIO::StrVec record;
//				crTableIO::DataVec records;
//				int nameIndex = accomplish_tab->getTitleIndex("Name");
//
//				crTableIO::DataVec lordCooperRecords, lordGoldRecords;
//				void *param;
//
//				mainroledata->excHandle(MAKECREPARAM(WCH_LockData,1));
//				AccomplishMap::iterator itr;
//
//				//�����ȼ�
//				accomplish_tab->queryRecords(titleOneIndex, "����", remarkIndex, crArgumentParser::appItoa(0), records);
//
//				mainroledata->getParam(WCHDATA_Level,param);
//				unsigned char lv = *(unsigned char *)param;
//				for(int i = 0; i < records.size(); ++i)
//				{
//					int achievementId = atoi(records[i][AchievementIdIndex].c_str());
//					itr = accomplishMap->find(achievementId);
//					if(!itr->second->isComplete())
//					{
//						itr->second->setStep(lv);
//					}
//				}
//				//����ͭ��
//				accomplish_tab->queryRecords(titleOneIndex, "����", remarkIndex, crArgumentParser::appItoa(1), lordCooperRecords);
//				if(accomplishMap && lordCooperRecords.size() > 0)
//				{
//					playerData->getParam(WCHDATA_JXJCoppercash,param);
//					int coppercash = *(int *)param;
//					int copperStep = coppercash/100000;		
//					if(copperStep>255)copperStep = 255;
//					for(int i = 0; i < lordCooperRecords.size(); ++i)
//					{
//						int achievementId = atoi(lordCooperRecords[i][AchievementIdIndex].c_str());
//						itr = accomplishMap->find(achievementId);
//						if(!itr->second->isComplete())
//						{
//							itr->second->setStep(copperStep);
//						}
//					}
//				}
//
//				//��������Ԫ��
//				accomplish_tab->queryRecords(titleOneIndex, "����", remarkIndex, crArgumentParser::appItoa(2), lordGoldRecords);
//				if(accomplishMap && lordGoldRecords.size() > 0)
//				{
//					playerData->getParam(WCHDATA_JXJGoldingot,param);
//					int goldingot = *(int *)param;
//					int goldStep = (goldingot>0) ? 1:0; 
//					for(int i = 0; i < lordGoldRecords.size(); ++i)
//					{
//						int achievementId = atoi(lordGoldRecords[i][AchievementIdIndex].c_str());
//						itr = accomplishMap->find(achievementId);
//						if(!itr->second->isComplete())
//						{
//							itr->second->setStep(goldStep);
//						}
//					}
//				}
//
//				crTableIO *itemtab = crGlobalHandle::gData()->gGlobalTable(WCHDATA_JXJItemTab);
//				int maxnumindex = itemtab->getTitleIndex("��������");
//				int typeindex = itemtab->getTitleIndex("����");
//				int qualityindex = itemtab->getTitleIndex("Ʒ��");
//				//int nameIndex = itemtab->getTitleIndex("name");
//				crTableIO::StrVec itemrecord, lordEquipRecord;
//
//				//������װ
//				if(accomplishMap)
//				{
//					playerData->getParam(WCHDATA_JXJItemBagVec,param);
//					JXJItemBagVec *bagvec = (JXJItemBagVec *)param;
//					JXJItemBagVec::iterator bagItr;
//					int equipStep = 0; 
//					for(bagItr = bagvec->begin(); bagItr != bagvec->end(); ++bagItr)
//					{
//						int itemId = bagItr->get()->getItemID();
//						itemtab->queryOneRecord(0,crArgumentParser::appItoa(itemId),itemrecord);
//						int quality = atoi(itemrecord[qualityindex].c_str());
//						if(quality==CardColor_Blue)
//						{
//							equipStep = 1; 
//							break;
//						}
//					}
//					if(accomplish_tab->queryOneRecord(titleOneIndex, "����", remarkIndex, crArgumentParser::appItoa(3), lordEquipRecord))
//					{
//						int achievementId = atoi(lordEquipRecord[AchievementIdIndex].c_str());
//						itr = accomplishMap->find(achievementId);
//						if(!itr->second->isComplete())
//						{
//							itr->second->setStep(equipStep);
//						}
//					}
//				}			
//				//������װ
//				if(accomplishMap)
//				{
//					playerData->getParam(WCHDATA_JXJItemBagVec,param);
//					JXJItemBagVec *bagvec = (JXJItemBagVec *)param;
//					JXJItemBagVec::iterator bagItr;
//					int equipStep = 0; 
//					for(bagItr = bagvec->begin(); bagItr != bagvec->end(); ++bagItr)
//					{
//						int itemId = bagItr->get()->getItemID();
//						itemtab->queryOneRecord(0,crArgumentParser::appItoa(itemId),itemrecord);
//						int quality = atoi(itemrecord[qualityindex].c_str());
//						if(quality==CardColor_Purple)
//						{
//							equipStep = 1; 
//							break;
//						}
//					}
//					if(accomplish_tab->queryOneRecord(titleOneIndex, "����", remarkIndex, crArgumentParser::appItoa(4), lordEquipRecord))
//					{
//						int achievementId = atoi(lordEquipRecord[AchievementIdIndex].c_str());
//						itr = accomplishMap->find(achievementId);
//						if(!itr->second->isComplete())
//						{
//							itr->second->setStep(equipStep);
//						}
//					}
//				}			
//				//������װ
//				if(accomplishMap)
//				{
//					playerData->getParam(WCHDATA_JXJItemBagVec,param);
//					JXJItemBagVec *bagvec = (JXJItemBagVec *)param;
//					JXJItemBagVec::iterator bagItr;
//					int equipStep = 0; 
//					for(bagItr = bagvec->begin(); bagItr != bagvec->end(); ++bagItr)
//					{
//						int itemId = bagItr->get()->getItemID();
//						itemtab->queryOneRecord(0,crArgumentParser::appItoa(itemId),itemrecord);
//						int quality = atoi(itemrecord[qualityindex].c_str());
//						if(quality>=CardColor_Orange)
//						{
//							equipStep = 1; 
//							break;
//						}
//					}
//					if(accomplish_tab->queryOneRecord(titleOneIndex, "����", remarkIndex, crArgumentParser::appItoa(5), lordEquipRecord))
//					{
//						int achievementId = atoi(lordEquipRecord[AchievementIdIndex].c_str());
//						itr = accomplishMap->find(achievementId);
//						if(!itr->second->isComplete())
//						{
//							itr->second->setStep(equipStep);
//						}
//					}
//				}
//				//������װ
//				//accomplish_tab->queryRecords(titleOneIndex, "����", remarkIndex, crArgumentParser::appItoa(3), lordBuleEquipRecords);
//				//if(accomplishMap && lordGoldRecords.size() > 0)
//				//{
//				//	playerData->getParam(WCHDATA_JXJItemBagVec,param);
//				//	JXJItemBagVec *bagvec = (JXJItemBagVec *)param;
//				//	JXJItemBagVec::iterator bagItr;
//				//	int equipStep = 0; 
//				//	for(bagItr = bagvec->begin(); bagItr != bagvec->end(); ++bagItr)
//				//	{
//				//		int itemId = bagItr->get()->getItemID();
//				//		itemtab->queryOneRecord(0,crArgumentParser::appItoa(itemId),itemrecord);
//				//		int quality = atoi(itemrecord[qualityindex].c_str());
//				//		if(quality>=CardColor_Orange)
//				//		{
//				//			equipStep = 1; 
//				//			break;
//				//		}
//				//	}
//
//				//	for(int i = 0; i < lordBuleEquipRecords.size(); ++i)
//				//	{
//				//		int achievementId = atoi(lordBuleEquipRecords[i][AchievementIdIndex].c_str());
//				//		itr = accomplishMap->find(achievementId);
//				//		if(!itr->second->isComplete())
//				//		{
//				//			itr->second->setStep(equipStep);
//				//		}
//				//	}
//				//}
//				//������ְ
//				accomplish_tab->queryRecords(titleOneIndex, "����", remarkIndex, crArgumentParser::appItoa(7), records);
//
//				mainroledata->getParam(WCHDATA_JXJGovPost,param);
//				lv = *(unsigned char *)param;
//				for(int i = 0; i < records.size(); ++i)
//				{
//					int achievementId = atoi(records[i][AchievementIdIndex].c_str());
//					itr = accomplishMap->find(achievementId);
//					if(!itr->second->isComplete())
//					{
//						itr->second->setStep(lv);
//					}
//				}
//
//				mainroledata->excHandle(MAKECREPARAM(WCH_LockData,0));	
//			}
//		}
//	}
//}
//
///////////////////////////////////////////
////
////crJXJAccomplishFengdiMethod
////�ɾ�-����-��ս����ʤ������
////
///////////////////////////////////////////
//crJXJAccomplishFengdiMethod::crJXJAccomplishFengdiMethod():
//	m_this(NULL),
//	m_mode(0),
//	m_time(0)
//{
//}
//crJXJAccomplishFengdiMethod::crJXJAccomplishFengdiMethod(const crJXJAccomplishFengdiMethod& handle):
//	crMethod(handle),
//	m_this(NULL),
//	m_mode(handle.m_mode),
//	m_canvas(handle.m_canvas),
//	m_time(handle.m_time)
//{
//}
//void crJXJAccomplishFengdiMethod::inputParam(int i, void *param)
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
//		m_this = (crJXJAccomplish*)param;
//		break;
//	}
//}
//void crJXJAccomplishFengdiMethod::addParam(int i, const std::string& str)
//{
//	switch(i)
//	{
//	case 0:
//		m_mode = atoi(str.c_str());
//		break;
//	case 1:
//		m_canvas = str;
//		break;
//	case 2:
//		m_time = atoi(str.c_str());
//		break;
//	}
//}
//void crJXJAccomplishFengdiMethod::operator()(crHandle &handle)
//{
//	return;
//	playerData->excHandle(MAKECREPARAM(WCH_LockData,1));
//
//	//���õȼ�
//	setAccomplishStep(playerData, "���", 0, WCHDATA_JXJFuyalv);
//	//��ӵȼ�
//	setAccomplishStep("���", 1, WCHDATA_JXJMingjulv1, 8);
//	//�����ȼ�
//	setAccomplishStep(playerData, "���", 2, WCHDATA_JXJJiusilv);		
//	//����ȼ�
//	setAccomplishStep(playerData, "���", 3, WCHDATA_JXJFukulv);
//	//���еȼ�
//	setAccomplishStep(playerData, "���", 4, WCHDATA_JXJShijilv);
//	//�����ȼ�
//	setAccomplishStep(playerData, "���", 5, WCHDATA_JXJGongfanglv);
//	//��Ӫ�ȼ�
//	setAccomplishStep(playerData, "���", 6, WCHDATA_JXJBingyinglv);
//	//�����ȼ�
//	setAccomplishStep("���", 7, WCHDATA_JXJMuchanglv1, 4);
//	//ũ��ȼ�
//	setAccomplishStep("���", 8, WCHDATA_JXJNongtianlv1, 8);
//	//�ֵصȼ�
//	setAccomplishStep("���", 9, WCHDATA_JXJLingdilv1, 4);
//	//��ɽ�ȼ�
//	setAccomplishStep("���", 10, WCHDATA_JXJKuangshanlv1, 4);
//
//	playerData->excHandle(MAKECREPARAM(WCH_LockData,0));	
//	//		}
//	//	}
//	//}
//}
//int crJXJAccomplishFengdiMethod::initAccomplishData()
//{
//	myPlayer = crMyPlayerData::getInstance()->getPlayerGameData();
//	if(myPlayer)
//	{
//		playerData = myPlayer->getDataClass();
//
//		mainroledata = myPlayer->getMainRole()->getDataClass();
//		if(mainroledata)
//		{
//			void *param;
//			mainroledata->getParam(WCHDATA_JXJAccomplishMap,param);
//			accomplishMap = (AccomplishMap*)param;
//
//			accomplish_tab = crGlobalHandle::gData()->gGlobalTable(WCHDATA_JXJAccomplishTab);
//			if(accomplish_tab)
//			{
//				AchievementIdIndex = accomplish_tab->getTitleIndex("id");
//				remarkIndex = accomplish_tab->getTitleIndex("��ע");
//				titleOneIndex = accomplish_tab->getTitleIndex("title1");
//			}
//		}
//	}
//	return 0;
//}
//int crJXJAccomplishFengdiMethod::setAccomplishStep(crData *data, std::string titleOne, int remarksId, int WCHDATA_JXJ_id)//���жಽ�ĳɾ��ж�
//{
//	if(accomplish_tab)
//	{
//		crTableIO::DataVec records;
//		if(data && accomplishMap)
//		{
//			void *param;
//			AccomplishMap::iterator itr;
//			accomplish_tab->queryRecords(titleOneIndex, titleOne, remarkIndex, crArgumentParser::appItoa(remarksId), records);
//
//			data->getParam(WCHDATA_JXJ_id,param);
//			unsigned char lv = *(unsigned char *)param;
//			for(int i = 0; i < records.size(); ++i)
//			{
//				int achievementId = atoi(records[i][AchievementIdIndex].c_str());
//				itr = accomplishMap->find(achievementId);
//				if(!itr->second->isComplete())
//				{
//					itr->second->setStep(lv);
//				}
//			}
//		}
//	}
//	return 0;
//}
//int crJXJAccomplishFengdiMethod::setAccomplishStep(std::string titleOne, int remarksId, int WCHDATA_JXJ_id, int WCHDATA_JXJ_num)//���ж��WCHDATA_JXJ_id�ĳɾ��ж�
//{
//	if(accomplish_tab)
//	{
//		crTableIO::DataVec records;
//		if(playerData && accomplishMap)
//		{
//			void *param;
//			AccomplishMap::iterator itr;
//			accomplish_tab->queryRecords(titleOneIndex, titleOne, remarkIndex, crArgumentParser::appItoa(remarksId), records);
//			if(WCHDATA_JXJ_id > 20000)
//			{
//				playerData->getParam(WCHDATA_JXJ_id,param);
//				unsigned char  minLv = *(unsigned char *)param;
//				int totalId = WCHDATA_JXJ_id + WCHDATA_JXJ_num;
//				for(int id = WCHDATA_JXJ_id + 1; id < totalId; ++id)
//				{
//					playerData->getParam(id,param);
//					unsigned char  lv = *(unsigned char *)param;
//					playerData->getParam(id,param);
//					if(minLv > lv)
//					{
//						minLv = lv;
//					}
//				}
//				for(int i = 0; i < records.size(); ++i)
//				{
//					int achievementId = atoi(records[i][AchievementIdIndex].c_str());
//					itr = accomplishMap->find(achievementId);
//					if(!itr->second->isComplete())
//					{
//						itr->second->setStep(minLv);
//					}
//				}
//			}
//		}
//	}
//	return 0;
//}
///////////////////////////////////////////
////
////crJXJShowAchievementStepMethod
////
///////////////////////////////////////////
//crJXJShowAchievementStepMethod::crJXJShowAchievementStepMethod():
//	m_this(NULL),
//	m_mode(0),
//	m_time(0)
//{
//}
//crJXJShowAchievementStepMethod::crJXJShowAchievementStepMethod(const crJXJShowAchievementStepMethod& handle):
//	crMethod(handle),
//	m_this(NULL),
//	m_mode(handle.m_mode),
//	m_canvas(handle.m_canvas),
//	m_time(handle.m_time)
//{
//}
//void crJXJShowAchievementStepMethod::inputParam(int i, void *param)
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
//		m_this = (crJXJAccomplish*)param;
//		break;
//	case 2:
//		if(param)
//		{
//			CREPARAM& param64 = *(CREPARAM*)param;
//			m_zhouPassData = *(std::string *)LOINT64(param64);
//			m_achievementIndex = *(int *)HIINT64(param64);
//		}
//
//		//if(param)
//		//{
//		//	CREPARAM& param64 = *(CREPARAM*)param;
//		//	m_type = (int *)LOINT64(param64);
//		//	if (m_type == ChengjiuType_None)
//		//	{
//		//		itembag = (crBagItemData *)HIINT64(param64);
//		//	}
//		//}
//		//else
//		//{
//		//	m_type = 0;
//		//}
//		break;
//	}
//}
//void crJXJShowAchievementStepMethod::addParam(int i, const std::string& str)
//{
//}
//void crJXJShowAchievementStepMethod::operator()(crHandle &handle)
//{
//	switch(m_achievementIndex)
//	{
//	case 0://����ʤ������
//		break;
//
//	}
//}
//int crJXJShowAchievementStepMethod::fubenPass(int id)
//{
//	std::string tmpStr;
//	void *param;
//	unsigned short stepID = 0;
//	int step =  -1;
//	int stepCount = -1;
//	bool fubenComplete;
//
//	crPlayerGameData *playerData = crMyPlayerData::getInstance()->getPlayerGameData();
//	if(playerData)
//	{
//		crRole *mainRole = playerData->getMainRole();
//		if(mainRole)
//		{
//			crJXJAccomplish *mainRoleAccomplish;
//			crData *mainRoleData = mainRole->getDataClass();
//			mainRoleData->excHandle(MAKECREPARAM(WCH_LockData,1));
//			mainRoleData->getParam(WCHDATA_JXJAccomplishMap,param);
//			AccomplishMap *accomplishMap = (AccomplishMap*)param;
//			AccomplishMap::iterator itr = accomplishMap->find(id);
//			if(itr != accomplishMap->end())
//			{
//				mainRoleAccomplish  = itr->second.get();
//				fubenComplete = itr->second->isComplete();
//				stepCount = itr->second->getStepCount();
//				step = itr->second->getStep();
//			}
//			mainRoleData->excHandle(MAKECREPARAM(WCH_LockData,0));
//		}
//	}
//	return step;
//}
////CRNetApp::crPlayerGameData *myPlayer = crMyPlayerData::getInstance()->getPlayerGameData();
////if(myPlayer)
////{
////	CRCore::crData *playerData = myPlayer->getDataClass();
////	CRCore::crData *mainroledata = myPlayer->getMainRole()->getDataClass();
////	if(mainroledata)
////	{
////		void *param;
////		mainroledata->getParam(WCHDATA_JXJAccomplishMap,param);
////		AccomplishMap *accomplishMap = (AccomplishMap*)param;
//
////		CREncapsulation::crTableIO *accomplish_tab = crGlobalHandle::gData()->gGlobalTable(WCHDATA_JXJAccomplishTab);
////		if(accomplish_tab)
////		{
////			int AchievementIdIndex = accomplish_tab->getTitleIndex("id");
////			int remarkIndex = accomplish_tab->getTitleIndex("��ע");
////			int titleOneIndex = accomplish_tab->getTitleIndex("title1");
//
////			crTableIO::StrVec record;
////			crTableIO::DataVec ZhouRecords;
////			int nameIndex = accomplish_tab->getTitleIndex("Name");
///////////////////////////////////////////
////
////crJXJSearchAccomplishCountMethod
////�ɾʹ�ɵ��ж�
////
///////////////////////////////////////////
////crJXJSearchAccomplishCountMethod::crJXJSearchAccomplishCountMethod():
////	m_this(NULL),
////	m_mode(0),
////	m_time(0)
////{
////}
////crJXJSearchAccomplishCountMethod::crJXJSearchAccomplishCountMethod(const crJXJSearchAccomplishCountMethod& handle):
////	crMethod(handle),
////	m_this(NULL),
////	m_mode(handle.m_mode),
////	m_canvas(handle.m_canvas),
////	m_time(handle.m_time)
////{
////}
////void crJXJSearchAccomplishCountMethod::inputParam(int i, void *param)
////{
////	switch(i) 
////	{
////	case 0:
////		if(param == 0)
////		{//�ͷ�
////			m_this = NULL;
////		}
////		break;
////	case 1:
////		m_this = (crJXJAccomplish*)param;
////		break;
////	}
////}
////void crJXJSearchAccomplishCountMethod::addParam(int i, const std::string& str)
////{
////	switch(i)
////	{
////	case 0:
////		m_mode = atoi(str.c_str());
////		break;
////	case 1:
////		m_canvas = str;
////		break;
////	case 2:
////		m_time = atoi(str.c_str());
////		break;
////	}
////}
////void crJXJSearchAccomplishCountMethod::operator()(crHandle &handle)
////{
////	if(myPlayer && playerData && mainroledata)
////	{
////		initAccomplishData();
////		searchFubenAchievement();
////		searchLordAchievement();
////		searchBuildingAchievement();
////	}
////}
////int crJXJSearchAccomplishCountMethod::initAccomplishData()
////{
////	myPlayer = crMyPlayerData::getInstance()->getPlayerGameData();
////	if(myPlayer)
////	{
////		playerData = myPlayer->getDataClass();
////
////		mainroledata = myPlayer->getMainRole()->getDataClass();
////		if(mainroledata)
////		{
////			void *param;
////			mainroledata->getParam(WCHDATA_JXJAccomplishMap,param);
////			accomplishMap = (AccomplishMap*)param;
////
////			accomplish_tab = crGlobalHandle::gData()->gGlobalTable(WCHDATA_JXJAccomplishTab);
////			if(accomplish_tab)
////			{
////				AchievementIdIndex = accomplish_tab->getTitleIndex("id");
////				remarkIndex = accomplish_tab->getTitleIndex("��ע");
////				titleOneIndex = accomplish_tab->getTitleIndex("title1");
////			}
////		}
////	}
////	return 0;
////}
////bool crJXJSearchAccomplishCountMethod::isFubenPass(int fubenId)
////{
////	bool isComplete = false;
////	if(myPlayer && playerData)
////	{
////		void *param;
////		playerData->excHandle(MAKECREPARAM(WCH_LockData,1));
////		playerData->getParam(WCHDATA_JXJFubenProgressMap,param);
////		FubenProgressMap *fubenProgressMap = (FubenProgressMap *)param;
////		FubenProgressMap::iterator itr = fubenProgressMap->find(fubenId);
////		if(itr != fubenProgressMap->end())
////		{
////			isComplete = itr->second->getComplete();
////		}
////		playerData->excHandle(MAKECREPARAM(WCH_LockData,0));
////	}
////	return isComplete; 
////}
//////һ�������渱��������
//////unsigned char crJXJSearchAccomplishCountMethod::searchZhouFubenCount(std::string zhouName)
//////{
//////	unsigned char ZhouFubenNum = 0;
//////	crPlayerGameData *myPlayer = crMyPlayerData::getInstance()->getPlayerGameData();
//////	if(myPlayer)
//////	{
//////		crData *data = myPlayer->getDataClass();
//////		if(data)
//////		{
//////			int passcount = 0;
//////			data->excHandle(MAKECREPARAM(WCH_LockData,1));
//////			int m_zhouPassNum = 0;
//////			CREncapsulation::crTableIO *chapter_table = CRNetApp::crGlobalHandle::gData()->gGlobalTable(WCHDATA_JXJChapterTab);
//////			int nameIndex = chapter_table->getTitleIndex("��ע");
//////			int idIndex = chapter_table->getTitleIndex("id");
//////			crTableIO::StrVec record;
//////			chapter_table->queryOneRecord(nameIndex, zhouName, record);//ͨ����������chapterId
//////			std::string chapterId = record[idIndex];
//////
//////			CREncapsulation::crTableIO *fuben_table = CRNetApp::crGlobalHandle::gData()->gGlobalTable(WCHDATA_JXJFubenTab);
//////			int chapteridIndex = fuben_table->getTitleIndex("chapterid");
//////			int fubenIdIndex = fuben_table->getTitleIndex("id");//����id
//////
//////			crTableIO::DataVec records;
//////			fuben_table->queryRecords(chapteridIndex, chapterId, records);
//////
//////			ZhouFubenNum = records.size();
//////		}
//////	}
//////	return ZhouFubenNum;
//////}
////unsigned char crJXJSearchAccomplishCountMethod::searchZhouFubenPassNum(std::string zhouName)
////{
////	unsigned char ZhoufubenPassNum = 0;
////	if(myPlayer && playerData)
////	{
////		int passcount = 0;
////		int m_zhouPassNum = 0;
////		CREncapsulation::crTableIO *chapter_table = CRNetApp::crGlobalHandle::gData()->gGlobalTable(WCHDATA_JXJChapterTab);
////		int nameIndex = chapter_table->getTitleIndex("��ע");
////		int idIndex = chapter_table->getTitleIndex("id");
////		crTableIO::StrVec record;
////		chapter_table->queryOneRecord(nameIndex, zhouName, record);//ͨ����������chapterId
////		std::string chapterId = record[idIndex];
////
////		CREncapsulation::crTableIO *fuben_table = CRNetApp::crGlobalHandle::gData()->gGlobalTable(WCHDATA_JXJFubenTab);
////		int chapteridIndex = fuben_table->getTitleIndex("chapterid");
////		int fubenIdIndex = fuben_table->getTitleIndex("id");//����id
////
////		crTableIO::DataVec records;
////		fuben_table->queryRecords(chapteridIndex, chapterId, records);
////
////		ZhoufubenPassNum = 0;//һ��������ͨ���ĸ���������
////		for(int i = 0; i < records.size(); ++i)
////		{
////			int fubenId = atoi((records[i][fubenIdIndex]).c_str());
////			if(isFubenPass(fubenId))
////			{
////				ZhoufubenPassNum++;
////			}
////		}
////	}
////	return ZhoufubenPassNum;
////}
////int  crJXJSearchAccomplishCountMethod::searchFubenAchievement()
////{
////	if(playerData && mainroledata && accomplish_tab)
////	{
////		crTableIO::StrVec record;
////		crTableIO::DataVec ZhouRecords;
////		int nameIndex = accomplish_tab->getTitleIndex("Name");
////
////		//�����ݵ�ͨ��
////		accomplish_tab->queryRecords(titleOneIndex, "����", remarkIndex, crArgumentParser::appItoa(2), ZhouRecords);//����1��title1��һ���е���"����"���У�����2����ע��һ���е���"0"���С��������lordLvRecords��
////		
////		mainroledata->excHandle(MAKECREPARAM(WCH_LockData,1));
////
////		AccomplishMap::iterator itr;
////		//for(AccomplishMap::iterator itr = accomplishMap->begin(); itr != accomplishMap->end(); ++itr)
////		if(accomplishMap && ZhouRecords.size() > 0)
////		{
////			for(int i = 0; i < ZhouRecords.size(); ++i)
////			{
////				std::string zhouName = ZhouRecords[i][nameIndex].substr(0,4);//��Ҫname�е�������ʽΪ��"����"+"����"
////				unsigned char zhouStep = searchZhouFubenPassNum(zhouName);
////				int achievementId = atoi(ZhouRecords[i][AchievementIdIndex].c_str());
////				itr = accomplishMap->find(achievementId);
////				if(!itr->second->isComplete())
////				{
////					itr->second->setStep(zhouStep);
////				}
////			}
////		}
////		mainroledata->excHandle(MAKECREPARAM(WCH_LockData,0));	
////	}
////	return 0;
////}
////int crJXJSearchAccomplishCountMethod::searchLordAchievement()
////{
////	if(playerData && mainroledata)
////	{
////		if(accomplish_tab)
////		{
////			crTableIO::StrVec record;
////			crTableIO::DataVec lordCooperRecords, lordGoldRecords;
////			void *param;
////
////			mainroledata->excHandle(MAKECREPARAM(WCH_LockData,1));
////			AccomplishMap::iterator itr;
////			
////			//�����ȼ�
////			setAccomplishStep(mainroledata, "����", 0, WCHDATA_Level);
////
////			//����ͭ��
////			accomplish_tab->queryRecords(titleOneIndex, "����", remarkIndex, crArgumentParser::appItoa(1), lordCooperRecords);
////			if(accomplishMap && lordCooperRecords.size() > 0)
////			{
////				playerData->getParam(WCHDATA_JXJCoppercash,param);
////				int coppercash = *(int *)param;
////				int copperStep = coppercash/100000;		
////				if(copperStep>255)copperStep = 255;
////				for(int i = 0; i < lordCooperRecords.size(); ++i)
////				{
////					int achievementId = atoi(lordCooperRecords[i][AchievementIdIndex].c_str());
////					itr = accomplishMap->find(achievementId);
////					if(!itr->second->isComplete())
////					{
////						itr->second->setStep(copperStep);
////					}
////				}
////			}
////
////			//��������Ԫ��
////			accomplish_tab->queryRecords(titleOneIndex, "����", remarkIndex, crArgumentParser::appItoa(2), lordGoldRecords);
////			if(accomplishMap && lordGoldRecords.size() > 0)
////			{
////				playerData->getParam(WCHDATA_JXJGoldingot,param);
////				int goldingot = *(int *)param;
////				int goldStep = (goldingot>0) ? 1:0; 
////				for(int i = 0; i < lordGoldRecords.size(); ++i)
////				{
////					int achievementId = atoi(lordGoldRecords[i][AchievementIdIndex].c_str());
////					itr = accomplishMap->find(achievementId);
////					if(!itr->second->isComplete())
////					{
////						itr->second->setStep(goldStep);
////					}
////				}
////			}
////
////
////
////			crTableIO *itemtab = crGlobalHandle::gData()->gGlobalTable(WCHDATA_JXJItemTab);
////			int maxnumindex = itemtab->getTitleIndex("��������");
////			int typeindex = itemtab->getTitleIndex("����");
////			int qualityindex = itemtab->getTitleIndex("Ʒ��");
////			int nameIndex = itemtab->getTitleIndex("name");
////			crTableIO::StrVec itemrecord, lordEquipRecord;
////
////			//������װ
////			if(accomplishMap)
////			{
////				playerData->getParam(WCHDATA_JXJItemBagVec,param);
////				JXJItemBagVec *bagvec = (JXJItemBagVec *)param;
////				JXJItemBagVec::iterator bagItr;
////				int equipStep = 0; 
////				for(bagItr = bagvec->begin(); bagItr != bagvec->end(); ++bagItr)
////				{
////					int itemId = bagItr->get()->getItemID();
////					itemtab->queryOneRecord(0,crArgumentParser::appItoa(itemId),itemrecord);
////					int quality = atoi(itemrecord[qualityindex].c_str());
////					if(quality==CardColor_Blue)
////					{
////						equipStep = 1; 
////						break;
////					}
////				}
////				if(accomplish_tab->queryOneRecord(titleOneIndex, "����", remarkIndex, crArgumentParser::appItoa(3), lordEquipRecord))
////				{
////					int achievementId = atoi(lordEquipRecord[AchievementIdIndex].c_str());
////					itr = accomplishMap->find(achievementId);
////					if(!itr->second->isComplete())
////					{
////						itr->second->setStep(equipStep);
////					}
////				}
////			}			
////			//������װ
////			if(accomplishMap)
////			{
////				playerData->getParam(WCHDATA_JXJItemBagVec,param);
////				JXJItemBagVec *bagvec = (JXJItemBagVec *)param;
////				JXJItemBagVec::iterator bagItr;
////				int equipStep = 0; 
////				for(bagItr = bagvec->begin(); bagItr != bagvec->end(); ++bagItr)
////				{
////					int itemId = bagItr->get()->getItemID();
////					itemtab->queryOneRecord(0,crArgumentParser::appItoa(itemId),itemrecord);
////					int quality = atoi(itemrecord[qualityindex].c_str());
////					if(quality==CardColor_Purple)
////					{
////						equipStep = 1; 
////						break;
////					}
////				}
////				if(accomplish_tab->queryOneRecord(titleOneIndex, "����", remarkIndex, crArgumentParser::appItoa(4), lordEquipRecord))
////				{
////					int achievementId = atoi(lordEquipRecord[AchievementIdIndex].c_str());
////					itr = accomplishMap->find(achievementId);
////					if(!itr->second->isComplete())
////					{
////						itr->second->setStep(equipStep);
////					}
////				}
////			}			
////			//������װ
////			if(accomplishMap)
////			{
////				playerData->getParam(WCHDATA_JXJItemBagVec,param);
////				JXJItemBagVec *bagvec = (JXJItemBagVec *)param;
////				JXJItemBagVec::iterator bagItr;
////				int equipStep = 0; 
////				for(bagItr = bagvec->begin(); bagItr != bagvec->end(); ++bagItr)
////				{
////					int itemId = bagItr->get()->getItemID();
////					itemtab->queryOneRecord(0,crArgumentParser::appItoa(itemId),itemrecord);
////					int quality = atoi(itemrecord[qualityindex].c_str());
////					if(quality>=CardColor_Orange)
////					{
////						equipStep = 1; 
////						break;
////					}
////				}
////				if(accomplish_tab->queryOneRecord(titleOneIndex, "����", remarkIndex, crArgumentParser::appItoa(5), lordEquipRecord))
////				{
////					int achievementId = atoi(lordEquipRecord[AchievementIdIndex].c_str());
////					itr = accomplishMap->find(achievementId);
////					if(!itr->second->isComplete())
////					{
////						itr->second->setStep(equipStep);
////					}
////				}
////			}
////			//������װ
////			//accomplish_tab->queryRecords(titleOneIndex, "����", remarkIndex, crArgumentParser::appItoa(3), lordBuleEquipRecords);
////			//if(accomplishMap && lordGoldRecords.size() > 0)
////			//{
////			//	playerData->getParam(WCHDATA_JXJItemBagVec,param);
////			//	JXJItemBagVec *bagvec = (JXJItemBagVec *)param;
////			//	JXJItemBagVec::iterator bagItr;
////			//	int equipStep = 0; 
////			//	for(bagItr = bagvec->begin(); bagItr != bagvec->end(); ++bagItr)
////			//	{
////			//		int itemId = bagItr->get()->getItemID();
////			//		itemtab->queryOneRecord(0,crArgumentParser::appItoa(itemId),itemrecord);
////			//		int quality = atoi(itemrecord[qualityindex].c_str());
////			//		if(quality>=CardColor_Orange)
////			//		{
////			//			equipStep = 1; 
////			//			break;
////			//		}
////			//	}
////
////			//	for(int i = 0; i < lordBuleEquipRecords.size(); ++i)
////			//	{
////			//		int achievementId = atoi(lordBuleEquipRecords[i][AchievementIdIndex].c_str());
////			//		itr = accomplishMap->find(achievementId);
////			//		if(!itr->second->isComplete())
////			//		{
////			//			itr->second->setStep(equipStep);
////			//		}
////			//	}
////			//}
////			//������ְ
////			setAccomplishStep(mainroledata, "����", 7, WCHDATA_JXJGovPost);
////
////			mainroledata->excHandle(MAKECREPARAM(WCH_LockData,0));	
////		}
////	}	
////	return 0;
////}
////int crJXJSearchAccomplishCountMethod::searchBuildingAchievement()
////{
////	playerData->excHandle(MAKECREPARAM(WCH_LockData,1));
////			
////		//���õȼ�
////		setAccomplishStep(playerData, "���", 0, WCHDATA_JXJFuyalv);
////		//��ӵȼ�
////		setAccomplishStep("���", 1, WCHDATA_JXJMingjulv1, 8);
////		//�����ȼ�
////		setAccomplishStep(playerData, "���", 2, WCHDATA_JXJJiusilv);		
////		//����ȼ�
////		setAccomplishStep(playerData, "���", 3, WCHDATA_JXJFukulv);
////		//���еȼ�
////		setAccomplishStep(playerData, "���", 4, WCHDATA_JXJShijilv);
////		//�����ȼ�
////		setAccomplishStep(playerData, "���", 5, WCHDATA_JXJGongfanglv);
////		//��Ӫ�ȼ�
////		setAccomplishStep(playerData, "���", 6, WCHDATA_JXJBingyinglv);
////		//�����ȼ�
////		setAccomplishStep("���", 7, WCHDATA_JXJMuchanglv1, 4);
////		//ũ��ȼ�
////		setAccomplishStep("���", 8, WCHDATA_JXJNongtianlv1, 8);
////		//�ֵصȼ�
////		setAccomplishStep("���", 9, WCHDATA_JXJLingdilv1, 4);
////		//��ɽ�ȼ�
////		setAccomplishStep("���", 10, WCHDATA_JXJKuangshanlv1, 4);
////				
////	playerData->excHandle(MAKECREPARAM(WCH_LockData,0));	
////		
////	return 0;
////}
////	
////
//////int crJXJSearchAccomplishCountMethod::setAccomplishStep(crData *data, std::string titleOne, int remarksId, int WCHDATA_JXJ_id)//װ���ɾ��ж�
//////{
//////	if(accomplishMap)
//////	{
//////		void *param
//////		playerData->getParam(WCHDATA_JXJItemBagVec,param);
//////		JXJItemBagVec *bagvec = (JXJItemBagVec *)param;
//////		JXJItemBagVec::iterator bagItr;
//////		int equipStep = 0; 
//////		for(bagItr = bagvec->begin(); bagItr != bagvec->end(); ++bagItr)
//////		{
//////			int itemId = bagItr->get()->getItemID();
//////			itemtab->queryOneRecord(0,crArgumentParser::appItoa(itemId),itemrecord);
//////			int quality = atoi(itemrecord[qualityindex].c_str());
//////			if(quality>=CardColor_Orange)
//////			{
//////				equipStep = 1; 
//////				break;
//////			}
//////		}
//////		if(accomplish_tab->queryOneRecord(titleOneIndex, "����", remarkIndex, crArgumentParser::appItoa(5), lordBuleEquipRecord))
//////		{
//////			int achievementId = atoi(lordBuleEquipRecord[AchievementIdIndex].c_str());
//////			itr = accomplishMap->find(achievementId);
//////			if(!itr->second->isComplete())
//////			{
//////				itr->second->setStep(equipStep);
//////			}
//////		}
//////	}
//////}
////int crJXJSearchAccomplishCountMethod::setAccomplishStep(crData *data, std::string titleOne, int remarksId, int WCHDATA_JXJ_id)//���жಽ�ĳɾ��ж�
////{
////	if(accomplish_tab)
////	{
////		crTableIO::DataVec records;
////		if(data && accomplishMap)
////		{
////			void *param;
////			AccomplishMap::iterator itr;
////			accomplish_tab->queryRecords(titleOneIndex, titleOne, remarkIndex, crArgumentParser::appItoa(remarksId), records);
////
////			data->getParam(WCHDATA_JXJ_id,param);
////			unsigned char lv = *(unsigned char *)param;
////			for(int i = 0; i < records.size(); ++i)
////			{
////				int achievementId = atoi(records[i][AchievementIdIndex].c_str());
////				itr = accomplishMap->find(achievementId);
////				if(!itr->second->isComplete())
////				{
////					itr->second->setStep(lv);
////				}
////			}
////		}
////	}
////	return 0;
////}
////int crJXJSearchAccomplishCountMethod::setAccomplishStep(std::string titleOne, int remarksId, int WCHDATA_JXJ_id, int WCHDATA_JXJ_num)//���ж��WCHDATA_JXJ_id�ĳɾ��ж�
////{
////	if(accomplish_tab)
////	{
////		crTableIO::DataVec records;
////		if(playerData && accomplishMap)
////		{
////			void *param;
////			AccomplishMap::iterator itr;
////			accomplish_tab->queryRecords(titleOneIndex, titleOne, remarkIndex, crArgumentParser::appItoa(remarksId), records);
////			if(WCHDATA_JXJ_id > 20000)
////			{
////				playerData->getParam(WCHDATA_JXJ_id,param);
////				unsigned char  minLv = *(unsigned char *)param;
////				int totalId = WCHDATA_JXJ_id + WCHDATA_JXJ_num;
////				for(int id = WCHDATA_JXJ_id + 1; id < totalId; ++id)
////				{
////					playerData->getParam(id,param);
////					unsigned char  lv = *(unsigned char *)param;
////					playerData->getParam(id,param);
////					if(minLv > lv)
////					{
////						minLv = lv;
////					}
////				}
////				for(int i = 0; i < records.size(); ++i)
////				{
////					int achievementId = atoi(records[i][AchievementIdIndex].c_str());
////					itr = accomplishMap->find(achievementId);
////					if(!itr->second->isComplete())
////					{
////						itr->second->setStep(minLv);
////					}
////				}
////			}
////
////		}
////	}
////	return 0;
////}
//
//
///////////////////////////////////////////
////
////GeneralTips
////TIPS
////
///////////////////////////////////////////
//
//GeneralTips::GeneralTips(std::string m_tipsCanvas, CRCore::crWidgetNode *m_this)	
//{
//	tips = crFilterRenderManager::getInstance()->findCanvas(m_tipsCanvas);
//	this->m_this = m_this;
//}
//GeneralTips::GeneralTips(std::string m_tipsCanvas)	
//{
//	tips = crFilterRenderManager::getInstance()->findCanvas(m_tipsCanvas);
//}
//void GeneralTips::setText(std::string m_tipsTextWidget, std::string textStr)
//{
//	if(tips)
//	{
//		tipsText = dynamic_cast<crStaticTextWidgetNode *>(tips->getWidget(m_tipsTextWidget));
//		if(tipsText )
//		{
//			tipsText->setString(textStr);
//		}
//	}
//}
//void GeneralTips::setText(std::string m_tipsTextWidget, std::string textStr, crVector4 textColor)
//{
//	if(tips)
//	{
//		tipsText = dynamic_cast<crStaticTextWidgetNode *>(tips->getWidget(m_tipsTextWidget));
//		if(tipsText )
//		{
//			tipsText->setColor(textColor);
//			tipsText->setString(textStr);
//		}
//	}
//}
//void GeneralTips::setImgage(std::string m_tipsImgWidget, std::string imgStr)
//{
//	if(tips && m_this)
//	{
//		tipsImg = dynamic_cast<crImageBoxWidgetNode *>(tips->getWidget(m_tipsImgWidget));
//		if(tipsText )
//		{
//			tipsImg->setImageName(imgStr);
//		}
//	}
//}
//void GeneralTips::setTipUpper()
//{
//	if(tips && m_this)
//	{
//		const crBoundingBox &btnbox = m_this->getBoundBox();
//		const crMatrix &mat = m_this->getParentCanvas()->getMatrix();
//		float posx = btnbox.m_min[0];
//		float posy = (btnbox.m_min[1]+1.5f*(btnbox.m_max[1]-btnbox.m_min[1]));
//		crVector2 mouse(crVector2(posx,posy));
//		tips->setMatrix(crMatrix::translate(mouse[0],mouse[1],0.0f) * mat);
//		crFilterRenderManager::getInstance()->showCanvas(tips,true);
//	}
//}
//void GeneralTips::setTipRight()
//{
//	if(tips && m_this)
//	{
//		const crBoundingBox &iconbox = m_this->getBoundBox();
//		const crBoundingBox &tip = tips->getBoundBox(); 
//		float posx = (tip.m_max[0]-tip.m_min[0])*0.5;
//		float posy = (tip.m_max[1]-tip.m_min[1])*0.5;
//		crVector3 pos(iconbox.m_max[0],iconbox.m_max[1],0.0f);
//		/////////////////////////////////////////
//		crVector3 pos2(iconbox.m_min[0] ,iconbox.m_min[1],0.0f);
//		float posx2,posy2;
//		posx2 = iconbox.m_max[0];
//		posy2 = iconbox.m_max[1] - posy;
//
//		crVector2 mouse(crVector2(posx2,posy2));
//		tips->setMatrix(crMatrix::translate(mouse[0],mouse[1],0.0f));
//		crFilterRenderManager::getInstance()->showCanvas(tips,true);
//	}
//}
//
//void GeneralTips::setTipAuto()
//{
//	if(tips && m_this)
//	{
//		if(m_this->getParentCanvas())
//		{
//			const crMatrix &mat = m_this->getParentCanvas()->getMatrix();//////////////////////////////////// m_this->getParentCanvas()
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
//			if (pos2[1] >= 0)//
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
//
//
///////////////////////////////////////////
////
////crJXJUIOficialRankBestLevelTipMethod
////������õĹ�ְ�Ѿ�����߼�����껬����Ǩ��ť��ʾ "�Ѿ�����߼���"
////
///////////////////////////////////////////
//crJXJUIOficialRankBestLevelTipMethod::crJXJUIOficialRankBestLevelTipMethod()
//{
//}
//crJXJUIOficialRankBestLevelTipMethod::crJXJUIOficialRankBestLevelTipMethod(const crJXJUIOficialRankBestLevelTipMethod& handle):
//	crMethod(handle),
//	m_tipsCanvas(handle.m_tipsCanvas),
//	m_tipsTextWidget(handle.m_tipsTextWidget)
//{
//}
//void crJXJUIOficialRankBestLevelTipMethod::inputParam(int i, void *param)
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
//void crJXJUIOficialRankBestLevelTipMethod::addParam(int i, const std::string& str)
//{
//	switch(i) 
//	{
//	case 0:
//		m_tipsCanvas = str;
//		break;
//	case 1:
//		m_tipsTextWidget = str;
//		break;
//
//	}
//}
//
//void crJXJUIOficialRankBestLevelTipMethod::operator()(crHandle &handle)
//{
//	crPlayerGameData *myPlayer = crMyPlayerData::getInstance()->getPlayerGameData();
//	if(myPlayer)
//	{
//		crTableIO *postTab = crGlobalHandle::gData()->gGlobalTable(WCHDATA_JXJGovPostTab);
//		void *param;
//		crData *data = myPlayer->getMainRole()->getDataClass();
//		if(postTab && data)
//		{
//			data->getParam(WCHDATA_JXJGovPost,param);
//			unsigned char post = *(unsigned char*)param;
//			int rowcount = postTab->getRowCount();
//			if(post == rowcount) 
//			{
//				GeneralTips generalTips(m_tipsCanvas, m_this);
//				std::string str = "�Ѿ�����߼���";
//				generalTips.setText(m_tipsTextWidget, str);
//				generalTips.setTipUpper();
//			}
//		}
//	}
//}
//

/////////////////////////////////////////
//
//crJXJSearchLordLevelInfoMethod
//
/////////////////////////////////////////
crJXJSearchLordLevelInfoMethod::crJXJSearchLordLevelInfoMethod():
	m_this(NULL)
{
}
crJXJSearchLordLevelInfoMethod::crJXJSearchLordLevelInfoMethod(const crJXJSearchLordLevelInfoMethod& handle):
	crMethod(handle),
	m_this(NULL)
{
}
void crJXJSearchLordLevelInfoMethod::inputParam(int i, void *param)
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
		m_this = (crJXJAccomplish*)param;
		break;
	}
}
void crJXJSearchLordLevelInfoMethod::addParam(int i, const std::string& str)
{
}
void crJXJSearchLordLevelInfoMethod::operator()(crHandle &handle)
{
	crPlayerGameData *myPlayer = crMyPlayerData::getInstance()->getPlayerGameData();
	if(myPlayer)
	{
		void *param;
		crPlayerGameData *playerGameData = crMyPlayerData::getInstance()->getPlayerGameData();
		crRole *mainRole = playerGameData->getMainRole();
		crData *mainRoleData = mainRole->getDataClass();
		mainRoleData->getParam(WCHDATA_Level,param);
		unsigned char nowlv = *(unsigned char *)param;
		m_this->setStep(nowlv);
	}
}

/////////////////////////////////////////
//
//crJXJSearchLordLevelInfoCompleteCheckMethod
//
/////////////////////////////////////////
crJXJSearchLordLevelInfoCompleteCheckMethod::crJXJSearchLordLevelInfoCompleteCheckMethod():
	m_this(NULL),
	m_player(NULL)
{
}
crJXJSearchLordLevelInfoCompleteCheckMethod::crJXJSearchLordLevelInfoCompleteCheckMethod(const crJXJSearchLordLevelInfoCompleteCheckMethod& handle):
	crMethod(handle),
	m_this(NULL),
	m_player(NULL)
{
}
void crJXJSearchLordLevelInfoCompleteCheckMethod::inputParam(int i, void *param)
{
	switch(i) 
	{
	case 0:
		if(param == 0)
		{//�ͷ�
			m_this = NULL;
			m_player = NULL;
		}
		break;
	case 1:
		m_this = (crJXJAccomplish*)param;
		break;
	case 2:
		if(param)
		{
			CREPARAM& param64 = *(CREPARAM*)param;
			m_player = (crPlayerGameData *)(LOCREPARAM(param64));
		}
		else
		{
			m_player = NULL;
		}
		break;
	}
}
void crJXJSearchLordLevelInfoCompleteCheckMethod::addParam(int i, const std::string& str)
{

}
void crJXJSearchLordLevelInfoCompleteCheckMethod::operator()(crHandle &handle)
{
	if(m_player)
	{
		void *param;
		crRole *mainRole = m_player->getMainRole();
		crData *mainRoleData = mainRole->getDataClass();
		mainRoleData->getParam(WCHDATA_Level,param);
		unsigned char nowlv = *(unsigned char *)param;
		m_this->setStep(nowlv);
	}
}
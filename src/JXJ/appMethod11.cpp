/**********************************************************************
*
*	�ļ�:	   appMethod10.cpp
*
*	����:	   
*
*	����:	   ������
*					
*
**********************************************************************/
#include <rbody/Creature3D/CreBody.h>
#include <JXJ/appMethod11.h>
#include <JXJ/appMethod2.h>
#include <JXJ/appMethod.h>
#include <JXJ/appDataParam.h>
#include <JXJ/appMsg.h>
#include <JXJ/appPackets.h>
#include <CRUI/crWidgetExtend.h>
#include <CRNetApp/appNetLogic.h>
#include <CRNetApp/appGlobalHandle.h>
#include <CRNetApp/appDBUpdate.h>
#include <CRProducer/crViewer.h>
#include <CRProducer/crSceneHandler.h>
#include <CRUtil/crAcceptGIVisitor.h>
#include <CRDataBase/crDataBaseManager.h>
#include <CRNetApp/appDBUpdate2.h>
#include <CRNetApp/appDBQuery2.h>
#include <CRIOManager/crConvertUTF.h>
#include <JXJ/appDBQuery.h>
#include <CRIOManager/crLoadManager.h>
#include <CRIOManager/crCookFile.h>
#include <CRIOManager/crReadFile.h>
#include <CREncapsulation/crNodeVisitors.h>
#include <sys/stat.h>
#include <JXJ/appData6.h>
using namespace CRCore;
using namespace CRNetApp;
using namespace CRDataBase;
using namespace CRNet;
using namespace CRProducer;
using namespace CRPhysics;
using namespace CREncapsulation;
using namespace CRUtil;
using namespace rbody;
using namespace JXJ;
using namespace CRIOManager;
using namespace CRUI;


///////////////////////////////////////////
////crJXJUIImageDecorateMethod
///////////////////////////////////////////
//crJXJUIImageDecorateUpdateMethod::crJXJUIImageDecorateUpdateMethod(const crJXJUIImageDecorateUpdateMethod& handle):
//	crMethod(handle)
//	, m_this(NULL)
//{	
//}
//void crJXJUIImageDecorateUpdateMethod::inputParam(int i, void *param)
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
//		m_this = (crCanvasNode*)param;
//		break;
//	}
//}
//
//void crJXJUIImageDecorateUpdateMethod::addParam(int i, const std::string& str)
//{
//	switch(i) 
//	{
//	case 0:
//		m_Dialog = str;
//		break;
//	case 1:
//		m_Radio1 = str;
//		break;
//	case 2:
//		m_Radio2 = str;
//		break;
//	}
//}
//void crJXJUIImageDecorateUpdateMethod::operator()(crHandle &handle)
//{
//	crPlayerGameData * playerGameData = crMyPlayerData::getInstance()->getPlayerGameData();
//	if (NULL == playerGameData)
//		return ;
//	crData *playerData = playerGameData->getDataClass();
//	if (NULL == playerData)
//		return ;
//
//	//�ҵ����
//	ref_ptr<crCanvasNode> canvas = crFilterRenderManager::getInstance()->findCanvas(m_Dialog);
//	if (!canvas.valid())
//		return ;
//
//	void *param;
//	crPlayerGameData *myPlayer = crMyPlayerData::getInstance()->getPlayerGameData();
//	crData *data = myPlayer->getDataClass();
//	data->getParam(WCHDATA_JXJVipLv,param);
//	unsigned char viplv = *(unsigned char *)param;
//	int nMaxBuyIconCount = atoi(crGlobalHandle::gData()->gGameGlobalValue(WCHDATA_JXJMaxBuyIconCount,viplv).c_str());
//
//	//����ͷ��ͱ�����һ�����
//	ref_ptr<crTableIO>playerIconTab = NULL;
//	int nCurSelectSex = 0;	//����Ҫ��ȡ�£�0��1
//	int nTypeSelect = 0;	//����Ҫ��ȡ�£�0,1,2
//	crRadioGroupWidgetNode * pRadio1 = dynamic_cast<crRadioGroupWidgetNode *>(canvas->getWidget(m_Radio1));
//	if (pRadio1)
//		nCurSelectSex = pRadio1->getSelect();
//	crRadioGroupWidgetNode * pRadio2 = dynamic_cast<crRadioGroupWidgetNode *>(canvas->getWidget(m_Radio2));
//	if (pRadio2)
//		nTypeSelect = pRadio2->getSelect();
//	crMultiSwitch *pagesw = dynamic_cast<crMultiSwitch *>(canvas->getChildNode("UI_Visualize_Label"));
//	if (pagesw)
//		pagesw->setActiveSwitchSet(0);
//	if (0 == nTypeSelect)
//	{
//		playerIconTab = crGlobalHandle::gData()->gGlobalTable(WCHDATA_JXJPlayerIconTab);
//	}
//	else
//	{
//		if (pagesw)
//			pagesw->setActiveSwitchSet(1);
//		if (1 == nTypeSelect)
//			playerIconTab = crGlobalHandle::gData()->gGlobalTable(WCHDATA_JXJPlayerIconTab);
//		else
//		{
//			playerIconTab = crGlobalHandle::gData()->gGlobalTable(WCHDATA_JXJPlayerIconBackTable);
//		}
//	}
//
//	if (!playerIconTab.valid())
//		return ;
//
//	int rowCount = playerIconTab->getRowCount();
//	int indexCount = 0;
//	int sexIndex = playerIconTab->getTitleIndex("�Ա�");
//	int iconIndex = playerIconTab->getTitleIndex("icon");
//	int priceIndex = playerIconTab->getTitleIndex("�۸�");
//	std::string strValue;
//	char szBuf[128] = {0};
//	for (int i = 0; i < rowCount && indexCount < 10; i++)
//	{
//		//�ж��Ƿ���ϵ�ǰ�Ա��������������-���Ա���
//		strValue = (*playerIconTab)(i, sexIndex);
//		if (nCurSelectSex == atoi(strValue.c_str()))
//		{
//			strValue = (*playerIconTab)(i, iconIndex);
//			//����ͼƬ
//			if (0 == nTypeSelect)
//				sprintf(szBuf, "UI_Visualize_SamsaraPortraits_%d", indexCount +1);
//			else
//				sprintf(szBuf, "UI_Visualize_ChargePortraits_%d", indexCount +1);
//			crImageBoxWidgetNode *iconImageBox = dynamic_cast<crImageBoxWidgetNode *>(canvas->getWidget(szBuf));
//			if (iconImageBox)
//			{
//				iconImageBox->setVisiable(true);
//				iconImageBox->setImageName(strValue);
//			}
//
//			indexCount ++;
//		}
//	}
//
//	//���Ѻͱ������Ĺ�����������
//	crWidgetNode *scroll = dynamic_cast<crWidgetNode *>(canvas->getWidget("UI_Visualize_Charge_ListScroll"));
//	if (scroll)
//		scroll->setVisiable(false);
//
//	//�����ͷ�����ó�ʹ�ã�û������óɹ���
//	playerData->getParam(WCHDATA_PlayerSex,param);
//	bool bSex = *((bool *)param);	//0��Ů��1����
//	if (0 == nTypeSelect)
//	{
//		playerData->getParam(WCHDATA_JXJVipLv,param);
//		unsigned char vipLv = *((unsigned char*)param);	//��ʦ�ȼ�
//
//		//��ҵ�ǰѡ���ͷ��ҵ�
//		playerData->getParam(WCHDATA_PlayerIconID,param);
//		unsigned char playerCurIconId = *((unsigned char *)param);
//
//		//�����ֻصı������ж���ʾ��Щ�����ʹ�ð�ť-�߻���8��Ū��һ����
//		//����Ĭ�Ͽ���ʹ�õ�ͷ��İ�ť��ʾ
//		crButtonWidgetNode *iconButton = NULL;
//		sprintf(szBuf, "UI_Visualize_Samsara_Use_1");
//		iconButton = dynamic_cast<crButtonWidgetNode *>(canvas->getWidget(szBuf));
//		if (iconButton)
//		{
//			iconButton->setVisiable(true);
//			if (1 == playerCurIconId)	//��ǰ�������������֮��Ҫ���óɻ�ɫ��
//				iconButton->setEnable(false);
//		}
//
//		sprintf(szBuf, "UI_Visualize_Samsara_Use_2");
//		iconButton = dynamic_cast<crButtonWidgetNode *>(canvas->getWidget(szBuf));
//		if (iconButton)
//		{
//			iconButton->setVisiable(true);
//			if (2 == playerCurIconId)	//��ǰ�������������֮��Ҫ���óɻ�ɫ��
//				iconButton->setEnable(false);
//		}
//
//		for (int i=2; i<10; i++)
//		{
//			sprintf(szBuf, "sw67_%d", i -1);
//			crMultiSwitch *iconsw = dynamic_cast<crMultiSwitch *>(canvas->getChildNode(szBuf));
//			if (vipLv >= i + 1)	//�Ƿ����ǰ������
//			{
//				if (iconsw)
//					iconsw->setActiveSwitchSet(1);
//
//				//��ʾʹ�ð�ť
//				sprintf(szBuf, "UI_Visualize_Samsara_Use_%d", i+1);
//				iconButton = dynamic_cast<crButtonWidgetNode *>(canvas->getWidget(szBuf));
//				if (iconButton)
//				{
//					iconButton->setVisiable(true);
//					if (i+1 == playerCurIconId)	//��ǰ�������������֮��Ҫ���óɻ�ɫ��
//						iconButton->setEnable(false);
//				}
//			}
//			else
//			{
//				if (iconsw)
//					iconsw->setActiveSwitchSet(0);
//
//				sprintf(szBuf, "UI_Visualize_SamsaraPortraits_%d", i +1);
//				crImageBoxWidgetNode *iconImageBox = dynamic_cast<crImageBoxWidgetNode *>(canvas->getWidget(szBuf));
//				if (iconImageBox)
//				{
//					iconImageBox->setVisiable(false);
//				}
//
//				//�رհ�ť
//				sprintf(szBuf, "UI_Visualize_Samsara_Use_%d", i+1);
//				iconButton = dynamic_cast<crButtonWidgetNode *>(canvas->getWidget(szBuf));
//				if (iconButton)
//					iconButton->setVisiable(false);
//				sprintf(szBuf, "UI_Visualize_Samsara_Buy_%d", i+1);
//				iconButton = dynamic_cast<crButtonWidgetNode *>(canvas->getWidget(szBuf));
//				if (iconButton)
//					iconButton->setVisiable(false);
//			}
//		}
//
//		//�ж��Ա��������ͬ�����ð�ť����ʾ
//		if (nCurSelectSex == (int)bSex)	//ֵ��ͬʱ������ͬ�Ա�
//		{
//			for (int i=0; i<10; i++)
//			{
//				sprintf(szBuf, "UI_Visualize_Samsara_Use_%d", i+1);
//				iconButton = dynamic_cast<crButtonWidgetNode *>(canvas->getWidget(szBuf));
//				if (iconButton)
//					iconButton->setVisiable(false);
//				sprintf(szBuf, "UI_Visualize_Samsara_Buy_%d", i+1);
//				iconButton = dynamic_cast<crButtonWidgetNode *>(canvas->getWidget(szBuf));
//				if (iconButton)
//					iconButton->setVisiable(false);
//			}
//		}
//	}
//	else if (1 == nTypeSelect)
//	{
//		//ȡ������
//		crData *data = m_this->getDataClass();
//		void *param = NULL;
//		JXJ::IconShopMap * iconShopMap = NULL;
//		data->excHandle(MAKECREPARAM(WCH_LockData,1));
//		data->getParam(WCHDATA_JXJPlayerIconShopMap,param);
//		iconShopMap = (JXJ::IconShopMap *)param;
//
//		//��ȡͷ����ҵ����ѵ�ͷ����ʾ����
//		int pay4IconIndex = playerIconTab->getTitleIndex("�Ƿ񸶷ѵ���"), id = playerIconTab->getTitleIndex("id");
//		std::string strIspay4Icon, strIconID, strPrice;
//		indexCount = 0;
//		unsigned char iconList[128];
//		for (int i = 0; i < rowCount && indexCount < nMaxBuyIconCount; i++)
//		{
//			//�ж��Ƿ���ϵ�ǰ�Ա��������������-���Ա���
//			strValue = (*playerIconTab)(i, sexIndex);
//			strIspay4Icon = (*playerIconTab)(i, pay4IconIndex);
//			strIconID = (*playerIconTab)(i, id);
//			if (nCurSelectSex == atoi(strValue.c_str()) && atoi(strIspay4Icon.c_str()))
//			{
//				strValue = (*playerIconTab)(i, iconIndex);
//				//����ͼƬ
//				sprintf(szBuf, "UI_Visualize_ChargePortraits_%d", indexCount +1);
//				crImageBoxWidgetNode *iconImageBox = dynamic_cast<crImageBoxWidgetNode *>(canvas->getWidget(szBuf));
//				if (iconImageBox)
//				{
//					iconImageBox->setVisiable(true);
//					iconImageBox->setImageName(strValue);
//				}
//
//				sprintf(szBuf, "UI_Visualize_Charge_Buy_%d", indexCount +1);
//				ref_ptr<crWidgetNode> pBuy = dynamic_cast<crWidgetNode *>(canvas->getWidget(szBuf));
//				(*iconShopMap)[pBuy] = atoi(strIconID.c_str());
//				sprintf(szBuf, "UI_Visualize_Charge_Use_%d", indexCount +1);
//				ref_ptr<crWidgetNode> pUse = dynamic_cast<crWidgetNode *>(canvas->getWidget(szBuf));
//				(*iconShopMap)[pUse] = atoi(strIconID.c_str());
//
//				iconList[indexCount] = atoi(strIconID.c_str());
//
//				//���ü�Ǯ
//				strPrice = (*playerIconTab)(i, priceIndex);
//				sprintf(szBuf, "UI_Visualize_Charge_Input_%d", indexCount +1);
//				ref_ptr<crStaticTextWidgetNode> pPrice = dynamic_cast<crStaticTextWidgetNode *>(canvas->getWidget(szBuf));
//				if (pPrice.valid())
//				{
//					sprintf(szBuf, "�۸�%s", strPrice.c_str());
//					pPrice->setString(std::string(szBuf));
//				}
//
//				indexCount ++;
//			}
//		}
//		data->excHandle(MAKECREPARAM(WCH_LockData, 0));
//
//		//���ù����ͷ��Ϊʹ�ã�û�й����ͷ��Ϊ����
//		crButtonWidgetNode *iconImageBox = NULL;
//		playerData->getParam(WCHDATA_JXJMainRoleBuyIcon, param);
//		PlayerIconVec * playerBuyIcon = (PlayerIconVec *)param;
//		for (int i=0; i<nMaxBuyIconCount; i++)
//		{
//			if (nCurSelectSex != (int)bSex)	//ֵ��ͬʱ������ͬ�Ա�
//			{
//				//�������ͷ���Ƿ񱻹�����ˣ�����ֱ��ʹ��
//				bool bIconBuy = false;
//				for (int mm=0; mm<(*playerBuyIcon).size(); mm++)
//				{
//					if (iconList[i] == (*playerBuyIcon)[mm])
//					{
//						bIconBuy = true;
//						break;
//					}
//				}
//				if (bIconBuy)
//				{
//					sprintf(szBuf, "UI_Visualize_Charge_Use_%d", i+1);
//					iconImageBox = dynamic_cast<crButtonWidgetNode *>(canvas->getWidget(szBuf));
//					if (iconImageBox)
//						iconImageBox->setVisiable(true);
//					sprintf(szBuf, "UI_Visualize_Charge_Buy_%d", i+1);
//					iconImageBox = dynamic_cast<crButtonWidgetNode *>(canvas->getWidget(szBuf));
//					if (iconImageBox)
//						iconImageBox->setVisiable(false);
//				}
//				else
//				{
//					sprintf(szBuf, "UI_Visualize_Charge_Use_%d", i+1);
//					iconImageBox = dynamic_cast<crButtonWidgetNode *>(canvas->getWidget(szBuf));
//					if (iconImageBox)
//						iconImageBox->setVisiable(false);
//					sprintf(szBuf, "UI_Visualize_Charge_Buy_%d", i+1);
//					iconImageBox = dynamic_cast<crButtonWidgetNode *>(canvas->getWidget(szBuf));
//					if (iconImageBox)
//						iconImageBox->setVisiable(true);
//				}
//			}
//			else
//			{
//				sprintf(szBuf, "UI_Visualize_Charge_Use_%d", i+1);
//				iconImageBox = dynamic_cast<crButtonWidgetNode *>(canvas->getWidget(szBuf));
//				if (iconImageBox)
//					iconImageBox->setVisiable(false);
//				sprintf(szBuf, "UI_Visualize_Charge_Buy_%d", i+1);
//				iconImageBox = dynamic_cast<crButtonWidgetNode *>(canvas->getWidget(szBuf));
//				if (iconImageBox)
//					iconImageBox->setVisiable(false);
//			}
//		}
//	}
//	else if (2 == nTypeSelect)
//	{
//		for (int i=0; i<nMaxBuyIconCount; i++)
//		{
//			//��ʱ�����Ĺ����ȹرհ�ť
//			crButtonWidgetNode *iconButton = NULL;
//			sprintf(szBuf, "UI_Visualize_Charge_Use_%d", i+1);
//			iconButton = dynamic_cast<crButtonWidgetNode *>(canvas->getWidget(szBuf));
//			if (iconButton)
//				iconButton->setVisiable(false);
//			sprintf(szBuf, "UI_Visualize_Charge_Buy_%d", i+1);
//			iconButton = dynamic_cast<crButtonWidgetNode *>(canvas->getWidget(szBuf));
//			if (iconButton)
//				iconButton->setVisiable(false);
//
//			//��ʱ�����Ĺر����
//			sprintf(szBuf, "UI_Visualize_ChargePortraits_%d", i +1);
//			crImageBoxWidgetNode *iconImageBox = dynamic_cast<crImageBoxWidgetNode *>(canvas->getWidget(szBuf));
//			if (iconImageBox)
//			{
//				iconImageBox->setVisiable(false);
//			}
//
//			sprintf(szBuf, "UI_Visualize_Charge_Input_%d", i +1);
//			ref_ptr<crStaticTextWidgetNode> pPrice = dynamic_cast<crStaticTextWidgetNode *>(canvas->getWidget(szBuf));
//			if (pPrice.valid())
//			{
//				pPrice->setString(std::string(""));
//			}
//		}
//	}
//}
///////////////////////////////////////////
////
////crJXJSendPlayerBuyIconMethod
////
///////////////////////////////////////////
//crJXJSendPlayerBuyIconMethod::crJXJSendPlayerBuyIconMethod():
//	m_this(NULL),
//	m_buyIconIndex(0)
//{
//}
//crJXJSendPlayerBuyIconMethod::crJXJSendPlayerBuyIconMethod(const crJXJSendPlayerBuyIconMethod& handle):
//	crMethod(handle),
//	m_this(NULL),
//	m_buyIconIndex(0)
//{
//}
//void crJXJSendPlayerBuyIconMethod::inputParam(int i, void *param)
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
//		m_this = (crCanvasNode*)param;
//		break;
//	case 2:
//		if(param)
//		{
//			CREPARAM& param64 = *(CREPARAM*)param;
//			m_stream = (crStreamBuf *)(LOCREPARAM(param64));
//		}
//		else
//		{
//			m_stream = NULL;
//		}
//		break;
//	}
//}
//void crJXJSendPlayerBuyIconMethod::addParam(int i, const std::string& str)
//{
//	switch(i) 
//	{
//	case 0:
//		m_buyIconIndex = atoi(str.c_str());
//		break;
//	}
//}
//void crJXJSendPlayerBuyIconMethod::operator()(crHandle &handle)
//{
//	//�Ƿ��Ѿ�����������
//	void *param;
//	crPlayerGameData *myPlayer = crMyPlayerData::getInstance()->getPlayerGameData();
//	crData *pTmpData = myPlayer->getDataClass();
//	pTmpData->getParam(WCHDATA_JXJVipLv,param);
//	unsigned char viplv = *(unsigned char *)param;
//	int nMaxBuyIconCount = atoi(crGlobalHandle::gData()->gGameGlobalValue(WCHDATA_JXJMaxBuyIconCount,viplv).c_str());
//
//	crData *playerData = crMyPlayerData::getInstance()->getPlayerGameData()->getDataClass();
//	playerData->excHandle(MAKECREPARAM(WCH_LockData,1));
//	playerData->getParam(WCHDATA_JXJMainRoleBuyIcon, param);
//	PlayerIconVec * playerBuyIcon = (PlayerIconVec *)param;
//	if ((*playerBuyIcon).size() >= nMaxBuyIconCount)
//	{
//		bool bFound = false;
//		for (int i=0; i<nMaxBuyIconCount; i++)
//		{
//			if (0 == (*playerBuyIcon)[i])
//			{
//				bFound = true;
//				break;
//			}
//		}
//		if ( ! bFound)
//		{
//			playerData->excHandle(MAKECREPARAM(WCH_LockData,0));
//			return ;
//		}
//	}
//
//	//ȡ������
//	crData *data = m_this->getParentCanvas()->getDataClass();
//	JXJ::BtnIconShopMap * btnIconShopMap = NULL;
//	data->getParam(WCHDATA_JXJPlayerBtnIconShopMap,param);
//	btnIconShopMap = (JXJ::BtnIconShopMap *)param;
//	JXJ::IconShopMap * iconShopMap = NULL;
//	data->getParam(WCHDATA_JXJPlayerIconShopMap,param);
//	iconShopMap = (JXJ::IconShopMap *)param;
//
//	//�ҵ�IconID
//	//JXJ::BtnIconShopMap::iterator IterBtn = btnIconShopMap->find(m_this);
//	//if (btnIconShopMap->end() == IterBtn)
//	//	return ;
//	JXJ::IconShopMap::iterator IterImage = iconShopMap->find(m_this);
//	if (iconShopMap->end() == IterImage)
//	{
//		playerData->excHandle(MAKECREPARAM(WCH_LockData,0));
//		return ;
//	}
//	unsigned char iconIndex = IterImage->second;
//
//	ref_ptr<crTableIO> playerIconTab = crGlobalHandle::gData()->gGlobalTable(WCHDATA_JXJPlayerIconTab);
//	int priceIndex = playerIconTab->getTitleIndex("�۸�");
//	crTableIO::StrVec record;
//	if (playerIconTab->queryOneRecord(0, crArgumentParser::appItoa(iconIndex), record)<0)
//	{
//		playerData->excHandle(MAKECREPARAM(WCH_LockData,0));
//		return ;
//	}
//
//	int price = atoi(record[7].c_str());	//��Ʒ�۸�
//
//	crNetConductor *netConductor = crNetContainer::getInstance()->getDynamicNetConductor(GameClient_Game);
//
//	playerData->getParam(WCHDATA_JXJGoldingot,param);	//��ǰ��Ǯ
//	int goldingot = *(int*)param;
//	playerData->getParam(WCHDATA_JXJGiftGold,param);
//	int giftgold = *(int*)param;
//	if(price<=goldingot + giftgold)
//	{
//		ref_ptr<crStreamBuf> stream = new crStreamBuf;
//		stream->createBuf(1);
//		stream->_writeUChar(iconIndex);
//
//		crPlayerDataEventPacket packet;
//		crPlayerDataEventPacket::buildRequestPacket(packet,WCH_JXJRecvPlayerBuyIcon,stream.get());
//		netConductor->getNetManager()->sendPacket("all",packet);
//	}
//	else
//	{//��ʾԪ������
//		myPlayer->doEvent(WCH_JXJUIShowTipsCanvas,MAKECREPARAM(2002,NULL));//Ԫ������
//	}
//	playerData->excHandle(MAKECREPARAM(WCH_LockData,0));
//}
//
///////////////////////////////////////////
////
////crJXJRecvPlayerBuyIconMethod
////
///////////////////////////////////////////
//crJXJRecvPlayerBuyIconMethod::crJXJRecvPlayerBuyIconMethod():
//	m_netType(GameClient_Game){}
//crJXJRecvPlayerBuyIconMethod::crJXJRecvPlayerBuyIconMethod(const crJXJRecvPlayerBuyIconMethod& handle)
//	: m_buyIconIndex(0)
//	, m_this(NULL)
//{
//}
//void crJXJRecvPlayerBuyIconMethod::inputParam(int i, void *param)
//{
//	switch(i) 
//	{
//	case 0:
//		if(param == 0)
//		{//�ͷ�
//			m_this = NULL;
//			m_stream = NULL;
//		}
//		break;
//	case 1:
//		m_this = (crPlayerGameData*)param;
//		break;
//	case 2:
//		if(param)
//		{
//			CREPARAM& param64 = *(CREPARAM*)param;
//			m_stream = (crStreamBuf *)(LOCREPARAM(param64));
//			m_netType = HICREPARAM(param64);
//		}
//		else
//		{
//			m_stream = NULL;
//		}
//		break;
//	}
//}
//
//void crJXJRecvPlayerBuyIconMethod::addParam(int i, const std::string& str)
//{
//}
//
//void crJXJRecvPlayerBuyIconMethod::operator()(crHandle &handle)
//{
//
//	if(m_this && m_stream.valid())
//	{
//		if(m_netType == GameServer)
//		{
//			void *param;
//			crData *data = m_this->getDataClass();
//			data->getParam(WCHDATA_JXJVipLv,param);
//			unsigned char viplv = *(unsigned char *)param;
//			int sexIconOffset = atoi(crGlobalHandle::gData()->gGameGlobalValue(WCHDATA_JXJFemaleIconOffset,viplv).c_str());	//Ů��������ͷ�����ӵ�ƫ��
//			int nMaxBuyIconCount = atoi(crGlobalHandle::gData()->gGameGlobalValue(WCHDATA_JXJMaxBuyIconCount,viplv).c_str());
//			//��ȡ���࣬���õ��������
//			int playerid = m_this->getPlayerID();
//			crNetConductor *gameServer = crNetContainer::getInstance()->getNetConductor(GameServer); 
//			ref_ptr<crGameServerPlayerData> playerData = dynamic_cast<crGameServerPlayerData *>(gameServer->getNetDataManager()->getPlayerData(playerid));
//			if(playerData.valid())
//			{
//				unsigned char buyIconIndex = m_stream->_readUChar();
//
//				//�ӱ��ж�ȡ�����Ʒ�Ľ�Ǯ
//				int price = 0;
//				ref_ptr<crTableIO>playerIconTable = crGlobalHandle::gData()->gGlobalTable(WCHDATA_JXJPlayerIconTab);
//				crTableIO::StrVec record;
//				if(playerIconTable->queryOneRecord(0,crArgumentParser::appItoa(buyIconIndex),record)>=0)
//				{
//					if (7 < record.size())
//						price = atoi(record[7].c_str());
//				}
//
//				//�޸Ĳ����湺���Icon��ֵ
//				void *param;
//				m_this->getDataClass()->excHandle(MAKECREPARAM(WCH_LockData,1));
//				m_this->getDataClass()->getParam(WCHDATA_JXJMainRoleBuyIcon, param);
//				PlayerIconVec * playerBuyIcon = (PlayerIconVec *)param;
//				if ((*playerBuyIcon).size() >= nMaxBuyIconCount)
//				{
//					bool bFound = false;
//					for (int i=0; i<nMaxBuyIconCount; i++)
//					{
//						if (0 == (*playerBuyIcon)[i])
//						{
//							(*playerBuyIcon)[i] = buyIconIndex;
//							break;
//						}
//					}
//					if ( ! bFound)
//					{
//						m_this->getDataClass()->excHandle(MAKECREPARAM(WCH_LockData, 0));
//						return ;
//					}
//				}
//
//				//��ȡ��Ǯ����֤�Ƿ�ӵ����ô��Ľ�Ǯ
//				m_this->getDataClass()->getParam(WCHDATA_JXJGoldingot,param);
//				int *goldingot = (int*)param;
//				m_this->getDataClass()->getParam(WCHDATA_JXJGiftGold,param);
//				int *giftgold = (int*)param;
//				if(price> ((*goldingot)+ (*giftgold)))
//				{
//					ref_ptr<crStreamBuf> stream = new crStreamBuf;
//					stream->createBuf(1);
//					stream->_writeUChar(2);	//1�ǳɹ���2��ʧ��
//
//					crNetConductor *gameServer = crNetContainer::getInstance()->getNetConductor(GameServer); 
//					crPlayerDataEventPacket packet;
//					crPlayerDataEventPacket::buildReplyPacket(packet,playerid,WCH_JXJRecvPlayerBuyIcon,stream.get());
//					gameServer->getNetManager()->sendPacket(playerData->getPlayerConnectServerAddress(),packet);
//
//					m_this->getDataClass()->excHandle(MAKECREPARAM(WCH_LockData, 0));
//					return ;
//				}
//
//				//�۳�Ԫ��
//				bool needdeductgold = false;
//				MoneyChangeData moneydata(price,"���򸶷�����");
//				m_this->doEvent(WCH_JXJDeductLijinGold,MAKECREPARAM(&moneydata,&needdeductgold));
//
//				(*playerBuyIcon).push_back(buyIconIndex);	//����
//
//				//������ҹ���ɹ�
//				ref_ptr<crStreamBuf> stream = new crStreamBuf;
//				stream->createBuf(2);
//				stream->_writeUChar(1);	//1�ǳɹ���2��ʧ��
//				stream->_writeUChar(buyIconIndex);	//����ͷ������100
//
//				crNetConductor *gameServer = crNetContainer::getInstance()->getNetConductor(GameServer); 
//				crPlayerDataEventPacket packet;
//				crPlayerDataEventPacket::buildReplyPacket(packet,playerid,WCH_JXJRecvPlayerBuyIcon,stream.get());
//				gameServer->getNetManager()->sendPacket(playerData->getPlayerConnectServerAddress(),packet);
//				m_this->getDataClass()->excHandle(MAKECREPARAM(WCH_LockData, 0));
//			}
//		}
//		else if(m_netType == GameClient_Game)
//		{
//			void *param;
//			crData *data = m_this->getDataClass();
//			data->getParam(WCHDATA_JXJVipLv,param);
//			unsigned char viplv = *(unsigned char *)param;
//			int sexIconOffset = atoi(crGlobalHandle::gData()->gGameGlobalValue(WCHDATA_JXJFemaleIconOffset,viplv).c_str());	//Ů��������ͷ�����ӵ�ƫ��
//			int nMaxBuyIconCount = atoi(crGlobalHandle::gData()->gGameGlobalValue(WCHDATA_JXJMaxBuyIconCount,viplv).c_str());
//
//			unsigned char success = m_stream->_readUChar();
//
//			if (1 == success)
//			{
//				//�޸ı�������
//				crData *playerData = crMyPlayerData::getInstance()->getPlayerGameData()->getDataClass();
//				playerData->getParam(WCHDATA_JXJMainRoleBuyIcon,param);
//				PlayerIconVec * playerBuyIcon = (PlayerIconVec *)param;
//				unsigned char buyIconIndex = m_stream->_readUChar();
//				bool bInsert = false;
//				playerData->excHandle(MAKECREPARAM(WCH_LockData, 1));
//				for (int i=0; i<playerBuyIcon->size(); i++)
//				{
//					if (0 == (*playerBuyIcon)[i])
//					{
//						bInsert = true;
//						(*playerBuyIcon)[i] = buyIconIndex;
//						break;
//					}
//				}
//				if ( ! bInsert)
//					(*playerBuyIcon).push_back(buyIconIndex);
//				playerData->excHandle(MAKECREPARAM(WCH_LockData, 0));
//
//				//�ҵ����Icon�������Icon�İ�ť�����óɡ�ʹ�á�
//				int nIndexOffset = buyIconIndex - 100;
//				playerData->getParam(WCHDATA_PlayerSex,param);
//				bool bSex = *(bool *)param;
//				if ( ! bSex)
//					nIndexOffset -= sexIconOffset;
//				ref_ptr<crCanvasNode> canvas = crFilterRenderManager::getInstance()->findCanvas("UI_Visualize");
//				if (!canvas.valid())
//					return ;
//
//				char szBuf[128] = {0};
//				sprintf(szBuf, "UI_Visualize_Charge_Use_%d", nIndexOffset);
//				crButtonWidgetNode * iconImageBox = dynamic_cast<crButtonWidgetNode *>(canvas->getWidget(szBuf));
//				if (iconImageBox)
//					iconImageBox->setVisiable(true);
//				sprintf(szBuf, "UI_Visualize_Charge_Buy_%d", nIndexOffset);
//				iconImageBox = dynamic_cast<crButtonWidgetNode *>(canvas->getWidget(szBuf));
//				if (iconImageBox)
//					iconImageBox->setVisiable(false);
//			}
//			else if (2 == success)
//			{
//				m_this->doEvent(WCH_JXJUIShowTipsCanvas,MAKECREPARAM(2036,NULL));//Ԫ������
//			}
//		}
//	}
//}
//
///////////////////////////////////////////
////
////crJXJPlayerUseIconMethod
////
///////////////////////////////////////////
//crJXJPlayerUseIconMethod::crJXJPlayerUseIconMethod():
//	m_netType(GameClient_Game), m_useIconIndex(0){}
//crJXJPlayerUseIconMethod::crJXJPlayerUseIconMethod(const crJXJPlayerUseIconMethod& handle):
//	crMethod(handle), m_useIconIndex(0)
//{
//}
//void crJXJPlayerUseIconMethod::inputParam(int i, void *param)
//{
//	switch(i) 
//	{
//	case 0:
//		if(param == 0)
//		{//�ͷ�
//			m_this = NULL;
//			m_stream = NULL;
//		}
//		break;
//	case 1:
//		m_this = (crCanvasNode*)param;
//		break;
//	case 2:
//		if(param)
//		{
//			CREPARAM& param64 = *(CREPARAM*)param;
//			m_stream = (crStreamBuf *)(LOCREPARAM(param64));
//			m_netType = HICREPARAM(param64);
//		}
//		else
//		{
//			m_stream = NULL;
//		}
//		break;
//	}
//}
//
//void crJXJPlayerUseIconMethod::addParam(int i, const std::string& str)
//{
//	switch(i) 
//	{
//	case 0:
//		m_useIconIndex = atoi(str.c_str());
//		break;
//	}
//}
//
//void crJXJPlayerUseIconMethod::operator()(crHandle &handle)
//{
//	//ȡ������
//	crData *data = m_this->getParentCanvas()->getDataClass();
//	void *param = NULL;
//	JXJ::BtnIconShopMap * btnIconShopMap = NULL;
//	data->getParam(WCHDATA_JXJPlayerBtnIconShopMap,param);
//	btnIconShopMap = (JXJ::BtnIconShopMap *)param;
//	JXJ::IconShopMap * iconShopMap = NULL;
//	data->getParam(WCHDATA_JXJPlayerIconShopMap,param);
//	iconShopMap = (JXJ::IconShopMap *)param;
//
//	//�ҵ�IconID
//	//JXJ::BtnIconShopMap::iterator IterBtn = btnIconShopMap->find(m_this);
//	//if (btnIconShopMap->end() == IterBtn)
//	//	return ;
//	JXJ::IconShopMap::iterator IterImage = iconShopMap->find(m_this);
//	unsigned char iconIndex = 0;
//	if (iconShopMap->end() != IterImage)
//		iconIndex = IterImage->second;
//	else if (m_useIconIndex)
//		iconIndex = m_useIconIndex;
//	else
//		return;
//
//	int sexIconOffset = atoi(crGlobalHandle::gData()->gGameGlobalValue(WCHDATA_JXJFemaleIconOffset,0).c_str());	//Ů��������ͷ�����ӵ�ƫ��
//
//	crPlayerGameData *myPlayer = crMyPlayerData::getInstance()->getPlayerGameData();
//	crNetConductor *netConductor = crNetContainer::getInstance()->getDynamicNetConductor(GameClient_Game);
//	if(m_this && m_stream.valid())
//	{
//		void *param;
//		crData *playerData = myPlayer->getDataClass();
//		playerData->getParam(WCHDATA_PlayerSex,param);
//		bool bSex = *(bool *)param;
//		unsigned char useIconIndex = iconIndex;
//		if ( ! bSex)
//			useIconIndex += sexIconOffset;
//
//		ref_ptr<crStreamBuf> stream = new crStreamBuf;
//		stream->createBuf(1);
//		stream->_writeUChar(useIconIndex);
//
//		crPlayerDataEventPacket packet;
//		crPlayerDataEventPacket::buildRequestPacket(packet,WCH_JXJPlayerUseIcon,stream.get());
//		netConductor->getNetManager()->sendPacket("all",packet);
//
//
//		//���ð�ť״̬
//		ref_ptr<crCanvasNode> canvas = crFilterRenderManager::getInstance()->findCanvas("UI_Visualize");
//		if (!canvas.valid())
//			return ;
//		char szBuf[128] = {0};
//		crButtonWidgetNode *iconButton = NULL;
//		if (useIconIndex < 100)
//		{
//			for (int i=0; i<10; i++)
//			{
//				sprintf(szBuf, "UI_Visualize_Samsara_Use_%d", i+1);
//				iconButton = dynamic_cast<crButtonWidgetNode *>(canvas->getWidget(szBuf));
//				if (iconButton)
//				{
//					if (iconIndex == i+1)	//��ǰ�������������֮��Ҫ���óɻ�ɫ��
//						iconButton->setEnable(false);
//					else
//						iconButton->setEnable(true);
//				}
//			}
//		}
//		else
//		{
//			for (int i=0; i<10; i++)
//			{
//				sprintf(szBuf, "UI_Visualize_Charge_Use_%d", i+1);
//				iconButton = dynamic_cast<crButtonWidgetNode *>(canvas->getWidget(szBuf));
//				if (iconButton)
//				{
//					if (iconIndex == i+1 + 100)	//��ǰ�������������֮��Ҫ���óɻ�ɫ��
//						iconButton->setEnable(false);
//					else
//						iconButton->setEnable(true);
//				}
//			}
//		}
//	}
//}
//
///////////////////////////////////////////
////
////crJXJProcPlayerUseIconMethod
////
///////////////////////////////////////////
//crJXJProcPlayerUseIconMethod::crJXJProcPlayerUseIconMethod():
//	m_netType(GameClient_Game){}
//crJXJProcPlayerUseIconMethod::crJXJProcPlayerUseIconMethod(const crJXJProcPlayerUseIconMethod& handle):
//	crMethod(handle),
//	m_useIconIndex(0)
//{
//}
//void crJXJProcPlayerUseIconMethod::inputParam(int i, void *param)
//{
//	switch(i) 
//	{
//	case 0:
//		if(param == 0)
//		{//�ͷ�
//			m_this = NULL;
//			m_stream = NULL;
//		}
//		break;
//	case 1:
//		m_this = (crPlayerGameData*)param;
//		break;
//	case 2:
//		if(param)
//		{
//			CREPARAM& param64 = *(CREPARAM*)param;
//			m_stream = (crStreamBuf *)(LOCREPARAM(param64));
//			m_netType = HICREPARAM(param64);
//		}
//		else
//		{
//			m_stream = NULL;
//		}
//		break;
//	}
//}
//
//void crJXJProcPlayerUseIconMethod::addParam(int i, const std::string& str)
//{
//	switch (i)
//	{
//	case 0:
//		m_useIconIndex = atoi(str.c_str());
//		break;
//	case 1:
//		break;
//	}
//}
//
//void crJXJProcPlayerUseIconMethod::operator()(crHandle &handle)
//{
//	if(m_this && m_stream.valid())
//	{
//		if(m_netType == GameServer)
//		{
//			unsigned char selectIndex = m_stream->_readUChar();
//// 			crData *mainRoleData = m_this->getMainRole()->getDataClass();
//			crData *data = m_this->getDataClass();
//			data->inputParam(WCHDATA_PlayerIconID,&selectIndex);
//
//			int playerid = m_this->getPlayerID();
//			crNetConductor *gameServer = crNetContainer::getInstance()->getNetConductor(GameServer); 
//			ref_ptr<crGameServerPlayerData> playerData = dynamic_cast<crGameServerPlayerData *>(gameServer->getNetDataManager()->getPlayerData(playerid));
//
//			//֪ͨ�ͻ���
//			ref_ptr<crStreamBuf> stream = new crStreamBuf;
//			stream->createBuf(1);
//			stream->_writeUChar(selectIndex);
//
//			crPlayerDataEventPacket packet;
//			crPlayerDataEventPacket::buildReplyPacket(packet,playerid,WCH_JXJPlayerUseIcon,stream.get());
//			gameServer->getNetManager()->sendPacket(playerData->getPlayerConnectServerAddress(),packet);
//		}
//		else if(m_netType == GameClient_Game)
//		{
//			crPlayerGameData *myPlayer = crMyPlayerData::getInstance()->getPlayerGameData();
//			crNetConductor *netConductor = crNetContainer::getInstance()->getDynamicNetConductor(GameClient_Game);
//			//����������ķ���
//			crData *data = crBrain::getInstance()->getDataClass();
//			unsigned char selectIndex = m_stream->_readUChar();
//			data->inputParam(WCHDATA_JXJCurPlayerIconID,(void *)&selectIndex);
//
//			crData *playerData = myPlayer->getDataClass();
//			playerData->inputParam(WCHDATA_PlayerIconID,(void *)&selectIndex);
//
//			//���á��޸�����������塱�е�ͷ��
//			crTableIO::StrVec record;
//			ref_ptr<crTableIO>playerIconTable = crGlobalHandle::gData()->gGlobalTable(WCHDATA_JXJPlayerIconTab);
//			if(playerIconTable.valid() && playerIconTable->queryOneRecord(0,crArgumentParser::appItoa(selectIndex),record)>=0)
//			{
//				//�ҵ����
//				ref_ptr<crCanvasNode> canvas = crFilterRenderManager::getInstance()->findCanvas("UI_Beta2_FeudalLord");
//				if (!canvas.valid())
//					return ;
//
//				//ͷ��
//				int iconindex = playerIconTable->getTitleIndex("icon2");
//				crImageBoxWidgetNode *image = dynamic_cast<crImageBoxWidgetNode *>(canvas->getWidget("UI_Beta2_FeudalLord_TouXiang"));
//				if(image && iconindex>=0 )image->setImageName(record[iconindex]);
//			}
//
//// 			playerData->getParam(WCHDATA_PlayerSex,param);
//// 			bool bSex = *(bool *)param;
//
//// 			//�ҵ�ͼƬ��
//// 			ref_ptr<crTableIO> playerIconTab = crGlobalHandle::gData()->gGlobalTable(WCHDATA_JXJPlayerIconTab);
//// 			int sexIndex = bSex;
//// 			std::string strValue = (*playerIconTab)(selectIndex, sexIndex);
//// 
//// 			//����ͼƬ
//// 			crButtonWidgetNode *playerFaceWidget = dynamic_cast<crButtonWidgetNode *>(canvas->getWidget("TouXiang"));
//// 			if (playerFaceWidget)
//// 			{
//// 				crStateSet *state_set = dynamic_cast<crObject *>(( dynamic_cast<crGroup *>(playerFaceWidget->getChild(0)))->getChild(0))->getDrawable(0)->getStateSet();
//// 				crTexture2D *texture_2d = dynamic_cast<crTexture2D *>(state_set->getTextureAttribute(0,crStateAttribute::TEXTURE));
//// 				if (texture_2d)
//// 				{
//// 					texture_2d->setImage(0, texture_2d->getImageDataRequestHandler()->requestImageFile(strValue,texture_2d));
//// 					playerFaceWidget->setVisiable(true);
//// 				}
//// 			}
//		}
//	}
//}
///////////////////////////////////////////
////
////crJXJPlayerIconShopInitMethod
////
///////////////////////////////////////////
//crJXJPlayerIconShopInitMethod::crJXJPlayerIconShopInitMethod():
//	m_this(NULL){}
//crJXJPlayerIconShopInitMethod::crJXJPlayerIconShopInitMethod(const crJXJPlayerIconShopInitMethod& handle):
//	crMethod(handle),m_this(NULL)
//{
//}
//void crJXJPlayerIconShopInitMethod::inputParam(int i, void *param)
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
//		m_this = (CRCore::crCanvasNode * )param;
//		break;
//	}
//}
//
//void crJXJPlayerIconShopInitMethod::addParam(int i, const std::string& str)
//{
//	if (i % 2)
//	{
//// 		crWidgetNode * pWidget = m_this->getWidget(str.c_str());
//		m_ImageName.push_back(str);
//	}
//	else
//	{
//		m_ButtonName.push_back(str);
//	}
//}
//
//void crJXJPlayerIconShopInitMethod::operator()(crHandle &handle)
//{
//	crData *data = m_this->getDataClass();
//
//	//ȡ������
//	void *param = NULL;
//	JXJ::BtnIconShopMap * btnIconShopMap = NULL;
//	data->getParam(WCHDATA_JXJPlayerBtnIconShopMap,param);
//	btnIconShopMap = (JXJ::BtnIconShopMap *)param;
//	//JXJ::IconShopMap * iconShopMap = NULL;
//	//data->getParam(WCHDATA_JXJPlayerIconShopMap,param);
//	//iconShopMap = (JXJ::IconShopMap *)param;
//
//	for (int i = 0; i < m_ButtonName.size() && i<m_ImageName.size(); i++)
//	{
//		ref_ptr<crWidgetNode> pBtnWidget = m_this->getWidget(m_ButtonName[i].c_str());
//
//		ref_ptr<crWidgetNode> pImageWidget = m_this->getWidget(m_ImageName[i].c_str());
//
//		(*btnIconShopMap)[pBtnWidget] = pImageWidget;
//	}
//}

/////////////////////////////////////////
//
//crJXJRecvPlayerGameDataCreateStreamMethod
//
/////////////////////////////////////////
crJXJRecvPlayerGameDataCreateStreamMethod::crJXJRecvPlayerGameDataCreateStreamMethod():
	m_flag(false)
{}
crJXJRecvPlayerGameDataCreateStreamMethod::crJXJRecvPlayerGameDataCreateStreamMethod(const crJXJRecvPlayerGameDataCreateStreamMethod& handle)
	: m_this(NULL),
	m_flag(handle.m_flag)
{
}
void crJXJRecvPlayerGameDataCreateStreamMethod::inputParam(int i, void *param)
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
		m_this = (crPlayerGameData*)param;
		break;
	}
}

void crJXJRecvPlayerGameDataCreateStreamMethod::addParam(int i, const std::string& str)
{
}

unsigned int crJXJRecvPlayerGameDataCreateStreamMethod::getCountryPlayerCount(int nOffset)
{
	int rtn = 0;
	void *param = NULL;
	crData *gsBrainData = crServerBrainHandle::getInstance()->getDataClass();
	gsBrainData->excHandle(MAKECREPARAM(WCH_LockData,1));
	gsBrainData->getParam(WCHDATA_JXJShiliWei + nOffset, param);
	crJXJShili *shili = (crJXJShili *)param;
	if (shili)
	{
		crData *shilidata = shili->getDataClass();
		shilidata->excHandle(MAKECREPARAM(WCH_LockData,1));
		shilidata->getParam(WCHDATA_JXJPeopleMap, param);
		PeopleMap * peopleMap = (PeopleMap *)param;
		if (peopleMap)
		{
			rtn = peopleMap->size();
		}
		shilidata->excHandle(MAKECREPARAM(WCH_LockData,0));
	}
	gsBrainData->excHandle(MAKECREPARAM(WCH_LockData, 0));
	return rtn;
}

void crJXJRecvPlayerGameDataCreateStreamMethod::operator()(crHandle &handle)
{
	CRCore::crData * playerData = m_this->getDataClass();
	if(m_this && playerData && !m_flag)
	{
		m_flag = true;
		unsigned char shiliid = 0;
		unsigned short chengchiid = 0, homeid = 0;
		void * param = NULL;
		playerData->getParam(WCHDATA_JXJHomeID, param);
		homeid = *(unsigned short *)param;
		if (0 == homeid)	//�������
		{
			//��ȡ�������ҵ�������Ȼ�����õ�����
			unsigned int WeiPeopleCount = getCountryPlayerCount(0);	//κ��������
			unsigned int ShuPeopleCount = getCountryPlayerCount(1);	//���������
			unsigned int WuPeopleCount = getCountryPlayerCount(2);	//���������
			//double WeiValue = pow((100.0 / WeiPeopleCount), 4);
			//double ShuValue = pow((100.0 / ShuPeopleCount), 4);
			//double WuValue = pow((100.0 / WuPeopleCount), 4);
			int WeiRate = 10;
			bool isLoseCountry = false;
			shiliid = c_startShiliID;
			crServerBrainHandle::getInstance()->doEvent(WCH_JXJCheckCountryLose,MAKECREPARAM(&isLoseCountry,&shiliid));
			if(isLoseCountry)
			{
				WeiRate = 0;
			}
			else if (WeiPeopleCount < ShuPeopleCount && WeiPeopleCount < WuPeopleCount)
			{
				WeiRate = 80;
			}

			int ShuRate = 10;
			isLoseCountry = false;
			shiliid = c_startShiliID+1;
			crServerBrainHandle::getInstance()->doEvent(WCH_JXJCheckCountryLose,MAKECREPARAM(&isLoseCountry,&shiliid));
			if(isLoseCountry)
			{
				ShuRate = 0;
			}
			else if (ShuPeopleCount < WeiPeopleCount && ShuPeopleCount < WuPeopleCount)
			{
				ShuRate = 80;
			}
			int WuRate = 10;
			isLoseCountry = false;
			shiliid = c_startShiliID+2;
			crServerBrainHandle::getInstance()->doEvent(WCH_JXJCheckCountryLose,MAKECREPARAM(&isLoseCountry,&shiliid));
			if(isLoseCountry)
			{
				WuRate = 0;
			}
			else if (WuPeopleCount < WeiPeopleCount && WuPeopleCount < ShuPeopleCount)
			{
				WuRate = 80;
			}
			int rat = WeiRate+ShuRate+WuRate;
			int nRandomValue = rangei(0,rat).get_random();
			int shiliOffset = 0;
			if (WeiRate >= nRandomValue)
			{
				shiliOffset = 0;	//κ��
				////�ж��Ƿ�����
				//int myshiliid = shiliOffset + c_startShiliID;
				//
				//crServerBrainHandle::getInstance()->doEvent(WCH_JXJCheckCountryLose,MAKECREPARAM(&isLoseCountry,&myshiliid));
				//if (isLoseCountry)
				//{
				//	if (WuPeopleCount > ShuPeopleCount)
				//		shiliOffset = 1;
				//	else
				//		shiliOffset = 2;
				//}
			}
			else if (WeiRate + ShuRate >= nRandomValue)
			{
				shiliOffset = 1;	//���
				////�ж��Ƿ�����
				//int myshiliid = shiliOffset + c_startShiliID;
				//bool isLoseCountry = false;
				//crServerBrainHandle::getInstance()->doEvent(WCH_JXJCheckCountryLose,MAKECREPARAM(&isLoseCountry,&myshiliid));
				//if (isLoseCountry)
				//{
				//	if (WeiPeopleCount > WuPeopleCount)
				//		shiliOffset = 2;
				//	else
				//		shiliOffset = 0;
				//}
			}
			else
			{
				shiliOffset = 2;	//���
				////�ж��Ƿ�����
				//int myshiliid = shiliOffset + c_startShiliID;
				//bool isLoseCountry = false;
				//crServerBrainHandle::getInstance()->doEvent(WCH_JXJCheckCountryLose,MAKECREPARAM(&isLoseCountry,&myshiliid));
				//if (isLoseCountry)
				//{
				//	if (WeiPeopleCount > ShuPeopleCount)
				//		shiliOffset = 0;
				//	else
				//		shiliOffset = 1;
				//}
			}
			ref_ptr<crTableIO>shiliTab = crGlobalHandle::gData()->gGlobalTable(WCHDATA_JXJShiliTab);
			ref_ptr<crTableIO>homeTab = crGlobalHandle::gData()->gGlobalTable(WCHDATA_JXJHomeTab);
			crTableIO::StrVec record;
			if (shiliTab->queryOneRecord(0,crArgumentParser::appItoa(shiliOffset + c_startShiliID),record)>=0)
			{
				shiliid = (unsigned char)(atoi(record[0].c_str()));
				chengchiid = (unsigned short)(atoi(record[shiliTab->getTitleIndex("Ĭ�ϳǳ�")].c_str()));

				if (homeTab->queryOneRecord(homeTab->getTitleIndex("chengchiid"),crArgumentParser::appItoa(chengchiid),record)>=0)
				{
					homeid = atoi(record[0].c_str());
				}

				if (homeid != 0)
				{
					playerData->inputParam(WCHDATA_JXJShiliID, &shiliid);
					playerData->inputParam(WCHDATA_JXJHomeID, &homeid);
					playerData->inputParam(WCHDATA_JXJChengchiID, &chengchiid);

					//��ȯ����
					int playerid = m_this->getPlayerID();
					playerData->excHandle(MAKECREPARAM(WCH_LockData,1));
					playerData->getParam(WCHDATA_JXJGiftGold, param);
					int *giftGold = (int *)param;
					int nOffset = atoi(crGlobalHandle::gData()->gGameGlobalValue(WCHDATA_JXJRandomCountryGiftCount,0).c_str());
					INTLIMITADD(*giftGold, nOffset,INT_MAX);
					playerData->excHandle(MAKECREPARAM(WCH_LockData,0));

					//��shiliid��chengchiid��homeid���߸��ͻ���
					crNetConductor *gameServer = crNetContainer::getInstance()->getNetConductor(GameServer); 
					int playerID = m_this->getPlayerID();
					ref_ptr<crGameServerPlayerData> player = dynamic_cast<crGameServerPlayerData *>(gameServer->getNetDataManager()->getPlayerData(playerID));
					if(player.valid())
					{
						crJXJRandomZhenYingTellClientIdPacket suijiCreateRole;
						crJXJRandomZhenYingTellClientIdPacket::buildReplyPacket(suijiCreateRole, playerID, shiliid, chengchiid, homeid, *giftGold);
						gameServer->getNetManager()->sendPacket(player->getPlayerConnectServerAddress(),suijiCreateRole);
					}
					///��Ϸ��־
					std::string logdata = "�������ѡ��,������" + crArgumentParser::appItoa(nOffset) + "������" + crArgumentParser::appItoa(shiliid);
					GameLogData gamelog(Log_RandShili,logdata);
					crServerBrainHandle::getInstance()->doEvent(WCH_GameLog,MAKECREPARAM(playerid,&gamelog));
				}
			}
		}
	}
}




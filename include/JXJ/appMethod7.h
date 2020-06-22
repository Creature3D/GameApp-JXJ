/**********************************************************************
*
*	�ļ�:	   appMethod7.h
*
*	����:	   
*
*	����:	   
*					
*
**********************************************************************/
#ifndef JXJ_APPMETHOD7_H
#define JXJ_APPMETHOD7_H
#include <CRCore/crHandleManager.h>
#include <CRCore/crWidgetNode.h>
#include <CRCore/crDataManager.h>
#include <CRCore/crRange.h>
#include <CREncapsulation/crLoader.h>
#include <CRNet/crNetContainer.h>
#include <CRNetApp/appDataParam.h>
#include <CRNetApp/appDataClass.h>
#include <CRNetApp/appMsg.h>
#include <CRNetApp/appNetGameData.h>
#include <CRNetApp/appNetCallbacks.h>
#include <CRNetApp/appNetDefine.h>
#include <CRNetApp/appNetPackets.h>
#include <CRNetApp/appNetPackets2.h>
#include <CRNetApp/appClientPlayerData.h>
#include <CRUtil/crUpdateVisitor.h>
#include <CRText/crText.h>
#include <JXJ/appData.h>
#include <JXJ/appData2.h>
#include <JXJ/appData5.h>
#include <CRUI/crWidgetExtend.h>
#include <vector>

namespace JXJ
{

//typedef std::vector<std::pair<std::string, std::string>> CanvasIconVec;
/////////////////////////////////////////
////
////crJXJAccomplishZhengzhantianxiaWinCountMethod
////�ɾ�-����-��ս����ʤ������
////
///////////////////////////////////////////
//class crJXJAccomplishZhengzhantianxiaWinCountMethod :public CRCore::crMethod
//{//Client Method
//public:
//	crJXJAccomplishZhengzhantianxiaWinCountMethod();
//	crJXJAccomplishZhengzhantianxiaWinCountMethod(const crJXJAccomplishZhengzhantianxiaWinCountMethod& handle);
//	MethodClass(JXJ, JXJAccomplishZhengzhantianxiaWinCount)
//		virtual void operator()(crHandle &handle);
//	virtual void inputParam(int i, void *param);
//	virtual void addParam(int i, const std::string& str);
//	bool isFubenPass(int fubenId);
//	unsigned char fubenPassNum();
//	unsigned char searchZhouFubenCount(std::string zhouName);
//	unsigned char searchZhouFubenPassNum(std::string zhouName);
//protected:
//	crJXJAccomplish *m_this;
//	int m_mode;//0��ս����
//	std::string m_canvas;
//	int m_time;
//	std::string m_zhouName;
//	CREncapsulation::crTableIO *accomplish_tab;
//	AccomplishMap *accomplishMap;
//	CRNetApp::crPlayerGameData *myPlayer;
//	CRCore::crData *playerData;
//	CRCore::crData *mainroledata;
//	int AchievementIdIndex;
//	int remarkIndex;
//	int titleOneIndex;
//};
//
///////////////////////////////////////////
////
////crJXJAccomplishQueryLordMethod
////�ɾ�-����
////
///////////////////////////////////////////
//class crJXJAccomplishQueryLordMethod :public CRCore::crMethod
//{//Client Method
//public:
//	crJXJAccomplishQueryLordMethod();
//	crJXJAccomplishQueryLordMethod(const crJXJAccomplishQueryLordMethod& handle);
//	MethodClass(JXJ, JXJAccomplishQueryLord)
//		virtual void operator()(crHandle &handle);
//	virtual void inputParam(int i, void *param);
//	virtual void addParam(int i, const std::string& str);
//	int setAccomplishStep(CRCore::crData *data, std::string titleOne, int remarksId, int WCHDATA_JXJ_id);
//	int setAccomplishStep(std::string titleOne, int remarksId, int WCHDATA_JXJ_id, int WCHDATA_JXJ_num);
//protected:
//	crJXJAccomplish *m_this;
//	int m_mode;//0��ս����
//	std::string m_canvas;
//	int m_time;
//	std::string m_zhouName;
//};
///////////////////////////////////////////
////
////crJXJAccomplishFengdiMethod
////�ɾ�-���
////
///////////////////////////////////////////
//class crJXJAccomplishFengdiMethod :public CRCore::crMethod
//{//Client Method
//public:
//	crJXJAccomplishFengdiMethod();
//	crJXJAccomplishFengdiMethod(const crJXJAccomplishFengdiMethod& handle);
//	MethodClass(JXJ, JXJAccomplishFengdi)
//		virtual void operator()(crHandle &handle);
//	virtual void inputParam(int i, void *param);
//	virtual void addParam(int i, const std::string& str);
//	int initAccomplishData();
//	int setAccomplishStep(CRCore::crData *data, std::string titleOne, int remarksId, int WCHDATA_JXJ_id);
//	int setAccomplishStep(std::string titleOne, int remarksId, int WCHDATA_JXJ_id, int WCHDATA_JXJ_num);
//protected:
//	crJXJAccomplish *m_this;
//	int m_mode;//0��ս����
//	std::string m_canvas;
//	int m_time;
//	std::string m_zhouName;
//	CREncapsulation::crTableIO *accomplish_tab;
//	AccomplishMap *accomplishMap;
//	CRNetApp::crPlayerGameData *myPlayer;
//	CRCore::crData *playerData;
//	CRCore::crData *mainroledata;
//	int AchievementIdIndex;
//	int remarkIndex;
//	int titleOneIndex;
//};
///////////////////////////////////////////
////
////crJXJSearchAccomplishCountMethod
////�ɾʹ�ɵ��ж�
////
///////////////////////////////////////////
////class crJXJSearchAccomplishCountMethod :public CRCore::crMethod
////{//Client Method
////public:
////	crJXJSearchAccomplishCountMethod();
////	crJXJSearchAccomplishCountMethod(const crJXJSearchAccomplishCountMethod& handle);
////	MethodClass(JXJ, JXJSearchAccomplishCount)
////		virtual void operator()(crHandle &handle);
////	virtual void inputParam(int i, void *param);
////	virtual void addParam(int i, const std::string& str);
////	bool isFubenPass(int fubenId);
////	int initAccomplishData();
////	unsigned char fubenPassNum();
////	unsigned char searchZhouFubenCount(std::string zhouName);
////	unsigned char searchZhouFubenPassNum(std::string zhouName);
////	int searchFubenAchievement();
////	int searchLordAchievement();
////	int searchBuildingAchievement();
////	int setAccomplishStep(CRCore::crData *data, std::string titleOne, int remarksId, int WCHDATA_JXJ_id);
////	int setAccomplishStep(std::string titleOne, int remarksId, int WCHDATA_JXJ_id, int WCHDATA_JXJ_num);
////protected:
////	crJXJAccomplish *m_this;
////	int m_mode;//0��ս����
////	std::string m_canvas;
////	int m_time;
////	std::string m_zhouName;
////	CREncapsulation::crTableIO *accomplish_tab;
////	AccomplishMap *accomplishMap;
////	CRNetApp::crPlayerGameData *myPlayer;
////	CRCore::crData *playerData;
////	CRCore::crData *mainroledata;
////	int AchievementIdIndex;
////	int remarkIndex;
////	int titleOneIndex;
////};
///////////////////////////////////////////
////
////crJXJSearchLingzhuLVMethod
////
///////////////////////////////////////////
//class crJXJSearchLordLVMethod :public CRCore::crMethod
//{//Client Method
//public:
//	crJXJSearchLordLVMethod();
//	crJXJSearchLordLVMethod(const crJXJSearchLordLVMethod& handle);
//	MethodClass(JXJ, JXJSearchLordLV)
//		virtual void operator()(crHandle &handle);
//	virtual void inputParam(int i, void *param);
//	virtual void addParam(int i, const std::string& str);
//protected:
//	crJXJAccomplish *m_this;
//	int m_mode;//0��ս����
//	std::string m_canvas;
//	int m_time;
//};
///////////////////////////////////////////
////
////crJXJShowAchievementStepMethod
////����һ���ɾ��Ƿ����
////
///////////////////////////////////////////
//class crJXJShowAchievementStepMethod :public CRCore::crMethod
//{//Client Method
//public:
//	crJXJShowAchievementStepMethod();
//	crJXJShowAchievementStepMethod(const crJXJShowAchievementStepMethod& handle);
//	MethodClass(JXJ, JXJShowAchievementStep)
//		virtual void operator()(crHandle &handle);
//	virtual void inputParam(int i, void *param);
//	virtual void addParam(int i, const std::string& str);
//	int crJXJShowAchievementStepMethod::fubenPass(int id);
//protected:
//	crJXJAccomplish *m_this;
//	int m_mode;//0��ս����
//	std::string m_canvas;
//	int m_time;
//	std::string m_zhouPassData;
//	int m_achievementIndex;
//};
///////////////////////////////////////////
////
////GeneralTips
////TIPS
////
///////////////////////////////////////////
//class GeneralTips
//{//Client Method
//public:
//	GeneralTips(std::string m_tipsCanvas, CRCore::crWidgetNode *m_this);
//	GeneralTips(std::string m_tipsCanvas);
//	void GeneralTips::setTipRight();
//	void GeneralTips::setTipUpper();
//	void GeneralTips::setTipAuto();
//	//void GeneralTipsMethod::showTips(CRCore::crCanvasNode *tips);
//	void GeneralTips::setText(std::string m_tipsTextWidget, std::string textStr);
//	void GeneralTips::setText(std::string m_tipsTextWidget, std::string textStr, CRCore::crVector4 textColor);
//	void GeneralTips::setImgage(std::string m_tipsImgWidget, std::string imgStr);
//protected:
//	CRCore::crWidgetNode* m_this;//��������ƶ����Ŀؼ�
//	std::string m_tipsTextWidget;
//	std::string m_tipsImgWidget;
//	CRUI::crStaticTextWidgetNode *tipsText;
//	CRUI::crImageBoxWidgetNode *tipsImg;
//	CRCore::crCanvasNode *tips;
//};
///////////////////////////////////////////
////
////crJXJUIOficialRankBestLevelTipMethod
////������õĹ�ְ�Ѿ�����߼�����껬����Ǩ��ť��ʾ "�Ѿ�����߼���"
////
///////////////////////////////////////////
//class crJXJUIOficialRankBestLevelTipMethod : public CRCore::crMethod
//{//Client Method
//public:
//	crJXJUIOficialRankBestLevelTipMethod();
//	crJXJUIOficialRankBestLevelTipMethod(const crJXJUIOficialRankBestLevelTipMethod& handle);
//	MethodClass(JXJ, JXJUIOficialRankBestLevelTip)
//		virtual void operator()(crHandle &handle);
//	virtual void inputParam(int i, void *param);
//	virtual void addParam(int i, const std::string& str);
//protected:
//	CRCore::crWidgetNode* m_this;
//	std::string m_tipsCanvas;
//	std::string m_tipsTextWidget;
//	std::string m_canvasName;
//};
////class crJXJCheckChengjiuCompleteMethod :public CRCore::crMethod
////{//Client Method & GameServer Method
////public:
////	crJXJCheckChengjiuCompleteMethod();
////	crJXJCheckChengjiuCompleteMethod(const crJXJCheckChengjiuCompleteMethod& handle);
////	MethodClass(JXJ, JXJCheckChengjiuComplete)
////		virtual void operator()(crHandle &handle);
////	virtual void inputParam(int i, void *param);
////	virtual void addParam(int i, const std::string& str);
////	void isComplete();
////protected:
////	CRNetApp::crPlayerGameData *m_this;
////	std::string m_tipcanvas;
////	std::string m_tipcontent;
////	int *m_type;
////	crBagItemData *itembag;
////};

class crJXJSearchLordLevelInfoMethod :public CRCore::crMethod
{//Client Method
public:
	crJXJSearchLordLevelInfoMethod();
	crJXJSearchLordLevelInfoMethod(const crJXJSearchLordLevelInfoMethod& handle);
	MethodClass(JXJ, JXJSearchLordLevelInfo)
	virtual void operator()(crHandle &handle);
	virtual void inputParam(int i, void *param);
	virtual void addParam(int i, const std::string& str);
protected:
	crJXJAccomplish *m_this;
};

class crJXJSearchLordLevelInfoCompleteCheckMethod :public CRCore::crMethod
{//GameServer Method
public:
	crJXJSearchLordLevelInfoCompleteCheckMethod();
	crJXJSearchLordLevelInfoCompleteCheckMethod(const crJXJSearchLordLevelInfoCompleteCheckMethod& handle);
	MethodClass(JXJ, JXJSearchLordLevelInfoCompleteCheck)
	virtual void operator()(crHandle &handle);
	virtual void inputParam(int i, void *param);
	virtual void addParam(int i, const std::string& str);
protected:
	crJXJAccomplish *m_this;
	CRNetApp::crPlayerGameData *m_player;
};

}
#endif 
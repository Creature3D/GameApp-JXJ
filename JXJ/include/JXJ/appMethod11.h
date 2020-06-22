/**********************************************************************
*
*	�ļ�:	   appMethod11.h
*
*	����:	   
*
*	����:	   ������
*					
*
**********************************************************************/
#ifndef JXJ_APPMETHOD_11_H
#define JXJ_APPMETHOD_11_H
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
#include <CRUI/crWidgetExtend.h>
namespace JXJ {

////������ʾ�Ի����ʱ���ʼ��
//class crJXJUIImageDecorateUpdateMethod :public CRCore::crMethod
//{//Client Method
//public:
//	crJXJUIImageDecorateUpdateMethod(){};
//	crJXJUIImageDecorateUpdateMethod(const crJXJUIImageDecorateUpdateMethod& handle);
//	MethodClass(JXJ, JXJUIImageDecorateUpdate)
//		virtual void operator()(crHandle &handle);
//	virtual void inputParam(int i, void *param);
//	virtual void addParam(int i, const std::string& str);
//protected:
//	CRCore::crCanvasNode *m_this;
//
//	std::string m_Dialog;
//	std::string m_Radio1;
//	std::string m_Radio2;
//};
//
////���͹���ͷ����Ϣ
//class crJXJSendPlayerBuyIconMethod : public CRCore::crMethod
//{//Client Method
//public:
//	crJXJSendPlayerBuyIconMethod();
//	crJXJSendPlayerBuyIconMethod(const crJXJSendPlayerBuyIconMethod& handle);
//	MethodClass(JXJ, JXJSendPlayerBuyIcon)
//		virtual void operator()(crHandle &handle);
//	virtual void inputParam(int i, void *param);
//	virtual void addParam(int i, const std::string& str);
//protected:
//	CRCore::crCanvasNode *m_this;
//	CRCore::ref_ptr<CRCore::crStreamBuf> m_stream;
//	unsigned char m_buyIconIndex;	//��0��ʼ
//};
//
////������ͷ����Ϣ
//class crJXJRecvPlayerBuyIconMethod :public CRCore::crMethod
//{//GameServer & Client Method
//public:
//	crJXJRecvPlayerBuyIconMethod();
//	crJXJRecvPlayerBuyIconMethod(const crJXJRecvPlayerBuyIconMethod& handle);
//	MethodClass(JXJ, JXJRecvPlayerBuyIcon)
//		virtual void operator()(crHandle &handle);
//	virtual void inputParam(int i, void *param);
//	virtual void addParam(int i, const std::string& str);
//protected:
//	CRNetApp::crPlayerGameData *m_this;
//	CRCore::ref_ptr<CRCore::crStreamBuf> m_stream;
//	int m_netType;
//	int m_buyIconIndex;
//};
//
////ʹ��ͷ����߱���
//class crJXJPlayerUseIconMethod :public CRCore::crMethod
//{//Client Method
//public:
//	crJXJPlayerUseIconMethod();
//	crJXJPlayerUseIconMethod(const crJXJPlayerUseIconMethod& handle);
//	MethodClass(JXJ, JXJPlayerUseIcon)
//		virtual void operator()(crHandle &handle);
//	virtual void inputParam(int i, void *param);
//	virtual void addParam(int i, const std::string& str);
//protected:
//	CRCore::crCanvasNode *m_this;
//	CRCore::ref_ptr<CRCore::crStreamBuf> m_stream;
//	int m_netType;
//	unsigned char m_useIconIndex;
//};
//
////�������Ϳͻ��˴���ʹ��ͷ����߱���
//class crJXJProcPlayerUseIconMethod :public CRCore::crMethod
//{//Client GameServer Method
//public:
//	crJXJProcPlayerUseIconMethod();
//	crJXJProcPlayerUseIconMethod(const crJXJProcPlayerUseIconMethod& handle);
//	MethodClass(JXJ, JXJProcPlayerUseIcon)
//		virtual void operator()(crHandle &handle);
//	virtual void inputParam(int i, void *param);
//	virtual void addParam(int i, const std::string& str);
//protected:
//	CRNetApp::crPlayerGameData *m_this;
//	CRCore::ref_ptr<CRCore::crStreamBuf> m_stream;
//	int m_netType;
//	unsigned char m_useIconIndex;
//};
//
//class crJXJPlayerIconShopInitMethod :public CRCore::crMethod
//{//Client Method
//public:
//	crJXJPlayerIconShopInitMethod();
//	crJXJPlayerIconShopInitMethod(const crJXJPlayerIconShopInitMethod& handle);
//	MethodClass(JXJ, JXJPlayerIconShopInit)
//		virtual void operator()(crHandle &handle);
//	virtual void inputParam(int i, void *param);
//	virtual void addParam(int i, const std::string& str);
//protected:
//	CRCore::crCanvasNode *m_this;
//	std::vector<std::string> m_ButtonName;
//	std::vector<std::string> m_ImageName;
//};

class crJXJRecvPlayerGameDataCreateStreamMethod :public CRCore::crMethod
{//GameServer Method
public:
	crJXJRecvPlayerGameDataCreateStreamMethod();
	crJXJRecvPlayerGameDataCreateStreamMethod(const crJXJRecvPlayerGameDataCreateStreamMethod& handle);
	MethodClass(JXJ, JXJRecvPlayerGameDataCreateStream)
		virtual void operator()(crHandle &handle);
	virtual void inputParam(int i, void *param);
	virtual void addParam(int i, const std::string& str);
protected:
	CRNetApp::crPlayerGameData *m_this;
	bool m_flag;

	unsigned int getCountryPlayerCount(int nOffset);	//�õ�ĳ��������
};



}
#endif

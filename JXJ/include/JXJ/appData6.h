/**********************************************************************
*
*	�ļ�:	   appData6.h
*
*	����:	   
*
*	����:	   ������
*					
*
	**********************************************************************/
#ifndef JXJ_APPDATA6_H
#define JXJ_APPDATA6_H
#include <CRCore/crStreamBuf.h>
#include <CRCore/crHandleManager.h>
#include <CRCore/crDataManager.h>
#include <CRCore/crWchMsg.h>
#include <gnelib.h>
#include <CRNetApp/appDataParam.h>
#include <CRNetApp/appMsg.h>
#include <CRCore/thread/crMutex.h>
#include <CRCore/thread/crScopedLock.h>
#include <CRNetApp/appDataClass.h>
#include <CREncapsulation/crTableIO.h>
#include <JXJ/appData.h>

namespace JXJ{

	//typedef std::map<CRCore::ref_ptr<CRCore::crWidgetNode>,CRCore::ref_ptr<CRCore::crWidgetNode> > BtnIconShopMap;//btn,imagebox
	//typedef std::map<CRCore::ref_ptr<CRCore::crWidgetNode>,unsigned char>IconShopMap;//imagebox,iconid

	//class crJXJPlayerIconShopData :  public CRCore::crUIData
	//{
	//public:
	//	crJXJPlayerIconShopData();
	//	crJXJPlayerIconShopData(const crJXJPlayerIconShopData& data);
	//	DataClass(JXJ, JXJPlayerIconShop)
	//		virtual void addParam(int i, const std::string& str);
	//	virtual void inputParam(int i, void *param);
	//	virtual void getParam(int i, void*& param);
	//	virtual void excHandle(CREPARAM msg);
	//protected:
	//	GNE::Mutex m_dataMutex;
	//	int m_nSex;	//�Ա�
	//	int m_nCurSelType;	//��ǰѡ�����
	//	BtnIconShopMap m_btnIconShopMap;
	//	IconShopMap m_iconShopMap;
	//};

}

#endif

/**********************************************************************
*
*	�ļ�:	   appMethod16.h
*
*	����:	   
*
*	����:	   Ԭΰ��
*					
*
**********************************************************************/
#ifndef JXJ_APPMETHOD16_H
#define JXJ_APPMETHOD16_H
#include <CRCore/crHandleManager.h>
#include <crcore/crWidgetNode.h>
#include <JXJ/appData.h>
#include <CRUI/crWidgetExtend.h>
#include <CREncapsulation/crTableIO.h>

const int MAX_ACITVITY_AWARD = 6;//������5������;
const int ACTIVITY_YELLOW_ID = 1100;//������������id;
const int ACTIVITY_YEAR_YELLOW = 1109;//��ѻ���ÿ������id;
const int ACTIVITY_YELLOW_UPGRADE = 1110;//�����������;
const int MAX_YELLOW_LEVEL = 8;//�������8��
enum YELLOW_AWARD_TYPE
{
	YELLOW_NEWBIE=1,
	YELLOW_DAILY,
	YELLOW_YEAR_DAILY,
	YELLOW_UPGRADE_NORMAL,
	YELLOW_UPGRADE
};
char setRewardInfo(const CRCore::crVector4i& award,CRUI::crImageBoxWidgetNode * imageBox,CRUI::crStaticTextWidgetNode* input = NULL,CRCore::crMultiSwitch* cardcolorsw = NULL);//����1��ʾcard
void sendReward(std::vector<CRCore::crVector4i>& awardVec,CRNetApp::crPlayerGameData* pPlayer,const std::string &command);
namespace JXJ{

	//����װ��ҳ(UI)
	class crJXJUIBuySavedEquipPageMethod :public CRCore::crMethod
	{//Client Method
	public:
		crJXJUIBuySavedEquipPageMethod();
		crJXJUIBuySavedEquipPageMethod(const crJXJUIBuySavedEquipPageMethod& handle);
		MethodClass(JXJ, JXJUIBuySavedEquipPage)
			virtual void operator()(crHandle &handle);
		virtual void inputParam(int i, void *param);
		virtual void addParam(int i, const std::string& str);
	protected:
		CRCore::crWidgetNode *m_this;
		std::string m_promptCanvas;
		std::string m_information;
		std::string m_okbtn;
	};

	//����װ��ҳ(client);
	class crJXJBuySavedEquipPageMethod :public CRCore::crMethod
	{//Client Method
	public:
		crJXJBuySavedEquipPageMethod();
		crJXJBuySavedEquipPageMethod(const crJXJBuySavedEquipPageMethod& handle);
		MethodClass(JXJ, JXJBuySavedEquipPage)
		virtual void operator()(crHandle &handle);
		virtual void inputParam(int i, void *param);
		virtual void addParam(int i, const std::string& str);
	protected:
		CRCore::crWidgetNode *m_this;
	};

	//����װ��ҳ(server);
	class crJXJRecvBuySavedEquipPageMethod :public CRCore::crMethod
	{//GameServer Method
	public:
		crJXJRecvBuySavedEquipPageMethod();
		crJXJRecvBuySavedEquipPageMethod(const crJXJRecvBuySavedEquipPageMethod& handle);
		MethodClass(JXJ, JXJRecvBuySavedEquipPage)
		virtual void operator()(crHandle &handle);
		virtual void inputParam(int i, void *param);
		virtual void addParam(int i, const std::string& str);
	protected:
		CRNetApp::crPlayerGameData *m_this;
		CRCore::ref_ptr<CRCore::crStreamBuf> m_stream;
		int m_netType;
	};

	//�л�װ��ҳ(UI);
	class crJXJUISwitchEquipMethod:public CRCore::crMethod
	{// client method
	public:
		crJXJUISwitchEquipMethod();
		crJXJUISwitchEquipMethod(const crJXJUISwitchEquipMethod& handle);

		MethodClass(JXJ, JXJUISwitchEquip)

		virtual void operator()(crHandle &handle);

		virtual void inputParam(int i, void *param);
		virtual void addParam(int i, const std::string& str);
	protected:
		CRUI::crRadioGroupWidgetNode	*m_this;
	};

	class crJXJRecvSwitchEquipPageMethod:public CRCore::crMethod
	{// client method
	public:
		crJXJRecvSwitchEquipPageMethod();
		crJXJRecvSwitchEquipPageMethod(const crJXJRecvSwitchEquipPageMethod& handle);

		MethodClass(JXJ, JXJRecvSwitchEquipPage)

		virtual void operator()(crHandle &handle);

		virtual void inputParam(int i, void *param);
		virtual void addParam(int i, const std::string& str);
	protected:
		CRNetApp::crPlayerGameData				*m_this;
		CRCore::ref_ptr<CRCore::crStreamBuf>	m_stream;
		int										m_net_type;
	};

	//���°󶨱�ӽ���;
	class crJXJUIFeudalLord_BangdingUpdateMethod : public CRCore::crMethod
	{//Client Method
	public:
		crJXJUIFeudalLord_BangdingUpdateMethod();
		crJXJUIFeudalLord_BangdingUpdateMethod(const crJXJUIFeudalLord_BangdingUpdateMethod& handle);
		MethodClass(JXJ, JXJUIFeudalLord_BangdingUpdate)
			virtual void operator()(crHandle &handle);
		virtual void inputParam(int i, void *param);
		virtual void addParam(int i, const std::string& str);
	protected:
		CRCore::crCanvasNode *m_this;
		//////////////////////////////////////////////////////////////////////////
		std::string m_bindInput[4];
		std::string m_equipInput[4];
		std::string m_equipButton[4];
		std::string m_gamelist[4];
		std::string m_combobox[4];
	};

	//����󶨱��(UI)
	class crJXJUISave_BindFormationMethod : public CRCore::crMethod
	{//Client Method
	public:
		crJXJUISave_BindFormationMethod();
		crJXJUISave_BindFormationMethod(const crJXJUISave_BindFormationMethod& handle);
		MethodClass(JXJ, JXJUISave_BindFormation)
			virtual void operator()(crHandle &handle);
		virtual void inputParam(int i, void *param);
		virtual void addParam(int i, const std::string& str);
	protected:
		CRCore::crWidgetNode *m_this;
		std::string m_combobox[4];
	};

	//����󶨱��(server)
	class crJXJRecvSave_BindFormationMethod :public CRCore::crMethod
	{//GameServer Method
	public:
		crJXJRecvSave_BindFormationMethod();
		crJXJRecvSave_BindFormationMethod(const crJXJRecvSave_BindFormationMethod& handle);
		MethodClass(JXJ, JXJRecvSave_BindFormation)
			virtual void operator()(crHandle &handle);
		virtual void inputParam(int i, void *param);
		virtual void addParam(int i, const std::string& str);
	protected:
		CRNetApp::crPlayerGameData *m_this;
		CRCore::ref_ptr<CRCore::crStreamBuf> m_stream;
		int m_netType;
	};

	//�������������ʼ��(ui)
	class crJXJUIYellowNewbieMethod : public CRCore::crMethod
	{//Client Method
	public:
		crJXJUIYellowNewbieMethod();
		crJXJUIYellowNewbieMethod(const crJXJUIYellowNewbieMethod& handle);
		MethodClass(JXJ, JXJUIYellowNewbie)
			virtual void operator()(crHandle &handle);
		virtual void inputParam(int i, void *param);
		virtual void addParam(int i, const std::string& str);
	protected:
		CRCore::crCanvasNode *m_this;
		std::string m_icons[4];
		std::string m_lockSwitch;
		std::string m_buttonSwitch;
		std::string m_input;

	};

	//��ȡ�����������
	class crJXJUIGetYellowNewbieAwardMethod : public CRCore::crMethod
	{//Client Method
	public:
		crJXJUIGetYellowNewbieAwardMethod();
		crJXJUIGetYellowNewbieAwardMethod(const crJXJUIGetYellowNewbieAwardMethod& handle);
		MethodClass(JXJ, JXJUIGetYellowNewbieAward)
			virtual void operator()(crHandle &handle);
		virtual void inputParam(int i, void *param);
		virtual void addParam(int i, const std::string& str);
	protected:
		CRCore::crWidgetNode *m_this;
	};

	//��ȡ�����������(server)
	class crJXJRecvGetYellowNewbieAwardMethod :public CRCore::crMethod
	{//GameServer Method
	public:
		crJXJRecvGetYellowNewbieAwardMethod();
		crJXJRecvGetYellowNewbieAwardMethod(const crJXJRecvGetYellowNewbieAwardMethod& handle);
		MethodClass(JXJ, JXJRecvGetYellowNewbieAward)
			virtual void operator()(crHandle &handle);
		virtual void inputParam(int i, void *param);
		virtual void addParam(int i, const std::string& str);
	protected:
		CRNetApp::crPlayerGameData *m_this;
		CRCore::ref_ptr<CRCore::crStreamBuf> m_stream;
		int m_netType;
	};


	//�����ֵ
	class crJXJUIYellowRechargeMethod : public CRCore::crMethod
	{//Client Method
	public:
		crJXJUIYellowRechargeMethod();
		crJXJUIYellowRechargeMethod(const crJXJUIYellowRechargeMethod& handle);
		MethodClass(JXJ, JXJUIYellowRecharge)
			virtual void operator()(crHandle &handle);
		virtual void inputParam(int i, void *param);
		virtual void addParam(int i, const std::string& str);
	protected:
		CRCore::crWidgetNode *m_this;
		std::string m_url;
	};

	//��ѻ����ֵ
	class crJXJUIYellowYearRechargeMethod : public CRCore::crMethod
	{//Client Method
	public:
		crJXJUIYellowYearRechargeMethod();
		crJXJUIYellowYearRechargeMethod(const crJXJUIYellowYearRechargeMethod& handle);
		MethodClass(JXJ, JXJUIYellowYearRecharge)
			virtual void operator()(crHandle &handle);
		virtual void inputParam(int i, void *param);
		virtual void addParam(int i, const std::string& str);
	protected:
		CRCore::crWidgetNode *m_this;
		std::string m_url;
	};

	//������Ȩ�����ʼ��(ui);
	class crJXJUIYellowPrivilegeMethod : public CRCore::crMethod
	{//Client Method
	public:
		crJXJUIYellowPrivilegeMethod();
		crJXJUIYellowPrivilegeMethod(const crJXJUIYellowPrivilegeMethod& handle);
		MethodClass(JXJ, JXJUIYellowPrivilege)
			virtual void operator()(crHandle &handle);
		virtual void inputParam(int i, void *param);
		virtual void addParam(int i, const std::string& str);
	protected:
		CRCore::crCanvasNode *m_this;
		std::string m_icons[43];
		std::string m_yellowSwitch;
		std::string m_inputs[43];
		std::string m_iconSwitch;
		std::string m_levelSwitch;
		std::string m_yearSwitch;
	};

	//�򿪻���ÿ��;
	class crJXJUIDailyYellowShowMethod : public CRCore::crMethod
	{//Client Method
	public:
		crJXJUIDailyYellowShowMethod();
		crJXJUIDailyYellowShowMethod(const crJXJUIDailyYellowShowMethod& handle);
		MethodClass(JXJ, JXJUIDailyYellowShow)
			virtual void operator()(crHandle &handle);
		virtual void inputParam(int i, void *param);
		virtual void addParam(int i, const std::string& str);
	protected:
		CRCore::crWidgetNode *m_this;
		std::string m_yellow;
		std::string m_year_yellow;
	};

	//����ÿ�����;
	class crJXJUIDailyYellowAwardMethod : public CRCore::crMethod
	{//Client Method
	public:
		crJXJUIDailyYellowAwardMethod();
		crJXJUIDailyYellowAwardMethod(const crJXJUIDailyYellowAwardMethod& handle);
		MethodClass(JXJ, JXJUIDailyYellowAward)
			virtual void operator()(crHandle &handle);
		virtual void inputParam(int i, void *param);
		virtual void addParam(int i, const std::string& str);
	protected:
		CRCore::crCanvasNode *m_this;
		std::string m_icons[4];
		std::string m_lockSwitch;
		std::string m_buttonSwitch;
		std::string m_btnGet;
	};

	//��ѻ���ÿ�����;
	class crJXJUIDailyYearYellowAwardMethod : public CRCore::crMethod
	{//Client Method
	public:
		crJXJUIDailyYearYellowAwardMethod();
		crJXJUIDailyYearYellowAwardMethod(const crJXJUIDailyYearYellowAwardMethod& handle);
		MethodClass(JXJ, JXJUIDailyYearYellowAward)
			virtual void operator()(crHandle &handle);
		virtual void inputParam(int i, void *param);
		virtual void addParam(int i, const std::string& str);
	protected:
		CRCore::crCanvasNode *m_this;
		std::string m_icons[8];
		std::string m_lockSwitch;
		std::string m_btnGet;
	};

	//��ȡÿ�����
	class crJXJUIGetDailyYellowAwardMethod : public CRCore::crMethod
	{//Client Method
	public:
		crJXJUIGetDailyYellowAwardMethod();
		crJXJUIGetDailyYellowAwardMethod(const crJXJUIGetDailyYellowAwardMethod& handle);
		MethodClass(JXJ, JXJUIGetDailyYellowAward)
		virtual void operator()(crHandle &handle);
		virtual void inputParam(int i, void *param);
		virtual void addParam(int i, const std::string& str);
	protected:
		CRCore::crWidgetNode *m_this;
		unsigned char m_type;
	};

	//��ȡÿ�����
	class crJXJRecvGetDailyYellowAwardMethod : public CRCore::crMethod
	{//Server Method
	public:
		crJXJRecvGetDailyYellowAwardMethod();
		crJXJRecvGetDailyYellowAwardMethod(const crJXJRecvGetDailyYellowAwardMethod& handle);
		MethodClass(JXJ, JXJRecvGetDailyYellowAward)
		virtual void operator()(crHandle &handle);
		virtual void inputParam(int i, void *param);
		virtual void addParam(int i, const std::string& str);
	protected:
		CRNetApp::crPlayerGameData *m_this;
		CRCore::ref_ptr<CRCore::crStreamBuf> m_stream;
		int m_netType;
	};

	//���������������(ui);
	class crJXJUIYellowUpgradeAwardMethod : public CRCore::crMethod
	{//Client Method
	public:
		crJXJUIYellowUpgradeAwardMethod();
		crJXJUIYellowUpgradeAwardMethod(const crJXJUIYellowUpgradeAwardMethod& handle);
		MethodClass(JXJ, JXJUIYellowUpgradeAward)
			virtual void operator()(crHandle &handle);
		virtual void inputParam(int i, void *param);
		virtual void addParam(int i, const std::string& str);
	protected:
		CRCore::crCanvasNode *m_this;
		std::string m_icons[8];
		std::string m_lockSwitch;
		std::string m_buttonSwitch;
	};

	//��ȡ�����������
	class crJXJUIGetYellowUpgradeAwardMethod : public CRCore::crMethod
	{//Client Method
	public:
		crJXJUIGetYellowUpgradeAwardMethod();
		crJXJUIGetYellowUpgradeAwardMethod(const crJXJUIGetYellowUpgradeAwardMethod& handle);
		MethodClass(JXJ, JXJUIGetYellowUpgradeAward)
			virtual void operator()(crHandle &handle);
		virtual void inputParam(int i, void *param);
		virtual void addParam(int i, const std::string& str);
	protected:
		CRCore::crWidgetNode *m_this;
	};

	//�����������
	class crJXJRecvGetYellowUpgradeAwardMethod : public CRCore::crMethod
	{//Server Method
	public:
		crJXJRecvGetYellowUpgradeAwardMethod();
		crJXJRecvGetYellowUpgradeAwardMethod(const crJXJRecvGetYellowUpgradeAwardMethod& handle);
		MethodClass(JXJ, JXJRecvGetYellowUpgradeAward)
			virtual void operator()(crHandle &handle);
		virtual void inputParam(int i, void *param);
		virtual void addParam(int i, const std::string& str);
	protected:
		CRNetApp::crPlayerGameData *m_this;
		CRCore::ref_ptr<CRCore::crStreamBuf> m_stream;
		int m_netType;
	};

	//����canvasʱ������canvasλ�ƶ��������ڵ�;
	class crJXJUIShowCanvasMethod : public CRCore::crMethod
	{//Client Method
	public:
		crJXJUIShowCanvasMethod();
		crJXJUIShowCanvasMethod(const crJXJUIShowCanvasMethod& handle);
		MethodClass(JXJ, JXJUIShowCanvas)
			virtual void operator()(crHandle &handle);
		virtual void inputParam(int i, void *param);
		virtual void addParam(int i, const std::string& str);
	protected:
		CRCore::crWidgetNode *m_this;
		std::string m_canvas;
	};

	//ת����̳
	//class crJXJUIGoToForumMethod : public CRCore::crMethod
	//{//Client Method
	//public:
	//	crJXJUIGoToForumMethod();
	//	crJXJUIGoToForumMethod(const crJXJUIGoToForumMethod& handle);
	//	MethodClass(JXJ, JXJUIGoToForum)
	//		virtual void operator()(crHandle &handle);
	//	virtual void inputParam(int i, void *param);
	//	virtual void addParam(int i, const std::string& str);
	//protected:
	//	CRCore::crWidgetNode *m_this;
	//	std::string m_canvas;
	//	std::string m_txUrl;
	//	std::string m_url;
	//};

	class crJXJShowYellowUpgradeCanvasMethod :public CRCore::crMethod
	{//Client  Method
	public:
		crJXJShowYellowUpgradeCanvasMethod ();
		crJXJShowYellowUpgradeCanvasMethod (const crJXJShowYellowUpgradeCanvasMethod & handle);
		MethodClass(JXJ, JXJShowYellowUpgradeCanvas)
			virtual void inputParam(int i, void *param);
		virtual void addParam(int i, const std::string& str);
		virtual void operator()(crHandle &handle);
	protected:
		CRCore::crBrain *m_this;
		std::string m_yellowUpgrade;
	};

	//��Ѷƽ̨��ֵ
	class crJXJUITXRechargeMethod : public CRCore::crMethod
	{//Client Method
	public:
		crJXJUITXRechargeMethod();
		crJXJUITXRechargeMethod(const crJXJUITXRechargeMethod& handle);
		MethodClass(JXJ, JXJUITXRecharge)
			virtual void operator()(crHandle &handle);
		virtual void inputParam(int i, void *param);
		virtual void addParam(int i, const std::string& str);
	protected:
		CRCore::crWidgetNode *m_this;
		std::string m_index;
		//std::string m_url;
	};

	class crJXJUIGoldingotBuyUpdateNewMethod :public CRCore::crMethod
	{//Client Method
	public:
		crJXJUIGoldingotBuyUpdateNewMethod();
		crJXJUIGoldingotBuyUpdateNewMethod(const crJXJUIGoldingotBuyUpdateNewMethod& handle);
		MethodClass(JXJ, JXJUIGoldingotBuyUpdateNew)
			virtual void operator()(crHandle &handle);
		virtual void inputParam(int i, void *param);
		virtual void addParam(int i, const std::string& str);
	protected:
		CRCore::crCanvasNode *m_this;
		std::string m_goodCount[4];
		std::string m_goodPrice[4];
		std::string m_buyBtn[4];
		std::string m_switch[4];
		std::string m_discountSwitch[4];
		std::string m_buyCount[4];
	};

	class crJXJUIGoldBuyNewMethod :public CRCore::crMethod
	{//Client Method
	public:
		crJXJUIGoldBuyNewMethod();
		crJXJUIGoldBuyNewMethod(const crJXJUIGoldBuyNewMethod& handle);
		MethodClass(JXJ, JXJUIGoldBuyNew)
			virtual void operator()(crHandle &handle);
		virtual void inputParam(int i, void *param);
		virtual void addParam(int i, const std::string& str);
	protected:
		CRCore::crWidgetNode *m_this;
		std::string m_msgbox;
		std::string m_title;
		std::string m_msg;
		std::string m_ok;
		CRCore::crVector4 m_goldColor;
		int m_index;
	};
	class crJXJUIGoldBuy2NewMethod :public CRCore::crMethod
	{//Client Method
	public:
		crJXJUIGoldBuy2NewMethod();
		crJXJUIGoldBuy2NewMethod(const crJXJUIGoldBuy2NewMethod& handle);
		MethodClass(JXJ, JXJUIGoldBuy2New)
			virtual void operator()(crHandle &handle);
		virtual void inputParam(int i, void *param);
		virtual void addParam(int i, const std::string& str);
	protected:
		CRCore::crWidgetNode *m_this;
		char m_index;
	};
	class crJXJRecvGoldBuyNewMethod :public CRCore::crMethod
	{//Client & GameServer Method
	public:
		crJXJRecvGoldBuyNewMethod();
		crJXJRecvGoldBuyNewMethod(const crJXJRecvGoldBuyNewMethod& handle);
		MethodClass(JXJ, JXJRecvGoldBuyNew)
			virtual void operator()(crHandle &handle);
		virtual void inputParam(int i, void *param);
		virtual void addParam(int i, const std::string& str);
	protected:
		CRNetApp::crPlayerGameData *m_this;
		CRCore::ref_ptr<CRCore::crStreamBuf> m_stream;
		int m_netType;

	};
	class crJXJBattleRecruitCheckNewMethod :public CRCore::crMethod
	{//Client & GameServer Method ս������
	public:
		crJXJBattleRecruitCheckNewMethod();
		crJXJBattleRecruitCheckNewMethod(const crJXJBattleRecruitCheckNewMethod& handle);
		MethodClass(JXJ, JXJBattleRecruitCheckNew)
			virtual void operator()(crHandle &handle);
		virtual void inputParam(int i, void *param);
		virtual void addParam(int i, const std::string& str);
	protected:
		CRNetApp::crPlayerGameData *m_this;
		TroopsMap* m_recruitTroopsMap;
		BattleRecruitCheckResult *m_result;
		//0:��Դ����VIP0������Ҫ�������� 1:��Դ���� 2:�������㣬��Դ���㣬ֱ�ӿ۳���Դ���� 3:��Դ���㣬�۳�Ԫ������
		//-1:���ܲ��� -2�����ݲ��� -3:Ԫ������ -4:��Դ���� -6:ͭǮ���� -7:���տɹ���Դ�����㣬���ܹ��� -8:��Դ����ʧ��
	};

	//�м���������ľ�tips
	class crJXJUIMarketBuyLimitTipsMethod : public CRCore::crMethod
	{//Client Method
	public:
		crJXJUIMarketBuyLimitTipsMethod();
		crJXJUIMarketBuyLimitTipsMethod(const crJXJUIMarketBuyLimitTipsMethod& handle);
		MethodClass(JXJ, JXJUIMarketBuyLimitTips)
			virtual void operator()(crHandle &handle);
		virtual void inputParam(int i, void *param);
		virtual void addParam(int i, const std::string& str);
	protected:
		CRCore::crWidgetNode* m_this;
		std::string m_tipsCanvas;
		std::string m_tipsTextWidget;
	};

	class crJXJTXMarketTaskDisposeMethod :public CRCore::crMethod
	{//GameServer Method
	public:
		crJXJTXMarketTaskDisposeMethod();
		crJXJTXMarketTaskDisposeMethod(const crJXJTXMarketTaskDisposeMethod& handle);
		MethodClass(JXJ, JXJTXMarketTaskDispose)
			virtual void operator()(crHandle &handle);
		virtual void inputParam(int i, void *param);
		virtual void addParam(int i, const std::string& str);
	protected:
		CRNetApp::crServerBrainHandle *m_this;
		int m_count;
	};

	class crJXJUpdateTXMarketTaskMethod :public CRCore::crMethod
	{//GameServer Method
	public:
		crJXJUpdateTXMarketTaskMethod();
		crJXJUpdateTXMarketTaskMethod(const crJXJUpdateTXMarketTaskMethod& handle);
		MethodClass(JXJ, JXJUpdateTXMarketTask)
			virtual void operator()(crHandle &handle);
		virtual void inputParam(int i, void *param);
		virtual void addParam(int i, const std::string& str);
	protected:
		CRNetApp::crPlayerGameData				*m_this;
		std::string m_type;
	};

	//ͳ��
	class crJXJUIHttpRecordMethod : public CRCore::crMethod
	{//Client Method
	public:
		crJXJUIHttpRecordMethod();
		crJXJUIHttpRecordMethod(const crJXJUIHttpRecordMethod& handle);
		MethodClass(JXJ, JXJUIHttpRecord)
			virtual void operator()(crHandle &handle);
		virtual void inputParam(int i, void *param);
		virtual void addParam(int i, const std::string& str);
	protected:
		CRCore::crWidgetNode* m_this;
		std::string m_url;
		std::string m_type;
		std::string m_param;
	};

	////////////////////////////////////////////////
	//
	//crJXJCountryBattleTimesMethod
	//��ս����
	///////////////////////////////////////////////
	class crJXJCountryBattleTimesMethod :public CRCore::crMethod
	{//Client Method �ɾ͹��ڹ�ս����ʤ��
	public:
		crJXJCountryBattleTimesMethod();
		crJXJCountryBattleTimesMethod(const crJXJCountryBattleTimesMethod& handle);
		MethodClass(JXJ, JXJCountryBattleTimes)
			virtual void operator()(crHandle &handle);
		virtual void inputParam(int i, void *param);
		virtual void addParam(int i, const std::string& str);
	protected:
		crJXJAccomplish *m_this;
	};

	////////////////////////////////////////////////
	//
	//crJXJCheckCountryBattleTimesMethod
	//��ս����ʤ������
	///////////////////////////////////////////////
	class crJXJCheckCountryBattleTimesMethod :public CRCore::crMethod
	{//GameServer Method �ɾ͹��ڹ�ս����ʤ��
	public:
		crJXJCheckCountryBattleTimesMethod();
		crJXJCheckCountryBattleTimesMethod(const crJXJCheckCountryBattleTimesMethod& handle);
		MethodClass(JXJ, JXJCheckCountryBattleTimes)
			virtual void operator()(crHandle &handle);
		virtual void inputParam(int i, void *param);
		virtual void addParam(int i, const std::string& str);
	protected:
		crJXJAccomplish *m_this;
		CRNetApp::crPlayerGameData *m_player;
	};

	class crJXJUITrainningCopyCheckMethod :public CRCore::crMethod
	{//Client Method
	public:
		crJXJUITrainningCopyCheckMethod();
		crJXJUITrainningCopyCheckMethod(const crJXJUITrainningCopyCheckMethod& handle);
		MethodClass(JXJ, JXJUITrainningCopyCheck)
			virtual void operator()(crHandle &handle);
		virtual void inputParam(int i, void *param);
		virtual void addParam(int i, const std::string& str);
	protected:
		CRCore::crWidgetNode* m_this;
	};

	//����������սѵ������
	class crJXJNewGuideTrainningCopyMethod : public CRCore::crMethod
	{//GameClient Method 
	public:
		crJXJNewGuideTrainningCopyMethod();
		crJXJNewGuideTrainningCopyMethod(const crJXJNewGuideTrainningCopyMethod& handle);
		MethodClass(JXJ, JXJNewGuideTrainningCopy)
			virtual void operator()(crHandle &handle);
		virtual void inputParam(int i, void *param);
		virtual void addParam(int i, const std::string& str);
	protected:
		CRNetApp::crGameTask *m_this;
	};

	class crJXJCheckPresentSoldierMethod : public CRCore::crMethod
	{//Server Method
	public:
		crJXJCheckPresentSoldierMethod();
		crJXJCheckPresentSoldierMethod(const crJXJCheckPresentSoldierMethod& handle);
		MethodClass(JXJ, JXJCheckPresentSoldier)
			virtual void operator()(crHandle &handle);
		virtual void inputParam(int i, void *param);
		virtual void addParam(int i, const std::string& str);
	protected:
		CRNetApp::crPlayerGameData *m_this;
		int m_lastlv;
		int m_nowlv;
	};

	class crJXJRecvPresentSoldierMethod : public CRCore::crMethod
	{//Client Method
	public:
		crJXJRecvPresentSoldierMethod();
		crJXJRecvPresentSoldierMethod(const crJXJRecvPresentSoldierMethod& handle);
		MethodClass(JXJ, JXJRecvPresentSoldier)
			virtual void operator()(crHandle &handle);
		virtual void inputParam(int i, void *param);
		virtual void addParam(int i, const std::string& str);
	protected:
		CRNetApp::crPlayerGameData *m_this;
		CRCore::ref_ptr<CRCore::crStreamBuf> m_stream;
		int m_netType;
		std::string m_canvas;
		std::string m_switch;
		std::string m_title;
		std::string m_icons[4];
		std::string m_inputs[4];
	};

	class crJXJ7DhuodongCanvasUpdateMethod :public CRCore::crMethod
	{//Client  Method
	public:
		crJXJ7DhuodongCanvasUpdateMethod ();
		crJXJ7DhuodongCanvasUpdateMethod (const crJXJ7DhuodongCanvasUpdateMethod & handle);
		MethodClass(JXJ, JXJ7DhuodongCanvasUpdate)
			virtual void inputParam(int i, void *param);
		virtual void addParam(int i, const std::string& str);
		virtual void operator()(crHandle &handle);
	protected:
		CRCore::crCanvasNode *m_this;
		std::string m_canvas;
		std::string m_tag;
		std::string m_icons[5][4];
		std::string m_inputs[5][4];
		std::string m_btnget[5];
		std::string m_title[5];
		std::string m_carddesc[4];
        std::string m_planes[5][4];
        std::string m_desc[6];
	};

	class crJXJCheck7DayMethod :public CRCore::crMethod
	{//GameServer Method
	public:
		crJXJCheck7DayMethod();
		crJXJCheck7DayMethod(const crJXJCheck7DayMethod& handle);
		MethodClass(JXJ, JXJCheck7Day)
			virtual void operator()(crHandle &handle);
		virtual void inputParam(int i, void *param);
		virtual void addParam(int i, const std::string& str);
	protected:
		CRNetApp::crPlayerGameData *m_this;
	};

	class crJXJUIGet7DayAwardMethod :public CRCore::crMethod
	{//Client Method
	public:
		crJXJUIGet7DayAwardMethod();
		crJXJUIGet7DayAwardMethod(const crJXJUIGet7DayAwardMethod& handle);
		MethodClass(JXJ, JXJUIGet7DayAward)
			virtual void operator()(crHandle &handle);
		virtual void inputParam(int i, void *param);
		virtual void addParam(int i, const std::string& str);
	protected:
		CRCore::crWidgetNode *m_this;
		std::string m_tag;
		char m_index;
	};

	class crJXJRecvGet7DayAwardMethod :public CRCore::crMethod
	{//Client & GameServer Method
	public:
		crJXJRecvGet7DayAwardMethod();
		crJXJRecvGet7DayAwardMethod(const crJXJRecvGet7DayAwardMethod& handle);
		MethodClass(JXJ, JXJRecvGet7DayAward)
			virtual void operator()(crHandle &handle);
		virtual void inputParam(int i, void *param);
		virtual void addParam(int i, const std::string& str);
	protected:
		CRNetApp::crPlayerGameData *m_this;
		CRCore::ref_ptr<CRCore::crStreamBuf> m_stream;
		int m_netType;
	};

	class crCheck7DayCompleteMethod : public CRCore::crMethod
	{//Client
	public:
		crCheck7DayCompleteMethod();
		crCheck7DayCompleteMethod(const crCheck7DayCompleteMethod& handle);
		MethodClass(CRNetApp, Check7DayComplete)
			virtual void operator()(crHandle &handle);
		virtual void inputParam(int i, void *param);
		virtual void addParam(int i, const std::string& str);
	protected:
		CRCore::crCanvasNode* m_this;
		std::string m_huodongcanvas;
		std::string m_countinput;
        std::string m_countbackboard;
	};

    class crJXJUI7DayInitMethod : public CRCore::crMethod
    {//Client Method
    public:
        crJXJUI7DayInitMethod();
        crJXJUI7DayInitMethod(const crJXJUI7DayInitMethod& handle);
        MethodClass(JXJ, JXJUI7DayInit)
            virtual void operator()(crHandle &handle);
        virtual void inputParam(int i, void *param);
        virtual void addParam(int i, const std::string& str);
    protected:
        CRCore::crCanvasNode *m_this;
        std::string m_radioGroup;
    };
}
#endif

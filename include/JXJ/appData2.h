/**********************************************************************
*
*	�ļ�:	   appData2.cpp
*
*	����:	   
*
*	����:	   ���
*					
*
**********************************************************************/
#ifndef JXJ_APPDATA2_H
#define JXJ_APPDATA2_H
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
namespace CRNetApp
{
	class crRole;
}
namespace JXJ{
////ע����洰��ƽ��data
class crJXJRegisterMoveUIData : public CRCore::crUIData
{//client
public:
	crJXJRegisterMoveUIData();
	crJXJRegisterMoveUIData(const crJXJRegisterMoveUIData& data);
	DataClass(JXJ, JXJRegisterMoveUI)
	virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
protected:
	GNE::Mutex m_dataMutex;
	bool m_bMoveFlag; ///�Ƿ�ʼ�ƶ�
	bool m_bHaveRandomed;  ///�Ƿ��������Ч����
	std::string playName;  ///��ɫ����
	float m_createTimer;//��������ʱ -1��ʾ����ʱȡ��
};


typedef std::deque<std::string> ChatInputRecordDeque;
typedef std::vector< std::pair<int,int> > ShowItemIDVec;
typedef std::vector< std::pair<int,int> > ShowAchieveIDVec;
class crJXJGameChatUIData : public CRCore::crUIData
{//client
public:
	crJXJGameChatUIData();
	crJXJGameChatUIData(const crJXJGameChatUIData& data);
	DataClass(JXJ, JXJGameChatUI)
	virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	virtual void excHandle(CREPARAM msg);
protected:
	GNE::Mutex m_dataMutex;
	JXJChatMode m_chatmode;
	float m_timer_1; // country
	float m_timer_2; // group
	float m_timer_3; // team
	float m_timer_4; // privacy
	float m_timer_5; // battle
	float m_timer_fade; // ���촰�ڵ���
	ChatInputRecordDeque m_chatInputDeque;
	bool m_isToShow;
	ShowItemIDVec m_isToShowItemIDVec;
	bool m_isShowAchieve;
	ShowAchieveIDVec m_AchieveIDVec;
	float m_timerHide;
	HKL m_oldHKL;
};
class crJXJBuildingHeadCanvasData :  public CRCore::crUIData
{
public:
	crJXJBuildingHeadCanvasData();
	crJXJBuildingHeadCanvasData(const crJXJBuildingHeadCanvasData& data);
	DataClass(JXJ, JXJBuildingHeadCanvas)
	virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
protected:
	GNE::Mutex m_dataMutex;
	int m_buildingid;
	CRNetApp::crInstanceItem *m_building_item;
};
typedef std::map<CRCore::crVector2i,int> GoodsStepMap;
typedef std::vector< int >GongFangTuZhiVec;
class crJXJCheckBuildingCanvasData :  public CRCore::crUIData
{
public:
	crJXJCheckBuildingCanvasData();
	crJXJCheckBuildingCanvasData(const crJXJCheckBuildingCanvasData& data);
	DataClass(JXJ, JXJCheckBuildingCanvas)
	virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
protected:
	GNE::Mutex m_dataMutex;
	int m_buildingid;
	GoodsStepMap m_goldbuySteps;
	GoodsStepMap m_coppersaleSteps;
	CRNetApp::crInstanceItem *m_building_item;
	GongFangTuZhiVec m_tuZhiVec;
	std::vector<int> m_ResourceCanExchangeVec;
	unsigned char m_sellsourcetype;
	int m_sellsourcecount;
	unsigned char m_getsourcetype;
};

typedef std::deque< std::pair<int,std::string> >AddFriendRequestDeq;
class crJXJCheckAddFriendRequestData :  public CRCore::crUIData
{
public:
	crJXJCheckAddFriendRequestData();
	crJXJCheckAddFriendRequestData(const crJXJCheckAddFriendRequestData& data);
	DataClass(JXJ, JXJCheckAddFriendRequest)
	virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	virtual void excHandle(CREPARAM msg);
protected:
	AddFriendRequestDeq m_addFriendRequest;
	GNE::Mutex m_dataMutex;
};

class crJXJCheckAddGroupMemberRequestData :  public CRCore::crUIData
{
public:
	crJXJCheckAddGroupMemberRequestData ();
	crJXJCheckAddGroupMemberRequestData (const crJXJCheckAddGroupMemberRequestData & data);
	DataClass(JXJ, JXJCheckAddGroupMemberRequest)
	virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	virtual void excHandle(CREPARAM msg);
protected:
	AddGroupMemberRequestDeq m_addGroupMemberRequestDeq;
	GNE::Mutex m_dataMutex;
};
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
// mail data class
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
class crJXJUIMailData :  public CRCore::crUIData
{
public:
	enum MAIL_STATE{ //�ʼ�״̬
		MS_ALL = 1,		// ����
		MS_READED,		// �Ѷ�
		MS_UNRE			// δ��
	};

	crJXJUIMailData();
	crJXJUIMailData(const crJXJUIMailData& data);
	DataClass(JXJ, JXJUIMail)
	virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	void prepare_send_to(int id, std::string name);
protected:
	std::string mail_canvas;
	int send_to_id;
	std::string send_to_name;

	// paging
	int total_page;
	int page_num;
	int cur_page;

	MAIL_STATE m_state_sel;
};
class crJXJBirthPointButtonData : public CRCore::crUIData
{
public:
	crJXJBirthPointButtonData();
	crJXJBirthPointButtonData(const crJXJBirthPointButtonData& data);
	DataClass(JXJ, JXJBirthPointButton)
		virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
protected:
	GNE::Mutex m_dataMutex;
	CRCore::crVector3i m_birthPos;
};
class crJXJBigMapCityData : public CRCore::crUIData
{
public:
	crJXJBigMapCityData();
	crJXJBigMapCityData(const crJXJBigMapCityData& data);
	DataClass(JXJ, JXJBigMapCity)
		virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
protected:
	GNE::Mutex m_dataMutex;
	unsigned short m_cityIndex;
};
typedef std::vector< int >SellJiangkaVec;
class crJXJSellJiangkaCanvasData :  public CRCore::crUIData
{
public:
	crJXJSellJiangkaCanvasData();
	crJXJSellJiangkaCanvasData(const crJXJSellJiangkaCanvasData& data);
	DataClass(JXJ, JXJSellJiangkaCanvas)
		virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
protected:
	SellJiangkaVec m_jiangkaVec;
};
class crJXJUIHyperTextItemData :  public CRCore::crUIData
{
public:
	crJXJUIHyperTextItemData();
	crJXJUIHyperTextItemData(const crJXJUIHyperTextItemData& data);
	DataClass(JXJ, JXJUIHyperTextItem)
		virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
protected:
	JXJItemBagVec m_itemvec;
};
class crJXJTavernBuildingCanvasData :  public CRCore::crUIData
{
public:
	crJXJTavernBuildingCanvasData();
	crJXJTavernBuildingCanvasData(const crJXJTavernBuildingCanvasData& data);
	DataClass(JXJ, JXJTavernBuildingCanvas)
		virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
protected:
	GNE::Mutex m_dataMutex;
	int m_buildingid;
	CRNetApp::crInstanceItem *m_building_item;
	int m_firstshowtimer;
	int m_lastshowtimer;
	int m_refreshtimer;
	int m_pushtimer;
	int m_step;
	bool m_ifknowcard;
	unsigned char m_luckycardindex;
	///int m_luckycard[3];
};
class crJXJBeautyDialogueCanvasData :  public CRCore::crUIData
{
public:
	crJXJBeautyDialogueCanvasData();
	crJXJBeautyDialogueCanvasData(const crJXJBeautyDialogueCanvasData& data);
	DataClass(JXJ, JXJBeautyDialogueCanvas)
		virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	virtual void excHandle(CREPARAM msg);
protected:
	GNE::Mutex m_dataMutex;
	int m_taskid;
	int m_xumuid;
	int m_dialoguenum;
	CRCore::crWidgetNode *m_widgetnode;
	CRCore::crDataObject *m_dataObject;
};
class crJXJRenWuCanvasData :  public CRCore::crUIData
{
public:
	crJXJRenWuCanvasData();
	crJXJRenWuCanvasData(const crJXJRenWuCanvasData& data);
	DataClass(JXJ, JXJRenWuCanvas)
		virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
protected:
	GNE::Mutex m_dataMutex;
	bool m_unfolden;
	int m_newHandTaskid;
	std::string m_targetCanvasName;
	std::string m_targetWidgetName;
	std::string m_rectCanvasName;
	int m_xinshouyindaoFlag21;
	int m_ArrowsUISelect;
	int m_brainTargetCardCount;
	int m_TargetBuildingID;
	int m_newHandUpgradeCardid;
	int m_newHandTroopPositionid;
};
class crJXJCityMiniMenuData :  public CRCore::crUIData
{
public:
	crJXJCityMiniMenuData();
	crJXJCityMiniMenuData(const crJXJCityMiniMenuData& data);
	DataClass(JXJ, JXJCityMiniMenu)
		virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
protected:
	int m_chengchiid;
	GNE::Mutex m_dataMutex;
};
typedef std::vector< std::pair< CRCore::crVector4ub,float> >ChengfangInfovec;//ashili,dshili,a����,d����,ʣ��ʱ��
typedef std::vector< unsigned char > RoomStateVec;
class crJXJBattleRoomInfoData :  public CRCore::crUIData
{
public:
	crJXJBattleRoomInfoData();
	crJXJBattleRoomInfoData(const crJXJBattleRoomInfoData& data);
	DataClass(JXJ, JXJBattleRoomInfo)
		virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	virtual void excHandle(CREPARAM msg);
protected:
	GNE::Mutex m_dataMutex;
	unsigned short m_chengchiid;//�ǳ�ID
	//unsigned char m_shiliid; // �ط�����ID
	//unsigned short m_chengfang;//�Ƿ�ֵ
	//unsigned short m_shiliwin1;//����1ʤ������
	//unsigned short m_shiliwin2;//����2ʤ������
	//unsigned short m_shiliwin3;//����3ʤ������
	//unsigned char m_roomnum;//�ѿ����ķ�����
	ChengfangInfovec m_chengfanginfovec;//��������ID�������������ط�����
	RoomStateVec m_roomstatevec;//���俪��״̬
};
class crJXJUIFxData :  public CRCore::crUIData
{
public:
	crJXJUIFxData();
	crJXJUIFxData(const crJXJUIFxData& data);
	DataClass(JXJ, JXJUIFx)
	virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	virtual void excHandle(CREPARAM msg);
protected:
	float m_visiableTime;
	unsigned short m_curaccomplishid;
	GNE::Mutex m_dataMutex;
};

typedef std::vector<CRCore::crVector3i> RenWuRewardVec;
class crJXJGetRenWuRewardData :  public CRCore::crUIData
{
public:
	crJXJGetRenWuRewardData();
	crJXJGetRenWuRewardData(const crJXJGetRenWuRewardData& data);
	DataClass(JXJ, JXJGetRenWuReward)
	virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	virtual void excHandle(CREPARAM msg);
protected:
	GNE::Mutex m_dataMutex;
	int m_taskid;
	RenWuRewardVec m_renwurewardvec;
};
class crJXJUIBattlePunishData :  public CRCore::crUIData
{
public:
	crJXJUIBattlePunishData();
	crJXJUIBattlePunishData(const crJXJUIBattlePunishData& data);
	DataClass(JXJ, JXJUIBattlePunish)
		virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	virtual void excHandle(CREPARAM msg);
protected:
	GNE::Mutex m_dataMutex;
	short m_punishtime;
	int m_needgold;
};
class crJXJFubenCanvasData :  public CRCore::crUIData
{
public:
	crJXJFubenCanvasData();
	crJXJFubenCanvasData(const crJXJFubenCanvasData& data);
	DataClass(JXJ, JXJFubenCanvas)
	virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	virtual void excHandle(CREPARAM msg);
protected:
	GNE::Mutex m_dataMutex;
	int m_fubencurpage;
	int m_fubentotalpage;
	unsigned short m_selfubenid;
	std::vector<int> m_fubenidvec;
};
class crJXJJueSeCanvasData :  public CRCore::crUIData
{
public:
	crJXJJueSeCanvasData();
	crJXJJueSeCanvasData(const crJXJJueSeCanvasData& data);
	DataClass(JXJ, JXJJueSeCanvas)
	virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	virtual void excHandle(CREPARAM msg);
protected:
	GNE::Mutex m_dataMutex;
	int m_proFoodProduct;
	int m_proWoodProduct;
	int m_proIronProduct;
	int m_proHorseProduct;
	int m_proFoodProductadd;
	int m_proWoodProductadd;
	int m_proIronProductadd;
	int m_proHorseProductadd;
	//CRCore::crVector2s m_ispushhuodong;
};

typedef std::vector <std::pair<std::string,int> >  GroupLeaderInfoVec;
typedef std::vector <std::pair<std::string,int> >  GroupActiveMemberVec;

class crJXJGroupInfo : public CRCore::Referenced
{
public:
	crJXJGroupInfo():m_dismissTime(-1),m_groupid(0),m_grouplv(0),m_membercount(0),m_grouptroops(0),m_groupcontri(0),m_rank(0),m_conquest(0),m_exploit(0)
	{
		m_groupLeaderVec.clear();
	}
	void setID(int groupid) { m_groupid = groupid; }
	int getID(){ return m_groupid; }
	void setName(const std::string &groupname){m_groupname = groupname;}
	std::string &getName(){return m_groupname;}
	void setCreatorName(const std::string &bossname){m_bossname = bossname;}
	std::string &getCreatorName(){return m_bossname;}
	void setLv(unsigned char grouplv){ m_grouplv = grouplv; }
	unsigned char getLv(){ return m_grouplv; }
	void setMemberCount(unsigned short membercount){ m_membercount = membercount; }
	unsigned short getMemberCount(){ return m_membercount; }
	void setNotice(const std::string &notice){m_notice = notice;}
	std::string &getNotice(){return m_notice;}

	void setContactNotice(const std::string &notice){m_contactNotice = notice;}
	std::string &getContactNotice(){return m_contactNotice;}

	void setRecruitNotice(const std::string &notice){m_recruitNotice = notice;}
	std::string &getRecruitNotice(){return m_recruitNotice;}

	void setCreatedata(const std::string &createdata){m_createdata = createdata;}
	std::string &getCreatedata(){return m_createdata;}

	void setShiliID(unsigned char shiliid){ m_shiliid = shiliid; }
	unsigned char getShiliID(){ return m_shiliid; }

	void setGroupTroops(int grouptroops) { m_grouptroops = grouptroops; }
	int getGroupTroops(){ return m_grouptroops; }

	void setGroupContribute(int groupcontri) { m_groupcontri = groupcontri; }
	int getGroupContribute(){ return m_groupcontri; }

	void setGroupExploit(int exploit) { m_exploit = exploit; }
	int getGroupExploit() {return m_exploit; }

	void setDismissTime(int time) {m_dismissTime = time;}
	int getDismissTime() {return m_dismissTime;}

	void setConquest(unsigned char conquest){m_conquest = conquest;}
	unsigned char getConquest(){return m_conquest;}

	void setFunds(int exp) {m_funds = exp;}
	int getFunds() {return m_funds;}

	int getRank() { return m_rank;}
	void setRank(int rank) {m_rank = rank;}

	std::string getLeaderName(int idx);
	//void setLeaderName(std::string & name) {m_leaderName = name;}
	int getLeaderLevel(int idx);
	//void setLeaderLevel(int lv) {m_leaderLevel = lv;}

	void setFengYi(const std::string & fengyi) {m_fengYi = fengyi;}
	std::string & getFengYi() {return m_fengYi;}

	GroupLeaderInfoVec & getLeaderVec() {return m_groupLeaderVec;}

	ConsortiaRecordsDeq & getConsortiaRecordsDeq() {return m_consortiarecordsDeq;}

protected:
	int m_groupid;
	std::string m_groupname;
	std::string m_bossname;
	std::string m_leaderName;
	int m_leaderLevel;
	unsigned char m_grouplv;
	unsigned short m_membercount;

	std::string m_createdata;
	std::string m_notice;
	std::string m_contactNotice;		// ��ϵ����
	std::string m_recruitNotice;		// ��ļ����
	std::string m_fengYi;				// ����

	unsigned char m_shiliid;
	int m_grouptroops;			
	int m_groupcontri;
	int m_rank;					// ��������
	int m_funds;
	int m_dismissTime;		// ���Ž�ɢʱ��
	unsigned char m_conquest;	//��������ֵ
	int m_exploit;			//���ų�Ա�ܹ�ѫ

	GroupLeaderInfoVec m_groupLeaderVec;		// ���ų���
	ConsortiaRecordsDeq m_consortiarecordsDeq;		//���Ŵ�ȡ���ļ�¼
};
typedef std::vector< CRCore::ref_ptr<crJXJGroupInfo> > GroupInfoVec;

class crJXJGroupCanvasData :  public CRCore::crUIData
{
public:
	crJXJGroupCanvasData();
	crJXJGroupCanvasData(const crJXJGroupCanvasData& data);
	DataClass(JXJ, JXJGroupCanvas)
		virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	virtual void excHandle(CREPARAM msg);
protected:
	GNE::Mutex m_dataMutex;
	int m_groupcurpage;
	int m_grouptotalpage;
	int m_groupMemberListCurPage;
	int m_groupMemberListTotalPage;
	GroupInfoVec m_groupinfovec;
	MyGroupApplySet m_groupApplySet;
	int m_curselectgroupid;
};

class PermissionCheck
{
public:
	int operator () ( int groupPos,int permission)
	{
		static int group_Normal =
				JXJGroup_LookGroupRank
				| JXJGroup_LeaveGroup;
		static int group_sec = 
				JXJGroup_ChangeName
				| JXJGroup_KickMember
				| JXJGroup_Upgrade			
				| JXJGroup_LookGroupRank		
				| JXJGroup_EditNotice			
				| JXJGroup_PublishNotice		
				| JXJGroup_YuanBaoStartFB		
				| JXJGroup_ExpStartFB	
				| JXJGroup_LeaveGroup			
				//| JXJGroup_DismissGroup		
				//| JXJGroup_DismissGroupImmediate	
				//| JXJGroup_CancelDismissGroup	
				| JXJGroup_AddGroupMember		
				| JXJGroup_RejectGroupMember	
				| JXJGroup_AgreeGroupMember	
				//| JXJCountry_Vote				
				;
				
		static int group_first =
				JXJGroup_ChangeLeader 
				| JXJGroup_ChangeName
				| JXJGroup_KickMember
				| JXJGroup_Upgrade			
				| JXJGroup_LookGroupRank		
				| JXJGroup_EditNotice			
				| JXJGroup_PublishNotice		
				| JXJGroup_YuanBaoStartFB		
				| JXJGroup_ExpStartFB	
				//| JXJGroup_LeaveGroup			
				| JXJGroup_DismissGroup		
				| JXJGroup_DismissGroupImmediate	
				| JXJGroup_CancelDismissGroup	
				| JXJGroup_AddGroupMember		
				| JXJGroup_RejectGroupMember	
				| JXJGroup_AgreeGroupMember	
				| JXJGroup_ApplyStationCanton 
				| JXJCountry_Vote				
				| JXJGroup_CantonManage		;
				
		static int country_fist = 
				JXJGroup_ApplyStationCanton 
				| JXJCountry_EditNotice		
				| JXJCountry_PublicNotice		
				| JXJCountry_Build			
				| JXJCountry_Vote				
				| JXJCountry_AllocateCanton	
				| JXJCountry_Fete_Business	
				| JXJCountry_Protect			;
		static int country_sec =
				JXJGroup_ApplyStationCanton 
				| JXJCountry_EditNotice		
				| JXJCountry_PublicNotice		
				| JXJCountry_Build			
				| JXJCountry_Vote				
				| JXJCountry_Fete_Business	
				| JXJCountry_Protect			;
				
		static int country_third =
				JXJGroup_ApplyStationCanton 
				| JXJCountry_EditNotice		
				| JXJCountry_PublicNotice		
				| JXJCountry_Build			
				| JXJCountry_Vote				
				| JXJCountry_Fete_Business	
				| JXJCountry_Protect			;
				
		switch (groupPos)
		{
		case JXJGroup_Normal:
			return group_Normal & permission; 
		case JXJGroup_SecondLeader:
			return group_sec & permission;
		case JXJGroup_FirstLeader:
			return group_first & permission;
		case JXJCountryOfficial_first:
			return country_fist & permission;
		case JXJCountryOfficial_second:
			return country_sec & permission;
		case JXJCountryOfficial_third:
			return country_third & permission;
		default:
			break;
		}
		return 0;
	}
};

class MyGroupChengChi : public CRCore::Referenced
{
public:
	MyGroupChengChi()
	{
		m_isCantonGroup = false;
		m_rank = 0;
		m_level = 0;
		m_memberCount = 0;
		m_totoalActiveVal = 0;
		m_chengChiId = 0;
		m_earnings = 0;
		m_UIearnings = 0;
	}
	int m_groupId;
	bool m_isCantonGroup;
	int m_rank;
	std::string m_groupName;
	std::string m_leaderName;
	int m_level;
	int m_memberCount;
	int m_totoalActiveVal;
	int m_chengChiId;
	short m_earnings;				// ʵ��ֵ  
	short m_UIearnings;				// ��������ʾ
};

class ChengChiCompare
{
public:
	bool operator() (const CRCore::ref_ptr<MyGroupChengChi> & l,const CRCore::ref_ptr<MyGroupChengChi> & r) const
	{
		return l->m_rank > r->m_rank;
	}
};

typedef std::vector<CRCore::ref_ptr<MyGroupChengChi> > CantonGroupVec;
//typedef std::vector<CRCore::ref_ptr<MyGroupChengChi> > MyGroupChengChiSet;
//typedef std::vector <std::pair<int ,MyGroupChengChiSet > >  MyGroupChengChiVec;
typedef std::vector<int> MyApplyCantonVec;
typedef std::set<int> CantonFenFengChengChiSet;
typedef std::vector<int> MyAllocatedCantonVec;
typedef std::vector<int> ChengChiIdVec;
//typedef std::deque< int > GovPostShopItemIDDeq;
typedef std::map<int, std::string> ClientFenFengedChengChiMap;	//chengchiid ��playername ���ͻ���ʹ��

class crJXJMyGroupCanvasData :  public CRCore::crUIData
{
public:
	crJXJMyGroupCanvasData();
	crJXJMyGroupCanvasData(const crJXJMyGroupCanvasData& data);
	DataClass(JXJ, JXJMyGroupCanvas)
		virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	virtual void excHandle(CREPARAM msg);
protected:
	GNE::Mutex m_dataMutex;

	bool m_hasNewApplyer;			
	bool m_hadOpenShenHe;	
	unsigned char m_myGroupPos;
	unsigned char m_qubingBtnidx;

	int m_groupapplycurpage;
	int m_groupapplytotalpage;
	int m_playerid;
	int m_groupmembercurpage;
	int m_groupmembertotalpage;
	int m_fubenCurPage;
	int m_fubenTotalPage;
	int m_chengchiCurPage;
	int m_chengchiTotalPage;
	int m_fenFengCurPage;								// �ַ⵱ǰҳ
	int m_fenFengTotalPage;								// �ַ���ҳ��
	int m_selectedCantonId;								// �ǳ�������ѡ�еĳǳ�Id

	int m_preSelectedIdx;							// �ϴ�ѡ�еľ���id
	
	crJXJGroupInfo m_mygroupinfo;

	/*StartedFubenSet m_startedFubenSet;*/
	StartedFubenMap m_startedFubenMap;
	ConsortiaApplyVec m_groupapplyvec;
	CRCore::ref_ptr<crJXJConsortiaMember> m_myselfInfo;
	ConsortiaMemberVec m_memberVec;
	GroupActiveMemberVec m_activeMemberVec;				// ��Ծ��Աǰʮ
	CRCore::ref_ptr<crJXJConsortiaMember> m_selmember;
	ConsortiaMemberVec m_canFengfenmemberVec;			//�ɱ��ַ�ľ��ų�Ա

	CantonGroupVec m_cantonGroupMap;					// һ���ݵ�פ������
	MyAllocatedCantonVec m_allocateCantonVec;			// ���ؾ��Ų���
	MyApplyCantonVec m_myApplyCantonVec;				// ������פ������
	ChengChiIdVec m_chengChiIdVec;						// 
	HadWonGroupFuBenSet m_hadWonGroupFuBenSet ;
	TroopsMap m_cunruTroopsMap;							//׼������ı� (��ûȷ�ϣ����ͻ��˼�¼)
	TroopsMap m_groupTroopsMap;
	// ����һ�������Ѿ��ַ�ĳǳ��б�
	//CantonFenFengChengChiSet m_fenFengChengChiSet;		// �Ѿ��ַ�ĳǳ��б�
	ClientFenFengedChengChiMap m_fenFengChengChiMap;			//�Ѿ��ַ�ĳǳ�id �� playername
};
typedef std::vector< CRCore::ref_ptr<crJXJConsortiaMember> > GroupMemberInfoVec;
//typedef std::multimap<unsigned char,CRCore::ref_ptr<crJXJConsortiaMember> > GroupMemberInfoMap;//postid,
class crJXJCheckGroupCanvasData :  public CRCore::crUIData
{
public:
	crJXJCheckGroupCanvasData();
	crJXJCheckGroupCanvasData(const crJXJCheckGroupCanvasData& data);
	DataClass(JXJ, JXJCheckGroupCanvas)
		virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	virtual void excHandle(CREPARAM msg);
protected:
	GNE::Mutex m_dataMutex;
	int m_groupcurpage;
	int m_grouptotalpage;
	GroupMemberInfoVec m_groupmemberinfovec;
};

//typedef std::vector<CRCore::ref_ptr<strInfo > > VoteVec;
typedef std::vector<std::pair <int,std::string> > OfficalVec;
typedef std::map<int,bool> ZhoujunMap;

class ChengchiInfo : public CRCore::Referenced
{
public:
	int m_id;
	int m_cantonId;
	std::string m_groupName;				// פ���ľ���
	std::string m_groupLeader;				// ���ų�
};

typedef std::set<int> FenFengedCantonSet;		// ���ű��ַ����id
class CountryCanvasFenFengListItem : public ConsortiaLvRankItem 
{
public:
	CountryCanvasFenFengListItem(int id) : m_rankVal(0),ConsortiaLvRankItem(id){}
	int m_rankVal;
	FenFengedCantonSet m_fenFengedCantonSet;
};

//class CantonGuardGroup :CRCore::Referenced		// ���ؾ��� ,ҳ����ʾ
//{
//public:
//	CantonGuardGroup(int groupId,int leaderId):m_groupId(groupId),m_leaderId(leaderId){}
//	int m_cantonId;
//	int m_groupId;
//	int m_leaderId;
//	std::string m_groupName;
//	std::string m_leaderName;
//};

typedef std::vector<CRCore::ref_ptr<CountryCanvasFenFengListItem> > CountryCanvasAllocateGroupVec;
typedef std::map<int,CRCore::ref_ptr<ChengchiInfo> > ChengchiInfoMap;
//typedef std::map<int,CRCore::ref_ptr<CantonGuardGroup> > CantonGuardGroupMap;
typedef std::vector<int> PeopleIdList;
typedef std::vector<unsigned char> GovShopIDVec;
typedef std::vector<CountryHistory> UIHistoryVec;
class crJXJMyCountryCanvasData :  public CRCore::crUIData
{
public:
	crJXJMyCountryCanvasData();
	crJXJMyCountryCanvasData(const crJXJMyCountryCanvasData& data);
	DataClass(JXJ, JXJMyCountryCanvas)
	virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	virtual void excHandle(CREPARAM msg);
protected:
	GNE::Mutex m_dataMutex;

	unsigned char m_officalPos;						// ��ְ
	unsigned char m_groupPos;						// ���Ź�ְ
	unsigned char m_lastMinLv;						// �ϴβ�ѯ��С�ȼ�
	unsigned char m_lastMaxLv;						// �ϴβ�ѯ���ȼ�
	bool m_voted;									// �Ƿ��Ѿ�Ͷ��Ʊ
	bool m_statedFete;								// �Ƿ��Ѿ���������
	bool m_startedEnrich;							// �Ƿ��Ѿ���������
	bool m_isselectedCantonfenfenged;				//�ݿ�������棬ѡ�е����Ƿ��Ѿ����ַ�
	unsigned char m_feteTimes;								// �������
	unsigned char m_enrichType;						// ��������
	unsigned char m_enrichTimes;								// ��������
	int m_curFenFengPage;							// �ݿ��ַ���棬��ǰҳ
	int m_totalFenFengPage;							// �ݿ��ַ���棬��ҳ��
	int m_selectedCantonId;							// �ݿ�������棬ѡ�е���id
	int m_curPeopleListPage;						// ��ս������ǰҳ
	int m_totalPeopleListPage;						// ��ս������ҳ��
	int m_siJinTai;										// ˾��̨
	int m_shenNongMiao;									// ��ũ��
	int m_siMaJian;										//˾���
	int m_shangLinYuan;									//����Է
	int m_taiMiao;										//̫��
	int m_countryContribute;							// ���ҹ���
	int m_shopCurPage;
	int m_shopTotalPage;
	//int m_curpage;
	//int m_totalpage;
	unsigned char m_purchaseitemid;

	std::string m_notice;
	std::string m_zhenshouGroupLeader;
	std::string m_zhenshouGroupName;

	//GovPostShopItemIDDeq m_govpostitemdeq;

	ShiliCityChangeDeq m_windeq;
	ShiliCityChangeDeq m_lostdeq;
	OfficalVec m_officalVec;							// 0 ���࣬1 ��˾��2 �󽫾�
	ZhoujunMap m_zhoujunMap;			
	ChengchiInfoMap m_chengchiMap;
	CountryCanvasAllocateGroupVec m_groupVec;			// �ַ���棬�����б�
	CandidateVec m_candidateVec;						// ͶƱ��ѡ��
	PeopleVec m_peopleVec;								// С�Ž��� �������б���ʾ
	UIHistoryVec m_historyVec;							// ������ʷ
	//GovPostShopItemIDDeq m_govShop;
	SelectLeaderIdSet m_selectLeaderSet;
	unsigned char m_benzhouzhanlingcity;
	CandidateVec m_candidateVecL;						// ����ͶƱ��ѡ��
	int m_guojiazijin;								// �����ʽ�
	char m_destroycountryid1;                   //�����������Ĺ���id
	char m_destroycountryid2;					//�����������Ĺ���id
	GovShopIDVec m_govShopIDVec;
};

class crCenterNoticeCanvasData :  public CRCore::crUIData
{
public:
	crCenterNoticeCanvasData();
	crCenterNoticeCanvasData(const crCenterNoticeCanvasData& data);
	DataClass(JXJ, CenterNoticeCanvas)
		virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	virtual void excHandle(CREPARAM msg);
protected:
	GNE::Mutex m_dataMutex;
	CRCore::ref_ptr<CRCore::crStreamBuf> cfgstream;
};
class crJXJCountryInfo : public CRCore::Referenced
{
public:
	crJXJCountryInfo():m_money(0),m_citynum(0),m_shiliid(0){}
	void setMoney(int money) { m_money = money; }
	int getMoney(){ return m_money; }
	void setCityNum(unsigned char citynum){ m_citynum = citynum; }
	unsigned char getCityNum(){ return m_citynum; }
	void setShiliID(unsigned char shiliid){ m_shiliid = shiliid; }
	unsigned char getShiliID(){ return m_shiliid; }
protected:
	int m_money;
	unsigned char m_citynum;
	unsigned char m_shiliid;
};
typedef std::multimap<unsigned char,CRCore::ref_ptr<crJXJCountryInfo>,std::greater<unsigned char> >CountryCityNumRankingMap;//�ǳ�����
typedef std::multimap<int,CRCore::ref_ptr<crJXJCountryInfo>,std::greater<int> >CountryMoneyRankingMap;//�����ʽ�
typedef std::multimap<unsigned char,CRCore::ref_ptr<crJXJGroupInfo>,std::greater<unsigned char> >GrouplvRankingMap;//���ŵȼ�
typedef std::multimap<unsigned short,CRCore::ref_ptr<crJXJGroupInfo>,std::greater<unsigned short> >GroupMemberRankingMap;//��������
typedef std::multimap<int ,CRCore::ref_ptr<crJXJGroupInfo>,std::greater<int> >GroupExploitRankingMap;//�����ܹ�ѫ
typedef std::multimap<int ,CRCore::ref_ptr<crJXJGroupInfo>,std::greater<int> >GroupTroopsRankingMap;//�����ܱ���
class crJXJRankingCanvasData :  public CRCore::crUIData
{
public:
	crJXJRankingCanvasData();
	crJXJRankingCanvasData(const crJXJRankingCanvasData& data);
	DataClass(JXJ, JXJRankingCanvas)
		virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	virtual void excHandle(CREPARAM msg);
protected:
	GNE::Mutex m_dataMutex;
	int m_curpagenum;
	int m_totalpagenum;
	unsigned short m_myranking;
	LevelRankingMap m_lvrankingmap;
	GovpostRankingMap m_govpostRankingMap;
	ExpRankingMap m_expRankingMap;
	TroopsRankingMap m_troopsRankingMap;
	AccomplishRankingMap m_accomplishRankingMap;
	CountrycontributeRankingMap m_countrycontributeRankingMap;
	ManorlvRankingMap m_manorlvrankingMap;
	CountryCityNumRankingMap m_countryCityNumRankingMap;
	CountryMoneyRankingMap m_countryMoneyRankingMap;
	GrouplvRankingMap m_GrouplvRankingMap;
	GroupMemberRankingMap m_GroupMemberRankingMap;
	GroupExploitRankingMap m_GroupExploitRankingMap;
	GroupTroopsRankingMap m_GroupTroopsRankingMap;
};
typedef std::deque< int > ShopCardIDDeq;
class crJXJCardShopCanvasData :  public CRCore::crUIData
{
public:
	crJXJCardShopCanvasData();
	crJXJCardShopCanvasData(const crJXJCardShopCanvasData& data);
	DataClass(JXJ, JXJCardShopCanvas)
		virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	virtual void excHandle(CREPARAM msg);
protected:
	GNE::Mutex m_dataMutex;
	int m_curpage;
	int m_totalpage;
	int m_puechasecardid;
	ShopCardIDDeq m_cardiddeq;
};
class crJXJProgressCanvasData :  public CRCore::crUIData
{
public:
	crJXJProgressCanvasData();
	crJXJProgressCanvasData(const crJXJProgressCanvasData& data);
	DataClass(JXJ, JXJProgressCanvas)
	virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	virtual void excHandle(CREPARAM msg);
protected:
	GNE::Mutex m_dataMutex;
	int m_totalcount;
	int m_progressAboutUseItemId;
};
class crJXJTouchItemCanvasData :  public CRCore::crUIData
{
public:
	crJXJTouchItemCanvasData();
	crJXJTouchItemCanvasData(const crJXJTouchItemCanvasData& data);
	DataClass(JXJ, JXJTouchItemCanvas)
	virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	virtual void excHandle(CREPARAM msg);
protected:
	GNE::Mutex m_dataMutex;
	float m_interval;
	CRCore::ref_ptr<CRNetApp::crInstanceItem> m_item;
};
class crJXJGovPostShopCanvasData :  public CRCore::crUIData
{
public:
	crJXJGovPostShopCanvasData();
	crJXJGovPostShopCanvasData(const crJXJGovPostShopCanvasData& data);
	DataClass(JXJ, JXJGovPostShopCanvas)
		virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	virtual void excHandle(CREPARAM msg);
protected:
	GNE::Mutex m_dataMutex;
	int m_curpage;
	int m_totalpage;
	unsigned char m_purchaseitemid;
	//GovPostShopItemIDDeq m_govpostitemdeq;
};
typedef std::vector< CRCore::ref_ptr<crBagItemData> > GongFangMaterialVec;
class crJXJGongFangCanvasData :  public CRCore::crUIData
{
public:
	crJXJGongFangCanvasData();
	crJXJGongFangCanvasData(const crJXJGongFangCanvasData& data);
	DataClass(JXJ, JXJGongFangCanvas)
		virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	virtual void excHandle(CREPARAM msg);
protected:
	GNE::Mutex m_dataMutex;
	int m_curpage;
	int m_totalpage;
	int m_buildingid;
	int m_maxmaterialcount;
	int m_costtype;
	int m_itemindex;
	int m_RefineEquipSelectIndex;
	int m_RefineEquipSuitIndex;
	int m_AttachEquipSelectIndex;
	int m_AttachMateSelectIndex;
	int m_refinetype;
	int m_curpage2;
	int m_totalpage2;
	crBagItemData m_bagitemdata;
	crBagItemData m_RefineEquipBagitemdata;
	crBagItemData m_AttachEquipBagitemdata;
	crBagItemData m_AttachMateBagitemdata;
	CRNetApp::crInstanceItem *m_building_item;
	GongFangTuZhiVec m_tuZhiVec;
	//JXJItemBagVec m_tempbagvec;
	int m_equipCurpage;
	int m_equipTotalpage;
	int m_newequipmagic;
	GongFangMaterialVec m_gongfangmaterialvec;
	int m_gongfangmaterialindex;
	unsigned short m_CurSelForgeTroopsEquipID;
	int m_CurSelForgeLordEquipID;
	int m_RefineNeedGold;
	char m_openway;//0:������ع�����1��ͨ��ʹ�þ���ʯ��2��ͨ��ʹ��������ʯ
};
class crJXJAppointCanvasData :  public CRCore::crUIData
{
public:
	crJXJAppointCanvasData();
	crJXJAppointCanvasData(const crJXJAppointCanvasData& data);
	DataClass(JXJ, JXJAppointCanvas)
		virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	virtual void excHandle(CREPARAM msg);
protected:
	GNE::Mutex m_dataMutex;
	int m_curAppointJiangkaBagPageNum;//ί�ν���������ǰҳ
	int m_totalAppointJiangkaBagPageNum;//ί�ν���������ҳ��
	int m_curselectappointcardid;//��ǰѡ���ί�ν���id
	int m_curselectundoappointcardid;//��ǰѡ���ί�ν���id
};
typedef std::vector< int > VIPAffairsVec;
class crJXJArmyAdviserCanvasData :  public CRCore::crUIData
{
public:
	crJXJArmyAdviserCanvasData();
	crJXJArmyAdviserCanvasData(const crJXJArmyAdviserCanvasData& data);
	DataClass(JXJ, JXJArmyAdviserCanvas)
		virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	virtual void excHandle(CREPARAM msg);
protected:
	GNE::Mutex m_dataMutex;
	VIPAffairsVec m_vipaffairsvec;
	int m_curpagenum;
	int m_totalpagenum;
};
typedef std::map<std::string,int>SceneServerPlayerCountMap;//
typedef std::vector<int>RemainPlayerVec;//
typedef std::vector<int>RemainPlayerIDVec;//
typedef std::map<unsigned char,RemainPlayerIDVec>RemainPlayerMap;//
typedef std::map<int,unsigned char> PlayerLvMap;//playerid.lv
class crJXJOperationCanvasData :  public CRCore::crUIData
{
public:
	//typedef std::vector<std::pair<int,int> > ServerVec; // ��������nettype
	//typedef std::vector< ServerVec > ServerGroupVec;
	typedef std::map<std::string,double> ServerHeartMap;//servername,time
	typedef std::vector<ServerHeartMap> ServerGroupVec;
	crJXJOperationCanvasData();
	crJXJOperationCanvasData(const crJXJOperationCanvasData& data);
	DataClass(JXJ, JXJOperationCanvas)
		virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	virtual void excHandle(CREPARAM msg);
protected:
	GNE::Mutex m_dataMutex;
	SceneServerPlayerCountMap m_SceneSeverOnlineMap;//ս������������
	int m_OnlineCount;//��Ϸ��������
	RemainPlayerVec m_remainplayervec;
	RemainPlayerMap m_remainplayermap;
	RemainPlayerVec m_totalplayervec;
	RemainPlayerMap m_totalplayermap;
	RemainPlayerVec m_createplayervec;
	RemainPlayerMap m_createplayermap;
	PlayerLvMap m_playerlvmapWei;
	PlayerLvMap m_playerlvmapShu;
	PlayerLvMap m_playerlvmapWu;

	time_t m_interval;
	bool m_init;
	//ServerGroupVec m_serverGroupVec;
	ServerHeartMap m_serverHeartMap;
	time_t m_monitorTimer;

	int m_netType;
};

typedef std::vector< int > ShowTechVec;
class crJXJTechCanvasData :  public CRCore::crUIData
{
public:
	crJXJTechCanvasData();
	crJXJTechCanvasData(const crJXJTechCanvasData& data);
	DataClass(JXJ, JXJTechCanvas)
		virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	virtual void excHandle(CREPARAM msg);
protected:
	GNE::Mutex m_dataMutex;
	int m_TechCanvasCurPage;//�Ƽ���ǰҳ
	int m_TechCanvasTotalPage;//�Ƽ���ҳ��
	int m_ClearTechCDNeedGold;//��Ƽ�CD����Ԫ��
	int m_ClearTechCDID;//��Ƽ�CDID
	ShowTechVec m_showtechvec;
};

class crJXJJunTuanFuBenSettleCanvasData :  public CRCore::crUIData
{
public:
	crJXJJunTuanFuBenSettleCanvasData ();
	crJXJJunTuanFuBenSettleCanvasData (const crJXJJunTuanFuBenSettleCanvasData & data);
	DataClass(JXJ, JXJJunTuanFuBenSettleCanvas)
		virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	virtual void excHandle(CREPARAM msg);
protected:
	GNE::Mutex m_dataMutex;
	int m_fubenId;
	unsigned char m_times;
	unsigned char m_totalTimes;
	unsigned char m_loseTime;
	int m_activeVal;
	int m_exp;
	int m_achivement;
	int m_exploit;
	int m_groupExp;
	int m_countryContribute;
	int m_groupContribute;
	float m_juntuanfubencircle;
};
class crJXJOrangeCanvasData :  public CRCore::crUIData
{
public:
	crJXJOrangeCanvasData();
	crJXJOrangeCanvasData(const crJXJOrangeCanvasData& data);
	DataClass(JXJ, JXJOrangeCanvas)
		virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
protected:
	GNE::Mutex m_dataMutex;
	int m_recvupgradeflag;
};

class crJXJFPSAndPingData :  public CRCore::crUIData
{
public:
	crJXJFPSAndPingData();
	crJXJFPSAndPingData(const crJXJFPSAndPingData& data);
	DataClass(JXJ, JXJFPSAndPing)
		virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	void excHandle(CREPARAM msg);

protected:
	GNE::Mutex m_dataMutex;
	float m_ping;
};

typedef std::vector<int> HuodongVec;
class crHuodongCanvasData :  public CRCore::crUIData
{
public:
	crHuodongCanvasData ();
	crHuodongCanvasData (const crHuodongCanvasData & data);
	DataClass(JXJ, HuodongCanvas)
		virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	void excHandle(CREPARAM msg);

protected:
	GNE::Mutex m_dataMutex;
	HuodongVec m_huodongVec;
	unsigned short m_selectId;
	unsigned int m_version;
	unsigned int m_newVersion;
	unsigned short m_idx;
	int m_selectleijihuodongid;
	unsigned short m_isFestivalHuodongExist;//�Ƿ���ڽ��ջ
};
class crScenarioTalkCanvasData :  public CRCore::crUIData
{
public:
	crScenarioTalkCanvasData ();
	crScenarioTalkCanvasData (const crScenarioTalkCanvasData & data);
	DataClass(JXJ, ScenarioTalkCanvas)
		virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	void excHandle(CREPARAM msg);

protected:
	GNE::Mutex m_dataMutex;
	std::vector<int> m_ScenarioTalkIDVec;//�����Ի�ID����
	int m_ScenarioTalkStep;//�Ի����е���һ��
	std::string m_ScenarioTalkHyperText;//�����Ի����ı�
	std::string m_ScenarioTalkImage;//�����Ի�ͼƬ��
	int m_ScenarioTalkEndmsg;//�����Ի�������Ϣ
	std::string m_ScenarioTalkNametext;//�����Ի���������
	float m_ScenarioTalkAutoClose;//�����Ի��Զ��ر�ʱ����0Ϊ���Զ��رգ�
	float m_ScenarioTalkCloseTime;//�����Ի��Զ��ر�ʱ��
};
class crNewFunctionOpenCanvasData : public CRCore::crUIData
{
public:
	crNewFunctionOpenCanvasData();
	crNewFunctionOpenCanvasData(const crNewFunctionOpenCanvasData & data);
	DataClass(JXJ, NewFunctionOpenCanvas)
		virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	void excHandle(CREPARAM msg);

protected:
	GNE::Mutex m_dataMutex;
	int m_NewFunctionID;//���ܿ�����ʾID
	float m_visiabletime;//��ʾʱ��
	float m_troopsid;//����ID
};

typedef std::vector<unsigned short> HuoyueduRewardVec;
typedef std::vector<int> HuoyueduRewardItemVec;
class crXiaoguanjiaCanvasData : public CRCore::crUIData
{
public:
	crXiaoguanjiaCanvasData();
	crXiaoguanjiaCanvasData(const crXiaoguanjiaCanvasData & data);
	DataClass(JXJ, XiaoguanjiaCanvas)
		virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	void excHandle(CREPARAM msg);

protected:
	GNE::Mutex m_dataMutex;
	unsigned short m_HuoyueduRewardID;//��Ծ�Ƚ���ID
	HuoyueduRewardVec m_huoyueduvec;
	HuoyueduRewardItemVec m_huoyueduitemvec;
	HuoyueduRewardItemVec m_huoyueduitemcountvec;
};

typedef std::map<std::string,std::set<unsigned short>> HuiKuiHuoDongMap;
class crChongZhiHuiKuiCanvasData :  public CRCore::crUIData
{
public:
	crChongZhiHuiKuiCanvasData ();
	crChongZhiHuiKuiCanvasData (const crChongZhiHuiKuiCanvasData & data);
	DataClass(JXJ, ChongZhiHuiKuiCanvas)
		virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	void excHandle(CREPARAM msg);

protected:
	GNE::Mutex m_dataMutex;
	HuiKuiHuoDongMap m_huikuihuodongmap;
	unsigned short m_serveropenday;
	unsigned short m_idx;
};

class crJXJJuntuanHuoDongUIData : public CRCore::crUIData
{//client
public:
	crJXJJuntuanHuoDongUIData();
	crJXJJuntuanHuoDongUIData(const crJXJJuntuanHuoDongUIData& data);
	DataClass(JXJ, JXJJuntuanHuoDongUI)
	virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	void excHandle(CREPARAM msg);
protected:
	GNE::Mutex m_dataMutex;
	int m_timer;
	std::vector<std::string> m_ConsortiaNameVec;
	std::vector<std::string> m_ConsortiaLeaderNameVec;
};

class crJXJDelayHideCanvasUIData : public CRCore::crUIData
{//client
public:
	crJXJDelayHideCanvasUIData();
	crJXJDelayHideCanvasUIData(const crJXJDelayHideCanvasUIData& data);
	DataClass(JXJ, JXJDelayHideCanvasUI)
	virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	void excHandle(CREPARAM msg);
protected:
	GNE::Mutex m_dataMutex;
	int m_timer;
};
class crJXJTimerCanvasData :  public CRCore::crUIData
{
public:
	crJXJTimerCanvasData();
	crJXJTimerCanvasData(const crJXJTimerCanvasData& data);
	DataClass(JXJ, JXJTimerCanvas)
	virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	virtual void excHandle(CREPARAM msg);
protected:
	GNE::Mutex m_dataMutex;
	short m_timer;
};
}; 
#endif
/**********************************************************************
*
*	�ļ�:	   appData.h
*
*	����:	   
*
*	����:	   ��ƻ�
*					
*
**********************************************************************/

#ifndef JXJ_APPDATA_H
#define JXJ_APPDATA_H
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
#include <JXJ/appDataParam.h>
#include <JXJ/appGameData.h>
#include <CRUI/crWidgetExtend.h>
#include <bitset>
namespace CRNetApp
{
	class crRole;
}
namespace JXJ{
/////////BattleID = unsigned char,unsigned char,unsigned short(������id,������id,�ǳ�id)
class crJXJChengfangInfo : public CRCore::Referenced
{
public:
	crJXJChengfangInfo():m_qun(0)
	{
	}
	unsigned char getChengzhuShili();
	unsigned short getChengzhuChengfang();
	unsigned char changeShiliChengfang(unsigned char winshili,unsigned char lostshili);//����ֵ�ǳ�������id
	void setQunChengfeng(unsigned short chengfang){ m_qun = chengfang; }
	unsigned short getQunChengfang() { return m_qun; }
	typedef std::multimap< unsigned short,unsigned char,std::greater<unsigned short> > ShiliChengfangMap;//�Ƿ�ֵ,����id
	ShiliChengfangMap getShiliChengfangMap(){ return m_shilichengfangmap; }
	void reset(unsigned char shili, unsigned short chengfang);
	void buildStream(CRCore::ref_ptr<CRCore::crStreamBuf> &stream);
	void setStream(CRCore::crStreamBuf *stream);
protected:
	GNE::Mutex m_shilichengfangmapMutex;
	ShiliChengfangMap m_shilichengfangmap;
	unsigned short m_qun;//Ⱥ�ĳǷ�
};
//typedef std::map<unsigned short, std::pair<unsigned char,unsigned short> >ChengchiMap;//�ǳ�id������id,�Ƿ�ֵ
typedef std::map<unsigned short, CRCore::ref_ptr<crJXJChengfangInfo> >ChengchiMap;//�ǳ�id������id,�Ƿ�ֵ
typedef std::deque<int> BattleDeque;
typedef std::map<_crInt32, BattleDeque> DefendDequeMap;//unsigned char,unsigned char,unsigned short(0,������id,�ǳ�id)
typedef std::map<_crInt32, BattleDeque> AttackDequeMap;//unsigned char,unsigned char,unsigned short(������id,������id,�ǳ�id)
typedef std::list<int> BattlePlayer;
typedef std::pair<BattlePlayer,BattlePlayer> BattlePlayerPair;//�������ط�
typedef std::multimap<_crInt32,std::pair<BattlePlayerPair,std::pair<int,float> >,std::less<int> > OpenBattleMap;//�Ѿ�������ս��,unsigned char,unsigned char,unsigned short(������id,������id,�ǳ�id),roomid,ս������ʱ
typedef std::map< unsigned char,std::pair<short,int> > ShiliScoreMap;//����ID��������ɱ������
typedef std::map<unsigned short, ShiliScoreMap> BattleScoreMap;//ս������ͳ��,�ǳ�id
typedef std::deque<_crInt64> CreateBattleDeque;
typedef std::map<int,std::pair<_crInt32,float> > BattleDropPlayerMap;//playerid,battleid,����ʱ,����ս�����ߺ���ǰ�˳�ս������ҵĳͷ���ʱ
typedef std::map< unsigned short, unsigned char >TroopsTechMap;//����id�������ȼ�
typedef std::map< int, float >TechDevelopMap;//�Ƽ�id���Ƽ�����ʱ
typedef std::map<unsigned short,CRCore::ref_ptr<crJXJNewGuide>> JXJNewGuideMap;//����id��crJXJNewGuide
typedef std::set<_crInt64> ClosedBattleSet;//battlerid,roomid
typedef std::set<unsigned short> NewFunctionOpenSet;//id(�¹��ܿ�����ʾ)
typedef std::map<unsigned short, bool>CouldGetAwardMap;//����ȡ����������ID�� �Ƿ����ȡ��;
typedef std::map< unsigned short, unsigned char >CardExtraTechMap;//���ID������ȼ�

template <class T,class C = std::greater<int>,class K = int >
class crJXJRankContainer 
{
public:

	typedef std::multiset<T,C>  RankSet;
	typedef std::multimap<K,T> RankMap;

	crJXJRankContainer():m_limitNum(100)
	{
		m_rankSet.clear();
		m_rankMap.clear();
	}
	void resize(unsigned int num)
	{
		m_limitNum = num;
		adjustSize();
	}
	int size () {return m_rankMap.size();}
	bool empty() {return m_rankMap.empty();}
	void updateRank(K key,T val)
	{
		RankMap::iterator it = m_rankMap.find(key);
		if (it != m_rankMap.end())
		{
			//C compare;
			//if ( !compare(it->second,val) )
			//{
				RankSet::iterator setItr = m_rankSet.begin();
				for (; setItr != m_rankSet.end(); ++ setItr)
				{
					if ( (*setItr )->getKey() == key )
					{
						m_rankSet.erase(setItr);
						m_rankSet.insert(val);
						it->second = val;
						break;
					}
				}
			//}
		}
		else
		{
			m_rankMap.insert(RankMap::value_type(key,val));
			m_rankSet.insert(val);
			adjustSize();
		}
	}
	void delRank(K key)
	{
		RankMap::iterator it = m_rankMap.find(key);
		if (it != m_rankMap.end())
		{
			RankSet::iterator setItr = m_rankSet.begin();
			for (; setItr != m_rankSet.end(); ++ setItr)
			{
				if ( (*setItr )->getKey() == key )
				{
					m_rankSet.erase(setItr);
					m_rankMap.erase(it);
					break;
				}
			}
		}
	}

	void adjustSize()
	{
		RankMap::reverse_iterator rItr ;
		if (m_rankMap.size() > m_limitNum)
		{
			rItr = m_rankMap.rbegin();
			for (; rItr != m_rankMap.rend() && m_rankMap.size() > m_limitNum;)
			{
				m_rankMap.erase( (++rItr).base() );
				rItr = m_rankMap.rbegin();
			}

			RankSet::reverse_iterator rItr2;
			if (m_rankSet.size() > m_limitNum)
			{
				rItr2 = m_rankSet.rbegin();
				for (; rItr2 != m_rankSet.rend() && m_rankSet.size() > m_limitNum;)
				{
					m_rankSet.erase( (++rItr2).base() );
					rItr2 = m_rankSet.rbegin();
				}
			}
		}
	}
	void clear()
	{
		m_rankSet.clear();
		m_rankMap.clear();
	}
	RankSet & getRankSet() {return m_rankSet;}
	RankMap & getRankMap() {return m_rankMap;}
	unsigned int getRankNum(K key)
	{
		unsigned int ret = 0;
		RankSet::iterator itr = m_rankSet.begin();
		for (; itr != m_rankSet.end(); ++ itr)
		{
			++ ret;
			if ((*itr)->getKey() == key)
				break;
		}
		if (!ret) ret = m_limitNum + 1;
		return ret;
	}

private:
	unsigned int m_limitNum;
	RankSet m_rankSet;
	RankMap m_rankMap;
};

//_crInt32 BattleID = unsigned char,unsigned char,unsigned short(������id,������id,�ǳ�id)
///
//struct MailInfo
//{
//	int sender_id;
//	int receiver_id;
//	std::string sender_name;
//	std::string receiver_name;
//	std::string title;
//	std::string content;
//};
//struct MailQuery
//{
//	unsigned char state;
//	int querier_id;
//	int start_pos;
//	int query_count;
//};
//������ʽ�������
typedef std::map<int,int> TroopsMap;//abstractid,count
typedef std::map<unsigned short,int> TroopsEquipMap;//equipid,count
//typedef std::map<int,int> LordEquipMap;//equipid,count
//typedef std::map<int,int> JXJItemMap;//itemid,count//ͼֽ�����ϡ�������
class crMailQuery : public CRCore::Referenced
{
public:
	crMailQuery():m_state(0),m_querier_id(0),m_start_pos(0),m_query_count(0),m_id(0){}
	void setState(unsigned char state){ m_state = state; }
	unsigned char getState() { return m_state; }
	void setQueryID(int querier_id){ m_querier_id = querier_id; }
	int getQueryID() { return m_querier_id; }
	void setStartPos(int start_pos){ m_start_pos = start_pos; }
	int getStartPos() { return m_start_pos; }
	void setQuerycount(int query_count){ m_query_count = query_count; }
	int getQuerycount() { return m_query_count; }
	void setID(int id){ m_id = id; }
	int getID() { return m_id; }
protected:
	unsigned char m_state;
	int m_querier_id;
	int m_start_pos;
	int m_query_count;
	int m_id;
};
typedef std::deque< CRCore::ref_ptr<crMailQuery> > MailQueryDeque;
class crMailInfo : public CRCore::Referenced
{
public:
	crMailInfo():m_state(0),m_senderid(0),m_recvid(0),m_dbID(0){}
	void setState(unsigned char state){ m_state = state; }
	unsigned char getState() { return m_state; }
	void setSenderName(const std::string &name) { m_sendername = name; }
	std::string &getSenderName() { return m_sendername; }
	void setRecvName(const std::string &name) { m_recvname = name; }
	std::string &getRecvName() { return m_recvname; }
	void setTitle(const std::string &title) { m_title = title; }
	std::string &getTitle() { return m_title; }
	void setCreateData(const std::string &data) { m_createdata = data; }
	std::string &getCreateData() { return m_createdata; }
	void setBody(CRCore::ref_ptr<CRCore::crStreamBuf> body) { m_body = body; }
	CRCore::ref_ptr<CRCore::crStreamBuf> &getBody() { return m_body; }
	//void setText(const std::string &text) { m_text = text; }
	//std::string &getText() { return m_text; }
	void setSenderID(int senderid){ m_senderid = senderid; }
	int getSenderID() { return m_senderid; }
	void setRecvID(int recvid){ m_recvid = recvid; }
	int getRecvID() { return m_recvid; }
	void setID(int id){ m_dbID = id; }
	int getID() { return m_dbID; }
protected:
	unsigned char m_state;
	std::string m_sendername;
	std::string m_recvname;
	std::string m_title;
	std::string m_createdata;
	CRCore::ref_ptr<CRCore::crStreamBuf> m_body;
	//std::string m_text;
	int m_senderid;
	int m_recvid;
	int m_dbID;
};
typedef std::vector< CRCore::ref_ptr<crMailInfo> > MailInfoVec;
typedef std::deque< CRCore::ref_ptr<crMailInfo> > MailTaskDeque;
typedef std::vector< CRCore::ref_ptr<crMailInfo> > JXJRecvMailVec;
class crAppointCardData : public CRCore::Referenced
{
public:
	crAppointCardData():m_itemid(0),m_validtime(0){}
	void setItemID(int itemid){ m_itemid = itemid; }
	int getItemID() { return m_itemid; }
	void setValidTime(float validtime){m_validtime = validtime;}
	float getValidTime(){return m_validtime;}
protected:
	int m_itemid;
	float m_validtime;
};
#define EquipMagicSize 4
class crBagItemData : public CRCore::Referenced
{
public:
	crBagItemData():m_itemid(0),m_count(0),m_flg(0),m_equipmagic(0){}
	void setItemID(int itemid){ m_itemid = itemid; }
	int getItemID() { return m_itemid; }
	void setItemCount(unsigned char count){ m_count = count; }
	unsigned char getItemCount() { return m_count; }
	//void setJiangkaData(unsigned char jiangkadata){ m_jiangkadata = jiangkadata; }
	//unsigned char getJiangkaData() { return m_jiangkadata; }
	void setFlg(bool flg){ m_flg = flg; }
	bool getFlg() { return m_flg; }
	void setRefidID(unsigned char ref0,unsigned char ref1,unsigned char ref2)
	{
		_crInt16 hi16 = HIINT32(m_equipmagic);
		m_equipmagic = MAKEINT32(MAKEINT16(ref0,ref1),MAKEINT16(ref2,HIINT16(hi16)));
	}
	void setInlayID(unsigned char inlayid)
	{
		_crInt16 lo16 = LOINT32(m_equipmagic);
		_crInt16 hi16 = HIINT32(m_equipmagic);
		m_equipmagic = MAKEINT32(lo16,MAKEINT16(LOINT16(hi16),inlayid));
	}
	unsigned char getInlayID() { return HIINT16(HIINT32(m_equipmagic)); }
	void setEquipMagic(_crInt32 equipmagic){ m_equipmagic = equipmagic; }
	_crInt32 getEquipMagic(){ return m_equipmagic; }
	///////////��ʱ����
	void setItemDeductCount(int deductcount){ m_deductcount = deductcount; }
	int getItemDeductCount() { return m_deductcount; }
	
protected:
	int m_itemid;
	unsigned char m_count;
	//unsigned char m_jiangkadata;
	unsigned char m_flg;//0, 1:������
	_crInt32 m_equipmagic;//װ����(refid0,refid1,refid2,inlayid)
	int m_deductcount;//��ʱ����
	
};
class crStoreBagItemData:public crBagItemData
{
public:
	crStoreBagItemData():m_serverid(0){}
	//void setItemGameID(int gameid){m_gameid = gameid;}
	//int getItemGameID(){return m_gameid;}
	void setItemServerID(int serverid){m_serverid = serverid;}
	int getItemServerID(){return m_serverid;}
	void setItemHasCycle(char bcycle){m_isCycle = bcycle;}
	char getItemHasCycle(){return m_isCycle;}
private:
	//int m_gameid;
	int m_serverid;
	char m_isCycle;//0,1
};

typedef std::map< int,CRCore::ref_ptr<CRCore::crDataObject> > ItemObjectMap;//itemid,dataobject
typedef std::vector< CRCore::ref_ptr<crBagItemData> > JXJItemBagVec;//itemid,count//ͼֽ�����ϡ�װ����
typedef std::vector< CRCore::ref_ptr<crStoreBagItemData> > JXJStoreItemBagVec;//itemid,count//ͼֽ�����ϡ�װ����
typedef std::vector< CRCore::ref_ptr<crAppointCardData> > JXJAppointCardVec;//itemid,time//ί�ν����б�
typedef std::vector< int > JXJItemBagVec2;//itemid//װ����������
typedef std::vector< std::pair<int,_crInt32> > JXJLordEquipVec;//itemid,equipmagic��������װ��
//typedef std::map< unsigned char,unsigned char > JXJLordSuitMap;//��װid����װ����
class crSaleItemData : public CRCore::Referenced
{
public:
	crSaleItemData():m_itemid(0),m_count(0),m_time(0),m_equipmagic(0){}
	void setItemID(int itemid){ m_itemid = itemid; }
	int getItemID() { return m_itemid; }
	void setEquipMagic(_crInt32 equipmagic){ m_equipmagic = equipmagic; }
	_crInt32 getEquipMagic() { return m_equipmagic; }
	void setItemCount(unsigned char count){ m_count = count; }
	unsigned char getItemCount() { return m_count; }
	void setTime(unsigned short time){ m_time = time; }
	unsigned short getTime() { return m_time; }
protected:
	int m_itemid;
	_crInt32 m_equipmagic;//
	unsigned char m_count;
	unsigned short m_time;
};
typedef std::list< CRCore::ref_ptr<crSaleItemData> >JXJSaleItemList;
class crFormationInfo : public CRCore::Referenced
{
public:
	crFormationInfo():m_roleid(0),m_abstractid(0),m_count(0){}
	void setRoleID(int roleid){ m_roleid = roleid; }
	int getRoleID(){ return m_roleid; }
	void setAbstractID(int abstractid){ m_abstractid = abstractid; }
	int getAbstractID() { return m_abstractid; }
	void setCount(unsigned short count) { m_count = count; }
	unsigned short getCount() { return m_count; }
	void setEquips(const CRCore::crVector2i &equips) { m_equips = equips; }
	CRCore::crVector2i &getEquips() { return m_equips; }
protected:
	int m_roleid;
	int m_abstractid;
	unsigned short m_count;
	CRCore::crVector2i m_equips;//����itemid
};
typedef std::vector< CRCore::ref_ptr<crFormationInfo> >FormationInfoVec;
typedef std::vector< std::pair<std::string, FormationInfoVec> >SavedFormationInfoVec;//name��formationvec
class crTeamInfo : public CRCore::Referenced
{
public:
	crTeamInfo():m_leaderid(0),m_leaderlv(0),m_count(0){}
	void setLeaderID(int playerid){ m_leaderid = playerid; }
	int getLeaderID() { return m_leaderid; }
	void setLeaderName(const std::string &name) { m_leaderName = name; }
	std::string &getLeaderName() { return m_leaderName; }
	void setLeaderLevel(unsigned char lv){ m_leaderlv = lv; }
	unsigned char getLeaderLevel() { return m_leaderlv; }
	void setCount(char count) { m_count = count; }
	char getCount() { return m_count; }
protected:
	int m_leaderid;//�ӳ�ID
	std::string m_leaderName;
	unsigned char m_leaderlv;
	char m_count;//��Ա����
};
typedef std::vector< CRCore::ref_ptr<crTeamInfo> >TeamVec;
class crTeamMember : public CRCore::Referenced
{
public:
	crTeamMember():m_playerid(0),m_level(0),m_isready(false){}
	void setIconID(unsigned char iconid){ m_iconid = iconid; }
	unsigned char getIconID() { return m_iconid; }
	void setPlayerID(int playerid){ m_playerid = playerid; }
	int getPlayerID() { return m_playerid; }
	void setName(const std::string &name) { m_name = name; }
	std::string &getName() { return m_name; }
	void setLevel(unsigned char lv){ m_level = lv; }
	unsigned char getLevel() { return m_level; }
	void setReady(bool bReady) {m_isready = bReady;}
	bool isReady(){return m_isready;}
protected:
	int m_playerid;
	std::string m_name;
	unsigned char m_level;
	unsigned char m_iconid;
	bool m_isready;
};
typedef std::list< CRCore::ref_ptr<crTeamMember> >TeamMemberVec;
class crFriend : public CRCore::Referenced
{
public:
	crFriend():m_playerid(0),m_level(0),m_ifonline(false){}
	crFriend(crFriend *fnd)
	{
		m_playerid = fnd->m_playerid;
		m_name = fnd->m_name;
		m_level = fnd->m_level;
		m_iconid = fnd->m_iconid;
		m_ifonline = fnd->m_ifonline;
	}
	void setIconID(unsigned char iconid){ m_iconid = iconid; }
	unsigned char getIconID() { return m_iconid; }
	void setPlayerID(int playerid){ m_playerid = playerid; }
	int getPlayerID() { return m_playerid; }
	void setName(const std::string &name) { m_name = name; }
	std::string &getName() { return m_name; }
	void setLevel(unsigned char lv){ m_level = lv; }
	unsigned char getLevel() { return m_level; }
	void setOnline(bool ifonline){ m_ifonline = ifonline; }
	bool getOnline() { return m_ifonline; }
protected:
	int m_playerid;
	std::string m_name;
	unsigned char m_level;
	unsigned char m_iconid;
	bool m_ifonline;/////�ͻ�����ʾ��
};
typedef std::list< CRCore::ref_ptr<crFriend> >FriendVec;
typedef std::set<std::string> BlackNameSet;
class crSale : public CRCore::Referenced
{
public:
	crSale():m_saleListID(-1),m_goodsType(0),m_goodsID(0),m_price(0),m_count(0),m_prepareTimer(0),m_saleid(0),m_saletimer(0),m_salestate(CRNetApp::Sale_Prepare),m_gaincash(0){}
	void setSaleListID(unsigned char id){ m_saleListID = id; }
	char getSaleListID(){ return m_saleListID; }
	void setGoodsType(int gtype){ m_goodsType = gtype; }
	int getGoodsType() { return m_goodsType; }
	void setGoodsID(int id){ m_goodsID = id; }
	int getGoodsID() { return m_goodsID; }
	void setPrice(int price){ m_price = price; }
	int getPrice() { return m_price; }
	void setCount(int count){ m_count = count; }
	int getCount() { return m_count; }
	short& prepareTimer(){ return m_prepareTimer; }

	void setSaleID(int saleid){ m_saleid = saleid; }
	int getSaleID(){ return m_saleid; }
	int& saleTimer(){ return m_saletimer; }
	void setSaleState(unsigned char s) { m_salestate = s; }
	unsigned char getSaleState() { return m_salestate; }
	void setGaincash(int cash){ m_gaincash = cash; }
	int getGaincash(){ return m_gaincash; }
protected:
	char m_saleListID;//
	int m_goodsType;
	int m_goodsID;
	int m_price;
	int m_count;
	short m_prepareTimer;//��ʱ��
	int m_saleid;
	int m_saletimer;
	unsigned char m_salestate;
	int m_gaincash;
};
typedef std::list< CRCore::ref_ptr<crSale> > SaleList;
class crFubenInfo : public CRCore::Referenced
{
public:
	crFubenInfo():m_fubenprogress(0),m_fubencomplete(0),m_starcount(0),m_chapterid(0){}
	void setFubenProgress(short fubenprogress){ m_fubenprogress = fubenprogress; }
	short getFubenProgress() { return m_fubenprogress; }
	void setComplete(unsigned char fubencomplete){ m_fubencomplete = fubencomplete; }
	unsigned char getComplete() { return m_fubencomplete; }
	void setStarCount(unsigned char starcount){ m_starcount = starcount; }
	unsigned char getStarCount() { return m_starcount; }
	void setChapterId(int chapterid){ m_chapterid = chapterid; }
	int getChapterId() { return m_chapterid; }
protected:
	short m_fubenprogress;//��������
	unsigned char m_fubencomplete;//0.δͨ�أ�1.��ͨ�ش���
	unsigned char m_starcount;//�Ǽ�
	int m_chapterid; //����chapterid
};
typedef std::map< unsigned short, CRCore::ref_ptr<crFubenInfo> > FubenProgressMap;//����ID����������,ͨ�ر�־��,�Ǳ�
class crExtraProduce : public CRCore::Referenced
{
public:
	crExtraProduce(){}
	//void setType(unsigned char type){ m_type = type; }
	//unsigned char getType() { return m_type; }
	int &timer() { return m_timer; }
	void setPercent(short percent) { m_percent = percent; }
	short getPercent() { return m_percent; }
protected:
	//unsigned char m_type;//T_Food T_Wood T_Iron T_Horse T_Copper
	int           m_timer;
	short         m_percent;
};

enum JXJChatMode
{
	ChatAll,		//ȫ��
	ChatInWorld,	//����
	ChatInCountry,  //����
	ChatInGroup,    //����
	ChatInTeam,     //����
	ChatOneToOne,  //˽��
	ChatNull
};
class crJXJChatRecord : public CRCore::Referenced
{
public:
	crJXJChatRecord():m_shiliID(0){}
	void setSenderName(const std::string &name){ m_senderName = name; }
	const std::string& getSenderName(){ return m_senderName; }
	void setChatText(const std::string &chattext){ m_chattext = chattext; }
	const std::string& getChattext(){ return m_chattext; }
	void setSenderShiliID(const unsigned char shili){m_shiliID = shili;}
	unsigned char getSenderShiliID(){return m_shiliID;}
	void setTextColor(CRCore::crVector4 color){m_color = color;}
	CRCore::crVector4 getTextColor(){return m_color;}
	std::string & getChatChannelName(){return m_type;}
	void setChatChannelName(std::string type){m_type = type;}
	std::string &getReciverName(){return m_reciverName;}
	void setReciverName(std::string reciverName){m_reciverName = reciverName;}
protected:
	std::string m_senderName;
	std::string m_reciverName;
	std::string m_chattext;
	unsigned char m_shiliID;
	CRCore::crVector4 m_color;
	std::string  m_type;
};

class crJXJPersuadeInfo : public CRCore::Referenced
{
public:
	crJXJPersuadeInfo():m_fubenid(0),m_canFinishTime(-1),m_level(0){}
	void setFubenId(unsigned short fubenid){m_fubenid = fubenid;}
	unsigned short getFubenId(){return m_fubenid;}
	void setTime(_crInt64 time){m_canFinishTime = time;}
	_crInt64 getTime(){return m_canFinishTime;}
	void setLevel(unsigned char setlv){m_level = setlv;}
	unsigned char getLevel(){return m_level;}
	void setJKId(int setjkid){m_jkid = setjkid;}
	int getJKId(){return m_jkid;}
protected:
	unsigned short m_fubenid;
	//_crInt64 m_time;
	_crInt64 m_canFinishTime;//�������˴洢���ʱ��ͻ��˴洢����ʱʱ��
	unsigned char m_level;
	int m_jkid;
};
struct BattleReportThree
{
	int first;
	int second;
	int third;
};
struct PlayerBattleReport
{
	BattleReportThree info;
	int experience;//jingyan
	int exploit;//��ѫ
};
typedef std::map<std::string, PlayerBattleReport> PlayerBattleReportInfoMap;//playerName����Ͷ��

struct strZhengzhaoInfo :public CRCore::Referenced
{
	unsigned char m_type; //���������ͣ����һ���ţ�
	std::string m_publisher; //������
	std::string m_chengchiName;
	_crInt64 m_battleroomid;
	int m_sceneid;
	unsigned short m_timer;
	std::string m_liuyan;
	unsigned char m_battletype; //ս������
	strZhengzhaoInfo()
	{
		m_type = 0; 
		m_publisher = "";
		m_chengchiName = "";
		m_battleroomid = 0;
		m_sceneid = 0;
		m_timer = 0;
		m_liuyan = "";
		m_battletype = 0;
	}
};
typedef std::vector<CRCore::ref_ptr<strZhengzhaoInfo> > ZhengzhaolingVec;		// ��������Ϣ(����ʹ��)���������ݿ�

class crJXJBattleReportInfo : public CRCore::Referenced
{
public:
	crJXJBattleReportInfo():m_battleid(0),m_isAttackWin(false){
		m_total.first = 0; m_total.second = 0; m_total.third = 0;
		m_totalDead.first = 0; m_totalDead.second = 0; m_totalDead.third = 0;
	}

	void setBattleId(int battleid){ m_battleid = battleid; }
	int getBattleId(){ return m_battleid; }

	void setAttackWin(bool win){ m_isAttackWin = win; }
	bool getAttackWin(){ return m_isAttackWin; }
	void setBattleName(const char * str){ m_strBattleName = str; }
	std::string & getBattleName(){ return m_strBattleName; }

	void setTotal(BattleReportThree total){ m_total = total; }
	BattleReportThree& getTotal(){ return m_total; }

	void seTotalDead(BattleReportThree &total){ m_totalDead = total; }
	BattleReportThree & geTotalDead(){ return m_totalDead; }

	PlayerBattleReportInfoMap & getReportPlayerInfoMap(){ return m_playerBattleReportInfo; }
	
protected:
	int m_battleid;
	bool m_isAttackWin;
	std::string m_strBattleName;
	BattleReportThree m_total;//�ܣ������ܣ��ط���
	BattleReportThree m_totalDead;//�������������ط�
	PlayerBattleReportInfoMap m_playerBattleReportInfo;
};

class GroupCantonSpecialty : public CRCore::Referenced
{
public:
	GroupCantonSpecialty():m_itemtype(0),m_itemid(0),m_itemnum(0),m_contribute(0){}
	int m_itemtype;
	int m_itemid;			//���ء�פ���ݵ��ز�id
	int m_itemnum;		
	int m_contribute;
};
typedef std::vector<CRCore::ref_ptr<GroupCantonSpecialty>> GroupCantonSpecialtyVec;	//���ųǳع�������8����Ʒ

typedef std::map<int, crJXJBattleReportInfo> BattleReportInfoMap;//ս��id

typedef std::map< unsigned char, CRCore::ref_ptr<crExtraProduce> > ExtraProduceMap;//JXJThingType,timer,Percent
typedef std::deque< std::pair< int,CRCore::ref_ptr<CRCore::crStreamBuf> > >ClientDesposeEventDeque;
typedef std::deque< CRCore::ref_ptr<CRCore::crStreamBuf>> ChatRecordDeque;
typedef std::map<JXJChatMode, ChatRecordDeque> ChatRecordMap;
typedef std::vector<unsigned short> RebelCityVec;
typedef std::map<unsigned short,CRCore::crVector2i> PersuadeTimeMap;//fubenid,����ID������ʱʱ��
typedef std::deque< CRCore::ref_ptr<crJXJPersuadeInfo> > PersuadeInfoDeq;//˵����Ϣ
typedef std::vector<unsigned char> PlayerIconVec;
typedef std::set<int> SelectLeaderIdSet;									// ���ͶƱ�ļ���
typedef std::set<int> HadWonGroupFuBenSet;									// ��� �Ѿ�ͨ�صĸ���ID
typedef std::vector<int> SelectedIdVec;										// ���ѡ��ĺ�ѡ�˵ļ��ϣ��������ݿ�
typedef std::map<int,_crInt64>	ItemUsedTimeMap;							// ��Ʒ���ʹ��ʱ��Map
typedef std::map<unsigned char,unsigned char> AchieveShopMap;			// (achieveshop.tabid,�ѹ������)�ɾ��̵���Ʒ���������¼��ֻ��¼�й���������Ƶ���Ʒ
typedef std::map<unsigned char,unsigned char> GovShopMap;			// (itemid,�ѹ������)�̵���Ʒ���������¼��ֻ��¼�й���������Ƶ���Ʒ

typedef std::deque < std::pair<int,std::pair<int,std::string> > > AddGroupMemberRequestDeq; // groupid ,playerid ,groupName
//typedef std::vector<CRCore::crVector3i> LunHuiRewardVec;		// id��magicid��count
typedef std::multimap<unsigned char,std::pair<unsigned char,CRCore::crVector3i>> LunHuiRewardMap; //�ȼ����Ƿ���ȡ��ʶ����1��ȡ��0Ϊ��ȡ�� �ֻؽ���Vector��
typedef std::set<int> MyGroupApplySet;
typedef std::map<int, CRCore::crVector3i> TroopsAchieveMap; //��ұ�����سɾ���Ϣ,vector[0]Ϊ��ɱ��Ҵ˱�������,vector[1]Ϊ��Ҵ˱�����������,vector[2]Ϊ��Ҵ˱��ֻ�ɱ����
class crPlayerRewardData;
struct InviteInfo
{
	unsigned char type;
	unsigned short id;
	int playerid;
};
struct CallForHelpInfo
{
	int secneid;
	int roomid;
};
typedef std::bitset<64>  BitSet64;

class crJXJPlayerDataMonitor : public CRCore::Referenced
{
public:
	crJXJPlayerDataMonitor();
	void setGoldingot(int goldingot);
	int getGoldingot();
	void setGiftgold(int giftgold);
	int getGiftgold();
	void setVipExp(int vipExp);
	int getVipExp();
	void setCoppercash(int coppercash);
	int getCoppercash();
	void setFood(int food);
	int getFood();
	void setWood(int wood);
	int getWood();
	void setIron(int iron);
	int getIron();
	void setHorse(int horse);
	int getHorse();
	void setLevel(unsigned char lv);
	unsigned char getLevel();
	void setExploit(int exploit);
	int getExploit();
	void setTroops(int troops);
	int getTroops();
	void setManorlv(unsigned short manorlv);
	unsigned short getManorlv();
protected:
	int m_goldingot;//Ԫ��
	int m_giftgold;//���
	int m_vipExp;//vip����
	int m_coppercash;//ͭǮ
	int m_food;//��ʳ
	int m_wood;//ľ��
	int m_iron;//��
	int m_horse;//��ƥ
	unsigned char m_level;//�ȼ�
	int m_exploit;//��ѫ
	int m_troops;//����
	unsigned short m_manorlv;//�����ܵȼ�
};
const int MAX_EQUIP_BIND = 4;//װ��������;
class crJXJPlayerData : public CRCore::crData
{//server & client
public:
	crJXJPlayerData();
	crJXJPlayerData(const crJXJPlayerData& data);
	DataClass(JXJ, JXJPlayer)
	virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	virtual void excHandle(CREPARAM msg);

protected:
	virtual ~crJXJPlayerData();
	int m_playerid;//Server�ã��������ݿ�
	bool m_playersex;//0Ů��1��
	unsigned char m_playericonid;//ͷ��ID
	unsigned char m_shiliid;//����ID
	unsigned short m_homeid;//���
	unsigned short m_chengchiid;//������ڳǳ�
	unsigned char	m_feteTimes;					// ���ҽ���������
	unsigned char m_enrichType;						// ���ҽ��渻������
	unsigned char m_enrichTimes;					// ���ҽ��渻������

	unsigned char m_groupContributeiType;			// ���ž�������
	unsigned char m_groupContributeiTimes;			// ���ž��״���
	int m_goldingot;//Ԫ��
	int m_giftgold;//���
	//��Դ
	int m_coppercash;//ͭǮ
	int m_food;//��ʳ
	int m_wood;//ľ��
	int m_iron;//��
	int m_horse;//��ƥ
	//פ�ؽ����ȼ�
	unsigned char m_fuyalv;//����
	unsigned char m_bingyinglv;//��Ӫ
	unsigned char m_jiusilv;//����
	unsigned char m_gongfanglv;//����
	unsigned char m_shijilv;//�м�
	unsigned char m_fukulv;//����
	_crInt64 m_mingjulv;//���unsigned char[8]
	_crInt64 m_nongtianlv;//ũ��unsigned char[8]
	_crInt32 m_muchanglv;//����unsigned char[4]
	_crInt32 m_lingdilv;//�ֵ�unsigned char[4]
	_crInt32 m_kuangshanlv;//��ɽunsigned char[4]
	_crInt64 m_updateTimer;//�ϴ����ݸ��¼�ʱ,���ݿ��¼������Ҫ�����ͻ��� time_t ��
    CRCore::crVector4i m_buildingTimes;//��
	CRCore::crVector4i m_recruitTimes;//��
	unsigned short m_junling;//���� /100
	//Ԥ������
	//unsigned char m_maxtroops;//Ԥ�����ӱ������
	TroopsMap m_troopsMap;
	TroopsEquipMap m_troopsEquipMap;
	// �����б�
	JXJItemBagVec m_itembagvec;
	//�Ƽ��ȼ�
	//unsigned char m_infantrylv;//�����Ƽ��ȼ�
	//unsigned char m_cavalrylv;//����Ƽ��ȼ�
	//unsigned char m_archerlv;//�������Ƽ��ȼ�
	//unsigned char m_siegelv;//���ǿƼ��ȼ�
	//unsigned char m_shieldlv;//�ܵȼ�
	//unsigned char m_guardlv;//�����ȼ�
	//unsigned char m_saddlelv;//�����ȼ�
	//unsigned char m_assaultlv;//ͻ���ȼ�
	//unsigned char m_assistlv;//Эս�ȼ�
	//unsigned char m_penetratelv;//��͸�ȼ�
	//unsigned char m_manufacturelv;//����ȼ�
	//unsigned char m_gunpowderlv;//��ҩ�ȼ�
	//unsigned char m_bravelv;//���ڵȼ�
	//unsigned char m_ironcavalrylv;//����ȼ�
	//unsigned char m_gearlv;//���صȼ�
	//unsigned char m_fireboltlv;//�����ȼ�
	//unsigned char m_masterlv;//�������ȼ�
	//unsigned char m_juntunlv;//���͵ȼ�
	//unsigned char m_reformlv;//���Ƹĸ�ȼ�
	////ǩ������
	//unsigned char m_signin;
	FormationInfoVec m_formationInfoVec;
	//��Ϣ��ʾ
	unsigned int m_goldcosthint;//������ʾ
	//�����б�
	FriendVec m_friendList;
	//������
	TeamMemberVec m_myTeam;//�����sceneid��ϵ������˳�scene��ӳ���
	TeamVec m_queryTeamVec;//�ͻ�����
	int m_teamLeaderID;
	//char m_queryTeamIndex;
	////����ˢ�¼�ʱ��
	//short m_halltimer;//����
	//int m_privatetimer;//�ż�
	//int m_hallCard[5];
	//int m_privateCard[3];
	//��˰
	unsigned char m_levyCount;
	//int m_levyTimer;
	/////���߽�����ʱ��
	unsigned char m_onlineRewardCount;//ʣ�����߽�������
	_crInt64 m_onlineRewardTimer;//��һ����ȡ������ʱ��
	////�ͻ������߽�����ʱ����
	int m_playerOnlineRewardTimer;
	//����
	char m_buyJunlingCount;
	unsigned short m_buyJunlingTimer;
	//����
	SaleList m_saleList;
	//CRCore::ref_ptr<CRCore::crStreamBuf> m_dataStream;
	GNE::Mutex m_dataMutex;
	static GNE::Mutex m_saveMutex;
	unsigned char m_utemp[8];
	////GameServerData
	bool m_openBattle;//������ս
	int m_battleTimer;//�������ݿ�
	//bool m_openPass;// �����ذ�
	//short m_passTimer;
	ChengchiMap m_chengchiMap;//��Ҹյ�¼��ʱ��������������,ֻ�ͻ�����Ч
	//��������Ϣ
	unsigned char m_inviteType;
	int m_inviteID;
	unsigned short m_inviteChengchiID;//�ǳ�id���߸���id
	//��ս
	unsigned char m_fubenOrChengchiType;//0���ޣ�1����վ 2������ 3:����ս��
	unsigned short m_fubenOrChengchiID;//Ҫ���ĸ���ID���߳ǳ�ID
	//unsigned short m_battleChengchiID;//Ҫ���ĳǳ�ID����ʱ����
	//unsigned short m_fubenID;//����ID����ʱ����
	_crInt64 m_battleRoomID;//battleid(��������ID���ط�����ID���ǳ�ID),roomid
	short m_curFubenProgress;//SceneServer����ʱ����
	//�ѿ��������ĸ�����
	unsigned char m_openbagnum;
	//��������б�
	JXJSaleItemList m_saleitemlist;
	// ���������б�
	JXJItemBagVec m_jiangkabagvec;
	FubenProgressMap m_fubenProgressMap;
	//���ߵ�DataObject���ͻ��˷��������У�����Ҫͬ��
	ItemObjectMap m_itemObjectMap;

	ExtraProduceMap m_extraProduceMap;//��Ҫ�������
	//unsigned char m_jingbinglv;//����
	//unsigned char m_jianjialv;//���
	//unsigned char m_qiangrenlv;//ǿ��
	//unsigned char m_guimoulv;//��ı
	//unsigned char m_gongchenglv;//����
	//unsigned char m_yuangonglv;//Զ��
	//unsigned char m_sugonglv;//�ٹ�
	//unsigned char m_qiangxinglv;//ǿ��
	//unsigned char m_zhaomulv;//��ļ
	//unsigned char m_rendelv;//�ʵ�
	JXJAppointCardVec m_appointjiangkabagvec;
	//unsigned char m_luckycardcoppercost;//��ȡ����ͭǮ���Ӵ���
	//unsigned char m_luckycardgoldcost;//��ȡ����Ԫ�����Ӵ���
	//unsigned char m_knowluckycard;//֪����Ԫ�����Ӵ���
	int m_luckycard[3];//��ȡ����
	//int m_jiusirefreshtime;//������ȡ�����۸�ˢ��ʱ��
	unsigned char m_viplv;//��ʦ�ȼ�
	int m_vipExp;//��ʦ�ȼ��ɳ�ֵ
	CRCore::ref_ptr< crPlayerRewardData > m_fubenReward;//������������
	unsigned char m_reliveCount; //������������
	ClientDesposeEventDeque m_clienteventdeq;//
	int m_countrycontribute;//���ҹ���
	ChatRecordMap m_chatRecordMap;//�ͻ���������Ϣ
	std::map<int,std::pair<int,int>> m_chatitemlinkIdMap;		//�ͻ���������Ʒlinkid
	std::map<int,InviteInfo> m_chatinviteIdMap;				//�ͻ�����������linkid
	std::map<int, std::pair<std::string, int>>m_chatBattleReportIDMap;//�ͻ�������ս���ֿ�id
	std::map<int, int>m_chatPraiseIDMap;//�ͻ��������������
	std::map<int, std::pair<int, int>> m_chatCallForHelpLinkIdMap;//�ͻ���������������
	unsigned short m_cardimpression;//�齫���øж�
	int m_cardpieces;//����
	unsigned char m_freeCounterinsurgency;//���ƽ�Ѵ���
	unsigned short m_RefineEquipFreeCount;//��Ѿ������� /100
	RebelCityVec m_rebelCityVec;//���ҳǳ�ID �ͻ�����ʱ����
	unsigned short m_rebelTimer;//�ͻ�����ʱ�������ҵ���ʱʱ��
	unsigned char m_NongTianShuiLilv;//ũ��ˮ��
	unsigned char m_ZhiShuZaoLinlv;//ֲ������
	unsigned char m_YouZhiCaoChanglv;//���ʲݳ�
	unsigned char m_JingKuangShenWalv;//��������
	unsigned char m_GuLiMaoYilv;//����ó��
	unsigned char m_ZhengShouXinDelv;//�����ĵ�
	unsigned char m_YanBingYueWulv;//�ݱ�����
	unsigned char m_XunBingXinDelv;//ѵ���ĵ�
	unsigned char m_ZongMiaoJiSilv;//�������
	unsigned char m_JiSiXinDelv;//�����ĵ�
	int m_MarketBuyResourceMax;//�м�ÿ���ѹ�����
	_crInt32 m_refinemagicid;//����ID
	CRCore::ref_ptr<CRCore::crStreamBuf> m_cfgstream;//���빫��
	CRCore::ref_ptr<CRCore::crStreamBuf> m_oldcfgstream;//���빫��
	unsigned short m_FreeRollCardCount;//��Ѿ������� /100
	CRCore::ref_ptr<crJXJPlayerStore> m_playerStore;//�ֻزֿ�
	short m_playerCycleCount;//����ֻش�����������playergamestore���ݿ������������ǲ�ѯͬ�������
	unsigned short m_autosellcard;//�Զ����۽������ף��̣�����
	TroopsTechMap m_troopstechmap;//���ֿƼ�||�����Ƽ�
	CardExtraTechMap m_cardExtraTechMap;//��Ͻ����Ƽ��ȼ�
	unsigned char m_CardImpression2CritTechLv;//�øжȱ����Ƽ�//2
	unsigned char m_CardImpression4CritTechLv;//�øжȱ����Ƽ�//4
	unsigned char m_CardImpression6CritTechLv;//�øжȱ����Ƽ�//6
	unsigned char m_CardImpression10CritTechLv;//�øжȱ����Ƽ�//10
	unsigned char m_FreeRollCardTechLv;//���ˢ���Ƽ�16
	unsigned char m_OrangeCardUpgradeTechLv;//�ȿ����ǿƼ�
	unsigned char m_CardShopOpenTechLv;//�����̵꿪���Ƽ�
	unsigned char m_MakeEquipTechLv;//װ������Ƽ�
	unsigned char m_EquipRefineTechLv;//װ�������Ƽ�
	unsigned char m_EquipAttachTechLv;//�����Ƽ�
	unsigned char m_SmeltEquipTechLv;//�����Ƽ�//����װ������
	unsigned char m_SmeltMaterialTechLv;//�����Ƽ�//������������
	unsigned char m_SmeltStoneTechLv;//�����Ƽ�//��������ʯ����
	unsigned char m_EquipRefineMaxCount1TechLv;//װ�������Ƽ���Ѵ���12
	unsigned char m_EquipRefineMaxCount2TechLv;//װ�������Ƽ���Ѵ���16
	unsigned char m_EquipRefineMaxCount3TechLv;//װ�������Ƽ���Ѵ���20
	unsigned char m_EquipRefineMaxCount4TechLv;//װ�������Ƽ���Ѵ���24
	unsigned char m_EquipRefineProduce1TechLv;//װ�������Ƽ��ظ�50%
	unsigned char m_EquipRefineProduce2TechLv;//װ�������Ƽ��ظ�100%
	unsigned char m_EquipRefineProduce3TechLv;//װ�������Ƽ��ظ�150%
	unsigned char m_EquipRefineProduce4TechLv;//װ�������Ƽ��ظ�200%
	unsigned char m_FreeRollCard2TechLv;//���ˢ���Ƽ�20
	unsigned char m_FreeRollCard3TechLv;//���ˢ���Ƽ�24
	unsigned char m_FreeRollCardProduce1TechLv;//���ˢ���ظ��Ƽ�
	unsigned char m_FreeRollCardProduce2TechLv;//���ˢ���ظ��Ƽ�
	unsigned char m_FreeRollCardProduce3TechLv;//���ˢ���ظ��Ƽ�
	unsigned char m_FreeRollCardProduce4TechLv;//���ˢ���ظ��Ƽ�
	unsigned char m_FuKuMaxTechLv;//�������ֵ�Ƽ�20
	unsigned char m_FuKuMaxTech2Lv;//�������ֵ�Ƽ�5
	unsigned char m_FuKuMaxTech3Lv;//�������ֵ�Ƽ�10
	BlackNameSet m_blacknameset; 
	TechDevelopMap m_techdevelopmap;//�з��еĿƼ�
	bool m_bisCycling;//�Ƿ����ֻأ��ͻ�����ʱʹ�ã�
	int m_iClientCycleTime;//�ֻ�ʱ�䣨�ͻ�����ʱʹ�ã�
	//PersuadeInfoDeq m_persuadeInfoDeq;//˵��
	SavedFormationInfoVec m_savedformationinfovec;//��ӱ�����ҳ
	unsigned char m_opensavedformationifo;//��ӱ�����ҳ����
	unsigned char m_changeShiliTimes;//�����ѹ�����
	unsigned short m_seriesLandDays;//������¼ʱ��
	unsigned short m_loginDays;		// ��½����
	unsigned char m_LandRewardGetCount;//��½�齱����
	CRCore::ref_ptr< crPlayerRewardData > m_lanRewardData;//��½�������������棨�������ݿ⣬�����ͻ��ˣ�
	int m_nLandRewardTime;//��½�����ͻ��˵���ʱ(ֻ�ͻ���ʹ��)
	LunHuiRewardMap m_lunhuiRewardMap;
	//PlayerIconVec m_playerBuyIconVec;
	int m_nLunHuiRewardGiftGold;//�ֻؽ������
	AddGroupMemberRequestDeq m_addGroupMemberRequestDeq;
	bool m_skipnewhand;//�Ƿ����ֻأ��ͻ�����ʱʹ�ã�

	int m_consortiaid;
	MyGroupApplySet m_myGroupApplySet;	// ����ľ��� id
	SelectLeaderIdSet m_selectLeaderIdSet;						//ͶƱ��¼
	unsigned char m_savedformationindex;//��ӱ�����ҳҳ��
	unsigned char m_iftechbtnnew;//�Ƽ�ͼ���Ƿ���˸

	HadWonGroupFuBenSet m_hadWonGroupFuBenSet;					// �Ѿ�ͨ�صľ��Ÿ���id����

	unsigned char m_inspireLv;//�ͻ��˺ͷ�������ʱ���ݲ������ݿ⣬����˳�ս���Ǵ��������

	CRCore::ref_ptr<crJXJShili> m_myShili;// �ͻ���ʹ�ã���braindata�ƹ�������ֹ�������������

	BitSet64 m_chatChannelSetInfo;//���������Ϣ������Ϣ
	//int m_serverVersion;			// ��¼�������汾�ţ����ڡ���������ڰ汾���º��һ�ε�½��ʱ�򵯳��汾���½���

	int m_flushTime;
	NewFunctionOpenSet m_newfunctionopenset;//�¹��ܿ�����ʾset������ʾ������set������¼
	BattleReportInfoMap m_battleReportInfoMap;//�ͻ��˴洢����Ѳ�ѯ��ս������
	int m_battleReportQueryedId;//�ͻ��˴洢��ҵ�ǰ��ѯս��ID
	unsigned char m_lingqufengluflag;//��ȡٺ»��ʶ��
	//unsigned char m_mainrolerefreshflag;//�Ƿ�ˢ��mainrole��0��ˢ��ʹ�ã��������ã�����Ҫͬ�����ͻ���
	unsigned char m_tuntianlv;//����(��ʳ)
	unsigned char m_yelianlv;//ұ��������
	unsigned char m_fanzhilv;//��ֳ����ƥ��
	unsigned char m_fanmaolv;//��ï��ľ�ģ�
	unsigned char m_qiaojianglv;//�ɽ�������CD��
	unsigned char m_zhengshuilv;//��˰
	unsigned char m_techfenglulv;//ٺ»�Ƽ�
	unsigned char m_techjiusibaojilv;//���������Ƽ�
	unsigned char m_techworldtalklv;//���緢�ԿƼ�
	unsigned char m_techbuyjunlinglv;//�����ĿƼ�

	unsigned char m_foundCountryAward;	// ����ϵͳ������ȡ�����λ�洢
	int m_playertotalpaygold;//����ۼƳ�ֵԪ����

	unsigned char m_shuichelv;//ˮ��������ũ�����
	unsigned char m_ronglulv;//��¯�������������
	unsigned char m_gongshelv;//���磺�����ֵز���
	unsigned char m_mochuanlv;//������������������
	unsigned char m_7DaysAward;			// 7�յ�½������ȡ�����λ�洢
	unsigned char m_shouchong;//0:��ʾû�У�1��ʾ�׳䣬2��ʾ�Ѿ���ȡ�׳佱��

	//�¿�
	unsigned short m_yuekaid;//0:��ʾ��ǰû���¿���ÿ�����ͬһʱ����ֻ����һ���¿�
	_crInt64 m_yuekaendtime;
	_crInt64 m_lastgettime;//���һ����ȡʱ��
	GroupCantonSpecialtyVec m_groupCantonSpecialtyVec;
	ItemUsedTimeMap m_itemusedtimeMap;	//��Ʒ���һ��ʹ��ʱ��	itemid , time

	bool m_hadwonjuntuanfubenT;	//�����Ƿ�ͨ�ع����Ÿ���
	bool m_hadshowdismisstip;//�Ƿ���ʾ�����Ž�ɢʱ��. ���ͻ���ʹ��
	_crInt64 m_kaoshangfutime; //���һ��ʹ���������ʱ���
	unsigned char m_specialtyrefreshtimes;	//�ݿ�����ˢ�´���
	_crInt64 m_lastchongzhitime;	//������ֵ� ���һ����Ч��ֵ��ʱ��
	_crInt64 m_lastzeroRefreshtime;	//���һ�����ˢ�µ�ʱ��
	int m_chongzhicountT;			//�����ֵ����		

	//�ܿ�
	int      m_gainedzhoukahuodongid;//�ҵ�ǰ��õ��ܿ��ID
	_crInt64 m_zhoukaendtime;
	unsigned char m_zhoukagetstatus;//�ܿ���ȡ״̬
	int m_zhoukagetdayidx;//�ܿ���ǰ��ȡ���ǵڼ���

	int m_cZhengZhanQuan; //���ӵ����սȯ����
	int m_cGuoZhanJiFen;  //���ӵ�й�ս����
	int m_treasonbuffertimer;   //�ѹ�����ʱ��
	int m_treasonpunishtimer;   //�ѹ��ͷ���
	int m_treasoncoolingtimer;  //�ѹ���ȴ��
	unsigned char m_selectedshili;   //����ѹ�ʱѡ�������
	unsigned char m_guanzhi;  //1 ة�࣬2 ��˾��3 �󽫾�
	std::map<int,unsigned char> m_buyshagnxianmap; //���ÿ������ս�̵깺����Ʒ����
	unsigned char m_timesshangwu;   //����ս����������ȡ����
	unsigned char m_timesxiawu;   //����ս����������ȡ����
	unsigned char m_timeswanshang;   //����ս�����ϻ����ȡ����
	unsigned char m_praiselimit;   //�����չʾ�б��޵Ĵ���
	int m_praisedcount;   //��ұ��޵Ĵ���
	int m_praisecount;   //����ޱ��˵Ĵ���
	TroopsAchieveMap m_troopsachievemap; //��ұ�����سɾ���Ϣ,vector[0]Ϊ��һ�ɱ�˱�������,vector[1]Ϊ��Ҵ˱�����������,vector[2]Ϊ��Ҵ˱��ֻ�ɱ����
	int m_killplayercount; //���ɱ���������
	int m_killnpccount; //���ɱ��npc����
	int m_playerdeadcount; //�����������
	unsigned short m_passmingjiangcount; //���ͨ������֮·����
	CRCore::crVector4i m_ckilleachtroops;//���ɱ������ϵ����(������е)
	CRCore::crVector4i m_cdeadeachtroops;//�����������ϵ����(������е)
	///ÿ��ɱ����
	int m_dayplayerdeadcount; //ÿ�������������
	int m_daykillplayercount; //ÿ�����ɱ���������
	int m_daykillnpccount; //ÿ�����ɱ��npc����
	CRCore::crVector4i m_dayckilleachtroops;//ÿ�����ɱ������ϵ����(������е)
	//CRCore::crVector4i m_daycdeadeachtroops;//ÿ�������������ϵ����

    unsigned short m_Cpassworldfuben;    //���ͨ������ս������
	unsigned char m_cmingjiangfail;   //���������֮·��ʧ�ܵĴ���
	unsigned char m_cfinishdays;   //���������ɻ�Ծ�ȵ�����
	bool m_huoyuedusign;           //�Ƿ����Ծ�ȴﵽĿ����־
	int m_accomplishPointCache;		//�ɾ͵����
	int m_usedachievepoint;           //�Ѿ�ʹ�õĳɾ͵�
	unsigned char m_ctianxiafail;   //���������֮·��ʧ�ܵĴ���
	unsigned short m_Cpasstianxia;    //���ͨ����ս���´���
	CRCore::crVector4i m_danchangkill;//��ҵ�����ս��ɱ����ϵ����
	CRCore::crVector4s m_killdoorboss;//��һ�ɱ�ĳ��š�������������BOSS
	unsigned char m_havegotviplv;   //����Ѿ���ȡ��vip�ȼ����

	CRCore::ref_ptr<crJXJPlayerDataMonitor> m_playerDataMonitor;//��������쳣���
	//ս��λ�ñ仯��¼������5�����޲����򵯳���֤��ʾ
	float m_battleActiveTimer;
	unsigned short m_battleValidateID;//��֤
	bool m_elector;//���洢���ݿ⣬�Ƿ�߱�ѡ���ʸ�
	unsigned char m_vote;//���ҹ�Աѡ��ͶƱȨ�أ����洢���ݿ�
	bool m_beElected;//���洢���ݿ⣬�Ƿ�߱�ѡ���ʸ�
	bool m_recommendSet;//����Ƿ����Լ�
	unsigned char m_electIcon; //ѡ��ͼ����ʾʱ�����
	int m_equipBindInfo;//װ���󶨱����Ϣ;
	unsigned char m_isYellow;//�Ƿ����
	unsigned char m_isYearYellow;//�Ƿ���ѻ���
	unsigned char m_yellowLevel;//����ȼ�
	
	//char       |char     | char        | char
	//����ÿ�����|��ѻ���ÿ��|�������� |�ȼ����;
	int m_yellowAwardInfo;//���������Ϣ  ;
	SelectedIdVec m_SelectedIdVec;
	int m_cancelCantonTimer; //�ݿ�����ȡ��פ����ȴ��
	unsigned short m_cardImpressionLevel;//�øжȽ����ȼ�;
	JXJLordEquipVec m_friendEquipVec;//��ǰ�鿴�ĺ�������װ�����������ݿ�	
	unsigned char m_resourceCount;//��������Դ����;(ÿ������)
	unsigned char m_freeBuy;//�м�30����ÿ��һ����ѹ���;
    unsigned char m_goldRecruitCount;//ս��Ԫ������(����)����;
	unsigned char m_zhengZhaoTimes;//��ǰʹ�õĹ������ٴ������賿5��ˢ�£�
	bool m_myself; //�Ƿ�ˢ��Ϊ�Լ���װ����Ϣ���������ݿ�
	unsigned char m_pageNum;//��ǰ��ʾ�������ҳ��
	ZhengzhaolingVec m_guanyuanlingVec;   //��ս������
	ZhengzhaolingVec m_juntuanlingVec;	  //����������
	ZhengzhaolingVec m_CurZhengzhaolingVec;//��ǰ������ʾ��������
	int m_zhengZhaolingUpdateTimer; //���������ˢ��ʱ�䣬�������ݿ�
	int m_GuoJiaReleaseTimer; //��һ�η����������ٵ�ʱ��,�������ݿ�
	int m_JunTuanReleaseTimer; //��һ�η����������ٵ�ʱ�䣬�������ݿ�
	bool m_CheckYingzhengReward;//����Ƿ񷢷�Ӧ���������������ݿ�
	unsigned char m_attackVictoryTimes;//��ս����ʤ����������Ӧ�ɾͣ��ε�ͷ�ս�����ˣ�
	unsigned char m_defendVictoryTimes;//��ս�س�ʤ����������Ӧ�ɾͣ�����������������ʯ��
	unsigned short m_countryBattleTimes;//��ɹ�ս����;
	std::string m_releaseName;//���Ӧ�������������
	bool m_autoBattle;//�Ƿ����Զ�ս��
	unsigned char m_curPageNum_Introduction;//����ָ�ϵ�ǰ��ʾҳ��
	char m_7DayData[7][5];//7��Ŀ��
	bool m_hadGottenReward;//�Ѿ���ȡ���ſ��������
	unsigned char m_myRankVal;//�����ڵľ����ھ��ſ�����л������
	unsigned short m_startedDays; //�������� 
	CouldGetAwardMap m_couldGetAwardMap;//����ȡ������Ŀǰ�������֣�1.ٺ»��2.��˰��3.��Ծ�ȣ�4.�������ˢ�����ͻ�������
	bool m_gameIntroductionNoTips;// �Ƿ�������ؽ�����Ϸ����ͼ��
	bool m_hadShowFestivalHuodongCanvas;// �����Ƿ��Ѿ��Զ���ʾ���ջ����
	int m_onlinetimer;//һ���ڵ��ۼ�����ʱ����0�����㣬������ϵͳ��,�������ã������ͻ���
	AchieveShopMap m_achieveShopMap;//�ɾ��̵���Ʒ���������¼
	GovShopMap m_govShopMap;//�����̵���Ʒ���������¼
	bool m_autoBuilding;//�Զ���������
	char m_buildCountryTimes;//ÿ��ɽ��й��ҽ����ʣ�����,-1��ʾ����
	CRCore::crVector3i m_foreigncard;//������� 
	std::vector<short> m_blackgoldshop;//�ڵ�
	int m_blackShopRefreshTimer;//�ڵ�ˢ�µ���ʱ
	int m_superEquipCoin;//������
	int m_refineDiscountTimer;//�����ۿ�ʱ��
	unsigned char m_refineDiscount;//�����ۿ��ʣ�50��ʾ50%
};

class crPlayerSaleRecord : public CRCore::Referenced
{
public:
	crPlayerSaleRecord():m_saleid(0),m_price(0),m_count(0){}
	void setSaleID(int id){ m_saleid = id; }
	int getSaleID(){ return m_saleid; }
	void setPlayerName(const std::string &name){ m_playerName = name; }
	const std::string& getPlayerName(){ return m_playerName; }
	void setPrice(int price){ m_price = price; }
	int getPrice() { return m_price; }
	void setCount(int count){ m_count = count; }
	int getCount() { return m_count; }
protected:
	int m_saleid;
	std::string m_playerName;
	int m_price;
	int m_count;
};
typedef std::vector< CRCore::ref_ptr<CRNetApp::crInstanceItem> > ItemVec;
typedef std::vector< CRCore::ref_ptr<crPlayerSaleRecord> > PlayerSaleRecordVec;
typedef std::deque < std::pair< int,CRCore::ref_ptr<crBagItemData> > > RecvBagItemDeq;//type,data
typedef std::vector< std::pair<CRCore::ref_ptr<CRCore::crCanvasNode>,CRCore::ref_ptr<CRCore::crCanvasNode>>> ItemCanvasPairVec;//itemname,itemicon
typedef std::deque < std::string > RecvFloatAnimationTextDeq;
typedef std::vector< CRCore::ref_ptr<CRCore::crCanvasNode> > FloatAnimationCanvasVec;//�����õ�canvas
typedef std::vector<int> RecruitArmyVec;

typedef std::map < int,CRCore::ref_ptr<crMailInfo>,std::greater<int>> MailCacheMap;//mailid,

class crJXJBrainData : public CRNetApp::crBrainData
{//client
public:
	crJXJBrainData();
	crJXJBrainData(const crJXJBrainData& data);
	DataClass(JXJ, JXJBrain)
	virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	virtual void excHandle(CREPARAM msg);
protected:
	int m_curPlayerIconID;
	int m_curRecruitArmID;//RecruitArmWalk
	int m_curSelRecruitArmAID;
	int m_curFormationArmID;//FormationArmWalk
	int m_curSelFormationArmAID;
	int m_curCDHintID;
	int m_curTimesID;
	PlayerSaleRecordVec m_playerSaleRecordVec;
	int m_curSalePageNum;
	int m_saleTotal;
	int m_mycurSalePageNum;
	int m_mysaleTotal;
	GNE::Mutex m_dataMutex;
	unsigned short m_equipID;//����װ��
	int m_curFriendPageNum;//���ѵ�ǰҳ
	int m_totalFriendPageNum;//������ҳ��
	std::string m_addfriendname;
	unsigned char m_saleitemid; //������Ʒ�ڱ����ڼ���
	int m_saleitemmax;
	int m_curJiangkaBagPageNum;//����������ǰҳ
	int m_totalJiangkaBagPageNum;//����������ҳ��
	char m_JiangkaFormationRow;//���������
	float m_NewsCanvasStep;
	bool m_IfSetArmyNum;	
	CRCore::ref_ptr<CRCore::crCanvasNode> m_cur_canvas; // ��ǰ��canvas ����
	CRCore::ref_ptr<CRUI::crImageBoxWidgetNode> m_rtt_widget; // ��ǰ��canvas rtt �ؼ�����
	bool m_rtt_refresh; // ȷ���Ƿ��ͷ��ʼRTT
	int m_autoequipscount; // �Զ�����װ��������
	int m_curinvitepagenum; // ������ѽ��浱ǰҳ
	int m_totalinvitepagenum; // ������ѽ�����ҳ��
	//unsigned char m_curinvitetype; // �������,��սor����
	int m_CurForgeEquipID;//GongfangEquipWalk
	//int m_CurSelForgeEquipID;//GongfangSelectEquipID
	JXJItemBagVec m_salebagvec;
	int m_cursalecardpagenum; // ���۽������浱ǰҳ
	int m_totalsalecardpagenum; // ���۽���������ҳ��
	short m_salejiangkaindex; // ��������index
	int m_newjiangkaid; // �����½���id
	JXJRecvMailVec m_recvmailvec;//��ȡ�ʼ��б�
	unsigned char m_checkmailindex;
	MailCacheMap m_recvmailbodyMap;//��ȡ�ʼ������б�
	unsigned char m_deleteallmailflag;//�Ƿ�ɾ�������ʼ�
	int m_curformationpagenum; // ���ƽ��浱ǰҳ
	int m_totalformationpagenum; //���ƽ�����ҳ��
	std::string m_chatReciverName; //˽�Ľ�����Ϣ���
	int m_rankingpagenum;
	int m_rankingtotal;
	int m_BrainRecruitCount;//��ʱ�б�����
	int m_BrainResourcesCardCount;//��ʱ��Դ������
	int m_BrainRushTaskCount;//��ʱ����ɨ������
	unsigned char m_BrainExtractJiangKa;//��ȡ�����ɹ��ж�
	bool m_unfoldtasktype1; //�����������Ƿ�չ��
	bool m_unfoldtasktype2; //�����������Ƿ�չ��
	bool m_unfoldtasktype3; //�����������Ƿ�չ��
	bool m_unfoldtasktype4; //�����������Ƿ�չ��
	int m_curselecttaskid;//��ǰѡ�������id
	int m_GongfangLordPaperCount;//����װ��ͼֽ����
	RecvBagItemDeq m_itemDeq;//���뱳����Ʒ����
	ItemCanvasPairVec m_canvasVec;
	unsigned char m_useitemremaincount;
	unsigned char m_rollcardremaincount;
	unsigned char m_PingpanRemainCount;	// ����ʣ�����

	CRCore::ref_ptr<CRCore::crNode> m_msOnBulidingNode;
	CRCore::ref_ptr<CREncapsulation::crTableIO> m_playdatatabIO;
	int m_goldcosthinttype;
	MailCacheMap m_mailMap;
	RecruitArmyVec m_recruitarmyvec;
	unsigned char m_friendorblack;//0�Ӻ���,1������
	unsigned char m_ifEndSendPlayerData;
	unsigned char m_remainfubenrushcount;
	CRCore::crVector2ub m_queryloseshiliid;//ע��ʱʹ�õģ����������ID

	bool m_onlineDongHuaVisiable;// ����ȡ������ʾ
	int m_hideModel;//ս������NPC�����ģ��
	int m_autoBattleSetting;//ս���Զ�����
	int m_newguideid;//��������ִ��ID
	int m_newguidestep;//��������ִ�е��ڼ���
	std::string m_newguidecanvas;//������������󴥷���ť�ĸ���������
	std::string m_newguidebtn;//������������󴥷���ť����
	int m_newguidebtnmessage;//������������󴥷���ť�ĵ���¼�����mousepush��mouserelease�ȣ�
	int m_totalrollcardcount;//�ͻ��˼�¼��ǰ�齫�ܴ���
	int m_totalupgradecardcount;//�ͻ��˼�¼��ǰ���������ܴ���
	int m_totalmakelordequipcount;//�ͻ��˼�¼��ǰ����װ���ܴ���
	//float m_newhandtaskscrollbar;//������������value
	std::vector<int> m_newguidebtnparam;//��������������ť����Ҫ����
	int m_newguideemptyhypertext;//�Ƿ����˳��ı�����

	bool m_showVersion;			// �Ƿ���ʾ�汾��Ϣ���
	CRCore::crVector3i m_mousePushPos;	// ������һ�ΰ��µ�λ��

	int m_totalexchangerescount;//�ͻ��˼�¼��ǰ�м��һ�����
	int m_totallevycount;//�ͻ��˼�¼��ǰ��˰����
	int m_delayHideWidgetTime;//�ӳ����ؿؼ�
	
};
//typedef std::map<unsigned short,bool> AccomplishMap;
typedef std::map<unsigned short,CRCore::ref_ptr<crJXJAccomplish> > AccomplishMap;
//typedef std::map<int, CRCore::ref_ptr<crJXJHuodong> > HuodongMap;
typedef std::map<int, CRCore::ref_ptr<crJXJNewHuodong> > NewHuodongMap;//huodongid
typedef std::map<unsigned short, CRCore::ref_ptr<crJXJHuoyuedu> > HuoyueduMap;
typedef std::set<unsigned short > HuoyueduRewardSet;
#define SuperEquipZhulingCount 10//�����ӵ���Ŀ����
#define SuperEquipCount 8//��������
#define SuperEquipMaxLevel 40//������ߵȼ�
typedef std::vector<unsigned char>SuperEquipZhulinglvVec;
class SuperEquipData : public CRCore::Referenced
{
public:
	friend class crJXJMainRoleData;
	SuperEquipData(unsigned char equipid)
	{
		m_superEquipID = equipid;
		m_superEquipLevel = 1;
		m_superEquipExp = 0;
	}
	void setSuperEquipID(unsigned char id) { m_superEquipID = id; }
	unsigned char getSuperEquipID() { return m_superEquipID; }
	unsigned short openSuperEquip(unsigned char lvupPoint)
	{
		return levelup(lvupPoint);
	}
	unsigned short levelup(unsigned char lvupPoint);//���ػ�õ�ע�����
	unsigned char getSuperEquipLevel() { return m_superEquipLevel; }
	void setSuperEquipLevel(unsigned char lv) { m_superEquipLevel = lv; }
	void setSuperEquipExp(int exp)
	{
		m_superEquipExp = exp;
	}
	unsigned short addSuperEquipExp(int exp, unsigned char lvupPoint)
	{
		m_superEquipExp += exp;
		return levelup(lvupPoint);
	}
	int getSuperEquipExp() { return m_superEquipExp; }
private:
	unsigned char m_superEquipID;
	int m_superEquipExp;//��������
	unsigned char m_superEquipLevel;//0��ʾδ����
};
class SuperEquipZhulingData : public CRCore::Referenced
{
public:
	friend class crJXJMainRoleData;
	SuperEquipZhulingData()
	{
		m_zhulingPoint = 0;
		m_zhulinglvVec.resize(SuperEquipZhulingCount, 1);
	}
	void addZhulingPoint(short point) { m_zhulingPoint += point; }
	bool reduceZhulingPoint(short point) 
	{
		if (m_zhulingPoint >= point)
		{
			m_zhulingPoint -= point;
			return true;
		}
		return false;
	}
	unsigned short getZhulingPoint() { return m_zhulingPoint; }
	void setZhulingPoint(unsigned short point) { m_zhulingPoint = point; }
	void setZhulinglv(unsigned char index, unsigned char zhulinglv)
	{
		if (index < SuperEquipZhulingCount) m_zhulinglvVec[index] = zhulinglv;
	}
	unsigned char getZhulinglv(unsigned char index)
	{
		if (index < SuperEquipZhulingCount)
			return m_zhulinglvVec[index];
		return 0;
	}
	SuperEquipZhulinglvVec &getZhulinglvVec() { return m_zhulinglvVec; }
	void resetZhuling()
	{
		for (SuperEquipZhulinglvVec::iterator itr = m_zhulinglvVec.begin();
			itr != m_zhulinglvVec.end();
			++itr)
		{
			*itr = 1;
		}
	}
private:
	unsigned short m_zhulingPoint;
	SuperEquipZhulinglvVec m_zhulinglvVec;
};
typedef std::vector< CRCore::ref_ptr<SuperEquipData> >SuperEquipDataVec;
class crJXJMainRoleData : public CRNetApp::crRoleData
{//server & client
public:
	crJXJMainRoleData();
	crJXJMainRoleData(const crJXJMainRoleData& data);
	DataClass(JXJ, JXJMainRole)
	virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	virtual void excHandle(CREPARAM msg);
protected:
	virtual ~crJXJMainRoleData();
	bool m_mainroleinited;//
	unsigned char m_level;//�ȼ�
	int m_experience;//����
	int m_exploit;//��ѫ
	int m_achievement;//ս��
	//int m_consortiaid;//����ID
	unsigned char m_govpost;//��ְ
	unsigned char m_nobility;//��λ
	//unsigned char m_groupPos;// ���Ź�ְ
	//unsigned short m_campaignranking;//��ս����
	unsigned short m_bingfa;//����
	unsigned short m_zhenfa;//��
	unsigned short m_dongcha;//����
	unsigned short m_tongshuai;//ͳ��

	//short m_soldierCount;//����
	//short m_combatpower;//ս����
	//JXJLordSuitMap m_lordsuitmap;//��Ҫȥ��
	AccomplishMap m_accomplishMap;
	//ClientAccomplishMap m_clientAccomplishMap;//�ͻ���MAP
	unsigned short m_accomplishPoint;//��õĳɾ͵�����
	//HuodongMap m_huodongMap;
	NewHuodongMap m_newHuodongMap;
	JXJNewGuideMap m_newGuideMap;//��������
	HuoyueduMap m_huoyuedumap;//��Ծ��
	HuoyueduRewardSet m_huoyuedurewardset;//��Ծ�Ƚ���
	//int m_mygroupapplyid;
	//MyGroupApplySet m_myGroupApplySet;	// ����ľ��� id

	//unsigned short m_attrPoint;//δ��������Ե�,ÿ��1�����5�㣬ע������������
	//unsigned short m_skillPoint;//δʹ�õļ��ܵ�,ÿ��1�����2�㣬ע������������
	std::vector<JXJLordEquipVec> m_equipvecs;//����װ���б�,װ����װ;
	unsigned char m_currentEquipIndex;//��ǰװ������;
	unsigned char m_openedEquipVec;//�ѿ�����װ��ҳ;
	unsigned char m_appointColumnsVec;//�ѿ���ί������
	_crInt64 m_changeNameTime;//��һ���޸Ľ�ɫ��ʱ��
	int m_qiyutaskid;//�����ȡ����������id��0������
	unsigned char m_qiyuCompleteCount;//����������ɴ���
	SuperEquipDataVec m_superEquipDataVec;//����
	unsigned char m_superEquipLvupPoint;//�����ȼ��������ע�������0,1,2,3,4��
	unsigned char m_expPelletBuyTimes;//���鵤�������
	CRCore::ref_ptr<SuperEquipZhulingData> m_superEquipZhulingData;
};
class crJXJMetierData : public CRCore::crData
{
public:
	crJXJMetierData();
	crJXJMetierData(const crJXJMetierData& data);
	DataClass(CRNetApp, JXJMetier)
	virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	virtual void excHandle(CREPARAM msg);
protected:
	virtual ~crJXJMetierData();
	CRNetApp::GameTaskMap m_gameTaskMap;
	GNE::Mutex m_dataMutex;
	int m_currentTaskID;
	static GNE::Mutex m_saveMutex;
};
class crJXJTechUIData : public CRCore::crUIData
{//client
public:
	crJXJTechUIData();
	crJXJTechUIData(const crJXJTechUIData& data);
	DataClass(JXJ, JXJTechUI)
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
protected:
	GNE::Mutex m_dataMutex;
	int m_techid;
};
class crJXJRoleData : public CRNetApp::crRoleData
{//server & client
public:
	crJXJRoleData();
	crJXJRoleData(const crJXJRoleData& data);
	DataClass(JXJ, JXJRole)
	virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	virtual void excHandle(CREPARAM msg);
protected:
	unsigned char m_level;
	/*unsigned short*/int m_jxjArmyCount;//
	/*unsigned short*/int m_rtArmyCount;
	CRCore::ref_ptr<CRNetApp::crInstanceItem> m_extraParasiticItem;//������ֻ������sceneserver�����ڼ�,�����Լ����������ճɵ��˺��������ڼ����ߵ�
	CRCore::ref_ptr<CRNetApp::crInstanceItem> m_extraParasiticItem_rd;//������ֻ������sceneserver

	unsigned char m_troopType;//��������
	unsigned char m_npcItemType;//npc����
	short m_attackgainmp;		// ��ͨ������õ�mp
	short m_damagegainmp;		// �ܻ�����MP
	short m_extraattackgainmp;	 // ����ʱ�����mp����
	short m_extraattackgainmp_rd;
	short m_extrauseitemreducemp;	// ʹ�ü���ʱ���ĵ�mp
	short m_extrauseitemreducemp_rd;	// ʹ�ü���ʱ���ĵ�mp
	//bool m_isAddRTMP;				//�Ƿ�����ʿ��
	unsigned char m_extraRevertType;		// �ظ�����
	unsigned char m_extraRevertType_rd;		// �ظ�����
	short m_oldExtraId; //֮ǰʰȡ�����buf ID (ս����ʱ���ݣ����÷���)
	short m_extradamagegainmp;	 // ���˺�ʱ�����mp����
	short m_extradamagegainmp_rd;
	unsigned char m_chenghao; //��ҵĹ�ְ
	char m_gainDamageType;//-1,û�У�JXJDamageType
	_crInt64 m_lastUseItemTime;//��һ��ʹ�ü��ܻ��߹�����ʱ��
};
class crJXJBuildingItemData : public CRCore::crData
{//client
public:
	crJXJBuildingItemData();
	crJXJBuildingItemData(const crJXJBuildingItemData& data);
	DataClass(JXJ, JXJBuildingItem)
	virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
protected:
	GNE::Mutex m_dataMutex;
	unsigned char m_dataType;
	unsigned char m_itemState;
	int m_buildingid;
};
typedef std::map<int, double> TouchPlayerMap;
class crJXJItemData : public CRCore::crData
{//server & client
public:
	crJXJItemData();
	crJXJItemData(const crJXJItemData& data);
	DataClass(JXJ, JXJItem)
	virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	virtual void excHandle(CREPARAM msg);
protected:
	unsigned char m_dataType;
	unsigned char m_itemState;
	unsigned int m_guiseState;//����״̬
	//CRCore::crVector2 m_halfLengths;//itemcollidesize,�ӽű���ȡ���������ݿ⣬����Ҫ����ͬ��
	CRCore::crVector3 m_halfPhysicsBox;//itemcollidesize,�ӽű���ȡ���������ݿ⣬����Ҫ����ͬ��
	CRNetApp::PatrolPointVec m_patrolPointVec;//Ѳ�ߵ�����
	char m_patrolIndex;//��ǰѲ������
	unsigned char m_patrolLoopMode;//0:��ѭ�� 1:LOOP 2:SWING
	unsigned char m_camp;//��Ӫ//0���������ɹ���,�۲��ߣ� 1��ս�������˶����Զ��乥���� 2���ID����2��ʼ���涼�����ID����ͬ��Ӽ���Թ�����
	short m_sightRange;//��Ұ �ӽű���ȡ�����ü�¼�����ݿ�
	short m_eyeHeight;//�۾��߶� �ӽű���ȡ�����ü�¼�����ݿ�
	//CRCore::ref_ptr<CRCore::crStreamBuf> m_dataStream;
	GNE::Mutex m_dataMutex;
	unsigned char m_npcItemType;//npc����
	TouchPlayerMap m_touchPlayerMap;
	float m_touchTime;//��������Ҫ��ʱ��
};
class crJXJSkillData : public CRCore::crData
{//server & client
public:
	crJXJSkillData();
	crJXJSkillData(const crJXJSkillData& data);
	DataClass(JXJ, JXJSkill)
	virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	virtual void excHandle(CREPARAM msg);
protected:
	GNE::Mutex m_dataMutex;
	unsigned char m_dataType;
	float m_cdtime;
	char m_skilltype;//��������,�������ܻ򱻶�����

	unsigned short m_itemUseRange;//ʹ�÷�Χ
	short m_itemUseScope;//���÷�Χ
	int m_damage;
	unsigned short m_percentDamage;//��ͨ����ǧ�ֱ��˺�
	unsigned char m_damageType;

	unsigned short m_needMP;
	unsigned short m_needHP;
	unsigned short m_useMPLimit;	// ʹ�ü��ܵ����mp����
	_crInt32 m_targetExtraID;//id,���ȼ�

	_crInt8 m_targetExtraMaxOverlapCount;//Ŀ�꼼�����ɵ��Ӵ���
	_crInt8 m_userExtraMaxOverlapCount;//Ŀ�꼼�����ɵ��Ӵ���

	_crInt32 m_userExtraID;//id,���ȼ�
	_crInt32 m_equipExtraID;//id,���ȼ�
	unsigned char m_targetType;//ʹ�ö�������
	int m_belongPlayerID;//�¼�

	float m_useItemProtectTime;//ʹ�ñ���ʱ��,����ʱ��
	float m_chanttime;//0��ʾֻ����һ�Σ���m_chanttime<m_useItemProtectTimeʱ����ʾ�÷����ǳ���ʩ����������m_useItemProtectTime�ڼ���ÿ��m_chanttime����һ��WCH_RecvItemUse
	float m_duration;//������Чʱ��
	//����ʱ������
	_crInt64 m_lastUseTime;//��һ��ʹ��ʱ��

	//short m_equiphp;
	//short m_equipmp;
	//short m_equipAttack;
	//short m_equipDefend;//����״̬�Է������Ե�Ӱ��ֵ
	//short m_equipMagicDefend;//����״̬�Է������Ե�Ӱ��ֵ
	//short m_equipSpeed;
	//short m_equipStealth;
	//short m_equipStealthSpy;
	//short m_equipAttackSpeed;//�����ٶ������ٷֱ�
	//short m_equipSkillSpeed;//ʩ���ٶ������ٷֱ�
	//short m_equipCrit;
	//short m_equipParry;
	//short m_equipDodge;
	//short m_equipBuildAttack;//���ǹ�����
	//short m_equipAttackDist;//��������
	//short m_equipHitratio;//������
	//short m_equipIgnoreDefend;//��͸�����׺��Ӱٷֱ�
	//short m_equipIgnoreMagicDefend;//������͸�����׺��Ӱٷֱ�
	//short m_equipSightRange;//

	//unsigned char m_equipIgnoreDodge;//����Ŀ������ ���ɵ���
	//short m_equipAttackDamageBack;//�����˺�����
	//short m_equipSkillDamageBack;//�����˺�����
	//short m_equipAttackAbsorbHP;//������Ѫ
	//short m_equipSkillAbsorbHP;//������Ѫ
	//unsigned char m_equipCritSword;//������ ���ɵ��ӣ�����ɱ������200%��Ϊ250%��
	//_crInt32 m_equipSputtering;//�����˺�������뾶(unsigned short)���˺��ٷֱȣ�unsigned short����
	//short m_equipAttackDamage;//�����˺������˺�����
	//short m_equipSkillDamage;
	char m_damageCount;//�˺��������ƣ�0��ʾ����,��ֵ��ʾ���Զ�ͬһ��Ŀ���������˺�
};
class crPlayerRanking : public CRCore::Referenced
{
public:
	crPlayerRanking():m_playerid(0),m_exploit(0),m_govpost(1),m_shiliid(0),m_nobility(0),m_accomplishPoint(0),m_troops(0),m_manorlv(0),m_countrycontribute(0){}
	void setPlayerID(int playerid){ m_playerid = playerid; }
	int getPlayerID() { return m_playerid; }
	void setName(const std::string &name) { m_name = name; }
	std::string &getName() { return m_name; }
	void setExploit(int exploit){ m_exploit = exploit; }
	int getExploit() { return m_exploit; }
	void setGovpost(unsigned char post){ m_govpost = post; }
	unsigned char getGovpost() { return m_govpost; }
	void setShiliID(unsigned char shili){ m_shiliid = shili; }
	unsigned char getShiliID() { return m_shiliid; }
	void setLevel(unsigned char lv){ m_level = lv; }
	unsigned char getLevel() { return m_level; }
	void setNobility(unsigned char nobility){ m_nobility = nobility; }
	unsigned char getNobility() { return m_nobility; }
	void setAccomplishPoint(unsigned short point){ m_accomplishPoint = point; }
	unsigned short getAccomplishPoint() { return m_accomplishPoint; }
	void setTroops(int troops){ m_troops = troops; }
	int getTroops() { return m_troops; }
	void setManorlv(unsigned short lv){ m_manorlv = lv; }
	unsigned short getManorlv() { return m_manorlv; }
	void setCountrycontribute(int countrycontribute){ m_countrycontribute = countrycontribute; }
	int getCountrycontribute() { return m_countrycontribute; } 
	void setPlayerRank(int playerrank) {m_playerrank = playerrank; }
	int getPlayerRank() { return m_playerrank;}
protected:
	int m_playerid;
	std::string m_name;//characterName
	int m_exploit;//��ѫ
	unsigned char m_govpost;
	unsigned char m_shiliid;//����ID
	unsigned char m_level;//�ȼ�
	unsigned char m_nobility;//��λ
	unsigned short m_accomplishPoint;//�ɾ͵���
	int m_troops;
	unsigned short m_manorlv;
	int m_countrycontribute;//���ҹ���
	int m_playerrank;
};
//typedef std::map<int,CRCore::ref_ptr<crPlayerRanking> >ExpRankingWaitMap;//playerid
typedef std::multimap<int,CRCore::ref_ptr<crPlayerRanking>,std::greater<int> >ExpRankingMap;//exploit
typedef std::multimap<unsigned char,CRCore::ref_ptr<crPlayerRanking>,std::greater<unsigned char> >LevelRankingMap;//level
typedef std::multimap<_crInt64,CRCore::ref_ptr<crPlayerRanking>,std::greater<_crInt64> >GovpostRankingMap;//exploit,govpost
typedef std::multimap<unsigned short,CRCore::ref_ptr<crPlayerRanking>,std::greater<unsigned short> >AccomplishRankingMap;//accomplishPoint
typedef std::multimap<int,CRCore::ref_ptr<crPlayerRanking>,std::greater<int> >TroopsRankingMap;//����
typedef std::multimap<int,CRCore::ref_ptr<crPlayerRanking>,std::greater<int> >CountrycontributeRankingMap;//���ҹ���
typedef std::multimap<unsigned short,CRCore::ref_ptr<crPlayerRanking>,std::greater<unsigned short> >ManorlvRankingMap;//��ط�չ

typedef std::deque<int>SaleDisposeDeq;//playerid
class crQuerySale : public CRCore::Referenced
{
public:
	crQuerySale(int playerid):m_playerid(playerid),m_start(0){}
	int getPlayerID(){ return m_playerid; }
	void setGoods(CRCore::crVector2i &goods){ m_goods = goods; }
	const CRCore::crVector2i& getGoods(){ return m_goods; }
	void setStart(int start){ m_start = start; }
	int getStart() { return m_start; }
protected:
	int m_playerid;
	CRCore::crVector2i m_goods;
	int m_start;
};
typedef std::deque< CRCore::ref_ptr<crQuerySale> > QuerySaleDeque;
typedef std::deque< std::pair<int,int> >BuySaleDeque;//saleid,playerid
typedef std::set< std::string >GiftsPackKeySet;

class crQueryGiftsPack : public CRCore::Referenced
{
public:
	crQueryGiftsPack(int playerid,std::string keyWord):m_playerid(playerid),m_keyWord(keyWord),m_mailID(0){}
	int getPlayerID(){ return m_playerid; }
	std::string getKey(){ return m_keyWord; }
	int getMailID(){return m_mailID;}
	void setMailID(int id){m_mailID = id;}
protected:
	int m_playerid;
	std::string m_keyWord;
	int m_mailID;
};
typedef std::deque< CRCore::ref_ptr<crQueryGiftsPack> > QueryGiftsPackDeque;
class crCreateGiftsPack : public CRCore::Referenced
{
public:
	crCreateGiftsPack(int playerid,std::string key,CRCore::crStreamBuf *packet):m_playerid(playerid),m_key(key),m_pack(packet){}
	int getPlayerID(){ return m_playerid; }
	std::string getKey(){return m_key;}
	CRCore::crStreamBuf *getStreamBuf(){return m_pack.get();}
protected:
	std::string m_key;
	int m_playerid;
	CRCore::ref_ptr<CRCore::crStreamBuf>m_pack;
};
class crRushPlayerInfo : public CRCore::Referenced
{
public:
	crRushPlayerInfo():m_state(0),m_rushcount(0),m_fubenid(0),m_playerid(0){}
	void setRushCount(unsigned char rushcount){ m_rushcount = rushcount; }
	unsigned char getRushCount() { return m_rushcount; }
	void setAllRushCount(unsigned char allrushcount){ m_allrushcount = allrushcount; }
	unsigned char getAllRushCount() { return m_allrushcount; }
	void setState(unsigned char state){ m_state = state; }
	unsigned char getState() { return m_state; }
	void setFubenID(unsigned short fubenid){ m_fubenid = fubenid; }
	unsigned short getFubenID() { return m_fubenid; }
	void setPlayerID(int playerid){ m_playerid = playerid; }
	int getPlayerID() { return m_playerid; }
protected:
	unsigned char m_rushcount;
	unsigned char m_allrushcount;
	unsigned char m_state;
	unsigned short m_fubenid;
	int m_playerid;
};
class crCounterPlayerInfo : public CRCore::Referenced
{//ƽ��
public:
	crCounterPlayerInfo():m_state(0),m_rushcount(0),m_chengchiid(0),m_playerid(0){}
	void setTotalCount(unsigned char allrushcount){ m_allrushcount = allrushcount; }
	unsigned char getTotalCount() { return m_allrushcount; }
	void setRemainCount(unsigned char rushcount){ m_rushcount = rushcount; }
	unsigned char getRemainCount() { return m_rushcount; }
	void setState(unsigned char state){ m_state = state; }
	unsigned char getState() { return m_state; }
	void setChengChiID(unsigned short chengchiid){ m_chengchiid = chengchiid; }
	unsigned short getChengChiID() { return m_chengchiid; }
	void setPlayerID(int playerid){ m_playerid = playerid; }
	int getPlayerID() { return m_playerid; }
protected:
	unsigned char m_rushcount;
	unsigned char m_allrushcount;
	unsigned char m_state;
	unsigned short m_chengchiid;
	int m_playerid;
};
class crQueryGroupMemberInfo : public CRCore::Referenced
{
public:
	crQueryGroupMemberInfo():m_querytype(0),m_startpage(0),m_perpagenum(0),m_groupid(0),m_playerid(0){}
	void setQueryType(unsigned char querytype){ m_querytype = querytype; }
	unsigned char getQueryType() { return m_querytype; }
	void setStartPage(unsigned char startpage){ m_startpage = startpage; }
	unsigned char getStartPage() { return m_startpage; }
	void setPerPageNum(unsigned char perpagenum){ m_perpagenum = perpagenum; }
	unsigned char getPerPageNum() { return m_perpagenum; }
	void setGroupID(unsigned short groupid){ m_groupid = groupid; }
	unsigned short getGroupID() { return m_groupid; }
	void setPlayerID(int playerid){ m_playerid = playerid; }
	int getPlayerID() { return m_playerid; }
protected:
	unsigned char m_querytype;
	unsigned char m_startpage;
	unsigned char m_perpagenum;
	int m_groupid;
	int m_playerid;
};
class crJXJSystermMailInfo : public CRCore::Referenced
{
public:
	crJXJSystermMailInfo(){}
	void setSysMailTitle(std::string mailTitle){m_mailTitle = mailTitle;}
	const std::string& getSysMailTitle(){return m_mailTitle;}
	void setSysMailContent(std::string mailContent){m_mailContent = mailContent;}
	const std::string& getSysMailContent(){return m_mailContent;}
	void setSysMailItems(const CRCore::crVector3i &mailItems1,const CRCore::crVector3i &mailItems2,const CRCore::crVector3i &mailItems3,const CRCore::crVector3i &mailItems4)
	{ m_rewardItems1 = mailItems1; m_rewardItems2 = mailItems2; m_rewardItems3 = mailItems3; m_rewardItems4 = mailItems4; }
	const CRCore::crVector3i& getSysRewardItems1(){return m_rewardItems1;}
	const CRCore::crVector3i& getSysRewardItems2(){return m_rewardItems2;}
	const CRCore::crVector3i& getSysRewardItems3(){return m_rewardItems3;}
	const CRCore::crVector3i& getSysRewardItems4(){return m_rewardItems4;}
	void setSysMailType(unsigned char type){m_mailType = type;}
	unsigned char getSysMailType(){return m_mailType;}
	void setPlayerCharacterName(std::string name){m_characterName = name;}
	const std::string& getPlayerCharacterName(){return m_characterName;}
protected:
	std::string m_mailTitle;
	std::string m_mailContent;
	std::string m_characterName;
	//CRCore::crVector4i  m_rewardItems;
	CRCore::crVector3i  m_rewardItems1;
	CRCore::crVector3i  m_rewardItems2;
	CRCore::crVector3i  m_rewardItems3;
	CRCore::crVector3i  m_rewardItems4;
	unsigned char m_mailType;
};
class crJXJCounterinsurgencyInfo : public CRCore::Referenced
{
public:
	crJXJCounterinsurgencyInfo():m_ucTotalCount(0),m_usChengChiID(0){}
	unsigned char & getTotalCount(){return m_ucTotalCount;}
	unsigned short & getChengChiID(){return m_usChengChiID;}
	unsigned short & getTimes(){return m_times;}
protected:
	unsigned char m_ucTotalCount;
	unsigned short m_usChengChiID;
	unsigned short m_times;
};

class QueryGroupDeqItem : public CRCore::Referenced
{
public:
	QueryGroupDeqItem()
	{
		startPage = 0;
		pageNum = 0;
		playerid = 0;
	}
	unsigned char startPage;
	unsigned char pageNum;
	int playerid;
};

typedef std::deque<CRCore::ref_ptr<crQueryGroupMemberInfo> > QueryGroupMemberDeq;
typedef std::deque< CRCore::ref_ptr<crCreateGiftsPack> > CreateGiftsPackDeque;
typedef std::set<int> OnBattleUIPlayerSet;//playerid
typedef std::set<int> OnChengfangUIPlayerSet;//playerid
typedef std::map<unsigned short,OnChengfangUIPlayerSet > OnChengfangUIPlayerMap;//chengchiid,playeridset
//typedef std::map<int,CRCore::ref_ptr<crRushPlayerInfo>> JXJFubenRushPlayerMap;//playerid,fubenid,rushcount,(1.rushing,2.pause)
typedef std::vector<CRCore::ref_ptr<crRushPlayerInfo> > JXJFubenRushVec;
typedef std::map<char,JXJFubenRushVec> JXJFubenRushMap;//0,1,2,3,4,5 ÿ��ִ��һ�Σ�0�����ɨ���������������˳������ε���swap������5��>4->3->2->1->0��>5)���¼���������ڶ�����Ѱ����û����ͬ��playerid��û������뵽5��

typedef std::vector<CRCore::ref_ptr<crCounterPlayerInfo> > JXJCounterVec;
typedef std::map<char,JXJCounterVec> JXJCounterMap;//0,1,2,3,4,5... ÿ��ִ��һ�Σ�0�����ƽ�ѣ������������˳������ε���swap������5��>4->3->2->1->0->5...)���¼���������ڶ�����Ѱ����û����ͬ��playerid��û������뵽time��

typedef std::map< int,CRCore::ref_ptr<crJXJConsortia> > ConsortiaMap;//Consortia id
/////////�������а�
typedef std::multimap<unsigned char,CRCore::ref_ptr<crJXJConsortia>,std::greater<unsigned char> >ConsortialvRankingMap;//���ŵȼ�
//typedef std::multimap<unsigned short,CRCore::ref_ptr<crJXJConsortia>,std::greater<unsigned short> >ConsortiaMemberRankingMap;//��������

typedef std::set< unsigned short > ChengchiModifySet;//chengchiid
typedef std::deque<std::pair<int,std::string> > CreateGroupDeq;//playerid,groupname
//typedef std::deque<std::pair<int,std::pair<unsigned char,unsigned char>> > QueryGroupDeq;//playerid,startid,count
typedef std::deque<CRCore::ref_ptr<QueryGroupDeqItem> > QueryGroupDeq;
typedef std::deque< int > OnCountryQueryDeq;//playerid
typedef std::map< int,OnCountryQueryDeq > OnCountryQueryMap;//shiliid
typedef std::deque< CRCore::crVector3i >	GroupAddMemberDeq;			// invitedplayerid, groupid,playerid
//typedef std::map< int,unsigned char > OnlineRewardMap;//playerid,rewardCount ���IDʣ�ཱ������
typedef std::deque < CRCore::ref_ptr<crJXJSystermMailInfo> >  SystermMailInfoDeq;
class crJXJChatMessageInfo : public CRCore::Referenced
{
public:
	crJXJChatMessageInfo(const std::string& sender,const std::string &text,unsigned char senderShili,unsigned char broadcastShili,int groupid = 0):
	m_sender(sender),m_text(text),m_senderShili(senderShili),m_broadcastShili(broadcastShili),m_groupid(groupid),m_leaderid(0),m_senderplayerid(0){}
	const std::string &getSender(){ return m_sender; }
	const std::string &getText(){ return m_text; }
	unsigned char getSenderShiliID(){ return m_senderShili; }
	unsigned char getBroadcastShiliID(){ return m_broadcastShili; }
	int getGroupID(){ return m_groupid; }
	void setLeaderID(int leaderid){ m_leaderid = leaderid; }
	int getLeaderID(){ return m_leaderid; }
	void setRecvName(const std::string &name){ m_recvName = name; }
	const std::string &getRecvName(){ return m_recvName; }
	void setSenderID(int playerid){ m_senderplayerid = playerid; }
	int getSenderID(){ return m_senderplayerid; }
protected:
	std::string m_sender;
	std::string m_text;
	unsigned char m_senderShili;
	unsigned char m_broadcastShili;
	int m_groupid;//��������
	int m_leaderid;//�������
	std::string m_recvName;//˽��
	int m_senderplayerid;
};

class crJXJPlayerStoreInfo : public CRCore::Referenced
{
public:
	crJXJPlayerStoreInfo() :m_playerID(0), m_money(0), m_totalmoney(0), m_playerCycleCount(0), m_vipexp(0){}
	int getPlayerId(){return m_playerID;}
	void setPlayerId(int playerid){m_playerID = playerid;}

	int getPlayerMoney(){ return m_money; }
	void setPlayerMoney(int money){ m_money = money; }

	int getTotalMoney(){ return m_totalmoney; }
	void setTotalMoney(int totalmoney){ m_totalmoney = totalmoney; }

	int getVipExp(){ return m_vipexp; }
	void setVipExp(int vipexp){ m_vipexp = vipexp; }

	char getPlayerCycleCount(){ return m_playerCycleCount; }
	void setPlayerCycleCount(short cycleCount){ m_playerCycleCount = cycleCount; }

	JXJStoreItemBagVec & getStoreItemVec(){ return m_itemBagVec; }
	JXJStoreItemBagVec & getStoreCardVec(){ return m_cradBagVec; }
	void setSuper(std::vector<int>&super) { m_super = super; }
	std::vector<int>& getSuper() { return m_super; }
	std::string getSuperStr() { return CRCore::crArgumentParser::appVectoa(m_super); }
protected:
	int m_playerID;
	short m_playerCycleCount;
	int m_money;
	int m_totalmoney;
	int m_vipexp;
	JXJStoreItemBagVec m_cradBagVec;
	JXJStoreItemBagVec m_itemBagVec;
	std::vector<int> m_super;
};

class crPlayerDataQuery : public CRCore::Referenced
{
public:
	crPlayerDataQuery():m_id(0){}
	void setPlayerID(int id){ m_id = id; }
	int getPlayerID() { return m_id; }
	void setAccountName(const std::string &accountname) { m_accountname = accountname; }
	const std::string &getAccountName() const{ return m_accountname; };
	void setLoginDate(const std::string &logindate) { m_logindate = logindate; }
	const std::string &getLoginDate() const{ return m_logindate; };
	void setCreateDate(const std::string &createdate) { m_createdate = createdate; }
	const std::string &getCreateDate() const{ return m_createdate; };
	void setOnlinetime(const std::string &onlinetime) { m_onlinetime = onlinetime; }
	const std::string &getOnlinetime() const{ return m_onlinetime; };
	void setEmail(const std::string &email) { m_email = email; }
	const std::string &getEmail() const{ return m_email; };
protected:
	std::string m_accountname;
	std::string m_logindate;
	std::string m_createdate;
	std::string m_onlinetime;
	std::string m_email;
	int m_id;
};
class crPlayerPayQuery : public CRCore::Referenced
{
public:
	crPlayerPayQuery():m_id(0),m_moneycount(0){}
	void setPlayerID(int id){ m_id = id; }
	int getPlayerID() { return m_id; }
	void setMoneyCount(int moneycount){ m_moneycount = moneycount; }
	int getMoneyCount() { return m_moneycount; }
	void setStr(const std::string &str) { m_str = str; }
	const std::string &getStr() const{ return m_str; };
	void setCreateDate(const std::string &createdate) { m_createdate = createdate; }
	const std::string &getCreateDate() const{ return m_createdate; };
protected:
	std::string m_str;//˵��
	std::string m_createdate;
	int m_id;
	int m_moneycount;
};

typedef std::map<int,CRCore::ref_ptr<crPlayerPayQuery>> PlayerPayMap;//playerid,��ֵ��¼
typedef std::vector<int> TechLvVec;
typedef std::vector<int> BuildingLvVec;
typedef std::map<int,CRCore::ref_ptr<crPlayerDataQuery>> PlayerMap;
typedef std::deque < CRCore::ref_ptr<crJXJChatMessageInfo> > BroadcastMessageDeq;//ȫ���͹�������
typedef std::deque < CRCore::ref_ptr<crJXJChatMessageInfo> > GroupMessageDeq;//��������
typedef std::deque < CRCore::ref_ptr<crJXJChatMessageInfo> > TeamMessageDeq;//�������
typedef std::deque < CRCore::ref_ptr<crJXJChatMessageInfo> > PlayerMessageDeq;//˽��
//typedef std::set <int> ImmediatelySavePlayerSet;
typedef std::multimap< _crInt32,int >GSTeamMap;//(FubenOrChengchiID,FubenOrChengchiType,shiliid),leaderid
typedef std::map<unsigned char,std::set<unsigned short>> RebelCityMap;//shili,chengchiid

typedef std::map< int,CRCore::ref_ptr<crJXJCounterinsurgencyInfo> > CounterInfoMap; // ƽ����Ϣmap 1.playerid 2.ƽ����Ϣ
typedef std::pair<int,CRCore::ref_ptr<crJXJSystermMailInfo>> SystemMailPair;//playerid,
typedef std::deque< SystemMailPair > SystemMailDeque;
typedef std::map <int ,CRCore::ref_ptr<crJXJConsortia>> DismissGroupMap;		// <groupid,dismisstime>

typedef std::pair<int,int> ResourceChangeData;			// ��Դ���ͣ���������

typedef std::deque<CRCore::ref_ptr<crJXJPlayerStoreInfo>> PlayerStoreInfoDeq;//��ʱ�洢��Ϣ

class UIQueryPeopleInfoByLevel : public CRCore::Referenced
{
public:
	UIQueryPeopleInfoByLevel() :m_playerid(0),m_minLv(-1),m_maxLv(-1),m_leftPtr(-1),m_rightPtr(-1)
	{
	}
	int m_playerid;
	unsigned char m_shili;
	unsigned char m_minLv;
	unsigned char m_maxLv;
	unsigned short m_leftPtr;
	unsigned short m_rightPtr;
	unsigned char m_curPage;
	unsigned int m_queryTime;				// �ϴβ�ѯʱ��

};

typedef std::deque<CRCore::ref_ptr<UIQueryPeopleInfoByLevel> > UIQueryPeopleInfoDeq;
typedef std::map<unsigned char,unsigned short > UIQueryFindByMinLvMap;
typedef std::map<unsigned char,unsigned short > UIQueryFindByMaxLvMap;

class ConsortiaLvRankItem : public CRCore::Referenced
{
public:
	ConsortiaLvRankItem(int id):
		m_id(id),m_lv(0), m_shili(0),m_memberCount(0),
		m_troops(0),m_exploit(0)
	{}
	int getKey() const {return m_id;}
	unsigned char m_lv;
	int m_id;
	int m_shili;
	int m_memberCount;
	int m_troops;
	int m_exploit;
	std::string m_groupName;
	std::string m_leaderName;
};

class ConsortiaLvCompare
{
public:
	bool operator() (const CRCore::ref_ptr<ConsortiaLvRankItem > & left,
		const CRCore::ref_ptr<ConsortiaLvRankItem > & right)
	{
		if (left->m_lv == right->m_lv)
		{
			if (left->m_memberCount == right->m_memberCount)
			{
				if (left->m_exploit == right->m_exploit)
				{
					return left->m_troops > right->m_troops;
				}
				return left->m_exploit > right->m_exploit;
			}
			return left->m_memberCount > right->m_memberCount;
		}
		return left->m_lv > right->m_lv;
	}
};

class ConsortiaMemberCountCompare
{
public:
	bool operator() (const CRCore::ref_ptr<ConsortiaLvRankItem > & left,
		const CRCore::ref_ptr<ConsortiaLvRankItem > & right)
	{
		if (left->m_memberCount == right->m_memberCount)
		{
			if (left->m_lv == right->m_lv)
			{
				if (left->m_exploit == right->m_exploit)
				{
					return left->m_troops > right->m_troops;
				}
				return left->m_exploit > right->m_exploit;
			}
			return left->m_lv > right->m_lv;
		}
		return left->m_memberCount > right->m_memberCount;
	}
};

class ConsortiaExploitCompare
{
public:
	bool operator() (const CRCore::ref_ptr<ConsortiaLvRankItem > & left,
		const CRCore::ref_ptr<ConsortiaLvRankItem > & right)
	{
		if (left->m_exploit == right->m_exploit)
		{
			if (left->m_lv == right->m_lv)
			{
				if (left->m_memberCount == right->m_memberCount)
				{
					return left->m_troops > right->m_troops;
				}
				return left->m_memberCount > right->m_memberCount;
			}
			return left->m_lv > right->m_lv;
		}
		return left->m_exploit > right->m_exploit;
	}
};

class ConsortiaTroopsCompare
{
public:
	bool operator() (const CRCore::ref_ptr<ConsortiaLvRankItem > & left,
		const CRCore::ref_ptr<ConsortiaLvRankItem > & right)
	{
		if (left->m_troops == right->m_troops)
		{
			if (left->m_lv == right->m_lv)
			{
				if (left->m_memberCount == right->m_memberCount)
				{
					return left->m_exploit > right->m_exploit;
				}
				return left->m_memberCount > right->m_memberCount;
			}
			return left->m_lv > right->m_lv;
		}
		return left->m_troops > right->m_troops;
	}
};

typedef crJXJRankContainer<CRCore::ref_ptr<ConsortiaLvRankItem>,ConsortiaLvCompare> ConsortialvRank;
typedef crJXJRankContainer<CRCore::ref_ptr<ConsortiaLvRankItem>,ConsortiaMemberCountCompare> ConsortiaMemberCountRank;
typedef crJXJRankContainer<CRCore::ref_ptr<ConsortiaLvRankItem>,ConsortiaExploitCompare> ConsortiaExploitRank;
typedef crJXJRankContainer<CRCore::ref_ptr<ConsortiaLvRankItem>,ConsortiaTroopsCompare> ConsortiaTroopsRank;

class JXJGroupChatMsgBase :public CRCore::Referenced
{
public:
	typedef JXJGroupChatMsgBase Base;
	virtual void getCompleteString(std::string &) = 0;
	virtual void readContent(CRCore::ref_ptr<CRCore::crStreamBuf> & stream);
	virtual void writeContent(CRCore::ref_ptr<CRCore::crStreamBuf> & stream);
	inline CRCore::crHandle * getNoticeHandle();
	unsigned char m_infoType;
	int m_msgId;
};

typedef std::vector<std::pair<int,CRCore::ref_ptr<JXJGroupChatMsgBase> > > GroupChatMsgVec;


class crBattleReportInfo : public CRCore::Referenced
{
public:
	crBattleReportInfo(){}
	void setBattleID(int id){ m_battleid = id; }
	int getBattleID(){ return m_battleid; }

	void setMailTitle(const char * str){ m_strMailTitle= str; }
	std::string &getMailTitle(){ return m_strMailTitle; }

	void setTextInfo(const char * str){ m_strTextInfo = str; }
	std::string & getTextInfo(){ return m_strTextInfo; }

	void setBattleData(CRCore::ref_ptr<CRCore::crStreamBuf>& buffer){ m_dataBuffer = buffer; }
	CRCore::ref_ptr<CRCore::crStreamBuf>& getBattleData(){ return m_dataBuffer; }

	std::vector<int> & getPlayerVec(){ return m_playerVec; }
protected:
	int m_battleid;
	CRCore::ref_ptr<CRCore::crStreamBuf> m_dataBuffer;//ս���������
	std::vector<int> m_playerVec;
	std::string m_strTextInfo;
	std::string m_strMailTitle;
};

typedef std::set<int> OnlinePlayerSet;				// ÿ�յ�½�����id
typedef std::deque< CRCore::ref_ptr<crBattleReportInfo> > InsertBattleReportDeq; //battleid��ս������
typedef std::deque< std::pair<int,int> > QueryBattleReportDeq;//playerid��ս��id
//typedef std::map< int,PersuadeInfoDeq > PersuadeInfoMap;//playerid,˵����Ϣ
typedef std::set< int > NoChatSet;//playerid ����

class crBattleRanking : public CRCore::Referenced
{
public:
	crBattleRanking():m_playerid(0),m_jifeng(0),m_killcount(0),m_deadcount(0),m_exploit(0),m_lingqu(false){}
	void setPlayerID(int playerid){ m_playerid = playerid; }
	int getPlayerID() { return m_playerid; }
	void setName(const std::string &name) { m_name = name; }
	std::string &getName() { return m_name; }
	void addJifeng(int jifeng){ m_jifeng += jifeng; }
	int getJifeng() { return m_jifeng; }
	void addKillCount(int killcount){ m_killcount += killcount; }
	int getKillCount() { return m_killcount; }
	void addDeadCount(int deadcount){ m_deadcount += deadcount; }
	int getDeadCount() { return m_deadcount; }
	void addExploit(int exploit){ m_exploit += exploit; }
	int getExploit() { return m_exploit; }
	void setLingqu(bool lingqu){ m_lingqu = lingqu; }
	int getLingqu() { return m_lingqu; }
protected:
	int m_playerid;
	std::string m_name;//characterName
	int m_jifeng;//�ܻ���
	int m_killcount;//ɱ������
	int m_deadcount;//��������
	int m_exploit;//�ܹ�ѫ
	bool m_lingqu;//�����Ƿ�����ȡ��ʶ
};
typedef std::multimap<int,CRCore::ref_ptr<crBattleRanking>,std::greater<int> >BattleRankingMap;//��ս�������а�,����ս�ܻ�����
class crJXJGameServerData : public CRCore::crData
{//server
public:
	crJXJGameServerData();
	crJXJGameServerData(const crJXJGameServerData& data);
	DataClass(JXJ, JXJGameServer)
	virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	virtual void excHandle(CREPARAM msg);
protected:
	//ExpRankingWaitMap m_expRankingWaitMap;
	//ExpRankingMap m_expRankingWaitMap;
	ExpRankingMap m_shiliExpRanking;//[JXJ_SHILICOUNT];
	//LevelRankingMap m_lvRankingWaitMap;
	LevelRankingMap m_lvRanking;
	//GovpostRankingMap m_govpostRankingWaitMap;
	GovpostRankingMap m_govpostRanking;
	//AccomplishRankingMap m_accomplishRankingWaitMap;
	AccomplishRankingMap m_accomplishRanking;
	//TroopsRankingMap m_troopsRankingWaitMap;
	TroopsRankingMap m_troopsRanking;
	//CountrycontributeRankingMap m_countrycontributeRankingWaitMap;
	CountrycontributeRankingMap m_countrycontributeRankingMap;
	//ManorlvRankingMap m_manorlvRankingWaitMap;
	ManorlvRankingMap m_manorlvRankingMap;
	///�������а�
	ConsortialvRankingMap m_consortialvRankingMap;//
	//ConsortiaMemberRankingMap m_consortiaMemberRankingMap;//
	ConsortialvRank m_consortiaLvRank;
	ConsortiaMemberCountRank m_consortiaMemberCountRank;
	ConsortiaExploitRank m_consortiaexploitRank;
	ConsortiaTroopsRank m_consortiatroopsRank;

	SaleDisposeDeq m_saleDisposeDeq;
	QuerySaleDeque m_querySaleDeq;
	BuySaleDeque m_buySaleDeq;
	bool m_openBattle;//������ս
	int m_battleTimer;//�������ݿ�
	//bool m_openPass; // �����ذ�
	//short m_passTimer; // �ذ���ʱ��
	ChengchiMap m_chengchiMap;
	//bool m_chengchiMapModify;
	DefendDequeMap m_defendDequeMap;
	AttackDequeMap m_attackDequeMap;
	OpenBattleMap m_openBattleMap;
	ClosedBattleSet m_closeBattleSet;//��¼ս������״̬
	BattleScoreMap m_battleScoreMap;
	CreateBattleDeque m_createBattleDeque;
	BattleDropPlayerMap m_battleDropPlayerMap;//
	//CRCore::ref_ptr<CRCore::crStreamBuf> m_dataStream;//��ҵ�¼��ʱ����Ҫ����Щ��Ϣͬ�������
	GNE::Mutex m_dataMutex;
	MailTaskDeque m_mail_sending;
	MailQueryDeque m_mail_query;
	GiftsPackKeySet m_giftsPackKeySet;
	MailQueryDeque m_mailbody_query;
	MailQueryDeque m_maildeletedeq;
	MailQueryDeque m_newmailquerylist;
	CreateGiftsPackDeque m_createGiftsPackDeque;
	QueryGiftsPackDeque m_queryGiftsPacketDeque;
	OnBattleUIPlayerSet m_onBattleUIPlayerSet;
	OnChengfangUIPlayerMap m_onChengfangUIPlayerMap;
	ConsortiaMap m_consortiaMap;
	JXJFubenRushMap m_fubenrushmap;
	ChengchiModifySet m_chengchiModifySet;
	CreateGroupDeq m_creategroupdeq;
	GroupAddMemberDeq m_groupAddMemberDeq;		
	QueryGroupDeq m_querygroupdeq;
	QueryGroupMemberDeq m_querygroupmemberdeq;
	CRCore::ref_ptr<crJXJShili> m_shiliWei;//����id 10
	CRCore::ref_ptr<crJXJShili> m_shiliShu;//����id 11
	CRCore::ref_ptr<crJXJShili> m_shiliWu;//����id 12
	OnCountryQueryMap m_oncountryquerymap;
	SystermMailInfoDeq	m_sysMailDeq;
	//ImmediatelySavePlayerSet m_immediatelySavePlayerSet;
	GSTeamMap m_gsteamMap;
	RebelCityMap m_rebelCityMap;
	bool m_bIsOpenRebel;
	int m_nContinuedRebelTimer;
	//CounterInfoMap m_counterMap;
	unsigned short m_perRebelTimer;
	BroadcastMessageDeq m_sysbroadcastMessageDeq;
	BroadcastMessageDeq m_broadcastMessageDeq;
	GroupMessageDeq m_groupMessageDeq;
	TeamMessageDeq m_teamMessageDeq;
	PlayerMessageDeq m_playerMessageDeq;
	PlayerMap m_checkplayerdatamap;
	int m_checkplayerdataplayerid;
	CRCore::ref_ptr<CRCore::crStreamBuf> m_cfgstream;//���빫��
	JXJCounterMap m_jxjcounterMap;
	SystemMailDeque m_systemMailDeq;
	float m_cycleTimer;//�ֻػ����ڵ���ʱ ��λ��s
	bool m_isCycling;//�ֻ��Ƿ���
	DismissGroupMap m_dismissGroupMap;
	PlayerStoreInfoDeq m_playerStoreInfos;
	PlayerStoreInfoDeq m_playerStoreRecordInfos;

	UIQueryPeopleInfoDeq m_queryPeopleInfoMap;
	GroupChatMsgVec m_groupChatVec;
	bool isChengChiShiliSyn;		// chengChimap �Ƿ�ͬ���� CantonMap		������
	time_t m_groupDayUpdate;
	time_t m_groupWeekUpdate;
	time_t m_shiliDayUpdate;

	InsertBattleReportDeq m_insertBattleReportDeq;//ս���������
	QueryBattleReportDeq m_queryBattleReportDeq;//ս����ѯ����

	NoChatSet m_noChatSet;//
	int m_systemnoticeid;
	OnlinePlayerSet m_onlinePlayerSet;
	time_t m_consortiaPromotion; //���Żˢ��ʱ��
	BattleRankingMap m_battleRankingMapWei;//��ս�������а�
	BattleRankingMap m_battleRankingMapShu;//��ս�������а�
	BattleRankingMap m_battleRankingMapWu;//��ս�������а�
	char m_battleRankingVerWei;
	char m_battleRankingVerShu;
	char m_battleRankingVerWu;
	time_t m_battleRankingSaveTime;
};
class crJXJSceneServerData : public CRNetApp::crSceneServerData
{//sceneserver
public:
	crJXJSceneServerData();
	crJXJSceneServerData(const crJXJSceneServerData& data);
	DataClass(JXJ, JXJSceneServer)
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	virtual void excHandle(CREPARAM msg);
protected:
	NoChatSet m_noChatSet;//
};
class crJXJQueryRankingUIData : public CRCore::crUIData
{//client
public:
	crJXJQueryRankingUIData();
	crJXJQueryRankingUIData(const crJXJQueryRankingUIData& data);
	DataClass(JXJ, JXJQueryRankingUI)
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	virtual void excHandle(CREPARAM msg);
protected:
	//_crInt64 m_lastQueryTime;
	GovpostRankingMap m_govpostRankingMap;
	GNE::Mutex m_dataMutex;
};
typedef std::vector<CRCore::crVector2i> GoodsVec;
class crJXJGoodsRadioUIData : public CRCore::crUIData
{//client
public:
	crJXJGoodsRadioUIData();
	crJXJGoodsRadioUIData(const crJXJGoodsRadioUIData& data);
	DataClass(JXJ, JXJGoodsRadioUI)
	virtual void addParam(int i, const std::string& str);
	virtual void getParam(int i, void*& param);
protected:
	GoodsVec m_goodsVec;
};
typedef std::map<CRCore::crVector2i,int> GoodsStepMap;
class crJXJMarketUIData : public CRCore::crUIData
{//client
public:
	crJXJMarketUIData();
	crJXJMarketUIData(const crJXJMarketUIData& data);
	DataClass(JXJ, JXJMarketUI)
	virtual void addParam(int i, const std::string& str);
	virtual void getParam(int i, void*& param);
protected:
	GoodsStepMap m_goldbuySteps;
	GoodsStepMap m_coppersaleSteps;
};

typedef std::map<char,ItemVec> BattleFormationMap;
typedef std::pair<CRCore::ref_ptr<CRCore::crWidgetNode>, CRCore::crVector3> WidgetNodePair;
typedef std::map< CRCore::ref_ptr<CRCore::crWidgetNode>, float >SignalNodeMap;
typedef std::multimap< std::string, WidgetNodePair >NamedSignalNodeMap;//
//typedef std::vector<CRCore::crVector3> StopSignalVec;

struct NotInSightNode
{
	CRCore::ref_ptr<CRCore::crWidgetNode> m_widget;
	float m_deltaTime;
	int m_id;
	bool m_isEnable;
	NotInSightNode()
	{
		m_id = -1;
		m_deltaTime= 0.0f;
		m_isEnable = false;
	}
};
typedef std::vector<NotInSightNode> SceneNodesVec;
//typedef	std::map<CRCore::ref_ptr<CRCore::crWidgetNode>, float> SceneNodeMap;

typedef std::pair<CRCore::ref_ptr<CRNetApp::crRole>,int> AboutUseItemPair;
typedef std::multimap< char,CRCore::ref_ptr<CRCore::crCanvasNode> > WidgetNodeMap;
typedef std::map< std::string,CRCore::ref_ptr<CRCore::crNode> > SkillRangeNodeMap;
typedef std::vector < CRCore::ref_ptr<CRNetApp::crInstanceItem> > TargetItemVec;
typedef std::vector < CRCore::ref_ptr<CRCore::crWidgetNode> > ButtonVector;
typedef	std::deque <  CRCore::ref_ptr<CRCore::crCanvasNode> > WidgetNodeDeque;
typedef std::map< CRCore::ref_ptr<CRNetApp::crInstanceItem>, float > QueryItemRTHPMap;
class crJXJBattleCameraData : public CRNetApp::crCameraData
{//client
public:
	crJXJBattleCameraData();
	crJXJBattleCameraData(const crJXJBattleCameraData& data);
	DataClass(JXJ, JXJBattleCamera)
	virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
protected:
	CRCore::ref_ptr<CRCore::crNode> m_useSkillDecal;
	//CRCore::ref_ptr<CRCore::crNode> m_useSkillRangeDecal;
	SkillRangeNodeMap m_useSkillRangeNodeMap;
	CRCore::ref_ptr<CRCore::crNode> m_usePreSkillRangeDecal;
	CRCore::ref_ptr<CRCore::crNode> m_usePreSkillDecal;
	BattleFormationMap m_battleFormationMap;
	unsigned short m_cameraOperator;
	SignalNodeMap m_signalDeque;
	NamedSignalNodeMap m_namedSignalMap;
	short m_timer;
	short m_othertimer;
	ItemVec m_mouseonitemVec;
	bool m_isShow;
	unsigned short m_range;
	short m_scope;
	unsigned char m_effectTargetType;
	CRCore::ref_ptr<CRNetApp::crRole> m_role;
	AboutUseItemPair m_useItemPair;
	WidgetNodeMap m_widgetNodeMap;
	//WidgetNodeDeque m_widgetNodeDeque;
	//bool m_bHeadCanvasShow;
	bool m_isFollow;//�������
	TargetItemVec m_targetItemVec;
	CRCore::ref_ptr< CRProducer::crGUIEventAdapter > m_ea;//��¼����״̬
	ButtonVector m_btVec;
	CRCore::ref_ptr<CRCore::crNode> m_msOnShuiJingNode;
	CRCore::ref_ptr<CRCore::crNode> m_msOnJianTaNode;

	SceneNodesVec m_sceneNodeMap;
	float m_campAddArmyTimer;//�ݵ㲹��ʱ�� �������ݿ⣬���ս������ʱ��������
	//bool m_isChangeSpeed;
	float m_cameraSpeed;
	bool m_battleCameraMovable;
	bool m_isSkillKeyDown;
	short m_delayTimer;//������ʾ������ʱ�ر�ʱ�䣬�������ݿ�
	QueryItemRTHPMap m_queryItemRTHPMap;
};
class crJXJEnterBattleUIData : public CRCore::crUIData
{//client
public:
	crJXJEnterBattleUIData();
	crJXJEnterBattleUIData(const crJXJEnterBattleUIData& data);
	DataClass(JXJ, JXJEnterBattleUI)
	virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
protected:
	GNE::Mutex m_dataMutex;
	int m_sceneid;
	int m_timer;
/*	unsigned char m_index;*/
};

typedef std::map< int,int > KillArmyInfoMap;//abstractid , count
class crJXJBattleStats : public CRCore::Referenced
{
public:
	crJXJBattleStats(int playerid,unsigned char shiliid):m_playerid(playerid),m_shiliid(shiliid),m_stats(1),m_kill(0),m_npckill(0),m_bosskill(0),m_bulidingkill(0),m_shadidengji(0),m_deaddengji(0),m_deadbuduic(0),
		m_playerpoints(0),m_zhanshi(true),m_Killedtimes(0),m_zhengtingkill(0),m_towerkill(0),m_doorkill(0){}
	int getPlayerID(){ return m_playerid; }
	unsigned char getShiliID(){ return m_shiliid; }
	void setStats(char stats){ m_stats = stats; }
	char getStats(){ return m_stats; }
	void setKillDengji(char dengji){ m_shadidengji = dengji; }
	char getKillDengji(){ return m_shadidengji; }
	void setDeadDengji(char dengji){ m_deaddengji = dengji; }
	char getDeadDengji(){ return m_deaddengji; }
	void addDeadBuDuiC(int deadbuduic){ m_deadbuduic += deadbuduic; }
	int getDeadBuDuiC(){ return m_deadbuduic; }
	void setPoints(unsigned short points){ m_playerpoints = points; }
	void addPoints(unsigned short points){ m_playerpoints += points; }
	unsigned short getPoint(){ return m_playerpoints; }
	void setShow(bool mark){m_zhanshi = mark; }
	bool getShow(){return m_zhanshi; }
	void addkilledtimes(unsigned char mark){m_Killedtimes += mark; }
	unsigned char getkilledtimes(){return m_Killedtimes; }
	void addKillZhengTing(unsigned char points){ m_zhengtingkill += points; }
	unsigned char getKillZhengTing(){ return m_zhengtingkill; }
	void addKillTower(unsigned char points){ m_towerkill += points; }
	unsigned char getKillTower(){ return m_towerkill; }
	void addKillDoor(unsigned char points){ m_doorkill += points; }
	unsigned char getKillDoor(){ return m_doorkill; }
	void addKillArmyCount(int abstractid,int kill)
	{
		KillArmyInfoMap::iterator itr_info = m_killArmyInfoMap.find(abstractid);
		if(itr_info!=m_killArmyInfoMap.end())
		{
			itr_info->second+=kill;
		}
		else
			m_killArmyInfoMap[abstractid] = kill;
	}
	KillArmyInfoMap & getKillArmyInfoMap(){ return m_killArmyInfoMap; }
	void addKillCount(int kill){m_kill += kill;}
	int getKillCount(){return m_kill;}
	void addDeadMap(int abstractid,int dead)
	{ 
		KillArmyInfoMap::iterator itr_info = m_deadInfoMap.find(abstractid);
		if(itr_info!=m_deadInfoMap.end())
		{
			itr_info->second+=dead;
		}
		else
			m_deadInfoMap[abstractid] = dead;
	}
	KillArmyInfoMap & getDeadCount(){ return m_deadInfoMap; }
	void addNpcKillCount(int npckill){ m_npckill += npckill; }
	int getNpcKillCount(){ return m_npckill; }
	void addBossKillCount(int bossCount){m_bosskill += bossCount;}
	int getBosskillCount(){return m_bosskill;}
	void addNpcKillArmyCount(int abstractid,int npckill)
	{ 
		KillArmyInfoMap::iterator itr_info = m_killNpcArmyMap.find(abstractid);
		if(itr_info!=m_killNpcArmyMap.end())
		{
			itr_info->second+=npckill;
		}
		else
			m_killNpcArmyMap[abstractid] = npckill;
	}
	KillArmyInfoMap & getNpcKillArmyMap(){ return m_killNpcArmyMap; }

	void addBuildingKillArmyCount(int abstractid,int count){ 

		KillArmyInfoMap::iterator itr_info = m_killBuildingArmyMap.find(abstractid);
		if(itr_info!=m_killBuildingArmyMap.end())
		{
			itr_info->second+=count;
		}
		else
			m_killBuildingArmyMap[abstractid] = count; 
	}
	KillArmyInfoMap & getBuildingKillArmyMap(){ return m_killBuildingArmyMap; }

	void addTroopsKillCount(int abstractid,int count){

		KillArmyInfoMap::iterator itr_info = m_bingzhongkillmap.find(abstractid);
		if(itr_info!=m_bingzhongkillmap.end())
		{
			itr_info->second+=count;
		}
		else
			m_bingzhongkillmap[abstractid] = count; 
	}
	KillArmyInfoMap & getTroopsKillMap(){ return m_bingzhongkillmap; }

	void addBuildingKillCount(int kill){m_bulidingkill+=kill;}
	int getBuildingKillCount(){return m_bulidingkill;}
	std::string getPlayerName(){return m_playername;}
	void  setCharacterName(std::string &name){m_playername = name;}
protected:
	int m_playerid;
	unsigned char m_shiliid;
	char m_stats;//0��ʾ���ߣ�1��ʾ���ߣ�2��ʾ��������
	int m_kill;//ɱ��Ҳ�������
	KillArmyInfoMap m_deadInfoMap;//��������
	int m_npckill;//ɱ��NPC����
	int m_bosskill;//ɱ��boss��
	KillArmyInfoMap m_killBuildingArmyMap;//�ݻٽ�������
	int m_bulidingkill;//�ݻٽ�����λ���� 
	KillArmyInfoMap m_killArmyInfoMap;//ɱ����ұ���
	KillArmyInfoMap m_killNpcArmyMap;//ɱ��NPC����
	std::string m_playername;//20
	char m_shadidengji;
	char m_deaddengji;
	int m_deadbuduic; //���������������
	unsigned short m_playerpoints; //����ս������ҵĻ���
	bool m_zhanshi;                //����ս�������а��ܷ�չʾ��־
	unsigned char m_Killedtimes;   //����ɱ�Ĵ���
	unsigned char m_zhengtingkill;   //������������
	unsigned char m_towerkill;   //���Ƽ�������
	unsigned char m_doorkill;   //���Ƴ�������
	KillArmyInfoMap m_bingzhongkillmap; //��ұ��ֻ�ɱ����
};
typedef std::map< int,CRCore::ref_ptr<crJXJBattleStats> > BattleStatsMap;//playerid

struct RecruitCheckResult
{
	RecruitCheckResult():
		m_code(0),
		m_bingyinglvNeed(0),
		m_stationidNeed(0),
		m_timeNeed(0.0f),
		m_equipid(0),
		m_equipCount(0),
		//m_coppercashNeed(0),
		//m_foodNeed(0),
		m_maxRecruitCount(0)
	{}
	char m_code;//0������ļ��1������-1������������, -2�����������ޣ�-3�����ȼ����㣬 -4פ������, -5û����ļʱ�䣬-6װ�����㣬-7��ʳ���㣬-8ľ�Ĳ��㣬-9�����㣬-10��ƥ���㣬-11ͭǮ���㣬-12������ļ
	unsigned char m_bingyinglvNeed;
	int m_stationidNeed;
	float m_timeNeed;
	unsigned short m_equipid;
	int m_equipCount;
	//int m_coppercashNeed;
	//int m_foodNeed;
	int m_maxRecruitCount;//������ļ����
	std::vector<int> m_needjunbeivec;//��Ҫ�����Ƽ�����
	std::vector<float> m_needresourcevec;//��Ҫ��Դ
};

// �ذ��е�checkpoint ���ֵ�����
class PassCheck : public CRCore::Referenced
{
public:
	PassCheck():m_type(-1),m_score(0),m_pos_x(0.0f),m_pos_y(0.0f),m_area(0.0f){}
	void setType(char type){m_type = type;}
	char getType(){return m_type;}
	void setScore(short score){m_score = score;}
	short getScore(){return m_score;}
	void setPosX(float x){m_pos_x = x;}
	float getPosX(){return m_pos_x;}
	void setPosY(float y){m_pos_y = y;}
	float getPosY(){return m_pos_y;}
	void setArea(float area){m_area = area;}
	float getArea(){return m_area;}
protected:
	virtual ~PassCheck(){}
	char  m_type;	//�ݵ�����---0.���� 1. �ذ�
	short m_score; // ��ǰռ��ֵ -limit ---- limit ����Ϊ������ ����Ϊ���ط�
	float m_pos_x; // �����x
	float m_pos_y; // �����y
	float m_area; // ���÷�Χ
};

typedef std::vector< CRCore::ref_ptr<PassCheck> > PassCheckVec;
class crJXJReliveItem : public CRCore::Referenced
{
public:
	crJXJReliveItem():m_instanceid(0),m_count(0),m_hpscale(1.0f),m_attackscale(1.0f),m_camp(1){}
	void setInstanceID(int instanceid) { m_instanceid = instanceid; }
	int getInstanceID(){ return m_instanceid; }
	void setCount(unsigned short count){ m_count = count; }
	unsigned short getCount(){ return m_count; }
	void setHPScale(float hpscale){ m_hpscale = hpscale; }
	float getHPScale(){ return m_hpscale; }
	void setAttackScale(float attackscale){ m_attackscale = attackscale; }
	float getAttackScale(){ return m_attackscale; }
	void setName(std::string name){m_name = name;}
	std::string getName(){return m_name;}
	void setCamp(unsigned char camp){ m_camp = camp; }
	unsigned char getCamp(){ return m_camp; }
	void setNpcItemType(unsigned char type){m_npcItemType = type;}
	unsigned char getNpcItemType(){return m_npcItemType;}
protected:
	int m_instanceid;
	std::string m_name;
	unsigned short m_count;
	float m_hpscale;
	float m_attackscale;
	unsigned char m_camp;//0:������1���أ�2����
	unsigned char m_npcItemType;
};
typedef std::multimap< short,CRCore::ref_ptr<crJXJReliveItem> > ReliveItemMap;
typedef std::set<short> SaveProgressSet;

typedef std::map<CRCore::crVector3i,std::string> JXJCampBirthpoint;
typedef std::map<unsigned char,JXJCampBirthpoint> JXJCampBirthpointMap;//shiliid
typedef std::map<int,char> BattleInspireMap;		//playerid,�������
typedef std::map<int,_crInt64> CampAddArmyTimerMap;//playerid,ʱ���
struct crJXJScenarioTimer : public CRCore::Referenced
{
	crJXJScenarioTimer(int msg,float interval,int times):m_msg(msg),m_interval(interval),m_times(times),m_timer(interval){}
	int m_msg;
	float m_interval;
	float m_timer;//����ʱ
	int m_times;//-1��ʾ����
};
//typedef std::multimap<int, crJXJScenarioTimer >ScenarioTimerMap;//id,msg,ʱ�䣬������������1��ʾ����,0��ʾδ���ã�
typedef std::map<int, CRCore::ref_ptr<crJXJScenarioTimer> >ScenarioTimerMap;//id,msg,ʱ�䣬������������1��ʾ����,0��ʾδ���ã�
typedef std::map<int, unsigned char> FubenStarMap;//playerid,stars
typedef std::map<unsigned char, int> NpcTotalCountMap;//shiliid,count
typedef std::map<std::string, float>ScenarioVariableMap;//nameid,value
//typedef std::set<int> PlayerSet;//����PVP��Ӫ����
//typedef std::map<unsigned char,PlayerSet> PVPCampMap;//����PVP��Ӫ����
typedef std::map<_crInt64, CRCore::crVector2f>PlayerCoordMap;//����ս��ͬ������������λ�ã�playerid,roleid,����x,y
class crJXJBattleRoomData : public CRNetApp::crRoomData
{//client
public:
	crJXJBattleRoomData();
	crJXJBattleRoomData(const crJXJBattleRoomData& data);
	DataClass(JXJ, JXJBattleRoom)
	virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
protected:
	int m_battleid;//��������ID���ط�����ID���ǳ�ID������ʱ����������ID��Ⱥ����ID��fubenid��
	BattleStatsMap m_battleStatsMap;
	//std::string m_checks_tabname;
	//short m_red_remain; // �췽���ݻ���
	//short m_blue_remain; // �������ݻ���
	//PassCheckVec m_checks; // ���� - ��������
	//bool m_modified;
	//bool m_is_init;
	//char m_isPassCapture;		//�ذ��Ƿ�ռ�� 0���� -1 �췽ռ�� 1����ռ��
	ReliveItemMap m_reliveItemMap;
	SaveProgressSet m_saveProgressSet;
	unsigned char m_roomType;//1:��վ��2:������3:����ս��
	JXJCampBirthpointMap m_roomCampMap;
	BattleInspireMap m_battleInspireMap;
	int m_getFirstBloodPlayerId;//���һѪ���
	CampAddArmyTimerMap m_campTimerMap;
	ScenarioTimerMap m_scenarioTimerMap;
	FubenStarMap m_fubenStarMap;
	NpcTotalCountMap m_totalNpcCount;//ս����NPC��
	ScenarioVariableMap m_scenarioVariableMap;
	CRCore::crVector2i m_battleRbuffId;//�����������ID,�ط��������ID
	//PVPCampMap m_pvpcampmap;//��ӪID,  ��Ӫplayerid SET
	PlayerCoordMap m_playerCoordMap;//ֻ������ս���ͻ�����������ݣ�����ս��ͬ������������λ��
	unsigned short m_weipoints;  //ֻ������ս���У�κ������
	unsigned short m_shupoints;  //ֻ������ս���У��������
	unsigned short m_wupoints;   //ֻ������ս���У��������
	std::map<int,std::set<int>> m_praisedid;  //����ս���б�������޹����������
	unsigned char m_temhuodong;   //��ǰ�
};
//////////////////////////////////////////////////////////////////////////
typedef std::vector< CRCore::ref_ptr<crBagItemData> > RewardItemVec;//int,unsigned char,unsigned char
typedef std::map<int, CRCore::ref_ptr<crBagItemData> > DeductItemMap;//int,unsigned char,unsigned char
//typedef std::map< int,CRCore::ref_ptr<crBagItemData> > RewardItemMap;
typedef std::vector< std::pair<unsigned short,int> > RewardEquipsVec;
typedef std::vector< std::pair<unsigned char, CRCore::crVector3i> > FubenDropRewardVec;//typeid,itemid/equipid/resid,equipmagic,count �ӽ����е��䣬ѡȡ����һ��
class crPlayerRewardData : public CRCore::Referenced
{//client
public:
	crPlayerRewardData():m_type(GP_RewardGameEnd),m_playerid(0),m_coopercash(0),m_exploit(0),m_exprience(0),m_achievement(0),m_food(0),
		m_wood(0), m_iron(0), m_horse(0), m_giftGold(0), m_junling(0), m_countrycontribution(0), m_freerollcardcount(0), m_freerefinecount(0),m_score(0),m_huoyuedu(0),
		m_warcounts(false), m_groupcontribute(0)
	{
		//m_rewardItems.resize(0);
		//m_equips.resize(0);
	}
	crPlayerRewardData(crPlayerRewardData* data):
		m_type(data->m_type),m_playerid(data->m_playerid),m_coopercash(data->m_coopercash),m_exploit(data->m_exploit),m_exprience(data->m_exprience),
		m_achievement(data->m_achievement),m_food(data->m_food),m_wood(data->m_wood),m_iron(data->m_iron),m_horse(data->m_horse),m_giftGold(data->m_giftGold),
		m_junling(data->m_junling),m_countrycontribution(data->m_countrycontribution),
		m_rewardItems(data->m_rewardItems),m_equips(data->m_equips),m_keyWord(data->m_keyWord),
		m_fubenDropVec(data->m_fubenDropVec),
		m_freerollcardcount(data->m_freerollcardcount),
		m_freerefinecount(data->m_freerefinecount),
		m_score(data->m_score),
		m_huoyuedu(data->m_huoyuedu),
		m_warcounts(data->m_warcounts),
		m_groupcontribute(data->m_groupcontribute)
	{
	}
	void setPlayerID(int playerid){m_playerid = playerid;}
	int getPlayerID(){return m_playerid;}
	void setCoopercash(int coopercash){m_coopercash = coopercash;}
	int getCooperCashReward(){return m_coopercash;}
	void setExploit(int exploit){m_exploit = exploit;}
	int getExploit(){return m_exploit;}
	void setExperience(int experience){m_exprience = experience;}
	int getExperience(){return m_exprience;}
	void setAchievement(int achievement){m_achievement = achievement;}
	int getAchievement(){return m_achievement;}
	//void setRewadItemsVec(RewardItemVec& rewardItem){m_rewardItems = rewardItem;}
	RewardItemVec& getRewardItemsVec(){return m_rewardItems;}
	void setType(unsigned char type){m_type = type;}
	unsigned char getType(){return m_type;}
	void setKeyWord(std::string key){m_keyWord = key;}
	std::string &getKeyWord(){return m_keyWord;}
	void setFood(int food ){m_food = food;}
	int getFood(){return m_food;}
	void setWood(int wood){m_wood = wood;}
	int getWood(){return m_wood;}
	void setIron(int iron){m_iron = iron;}
	int getIron(){return m_iron;}
	void setHorse(int horse){m_horse = horse;}
	int getHorse(){return m_horse;}
	void setGiftgold(int giftgold){m_giftGold = giftgold;}
	int getGiftgold(){return m_giftGold;}
	//void setEquipsVec(RewardEquipsVec equips){m_equips = equips;}
	RewardEquipsVec& getEquipsVec(){return m_equips;}
	//void setFubenDropItems(FubenDropRewardVec dropitem){m_fubenDropItems = dropitem;}
	FubenDropRewardVec &getFubenDropVec(){return m_fubenDropVec;}
	void setJunling(int junling){m_junling = junling;}
	unsigned char getJunling(){return m_junling;}
	void setCountryContribution(int countrycontribution){m_countrycontribution = countrycontribution;}
	int getCountryContribution(){return m_countrycontribution;}
	void setGroupContribution(int value){ m_groupcontribute = value; }
	int getGroupContribution(){ return m_groupcontribute; }
	void buildGiftStream(CRCore::ref_ptr<CRCore::crStreamBuf> &stream);
	void setGiftDataStream(CRCore::crStreamBuf *stream);
	void parseRewardItemCount(int &cardcount,int &itemcount);
	void setTimer(time_t time){m_startTimer = time;}
	time_t getTimer(){return m_startTimer;}
	std::string &getDescribtion(){ return m_describtion; }
	void setFreerollcardcount(int freerollcardcount){ m_freerollcardcount = freerollcardcount; }
	unsigned char getFreerollcardcount(){ return m_freerollcardcount; }
	void setFreerefinecount(int freerefinecount){ m_freerefinecount = freerefinecount; }
	unsigned char getFreerefinecount(){ return m_freerefinecount; }
	void setScore(int score){m_score = score;}
	int getScore(){return m_score;}
	void setHuoyuedu(char huoyuedu){m_huoyuedu = huoyuedu;}
	char getHuoyuedu(){return m_huoyuedu;}
	void setwarcounts(bool var){m_warcounts = var;}
	bool getwarcounts(){return m_warcounts;}
protected:
	unsigned char m_type;			//��������
	int m_playerid;					//���ID
	int m_coopercash;				//��Ǯ
	int m_exploit;					//��ѫ
	int m_exprience;				//����
	int m_achievement;				//ս��
	int m_food;						//ʳ��
	int m_wood;						//ľ��
	int m_iron;						//����
	int m_horse;					//��ƥ
	int m_giftGold;					//���
	unsigned char m_junling;		//����//��Ҫȥ��
	int m_countrycontribution;		//���ҹ���
	RewardItemVec m_rewardItems;	//������Ʒ
	RewardEquipsVec m_equips;		//T_TroopsEquip
	std::string m_keyWord;			//���KEY
	FubenDropRewardVec m_fubenDropVec;//�������佱��,��ʱ����
	time_t m_startTimer;				//������������������ʱ��
	std::string m_describtion;		//��������
	unsigned char m_freerollcardcount;//��ѳ齫������
	unsigned char m_freerefinecount;//��Ѿ�������
	int  m_score;                   //��ս����
	char m_huoyuedu;
	bool m_warcounts;				//��ս�����Ƿ�+1
	int m_groupcontribute;//���Ź���
};

class crJXJUIGiftsPackMailHyperData :  public CRCore::crUIData
{
public:
	crJXJUIGiftsPackMailHyperData();
	crJXJUIGiftsPackMailHyperData(const crJXJUIGiftsPackMailHyperData& data);
	DataClass(JXJ, JXJUIGiftsPackMailHyper)
	virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
protected:
	std::string m_keyWords;
	RewardItemVec m_packItemVec;
	int m_reportId;
};
class crJXJNewHandUIData :  public CRCore::crUIData
{//GameClient Method
public:
	crJXJNewHandUIData();
	crJXJNewHandUIData(const crJXJNewHandUIData& data);
	DataClass(JXJ, JXJNewHandUI)
	virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
protected:
	GNE::Mutex m_dataMutex;
	int m_newHandTaskid;
	std::string m_targetCanvasName;
	std::string m_targetWidgetName;
};

typedef std::map<int,int> GroupChengChiEarningMap;					//�������� ����,����

class crJXJConsortiaMember : public CRCore::Referenced
{
public:
	crJXJConsortiaMember(int playerid):m_playerid(playerid),m_lv(0),m_pos(0),m_grouppos(0),m_ifonline(0),
		m_curWeekActiveVal(0),m_lastWeekActiveVal(0),m_todayActiveVal(0),m_tribute(0),
		m_yesterdayActiveVal(0),m_getEarningsYesterday(true),
		m_curFuBen(0),m_curFuBenTimes(0),m_curFuBenValidTimes(0),m_curFuBenAchievement(0),
		m_curFuBenActiveVal(0),m_curFuBenCountryContribute(0),m_curFuBenExp(0),
		m_curFuBenExploit(0),m_curFuBenGroupFunds(0),m_newer(true),m_loginTime(time(0)),
		m_groupcontribute(0),m_troopstorednumT(0),m_trooptakednumT(0),m_curFuBenGroupContribute(0),
		m_fubencircle(0.0f)
	{ m_groupcantonspecialtyVec.resize(8); }
	unsigned char getGroupPos() const {return m_grouppos;}
	unsigned char getIfOnline() const {return m_ifonline;}
	unsigned char getLevel() const {return m_lv;}
	unsigned char getPos() const{return m_pos;}
	//unsigned char getContributeTimes() {return m_contributeTimes;}
	//unsigned char getContributeType() const {return m_contributeType;}

	void setName(const std::string &name){m_playername = name;}
	void setLevel(unsigned char lv){m_lv = lv;}
	void setPos(unsigned char pos){m_pos = pos;}
	void setTime(_crInt64 applytime){m_applytime = applytime;}
	void setGroupPos(unsigned char grouppos){m_grouppos = grouppos;}
	void setIfOnlie(unsigned char ifonline){m_ifonline = ifonline;}
	void setTribute(int tribute){m_tribute = tribute;}
	void setActiveValue(int activeValue) {m_todayActiveVal = activeValue;}
	void setLastWeekActive(int val) {m_lastWeekActiveVal = val;}
	void setTodayWeekActive(int val) {m_curWeekActiveVal = val;}
	void setYesterdayActive(int val) {m_yesterdayActiveVal = val;}
	void setEarningsYesterday(bool val) {m_getEarningsYesterday = val;}
	void setNewer(bool val) {m_newer = val;}
	void setLoginTime(time_t time) {m_loginTime = time;}
	void setGroupContribute(int groupcontribute) {m_groupcontribute = groupcontribute;}
	void setTroopStoredNumT(int num) {m_troopstorednumT = num;}
	void setTroopTakedNumT(int num) {m_trooptakednumT = num;}
	void dayZero();
	void weekZero();
	void clearJunTuanFuBenInfo() 
	{
		m_curFuBen = 0,m_curFuBenAchievement = 0,m_curFuBenActiveVal = 0,
		m_curFuBenCountryContribute = 0,m_curFuBenExp = 0,
		m_curFuBenExploit = 0,m_curFuBenGroupFunds = 0,
		m_curFuBenTimes = 0,m_curFuBenValidTimes = 0,m_curFuBenGroupContribute = 0;
		m_fubencircle = 0.0f;
	}

	_crInt64 getTime()const {return m_applytime;}
	time_t getLoginTime() {return m_loginTime;}
	int getTribute() const {return m_tribute;}
	int getPlayerID() const { return m_playerid; }
	int getActiveVaule( ) const {return m_todayActiveVal;}
	int getLastWeekActive() const {return m_lastWeekActiveVal;};
	int getTodayWeekActive() {return m_curWeekActiveVal ;}
	int getYesterdayActive() {return m_yesterdayActiveVal;}
	bool getEarningsYesterday() {return m_getEarningsYesterday;}
	bool getNewer() {return m_newer;}
	int getGroupContribute() {return m_groupcontribute; }
	int getTroopStoredNumT() {return m_troopstorednumT; }
	int getTroopTakedNumT() {return m_trooptakednumT; }
	GroupCantonSpecialtyVec & getGroupCantonSpecialtyVec() {return m_groupcantonspecialtyVec;}
	void clearGroupcantonspecialtyVec()
	{
		for( GroupCantonSpecialtyVec::iterator itr = m_groupcantonspecialtyVec.begin();
			itr != m_groupcantonspecialtyVec.end();
			++itr )
		{
			*itr = NULL;
		}
	}
	bool isGroupcantonspecialtyVecempty()
	{
		for( GroupCantonSpecialtyVec::iterator itr = m_groupcantonspecialtyVec.begin();
			itr != m_groupcantonspecialtyVec.end();
			++itr )
		{
			if(*itr != NULL)
				return false;
		}
		return true;
	}
	GroupChengChiEarningMap & getGroupChengChiEarningMap() {return m_groupchengchiearningMap;}

	std::string &getName() {return m_playername;}

	bool m_getEarningsYesterday;			// ���������Ƿ��Ѿ���ȡ
	unsigned char m_lv;//�ȼ�
	unsigned char m_pos;//ְλ��ְ
	unsigned char m_grouppos;//����ְλ 
	unsigned char m_ifonline;//����״̬,ֻ�ͻ�����ʹ��
	//unsigned char m_contributeType;			// ��������
	//unsigned char m_contributeTimes;		// ���״���
	unsigned char m_curFuBenTimes;			// ��ǰ���㸱������������
	unsigned char m_curFuBenValidTimes;		// ��ǰ���㸱��������Ч������

	int m_playerid;
	int m_curWeekActiveVal;					// ���ܵ�����Ļ�Ծֵ�ܺ�
	int m_todayActiveVal;					// ����Ļ�Ծֵ
	int m_yesterdayActiveVal;				// ���յĻ�Ծֵ
	int m_lastWeekActiveVal;				// ���ܵĻ�Ծֵ�ܺ�
	int m_curFuBen;							// ��ǰ����ľ��Ÿ���
	int m_curFuBenActiveVal;				// ��ǰ����������Ծֵ
	int m_curFuBenExp;						// ��ǰ������������
	int m_curFuBenAchievement;				// ��ǰ��������ս��
	int m_curFuBenExploit;					// ��ǰ����������ѫ
	int m_curFuBenGroupFunds;				// ��ǰ�������������ʽ�
	int m_curFuBenCountryContribute;		// ��ǰ�����������ҹ���
	int m_curFuBenGroupContribute;			// ��ǰ�����������Ź���
	float m_fubencircle;					// ��ǰ����ͨ�ز���
	int m_tribute;//�Ϲ��ʽ�
	_crInt64 m_applytime;
	int m_groupcontribute;					//���Ź���
	int m_troopstorednumT;					//�����Ѵ�ž��ű����������
	int m_trooptakednumT;					//������ȡ���������� 
	GroupCantonSpecialtyVec m_groupcantonspecialtyVec;	//���Ź�������8����Ʒ
	GroupChengChiEarningMap m_groupchengchiearningMap;	//���ųǳ�����

	std::string m_playername;
	bool m_newer;							// ����ռ���
	time_t m_loginTime;		
};

class crJXJConsortiaApplyMember : public CRCore::Referenced
{
public:
	crJXJConsortiaApplyMember(int playerid):m_playerid(playerid),m_lv(0),m_pos(0){}
	int getPlayerID(){ return m_playerid; }
	void setName(const std::string &name){m_playername = name;}
	std::string &getName(){return m_playername;}
	unsigned char getLevel(){return m_lv;}
	void setLevel(unsigned char lv){m_lv = lv;}
	unsigned char getPos(){return m_pos;}
	void setPos(unsigned char pos){m_pos = pos;}
	void setTime(_crInt64 applytime){m_applytime = applytime;}
	_crInt64 getTime(){return m_applytime;}
protected:
	int m_playerid;
	std::string m_playername;
	_crInt64 m_applytime;
	unsigned char m_lv;//�ȼ�
	unsigned char m_pos;//ְλ
};



//class GroupEarnings : public CRCore::Referenced
//{
//public:
//	GroupEarnings():m_type(0),m_num(0){}
//	~GroupEarnings(){}
//	//short m_earningsScale;	// �������
//	//int m_cantonId;			// ������
//	int m_type;				//  ��������
//	int m_num;				//  ��������
//};

typedef std::vector< CRCore::ref_ptr<crJXJConsortiaApplyMember> > ConsortiaApplyVec;
typedef std::vector < int > GroupLeaderVec;
typedef std::map<int,CRCore::ref_ptr<crJXJConsortiaMember> ,std::greater<int> > ConsortiaMemberMap;//playerid,
typedef std::vector<CRCore::ref_ptr<crJXJConsortiaMember> > ConsortiaMemberVec;
typedef std::map<int,short> ApplyCantonMap;					//  ��������פ������id������
typedef std::map<int,short> FenFengedCantonMap;				//  ���ű��ַ���ݵ�id������
typedef std::set<int> FenFengedChengChiSet;					// ���ű��ַ�ĳǳ�
typedef std::map<int,int> FenFengedChengChiMap;				//���ŷַ����Ա�ĳǳ�	chengchiid�� playerid
//typedef std::set<int> StartedFubenSet;
//typedef std::vector< CRCore::ref_ptr<GroupEarnings> > GroupEarningsVec;				// ��������
typedef std::map<int,unsigned char> ConsortiaPlayerReliveCount;//playerid,�������
typedef std::map<unsigned short,std::pair<int,ConsortiaPlayerReliveCount> > StartedFubenMap;//����id �� roomid����Ҹ������

class ConsortiaActiveRankItem : public CRCore::Referenced
{
public:
	ConsortiaActiveRankItem(int id):
	m_groupPos(0),m_id(id),m_activeVal(0)
	{}
	~ConsortiaActiveRankItem(){}
	int getKey() const {return m_id;}
	unsigned char m_groupPos;
	int m_id;
	int m_activeVal;
	std::string m_name;
};

class GroupActiveValueCompare
{
public:
	bool operator ()(const CRCore::ref_ptr<ConsortiaActiveRankItem> & left,
		const CRCore::ref_ptr<ConsortiaActiveRankItem> & right) 
	{
		if (left->m_activeVal == right->m_activeVal)
			return left->m_groupPos > right->m_groupPos;
		return left->m_activeVal > right->m_activeVal;
	}
};

typedef crJXJRankContainer<CRCore::ref_ptr<ConsortiaActiveRankItem>,GroupActiveValueCompare> ConsortiaActiveRank;

class ConsortiaMemberRankItem: public ConsortiaActiveRankItem
{
public:
	ConsortiaMemberRankItem(int id):ConsortiaActiveRankItem(id),m_level(0){}
	void fullOfData(crJXJConsortiaMember * memberinfo)
	{
		m_id = memberinfo->getPlayerID();
		m_activeVal = memberinfo->getTodayWeekActive();
		m_groupPos = memberinfo->getGroupPos();
		m_level = memberinfo->getLevel();
		m_name = memberinfo->getName();
		m_govPos = memberinfo->getPos();
	}
	unsigned char m_level;
	int m_govPos;
};

class GroupMemberRankCompare
{
public:
	bool operator () (const CRCore::ref_ptr<ConsortiaMemberRankItem > & left,
		const CRCore::ref_ptr<ConsortiaMemberRankItem > & right)
	{
		if (left->m_groupPos == right->m_groupPos)
		{
			if (left->m_level == right->m_level)
			{
				return left->m_activeVal > right->m_activeVal;
			}
			return left->m_level > right->m_level;
		}
		return left->m_groupPos > right->m_groupPos;
	}
};
typedef crJXJRankContainer<CRCore::ref_ptr<ConsortiaMemberRankItem>,GroupMemberRankCompare > ConsortiaMemberRank;
typedef std::deque<std::string> ConsortiaRecordsDeq;

class crJXJConsortiaData :  public CRCore::crData
{//GameServer & GameClient Method
public:
	crJXJConsortiaData();
	crJXJConsortiaData(const crJXJConsortiaData& data);
	DataClass(JXJ, JXJConsortia)
	virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	virtual void excHandle(CREPARAM msg);
	JXJGroupPos getGroupPos(int playerid);
	void dayZero();
	void weekZero();
	void twoSecZero();
	void clearRankCache();
	void settleEarnings();

	static  void split( std::string str,std::string pattern ,std::vector<std::string> &);
protected:
	//CRCore::ref_ptr<CRCore::crStreamBuf> m_dataStream;
	bool m_modify;//�������ݿ�
	bool m_yesterdayIsCantonGroup;			// �����Ƿ������ؾ���
	unsigned char m_lv;//���ŵȼ�
	unsigned char m_manorlevel;//��صȼ�
	unsigned char m_barrackslevel;//��Ӫ�ȼ�
	unsigned char m_shiliid;//��������ID
	short m_earningsScaleY;					// �����������
	short m_earningsScaleT;					// �����������
	short m_totalChengChiNum;				// �ܵı�ռ��ǳ���
	
	int m_funds;		// �����ʽ�
	int m_dismissTime;				// -1 δ��ɢ >=0 ��ɢ����ʱ
	int m_totalActiveValY;				// ���ճ�Ա��Ծֵ�ܺ�

	std::string m_recruitNotice;		// ��ļ����
	std::string m_contactNotice;		// ��ϵ����
	std::string m_notice;				// һ�㹫��
	std::string m_groupName;			// ��������
	std::string m_fengyi;				// ���ŷ���

	static GNE::Mutex m_saveMutex;
	GNE::Mutex m_dataMutex;
	ConsortiaMemberMap m_consortiaMemberMap;
	ConsortiaActiveRank m_activeRank;				// �ܻ�Ծֵ����
	ConsortiaApplyVec m_applyvec;							//�����б�
	GroupLeaderVec m_groupLeaderVec;				// ���ų������ų� 0 ���ų���1 ���ų���2 ���ų�
	/*StartedFubenSet m_startedFuBenSet;*/				// �Ѿ������ĸ���
	StartedFubenMap m_startedFuBenMap;				////����id �� roomid����Ҹ������

	FenFengedCantonMap m_fenFengedCantonMapT;		// ���ص��� �� ���� ����
	FenFengedCantonMap m_fenFengedCantonMapY;		// ���ص��� �� ���� ���� 
	ApplyCantonMap m_applyCantonMapT;				// ����פ�����ݣ������� ����
	ApplyCantonMap m_applyCantonMapY;				// ����פ�����ݣ������� ���� 
	FenFengedChengChiSet m_fenFengedChengChiSet;	// ���ַ�ĳǳ�
	/*GroupEarningsVec m_earningsVec;	*/				// ��������
	ConsortiaMemberRank m_memberRank;				// ������ʾ�����洢
	_crInt64 m_dayLastUpdate;							// �ϴθ���ʱ��
	_crInt64 m_weekLastUpdate;						// �ϴ��ܸ���ʱ��
	unsigned char m_conquest;						//��������ֵ ����Ϊ7
	TroopsMap m_grouptroopsMap;						//���ű���
	FenFengedChengChiMap m_fenFengedChengChiMap;	//���ŷַ����Ա�� �ǳ�id ��playerid
	ConsortiaRecordsDeq m_consortiarecordsDeq;		//���Ŵ�ȡ����¼
};

class ChengChiEarnings : public CRCore::Referenced
{
public:
	ChengChiEarnings(int groupid);
	int getGroupId() {return m_cantonGroupId;}
	int getChengChiId() {return m_chengChiId;}
	void setChengChiId(int id) {m_chengChiId = id;}
	short getEarnings() {return m_earnings;}
	void setEarnings(short earnings) {m_earnings = earnings;}

	int m_cantonGroupId;				// פ���ľ���id
	int m_chengChiId;			// �ǳ� id ����Ϊ0 ˵��û�з��� �ǳ�
	short m_earnings;				// �������
};

typedef std::map<int,CRCore::ref_ptr<ChengChiEarnings>> ChengChiEarningsMap;//consortiaID

class Canton:public CRCore::Referenced
{
public:
	Canton();
	void setCantonId(int id) {m_cantonId = id;}
	int getCantonId() {return m_cantonId;}
	void setConsortiaId(int id) {m_consortiaID = id;}
	int getConsortiaId() {return m_consortiaID;}
	short reCalculateEarnings();
	ChengChiEarningsMap & getChengChiEarningsMap() {return m_chengChiEarningsMap;}
	int m_cantonId;
	int m_consortiaID;//�ݳ�����
	ChengChiEarningsMap m_chengChiEarningsMap;
};
typedef std::vector<int> SuperEquipExpVec;
class PeopleInfo : public CRCore::Referenced
{
public:
	PeopleInfo(int id,const std::string & name,unsigned char shili):m_id(id),m_name(name),m_shili(shili)
	{
		m_lv = 1;
		m_troopsLv = 0;
		m_consortiaId = 0;
		m_isSmallAcc = false;
		m_killNum = 0;
		m_newerStep = 0;
		m_deadTroopsNum = 0;
		m_giftGold = 0;
		m_totalRecharge = 0;
		m_troopsnum = 0;
		m_exploit = 0;
	}
	PeopleInfo()
	{
		m_id = 0;
		m_lv = 1;
		m_troopsLv = 0;
		m_consortiaId = 0;
		m_isSmallAcc = false;
		m_killNum = 0;
		m_newerStep = 0;
		m_deadTroopsNum = 0;
		m_shili = 0;
		m_giftGold = 0;
		m_totalRecharge = 0;
		m_troopsnum = 0;
		m_exploit = 0;
	}
	PeopleInfo( const PeopleInfo & info)
	{
		m_isSmallAcc = info.m_isSmallAcc;
		m_lv = info.m_lv;
		m_troopsLv = info.m_troopsLv;
		m_id = info.m_id;
		m_consortiaId = info.m_consortiaId;
		m_killNum = info.m_killNum;
		m_name = info.m_name;
		m_consortiaName = info.m_consortiaName;
		m_deadTroopsNum = info.m_deadTroopsNum;
		m_shili = info.m_shili;
		m_giftGold = info.m_giftGold;
		m_troopsnum = info.m_troopsnum;
		m_exploit = info.m_exploit;
	}

	void setSamllAcc(bool smallAcc,bool forceModify = true) { if(m_isSmallAcc == smallAcc) return; m_isSmallAcc = smallAcc; if (forceModify) needUpdate(); }
	void setLv(unsigned char lv,bool forceModify = true) { if(m_lv == lv) return; m_lv = lv; if (forceModify) needUpdate();}
	void setTroopsLv(unsigned char lv,bool forceModify = true) { if(m_troopsLv == lv) return; m_troopsLv = lv; if (forceModify) needUpdate();}
	void setConsortiaID(int id,bool forceModify = true) { if(m_consortiaId == id) return; m_consortiaId = id; if (forceModify) needUpdate();}
	void setKillNum(int num,bool forceModify = true) { if(m_killNum == num) return; m_killNum = num; if (m_killNum < 0) m_killNum = 0;if (forceModify) needUpdate();}
	void setName(const std::string &name,bool forceModify = true) { if(m_name == name) return; m_name = name;if (forceModify) needUpdate();}
	void setConsortiaName(const std::string &name) { if(m_consortiaName == name) return; m_consortiaName = name;}
	void setNewrStep(int step,bool forceModify = true) { if(m_newerStep == step) return; m_newerStep = step; if (forceModify) needUpdate();}
	void setDeadTroopsNum(int num,bool forceModify = true) { if(m_deadTroopsNum == num) return; m_deadTroopsNum = num; if (forceModify) needUpdate();}
	void setID(int id) {m_id = id;}

	void setShili(unsigned char shili) {m_shili = shili;}
	void setGiftGold(int giftGold,bool forceModify = true) { if(m_giftGold == giftGold) return; m_giftGold = giftGold;if (forceModify) needUpdate();}
	void setTotalRecharge(int recharge,bool forceModify = true) { if(m_totalRecharge == recharge) return; m_totalRecharge = recharge;if (forceModify) needUpdate();}
	void setTroopsnum(int num) {m_troopsnum = num; }
	void setExploit(int expolit) {m_exploit = expolit; }
	void setSuperEquipLvupPoint(unsigned char point, bool forceModify = true) { if (m_superEquipLvupPoint == point) return; m_superEquipLvupPoint = point; if (forceModify) needUpdate(); }
	void setSuperEquipExpVec(SuperEquipExpVec &superEquipExpVec, bool forceModify = true) { if (m_superEquipExpVec == superEquipExpVec) return; m_superEquipExpVec = superEquipExpVec; if (forceModify) needUpdate(); }

	bool getSmallAcc() {return m_isSmallAcc;}
	unsigned char getLv() {return m_lv;}
	unsigned char getTroopsLv() {return m_troopsLv;}
	int getID() {return m_id;}
	int getConsortiaId() {return m_consortiaId;}
	int getKillNum() {return m_killNum;}
	const std::string & getName() {return m_name;}
	const std::string & getConsortiaName() {return m_consortiaName;}
	int getNewerStep() {return m_newerStep;}
	int getDeadTroopsNum() {return m_deadTroopsNum;}
	unsigned char getShili() {return m_shili;}
	int getGiftGold() {return m_giftGold;}
	int getTotalRecharge() {return m_totalRecharge;}
	int getTroopsnum() {return m_troopsnum;}
	int getExploit() {return m_exploit;}
	unsigned char getSuperEquipLvupPoint() { return m_superEquipLvupPoint; }
	SuperEquipExpVec& getSuperEquipExpVec() { return m_superEquipExpVec; }
	std::string getSuper()
	{
		return CRCore::crArgumentParser::appItoa(m_superEquipLvupPoint) + "|" + CRCore::crArgumentParser::appVectoa(m_superEquipExpVec,'|');
	}
	void needUpdate();
	void needInsert();

	friend class crJXJShiliData ;
private:
	

	bool m_isSmallAcc;						// �Ƿ񱻱�ǳ�С��
	unsigned char m_lv;						// �ȼ�
	unsigned char m_troopsLv;				// ���ڱ�Ӫ�ȼ�
	int m_id;								// ���id
	int m_consortiaId;						// ����id
	int m_killNum;							// ��սɱ����
	std::string m_name;						// ����
	std::string m_consortiaName;			// ��������		// ���洢
	int m_newerStep;						// �Ѿ���ɵ����ֲ���
	int m_deadTroopsNum;					// ���������ս���������ı�������.
	int m_giftGold;							// ������
	int m_totalRecharge;					// ����ۼƳ�ֵ
	int m_troopsnum;						// ��ҵ�ǰ����
	int m_exploit;							// ��ҵ�ǰ��ѫ
	unsigned char m_superEquipLvupPoint;//�����ȼ��������ע�������1,2,3,4��
	SuperEquipExpVec m_superEquipExpVec;//��������

	unsigned char m_shili;					
};

class PeopleInfoCmp
{
public:
	bool operator() (CRCore::ref_ptr<PeopleInfo> & left,CRCore::ref_ptr<PeopleInfo> right)
	{
		return left->getLv() < right->getLv();
	}
};

typedef std::map <int,CRCore::ref_ptr<Canton> > CantonMap;				// �ݣ��ǳ� ���� ����map
typedef std::deque< unsigned short > ShiliCityChangeDeq;//�ǳ�id
typedef std::map<int,CRCore::ref_ptr<PeopleInfo > > PeopleMap;//playerid
typedef std::vector<CRCore::ref_ptr<PeopleInfo> > PeopleVec;
typedef std::deque< int > PeopleDeq;//playerid
struct strToupiaoInfo :public CRCore::Referenced
{
	int m_rankVal;
	int nPlayerID;
	std::string playerName;
	int nJuntuanID;
	std::string juntuanName;
	int nNumber;//Ʊ��
	int m_level;
	time_t m_lastLogin;
	strToupiaoInfo()
	{
		m_rankVal = 0;
		nPlayerID = 0;
		playerName = "";
		nJuntuanID = 0;
		juntuanName = "";
	//	nRankNumber = 0;
		nNumber = 0;
		m_level = 0;
		m_lastLogin = 0;
	}
};

class strToupiaoInfoCmp 
{
public:
	bool operator() (const CRCore::ref_ptr<strToupiaoInfo> & left,const CRCore::ref_ptr<strToupiaoInfo> & right)
	{
		if (left->nNumber == right->nNumber)
		{
			//return left->m_lastLogin > left->m_lastLogin;
			return left->m_rankVal < right->m_rankVal;
		}
		return left->nNumber > right->nNumber;
	}
};

//typedef std::map<int, CRCore::ref_ptr<strToupiaoInfo> > ToupiaoData;//ͶƱ����
//struct strInfo :public CRCore::Referenced
//{
//	int m_rankVal;
//	int nPlayerID;
//	std::string playerName;
//	int nJuntuanID;
//	std::string junTuanName;
//	strInfo()
//	{
//		m_rankVal = 0;
//		nPlayerID = 0;
//		playerName = "";
//		nJuntuanID = 0;
//		junTuanName = "";
//	}
//};

class CountryHistoryInfoBase :public CRCore::Referenced
{
public:
	typedef CountryHistoryInfoBase Base;
	CountryHistoryInfoBase();;
	inline unsigned char getInfoType();
	inline void setTime( time_t time );
	inline void setInfoId(int id);

	virtual void getCompleteString(std::string &) = 0;
	virtual void readContent(CRCore::ref_ptr<CRCore::crStreamBuf> & stream);
	virtual void writeContent(CRCore::ref_ptr<CRCore::crStreamBuf> & stream);
	virtual unsigned char buildSaveStream(std::vector<std::string> & strVec);
	virtual unsigned char getSaveStream(std::vector<std::string> & strVec);
	inline CRCore::crHandle * getNoticeHandle();

	unsigned char m_infoType;
	int m_infoId;
	time_t m_time;
};

class CountryHistoryOfficalChange : public CountryHistoryInfoBase
{
public:
	CountryHistoryOfficalChange();
	virtual void getCompleteString(std::string & outString );
	virtual void readContent(CRCore::ref_ptr<CRCore::crStreamBuf> & stream);
	virtual void writeContent(CRCore::ref_ptr<CRCore::crStreamBuf> & stream);
	virtual unsigned char buildSaveStream(std::vector<std::string> & strVec);
	virtual unsigned char getSaveStream(std::vector<std::string> & strVec);
	std::string m_playerName;
	std::string m_officalName;
};

class CountryHistoryBenefitChange : public CountryHistoryInfoBase
{
public:
	CountryHistoryBenefitChange();
	virtual void getCompleteString(std::string & outString );
	virtual void readContent(CRCore::ref_ptr<CRCore::crStreamBuf> & stream);
	virtual void writeContent(CRCore::ref_ptr<CRCore::crStreamBuf> & stream);
	virtual unsigned char buildSaveStream(std::vector<std::string> & strVec);
	virtual unsigned char getSaveStream(std::vector<std::string> & strVec);
	std::string m_officalName;
	std::string m_playerName;
};


class CountryHistoryChengChiChange : public CountryHistoryInfoBase
{
public:
	CountryHistoryChengChiChange ();
	virtual void getCompleteString(std::string & outString );
	virtual void readContent(CRCore::ref_ptr<CRCore::crStreamBuf> & stream);
	virtual void writeContent(CRCore::ref_ptr<CRCore::crStreamBuf> & stream);
	virtual unsigned char buildSaveStream(std::vector<std::string> & strVec);
	virtual unsigned char getSaveStream(std::vector<std::string> & strVec);
	bool m_winOrlose;					// true -> win,false -> lose
	int m_chengchiId;
	int m_shiliid;
	//std::string m_officalName;
	//std::string m_playerName;
};

class CountryHistoryManager
{
public:
	void operator()(unsigned char type,CRCore::ref_ptr<CountryHistoryInfoBase> & newBase)
	{
		switch (type)
		{
		case JXJCountryHistoryType_Offical:
			newBase =  new CountryHistoryOfficalChange;
			break;
		case JXJCountryHistoryType_Benefit:
			newBase = new CountryHistoryBenefitChange;
			break;
		case JXJCountryHistoryType_Chengchi:
			newBase = new CountryHistoryChengChiChange ;
			break;
		default:
			newBase = NULL;
			break;
		}
	}
};

typedef std::deque<CRCore::ref_ptr<CountryHistoryInfoBase > > CountryHistory;		
typedef std::vector<CRCore::ref_ptr<strToupiaoInfo> > CandidateVec;//ͶƱ��ѡ��
typedef std::set<int> VotersSet;								// Ͷ��Ʊ�����id
typedef std::set<int> ShiliBlacklistSet;						// С�ű��

typedef std::set<int> InsertPlayerSet;							// �¼�������б�����id
typedef std::set<int> ModifyPlayerSet;							// �������޸ĵ����id

struct strConsortiaHuoDongInfo:public CRCore::Referenced 
{
	int nPlayerId;
	unsigned char rankNum;
	bool isConsortiaLeader;
	int groupId;
	strConsortiaHuoDongInfo(){
		nPlayerId = 0;
		rankNum = 0;
		isConsortiaLeader = false;
		groupId = 0;
	}
};
typedef std::vector<CRCore::ref_ptr<strConsortiaHuoDongInfo> > ConsortiaStartPromotionVec;				// ���ſ���������ʸ����
typedef std::vector<CRCore::ref_ptr<strConsortiaHuoDongInfo> > ConsortiaStartPromotionRankVec;			// ���ſ������Χ����

class crJXJShiliData :  public CRCore::crData
{//GameServer & GameClient Method
public:
	crJXJShiliData();
	crJXJShiliData(const crJXJShiliData& data);
	DataClass(JXJ, JXJShili)
	virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	virtual void excHandle(CREPARAM msg);
	JXJCountryOfficial getOfficialDes(int id);					// �õ���ְ
	std::string getOfficialStr( int id );
protected:
	//CRCore::ref_ptr<CRCore::crStreamBuf> m_dataStream;
	static GNE::Mutex m_saveMutex;
	GNE::Mutex m_dataMutex;
	bool m_modify;//�������ݿ�
	bool m_startedFete;								// �Ƿ�������	
	bool m_startedEnrichCountry;					// �Ƿ�������
	short m_smallAccLimit;							// С�ű�������
	int m_chengxiang;//ة��
	int m_dasima;//��˾��
	int m_dajiangjun;//�󽫾�
	int m_sijintai;//˾��̨
	int m_shennongtai;//��ų̃
	int m_simajian;//˾���
	int m_lubansi;//³����
	int m_dianjiangtai;//�㽫̨
	int m_version;		// ���洢
	unsigned char m_winCity;	// λ��� ������֮·�˸�����

	_crInt64 m_chengxiangLastLogin;
	_crInt64 m_dasimaLastLogin;
	_crInt64 m_dajiangjunLastLogin;

	_crInt64 m_shiliDayLastZero;//����ȡ������GameServerData���m_shiliDayUpdate

	std::string m_chengxiangName;
	std::string m_dasimaName;
	std::string m_dajiangjunName;
	std::string m_notice;

	CantonMap m_cantonMap;// �ݣ��ǳ� ���� ����map
	ShiliCityChangeDeq m_wincitydeq;
	ShiliCityChangeDeq m_lostcitydeq;
	PeopleMap m_peopleMap;//�����б�
	ShiliBlacklistSet m_blacklistSet;				// С���б�
	VotersSet m_votersSet;							// ͶƱ��id set
	//PeopleMap m_peopleToupiaoMap;//��ͶƱ���ID
	//CandidateVec m_toupiaoData;//����ͶƱ����
	//CandidateVec m_toupiaoResultLastweek;//����ͶƱ���
	CandidateVec m_candidateVecT;					//���ܹ�Ա��ѡ���б�
	CandidateVec m_candidateVecL;					//���ܹ�Ա��ѡ���б�
	CountryHistory m_countryHistory;

	PeopleVec m_tempPeopleVec;						// ��������б�,���������ݿ⣬ �Եȼ�Ϊ���� ����ǰ�˲�ѯ
	UIQueryFindByMinLvMap m_queryFindbyMinLvMap;
	UIQueryFindByMaxLvMap m_queryFindbyMaxLvMap;
	
	ModifyPlayerSet m_modifyPlayerSet;
	InsertPlayerSet m_insertPlayerSet;			// �����б������������id
	unsigned char m_cZhanLingChengChi;          //����ÿ��ռ��ǳ���
	int m_guojiazijn;                           //�����ʽ�
	CRCore::crVector3i m_guojiajifen;           //���һ���0�����磬1�����硢2������
	char m_destroycountryid1;                   //�����������Ĺ���id
	char m_destroycountryid2;					//�����������Ĺ���id
	ConsortiaStartPromotionVec m_consortiaStartPromotionVecT;    //���ſ��������Ҫ�����id
	ConsortiaStartPromotionRankVec m_consortiaPromotionRankVecT;  //���ſ������Χ����
	std::set<int> m_todayhavelandedplayer;     //���յ�½����Ҽ���  ���洢
	unsigned char m_cyesterdayconqueredcity;         //����ռ��ĳǳ�����
	unsigned char m_ctodayconqueredcity;         //����ռ��ĳǳ����� ���洢
	unsigned char m_countrystrength;            //���ҵ�ǿ��,0������1��ͨ��2ǿ����3�۹�
};

class crJXJSelectServerUIData :  public CRCore::crUIData
{//GameClient Method
public:
	crJXJSelectServerUIData();
	crJXJSelectServerUIData(const crJXJSelectServerUIData& data);
	DataClass(JXJ, JXJSelectServerUI)
	virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
protected:
	CRNetApp::ServerListMap m_serverListMap;
	int m_curpage;
	int m_totalpage;
};
typedef std::vector<int> SuperEquipCycleExpVec;
class crJXJPlayerStoreData :  public CRCore::crData
{//GameServer & GameClient Method
public:
	crJXJPlayerStoreData();
	crJXJPlayerStoreData(const crJXJPlayerStoreData& data);
	DataClass(JXJ, JXJPlayerStore)
	virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	virtual void excHandle(CREPARAM msg);
protected:
	static GNE::Mutex m_saveMutex;
	GNE::Mutex m_dataMutex;
	int m_money;//�ֻزֿ����Ԫ������
	// �����б�
	//unsigned char m_itembagnum;
	JXJStoreItemBagVec m_itembagvec;
	//// ���������б�
	//unsigned char m_jiangkabagnum;
	JXJStoreItemBagVec m_jiangkabagvec;
	int m_playerUsedMoney;//�ý�ɫ�ܹ����ѵ�Ԫ��
	unsigned short m_cyclecount;
	int m_vipexp;//vip����
	unsigned char m_superEquipCycleLvupPoint;//�ֻ������ȼ��������ע�������0,1,2,3,4��
	SuperEquipCycleExpVec m_superEquipCycleExpVec;//�����ֻؾ���
};

struct BattleRecruitCheckResult
{
	BattleRecruitCheckResult():
		m_code(-1),
		m_copperneed(0),
		m_woodneed(0),
		m_ironneed(0),
		m_horseneed(0),
		m_foodneed(0),
		m_timeneed(0),
		m_goldneed(0),
		m_shijibuycount(0)
	{}
	//0:��Դ����VIP0������Ҫ�������� 1:��Դ���� 2:�������㣬��Դ���㣬ֱ�ӿ۳���Դ���� 3:��Դ���㣬�۳�Ԫ������
	//-1:���ܲ��� -2�����ݲ��� -3:Ԫ������ -4:��Դ���� -6:ͭǮ���� -7:���տɹ���Դ�����㣬���ܹ��� -8:��Դ����ʧ��
	//-12:������ļ
	char m_code;
	int m_copperneed;
	int m_foodneed;
	int m_woodneed;
	int m_ironneed;
	int m_horseneed;
	int m_timeneed;
	int m_goldneed;
	int m_shijibuycount;
};
class crJXJExitSceneServerUIData :  public CRCore::crUIData
{//GameClient Method
public:
	crJXJExitSceneServerUIData();
	crJXJExitSceneServerUIData(const crJXJExitSceneServerUIData& data);
	DataClass(JXJ, JXJExitSceneServerUI)
	virtual void addParam(int i, const std::string& str);
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
protected:
	int m_codetext;
	short m_exittimer;
};

class crJXJTipsUIData : public CRCore::crUIData
{//client
public:
	crJXJTipsUIData();
	crJXJTipsUIData(const crJXJTipsUIData& data);
	DataClass(JXJ, JXJTipsUI)
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
protected:
	int m_id;
	int m_count;
};
class crJXJBattleRankingUIData : public CRCore::crUIData
{//client
public:
	crJXJBattleRankingUIData();
	crJXJBattleRankingUIData(const crJXJBattleRankingUIData& data);
	DataClass(JXJ, JXJBattleRankingUI)
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
	virtual void excHandle(CREPARAM msg);
protected:
	GNE::Mutex m_dataMutex;
	BattleRankingMap m_battleRankingMap;
	short m_mypos;
	int m_killtotal;
	int m_deadtotal;
	int m_myJifen;
	int m_myKill;
	int m_myDead;
	int m_myExploit;
	bool m_myLingqu;
	char m_battlerankingVer;
};
class crJXJUIIDData : public CRCore::crUIData
{//client
public:
	crJXJUIIDData();
	crJXJUIIDData(const crJXJUIIDData& data);
	DataClass(JXJ, JXJUIID)
	virtual void inputParam(int i, void *param);
	virtual void getParam(int i, void*& param);
protected:
	int m_id;
};
}
#endif
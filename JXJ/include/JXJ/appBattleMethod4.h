
/**********************************************************************
*
*	�ļ�:	   appBattleMethod4.h
*
*	����:	   
*
*	����:	   ����
*					
*
**********************************************************************/
#ifndef JXJ_APPBATTLEMETHOD4_H
#define JXJ_APPBATTLEMETHOD4_H
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
#include <JXJ/appData.h>
#include <JXJ/appData2.h>
#include <JXJ/appDefine.h>
namespace JXJ{


class crJXJRoomElapseTimeIsGreaterMethod : public CRCore::crMethod
{//SceneServer Method ����room�������Ƿ����ĳ��ֵ
public:
	crJXJRoomElapseTimeIsGreaterMethod ();
	crJXJRoomElapseTimeIsGreaterMethod (const crJXJRoomElapseTimeIsGreaterMethod & handle);
	MethodClass(JXJ, JXJRoomElapseTimeIsGreater)
	virtual void inputParam(int i, void *param);
	virtual void addParam(int i, const std::string& str);
	virtual void operator()(crHandle &handle);
protected:
	CRNetApp::crRoom* m_this;
	float m_scriptTime;
};

class crJXJAlterRelivedNpcAttrFromTableMethod : public CRCore::crMethod
{//SceneServer Method �ı�Npc Ѫ����������armycount
public:
	typedef std::vector<float> AttrFactorVec;
	crJXJAlterRelivedNpcAttrFromTableMethod ();
	crJXJAlterRelivedNpcAttrFromTableMethod (const crJXJAlterRelivedNpcAttrFromTableMethod & handle);
	MethodClass(JXJ, JXJAlterRelivedNpcAttrFromTable)
	virtual void inputParam(int i, void *param);
	virtual void addParam(int i, const std::string& str);
	virtual void operator()(crHandle &handle);
protected:
	CRNetApp::crRoom* m_this;
	int m_tableid;
	AttrFactorVec m_attrFactorVec;
};

class crJXJCheckItemsLivedFromTabMethod : public CRCore::crMethod
{//SceneServer Method 
public:
	crJXJCheckItemsLivedFromTabMethod ();
	crJXJCheckItemsLivedFromTabMethod (const crJXJCheckItemsLivedFromTabMethod & handle);
	MethodClass(JXJ, JXJCheckItemsLivedFromTab)
		virtual void operator()(crHandle &handle);
	virtual void inputParam(int i, void *param);
	virtual void addParam(int i, const std::string& str);
protected:
	CRNetApp::crRoom *m_this;
	int m_id;
	bool m_orOrAnd;		// 0 ��ʾ��1��ʾ��
};

class crJXJNPCCloseToPlayerFromTableMethod : public CRCore::crMethod
{//SceneServer Method npc�Ƿ�ӽ�player
public:
	crJXJNPCCloseToPlayerFromTableMethod ();
	crJXJNPCCloseToPlayerFromTableMethod (const crJXJNPCCloseToPlayerFromTableMethod & handle);
	MethodClass(JXJ, JXJNPCCloseToPlayerFromTable)
	virtual void inputParam(int i, void *param);
	virtual void addParam(int i, const std::string& str);
	virtual void operator()(crHandle &handle);
protected:
	CRNetApp::crRoom* m_this;
	int m_tableID;
	float m_distance;
};

class crJXJAlterNPCRTHPFromTableMethod : public CRCore::crMethod
{//SceneServer Method ֱ�Ӹı�npc��Ѫ��
public:
	crJXJAlterNPCRTHPFromTableMethod ();
	crJXJAlterNPCRTHPFromTableMethod (const crJXJAlterNPCRTHPFromTableMethod & handle);
	MethodClass(JXJ, JXJAlterNPCRTHPFromTable)
	virtual void inputParam(int i, void *param);
	virtual void addParam(int i, const std::string& str);
	virtual void operator()(crHandle &handle);
protected:
	CRNetApp::crRoom* m_this;
	int m_tableID;
	float m_factor;	// �ı��ϵ��
};

class crJXJRoomProgressIsBelowValMethod : public CRCore::crMethod
{//SceneServer Method		// �жϵ�ǰ�Ǵ������½�����
public:
	crJXJRoomProgressIsBelowValMethod ();
	crJXJRoomProgressIsBelowValMethod (const crJXJRoomProgressIsBelowValMethod & handle);
	MethodClass(JXJ, JXJRoomProgressIsBelowVal)
		virtual void operator()(crHandle &handle);
	virtual void inputParam(int i, void *param);
	virtual void addParam(int i, const std::string& str);
	typedef std::vector<short> ProgressVec;
protected:
	CRNetApp::crRoom *m_this;
	ProgressVec m_progressVec;
};

class crJXJNPCCloseToNPCFromTableMethod : public CRCore::crMethod
{//SceneServer Method npc�Ƿ�ӽ�npc
public:
	crJXJNPCCloseToNPCFromTableMethod ();
	crJXJNPCCloseToNPCFromTableMethod (const crJXJNPCCloseToNPCFromTableMethod & handle);
	MethodClass(JXJ, JXJNPCCloseToNPCFromTable)
	virtual void inputParam(int i, void *param);
	virtual void addParam(int i, const std::string& str);
	virtual void operator()(crHandle &handle);
protected:
	CRNetApp::crRoom* m_this;
	int m_tableID1;
	int m_tableID2;
	float m_distance;
};

class crJXJAlterPlayerRTHPMethod : public CRCore::crMethod
{//SceneServer Method  �����ֱ�ӵ�Ѫ ����
public:
	crJXJAlterPlayerRTHPMethod ();
	crJXJAlterPlayerRTHPMethod (const crJXJAlterPlayerRTHPMethod & handle);
	MethodClass(JXJ, JXJAlterPlayerRTHP)
	virtual void inputParam(int i, void *param);
	virtual void addParam(int i, const std::string& str);
	virtual void operator()(crHandle &handle);
protected:
	CRNetApp::crRoom* m_this;
	float m_factor;
};


class crJXJNPCCloseToPointFromTableMethod : public CRCore::crMethod
{//SceneServer Method npc�Ƿ�ӽ� ĳһ��
public:
	crJXJNPCCloseToPointFromTableMethod ();
	crJXJNPCCloseToPointFromTableMethod (const crJXJNPCCloseToPointFromTableMethod & handle);
	MethodClass(JXJ, JXJNPCCloseToPointFromTable)
	virtual void inputParam(int i, void *param);
	virtual void addParam(int i, const std::string& str);
	virtual void operator()(crHandle &handle);
protected:
	CRNetApp::crRoom* m_this;
	int m_tableID;
	CRCore::crVector2f m_point;
	float m_distance;
};

class crJXJPlayerCloseToPointMethod : public CRCore::crMethod
{//SceneServer Method ����Ƿ�ӽ�ĳһ��
public:
	crJXJPlayerCloseToPointMethod ();
	crJXJPlayerCloseToPointMethod (const crJXJPlayerCloseToPointMethod & handle);
	MethodClass(JXJ, JXJPlayerCloseToPoint)
	virtual void inputParam(int i, void *param);
	virtual void addParam(int i, const std::string& str);
	virtual void operator()(crHandle &handle);
protected:
	CRNetApp::crRoom* m_this;
	CRCore::crVector2f m_point;
	float m_distance;
};

class crJXJNPCSurvivalNumIsNotLessMethod : public CRCore::crMethod
{//SceneServer Method �ж�NPC�Ƿ� ��ָ���������
public:
	crJXJNPCSurvivalNumIsNotLessMethod ();
	crJXJNPCSurvivalNumIsNotLessMethod (const crJXJNPCSurvivalNumIsNotLessMethod & handle);
	MethodClass(JXJ, JXJNPCSurvivalNumIsNotLess)
	virtual void inputParam(int i, void *param);
	virtual void addParam(int i, const std::string& str);
	virtual void operator()(crHandle &handle);
protected:
	CRNetApp::crRoom* m_this;
	int m_tableID;
	unsigned char m_num;
};

class crJXJExtraGainMpPerAttackMethod : public CRCore::crMethod
{//SceneServer & GameClient Method  ����ÿ�ι�����õ�ʿ��
public:
	crJXJExtraGainMpPerAttackMethod ();
	crJXJExtraGainMpPerAttackMethod (const crJXJExtraGainMpPerAttackMethod & handle);
	MethodClass(JXJ, JXJExtraGainMpPerAttack)
		virtual void operator()(crHandle &handle);
	virtual void inputParam(int i, void *param);
	virtual void addParam(int i, const std::string& str);
protected:
	CRNetApp::crInstanceItem* m_this;
	float *m_dt;
	float m_duration;
	short m_extraValue;
	bool m_start;
	float m_timer;

	unsigned char m_overlapCount;
};

class crJXJExtraGainMpPerTimerMethod: public CRCore::crMethod
{//SceneServer & GameClient Method		ÿһ��ʱ������ʿ��ֵ
public:
	crJXJExtraGainMpPerTimerMethod();
	crJXJExtraGainMpPerTimerMethod(const crJXJExtraGainMpPerTimerMethod& handle);
	MethodClass(JXJ, JXJExtraGainMpPerTimer)
	virtual void operator()(crHandle &handle);
	virtual void inputParam(int i, void *param);
	virtual void addParam(int i, const std::string& str);
protected:
	CRNetApp::crInstanceItem* m_this;
	float *m_dt;
	float m_duration;
	float m_extraValue;
	//short m_addValue;

	bool m_start;
	float m_timer;
	float m_dtrec;
	float m_interval;

	unsigned char m_overlapCount;
};

class crJXJExtraReduceMpPerTimerAndRemoveExtraMethod: public CRCore::crMethod
{//SceneServer & GameClient Method		ÿһ��ʱ�����ʿ��ֵ ����ʱɾ�����buf
public:
	crJXJExtraReduceMpPerTimerAndRemoveExtraMethod();
	crJXJExtraReduceMpPerTimerAndRemoveExtraMethod(const crJXJExtraReduceMpPerTimerAndRemoveExtraMethod& handle);
	MethodClass(JXJ, JXJExtraReduceMpPerTimerAndRemoveExtra)
	virtual void operator()(crHandle &handle);
	virtual void inputParam(int i, void *param);
	virtual void addParam(int i, const std::string& str);
protected:
	CRNetApp::crInstanceItem* m_this;
	float *m_dt;
	float m_duration;
	float m_extraValue;
	//short m_addValue;

	bool m_start;
	float m_timer;
	float m_dtrec;
	float m_interval;
	bool *m_output;
	unsigned char m_overlapCount;
};


class crJXJExtraReduceMpPerSkillDamageMethod : public CRCore::crMethod
{//SceneServer & GameClient Method  ����ÿ�μ����ͷ����ĵ�ʿ��
public:
	crJXJExtraReduceMpPerSkillDamageMethod ();
	crJXJExtraReduceMpPerSkillDamageMethod (const crJXJExtraReduceMpPerSkillDamageMethod & handle);
	MethodClass(JXJ, JXJExtraReduceMpPerSkillDamage)
		virtual void operator()(crHandle &handle);
	virtual void inputParam(int i, void *param);
	virtual void addParam(int i, const std::string& str);
protected:
	CRNetApp::crInstanceItem* m_this;
	float *m_dt;
	float m_duration;
	short m_extraValue;
	bool m_start;
	float m_timer;
	unsigned char m_overlapCount;
};

class crJXJGetGainRTMPMethod : public CRCore::crMethod
{//SceneServer & Client Method
public:
	crJXJGetGainRTMPMethod ();
	crJXJGetGainRTMPMethod (const crJXJGetGainRTMPMethod & handle);
	MethodClass(JXJ, JXJGetGainRTMP)
	virtual void operator()(crHandle &handle);
	virtual void inputParam(int i, void *param);
	virtual void addParam(int i, const std::string& str);
protected:
	CRNetApp::crInstanceItem* m_this;
	float *m_output;
	int m_type;	// 0,�˺���1 ����
	CRCore::Timer_t m_lasttime;
};

class crJXJGetSkillNeedRTMPMethod : public CRCore::crMethod
{//SceneServer & Client Method
public:
	crJXJGetSkillNeedRTMPMethod ();
	crJXJGetSkillNeedRTMPMethod (const crJXJGetSkillNeedRTMPMethod & handle);
	MethodClass(JXJ, JXJGetSkillNeedRTMP)
	virtual void operator()(crHandle &handle);
	virtual void inputParam(int i, void *param);
	virtual void addParam(int i, const std::string& str);
protected:
	CRNetApp::crInstanceItem* m_this;
	CRNetApp::crInstanceItem* m_skillThis;
	float *m_output;
};

class crJXJExtraDonotGetMPMethod : public CRCore::crMethod
{//SceneServer & GameClient Method  һ��ʱ�����޷����ʿ��
public:
	crJXJExtraDonotGetMPMethod ();
	crJXJExtraDonotGetMPMethod (const crJXJExtraDonotGetMPMethod & handle);
	MethodClass(JXJ, JXJExtraDonotGetMP)
		virtual void operator()(crHandle &handle);
	virtual void inputParam(int i, void *param);
	virtual void addParam(int i, const std::string& str);
protected:
	CRNetApp::crInstanceItem* m_this;
	float *m_dt;
	float m_duration;
	short m_extraValue;
	bool m_start;
	float m_timer;
};

//class crJXJReduceRTMPDirectlyMethod: public CRCore::crMethod
//{//SceneServer & GameClient Method		ֱ�Ӽ���ʿ��ֵ
//public:
//	crJXJReduceRTMPDirectlyMethod();
//	crJXJReduceRTMPDirectlyMethod(const crJXJReduceRTMPDirectlyMethod& handle);
//	MethodClass(JXJ, JXJReduceRTMPDirectly)
//	virtual void operator()(crHandle &handle);
//	virtual void inputParam(int i, void *param);
//	virtual void addParam(int i, const std::string& str);
//protected:
//	CRNetApp::crInstanceItem* m_this;
//	CRCore::ref_ptr<CRNetApp::HitParam> m_hitParam;
//	float m_extraValue;
//};
class crJXJHitParamRTMPMethod: public CRCore::crMethod
{//SceneServer Method		ֱ������ʿ��ֵ
public:
	crJXJHitParamRTMPMethod();
	crJXJHitParamRTMPMethod(const crJXJHitParamRTMPMethod& handle);
	MethodClass(JXJ, JXJHitParamRTMP)
	virtual void operator()(crHandle &handle);
	virtual void inputParam(int i, void *param);
	virtual void addParam(int i, const std::string& str);
protected:
	CRNetApp::crInstanceItem* m_this;
	CRCore::ref_ptr<CRNetApp::HitParam> m_hitParam;
	int m_flg;//0�����ߣ�1��ʾ�ܻ���
	float m_extraValue;//+��ʾ��ʿ��������ʾ��ʿ��
};

class crJXJClearTargetExtraPerTimeMethod : public CRCore::crMethod
{//SceneServer GameClient Method  ���������Ч��
public: 
	crJXJClearTargetExtraPerTimeMethod ();
	crJXJClearTargetExtraPerTimeMethod (const crJXJClearTargetExtraPerTimeMethod & handle);
	MethodClass(JXJ, JXJClearTargetExtraPerTime)
	virtual void operator()(crHandle &handle);
	virtual void inputParam(int i, void *param);
	virtual void addParam(int i, const std::string& str);
protected:
	CRNetApp::crInstanceItem* m_this;
	//CRCore::ref_ptr<CRNetApp::HitParam> m_hitParam;
	float m_duration;//����ʱ��
	std::set<int> m_exceptBufTypeSet;//Ҫ�����buf���ͣ�bufferAttrTab��Buf����
	float m_interval;//ÿ��interval����һ��

	float m_timer;
	float *m_dt;
	float m_dtrec;
	bool m_start;
};

class crJXJChangeNPCShiliFromTableMethod : public CRCore::crMethod
{//SceneServer Method �ı�npc���� 
public:
	crJXJChangeNPCShiliFromTableMethod ();
	crJXJChangeNPCShiliFromTableMethod (const crJXJChangeNPCShiliFromTableMethod & handle);
	MethodClass(JXJ, JXJChangeNPCShiliFromTable)
	virtual void inputParam(int i, void *param);
	virtual void addParam(int i, const std::string& str);
	virtual void operator()(crHandle &handle);
protected:
	CRNetApp::crRoom* m_this;
	int m_tableID;
	char m_scriptVal;
	bool m_initdata;//�Ƿ���Ѫ
};

class crJXJExtraGainMpPerDamageMethod : public CRCore::crMethod
{//SceneServer & GameClient Method  ����ÿ���յ��˺���õ�ʿ��
public:
	crJXJExtraGainMpPerDamageMethod ();
	crJXJExtraGainMpPerDamageMethod (const crJXJExtraGainMpPerDamageMethod & handle);
	MethodClass(JXJ, JXJExtraGainMpPerDamage)
		virtual void operator()(crHandle &handle);
	virtual void inputParam(int i, void *param);
	virtual void addParam(int i, const std::string& str);
protected:
	CRNetApp::crInstanceItem* m_this;
	float *m_dt;
	float m_duration;
	short m_extraValue;
	bool m_start;
	float m_timer;
	unsigned char m_overlapCount;
};

}

#endif
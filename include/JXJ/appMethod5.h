/**********************************************************************
*
*	�ļ�:	   appMethod5.h
*
*	����:	   
*
*	����:	   ��ѩ��
*					
*
**********************************************************************/
#ifndef JXJ_APPMETHOD5_H
#define JXJ_APPMETHOD5_H
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
	typedef std::vector<std::pair<std::string, std::string>> CanvasIconVec;

/////////////////////////////////////////
//
//GeneralTips
//TIPS
//
/////////////////////////////////////////
class GeneralTips
{//Client Method
public:
	GeneralTips(std::string m_tipsCanvas, CRCore::crWidgetNode *m_this);
	GeneralTips(std::string m_tipsCanvas);
	void GeneralTips::setTipRight();
	void GeneralTips::setTipUpper();
	void GeneralTips::setTipAuto();
	//void GeneralTipsMethod::showTips(CRCore::crCanvasNode *tips);
	void GeneralTips::setText(std::string m_tipsTextWidget, std::string textStr);
	void GeneralTips::setText(std::string m_tipsTextWidget, std::string textStr, CRCore::crVector4 textColor);
	void GeneralTips::setImgage(std::string m_tipsImgWidget, std::string imgStr);
protected:
	CRCore::crWidgetNode* m_this;//��������ƶ����Ŀؼ�
	std::string m_tipsTextWidget;
	std::string m_tipsImgWidget;
	CRUI::crStaticTextWidgetNode *tipsText;
	CRUI::crImageBoxWidgetNode *tipsImg;
	CRCore::crCanvasNode *tips;
};
/////////////////////////////////////////
//
//crJXJUIOficialRankBestLevelTipMethod
//������õĹ�ְ�Ѿ�����߼�����껬����Ǩ��ť��ʾ "�Ѿ�����߼���"
//
/////////////////////////////////////////
class crJXJUIOficialRankBestLevelTipMethod : public CRCore::crMethod
{//Client Method
public:
	crJXJUIOficialRankBestLevelTipMethod();
	crJXJUIOficialRankBestLevelTipMethod(const crJXJUIOficialRankBestLevelTipMethod& handle);
	MethodClass(JXJ, JXJUIOficialRankBestLevelTip)
	virtual void operator()(crHandle &handle);
	virtual void inputParam(int i, void *param);
	virtual void addParam(int i, const std::string& str);
protected:
	CRCore::crWidgetNode* m_this;
	std::string m_tipsCanvas;
	std::string m_tipsTextWidget;
	std::string m_canvasName;
};

/////////////////////////////////////////
//
//crJXJSelectCharacterPowerOnShowMethod
//���ν�����Ϸʱ���������������������
//
/////////////////////////////////////////
class crJXJSelectCharacterPowerOnShowMethod : public CRCore::crMethod
{//Client Method
public:
	crJXJSelectCharacterPowerOnShowMethod();
	crJXJSelectCharacterPowerOnShowMethod(const crJXJSelectCharacterPowerOnShowMethod& handle);
	MethodClass(JXJ, JXJSelectCharacterPowerOnShow)
	virtual void operator()(crHandle &handle);
	virtual void inputParam(int i, void *param);
	virtual void addParam(int i, const std::string& str);
protected:
	CRCore::crCanvasNode* m_this;
	std::string m_PowerRaidoCanvas;
	std::string m_radio[3];
};
/////////////////////////////////////////
//
//crJXJUINationIntroduceInfoMethod
//��ɫѡ����Ϣ��ʾ
//
/////////////////////////////////////////
class crJXJUINationIntroduceInfoMethod : public CRCore::crMethod
{//Client Method
public:
	crJXJUINationIntroduceInfoMethod();
	crJXJUINationIntroduceInfoMethod(const crJXJUINationIntroduceInfoMethod& handle);
	MethodClass(JXJ, JXJUINationIntroduceInfo)
		virtual void operator()(crHandle &handle);
	virtual void inputParam(int i, void *param);
	virtual void addParam(int i, const std::string& str);
protected:
	CRUI::crRadioGroupWidgetNode *m_this;
	std::string m_infoSwitch;
};
///////////////////////////////////////////
////
////crJXJUIBattleTroopsTypeTipMethod
////ս������������ʾ��Ϣ
////
///////////////////////////////////////////
//class crJXJUIBattleTroopsTypeTipMethod : public CRCore::crMethod
//{//Client Method
//public:
//	crJXJUIBattleTroopsTypeTipMethod();
//	crJXJUIBattleTroopsTypeTipMethod(const crJXJUIBattleTroopsTypeTipMethod& handle);
//	MethodClass(JXJ, JXJUIBattleTroopsTypeTip)
//		virtual void operator()(crHandle &handle);
//	virtual void inputParam(int i, void *param);
//	virtual void addParam(int i, const std::string& str);
//protected:
//	CRCore::crWidgetNode* m_this;
//	std::string m_tipsCanvas;
//	std::string m_tipsTroopsNameWidget;
//	std::string m_tipsTroopsFeatureWidget;
//	int m_index_1;
//	int m_index_2;
//};

/////////////////////////////////////////
//
//crJXJUITroopsTypeTipMethod
//���������������ʾ��Ϣ
//
/////////////////////////////////////////
class crJXJUITroopsTypeTipMethod : public CRCore::crMethod
{//Client Method
public:
	crJXJUITroopsTypeTipMethod();
	crJXJUITroopsTypeTipMethod(const crJXJUITroopsTypeTipMethod& handle);
	MethodClass(JXJ, JXJUITroopsTypeTip)
	virtual void operator()(crHandle &handle);
	virtual void inputParam(int i, void *param);
	virtual void addParam(int i, const std::string& str);
	void gethypertext(int abstractid,rcfg::ConfigScript& output, rcfg::ConfigScript& output2, rcfg::ConfigScript& output3);
protected:
	CRProducer::crGUIEventAdapter* m_ea;
	CRCore::crWidgetNode* m_this;
	std::string m_tipsCanvas;
	std::string m_tipsTroopsNameWidget;
	std::string m_tipsZhanliinput[2];
	std::string m_armyTypeRadio;
	std::string m_infoCanvas;
	std::string m_infoInput;
	std::string m_infoBK;
	std::string m_infoDi;
	int m_index_1;
	int m_index_2;
};

/////////////////////////////////////////
//
//crJXJUICDTimeTipMethod
//��������������ˢ��ʱ�����ʾ
//
/////////////////////////////////////////
class crJXJUICDTimeTipMethod : public CRCore::crMethod
{//Client Method
public:
	crJXJUICDTimeTipMethod();
	crJXJUICDTimeTipMethod(const crJXJUICDTimeTipMethod& handle);
	MethodClass(JXJ,JXJUICDTimeTip)
		virtual void operator()(crHandle &handle);
	virtual void inputParam(int i, void *param);
	virtual void addParam(int i, const std::string& str);
protected:
	CRCore::crWidgetNode* m_this;
	std::string m_tipsCanvas;
	std::string m_tipsTextWidget;
	std::string m_canvasName;
	int m_index;
	int m_btnindex;
	std::vector<std::string> m_buildinginputnamevec;
	std::vector<std::string> m_recruitinputnamevec;
};

/////////////////////////////////////////
//
//crJXJUICDTimeColorTipMethod
//��������������ˢ��ʱ�����ʾ
//
/////////////////////////////////////////
class crJXJUICDTimeColorTipMethod : public CRCore::crMethod
{//Client Method
public:
	crJXJUICDTimeColorTipMethod();
	crJXJUICDTimeColorTipMethod(const crJXJUICDTimeColorTipMethod& handle);
	MethodClass(JXJ,JXJUICDTimeColorTip)
		virtual void operator()(crHandle &handle);
	virtual void inputParam(int i, void *param);
	virtual void addParam(int i, const std::string& str);
protected:
	CRCore::crWidgetNode* m_this;
};

/////////////////////////////////////////
//
//crJXJXueTiaoColorMethod
//Ѫ����ɫ�ı�
//
/////////////////////////////////////////
class crJXJXueTiaoColorMethod:public CRCore::crMethod
{
public:
	crJXJXueTiaoColorMethod();
	crJXJXueTiaoColorMethod(const crJXJXueTiaoColorMethod &handle);
	MethodClass(JXJ,JXJXueTiaoColor)
	void virtual operator()(crHandle &handle);
	void virtual inputParam(int i, void *param);
	void virtual addParam(int i, const std::string& str);

private:
	CRCore::crCanvasNode * m_this;
	std::string m_canvas;
	std::string m_progress_F1;
	std::string m_progress_F2;
	std::string m_progress_F3;
	std::string m_progress_F1_1;
	std::string m_progress_F1_2;
	std::string m_progress_F1_3;
	std::string m_progress_F2_1;
	std::string m_progress_F2_2;
	std::string m_progress_F2_3;
	std::string m_progress_F3_1;
	std::string m_progress_F3_2;
	std::string m_progress_F3_3;
	std::string m_strarmyCount_F1;
	std::string m_strarmyCount_F2;
	std::string m_strarmyCount_F3;
};

/////////////////////////////////////////
//
//crJXJFubenDropTipsMethod
//����������ƷTips
//
/////////////////////////////////////////
class crJXJFubenDropTipsMethod:public CRCore::crMethod
{
public:
	crJXJFubenDropTipsMethod();
	crJXJFubenDropTipsMethod(const crJXJFubenDropTipsMethod& handle);
	MethodClass(JXJ, JXJFubenDropTips)
		virtual void operator()(crHandle &handle);
	virtual void inputParam(int i, void *param);
	virtual void addParam(int i, const std::string& str);
protected:
	CRCore::crWidgetNode* m_this;
	std::string m_tips;
	std::string m_name;
	std::string m_info1;
	std::string m_info2;
	std::string m_itemlv;
	std::string m_itemicon;
	std::string m_itemequipon;
	std::string m_canvas;
	std::string m_infocanvas;
	std::string m_infobk;
	std::string m_infodi;
	CRCore::crVector3 m_offsets;
	CRCore::crVector4f m_colorred;
	int m_index;
	//float m_expandnum;
	//bool m_ifexpand;
};

/////////////////////////////////////////
//
//crJXJUIAchievementUpdateMethod
//�ɾ���ϸ��Ϣ��ʾ
//
/////////////////////////////////////////
class crJXJUIAchievementUpdateMethod:public CRCore::crMethod
{
public:
	crJXJUIAchievementUpdateMethod();
	crJXJUIAchievementUpdateMethod(const crJXJUIAchievementUpdateMethod& handle);
	MethodClass(JXJ, JXJUIAchievementUpdate)
		virtual void operator()(crHandle &handle);
	virtual void inputParam(int i, void *param);
	virtual void addParam(int i, const std::string& str);
protected:
	CRCore::crCanvasNode* m_this;
	std::string m_canvas;
	std::string m_Button[10];
	std::string m_input[25];
	std::string m_icon[5];
	int m_totalBtnNum;
	int m_totalItemNum;
	int m_OneItemNum;
	std::string m_scroll;
	//int index;
	std::string m_infoinput[3];
	std::string m_progressbar;
	std::string m_backbordsw[5];
};

/////////////////////////////////////////
//
//crJXJUIAchievementUpdateNewMethod
//�ɾ���ϸ��Ϣ��ʾ�°�
//
/////////////////////////////////////////
class crJXJUIAchievementUpdateNewMethod:public CRCore::crMethod
{
public:
	crJXJUIAchievementUpdateNewMethod();
	crJXJUIAchievementUpdateNewMethod(const crJXJUIAchievementUpdateNewMethod& handle);
	MethodClass(JXJ, JXJUIAchievementUpdateNew)
		virtual void operator()(crHandle &handle);
	virtual void inputParam(int i, void *param);
	virtual void addParam(int i, const std::string& str);
protected:
	CRCore::crCanvasNode* m_this;
	std::string m_canvas;
	std::string m_Button[11];
	std::string m_input[35];
	std::string m_icon[7];
	int m_totalBtnNum;
	int m_totalItemNum;
	int m_OneItemNum;
	std::string m_scroll;
	//int index;
	std::string m_infoinput[2];
	std::string m_progressbar[6];
	std::string m_backbordsw[7];
	std::string m_progresstext[6];
	std::string m_dalytarget[5];
	std::string m_buybtn[10];
	std::string m_pricetext[10];
	std::string m_imagebox[10];
	std::string m_shopscroll;
	std::string m_zonglansw;
	CRCore::crVector2i m_guozhanid;
	CRCore::crVector2i m_lingzhuid;
	CRCore::crVector2i m_fengdiid;
	CRCore::crVector2i m_jiangkaid;
	CRCore::crVector2i m_fubenid;
	std::string m_strFoodImage;//����
	std::string m_strWoodImage;//ľ��
	std::string m_strIronImage;//����
	std::string m_strHorseImage;//��ƥ
	std::string m_strCopperImage;//ͭǮ
	std::string m_strExpImage;//����
	std::string m_strAchievementImage;//��ѫ
	std::string m_strGiftGoldImage;//���
	std::string m_strContributeImage;//�Ƿ�ֵ
	std::string m_strExploitImage;//ս��
	std::string m_strVipImage;//vip����
	std::string m_strZhanquanImage;//սȯ
	std::string m_childnode[7];
	std::string m_commodityc[10];
};
/////////////////////////////////////////
//
//crJXJChengjiuButtonMethod
//�ɾͰ�ťת��[UI]
//
/////////////////////////////////////////
class crJXJChengjiuButtonMethod:public CRCore::crMethod
{
public:
	crJXJChengjiuButtonMethod();
	crJXJChengjiuButtonMethod(const crJXJChengjiuButtonMethod& handle);
	MethodClass(JXJ, JXJChengjiuButton)
		virtual void operator()(crHandle &handle);
	virtual void inputParam(int i, void *param);
	virtual void addParam(int i, const std::string& str);
protected:
	CRCore::crWidgetNode* m_this;
	std::string m_canvas;
	int m_index;
	//CREncapsulation::crTableIO *accomplish_table;
	int achievementTabInfo(CREncapsulation::crTableIO *accomplish_table);
};
/////////////////////////////////////////
//
//ImgAndTextInfo
//һ�������Ϣ[UI]
//
/////////////////////////////////////////
class ImgAndTextInfo
{
public:
	ImgAndTextInfo(CRCore::crNode *childnodex,CRUI::crImageBoxWidgetNode *itemImg, std::vector<CRUI::crStaticTextWidgetNode*> itemVct,CRCore::crMultiSwitch *itemSw);
	CRUI::crImageBoxWidgetNode *getItemImg();
	CRCore::crMultiSwitch *getItemSw();
	CRCore::crNode *getChildNode();
	std::vector<CRUI::crStaticTextWidgetNode*> getItemVec();
	int  ImgAndTextInfo::clearItem(std::string backgroundImg);
protected:
	CRUI::crImageBoxWidgetNode *itemImg;
	std::vector<CRUI::crStaticTextWidgetNode*> itemVct;
	CRCore::crMultiSwitch *m_backboardsw;
	CRCore::crNode *childnode;
};
/////////////////////////////////////////
//
//crJXJChengjiuButtonInitMethod
//�ɾͰ�ť��ʼ��[UI]
//
/////////////////////////////////////////
class crJXJChengjiuButtonInitMethod:public CRCore::crMethod
{
public:
	crJXJChengjiuButtonInitMethod();
	crJXJChengjiuButtonInitMethod(const crJXJChengjiuButtonInitMethod& handle);
	MethodClass(JXJ, JXJChengjiuButtonInit)
		virtual void operator()(crHandle &handle);
	virtual void inputParam(int i, void *param);
	virtual void addParam(int i, const std::string& str);
protected:
	CRCore::crCanvasNode* m_this;
	std::string m_canvas;
	std::string m_Button[11];
	int m_totalBtnNum;
	std::string m_img[5];
};
/////////////////////////////////////////
//
//crJXJUIAchievementPromptMethod
//�ɾ͵�����[UI]
//
/////////////////////////////////////////
class crJXJUIAchievementPromptMethod : public CRCore::crMethod
{//Client Method
public:
	crJXJUIAchievementPromptMethod();
	crJXJUIAchievementPromptMethod(const crJXJUIAchievementPromptMethod& handle);
	MethodClass(JXJ, JXJUIAchievementPrompt)
		virtual void operator()(crHandle &handle);
	virtual void inputParam(int i, void *param);
	virtual void addParam(int i, const std::string& str);
protected:
	CRCore::crCanvasNode* m_this;
	std::string m_tipsCanvas;
	std::string m_icon;
	std::string m_input1;
	std::string m_input2;
	std::string m_sequence;
};
/////////////////////////////////////////
//
//TwoLevelMenuButton
//��չ���Ķ༶��ť�˵�[UI]
//
/////////////////////////////////////////
class TwoLevelMenuButton
{
public:
	TwoLevelMenuButton(std::vector<CRUI::crCheckBoxWidgetNode*> ButtonVct, CanvasIconVec *accomplishBtnIcon, CREncapsulation::crTableIO *picture_table, int index);
	int expandFirstLevel(int parentIndex, int pictureTabIdIndex, CREncapsulation::crTableIO::DataVec iconRecords);//(accomplishBtnIcon ��ť�б�m_index ����İ�ť��parentIndex)
	int showButtonInfo(CREncapsulation::crTableIO *accomplish_table,std::vector<ImgAndTextInfo> imgAndTextVec, int titleIndex, int totalItemNum);
	int showButtonInfo(CREncapsulation::crTableIO *accomplish_table,std::vector<ImgAndTextInfo> imgAndTextVec, int titleIndex, int totalItemNum, CRUI::crScrollBarWidgetNode *chapterscroll);
	int showButtonImg();
	int scrollInfo(CRUI::crScrollBarWidgetNode *chapterscroll, int rowcount, int maxsize);
private:
	int TwoLevelMenuButton::stepFubenShow(int id, CRUI::crStaticTextWidgetNode *tmpText, std::vector< CRUI::crStaticTextWidgetNode *> tmpTextVec,CRCore::crMultiSwitch *tempSwitch,std::string& notestr);
protected:
	CRCore::crWidgetNode *m_this;
	std::vector<CRUI::crCheckBoxWidgetNode*> ButtonVec;//����ϵ�button�ؼ�(crCheckBoxWidgetNode��ť�ؼ��б�
	CanvasIconVec *accomplishBtnIcon;//���ǵ������õ��İ�ťicon���ܳ���buttonVec��size�����⽨��һ��ֻ�洢��Ҫ��ʾ�İ�ť�б�����б���ܴ���Ҳ����С��buttonVec��size
	CREncapsulation::crTableIO *picture_table;//�洢���а�ťͼƬ�ı�
	std::string titleOne;//һ����ť�ı�־
	std::string indexBtn;//������İ�ťid��Ϣ
	int index;//������İ�ť
	//int rowcount;//�����Ϣ����������δ��ʾ��

	int idIndex;
	int nameTitleIndex;
	int iconIndex;
	int iconHighlightedIndex;
};

/////////////////////////////////////////
//
//crJXJUIResourceCardTimeTipMethod
//��Դ�ӳɿ�ʣ��ʱ��tips
//
/////////////////////////////////////////
class crJXJUIResourceCardTimeTipMethod : public CRCore::crMethod
{//Client Method
public:
	crJXJUIResourceCardTimeTipMethod();
	crJXJUIResourceCardTimeTipMethod(const crJXJUIResourceCardTimeTipMethod& handle);
	MethodClass(JXJ, JXJUIResourceCardTimeTip)
		virtual void operator()(crHandle &handle);
	virtual void inputParam(int i, void *param);
	virtual void addParam(int i, const std::string& str);
protected:
	CRCore::crWidgetNode* m_this;
	std::string m_tipsCanvas;
	std::string m_tipsTextWidget;
	std::string m_canvasName;
	int m_index;
	std::string m_extsw;
};

/////////////////////////////////////////
//
//crJXJUIBattleBuffTipsMethod
//ս����buff tips
//
/////////////////////////////////////////
//class crJXJUIBattleBuffTipsMethod : public CRCore::crMethod
//{//Client Method
//public:
//	crJXJUIBattleBuffTipsMethod();
//	crJXJUIBattleBuffTipsMethod(const crJXJUIBattleBuffTipsMethod& handle);
//	MethodClass(JXJ, JXJUIBattleBuffTips)
//		virtual void operator()(crHandle &handle);
//	virtual void inputParam(int i, void *param);
//	virtual void addParam(int i, const std::string& str);
//protected:
//	CRCore::crWidgetNode* m_this;
//	std::string m_tipsCanvas;
//	std::string m_tipsTextWidget;
//	std::string m_canvasName;
//	int m_indexRow;
//	int m_indexCol;
//};

/////////////////////////////////////////
//
//crJXJUIJunLingTimesTipMethod
//ʣ�����������ʾ
//
/////////////////////////////////////////
class crJXJUIJunLingTimesTipMethod : public CRCore::crMethod
{//Client Method
public:
	crJXJUIJunLingTimesTipMethod();
	crJXJUIJunLingTimesTipMethod(const crJXJUIJunLingTimesTipMethod& handle);
	MethodClass(JXJ, JXJUIJunLingTimesTip)
		virtual void operator()(crHandle &handle);
	virtual void inputParam(int i, void *param);
	virtual void addParam(int i, const std::string& str);
protected:
	CRCore::crWidgetNode* m_this;
	std::string m_tipsCanvas;
	std::string m_tipsTextWidget;
	std::string m_canvasName;
};

/////////////////////////////////////////
//
//crJXJUIMailTipMethod
//�ʼ�������Ʒ��ʾ
//
/////////////////////////////////////////
class crJXJUIMailTipMethod : public CRCore::crMethod
{//Client Method
public:
	crJXJUIMailTipMethod();
	crJXJUIMailTipMethod(const crJXJUIMailTipMethod& handle);
	MethodClass(JXJ, JXJUIMailTip)
		virtual void operator()(crHandle &handle);
	virtual void inputParam(int i, void *param);
	virtual void addParam(int i, const std::string& str);
protected:
	CRCore::crCanvasNode* m_this;
	int m_index;
	int *m_itemid;
	std::string m_mailinput;
};

/////////////////////////////////////////
//
//crJXJGetOnlineRewardIDCaseMethod
//���߽�����Ʒ��ʾ
//
/////////////////////////////////////////
class crJXJGetOnlineRewardIDCaseMethod :public CRCore::crMethod
{//Client Method
public:
	crJXJGetOnlineRewardIDCaseMethod();
	crJXJGetOnlineRewardIDCaseMethod(const crJXJGetOnlineRewardIDCaseMethod& handle);
	MethodClass(JXJ, JXJGetOnlineRewardIDCase)
	virtual void operator()(crHandle &handle);
	virtual void inputParam(int i, void *param);
	virtual void addParam(int i, const std::string& str);
protected:
	CRCore::crWidgetNode *m_this;
	int m_rewardInput;
};
/////////////////////////////////////////
//
//crJXJUIBattleInspireTipMethod
//ս������tips
//
/////////////////////////////////////////
class crJXJUIBattleInspireTipMethod : public CRCore::crMethod
{//Client Method
public:
	crJXJUIBattleInspireTipMethod();
	crJXJUIBattleInspireTipMethod(const crJXJUIBattleInspireTipMethod& handle);
	MethodClass(JXJ,JXJUIBattleInspireTip)
		virtual void operator()(crHandle &handle);
	virtual void inputParam(int i, void *param);
	virtual void addParam(int i, const std::string& str);
protected:
	CRCore::crWidgetNode *m_this;
	std::string m_strBt;
	std::string m_tips;
	std::string m_tipstext;
	int m_str;
	unsigned short m_itemId;//������itemId
};
/////////////////////////////////////////
//
//crJXJUICopyBattleUserTipMethod
//ս������tips
//
/////////////////////////////////////////
class crJXJUICopyBattleUserTipMethod : public CRCore::crMethod
{//Client Method
public:
	crJXJUICopyBattleUserTipMethod();
	crJXJUICopyBattleUserTipMethod(const crJXJUICopyBattleUserTipMethod& handle);
	MethodClass(JXJ,JXJUICopyBattleUserTip)
		virtual void operator()(crHandle &handle);
	virtual void inputParam(int i, void *param);
	virtual void addParam(int i, const std::string& str);
protected:
	CRCore::crWidgetNode *m_this;
	std::string m_tips;
	std::string m_tipstext;
};
/////////////////////////////////////////
//
//crJXJUIHuigouTipMethod
//�ع���Ʒtips
//
/////////////////////////////////////////
class crJXJUIHuigouTipMethod : public CRCore::crMethod
{//Client Method
public:
	crJXJUIHuigouTipMethod();
	crJXJUIHuigouTipMethod(const crJXJUIHuigouTipMethod& handle);
	MethodClass(JXJ,JXJUIHuigouTip)
		virtual void operator()(crHandle &handle);
	virtual void inputParam(int i, void *param);
	virtual void addParam(int i, const std::string& str);
protected:
	CRCore::crWidgetNode *m_this;
	std::string m_tips;
	std::string m_tipstext;
	int m_index;
};

/////////////////////////////////////////
//
//crJXJUIAppointCardTipMethod
//ί�ν���tips
//
/////////////////////////////////////////
class crJXJUIAppointCardTipMethod : public CRCore::crMethod
{//Client Method
public:
	crJXJUIAppointCardTipMethod();
	crJXJUIAppointCardTipMethod(const crJXJUIAppointCardTipMethod& handle);
	MethodClass(JXJ,JXJUIAppointCardTip)
		virtual void operator()(crHandle &handle);
	virtual void inputParam(int i, void *param);
	virtual void addParam(int i, const std::string& str);
protected:
	CRCore::crWidgetNode *m_this;
	std::string m_tips;
	std::string m_tipstext;
	int m_index;
};
}
#endif 
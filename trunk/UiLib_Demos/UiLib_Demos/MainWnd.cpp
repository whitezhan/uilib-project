#include "StdAfx.h"
#include "MainWnd.h"

#define IDM_SHOW_LOG		WM_USER+2200
#define IDM_EXIT_APP		WM_USER+2300

CMainWnd::CMainWnd(void)
{
	mChartDataPos = 0;
} 


CMainWnd::~CMainWnd(void)
{
}

//************************************
// Method:    GetSkinFile
// FullName:  CMainWnd::GetSkinFile
// Access:    public 
// Returns:   UiLib::CDuiString
// Qualifier:
// Note:	  
//************************************
UiLib::CDuiString CMainWnd::GetSkinFile()
{
	try
	{
		return CDuiString(_T("MainSkin.xml"));
	}
	catch (...)
	{
		throw "CMainWnd::GetSkinFile";
	}
}

//************************************
// Method:    GetWindowClassName
// FullName:  CMainWnd::GetWindowClassName
// Access:    public 
// Returns:   LPCTSTR
// Qualifier: const
// Note:	  
//************************************
LPCTSTR CMainWnd::GetWindowClassName() const
{
	try
	{
		return _T("UiLib_Demos");
	}
	catch (...)
	{
		throw "CMainWnd::GetWindowClassName";
	}
}

//************************************
// Method:    HandleMessage
// FullName:  CMainWnd::HandleMessage
// Access:    public 
// Returns:   LRESULT
// Qualifier:
// Parameter: UINT uMsg
// Parameter: WPARAM wParam
// Parameter: LPARAM lParam
// Note:	  
//************************************
LRESULT CMainWnd::HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	try
	{
		if(lParam == WM_RBUTTONUP)
		{
			::SetForegroundWindow(this->m_hWnd);

			hMenu = CreatePopupMenu();
			AppendMenu(hMenu,MF_STRING,IDM_SHOW_LOG,_T("��ʾ��־"));
			AppendMenu(hMenu,MF_STRING,IDM_EXIT_APP,_T("�˳�����"));

			POINT point;
			point.x=LOWORD(lParam);
			point.y=HIWORD(lParam);
			GetCursorPos(&point);
			TrackPopupMenu(hMenu,TPM_RIGHTALIGN,point.x,point.y,0,m_hWnd,NULL);

			::PostMessage(m_hWnd,WM_NULL,0,0);

			return TRUE;
		}
		else if(wParam == IDM_SHOW_LOG || lParam == WM_LBUTTONDBLCLK)
		{
			this->ShowWindow();
			return TRUE;
		}
		else if(wParam == IDM_EXIT_APP)
		{
			Close(IDOK);
			return TRUE;
		}
		return IWindowBase::HandleMessage(uMsg,wParam,lParam);
	}
	catch (...)
	{
		throw "CMainWnd::HandleMessage";
	}
}

void CMainWnd::Init()
{
	try
	{
		IWindowBase::Init();

#ifndef _UNICODE
		strcpy(nid.szTip,"˫������ʾ����");//��Ϣ��ʾ��
		Shell_NotifyIconA(NIM_ADD,&nid);//������������ͼ��
#else
		wcscpy_s(nid.szTip,L"˫������ʾ����");//��Ϣ��ʾ��
		Shell_NotifyIcon(NIM_ADD,&nid);//������������ͼ��
#endif

		pAnimWnd		= static_cast<CHorizontalLayoutUI*>(pm.FindControl(_T("AnimWnd")));
		pTestLabel		= static_cast<CLabelUI*>(pm.FindControl(_T("TestLabel")));
		pChartView		= static_cast<CChartViewUI*>(pm.FindControl(_T("ChartView")));
		pEffectsDemo	= static_cast<CButtonUI*>(pm.FindControl(_T("EffectsDemo")));
		
		nid.cbSize				= (DWORD)sizeof(NOTIFYICONDATA);
		nid.hWnd				= m_hWnd;
		nid.uID					= IDI_UILIB_DEMOS;
		nid.uFlags				= NIF_ICON|NIF_MESSAGE|NIF_TIP ;
		nid.uCallbackMessage	= WM_USER + 1;
		nid.hIcon				= LoadIcon(pm.GetInstance(),MAKEINTRESOURCE(IDI_UILIB_DEMOS));

		CButtonUI*	pTextMsgBtn			= static_cast<CButtonUI*>(pm.FindControl(_T("TextMsg")));
		CButtonUI*	pAddNodeBtn			= static_cast<CButtonUI*>(pm.FindControl(_T("AddNode")));
		CButtonUI*	pAddAtNodeBtn		= static_cast<CButtonUI*>(pm.FindControl(_T("AddAtNode")));
		CButtonUI*	pCreateChartViewBtn	= static_cast<CButtonUI*>(pm.FindControl(_T("CreateChartView")));
		CButtonUI*	pAddChartDataABtn	= static_cast<CButtonUI*>(pm.FindControl(_T("AddChartDataA")));
		CButtonUI*	pAddChartDataBBtn	= static_cast<CButtonUI*>(pm.FindControl(_T("AddChartDataB")));
		CButtonUI*	pAddChartDataCBtn	= static_cast<CButtonUI*>(pm.FindControl(_T("AddChartDataC")));
		CButtonUI*	pLegendTopCBtn		= static_cast<CButtonUI*>(pm.FindControl(_T("LegendTop")));
		CButtonUI*	pLegendRightBtn		= static_cast<CButtonUI*>(pm.FindControl(_T("LegendRight")));
		CButtonUI*	pLegendBottomBtn	= static_cast<CButtonUI*>(pm.FindControl(_T("LegendBottom")));
		CButtonUI*	pDelChartDataBtn	= static_cast<CButtonUI*>(pm.FindControl(_T("DelChartData")));

		pEffectsDemo->OnNotify			+= MakeDelegate(this,&CMainWnd::OnEffectsBtnClick,_T("click"));
		pTextMsgBtn->OnNotify			+= MakeDelegate(this,&CMainWnd::OnMsgBtnClick,_T("click"));
		pTextMsgBtn->OnEvent			+= MakeDelegate(this,&CMainWnd::OnMsgBtnMouseEnter,UIEVENT_MOUSEENTER);
		pTextMsgBtn->OnEvent			+= MakeDelegate(this,&CMainWnd::OnMsgBtnMouseLeave,UIEVENT_MOUSELEAVE);
		pAddNodeBtn->OnNotify			+= MakeDelegate(this,&CMainWnd::OnAddNodeBtnClick,_T("click"));
		pAddAtNodeBtn->OnNotify			+= MakeDelegate(this,&CMainWnd::OnAddNodeBtnClick,_T("click"));
		pCreateChartViewBtn->OnNotify	+= MakeDelegate(this,&CMainWnd::OnCreateChartViewBtn,_T("click"));
		pAddChartDataABtn->OnNotify		+= MakeDelegate(this,&CMainWnd::OnAddChartDataABtn,_T("click"));
		pAddChartDataBBtn->OnNotify		+= MakeDelegate(this,&CMainWnd::OnAddChartDataBBtn,_T("click"));
		pAddChartDataCBtn->OnNotify		+= MakeDelegate(this,&CMainWnd::OnAddChartDataCBtn,_T("click"));
		pLegendTopCBtn->OnNotify		+= MakeDelegate(this,&CMainWnd::OnLegendTopBtn,_T("click"));
		pLegendRightBtn->OnNotify		+= MakeDelegate(this,&CMainWnd::OnLegendRightBtn,_T("click"));
		pLegendBottomBtn->OnNotify		+= MakeDelegate(this,&CMainWnd::OnLegendBottomBtn,_T("click"));
		pDelChartDataBtn->OnNotify		+= MakeDelegate(this,&CMainWnd::OnDelChartDataBtn,_T("click"));

	}
	catch (...)
	{
		throw "CMainWnd::Init";
	}
}

//************************************
// ��������: Notify
// ��������: void
// ������Ϣ: TNotifyUI & msg
// ����˵��: 
//************************************
void CMainWnd::Notify( TNotifyUI& msg )
{
	IWindowBase::Notify(msg);
}

//************************************
// Method:    OnFinalMessage
// FullName:  CMainWnd::OnFinalMessage
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: HWND hWnd
// Note:	  
//************************************
void CMainWnd::OnFinalMessage( HWND hWnd )
{
	try
	{
		::Shell_NotifyIcon(NIM_DELETE,&nid);

		IWindowBase::OnFinalMessage(hWnd);
		PostQuitMessage(0);
	}
	catch (...)
	{
		throw "CMainWnd::OnFinalMessage";
	}
}
//************************************
// ��������: OnMsgBtnClick
// ��������: bool
// ������Ϣ: TNotifyUI * pTNotifyUI
// ����˵��: 
//************************************
bool CMainWnd::OnMsgBtnClick( TNotifyUI* pTNotifyUI )
{
	MessageBox(m_hWnd,_T("���ǰ󶨵İ�ť�����Ϣ OK!"),_T("��Ϣ·��"),MB_OK);
	return true;
}

//************************************
// ��������: OnMsgBtnMouseEnter
// ��������: bool
// ������Ϣ: TEventUI * pTEventUI
// ����˵��: 
//************************************
bool CMainWnd::OnMsgBtnMouseEnter( TEventUI* pTEventUI )
{
	DUI__Trace(_T("���������밴ťʱ����Ϣ OK!"));
	pTEventUI->pSender->SetText(_T("��������^_^"));
	return true;
}

//************************************
// ��������: OnMsgBtnMouseLeave
// ��������: bool
// ������Ϣ: TEventUI * pTEventUI
// ����˵��: 
//************************************
bool CMainWnd::OnMsgBtnMouseLeave( TEventUI* pTEventUI )
{
	DUI__Trace(_T("��������뿪��ťʱ����Ϣ OK!"));
	pTEventUI->pSender->SetText(_T("������� T_T"));
	return true;
}

//************************************
// ��������: OnEffectsBtnClick
// ��������: bool
// ������Ϣ: TNotifyUI * pTNotifyUI
// ����˵��: 
//************************************
bool CMainWnd::OnEffectsBtnClick( TNotifyUI* pTNotifyUI )
{
	pAnimWnd->SetAnimEffects(true);
	pEffectsDemo->SetTag(pEffectsDemo->GetTag()+1);

	pm.SetCurStyles(pEffectsDemo->GetTag()%2?_T("LangChinese"):_T("LangEnglish"));

	if(pEffectsDemo->GetTag() == 1)
		pAnimWnd->SetAttribute(_T("adveffects"),_T("anim='left2right' offset='180'"));
	else if(pTNotifyUI->pSender->GetTag() == 2)
		pAnimWnd->SetAttribute(_T("adveffects"),_T("anim='right2left' offset='180'"));
	else if(pEffectsDemo->GetTag() == 3)
		pAnimWnd->SetAttribute(_T("adveffects"),_T("anim='top2bottom' offset='180'"));
	else if(pEffectsDemo->GetTag() == 4)
		pAnimWnd->SetAttribute(_T("adveffects"),_T("anim='bottom2top' offset='180'"));
	else if(pEffectsDemo->GetTag() == 5)
		pAnimWnd->SetAttribute(_T("adveffects"),_T("anim='zoom+' offset='180'"));
	else if(pEffectsDemo->GetTag() == 6)
		pAnimWnd->SetAttribute(_T("adveffects"),_T("anim='zoom-' offset='180'"));
	else if(pEffectsDemo->GetTag() == 7)
		pAnimWnd->SetAttribute(_T("adveffects"),_T("offsetx='180' rotation='0.3'"));
	else if(pEffectsDemo->GetTag() == 8)
		pAnimWnd->SetAttribute(_T("adveffects"),_T("offsetx='180' rotation='-0.3'"));
	else if(pEffectsDemo->GetTag() == 9)
		pAnimWnd->SetAttribute(_T("adveffects"),_T("offsety='180' rotation='0.3'"));
	else if(pEffectsDemo->GetTag() == 10)
		pAnimWnd->SetAttribute(_T("adveffects"),_T("offsety='180' rotation='-0.3'"));
	else
	{
		pEffectsDemo->SetTag(1);
		pAnimWnd->SetAttribute(_T("adveffects"),_T("anim='left2right' offset='80'"));
	}
	pAnimWnd->TriggerEffects();

	return true;
}

//************************************
// ��������: OnAddNodeBtnClick
// ��������: bool
// ������Ϣ: TNotifyUI * pTNotifyUI
// ����˵��: 
//************************************
bool CMainWnd::OnAddNodeBtnClick( TNotifyUI* pTNotifyUI )
{
	CEditUI* pEdit = static_cast<CEditUI*>(pm.FindControl(_T("AddNodeText")));
	if(!pEdit && pEdit->GetText().GetLength() > 0)
		return true;

	CTreeNodeUI* pParentNode = static_cast<CTreeNodeUI*>(pTNotifyUI->pSender->GetParent()->GetParent());
	if(!pParentNode || !pParentNode->GetInterface(_T("TreeNode")))
		return true;

	CFadeButtonUI* pRemoveBtn = new CFadeButtonUI();
	pRemoveBtn->SetText(_T("ɾ���ڵ�"));
	pRemoveBtn->SetName(_T("RemoveNodeBtn"));

	CTreeNodeUI* pNewNode = new CTreeNodeUI();
	pNewNode->SetItemText(pEdit->GetText().GetData());
	pParentNode->Add(pNewNode);
	pNewNode->GetTreeNodeHoriznotal()->Add(pRemoveBtn);

	pNewNode->SetStyleName(_T("treenode"));
	pRemoveBtn->SetStyleName(_T("FadeButtonDemo"),&pm);
	pRemoveBtn->SetFixedWidth(60);

	pRemoveBtn->OnNotify		+= MakeDelegate(this,&CMainWnd::OnRemoveNodeBtnClick,_T("click"));

	return true;
}

//************************************
// ��������: OnAddAtNodeBtnClick
// ��������: bool
// ������Ϣ: TNotifyUI * pTNotifyUI
// ����˵��: 
//************************************
bool CMainWnd::OnAddAtNodeBtnClick( TNotifyUI* pTNotifyUI )
{
	CTreeNodeUI* pParentNode = static_cast<CTreeNodeUI*>(pTNotifyUI->pSender->GetParent()->GetParent());
	if(!pParentNode || !pParentNode->GetInterface(_T("TreeNode")))
		return true;

	CEditUI* pEdit = static_cast<CEditUI*>(pParentNode->GetTreeNodeHoriznotal()->FindSubControl(_T("AddAtNodeText")));
	if(!pEdit && pEdit->GetText().GetLength() > 0)
		return true;

	CFadeButtonUI* pRemoveBtn = new CFadeButtonUI();
	pRemoveBtn->SetText(_T("ɾ"));
	pRemoveBtn->SetName(_T("RemoveNodeBtn"));

	CFadeButtonUI* pAddAtBtn = new CFadeButtonUI();
	pAddAtBtn->SetText(_T("����ڵ�"));
	pAddAtBtn->SetName(_T("AddAtNode"));

	CEditUI* pAddEdit = new CEditUI();
	pAddEdit->SetName(_T("AddAtNodeText"));
	pAddEdit->SetText(_T("�ڵ�����"));
	pAddEdit->SetTipValue(_T("�ڵ�����"));

	CTreeNodeUI* pNewNode = new CTreeNodeUI();
	pNewNode->SetItemText(pEdit->GetText().GetData());
	pParentNode->AddAt(pNewNode,0);
	pNewNode->GetTreeNodeHoriznotal()->Add(pAddEdit);
	pNewNode->GetTreeNodeHoriznotal()->Add(pAddAtBtn);
	pNewNode->GetTreeNodeHoriznotal()->Add(pRemoveBtn);

	pNewNode->SetStyleName(_T("treenode"));
	pAddAtBtn->SetStyleName(_T("FadeButtonDemo"),&pm);
	pRemoveBtn->SetStyleName(_T("FadeButtonDemo"),&pm);
	pAddEdit->SetFixedWidth(50);
	pAddAtBtn->SetFixedWidth(60);
	pRemoveBtn->SetFixedWidth(20);


	pRemoveBtn->OnNotify		+= MakeDelegate(this,&CMainWnd::OnRemoveNodeBtnClick,_T("click"));

	return true;
}

//************************************
// ��������: OnRemoveNodeBtnClick
// ��������: bool
// ������Ϣ: TNotifyUI * pTNotifyUI
// ����˵��: 
//************************************
bool CMainWnd::OnRemoveNodeBtnClick( TNotifyUI* pTNotifyUI )
{
	CTreeNodeUI* pParentNode = static_cast<CTreeNodeUI*>(pTNotifyUI->pSender->GetParent()->GetParent());
	if(!pParentNode || !pParentNode->GetInterface(_T("TreeNode")))
		return true;

	if(pParentNode->GetParentNode())
		pParentNode->GetParentNode()->Remove(pParentNode);

	return true;
}

//************************************
// ��������: OnCreateChartViewBtn
// ��������: bool
// ������Ϣ: TNotifyUI * pTNotifyUI
// ����˵��: 
//************************************
bool CMainWnd::OnCreateChartViewBtn( TNotifyUI* pTNotifyUI )
{
	//pChartView->GetXYAxis().SetTickLimis(-50,100,20);
	pChartView->AddLabel(_T("һ��"));
	pChartView->AddLabel(_T("����"));
	pChartView->AddLabel(_T("����"));
	pChartView->AddLabel(_T("����"));

	return true;
}

//************************************
// ��������: OnAddChartDataABtn
// ��������: bool
// ������Ϣ: TNotifyUI * pTNotifyUI
// ����˵��: 
//************************************
bool CMainWnd::OnAddChartDataABtn( TNotifyUI* pTNotifyUI )
{
	if(!pChartView->GetGroupCount())
		return true;

	CDuiString mLegend;
	mLegend.Format(_T("����ͼ��%d"),mChartDataPos++);
	CChartSeries* pSeriesA = new CChartSeries(mLegend,Color(rand()%256,rand()%256,rand()%256).GetValue(),Color(rand()%256,rand()%256,rand()%256).GetValue());

	for(int nIndex = 0;(UINT)nIndex < pChartView->GetGroupCount();nIndex++){
		pSeriesA->AddSeriesData(rand()%100-50);
	}
	pChartView->AddSeries(pSeriesA);

	return true;
}

//************************************
// ��������: OnAddChartDataBBtn
// ��������: bool
// ������Ϣ: TNotifyUI * pTNotifyUI
// ����˵��: 
//************************************
bool CMainWnd::OnAddChartDataBBtn( TNotifyUI* pTNotifyUI )
{
	if(!pChartView->GetGroupCount())
		return true;

	CDuiString mLegend;
	mLegend.Format(_T("����ͼ��%d"),mChartDataPos++);
	CChartSeries* pSeriesA = new CChartSeries(mLegend,Color(rand()%256,rand()%256,rand()%256).GetValue(),Color(rand()%256,rand()%256,rand()%256).GetValue());

	for(int nIndex = 0;(UINT)nIndex < pChartView->GetGroupCount();nIndex++){
		pSeriesA->AddSeriesData(rand()%151);
	}
	pChartView->AddSeries(pSeriesA);

	return true;
}

//************************************
// ��������: OnAddChartDataCBtn
// ��������: bool
// ������Ϣ: TNotifyUI * pTNotifyUI
// ����˵��: 
//************************************
bool CMainWnd::OnAddChartDataCBtn( TNotifyUI* pTNotifyUI )
{
	if(!pChartView->GetGroupCount())
		return true;

	CDuiString mLegend;
	mLegend.Format(_T("����ͼ��%d"),mChartDataPos++);
	CChartSeries* pSeriesA = new CChartSeries(mLegend,Color(rand()%256,rand()%256,rand()%256).GetValue(),Color(rand()%256,rand()%256,rand()%256).GetValue());

	for(int nIndex = 0;(UINT)nIndex < pChartView->GetGroupCount();nIndex++){
		pSeriesA->AddSeriesData(rand()%151-151);
	}
	pChartView->AddSeries(pSeriesA);

	return true;
}

//************************************
// ��������: OnLegendTopBtn
// ��������: bool
// ������Ϣ: TNotifyUI * pTNotifyUI
// ����˵��: 
//************************************
bool CMainWnd::OnLegendTopBtn( TNotifyUI* pTNotifyUI )
{
	pChartView->GetXYAxis().SetLegendLocation(LOCATION_TOP);
	return true;
}

//************************************
// ��������: OnLegendRightBtn
// ��������: bool
// ������Ϣ: TNotifyUI * pTNotifyUI
// ����˵��: 
//************************************
bool CMainWnd::OnLegendRightBtn( TNotifyUI* pTNotifyUI )
{
	pChartView->GetXYAxis().SetLegendLocation(LOCATION_RIGHT);
	return true;
}

//************************************
// ��������: OnLegendBottomBtn
// ��������: bool
// ������Ϣ: TNotifyUI * pTNotifyUI
// ����˵��: 
//************************************
bool CMainWnd::OnLegendBottomBtn( TNotifyUI* pTNotifyUI )
{
	pChartView->GetXYAxis().SetLegendLocation(LOCATION_BOTTOM);
	return true;
}

//************************************
// ��������: OnDelChartDataBtn
// ��������: bool
// ������Ϣ: TNotifyUI * pTNotifyUI
// ����˵��: 
//************************************
bool CMainWnd::OnDelChartDataBtn( TNotifyUI* pTNotifyUI )
{
	pChartView->RemoveSeries(0);
	return true;
}
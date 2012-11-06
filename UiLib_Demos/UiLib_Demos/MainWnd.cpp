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
			AppendMenu(hMenu,MF_STRING,IDM_SHOW_LOG,_T("显示日志"));
			AppendMenu(hMenu,MF_STRING,IDM_EXIT_APP,_T("退出程序"));

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

//************************************
// Method:    Init
// FullName:  CMainWnd::Init
// Access:    public 
// Returns:   void
// Qualifier:
// Note:	  
//************************************
void CMainWnd::Init()
{
	try
	{
		IWindowBase::Init();
		pAnimWnd		= static_cast<CHorizontalLayoutUI*>(pm.FindControl(_T("AnimWnd")));
		pTestEdit		= static_cast<CEditUI*>(pm.FindControl(_T("TestEdit")));
		pTestLabel		= static_cast<CLabelUI*>(pm.FindControl(_T("TestLabel")));
		pChartView		= static_cast<CChartViewUI*>(pm.FindControl(_T("ChartView")));
		pEffectsDemo	= static_cast<CButtonUI*>(pm.FindControl(_T("EffectsDemo")));
		
		nid.cbSize				= (DWORD)sizeof(NOTIFYICONDATA);
		nid.hWnd				= m_hWnd;
		nid.uID					= IDI_UILIB_DEMOS;
		nid.uFlags				= NIF_ICON|NIF_MESSAGE|NIF_TIP ;
		nid.uCallbackMessage	= WM_USER + 1;
		nid.hIcon				= LoadIcon(pm.GetInstance(),MAKEINTRESOURCE(IDI_UILIB_DEMOS));

#ifndef _UNICODE
		strcpy(nid.szTip,"双击主显示界面");//信息提示条
		Shell_NotifyIconA(NIM_ADD,&nid);//在托盘区添加图标
#else
		wcscpy_s(nid.szTip,L"双击主显示界面");//信息提示条
		Shell_NotifyIcon(NIM_ADD,&nid);//在托盘区添加图标
#endif
	}
	catch (...)
	{
		throw "CMainWnd::Init";
	}
}

//************************************
// Method:    Notify
// FullName:  CMainWnd::Notify
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: TNotifyUI & msg
// Note:	  
//************************************
void CMainWnd::Notify( TNotifyUI& msg )
{
	try
	{
		if(msg.sType == _T("click")){
			if(msg.pSender->GetName() == _T("EffectsDemo"))
			{
				pAnimWnd->SetAnimEffects(true);
				pEffectsDemo->SetTag(pEffectsDemo->GetTag()+1);

				pm.SetCurStyles(pEffectsDemo->GetTag()%2?_T("LangChinese"):_T("LangEnglish"));

				if(pEffectsDemo->GetTag() == 1)
					pAnimWnd->SetAttribute(_T("adveffects"),_T("anim='left2right' offset='180'"));
				else if(msg.pSender->GetTag() == 2)
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
			}
			else if(msg.pSender->GetName() == _T("AddNode")){
				CEditUI* pEdit = static_cast<CEditUI*>(pm.FindControl(_T("AddNodeText")));
				if(!pEdit && pEdit->GetText().GetLength() > 0)
					return;

				CTreeNodeUI* pParentNode = static_cast<CTreeNodeUI*>(msg.pSender->GetParent()->GetParent());
				if(!pParentNode || !pParentNode->GetInterface(_T("TreeNode")))
					return;

				CFadeButtonUI* pRemoveBtn = new CFadeButtonUI();
				pRemoveBtn->SetText(_T("删除节点"));
				pRemoveBtn->SetName(_T("RemoveNodeBtn"));

				CTreeNodeUI* pNewNode = new CTreeNodeUI();
				pNewNode->SetItemText(pEdit->GetText().GetData());
				pParentNode->Add(pNewNode);
				pNewNode->GetTreeNodeHoriznotal()->Add(pRemoveBtn);

				pNewNode->SetStyleName(_T("treenode"));
				pRemoveBtn->SetStyleName(_T("FadeButtonDemo"),&pm);
				pRemoveBtn->SetFixedWidth(60);
			}
			else if(msg.pSender->GetName() == _T("AddAtNode")){
				CTreeNodeUI* pParentNode = static_cast<CTreeNodeUI*>(msg.pSender->GetParent()->GetParent());
				if(!pParentNode || !pParentNode->GetInterface(_T("TreeNode")))
					return;

				CEditUI* pEdit = static_cast<CEditUI*>(pParentNode->GetTreeNodeHoriznotal()->FindSubControl(_T("AddAtNodeText")));
				if(!pEdit && pEdit->GetText().GetLength() > 0)
					return;

				CFadeButtonUI* pRemoveBtn = new CFadeButtonUI();
				pRemoveBtn->SetText(_T("删"));
				pRemoveBtn->SetName(_T("RemoveNodeBtn"));

				CFadeButtonUI* pAddAtBtn = new CFadeButtonUI();
				pAddAtBtn->SetText(_T("插入节点"));
				pAddAtBtn->SetName(_T("AddAtNode"));

				CEditUI* pAddEdit = new CEditUI();
				pAddEdit->SetName(_T("AddAtNodeText"));
				pAddEdit->SetText(_T("节点名称"));
				pAddEdit->SetTipValue(_T("节点名称"));

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
			}
			else if(msg.pSender->GetName() == _T("RemoveNodeBtn")){
				CTreeNodeUI* pParentNode = static_cast<CTreeNodeUI*>(msg.pSender->GetParent()->GetParent());
				if(!pParentNode || !pParentNode->GetInterface(_T("TreeNode")))
					return;

				if(pParentNode->GetParentNode())
					pParentNode->GetParentNode()->Remove(pParentNode);
			}
			else if(msg.pSender->GetName() == _T("CreateChartView")){

				//pChartView->GetXYAxis().SetTickLimis(-50,100,20);
				pChartView->AddLabel(_T("一月"));
				pChartView->AddLabel(_T("二月"));
				pChartView->AddLabel(_T("三月"));
				pChartView->AddLabel(_T("四月"));

			}
			else if(msg.pSender->GetName() == _T("AddChartDataA") && pChartView->GetGroupCount()){
				CDuiString mLegend;
				mLegend.Format(_T("测试图例%d"),mChartDataPos++);
				CChartSeries* pSeriesA = new CChartSeries(mLegend,Color(rand()%256,rand()%256,rand()%256).GetValue(),Color(rand()%256,rand()%256,rand()%256).GetValue());

				for(int nIndex = 0;(UINT)nIndex < pChartView->GetGroupCount();nIndex++){
					pSeriesA->AddSeriesData(rand()%100-50);
				}
				pChartView->AddSeries(pSeriesA);
			}
			else if(msg.pSender->GetName() == _T("AddChartDataB") && pChartView->GetGroupCount()){
				CDuiString mLegend;
				mLegend.Format(_T("测试图例%d"),mChartDataPos++);
				CChartSeries* pSeriesA = new CChartSeries(mLegend,Color(rand()%256,rand()%256,rand()%256).GetValue(),Color(rand()%256,rand()%256,rand()%256).GetValue());

				for(int nIndex = 0;(UINT)nIndex < pChartView->GetGroupCount();nIndex++){
					pSeriesA->AddSeriesData(rand()%151);
				}
				pChartView->AddSeries(pSeriesA);
			}
			else if(msg.pSender->GetName() == _T("AddChartDataC") && pChartView->GetGroupCount()){
				CDuiString mLegend;
				mLegend.Format(_T("测试图例%d"),mChartDataPos++);
				CChartSeries* pSeriesA = new CChartSeries(mLegend,Color(rand()%256,rand()%256,rand()%256).GetValue(),Color(rand()%256,rand()%256,rand()%256).GetValue());

				for(int nIndex = 0;(UINT)nIndex < pChartView->GetGroupCount();nIndex++){
					pSeriesA->AddSeriesData(rand()%151-151);
				}
				pChartView->AddSeries(pSeriesA);
			}
			else if(msg.pSender->GetName() == _T("LegendTop")){
				pChartView->GetXYAxis().SetLegendLocation(LOCATION_TOP);
			}
			else if(msg.pSender->GetName() == _T("LegendRight")){
				pChartView->GetXYAxis().SetLegendLocation(LOCATION_RIGHT);
			}
			else if(msg.pSender->GetName() == _T("LegendBottom")){
				pChartView->GetXYAxis().SetLegendLocation(LOCATION_BOTTOM);
			}
			else if(msg.pSender->GetName() == _T("DelChartData")){
				pChartView->RemoveSeries(0);
			}
		}
		if(msg.sType == _T("OnEditTimer") && msg.pSender == pTestEdit){
			pTestLabel->SetText(msg.pSender->GetText().GetData());
			pTestLabel->NeedUpdate();
		}
		else if(msg.sType == _T("OnSelectDate"))
		{
			MessageBox(m_hWnd,_T("Test"),NULL,MB_OK);
		}

		IWindowBase::Notify(msg);
	}
	catch (...)
	{
		throw "CMainWnd::Notify";
	}
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

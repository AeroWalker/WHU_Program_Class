
// ex3p5Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "ex3p5.h"
#include "ex3p5Dlg.h"
#include "afxdialogex.h"
#include <algorithm>

//#include "./RobotPlus.cpp"
#include <Windows.h>
#include <tchar.h>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void Sort_Name();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cex3p5Dlg 对话框



Cex3p5Dlg::Cex3p5Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EX3P5_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cex3p5Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, RobotListCtr);
}

BEGIN_MESSAGE_MAP(Cex3p5Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_ID, &Cex3p5Dlg::IDSort)
	ON_COMMAND(ID_Name, &Cex3p5Dlg::NameSort)
	ON_COMMAND(ID_IQ, &Cex3p5Dlg::IQSort)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST1, &Cex3p5Dlg::OnLvnColumnclickList1)
END_MESSAGE_MAP()


// Cex3p5Dlg 消息处理程序

BOOL Cex3p5Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	RobotListCtr.InsertColumn(0, _T("ID"), LVCFMT_CENTER, 160);
	RobotListCtr.InsertColumn(1, _T("Name"), LVCFMT_CENTER, 240);
	RobotListCtr.InsertColumn(2, _T("IQ"), LVCFMT_CENTER, 160);

	vector<Robot> RobotArr = Robot::Readxml("robots.xml");
	sort(RobotArr.begin(), RobotArr.end(), Robot::CompareItem(-1));
	AddToList(RobotArr);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Cex3p5Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Cex3p5Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Cex3p5Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void Cex3p5Dlg::IDSort()
{

	vector<Robot> RobotArr = Robot::Readxml("robots.xml");
	sort(RobotArr.begin(), RobotArr.end(), Robot::CompareItem(0));
	AddToList(RobotArr);

	

	// TODO: 在此添加命令处理程序代码
}

void Cex3p5Dlg::AddToList(vector<Robot> ToAdd)
{
	RobotListCtr.DeleteAllItems();
	for (Robot i : ToAdd)
	{
		int nRow = RobotListCtr.InsertItem(0, CString(i.ID.c_str()));
		RobotListCtr.SetItemText(nRow, 1, CString(i.Name.c_str()));
		RobotListCtr.SetItemText(nRow, 2, CString(i.IQ.c_str()));
	}
}




//void CAboutDlg::Sort_Name()
//{
//
//}


void Cex3p5Dlg::NameSort()
{
	// TODO: 在此添加命令处理程序代码
	vector<Robot> RobotArr = Robot::Readxml("robots.xml");
	sort(RobotArr.begin(), RobotArr.end(), Robot::CompareItem(1));
	AddToList(RobotArr);

}


void Cex3p5Dlg::IQSort()
{
	vector<Robot> RobotArr = Robot::Readxml("robots.xml");
	sort(RobotArr.begin(), RobotArr.end(), Robot::CompareItem(2));
	AddToList(RobotArr);
	// TODO: 在此添加命令处理程序代码
}


void Cex3p5Dlg::OnLvnColumnclickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int sort_column = pNMLV->iSubItem;
	vector<Robot> RobotArr = Robot::Readxml("robots.xml");
	sort(RobotArr.begin(), RobotArr.end(), Robot::CompareItem(sort_column));
	AddToList(RobotArr);
	*pResult = 0;
}

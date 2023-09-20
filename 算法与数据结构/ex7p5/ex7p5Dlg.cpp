
// ex7p5Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "ex7p5.h"
#include "ex7p5Dlg.h"
#include "afxdialogex.h"

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


// Cex7p5Dlg 对话框



Cex7p5Dlg::Cex7p5Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EX7P5_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cex7p5Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, mytree);
}

BEGIN_MESSAGE_MAP(Cex7p5Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &Cex7p5Dlg::OnTvnSelchangedTree1)
	ON_BN_CLICKED(IDOK, &Cex7p5Dlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT1, &Cex7p5Dlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// Cex7p5Dlg 消息处理程序

BOOL Cex7p5Dlg::OnInitDialog()
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Cex7p5Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Cex7p5Dlg::OnPaint()
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
	Inij_Tree();
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Cex7p5Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cex7p5Dlg::OnTvnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


int Cex7p5Dlg::Inij_Tree()
{
	HTREEITEM hroot = mytree.InsertItem(_T("武汉大学"));
	HTREEITEM hroot_sub1 = mytree.InsertItem(_T("电子信息学院"), hroot);
	HTREEITEM hroot_sub2 = mytree.InsertItem(_T("计算机学院"), hroot);
	//HTREEITEM hroot_sub3 = mytree.InsertItem(_T("son3"), hroot);
	HTREEITEM hroot_sub1_sub1 = mytree.InsertItem(_T("通讯工程系"), hroot_sub1);
	HTREEITEM hroot_sub1_sub2 = mytree.InsertItem(_T("测控技术与仪器系"), hroot_sub1);
	HTREEITEM hroot_sub1_sub3 = mytree.InsertItem(_T("空间物理系"), hroot_sub1);
	HTREEITEM hroot_sub1_sub4 = mytree.InsertItem(_T("电子工程系"), hroot_sub1);
	HTREEITEM hroot_sub1_sub5 = mytree.InsertItem(_T("光电信息工程系"), hroot_sub1);
	//HTREEITEM hroot_sub3_sub1 = mytree.InsertItem(_T("孙子3-1"), hroot_sub3);
	//HTREEITEM hroot_sub3_sub2 = mytree.InsertItem(_T("孙子3-2"), hroot_sub3);
	static UINT opcode = TVE_EXPAND;
	//扩展父节点
	mytree.Expand (hroot, opcode);

	// TODO: 在此处添加实现代码.
	return 0;
}

//#include "../ex7p2/BinaryTree.cpp"
void Cex7p5Dlg::OnBnClickedOk()
{
	//mytree.DeleteAllItems();

	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}


void Cex7p5Dlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

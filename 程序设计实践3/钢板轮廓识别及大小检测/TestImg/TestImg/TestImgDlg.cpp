
// TestImgDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "TestImg.h"
#include "TestImgDlg.h"
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


// CTestImgDlg 对话框



CTestImgDlg::CTestImgDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TESTIMG_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestImgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestImgDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CTestImgDlg::OnBnClickedButtonLoad)
END_MESSAGE_MAP()


// CTestImgDlg 消息处理程序

BOOL CTestImgDlg::OnInitDialog()
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

	 //namedWindow("SteelImg1", WINDOW_AUTOSIZE);
	//HWND hWnd = (HWND)cvGetWindowHandle("SteelImg1");
	//HWND hParent = (HWND)::GetParent(hWnd);
	//::SetParent(hWnd, GetDlgItem(IDC_STATIC_IMG0)->m_hWnd);
	//::ShowWindow(hParent, SW_HIDE);

	CString fname;
	m_uId[0] = IDC_STATIC_IMG0;
	m_uId[1] = IDC_STATIC_IMG1;
	m_uId[2] = IDC_STATIC_IMG2;
	m_uId[3] = IDC_STATIC_IMG3;
	m_uId[4] = IDC_STATIC_IMG4;
	m_uId[5] = IDC_STATIC_IMG5;
	m_uId[6] = IDC_STATIC_IMG6;
	m_uId[7] = IDC_STATIC_IMG7;
	m_uId[8] = IDC_STATIC_IMG8;




	HWND hParent = NULL;

	for (int i = 1; i < 10; i++)
	{
		fname.Format("%d", i);
		m_wndName[i - 1] = "SteelImg" + fname;
		const char* pwndname = m_wndName[i - 1].GetBuffer(m_wndName[i - 1].GetLength());
		namedWindow(string(m_wndName[i - 1]), WINDOW_AUTOSIZE);
		HWND hWnd = (HWND)cvGetWindowHandle(pwndname);
		hParent = (HWND)::GetParent(hWnd);
		::SetParent(hWnd, GetDlgItem(m_uId[i - 1])->m_hWnd);
		::ShowWindow(hParent, SW_HIDE);
	}



	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTestImgDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTestImgDlg::OnPaint()
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
HCURSOR CTestImgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTestImgDlg::GetSerialFname()
{
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY);
	CString strfname;
	CString strfpath;
	CString strfExt;
	CString strfTitle;
	if (dlg.DoModal() == IDOK)
	{
		strfname = dlg.GetFileName();
		strfpath = dlg.GetPathName();
		strfExt = dlg.GetFileExt();
	}
	//strfname = "20070728_170504_03.bmp";

	int strfnamelen = strfname.GetLength();
	int strfpathlen = strfpath.GetLength();

	strfpath.Delete(strfpathlen - strfnamelen, strfnamelen);

	CString strfnroot;
	strfnroot = strfname;
	strfnroot.Delete(strfnroot.GetLength() - 6, 6);

	//AfxMessageBox(strfname);
	//AfxMessageBox(strfpath);
	//AfxMessageBox(strfExt);
	//AfxMessageBox(strfnroot);


	for (int i = 0; i < 9; i++)
	{
		CString curfn;
		CString fullname;
		curfn.Format("%d", i + 1);
		curfn = "0" + curfn;
		fullname = strfnroot + curfn;
		fullname = strfpath + fullname + ".bmp";
		m_fnameary[i] = fullname;


	}


}

void CTestImgDlg::OnBnClickedButtonLoad()
{
	// TODO: 在此添加控件通知处理程序代码

	//int cx, cy;
	//CRect rect, pic_rect;
	//int width, height;

	//GetDlgItem(IDC_STATIC_IMG0)->GetClientRect(&pic_rect);
	//width = pic_rect.right;
	//height = pic_rect.bottom;
	//
	////m_fnameary[0] = "D:\\教学\\summer-term\\steelimg\\20070728_175631_06.bmp";
	//m_wndName[0] = "SteelImg1";

	//GetSerialFname();
	////============open file============
	//CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY);
	//CString strfname;
	//CString strfpath;
	//if (dlg.DoModal() == IDOK)
	//{
	//	strfpath = dlg.GetPathName();

	//}

	////===============open file=======
	//	
	////m_steelImg[0] = imread(string(m_fnameary[0]));
	//m_steelImg[0] = imread(string(strfpath));
	//resize(m_steelImg[0], m_showsteelImg[0], Size(width, height));
	//imshow(string(m_wndName[0]), m_showsteelImg[0]);

	GetSerialFname();

	LoadSerialImg();
}


void CTestImgDlg::LoadSerialImg()
{

	int cx, cy;
	CRect rect, pic_rect;
	int width, height;

	GetDlgItem(IDC_STATIC_IMG1)->GetClientRect(&pic_rect);
	width = pic_rect.right;
	height = pic_rect.bottom;



	for (int i = 0; i < 9; i++)
	{
		m_steelImg[i] = imread(string(m_fnameary[i]));

		resize(m_steelImg[i], m_showsteelImg[i], Size(width, height));
		imshow(string(m_wndName[i]), m_showsteelImg[i]);


	}

	

}


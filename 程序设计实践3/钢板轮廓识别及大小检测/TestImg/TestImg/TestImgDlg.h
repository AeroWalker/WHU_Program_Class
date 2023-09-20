
// TestImgDlg.h: 头文件
//
#include <opencv2/opencv.hpp>
#include <vector>
using namespace cv;
using namespace std;



#pragma once


// CTestImgDlg 对话框
class CTestImgDlg : public CDialogEx
{
// 构造
public:
	CTestImgDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TESTIMG_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonLoad();

public:
	Mat m_steelImg[9];
	Mat m_showsteelImg[9];
	CString m_wndName[9];
	UINT m_uId[9];
	UINT m_uIdMode[9];
	CString m_fnameary[9];
	int m_nMode[9];
	int m_nCurCamreno;

	Point2f m_rect[9][4];

	float m_xfratio;
	float m_yfratio;
public:
	void GetSerialFname();
	void LoadSerialImg();
};

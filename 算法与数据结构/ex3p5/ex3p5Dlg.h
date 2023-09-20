
// ex3p5Dlg.h: 头文件
//
#pragma once
#include <vector>
using namespace std;
#include "RobotPlus.cpp"

// Cex3p5Dlg 对话框
class Cex3p5Dlg : public CDialogEx
{
// 构造
public:
	Cex3p5Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EX3P5_DIALOG };
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
	afx_msg void IDSort();
	CListCtrl RobotListCtr;
	void AddToList(vector<Robot> ToAdd);
	afx_msg void NameSort();
	afx_msg void IQSort();
	afx_msg void OnLvnColumnclickList1(NMHDR* pNMHDR, LRESULT* pResult);
	vector<Robot> rarr;
};

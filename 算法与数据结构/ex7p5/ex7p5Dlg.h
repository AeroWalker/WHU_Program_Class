
// ex7p5Dlg.h: 头文件
//

#pragma once


// Cex7p5Dlg 对话框
class Cex7p5Dlg : public CDialogEx
{
// 构造
public:
	Cex7p5Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EX7P5_DIALOG };
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
	afx_msg void OnTvnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult);
	int Inij_Tree();
	CTreeCtrl mytree;
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEdit1();
};

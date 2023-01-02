
// PVZCheaterDlg.h: 头文件
//

#pragma once


// CPVZCheaterDlg 对话框
class CPVZCheaterDlg : public CDialogEx
{
	// 构造
public:
	CPVZCheaterDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PVZCHEATER_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 声明
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedYG();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedJump();
	afx_msg void OnBnClickedKillzb();
	CButton m_bnKillZb;
	// 无限阳光
	CButton m_bnCheckYG;
	//监视游戏句柄
	HANDLE m_monitorThread;
	//友元函数
	friend DWORD WINAPI monitorThreadFunc(LPVOID);

};

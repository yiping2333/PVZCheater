
// PVZCheaterDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "PVZCheater.h"
#include "PVZCheaterDlg.h"
#include "afxdialogex.h"
#include "process.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//宏定义弹窗
#define log(fmt,...) CString str_log;str_log.Format(CString(fmt),__VA_ARGS__);MessageBox(str_log);

//定义全局对话框变量
CPVZCheaterDlg* g_dlg;
void infinitySun();
//获取进程句柄

//监控游戏线程
DWORD WINAPI monitorThreadFunc(LPVOID paramter) {
	HWND game;
	HWND lastTime = NULL;
	while (1) {
		//判断植物大战僵尸是否打开
		game = FindWindow(L"MainWindow", L"植物大战僵尸中文版");

		//基本状态处理
		if (game != lastTime) {
			if (game == NULL) {
				g_dlg->m_bnCheckYG.SetCheck(false);
				g_dlg->m_bnCheckYG.EnableWindow(false);
				g_dlg->m_bnKillZb.SetCheck(false);
				g_dlg->m_bnKillZb.EnableWindow(false);
				g_processHandle = NULL;
			}
			else {
				g_dlg->m_bnCheckYG.EnableWindow(true);
				g_dlg->m_bnKillZb.EnableWindow(true);

				DWORD threadId = NULL;
				GetWindowThreadProcessId(game, &threadId);
				g_processHandle = OpenProcess(PROCESS_ALL_ACCESS, false, threadId);
			}
			lastTime = game;
		}

		//游戏内处理
		if (g_processHandle != NULL) {
			//无限阳光
			infinitySun();
		}
		Sleep(1000);
	}
	return NULL;
}

void infinitySun() {
	if (!g_dlg->m_bnCheckYG.GetCheck()) {
		return;
	}
	DWORD sun = 9990;
	WriteProcessMemory(g_processHandle, (LPVOID)0x1111, &sun, sizeof(sun), NULL);
	WriteMemory(&sun, sizeof(sun), 0x6A9EC0, 0x320, 0x8, 0x0, 0x8, 0x144, 0x2c, 0x5560, -1);
}

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


// CPVZCheaterDlg 对话框



CPVZCheaterDlg::CPVZCheaterDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PVZCHEATER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPVZCheaterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_KILLZB, m_bnKillZb);
	DDX_Control(pDX, IDC_CHECK_YG, m_bnCheckYG);
}

BEGIN_MESSAGE_MAP(CPVZCheaterDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHECK_YG, CPVZCheaterDlg::OnBnClickedYG)
	ON_BN_CLICKED(IDC_JUMP, &CPVZCheaterDlg::OnBnClickedJump)
	ON_BN_CLICKED(IDC_KILLZB, &CPVZCheaterDlg::OnBnClickedKillzb)
END_MESSAGE_MAP()


// CPVZCheaterDlg 消息处理程序

BOOL CPVZCheaterDlg::OnInitDialog()
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

	//创建监视游戏的线程
	m_monitorThread = CreateThread(NULL, NULL, monitorThreadFunc, NULL, NULL, NULL);
	//返回全局对话框变量
	g_dlg = this;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CPVZCheaterDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPVZCheaterDlg::OnPaint()
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
HCURSOR CPVZCheaterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




//无限阳光按钮点击
void CPVZCheaterDlg::OnBnClickedYG() {

	/*CString str;
	str.Format(CString("哈哈哈%d"), age);
	MessageBox(str, CString("警告"), MB_YESNOCANCEL);*/
	/*if (IsDlgButtonChecked(IDC_CHECK_YG)) {
		int age = 20;
		log("age is %d", age);

	}*/
	/*log("hahaha");*/

}

//跳转网页
void CPVZCheaterDlg::OnBnClickedJump()
{
	ShellExecute(NULL,
		CString("open"),//要做什么
		CString("https://www.baidu.com"),//链接
		NULL, NULL,
		SW_SHOWNORMAL//展示模式
	);
}


//秒杀僵尸
void CPVZCheaterDlg::OnBnClickedKillzb()
{

	if (m_bnKillZb.GetCheck()) {//秒杀僵尸
		BYTE data[] = { 0xFF,0x90,0x90 };
		WriteProcessMemory(g_processHandle, (LPVOID)0x00531310, data, sizeof(data), NULL);
	}
	else {
		BYTE data[] = { 0x7C,0x24,0x20 };
		WriteProcessMemory(g_processHandle, (LPVOID)0x00531310, data, sizeof(data), NULL);
	}
}

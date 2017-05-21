
// ChsChessDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ChsChess.h"
#include "ChsChessDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChsChessDlg 对话框




CChsChessDlg::CChsChessDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChsChessDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChsChessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CChsChessDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDOK, &CChsChessDlg::OnBnClickedOk)
    ON_BN_CLICKED(IDCANCEL, &CChsChessDlg::OnBnClickedCancel)
    ON_BN_CLICKED(IDC_OK, &CChsChessDlg::OnBnClickedOk)
    ON_BN_CLICKED(IDC_CANCEL, &CChsChessDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CChsChessDlg 消息处理程序

BOOL CChsChessDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CChsChessDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CChsChessDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CChsChessDlg::OnOK()
{
    // TODO: 在此添加专用代码和/或调用基类
    TRACE("CChsChessDlg::OnOK()\n");
    //CDialog::OnOK();
}

void CChsChessDlg::OnCancel()
{
    // TODO: 在此添加专用代码和/或调用基类
    TRACE("CChsChessDlg::OnCancel()\n");
    //CDialog::OnCancel();
}

void CChsChessDlg::OnBnClickedOk()
{
    // TODO: 在此添加控件通知处理程序代码
    TRACE("CChsChessDlg::OnBnClickedOk()\n");
    //CDialog::OnOK();
}

void CChsChessDlg::OnBnClickedCancel()
{
    // TODO: 在此添加控件通知处理程序代码
    TRACE("CChsChessDlg::OnBnClickedCancel()\n");
    //CDialog::OnCancel();
}

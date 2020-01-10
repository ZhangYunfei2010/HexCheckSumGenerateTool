
// HexCheckSumGenerateToolDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "HexCheckSumGenerateTool.h"
#include "HexCheckSumGenerateToolDlg.h"
#include "Utils.h"
#include "HexTools.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHexCheckSumGenerateToolDlg 对话框



CHexCheckSumGenerateToolDlg::CHexCheckSumGenerateToolDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_HEXCHECKSUMGENERATETOOL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHexCheckSumGenerateToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_FILEPATH, m_txtFilePath);
	DDX_Control(pDX, IDC_EDIT_CHECK_SUM, m_txtCheckSum);
	DDX_Control(pDX, IDC_EDIT_STRING, m_txtString);
}

BEGIN_MESSAGE_MAP(CHexCheckSumGenerateToolDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BUTTON_OPENFILE, &CHexCheckSumGenerateToolDlg::OnBnClickedButtonOpenfile)
	ON_BN_CLICKED(IDC_BUTTON_FILE_GENERATE, &CHexCheckSumGenerateToolDlg::OnBnClickedButtonFileGenerate)
	ON_BN_CLICKED(IDC_BUTTON_STR_GENERATE, &CHexCheckSumGenerateToolDlg::OnBnClickedButtonStrGenerate)
END_MESSAGE_MAP()


// CHexCheckSumGenerateToolDlg 消息处理程序

BOOL CHexCheckSumGenerateToolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CHexCheckSumGenerateToolDlg::OnPaint()
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
HCURSOR CHexCheckSumGenerateToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CHexCheckSumGenerateToolDlg::OnBnClickedButtonOpenfile()
{
    // TODO: 在此添加控件通知处理程序代码
    CFileDialog dlg(TRUE/*这个参数为TRUE就是“打开”对话框，为FALSE就是“保存”对话框*/
		, L"txt"/*默认文件类型*/
		, NULL/*默认文件名*/
		, OFN_HIDEREADONLY/*样式，这里设置为“隐藏只读”*/
		, _T("Text file(*.txt)|*.txt|Hex file(*.hex)|*.hex|Hxd file(*.hxd)|*.hxd|All files(*.*)|*.*||")/*文件类型列表*/
		, NULL, NULL, FALSE/*指定文件打开对话框是否为Vista样式*/);
	if (dlg.DoModal() == IDOK)//如果用户在文件对话框中点击了“确定”按钮
    {
        m_txtFilePath.SetWindowTextW(dlg.GetPathName());//获取文件路径到strPathName
    }
}


void CHexCheckSumGenerateToolDlg::OnBnClickedButtonFileGenerate()
{
	// TODO: 在此添加控件通知处理程序代码
    CString inFileName;
    m_txtFilePath.GetWindowTextW(inFileName);
    CString outFileName;
    int pos = inFileName.ReverseFind(L'.');
    outFileName = inFileName;
    outFileName.Insert(pos, L"_out");

    std::string inFileNameStr, outFileNameStr;
    Utils::WStrToStr(inFileName.GetBuffer(), inFileNameStr);
    Utils::WStrToStr(outFileName.GetBuffer(), outFileNameStr);
	if (!HexTools::GenerateCheckSum(inFileNameStr.c_str(), outFileNameStr.c_str())) {
		MessageBox(L"Fail");
	}
	else {
		MessageBox(L"Success");
	}
}


void CHexCheckSumGenerateToolDlg::OnBnClickedButtonStrGenerate()
{
	// TODO: 在此添加控件通知处理程序代码
	CString hex;
	m_txtString.GetWindowTextW(hex);
	std::string hexStr;
	Utils::WStrToStr(hex.GetBuffer(), hexStr);
	char checkSum[3];
	if (!HexTools::GenerateCheckSum(hexStr.c_str(), checkSum)) {
		MessageBox(L"Fail");
	}
	else {
		std::wstring checkSumStr;
		Utils::StrToWStr(checkSum, checkSumStr);
		m_txtCheckSum.SetWindowTextW(checkSumStr.c_str());
	}
}

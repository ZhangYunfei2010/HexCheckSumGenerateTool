
// HexCheckSumGenerateToolDlg.h: 头文件
//

#pragma once


// CHexCheckSumGenerateToolDlg 对话框
class CHexCheckSumGenerateToolDlg : public CDialog
{
// 构造
public:
	CHexCheckSumGenerateToolDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HEXCHECKSUMGENERATETOOL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    CEdit m_txtFilePath;
    CEdit m_txtCheckSum;
    afx_msg void OnBnClickedButtonOpenfile();
    afx_msg void OnBnClickedButtonFileGenerate();
    afx_msg void OnBnClickedButtonStrGenerate();
    CEdit m_txtString;
};

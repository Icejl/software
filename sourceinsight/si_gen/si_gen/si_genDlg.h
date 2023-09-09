
// si_genDlg.h: 头文件
//

#pragma once


// CsigenDlg 对话框
class CsigenDlg : public CDialogEx
{
// 构造
public:
	CsigenDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SI_GEN_DIALOG };
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
	afx_msg void OnBnClickedOk();
	CStatic m_info;
	afx_msg void OnEnChangeEdit1();
	CEdit m_serial;
	CEdit m_user;
	CEdit m_mail;
};

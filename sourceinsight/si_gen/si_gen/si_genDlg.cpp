
// si_genDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "si_gen.h"
#include "si_genDlg.h"
#include "afxdialogex.h"
#include <sddl.h>

#include "base64.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma warning(disable : 6011)
#pragma warning(disable : 6386)

// CsigenDlg 对话框

CsigenDlg::CsigenDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SI_GEN_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CsigenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_USER, m_user);
	DDX_Control(pDX, IDC_EDIT_MAIL, m_mail);
}

BEGIN_MESSAGE_MAP(CsigenDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CsigenDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CsigenDlg 消息处理程序

BOOL CsigenDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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

void CsigenDlg::OnPaint()
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
HCURSOR CsigenDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CHAR * wchar2byte(LPCWSTR wbuf)
{
	DWORD dBufSize = WideCharToMultiByte(CP_OEMCP, 0, wbuf, -1, NULL, 0, NULL, FALSE);

	CHAR* szbuf = new char[dBufSize];
	memset(szbuf, 0, dBufSize);

	int nRet = WideCharToMultiByte(CP_OEMCP, 0, wbuf, -1, szbuf, dBufSize, NULL, FALSE);
	if (nRet <= 0)
	{
		return 0;
	}
	return szbuf;
}

UCHAR byte_5D8B98[] = {0x32, 0xDF, 0x71, 0xB7, 0x61, 0x3D, 0x6B, 0x57, 0xD7, 0xA1,
0x34, 0x38, 0xF2, 0xE1, 0xF3, 0xB8, 0x23, 0xDD, 0x78, 0xB5,
0x33, 0x6F, 0xD4, 0xF9, 0xA6, 0xE8, 0xCC, 0x7C, 0x9F, 0xB3,
0x22, 0xDA, 0x37, 0xF1, 0x2F, 0x4E, 0xE7, 0x6A, 0x75, 0xA8,
0x26, 0xEB, 0x3F, 0x6C, 0x69, 0x20, 0x87, 0x62, 0xA7, 0x41,
0x96, 0x90, 0xB4, 0x42, 0x63, 0x99, 0xD0, 0x4D, 0x97, 0xBE,
0x40, 0xCF, 0x84, 0xE5, 0x1D, 0x5A, 0x0C, 0x7F, 0xC7, 0xEA,
0xEE, 0xEC, 0x00, 0xD5, 0x49, 0x2D, 0x51, 0xAD, 0xB9, 0x89,
0x1A, 0x80, 0xF5, 0xFE, 0x91, 0x01, 0x3C, 0x73, 0x93, 0x48,
0xA0, 0xE0, 0x94, 0xAA, 0x39, 0x8F, 0x58, 0xE2, 0x31, 0x0B,
0xBB, 0xCE, 0x4C, 0xD2, 0x56, 0xC2, 0x5E, 0x27, 0xB6, 0xFB,
0x65, 0xAE, 0x9A, 0xB0, 0xEF, 0x36, 0xC5, 0x72, 0x5B, 0x7E,
0x54, 0x2C, 0x0F, 0xF6, 0xA9, 0x85, 0x2A, 0xB1, 0x55, 0x60,
0xBD, 0x10, 0x86, 0xF7, 0xC1, 0x88, 0x12, 0xED, 0x67, 0xC4,
0x74, 0x30, 0x1B, 0xBC, 0x77, 0x52, 0x3E, 0x8C, 0xE6, 0xFF,
0x15, 0xDE, 0x6D, 0x14, 0xA2, 0xCD, 0xA3, 0xD6, 0x17, 0x81,
0x8D, 0x68, 0xA5, 0xFA, 0x3A, 0x04, 0x21, 0x1F, 0xAC, 0x05,
0xA4, 0x76, 0x11, 0x70, 0x9E, 0x46, 0x24, 0x5D, 0xC6, 0xE4,
0x95, 0x82, 0x1C, 0xBA, 0x59, 0x09, 0xD9, 0x44, 0x98, 0x92,
0x07, 0xAF, 0xC8, 0x45, 0x4B, 0x35, 0x0A, 0x0D, 0xFC, 0x9D,
0x16, 0x3B, 0xD3, 0x7D, 0xD1, 0xF4, 0xFD, 0xCA, 0x8E, 0x4F,
0xE3, 0xC9, 0x8B, 0xDC, 0x5C, 0xC0, 0x1E, 0x9B, 0x18, 0x02,
0x47, 0x03, 0x2B, 0x0E, 0x25, 0x06, 0x6E, 0xF8, 0x5F, 0xBF,
0x8A, 0x7B, 0x50, 0xD8, 0x79, 0x9C, 0xAB, 0x43, 0x53, 0xCB,
0x66, 0x4A, 0xB2, 0xF0, 0xE9, 0x19, 0x29, 0x7A, 0xC3, 0x08,
0x83, 0xDB, 0x64, 0x13, 0x2E, 0x28 };

unsigned char byte_607280[] =
{
  0x23, 0xDD, 0x78, 0xB5, 0x33, 0x6F, 0xD4, 0xF9, 0xA6, 0xE8,
  0xCC, 0x7C, 0x9F, 0xB3, 0x22, 0xDA, 0x32, 0xDF, 0x71, 0xB7,
  0x61, 0x3D, 0x6B, 0x57, 0xD7, 0xA1, 0x34, 0x38, 0xF2, 0xE1,
  0xF3, 0xB8, 0x1A, 0x80, 0xF5, 0xFE, 0x91, 0x01, 0x3C, 0x73,
  0x93, 0x48, 0xA0, 0xE0, 0x94, 0xAA, 0x39, 0x8F, 0x58, 0xE2,
  0x31, 0x0B, 0xBB, 0xCE, 0x4C, 0xD2, 0x56, 0xC2, 0x5E, 0x27,
  0xB6, 0xFB, 0x65, 0xAE, 0x55, 0x60, 0xBD, 0x10, 0x86, 0xF7,
  0xC1, 0x88, 0x12, 0xED, 0x67, 0xC4, 0x74, 0x30, 0x1B, 0xBC,
  0x9A, 0xB0, 0xEF, 0x36, 0xC5, 0x72, 0x5B, 0x7E, 0x54, 0x2C,
  0x0F, 0xF6, 0xA9, 0x85, 0x2A, 0xB1, 0x37, 0xF1, 0x2F, 0x4E,
  0xE7, 0x6A, 0x75, 0xA8, 0x26, 0xEB, 0x3F, 0x6C, 0x69, 0x20,
  0x87, 0x62, 0x8D, 0x68, 0xA5, 0xFA, 0x3A, 0x04, 0x21, 0x1F,
  0xAC, 0x05, 0xA4, 0x76, 0x11, 0x70, 0x9E, 0x46, 0x24, 0x5D,
  0xC6, 0xE4, 0x95, 0x82, 0x1C, 0xBA, 0x59, 0x09, 0xD9, 0x44,
  0x98, 0x92, 0x07, 0xAF, 0xA7, 0x41, 0x96, 0x90, 0xB4, 0x42,
  0x63, 0x99, 0xD0, 0x4D, 0x97, 0xBE, 0x40, 0xCF, 0x84, 0xE5,
  0x1D, 0x5A, 0x0C, 0x7F, 0xC7, 0xEA, 0xEE, 0xEC, 0x00, 0xD5,
  0x49, 0x2D, 0x51, 0xAD, 0xB9, 0x89, 0x77, 0x52, 0x3E, 0x8C,
  0xE6, 0xFF, 0x15, 0xDE, 0x6D, 0x14, 0xA2, 0xCD, 0xA3, 0xD6,
  0x17, 0x81, 0xC8, 0x45, 0x4B, 0x35, 0x0A, 0x0D, 0xFC, 0x9D,
  0x16, 0x3B, 0xD3, 0x7D, 0xD1, 0xF4, 0xFD, 0xCA, 0x25, 0x06,
  0x6E, 0xF8, 0x5F, 0xBF, 0x8A, 0x7B, 0x50, 0xD8, 0x79, 0x9C,
  0xAB, 0x43, 0x53, 0xCB, 0x8E, 0x4F, 0xE3, 0xC9, 0x8B, 0xDC,
  0x5C, 0xC0, 0x1E, 0x9B, 0x18, 0x02, 0x47, 0x03, 0x2B, 0x0E,
  0x66, 0x4A, 0xB2, 0xF0, 0xE9, 0x19, 0x29, 0x7A, 0xC3, 0x08,
  0x83, 0xDB, 0x64, 0x13, 0x2E, 0x28
};

LPSTR actid_arr[] = { "0A51", "C762", "87A8", "0AD6", "673A", "A478", "13DC", 
"49F9", "61B5", "A360", "16F5", "74E6", "3E93", "L555", "52A9", "5B36", "3BF2",
"557A", "F358", "F148", "F509", "00D0", "08F1", "F661", "B755", "4F26", "FE7E", 
"047E", "1C67", "0E90", "7B3E", "03A1", "D2F4", "1F3F", "C603", "D775", "4B67", 
"68E3", "DA22", "18E3", "365D", "FA17", "0F09", "55E0", "08E5", "1EA4", "83A6", "44D3", "76B6" };

LPSTR sig_temp = "<SourceInsightLicense>\n\
\t<LicenseProperties\n\
\t\tType=\"Standard\"\n\
\t\tLicensedUser=\"%s\"\n\
\t\tOrganization=\"%s\"\n\
\t\tEmail=\"%s\"\n\
\t\tActId=\"%s\"\n\
\t\tVersion=\"4\"\n\
\t\tinorVersion=\"0\"\n\
\t\tDate=\"%s\"\n\
\t\tExpiration=\"%s\"\n\
\t\tSerial=\"%s\">\n\
\t</LicenseProperties>\n\
\t<Signature Value=\"%s\">\n\
\t</Signature>\n\
</SourceInsightLicense>";


LPSTR sig_temp2 = "<!--\n"
"\tSource Insight 4.x License File\n"
"\n"
"\tDO NOT EDIT THIS FILE. Doing so will render it unusable.\n"
"\n"
"\tThis license was created for:\n"
"\n"
"\t\t%s\n"
"\t\t%s\n"
"\t\t%s\n"
"\n"
"-->\n"
"<SourceInsightLicense>\n"
"\t<LicenseProperties\n"
"\t\tActId=\"%s\"\n"
"\t\tSerial=\"%s\"\n"
"\t\tLicensedUser=\"%s\"\n"
"\t\tOrganization=\"%s\"\n"
"\t\tEmail=\"%s\"\n"
"\t\tType=\"%s\"\n"
"\t\tVersion=\"%d\"\n"
"\t\tMinorVersion=\"%d\"\n"
"\t\tDate=\"%s\"\n"
"\t\tExpiration=\"%s\">\n"
"\t</LicenseProperties>\n"
"\t<Signature Value=\"%s\">\n"
"\t</Signature>\n"
"</SourceInsightLicense>";


LPSTR crypt(int x, int y, CHAR* data, int data_len)
{
	LPSTR buffer = (LPSTR)malloc(y+1);
	if (!buffer)
		return 0;
	memset(buffer, 0, y + 1);
	for (int i = 0; i < y; i++)
	{
		UCHAR t = byte_5D8B98[(x + i + data[0]) % 256];
		for (int j = 1; j < data_len; j++)
		{
			t = byte_5D8B98[t ^ data[j]];
		}
		buffer[i] = t;
	}
	return buffer;
}


BOOL get_VolId( LPSTR guid )
{
	CHAR volname[256];
	LPSTR szVol = "\\\\?\\Volume{";
	DWORD size = sizeof(volname);
	GetVolumeNameForVolumeMountPointA("c:\\", volname, size);
	int len = strlen(szVol);
	if (memcmp(szVol, volname, len))
	{
		return FALSE;
	}
	memcpy(guid,volname + len,36);
	return TRUE;
}

 LPSTR get_sid()
{
	HANDLE hToken = 0;
	LPSTR sid = 0;
	PSID* psid = 0;
	DWORD len = 0;
	if (!OpenProcessToken(GetCurrentProcess(), 0x8, &hToken))
	{
		AfxMessageBox(L"OpenProcessToken failed");
		return 0;
	}
	if (GetTokenInformation(hToken, TokenUser,0,0,&len) || GetLastError() == ERROR_INSUFFICIENT_BUFFER)
	{
		psid = (PSID*)malloc(len);
		if (GetTokenInformation(hToken, TokenUser, psid, len, &len))
		{
			ConvertSidToStringSidA(*psid, &sid);
			CloseHandle(hToken);
			return sid;
		}
	}
	AfxMessageBox(L"get sid failed");
	return 0;
}

BOOL get_ComputeName(LPSTR buffer)
{
	DWORD size = 256;
	GetComputerNameA(buffer,&size);
	return TRUE;
}

LPSTR strip( LPSTR data , LPSTR str )
{
	int len = strlen(data);
	LPSTR buffer = (LPSTR)malloc(len+1);
	int j = 0;
	for (int i = 0; i < len ; i++)
	{
		if (!strchr(str, data[i]))
		{
			buffer[j++] = data[i];
		}
	}
	buffer[j] = 0;
	return buffer;
}

LPSTR calc_serial()
{
	LPSTR serial = (LPSTR)malloc(20);
	strcpy_s(serial, 20, "S4UG-XXXX-XXXX-XXXX");

	for (int i = 0; i < 20; i++)
	{
		if (serial[i] == 'X')
		{
			serial[i] = 'A' + rand() % 26;
		}
	}

	srand((unsigned)time(NULL));
	serial[6] = "RGDF"[rand()%4];

	int len = 15;
	char* tab = "KV96GMJYH7QF5TCW4U3XZPRSDN";
	for (int i = 0; i < 4; i++)
	{
		UCHAR t = byte_607280[i + serial[0]];
		for (int j = 1; j < len; j++)
		{
			t = byte_607280[t ^ serial[j]];
		}
		serial[i+15] = tab[t % strlen(tab)];
	}
	return serial;
}

void CsigenDlg::OnBnClickedOk()
{
	CHAR buffer[1024] = {0};
	CHAR buffer2[2048] = { 0 };
	CHAR buffer3[2048] = { 0 };
	CHAR name[256] = {0};
	CHAR guid[256] = {0};
	CHAR actId[256] = { 0 };

	if (m_user.GetWindowTextLengthW() == 0)
	{
		AfxMessageBox(L"请输入用户名！");
		return;
	}

	if (m_mail.GetWindowTextLengthW() == 0)
	{
		AfxMessageBox(L"请输入邮箱！");
		return;
	}


	LPSTR sid = get_sid();
	get_ComputeName(name);
	get_VolId(guid);

	// 计算actID
	sprintf_s(buffer, 1024, "%s%s%s", guid, sid, name);


	LPSTR actId2 = crypt(1961, 4, buffer, strlen(buffer));
	UINT id;
	memcpy(&id, actId2, 4);
	sprintf_s(actId, sizeof(actId), "%s%u", actid_arr[rand()%(sizeof(actid_arr)/sizeof(actid_arr[0]))], id);

	// 计算serial
	LPSTR serial = calc_serial();

	CString cstr;
	m_user.GetWindowTextW(cstr);
	LPSTR user = wchar2byte(cstr.GetString());

	m_mail.GetWindowTextW(cstr);
	LPSTR email = wchar2byte(cstr.GetString());

	LPSTR organ = "Personal";

	CHAR curDate[100];
	CHAR expDate[100];

	SYSTEMTIME st;
	GetLocalTime(&st);

	COleDateTime dt1;
	COleDateTimeSpan span;
	span.m_span = 365 * 5;
	dt1.SetDate(st.wYear, st.wMonth, st.wDay);
	dt1 += span;
	
	sprintf_s(curDate, sizeof(curDate), "%4d-%02d-%02d", st.wYear, st.wMonth, st.wDay);
	sprintf_s(expDate, sizeof(expDate), "%4d-%02d-%02d", dt1.GetYear(), dt1.GetMonth(), dt1.GetDay());

	//sprintf_s(buffer2, sizeof(buffer2), sig_temp, user, organ, email, actId, curDate, expDate, serial, "%s");
	sprintf_s(buffer2, sizeof(buffer2), sig_temp2, user, organ, email, actId, serial\
		, user, organ, email,"Standard",4,0, curDate, expDate, "%s");

	LPSTR temp = strip(buffer2, "\r\n\t ");
	LPSTR p = strstr(temp, "<Signature");
	*p = 0;

	int len = strlen(temp);

	LPSTR p2 = crypt(1968, 128, temp, len+1);

	LPSTR sig = (LPSTR)malloc(128 * 2);
	base64_encode((unsigned char*)p2, 128, (unsigned char*)sig, 128 * 2);


	len = sprintf_s(buffer3, sizeof(buffer3), buffer2, sig);

	SetDlgItemTextA(CWnd::GetSafeHwnd(), IDC_EDIT_SERIAL, buffer3);

	CFile cf;
	if (len > 0 && cf.Open(L"si4.lic", CFile::modeCreate | CFile::modeReadWrite))
	{
		cf.Write(buffer3, len);
		cf.Flush();
		cf.Close();

		AfxMessageBox(L"si4.lic文件生成成功！");
	}

	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}

// MFCApplication1Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include <fstream> // For file operations

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Implementation
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

// CMFCApplication1Dlg dialog
CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent),
	m_cpuLimit(100), m_overrideFanSpeed(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	// Bind controls
	DDX_Control(pDX, IDC_CPU, m_cpuProgress);
	DDX_Control(pDX, IDC_GPU2, m_gpuProgress);
	DDX_Control(pDX, IDC_FAN, m_fanProgress);
	DDX_Control(pDX, IDC_TEMP, m_tempProgress);
	DDX_Control(pDX, IDC_EDIT1, m_editLimit);
	DDX_Control(pDX, IDC_EDIT2, m_editFanSpeed);
}



BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDOK, &CMFCApplication1Dlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT1, &CMFCApplication1Dlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &CMFCApplication1Dlg::OnEnChangeEdit2)
END_MESSAGE_MAP()

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set up progress bars
	m_cpuProgress.SetRange(0, 100);
	m_gpuProgress.SetRange(0, 100);
	m_fanProgress.SetRange(0, 100);
	m_tempProgress.SetRange(0, 100);

	// Start timer for updates
	SetTimer(1, 500, nullptr); // 500ms interval

	return TRUE;
}

void CMFCApplication1Dlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1) // Timer ID
	{
		UpdateCPUProgress();
		UpdateGPUProgress();
		UpdateFanProgress();
		UpdateTempProgress();
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CMFCApplication1Dlg::UpdateCPUProgress()
{
	static int value = 0;
	static bool increasing = true;

	if (increasing)
	{
		value += 5;
		if (value >= m_cpuLimit) increasing = false;
	}
	else
	{
		value -= 5;
		if (value <= 0) increasing = true;
	}

	m_cpuProgress.SetPos(value);
}

void CMFCApplication1Dlg::UpdateGPUProgress()
{
	std::ifstream file("gpu_usage.txt");
	if (file.is_open())
	{
		int gpuUsage;
		file >> gpuUsage;
		file.close();

		m_gpuProgress.SetPos(gpuUsage);
	}
}

void CMFCApplication1Dlg::UpdateFanProgress()
{
	if (m_overrideFanSpeed)
	{
		return; // Use manually set fan speed
	}

	std::ifstream file("fan_speed.txt");
	if (file.is_open())
	{
		int fanSpeed;
		file >> fanSpeed;
		file.close();

		m_fanProgress.SetPos(fanSpeed);
	}
}

void CMFCApplication1Dlg::UpdateTempProgress()
{
	std::ifstream file("temperature.txt");
	if (file.is_open())
	{
		int temp;
		file >> temp;
		file.close();

		m_tempProgress.SetPos(temp);

		// Change progress bar color based on temperature
		CWnd* pWnd = GetDlgItem(IDC_TEMP);
		if (pWnd)
		{
			COLORREF color = RGB(0, 0, 255); // Blue
			if (temp > 60)
				color = RGB(255, 0, 0); // Red
			else if (temp >= 50)
				color = RGB(255, 165, 0); // Orange

			CBrush brush(color);
			CClientDC dc(pWnd);
			CRect rect;
			pWnd->GetClientRect(&rect);
			dc.FillRect(&rect, &brush);
		}
	}
}



void CMFCApplication1Dlg::OnEnChangeEdit1()
{
	CString strValue;
	m_editLimit.GetWindowText(strValue);
	int newLimit = _ttoi(strValue);

	if (newLimit < 0) newLimit = 0;
	if (newLimit > 100) newLimit = 100;

	m_cpuLimit = newLimit;
}

void CMFCApplication1Dlg::OnEnChangeEdit2()
{
	CString strValue;
	m_editFanSpeed.GetWindowText(strValue);
	int fanSpeed = _ttoi(strValue);

	if (fanSpeed >= 0 && fanSpeed <= 100)
	{
		m_fanProgress.SetPos(fanSpeed);
		m_overrideFanSpeed = true;
	}
}

void CMFCApplication1Dlg::OnBnClickedOk()
{
	CDialogEx::OnOK();
}

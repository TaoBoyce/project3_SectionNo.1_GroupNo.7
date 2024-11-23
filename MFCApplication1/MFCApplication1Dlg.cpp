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

// CMFCApplication1Dlg dialog
CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent),
	m_cpuLimit(100), m_powerLimit(100), m_overrideFanSpeed(false), m_overridePower(false)
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
	DDX_Control(pDX, IDC_POWER, m_powerProgress);
	DDX_Control(pDX, IDC_EDIT1, m_editLimit);
	DDX_Control(pDX, IDC_EDIT2, m_editFanSpeed);
	DDX_Control(pDX, IDC_EDIT3, m_editPowerLimit);
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
	ON_EN_CHANGE(IDC_EDIT3, &CMFCApplication1Dlg::OnEnChangeEdit3)
	ON_BN_CLICKED(IDC_WIFION, &CMFCApplication1Dlg::OnBnClickedWifiOn)
	ON_BN_CLICKED(IDC_WIFIOFF, &CMFCApplication1Dlg::OnBnClickedWifiOff)
END_MESSAGE_MAP()

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set up progress bars
	m_cpuProgress.SetRange(0, 100);
	m_gpuProgress.SetRange(0, 100);
	m_fanProgress.SetRange(0, 100);
	m_tempProgress.SetRange(0, 100);
	m_powerProgress.SetRange(0, 100);
	// Initialize the WiFi progress bar and state
	m_wifiProgress.SetRange(0, 100);
	m_wifiProgress.SetPos(0);
	m_isWifiOn = true; // Default: WiFi reading is active

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
		UpdatePowerProgress();
		UpdateWiFiProgress(); // Add WiFi update logic
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

void CMFCApplication1Dlg::UpdatePowerProgress()
{
	if (m_overridePower)
	{
		return; // Use manually set power value
	}

	std::ifstream file("power_usage.txt");
	if (file.is_open())
	{
		int powerUsage;
		file >> powerUsage;
		file.close();

		m_powerProgress.SetPos(powerUsage);
	}
}

void CMFCApplication1Dlg::UpdateWiFiProgress()
{
	if (!m_isWifiOn) // Stop updating if WiFi is off
		return;

	static int wifiValue = 0; // Example: WiFi usage value from the file
	CStdioFile file;
	CString line;

	// Open and read the WiFi data file
	if (file.Open(_T("wifi_data.txt"), CFile::modeRead | CFile::typeText))
	{
		if (file.ReadString(line))
		{
			wifiValue = _ttoi(line); // Convert to integer
			m_wifiProgress.SetPos(wifiValue); // Update the progress bar
		}
		file.Close();
	}
	else
	{
		// Handle error if file is not found
		AfxMessageBox(_T("WiFi data file not found!"), MB_ICONERROR);
		m_isWifiOn = false; // Stop updating
	}
}


void CMFCApplication1Dlg::OnDestroy()
{
	KillTimer(1);
	CDialogEx::OnDestroy();
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

void CMFCApplication1Dlg::OnEnChangeEdit3()
{
	CString strValue;
	m_editPowerLimit.GetWindowText(strValue);
	int powerLimit = _ttoi(strValue);

	if (powerLimit >= 0 && powerLimit <= 100)
	{
		m_powerProgress.SetPos(powerLimit);
		m_overridePower = true;
	}
}

void CMFCApplication1Dlg::OnBnClickedWifiOn()
{
	m_isWifiOn = true; // Enable WiFi reading
}

void CMFCApplication1Dlg::OnBnClickedWifiOff()
{
	m_isWifiOn = false; // Disable WiFi reading
}


void CMFCApplication1Dlg::OnBnClickedOk()
{
	CDialogEx::OnOK();
}
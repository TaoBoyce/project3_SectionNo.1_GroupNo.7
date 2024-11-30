#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include "FanSpeedMonitor.h"
#include<string>
// For file operations

#ifdef _DEBUG
#define new DEBUG_NEW
#define TEMP_UPDATE_TIMER 1
#endif



// CMFCApplication1Dlg dialog
CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent),
	m_cpuLimit(100), m_powerLimit(100), m_fanActualSpeed(0), m_overrideFanSpeed(false), m_overridePower(false),
	m_currentTemp(0), m_targetTemp(0) // Initialize temperature variables
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
	DDX_Control(pDX, IDC_WIFI2, m_wifiProgress);
	DDX_Control(pDX, IDC_LIGHT, m_progressLight);

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
	ON_BN_CLICKED(IDC_RED, &CMFCApplication1Dlg::OnBnClickedRed)
	ON_BN_CLICKED(IDC_GREEN, &CMFCApplication1Dlg::OnBnClickedGreen)
	ON_BN_CLICKED(IDC_BLUE, &CMFCApplication1Dlg::OnBnClickedBlue)
	ON_BN_CLICKED(IDC_PURPLE, &CMFCApplication1Dlg::OnBnClickedPurple)
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
	m_wifiProgress.SetRange(0, 100);
	m_isWifiOn = true;
	m_progressLight.SetRange(0, 100); // Set range
	m_progressLight.SetPos(100);


	m_cpuFile.open("cpu_usage.txt");
	m_gpuFile.open("gpu_usage.txt");
	m_fanFile.open("fan_speed.txt");
	m_tempFile.open("temperature.txt");
	m_powerFile.open("power_usage.txt");
	m_wifiFile.open("wifi_data.txt");

	// Start timer for updates
	SetTimer(TEMP_UPDATE_TIMER, 1000, nullptr); // 1000ms interval

	return TRUE;
}

void CMFCApplication1Dlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == TEMP_UPDATE_TIMER) // Timer ID
	{
		UpdateCPUProgress();
		UpdateGPUProgress();
		UpdateFanProgress();
		UpdateTempProgress();
		UpdatePowerProgress();
		UpdateWiFiProgress();
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CMFCApplication1Dlg::UpdateCPUProgress()
{
	if (m_cpuLimit)
	{
		// Continue reading the file but do not change the progress bar if the fan speed is overridden.
		std::string line;
		if (std::getline(m_cpuFile, line))
		{
			int temp = std::stoi(line); // Process the temperature
			if (temp < m_cpuLimit)
			{
				m_cpuProgress.SetPos(temp);
			}
			m_previousTemp = temp;
		}
	}

	if (!m_cpuFile.is_open())
	{
		m_cpuFile.open("cpu_usage.txt");
	}

	std::string line;
	if (std::getline(m_cpuFile, line))
	{
		int temp = std::stoi(line); // Process the temperature
		m_cpuProgress.SetPos(temp);
	}
	else
	{
		m_cpuFile.clear(); // Clear EOF flag
		m_cpuFile.seekg(0, std::ios::beg); // Reset to the beginning
	}
}

void CMFCApplication1Dlg::UpdateGPUProgress()
{
	if (!m_gpuFile.is_open())
	{
		m_gpuFile.open("gpu_usage.txt");
	}

	std::string line;
	if (std::getline(m_gpuFile, line))
	{
		int temp = std::stoi(line); // Process the temperature
		m_gpuProgress.SetPos(temp);
	}
	else
	{
		m_gpuFile.clear(); // Clear EOF flag
		m_gpuFile.seekg(0, std::ios::beg); // Reset to the beginning
	}
}

void CMFCApplication1Dlg::UpdateFanProgress()
{
	FanSpeedMonitor f;
	f.setRPM(m_fanActualSpeed);



	if (m_overrideFanSpeed) {

		int speed = f.getFluctuatingRPM();
		double fanPerc = (double)speed / (double)MAX_FAN_RPM;
		fanPerc = fanPerc * 100;

		m_fanProgress.SetPos(fanPerc);
	}

}

void CMFCApplication1Dlg::UpdateTempProgress()
{
	if (!m_tempFile.is_open())
	{
		m_tempFile.open("temperature.txt");
	}

	std::string line;
	if (std::getline(m_tempFile, line))
	{
		int temp = std::stoi(line); // Process the temperature
		m_tempProgress.SetPos(temp);
	}
	else
	{
		m_tempFile.clear(); // Clear EOF flag
		m_tempFile.seekg(0, std::ios::beg); // Reset to the beginning
	}
}

void CMFCApplication1Dlg::UpdatePowerProgress()
{
	if (m_overridePower)
	{
		// Continue reading the file but do not change the progress bar if the fan speed is overridden.
		std::string line;
		if (std::getline(m_powerFile, line))
		{
			int temp = std::stoi(line); // Process the temperature
			if (temp < m_overridePower)
			{
				m_powerProgress.SetPos(temp);
			}
			m_previousTemp = temp;
		}
	}

	if (!m_powerFile.is_open())
	{
		m_powerFile.open("power_usage.txt");
	}

	std::string line;
	if (std::getline(m_powerFile, line))
	{
		int temp = std::stoi(line); // Process the temperature
		m_powerProgress.SetPos(temp);
	}
	else
	{
		m_powerFile.clear(); // Clear EOF flag
		m_powerFile.seekg(0, std::ios::beg); // Reset to the beginning
	}
}

void CMFCApplication1Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	KillTimer(TEMP_UPDATE_TIMER);

}

void CMFCApplication1Dlg::OnEnChangeEdit1()
{
	CString strValue;
	m_editLimit.GetWindowText(strValue);
	int newLimit = _ttoi(strValue);



	m_cpuLimit = newLimit;
	m_cpuProgress.SetPos(newLimit);
}

void CMFCApplication1Dlg::OnEnChangeEdit2()
{
	CString strValue;
	m_editFanSpeed.GetWindowText(strValue);
	int fanSpeed = _ttoi(strValue);

	FanSpeedMonitor f;
	if (f.setRPM(fanSpeed)) {
		m_overrideFanSpeed = true;
		m_fanActualSpeed = f.getRPM();
	}

	int speed = f.getFluctuatingRPM();
	double fanPerc = (double)speed / (double)MAX_FAN_RPM;
	fanPerc = fanPerc * 100;

	m_fanProgress.SetPos(fanPerc);

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

void CMFCApplication1Dlg::UpdateWiFiProgress()
{
	if (!m_isWifiOn) // Stop updating if WiFi is off
		return;

	if (!m_wifiFile.is_open())
	{
		m_wifiFile.open("wifi_data.txt");
	}

	std::string line;
	if (std::getline(m_wifiFile, line))
	{
		int temp = std::stoi(line); // Process the temperature
		m_wifiProgress.SetPos(temp);
	}
	else
	{
		m_wifiFile.clear(); // Clear EOF flag
		m_wifiFile.seekg(0, std::ios::beg); // Reset to the beginning
	}

}

void CMFCApplication1Dlg::OnBnClickedWifiOn()
{
	m_isWifiOn = true; // Enable WiFi reading
}

void CMFCApplication1Dlg::OnBnClickedWifiOff()
{
	m_isWifiOn = false; // Disable WiFi reading
	m_wifiProgress.SetPos(0);
}

void CMFCApplication1Dlg::OnBnClickedOk()
{
	CDialogEx::OnOK();
}

// PreTranslateMessage to clear text on pressing Enter for all IDC_EDIT controls
BOOL CMFCApplication1Dlg::PreTranslateMessage(MSG* pMsg)
{
	// Check if the message is a key press (WM_KEYDOWN)
	if (pMsg->message == WM_KEYDOWN)
	{
		// Check if the pressed key is the Enter key (VK_RETURN)
		if (pMsg->wParam == VK_RETURN)
		{
			// Handle the Enter key for IDC_EDIT controls to prevent closing the dialog
			CEdit* pEditCtrl = (CEdit*)GetFocus(); // Get the currently focused control
			if (pEditCtrl)
			{
				// Get the current value and re-set it, to ensure the limit is kept
				CString strValue;
				pEditCtrl->GetWindowText(strValue); // Get text from the control
				int newLimit = _ttoi(strValue); // Convert the text to an integer

				// Optionally, validate the value to stay within limits
				if (newLimit < 0) newLimit = 0;
				if (newLimit > 100) newLimit = 100;

				// Depending on the control, update the corresponding variable
				if (pEditCtrl == &m_editLimit)
				{
					m_cpuLimit = newLimit;
				}
				else if (pEditCtrl == &m_editFanSpeed)
				{
					m_overrideFanSpeed = true;  // Set manual override flag
				}
				else if (pEditCtrl == &m_editPowerLimit)
				{
					m_powerLimit = newLimit;
					m_overridePower = true;  // Set manual override flag
				}

				// Optionally, update the control to show the validated value
				pEditCtrl->SetWindowText(strValue);
			}

			return TRUE;  // Return TRUE to indicate that the message has been handled
		}
	}

	// Default handling for other messages
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CMFCApplication1Dlg::OnBnClickedRed()
{
	CWnd* pWnd = GetDlgItem(IDC_LIGHT);

	COLORREF color = RGB(255, 0, 0); // Red

	CBrush brush(color);
	CClientDC dc(pWnd);
	CRect rect;
	pWnd->GetClientRect(&rect);
	dc.FillRect(&rect, &brush);

}


void CMFCApplication1Dlg::OnBnClickedGreen()//
{
	CWnd* pWnd = GetDlgItem(IDC_LIGHT);

	COLORREF color = RGB(0, 128, 0); // Red

	CBrush brush(color);
	CClientDC dc(pWnd);
	CRect rect;
	pWnd->GetClientRect(&rect);
	dc.FillRect(&rect, &brush);
}


void CMFCApplication1Dlg::OnBnClickedBlue()
{
	CWnd* pWnd = GetDlgItem(IDC_LIGHT);

	COLORREF color = RGB(0, 0, 255); // Red

	CBrush brush(color);
	CClientDC dc(pWnd);
	CRect rect;
	pWnd->GetClientRect(&rect);
	dc.FillRect(&rect, &brush);
}


void CMFCApplication1Dlg::OnBnClickedPurple()
{
	CWnd* pWnd = GetDlgItem(IDC_LIGHT);

	COLORREF color = RGB(128, 0, 128); // Red

	CBrush brush(color);
	CClientDC dc(pWnd);
	CRect rect;
	pWnd->GetClientRect(&rect);
	dc.FillRect(&rect, &brush);
}

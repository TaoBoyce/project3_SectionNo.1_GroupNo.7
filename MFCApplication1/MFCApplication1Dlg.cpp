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
	m_cpuLimit(100), m_powerLimit(100), m_overrideFanSpeed(false), m_overridePower(false),
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
		UpdateWiFiProgress();
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CMFCApplication1Dlg::UpdateCPUProgress()
{
	std::ifstream file("cpu_usage.txt"); // Reading CPU usage from the file
	if (file.is_open())
	{
		int cpuUsage;
		file >> cpuUsage; // Assuming the file contains a single integer value for CPU usage
		file.close();

		// Ensure the value is within the range 0 to 100
		if (cpuUsage < 0) cpuUsage = 0;
		if (cpuUsage > 100) cpuUsage = 100;

		// Update progress bar with the CPU usage value
		m_cpuProgress.SetPos(cpuUsage);
	}
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
		// Read the temperature from the file
		int temp;
		file >> temp;
		file.close();

		// If the temperature has changed, set the target temperature
		if (temp != m_targetTemp)
		{
			m_targetTemp = temp;
		}

		// Gradually move towards the target temperature
		if (m_currentTemp < m_targetTemp)
			m_currentTemp++;  // Increase by 1
		else if (m_currentTemp > m_targetTemp)
			m_currentTemp--;  // Decrease by 1

		// Update the progress bar with the new temperature
		m_tempProgress.SetPos(m_currentTemp);

		// Change progress bar color based on the current temperature
		CWnd* pWnd = GetDlgItem(IDC_TEMP);
		if (pWnd)
		{
			COLORREF color = RGB(0, 0, 255); // Blue
			if (m_currentTemp > 60)
				color = RGB(255, 0, 0); // Red
			else if (m_currentTemp >= 50)
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



	m_cpuLimit = newLimit;
	m_cpuProgress.SetPos(newLimit);
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

void CMFCApplication1Dlg::UpdateWiFiProgress()
{
	if (!m_isWifiOn) // Stop updating if WiFi is off
		return;

	int wifiValue = 0; // Variable to hold WiFi usage value from the file
	CStdioFile file;
	CString line;

	// Open and read the WiFi data file
	if (file.Open(_T("wifi_data.txt"), CFile::modeRead | CFile::typeText))
	{
		if (file.ReadString(line)) // Read one line from the file
		{
			wifiValue = _ttoi(line); // Convert string to integer

			// Ensure the value is within the range 0 to 100
			if (wifiValue < 0) wifiValue = 0;
			if (wifiValue > 100) wifiValue = 100;

			m_wifiProgress.SetPos(wifiValue); // Update the progress bar
		}
		file.Close();
	}
	else
	{
		// Handle error if file is not found
		m_isWifiOn = false; // Stop updating if the file is missing
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

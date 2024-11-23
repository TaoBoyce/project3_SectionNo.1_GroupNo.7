#pragma once

// CMFCApplication1Dlg dialog
class CMFCApplication1Dlg : public CDialogEx
{
	// Construction
public:
	CMFCApplication1Dlg(CWnd* pParent = nullptr);  // standard constructor

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);  // DDX/DDV support

	// Implementation
protected:
	HICON m_hIcon;

	// Controls for progress bars
	CProgressCtrl m_cpuProgress;
	CProgressCtrl m_gpuProgress;
	CProgressCtrl m_fanProgress;
	CProgressCtrl m_tempProgress;
	CProgressCtrl m_powerProgress;
	CProgressCtrl m_wifiProgress; // WiFi progress bar

	// Controls for manual input
	CEdit m_editLimit;       // For CPU limit
	CEdit m_editFanSpeed;    // For fan speed input
	CEdit m_editPowerLimit;

	// Function to update CPU progress
	void UpdateCPUProgress();  // Add the declaration of the function
	void UpdateGPUProgress();
	void UpdateTempProgress();
	void UpdateFanProgress();
	void UpdatePowerProgress();
	void UpdateWiFiProgress();

	// Member variables
	int m_cpuLimit;          // CPU usage limit
	int m_powerLimit;
	bool m_overrideFanSpeed; // Flag to override fan speed input
	bool m_overridePower;
	bool m_isWifiOn;              // Tracks whether WiFi reading is active
	// Generated message map functions
	virtual BOOL OnInitDialog();
	//afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	//void OnPaint();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedWifiOff();
	afx_msg void OnBnClickedWifiOn();

	//afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:

	afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT_PTR nIDEvent); // Timer event handler
	afx_msg void OnEnChangeEdit3();
};


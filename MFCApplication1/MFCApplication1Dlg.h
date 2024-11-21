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

	// Controls for manual input
	CEdit m_editLimit;       // For CPU limit
	CEdit m_editFanSpeed;    // For fan speed input
	// Function to update CPU progress
	void UpdateCPUProgress();  // Add the declaration of the function
	void UpdateGPUProgress();
	void UpdateTempProgress();
	void UpdateFanProgress();


	// Member variables
	int m_cpuLimit;          // CPU usage limit
	bool m_overrideFanSpeed; // Flag to override fan speed input

	// Generated message map functions
	virtual BOOL OnInitDialog();
	//afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	//void OnPaint();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	//afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:

	afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT_PTR nIDEvent); // Timer event handler
};


// test1Dlg.h : header file
//

#if !defined(AFX_TEST1DLG_H__6D7EAD7C_C988_4FB4_8D58_ADC4CB268BB6__INCLUDED_)
#define AFX_TEST1DLG_H__6D7EAD7C_C988_4FB4_8D58_ADC4CB268BB6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "usbi2cio.h"


/////////////////////////////////////////////////////////////////////////////
// CTest1Dlg dialog

class CTest1Dlg : public CDialog
{
// Construction
public:
	BOOL flag;
	LONG *IoRead;
	LONG ulIoPortConfig;
	HANDLE hDevice[127];
	I2C_TRANS TransI2C;
	CTest1Dlg(CWnd* pParent = NULL);	// standard constructor
	HINSTANCE hDLL;
	typedef WORD(CALLBACK* GETDLLVERSION)(void);
	typedef HANDLE(CALLBACK* OPENDEVICEINSTANCE)(LPSTR,BYTE);
	typedef BOOL(CALLBACK* CLOSEDEVICEINSTANCE)(HANDLE);
	typedef BOOL(CALLBACK* DETECTDEVICE)(HANDLE);
  typedef BYTE(CALLBACK* GETDEVICECOUNT)(LPSTR);
  typedef BYTE(CALLBACK* GETDEVICEINFO)(LPSTR,LPDEVINFO);
  typedef HANDLE(CALLBACK* OPENDEVICEBYSERIALID)(LPSTR,LPSTR);
	typedef BOOL(CALLBACK* GETSERIALID)(HANDLE,LPSTR);
	typedef BOOL(CALLBACK* CONFIGIOPORTS)(HANDLE,ULONG);
	typedef BOOL(CALLBACK* GETIOCONFIG)(HANDLE,LPLONG);
	typedef BOOL(CALLBACK* READIOPORTS)(HANDLE,LPLONG);
	typedef BOOL(CALLBACK* WRITEIOPORTS)(HANDLE,ULONG,ULONG);
	typedef BOOL(CALLBACK* READI2C)(HANDLE,PI2C_TRANS);
	typedef BOOL(CALLBACK* WRITEI2C)(HANDLE,PI2C_TRANS);
	GETDLLVERSION GetDllVersion;
	OPENDEVICEINSTANCE OpenDeviceInstance;
	CLOSEDEVICEINSTANCE CloseDeviceInstance;
	DETECTDEVICE DetectDevice;
  GETDEVICECOUNT GetDeviceCount;
  GETDEVICEINFO GetDeviceInfo;
  OPENDEVICEBYSERIALID OpenDeviceBySerialId;
	GETSERIALID GetSerialId;
	CONFIGIOPORTS ConfigIoPorts;
	GETIOCONFIG GetIoConfig;
	READIOPORTS ReadIoPorts;
	WRITEIOPORTS WriteIoPorts;
	READI2C ReadI2c;
	WRITEI2C WriteI2c;
// Dialog Data
	//{{AFX_DATA(CTest1Dlg)
	enum { IDD = IDD_TEST1_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTest1Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTest1Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnChangeEdit1();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnExit();
	afx_msg void OnButtonReadI2c();
	afx_msg void OnButtonWriteI2c();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEST1DLG_H__6D7EAD7C_C988_4FB4_8D58_ADC4CB268BB6__INCLUDED_)

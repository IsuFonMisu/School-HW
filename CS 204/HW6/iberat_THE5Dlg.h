
// iberat_THE5Dlg.h : header file
//

#pragma once
#include "afxwin.h"


// Ciberat_THE5Dlg dialog
class Ciberat_THE5Dlg : public CDialogEx
{
// Construction
public:
	Ciberat_THE5Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_IBERAT_THE5_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox comboBox;
	CEdit shifInput;
	afx_msg void OnBnClickedCheck1();
	CButton Shift;
	int operatorNum;
	afx_msg void OnBnClickedButton1();
	CEdit input1;
	CEdit input2;
	CListBox results;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
};

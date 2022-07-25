
// iberat_THE5Dlg.cpp : implementation file
//


////don't mind all these THE5 names it is just a minor mistake


#include "stdafx.h"
#include "iberat_THE5.h"
#include "iberat_THE5Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Ciberat_THE5Dlg dialog



Ciberat_THE5Dlg::Ciberat_THE5Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Ciberat_THE5Dlg::IDD, pParent)
	, operatorNum(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Ciberat_THE5Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, comboBox);
	DDX_Control(pDX, IDC_EDIT4, shifInput); /// accidentally shifInput
	DDX_Control(pDX, IDC_CHECK1, Shift);
	DDX_Radio(pDX, IDC_RADIO1, operatorNum);
	DDV_MinMaxInt(pDX, operatorNum, 0, 2);
	DDX_Control(pDX, IDC_EDIT1, input1);
	DDX_Control(pDX, IDC_EDIT2, input2);
	DDX_Control(pDX, IDC_LIST1, results);
}

BEGIN_MESSAGE_MAP(Ciberat_THE5Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHECK1, &Ciberat_THE5Dlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_BUTTON1, &Ciberat_THE5Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_RADIO1, &Ciberat_THE5Dlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &Ciberat_THE5Dlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &Ciberat_THE5Dlg::OnBnClickedRadio3)
END_MESSAGE_MAP()


// Ciberat_THE5Dlg message handlers

BOOL Ciberat_THE5Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	comboBox.SetCurSel(0);

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void Ciberat_THE5Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void Ciberat_THE5Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR Ciberat_THE5Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Ciberat_THE5Dlg::OnBnClickedCheck1()
{



	if (Shift.GetCheck()){
		shifInput.EnableWindow(TRUE);
		comboBox.EnableWindow(TRUE);
	}
	else{
		shifInput.EnableWindow(FALSE);
		comboBox.EnableWindow(FALSE);
	}
	// TODO: Add your control notification handler code here
}

int maxSize = 0;

void Ciberat_THE5Dlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here

	CString str_Data1, str_Data2, resultLine, operName, str_shiftNumber, direction, str_result ;

	unsigned int data1, data2, shiftNumber, result;
	
	////// not sure if this works
	CDC *pDC = GetDC();// This class is necessary to get the length of the string
	CSize cz;// An object which keeps the length of the string.
	
	input1.GetWindowTextW(str_Data1);
	input2.GetWindowTextW(str_Data2);
	shifInput.GetWindowTextW(str_shiftNumber);


	if(str_Data1==_T("") || str_Data2==_T("")){
		resultLine=_T("At least one operand was not entered.");
		results.AddString(resultLine);
	}
	else if (Shift.GetCheck() && str_shiftNumber==_T("")){
		resultLine=_T("Specify how many bits you want to shift");
		results.AddString(resultLine);
	}
	else{

		data1 = _tcstoul(str_Data1,nullptr,10);
		data2 = _tcstoul(str_Data2,nullptr,10);

		if(Shift.GetCheck()){ /// if shift enabled shifts

			shiftNumber = _tcstoul(str_shiftNumber,nullptr,10);

			comboBox.GetWindowTextW(direction);

			if(direction == _T("Left")){ // to left
				data1=data1<<shiftNumber;
				data2=data2<<shiftNumber;


			}
			else{						// to right
				data1=data1>>shiftNumber;
				data2=data2>>shiftNumber;
			}
			str_Data1.Format(_T("%u"), data1);
			str_Data2.Format(_T("%u"), data2);
		}
		
		if(operatorNum==0){
		
			operName= _T(" AND ");
			result = (data1&data2);
		
		}
		else if(operatorNum==1){
		
			operName= _T(" OR ");
			result = (data1|data2);
		
		}
		else if(operatorNum==2){

			operName =_T(" XOR ");	
			result = (data1^data2);
		
		}
		
		str_result.Format(_T("%u"), result);

		resultLine += str_Data1 + operName + str_Data2 + _T(" = ") + str_result;

		results.AddString(resultLine);



	}

		//// hope works
	cz = pDC->GetTextExtent(resultLine);
	if(cz.cx > maxSize)
		maxSize = cz.cx; 
	results.SetHorizontalExtent(maxSize);

}


void Ciberat_THE5Dlg::OnBnClickedRadio1()
{
	operatorNum=0;
	// TODO: Add your control notification handler code here
}


void Ciberat_THE5Dlg::OnBnClickedRadio2()
{
	operatorNum=1;
	// TODO: Add your control notification handler code here
}


void Ciberat_THE5Dlg::OnBnClickedRadio3()
{
	operatorNum=2;
	// TODO: Add your control notification handler code here
}

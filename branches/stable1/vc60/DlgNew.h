#if !defined(AFX_DLGNEW_H__CF54CA13_ECAF_4905_9B0B_168DA9D56AB5__INCLUDED_)
#define AFX_DLGNEW_H__CF54CA13_ECAF_4905_9B0B_168DA9D56AB5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgNew.h : header file
//
#include "..\program\program.h"

/*#########################################################################*/
/*#########################################################################*/

/////////////////////////////////////////////////////////////////////////////
// CDlgNew dialog

class CDlgNew : public CDialog
{
// Construction
public:
	CDlgNew(CWnd* pParent = NULL);   // standard constructor

	static CCommand *createCommand();
	static bool updateCommand( CCommand *cmd );
	static bool setCommand( CCommand *cmd , int nCmd );
	static bool createCommand( int nCmd , CCommand *parent , CCommand *before );

private:
	void enableControls( CommandType type );
	static void setCommandTo( CCommand *cmd , int nCmd );

public:
	CCommand *cmd;
	COLORREF currentColor;

// Dialog Data
	//{{AFX_DATA(CDlgNew)
	enum { IDD = IDD_CMDNEW };
	CStatic	m_wndColor;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgNew)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgNew)
	afx_msg void OnCmdtypeif();
	afx_msg void OnCmdtypemove();
	afx_msg void OnCmdtypepaint();
	afx_msg void OnColor();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/*#########################################################################*/
/*#########################################################################*/

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGNEW_H__CF54CA13_ECAF_4905_9B0B_168DA9D56AB5__INCLUDED_)

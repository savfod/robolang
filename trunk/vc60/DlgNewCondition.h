#if !defined(AFX_DLGNEWCONDITION_H__A98B2029_76D9_4236_A8E2_7ED61534FFB3__INCLUDED_)
#define AFX_DLGNEWCONDITION_H__A98B2029_76D9_4236_A8E2_7ED61534FFB3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgNewCondition.h : header file
//
#include "..\program\Program.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgNewCondition dialog

class CDlgNewCondition : public CDialog
{
// Construction
public:
	CDlgNewCondition(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgNewCondition)
	enum { IDD = IDD_NEWCONDITION };
	CEdit	m_Condition;
	CEdit	m_Cond2;
	CEdit	m_Cond1;
	//}}AFX_DATA
public:
	CommandCondition cond;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgNewCondition)
	public:
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgNewCondition)
	afx_msg void OnConditionNot();
	afx_msg void OnConditionOr();
	afx_msg void OnConditionAnd();
	afx_msg void OnConditionWallLeft();
	afx_msg void OnConditionWallRight();
	afx_msg void OnConditionWallUp();
	afx_msg void OnConditionWallDown();
	afx_msg void OnConditionPainted();
	afx_msg void OnConditionMake1();
	afx_msg void OnConditionMake2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CString getTypeName( CommandConditionType type );
	void updateEdits();

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGNEWCONDITION_H__A98B2029_76D9_4236_A8E2_7ED61534FFB3__INCLUDED_)

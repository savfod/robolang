// DlgNewCondition.cpp : implementation file
//

#include "stdafx.h"
#include "robolang.h"
#include "DlgNewCondition.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgNewCondition dialog


CDlgNewCondition::CDlgNewCondition(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgNewCondition::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgNewCondition)
	//}}AFX_DATA_INIT
}


void CDlgNewCondition::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgNewCondition)
	DDX_Control(pDX, IDC_CONDITION_EDIT, m_Condition);
	DDX_Control(pDX, IDC_CONDITION_COND2, m_Cond2);
	DDX_Control(pDX, IDC_CONDITION_COND1, m_Cond1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgNewCondition, CDialog)
	//{{AFX_MSG_MAP(CDlgNewCondition)
	ON_BN_CLICKED(IDC_CONDITION_NOT, OnConditionNot)
	ON_BN_CLICKED(IDC_CONDITION_OR, OnConditionOr)
	ON_BN_CLICKED(IDC_CONDITION_AND, OnConditionAnd)
	ON_BN_CLICKED(IDC_CONDITION_WALL_LEFT, OnConditionWallLeft)
	ON_BN_CLICKED(IDC_CONDITION_WALL_RIGHT, OnConditionWallRight)
	ON_BN_CLICKED(IDC_CONDITION_WALL_UP, OnConditionWallUp)
	ON_BN_CLICKED(IDC_CONDITION_WALL_DOWN, OnConditionWallDown)
	ON_BN_CLICKED(IDC_CONDITION_PAINTED, OnConditionPainted)
	ON_BN_CLICKED(IDC_CONDITION_MAKE1, OnConditionMake1)
	ON_BN_CLICKED(IDC_CONDITION_MAKE2, OnConditionMake2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgNewCondition message handlers



int CDlgNewCondition::DoModal() 
{
	// TODO: Add your specialized code here and/or call the base class
	if( !cond.cond1 )
		cond.cond1 = new CommandCondition;

	if( !cond.cond2 )
		cond.cond2 = new CommandCondition;

	int res = CDialog::DoModal();
		
	return res;
}

CString CDlgNewCondition::getTypeName( CommandConditionType type )
{
	switch( type )
	{
		case CONDTYPE_WALLLEFT : return( "Слева стена" );
		case CONDTYPE_WALLRIGHT : return( "Справа стена " );
		case CONDTYPE_WALLUP : return( "Сверху стена " );
		case CONDTYPE_WALLDOWN : return( "Снизу стена " );
		case CONDTYPE_PAINTED : return( "Поле закрашено " );
		case CONDTYPE_OR: return("ИЛИ");
		case CONDTYPE_AND: return("И");
		case CONDTYPE_NOT: return("НЕ");
	}
	return( "" );
}

void CDlgNewCondition::updateEdits()
{
	m_Cond1.SetWindowText("");
	m_Cond2.SetWindowText("");

	switch( cond.type )
	{
		case CONDTYPE_OR: 
		case CONDTYPE_AND: 
			m_Cond2.SetWindowText( cond.cond2 -> getConditionName() );	
		case CONDTYPE_NOT: 
			m_Cond1.SetWindowText( cond.cond1 -> getConditionName() );
	}

	m_Condition.SetWindowText( getTypeName ( cond.type ) );

}
//////////////////////////////////////////////////////////////////////////////
// Buttons:

void CDlgNewCondition::OnConditionNot() 
{
	// TODO: Add your control notification handler code here
	cond.type = CONDTYPE_NOT;
	updateEdits();
}


void CDlgNewCondition::OnConditionOr() 
{
	// TODO: Add your control notification handler code here
	cond.type = CONDTYPE_OR;
	updateEdits();
}

void CDlgNewCondition::OnConditionAnd() 
{
	// TODO: Add your control notification handler code here
	cond.type = CONDTYPE_AND;
	updateEdits();
}

void CDlgNewCondition::OnConditionWallLeft() 
{
	// TODO: Add your control notification handler code here
	cond.type = CONDTYPE_WALLLEFT;
	updateEdits();
}

void CDlgNewCondition::OnConditionWallRight() 
{
	// TODO: Add your control notification handler code here
	cond.type = CONDTYPE_WALLRIGHT;
	updateEdits();
}

void CDlgNewCondition::OnConditionWallUp() 
{
	// TODO: Add your control notification handler code here
	cond.type = CONDTYPE_WALLUP;
	updateEdits();
}

void CDlgNewCondition::OnConditionWallDown() 
{
	// TODO: Add your control notification handler code here
	cond.type = CONDTYPE_WALLDOWN;
	updateEdits();
}

void CDlgNewCondition::OnConditionPainted() 
{
	// TODO: Add your control notification handler code here
	cond.type = CONDTYPE_PAINTED;
	updateEdits();
	
}

void CDlgNewCondition::OnConditionMake1() 
{
	// TODO: Add your control notification handler code here
	CDlgNewCondition dlg;
	dlg.cond = cond.cond1 -> getCopy();
	if( dlg.DoModal() )
		*(cond.cond1) = dlg.cond.getCopy();
	updateEdits();
}

void CDlgNewCondition::OnConditionMake2() 
{
	// TODO: Add your control notification handler code here
	CDlgNewCondition dlg;
	dlg.cond = cond.cond2 -> getCopy();
	if( dlg.DoModal() )
		*(cond.cond2) = dlg.cond.getCopy();
	updateEdits();
}

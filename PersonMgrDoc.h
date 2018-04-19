// PersonMgrDoc.h : interface of the CPersonMgrDoc class
//
/////////////////////////////////////////////////////////////////////////////
// CONSTANTS declare
#if !defined(AFX_PERSONMGRDOC_H__B285B61D_CA4F_4C30_BAB4_3A9E0B139A47__INCLUDED_)
#define AFX_PERSONMGRDOC_H__B285B61D_CA4F_4C30_BAB4_3A9E0B139A47__INCLUDED_
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define		ONECOLUMNHEIGH	35


#define		COLUMNVALUEMAX		100		// ÿһ�е�����ַ���
#define		UP_BOARDLINE		15		// �ϱ߽�(unit: mm)
#define		DOWN_BOARDLINE		15		// �±߽�(unit: mm)
#define		LEFT_BOARDLINE		15		// ��߽�(unit: mm)
#define		RIGHT_BOARDLINE		15		// �ұ߽�(unit: mm)
#define		HEAD_HEIGHT			15		// ���ͷ(unit: mm)
#define		TAIL_HEIGHT			10		// ���β(unit: mm)
#define		LINE_HEIGHT			20		// �ڱ���һ���ߣ���ȥ10���߼���

/////////////////////////////////////////////////////////////////////////////
// extern class declare
class	CPersonMgrTreeView;
class	CPersonMgrTitleView;
class	CPersonMgrQueryView;
class	CPersonMgrListView;
/////////////////////////////////////////////////////////////////////////////
// Enum declare
// ImageList ImageId
enum en_ImageID{
	IID_ROOT = 0,
	IID_ACCOUNT,
	IID_PLAN,
	IID_CONTACT,
	IID_FAMILY,
	IID_CALL,
	IID_OTHER,
	IID_TABLE,
	IID_QUERY
	};
// Edit type
enum en_EditType{
	NONE = 0,
	INPUT,
	QUERY	
	};
/////////////////////////////////////////////////////////////////////////////
// Class object declare
class CPersonMgrDoc : public CDocument
{
protected: // create from serialization only
	CPersonMgrDoc();
	DECLARE_DYNCREATE(CPersonMgrDoc)

// Attributes
public:
	CDaoDatabase*		m_pDaoDB;
	CDaoRecordset*		m_pDaoRecordSet;

	CString				m_curTable;
	CString				m_strUser;
	int					m_nType;

	CStringArray		m_arrTable;
	CStringArray		m_arrQuery;
	CStringArray		m_arrColumn;
	CStringArray		m_arrParam;
	CUIntArray			m_arrParamType;
	CUIntArray			m_arrColumnType;

	CMapStringToString	m_mapColumnToDataType;
	CMapStringToString	m_mapColumnToHelpInfo;

	CMapStringToString	m_mapParamToDataType;
	CMapStringToString	m_mapParamToHelpInfo;

	CMapStringToString  m_mapUserToPassword;

	CPersonMgrTreeView*	m_pTreeView;
	CPersonMgrTitleView	*m_pTitleView;
	CPersonMgrQueryView	*m_pQueryView;	
	CPersonMgrListView*	m_pListView;

	// auto power off section
	BOOL				m_bAutoShutDown;
	CString				m_strTime;

	// about print and print preView section
	// ÿһmm������߼����Ƕ���
	int					m_nPerMMPixel;	
	// ÿһҳ(listView��)��Ŀǰ��������ʾ������
	int					m_nRowPerPage;	
	// ��ǰ��yin����ĸ߶�
	int					m_nTextHeight;
	// ҳ���Y��������ص�
	int					m_nYMaxPixel;
	// ҳҳ��X��������ص�
	int					m_nXMaxPixel;
	
	BOOL				m_bLogin;
	int					m_nLangID;
	BOOL				m_bDynamic;

// Operations
public:
	BOOL				Login( );
	CString				GetDBName( );
	void				SetEditType( int nType) { m_nType = nType; }
	void				InitallColumnName();
	void				GetColumnDataTypeAndHelpInfo( CDaoFieldInfo& fieldInfo );
	void				GetParamDataTypeAndHelpInfo( CDaoParameterInfo &paramInfo);
	CString				GetDataTypeString( short nDataType, int nSize = 100 );
	CString				GetHelpInfoString( short nDataType, int nSize = 100, 
										   BOOL bAllowZero = FALSE );

	// ini�ļ���·��
	CString				GetPrivateFileName( void );
	void				InitUserData( );
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPersonMgrDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void OnCloseDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	void DrawLine(CDC *pDC, int nLeft, int nTop, int nRight, int nBottom, int nPenStyle, int nWidth = 1);
	void EmptyMapString(CMapStringToString& mapString);
	void EmptyArray( CStringArray &strArray );
	void EmptyArray( CUIntArray   &strArray );
	int GetDayCount( CTime time );
	void JudgeRegister( );
	BOOL IsShutDownTime( );
	void SetSomeStatus( );

	void SetPrivateInfo( );
	void GetPrivateInfo( );

	BOOL IsDayAlarm( CString& strNote, CString& strMelody );
	BOOL IsWeekAlarm( CString& strNote, CString& strMelody );
	BOOL IsPlanTaskAlarm( CString& strNote, CString& strMelody );
	BOOL IsSimpleTimeType( CString strColumn, int nType );
	BOOL DeleteUser( CString strUser );
	void OpenInternet( CString strWeb );
	void SendEmail( CString strMailAddress );
	BOOL ChgUserPSD( CString strUser, CString strPSD );
	BOOL AddUser( CString strUser, CString strPSD );
	void GetUserPsdInfo( );
	CString GetFilterString( );
	virtual ~CPersonMgrDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPersonMgrDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PERSONMGRDOC_H__B285B61D_CA4F_4C30_BAB4_3A9E0B139A47__INCLUDED_)

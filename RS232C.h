// RS232C.h: interface for the CRS232C class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RS232C_H__C56ED219_E33A_4F18_8385_03A4827A5C1D__INCLUDED_)
#define AFX_RS232C_H__C56ED219_E33A_4F18_8385_03A4827A5C1D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//////////////////////////////////////////////////////////////////////
class CRS232C : public CObject {

public:
	RS232C(const CRS232C &nRs232c);
	CRS232C();
	virtual ~CRS232C();
	void	operator =(const CRS232C &nRs232c);

public:
	BOOL		ReadData( LPVOID lpBuf, DWORD dwRead, LPDWORD lpReaded );
	BOOL		WriteData( LPVOID lpBuf, DWORD dwWrite, LPDWORD lpWrited );
			
	BOOL		OpenPort(void);
	BOOL		IsOpened(){return m_bOpened;}
	void		Attach(CString strPort="COM1", int iBaudRate=9600);
	int			GetBaudRate(void) const;
	void		SetBaudRate(int iBaudRate);
	CString		GetComPort(void) const;
	void		SetComPort(const CString strPort);

public:

	OVERLAPPED	m_OverlappedRead;
	OVERLAPPED	m_OverlappedWrite;
	HANDLE		m_hCommDev;
	CString		m_strPort;
	int			m_iBaudRate;

private:	
	BOOL m_bOpened;
};

#endif // !defined(AFX_RS232C_H__C56ED219_E33A_4F18_8385_03A4827A5C1D__INCLUDED_)

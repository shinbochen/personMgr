// RS232C.cpp: implementation of the CRS232C class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PersonMgr.h"
#include "RS232C.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
// CRS232C class member
CRS232C::CRS232C(){

	m_hCommDev=NULL;
	m_strPort="COM1";
	m_iBaudRate=9600;
	memset(&m_OverlappedRead,0,sizeof(OVERLAPPED));
	memset(&m_OverlappedWrite,0,sizeof(OVERLAPPED));
	m_bOpened=FALSE;
}
//////////////////////////////////////////////////////////////////////
// CRS232C class member
CRS232C::~CRS232C(){

	if(m_hCommDev!=NULL){
		CloseHandle(m_hCommDev);
	}
	if(m_OverlappedRead.hEvent!=NULL){
		CloseHandle(m_OverlappedRead.hEvent);
	}
	if(m_OverlappedWrite.hEvent!=NULL){
		CloseHandle(m_OverlappedWrite.hEvent);
	}
}

//////////////////////////////////////////////////////////////////////
// CRS232C class member
void CRS232C::SetComPort(const CString strPort){
	m_strPort=strPort;
}

//////////////////////////////////////////////////////////////////////
// CRS232C class member
CString CRS232C::GetComPort() const{
	return m_strPort;
}

//////////////////////////////////////////////////////////////////////
// CRS232C class member
void CRS232C::SetBaudRate(int iBaudRate){
	m_iBaudRate=iBaudRate;
}

//////////////////////////////////////////////////////////////////////
// CRS232C class member
int CRS232C::GetBaudRate() const{
	return m_iBaudRate;
}

//////////////////////////////////////////////////////////////////////
// CRS232C class member
void CRS232C::Attach(CString strPort, int iBaudRate){
	m_strPort=strPort;
	m_iBaudRate=iBaudRate;
}

//////////////////////////////////////////////////////////////////////
// CRS232C class member
CRS232C::RS232C(const CRS232C &nRs232c){
	m_strPort=nRs232c.GetComPort();
	m_iBaudRate=nRs232c.GetBaudRate();
	m_hCommDev=nRs232c.m_hCommDev;
	memcpy(&m_OverlappedRead,&nRs232c.m_OverlappedRead,sizeof(OVERLAPPED));
	memcpy(&m_OverlappedWrite,&nRs232c.m_OverlappedWrite,sizeof(OVERLAPPED));
}

//////////////////////////////////////////////////////////////////////
// CRS232C class member
void CRS232C::operator =(const CRS232C &nRs232c){

	m_strPort=nRs232c.GetComPort();
	m_iBaudRate=nRs232c.GetBaudRate();
	m_hCommDev=nRs232c.m_hCommDev;
	memcpy(&m_OverlappedRead,&nRs232c.m_OverlappedRead,sizeof(OVERLAPPED));
	memcpy(&m_OverlappedWrite,&nRs232c.m_OverlappedWrite,sizeof(OVERLAPPED));
	return;
}

//////////////////////////////////////////////////////////////////////
// CRS232C class member
BOOL CRS232C::OpenPort(void){
	// if have opened then close
	if(m_bOpened){				
		if(m_OverlappedRead.hEvent!=NULL){
			CloseHandle(m_OverlappedRead.hEvent);
		}
		if(m_OverlappedWrite.hEvent!=NULL){
			CloseHandle(m_OverlappedWrite.hEvent);
		}
		CloseHandle(m_hCommDev);
		m_bOpened=FALSE;
	}
	m_hCommDev=CreateFile(
		m_strPort.GetBuffer(0),
		GENERIC_READ|GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED,
		NULL);

	m_strPort.ReleaseBuffer();

	if( m_hCommDev == INVALID_HANDLE_VALUE ){
		m_bOpened=FALSE;
		TRACE("Can't open the port\n");
		return m_bOpened;
	}
	else{
		TRACE("Success Open the port\n");
		// 设置超时
		COMMTIMEOUTS	CommTimeOuts;

		CommTimeOuts.ReadIntervalTimeout = 1000;
		CommTimeOuts.ReadTotalTimeoutConstant = 1000;
		CommTimeOuts.ReadTotalTimeoutMultiplier = 500;
		CommTimeOuts.WriteTotalTimeoutConstant = 1000;
		CommTimeOuts.WriteTotalTimeoutMultiplier = 500;

		if( !SetCommTimeouts(m_hCommDev,&CommTimeOuts) ){
			ASSERT( FALSE );
			TRACE("设置超时失败\n");
		}
		memset(&m_OverlappedRead, 0, sizeof(OVERLAPPED) );
		memset(&m_OverlappedWrite, 0, sizeof(OVERLAPPED) );

		m_OverlappedRead.hEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
		m_OverlappedWrite.hEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
		
		// 设置参数
		DCB			dcb;

		dcb.DCBlength=sizeof(DCB);

		GetCommState (m_hCommDev, &dcb );
		dcb.BaudRate = m_iBaudRate;
		dcb.ByteSize = 8;
		if( !SetCommState(m_hCommDev,&dcb) ||
			!SetupComm(m_hCommDev,1000,1000) ||
			m_OverlappedRead.hEvent==NULL ||
			m_OverlappedWrite.hEvent==NULL){

			CloseHandle(m_hCommDev);
			if(m_OverlappedRead.hEvent!=NULL){
				CloseHandle(m_OverlappedRead.hEvent);
			}
			if(m_OverlappedWrite.hEvent!=NULL){
				CloseHandle(m_OverlappedWrite.hEvent);
			}
			TRACE0("设置参数失败\n");
			m_bOpened=FALSE;
		}
		m_bOpened=TRUE;
	}
	return m_bOpened;
}
//////////////////////////////////////////////////////////////////////
// CRS232C class member
// 接收数据
BOOL CRS232C::ReadData( LPVOID lpBuf, DWORD dwRead, LPDWORD lpReaded ){

	BOOL			bFlag;

	ASSERT( m_bOpened == TRUE );

	if( m_bOpened == FALSE ){
		lpReaded = 0;
		return FALSE;
	}
	ResetEvent( m_OverlappedRead.hEvent );

	bFlag = ReadFile( m_hCommDev, lpBuf, dwRead, lpReaded, &m_OverlappedRead );
	if( bFlag == FALSE ){
		if( GetLastError() == ERROR_IO_PENDING ){
			if( WaitForSingleObject( m_OverlappedRead.hEvent,1000) == WAIT_TIMEOUT ){
				bFlag = FALSE;
			}
			else{
				bFlag = GetOverlappedResult(m_hCommDev,
											&m_OverlappedRead,
											lpReaded, FALSE );
			}
		}
	}
	return bFlag;
}
//////////////////////////////////////////////////////////////////////
// CRS232C class member
// 写数据
BOOL CRS232C::WriteData( LPVOID lpBuf, DWORD dwWrite, LPDWORD lpWrited ){

	BOOL			bFlag;

	ASSERT( m_bOpened == TRUE );

	if( m_bOpened == FALSE ){
		lpWrited = 0;
		return FALSE;
	}
	ResetEvent( m_OverlappedWrite.hEvent );

	bFlag = WriteFile( m_hCommDev, lpBuf, dwWrite, lpWrited, &m_OverlappedWrite );
	if( bFlag == FALSE ){
		if( GetLastError() == ERROR_IO_PENDING ){
			if( WaitForSingleObject( m_OverlappedWrite.hEvent,1000) == WAIT_TIMEOUT ){
				bFlag = FALSE;
			}
			else{
				bFlag = GetOverlappedResult(m_hCommDev,
											&m_OverlappedWrite,
											lpWrited, FALSE );
			}
		}
	}
	return bFlag;
}
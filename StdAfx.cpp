// stdafx.cpp : source file that includes just the standard includes
//	PersonMgr.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
// 多媒体支持
#pragma comment(lib,"WINMM.LIB")

//////////////////////////////////////////////////////////////////
// 全局函数的实现
// 得到程序路径
CString GetModulePath( ){

	CString			strPath;
	int				nPos = 0;

	GetModuleFileName( NULL, strPath.GetBuffer(255), 255 );
	strPath.ReleaseBuffer();
	nPos = strPath.ReverseFind( '\\' );
	strPath = strPath.Left( nPos );
	return strPath;
}
/////////////////////////////////////////////////////////////////////////////
// Global Function
// 硬盘序号
/*BOOL GetIDESeriala( CString&	strText ){

	DWORD			dwSN;
	DWORD			dwMask[12] = {
		0x13425673,
		0x56128084,
		0x16872023,
		0x10034681,
		0x13056808,
		0x13594023,
		0x80912353,
		0x21474504,
		0x15235475,
		0x29464865,
		0x86657354,
		0x06825422};
	UINT			nMask;

	if( GetVolumeInformation("C:\\",
							 NULL,			// lpVolumeNameBuffer 
							 0,
							 &dwSN,
							 NULL,			// lpMaximumComponentLength 
							 NULL,			// lpFileSystemFlags 
							 NULL,			// lpFileSystemNameBuffer 
						     0 ) != 0 ){
		nMask = dwSN % 12;
		dwSN &= dwMask[nMask];
		strText.Format( "%d", dwSN );
		return TRUE;	
	}
	else{
		return FALSE;
	}
}*/
/////////////////////////////////////////////////////////////////////////////
// 注册码
/*CString GetRegisterCodea( CString strSN ){

	CString			strDest;
	TCHAR			szDest[256];
	DWORD			dwSN;
	UINT			nMask;
	
	DWORD			dwMask[12] = {
		0x34534533,
		0x35345384,
		0x14545624,
		0x23423423,
		0x96767353,
		0x24253478,
		0x96778456,
		0x78968313,
		0x68669685,
		0x23436467,
		0x06785643,
		0x13454684};

	dwSN = atoi( strSN.GetBuffer(0) );
	strSN.ReleaseBuffer();

	nMask = dwSN % 12;
	dwSN &= dwMask[nMask]; 
	
	_i64toa( dwSN, szDest, 31 );

	strDest.Format( "PIM-%s-asE", szDest );
	return strDest;
}
*/
/////////////////////////////////////////////////////////////////////////////
// global function
CString	ChangeVariantToString( COleVariant& varValue, BOOL bFlag ){
	
	CString			strValue;
	COleCurrency	c;
	COleDateTime	t;
	CString			strTmp;
	TCHAR			tChar;

	switch( varValue.vt ){
	case VT_ERROR:
		strValue = "Error";					
		break;
	case VT_UI1:
		strValue.Format( "%C", varValue.bVal );
		break;
	case VT_I2:	
		strValue.Format( "%d", varValue.iVal );
		break;
			   
	case VT_I4: 
		strValue.Format( "%d", varValue.lVal );
		break;
		
	case VT_R4:  
		strValue.Format( "%.2f", varValue.fltVal);       
		break;
			
	case VT_R8:
		strValue.Format( "%.2f", varValue.dblVal);
		break;

	case VT_CY:					// ie.:  1.00
		c = varValue;
		strValue = c.Format( );
		tChar = strValue.GetAt( 0 );
		if( ( tChar == _T('.') ) || 
			( tChar == _T('-') ) ||
			( tChar >= _T('0') && tChar <= _T('9') ) ){

			strValue = "$"+strValue;
		}
		break;

	case VT_DATE:						// Year/month/day hour:minute:secont Day of Week
		t = varValue; 
		if( bFlag == TRUE ){
			strTmp = "%H:%M";
			if( t.GetSecond() ){
				strTmp += ":%S";
			}
			strValue = t.Format( strTmp );
		}
		else{
			strTmp = "%Y-%m-%d ";
			if( t.GetHour() || t.GetMinute() || t.GetSecond() ){
				strTmp += "%H:%M";
				if( t.GetSecond() ){
					strTmp += ":%S";
				}
			}
			strValue = t.Format( strTmp ); //"%Y/%m/%d %H:%M:%S(%a)" );	
		}
		break;
				 
	case VT_BSTR:
		strValue = V_BSTRT( &varValue );
		break;
				
	case VT_BOOL:
		if( varValue.boolVal ){
			strValue = "Yes";
		}
		else{
			strValue = "No";
		}
		break;

	case VT_EMPTY:
	case VT_NULL:
		strValue = "";
		break;

	default:
		ASSERT(FALSE);
		break;
	}
	return	strValue;
}
/////////////////////////////////////////////////////////////////////////////
// global fucntion
BOOL GetDate( CString strValue, CTime& time ){

	int			nChar = '-';
	int			nValue = 0;
	int			nCnt = 0;
	int			nFlag = 0;

	int			nYear = 2003;
	int			nMonth = 1;
	int			nDay = 1;
	int			nHour = 0;
	int			nMinute = 0;
	int			nSecond = 0;
	CString		strTmp;

	while( (nCnt = strValue.Find( nChar )) != -1 ){

		strTmp = strValue.Left( nCnt );
		strValue = strValue.Mid( nCnt + 1 );

		nValue = atoi( strTmp.GetBuffer(0) );
		strTmp.ReleaseBuffer();

		switch( nFlag ){
		case 0:			// year
			if( nValue < 1970 ){
				nValue = 1970;
			}
			if( nValue > 2037 ){
				nValue = 2037;
			}
			nYear = nValue;
			break;
		case 1:			// month
			if( nValue < 1 ){
				nValue = 1;
			}
			if( nValue > 12 ){
				nValue = 12;
			}
			nMonth = nValue;
			nChar = ' ';
			break;
		case 2:			// day
			if( nValue < 1 ){
				nValue = 1;
			}
			if( nValue > 31 ){
				nValue = 31;
			}
			nDay = nValue;
			nChar = ':';
			break;
		case 3:			// hour
			if( nValue < 0 ){
				nValue = 0;
			}
			if( nValue > 23 ){
				nValue = 23;
			}
			nHour = nValue;
			break;
		case 4:			// Minute
			if( nValue < 0 ){
				nValue = 0;
			}
			if( nValue > 59 ){
				nValue = 59;
			}
			nMinute = nValue;
			break;
		case 5:			// Second
			if( nValue < 0 ){
				nValue = 0;
			}
			if( nValue > 59 ){
				nValue = 59;
			}
			nSecond = nValue;
			break;
		}
		nFlag++;
		if( nFlag >= 5 ){
			break;
		}
	}

	strTmp = strValue;
	nValue = atoi( strTmp.GetBuffer(0) );
	strTmp.ReleaseBuffer();

	switch( nFlag ){
	case 0:			// year
		if( nValue < 1970 ){
			nValue = 1970;
		}
		if( nValue > 2037 ){
			nValue = 2037;
		}
		nYear = nValue;
		break;
	case 1:			// month
		if( nValue < 1 ){
			nValue = 1;
		}
		if( nValue > 12 ){
			nValue = 12;
		}
		nMonth = nValue;
		nChar = ' ';
		break;
	case 2:			// day
		if( nValue < 1 ){
			nValue = 1;
		}
		if( nValue > 31 ){
			nValue = 31;
		}
		nDay = nValue;
		nChar = ':';
		break;
	case 3:			// hour
		if( nValue < 0 ){
			nValue = 0;
		}
		if( nValue > 23 ){
			nValue = 23;
		}
		nHour = nValue;
		break;
	case 4:			// Minute
		if( nValue < 0 ){
			nValue = 0;
		}
		if( nValue > 59 ){
			nValue = 59;
		}
		nMinute = nValue;
		break;
	case 5:			// Second
		if( nValue < 0 ){
			nValue = 0;
		}
		if( nValue > 59 ){
			nValue = 59;
		}
		nSecond = nValue;
		break;
	}

	CTime	t( nYear, nMonth, nDay, nHour, nMinute, nSecond, 0 );
	time = t;
	return TRUE;
}
/////////////////////////////////////////////////////////////////////////////
// global function
BOOL GetVariantFromString( COleVariant& varValue, short nDataType, 
						   CString strValue ){
	COleCurrency	c;
	COleDateTime	t;

	long			nValue;
	double			dbValue;

	CTime			time;

	CString			strTmp;
	int				nCnt;

	nValue = atol( strValue.GetBuffer(0) );
	strValue.ReleaseBuffer();

	dbValue = atof( strValue.GetBuffer(0) );
	strValue.ReleaseBuffer();

	if( strValue.IsEmpty() ){
		varValue.Clear();
		return TRUE;
	}

	switch( nDataType ){
	case dbBoolean:
		varValue.vt = VT_BOOL;
		if( nValue == 1 ){
			varValue.boolVal = TRUE;
		}
		else{
			varValue.boolVal = FALSE;
		}				
		break;

	case dbByte:
		varValue.vt = VT_UI1;
		if( nValue < 0 ){
			nValue = 0;
		}
		if( nValue > 255 ){
			nValue = 255;
		}
		varValue.bVal = (BYTE)nValue;
		break;

	case dbInteger:
		varValue.vt = VT_I2;
		if( nValue < -32768 ){
			nValue = -32768;
		}
		if( nValue > 32768 ){
			nValue = 32768;
		}
		varValue.iVal = (int)nValue;
		break;

	case dbLong:
		varValue.vt = VT_I4;
		varValue.lVal = nValue;		
		break;
			   
	case dbCurrency: 
		nCnt = strValue.Find('$');
		if( nCnt != -1 ){
			strValue = strValue.Mid( nCnt+1 );
		}
		c.ParseCurrency( strValue );

		varValue = COleVariant( c );
		break;

	case dbSingle:
		varValue.vt = VT_R4;
		varValue.fltVal = (float)dbValue;
		break;

	case dbDouble:
		varValue.vt = VT_R8;
		varValue.dblVal = dbValue;
		break;

	case dbDate:
		GetDate( strValue, time );
		t.SetDateTime( time.GetYear(),
					   time.GetMonth(),
					   time.GetDay(),
					   time.GetHour(),
					   time.GetMinute(),
					   time.GetSecond() );
		varValue = COleVariant( t );
		break;

	case dbTime:
		strValue = "2003-1-1 " + strValue;
		GetDate( strValue, time );
		t.SetDateTime( time.GetYear(),
					   time.GetMonth(),
					   time.GetDay(),
					   time.GetHour(),
					   time.GetMinute(),
					   time.GetSecond() );
		varValue = COleVariant( t );
		break;

	case dbText:
	case dbMemo:
		varValue.SetString( strValue, VT_BSTRT );
		break;

	default:
		ASSERT( FALSE );
		break;
	}
	return TRUE;
}
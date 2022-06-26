// MD51.h: Definition of the MD5 class
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MD51_H__BFC8E43C_1950_4674_81F9_CC4DE6BAF117__INCLUDED_)
#define AFX_MD51_H__BFC8E43C_1950_4674_81F9_CC4DE6BAF117__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// MD5

class MD5 : 
	public IMD5,
	public CComObjectRoot,
	public CComCoClass<MD5,&CLSID_MD5>
{
public:
	MD5() {}
BEGIN_COM_MAP(MD5)
	COM_INTERFACE_ENTRY(IMD5)
END_COM_MAP()
//DECLARE_NOT_AGGREGATABLE(MD5) 
// Remove the comment from the line above if you don't want your object to 
// support aggregation. 

DECLARE_REGISTRY_RESOURCEID(IDR_MD5)

// IMD5
public:
};

#endif // !defined(AFX_MD51_H__BFC8E43C_1950_4674_81F9_CC4DE6BAF117__INCLUDED_)

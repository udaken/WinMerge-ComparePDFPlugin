// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__1A520598_1E89_4BFA_98CD_7628B0C3DAA0__INCLUDED_)
#define AFX_STDAFX_H__1A520598_1E89_4BFA_98CD_7628B0C3DAA0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT _WIN32_WINNT_WINBLUE
#endif
#define _ATL_APARTMENT_THREADED
//#define _ATL_NO_AUTOMATIC_NAMESPACE

#define WIN32_LEAN_AND_MEAN
#define WINRT_LEAN_AND_MEAN
#define NOMINMAX

#define STRICT_TYPED_ITEMIDS
#define STRICT_CONST

#include <atlbase.h>
// You may derive a class from CComModule and use it if you want to override
// something, but do not change the name of _Module
extern CComModule _Module;

#include <atlcom.h>
#include <atlsafe.h>
#include <atlstr.h>

#include <wincodec.h>

#include <unknwn.h>
#include "winrt/base.h"
#include "winrt/Windows.Foundation.h"
#include "winrt/Windows.Data.Pdf.h"
#include "winrt/Windows.Storage.Streams.h"
#include "winrt/Windows.Storage.h"

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__1A520598_1E89_4BFA_98CD_7628B0C3DAA0__INCLUDED)

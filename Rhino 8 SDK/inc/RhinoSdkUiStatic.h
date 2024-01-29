/* $NoKeywords: $ */
/*
//
// Copyright (c) 1993-2007 Robert McNeel & Associates. All rights reserved.
// Rhinoceros is a registered trademark of Robert McNeel & Associates.
//
// THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT EXPRESS OR IMPLIED WARRANTY.
// ALL IMPLIED WARRANTIES OF FITNESS FOR ANY PARTICULAR PURPOSE AND OF
// MERCHANTABILITY ARE HEREBY DISCLAIMED.
//				
// For complete Rhino SDK copyright information see <http://www.rhino3d.com/developer>.
//
////////////////////////////////////////////////////////////////
*/

#pragma once


// CRhinoUiStatic

class RHINO_SDK_CLASS  CRhinoUiStatic : public CStatic
{
	DECLARE_DYNAMIC(CRhinoUiStatic)

public:
	CRhinoUiStatic();
	virtual ~CRhinoUiStatic();

  // Returns the static window text
  CString GetText();

  // Sets the static window text
  void SetText( const char* lpsText );
  void SetText( const wchar_t* lpsText );

  bool TextIsFilePath();
  void SetTextIsFilePath( bool);

protected:
  bool m_bIsFilePath;

protected:
	DECLARE_MESSAGE_MAP()
public:
  afx_msg void OnPaint();
};



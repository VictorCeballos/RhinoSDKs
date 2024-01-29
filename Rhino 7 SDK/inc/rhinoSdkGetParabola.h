//
// Copyright (c) 1993-2017 Robert McNeel & Associates. All rights reserved.
// Rhinoceros is a registered trademark of Robert McNeel & Associates.
//
// THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT EXPRESS OR IMPLIED WARRANTY.
// ALL IMPLIED WARRANTIES OF FITNESS FOR ANY PARTICULAR PURPOSE AND OF
// MERCHANTABILITY ARE HEREBY DISCLAIMED.
//				
// For complete Rhino SDK copyright information see <http://www.rhino3d.com/developer>.
//
////////////////////////////////////////////////////////////////

#pragma once

#include "rhinoSdkGetPoint.h"

// Todo - make this puppy work, and when done separate the Get-part and add to SDK
// SDK header stuff, goes to rhinoSdkGetParabola.h
/*-------------------------------------------------------------------
CLASS
  CArgsRhinoGetParabola

OVERVIEW TEXT
  Arguments for RhinoGetParabola... functions

KEYWORDS
  Parabola GetParabola RhinoGetParabola Paraboloid GetParaboloid RhinoGetParaboloid
-------------------------------------------------------------------*/
class RHINO_SDK_CLASS CArgsRhinoGetParabola
{
public:
  CArgsRhinoGetParabola();
  ~CArgsRhinoGetParabola();

  CArgsRhinoGetParabola(const CArgsRhinoGetParabola&);
  CArgsRhinoGetParabola& operator=(const CArgsRhinoGetParabola&);

  // sets  
  void SetVertexPrompt( const wchar_t* );
  void SetFocusPrompt( const wchar_t* );
  void SetDirectionPrompt( const wchar_t* );
  void SetEndPrompt( const wchar_t* );

  void SetVertexPoint( const ON_3dPoint& );
  void SetFocusPoint( const ON_3dPoint& );
  void SetDirection( const ON_3dVector& );
  void SetEndPoint( const ON_3dPoint& );

  void SetSurfaceMode( BOOL = TRUE );
  void SetVertexMode( BOOL = TRUE );
  void SetHalfMode( BOOL = TRUE );
  void SetCapMode( BOOL = TRUE );
  void SetMarkFocus( BOOL = TRUE );

  
  // gets
  const ON_wString& VertexPrompt() const;
  const ON_wString& FocusPrompt() const;
  const ON_wString& DirectionPrompt() const;
  const ON_wString& EndPrompt() const;

  const ON_3dPoint VertexPoint() const;
  const ON_3dPoint FocusPoint() const;
  const ON_3dVector Direction() const;
  const ON_3dPoint EndPoint() const;

  const BOOL SurfaceMode() const;
  const BOOL VertexMode() const;
  const BOOL HalfMode() const;
  const BOOL CapMode() const;
  const BOOL MarkFocus() const;

protected:
  ON_wString m_VertexPrompt;
  ON_wString m_FocusPrompt;
  ON_wString m_DirectionPrompt;
  ON_wString m_EndPrompt;

  ON_3dPoint m_VertexPoint;
  ON_3dPoint m_FocusPoint;
  ON_3dVector m_Direction;
  ON_3dPoint m_EndPoint;

  BOOL m_SurfaceMode;
  BOOL m_VertexMode;
  BOOL m_CapMode;
  BOOL m_HalfMode;
  BOOL m_MarkFocus;
};

// Description:
//   UI tool to get a parabola curve.
// Parameters:
//   args - [in/out] used to specify ui elements and return
//                   user choices, focus, and vertex.
//   parabola_out - [out] parabola returned here
//   history - [out] optional history information returned here
// Returns:
//   CRhinoCommand::success if successful.
RHINO_SDK_FUNCTION
CRhinoCommand::result RhinoGetParabola( 
          CArgsRhinoGetParabola& args, 
          ON_BezierCurve& parabola_out, 
          CRhinoHistory* history = NULL
          );

// Description:
//   UI tool to get a paraboloid surface or solid.
// Parameters:
//   args - [in/out] used to specify ui elements and return
//                   user choices, focus, and vertex.
//   paraboloid_out - [out] paraboloid returned here
//   history - [out] optional history information returned here
// Returns:
//   CRhinoCommand::success if successful.
RHINO_SDK_FUNCTION
CRhinoCommand::result RhinoGetParaboloid( 
          CArgsRhinoGetParabola& args, 
          ON_Brep*& paraboloid_out,
          CRhinoHistory* history = NULL
          );


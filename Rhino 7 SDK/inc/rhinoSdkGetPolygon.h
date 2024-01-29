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


#define POLYGON_MIN_NUMSIDES 3
#define POLYGON_MAX_NUMSIDES 50000

// SDK header stuff
/*-------------------------------------------------------------------
CLASS
  CArgsRhinoGetPolygon

OVERVIEW TEXT
  Arguments for RhinoGetPolygon... functions

KEYWORDS
  Polygon RhinoGetPolygon GetPolygon
-------------------------------------------------------------------*/
class RHINO_SDK_CLASS CArgsRhinoGetPolygon
{
public:
  CArgsRhinoGetPolygon();
  ~CArgsRhinoGetPolygon();

  CArgsRhinoGetPolygon(const CArgsRhinoGetPolygon&);
  CArgsRhinoGetPolygon& operator=(const CArgsRhinoGetPolygon&);


  //sets
  void SetInscribedCenterPrompt( const wchar_t*);
  void SetInscribedAroundCurveCenterPrompt( const wchar_t*);
  void SetCornerPrompt( const wchar_t*);

  void SetCircumscribedCenterPrompt( const wchar_t*);
  void SetCircumscribedAroundCurveCenterPrompt( const wchar_t*);
  void SetEdgeMidpointPrompt( const wchar_t*);

  void SetEdgeStartPrompt( const wchar_t*);
  void SetEdgeEndPrompt( const wchar_t*);

  void SetStarCenterPrompt( const wchar_t*);
  void SetStarAroundCurveCenterPrompt( const wchar_t*);
  void SetStarEndPrompt( const wchar_t*);  
  void SetStarSecondRadiusPrompt( const wchar_t*);

  void SetCircle( const ON_Circle&);

  void SetFirstPoint( const ON_3dPoint&);
  void SetSecondPoint( const ON_3dPoint&);
  void SetNormal( const ON_3dVector&);
  
  void SetNumSides( int );
  void SetStarSecondRadius( double);

  void SetInscribed( BOOL);
  void SetStarMode( BOOL);
  void SetEdgeMode( BOOL);
  void SetUseFirstPoint( BOOL);
  void SetVertical( BOOL);
  void SetAroundCurve( BOOL);
  void SetCurve(const ON_Curve*);
  void SetUseNormal( BOOL);
  void SetFlip( BOOL);
  void SetUseStarSecondRadius( BOOL);
  void SetGettingStarModePolygon( BOOL);

  void EnableVerticalPolygonOption(bool = true);
  void EnablePyramidOption(bool = true);
  void SetPyramidConstraint(int);
  void SetCap(unsigned int);

  //gets
  const ON_wString& InscribedCenterPrompt() const;
  const ON_wString& InscribedAroundCurveCenterPrompt() const;
  const ON_wString& CornerPrompt() const;

  const ON_wString& CircumscribedCenterPrompt() const;
  const ON_wString& CircumscribedAroundCurveCenterPrompt() const;
  const ON_wString& EdgeMidpointPrompt() const;

  const ON_wString& EdgeStartPrompt() const;
  const ON_wString& EdgeEndPrompt() const;

  const ON_wString& StarCenterPrompt() const;
  const ON_wString& StarAroundCurveCenterPrompt() const;
  const ON_wString& StarEndPrompt() const;  
  const ON_wString& StarSecondRadiusPrompt() const;

  const ON_Circle& Circle() const;

  const ON_3dPoint& FirstPoint() const;
  const ON_3dPoint& SecondPoint() const;
  const ON_3dVector& Normal() const;
  
  int NumSides() const;
  double StarSecondRadius() const;

  const BOOL Inscribed() const;
  const BOOL StarMode() const;
  const BOOL EdgeMode() const;
  const BOOL UseFirstPoint() const;
  const BOOL Vertical() const;
  const BOOL AroundCurve() const;
  const ON_Curve* Curve() const;
  const BOOL UseNormal() const;
  const BOOL Flip() const;
  const BOOL UseStarSecondRadius() const;
  const BOOL GettingStarModePolygon() const;

  const bool VerticalPolygonOptionAvailable() const;
  const bool PyramidOptionAvailable() const;
  const int PyramidConstraint() const;
  unsigned int GetCap() const;

  // variables
  int m_NumSides;

protected:
  ON_wString  m_InscribedCenterPrompt;
  ON_wString  m_InscribedAroundCurveCenterPrompt;
  ON_wString  m_CornerPrompt;

  ON_wString  m_CircumscribedCenterPrompt;
  ON_wString  m_CircumscribedAroundCurveCenterPrompt;
  ON_wString  m_EdgeMidpointPrompt;

  ON_wString  m_EdgeStartPrompt;
  ON_wString  m_EdgeEndPrompt;

  ON_wString  m_StarCenterPrompt;
  ON_wString  m_StarAroundCurveCenterPrompt;
  ON_wString  m_StarEndPrompt;  
  ON_wString  m_StarSecondRadiusPrompt;

  ON_Circle m_Circle;

  ON_3dPoint m_FirstPoint;
  ON_3dPoint m_SecondPoint;
  ON_3dVector m_Normal;
  
  double m_StarSecondRadius;

  BOOL m_Inscribed; // true=inscribed, false=circumscribed
  BOOL m_StarMode; // true=star
  BOOL m_EdgeMode; // true=polygon by edge
  BOOL m_UseFirstPoint;
  BOOL m_Vertical;
  BOOL m_AroundCurve;
  const ON_Curve* m_Curve;
  BOOL m_UseNormal;
  BOOL m_Flip;
  BOOL m_UseStarSecondRadius;
  BOOL m_bGettingStarModePolygon;

  bool m_bVerticalPolygonAvailable;
  bool m_bPyramidAvailable;

private:
  unsigned char m_bCap;        // [io] Used when CRhinoGetPolygon is called by a primitive solid command like pyramid
  unsigned char m_bReserved1;

protected:
  int m_bPyramidConstraint; //0 = None, 1 = Vertical, 2 = AroundCurve

};

// interactive Polygon getter declaration
RHINO_SDK_FUNCTION
CRhinoCommand::result RhinoGetPolygon(
  CArgsRhinoGetPolygon& args,  // [in/out] 
  ON_Polyline& polygon_out,  // [out] Polygon returned here
  CRhinoHistory* history = NULL  // [out] optional history returned here
  );


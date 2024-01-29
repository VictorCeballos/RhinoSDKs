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

/*-------------------------------------------------------------------
CLASS
  CArgsRhinoGetEllipse

OVERVIEW TEXT
  Arguments for RhinoGetEllipse... functions

KEYWORDS
  Ellipse RhinoGetEllipse
-------------------------------------------------------------------*/
class RHINO_SDK_CLASS CArgsRhinoGetEllipse
{
public:
  
  //////////
  // current Ellipse mode of RhinoGetEllipse functions
  enum eEllipseMode
  {
    center,
    centercorner,
    corner,
    diameter,
    fromfoci,
    aroundcurve
  };

  CArgsRhinoGetEllipse();
  ~CArgsRhinoGetEllipse();

  CArgsRhinoGetEllipse(const CArgsRhinoGetEllipse&);
  CArgsRhinoGetEllipse& operator=(const CArgsRhinoGetEllipse&);

  //////////
  // Set a custom prompt to use for getting the first point
  void SetFirstPrompt( const wchar_t* );
  void SetFirstPromptIfEmpty( const wchar_t* );
  const ON_wString& FirstPrompt() const;
  BOOL UseFirstPrompt() const; 

  //////////
  // Set a custom prompt to use for getting the second point
  void SetSecondPrompt( const wchar_t* );
  void SetSecondPromptIfEmpty( const wchar_t* );

  const ON_wString& SecondPrompt() const;
  BOOL UseSecondPrompt() const; 

  //////////
  // Set a custom prompt to use for getting third point
  void SetThirdPrompt( const wchar_t* );
  void SetThirdPromptIfEmpty( const wchar_t* );
  const ON_wString& ThirdPrompt() const;
  BOOL UseThirdPrompt() const; 

  void ClearPrompts( void);

  //////////
  // Set the first point to use instead of asking for one
  void SetFirstPoint( const ON_3dPoint& );
  const ON_3dPoint& FirstPoint() const;
  BOOL UseFirstPoint() const; 

  //////////
  // Set the second point to use instead of asking for one
  void SetSecondPoint( const ON_3dPoint& );
  const ON_3dPoint& SecondPoint() const;
  BOOL UseSecondPoint() const; 

  //////////
  // Set the third point to use instead of asking for one
  void SetThirdPoint( const ON_3dPoint& );
  const ON_3dPoint& ThirdPoint() const;
  BOOL UseThirdPoint() const; 
  void SetUseThirdPoint( BOOL = TRUE);

  //////////
  // Set the Ellipse mode
  void SetEllipseMode( eEllipseMode = center);
  eEllipseMode EllipseMode() const; 

  ///////
  // Set whether the last prompt accepts a number or not. Used in center_start_end
  void SetAcceptNumber( BOOL = TRUE);
  BOOL AcceptNumber() const; 

  ///////
  // Indicates the user wants the ellipse foci marked with point objects
  void SetMarkFoci( BOOL = TRUE);
  BOOL MarkFoci() const; 

  ////////
  // The current third point quadrant in center_start_end
  void SetQuadrant( int);
  int Quadrant() const; 

  ///////
  // The current Ellipse direction in center_start_end
  void SetDir( int);
  int Dir() const; 

  ///////
  // The current Ellipse normal in center_start_end
  void SetNormal( const ON_3dVector&);
  const ON_3dVector& Normal() const; 

  ///////
  // The current Ellipse angle in center_start_angle
  void SetAngle( double);
  const double Angle() const; 

  ///////
  // The eccentricity of FromFoci ellipse
  void SetEccentricity( double);
  const double Eccentricity() const; 

  void SetDeformable( BOOL = TRUE);
  BOOL Deformable() const;

  void SetShowDeformableOption( BOOL = TRUE);
  BOOL ShowDeformableOption() const;

  void SetDeformablePointCount( int = 12);
  BOOL DeformablePointCount() const;

  //Interface to allow primitive mesh creation to use 
  //RhinoGetPlane, RhinoGetBox, RhinoGetCircle etc.
  void SetPromptForMeshDensity( bool bMeshDensity = true);
  bool PromptForMeshDensity() const;

  void SetCapFaceStyle(bool bMakeQuadCaps = true);  // false == tris, true == quads
  bool CapFaceStyle() const;

  // prompt for number of faces in the vertical direction
  const CRhinoCommandOptionName& VerticalMeshDensityDirectionPrompt() const;
  void SetVerticalMeshDensityDirectionPrompt(const CRhinoCommandOptionName&);
  // number of faces in the vertical direction
  int VerticalDirectionCount() const;
  void SetVerticalDirectionCount( int count);
  int VerticalDirectionMinCount() const;
  void SetVerticalDirectionMinCount( int count);

  // prompt for number of faces in the around direction
  const CRhinoCommandOptionName& AroundMeshDensityDirectionPrompt() const;
  void SetAroundMeshDensityDirectionPrompt(const CRhinoCommandOptionName&);
  // number of faces in the around direction
  int AroundDirectionCount() const;
  void SetAroundDirectionCount( int count);
  int AroundDirectionMinCount() const;
  void SetAroundDirectionMinCount( int count);


  double m_rx;
  double m_ry;
  ON_Plane m_plane;
  ON_3dVector m_tangent;            // [i] curve tangent in around curve mode
  BOOL m_tangent_mode;              // true if curve tangent defined

protected:
  ON_wString  m_FirstPrompt;           // [i] Custom prompt for first point
  ON_wString  m_SecondPrompt;           // [i] Custom prompt for second point
  ON_wString  m_ThirdPrompt;           // [i] Custom prompt for third point

  ON_3dPoint  m_FirstPoint;            // [i] if m_bHaveFirstPoint first point specified here
  ON_3dPoint  m_SecondPoint;            // [i] if m_bHaveSecondPoint second point specified here
  ON_3dPoint  m_ThirdPoint;            // [i] if m_bHaveThirdPoint third point specified here
  
  BOOL m_bUseFirstPrompt;              // [i] use custom prompt m_FirstPrompt
  BOOL m_bUseSecondPrompt;              // [i] use custom prompt m_SecondPrompt
  BOOL m_bUseThirdPrompt;              // [i] use custom prompt m_ThirdPrompt

  BOOL m_bUseFirstPoint;               // [i] use m_FirstPoint instead of asking for point
  BOOL m_bUseSecondPoint;               // [i] use m_SecondPoint instead of asking for point
  BOOL m_bUseThirdPoint;               // [i] use m_ThirdPoint instead of asking for point
 
  BOOL m_bAcceptNumber;            // [i] if true, the last prompt accept number. Needed for center_start_end/angle
  BOOL m_bMarkFoci;               // [i] when set, the user wants the ellipse foci to be marked with a point
  
  // Fix for RH-56780 -  Tim February 3, 2020
  // Converted m_bDeformable to a bitfield so we can add extra settings without changing the size of the class.
  int m_bDeformable;               // [i/o] when set, the user wants a deformable ellipse

  BOOL m_bShowDeformableOption;    // [i] when set, the user is allowed to change the deformable option
  int m_deformable_point_count;    // [i/o] defines the requested point count for deformable ellipse

  int m_quadrant;                  // [internal] previous quadrant for last point. Needed for center_start_end/angle
  int m_dir;                       // [internal] previous Ellipse direction. Needed for center_start_end/angle
  double m_angle;                  // [internal] the Ellipse angle, used in center_start_angle
  double m_eccentricity;           // [internal] eccentricity of FromFoci ellipse
  ON_3dVector m_normal;            // [i] the Ellipse normal. Needed for center_start_end/angle

  eEllipseMode m_mode;                 // [internal]  Current mode while drawing the Ellipse

  //Interface to allow primitive mesh creation to use 
  //RhinoGetCylinder, RhinoGetCone, etc.
  bool m_PromptForMeshDensity;
  CRhinoCommandOptionName m_mesh_density_vertical_direction_prompt;
  int m_mesh_density_VerticalDirection;
  int m_mesh_density_MinVerticalDirection;
  CRhinoCommandOptionName m_mesh_density_around_direction_prompt;
  int m_mesh_density_AroundDirection;
  int m_mesh_density_MinAroundDirection;

};

//////////
// describe RhinoGetEllipse
RHINO_SDK_FUNCTION
CRhinoCommand::result RhinoGetEllipse( 
    CArgsRhinoGetEllipse&,
    ON_Ellipse&,
    CRhinoHistory* = NULL // optional history recorder
    );

//////////
// RhinoGetEllipseCenter
RHINO_SDK_FUNCTION
CRhinoCommand::result RhinoGetEllipseCenter( 
    CArgsRhinoGetEllipse&,
    ON_Ellipse&, // output_ellipse
    CRhinoHistory* = NULL // optional history recorder
    );

//////////
// RhinoGetEllipseCorner
RHINO_SDK_FUNCTION
CRhinoCommand::result RhinoGetEllipseCorner( 
    CArgsRhinoGetEllipse&,
    ON_Ellipse&, // output_ellipse
    CRhinoHistory* = NULL // optional history recorder
    );

//////////
// RhinoGetEllipseCenterCorner
RHINO_SDK_FUNCTION
CRhinoCommand::result RhinoGetEllipseCenterCorner( 
    CArgsRhinoGetEllipse&,
    ON_Ellipse&, // output_ellipse
    CRhinoHistory* = NULL // optional history recorder
    );

//////////
// RhinoGetEllipseDiameter
RHINO_SDK_FUNCTION
CRhinoCommand::result RhinoGetEllipseDiameter( 
    CArgsRhinoGetEllipse&,
    ON_Ellipse&, // output_ellipse
    CRhinoHistory* = NULL // optional history recorder
    );

//////////
// RhinoGetEllipseFromFoci
RHINO_SDK_FUNCTION
CRhinoCommand::result RhinoGetEllipseFromFoci( 
    CArgsRhinoGetEllipse&,
    ON_Ellipse&, // output_ellipse
    CRhinoHistory* = NULL // optional history recorder
    );

//////////
// RhinoGetEllipseAroundCurve
RHINO_SDK_FUNCTION
CRhinoCommand::result RhinoGetEllipseAroundCurve( 
    CArgsRhinoGetEllipse&,
    ON_Ellipse&, // output_ellipse
    CRhinoHistory* = NULL // optional history recorder
    );

//////////
// describe RhinoGetEllipsoid
RHINO_SDK_FUNCTION
CRhinoCommand::result RhinoGetEllipsoid( 
    CArgsRhinoGetEllipse&,
    ON_Ellipse&, ON_Ellipse&,
    CRhinoHistory* = NULL // optional history recorder
    );


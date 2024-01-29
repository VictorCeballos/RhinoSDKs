/* $NoKeywords: $ */
/*
//
// Copyright (c) 1993-2012 Robert McNeel & Associates. All rights reserved.
// OpenNURBS, Rhinoceros, and Rhino3D are registered trademarks of Robert
// McNeel & Associates.
//
// THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT EXPRESS OR IMPLIED WARRANTY.
// ALL IMPLIED WARRANTIES OF FITNESS FOR ANY PARTICULAR PURPOSE AND OF
// MERCHANTABILITY ARE HEREBY DISCLAIMED.
//				
// For complete openNURBS copyright information see <http://www.opennurbs.org>.
//
////////////////////////////////////////////////////////////////
*/

#if !defined(OPENNURBS_PLUS) || !defined(OPENNURBS_PLUS_INC_) || defined(OPENNURBS_PUBLIC)
#error This file should not be distributed with the public opennurbs source code toolkit.
#endif

#if !defined(OPENNURBS_PLUS_SQUISH_INC_)
#define OPENNURBS_PLUS_SQUISH_INC_

class ON_CLASS ON_SquishConstraint
{
public:
  // 0 = none
  // 1 = 2d point: (m_v[0],m_v[1])
  // 2 = 2d line:  0 = m_v[0]*x + m_v[1]*y + m_v[2]
  unsigned int m_constraint_type;

private:
  unsigned int m_reserved;

public:
  double m_v[4];
};

#if defined(ON_DLL_TEMPLATE)
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_SquishConstraint>;
#endif

class ON_CLASS ON_SquishConstraints
{
public:
  // m_constraints[] is a list of various constraints
  // you want to apply to some of the mesh's vertices.
  ON_SimpleArray<ON_SquishConstraint> m_constraints;

  // m_constrained_vertices[] is a list that specifies
  // mesh vertices and the constraint. The ON_2dex.i value
  // is a mesh.m_V[] index and the ON_2dex.j value
  // m_constraints[] index.
  ON_SimpleArray<ON_2dex> m_constrained_vertices;
};

class ON_CLASS ON_SquishParameters
{
public:
  ON_SquishParameters();

  void Dump( 
    ON_TextLog& text_log
    ) const;

  void DumpSpringConstants( 
    ON_TextLog& text_log
    ) const;

  void DumpRelativeTolerances( 
    ON_TextLog& text_log
    ) const;

  /*
  Description:
    A simplified interface for setting the m_*_stretch_c 
    and m_*_compress_c constants.
  Parameters:
    boundary_bias - [in]  0.0 to 1.0
      0.0: boundary and interior treated the same
      1.0: strongest bias to preserving boundary lengths at the expense 
           of interior distortion.
    deformation_bias - [in] -1.0 to 1.0
      -1.0: strongest bias in favor of compression.
       0.0: no preference between compression and stretching
       1.0: strongest bias in favor of stretching
  */
  void SetSpringConstants(
    double boundary_bias,
    double deformation_bias
    );

  /*
  Description:
    See if the spring constants could have been set with
    SetSpringConstants().
  Parameters:
    boundary_bias - [out]
    deformation_bias - [out]
  Returns:
    If the spring constants have values that could be set by
    calling SetSpringConstants(), then boundary_bias and
    deformation_bias are set to those values and this function
    returns true.
    Otherwise, boundary_bias and deformation_bias are set to 0.0
    and false is returned.
  */
  bool GetSpringConstants(
    double* boundary_bias,
    double* deformation_bias
    ) const;

  bool Write( 
    class ON_BinaryArchive& binary_archive
    ) const;

  bool Read( 
    class ON_BinaryArchive& binary_archive
    );

  // spring constant for compressed boundary edges is
  // m_boundary_compress_c/(rest length)
  double m_boundary_stretch_c;
  double m_boundary_compress_c;
  double m_interior_stretch_c;
  double m_interior_compress_c;
  double m_diagonal_stretch_c;
  double m_diagonal_compress_c;

  // If a m_..._stretch_rel_tol parameter is > 1.0, then the 
  // mesh will be automatically split in areas where the
  // relative stretch exceedes the specified relative tolerance.
  // If a m_..._compress_rel_tol parameter is > 0.0 and < 1.0,
  // then the mesh will be automatically split in areas where
  // the relative compression exceedes the specified relative
  // tolerance.
  double m_boundary_stretch_rel_tol;
  double m_boundary_compress_rel_tol;
  double m_interior_stretch_rel_tol;
  double m_interior_compress_rel_tol;
  double m_diagonal_stretch_rel_tol;
  double m_diagonal_compress_rel_tol;

  /*
  If -1.0 <= m_absolute_limit < 0.0, then then an absolute
  compression limit is applied so that
  (2d length)/(3d length) >= fabs(m_absolute_limit).
  In particular, if m_absolute_limit = -1.0, then no compression
  is permitted (2d length) >= (3d length).

  If 0.0 < m_absolute_limit <= 1.0 then then an absolute
  stretching limit is applied so that
  (2d length)/(3d length) <= 1/fabs(m_absolute_limit).

  Examples:
    m_absolute_limit
     1.0: no stretching, (2d length) <= 1.0*(3d length)
     0.5: cap on stretching, 0.5*(2d length) <= (3d length)
    -0.5: cap on compression, (2d length) >= 0.5*(3d length)
    -1.0: no compression, (2d length) >= 1.0*(3d length)
  */
  double m_absolute_limit;

  // 0 = geometric flattening algorithm
  //     (scale independent)the "spring" constant is
  //     proportional to 1/L^2 and the result is 
  //     independent of scale.
  // 1 = physical stress flattening algorithm
  //     (scale dependent) the "spring" constant is 
  //     proportional to 1/L.
  unsigned int m_material;

  // If the mesh has coincident vertices and m_bPreserveTopology
  // is true, then the flattening is based on the mesh's
  // topology and coincident vertices will remain coincident.
  // Otherwise coincident vertices are free to move apart.
  bool m_bPreserveTopology;

  // If m_bEnableMapBack is true, then ON_SquishMesh()
  // will save extra information on the squished mesh so 
  // 3d points and curves near the input mesh can be mapped
  // to the squished mesh and 2d points and curves on the 
  // squished mesh can be mapped back to the 3d mesh.
  bool m_bSaveMapping;

  /////////////////////////////////////////////////////////
  //
  // These settings determine how the solution is calculated
  // Leave them as is unless you are debugging.
  //

  // Default is false.  Set to true to debug problem cases.
  bool m_bNewtonPreprocess;

  // Set to true if the initial guess has at least 20% of the
  // triangles in the wrong orientation.
  bool m_bAreaPreprocess;

  // Enables the critical optimization step.
  // Default is true.  Setting it to false is
  // used for debugging the results of the setup
  // and preprocessing steps.
  bool m_bOptimize;

  // Set to true to tune up the result.
  bool m_bLengthPostprocess;

  // Set to bias deformation to happen in regions with
  // relatively more Gaussian curvature.  The mesh's m_K[]
  // values must be set for this setting to have an effect.
  bool m_bGaussianBias;

private:
  bool m_reserved0[5];
  double m_reserved1[16];
  void* m_reserved2[2];

public:
  const static ON_SquishParameters DefaultValue;
};

/*
  Description:
    Use to flatten a mesh.
  Parameters:
    mesh - [in]
      3d mesh to flatten.
    squish_parameters - [in]
      parameters used to calculate the 2d result.
    squish_constraints - [in]
      optional constraints.  Pass null if there
      are not constraints.
    squished_mesh - [in]
      optional parameter that can be used to
      specify where the 2d result should be saved.
  Returns:
    If successful, a flattened mesh.
    Null if not successful.
*/
ON_DECL
ON_Mesh* ON_SquishMesh( 
  const ON_Mesh* mesh,
  const ON_SquishParameters* squish_parameters,
  const ON_SquishConstraints* squish_constraints,
  ON_Mesh* squished_mesh
  );

#endif

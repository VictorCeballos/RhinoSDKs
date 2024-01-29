//
// Copyright (c) 1993-2022 Robert McNeel & Associates. All rights reserved.
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

#if !defined(ON_GEOMETRY_CURVE_ARC_INC_)
#define ON_GEOMETRY_CURVE_ARC_INC_


/*
Description:
  ON_ArcCurve is used to represent arcs and circles.
  ON_ArcCurve.IsCircle() returns true if the curve
  is a complete circle.
Remarks:
	- An ON_ArcCurve is a subcurve of a circle, with a 
	  constant speed parameterization. The parameterization is
	  an affine linear reparameterzation of the underlying arc
	  m_arc onto the domain m_t.
	- A valid ON_ArcCurve has  a strictly increasing Domain() and
		ON_ArePointsCoincident(Start,End) == IsCircle()
*/
class ON_CLASS ON_ArcCurve : public ON_Curve
{
  ON_OBJECT_DECLARE(ON_ArcCurve);

public:
  ON_ArcCurve() ON_NOEXCEPT;
  virtual ~ON_ArcCurve();
  ON_ArcCurve(const ON_ArcCurve&);
	ON_ArcCurve& operator=(const ON_ArcCurve&);

#if defined(ON_HAS_RVALUEREF)
  // rvalue copy constructor
  ON_ArcCurve( ON_ArcCurve&& ) ON_NOEXCEPT;

  // The rvalue assignment operator calls ON_Object::operator=(ON_Object&&)
  // which could throw exceptions.  See the implementation of
  // ON_Object::operator=(ON_Object&&) for details.
  ON_ArcCurve& operator=( ON_ArcCurve&& );
#endif

  // virtual ON_Object::SizeOf override
  unsigned int SizeOf() const override;

  // virtual ON_Object::DataCRC override
  ON__UINT32 DataCRC(ON__UINT32 current_remainder) const override;

  /*
  Description:
    Create an arc curve with domain (0,arc.Length()).
  */
  ON_ArcCurve( 
      const ON_Arc& arc 
      );

  /*
  Description:
    Create an arc curve with domain (t0,t1)
  */
  ON_ArcCurve(
      const ON_Arc& arc,
      double t0,
      double t1
      );

  /*
  Description:
    Creates a curve that is a complete circle with 
    domain (0,circle.Length()).
  */
  ON_ArcCurve(
      const ON_Circle& circle
      );

  /*
  Description:
    Creates a curve that is a complete circle with domain (t0,t1).
  */
  ON_ArcCurve(
      const ON_Circle& circle,
      double t0,
      double t1
      );

  /*
  Description:
    Create an arc curve with domain (0,arc.Length()).
  */
	ON_ArcCurve& operator=(const ON_Arc& arc);

  /*
  Description:
    Creates a curve that is a complete circle with 
    domain (0,circle.Length()).
  */
	ON_ArcCurve& operator=(const ON_Circle& circle);
  
  /////////////////////////////////////////////////////////////////
  // ON_Object overrides

  bool IsValid( class ON_TextLog* text_log = nullptr ) const override;

  void Dump( ON_TextLog& ) const override;

  bool Write(
         ON_BinaryArchive&  // open binary file
       ) const override;

  bool Read(
         ON_BinaryArchive&  // open binary file
       ) override;

  /////////////////////////////////////////////////////////////////
  // ON_Geometry overrides

  int Dimension() const override;

  // virtual ON_Geometry GetBBox override		
  bool GetBBox( double* boxmin, double* boxmax, bool bGrowBox = false ) const override;

  // virtual ON_Geometry GetTightBoundingBox override		
  bool GetTightBoundingBox( class ON_BoundingBox& tight_bbox, bool bGrowBox = false, const class ON_Xform* xform = nullptr ) const override;

  bool Transform( 
         const ON_Xform&
         ) override;

  /////////////////////////////////////////////////////////////////
  // ON_Curve overrides

  // Description:
  //   virtual ON_Curve::SetDomain override.
  //   Set the domain of the curve
  // Parameters:
  //   t0 - [in]
  //   t1 - [in] new domain will be [t0,t1]
  // Returns:
  //   true if successful.
  bool SetDomain(
        double t0, 
        double t1 
        ) override;

  ON_Interval Domain() const override;

  bool ChangeDimension(
          int desired_dimension
          ) override;

  bool ChangeClosedCurveSeam( 
            double t 
            ) override;

  int SpanCount() const override; // number of smooth spans in curve

  bool GetSpanVector( // span "knots" 
         double* // array of length SpanCount() + 1 
         ) const override; //

  int Degree( // returns maximum algebraic degree of any span 
                  // ( or a good estimate if curve spans are not algebraic )
    ) const override;

  bool IsLinear( // true if curve locus is a line segment between
                 // between specified points
        double = ON_ZERO_TOLERANCE // tolerance to use when checking linearity
        ) const override;

  bool IsArc( // ON_Arc.m_angle > 0 if curve locus is an arc between
              // specified points
        const ON_Plane* = nullptr, // if not nullptr, test is performed in this plane
        ON_Arc* = nullptr, // if not nullptr and true is returned, then arc parameters
                         // are filled in
        double = 0.0    // tolerance to use when checking
        ) const override;

  bool IsPlanar(
        ON_Plane* = nullptr, // if not nullptr and true is returned, then plane parameters
                           // are filled in
        double = 0.0    // tolerance to use when checking
        ) const override;

  bool IsInPlane(
        const ON_Plane&, // plane to test
        double = 0.0    // tolerance to use when checking
        ) const override;

  bool IsClosed(  // true if curve is closed (either curve has
        void      // clamped end knots and euclidean location of start
        ) const override;  // CV = euclidean location of end CV, or curve is
                  // periodic.)

  bool IsPeriodic(  // true if curve is a single periodic segment
        void 
        ) const override;
  
  bool IsContinuous(
    ON::continuity c,
    double t, 
    int* hint = nullptr,
    double point_tolerance=ON_ZERO_TOLERANCE,
    double d1_tolerance=ON_ZERO_TOLERANCE,
    double d2_tolerance=ON_ZERO_TOLERANCE,
    double cos_angle_tolerance=ON_DEFAULT_ANGLE_TOLERANCE_COSINE,
    double curvature_tolerance=ON_SQRT_EPSILON
    ) const override;

  bool Reverse() override;       // reverse parameterizatrion
                        // Domain changes from [a,b] to [-b,-a]

  /*
  Description:
    Force the curve to start at a specified point.
  Parameters:
    start_point - [in]
  Returns:
    true if successful.
  Remarks:
    Some end points cannot be moved.  Be sure to check return
    code.
  See Also:
    ON_Curve::SetEndPoint
    ON_Curve::PointAtStart
    ON_Curve::PointAtEnd
  */
  bool SetStartPoint(
          ON_3dPoint start_point
          ) override;

  /*
  Description:
    Force the curve to end at a specified point.
  Parameters:
    end_point - [in]
  Returns:
    true if successful.
  Remarks:
    Some end points cannot be moved.  Be sure to check return
    code.
  See Also:
    ON_Curve::SetStartPoint
    ON_Curve::PointAtStart
    ON_Curve::PointAtEnd
  */
  bool SetEndPoint(
          ON_3dPoint end_point
          ) override;

  bool Evaluate( // returns false if unable to evaluate
         double,         // evaluation parameter
         int,            // number of derivatives (>=0)
         int,            // array stride (>=Dimension())
         double*,        // array of length stride*(ndir+1)
         int = 0,        // optional - determines which side to evaluate from
                         //         0 = default
                         //      <  0 to evaluate from below, 
                         //      >  0 to evaluate from above
         int* = 0        // optional - evaluation hint (int) used to speed
                         //            repeated evaluations
         ) const override;

  bool Trim( const ON_Interval& ) override;

  // Description:
  //   Where possible, analytically extends curve to include domain.
  // Parameters:
  //   domain - [in] if domain is not included in curve domain, 
  //   curve will be extended so that its domain includes domain.  
  //   Will not work if curve is closed. Original curve is identical
  //   to the restriction of the resulting curve to the original curve domain, 
  // Returns:
  //   true if successful.
  bool Extend(
    const ON_Interval& domain
    ) override;

  /*
  Description:
    Splits (divides) the arc at the specified parameter.  
    The parameter must be in the interior of the arc's domain.
    The ON_Curve pointers passed to ON_ArcCurve::Split must 
    either be nullptr or point to ON_ArcCurve objects.
    If a pointer is nullptr, then an ON_ArcCurve will be created 
    in Split().  You may pass "this" as left_side or right_side.
  Parameters:
    t - [in] parameter to split the curve at in the
             interval returned by Domain().
    left_side - [out] left portion of curve returned here.
       If not nullptr, left_side must point to an ON_ArcCuve.
    right_side - [out] right portion of curve returned here
       If not nullptr, right_side must point to an ON_ArcCuve.
  Remarks:
    Overrides virtual ON_Curve::Split.
  */
  bool Split(
      double t,
      ON_Curve*& left_side,
      ON_Curve*& right_side
    ) const override;

#if defined(OPENNURBS_PLUS)
  //////////
  // Find parameter of the point on a curve that is closest to test_point.
  // If the maximum_distance parameter is > 0, then only points whose distance
  // to the given point is <= maximum_distance will be returned.  Using a 
  // positive value of maximum_distance can substantially speed up the search.
  // If the sub_domain parameter is not nullptr, then the search is restricted
  // to the specified portion of the curve.
  //
  // true if returned if the search is successful.  false is returned if
  // the search fails.
  bool GetClosestPoint( const ON_3dPoint&, // test_point
          double*,       // parameter of local closest point returned here
          double = 0.0,  // maximum_distance
          const ON_Interval* = nullptr // sub_domain
          ) const override;

  //////////
  // Find parameter of the point on a curve that is locally closest to 
  // the test_point.  The search for a local close point starts at 
  // seed_parameter. If the sub_domain parameter is not nullptr, then
  // the search is restricted to the specified portion of the curve.
  //
  // true if returned if the search is successful.  false is returned if
  // the search fails.
  bool GetLocalClosestPoint( const ON_3dPoint&, // test_point
          double,    // seed_parameter
          double*,   // parameter of local closest point returned here
          const ON_Interval* = nullptr // sub_domain
          ) const override;

  // virtual ON_Curve override
  int IntersectSelf( 
          ON_SimpleArray<ON_X_EVENT>& x,
          double intersection_tolerance = 0.0,
          const ON_Interval* curve_domain = 0
          ) const override;

  //////////
  // Length of curve.
  // true if returned if the length calculation is successful.
  // false is returned if the length is not calculated.
  //
  // The arc length will be computed so that
  // (returned length - real length)/(real length) <= fractional_tolerance
  // More simply, if you want N significant figures in the answer, set the
  // fractional_tolerance to 1.0e-N.  For "nice" curves, 1.0e-8 works
  // fine.  For very high degree nurbs and nurbs with bad parameterizations,
  // use larger values of fractional_tolerance.
  bool GetLength( // returns true if length successfully computed
          double*,                   // length returned here
          double = 1.0e-8,           // fractional_tolerance
          const ON_Interval* = nullptr  // (optional) sub_domain
          ) const override;

  /*
  Description:
    Used to quickly find short curves.
  Parameters:
    tolerance - [in] (>=0)
    sub_domain - [in] If not nullptr, the test is performed
      on the interval that is the intersection of 
      sub_domain with Domain().
  Returns:
    True if the length of the curve is <= tolerance.
  Remarks:
    Faster than calling Length() and testing the
    result.
  */
  bool IsShort(
    double tolerance,
    const ON_Interval* sub_domain = 0,
    double* length_estimate = 0
    ) const override;


  // Description:
  //   virtual ON_Curve::GetNormalizedArcLengthPoint override.
  //   Get the parameter of the point on the curve that is a 
  //   prescribed arc length from the start of the curve.
  // Parameters:
  //   s - [in] normalized arc length parameter.  E.g., 0 = start
  //        of curve, 1/2 = midpoint of curve, 1 = end of curve.
  //   t - [out] parameter such that the length of the curve
  //      from its start to t is arc_length.
  //   fractional_tolerance - [in] desired fractional precision.
  //       fabs(("exact" length from start to t) - arc_length)/arc_length <= fractional_tolerance
  //   sub_domain - [in] If not nullptr, the calculation is performed on
  //       the specified sub-domain of the curve.
  // Returns:
  //   true if successful
  bool GetNormalizedArcLengthPoint(
          double s,
          double* t,
          double fractional_tolerance = 1.0e-8,
          const ON_Interval* sub_domain = nullptr
          ) const override;

  /*
  Description:
    virtual ON_Curve::GetNormalizedArcLengthPoints override.
    Get the parameter of the point on the curve that is a 
    prescribed arc length from the start of the curve.
  Parameters:
    count - [in] number of parameters in s.
    s - [in] array of normalized arc length parameters. E.g., 0 = start
         of curve, 1/2 = midpoint of curve, 1 = end of curve.
    t - [out] array of curve parameters such that the length of the 
       curve from its start to t[i] is s[i]*curve_length.
    absolute_tolerance - [in] if absolute_tolerance > 0, then the difference
        between (s[i+1]-s[i])*curve_length and the length of the curve
        segment from t[i] to t[i+1] will be <= absolute_tolerance.
    fractional_tolerance - [in] desired fractional precision for each segment.
        fabs("true" length - actual length)/(actual length) <= fractional_tolerance
    sub_domain - [in] If not nullptr, the calculation is performed on
        the specified sub-domain of the curve.  A 0.0 s value corresponds to
        sub_domain->Min() and a 1.0 s value corresponds to sub_domain->Max().
  Returns:
    true if successful
  */
  bool GetNormalizedArcLengthPoints(
          int count,
          const double* s,
          double* t,
          double absolute_tolerance = 0.0,
          double fractional_tolerance = 1.0e-8,
          const ON_Interval* sub_domain = nullptr
          ) const override;
#endif

  // virtual ON_Curve::GetNurbForm override
  int GetNurbForm( // returns 0: unable to create NURBS representation
                   //            with desired accuracy.
                   //         1: success - returned NURBS parameterization
                   //            matches the curve's to wthe desired accuracy
                   //         2: success - returned NURBS point locus matches
                   //            the curve's to the desired accuracy but, on
                   //            the interior of the curve's domain, the 
                   //            curve's parameterization and the NURBS
                   //            parameterization may not match to the 
                   //            desired accuracy.
        ON_NurbsCurve&,
        double = 0.0,
        const ON_Interval* = nullptr     // OPTIONAL subdomain of arc curve
        ) const override;

  // virtual ON_Curve::HasNurbForm override
  int HasNurbForm( // returns 0: unable to create NURBS representation
                   //            with desired accuracy.
                   //         1: success - NURBS parameterization
                   //            matches the curve's
                   //         2: success - returned NURBS point locus matches
                   //            the curve'sbut, on
                   //            the interior of the curve's domain, the 
                   //            curve's parameterization and the NURBS
                   //            parameterization may not match to the 
                   //            desired accuracy.
        ) const override;

  // virtual ON_Curve::GetCurveParameterFromNurbFormParameter override
  bool GetCurveParameterFromNurbFormParameter(
        double, // nurbs_t
        double* // curve_t
        ) const override;

  // virtual ON_Curve::GetNurbFormParameterFromCurveParameter override
  bool GetNurbFormParameterFromCurveParameter(
        double, // curve_t
        double* // nurbs_t
        ) const override;
  
  
  /*
  Description:
    Returns true if this arc curve is a complete circle.
  */
  bool IsCircle() const;

  // Returns:
  //   The arc's radius.
	double Radius() const;

  // Returns:
  //   The arc's subtended angle in radians.
  double AngleRadians() const;

  // Returns:
  //   The arc's subtended angle in degrees.
  double AngleDegrees() const;


  /////////////////////////////////////////////////////////////////

  ON_Arc m_arc = ON_Arc::UnitCircle; // default = radius 1 circle in x-y plane
  
  ON_Interval m_t = ON_Interval::ZeroToTwoPi;

  // The dimension of a arc curve can be 2 or 3.
  // (2 so ON_ArcCurve can be used as a trimming curve)
  int m_dim = 3;
};


#endif

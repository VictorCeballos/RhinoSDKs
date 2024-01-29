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


class RHINO_SDK_CLASS CRhinoClippingPlaneObject : public CRhinoObject
{
  ON_OBJECT_DECLARE(CRhinoClippingPlaneObject);

public:
  CRhinoClippingPlaneObject();                              // assigns a new object UUID
  CRhinoClippingPlaneObject(const ON_3dmObjectAttributes&); // assigns a new object UUID
  CRhinoClippingPlaneObject( const CRhinoClippingPlaneObject& );          // copies source object UUID
  CRhinoClippingPlaneObject& operator=(const CRhinoClippingPlaneObject&); // copies source object UUID
  ~CRhinoClippingPlaneObject();

  // virtual ON_Object override
  void MemoryRelocate() override;

  // virtual CRhinoObject override returns ON::clipping_plane_object
  ON::object_type ObjectType() const override;

  //Description:
  //  virtual CRhinoObject::ShortDescription override
  //Returns:
  //  "clipping plane" or "clipping planes"
  const wchar_t* ShortDescription( bool bPlural ) const override;

  void EnableGrips( bool bGripsOn ) override;
  void Draw(CRhinoDisplayPipeline& dp) const override;

  bool PickFilter( const CRhinoGetObject&, bool ) const override;
  int Pick( const CRhinoPickContext&, CRhinoObjRefArray& ) const override;
  bool SnapTo( const CRhinoSnapContext& snap_context, CRhinoSnapEvent& snap_event ) const override;

  ON_BoundingBox BoundingBox() const override;
  bool GetTightBoundingBox( 
    ON_BoundingBox& tight_bbox, 
    bool bGrowBox = false,
    const ON_Xform* xform = nullptr
    ) const override;

  CRhinoObject* DuplicateRhinoObject() const override;
   
  ON_ClippingPlane ClippingPlane() const;

  ON_ClippingPlaneInfo ClippingPlaneInfo() const;

  const ON_PlaneSurface& PlaneSurface() const;
  bool SetPlaneSurface( const ON_PlaneSurface& ps );

  //Description:
  // A clipping plane object maintains a list of viewports that it clips against.
  // This is stored in ON_ClippingPlane::m_viewport_ids
  //Parameters:
  // viewport_id: [in] the viewport that should be clipped by this object
  //Returns:
  // true if successful
  // false if this object already clips the viewport (the viewport id is already in
  //    the object's list)
  bool AddClipViewport( const ON_UUID& viewport_id );

  //Description:
  // A clipping plane object maintains a list of viewports that it clips against.
  // This is stored in ON_ClippingPlane::m_viewport_ids
  //Parameters:
  // viewport_id: [in] the viewport that should no longer be clipped by this object
  //Returns:
  // true if successful
  // false if this object did not already clip the viewport
  //   (the viewport id was not in the object's list)
  bool RemoveClipViewport( const ON_UUID& viewport_id );

  //Returns:
  // true if the viewport_id is in the list of viewports that this object clips
  bool ClipsViewport( const ON_UUID& viewport_id ) const;

  void DeleteFromDocNotification() override;
  void AddToDocNotification() override;

  void EnableDynamicDisplay(bool bEnable=true);
  bool IsDynamicDisplayEnabled() const;
  
  class CRhClippingPlaneDisplay* ClippingPlaneDisplay() const;

  const ON_ClippingPlaneSurface& ClippingPlaneSurface() const;
  bool SetClippingPlaneSurface(const ON_ClippingPlaneSurface& cps);
  
private:
  ON_ClippingPlaneSurface m_plane;

  void UpdateDisplayLines() const;
  mutable class CRhClippingPlaneDisplay* m_display = nullptr;
  bool m_reserved1 = false;
  bool m_reserved2 = false;
  int m_reserved3 = 0;
  int m_reserved4 = 0;
  ON__UINT_PTR m_sdk_reserved = 0;
};

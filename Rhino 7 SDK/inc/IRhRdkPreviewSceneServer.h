
#pragma once // SDK header

#include "RhRdkDefinitions.h"

class CRhRdkMaterial;
class CRhRdkEnvironment;

/** \class IRhRdkPreviewSceneServer

	This is the interface to RDK's scene server which provides the information necessary to render
	a preview of a material or an environment.
*/
class RHRDK_SDK IRhRdkPreviewSceneServer
{
public:
	virtual ~IRhRdkPreviewSceneServer() { }

	class IObject;

public:
	// Internal interface to set up preview scene.
	enum eGeometry
	{
		geomSphere  = 0,
		geomCuboid  = 1,
		geomCone    = 2,
		geomPyramid = 3,
		geomTorus   = 4,
		geomPlane   = 5,
		geomSelectedObjects = 6, // Not implemented.
		geomMesh    = 7,

		geomForce32bit = 0xFFFFFFFF
	};

public:
	// External interface for sucking the scene details out.

	/** \return A signature value which changes when the scene changes in any way
		that would affect the rendered image. */
	virtual DWORD Signature(void) const = 0;

	/** Set the image used to cache the thumbnail for this scene. */
	virtual void SetCacheImage(const CRhinoDib& image, const UUID& uuidRenderEngine) const = 0;

	/** Return the type id of the content being previewed. */
	virtual const UUID& ContentType(void) const = 0;

	/** Return the kind of the content being previewed. */
	virtual CRhRdkContent::Kinds ContentKind(void) const = 0;

	/** Return the plug-in id of the content being previewed. */
	virtual const UUID& ContentPluginId(void) const = 0;

	/** \return A pointer to the environment that the previewed object is rendered in. */
	virtual const CRhRdkEnvironment* Environment(void) const = 0;

	/** Get information about the view. */
	virtual bool GetView(ON_Viewport& view) const = 0;

	virtual int LightCount(void) const = 0;
	virtual void ResetLightEnumerator(void) const = 0;
	virtual const ON_Light* NextLight(void) const = 0;
	virtual bool Skylighting(void) const = 0;

	/** Support for linear workflow in the preview scene. */
	virtual const IRhRdkLinearWorkflow& LinearWorkflow(void) const = 0;

	RDK_DEPRECATED const class CRhRdkLinearWorkflow& LinearWorkfow(void) const; // Not implemented.

	// Geometry.
	class IGeometry
	{
	public:
		virtual eGeometry Type(void) const = 0;

		/** \return Radius of sphere, radius of base of cone or cylinder. */
		virtual double Radius(void) const = 0;

		/** \return Width of cuboid or base of pyramid. */
		virtual double Width(void) const = 0;

		/** \return Height of cuboid, cone, cylinder or pyramid. */
		virtual double Height(void) const = 0;

		/** Create a mesh of the geometry centered at the origin. */
		virtual void CreateLocalMesh(ON_Mesh& meshOut) const = 0;

		/** Apply UV mapping to the geometry. */
		virtual void ApplyUVMapping(ON_Mesh& meshOut) const = 0;

		/** Emergency virtual function for future expansion. */
		virtual void* EVF(const wchar_t*, void*) = 0;
	};

	// Objects.
	class IObject
	{
	public:
		virtual void CreateMesh(ON_Mesh& meshOut) const = 0;
		virtual IGeometry* Geometry(void) const = 0;
		virtual const CRhRdkMaterial* Material(void) const = 0;
		virtual ON_3dPoint Location(void) const = 0;
		virtual bool Normals(void) const = 0;
		virtual void* EVF(const wchar_t*, void*) = 0;
	};

	class ICancellation
	{
	public:
		virtual ~ICancellation() { }

		/** Set the timeout for cancellation in milliseconds. */
		virtual void SetTimeout(int ms) = 0;

		/** Set whether or not the preview job will be auto-cancelled.
			Jobs are auto-cancelled after 20 seconds by default. */
		virtual void SetSupportCancelation(bool) = 0;

		/** Emergency virtual function for future expansion. */
		virtual void* EVF(const wchar_t*, void*) = 0;
	};

	virtual ICancellation* CancellationToken() const = 0;
	virtual void SetCancellationToken(ICancellation*) = 0;

	/** Set the scale of the scene. */
	virtual void SetSceneScale(double dScale) = 0;

	enum eRotationType { camera, object, unset };
	virtual void ApplyRotation(double dRotationX, double dRotationY, eRotationType type) = 0;

	/** \return The number of objects in the scene. */
	virtual int ObjectCount(void) const = 0;

	/** Reset the enumerator used by NextObject(). */
	virtual void ResetObjectEnumerator(void) const = 0;

	/** \return A pointer to the next object in the scene, or NULL if no more. */
	virtual const IObject* NextObject(void) const = 0;

	/** Emergency virtual function for future expansion. */
	virtual void* EVF(const wchar_t*, void*) = 0;
};

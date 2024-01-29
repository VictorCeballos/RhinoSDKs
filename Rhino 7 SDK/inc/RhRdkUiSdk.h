
#pragma once // UI SDK header

// ##########################################################################################################
// ######
// ###### Important note for plug-in developers:
// ######
// ###### This file was included in the PUBLIC SDK by mistake. 3rd-party plug-ins should not use this.
// ######
// ###### It has only been kept included to avoid breaking the SDK.
// ######
// ##########################################################################################################

#include "RhRdkObject.h"
#include "RhRdkColorButton.h"
#include "RhRdkCity.h"                // Extra header for city UI SDK.
#include "RhRdkTimeZone.h"            // Extra header for sun UI SDK.
#include "RhRdkIORManager.h"          // Extra header for IOR manager SDK.
#include "RhRdkToneMappers.h"         // Extra header for tone mapper UI SDK.
#include "RhRdkNewContentCtrl.h"

class CRhRdkContent;
class IRhRdkContentUI;
class IRhRdkContentKind;
class CRhRdkContentKindList;
class CRhRdkPreviewAppearance;
class CRhRdkDocument;
class CRhRdkPreviewSceneServer;
class CRhRdkPreviewJobSignature;
class CRhRdkPreviewMetaData;

RHRDK_UI_SDK CRhRdkColor RhRdkGetPanelBackgroundColor(RhRdkUiModalities m);

RHRDK_UI_SDK void RhRdkDebugOutput(int category, const wchar_t* wsz);
RHRDK_UI_SDK void RhRdkDebugOutput(int category, const wchar_t* wsz, int level);

// Displays wsz only if RDK_DEBUG_GENERAL is enabled.
RHRDK_UI_SDK void RhRdkOutputDebugString(const wchar_t* wsz);

// Displays wsz with a rolling count which makes it easier to see when a new message comes out.
RHRDK_UI_SDK void RhRdkOutputDebugStringWithCounter(const wchar_t* wsz);

// Reset all "Do not show me again" message boxes in the RDK, and forces checking of textures before rendering.
RHRDK_UI_SDK void RhRdkResetAllMessageBoxes(void);

#ifdef _DEBUG

enum // For RhRdkWantDebugOutput() [SDK_UNFREEZE] This should be enum DebugCategory.
{
	// Do not change the order of these.
	RDK_DEBUG_AUTO_UI,
	RDK_DEBUG_CONTENT_REGISTRY,
	RDK_DEBUG_CONTENT_TAGS,
	RDK_DEBUG_CONTENT_TOOLTIPS,
	RDK_DEBUG_CONTENT_UI,
	RDK_DEBUG_CONTENT_UNDO,
	RDK_DEBUG_CONTENT_USAGE,
	RDK_DEBUG_CURRENT_CONTENT,
	RDK_DEBUG_DOCUMENT,
	RDK_DEBUG_EVENTS,
	RDK_DEBUG_DATA_SOURCE,
	RDK_DEBUG_PROXY_LABEL,
	RDK_DEBUG_PROXY_UPDATE,
	RDK_DEBUG_STORAGE_ACCESS, // OBSOLETE.
	RDK_DEBUG_THREADS,
	RDK_DEBUG_REGISTERABLE_PROPS,
	RDK_DEBUG_DECAL_CRC,
	RDK_DEBUG_DECAL_CRC_DYNAMIC,
	RDK_DEBUG_MENU_ORDER,
	RDK_DEBUG_TO_FILES,
	RDK_DEBUG_GENERAL,

	RDK_DEBUG_COUNTOF // This value can change and is for internal RDK use only.
};

RHRDK_UI_SDK bool RhRdkWantDebugOutput(int d);
RHRDK_UI_SDK bool RhRdkWantDebugOutput(int d, int level);

#define RDK_DEBUG_OUTPUT(category, string) RhRdkDebugOutput(category, string);

#else

RHRDK_UI_SDK bool RhRdkWantDebugOutput(int d);

#define RDK_DEBUG_OUTPUT(category, string) { }

#endif

/** \return the Rhino plug-in id of the RDK plug-in (i.e., 0x1659...) */
RHRDK_UI_SDK UUID RhRdkRhinoPlugInId(void);

RHRDK_UI_SDK CRhRdkPlugIn* RhRdkFindPlugIn(const UUID& uuidRenderEngine);

class RHRDK_UI_SDK IRhRdkCustomExtensions
{
public:
	virtual ~IRhRdkCustomExtensions() { }

	virtual CRhRdkExtension* First(void) const = 0;
	virtual CRhRdkExtension* Next(void) const = 0;

	/** Emergency virtual function for future expansion. */
	virtual void* EVF(const wchar_t*, void*) = 0;
};

RHRDK_UI_SDK IRhRdkCustomExtensions& RhRdkCustomExtensions(void);

class RHRDK_UI_SDK IRhRdkContentCtrlBase : public IRhinoUiWithController
{
public:
	virtual ~IRhRdkContentCtrlBase() { }

	virtual bool ReadOnly(void) const = 0;
	virtual void SetReadOnly(bool b) = 0;
	virtual bool IsEmpty(void) const = 0;
	virtual void ShowIcon(bool b) = 0;
	virtual CRhRdkVariant GetChannelMode(void) const = 0;
	virtual bool SetChannelMode(const CRhRdkVariant& vMode) = 0;
	virtual CRhRdkVariant GetChannelCustom(void) const = 0;
	virtual void SetChannelCustom(const CRhRdkVariant& vCustom) = 0;
	virtual void DisplayData(void) = 0;
	virtual void EnableDisableControls(void) = 0;
	virtual void Change(void) = 0;
	virtual void ShowCheck(bool b) = 0;
	virtual UINT GetCheck(void) const = 0;
	virtual void SetCheck(UINT u) = 0;
	virtual bool CheckEnabled(void) const = 0;
	virtual void SetCheckEnabled(bool b) = 0;
	virtual void ShowAmount(bool b) = 0;
	virtual double GetAmount(void) const = 0;
	virtual void SetAmount(double d) = 0;
	virtual void SetAmountBounds(double dMin, double dMax) = 0;
	virtual bool AmountVaries(void) const = 0;
	virtual void SetAmountVaries(bool b=true) = 0;
	virtual bool AmountEnabled(void) const = 0;
	virtual void SetAmountEnabled(bool b) = 0;

#pragma region RH_C_SHARED_ENUM [IRhRdkContentCtrlBase::NotificationContexts] [ANDYENUM] [nested]
	/// <summary>Notification contexts.</summary>
	enum class NotificationContexts : unsigned int
	{
		/// <summary>Notification is about the check state.</summary>
		Check,
		/// <summary>Notification is about the amount value.</summary>
		Amount,
		/// <summary>Notification is about the content changing.</summary>
		Content,
		/// <summary>Notification is about the properties changing.</summary>
		Props,
	};
#pragma endregion

	/** Set a notification handler. RDK takes ownership of the object.
		When IRhRdkNotificationHandler::OnNotify(), OnBeginNotify() or OnEndNotify() are called,
		the type of the vOld and vNew variants will be as follows:
		- If 'context' is Check   : bool; old and new check states.
		- If 'context' is Amount  : double; old and new amount values.
		- If 'context' is Content : vOld is null, vNew is pointer; must be cast to CRhRdkContentArray*
		- If 'context' is Props   : vOld and vNew are both null.
		  \note If the content array is empty, it means content was deleted, not changed. */
	virtual void SetNotificationHandler(IRhRdkNotificationHandler* pNH) = 0;
};

class RHRDK_UI_SDK IRhRdkSubNodeCtrl
{
public:
	virtual void Delete(void) = 0;

	/** Ask the control to refresh its display */
	virtual void DisplayData(void) = 0;

	/** Get a list of parent instance ids. */
	virtual bool ParentInstanceIdList(CRhRdkUuidCollection& ucOut) const = 0;

	/** Get the child slot name of the sub-node (child). */
	virtual ON_wString ChildSlotName(void) const = 0;

	/** Set the child slot name of the sub-node (child). */
	virtual void SetChildSlotName(const ON_wString& sChildSlotName) = 0;

	enum class IconResults
	{
		Success,
		Failure,
		Varies
	};

	/** Get the dynamic content icon of the sub-node (child).
		\return \e true if successful, \e false if failed (or varies). */
	virtual IconResults DynamicIcon(int w, int h, CRhinoDib& dibOut) const = 0;

	/** \return \e true if the sub-node state varies, \e false. */
	virtual bool Varies(void) const = 0;

	/** Get the base interface. */
	virtual IRhRdkContentCtrlBase& GetBaseInterface(void) = 0;

	/** \return a new instance of an implementation of this interface.
		\param f is the framework to use. The default, 'Auto', will automatically
		 choose the most suitable framework. */
	static class IRhRdkSubNodeCtrl* New(RhRdkUiFrameworks f);

	/** Emergency virtual function for future expansion. */
	virtual void* EVF(const wchar_t* wszFunc, void* pvData) = 0;

protected:
	virtual ~IRhRdkSubNodeCtrl() { }
};

class RHRDK_UI_SDK IRhRdkContentCtrl
{
public:
	virtual void Delete(void) = 0;

	virtual bool GetContentArray(CRhRdkContentArray& aOut) const = 0;
	virtual bool SetContentArray(const CRhRdkContentArray& a) = 0;

	virtual IRhRdkContentCtrlBase& GetBaseInterface(void) = 0;

	static class IRhRdkContentCtrl* New(CRhRdkContent::Kinds kind, RhRdkUiFrameworks f);

	/** Emergency virtual function for future expansion. */
	virtual void* EVF(const wchar_t* wszFunc, void* pvData) = 0;

protected:
	virtual ~IRhRdkContentCtrl() { }
};

class RHRDK_UI_SDK IRhRdkAngleCtrl : public IRhinoUiWindow
{
public:
	virtual bool IsValid(void) const = 0;
	virtual bool DebugColorsOn(void) const = 0;
	virtual void SetDebugColorsOn(bool bOn) = 0;
	virtual COLORREF BackgroundColor(void) const = 0;
	virtual void SetBackgroundColor(COLORREF col) = 0;
	virtual void SetDecoratorPre (class IRhRdkAngleDialDecorator* pDec) = 0;
	virtual void SetDecoratorPost(class IRhRdkAngleDialDecorator* pDec) = 0;
	virtual void SetManualControlOn(bool bOn) = 0;
	virtual void SetHotTrackingOn(bool bOn) = 0;
	virtual double Angle(void) const = 0;
	virtual void SetAngle(double dAngle) = 0;
	virtual void SetDialColors(COLORREF col1, COLORREF col2) = 0;
	virtual bool Varies(void) const = 0;
	virtual void SetVaries(bool b) = 0;

	/** Set a notification handler. RDK takes ownership of the object. */
	virtual void SetNotificationHandler(IRhRdkNotificationHandler* pNH) = 0;

	/** Emergency virtual function for future expansion. */
	virtual void* EVF(const wchar_t* wszFunc, void* pvData) = 0;

protected:
	virtual ~IRhRdkAngleCtrl() { }
};

class RHRDK_UI_SDK IRhRdkAzimuthCtrl
{
public:
	virtual void Delete(void) = 0;

	enum class Display : unsigned int { kNone, kDegrees, kNESW };
	virtual void SetDisplay(Display) = 0;

	virtual IRhRdkAngleCtrl& GetBaseInterface(void) = 0;

	/** \return a new instance of an implementation of this interface.
		\param f is the framework to use. The default, 'Auto', will automatically
		 choose the most suitable framework. */
	static IRhRdkAzimuthCtrl* New(RhRdkUiFrameworks f);

	/** Emergency virtual function for future expansion. */
	virtual void* EVF(const wchar_t* wszFunc, void* pvData) = 0;

protected:
	virtual ~IRhRdkAzimuthCtrl() { }
};

class RHRDK_UI_SDK IRhRdkAltitudeCtrl
{
public:
	virtual void Delete(void) = 0;

	virtual void SetCoWidth(int w) = 0;
	virtual void SetBounds(double dLower, double dUpper) = 0;

	virtual IRhRdkAngleCtrl& GetBaseInterface(void) = 0;

	/** \return a new instance of an implementation of this interface.
		\param f is the framework to use. The default, 'Auto', will automatically
		 choose the most suitable framework. */
	static IRhRdkAltitudeCtrl* New(RhRdkUiFrameworks f);

	/** Emergency virtual function for future expansion. */
	virtual void* EVF(const wchar_t* wszFunc, void* pvData) = 0;

protected:
	virtual ~IRhRdkAltitudeCtrl() { }
};

class RHRDK_UI_SDK IRhRdkBreadcrumbCtrl : public IRhinoUiWithController
{
public:
	virtual void Rebuild(void) = 0;

	virtual ON_Color TextColor(void) const = 0;
	virtual void SetTextColor(const ON_Color& c) = 0;

	virtual ON_Color GrayTextColor(void) const = 0;
	virtual void SetGrayTextColor(const ON_Color& c) = 0;

	virtual ON_Color TopHotColor(void) const = 0;
	virtual void SetTopHotColor(const ON_Color& c) = 0;

	virtual ON_Color BottomHotColor(void) const = 0;
	virtual void SetBottomHotColor(const ON_Color& c) = 0;

	virtual ON_Color BorderColor(void) const = 0;
	virtual void SetBorderColor(const ON_Color& c) = 0;

	/** Set a notification handler. RDK takes ownership of the object. */
	virtual void SetNotificationHandler(IRhRdkNotificationHandler* pNH) = 0;

	static IRhRdkBreadcrumbCtrl* New(RhRdkUiFrameworks f);
};

RHRDK_UI_SDK class IRhRdkContentUIManager* RhRdkFindContentUIManager(const UUID& uuidEditor);

RHRDK_UI_SDK class IRhRdkContentUI* RhRdkFindContentUI(const UUID& uuidUI);

RHRDK_UI_SDK void RhRdkEnableEventMachine(bool bEnable);

RHRDK_UI_SDK ON_wString RhRdkLibrariesFolder(CRhRdkContent::Kinds kind=CRhRdkContent::Kinds::Unset);

RHRDK_UI_SDK ON_wString RhRdkLibrariesRootFolder(void);

RHRDK_UI_SDK bool RhRdkGenerateQuickContentPreview(const CRhRdkContent& c, int width, int height,
                                                   const IRhRdkPreviewSceneServer* pSS, CRhRdkRenderPlugIn::QuickPreviewReason reason,
                                                   bool bSuppressLocalMapping, OUT CRhinoDib& dib);

/** Return codes for RhRdkGenerateRenderedContentPreview() */
enum class RhRdkRCPResult : unsigned int
{
	Rendering, // A preview job was issued to do the rendering using the current renderer.
	CacheOK,   // The 'cache' parameter accepted a cached preview.
	CacheFail, // There was a preview in the cache but it couldn't be loaded.
	Nothing,   // The function did nothing because a new preview was not required or impossible to create.
};

/** Render a content preview using the current renderer. If a suitable preview is cached (and the cache is enabled in options)
	this will output the cached bitmap to 'cache' and return \e CacheOK. If not, a render job will be issued and the function will
	return \e Rendering. The rendered bitmap will (probably) be sent later in an OnPreviewRendered event.
	If the function determines that a rendered preview is not required or impossible to create, it returns \e Nothing.
	If it determines that the preview is cached, but it can't be loaded (corrupt file, etc) it returns \e CacheFail. */
RHRDK_UI_SDK RhRdkRCPResult RhRdkGenerateRenderedContentPreview(const IRhRdkLinearWorkflow& lw, const CRhRdkContent& c, int width, int height,
                                                                bool bSuppressLocalMapping, IN OUT CRhRdkPreviewJobSignature& sig,
                                                                const CRhRdkPreviewAppearance& appearance, OUT CRhinoDib& cache);

enum class RhRdkAccResult : unsigned int
{
	kNonExistent, kNo, kYes
};

RHRDK_UI_SDK const CRhRdkContent* RhRdkCreateContentHelper(CRhRdkDocument& rdkDoc, const CRhRdkContentKindList& topLevelKind, const UUID uuidDefType, const UUID uuidDefInstance, const CRhRdkPreviewMetaData* pMetaData);

RHRDK_UI_SDK RhRdkAccResult RhRdkAddContentCheck(const CRhRdkDocument& rdkDoc, const CRhRdkContent& c);

RHRDK_UI_SDK void RhRdkDeleteTempUnpackedEmbeddedFiles(void);

RHRDK_UI_SDK bool RhRdkHandleTempUnpackedEmbeddedFiles(const wchar_t* wszFullPath, bool bIs3dmFolder=false);

RHRDK_UI_SDK bool RhRdkIsHDRFile(const wchar_t* wszFilename);
RHRDK_UI_SDK bool RhRdkIsEXRFile(const wchar_t* wszFilename);
RHRDK_UI_SDK bool RhRdkIsValidEXRFile(const wchar_t* wszFilename);

RHRDK_UI_SDK bool RhRdkCurrentRendererSupportsFeature(const UUID& uuidFeature);

RHRDK_UI_SDK bool RhRdkRendererSupportsFeature(const UUID& uuidRenderEngine, const UUID& uuidFeature);

RHRDK_UI_SDK bool RhRdkRendererUsesCustomRenderFrameTabs(const UUID& uuidRenderEngine);

RHRDK_UI_SDK double RhRdkTwilightZone(void);

RHRDK_UI_SDK CRhRdkColor RhRdkSunColorFromAltitude(double dAltitude);

RHRDK_UI_SDK extern UUID uuidDialogDangerBegin;
RHRDK_UI_SDK extern UUID uuidDialogDangerEnd;

class RHRDK_UI_SDK CRhRdkDialogDanger final
{
public:
	CRhRdkDialogDanger();
	~CRhRdkDialogDanger();

	static bool IsActive(void);

private:
	static int m_iDanger;
	UINT_PTR m_uReserved;
};

class RHRDK_UI_SDK IRhRdkContentUIs
{
public:
	/** Get all the UIs. */
	virtual void GetUIs(OUT ON_SimpleArray<IRhRdkContentUI*>& aUI) const = 0;

	/** Called when a UI is changed. */
	virtual void Changed(void) = 0;

	/** Emergency virtual function for future expansion. */
	virtual void* EVF(const wchar_t*, void*) = 0;

protected:
	virtual ~IRhRdkContentUIs() { }
};

class RHRDK_UI_SDK IRhRdkContentUIManager
{
public:
	virtual ~IRhRdkContentUIManager() { }

	static IRhRdkContentUIManager* New(void);

	/** Register a content UI.
		\param pUI is the UI to register. */
	virtual void RegisterUI(IRhRdkContentUI* pUI) = 0;

	/** Unregister a content UI.
		\param pUI is the UI to unregister. */
	virtual void UnregisterUI(IRhRdkContentUI* pUI) = 0;

	/** Get all the UIs. */
	virtual void GetUIs(OUT ON_SimpleArray<IRhRdkContentUI*>& aUI) const = 0;

	/** Find a content UI by its unique id.
		\param uuidUI is the unique identifier of the UI to find.
		return A pointer to the UI if it is registered, else null. */
	virtual IRhRdkContentUI* FindUI(const UUID& uuidUI) const = 0;

	/** Set the controller that allows content UIs to communicate with Eto. */
	virtual void SetController(CRhRdkControllerPtr con) = 0;

	/** Deletes unused UIs. */
	virtual void DoGarbageCollection(void) = 0;

	/** Emergency virtual function for future expansion. */
	virtual void* EVF(const wchar_t*, void*) = 0;
};

class RHRDK_UI_SDK CRhRdkCoreContentUI : public CRhRdkObject, public IRhRdkExpandableContentUI
{
public:
	CRhRdkCoreContentUI(const UUID& uuidEditor, const UUID& uuidUI);

public: // Implement IRhRdkContentUI.
	virtual UUID Uuid(void) const override;
	virtual UUID EditorUuid(void) const override;
	virtual int ClientCount(void) const override;
	virtual void AddClient(const CRhRdkContent& c) override;
	virtual void RemClient(const CRhRdkContent& c) override;
	virtual ON_wString DebugString(void) const override;
	virtual CRhRdkControllerPtr Controller(void) const override;
	virtual void SetController(CRhRdkControllerPtr con) override;
	virtual void ReleaseAllClients(void) override;

protected:
	virtual ~CRhRdkCoreContentUI();

	void BrazilWorkaround(const CRhRdkContent& c); // [SDK_UNFREEZE] Delete this obsolete function.

private:
	void operator = (const CRhRdkCoreContentUI&);    // Not implemented.
	CRhRdkCoreContentUI(const CRhRdkCoreContentUI&); // Not implemented.

private:
	class CImpl;
	CImpl* m_pImpl;
};

class RHRDK_UI_SDK CRhRdkPreviewJobSignature : public CRhRdkObject
{
public:
	CRhRdkPreviewJobSignature(int imageWidth, int imageHeight, unsigned long sceneSignature);
	CRhRdkPreviewJobSignature(const CRhRdkPreviewJobSignature& sig);
	virtual ~CRhRdkPreviewJobSignature();

	const CRhRdkPreviewJobSignature& operator = (const CRhRdkPreviewJobSignature& sig);

	bool operator == (const CRhRdkPreviewJobSignature& sig) const;
	bool operator != (const CRhRdkPreviewJobSignature& sig) const;

	bool IsNull(void) const;
	bool IsSceneSignatureEqualTo(DWORD dwSceneSig) const;

	int ImageWidth(void) const;
	int ImageHeight(void) const;

	unsigned long SceneSignature(void) const;

	ON_wString AsString(void) const;

	void Clear(void);

private:
	class CImpl;
	CImpl* m_pImpl;
};

/** \class CRhRdkPreviewSceneElement

	This class represents a scene element which provides information about an element in
	the scene necessary to render a preview of a material or an environment.
	These elements are typically backgrounds, lighting, or simple objects like sphere, cube etc.
*/
class RHRDK_UI_SDK CRhRdkPreviewSceneElement : public CRhRdkObject
{
public:
	CRhRdkPreviewSceneElement();
	virtual ~CRhRdkPreviewSceneElement();

	virtual UUID TypeId(void) const = 0;
	virtual const wchar_t* ElementKind(void) const = 0;
	virtual const wchar_t* XmlTag(void) const = 0;

	virtual CRhRdkPreviewSceneElement* Duplicate(void) const = 0;
};

class RHRDK_UI_SDK CRhRdkPreviewGeometry : public CRhRdkPreviewSceneElement
{
public:
	virtual const wchar_t* ElementKind(void) const final override;

public:
	/** \internal For RDK internal use only. */
	virtual void SetUpPreview(CRhRdkPreviewSceneServer& ss, const CRhRdkContent& c, bool bCopy) const = 0;
};

class RHRDK_UI_SDK CRhRdkPreviewBackground : public CRhRdkPreviewSceneElement
{
public:
	/** If the background uses an environment, return the instance id of the environment.
		The default implementation returns ON_nil_uuid. */
	virtual UUID EnvironmentInstanceId(void) const;

	/** If the background uses an environment, set the instance id of the environment. */
	virtual void SetEnvironmentInstanceId(const UUID& uuidInstance);

public:
	virtual const wchar_t* ElementKind(void) const final override;

public:
	/** \internal For RDK internal use only. */
	virtual void SetUpPreview(CRhRdkPreviewSceneServer& ss, const UUID uuidRdkDoc) const = 0;
};

class RHRDK_UI_SDK CRhRdkPreviewLighting : public CRhRdkPreviewSceneElement
{
public:
	virtual const wchar_t* ElementKind(void) const final override;

public:
	/** \internal For RDK internal use only. */
	virtual void SetUpPreview(CRhRdkPreviewSceneServer& ss) const = 0;
};

#define SS_BASIC_ENV_TEXTURE_CHILD_SLOT_NAME L"texture"

// Preview geometry strings.
#define SS_PG_SPHERE       L"sphere"
#define SS_PG_CUBE         L"cube"
#define SS_PG_CONE         L"cone"
#define SS_PG_PYRAMID      L"pyramid"
#define SS_PG_TORUS        L"torus"
#define SS_PG_PLANE        L"plane"
#define SS_PG_CONE_SPHERE  L"cone-sphere"
#define SS_PG_SCENE        L"material-scene"

RHRDK_UI_SDK CRhRdkPreviewGeometry* RhRdkNewPreviewGeometry(const wchar_t* wszPG);

// Preview background strings.
#define SS_PB_UNUSED     L"unused"
#define SS_PB_NONE       L"none"
#define SS_PB_CHECKERED  L"checkered"
#define SS_PB_CUSTOM     L"custom"
#define SS_PB_SCENE      L"material-scene"

RHRDK_UI_SDK CRhRdkPreviewBackground* RhRdkNewPreviewBackground(const wchar_t* wszPB);

// Preview lighting strings.
#define SS_PL_SIMPLE  L"simple-lighting"
#define SS_PL_SKY     L"skylighting"

RHRDK_UI_SDK CRhRdkPreviewLighting* RhRdkNewPreviewLighting(const wchar_t* wszPL);

// Rotation type.
#define SS_RT_OBJECT  L"object"
#define SS_RT_CAMERA  L"camera"

class RDK_DEPRECATED_CLASS RHRDK_UI_SDK IRhRdkThumbViewDefaults
{
	virtual const wchar_t* Geometry(void) const = 0;
	virtual const wchar_t* Background(void) const = 0;
	virtual const UUID& EnvironmentInstance(void) const = 0;
	virtual double RotationX(void) const = 0;
	virtual double RotationY(void) const = 0;
	virtual double Size(void) const = 0;
	virtual IRhRdkPreviewSceneServer::eRotationType RotationType(void) const = 0;
};

class RHRDK_UI_SDK IRhRdkPreviewAppearanceDefaults
{
public:
	virtual ~IRhRdkPreviewAppearanceDefaults() { }

public:
	/** \return The X rotation angle in degrees. */
	virtual double RotationX(void) const = 0;

	/** \return The Y rotation angle in degrees. */
	virtual double RotationY(void) const = 0;

	/** \return The size of the object in units (base scenes are generally unit-sized). */
	virtual double Size(void) const = 0;

	/** \return The rotation type. */
	virtual IRhRdkPreviewSceneServer::eRotationType RotationType(void) const = 0;

	/** \return The canned geometry type.
		Valid strings for geometry are given above as SS_PG... */
	virtual const wchar_t* Geometry(void) const = 0;

	/** \return The canned background type.
		Valid strings for background are given above as SS_PB... */
	virtual const wchar_t* Background(void) const = 0;

	/** \return The canned lighting type.
		Valid strings for lighting are given above as SS_PL... */
	virtual const wchar_t* Lighting(void) const = 0;

	/** \return The environment instance to use for lighting and background if required. */
	virtual const UUID& EnvironmentInstance(void) const = 0;

	/** Emergency virtual function for future expansion. */
	virtual void* EVF(const wchar_t*, void*) = 0;
};

class RHRDK_UI_SDK CRhRdkPreviewAppearanceDefaults : public IRhRdkPreviewAppearanceDefaults
{
public:
	CRhRdkPreviewAppearanceDefaults();
	virtual ~CRhRdkPreviewAppearanceDefaults();

	void operator = (const CRhRdkPreviewAppearanceDefaults& d);

	void Set(const wchar_t* wszGeometry, const wchar_t* wszBackground, const wchar_t* wszLighting,
	         const UUID& uuidEnvironmentInstance, double dAngleX, double dAngleY, double dSize,
	         IRhRdkPreviewSceneServer::eRotationType rt);

public:
	virtual double RotationX(void) const override;
	virtual double RotationY(void) const override;
	virtual double Size(void) const override;
	virtual IRhRdkPreviewSceneServer::eRotationType RotationType(void) const override;
	virtual const wchar_t* Geometry(void) const override;
	virtual const wchar_t* Background(void) const override;
	virtual const wchar_t* Lighting(void) const override;
	virtual const UUID& EnvironmentInstance(void) const override;
	virtual void* EVF(const wchar_t*, void*) override;

protected:
	class CImpl;
	CImpl* m_pImpl;
};

class RHRDK_UI_SDK CRhRdkPreviewAppearanceDefaults_ByKind : public CRhRdkPreviewAppearanceDefaults
{
public:
	CRhRdkPreviewAppearanceDefaults_ByKind(CRhRdkContent::Kinds kind);
	virtual ~CRhRdkPreviewAppearanceDefaults_ByKind();

	bool Load(void);
	void Save(void) const;

private:
	class CImpl;
	CImpl* m_pImpl2;
};

/** \class CRhRdkPreviewAppearance

	This class represents the appearance of a content preview as seen in a thumbnail image.

*/
class RHRDK_UI_SDK CRhRdkPreviewAppearance : public CRhRdkObject
{
public:
	CRhRdkPreviewAppearance();
	CRhRdkPreviewAppearance(const CRhRdkContent* pContent);
	CRhRdkPreviewAppearance(const CRhRdkPreviewAppearance& v);
	virtual ~CRhRdkPreviewAppearance();

	virtual const CRhRdkPreviewAppearance& operator = (const CRhRdkPreviewAppearance& v);

	virtual bool operator == (const CRhRdkPreviewAppearance& v) const;

	// These angles are in radians.
	virtual double RotationX(void) const;
	virtual void SetRotationX(double d);

	// These angles are in radians.
	virtual double RotationY(void) const;
	virtual void SetRotationY(double d);

	//Call SceneSize for the size, in model units
	/*virtual*/ double SceneSize(void) const; // [SDK_UNFREEZE]

	//Call Size for the size in meters
	virtual double Size(void) const;

	//Set the size in meters.
	virtual void SetSize(double d);

	virtual IRhRdkPreviewSceneServer::eRotationType RotationType(void) const;
	virtual void SetRotationType(IRhRdkPreviewSceneServer::eRotationType type);

	virtual const CRhRdkPreviewGeometry* Geometry(void) const;
	virtual void SetGeometry(const CRhRdkPreviewGeometry* pGeometry);

	virtual const CRhRdkPreviewBackground* Background(void) const;
	virtual void SetBackground(const CRhRdkPreviewBackground* pBackground);

	virtual const CRhRdkPreviewLighting* Lighting(void) const;
	virtual void SetLighting(const CRhRdkPreviewLighting* pLighting);

	virtual void FromMetaData(const IRhRdkPreviewSettings::IMetaData& m);
	virtual void ToMetaData(IRhRdkPreviewSettings::IMetaData& m) const;

	virtual void LoadFromDefaults(const IRhRdkPreviewAppearanceDefaults& viewDefaults);

private:
	class CImpl;
	CImpl* m_pImpl;
};

/** \class CRhRdkPreviewMetaData

	This class represents content preview 'meta data' which is saved in a document.
	This meta data generally contains the properties for all previews in a particular content editor.

*/
class RHRDK_UI_SDK CRhRdkPreviewMetaData : public CRhRdkObject
{
public:
	/** \class CItem. This contains the meta data for a single preview.
		 It corresponds to CRhRdkPreviewAppearance with a few extra values. */
	class RHRDK_UI_SDK CItem final
	{
	public:
		// This section corresponds to CRhRdkPreviewAppearance.
		double m_dRotationX = 0.0;    // The preview's rotation angle in X.
		double m_dRotationY = 0.0;    // The preview's rotation angle in Y.
		double m_dSize = 0.0;         // The preview's size in units. */
		ON_wString m_sRotationType;   // The preview's rotation type (SS_RT...).
		ON_wString m_sGeometry;       // The preview geometry's name (SS_PG...).
		ON_wString m_sBackground;     // The preview background's name (SS_PB...).
		ON_wString m_sLighting;       // The preview lighting's name (SS_PL...).

		// This section contains information about contents.
		UUID m_uuidContentInstance = ON_nil_uuid;   // The instance id of the content that the preview is for.
		UUID m_uuidCustomEnvironment = ON_nil_uuid; // The instance id of an environment used when the preview background is customizable.

		UINT_PTR m_Reserved = 0;        // Reserved for future use.
	};

public:
	CRhRdkPreviewMetaData();
	virtual ~CRhRdkPreviewMetaData();

	/** Set a name for the collection. The name must be unique within the document
		so it is good practise to include a UUID and/or the name of your plug-in.
		Internally the RDK uses a special prefix followed by the editor id. */
	virtual void SetName(const wchar_t* wszName);

	/** Clear the collection. */
	virtual void Clear(void);

	/** Add an item to the collection. */
	virtual void Add(const CItem& desc);

	/** Reset the built-in item iterator. */
	virtual void ResetIterator(void) const;

	/** Get the next item using the built-in item iterator. */
	virtual bool Next(CItem& itemOut) const;

private:
	class CImpl;
	CImpl* m_pImpl;
};

/** \class CRhRdkSSData

	This class contains data about the preview scene server.

*/
class RHRDK_UI_SDK CRhRdkSSData : public CRhRdkObject
{
public:
	enum class Usage : unsigned int
	{
		Synchronous,
		Asynchronous,
	};

	CRhRdkSSData(const CRhRdkPreviewGeometry* pGeo, const CRhRdkPreviewBackground* pBack, const CRhRdkPreviewLighting* pLight, Usage u);
	~CRhRdkSSData();

	Usage GetUsage(void) const;

	const CRhRdkPreviewGeometry* Geometry(void) const;
	const CRhRdkPreviewBackground* Background(void) const;
	const CRhRdkPreviewLighting* Lighting(void) const;

private:
	class CImpl;
	CImpl* m_pImpl;
};

class RHRDK_UI_SDK CRhRdkNewUndoableEvent : public CRhRdkObject
{
public:
	CRhRdkNewUndoableEvent(const IRhinoUiDataSource& h, const wchar_t* wsz);
	CRhRdkNewUndoableEvent(const IRhinoUiDataSourceHost& h, const wchar_t* wsz);

	// This constructor allows a null host and just does nothing.
	// Convenient when you want to put one on the stack without any hassle.
	CRhRdkNewUndoableEvent(const IRhinoUiDataSourceHost* pHost, const wchar_t* wsz);
	virtual ~CRhRdkNewUndoableEvent();

private:
	class CImpl;
	CImpl* m_pImpl;
};

class RHRDK_UI_SDK CRhRdkUndoableEvent : public CRhRdkObject
{
public:
	CRhRdkUndoableEvent(CRhinoDoc& doc, const wchar_t* wszDesc);
	CRhRdkUndoableEvent(CRhinoDoc* pDoc, const wchar_t* wszDesc);
	CRhRdkUndoableEvent(const CRhRdkDocument* pRdkDoc, const wchar_t* wszDesc);
	virtual ~CRhRdkUndoableEvent();

private:
	class CImpl;
	CImpl* m_pImpl;
};

class RHRDK_UI_SDK CRhRdkTextureGraphInfo : public CRhRdkObject
{
public:
	CRhRdkTextureGraphInfo();
	CRhRdkTextureGraphInfo(const CRhRdkTextureGraphInfo& info);
	virtual ~CRhRdkTextureGraphInfo();

	enum class Axis : unsigned int
	{
		kU = 0,
		kV = 1,
		kW = 2,
	};

	enum class Channel : unsigned int
	{
		kRed = 0,
		kGrn = 1,
		kBlu = 2,
		kAlp = 3,
		kLum = 4,
	};

	double AmountU(void) const;
	void SetAmountU(double);

	double AmountV(void) const;
	void SetAmountV(double);

	double AmountW(void) const;
	void SetAmountW(double);

	Axis ActiveAxis(void) const;
	void SetActiveAxis(Axis);

	Channel ActiveChannel(void) const;
	void SetActiveChannel(Channel);

	const CRhRdkTextureGraphInfo& operator = (const CRhRdkTextureGraphInfo& info);

	bool operator == (const CRhRdkTextureGraphInfo& info);
	bool operator != (const CRhRdkTextureGraphInfo& info);

private:
	class CImpl;
	CImpl* m_pImpl;
};

class RHRDK_UI_SDK CRhRdkMaterialCriticalDataPreserver final
{
public:
	CRhRdkMaterialCriticalDataPreserver(ON_Material& mat);
	~CRhRdkMaterialCriticalDataPreserver();

private:
	class CImpl;
	CImpl* m_pImpl;
};

class RHRDK_UI_SDK CRhRdkRhinoObjectList : public CRhRdkObject
{
public:
	CRhRdkRhinoObjectList();
	virtual ~CRhRdkRhinoObjectList();

	void Clear(void);
	int  Count(void) const;
	void Add(const CRhinoObject* pObject);
	void Remove(const CRhinoObject* pObject);
	bool Replace(int iIndex, const UUID& uuid);
	bool Contains(const CRhinoObject& obj) const;
	const CRhinoObject* Object(int iIndex) const;
	void AddObjects(const class CLBPRhObjectSelection& sel);
	CRhinoGet::result SelectAddObjects(void);
	ON_BoundingBox BoundingBox(void) const;

public:
	virtual const CRhinoDoc* GetDocument(void) const = 0;

protected:
	virtual bool Filter(const CRhinoObject* pObject) const;

private:
	class CImpl;
	CImpl* m_pImpl;
};

class RHRDK_UI_SDK CRhRdkDecalCRCList final : public ON_SimpleArray<RDK_DECAL_CRC>
{
	// Implemented in RhRdkDecalSupport.cpp
public:
	CRhRdkDecalCRCList();

	bool ContainsDecalCRC(RDK_DECAL_CRC crc) const;

private:
	void* m_pReserved;
};

class RHRDK_UI_SDK CRhRdkDecalWidgetGeometry : public CRhinoWidgetGeometry
{
	// Implemented in RhRdkDecalWidget.cpp
	ON_OBJECT_DECLARE(CRhRdkDecalWidgetGeometry);
public:
	CRhRdkDecalWidgetGeometry();
	CRhRdkDecalWidgetGeometry(unsigned int doc_sn, const UUID& uuidObject, const UUID& uuidDecal, IRhRdkDecal::eMapping m);
	virtual ~CRhRdkDecalWidgetGeometry();

	const CRhRdkDecalWidgetGeometry& operator = (const CRhRdkDecalWidgetGeometry& g);

	void GetGripPoints(ON_3dPointArray& aOut) const;
	void ApplyTransformation(const ON_Xform& xform) const;
	void SetSweepAngles(const CSweep::CAngles& angles);
	bool GetXformTrans(ON_Xform& xformTransOut) const;
	bool IsAssociatedWithObject(const CRhinoObject& obj) const;
	IRhRdkDecal::eMapping DecalMapping(void) const;
	bool SnapTo(const CRhinoSnapContext& sc, CRhinoSnapEvent& se) const;

public:
	virtual bool AddToDrawCache(IRhWidgetDrawCache& wdc, const ON_Xform& xformLocal, const UUID& uuidObject) override;

private:
	class CImpl;
	CImpl* m_pImpl;
};

class RHRDK_UI_SDK CRhRdkDecalWidget : public CRhinoWidget, protected CRhRdkEventWatcher
{
	// Implemented in RhRdkDecalWidget.cpp
	ON_OBJECT_DECLARE(CRhRdkDecalWidget);
public:
	CRhRdkDecalWidget();
	CRhRdkDecalWidget(const CRhinoObject& obj, RDK_DECAL_CRC crc);
	virtual ~CRhRdkDecalWidget();

	const CRhRdkDecalWidget& operator = (const CRhRdkDecalWidget& w);

	CRhRdkDecalWidgetGeometry& DecalGeometry(void) const;

	UUID DecalId(void) const;
	UUID ObjectId(void) const;

	static void UnselectBrokenWidgets(CRhinoDoc& doc);

	virtual bool GumballHack(const CRhinoDoc& doc, CRhinoGumball& gumball, bool bAlignToObject) const override;

protected:
	virtual int GripOriginIndex(void) const;
	virtual int GripOppositeIndex(int index, int count) const;
	virtual CRhinoWidgetGrip* NewGrip(int index) const;
	virtual const wchar_t* ShortDescription(bool bPlural) const;
	virtual void ComputeFeedback(const ON_Xform& xformDynamic) const;
	virtual void DrawFeedback(const ON_Xform& xformDynamic, CRhinoDisplayPipeline& dp) const;
	virtual void ApplyTransformation(const ON_Xform& xform);
	virtual bool GetXformTrans(ON_Xform& xformTransOut) const;
	virtual void GetGripPoints(ON_3dPointArray& aOut) const;
	virtual bool SnapTo(const CRhinoSnapContext& sc, CRhinoSnapEvent& se) const;
	virtual void AddToDrawCache(CRhinoWidgetGeometry& geom);
	virtual CRhinoWidgetGeometry* NewGeometry(void) const;
	virtual void UpdateFeedbackManager(const CRhinoWidgetGeometry& geom, const ON_Xform& xformLocal) const;
	virtual bool MovesWithAssociatedObjects(void) const;
	virtual bool IsAssociatedWithObject(const CRhinoObject& obj) const;
	virtual void SetGeometryWhenGripDropped(CRhinoWidgetGeometry& newGeom, bool bApplyToDynamicDecal);
	virtual CRhinoWidgetGeometry* NewGeometryForMovedGrip(const CRhinoWidgetGrip& movedGrip) const;
	virtual void OnWidgetDeleted(void);
	virtual bool VetoTransformObject(CRhinoDoc& doc, bool bDeleteOriginal, bool bAddNewObjectToDoc, bool bAddTransformHistory) const override;

protected: // Event watcher overrides.
	virtual void OnUserDataTransformed(const CRhinoObject& obj);

private:
	class CImpl;
	CImpl* m_pImpl;

private:
	CRhRdkDecalWidget(const CRhRdkDecalWidget& w); // Not implemented.
};

class RHRDK_UI_SDK CRhRdkDecalWrapper final
{
	// Implemented in RhRdkDecalSupport.cpp
public:
	CRhRdkDecalWrapper(const CRhinoObject& obj);
	CRhRdkDecalWrapper(const CRhinoObject& obj, RDK_DECAL_CRC decalCRC);
	CRhRdkDecalWrapper(unsigned int doc_sn, const UUID& uuidObject, const UUID& uuidDecal);
	~CRhRdkDecalWrapper();

public: // Object operations.
	bool HasValidObject(void) const;
	RDK_DECAL_CRC FindDecalCRC(const UUID& uuidInstance) const;
	bool CullIdenticalDecals(void);

public: // Event operations
	void SendModifiedEvent(RDK_DECAL_CRC old_decal_crc) const;
	void SetTriggerModifiedEvents(bool bTriggerModifiedEvents);

public: // Decal operations.
	const IRhRdkDecal* GetDecal(void) const;

	/** Replaces any wrapped decal with a new one for the decalCRC. */
	const IRhRdkDecal* GetDecalForCRC(RDK_DECAL_CRC decalCRC) const;

	bool IsValid(void) const;
	bool HasValidDecal(void) const;
	void GetDecalCRCList(CRhRdkDecalCRCList& listOut) const;
	void ApplyTransformation(const ON_Xform& xform);
	bool RemoveValue(const wchar_t* wsz) const;
	void Delete(void) const;
	void Move(RDK_DECAL_CRC crcTo) const;
	UUID DecalInstanceId(void) const;
	UUID TextureInstanceId(void) const;
	RDK_DECAL_CRC CRC(void) const;
	IRhRdkDecal::eMapping Mapping(void) const;
	IRhRdkDecal::eProjection Projection(void) const;
	bool MapToInside(void) const;
	double Transparency(void) const;
	ON_3dPoint Origin(void) const;
	ON_3dVector VectorUp(void) const;
	ON_3dVector VectorAcross(void) const;
	double Height(void) const;
	double Radius(void) const;
	void GetHorzSweep(double& sta, double& end) const;
	void GetVertSweep(double& sta, double& end) const;
	const IRhRdk_XMLSection* CustomData(void) const;
	void SetCustomData(const IRhRdk_XMLSection& section);
	const ON_TextureMapping* TextureMapping(void) const;
	CRhRdkTexture::ProjectionModes TextureProjectionMode(void) const;
	void UVBounds(double& dMinUOut, double& dMinVOut, double& dMaxUOut, double& dMaxVOut) const;
	void SetMapping(IRhRdkDecal::eMapping m);
	void SetProjection(IRhRdkDecal::eProjection p);
	void SetMapToInside(bool b);
	void SetTransparency(double d);
	void SetTextureInstanceId(const UUID& uuidInstance);
	void SetOrigin(const ON_3dPoint& pt);
	void SetVectorUp(const ON_3dVector& vec);
	void SetVectorAcross(const ON_3dVector& vec);
	void SetHeight(double dHeight);
	void SetRadius(double dRadius);
	void SetHorzSweep(double sta, double end);
	void SetVertSweep(double sta, double end);
	void SetUVBounds(double dMinU, double dMinV, double dMaxU, double dMaxV);

private:
	void OnDecalModified(RDK_DECAL_CRC old_decal_crc) const;

	bool m_bTriggerModifiedEvents = true;

private:
	class CImpl;
	CImpl* m_pImpl;
};

class RHRDK_UI_SDK CRhRdkUiScrollBarInfo final
{
public:
	CRhRdkUiScrollBarInfo();

public:
#ifdef ON_RUNTIME_WIN //This will probably look different on the Mac - or it will need to be abstracted across the platforms
	SCROLLINFO siH;
	SCROLLINFO siV;
#endif
	UINT_PTR m_uReserved;
};

class RHRDK_UI_SDK CRhRdkRenderingInfo final
{
public:
	CRhRdkRenderingInfo();
	CRhRdkRenderingInfo(const CRhRdkRenderingInfo&);
	~CRhRdkRenderingInfo();

	void operator = (const CRhRdkRenderingInfo&);

	bool ReadFromFile(const wchar_t* wszFilename);

	// For internal RDK use only.
	class CRhRdkRenderingInfoExtension& GetExtension(void) const;

public:
	UUID m_uuidRenderer;
	ON_wString m_sRenderer;
	ON_wString m_sFilename;
	int m_iElapsedSeconds; // Legacy value for old rimage files.
	UINT_PTR m_uReserved;  // Now used for an extension. Not exposed here.
};

class RHRDK_UI_SDK CRhRdkImageAdjust : public CRhRdkObject, public IRhRdkImageAdjust
{
public:
	CRhRdkImageAdjust();
	CRhRdkImageAdjust(const CRhRdkImageAdjust& a);
	virtual ~CRhRdkImageAdjust();

	const CRhRdkImageAdjust& operator = (const CRhRdkImageAdjust& a);
	const CRhRdkImageAdjust& operator = (const IRhRdkImageAdjust& a);

	bool operator == (const IRhRdkImageAdjust& a) const;
	bool operator == (const CRhRdkImageAdjust& a) const;
	bool operator != (const CRhRdkImageAdjust& a) const;

	virtual IRhRdkDithering::Methods Dither(void) const override;
	virtual void SetDither(IRhRdkDithering::Methods dm) override;

	virtual float Gamma(void) const override;
	virtual void SetGamma(float f) override;

	virtual IRhRdkToneMapping& ToneMapping(void) const override;

	virtual bool IsEqual(const IRhRdkImageAdjust& a) const override;

	virtual void* EVF(const wchar_t*, void*) override { return nullptr; }

protected:
	class CImpl;
	CImpl* m_pImpl;
};

RDK_DEPRECATED_CLASS class RHRDK_UI_SDK CRhRdkDocRenderedImageAdjust : public CRhRdkImageAdjust // OBSOLETE; not implemented.
{
public:
	CRhRdkDocRenderedImageAdjust(const CRhinoDoc& doc);
};

RHRDK_UI_SDK void RhRdkCleanUpRecentRenderingFiles(void);
RHRDK_UI_SDK ON_wString RhRdkRecentRenderingFolder(void);
RHRDK_UI_SDK ON_wString RhRdkMostRecentRenderingFilename(void);

RDK_DEPRECATED_CLASS class RHRDK_UI_SDK CRhRdkActions : public IRhRdkActions // OBSOLETE; not implemented.
{
public:
	CRhRdkActions();
	virtual ~CRhRdkActions();

	virtual int Count(void) const;
	virtual bool Add(CRhRdkAction* pAction);
	virtual CRhRdkAction* Action(int iIndex) const;
	virtual CRhRdkAction* Find(const UUID& uuidAction) const;
	virtual CRhRdkAction* Find(unsigned short cmd) const;

private:
	class CImpl;
	CImpl* m_pImpl;
};

class RHRDK_UI_SDK IRhRdkIORContextMenu
{
public:
	virtual ~IRhRdkIORContextMenu() { }

	virtual void DeleteThis(void) = 0;

	/** Display and track the context menu.
		\param pWnd is the window that displays the menu, for example an edit box.
		\param point is the position to display the menu at inside the window.
		\param dIOROut accepts the IOR value of the user's chosen substance.
		\param pStringOut accepts the name of the user's chosen substance. Can be NULL if not required.
		\return \e true if the user chose a substance, else \e false. */
	virtual bool TrackMenu(HWND pWnd, const ON_2iPoint& point, double& dIOROut, ON_wString* pStringOut=nullptr) const = 0;

	/** Emergency virtual function for future expansion. */
	virtual void* EVF(const wchar_t*, void*) = 0;
};

/** \class IRhRdkSdkContentThumbnailList

	Legacy SDK thumbnail list. TODO: Needs review. Might not be needed anymore.

*/
class RHRDK_UI_SDK IRhRdkSdkContentThumbnailList
{
public:
	virtual ~IRhRdkSdkContentThumbnailList() { }

	virtual void DeleteThis(void) = 0;
	virtual UUID Uuid(void) const = 0;
	virtual void Destroy(void) = 0;
	virtual void Move(const ON_4iRect& rect) = 0;
	virtual int Gap(void) const = 0;
	virtual int Border(void) const = 0;
	virtual void GetThumbnailSize(int& w, int& h) const = 0;
	virtual bool ScrollBarVisible(void) const = 0;
	virtual bool GridModeVertical(void) const = 0;
	virtual void SetGridModeVertical(bool) = 0;
	virtual const CRhRdkThumbArray& GetSelection(void) const = 0;
	virtual void SetSelection(const CRhRdkThumbArray& aThumb, bool) = 0;
	virtual void GetContentArray(const CRhRdkThumbArray& aThumb, CRhRdkInstanceIdArray& aContentOut) const = 0;
	virtual unsigned int SelChangingMessageNumber(void) const = 0;
	virtual unsigned int SelChangedMessageNumber(void) const = 0;
	virtual unsigned int DoubleClickedMessageNumber(void) const = 0;
	virtual unsigned int ThumbSizeChangedMessageNumber(void) const = 0;

	/** Emergency virtual function for future expansion. */
	virtual void* EVF(const wchar_t*, void*) = 0;
};

// BEGIN - Support for Missing Images dialog.

void RHRDK_UI_SDK RhRdkListFileUsers(const CRhinoDoc& doc, const wchar_t* wszFilename, ON_ClassArray<ON_wString>& aResult, ON_SimpleArray<UUID>& aUuidResult);
void RHRDK_UI_SDK RhRdkReplaceTexture(CRhinoDoc& doc, const wchar_t* wszFilenameOld, const wchar_t* wszFilenameNew);
bool RHRDK_UI_SDK RhRdkSearchOnline(CRhinoDoc& doc, const wchar_t* wszFilename);

// END   - Support for Missing Images dialog.

RHRDK_UI_SDK bool RhRdkHere(double& dLatitude, double& dLongitude);

RHRDK_UI_SDK ON_wString RhRdkSmartUndoString(CRhRdkControllerPtr con,  const wchar_t* wszField, const wchar_t* wszNoField=nullptr);
RHRDK_UI_SDK ON_wString RhRdkSmartUndoString(const IRhinoUiSection& s, const wchar_t* wszField, const wchar_t* wszNoField=nullptr);

class RHRDK_UI_SDK IRhRdkSectionFactory
{
public:
	/*virtual ~IRhRdkSectionFactory() { } // [SDK_UNFREEZE]*/

	virtual IRhinoUiSection* Create(const UUID& id) const = 0;

	/** Emergency virtual function for future expansion. */
	virtual void* EVF(const wchar_t*, void*) = 0;
};

class RHRDK_UI_SDK IRhRdkControllerFactory
{
public:
	/*virtual ~IRhRdkControllerFactory() { } // [SDK_UNFREEZE]*/

	virtual CRhRdkControllerPtr Create(const UUID& id) const = 0;

	/** Emergency virtual function for future expansion. */
	virtual void* EVF(const wchar_t*, void*) = 0;
};

RHRDK_UI_SDK void RhRdkRegisterSectionFactory(IRhRdkSectionFactory* pSection);
RHRDK_UI_SDK IRhinoUiSection* RhRdkNewSectionFromFactory(const UUID& id);

RHRDK_UI_SDK void RhRdkRegisterControllerFactory(IRhRdkControllerFactory* pSection);
RHRDK_UI_SDK CRhRdkControllerPtr RhRdkNewControllerFromFactory(const UUID& id);

RHRDK_UI_SDK void RhRdkCustomRenderFrameTabFactoriesForRenderer(const ON_UUID& uuidRenderEngine, ON_SimpleArray<const CRhRdkRenderFrameTabFactory*>& aTabs);

RHRDK_UI_SDK void RhRdkSendCustomEvent(const UUID& uuidCode, void* pvContext);

// Get the font to use for dialogs (MS Shell Dlg, 8-point).
RHRDK_UI_SDK HFONT RhRdkGetDialogFont(void);

class RHRDK_UI_SDK CRhRdkWorldMapDayNight : public CRhRdkObject
{
public:
	CRhRdkWorldMapDayNight();
	virtual ~CRhRdkWorldMapDayNight();

	int Width(void) const;
	int Height(void) const;

	const CRhinoDib& Map(void) const;

	// Force the creation of the bitmap.
	const CRhinoDib& MakeMapBitmap(void);

	bool HasMapForCurrentSettings(void) const;

	void SetDayNightDisplay(bool bOn);
	void SetEnabled(bool bEnabled);
	void SetTimeInfo(int year, int month, int day, double decimalHour, double timeZone, int daylightSavingMinutes, bool bDaylightSavingsOn);

	void LocationToMap(double dLatitude, double dLongitude, int& iMapX, int& iMapY) const;
	void MapToLocation(int iMapX, int iMapY, double& dLatitude, double& dLongitude) const;

private:
	class CImpl;
	CImpl* m_pImpl;
};

enum class SimpleBumpTypes : int
{
	None,
	Hatch,
	Crosshatch,
	Dot,
	Grit,
	Leather,
	Speckle
};

RHRDK_UI_SDK SimpleBumpTypes RhRdkSimpleBumpTypeFromString(const ON_wString& stype);
RHRDK_UI_SDK ON_wString RhRdkStringFromSimpleBumpType(SimpleBumpTypes t);
RHRDK_UI_SDK CRhRdkContent* RhRdkCreateBumpTextureFromType(SimpleBumpTypes t);
RHRDK_UI_SDK UUID RhRdkBumpTextureTypeFromType(SimpleBumpTypes t);

RDK_DEPRECATED RHRDK_UI_SDK void RhRdkEarlyPlugInsAddCustomSections(void); // OBSOLETE; not implemented.

RHRDK_UI_SDK void RhRdkEarlyPlugInsCreateAutoUI(void);

bool RHRDK_UI_SDK RhRdkCheckSearchPattern(const wchar_t* wszName, const wchar_t* wszNotes, const wchar_t* wszTags, const wchar_t* wszPattern);

bool RHRDK_UI_SDK RhRdkDibIcon(DWORD idi, const ON_2iSize& size, OUT CRhinoDib& dib);

// These functions check if a string starts with 'name:' 'notes:' 'tags:' etc.
// They account for localization and are case-insensitive.
bool RHRDK_UI_SDK RhRdkStartsWithNamePrefix(const wchar_t* wsz);
bool RHRDK_UI_SDK RhRdkStartsWithNotePrefix(const wchar_t* wsz);
bool RHRDK_UI_SDK RhRdkStartsWithTagPrefix(const wchar_t* wsz);

/** Replace a content in a document. Can be called after CRhRdkContent::Edit().
	\param rdkDoc is the document to replace the content in.
	\param aOld is an array of content to replace. This content must be registered in rdkDoc or the function will fail.
	\param aNew is an array of content to replace the old content with. This content must not be registered with a document
	 or the function will fail.
	\note aOld and aNew must be the same size or the function will fail.
	 The instance ids of each content in the aOld and aNew arrays must match or the function will fail.
	\return \e true if successful, else \e false. */
bool RHRDK_UI_SDK RhRdkReplaceContentInDocument(const CRhRdkDocument& rdkDocIn, const CRhRdkContentArray& aOld, const CRhRdkContentArrayNC& aNew);

/** \class CRhRdkContentEditor

	You should derive your content editor class from this instead
	of trying to implement IRhRdkContentEditor which will not work
	because this class does some critical operations behind the scenes.

*/
class RHRDK_UI_SDK CRhRdkContentEditor : public IRhRdkContentEditor
{
public:
	CRhRdkContentEditor(RhRdkUiFrameworks f, IRhRdkEditor::Types t, CRhRdkContent::Kinds kind, int inPlaceId=0);
	virtual ~CRhRdkContentEditor();

	void SetUiHostWindow(HWND h);
	void SetController(CRhRdkControllerPtr con);
	void SetRdkDocumentId(const UUID& uuidRdkDoc);

public: // Implement IRhRdkContentEditor.
	virtual UUID Id(void) const override;
	virtual RhRdkUiFrameworks Framework(void) const override;
	virtual Types Type(void) const override;
	virtual RhRdkUiModalities Modality(void) const override;
	virtual CRhRdkControllerPtr Controller(void) const override;
	virtual CRhRdkContent::Kinds TopLevelKind(void) const override;
	virtual void OnContentUICreated(class IRhRdkContentUI& ui) override;
	virtual HWND UiHostWindow(void) const override;
	virtual void* EVF(const wchar_t*, void*) override;

private:
	class CImpl;
	CImpl* m_pImpl;
};

/** \return \e true if private content can be shown by the UI, else \e false.
	This is controlled by the TestShowPrivateContent command. */
RHRDK_UI_SDK bool RhRdkShowPrivateContent(void);

class RHRDK_UI_SDK IRhRdkRenderUI
{
public:
	virtual bool ShowRenderedImage(void) const = 0;
	virtual bool SaveRenderedImage(const wchar_t* wszFilename) = 0;
	virtual void Dismiss(void) = 0;

	virtual HWND PostEffectPanelHost(void) const = 0;
	virtual void OnProcessImageBegin(const wchar_t* wszPlugIn) = 0;
	virtual void OnProcessImageEnd(const wchar_t* wszPlugIn) = 0;
	virtual void OnProcessImageProgress(const wchar_t* wszPlugIn, float fProgress) = 0;
	virtual bool IsProcessInterrupted(void) const = 0;
	virtual bool IsPickPointOnImageImplemented(void) const = 0;
	virtual bool PickPointOnImage(int& x, int& y, HCURSOR hCursor) = 0;
	virtual bool PickRectangleOnImage(ON_4iRect& rectOut, HCURSOR hCursor) = 0;

	class RHRDK_UI_SDK CInfo final
	{
	public:
		CInfo();

		CRhRdkUiScrollBarInfo m_SBI;
		ON_wString m_sFilename;
		ON_4iRect m_Rect;
		float m_fZoom;
		bool m_bPostEffectsVisible;
		bool m_bToolBarVisible;
		bool m_bShowRenderedImage;
		bool m_bMinimized;
		UINT_PTR m_uReserved;
	};
	virtual bool GetInfo(CInfo& info) const = 0;

	/** Emergency virtual function for future expansion. */
	virtual void* EVF(const wchar_t*, void*) = 0;

protected:
	virtual ~IRhRdkRenderUI() { }
};

/** \class IRhRdkTinyIcons

	Interface for displaying tiny icons on thumbnails.

	\see uuidData_RdkTinyIcons

*/
class RHRDK_UI_SDK IRhRdkTinyIcons
{
public:
	class RHRDK_UI_SDK IIcon
	{
	public:
		virtual ON_4iRect Rect(void) const = 0;
		virtual ON_wString ToolTip(void) const = 0;
		virtual const CRhinoDib& Dib(void) const = 0;

		/** Emergency virtual function for future expansion. */
		virtual void* EVF(const wchar_t*, void*) = 0;

	protected:
		virtual ~IIcon() { }
	};

	class RHRDK_UI_SDK IIterator
	{
	public:
		/** Reset the iterator. */
		virtual void Reset(void) = 0;

		/** Get the next icon from the collection.
			\note The returned object is temporary. Do not store a pointer to this object.
			\return The next item or null if no more. */
		virtual const IIcon* Next(void) = 0;

		/** This method is implemented as \code delete this; \endcode */
		virtual void DeleteThis(void) = 0;

		/** Emergency virtual function for future expansion. */
		virtual void* EVF(const wchar_t*, void*) = 0;

	protected:
		virtual ~IIterator() { }
	};

	/** \return a new icon iterator. The caller shall call DeleteThis()
		 on the iterator when it is no longer needed. */
	virtual IIterator* NewIterator(const CRhRdkContent& c, const ON_4iRect& rectIconArea) const = 0;

	/** Emergency virtual function for future expansion. */
	virtual void* EVF(const wchar_t* wszFunc, void* pvData) = 0;

protected:
	virtual ~IRhRdkTinyIcons() { }
};

class RHRDK_UI_SDK CRhRdkTinyIcon : public IRhRdkTinyIcons::IIcon
{
public:
	void SetRect(const ON_4iRect& rect);
	void SetToolTip(const wchar_t* wsz);
	void SetDib(const CRhinoDib& dib);

	void CopyFrom(const IRhRdkTinyIcons::IIcon& icon);

public:
	virtual ON_4iRect Rect(void) const override;
	virtual ON_wString ToolTip(void) const override;
	virtual const CRhinoDib& Dib(void) const override;
	virtual void* EVF(const wchar_t* wszFunc, void* pvData) override { return nullptr; }

private:
	ON_4iRect m_Rect;
	CRhinoDib m_Dib;
	ON_wString m_sToolTip;
};

void RHRDK_UI_SDK RhRdkGetTinyIconArray(const CRhRdkContent& c, const ON_4iRect& rectIconArea, OUT ON_ClassArray<CRhRdkTinyIcon>& a);

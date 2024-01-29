
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

#include "RhRdkUuids.h"
#include "RhRdkEventWatcher.h"

/** \class IRhinoUiEventInfo

	Used by certain data source events. Depending on the event UUID
	this interface is cast to a more specific interface to allow
	information about the event to be retrieved.

*/
class RHRDK_SDK IRhinoUiEventInfo
{
public:
	/** Emergency virtual function for future expansion. */
	virtual void* EVF(const wchar_t*, void*) = 0;

protected:
	virtual ~IRhinoUiEventInfo() { }
};

/** \class IRhinoUiDataSourceEventWatcher

	Any object that has access to a data source can register itself
	to receive events from that data source by implementing this
	interface and calling IRhinoUiDataSource::RegisterEventWatcher()

*/
class RHRDK_SDK IRhinoUiDataSourceEventWatcher
{
public:
	/** Implement this method to unregister and delete the event watcher. */
	virtual void Delete(void) = 0;

	/** Currently implemented by EVF. It should supplement Delete() which should only delete it.
		Sometimes an event watcher needs to be unregistered without being deleted. */
		//[SDK_UNFREEZE] virtual void OnDeleteDataSource(IRhinoUiDataSource* pDS) = 0;

	/** Implement this method to handle an event when the data of a certain type changes.
		Your handler will typically transfer data of that type to elements of your user interface.
		\param uuidData is the identifier of the data.
		\param pInfo is a pointer to an object that contains more information about the event.
		\see IRhinoUiDataSource::RegisterEventWatcher() */
	virtual void OnEvent(const UUID& uuidData, const IRhinoUiEventInfo* pInfo) = 0;

	/** Emergency virtual function for future expansion.
		Vanilla (non-host) data source event watchers \e must unregister by handling EVF(\"OnDeleteDataSource\")
		wszFunc = "OnDeleteDataSource", pvData = IRhinoUiDataSource* */
	virtual void* EVF(const wchar_t* wszFunc, void* pvData) = 0;

protected:
	virtual ~IRhinoUiDataSourceEventWatcher() { }
};

/** \class IRhinoUiDataSourceHost

	A data source host is an object, usually a controller, that hosts one or more data sources.
	These data sources allow the host to get or set data that is stored somewhere, often in a document.
	All data source hosts are automatically also data source event watchers which means they can
	be notified when the data changes. A data source host can host any number of data sources,
	each one capable of providing different data types. Note that the host does not own the
	data sources, it simply stores references to them.

*/
class RHRDK_SDK IRhinoUiDataSourceHost : public IRhinoUiDataSourceEventWatcher
{
public:
	/** Add a data source to the host. The implementation of this method
		typically also registers the host as a data source event watcher. */
	virtual void AddDataSource(class IRhinoUiDataSource& ds) = 0;

	/** Removes a data source from the host. This is called when a data source
		is being deleted. The implementation of this method typically also
		unregisters the host as a data source event watcher. */
	virtual void RemoveDataSource(IRhinoUiDataSource& ds) = 0;

	/** Get the data sources that are being hosted. */
	virtual void GetDataSources(ON_SimpleArray<IRhinoUiDataSource*>& aOut) const = 0;

	/** Copy the data sources from another host. The implementation of this method
		typically also registers this host as a data source event watcher. */
	virtual void CopyDataSourcesFrom(IRhinoUiDataSourceHost& host) = 0;

	/** Get data, specified by a unique id, from one of the host's data source(s).
		Each data source will be asked to provide the data until either one provides
		it or there are no more data sources to ask.
		\param uuidData is the identifier of the data.
		\param bForWrite is \e true if the data source is going to be written to.
		 Every call to GetData() with bForWrite=true \e must be matched by a call to either Commit() or Discard().
		\param bAutoChangeBracket is \e true if a content change bracket should be applied.
		\return The data from a data source or null if no such data could be provided. */
	virtual void* GetData(const UUID& uuidData, bool bForWrite, bool bAutoChangeBracket=true) const = 0;

	/** Commit changes made using GetData() with bForWrite=true.
		\param uuidData is the identifier of the data.
		\param pInfo is a pointer to optional info to be sent with any event that is raised.
		Events will be sent for any data objects that have had data committed.
		Every call to GetData() with bForWrite=true \e must be matched by a call to either Commit() or Discard().
		This method should not be called if the operation is cancelled. Instead you should call Discard().
		\see GetData() \see Discard() */
	virtual void Commit(const UUID& uuidData, IRhinoUiEventInfo* pInfo=nullptr) = 0;

	/** Discard changes made using GetData() with bForWrite=true.
		\param uuidData is the identifier of the data.
		Every call to GetData() with bForWrite=true \e must be matched by a call to either Commit() or Discard().
		This method should only be called if the operation is cancelled. Otherwise you should call Commit().
		\see GetData() \see Commit() */
	virtual void Discard(const UUID& uuidData) = 0;
};

class RHRDK_SDK IRhinoUiController : public IRhinoUiDataSourceHost
{
public:
	/** Call this method when UI construction is complete and the values should be passed
		for the first time from the model to the view. */
	virtual void Activate(void) = 0;

	/** Register an event watcher to be notified when the model changes. */
	virtual void RegisterEventWatcher(class IRhinoUiControllerEventWatcher& ew) = 0;

	/** Unregister an event watcher which has been added by RegisterEventWatcher().
		This must be done when the event watcher is deleted. */
	virtual void UnregisterEventWatcher(class IRhinoUiControllerEventWatcher& ew) = 0;

#pragma region RH_C_SHARED_ENUM [IRhinoUiController::EventPriority] [Rhino.UI.Controls.RdkViewModel.EventPriority] [nested]
	/// <summary>Event priority</summary>
	enum class EventPriority : unsigned int
	{
		/// <summary>Low priority</summary>
		Low,
		/// <summary>Normal priority</summary>
		Normal,
		/// <summary>High priority</summary>
		High,
		/// <summary>Real-time priority</summary>
		RealTime,
	};
#pragma endregion

	/** Set the event priority. You should only change the event priority around an
		event send and set it back to the old value afterwards.
		\return the old event priority. */
	virtual EventPriority SetEventPriority(EventPriority ep) = 0;

	/** \return The unique id of this controller. */
	virtual UUID Id(void) const = 0;

	/** Retrieve an array of data source ids required by this controller. */
	virtual void RequiredDataSources(OUT ON_SimpleArray<ON_UUID>& aId) const = 0;

	virtual bool IsActivated(void) const = 0;

	static void CustomDeleter(IRhinoUiController*);

	static std::shared_ptr<IRhinoUiController> make_shared(IRhinoUiController*);

protected:
	virtual ~IRhinoUiController() { }
};

/** \class IRhinoUiControllerEventWatcher

	Any object that has access to a IRhinoUiController can register itself
	to receive events from that controller by implementing this
	interface and calling IRhinoUiController::RegisterEventWatcher()

*/
class RHRDK_SDK IRhinoUiControllerEventWatcher
{
public: // Events.

	/** Implement this method to handle an event when the data of a certain type changes.
		Your handler will typically transfer data of that type to elements of your user interface.
		\param con is the controller sending the event.
		\param uuidData is the identifier of the data.
		\param ep is the event priority.
		\param pInfo is an optional pointer to extra event-specific information. This is often null.
		\see IRhinoUiDataSource::RegisterEventWatcher(). */
	virtual void OnEvent(IRhinoUiController& con, const UUID& uuidData, IRhinoUiController::EventPriority ep, const IRhinoUiEventInfo* pInfo) = 0;

	/** Implement this method to handle an event when the controller is first activated. */
	virtual void OnControllerActivatedEvent(IRhinoUiController& con) = 0;

	/** Emergency virtual function for future expansion. */
	virtual void* EVF(const wchar_t* wszFunc, void* pvData) = 0;

protected:
	virtual ~IRhinoUiControllerEventWatcher() { }
};

/** \class IRhinoUiDataSource

	Data source for user interfaces. A UI can have any number of data sources.

*/
class RHRDK_SDK IRhinoUiDataSource
{
public:
	/** You must implement this method as \code delete this; \endcode */
	virtual void DeleteThis(void) = 0;

	/** Get data specified by a unique id.
		\param uuidData is the identifier of the data. UUIDs defined by Rhino are specified above.
		\param bForWrite specifies if you intend to write to the data. \see Commit() \see Discard.
		\param bAutoChangeBracket is \e if you want BeginChange() and EndChange() to be called
		 automatically when the data is contents.
		\return a pointer which can be cast to the type for the identifier as documented above.
		 Note that this method will return null if the requested data type cannot be provided. */
	virtual void* GetData(const UUID& uuidData, bool bForWrite, bool bAutoChangeBracket=true) const = 0;

	/** Set the data source as changed. This must be called in between GetData() with bForWrite == true
		and Commit() in order for the commit to succeed and an event to be sent. If it is called when
		the data source is not in write mode, the call will fail.
		\return \e true if successful, else \e false. */
	virtual bool SetChanged(void) = 0;

	/** Commit changes made using GetData() with bForWrite=true.
		\param uuidData is the identifier of the data.
		\param pInfo is a pointer to optional info to be sent with any event that is raised.
		Events will be sent for any data objects that have had data committed.
		Every call to GetData() with bForWrite=true \e must be matched by a call to either Commit() or Discard().
		This method should not be called if the operation is cancelled. Instead you should call Discard().
		\see GetData() \see Discard() */
	virtual void Commit(const UUID& uuidData, IRhinoUiEventInfo* pInfo=nullptr) = 0;

	/** Discard changes made using GetData() with bForWrite=true.
		\param uuidData is the identifier of the data.
		Every call to GetData() with bForWrite=true \e must be matched by a call to either Commit() or Discard().
		This method should only be called if the operation is cancelled. Otherwise you should call Commit().
		\see GetData() \see Commit() */
	virtual void Discard(const UUID& uuidData) = 0;

	/** Add a data source host which would like to be notified of events
		that affect its data. When such an event arrives, the data source
		checks if the host is interested in the event and if so, it calls
		the host's OnEvent() method. */
	virtual void RegisterEventWatcher(IRhinoUiDataSourceEventWatcher& ew) = 0;

	/** Remove a data source host which has been added by RegisterEventWatcher().
		This must be done when such a host is deleted. */
	virtual void UnregisterEventWatcher(IRhinoUiDataSourceEventWatcher& ew) = 0;

	/** Implement this method to reset all data to defaults, if possible.
		\return \e true if successful, else \e false. */
	virtual bool ResetToDefaults(void) = 0;

	/** Called when the data source is added to a data source host. */
	virtual void AddHost(IRhinoUiDataSourceHost& h) = 0;

	/** Called by a data source host when it is being deleted. */
	virtual void RemoveHost(IRhinoUiDataSourceHost& h) = 0;

	/** Emergency virtual function for future expansion. */
	virtual void* EVF(const wchar_t* wszFunc, void* pvData) = 0;

protected:
	virtual ~IRhinoUiDataSource() { }
};

class RHRDK_UI_SDK CRhRdkController : public IRhinoUiController
{
public:
	CRhRdkController();

public: // Implement IRhinoUiDataSourceHost.
	virtual void* GetData(const UUID& uuidData, bool bForWrite, bool bAutoChangeBracket) const override;
	virtual void Commit(const UUID& uuidData, IRhinoUiEventInfo* pInfo=nullptr) override;
	virtual void Discard(const UUID& uuidData) override;
	virtual void AddDataSource(IRhinoUiDataSource& ds) override;
	virtual void RemoveDataSource(IRhinoUiDataSource& ds) override;

public: // Implement IRhinoUiController.
	virtual void Activate(void) override;
	virtual void GetDataSources(ON_SimpleArray<IRhinoUiDataSource*>& aOut) const override;
	virtual void CopyDataSourcesFrom(IRhinoUiDataSourceHost& host) override;
	virtual void RegisterEventWatcher(IRhinoUiControllerEventWatcher& ew) override;
	virtual void UnregisterEventWatcher(IRhinoUiControllerEventWatcher& ew) override;
	virtual EventPriority SetEventPriority(EventPriority ep) override;
	virtual UUID Id(void) const override;
	virtual bool IsActivated(void) const override;

public: // Implement IRhinoUiDataSourceEventWatcher.
	virtual void Delete(void) override;
	virtual void OnEvent(const UUID& uuidData, const IRhinoUiEventInfo* pInfo) override;
	virtual void* EVF(const wchar_t* wszFunc, void* pvData) override { return nullptr; }

private:
	class CImpl;
	CImpl* m_pImpl;

protected:
	virtual ~CRhRdkController();
};

class RHRDK_UI_SDK CRhRdkGenericController : public CRhRdkController
{
public:
	virtual void RequiredDataSources(OUT ON_SimpleArray<ON_UUID>& aId) const override;
	virtual void Delete(void) override;
};

/** \class IRhRdkUndoRecord

	This interface is returned by IRhRdkUndo::NewUndoRecord().

	\see IRhRdkUndo
	\see uuidData_RdkUndo

*/
class RHRDK_SDK IRhRdkUndoRecord
{
public:
	/** This method is implemented as \code delete this; \endcode */
	virtual void DeleteThis(void) = 0;

	/** Set the localized description of the undo record. */
	virtual void SetDescription(const wchar_t* wsz) = 0;

	/** Emergency virtual function for future expansion. */
	virtual void* EVF(const wchar_t* wszFunc, void* pvData) = 0;

protected:
	virtual ~IRhRdkUndoRecord() { }
};

/** \class IRhRdkToneMapping

*/
class RHRDK_UI_SDK IRhRdkToneMapping
{
public:
	/*RDK_DEPRECATED*/ enum class Methods : unsigned int
	{
		None,
		BlackWhitePoint,
		Logarithmic,
	};

	/** Get whether or not tone mapping will be applied during rendering. */
	/*RDK_DEPRECATED*/ virtual bool ApplyWhileRendering(void) const = 0;

	/** Set whether or not tone mapping will be applied during rendering. */
	/*RDK_DEPRECATED*/ virtual void SetApplyWhileRendering(bool b) = 0;

	/** Get tone mapping method. */
	/*RDK_DEPRECATED*/ virtual IRhRdkToneMapping::Methods Method(void) const = 0;

	/** Set tone mapping method. */
	/*RDK_DEPRECATED*/ virtual void SetMethod(IRhRdkToneMapping::Methods) = 0;

	/** Get tone mapping params. */
	virtual void GetParams(OUT IRhRdk_XMLSection& section) const = 0;

	/** Set tone mapping params. */
	virtual void SetParams(const IRhRdk_XMLSection& section) = 0;

	/** Emergency virtual function for future expansion. */
	virtual void* EVF(const wchar_t* wszFunc, void* pvData) = 0;

protected:
	virtual ~IRhRdkToneMapping() { }
};

/** \class IRhRdkImageAdjust

*/
class RHRDK_UI_SDK IRhRdkImageAdjust
{
public:
	virtual IRhRdkDithering::Methods Dither(void) const = 0;
	virtual void SetDither(IRhRdkDithering::Methods dm) = 0;

	virtual float Gamma(void) const = 0;
	virtual void SetGamma(float f) = 0;

	/*RDK_DEPRECATED*/ virtual IRhRdkToneMapping& ToneMapping(void) const = 0;
	/*RDK_DEPRECATED*/ virtual bool IsEqual(const IRhRdkImageAdjust& a) const = 0;

	/** Emergency virtual function for future expansion. */
	virtual void* EVF(const wchar_t* wszFunc, void* pvData) = 0;

protected:
	virtual ~IRhRdkImageAdjust() { }
};

/** \class IRhRdkImageFile

	This interface is returned by IRhinoUiDataSource::GetData(uuidData_RdkImageFile).
	It allows a UI to get information about an image file. An image file is a file
	that contains image data, such as a BMP, JPEG or HDR image.

	\see uuidData_RdkImageFile

*/
class RHRDK_UI_SDK IRhRdkImageFile
{
public:
	class RHRDK_UI_SDK IInfo
	{
	public:
		/** \return The original file name of the file. */
		virtual ON_wString Filename(void) const = 0;

		/** \return The full path to the file after any 'file-finding'. */
		virtual ON_wString FoundFilename(void) const = 0;

		/** \return the width of the image. */
		virtual int ImageWidth(void) const = 0;

		/** \return the height of the image. */
		virtual int ImageHeight(void) const = 0;

		/** \return the depth of the image. Not valid for HDR images */
		virtual int ImageDepth(void) const = 0;

		/** \return the size of the image in bytes. Not valid for HDR images */
		virtual size_t ImageSize(void) const = 0;

		/** \return the size of the file in bytes. */
		virtual size_t FileSize(void) const = 0;

		/** \return An array of localized strings giving the image and
			 file information formatted for display to the user. These
			 strings can be displayed in a single control by concatenating
			 them together with the necessary delimiters. */
		virtual void InfoStrings(OUT ON_ClassArray<ON_wString>& a) const = 0;

		/** OBSOLETE: Get a dib containing the pixels of a 'preview' version of the image.
			This dib always has 32 bits per pixel.
			\param size is the desired preview image size.
			\param dib accepts the dib.
			\param bTrans is \e true if a transparent color should be processed.
			\param colTrans is the transparent color. Only used if bTrans is \e true.
			\param dTrans is the transparent color sensitivity (0.0 to 1.0). Only used if bTrans is \e true.
			\return \e true if successful, else \e false. */
		ON_DEPRECATED_MSG("Use GetPreviewImage2")
		virtual bool GetPreviewImage(const ON_2iSize& size, bool bTrans, const CRhRdkColor& colTrans, double dTrans, OUT CRhinoDib& dib) const = 0;

		/** Emergency virtual function for future expansion. */
		virtual void* EVF(const wchar_t* wszFunc, void* pvData) = 0;

	protected:
		virtual ~IInfo() { }
	};

	class RHRDK_UI_SDK IInfo2 : public IInfo
	{
	public:
		class RHRDK_UI_SDK PreviewImageParameters
		{
		public:
			PreviewImageParameters(const ON_2iSize& size,
				bool bUseTransparentColor,
				const CRhRdkColor& colTransparentColor,
				double dTransparentColorSensitivity,
				bool bUseAlphaChannel);

			virtual ~PreviewImageParameters();

			ON_2iSize Size(void) const;
			bool UseTransparentColor(void) const;
			CRhRdkColor TransparentColor(void) const;
			double TransparentColorSensitivity(void) const;
			bool UseAlphaChannel(void) const;

			ON__UINT32 CRC(void) const;

		private:
			class CImpl;
			CImpl* m_pImpl;
		};

		/** Get a dib containing the pixels of a 'preview' version of the image.
		This dib always has 32 bits per pixel.
		\param params is the input data used to specify the image.
		\param dib accepts the dib.
		\return \e true if successful, else \e false. */
		virtual bool GetPreviewImage2(const PreviewImageParameters& params, OUT CRhinoDib& dib) const = 0;

		virtual const CRhinoDoc* Document(void) const = 0;

	protected:
		virtual ~IInfo2() { }
	};

	class RHRDK_UI_SDK IEventInfo : public IRhinoUiEventInfo
	{
	public:
		virtual const IInfo& ImageFileInfo(void) const = 0;
	};

	/** Get a pointer to an interface for getting information about a specific image file.
		\param rhino_doc_sn is a document serial number. This is used by the file-finding process.
		\param wszFilename is the name of the file of interest. This may be just a file name
		 or it can be a fully-qualified path. The function will do all necessary file-finding.
		\return A pointer to an interface or null if the file could not be opened. */
	virtual const IInfo* Info(unsigned int rhino_doc_sn, const wchar_t* wszFilename) const = 0;

	/** Emergency virtual function for future expansion. */
	virtual void* EVF(const wchar_t* wszFunc, void* pvData) = 0;

protected:
	virtual ~IRhRdkImageFile() { }
};

/** \class IRhRdkContentFilters

	This interface is returned by IRhinoUiDataSource::GetData(uuidData_RdkContentFilters)

	\see uuidData_RdkContentFilters

*/
class RHRDK_UI_SDK IRhRdkContentFilters
{
public:
	virtual ON_wString NameFilter(void) const = 0;
	virtual bool NameFilterInvert(void) const = 0;
	virtual bool ShowUnassigned(void) const = 0;
	virtual bool ShowV4(void) const = 0;
	virtual bool ShowHidden(void) const = 0;
	virtual bool ShowReference(void) const = 0;

	virtual bool IsContentFilteredOut(const CRhRdkContent& c) const = 0;

	/** Emergency virtual function for future expansion. */
	virtual void* EVF(const wchar_t* wszFunc, void* pvData) = 0;

protected:
	virtual ~IRhRdkContentFilters() { }
};

/** \class IRhRdkContentLookup

	This interface is returned by IRhinoUiDataSource::GetData(uuidData_RdkContentLookup)

	\see uuidData_RdkContentLookup

*/
class RHRDK_UI_SDK IRhRdkContentLookup
{
public:
	/**	Looks up a content in the relevant location (typically a document).
		**** IMPORTANT **** This will also find non-document contents that are globally registered.
		If this global lookup is not desired, please call LookUpContentInDocument() instead.
		\param uuidInstance is the instance id of the content to look up.
		\param uuidLocation is an optional location identifier **** This is currently not used.
		\return A pointer to the content if found, else null. */
	virtual const CRhRdkContent* LookUpContent(const UUID& uuidInstance, const UUID& uuidLocation=ON_nil_uuid) const = 0;

	/** Looks up a content in the relevant location (typically a document). Note that this does not find
		global contents. To be found, the content must be attached to the document associated with this data source.
		\param uuidInstance is the instance id of the content to look up.
		\param uuidLocation is an optional location identifier **** This is currently not used.
		\return A pointer to the content if found, else null. */
	/*virtual*/ const CRhRdkContent* LookUpContentInDocument(const UUID& uuidInstance, const UUID& uuidLocation=ON_nil_uuid) const; /*= 0;*/ // [SDK_UNFREEZE]

	/** Creates a new data source for looking up document-resident contents.
		\param pRdkDoc specifies the document within which the contents reside (or null to use the modeless document).
		The caller shall delete the returned object when it is no longer needed. */
	static IRhinoUiDataSource* NewDataSource(const CRhRdkDocument* pRdkDoc=nullptr);

	/*virtual void DeleteThis(void) = 0; [SDK_UNFREEZE] Use EVF(L"DeleteThis") for now. */

	/** Emergency virtual function for future expansion. */
	virtual void* EVF(const wchar_t* wszFunc, void* pvData) = 0;

protected:
	virtual ~IRhRdkContentLookup() { }
};

/** \class IRhRdkContentCollection

	This interface is returned in several different contexts:

	* Public:

	  - It is returned by GetData(uuidData_RdkContentDatabase) where it will get
	    a collection that represents all the content in a 'database' -- usually a document.

	  - It is returned by GetData(uuidData_RdkContentDisplayCollection) where it will get
	    a collection that represents only the content in a database that is not filtered out
	    by a search phrase.

	  - It is returned by GetData(uuidData_RdkContentSelection) where it will get
	    a collection that represents the current selection in a Content UI.

	    \see uuidData_RdkContentDatabase
	    \see uuidData_RdkContentDisplayCollection
	    \see uuidData_RdkContentSelection

	* Internal:

	  - It is returned by GetData(uuidData_RdkContentSelectionOverride) where it will get
	    a collection that represents the current right-clicked selection in a drop-down list (NCC).

	  - It is returned by GetData(uuidData_RdkContentSelectionForPreview) where it will get a collection
	    that represents the current selection made by the user. This is usually the same as
	    uuidData_RdkContentSelection but when the user selects a Texture Proxy, uuidData_RdkContentSelection
	    gives the proxy's members whereas uuidData_RdkContentSelectionForPreview gives the proxy itself.

	    \see uuidData_RdkContentSelectionOverride
	    \see uuidData_RdkContentSelectionForPreview

*/
class RHRDK_UI_SDK IRhRdkContentCollection
{
public:
	/** Clear the collection. */
	virtual void Clear(void) = 0;

	/** \return The number of items in the collection. */
	virtual int Count(void) const = 0;

	/** Get the content kinds that are allowed in the collection. */
	virtual CRhRdkContentKindList AllowedKinds(void) const = 0;

	/** Get an array of const contents from the collection.
		\param aContent accepts the array of contents.
		\return \e true if successful, else \e false. */
	virtual bool Get(OUT CRhRdkContentArray& aContent) const = 0;

	/** Set an array of const contents as the collection.
		\param aContent is the array of contents to set.
		\return \e true if successful, else \e false. */
	virtual bool Set(const CRhRdkContentArray& aContent) = 0;

	/** Set an array of non-const contents as the collection.
		\param aContent is the array of contents to set.
		\return \e true if successful, else \e false. */
	virtual bool Set(const CRhRdkContentArrayNC& aContent) = 0;

	/** Add an array of const contents to the collection.
		\param aContent is the array of contents to add.
		\return \e true if successful, else \e false. */
	virtual bool Add(const CRhRdkContentArray& aContent) = 0;

	/** Add an array of non-const contents to the collection.
		\param aContent is the array of contents to add.
		\return \e true if successful, else \e false. */
	virtual bool Add(const CRhRdkContentArrayNC& aContent) = 0;

	/** Remove an array of contents from the collection.
		\param aContentIn is the array of contents to remove.
		The following only applies when the collection is a 'database' collection:
		\param aContentOut accepts the contents that were successfully removed.
		\note This method removes the contents from the collection if they are present in it,
		 but it does not delete them. Instead, it returns them as non-const; the caller takes
		 ownership of them.
		The following only applies if the collection is a 'selection' collection:
		\param aContentOut is ignored. Ownership of the contents in the selection does not change.
		\return \e true if successful, else \e false. */
	virtual bool Remove(const CRhRdkContentArray& aContentIn, OUT CRhRdkContentArrayNC& aContentOut) = 0;

	/** \see SetForcedVaries() */
	virtual bool GetForcedVaries(void) const = 0;

	/** Set the collection to 'varies'.
		Only valid if the collection is a 'selection' collection.
		Useful for clients that only support single content selections. */
	virtual void SetForcedVaries(bool b=true) = 0;

	class RHRDK_UI_SDK IIterator
	{
	public:
		virtual void DeleteThis(void) = 0;

		/** \return the first content in the collection or null if none. */
		virtual const CRhRdkContent* First(void) = 0;

		/** \return the next content in the collection or null if no more. */
		virtual const CRhRdkContent* Next(void) = 0;

		/** Emergency virtual function for future expansion. */
		virtual void* EVF(const wchar_t* wszFunc, void* pvData) = 0;

	protected:
		virtual ~IIterator() { }
	};

	/** Get a new content iterator. The caller shall delete the iterator after use.
		\note It is the caller's responsibility to filter out unwanted contents from the returned collection.
		 To filter out the default instance, you can call CRhRdkContent::IsDefaultInstance() and ignore
		 the content if the result is \e true.
		 To filter out proxies, you can call CRhRdkContent::ProxyType() and ignore the content if
		 the type is not CRhRdkContent::ProxyTypes::None. */
	virtual IIterator* NewIterator(void) const = 0;

public: // Support for searching and filtering. Only used by GetData(uuidData_RdkContentDisplayCollection).

	/** Sets a search pattern for filtering contents. This is not actually used by the iterator,
		but is stored for use by any UI that wants to filter contents based on a search string
		by using the function RhRdkCheckSearchPattern().
		\param wszPattern is the search pattern. See RhRdkCheckSearchPattern() for details.
		\see RhRdkCheckSearchPattern() */
	virtual void SetSearchPattern(const wchar_t* wszPattern) = 0;

	/** Gets the search pattern.
		\see SetSearchPattern()
		\see RhRdkCheckSearchPattern() */
	virtual ON_wString GetSearchPattern(void) const = 0;

/*	[SDK_UNFREEZE] Add these functions and remove temporary EVF implementation.
	virtual void SetFilterContentByUsage(RhRdkFilterContentByUsage fc) = 0;
	virtual RhRdkFilterContentByUsage GetFilterContentByUsage(void) const = 0;
	virtual bool ContentNeedsPreviewThumbnail(const CRhRdkContent& c, CRhRdkContent::Kinds topLevelKind) = 0;
	virtual bool FirstTag(OUT ON_wString& sTag) = 0;
	virtual bool NextTag(OUT ON_wString& sTag) = 0; */

	/** Emergency virtual function for future expansion. */
	virtual void* EVF(const wchar_t* wszFunc, void* pvData) = 0;

protected:
	virtual ~IRhRdkContentCollection() { }
};

/** \class IRhRdkEdit

	This interface is returned by IRhinoUiDataSource::GetData(uuidData_RdkEdit).
	It is used by the 'edit' task.

	\see uuidData_RdkEdit

*/
class RHRDK_UI_SDK IRhRdkEdit
{
public:
	/** \return the string that should appear in menus for this edit operation. */
	virtual const wchar_t* MenuString(void) const = 0;

	/** Execute the edit operation to edit an array of contents.
		\param aContent is the array of contents to edit.
		\return \e true if successful, else \e false. */
	virtual bool Execute(const CRhRdkContentArray& aContent) const = 0;

	/** Emergency virtual function for future expansion. */
	virtual void* EVF(const wchar_t* wszFunc, void* pvData) = 0;

protected:
	virtual ~IRhRdkEdit() { }
};

/** \class IRhRdkFindFile

	This interface is returned by IRhinoUiDataSource::GetData(uuidData_RdkFindFile)

	\see uuidData_RdkFindFile

*/
class RHRDK_UI_SDK IRhRdkFindFile
{
public:
	/** Find a file. */
	virtual bool FindFile(const wchar_t* wszFullPath, bool bAutoUnpackBitmaps, ON_wString& sFoundFileOut) const = 0;

	/** Emergency virtual function for future expansion. */
	virtual void* EVF(const wchar_t* wszFunc, void* pvData) = 0;

protected:
	virtual ~IRhRdkFindFile() { }
};

/** \class IRhRdkRhinoSettings

	This interface is returned by IRhinoUiDataSource::GetData(uuidData_RdkRhinoSettings)

	\see uuidData_RdkRhinoSettings

*/
class RHRDK_UI_SDK IRhRdkRhinoSettings
{
public:
	/** Call this method to get a non-const object upon which you can call non-const methods.
		Calls to this method are counted; you must call EndChange() once for every call to
		BeginChange(). Please do not use const_cast or any other means of circumventing this requirement. */
	/*virtual*/ IRhRdkRhinoSettings& BeginChange(RhRdkChangeContext cc) const; // [SDK_UNFREEZE] = 0;
	/*virtual*/ bool EndChange(void); // [SDK_UNFREEZE] = 0;

	/** Get the underlying ON_3dmRenderSettings. */
	virtual const ON_3dmRenderSettings& Get3dmRenderSettings(void) const = 0;

	/** Set the underlying ON_3dmRenderSettings. */
	virtual void Set3dmRenderSettings(const ON_3dmRenderSettings& rs) = 0;

	/** Get the underlying model ON_3dmUnitsAndTolerances. */
	virtual const ON_3dmUnitsAndTolerances& GetModelUnitsAndTolerances(void) const = 0;

	/** Set the underlying model ON_3dmUnitsAndTolerances. */
	virtual void SetModelUnitsAndTolerances(const ON_3dmUnitsAndTolerances& ut, bool bScaleModelObjects=false) = 0;

	/** Get the underlying page ON_3dmUnitsAndTolerances. */
	virtual const ON_3dmUnitsAndTolerances& GetPageUnitsAndTolerances(void) const = 0;

	/** Set the underlying page ON_3dmUnitsAndTolerances. */
	virtual void SetPageUnitsAndTolerances(const ON_3dmUnitsAndTolerances& ut, bool bScalePaperObjects=false) = 0;

	enum : unsigned int // Bit flags for GetLights().
	{
		IncludeDeletedLights        = 0x01, // Returns lights that have been deleted.
		IncludeLightsOnHiddenLayers = 0x02, // Returns lights that are on layers that are hidden.
	};

	class RHRDK_UI_SDK CLightInfo final
	{
	public:
		CLightInfo();
		CLightInfo(const CLightInfo&);
		CLightInfo(const ON_Light& l, bool bDeleted, int iLayerIndex);
		~CLightInfo();

		const CLightInfo& operator = (const CLightInfo&);

		      ON_Light& Light(void);
		const ON_Light& Light(void) const;

		bool IsDeleted(void) const;
		void SetIsDeleted(bool);

		int LayerIndex(void) const;
		void SetLayerIndex(int) const;

	private:
		class CImpl;
		CImpl* m_pImpl;
	};

	/** Get the underlying lights. */
	virtual void GetLights(OUT ON_ClassArray<CLightInfo>&, unsigned int flags) const = 0;

	/** Set the underlying lights. */
	virtual void SetLights(const ON_ClassArray<CLightInfo>&) = 0;

	/** Get the underlying ON_EarthAnchorPoint. */
	virtual const ON_EarthAnchorPoint& GetEarthAnchorPoint(void) const = 0;

	/** Set the underlying ON_EarthAnchorPoint. */
	virtual void SetEarthAnchorPoint(const ON_EarthAnchorPoint& eap) = 0;

	/** Helper to just set the underlying ON_EarthAnchorPoint north direction. */
	virtual void SetEarthAnchorPointNorth(double dNorth) = 0;

	/** Get the custom render sizes specified by Rhino. */
	virtual void GetCustomRenderSizes(OUT ON_SimpleArray<ON_2iSize>& aSize) const = 0;

	/** Get the active Rhino view.
		Deprecated - use RenderingView instead. */
	virtual CRhinoView* ActiveView(void) const = 0;

	/*virtual*/ const ON_3dmView* RenderingView(void) const; // = 0; [SDK_UNFREEZE]
	/*virtual*/ UUID CurrentRenderer(void) const;            // = 0; [SDK_UNFREEZE]
	/*virtual*/ void SetCurrentRenderer(const UUID&) const;  // = 0; [SDK_UNFREEZE]
	/*virtual*/ bool CustomImageSizeIsPreset(void) const;    // = 0; [SDK_UNFREEZE]
	/*virtual*/ void SetCustomImageSizeIsPreset(bool);       // = 0; [SDK_UNFREEZE]

	// View display mode.
	virtual bool GroundPlaneOnInViewDisplayMode(const CRhinoView& view) const = 0;
	virtual void SetGroundPlaneOnInViewDisplayMode(const CRhinoView& view, bool bOn) = 0;
	virtual CDisplayPipelineAttributes* ViewDisplayAttributes(const CRhinoView& view) const = 0;
	virtual bool ViewSupportsShading(const CRhinoView& view) const = 0;

	/** Copy this object from another one. */
	virtual void CopyFrom(const IRhRdkRhinoSettings& rs) = 0;

	/** Emergency virtual function for future expansion. Currently supports:
		"RenderingView" returns const ON_3dmView*. Supports ON_3dmRenderSettings::RenderingSources.
		"CurrentRenderer" returns UUID*.
		"SetCurrentRenderer" takes UUID*.
		"CustomImageSizeIsPreset" returns null=false, non-null=true.
		"SetCustomImageSizeIsPreset" takes null=false, non-null=true.
	*/
	virtual void* EVF(const wchar_t*, void*) = 0;

protected:
	virtual ~IRhRdkRhinoSettings() { }
};

/** \class IRhRdkPreviewSettings

	This interface is returned by IRhinoUiDataSource::GetData(uuidData_RdkPreviewSettings)

	\see uuidData_RdkPreviewSettings

*/
class RHRDK_UI_SDK IRhRdkPreviewSettings
{
public:
	enum class Modes : unsigned int
	{
		Unset,
		Grid, // Big thumbnails like Explorer icon mode.
		List, // Small thumbnails and info on right like Explorer report mode.
		Tree, // Tree mode.
	};

	virtual Modes Mode(void) const = 0;
	virtual void SetMode(Modes m) = 0;

	enum class Sizes : unsigned int
	{
		Unset,
		Tiny,
		Small,
		Medium,
		Large,
	};

	virtual Sizes Size(void) const = 0;
	virtual void SetSize(Sizes s) = 0;

	virtual bool ShowLabels(void) const = 0;
	virtual void SetShowLabels(bool b) = 0;

	virtual bool ShowUnits(void) const = 0;
	virtual void SetShowUnits(bool b) = 0;

	virtual bool AutoUpdate(void) const = 0;
	virtual void SetAutoUpdate(bool b) = 0;

	virtual bool IsPersistent(void) const = 0;
	virtual void SetIsPersistent(bool b) = 0;

	virtual int UpdateMetaDataIncFlag(void) = 0;

	/** \class IMetaData. This interface provides the meta data for a single preview.
		 It corresponds to CRhRdkPreviewAppearance with a few extra values. */
	class RHRDK_UI_SDK IMetaData
	{
	public:
		virtual ~IMetaData() { }

		/** \return The preview's rotation angle in X. */
		virtual double RotationX(void) const = 0;

		/** Set the preview's rotation angle in X. */
		virtual void SetRotationX(double) = 0;

		/** \return The preview's rotation angle in Y. */
		virtual double RotationY(void) const = 0;

		/** Set the preview's rotation angle in Y. */
		virtual void SetRotationY(double) = 0;

		/** \return The preview's size in units. */
		virtual double Size(void) const = 0;

		/** Set the preview's size in units. */
		virtual void SetSize(double) = 0;

		/** \return The preview's rotation type (SS_RT...). */
		virtual const wchar_t* RotationType(void) const = 0;

		/** Set the preview's rotation type (SS_RT...). */
		virtual void SetRotationType(const wchar_t* wszType) = 0;

		/** \return The preview geometry's name (SS_PG...). */
		virtual const wchar_t* Geometry(void) const = 0;

		/** Set the preview geometry's name (SS_PG...). */
		virtual void SetGeometry(const wchar_t* wszGeom) = 0;

		/** \return The preview background's name (SS_PB...). */
		virtual const wchar_t* Background(void) const = 0;

		/** Set the preview background's name (SS_PB...). */
		virtual void SetBackground(const wchar_t* wszBack) = 0;

		/** \return The preview lighting's name (SS_PL...). */
		virtual const wchar_t* Lighting(void) const = 0;

		/** Set the preview lightings's name (SS_PL...). */
		virtual void SetLighting(const wchar_t* wszLigh) = 0;

		/** \return The instance id of an environment used when the preview background is customizable. */
		virtual UUID CustomEnvironmentInstanceId(void) const = 0;

		/** Set the instance id of an environment used when the preview background is customizable. */
		virtual void SetCustomEnvironmentInstanceId(const UUID& uuidInstance) = 0;

		/** \return The instance id of the content that the meta data is for
			 if the meta data is linked to content.
			\see IsMetaDataLinkedToContent() */
		virtual UUID ContentInstanceId(void) const = 0;

		/** Set the instance id of the content that the meta data is for
			 if the meta data is linked to content.
			\see IsMetaDataLinkedToContent() */
		virtual void SetContentInstanceId(const UUID& uuidInstance) = 0;

		/** Emergency virtual function for future expansion. */
		virtual void* EVF(const wchar_t* wszFunc, void* pvData) = 0;
	};

	/** \return \e true if the meta data is linked to content. Clients should only access
		 the meta data content instance id if this returns \e true. Some meta data is
		 not linked to content, for example when the settings are used by the editor
		 preview thumbnail list. This single-item thumbnail 'list' uses the same meta
		 data for all contents. Its preview settings contains a single non-linked meta data.
		\see ContentInstanceId() \see SetContentInstanceId() */
	virtual bool IsMetaDataLinkedToContent(void) const = 0;

	/** Clear the meta data collection. */
	virtual void ClearMetaData(void) = 0;

	/** Add an item to the meta data collection. */
	virtual void AddMetaData(const IMetaData& m) = 0;

	/** Reset the built-in meta data iterator. */
	virtual void ResetMetaDataIterator(void) const = 0;

	/** Get the next meta data item using the built-in iterator. */
	virtual IMetaData* NextMetaData(void) const = 0;

	/** Get the meta data for a specific content. */
	virtual IMetaData* MetaDataForContent(const CRhRdkContent& c) const = 0;

	/** Get the common geometry of all previews associated with a certain content collection.
		If the function fails or the geometry varies, it returns an empty string. */
	virtual ON_wString GetGeometry(const IRhRdkContentCollection& cc) const = 0;

	/** Set the geometry of all previews associated with a certain content collection. */
	virtual void SetGeometry(const IRhRdkContentCollection& cc, const wchar_t* wszGeom) = 0;

	/*virtual*/ void AlphaSort(void) /*= 0*/; // [SDK_UNFREEZE] Use EVF(L"AlphaSort") for now.

	/** Emergency virtual function for future expansion. */
	virtual void* EVF(const wchar_t* wszFunc, void* pvData) = 0;

protected:
	virtual ~IRhRdkPreviewSettings() { }
};

/** \class IRhRdkContentEditorSettings

	This interface is returned by IRhinoUiDataSource::GetData(uuidData_RdkContentEditorSettings)

	It encapsulates the persistent settings used by content editors. These are the settings
	that determine the layout of content editor panes, splitters, etc.

	\see uuidData_RdkContentEditorSettings

*/
class RHRDK_UI_SDK IRhRdkContentEditorSettings
{
public:
	/** \return The top-level kind of content in the editor. */
	virtual CRhRdkContent::Kinds TopLevelKind(void) const = 0;

	/** \return The id of the editor that these settings are for. */
	virtual UUID EditorId(void) const = 0;

	/** \return \e true if the preview pane is visible, else \e false. */
	virtual bool ShowPreviewPane(void) const = 0;

	/** Set the visibility of the preview pane. */
	virtual void SetShowPreviewPane(bool bShow) = 0;

	/** \return \e true if the Splitter A's chevron is engaged, else \e false. */
	virtual bool ChevronEngaged(void) const = 0;

	/** Set Splitter A's chevron engaged state. */
	virtual void SetChevronEngaged(bool b) = 0;

	enum class Splitters : unsigned int
	{
		/* Horizontal layout
		___________        ___________
		|         |        |         |
		|  thumb  |        |  tree   |
		|         |        |         |
		|---HA----|        |---HB----|
		|         |        |         |
		| preview |        | preview |
		|         |        |         |
		|---HC----|        |---HC----|
		|         |        |         |
		|   ui    |        |   ui    |
		|         |        |         |
		-----------        -----------
		*/
		HA, HB, HC,

		/* Vertical layout
		_______________    _______________
		|   |         |    |   |         |
		|   | preview |    |   | preview |
		| t |         |    | t |         |
		| h |---VC----|    | r |---VC----|
		| u |         |    | e |         |
		| m VA        |    | e VB        |
		| b |   ui    |    |   |   ui    |
		|   |         |    |   |         |
		---------------    ---------------
		*/
		VA, VB, VC,
	};

	/** Get the position of a particular splitter. */
	virtual int SplitterPos(Splitters s) const = 0;

	/** Set the position of a particular splitter. */
	virtual void SetSplitterPos(Splitters s, int pos) = 0;

	enum class Layouts : unsigned int
	{
		Horizontal,
		Vertical,
	};

	/** Get the editor layout. */
	virtual Layouts Layout(void) const = 0;

	/** Set the editor layout. */
	virtual void SetLayout(Layouts l) = 0;

	/** Emergency virtual function for future expansion. */
	virtual void* EVF(const wchar_t* wszFunc, void* pvData) = 0;

protected:
	virtual ~IRhRdkContentEditorSettings() { }
};

/** \class IRhRdkPreviewRendered

	This interface is returned by IRhinoUiDataSource::GetData(uuidData_RdkPreviewRendered)

	\see uuidData_RdkPreviewRendered

*/
class RHRDK_UI_SDK IRhRdkPreviewRendered
{
public:
	/** Get the rendered imagery for the preview. */
	virtual const CRhinoDib& Dib(void) const = 0;

	/** Get the quality associated with the preview. */
	virtual RhRdkPreviewQuality Quality(void) const = 0;

	/** Get the job signature associated with the preview. */
	virtual const class CRhRdkPreviewJobSignature& JobSignature(void) const = 0;

	/** Emergency virtual function for future expansion. */
	virtual void* EVF(const wchar_t* wszFunc, void* pvData) = 0;

protected:
	virtual ~IRhRdkPreviewRendered() { }
};

/** \class IRhRdkSelectionNavigator

	Interface for navigating a selection back and forth.

	\see uuidData_RdkSelectionNavigator

*/
class RHRDK_UI_SDK IRhRdkSelectionNavigator
{
public:
	/** Clear the navigator. */
	virtual void Clear(void) = 0;

	/** Add a selection of contents at the current position.
		Clears the navigator ahead of the current position. */
	virtual void Add(const CRhRdkContentArray& aContent) = 0;

	/** \return \e true if it is possible to navigate backwards, else \e false. */
	virtual bool CanGoBackwards(void) const = 0;

	/** \return \e true if it is possible to navigate forwards, else \e false. */
	virtual bool CanGoForwards(void) const = 0;

	/** Navigate backwards if possible.
		\param aSelection is the new selection after navigating backwards.
		 The caller should set the selection using GetData(uuidData_RdkContentSelection...
		\return \e true on success, else \e false. */
	virtual bool GoBackwards(OUT CRhRdkContentArray& aSelection) = 0;

	/** Navigate forwards if possible.
		\param aSelection is the new selection after navigating forwards.
		 The caller should set the selection using GetData(uuidData_RdkContentSelection...
		\return \e true on success, else \e false. */
	virtual bool GoForwards(OUT CRhRdkContentArray& aSelection) = 0;

	/** Emergency virtual function for future expansion. */
	virtual void* EVF(const wchar_t* wszFunc, void* pvData) = 0;

protected:
	virtual ~IRhRdkSelectionNavigator() { }
};

/** \class IRhRdkContentUpdatePreviewEventInfo

	Event info used by event for uuidData_RdkContentUpdatePreview.

	\see uuidData_RdkContentUpdatePreview

*/
class RHRDK_UI_SDK IRhRdkContentUpdatePreviewEventInfo : public IRhinoUiEventInfo
{
public:
	/** Get the content whose preview needs updating. */
	virtual const CRhRdkContent& Content(void) const = 0;

protected:
	virtual ~IRhRdkContentUpdatePreviewEventInfo() { }
};

/** \class IRhRdkContentUpdatePreviewMarkersEventInfo

	Event info used by event for uuidData_RdkContentUpdatePreviewMarkers.

	\see uuidData_RdkContentUpdatePreviewMarkers

*/
class RHRDK_UI_SDK IRhRdkContentUpdatePreviewMarkersEventInfo : public IRhinoUiEventInfo
{
public:
	/** Get the content kind whose preview markers needs updating. */
	virtual CRhRdkContent::Kinds Kind(void) const = 0;

protected:
	virtual ~IRhRdkContentUpdatePreviewMarkersEventInfo() { }
};

/** \class IRhRdkContentDatabaseEventInfo

	Event info used by event for uuidData_RdkContentDatabase.

*/
class RHRDK_UI_SDK IRhRdkContentDatabaseEventInfo : public IRhinoUiEventInfo
{
public:
	/** Get extra information. The meaning of this value depends on the type. \see Types. */
	virtual ON__UINT64 Extra(void) const = 0;

	enum class Types : unsigned int
	{
		Attached,   // A content was attached (usually to a document). 'Extra' must be cast to CRhRdkEventWatcher::AttachReason.
		Detaching,  // A content is about to be detached (usually from a document). 'Extra' must be cast to CRhRdkEventWatcher::DetachReason.
		Detached,   // A content was detached (usually from a document). 'Extra' must be cast to CRhRdkEventWatcher::DetachReason.
		Replacing,  // A content is about to be replaced (usually in a document). 'Extra' is not used.
		Replaced,   // A content was replaced (usually in a document). 'Extra' is not used.
		Blossom,    // A V4 material was changed into a real RDK material (usually in a document). 'Extra' is not used.
	};

	/** Get the content that was affected. */
	virtual const CRhRdkContent& Content(void) const = 0;

	/** Get the type of database change. */
	virtual Types Type(void) const = 0;

protected:
	virtual ~IRhRdkContentDatabaseEventInfo() { }
};

/** \class IRhRdkContentParamEventInfo

	Event info used by event for uuidData_RdkContentParam.

*/
class RHRDK_UI_SDK IRhRdkContentParamEventInfo : public IRhinoUiEventInfo
{
public:
	enum class Types : unsigned int
	{
		Name,    // Content name changed.
		Notes,   // Content notes changed.
		Tags,    // Content tags changed.
		GroupId, // Content group id changed.
		Param,   // Some other content state / field changed.
	};

	/** Get the content that was affected. */
	virtual const CRhRdkContent& Content(void) const = 0;

	/** Get the type of change. */
	virtual Types Type(void) const = 0;

	/** Get extra information. Currently unused (for future use). */
	virtual ON__UINT64 Extra(void) const = 0;

protected:
	virtual ~IRhRdkContentParamEventInfo() { }
};

/** \class IRhRdkDecalEventInfo

	Event info used by event for uuidData_RdkDecals.

	\see uuidData_RdkDecals

*/
class RHRDK_UI_SDK IRhRdkDecalEventInfo : public IRhinoUiEventInfo
{
public:
	enum class Operations { Add, Delete, Modify };
	virtual Operations Operation(void) const = 0;

	virtual const CRhinoObject& Object(void) const = 0;
	virtual const IRhRdkDecal* Decal(void) const = 0;
	virtual RDK_DECAL_CRC OldCRC(void) const = 0;

protected:
	virtual ~IRhRdkDecalEventInfo() { }
};

/** \class CRhRdkDataSource

	This is the base class for all data sources. You should prefer to subclass
	this instead of implementing IRhinoUiDataSource directly because it takes
	care of critical lifetime and ownership issues regarding data source hosts.
	If you must implement the interface yourself, you will be responsible for
	these issues. Please ask Andy or John C for help.

*/
class RHRDK_UI_SDK CRhRdkDataSource : public IRhinoUiDataSource
{
public:
	CRhRdkDataSource(const wchar_t* wszDebug=L"");

	bool IsWriting(void) const;
	bool IsUuidDataInteresting(const UUID& uuidData) const;

public:
	virtual void BeginWrite(bool bAutoChangeBracket); // [SDK_UNFREEZE] uuidData param is needed here.
	virtual void EndWrite(const UUID& uuidData);
	virtual bool WantBeginChange(void) const;

protected:
	virtual void OnBeginWrite(void); // [SDK_UNFREEZE] This is badly named. It's only called when bAutoChangeBracket is true.
	virtual void OnCommit(const UUID& uuidData);
	virtual void OnEndWrite(void);   // [SDK_UNFREEZE] This is badly named. It's only called when bAutoChangeBracket is true.
	virtual IRhinoUiEventInfo* EventInfo(void) const;
	virtual void SendEvent(const UUID& uuidData, const IRhinoUiEventInfo* pInfo=nullptr) const;

public:
	virtual void SupportedUuidData(OUT ON_SimpleArray<UUID>& aUuidData) const = 0;

public: // Implement IRhinoUiDataSource.
	virtual bool SetChanged(void) override;
	virtual void DeleteThis(void) final override;
	virtual void AddHost(IRhinoUiDataSourceHost& h) override;
	virtual void RemoveHost(IRhinoUiDataSourceHost& h) override;
	virtual void RegisterEventWatcher(IRhinoUiDataSourceEventWatcher& ew) override;
	virtual void UnregisterEventWatcher(IRhinoUiDataSourceEventWatcher& ew) override;
	virtual void Commit(const UUID& uuidData, IRhinoUiEventInfo* pInfo=nullptr) override;
	virtual void Discard(const UUID& uuidData) override;
	virtual bool ResetToDefaults(void) override;
	virtual void* EVF(const wchar_t* wszFunc, void* pvData) override;

protected:
	UUID CurrentUuidData(void) const; // For RDK internal use only. Do not call this.
	bool PrepareGetData(const UUID& uuidData, bool bForWrite, bool bAutoChangeBracket) const;

protected:
	virtual ~CRhRdkDataSource();

private:
	class CImpl;
	CImpl* m_pImpl;

protected:
	CImpl& BaseImpl(void) const;
};

/** \class IRhRdkChannelInfo

	This interface is the base for IRhRdkContentCtrlInfo and IRhRdkContentChildSlot.
	It contains the common 'channel' methods.

	\see IRhRdkContentCtrlInfo
	\see IRhRdkContentChildSlot

*/
class RHRDK_UI_SDK IRhRdkChannelInfo
{
public:
	virtual ~IRhRdkChannelInfo() { }

	virtual CRhRdkVariant GetChannelMode(void) const = 0;
	virtual bool SetChannelMode(const CRhRdkVariant& v) = 0;

	virtual CRhRdkVariant GetChannelCustom(void) const = 0;
	virtual bool SetChannelCustom(const CRhRdkVariant& v) = 0;

	virtual CRhRdkVariant GetChannelStrings(void) const = 0;
	virtual bool SetChannelStrings(const CRhRdkVariant& v) = 0;

	/** Emergency virtual function for future expansion. */
	virtual void* EVF(const wchar_t* wszFunc, void* pvData) = 0;
};

/** \class IRhRdkContentCtrlInfo

	This interface is returned by IRhinoUiDataSource::GetData(uuidData_RdkContentCtrlInfo)

	\see uuidData_RdkContentCtrlInfo

*/
class RHRDK_UI_SDK IRhRdkContentCtrlInfo : public IRhRdkChannelInfo
{
public:
	virtual ~IRhRdkContentCtrlInfo() { }

	virtual void GetContentArray(CRhRdkContentArray& aOut) const = 0;
	virtual void SetContentArray(const CRhRdkContentArray& a) = 0;
};

/** \class IRhRdkIORMenuData

	This interface is returned by IRhinoUiDataSource::GetData(uuidData_RdkIORMenuData)

	\see uuidData_RdkIORMenuData

*/
class RHRDK_UI_SDK IRhRdkIORMenuData
{
public:
	virtual ~IRhRdkIORMenuData() { }

	/** Build the menu from default IOR strings. */
	virtual bool BuildMenu(OUT IRhRdkMenu& menu) const = 0;

	/** Build the menu from IOR strings stored in an XML file. */
	virtual bool BuildMenu(const wchar_t* wszFilename, OUT IRhRdkMenu& menu) const = 0;

	/** Get the IOR and optional string from a menu command number. */
	virtual bool GetIORForCmd(unsigned short cmd, OUT double& dIOR, OUT ON_wString* pString=nullptr) const = 0;

	/** Emergency virtual function for future expansion. */
	virtual void* EVF(const wchar_t* wszFunc, void* pvData) = 0;
};

class RHRDK_SDK CRhRdkSimpleSunDataSource : public CRhRdkDataSource, protected CRhRdkEventWatcher
{
public:
	CRhRdkSimpleSunDataSource();
	virtual ~CRhRdkSimpleSunDataSource();

	IRhRdkSun& Sun(void);

public: // Implement IRhinoUiDataSource.
	virtual void SupportedUuidData(OUT ON_SimpleArray<UUID>& aUuidData) const override;
	virtual void* GetData(const UUID& uuidData, bool bForWrite, bool bAutoChangeBracket=true) const override;
	virtual void Commit(const UUID& uuidData, IRhinoUiEventInfo* pInfo=nullptr) override;
	virtual void Discard(const UUID&) override;
	virtual bool ResetToDefaults(void) override;

protected: // RDK event watcher overrides.
	virtual void OnSunSettingsChanged(const CRhRdkDocument& rdkDoc, const IRhRdkSun& newSun, const IRhRdkSun& oldSun, const void*) override;

public:
	class CImpl;
	CImpl* m_pImpl;
};

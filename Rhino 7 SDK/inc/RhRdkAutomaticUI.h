
#pragma once // SDK header

#include "RhRdkDefinitions.h"

RDK_DEPRECATED class IRhRdkParamTransport // Obsolete. Replaced by IRhinoUiDataSource.
{
};

/** \class IRhRdkParamBlock

	RDK provides automatic user interface services that allow the user to manipulate
	arbitrary sets of named parameters which can be stored inside your RDK plug-in.
	RDK accesses the parameters by means of the IRhRdkParamBlock interface.
	This interface is only implemented inside RDK.

*/
class RHRDK_SDK IRhRdkParamBlock
{
public:
	virtual ~IRhRdkParamBlock() { }

	/** \return a new instance of a generic param block. */
	static IRhRdkParamBlock* New(void);

	/** \return a new instance of a data source param block. */
	static IRhRdkParamBlock* New(IRhinoUiDataSource& ds);

	/** This method is implemented as \code delete this; \endcode */
	virtual void DeleteThis(void) = 0;

	/** Clear the collection. */
	virtual void Clear(void) = 0;

	enum class UiHints : unsigned int
	{
		None,     // No specialization.
		Folder,   // If the value is a string, it represents a folder. A folder chooser will be shown.
		Filename, // If the value is a string, it represents a file name. A file chooser will be shown.
		Combo,    // If the value is an integer, it represents a combo box index. Extra requirements define the combo contents.
		Solar,    // If the value is a 3D vector, it represents a solar vector (light direction). A sun UI will be shown.
		Location, // If the value is a 2D vector, it represents a latitude (x) and longitude (y). A location UI will be shown.
	};

	/** Add a parameter to the collection.
		\param wszParamName is the name of the parameter to add. If a parameter with
		 this name already exists, the function will fail.
		\param wszChildSlotName is the child slot name associated with the parameter.
		\param wszDisplayName is the localized display name of the parameter.
		\param vValue is the parameter's value.
		\param vMin is the parameter's minimum value (optional, can be nil).
		\param vMax is the parameter's maximum value (optional, can be nil).
		\param uih allows the UI to be enhanced by interpreting the value in a special way.
		\param wszExtraRequirementSet is the optional name of an extra requirement set.
		\param pExtraRequirement is a pointer to an extra requirement interface.
		 If wszExtraRequirementSet is specified, this pointer cannot be null.
		 \see IAutoUIExtraRequirements
		\return \e true if successful, else \e false. */
	virtual bool Add(const wchar_t* wszParamName, const wchar_t* wszChildSlotName, const wchar_t* wszDisplayName,
	                 const CRhRdkVariant& vValue, const CRhRdkVariant& vMin, const CRhRdkVariant& vMax, UiHints uih=UiHints::None,
	                 const wchar_t* wszExtraRequirementSet=nullptr,
	                 const IAutoUIExtraRequirements* pExtraRequirements=nullptr) = 0;

	/** Remove a parameter from the collection.
		\return \e true if successful, else \e false. */
	virtual bool Remove(const wchar_t* wszParamName) = 0;

	/** Get a parameter from the collection by its internal name.
		\return \e true on success, \e false if parameter not found. */
	virtual bool Get(const wchar_t* wszParamName, CRhRdkVariant& vValueOut) const = 0;

	RDK_DEPRECATED enum eSortBy { paramName, friendlyName };

	enum class SortBy : unsigned int { ParamName, DisplayName };

	/** Sort the collection. */
	virtual void Sort(SortBy by) = 0;

	class RHRDK_SDK IIterator
	{
	public:
		/** Get the next parameter from the collection.
			\return \e true on success, \e false if no more parameters. */
		virtual bool Next(OUT ON_wString& sParamName, OUT CRhRdkVariant& vParamValue) = 0;

		virtual void DeleteThis(void) = 0;
		virtual void* EVF(const wchar_t*, void*) = 0;

	protected:
		virtual ~IIterator() { }
	};

	/** Get an iterator to use when calling Next().
		The caller shall delete the iterator. */
	virtual IIterator* NewIterator(void) const = 0;

	class RHRDK_SDK IParam
	{
	public:
		virtual ~IParam() { }

		virtual CRhRdkVariant Value(void) const = 0;
		virtual void SetValue(const CRhRdkVariant& v) = 0;
		virtual UiHints UiHint(void) const = 0;
		virtual bool IsEnabled(void) const = 0;
		virtual void SetIsEnabled(bool bEnabled) = 0;
		/*virtual*/ bool IsHidden(void) const;      // = 0; [SDK_UNFREEZE]
		/*virtual*/ void SetIsHidden(bool bHidden); // = 0; [SDK_UNFREEZE]
		virtual bool IsLessThan(SortBy by, const IParam& p) const = 0;    // [SDK_UNFREEZE] These two functions are never
		virtual bool IsGreaterThan(SortBy by, const IParam& p) const = 0; // called and will be removed in the future.
		virtual const wchar_t* ParamName(void) const = 0;
		virtual const wchar_t* DisplayName(void) const = 0;
		virtual const wchar_t* ChildSlotName(void) const = 0;
		virtual const wchar_t* ExtraReqs(void) const = 0;
		virtual const CRhRdkVariant& Min(void) const = 0;
		virtual const CRhRdkVariant& Max(void) const = 0;
		virtual class IAutoUIExtraRequirements* ExtraReqPtr(void) const = 0;
		virtual void* EVF(const wchar_t*, void*) = 0;
	};

	virtual       IParam* GetParam(const wchar_t* wszParamName) = 0;
	virtual const IParam* GetParam(const wchar_t* wszParamName) const = 0;

	/** Emergency virtual function for future expansion. */
	virtual void* EVF(const wchar_t*, void*) = 0;
};

/**	\class IRhRdkAutomaticUI

	This interface allows you to use RDK's automatic user interface services from your RDK plug-in.

	Call RhRdkNewAutomaticUI() to get a pointer to this interface. It represents
	the main user interface window. This window is the holder for any number of sections
	which can be added by calling AddSection(). Non-automatic sections can be added by
	calling Holder() and using the returned interface.

*/
class RHRDK_SDK IRhRdkAutomaticUI
{
public:
	virtual ~IRhRdkAutomaticUI() { }

	/** Move the UI's window.
		\param rect is the rect to move to in client coordinates of the parent window. */
	virtual void Move(const ON_4iRect& rect, bool bRepaint=true) = 0;

	/** \return \e true if an automatic section is hidden, else \e false. \see SetSectionHidden()
		\param id is the caller-defined identifier of the automatic section to check.
		\note This only works for automatic sections. */
	virtual bool IsSectionHidden(int id) const = 0;

	/** Set an automatic section as hidden.
		\param id is the caller-defined identifier of the automatic section to set.
		\param bHidden is \e true to hide the section, else \e false.
		\note This only works for automatic sections. It can be called even before the
		 section is created to ensure that the section controls will not be created
		 before they are really needed.
		\return \e true if successful, else \e false. */
	virtual bool SetSectionHidden(int id, bool bHidden) = 0;

	/** \return \e true if section exists, else \e false.
		\param id is the caller-defined identifier of the automatic section to check.
		\note This only works for automatic sections. */
	virtual bool SectionExists(int id) const = 0;

	/** \return \e true if section is expanded, else \e false.
		\param id is the caller-defined identifier of the automatic section to check.
		\note This only works for automatic sections. */
	virtual bool IsSectionExpanded(int id) const = 0;

	/** \return \e true if section is expanded, else \e false.
		\param uuidSection is the identifier of the section to check. */
	virtual bool IsSectionExpanded(const UUID& uuidSection) const = 0;

	/** Sets a section as expanded or collapsed.
		\param id is the caller-defined identifier of the automatic section to change.
		\note This only works for automatic sections. */
	virtual void SetSectionExpanded(int id, bool bExpanded, bool bEnsureVisible) const = 0;

	/** Sets a section as expanded or collapsed.
		\param uuidSection is the identifier of the section to change.
		\note This only works for automatic sections. */
	virtual void SetSectionExpanded(const UUID& uuidSection, bool bExpanded, bool bEnsureVisible) const = 0;

	/** This method is deprecated in favor of the one below. NOT IMPLEMENTED. */
	RDK_DEPRECATED virtual void AddSection(int, class IRhRdkParamTransport*, bool, bool, IRhRdkHeaderButtonHandler* = nullptr);

	enum : unsigned int // Flags for AddSection().
	{
		Generic    = 0x0000, // Generic automatic section; nothing special.
		ForContent = 0x0001, // The section will adapt its control sizing to better suit content UIs.
	};

	/** Add an automatic parameter section to the UI.
		\param con is the controller for the section.
		\param flags specifies flags from the enum above.
		\param id is a caller-defined identifier.
		\param wszLocalCaption is the localized caption of the section.
		\param wszEnglishCaption is the English caption of the section.
		\param bExpand is \e true if the section should be initially expanded.
		 This only works the very first time the section is used because the state is persistent.
		 This flag will be removed in a future version of the SDK.
		\param pHBH is an optional handler for header buttons. The RDK takes ownership of the handler.
		\note pHBH can only be used for XP-Style sections. */
	virtual void AddSection(CRhRdkControllerPtr con, unsigned int flags, int id, const wchar_t* wszLocalCaption, const wchar_t* wszEnglishCaption, bool bExpand, IRhRdkHeaderButtonHandler* pHBH=nullptr) = 0;

//	virtual void AddSection(CRhRdkControllerPtr con, const UUID& uuidPlugIn, unsigned int flags, int id, const wchar_t* wszLocalCaption,
//	                        const wchar_t* wszEnglishCaption, IRhRdkHeaderButtonHandler* pHBH=nullptr) = 0; // [SDK_UNFREEZE]

	/** Get the section holder. Only works for XP-Style sections.
		\return A pointer to the holder or null if the UI is 'Plain'. */
	virtual IRhinoUiHolder* Holder(void) const = 0;

	/** \return The number of sections in the UI.
		\note The implementation of this method uses an iterator and is therefore 'slow'. */
	virtual int SectionCount(void) const = 0;

	/** Set the background color of the entire UI. Has no effect on XP style sections. */
	virtual void SetBackgroundColor(COLORREF col) const = 0;

	/** Set the text to display when the UI is blank. */
	virtual void SetTextWhenBlank(const wchar_t* wszText) = 0;

	/** Calls DisplayData() on all the UI sections. */
	virtual void DisplayData(void) = 0;

	/** Remove all the sections from the UI. */
	virtual void RemoveAllSections(void) = 0;

	/** Emergency virtual function for future expansion. */
	virtual void* EVF(const wchar_t*, void*) = 0;

public:
	/** Auto UI styles. \see RhRdkNewAutomaticUI(). */
	enum class Styles : unsigned int
	{
		Plain,  // Simple panel in dialog color.
		Flat,   // Expanding dialog with flat border.
		Sunken, // Expanding dialog with sunken border. Now the same as Flat ('sunken' not implemented).
		Table,  // Expanding dialog with tabulated elements (not implemented yet).
	};
};

class RHRDK_UI_SDK CRhRdkAutoUIContext : public CRhRdkObject
{
public:
	CRhRdkAutoUIContext(IAutoUIExtraRequirements* pExtraReqs);
	virtual ~CRhRdkAutoUIContext();

	virtual CRhRdkAutoUIContext* Duplicate(void) const;
	virtual bool GetValue(const wchar_t* wszParamName, const wchar_t* wszCtrlName, CRhRdkVariant& vValueOut) const;
	virtual bool SetValue(const wchar_t* wszParamName, const wchar_t* wszCtrlName, const CRhRdkVariant& vValue) const;
	virtual bool OnButtonClicked(const wchar_t* wszParamName, const wchar_t* wszCtrlName) const;
	virtual UUID TypeId(void) const;

protected:
	IAutoUIExtraRequirements* ExtraRequirements(void) const;

private:
	IAutoUIExtraRequirements* m_pExtraReqs;
	static bool m_bInsideHandler;
	void* m_pReserved;
};

class RHRDK_UI_SDK CRhRdkExcludeListAutoUIContext : public CRhRdkAutoUIContext
{
public:
	CRhRdkExcludeListAutoUIContext(IAutoUIExtraRequirements* pExtraReqs);

	virtual CRhRdkAutoUIContext* Duplicate(void) const override;
	virtual bool OnButtonClicked(const wchar_t* wszParamName, const wchar_t* wszCtrlName) const override;
	virtual UUID TypeId(void) const override;
};

class RHRDK_UI_SDK CRhRdkAutomaticUIRow : public CRhRdkObject
{
public:
	CRhRdkAutomaticUIRow();
	virtual ~CRhRdkAutomaticUIRow();

	bool FromParam(const IRhRdkParamBlock::IParam& param);
	const CRhRdkVariant& Value(void) const;
	void SetValue(const CRhRdkVariant& v);
	bool IsEnabled(void) const;
	const wchar_t* ParamName(void) const;
	const wchar_t* DisplayName(void) const;
	const wchar_t* ChildSlotName(void) const;
	const wchar_t* ValidValues(void) const;
	const wchar_t* ExtraReqs(void) const;
	const CRhRdkVariant& MinValue(void) const;
	const CRhRdkVariant& MaxValue(void) const;
	CRhRdkAutoUIContext* AutoUIContext(void) const;
	IRhRdkParamBlock::UiHints UiHint(void) const;
	void AddTexturingDS(IRhinoUiDataSource& ds);

private:
	class CImpl;
	CImpl* m_pImpl;
	const CRhRdkAutomaticUIRow& operator = (const CRhRdkAutomaticUIRow& row);
};

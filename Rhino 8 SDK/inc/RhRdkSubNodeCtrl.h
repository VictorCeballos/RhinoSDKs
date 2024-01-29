
#pragma once // Public SDK header

#if defined ON_RUNTIME_WIN && defined RHINO_SDK_MFC

#include "RhRdkContentCtrlBase.h"

/** \class CRhRdkSubNodeCtrl

	Provides a control that supports adding and deleting sub-nodes (content children)
	by using a context menu and/or a button, or drag and drop.

	STARTING WITH RHINO 8, THIS CONTROL IS DEPRECATED AND DOES NOT WORK. See [DEPCTL]

*/
RDK_DEPRECATED_CLASS class RHRDK_SDK CRhRdkSubNodeCtrl : public CRhRdkContentCtrlBase
{
public:
	CRhRdkSubNodeCtrl();
	virtual ~CRhRdkSubNodeCtrl();

	/** This method is deprecated in favor of ParentInstanceIdList(). */
	RDK_DEPRECATED virtual UUID ParentInstanceId(void) const;

	/** This method is deprecated because the control is now data-aware and is able
		to get its parents automatically. Where you would have called this method
		in the past, please call DisplayData() instead.*/
	RDK_DEPRECATED virtual bool SetParentInstanceId(const UUID&);

	/** \return A collection of instance ids of the parent contents referenced by the control.
		\param ucOut accepts the collection of instance ids.
		\return \e true if the collection contains at least one item, else \e false. */
	virtual bool ParentInstanceIdList(CRhRdkUuidCollection& ucOut) const;

	/** This method is deprecated because the control is now data-aware and is able
		to get its parents automatically. Where you would have called this method
		in the past, please call DisplayData() instead.*/
	RDK_DEPRECATED virtual bool SetParentInstanceIdList(const CRhRdkUuidCollection& uc);

	/** \return The child slot name of the associated child content. */
	virtual ON_wString ChildSlotName(void) const;

	/** Set the child slot name of the associated child content.
		\param sChildSlotName is the name of the associated child slot. */
	virtual void SetChildSlotName(const ON_wString& sChildSlotName);

	/** \return \e true if the control is displaying "(varies)", else \e false. */
	virtual bool Varies(void) const;

	// These methods are deprecated because the control is now data-aware
	// and is able to handle changes automatically.
	RDK_DEPRECATED static UINT ChangingMessageNumber(void);
	RDK_DEPRECATED static UINT ChangedMessageNumber(void);

protected:
	// These methods are deprecated because the control is now data-aware
	// and is able to handle changes automatically.
	RDK_DEPRECATED afx_msg LRESULT OnChanging(WPARAM, LPARAM);
	RDK_DEPRECATED afx_msg LRESULT OnChanged(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()

protected:
	/** \internal For RDK internal use only. */
	virtual IRhRdkContentCtrlBase* GetBaseInterface(void) const override;

private:
	class CImpl;
	CImpl* m_pImpl;
};

#endif

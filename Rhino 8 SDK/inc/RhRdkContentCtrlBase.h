
#pragma once // Public SDK header

#if defined ON_RUNTIME_WIN && defined RHINO_SDK_MFC

#include "RhRdkDefinitions.h"

/** \class CRhRdkContentCtrlBase

	Base class for content controls. This is the old-style control that looks like a hyperlink.
	It also optionally has a check box and amount edit box.

*/
RDK_DEPRECATED_CLASS class RHRDK_SDK CRhRdkContentCtrlBase : public CWnd
{
public:
	CRhRdkContentCtrlBase();
	virtual ~CRhRdkContentCtrlBase();

	CRhRdkControllerPtr Controller(void) const;
	void SetController(CRhRdkControllerPtr con);

	/**	Create the control.
		\param dwStyle specifies window styles for the control.
		\param rect specifies the size and position of the control in client coords of pParent.
		\param pParent is the parent window.
		\param uID is the ID of the control.
		\return \e true if created successfully, else \e false. */
	virtual bool CreateWnd(DWORD dwStyle, const RECT& rect, CWnd* pParent, UINT uID);

	/**	\return \e true if the control is displaying "(none)", else \e false. */
	virtual bool IsEmpty(void) const;

	/** Shows or hides an icon on the left of the content control.
		The icon is generated from the content. */
	virtual void ShowIcon(bool b);

	/** \return The channel mode set in the Properties dialog expressed as a string variant. */
	virtual CRhRdkVariant GetChannelMode(void) const;

	/** \return The custom channel string set in the Properties dialog expressed as a string variant. */
	virtual CRhRdkVariant GetChannelCustom(void) const;

	/** Set the channel mode for the Properties dialog.
		\param vMode is a string variant. Valid values are "default" or "custom" */
	virtual bool SetChannelMode(const CRhRdkVariant& vMode);

	/** Set the custom channel string for the Properties dialog. */
	virtual void SetChannelCustom(const CRhRdkVariant& vString);

	/** Force the control to re-display its content information. */
	virtual void DisplayData(void);

	/** Executes the change command - as if the button on the right had been pressed. */
	virtual void Change(void);

	/** This function is called after the user has changed the content.
		Optionally override this method to handle changes in a subclass of the control. */
	virtual void OnChange(void) { }

	/** \return \e true if the control is read-only. */
	virtual bool ReadOnly(void) const;

	/** Make the control read-only. This prevents the user from changing or removing the child. */
	virtual void SetReadOnly(bool b);

	/** Emergency virtual function for future expansion. */
	virtual void* EVF(const wchar_t* wszFunc, void* pvData);

public: // Check mark interface.

	/** Shows or hides a check mark on the left of the content control. */
	virtual void ShowCheck(bool b);

	/** \return The state of the check mark. Same as CButton::GetCheck(). */
	virtual UINT GetCheck(void) const;

	/** Set the state of the check mark. Same as CButton::SetCheck(). */
	virtual void SetCheck(UINT u);

	/** \return The enable state of the check mark. */
	virtual bool CheckEnabled(void) const;

	/** Set the enable state of the check mark. */
	virtual void SetCheckEnabled(bool b);

	// This method is deprecated because the control is now data-aware
	// and is able to handle changes automatically.
	RDK_DEPRECATED static UINT CheckMessageNumber(void);

	/** This is called after the user has changed the check box state.
		Optionally override this method to handle check changes in a subclass of the control. */
	virtual void OnCheckChanged(void) { }

public: // Amount interface.

	/** Shows or hides an amount control on the right of the content control.
		\note The amount control is 'percentile'; it shows 0% to 100% but actual values
		 are always in the range 0.0 to 1.0. */
	virtual void ShowAmount(bool b);

	/** \return The amount shown by the amount control in the range of its bounds. */
	virtual double GetAmount(void) const;

	/** Set the amount shown by the amount control in the range of its bounds. */
	virtual void SetAmount(double d);

	/** Set the bounds of the amount control in the range -1.0 to 1.0.
		The default bounds are 0.0 and 1.0. */
	virtual void SetAmountBounds(double dMin, double dMax);

	/** \return \e true if the amount varies, else \e false. */
	virtual bool AmountVaries(void) const;

	/** Set the varies state of the amount control. */
	virtual void SetAmountVaries(bool b=true);

	/** \return The enable state of the amount control. */
	virtual bool AmountEnabled(void) const;

	/** Set the enable state of the amount control. */
	virtual void SetAmountEnabled(bool b);

	// This method is deprecated because the control is now data-aware
	// and is able to handle changes automatically.
	RDK_DEPRECATED static UINT AmountMessageNumber(void);

	/** This is called after the user has changed the amount value.
		Optionally override this method to handle amount changes in a subclass of the control. */
	virtual void OnAmountChanged(void) { }

protected:
	/** Called just before the control is subclassed. */
	virtual void PreSubclassWindow() override;

protected:
	afx_msg int OnCreate(LPCREATESTRUCT);
	afx_msg BOOL32 OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnEnable(BOOL32 bEnable);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	// These methods are deprecated and never called.
	RDK_DEPRECATED afx_msg LRESULT OnCheck(WPARAM, LPARAM);
	RDK_DEPRECATED afx_msg LRESULT OnAmount(WPARAM, LPARAM);

	DECLARE_MESSAGE_MAP()

	/** \internal For RDK internal use only. */
	virtual void Initialize(void);

	/** \internal For RDK internal use only. */
	virtual class IRhRdkContentCtrlBase* GetBaseInterface(void) const = 0;

private:
	/** \internal For RDK internal use only. */
	class CImpl;
	CImpl* m_pBaseImpl;
};

#endif

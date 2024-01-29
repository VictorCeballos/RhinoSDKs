
#pragma once // Public SDK header

#include "RhRdkObject.h"

class CRhRdkColor;

/** \class IRhRdkAngleDialDecorator

	Implement this interface to provide decoration for the dial of an angle control.

	\see CRhRdkAngleCtrl

*/
RDK_DEPRECATED_CLASS class RHRDK_SDK IRhRdkAngleDialDecorator
{
public:
	virtual ~IRhRdkAngleDialDecorator() { }

	/** You must implement this method as \code delete this; \endcode */
	virtual void DeleteThis(void) = 0;

	/** Implement this method to override the default dial colors when the style is kUnmarked, kCompass or kAzimuth.
		If you don't want to override the dial colors, implement a no-op stub.
		\see CRhRdkAngleCtrl::SetDialColors(). */
	virtual void DialColors(CRhRdkColor& colOut1, CRhRdkColor& colOut2) const = 0;

	/** Implement this method to draw the decoration.
		\param dc is the device context to draw into.
		\param dialRect is the rectangle of the dial.
		\param dRadius is the radius of the dial.
		\param dAngle is the angle being displayed by the control.
		\param bEnabled is \e true if the control is enabled, else \e false.
		\param bHot is \e true if the decoration should be drawn in hot-tracked style. */
	virtual void Draw(HDC dc, const ON_4iRect& dialRect, double dRadius, double dAngle, bool bEnabled, bool bHot) const = 0;

	/** Implement this method to return a pointer to an optional next decorator.
		This allows decorators to be chained together. Return null if not needed. */
	virtual IRhRdkAngleDialDecorator* NextDecorator(void) const = 0;

	/** Emergency virtual function for future expansion. */
	virtual void* EVF(const wchar_t*, void*) = 0;
};

#if defined ON_RUNTIME_WIN

/** \class CRhRdkAngleCtrl

	This class is a control which can be placed on a dialog to allow the user to set an angle.

	STARTING WITH RHINO 8, THIS CONTROL IS DEPRECATED AND DOES NOT WORK. See [DEPCTL]

*/
RDK_DEPRECATED_CLASS class RHRDK_SDK CRhRdkAngleCtrl : public CRhRdkObject
{
public:
	enum RDK_DEPRECATED eStyle { unmarked, compass, azimuth, altitude, altitude0, force32_style = 0xFFFFFFFF };

	enum class Style : unsigned int
	{
		kUnmarked,  // Specifies an azimuth dial with no marks.
		kCompass,   // Specifies an azimuth dial with compass point marks (N, E, S, W).
		kAzimuth,   // Specifies an azimuth dial with heading marks (0, 90, 180, 270).
		kAltitude,  // Specifies an altitude dial that goes from +90 to -90 degrees.
		kAltitude0, // Specifies an altitude dial that goes from +90 to 0 degrees.
	};

	RDK_DEPRECATED CRhRdkAngleCtrl(eStyle s); // Not implemented.
	CRhRdkAngleCtrl(Style s);
	virtual ~CRhRdkAngleCtrl();

	/**	Create the control.
		\param dwStyle specifies window styles for the control.
		\param rect specifies the size and position of the control in client coords of pParent.
		\param pParent is the parent window.
		\param uID is the ID of the control.
		\return \e true if created successfully, else \e false. */
	virtual bool Create(DWORD dwStyle, const ON_4iRect& rect, HWND pParent, UINT uID);

	/** \return The angle, in degrees, that the control is displaying. */
	virtual double Angle(void) const;

	/** Set the angle that the control displays.
		\param dAngle is the angle in degrees. */
	virtual void SetAngle(double dAngle);

	/** OBSOLETE. */
	virtual void SetBackgroundColor(COLORREF col);

	/**	/** OBSOLETE. Rhino compliant colors are used. The dial will be shaded with a blend from 'normal start'
		 to 'normal end' and the blend will rotate with the dial's angle setting.
		\note It is possible to implement IRhRdkAngleDialDecorator to override these colors dynamically. */
	virtual void SetDialColors(COLORREF col1, COLORREF col2);

	/** Set a decorator to the control. The control takes ownership of the decorator.
		This decorator is drawn before the dial lines. */
	virtual void SetDecoratorPre(IRhRdkAngleDialDecorator* pDecorator);

	/** Set a decorator to the control. The control takes ownership of the decorator.
		This decorator is drawn after the dial lines. */
	virtual void SetDecoratorPost(IRhRdkAngleDialDecorator* pDecorator);

	/** Set hot-tracking of the control on or off. */
	virtual void SetHotTrackingOn(bool bOn);

	/** Set debugging colors on or off. This can be used as an aid to placing the control on a dialog.
		When on, the control is painted in red and the text rectangle is painted in green. */
	virtual void SetDebugColorsOn(bool bOn);

	// These two methods have been retained for use by Brazil but are not recommended.
	// You should be able to replace your calls with one of the following 4 functions.
	operator HWND (void) const;
	HWND Wnd(void) const;

	virtual bool IsWindow(void) const;
	virtual void EnableWindow(bool bEnable);
	virtual void ShowWindow(bool bShow);
	virtual void MoveWindow(const ON_4iRect& rect);

	/**	A message is sent continuously to the parent window when the user plays with the control. Example usage:
		\code
		const UINT uAngleChangedMsg = CRhRdkAngleCtrl::ChangedMessageNumber();
		...
		BEGIN_MESSAGE_MAP(CMyDialog, CDialog)
			ON_REGISTERED_MESSAGE(uAngleChangedMsg, OnAngleChanged)
		END_MESSAGE_MAP()
		...
		LRESULT CMyDialog::OnAngleChanged(WPARAM, LPARAM ctrlID)
		{
			CWnd* pWnd = GetDlgItem(ctrlID);
			...
			return 1;
		}
		\endcode
	*/
	static UINT ChangedMessageNumber(void);

	/**	A message is sent to the parent window when the user stops dragging the control. Example usage:
		\code
		const UINT uAngleEndDragMsg = CRhRdkAngleCtrl::EndDragMessageNumber();
		...
		BEGIN_MESSAGE_MAP(CMyDialog, CDialog)
			ON_REGISTERED_MESSAGE(uAngleEndDragMsg, OnAngleEndDrag)
		END_MESSAGE_MAP()
		...
		LRESULT CMyDialog::OnAngleEndDrag(WPARAM, LPARAM ctrlID)
		{
			CWnd* pWnd = GetDlgItem(ctrlID);
			...
			return 1;
		}
		\endcode
	*/
	static UINT EndDragMessageNumber(void);

public:
	/** \internal For RDK internal use only. */
	class CImpl;
	CImpl* m_pImpl;
};

#endif

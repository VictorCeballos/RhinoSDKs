
#pragma once // SDK header

#include "RhRdkExtension.h"

/** \class CRhRdkRenderWindowEventSink

	This interface is deprecated in favor of CRhRdkRenderWindowMouseEventWatcher.

*/
RDK_DEPRECATED class RHRDK_SDK CRhRdkRenderWindowEventSink : public CRhRdkExtension
{
public:
	virtual UUID InterfaceId(void) const final override;

	virtual void OnLButtonDown(const CPoint& pt) = 0;

	// These were never implemented and are not called.
	virtual void OnLButtonUp(const CPoint& pt) = 0;
	virtual void OnLButtonDblClick(const CPoint& pt) = 0;
	virtual void OnRButtonDown(const CPoint& pt) = 0;
	virtual void OnRButtonUp(const CPoint& pt) = 0;
	virtual void OnRButtonDblClick(const CPoint& pt) = 0;
};

/** \class CRhRdkRenderWindowMouseEventWatcher

	This object is an RDK extension that allows a plug-in to find out about mouse activity
	in the render window. To use it, derive a class that implements each abstract method
	to respond to mouse events. Then register your subclass as follows:

	\code
	void CMyRdkPlugIn::RegisterExtensions(void) const
	{
		...
		AddExtension(new CMyRenderWindowEventWatcher);
		...
	}
	\endcode

	The mouse event methods will be called when the user operates the mouse inside the view
	area (rendering) of any render window that was opened by your plug-in. You can use the
	supplied render window reference to determine which render window it is.

*/
class RHRDK_SDK CRhRdkRenderWindowMouseEventWatcher : public CRhRdkExtension
{
public:
	/** Implement this method to respond to mouse move events. */
	virtual void OnMouseMove(IRhRdkRenderWindow& rw, const ON_2iPoint& point) = 0;

	/** Implement this method to respond to left mouse button down events. */
	virtual void OnLButtonDown(IRhRdkRenderWindow& rw, const ON_2iPoint& point) = 0;

	/** Implement this method to respond to left mouse button up events. */
	virtual void OnLButtonUp(IRhRdkRenderWindow& rw, const ON_2iPoint& point) = 0;

	/** Implement this method to respond to left mouse button double-click events. */
	virtual void OnLButtonDblClk(IRhRdkRenderWindow& rw, const ON_2iPoint& point) = 0;

	/** Implement this method to respond to right mouse button down events. */
	virtual void OnRButtonDown(IRhRdkRenderWindow& rw, const ON_2iPoint& point) = 0;

	/** Implement this method to respond to right mouse button up events. */
	virtual void OnRButtonUp(IRhRdkRenderWindow& rw, const ON_2iPoint& point) = 0;

	/** Implement this method to respond to right mouse button double-click events. */
	virtual void OnRButtonDblClk(IRhRdkRenderWindow& rw, const ON_2iPoint& point) = 0;

public:
	virtual UUID InterfaceId(void) const final override;
};

/** \class CRhRdkRenderWindowCustomDlg

	This custom plug-in interface allows you to create a custom dialog to be hosted on a dock bar inside the render frame.
	Since it is possible to have more than one open render frame, it is possible for this interface to access more than
	one hosted dialog. This is made possible by use of the render session id which also identifies the dialog.
	Your implementation must ensure that it is possible to have multiple dialogs identified by this UUID.

*/
class RHRDK_SDK CRhRdkRenderWindowCustomDlg : public CRhRdkExtension
{
public:
	virtual UUID InterfaceId(void) const final override;

	/** Implement this method to return the title that will appear on the host dock bar when it is floating.
		\param uuidRenderSession is the render session id of the dock bar. */
	virtual const wchar_t* DockBarTitle(const UUID& uuidRenderSession) const = 0;

	/** Implement this method to construct and create your dialog.
		\param pParentWnd is a pointer to the dialog's parent.
		\param uuidRenderSession is the id of the associated render session. You can get a pointer to the
		 render window interface by calling RhRdkFindRenderWindow().
		\see RhRdkFindRenderWindow() */
	virtual bool Create(HWND pParentWnd, const UUID& uuidRenderSession) = 0;

	/** Implement this method to destroy and delete your dialog.
		\param uuidRenderSession is the render session id of the dialog to destroy. */
	virtual void Destroy(const UUID& uuidRenderSession) = 0;

	/** Implement this method to move your dialog to the position specified by 'rect'.
		\param rect specifies the position to move the dialog to.
		\param uuidRenderSession is the render session id of the dialog to move. */
	virtual void MoveWindow(const ON_4iRect& rect, const UUID& uuidRenderSession) = 0;

	/** Implement this method to return the flags to be passed to CControlBar::EnableDocking() (e.g., CBRS_ALIGN_ANY) */
	virtual UINT EnableDockingFlags(void) const = 0;

	/** Implement this method to return the flags to be passed to CFrameWnd::DockControlBar() (e.g., AFX_IDW_DOCKBAR_LEFT) */
	virtual UINT DockControlBarFlags(void) const = 0;

	/** Implement this method to return the initial visibility of the dock bar. */
	virtual bool InitialShowControlBar(void) const = 0;

	/** Implement this method to return \e true if you want this dialog to always appear on the render window even when
		the render window is for a different renderer. If you return \e false, the dialog and dock bar will only be created
		when the current renderer id matches the render engine id.
		\note It should be \e very rare to implement this as anything other than \code return false; \endcode. */
	virtual bool AlwaysShowDialog(void) const = 0;

	/** Implement this method to return the window handle of your dialog.
		\param uuidRenderSession is the render session id of the dialog to return. */
	virtual HWND WindowHandle(const UUID& uuidRenderSession) const = 0;
};

/** \class CRhRdkRenderFrameTabFactory

	RDK provides two tabs on the Render Window's 'effects' panel, Exposure
	and Post-Effects. This class is an RDK extension which allows users to
	add their own tabs to this panel.

*/
class RHRDK_SDK CRhRdkRenderFrameTabFactory : public CRhRdkExtension
{
public:
	virtual UUID InterfaceId(void) const final override;
	virtual class CRhinoUiDockBarTab* NewTab(IRhRdkRenderWindow&) const = 0;
	virtual UUID RenderEngineId(void) const = 0;
	virtual UUID TabId(void) const = 0;
};

/** \class CRhRdkRenderFrameTabFactory

	Extended version only used on the Mac at the moment. Might be used on Windows in Rhino 7.

*/
class RHRDK_SDK CRhRdkRenderFrameTabFactoryEx : public CRhRdkRenderFrameTabFactory
{
public:
	virtual class CRhinoUiDockBarTab* NewTabEx(CRhRdkControllerPtr con, HWND parent) const = 0;
};

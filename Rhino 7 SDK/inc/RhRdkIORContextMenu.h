
#pragma once

#include "RhRdkDefinitions.h"

/** \class CRhRdkIORContextMenu

	This class displays a context menu containing an extensive list of substances with their IOR values.
	It is designed to be used from an OnContextMenu handler. Create an instance on the stack and
	call its TrackMenu() method.
*/
class RHRDK_SDK CRhRdkIORContextMenu final
{
public:
	CRhRdkIORContextMenu();
	~CRhRdkIORContextMenu();

	/** Display and track the context menu.
		\param pWnd is the window that displays the menu, for example an edit box.
		\param point is the position to display the menu at inside the window.
		\param dIOROut accepts the IOR value of the user's chosen substance.
		\param pStringOut accepts the name of the user's chosen substance. Can be NULL if not required.
		\return \e true if the user chose a substance, else \e false. */
	bool TrackMenu(HWND pWnd, const ON_2iPoint& point, double& dIOROut, ON_wString* pStringOut=nullptr) const;

private:
	/** \internal For RDK internal use only. */
	class CImpl;
	CImpl* m_pImpl;
};


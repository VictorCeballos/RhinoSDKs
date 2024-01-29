/* $NoKeywords: $ */
/*
//
// Copyright (c) 1993-2007 Robert McNeel & Associates. All rights reserved.
// Rhinoceros is a registered trademark of Robert McNeel & Associates.
//
// THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT EXPRESS OR IMPLIED WARRANTY.
// ALL IMPLIED WARRANTIES OF FITNESS FOR ANY PARTICULAR PURPOSE AND OF
// MERCHANTABILITY ARE HEREBY DISCLAIMED.
//				
// For complete Rhino SDK copyright information see <http://www.rhino3d.com/developer>.
//
////////////////////////////////////////////////////////////////
*/

#pragma once

class CRhinoUiDockBar;

// These classes do not use MFC
#include "rhinoSdkUiProfileContext.h"
#include "rhinoSdkUiProfileContextIterator.h"

#if defined (RHINO_SDK_MFC)
#include "rhinosdkDib.h"
#include "rhinoSdkUiThemeDraw.h"
//#include "rhinoSdkUiBitmapButton.h"
//#include "rhinoSdkUiColorButton.h"
#include "rhinoSdkUiCheckBox.h"
#include "rhinoSdkUiImageList.h"
#include "rhinoSdkUiLayerListCtrl.h"
#include "rhinoSdkUiLayerComboBox.h"
#include "rhinoSdkUiColorComboBox.h"
#include "rhinoSdkUiColorListBox.h"
#include "rhinoSdkUiDirDialog.h"
#include "rhinoSdkUiFileDialog.h"
#include "RhinoSkdUiFontComboBox.h"
#include "rhinoSdkUiSliderCtrl.h"
#include "rhinoSdkUiGradientSliderCtrl.h"
#include "rhinoSdkUiHyperLink.h"
#include "rhinoSdkUiInPlaceCtrls.h"
#include "rhinoSdkUiListBoxEx.h"
#include "rhinoSdkUiMemDC.h"
#include "rhinoSdkUiPopUpMenu.h"
#include "rhinoSdkUiPopuUpListBox.h"
#include "rhinoSdkUiPopUpListWnd.h"
#include "rhinoSdkUiProgressCtrl.h"
#include "rhinoSdkUiProgressBar.h"
#include "rhinoSdkUiRichEditCtrl.h"
#include "rhinoSdkUiStatic.h"
#include "rhinoSdkUiSeparator.h"
#include "rhinoSdkUiGridListCombo.h"
#include "rhinoSdkUiGridListEdit.h"
#include "rhinoSdkUiGridListHeaderCtrl.h"
#include "rhinoSdkUiGridListCtrl.h"
#include "rhinoSdkuimultimonitor.h"
#include "rhinoSdkUiRegistry.h"
#include "rhinoSdkuiresourcemanager.h"
#include "rhinoSdkUiWindowsPaintManager.h"
#include "rhinoSdkUiComboBox.h"
#include "rhinoSdkUiDragBitmapWnd.h"
#include "rhinoSdkUiEdit.h"
#include "RhinoSdkUiPointEdit.h"
#include "rhinoSdkUiDialogItemResizer.h"
#include "rhinoSdkUiDialog.h"
#include "rhinoSdkUiTabCtrlPage.h"
#include "RhinoSdkUiTabCtrl.h"
#include "rhinoSdkUiTabPageCtrl.h"
#include "rhinoSdkUiDHtmlDialog.h"
#include "rhinoSdkUiExpandableTabCtrl.h"
#include "rhinoSdkUiExpandableTabPage.h"
#include "rhinoSdkUiDockBarCaptionButton.h"
#include "rhinoSdkUiDockBarClientWnd.h"
#include "rhinoSdkUiDockBarDialog.h"
#include "RhinoSdkUiTabbedSheetCtrl.h"
#include "rhinoSdkUiToolTip.h"
#include "RhinoSdkUiButton.h"
#include "rhinoSdkUiBitmapButton.h"
#include "rhinoSdkUiColorButton.h"
#include "rhinoSdkUiDockBar.h"
#include "rhinoSdkUiDockBarManager.h"
#include "rhinoSdkUiDockBarExpandableTabCtrl.h"
#include "RhinoSdkUiExpandableTabbedDockBar.h"
#include "RhinoSdkUiPageDockBarManager.h"
#include "rhinoSdkUiManager.h"
#include "rhinoSdkUiUtilities.h"
#include "rhinoSdkUiLineTypeListCtrl.h"
#include "rhinoSdkUiPrintWidthListCtrl.h"
#include "rhinoSdkUiAutocomplete.h"
#include "rhinoSdkUiOptionsListCtrlItem.h"
#include "rhinoSdkUiOptionsListCtrl.h"
// The next 2 files are provided for backwards compatibility only
// New code should use CRhinoSdkUiEdit
#include "rhinoSdkUiEditInt.h"
#include "rhinoSdkUiEditReal.h"
#include "RhinoSdkUiBlockPreview.h"
#include "RhinoSdkUiCheckListBox.h"
#endif

// END - From RMA MFC UI Lib

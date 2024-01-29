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

class CRhinoUiListBoxExBuddy;

////////////////////////////////////////////////////////////////
//
// CRhinoUiListBoxEx
//
class RHINO_SDK_CLASS CRhinoUiListBoxEx : public CDragListBox
{
  DECLARE_DYNCREATE( CRhinoUiListBoxEx )
    
public:
  CRhinoUiListBoxEx();
  virtual ~CRhinoUiListBoxEx();

  enum
  {
    ////////////////////////////////////////////////////////////////
    // Listbox editing mode
    // If set, shows a "..." button near the edit box
    LBEX_EDITBUTTON = 0x4000L,
    // for internal use only, this allows adding additional values without
    // breaking the SDK in the future
    force_32bit_listbox_ex = 0xFFFFFFFF
  };

  void AllowEditing( BOOL bAllowEditing = TRUE ) { m_bAllowEditing = bAllowEditing; }
  void AllowDrag(BOOL bAllowDrag = TRUE) { m_bAllowDrag = bAllowDrag; }
  
  void BeginEditing( int iItem );
  void EndEditing( BOOL fCancel );
  
  void EditNew();
  void SetEditStyle( DWORD dwEditStyle );
  HWND GetEditHandle() const;
  void SetEditText( const CString& strNewText ) const;
  
  int MoveItemUp( int iItem );
  int MoveItemDown( int iItem );
  void SwapItems( int iFirstItem, int iSecondItem );
  void SetItem( int iItem, LPCTSTR szItemText, DWORD_PTR dwItemData) ;
  void SetItemText( int iItem, LPCTSTR szItemText );
  
private:
  void CreateEdit();
  UINT ListBoxExStyleFlags() const;
  UINT ListBoxExStyleFlagsEX() const;
  BOOL AltKeyPressed( UINT uFlag) const;
private:
  enum
  {
    LBEX_ID_EDITCONTROL   = 1,
    LBEX_ID_BUTTONCONTROL = 2,
    LBEX_LASTITEM_MAGIC   = 0x45424558,   // 'LBEX'
    // for internal use only, this allows adding additional values without
    // breaking the SDK in the future
    force_32bit_listbox_ex_id = 0xFFFFFFFF
  };
private:
  static UINT const m_DragListMsg;
  static UINT const m_IPCEndEditMsg;
  CRhinoUiListBoxExBuddy* m_pBuddy;
  DWORD m_dwEditStyle;
  CRhinoUiInPlaceEdit* m_pEdit;
  CRect m_rcEdit;
  CRhinoUiInPlaceButton* m_pBrowseButton;
  CRect m_rcButton;
  int m_iSelected;
  int m_iEdited;
  BOOL m_bAllowEditing;
  BOOL m_bAllowDrag;
public:
  virtual BOOL OnBeginEditing( int iItem );
  virtual BOOL OnEndEditing( int iItem, BOOL fCanceled );
  virtual void OnBrowseButton( int iItem );
public:
  virtual BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult);
protected:
  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
  virtual void PreSubclassWindow();
  virtual void MeasureItem( LPMEASUREITEMSTRUCT lpMeasureItemStruct );
  virtual void DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct );   
  virtual void DrawInsert( int nIndex );
  void DrawSeparator( int nIndex );
protected:
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
  afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
  afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
  afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
  afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
  afx_msg LRESULT OnEndEditMessage(WPARAM wParam, LPARAM lParam);
protected:
  DECLARE_MESSAGE_MAP()
};

////////////////////////////////////////////////////////////////
//
// CRhinoUiListBoxExBuddy
//
class RHINO_SDK_CLASS CRhinoUiListBoxExBuddy : public CWnd
{
public:
  CRhinoUiListBoxExBuddy( UINT nBitmapID);
  virtual ~CRhinoUiListBoxExBuddy();

  enum
  {
    bmp_width    = 88,
    bmp_height   = 20,
    bmp_btnwidth = 22,

    btn_new    =  0,
    btn_del    =  1,
    btn_up     =  2,
    btn_down   =  3,
    bmp_numbtn =  4,
    // for internal use only, this allows adding additional values without
    // breaking the SDK in the future
    force_32bit_list_box_ex_buddy = 0xFFFFFFFF
  };
  
  void SetListBox( CRhinoUiListBoxEx *pListBox ) { m_pListBoxEx = pListBox; }

private:
  void CreateTooltips();
  void SetTipText(UINT nID, LPTSTR szTipText);
  int  FindButton(const CPoint & point);
  void InvalidateButton(int iIndex, BOOL bUpdateWindow = TRUE);
  void DoClick(int iIndex);
  
private:
  CRhinoUiListBoxEx* m_pListBoxEx;
  CBitmap m_ButtonBitmap;
  UINT m_iButton;
  BOOL m_bButtonPressed;
  CRect m_arcButtons[bmp_numbtn];
  CToolTipCtrl m_ToolTip;
  HBITMAP m_hBitmap;
protected:
  virtual void PreSubclassWindow();
  virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
protected:
  afx_msg void OnPaint();
  afx_msg void OnMouseMove(UINT nFlags, CPoint point);
  afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
  afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
  afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
protected:
  DECLARE_MESSAGE_MAP()
};

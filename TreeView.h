
// TreeView.h : interface of the TreeView class
//

#pragma once


class TreeView : public CTreeView
{
protected: // create from serialization only
	TreeView();
	DECLARE_DYNCREATE(TreeView)

// Attributes
public:
	CMFCApplication1Doc* GetDocument() const;
	TVINSERTSTRUCT tvInsert;
// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~TreeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TreeView.cpp
inline CMFCApplication1Doc* TreeView::GetDocument() const
   { return reinterpret_cast<CMFCApplication1Doc*>(m_pDocument); }
#endif



// TreeView.cpp : implementation of the TreeView class
//

#include "stdafx.h"
#include <msxml.h>
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCApplication1.h"
#endif

#include "MFCApplication1Doc.h"
#include "TreeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// TreeView

IMPLEMENT_DYNCREATE(TreeView, CTreeView)

BEGIN_MESSAGE_MAP(TreeView, CTreeView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// TreeView construction/destruction

TreeView::TreeView()
{
	// TODO: add construction code here

}

TreeView::~TreeView()
{
}

BOOL TreeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CTreeView::PreCreateWindow(cs);
}

void ExpandTreeItem(CTreeCtrl& tree, HTREEITEM hItem, UINT nCode)
{
	HTREEITEM hChild;

	if (tree.ItemHasChildren(hItem))
	{
		tree.Expand(hItem, nCode);
		hChild = tree.GetChildItem(hItem);

		while (hChild)
		{
			ExpandTreeItem(tree, hChild, nCode);
			hChild = tree.GetNextItem(hChild, TVGN_NEXT);
		}
	}
}

void FillNodes(IXMLDOMNode* pRoot, HTREEITEM parent, CTreeCtrl& tree) {
	CComBSTR tagName;
	pRoot->get_nodeName(&tagName);

	HTREEITEM hi = tree.InsertItem(tagName, parent);

	CComPtr<IXMLDOMNodeList> childNodes;
	pRoot->get_childNodes(&childNodes);

	long count(0);
	childNodes->get_length(&count);
	for (long i = 0; i < count; ++i) {
		CComPtr<IXMLDOMNode> pChild;
		childNodes->get_item(i, &pChild);
		FillNodes(pChild, hi, tree);
	}
}

void TreeView::OnInitialUpdate()
{
	CString path = GetDocument()->GetPathName();
	if (path.IsEmpty()) return;
	
	CComPtr<IXMLDOMDocument> iXMLDoc;
	iXMLDoc.CoCreateInstance(__uuidof(DOMDocument));

	// Load the file. 
	VARIANT_BOOL bSuccess = false;
	// Can load it from a url/filename...
	iXMLDoc->load(CComVariant(path), &bSuccess);
	// or from a BSTR...
	//iXMLDoc->loadXML(CComBSTR(s),&bSuccess);

	// Get a pointer to the root
	CComPtr<IXMLDOMElement> iRootElm;
	iXMLDoc->get_documentElement(&iRootElm);

	
	// Thanks to the magic of CComPtr, we never need call
	// Release() -- that gets done automatically.
	
	CTreeCtrl& tree = GetTreeCtrl();
	tree.ModifyStyle(0, TVS_EDITLABELS | TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT);
	
	tree.DeleteAllItems();
	FillNodes(iRootElm, TVI_ROOT, tree);

	ExpandTreeItem(tree, tree.GetRootItem(), TVE_EXPAND);
}

void TreeView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void TreeView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// TreeView diagnostics

#ifdef _DEBUG
void TreeView::AssertValid() const
{
	CTreeView::AssertValid();
}

void TreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CMFCApplication1Doc* TreeView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication1Doc)));
	return (CMFCApplication1Doc*)m_pDocument;
}
#endif //_DEBUG


// TreeView message handlers

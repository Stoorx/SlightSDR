#pragma once

#include <wx/wx.h>
#include <wx/splitter.h>
#include <string>
#include <sstream>
#include "IView.h"
#include "LeftPanel.h"

class MainWindow : public wxFrame {
public:
	MainWindow(IView* view);
private:
	IView* _view;
};



MainWindow::MainWindow(IView* view) {
	_view = view;

	Create(nullptr, wxID_ANY, L"SlightSDR");
	SetIcon(wxIcon("wxwin.ico", wxBITMAP_TYPE_ICO));
	SetSize(wxSize(800, 480));
	SetBackgroundColour(wxColour(250, 250, 250));
	// Menu
	auto menuFile = new wxMenu();
	menuFile->Append(new wxMenuItem(nullptr, wxID_ANY, L"Создать"));

	auto menuView = new wxMenu();
	menuView->Append(new wxMenuItem(nullptr, wxID_ANY, L"Четотам"));

	auto menuBar = new wxMenuBar();
	menuBar->Append(menuFile, L"Файл");
	menuBar->Append(menuView, L"Вид");
	SetMenuBar(menuBar);

	auto splitView = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_LIVE_UPDATE | wxSP_NO_XP_THEME | wxSP_3DSASH | wxSP_THIN_SASH);
	auto left = new LeftPanel(splitView);

	
	auto right = new wxTextCtrl(splitView, wxID_ANY, L"ФАК Ю!");
	right->SetWindowStyleFlag(wxTE_MULTILINE);
	splitView->SplitVertically(left, right, 300);
	splitView->SetSashInvisible(false);

	Show();
}



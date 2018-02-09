#pragma once

#include <wx/wx.h>
#include <wx/splitter.h>
#include <string>
#include <sstream>
#include "IView.h"
#include "LeftPanel.h"

class MainWindow : public wxFrame {
public:
	MainWindow();
private:
};



MainWindow::MainWindow() {
	�reate(nullptr, wxID_ANY, L"SlightSDR");
	SetIcon(wxIcon("wxwin.ico", wxBITMAP_TYPE_ICO));
	SetSize(wxSize(800, 480));
	SetBackgroundColour(wxColour(250, 250, 250));
	// Menu
	auto menuFile = new wxMenu();
	menuFile->Append(new wxMenuItem(nullptr, wxID_ANY, L"�������"));

	auto menuView = new wxMenu();
	menuView->Append(new wxMenuItem(nullptr, wxID_ANY, L"�������"));

	auto menuAbout = new wxMenu();
	menuAbout->Append(new wxMenuItem(nullptr, wxID_ANY, L"������� �� ���������"));
	menuAbout->Append(new wxMenuItem(nullptr, wxID_ANY, L"� ���������"));

	auto menuBar = new wxMenuBar();
	menuBar->Append(menuFile, L"����");
	menuBar->Append(menuView, L"���");
	menuBar->Append(menuAbout, L"�������");
	SetMenuBar(menuBar);

	auto left = new LeftPanel(this);
	left->SetMinSize(wxSize(200, wxDefaultSize.GetY()));
	
	auto right = new wxTextCtrl(this, wxID_ANY);
	right->SetWindowStyleFlag(wxTE_MULTILINE);
	
	auto sizer = new wxBoxSizer(wxHORIZONTAL);
	sizer->Add(left, 0, wxEXPAND);
	sizer->Add(right, 1, wxEXPAND);

	SetSizer(sizer);

	Show();
}



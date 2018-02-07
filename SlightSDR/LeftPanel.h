#pragma once


#include <wx/wx.h>
#include "PlayControl.h"


class LeftPanel : public wxPanel {
public:
	LeftPanel(wxWindow* parent);
};

LeftPanel::LeftPanel(wxWindow* parent) {
	Create(parent, wxID_ANY);

	auto recieverGroup = new wxStaticBox(this, wxID_ANY, L"Настройки устройства");
	auto rgSizer = new wxBoxSizer(wxVERTICAL);
	recieverGroup->SetSizer(rgSizer);
	

	auto playControl = new PlayControl(recieverGroup);
	rgSizer->AddSpacer(15);
	rgSizer->Add(playControl);
	rgSizer->AddSpacer(5);
	
	
	

	auto sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(recieverGroup, 0, wxALL | wxEXPAND, 5);
	

	SetSizer(sizer);
}


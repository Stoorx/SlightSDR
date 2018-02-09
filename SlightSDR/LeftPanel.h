#pragma once


#include <wx/wx.h>
#include "PlayControl.h"
#include <vector>


class LeftPanel : public wxPanel {
public:
	LeftPanel(wxWindow* parent);
};

LeftPanel::LeftPanel(wxWindow* parent) {
	Create(parent, wxID_ANY);
	auto sizer = new wxBoxSizer(wxVERTICAL);
	sizer->AddSpacer(5);

	auto playControl = new PlayControl(this);
	sizer->Add(playControl, 0, wxEXPAND | wxLEFT | wxRIGHT, 5);
			
	auto recieverGroup = new wxStaticBox(this, wxID_ANY, L"Настройки устройства");
	auto rgSizer = new wxBoxSizer(wxVERTICAL);
	recieverGroup->SetSizer(rgSizer);
	rgSizer->AddSpacer(18);
	std::vector<wxString> recievers = { L"RTL820 T", L"Mini-YES" };
	auto recieverSelectComboBox = new wxComboBox(recieverGroup, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, recievers.size(), recievers.data());
	rgSizer->Add(recieverSelectComboBox, 0, wxEXPAND | wxLEFT | wxRIGHT, 3);
	rgSizer->AddSpacer(5);
	
	auto label = new wxStaticText(recieverGroup, wxID_ANY, L"Частота");
	rgSizer->Add(label, 0);
	rgSizer->AddSpacer(5);
	sizer->Add(recieverGroup, 0, wxALL | wxEXPAND, 5);

	SetSizer(sizer);
}


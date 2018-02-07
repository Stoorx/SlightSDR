#pragma once


#include <wx/wx.h>
#include <wx/stdpaths.h>
#include <string>
#include "global.h"

class PlayControl : public wxPanel {
public:
	PlayControl(wxWindow* parent);
};

PlayControl::PlayControl(wxWindow* parent) {
	std::wstring basePath = g_Controller->getApplicationPath();
	// Create panel
	Create(parent, wxID_ANY);

	// Add sizer
	auto sizer = new wxBoxSizer(wxHORIZONTAL);
	SetSizer(sizer);
	
	sizer->AddSpacer(5);
	// Play/pause button
	auto playPauseButton = new wxBitmapButton(this, wxID_ANY, wxBitmap(), wxDefaultPosition, wxSize(32, 32));
	sizer->Add(playPauseButton, 0, wxTOP | wxBOTTOM, 3);
	sizer->AddSpacer(3);
	// Stop button
	auto stopButton = new wxBitmapButton(this, wxID_ANY, wxBitmap(), wxDefaultPosition, wxSize(32, 32));
	sizer->Add(stopButton, 0, wxTOP | wxBOTTOM, 3);

	

}
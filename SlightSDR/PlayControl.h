#pragma once


#include <wx/wx.h>
#include <wx/stdpaths.h>
#include <string>
#include "global.h"

class PlayControl : public wxPanel {
public:
	PlayControl(wxWindow* parent);
private:
	// Play/pause button handler
	void playPauseButton_Click(wxCommandEvent& event) {
		g_Controller->Play();
	}
	void stopButton_Click(wxCommandEvent& event) {
		g_Controller->Stop();
	}
};

PlayControl::PlayControl(wxWindow* parent) {
	std::wstring basePath = g_Controller->getApplicationPath();
	// Create panel
	Create(parent, wxID_ANY);

	// Add sizer
	auto sizer = new wxGridSizer(4, 3, 3);
	SetSizer(sizer);
	
	// Play/pause button
	auto playPauseButton = new wxBitmapButton(this, wxID_ANY, wxBitmap(wxImage(basePath + L"\\resources\\icons\\play24.png", wxBITMAP_TYPE_PNG)), wxDefaultPosition);
	playPauseButton->Bind(wxEVT_BUTTON, &PlayControl::playPauseButton_Click, this);
	sizer->Add(playPauseButton, 0, wxEXPAND);
	
	// Stop button
	auto stopButton = new wxBitmapButton(this, wxID_ANY, wxBitmap(wxImage(basePath + L"\\resources\\icons\\stop24.png", wxBITMAP_TYPE_PNG)), wxDefaultPosition);
	stopButton->Bind(wxEVT_BUTTON, &PlayControl::stopButton_Click, this);
	sizer->Add(stopButton, 0, wxEXPAND);

	// Record button
	auto recordButton = new wxBitmapButton(this, wxID_ANY, wxBitmap(wxImage(basePath + L"\\resources\\icons\\record24.png", wxBITMAP_TYPE_PNG)), wxDefaultPosition);
	sizer->Add(recordButton, 0, wxEXPAND);
	
	// Mute button
	auto muteButton = new wxBitmapButton(this, wxID_ANY, wxBitmap(wxImage(basePath + L"\\resources\\icons\\mute24.png", wxBITMAP_TYPE_PNG)), wxDefaultPosition);
	sizer->Add(muteButton, 0, wxEXPAND);
}
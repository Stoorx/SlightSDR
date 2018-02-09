#pragma once

#include "config.h"
#include "IController.h"
#include "View.h"
#include "Model.h"
#include <wx/wx.h>
#include <wx/evtloop.h>
#include <wx/image.h>
#include <wx/stdpaths.h>
#include <wx/splash.h>
#include "global.h"
#include <chrono>
#include <thread>


class Controller : public wxApp, public IController {
public:
	virtual bool OnInit() override;
	virtual int OnExit() override;

	virtual const std::wstring& getApplicationPath() const override;
	virtual const IView& getView() const override;

	// Commands
	// Play
	virtual void Play() override {
		view->SetPlayStatus();
	}
	// Stop
	virtual void Stop() override {
		view->SetStopStatus();
	}
private:
	IView* view;
	IModel* model;

	std::wstring applicationPath;
};


bool Controller::OnInit() {
	// We have 
	wxEventLoopGuarantor eventLoopGuarantor;
	
	// Application name
#ifdef NIGHT_SDR
	std::wstring appName = L"SlightSDR Night";
#else
	std::wstring appName = L"SlightSDR";
#endif
	// Set names
	wxTheApp->SetAppName(appName);
	wxTheApp->SetAppDisplayName(appName);
	wxTheApp->SetVendorName(L"KryptonTech");

	// For using wxImage
	wxInitAllImageHandlers();
	
	// Base application path
	applicationPath = wxPathOnly(argv[0]);

	// Create splash
	//wxImage logoImage(applicationPath + L"\\resources\\splash.png", wxBITMAP_TYPE_PNG, wxID_ANY);

	//wxSplashScreen splash(wxBitmap(logoImage), wxSPLASH_CENTRE_ON_SCREEN | wxSPLASH_NO_TIMEOUT, 0, nullptr, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxFRAME_NO_TASKBAR);
	//wxAppConsole::Yield();
		
	wxEventLoopBase::GetActive()->Yield();
	//std::this_thread::sleep_for(std::chrono::seconds(10));
	g_Controller = this;
	
	model = new Model();
	g_Model = model;

	view = new View(this, model);
	g_View = view;
	//splash.Show(false);
	return true;
}

int Controller::OnExit() {
	delete view;
	delete model;
	return wxApp::OnExit();
}

const std::wstring& Controller::getApplicationPath() const {
	return applicationPath;
}

const IView& Controller::getView() const {
	return *view;
}


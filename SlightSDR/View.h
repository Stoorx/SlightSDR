#pragma once

#include "IView.h"
#include "MainWindow.h"
#include "IController.h"
#include "IModel.h"

class View : public IView
{
public:
	View(IController* controller, IModel* model);
	~View();

	virtual void SetPlayStatus() override {
		mainWindow->SetTitle(L"Playing!");
	}
	virtual void SetStopStatus() override {
		mainWindow->SetTitle(L"Stopped!");
	}
private:
	MainWindow* mainWindow;

	IController* _controller;
	IModel* _model;
};

View::View(IController* controller, IModel* model)
{
	_controller = controller;
	_model = model;
	mainWindow = new MainWindow();
}

View::~View()
{
	delete mainWindow;
}
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

private:
	MainWindow* mainWindow;

	IController* _controller;
	IModel* _model;
};

View::View(IController* controller, IModel* model)
{
	_controller = controller;
	_model = model;
	mainWindow = new MainWindow(this);
}

View::~View()
{
	delete mainWindow;
}
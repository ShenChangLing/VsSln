#pragma once

#include "stdafx.h"
#include "SCLRoot.h"
#include "SCLWindow.h"
#include "SCLScene.h"
#include "SCLViewport.h"
#include "SCLCamera.h"


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                      _In_opt_ HINSTANCE hPrevInstance,
                      _In_ LPWSTR lpCmdLine,
                      _In_ int nCmdShow)
{
	SCL::Root root;
	SCL::Window* window = root.createWindow("hello", -1, -1, 800, 600);

	SCL::Scene* scene = root.createScene();
	SCL::Camera* camera = scene->createCamera("Main");
	camera->setPosition(0, 5, 5);
	camera->lookat(0, 0, 0);

	SCL::Viewport* viewport = window->addViewport(camera);


	root.run();
	return 0;
}

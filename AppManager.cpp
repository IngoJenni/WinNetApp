/*
 * UserIoHandler.cpp
 *
 *  Created on: 23.08.2018
 *      Author: Ingo
 */
 
#include <iostream>
#include "AppManager.h"
#include "UserIoHandler.h"
#include "DijkstraTest.h"

using namespace std;

int main()
{
	DijkstraTest dijTest;

	dijTest.testDijkstra();


//	AppManager appManager;
//
//	appManager.go();
//
//	return appManager.getErrorState();
	return 1;
}


AppManager::AppManager()
{
	version ="0.1";
	errorState    = -1;
	userIoHandler = new UserIoHandler();
}

void AppManager::go()
{
	cout << "WinNetApp version " << version << "\n";
	errorState = userIoHandler->launch(); // Returns when appManager is finished
	cout << "Bye.\n";
}


int AppManager::getErrorState()
{
	return errorState;
}


AppManager::~AppManager()
{
	delete userIoHandler;
}


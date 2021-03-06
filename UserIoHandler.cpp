/*
 * UserIoHandler.cpp
 *
 *  Created on: 23.08.2018
 *      Author: Ingo
 */
#include <iostream>
#include <thread>
#include "UserIoHandler.h"

using namespace std;

UserIoHandler::UserIoHandler()
{
	shutdown = false;
	activeService = 0;
}

void UserIoHandler::registerService(Service *_service)
{
	services.insert(make_pair(_service->getName(), _service));
}

void UserIoHandler::userIoThread()
{
	cout << "Type 'help' for help!\n\n";
	while(!shutdown)
	{
		handleCommandPrompt();
	}
}

int UserIoHandler::launch()
{
	thread th (&UserIoHandler::userIoThread, this);
	th.join();

	return 0; // Later a proper return value can be implemented
}

void UserIoHandler::handleCommandPrompt()
{
	if(activeService == 0)
	{
		handleIoHandlerInput();
	}
	else
	{
		handleServiceInput();
	}
}

void UserIoHandler::handleIoHandlerInput()
{
	string input;
	map<string, Service*>::iterator iter;

	cout << "WinNetApp> ";
	getline(cin, input);

	if(input.find("shutdown") == 0)
	{
		shutdown = true;
	}
	else if(input.find("help") == 0)
	{
		printHelpText();
	}
	else
	{
		iter = services.find(input);
		if(iter == services.end())
		{
			cout << "Command or service '" << input << "' not availble" << endl;
		}
		else
		{
			activeService = (*iter).second;
		}
	}
}

void UserIoHandler::handleServiceInput()
{
	string input;

	cout << "WinNetApp\\" << activeService->getName() << "> ";
	getline(cin, input);

	if(input.find("return") == 0)
	{
		activeService = 0;
	}
	else if(input.find("shutdown") == 0)
	{
		shutdown = true;
	}
	else
	{
		activeService->executeCommand(input);
		if(input.find("help") == 0)
		{
			printUniversalCommands();
		}
	}
}

void UserIoHandler::printHelpText()
{
	map<string, Service*>::iterator iter;

	cout << "Available commands:" << endl;
	cout << "'help'               - display this help message" << endl;
	cout << "[service name]       - enter service submenu" << endl;

	printUniversalCommands();

	cout << endl;
	cout << "Available services:" << endl;

	for(iter = services.begin(); iter != services.end(); iter++)
	{
		cout <<"'" << (*iter).second->getName() <<"':\t" << (*iter).second->getDescription() << endl;
	}
}

void UserIoHandler::printUniversalCommands()
{
	cout << "'return'             - exit service submenu and go back to main menu." << endl;
	cout << "'shutdown'           - terminate WinNetApp" << endl;
}



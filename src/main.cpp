#include "MainWindow.h"


int main()
{
	srand(time(NULL));
	auto mainWindow = new MainWindow();
	mainWindow->run();

	return 0;
}
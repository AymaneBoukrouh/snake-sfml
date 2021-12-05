#include "includes/Config.h"
#include "includes/MainWindow.h"
#include <SFML/Graphics.hpp>


int main()
{
	srand(time(NULL));
	auto mainWindow = new MainWindow();
	mainWindow->run();

	return 0;
}
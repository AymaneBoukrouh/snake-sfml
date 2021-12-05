#include "Config.h"
#include "Block.h"
#include "Snake.h"
#include "MainWindow.h"
#include <SFML/Graphics.hpp>


using std::pair;
using std::vector;
using std::string;


int main()
{
	srand(time(NULL));
	auto mainWindow = new MainWindow();
	mainWindow->run();

	return 0;
}
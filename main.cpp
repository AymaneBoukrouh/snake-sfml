#include "includes/Config.h"
#include "includes/Block.h"
#include "includes/Snake.h"
#include "includes/MainWindow.h"
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
#include "Menu.h"
#include "FileHandler.h"
#include "WeatherEntry.h"
#include "BST.h"
#include "Vector.h"
#include <map>
#include <string>

int main() {
    BST<std::string> dateTree; //stores unique year/month keys
    std::map<std::string, WeatherLog> dataMap;

    if (!FileHandler::loadDataFiles(dateTree, dataMap)) {
        return 1; //exit if no data loaded
    }

    Menu::run(dateTree, dataMap);
    return 0;
}

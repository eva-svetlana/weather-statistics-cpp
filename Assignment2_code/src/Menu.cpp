#include "Menu.h"
#include <iomanip>
#include <cmath>

void Menu::run(BST<std::string>& tree, std::map<std::string, WeatherLog>& dataMap) {
    int option = 0;
    do {
        std::cout << "\n";
        printMenu();
        std::cout << "Enter your choice (1-5): ";
        std::cin >> option;
        switch (option) {
            case 1: showWindStats(tree, dataMap); break;
            case 2: showTempStats(tree, dataMap); break;
            case 3: showCorrelations(tree, dataMap); break;
            case 4: handleWriteToFile(tree, dataMap); break;
            case 5: std::cout << "Exiting the program.\n"; break;
            default: std::cout << "Invalid choice.\n";
        }
    } while(option != 5);
}

void Menu::printMenu() {
    std::cout << "Menu options are:\n";
    std::cout << "1. Calculate average wind speed and std dev for month and year\n";
    std::cout << "2. Calculate average temperature and std dev for each month in year\n";
    std::cout << "3. Calculate sPCC for (S_T, S_R, T_R) for a selected month for all years.\n";
    std::cout << "4. Write all stats to file\n";
    std::cout << "5. Exit the program.\n";
}

bool Menu::hasData(const WeatherLog& records, int month, int year, int opt) {
    if(records.GetSize() == 0) {
        if(opt == 1) std::cout << monthName(month) << " " << year << ": No Data\n";
        else std::cout << monthName(month) << ": No Data\n";
        return false;
    }
    return true;
}

std::string Menu::monthName(int month) {
    const std::string names[] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };
    return (month >= 1 && month <= 12) ? names[month-1] : "Invalid";
}

void Menu::showWindStats(const BST<std::string>& tree, const std::map<std::string, WeatherLog>& dataMap) {
    int year = FileHandler::promptYear();
    int month = FileHandler::promptMonth();
    WeatherLog data = getRecordsByYearMonth(tree, dataMap, year, month);
    if(!hasData(data, month, year, 1)) return;

    Vector<float> speeds = extractWindSpeeds(data);
    float avg = mean(speeds)*3.6f;
    float sd = stdev(speeds)*3.6f;
    std::cout << monthName(month) << " " << year << ": "
              << "Average wind speed: " << std::fixed << std::setprecision(1) << avg
              << " km/h, Std dev: " << sd << " km/h\n";
}

void Menu::showTempStats(const BST<std::string>& tree, const std::map<std::string, WeatherLog>& dataMap) {
    int year = FileHandler::promptYear();
    std::cout << year << "\n";
    for(int month=1; month<=12; ++month) {
        WeatherLog data = getRecordsByYearMonth(tree, dataMap, year, month);
        if(!hasData(data, month, year, 2)) continue;
        Vector<float> temps = extractTemperatures(data);
        float avgv = mean(temps);
        float sdv = stdev(temps);
        std::cout << monthName(month) << ": average: "
                  << std::fixed << std::setprecision(1) << avgv
                  << " degree C, std dev: " << sdv << "\n";
    }
}

void Menu::printCorrelation(const Vector<float>& v1, const Vector<float>& v2, const std::string& lbl) {
    try {
        double value = pearson(v1, v2);
        std::cout << lbl << ": ";
        if(std::isnan(value))
            std::cout << "NaN";
        else
            std::cout << std::fixed << std::setprecision(2) << value;
        std::cout << std::endl;
    } catch(const std::exception& e) {
        std::cout << "Error (" << lbl << "): " << e.what() << std::endl;
    }
}

void Menu::showCorrelations(const BST<std::string>& tree, const std::map<std::string, WeatherLog>& dataMap) {
    int month = FileHandler::promptMonth();
    WeatherLog data = getRecordsByMonth(tree, dataMap, month);
    if(!hasData(data, month, -1, 1)) return;

    //pairwise deletion for S_T, S_R, T_R
    Vector<float> s_t1, s_t2, s_r1, s_r2, t_r1, t_r2;
    for(int i=0;i<data.GetSize();i++) {
        float s = data[i].windSpeed, t = data[i].temperature, r = data[i].solarRadiation;
        if(!std::isnan(s) && !std::isnan(t))           { s_t1.pushBack(s); s_t2.pushBack(t); }
        if(!std::isnan(s) && !std::isnan(r) && r>=100) { s_r1.pushBack(s); s_r2.pushBack(r); }
        if(!std::isnan(t) && !std::isnan(r) && r>=100) { t_r1.pushBack(t); t_r2.pushBack(r); }
    }

    std::cout << "Sample Pearson Correlation Coefficients sPCC for " << monthName(month) << ":\n";
    printCorrelation(s_t1, s_t2, "S_T");
    printCorrelation(s_r1, s_r2, "S_R");
    printCorrelation(t_r1, t_r2, "T_R");
}

void Menu::writeMonthStats(std::ofstream& file, const BST<std::string>& tree, const std::map<std::string, WeatherLog>& dataMap, int year, int month) {
    WeatherLog data = getRecordsByYearMonth(tree, dataMap, year, month);
    if(data.GetSize() == 0) return;

    Vector<float> wind = extractWindSpeeds(data), temp = extractTemperatures(data), solar = extractSolarRadiation(data);
    float wAvg = mean(wind)*3.6f, wStdev = stdev(wind)*3.6f, wMad = 0;
    float tAvg = mean(temp), tStdev = stdev(temp), tMad = 0;
    float solarTotal = calculateTotalSolar(solar);

    //compute MAD (Mean Absolute Deviation, 1 decimal) for wind
    float wMean = mean(wind)*3.6f;
    int w_n = 0;
    for(int i=0; i<wind.GetSize(); i++) {
        if(!std::isnan(wind[i])) { wMad += std::abs(wind[i]*3.6f - wMean); w_n++; }
    }
    if(w_n>0) wMad /= w_n;

    //compute MAD for temp
    float tMean = mean(temp);
    int t_n = 0;
    for(int i=0; i<temp.GetSize(); i++) {
        if(!std::isnan(temp[i])) { tMad += std::abs(temp[i] - tMean); t_n++; }
    }
    if(t_n>0) tMad /= t_n;

    file << monthName(month) << ",";
    if(!std::isnan(wAvg))
        file << std::fixed << std::setprecision(1)
             << wAvg << "(" << wStdev << ", " << wMad << "),";
    else
        file << " ,";
    if(!std::isnan(tAvg))
        file << std::fixed << std::setprecision(1)
             << tAvg << "(" << tStdev << ", " << tMad << "),";
    else
        file << " ,";
    if(!std::isnan(solarTotal))
        file << std::fixed << std::setprecision(1) << solarTotal;
    else
        file << " ";
    file << "\n";
}

void Menu::writeAllStats(const BST<std::string>& tree, const std::map<std::string, WeatherLog>& dataMap, const std::string& filename, int year) {
    std::ofstream file(filename);
    if(!file) {
        std::cerr << "Error opening output file: " << filename << std::endl;
        return;
    }
    file << year << "\n";
    bool any = false;
    for(int month=1; month<=12; ++month) {
        if(getRecordsByYearMonth(tree, dataMap, year, month).GetSize()>0) {
            writeMonthStats(file, tree, dataMap, year, month);
            any = true;
        }
    }
    if(!any) file << "No Data";
}

void Menu::handleWriteToFile(const BST<std::string>& tree, const std::map<std::string, WeatherLog>& dataMap) {
    int year = FileHandler::promptYear();
    writeAllStats(tree, dataMap, "WindTempSolar.csv", year);
    std::cout << "Data written to WindTempSolar.csv\n";
}

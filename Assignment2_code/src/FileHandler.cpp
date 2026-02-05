
#include "FileHandler.h"
#include <fstream>
#include <sstream>
#include <cmath>
#include <stdexcept>

//reads user input in day/month/year format into a Date object
std::istream& FileHandler::readDate(std::istream& is, Date& date) {
    int day, month, year;
    char slash;
    is >> day >> slash >> month >> slash >> year;
    if (slash != '/') {
        is.setstate(std::ios::failbit);
        return is;
    }
    try {
        date.SetDay(day);
        date.SetMonth(month);
        date.SetYear(year);
    } catch (...) {
        is.setstate(std::ios::failbit);
    }
    return is;
}

//outputs Date in day/month/year
std::ostream& FileHandler::printDate(std::ostream& os, const Date& d) {
    os << (d.GetDay() < 10 ? "0" : "") << d.GetDay() << "/"
       << (d.GetMonth() < 10 ? "0" : "") << d.GetMonth() << "/"
       << d.GetYear();
    return os;
}

//reads time in hh:mm format into MyTime object
std::istream& FileHandler::readTime(std::istream& is, MyTime& t) {
    int hour, minute;
    char colon;
    is >> hour >> colon >> minute;
    if (colon != ':') {
        is.setstate(std::ios::failbit);
        return is;
    }
    try {
        t.SetHour(hour);
        t.SetMinute(minute);
    } catch (...) {
        is.setstate(std::ios::failbit);
    }
    return is;
}

//outputs time in hh:mm format
std::ostream& FileHandler::printTime(std::ostream& os, const MyTime& t) {
    os << (t.GetHour() < 10 ? "0" : "") << t.GetHour() << ":"
       << (t.GetMinute() < 10 ? "0" : "") << t.GetMinute();
    return os;
}

//prompt user for a year enter (with repeat on invalid entry)
int FileHandler::promptYear() {
    int year;
    while (true) {
        std::cout << "Enter year: ";
        std::cin >> year;
        if (std::cin.fail() || year < 1800 || year > 2100) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid year, please try again." << std::endl;
        } else {
            return year;
        }
    }
}

//prompt user for month (from 1-12) with validation
int FileHandler::promptMonth() {
    int month;
    while (true) {
        std::cout << "Enter month (1-12): ";
        std::cin >> month;
        if (std::cin.fail() || month < 1 || month > 12) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid month, please try again." << std::endl;
        } else {
            return month;
        }
    }
}

//loads all files listed in data/data_source.txt into structures
bool FileHandler::loadDataFiles(BST<std::string>& dateTree, std::map<std::string, WeatherLog>& dataMap) {
    std::ifstream srcList("data/data_source.txt");
    if (!srcList.is_open()) {
        std::cerr << "Could not open data_source.txt" << std::endl;
        return false;
    }
    std::string filename;
    bool loaded = false;
    while (std::getline(srcList, filename)) {
        if (filename.empty()) continue;
        if (parseCSV("data/" + filename, dateTree, dataMap)) loaded = true;
    }
    return loaded;
}

//parses one CSV file for weather data, populates BST and map
bool FileHandler::parseCSV(const std::string& filename, BST<std::string>& dateTree, std::map<std::string, WeatherLog>& dataMap) {
    std::ifstream file(filename);
    if(!file.is_open()) {
        std::cerr << "Could not open: " << filename << std::endl;
        return false;
    }
    std::string header;
    if (!std::getline(file, header)) {
        std::cerr << "Empty CSV or unreadable: " << filename << std::endl;
        return false;
    }
    std::map<std::string, int> colMap = buildColumnMap(header);
    std::string line;
    while (std::getline(file, line)) {
        processCSVLine(line, colMap, dateTree, dataMap);
    }
    return true;
}

//build map of column name to index
std::map<std::string, int> FileHandler::buildColumnMap(const std::string& headerLine) {
    std::map<std::string, int> colMap;
    std::stringstream ss(headerLine);
    std::string col;
    int idx = 0;
    while (std::getline(ss, col, ',')) {
        colMap[col] = idx++;
    }
    return colMap;
}

//process one CSV line for weather data
void FileHandler::processCSVLine(const std::string& line, const std::map<std::string, int>& colMap,
                                 BST<std::string>& dateTree, std::map<std::string, WeatherLog>& dataMap) {
    std::stringstream ss(line);
    std::string cell;
    Vector<std::string> fields;
    while (std::getline(ss, cell, ',')) {
        fields.pushBack(cell);
    }

    //extract and parse fields.
    //Expects day/month/year for date, hh:mm for time.
    try {
        std::string dateTimeStr = fields[colMap.at("WAST")];
        // If CSV entry is "15/07/2025 09:45"
        std::stringstream dts(dateTimeStr);
        std::string datePart, timePart;
        std::getline(dts, datePart, ' ');
        std::getline(dts, timePart);

        Date date = parseDate(datePart);
        MyTime time = parseTime(timePart);

        float wind = fields[colMap.at("S")].empty() ? NAN : std::stof(fields[colMap.at("S")]);
        float temp = fields[colMap.at("T")].empty() ? NAN : std::stof(fields[colMap.at("T")]);
        float solar = fields[colMap.at("SR")].empty() ? NAN : std::stof(fields[colMap.at("SR")]);

        WeatherEntry w {date, time, wind, temp, solar};
        //key is year month as string
        std::string key = std::to_string(date.GetYear()) + "-" + (date.GetMonth() < 10 ? "0" : "") + std::to_string(date.GetMonth());

        dataMap[key].pushBack(w);
        if (!dateTree.search(key)) {
            dateTree.insert(key);
        }
    } catch (...) {
        //skip any problematic lines
    }
}

//create Date object from string in day/month/year
Date FileHandler::parseDate(const std::string& dateStr) {
    int day, month, year;
    char slash;
    std::stringstream ss(dateStr);
    ss >> day >> slash >> month >> slash >> year;
    if (slash != '/') throw std::runtime_error("Invalid date format (expected /)");
    Date d;
    d.SetDay(day);
    d.SetMonth(month);
    d.SetYear(year);
    return d;
}

//create MyTime object from string in hh:mm
MyTime FileHandler::parseTime(const std::string& timeStr) {
    int hour, minute;
    char colon;
    std::stringstream ss(timeStr);
    ss >> hour >> colon >> minute;
    if (colon != ':') throw std::runtime_error("Invalid time format (expected :)");
    MyTime t;
    t.SetHour(hour);
    t.SetMinute(minute);
    return t;
}

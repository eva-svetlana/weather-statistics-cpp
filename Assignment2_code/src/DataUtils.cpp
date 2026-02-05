#include "DataUtils.h"
#include "Vector.h"
#include <cmath>
#include <sstream>

WeatherLog getRecordsByYearMonth(const BST<std::string>& tree, const std::map<std::string, WeatherLog>& dataMap, int year, int month) {
    //to gather all BST keys
    Vector<std::string> keys;
    tree.InOrder([](const std::string& s){});
    //compose key as year/month
    std::stringstream keyBuilder;
    keyBuilder << year << "-";
    if(month < 10) keyBuilder << "0";
    keyBuilder << month;
    std::string key = keyBuilder.str();

    auto it = dataMap.find(key);
    if(it != dataMap.end()) return it->second;
    return WeatherLog();
}

WeatherLog getRecordsByMonth(const BST<std::string>& tree, const std::map<std::string, WeatherLog>& dataMap, int month) {
    Vector<std::string> keys;
    tree.InOrder([](const std::string& s){});
    for(const auto& pair : dataMap) {
        std::string key = pair.first;
        int foundMonth = std::stoi(key.substr(5,2));
        if(foundMonth == month) return pair.second;
    }
    return WeatherLog();
}

Vector<float> extractWindSpeeds(const WeatherLog& records) {
    Vector<float> wind;
    for(int i=0; i<records.GetSize(); i++) wind.pushBack(records[i].windSpeed);
    return wind;
}
Vector<float> extractTemperatures(const WeatherLog& records) {
    Vector<float> temp;
    for(int i=0; i<records.GetSize(); i++) temp.pushBack(records[i].temperature);
    return temp;
}
Vector<float> extractSolarRadiation(const WeatherLog& records) {
    Vector<float> solar;
    for(int i=0; i<records.GetSize(); i++) {
        float sr = records[i].solarRadiation;
        if(!std::isnan(sr) && sr >= 100) solar.pushBack(sr);
    }
    return solar;
}
float calculateTotalSolar(const Vector<float>& solarVals) {
    float total = 0.0f;
    for(int i=0; i<solarVals.GetSize(); i++)
        total += solarVals[i] * (10.0f / 60.0f) / 1000.0f; //to convert Wh to kWh
    return std::round(total*10.0f)/10.0f;
}

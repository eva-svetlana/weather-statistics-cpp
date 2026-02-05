/**
 * @file DataUtils.h
 * @author Svetlana Alkhasova
 * @date 18/07/25
 * @version 1.0
 * @brief Utility functions for filtering, extracting, and manipulating weather data collections.
 */

#ifndef DATAUTILS_H
#define DATAUTILS_H

#include "WeatherEntry.h"
#include "BST.h"
#include <map>
#include <string>

/**
* @brief Get all records for a specific year/month combination.
*
* Returns all weather records for a given year and month.
* The key is formatted as year month.
*
* @param tree Binary Search Tree holding all date keys as strings.
* @param dataMap Map from key (string) to WeatherLog (vector of entries).
* @param year  Year to filter (2016).
* @param month Month to filter (1-12).
* @return WeatherLog containing the records for the specified year/month.
*/
WeatherLog getRecordsByYearMonth(const BST<std::string>& tree, const std::map<std::string, WeatherLog>& dataMap, int year, int month);

/**
* @brief Get all records for a specific month across all years.
*
* Combines weather records for the given month (all May's),
* searching over all available years in the tree/map.
*
* @param tree BST of available year-month keys (as year month strings).
* @param dataMap Map from key (string) to WeatherLog.
* @param month  Month to filter (1-12).
* @return WeatherLog containing all records for the given month, all years.
*/
WeatherLog getRecordsByMonth(const BST<std::string>& tree, const std::map<std::string, WeatherLog>& dataMap, int month);

/**
* @brief Extracts wind speeds from a set of weather records.
*
* Iterates over the WeatherLog and returns a vector containing
* only wind speed values.
*
* @param records WeatherLog of entries to process.
* @return Vector<float> of wind speeds.
*/
Vector<float> extractWindSpeeds(const WeatherLog& records);

/**
* @brief Extracts air temperatures from weather records.
*
* Iterates through the WeatherLog and builds a vector of the
* temperature values found.
*
* @param records WeatherLog to extract from.
* @return Vector<float> of temperatures.
*/
Vector<float> extractTemperatures(const WeatherLog& records);

/**
* @brief Extracts valid solar radiation values >= 100 from records
*
* Includes only solar readings that are 100 or greater.
*
* @param records WeatherLog to process.
* @return Vector<float> of valid solar radiation readings.
*/
Vector<float> extractSolarRadiation(const WeatherLog& records);

/**
* @brief sums all solar radiation values in a vector and converts to kWh
*
* Adds up all values, converts the sum to kilowatt-hours, and rounds
* the result to 1 decimal place.
*
* @param solarVals Vector of solar readings.
* @return Total radiation in kWh (float, rounded).
*/
float calculateTotalSolar(const Vector<float>& solarVals);

#endif // DATAUTILS_H

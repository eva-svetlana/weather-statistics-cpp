/**
 * @file WeatherEntry.h
 * @author Svetlana Alkhasova
 * @date 18/07/25
 * @version 3.0
 * @brief A single weather measurement and a type alias for logs of weather data.
 *
 * This file sets up a struct for one line of weather readings (date, time, wind, temperature, solar)
 * and gives a shortcut for making a list of these with Vector class.
 */

#ifndef WEATHERENTRY_H
#define WEATHERENTRY_H


#include "Date.h"
#include "MyTime.h"
#include "Vector.h"

/**
* @struct WeatherEntry
* @brief Holds one record of weather readings (from a single moment in time).
*
* This struct is just one set of data: date, time, wind speed, temperature, and solar power.
* All together, it’s one "row" from a weather csv
*
**/
struct WeatherEntry {
    Date date;    ///< Date for the measurement
    MyTime time;///< Time of the measurement
    float windSpeed;  ///< Wind speed (km/h)
    float temperature; ///< Temperature  C
    float solarRadiation;///< Solar radiation (W/m^2)
};

/**
* @typedef WeatherLog
* @brief A vector of WeatherEntry records, used for storing lots of readings together.
*
* Makes it easier to talk about a full group of entries from a single month or year.
*
**/
typedef Vector<WeatherEntry> WeatherLog;

#endif // WEATHERENTRY_H

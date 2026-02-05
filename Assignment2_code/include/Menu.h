/**
 * @file Menu.h
 * @author Svetlana Alkhasova
 * @date 18/07/25
 * @version 2.1
 * @brief Defines menu presentation and user interaction logic for the Weather App.
 *
 * Contains static methods for running the main menu, processing user selections, and
 * displaying or saving weather statistics.
 */

#ifndef MENU_H
#define MENU_H

#include "FileHandler.h"
#include "WeatherEntry.h"
#include "Vector.h"
#include "Statistics.h"
#include "DataUtils.h"
#include "BST.h"
#include <map>
#include <string>
#include <iostream>
#include <fstream>


    /**
     * @class Menu
     * @brief Static utility class for main program menu and user interaction.
     *
     * Provides all functions related to presenting the menu, handling user choices,
     * displaying calculated weather statistics, and writing summaries to output files.
     * All functions are static and Menu is not meant to be instantiated.
     *
     * @author Svetlana Alkhasova
     * @version 2.1
     * @date 18/07/25
     */
class Menu {
public:
        /**
         * @brief Runs the main loop for the menu/user interface.
         * @param tree BST holding all year-month keys (as strings).
         * @param dataMap Map from string key to WeatherLog, holding all records.
         *
         * Presents the menu, receives user choices, and calls the appropriate functions
         * to display stats or export data, looping until the user exits.
         */
    static void run(BST<std::string>& tree, std::map<std::string, WeatherLog>& dataMap);

        /**
         * @brief Prints the main program menu for user selection.
         */
    static void printMenu();

        /**
         * @brief Displays wind statistics (average and std dev) for user-selected month/year.
         * @param tree BST of valid year-month keys.
         * @param dataMap Source map for weather logs.
         */
    static void showWindStats(const BST<std::string>& tree, const std::map<std::string, WeatherLog>& dataMap);

        /**
         * @brief Displays temperature statistics for each month in a user-specified year.
         * @param tree BST of valid year-month keys.
         * @param dataMap Map of weather logs keyed by year/month.
         */
    static void showTempStats(const BST<std::string>& tree, const std::map<std::string, WeatherLog>& dataMap);

        /**
         * @brief Calculates and displays Pearson correlations between parameters for given month.
         * @param tree BST of available keys.
         * @param dataMap WeatherLog data map.
         */
    static void showCorrelations(const BST<std::string>& tree, const std::map<std::string, WeatherLog>& dataMap);

        /**
         * @brief Writes statistics for a single month to the supplied file.
         * @param file Output file stream (already open and ready).
         * @param tree BST of year/month keys.
         * @param dataMap Map of records.
         * @param year Year as integer.
         * @param month Month number (1-12).
         */
    static void writeMonthStats(std::ofstream& file, const BST<std::string>& tree, const std::map<std::string, WeatherLog>& dataMap, int year, int month);

        /**
         * @brief Writes statistics for all months of a specified year to a file.
         * @param tree BST of keys.
         * @param dataMap WeatherLog records.
         * @param filename Output file name.
         * @param year The selected year.
         */
    static void writeAllStats(const BST<std::string>& tree, const std::map<std::string, WeatherLog>& dataMap, const std::string& filename, int year);

        /**
         * @brief Handles user interaction and calls the writetofile operation.
         * @param tree BST of available keys.
         * @param dataMap WeatherLog map
         *
         * prompts user for year and triggers output of statistics to CSV file.
         */
    static void handleWriteToFile(const BST<std::string>& tree, const std::map<std::string, WeatherLog>& dataMap);

        /**
         * @brief checks if records exist for a particular month/year or option.
         * @param records WeatherLog as vector of entries.
         * @param month Month number (1-12).
         * @param year  Year as integer.
         * @param option Used to change test logic for different menu actions.
         * @return True if records found for that selection, false otherwise.
         */
    static bool hasData(const WeatherLog& records, int month, int year, int option);

        /**
         * @brief Returns the name of a month given its number.
         * @param month Integer month (1 for January to 12 for December).
         * @return String name of the month.
         */
    static std::string monthName(int month);

        /**
         * @brief Prints the correlation result between two parameter vectors.
         * @param v1 First data vector.
         * @param v2 Second data vector.
         * @param label Label for correlation type (S_T, S_R, R_T).
         */
    static void printCorrelation(const Vector<float>& v1, const Vector<float>& v2, const std::string& label);
};


#endif // MENU_H

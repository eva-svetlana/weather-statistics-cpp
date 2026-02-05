/**
 * @file FileHandler.h
 * @author Svetlana Alkhasova
 * @date 18/07/25
 * @version 1.0
 * @brief Handles CSV file input and output, user input prompts, and parsing of weather data fields.
 *
 * This class provides static utility functions for:
 *   - Reading and parsing weather data files (CSV) into data structures
 *   - Handling user prompts for year/month input
 *   - Overloaded operators and helpers for Date and MyTime I/O
 **/

#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "Date.h"
#include "MyTime.h"
#include "Vector.h"
#include "WeatherEntry.h"
#include "BST.h"
#include <string>
#include <map>
#include <iostream>


    /**
     * @class FileHandler
     * @brief Static utility class for file and stream operations, user input, and parsing.
     *
     * All functions are static and designed to help with reading/writing weather data,
     * inputting dates/times, and parsing CSV fields into the project’s main structures.
     *
     * This class is not intended to be instantiated.
     *
     * @author Svetlana Alkhasova
     * @version 2.0
     * @date 19/07/25
     **/
class FileHandler {
public:

        /**
         * @brief Reads a Date from an input stream in day/month/year format.
         * @param is Input stream to read from.
         * @param date Date object to store result in.
         * @return Reference to the input stream is.
         */
    static std::istream& readDate(std::istream& is, Date& date);

        /**
         * @brief Prints a Date to an output stream as day/month/year
         * @param os Output stream.
         * @param d Date object to print.
         * @return Reference to the output stream (os).
         */
    static std::ostream& printDate(std::ostream& os, const Date& d);

        /**
         * @brief Reads a MyTime (HH:MM) from an input stream.
         * @param is Input stream.
         * @param t MyTime object to store result.
         * @return Reference to the input stream (is).
         */
    static std::istream& readTime(std::istream& is, MyTime& t);

        /**
         * @brief Prints a MyTime to an output stream as HH:MM.
         * @param os Output stream.
         * @param t MyTime object to print.
         * @return Reference to the output stream (os).
         */
    static std::ostream& printTime(std::ostream& os, const MyTime& t);

        /**
         * @brief Prompts the user for a year, with validation.
         * @return Valid year (integer).
         */
    static int promptYear();

        /**
         * @brief Prompts the user for a month (1-12), with validation.
         * @return Valid month number (integer).
         */
    static int promptMonth();

        /**
         * @brief Loads weather data files into the BST and dataMap.
         *
         * Reads all relevant CSV files as specified by the assignment,
         * parsing each and populating the BST and map structures.
         *
         * @param dateTree BST to store date keys.
         * @param dataMap Map from date key to WeatherLog.
         * @return True on success, false on file read error.
         *
         * @pre Data files must exist in the expected location.
         */
    static bool loadDataFiles(BST<std::string>& dateTree, std::map<std::string, WeatherLog>& dataMap);

        /**
         * @brief Parses a single CSV file into the BST and dataMap.
         * @param filename Path to the CSV file.
         * @param dateTree BST to store extracted date keys.
         * @param dataMap Map from date key to WeatherLog.
         * @return True if file successfully read, false otherwise.
         */
    static bool parseCSV(const std::string& filename, BST<std::string>& dateTree, std::map<std::string, WeatherLog>& dataMap);

        /**
         * @brief Builds a column name-to-index map from a CSV header line.
         * @param headerLine The header string, comma separated.
         * @return Map from column name to column index.
         */
    static std::map<std::string, int> buildColumnMap(const std::string& headerLine);

        /**
         * @brief Processes a line from a CSV file and adds entry to data structures.
         *
         * This helper parses the line, extracts fields, constructs a WeatherEntry,
         * and updates the BST and dataMap as required.
         *
         * @param line A single non-header line from the CSV.
         * @param colMap Map from column names to indices (from `buildColumnMap`).
         * @param dateTree BST to update (if new date key is found).
         * @param dataMap Map from key to WeatherLog to update.
         */
    static void processCSVLine(const std::string& line, const std::map<std::string, int>& colMap,
                               BST<std::string>& dateTree, std::map<std::string, WeatherLog>& dataMap);

        /**
         * @brief Parses a Date from a combined date-time string.
         * @param dateTimeStr String in combined day/moth/year hh:mm or similar format.
         * @return Date object with parsed day, month, year values.
         */
    static Date parseDate(const std::string& dateTimeStr);

        /**
         * @brief Parses a MyTime from a combined date-time string.
         * @param dateTimeStr String in combined day/moth/year hh:mm or similar format.
         * @return MyTime object with parsed hour and minute values.
         */
    static MyTime parseTime(const std::string& dateTimeStr);
};


#endif // FILEHANDLER_H

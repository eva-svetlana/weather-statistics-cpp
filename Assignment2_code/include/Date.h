/**
 * @file Date.h
 * @author Svetlana Alkhasova
 * @date 18/07/25
 *
 * Provides getter and setter methods with basic validation. Used for representing
 * and manipulating simple date values in weather records and other parts of the project.
 * @version 2.0
 * @brief Class representing a basic calendar date with day, month, and year.
 *
 */

#ifndef DATE_H
#define DATE_H

/**
* @class Date
* @brief Represents a calendar date (day/month/year).
*
* Provides accessors (getters) and mutators (setters) for each date component,
* with simple validation to ensure day, month, and year are in a valid range.
**/
class Date {
public:

    /**
    * @brief Default constructor. Initializes to an empty or zero date.
    */
    Date();

    /**
    * @brief Gets the day component.
    * @return Day of month (1-31).
    */
    int GetDay() const;

    /**
    * @brief Gets the month component.
    * @return Month number (1-12).
    */
    int GetMonth() const;

    /**
    * @brief Gets the year component.
    * @return Year
    */
    int GetYear() const;


    /**
    * @brief Sets the day component. Range-checked.
    * @param day Day of the month (should be 1-31).
    */
    void SetDay(int day);

    /**
    * @brief Sets the month component. Range-checked.
    * @param month Month number (should be 1-12).
    */
    void SetMonth(int month);

    /**
    * @brief Sets the year component.
    * @param year Full year
    **/
    void SetYear(int year);

private:
    int day;  ///< Day of the month
    int month;///< Month number (1-12)
    int year; ///< Year
};

#endif // DATE_H

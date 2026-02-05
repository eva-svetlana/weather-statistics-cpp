/**
 * @file MyTime.h
 * @author Svetlana Alkhasova
 * @date 18/07/25
 * @version 2.0
 * @brief Class representing time as hour and minute with basic accessors and validation.
 *
 * Provides getter (accessor) and setter (mutator) functions for the hour and minute fields,
 * with range validation for typical time of day values.
 */

#ifndef MYTIME_H
#define MYTIME_H

    /**
     * @class MyTime
     * @brief Encapsulates a time as hour and minute.
     *
     * Provides access and modification functions for hour and minute, with range checks:
     * Hour:   0-23
     * Minute: 0-59
     *
     *
     * @author Svetlana Alkhasova
     * @version 2.0
     * @date 18/07/25
     */
class MyTime {
public:
        /**
         * @brief Default constructor. Initializes to 0:0 (midnight).
         */
    MyTime();

        /**
         * @brief Gets the hour component.
         * @return Hour of the day (0-23).
         */
    int GetHour() const;

        /**
         * @brief Gets the minute component.
         * @return Minute of the hour (0-59).
         */
    int GetMinute() const;

        /**
         * @brief Sets the hour. Checks for valid range.
         * @param hour Hour value (should be 0-23).
         */
    void SetHour(int hour);

        /**
         * @brief Sets the minute. Checks for valid range.
         * @param minute Minute value (should be 0-59).
         */
    void SetMinute(int minute);

private:
    int hour; ///< Hour of the day (0-23)
    int minute; ///< Minute of the hour (0-59)
};

#endif // MYTIME_H

/**
 * @file Statistics.h
 * @author Svetlana Alkhasova
 * @date 18/07/25
 * @version 2.0
 * @brief Some basic statistics functions for working with vectors in this assignment.
 *
 * Here are helpers for mean, standard deviation, Pearson correlation, and rounding.
 * All of these skip NaN values so they work okay with incomplete data.
 */

#ifndef STATISTICS_H
#define STATISTICS_H

#include "Vector.h"
#include <cmath>
#include <stdexcept>


    /**
     * @brief Rounds a value to n decimal places.
     *
     * Pass in a number and how many decimals you want, and it does normal rounding.
     * If your value is NaN, you'll get back NaN.
     *
     * @tparam T Any numeric type (like float, double).
     * @param val The value to round.
     * @param n Number of decimal places.
     * @return Rounded value, or NaN if input is NaN.
     */
template<typename T>
T RoundVal(T val, int n) {
    if(std::isnan(val)) return NAN;
    T factor = std::pow(10.0, n);
    return std::round(val * factor) / factor;
}


    /**
     * @brief Finds the mean (average) of all the real (non-NaN) values in your vector.
     *
     * Loops through the numbers and divides by how many were valid (not NaN).
     * Gives NaN if the vector is empty or totally full of NaNs.
     *
     * @tparam T Numeric type in your vector (probably float).
     * @param data Vector of values.
     * @return The average, or NaN if no valid values.
     */
template<typename T>
float mean(const Vector<T>& data) {
    float sum = 0.0f; int n = 0;
    for(int i=0;i<data.GetSize();i++) {
        float v = data[i];
        if(!std::isnan(v)) { sum += v; n++; }
    }
    return n > 0 ? sum/n : NAN;
}


    /**
     * @brief Computes the sample standard deviation for your vector (skips NaN values).
     *
     * Useful for showing the "spread" of your data.
     * Returns NaN if there are fewer than 2 valid numbers.
     *
     * @tparam T Numeric type in the vector.
     * @param data Vector of numbers.
     * @return Standard deviation, or NaN if not enough data.
     */
template<typename T>
float stdev(const Vector<T>& data) {
    int n = 0; float avg = mean(data), sum2 = 0.0f;
    if(std::isnan(avg)) return NAN;
    for(int i=0;i<data.GetSize();i++) {
        float v = data[i];
        if(!std::isnan(v)) { sum2 += (v - avg)*(v - avg); n++; }
    }
    return (n<=1) ? NAN : std::sqrt(sum2/(n-1));
}


    /**
     * @brief Calculates Pearson correlation coefficient between two vectors.
     *
     * Measures how closely the two datasets change together (from -1 to 1).
     * Any value that's NaN in either vector will be ignored for the calculation.
     * Throws an invalid_argument if the vectors are different lengths or empty.
     * Returns NaN if there aren't enough valid pairs to calculate, and rounds the result to two decimals.
     *
     * @tparam T Numeric type (float).
     * @param x First vector.
     * @param y Second vector.
     * @return Correlation coefficient (rounded to 2 decimals), or NaN/0 for special cases.
     * @throws std::invalid_argument if vector sizes don't match.
     */
template<typename T>
float pearson(const Vector<T>& x, const Vector<T>& y) {
    if(x.GetSize() != y.GetSize() || x.GetSize() == 0)
        throw std::invalid_argument("Vector dimensions mismatch");
    float sumX=0, sumY=0, sumXY=0, sumX2=0, sumY2=0;
    int n=0;
    for(int i=0;i<x.GetSize();i++) {
        float xv=x[i], yv=y[i];
        if(std::isnan(xv) || std::isnan(yv)) continue;
        sumX += xv;
        sumY += yv;
        sumXY += xv * yv;
        sumX2 += xv * xv;
        sumY2 += yv * yv;
        n++;
    }
    if(n < 2) return NAN;
    float num = sumXY - (sumX*sumY)/n;
    float denom = std::sqrt((sumX2-sumX*sumX/n)*(sumY2-sumY*sumY/n));
    return denom == 0 ? 0.0f : RoundVal(num/denom, 2);
}

#endif // STATISTICS_H

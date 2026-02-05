# Weather Statistics Analysis (C++)

## Description
This is an individual university project developed in C++ that analyses weather data
(wind speed, temperature, and solar radiation) from multiple CSV files.

The program provides statistical analysis including averages, standard deviation,
mean absolute deviation, and Pearson correlation coefficients.

## Features
- Interactive menu-driven console application
- Monthly and yearly statistical analysis
- Pearson correlation coefficient calculation
- CSV data import and export
- Robust input validation (no crashes on invalid input)
- Graceful handling of missing data ("No Data")

## Technologies
- C++
- STL (encapsulated in custom classes)
- CSV file processing
- Doxygen documentation

## Program Menu
1. Average wind speed and standard deviation (selected month/year)
2. Average temperature and standard deviation (yearly)
3. Pearson correlation coefficients (monthly)
4. Export statistics to CSV
5. Exit program

## Documentation
- Doxygen configuration is provided in `docs/doxygen/Doxyfile`
- Evaluation summary and limitations are available in `docs/evaluation.md`

## Limitations
- Exported CSV file overwrites existing data
- Optimized for small to medium datasets
- Terminal-based interface only

## Author
Svetlana Alkhasova  
Individual university project (July 2025)

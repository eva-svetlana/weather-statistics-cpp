EVALUATION SUMMARY

What works:
- The program compiles and runs without any errors or warnings.
- It loads the required data source and all the CSV files listed in data/data_source.txt file.
- The main menu displays 5 menu options and responds to whatever the user types in.
- Program handles invalid menu, month, and year input, it prompts user to repeat, does not crash.
- All the menu options do what they are supposed to:
    - Option 1: Calculates and shows the average wind speed and standard deviation for any month and year user selected.
    - Option 2: Shows the average temperature and standard deviation for each month in the year user ask for.
    - Option 3: Calculates the Pearson correlation coefficients sPCC (S_T, S_R, T_R) for a chosen month, and it shows two decimal places like in the requirements.
    - Option 4: Outputs all the statistics to the CSV file in the format required, with mad included.
    - Option 5: Quits the program, exiting.
- If user enters anything wrong (like letters instead of numbers, or a month out of range), the program provides warning and asks user again to repeat, it never crashes.
- When there is no data for a certain month or year, it says “No Data” instead of giving an error.
- Writing stats to file always works and the CSV output looks right each time.
- All STL containers are wrapped inside my own classes (encapsulated), except std::map which we were allowed to use.
- I didn’t notice any runtime errors or crashes during all my testing.

What does not work or limitations:
- If user use Option 4 to write stats, it always overwrites the existing "WindTempSolar.csv" file, there is no warning, so user could lose old data if user is not careful.
- If user try to use the program on a really big weather dataset, it might take a lot longer to start up.
- The program assumes all the CSV files it reads are mostly in the correct format. If a file is really broken or mixed up, the program may not handle it perfectly.
- User can only import and export data in the specific CSV format, no support for other file types.
- There is no web or graphical interface, everything happens in the terminal window only.

Malware scan declaration:
- I checked my entire submission folder, including all source code and extra files, for viruses and malware on 20 July 2025.
- I used https://www.virustotal.com to perform malware scanning.
- No malware, viruses, or anything suspicious was found at the time I submitted this assignment.

Declaration completed by: Alkhasova Svetlana 34899426
Date: 20 July 2025
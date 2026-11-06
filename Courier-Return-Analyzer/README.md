# Courier Return-to-Sender Analyzer (CAP455 - CA1)

Author: Priyanshu Kumar | Reg No: [YOUR REG NO] | Roll No: [YOUR ROLL NO]

Menu-driven C++ console app that records parcels returned to sender and analyses
return reasons. CA1 scope: in-memory Create & Read with validation and no duplicate IDs.

## Build and run
    g++ -std=c++11 -Wall -Wextra src/main.cpp -o main
    ./main                      (Windows: .\main)
    ./main < tests/test_input.txt   (scripted demo run)

## Features (CA1)
- Register returned parcel (unique positive parcel ID, full field validation)
- Display all, search by ID, total count
- Return-reason analysis (count, percentage, most common reason)
- Concepts: static, inline, friend, array of objects, object pointer, this, std::string

## Layout
/docs   proposal report   /src   main.cpp   /data   sample data (CA2+)   /tests   test input and sample output

#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <iomanip>
#include <ctime>
#include "Hash.h"
#include "Tree.h"
using namespace std;

int main() {
    clock_t runTime = clock();
    ifstream reviewFile("amazon_reviews.csv");
    set<string> categories;
    Hash table;
<<<<<<< HEAD
    FiveAryTree tree;
=======
>>>>>>> eee3d41ba0d3736e9f482053e68e73b60955098a
    int choice;
    cout << "What data structure would you like to use today?" << endl;
    cout << "1. Hash Table" << endl << "2. 5-ary tree" << endl;
    cin >> choice;
    clock_t insertTime;
    if (reviewFile.is_open()) {
        runTime = clock();
        string line;
        getline(reviewFile, line);

        while (getline(reviewFile, line)) {
            istringstream stream(line);
            string toss;
            string name;
            string category;
            string tempRate;
            double rating = 0;


            char first = line.at(0);
            char second = '"';
            if (first == second) {
                getline(stream, toss, '"'); //toss brand
                getline(stream, name, '"'); // keep item name, uses a dif delimeter because name can have commas
                getline(stream, toss, ','); //toss brand
                getline(stream, category, ','); //keep category
                getline(stream, tempRate, ','); //keep rating
                rating = stod(tempRate);
            }
            else {
                getline(stream, name, ','); // keep item name, uses a dif delimeter because name can have commas
                getline(stream, category, ','); //keep category
                getline(stream, tempRate, ','); //keep rating
                rating = stod(tempRate);
            }

            categories.insert(category); // this was used to test data reading
            //add insert method calls here
            switch (choice) {
            case 1:
                table.UpdateCategory(category, name, rating);
                insertTime = clock() - runTime;
                break;
            case 2:
                //insert table insert
<<<<<<< HEAD
                tree.Insert(category, name, rating)
=======
>>>>>>> eee3d41ba0d3736e9f482053e68e73b60955098a
                int insertTime = clock() - runTime;
            }
        }

    }
    else {
        cout << "error reading file :(" << endl;
    }
    //now that data is in structures, which structure do we use?

    cout << "Please select the category number you would like to search" << endl;
    int i = 1;
    for (auto iter = categories.begin(); iter != categories.end(); iter++) {
        cout << i << ": " << *iter << endl;
        i++;
    }
    int search;
    cin >> search;
    string searchFor = "";
    auto iter = categories.begin();
    i = 0;
    for (auto iter = categories.begin(); iter != categories.end(); iter++) {
        i++;
        if (i == search) {
            searchFor = *iter;
        }
    }
    //cout << searchFor << endl;
    switch (choice) {
    case 1:
        //hast table
        runTime = clock(); //start of searching
        //search functions
        table.PrintHighestLowestForCategory(searchFor);
        runTime = clock() - runTime;
        cout << "It took a hash table " << (float)runTime / CLOCKS_PER_SEC << " seconds to search and " << (float)insertTime / CLOCKS_PER_SEC << " seconds to insert!" << endl;
        break;
    case 2:
        //5-ary
        map<string, pair<string, double>> items{};
        runTime = clock(); //start of searching
        //search functions
        items = tree.HighAndLowRated(searchFor);
        runTime = clock() - runTime;
<<<<<<< HEAD
        cout << searchFor << "\n" << "Highest: " << items["Max"].first << ", Rating: " << items["Max"].second << "\n";
        cout << "Lowest: " << items["Min"].first << ", Rating: " << items["Min"].second << "\n";
=======
>>>>>>> eee3d41ba0d3736e9f482053e68e73b60955098a
        cout << "It took a 5-ary tree " << (float)runTime / CLOCKS_PER_SEC << " seconds to search and " << (float)insertTime / CLOCKS_PER_SEC << " seconds to insert!" << endl;
        break;
    }


    return 0;
}

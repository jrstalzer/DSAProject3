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
    set<string> categories{};
    Hash table{};
    FiveAryTree tree{};
    int choice = 0;
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

            categories.insert(category);
            //add insert method calls here
            switch (choice) {
            case 1:
                table.UpdateCategory(category, name, rating);
                insertTime = clock() - runTime;
                break;
            case 2:
                //insert table insert
                tree.Insert(category, name, rating);
                insertTime = clock() - runTime;
                break;
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
        cout << searchFor << "\n" << "Highest Rated Item: " << items["Max"].first << " | " << items["Max"].second << " Stars\n";
        cout << "Lowest Rated Item: " << items["Min"].first << " | " << items["Min"].second << " Stars\n";
        cout << "It took a 5-ary tree " << (float)runTime / CLOCKS_PER_SEC << " seconds to search and " << (float)insertTime / CLOCKS_PER_SEC << " seconds to insert!" << endl;
        break;
    }


    return 0;
}

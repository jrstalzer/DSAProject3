#include <iostream>
#include <map>
#include <random>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
using namespace std; 

int main(){
    ifstream reviewFile("amazon_reviews.csv");

    if (reviewFile.is_open) {
        string line;
        getline(reviewFile, line);

        int i = 0;
        while (i == 0) {
            istringstream stream(line);
            string toss;
            string name;
            string brand;
            string category;
            string tempPrice;
            double price = 0;
            string tempRate;
            double rating = 0;

            getline(stream, toss, ','); //toss username
            getline(stream, toss, ','); //toss verified status
            getline(stream, name, ']'); // keep item name, uses a dif delimeter because name can have commas
            name = name.substr(name.begin, name.end); //should take out the last comma
            getline(stream, toss, ']'); //toss description
            getline(stream, toss, ','); //toss image
            getline(stream, brand, ','); //keep brand
            getline(stream, toss, ','); //toss feature
            getline(stream, category, ','); //keep category
            getline(stream, tempPrice, ','); //keep price
            tempPrice = tempPrice.substr(tempPrice.begin + 1, tempPrice.end);
            price = stod(tempPrice);
            getline(stream, tempRate, ','); //keep rating
            rating = stod(tempRate);

            i++;
        }
        cout << name << " " << brand << " " << cateogry << " " << price << " " << rating << endl;
    }
    return 0; 
}

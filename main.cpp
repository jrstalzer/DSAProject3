#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
using namespace std;

int main() {
    ifstream reviewFile("amazon_reviews.csv");

    if (reviewFile.is_open()) {
        string line;
        getline(reviewFile, line);

        int i = 0;
        while (i < 2) {
            getline(reviewFile, line);
            istringstream stream(line);
            string toss;
            string name;
            string category;
            string tempRate;
            double rating = 0;

            getline(stream, toss, ','); //toss username
            getline(stream, toss, '"'); //toss verified status
            getline(stream, name, '"'); // keep item name, uses a dif delimeter because name can have commas
            getline(stream, toss, ']'); //toss description
            getline(stream, toss, ']'); //toss image
            getline(stream, toss, ','); //toss filler
            getline(stream, toss, ','); //toss feature
            getline(stream, toss, ','); //toss brand
            getline(stream, category, ','); //keep category
            getline(stream, toss, ','); //toss price
            getline(stream, tempRate, ','); //keep rating
            rating = stod(tempRate);

            i++;
            cout << name << " " << category << " " << rating << endl;
        }

    }
    else
        cout << "error :(" << endl;
    return 0;
}

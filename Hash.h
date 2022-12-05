#pragma once
#include <map> 
#include <string>
using namespace std; 


//TO USE: 
//1. Create a Hash object: Hash table; 
//2. To add an item: table.UpdateCategory("Category", "Item", rating); 
//3. To print the highest and lowest scores: table.PrintHighestLowestForCategory("category"); 

struct Stats {
    string itemName;
    int totalReviewCount = 0; //the total number of reviews 
    int totalReviewScore = 0; //all of the reviews summed
};

class Category {
public: 
    string catName; 
    Category* next = nullptr;
    map<string, Stats> items; 

    Category() { catName = "-1";  };
    //void UpdateItem(string itemName, int rating);
    void UpdateItem2(string itemName, int rating); 
    void UpdateItem(string itemName, int totalNumReview, int totalReviewScore); 
    void PrintAllItems(); 
    void PrintHighestLowestRated(); 
};

class Hash
{
public: 
    Category* array = new Category[10];
    int arraySize = 10; 
    int categoryCount = 0; 
    double maxLoadFactor = 0.8; 

    int CalculateHashCode(string category);
    int ReduceHashCode(string category);
    void UpdateCategory(string category, string itemName, int rating); 
    void PrintHighestLowestForCategory(string category); 
    void Print(); 
    double CalculateLoadFactor(); 
    void RehashTable(); 

};



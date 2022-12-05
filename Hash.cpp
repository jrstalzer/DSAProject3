#include "Hash.h"
#include <iostream>
using namespace std; 

//void Category::UpdateItem(string itemName, int rating) {
//    items[itemName] = rating;
//};

void Category::UpdateItem2(string itemName, int rating) {
    items[itemName].itemName = itemName; 
    items[itemName].totalReviewCount++; 
    items[itemName].totalReviewScore += rating; 
};

void Category::UpdateItem(string itemName, int totalNumReview, int totalReviewScore) {
	items[itemName].itemName = itemName;
	items[itemName].totalReviewCount = totalNumReview;
	items[itemName].totalReviewScore = totalReviewScore; 
};


void Category::PrintAllItems() {
	for (auto it = items.begin(); it != items.end(); it++) {
		cout << it->first << " | ";
		Stats* currStat = &it->second;
		//cout << "From Stats: " << currStat->itemName << " | ReviewCount: " << currStat->totalReviewCount << " | ReviewScore: " << currStat->totalReviewScore << endl;
		double avg = (double)currStat->totalReviewScore / (double)currStat->totalReviewCount;
		cout << "Average Rating: " << avg << endl;
	}
	cout << endl;
}

void Category::PrintHighestLowestRated() { //Add traversing the list
	string highestItemName = "";
	double highestItemRating = 0; 

	string lowestItemName = "";
	double lowestItemRating = 0; 

	for (auto it = items.begin(); it != items.end(); it++) {
		if (it == items.begin()) { //initialize values at first item in the map
			highestItemName = it->first; 
			lowestItemName = it->first; 
			Stats* start = &it->second; 
			double avg = (double)start->totalReviewScore / (double)start->totalReviewCount;
			highestItemRating = avg; 
			lowestItemRating = avg; 
		}
		Stats* currStat = &it->second;
		double avg = (double)currStat->totalReviewScore / (double)currStat->totalReviewCount;

		//check if it is greatest item
		if (avg > highestItemRating) {
			highestItemName = it->first; 
			highestItemRating = avg; 
		}

		//check if it is least item
		if (avg < lowestItemRating) {
			lowestItemName = it->first; 
			lowestItemRating = avg; 
		}
	}

	cout << "Category: " << catName << endl; 
	cout << "Highest Rated Item: " << highestItemName << " | " << highestItemRating << " Stars" << endl; 
	cout << "Lowest Rated Item: " << lowestItemName << " | " << lowestItemRating << " Stars" << endl; 
};


int Hash::CalculateHashCode(string category) {
	int hashcode = 0;

	for (int i = 0; i < category.length(); i++) {
		switch (category.at(i)) {
		case 'a':
		case 'A':
			hashcode += 0;
			break;
		case 'b':
		case 'B':
			hashcode += 1;
			break;
		case 'c':
		case'C':
			hashcode += 2;
			break;
		case 'd':
		case 'D':
			hashcode += 3;
			break;
		case 'e':
		case 'E':
			hashcode += 4;
			break;
		case 'f':
		case 'F':
			hashcode += 5;
			break;
		case 'g':
		case 'G':
			hashcode += 6;
			break;
		case 'h':
		case 'H':
			hashcode += 7;
			break;
		case 'i':
		case 'I':
			hashcode += 8;
			break;
		case 'j':
		case 'J':
			hashcode += 9;
			break;
		case 'k':
		case 'K':
			hashcode += 10;
			break;
		case 'l':
		case 'L':
			hashcode += 11;
			break;
		case 'm':
		case 'M':
			hashcode += 12;
			break;
		case 'n':
		case 'N':
			hashcode += 13;
			break;
		case 'o':
		case 'O':
			hashcode += 14;
			break;
		case 'p':
		case 'P':
			hashcode += 15;
			break;
		case 'q':
		case 'Q':
			hashcode += 16;
			break;
		case 'r':
		case 'R':
			hashcode += 17;
			break;
		case 's':
		case 'S':
			hashcode += 18;
			break;
		case 't':
		case 'T':
			hashcode += 19;
			break;
		case 'u':
		case 'U':
			hashcode += 20;
			break;
		case 'v':
		case 'V':
			hashcode += 21;
			break;
		case 'w':
		case 'W':
			hashcode += 22;
			break;
		case 'x':
		case 'X':
			hashcode += 23;
			break;
		case 'y':
		case 'Y':
			hashcode += 24;
			break;
		case 'z':
		case 'Z':
			hashcode += 25;
			break;
		}
	}

	return hashcode;
};

int Hash::ReduceHashCode(string category) {
	int hashCode = CalculateHashCode(category);
	int reduced = hashCode % arraySize;
	return reduced;
};

void Hash::UpdateCategory(string category, string itemName, int rating) {
	int reduced = ReduceHashCode(category); //get the location where the item should be stored in the array 
	Category* temp = &array[reduced]; 
	if (temp->catName == "-1") { //if its not in the table yet, add it 
		temp->catName = category; 
		temp->UpdateItem2(itemName, rating);
		categoryCount++; 
		if (CalculateLoadFactor() >= maxLoadFactor) {
			RehashTable(); 
		}
	}
	else if (temp->catName == category) { //if it is in the table, update items
		temp->UpdateItem2(itemName, rating); 
	}
	else {
		while (temp->next != nullptr) { //traverse to the end of the linked list temp->next should be nullptr. This is where we will add the new item 
			temp = temp->next;
			if (temp->catName == category) {
				temp->UpdateItem2(itemName, rating); 
				return; 
			}
		}
		Category* toAdd = new Category(); 
		toAdd->catName = category; 
		toAdd->UpdateItem2(itemName, rating); 
		temp->next = toAdd; 
		categoryCount++; 
		if (CalculateLoadFactor() >= maxLoadFactor) {
			RehashTable(); 
		}
	}

};

void Hash::PrintHighestLowestForCategory(string category) {
	int reduced = ReduceHashCode(category); 
	Category* current = &array[reduced];
	while (current->catName != category && current->next != nullptr) {
		current = current->next; 
	}
	if (current->catName == category) {
		current->PrintHighestLowestRated();
	}
};

void Hash::Print() {
	for (int i = 0; i < arraySize; i++) {
		Category* curr = &array[i];
		if (curr->catName == "-1") { //if there is nothing at that location 
			continue;
		}
		else {
			cout << "Category: " << curr->catName << endl;
			curr->PrintAllItems();

			while (curr->next != nullptr) {
				curr = curr->next; 
				cout << "Category: " << curr->catName << endl; 
				curr->PrintAllItems(); 
			}
		}
	}
};

double Hash::CalculateLoadFactor() {
	return (double)categoryCount / (double)arraySize; 
};

void Hash::RehashTable() {
	int oldArraySize = arraySize; 
	arraySize = arraySize * 2; 

	Category* newArray = new Category[arraySize];
	
	for (int i = 0; i < oldArraySize; i++) {
		Category* temp = &array[i];
		if (temp->catName == "-1") { //if its empty, go to the next index
			continue; 
		}
		//if its not empty, copy to new location & ensure pointers are null
		int rehashed = ReduceHashCode(temp->catName);
		Category* newTemp = &newArray[rehashed];
		
		while (temp != nullptr) {
			if (newTemp->catName == "-1") { //if there isnt anything in the initial part of the new array
				newTemp->catName = temp->catName;
				for (auto iter = temp->items.begin(); iter != temp->items.end(); iter++) {
					Stats* tempStat = &iter->second;
					string itemName = tempStat->itemName;
					int totalRevCount = tempStat->totalReviewCount;
					int totalRevScore = tempStat->totalReviewScore;
					newTemp->UpdateItem(itemName, totalRevCount, totalRevScore);
				}
			}
			else {
				while (newTemp->next != nullptr) { //navigate to the end of the single chain
					newTemp = newTemp->next;
				}
				//add category to the end
				Category* toAdd = new Category();
				toAdd->catName = temp->catName;
				for (auto iter = temp->items.begin(); iter != temp->items.end(); iter++) {
					Stats* tempStat = &iter->second;
					string itemName = tempStat->itemName;
					int totalRevCount = tempStat->totalReviewCount;
					int totalRevScore = tempStat->totalReviewScore;
					toAdd->UpdateItem(itemName, totalRevCount, totalRevScore);
				}
				newTemp->next = toAdd;
			}
			Category* prev = temp; 
			temp = temp->next; 
			prev->next = nullptr; 
		}
		
	}
	//have iterated through the entirety of the old table
	delete[] array; 
	array = newArray; 
	newArray = nullptr; 

}


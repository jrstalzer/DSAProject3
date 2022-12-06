#pragma once
#ifndef _TREE_H
#define _TREE_H
#include <vector>
#include <string>
#include <map>
#include <set>
using namespace std;

class FiveAryTree
{
private:
	struct Node		// I am adapting my own node class from the Gator AVL project.
	{
		struct Item
		{
			string name = "";
			int numRatings = 0;
			double sumRatings = 0;
			double avgRating = 0;
			Item()
			{
				name = "";
				numRatings = 0;
				sumRatings = 0;
				avgRating = 0;
			}
			Item(string n, double r)
			{
				name = n;
				numRatings++;
				sumRatings += r;
				avgRating = sumRatings / numRatings;
			}
			void AddRating(double r)
			{
				numRatings++;
				sumRatings += r;
				avgRating = sumRatings / numRatings;
			}
		};
		string category = "";
		map<string, Item> items{};
		Node* first = nullptr;	
		Node* second = nullptr;
		Node* third = nullptr;
		Node* fourth = nullptr;
		Node* fifth = nullptr;
		Node(string c, string n, double r)
		{
			category = c;
			items[n] = Item(n, r);
		}
		~Node()
		{
			first = nullptr;
			second = nullptr;
			third = nullptr;
			fourth = nullptr;
			fifth = nullptr;
		}
		void AddItem(string n, double r)
		{
			items[n] = Item(n, r);
		}
		bool ItemExists(string n) // O(t)
		{
			for (auto iter = items.begin(); iter != items.end(); iter++)
			{
				if (n == iter->first)
				{
					return true;
				}
			}
			return false;
		}
		void AddRatingToExistingItem(string n, double r)
		{
			items[n].AddRating(r);
		}
		string HighestRatedInd() // O(t)
		{
			double high = 0;
			string retVal = "";
			for (auto iter = items.begin(); iter != items.end(); iter++)
			{
				if (high < items[iter->first].avgRating)
				{
					high = items[iter->first].avgRating;
					retVal = iter->first;
				}
			}
			return retVal;
		}
		string LowestRatedInd() // O(t)
		{
			double low = 5.1;
			string retVal = "";
			for (auto iter = items.begin(); iter != items.end(); iter++)
			{
				if (low > items[iter->first].avgRating)
				{
					low = items[iter->first].avgRating;
					retVal = iter->first;
				}
			}
			return retVal;
		}
	};

	Node* root = nullptr;
	vector<string> itemNames{};
	set<string> categoryNames{};
	Node* HelpInsert(Node* _root, string c, string n, double r);
	Node* HelpInsertItemAndRating(Node* _root, string c, string n, double r);
	map<string, pair<string, double>> HighestAndLowestRatedItem(Node* _root, string c);
	void HelpDestructor(Node* _root);

public:
	FiveAryTree();
	~FiveAryTree();
	void Insert(string category, string name, double rating);
	map<string, pair<string, double>> HighAndLowRated(string category);
};

#endif

FiveAryTree::FiveAryTree()
{
	root = nullptr;
}

FiveAryTree::~FiveAryTree()
{
	HelpDestructor(this->root);
	this->root = nullptr;
}
void FiveAryTree::HelpDestructor(Node* _root)
{
	if (_root == nullptr)
	{
		return;
	}
	else
	{
		HelpDestructor(_root->first);
		HelpDestructor(_root->second);
		HelpDestructor(_root->third);
		HelpDestructor(_root->fourth);
		HelpDestructor(_root->fifth);
		delete _root;
	}
}

void FiveAryTree::Insert(string category, string name, double rating) // O((g^2)logt)
{
	if (categoryNames.find(category) != categoryNames.end()) // O((g^2)t) + O(logg)
	{
		this->root = HelpInsertItemAndRating(this->root, category, name, rating); // O(glogt)
		return;
	}
	this->root = HelpInsert(this->root, category, name, rating);  // O(g)
}

FiveAryTree::Node* FiveAryTree::HelpInsertItemAndRating(Node* _root, string c, string n, double r) // O(glogt)
{
	if (_root == nullptr)
	{
		return _root;
	}
	else
	{
		if (_root->category == c)
		{
			if (!(_root->items.find(n) != _root->items.end())) // O(logt), t = # of items in a given category
			{
				_root->AddItem(n, r);
				itemNames.push_back(n);
			}
			else
			{
				_root->AddRatingToExistingItem(n, r);
			}
			return _root;
		}
	}
	if (_root->first == nullptr)
	{
		return _root;
	}
	else
	{
		if (_root->first->category == c)
		{
			if (!(_root->first->items.find(n) != _root->first->items.end()))
			{
				_root->first->AddItem(n, r);
				itemNames.push_back(n);
			}
			else
			{
				_root->first->AddRatingToExistingItem(n, r);
			}
			return _root;
		}
	}
	if (_root->second == nullptr)
	{
		return _root;
	}
	else
	{
		if (_root->second->category == c)
		{
			if (!(_root->second->items.find(n) != _root->second->items.end()))
			{
				_root->second->AddItem(n, r);
				itemNames.push_back(n);
			}
			else
			{
				_root->second->AddRatingToExistingItem(n, r);
			}
			return _root;
		}
	}
	if (_root->third == nullptr)
	{
		return _root;
	}
	else
	{
		if (_root->third->category == c)
		{
			if (!(_root->third->items.find(n) != _root->third->items.end()))
			{
				_root->third->AddItem(n, r);
				itemNames.push_back(n);
			}
			else
			{
				_root->third->AddRatingToExistingItem(n, r);
			}
			return _root;
		}
	}
	if (_root->fourth == nullptr)
	{
		return _root;
	}
	else
	{
		if (_root->fourth->category == c)
		{
			if (!(_root->fourth->items.find(n) != _root->fourth->items.end()))
			{
				_root->fourth->AddItem(n, r);
				itemNames.push_back(n);
			}
			else
			{
				_root->fourth->AddRatingToExistingItem(n, r);
			}
			return _root;
		}
	}
	if (_root->fifth == nullptr)
	{
		return _root;
	}
	else
	{
		if (_root->fifth->category == c)
		{
			if (!(_root->fifth->items.find(n) != _root->fifth->items.end()))
			{
				_root->fifth->AddItem(n, r);
				itemNames.push_back(n);
			}
			else
			{
				_root->fifth->AddRatingToExistingItem(n, r);
			}
			return _root;
		}
	}
	if (_root->fifth != nullptr)
	{
		_root->first = HelpInsertItemAndRating(_root->first, c, n, r);
		_root->second = HelpInsertItemAndRating(_root->second, c, n, r);
		_root->third = HelpInsertItemAndRating(_root->third, c, n, r);
		_root->fourth = HelpInsertItemAndRating(_root->fourth, c, n, r);
		_root->fifth = HelpInsertItemAndRating(_root->fifth, c, n, r);
		return _root;
	}
}

FiveAryTree::Node* FiveAryTree::HelpInsert(Node* _root, string c, string n, double r) // O(g)
{
	if (_root == nullptr)
	{
		_root = new Node(c, n, r);
		categoryNames.insert(c);
		itemNames.push_back(n);
		return _root;
	}
	if (_root->first == nullptr)
	{
		_root->first = new Node(c, n, r);
		categoryNames.insert(c);
		itemNames.push_back(n);
		return _root;
	}
	if (_root->second == nullptr)
	{
		_root->second = new Node(c, n, r);
		categoryNames.insert(c);
		itemNames.push_back(n);
		return _root;
	}
	if (_root->third == nullptr)
	{
		_root->third = new Node(c, n, r);
		categoryNames.insert(c);
		itemNames.push_back(n);
		return _root;
	}
	if (_root->fourth == nullptr)
	{
		_root->fourth = new Node(c, n, r);
		categoryNames.insert(c);
		itemNames.push_back(n);
		return _root;
	}
	if (_root->fifth == nullptr)
	{
		_root->fifth = new Node(c, n, r);
		categoryNames.insert(c);
		itemNames.push_back(n);
		return _root;
	}
	if (_root->fifth != nullptr)
	{
		bool fullBefore = false;
		bool fullAfter = false;
		if (_root->first->fifth != nullptr)
		{
			fullBefore = true;
			fullAfter = true;
		}
		if (!fullBefore)
		{
			_root->first = HelpInsert(_root->first, c, n, r);
			if (_root->first->fifth != nullptr)
			{
				fullAfter = true;
			}
		}
		if ((fullBefore != fullAfter) || ((fullBefore == false) && (fullAfter == false)))
		{
			return _root;
		}
		fullBefore = false;
		fullAfter = false;
		if (_root->second->fifth != nullptr)
		{
			fullBefore = true;
			fullAfter = true;
		}
		if (!fullBefore)
		{
			_root->second = HelpInsert(_root->second, c, n, r);
			if (_root->second->fifth != nullptr)
			{
				fullAfter = true;
			}
		}
		if ((fullBefore != fullAfter) || ((fullBefore == false) && (fullAfter == false)))
		{
			return _root;
		}
		fullBefore = false;
		fullAfter = false;
		if (_root->third->fifth != nullptr)
		{
			fullBefore = true;
			fullAfter = true;
		}
		if (!fullBefore)
		{
			_root->third = HelpInsert(_root->third, c, n, r);
			if (_root->third->fifth != nullptr)
			{
				fullAfter = true;
			}
		}
		if ((fullBefore != fullAfter) || ((fullBefore == false) && (fullAfter == false)))
		{
			return _root;
		}
		fullBefore = false;
		fullAfter = false;
		if (_root->fourth->fifth != nullptr)
		{
			fullBefore = true;
			fullAfter = true;
		}
		if (!fullBefore)
		{
			_root->fourth = HelpInsert(_root->fourth, c, n, r);
			if (_root->fourth->fifth != nullptr)
			{
				fullAfter = true;
			}
		}
		if ((fullBefore != fullAfter) || ((fullBefore == false) && (fullAfter == false)))
		{
			return _root;
		}
		fullBefore = false;
		fullAfter = false;
		if (_root->fifth->fifth != nullptr)
		{
			fullBefore = true;
			fullAfter = true;
		}
		if (!fullBefore)
		{
			_root->fifth = HelpInsert(_root->fifth, c, n, r);
			if (_root->fifth->fifth != nullptr)
			{
				fullAfter = true;
			}
		}
		if ((fullBefore != fullAfter) || ((fullBefore == false) && (fullAfter == false)))
		{
			return _root;
		}
		return _root;
	}
}

map<string, pair<string, double>> FiveAryTree::HighAndLowRated(string category) // O(2g2t)
{
	map<string, pair<string, double>> retVal{};
	retVal = HighestAndLowestRatedItem(this->root, category);
	return retVal;
}

map<string, pair<string, double>> FiveAryTree::HighestAndLowestRatedItem(Node* _root, string c) // O(gt)
{
	string nameMax = "";
	string nameMin = "";
	map<string, pair<string, double>> minMax{};
	if (_root == nullptr)
	{
		return {};
	}
	else
	{
		if (_root->category == c)
		{
			nameMax = _root->HighestRatedInd(); // O(t)
			nameMin = _root->LowestRatedInd();
			minMax["Max"] = make_pair(_root->items[nameMax].name, _root->items[nameMax].avgRating);
			minMax["Min"] = make_pair(_root->items[nameMin].name, _root->items[nameMin].avgRating);
			return minMax;
		}
	}
	if (_root->first == nullptr)
	{
		return {};
	}
	else
	{
		if (_root->first->category == c)
		{
			nameMax = _root->first->HighestRatedInd();
			nameMin = _root->first->LowestRatedInd();
			minMax["Max"] = make_pair(_root->first->items[nameMax].name, _root->first->items[nameMax].avgRating);
			minMax["Min"] = make_pair(_root->first->items[nameMin].name, _root->first->items[nameMin].avgRating);
			return minMax;
		}
	}
	if (_root->second == nullptr)
	{
		return {};
	}
	else
	{
		if (_root->second->category == c)
		{
			nameMax = _root->second->HighestRatedInd();
			nameMin = _root->second->LowestRatedInd();
			minMax["Max"] = make_pair(_root->second->items[nameMax].name, _root->second->items[nameMax].avgRating);
			minMax["Min"] = make_pair(_root->second->items[nameMin].name, _root->second->items[nameMin].avgRating);
			return minMax;
		}
	}
	if (_root->third == nullptr)
	{
		return {};
	}
	else
	{
		if (_root->third->category == c)
		{
			nameMax = _root->third->HighestRatedInd();
			nameMin = _root->third->LowestRatedInd();
			minMax["Max"] = make_pair(_root->third->items[nameMax].name, _root->third->items[nameMax].avgRating);
			minMax["Min"] = make_pair(_root->third->items[nameMin].name, _root->third->items[nameMin].avgRating);
			return minMax;
		}
	}
	if (_root->fourth == nullptr)
	{
		return {};
	}
	else
	{
		if (_root->fourth->category == c)
		{
			nameMax = _root->fourth->HighestRatedInd();
			nameMin = _root->fourth->LowestRatedInd();
			minMax["Max"] = make_pair(_root->fourth->items[nameMax].name, _root->fourth->items[nameMax].avgRating);
			minMax["Min"] = make_pair(_root->fourth->items[nameMin].name, _root->fourth->items[nameMin].avgRating);
			return minMax;
		}
	}
	if (_root->fifth == nullptr)
	{
		return {};
	}
	else
	{
		if (_root->fifth->category == c)
		{
			nameMax = _root->fifth->HighestRatedInd();
			nameMin = _root->fifth->LowestRatedInd();
			minMax["Max"] = make_pair(_root->fifth->items[nameMax].name, _root->fifth->items[nameMax].avgRating);
			minMax["Min"] = make_pair(_root->fifth->items[nameMin].name, _root->fifth->items[nameMin].avgRating);
			return minMax;
		}
	}
	if (_root->fifth != nullptr)
	{
		map<string, pair<string, double>> retVal{};
		retVal = HighestAndLowestRatedItem(_root->first, c);
		if (!retVal.empty())
		{
			return retVal;
		}
		retVal = HighestAndLowestRatedItem(_root->second, c);
		if (!retVal.empty())
		{
			return retVal;
		}
		retVal = HighestAndLowestRatedItem(_root->third, c);
		if (!retVal.empty())
		{
			return retVal;
		}
		retVal = HighestAndLowestRatedItem(_root->fourth, c);
		if (!retVal.empty())
		{
			return retVal;
		}
		retVal = HighestAndLowestRatedItem(_root->fifth, c);
		return retVal;
	}
}
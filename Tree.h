#pragma once
#ifndef _TREE_H
#define _TREE_H
#include <vector>
#include <string>
#include <map>
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
		bool ItemExists(string n)
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
		string HighestRatedInd()
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
		string LowestRatedInd()
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
	vector<string> categoryNames{};
	Node* HelpInsert(Node* _root, string c, string n, double r);
	Node* HelpInsertRating(Node* _root, string c, string n, double r);
	Node* HelpInsertItem(Node* _root, string c, string n, double r);
	pair<string, double> HighestRatedItem(Node* _root, string c);
	pair<string, double> LowestRatedItem(Node* _root, string c);
	void HelpDestructor(Node* _root);

public:
	FiveAryTree();
	~FiveAryTree();
	void Insert(string category, string name, double rating);
	bool ItemExists(string n);
	bool CategoryExists(string c);
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

bool FiveAryTree::ItemExists(string n)
{
	for (int i = 0; i < itemNames.size(); i++)
	{
		if (n == itemNames[i])
		{
			return true;
		}
	}
	return false;
}

bool FiveAryTree::CategoryExists(string c)
{
	for (int i = 0; i < categoryNames.size(); i++)
	{
		if (c == categoryNames[i])
		{
			return true;
		}
	}
	return false;
}

void FiveAryTree::Insert(string category, string name, double rating)
{
	if (ItemExists(name))
	{
		this->root = HelpInsertRating(this->root, category, name, rating);
		return;
	}
	if (CategoryExists(category))
	{
		this->root = HelpInsertItem(this->root, category, name, rating);
		return;
	}
	this->root = HelpInsert(this->root, category, name, rating);
}

FiveAryTree::Node* FiveAryTree::HelpInsertRating(Node* _root, string c, string n, double r)
{
	if (_root == nullptr)
	{
		return _root;
	}
	else
	{
		if (_root->category == c)
		{
			if (_root->ItemExists(n))
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
			if (_root->first->ItemExists(n))
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
			if (_root->second->ItemExists(n))
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
			if (_root->third->ItemExists(n))
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
			if (_root->fourth->ItemExists(n))
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
			if (_root->fifth->ItemExists(n))
			{
				_root->fifth->AddRatingToExistingItem(n, r);
			}
			return _root;
		}
	}
	if (_root->fifth != nullptr)
	{
		_root->first = HelpInsertRating(_root->first, c, n, r);
		_root->second = HelpInsertRating(_root->second, c, n, r);
		_root->third = HelpInsertRating(_root->third, c, n, r);
		_root->fourth = HelpInsertRating(_root->fourth, c, n, r);
		_root->fifth = HelpInsertRating(_root->fifth, c, n, r);
		return _root;
	}
}

FiveAryTree::Node* FiveAryTree::HelpInsertItem(Node* _root, string c, string n, double r)
{
	if (_root == nullptr)
	{
		return _root;
	}
	else
	{
		if (_root->category == c)
		{
			if (!_root->ItemExists(n))
			{
				_root->AddItem(n, r);
				itemNames.push_back(n);
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
			if (!_root->first->ItemExists(n))
			{
				_root->first->AddItem(n, r);
				itemNames.push_back(n);
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
			if (!_root->second->ItemExists(n))
			{
				_root->second->AddItem(n, r);
				itemNames.push_back(n);
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
			if (!_root->third->ItemExists(n))
			{
				_root->third->AddItem(n, r);
				itemNames.push_back(n);
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
			if (!_root->fourth->ItemExists(n))
			{
				_root->fourth->AddItem(n, r);
				itemNames.push_back(n);
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
			if (!_root->fifth->ItemExists(n))
			{
				_root->fifth->AddItem(n, r);
				itemNames.push_back(n);
			}
			return _root;
		}
	}
	if (_root->fifth != nullptr)
	{
		_root->first = HelpInsertRating(_root->first, c, n, r);
		_root->second = HelpInsertRating(_root->second, c, n, r);
		_root->third = HelpInsertRating(_root->third, c, n, r);
		_root->fourth = HelpInsertRating(_root->fourth, c, n, r);
		_root->fifth = HelpInsertRating(_root->fifth, c, n, r);
		return _root;
	}
}

FiveAryTree::Node* FiveAryTree::HelpInsert(Node* _root, string c, string n, double r)
{
	if (_root == nullptr)
	{
		_root = new Node(c, n, r);
		categoryNames.push_back(c);
		itemNames.push_back(n);
		return _root;
	}
	else
	{
		if (_root->category == c)
		{
			if (_root->ItemExists(n))
			{
				_root->AddRatingToExistingItem(n, r);
			}
			else
			{
				_root->AddItem(n, r);
				itemNames.push_back(n);
			}
			return _root;
		}
	}
	if (_root->first == nullptr)
	{
		_root->first = new Node(c, n, r);
		categoryNames.push_back(c);
		itemNames.push_back(n);
		return _root;
	}
	else
	{
		if (_root->first->category == c)
		{
			if (_root->first->ItemExists(n))
			{
				_root->first->AddRatingToExistingItem(n, r);
			}
			else
			{
				_root->first->AddItem(n, r);
				itemNames.push_back(n);
			}
			return _root;
		}
	}
	if (_root->second == nullptr)
	{
		_root->second = new Node(c, n, r);
		categoryNames.push_back(c);
		itemNames.push_back(n);
		return _root;
	}
	else
	{
		if (_root->second->category == c)
		{
			if (_root->second->ItemExists(n))
			{
				_root->second->AddRatingToExistingItem(n, r);
			}
			else
			{
				_root->second->AddItem(n, r);
				itemNames.push_back(n);
			}
			return _root;
		}
	}
	if (_root->third == nullptr)
	{
		_root->third = new Node(c, n, r);
		categoryNames.push_back(c);
		itemNames.push_back(n);
		return _root;
	}
	else
	{
		if (_root->third->category == c)
		{
			if (_root->third->ItemExists(n))
			{
				_root->third->AddRatingToExistingItem(n, r);
			}
			else
			{
				_root->third->AddItem(n, r);
				itemNames.push_back(n);
			}
			return _root;
		}
	}
	if (_root->fourth == nullptr)
	{
		_root->fourth = new Node(c, n, r);
		categoryNames.push_back(c);
		itemNames.push_back(n);
		return _root;
	}
	else
	{
		if (_root->fourth->category == c)
		{
			if (_root->fourth->ItemExists(n))
			{
				_root->fourth->AddRatingToExistingItem(n, r);
			}
			else
			{
				_root->fourth->AddItem(n, r);
				itemNames.push_back(n);
			}
			return _root;
		}
	}
	if (_root->fifth == nullptr)
	{
		_root->fifth = new Node(c, n, r);
		categoryNames.push_back(c);
		itemNames.push_back(n);
		return _root;
	}
	else
	{
		if (_root->fifth->category == c)
		{
			if (_root->fifth->ItemExists(n))
			{
				_root->fifth->AddRatingToExistingItem(n, r);
			}
			else
			{
				_root->fifth->AddItem(n, r);
				itemNames.push_back(n);
			}
			return _root;
		}
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

map<string, pair<string, double>> FiveAryTree::HighAndLowRated(string category)
{
	map<string, pair<string, double>> retVal{};
	retVal["Max"] = HighestRatedItem(this->root, category);
	retVal["Min"] = LowestRatedItem(this->root, category);
	return retVal;
}

pair<string, double> FiveAryTree::HighestRatedItem(Node* _root, string c)
{
	string name = "";
	if (_root == nullptr)
	{
		return make_pair("", 0);
	}
	else
	{
		if (_root->category == c)
		{
			name = _root->HighestRatedInd();
			return make_pair(_root->items[name].name, _root->items[name].avgRating);
		}
	}
	if (_root->first == nullptr)
	{
		return make_pair("", 0);
	}
	else
	{
		if (_root->first->category == c)
		{
			name = _root->first->HighestRatedInd();
			return make_pair(_root->first->items[name].name, _root->first->items[name].avgRating);
		}
	}
	if (_root->second == nullptr)
	{
		return make_pair("", 0);
	}
	else
	{
		if (_root->second->category == c)
		{
			name = _root->second->HighestRatedInd();
			return make_pair(_root->second->items[name].name, _root->second->items[name].avgRating);
		}
	}
	if (_root->third == nullptr)
	{
		return make_pair("", 0);
	}
	else
	{
		if (_root->third->category == c)
		{
			name = _root->third->HighestRatedInd();
			return make_pair(_root->third->items[name].name, _root->third->items[name].avgRating);
		}
	}
	if (_root->fourth == nullptr)
	{
		return make_pair("", 0);
	}
	else
	{
		if (_root->fourth->category == c)
		{
			name = _root->fourth->HighestRatedInd();
			return make_pair(_root->fourth->items[name].name, _root->fourth->items[name].avgRating);
		}
	}
	if (_root->fifth == nullptr)
	{
		return make_pair("", 0);
	}
	else
	{
		if (_root->fifth->category == c)
		{
			name = _root->fifth->HighestRatedInd();
			return make_pair(_root->fifth->items[name].name, _root->fifth->items[name].avgRating);
		}
	}
	if (_root->fifth != nullptr)
	{
		pair<string, double> retVal{};
		retVal = HighestRatedItem(_root->first, c);
		retVal = HighestRatedItem(_root->second, c);
		retVal = HighestRatedItem(_root->third, c);
		retVal = HighestRatedItem(_root->fourth, c);
		retVal = HighestRatedItem(_root->fifth, c);
		return retVal;
	}
}

pair<string, double> FiveAryTree::LowestRatedItem(Node* _root, string c)
{
	string name = "";
	if (_root == nullptr)
	{
		return make_pair("", 0);
	}
	else
	{
		if (_root->category == c)
		{
			name = _root->LowestRatedInd();
			return make_pair(_root->items[name].name, _root->items[name].avgRating);
		}
	}
	if (_root->first == nullptr)
	{
		return make_pair("", 0);
	}
	else
	{
		if (_root->first->category == c)
		{
			name = _root->first->LowestRatedInd();
			return make_pair(_root->first->items[name].name, _root->first->items[name].avgRating);
		}
	}
	if (_root->second == nullptr)
	{
		return make_pair("", 0);
	}
	else
	{
		if (_root->second->category == c)
		{
			name = _root->second->LowestRatedInd();
			return make_pair(_root->second->items[name].name, _root->second->items[name].avgRating);
		}
	}
	if (_root->third == nullptr)
	{
		return make_pair("", 0);
	}
	else
	{
		if (_root->third->category == c)
		{
			name = _root->third->LowestRatedInd();
			return make_pair(_root->third->items[name].name, _root->third->items[name].avgRating);
		}
	}
	if (_root->fourth == nullptr)
	{
		return make_pair("", 0);
	}
	else
	{
		if (_root->fourth->category == c)
		{
			name = _root->fourth->LowestRatedInd();
			return make_pair(_root->fourth->items[name].name, _root->fourth->items[name].avgRating);
		}
	}
	if (_root->fifth == nullptr)
	{
		return make_pair("", 0);
	}
	else
	{
		if (_root->fifth->category == c)
		{
			name = _root->fifth->LowestRatedInd();
			return make_pair(_root->fifth->items[name].name, _root->fifth->items[name].avgRating);
		}
	}
	if (_root->fifth != nullptr)
	{
		pair<string, double> retVal{};
		retVal = LowestRatedItem(_root->first, c);
		retVal = LowestRatedItem(_root->second, c);
		retVal = LowestRatedItem(_root->third, c);
		retVal = LowestRatedItem(_root->fourth, c);
		retVal = LowestRatedItem(_root->fifth, c);
		return retVal;
	}
}
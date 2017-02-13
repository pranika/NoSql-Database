#pragma 
#pragma once
/////////////////////////////////////////////////////////////////////
// NoSqlDb.h - key/value pair in-memory database and persistance to
//	XML	file attached.												//
// PROJECT REQUIREMENTS :											//
//	Version		:	1.0												//
//	APPLICATION	:	Project #1 NOSQL DATABASE						//
//	LANGUAGE	:	C++, VISUAL STUDIO 2015							//
//	Platform	:	MACBOOK PRO,processor-i7,WINDOWS-10				//
//	Author		:	Pranika Jain, SUID-234898626					//
//	Reference	:	Jim Fawcett, CST 4-187, SYRACUSE UNIVERSITY		//
//				:	   (315) 443-3948, jfawcett@twcny.rr.com		//
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2017       //
/////////////////////////////////////////////////////////////////////

/*
* Package Operations :
*== == == == == == == == == == == == == == == =
* This package acts as the main executive for the whole project.
* it will use NoSQL Databse to build an a database which is in memory and query mechanism is added to it.
* This package will paires the required files from the given directory.
*
* Public Interface :
*== == == == == == == == == == == == == == ==
*	bool save(Key key, Element<Data> elem); //REQUIREMENT 2
*	bool editElement(Key key, Element<Data> elem); // REQUIREMENT 3
*	bool deleteChild(Key key, Keys childkeys);	// REQUIREMENT 4
*	bool addChild(Key key, Keys childkeys);	//REQUIREMENT 4
*	Element<Data> value_return(Key key);	// REQUIRENT 7.1
*	std::vector<std::string> key_return(string key_pattern,int x); // REQUIREMENT 7.3
*	std::vector<std::string> name_key(string name_string);	// REQUIREMENT 7.4
*	std::vector<std::string> category_key(string category_string); // REQUIREMENT 7.5
*	std::vector<std::string> data_key(string data_string); // REQUIREMENT 7.6
*	std::set<std::string> unionofkeys(std::vector<std::string> query1, std::vector<std::string> query2); //REQUIREMENT 9
*	bool deletion(Key key); // REQUIREMENT 3
*	Element<Data> value(Key key); 
*	Element<Data> element_return(Key key); // REQUIREMENT 5
*	std::vector<std::string> child_return(string key);	// REQUIREMENT 7.2
*	bool replace(Key original_key, Key replace_key);	// REQUIREMENT 4
*	std::vector<std::string> time_interval(string t1,string t2);	// REQUIREMENT 7.7
*	std::vector<std::string> search_rejex(); REQUIREMENT 12
*	std::set<std::string> intersection(std::vector<std::string> query1, 
*	std::vector<std::string> query2); // REQUIREMENT 8
*	
* Required Files :
*== == == == == == == == == == == == == ==
*	NoSQLDb.h, nosqldb.xml,CppProperties.h,XmlDocument.h,XmlElement.h,XmlParser.StringHelper.h,
*	Convert.h, xmlElementParts.h , Tokenizer.h 
*
* Build Command :
*== == == == == == == == == == == == == ==
* devenv InMemoryDb.sln / rebuild debug
*
* Maintenance History :
*== == == == == == == == == == == == == ==
* ver 1.0 : 02 /08 / 17
* -first release
*/

#ifndef NO_SQLDB
#define NO_SQLDB
 // !NO_SQLDB


#include <unordered_map>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <iostream>
#include "../CppProperties/CppProperties.h"
#include <algorithm>
#include <set>
#include <regex>


using namespace std;
/////////////////////////////////////////////////////////////////////
// Element class represents a data record in our NoSql database
// - in our NoSql database that is just the value in a key/value pair
// - it needs to store child data, something for you to implement
//

template<typename Data>

class Element 
{
	
public:
	using Key = std::string;
	using Name = std::string;
	using Category = std::string;
	using TimeDate = std::string;
	using Description = std::string;
	using Keys = std::vector<Key>;
	using Children = Keys;

	Property<Name> name;            // metadata
	Property<Category> category;    // metadata
	Property<Description> description; //metadata
	Property<TimeDate> timeDate; // metadata
	Children children;     // metadata
	Property<Data> data;            // data
	
	std::string show();
};


template<typename Data>
std::string Element<Data>::show()
{
	// show children when you've implemented them

	std::ostringstream out;
	out.setf(std::ios::adjustfield, std::ios::left);
	out << "\n    " << std::setw(8) << "name" << " : " << name;
	out << "\n    " << std::setw(8) << "category" << " : " << category;
	out << "\n    " << std::setw(8) << "description" << " : " << description;
	out << "\n    " << std::setw(8) << "timeDate" << " : " << timeDate;

	out << "\n    " << std::setw(8) << "data" << " : " << data;
	out << "\n    " << std::setw(8) << "children" << " : ";
	
	if(children.size() != 0)
	{ 
		int i = 1;
		for (Key childkey : children)
		{
			out << "\n		" << std::setw(1) << "Child" << i << " : " << childkey;
			i++;
		}

	}
	else
		out  << std::setw(8) << "No Children for this element" ;
	
	out << "\n";
	return out.str();
}

/////////////////////////////////////////////////////////////////////
// NoSqlDb class is a key/value pair in-memory database
// - stores and retrieves elements
// - queries are added
// - persistance is added
//
template<typename Data>
class NoSqlDb
{
public:
	using Key = std::string;
	using Keys = std::vector<Key>;
	using TimeDate = std::string;

	Keys keys();
	bool save(Key key, Element<Data> elem);
	bool editElement(Key key, Element<Data> elem);
	bool deleteChild(Key key, Keys childkeys);
	bool addChild(Key key, Keys childkeys);
	Element<Data> value_return(Key key);
	std::vector<std::string> key_return(string key_pattern,int x);
	std::vector<std::string> name_key(string name_string);
	std::vector<std::string> category_key(string category_string);
	std::vector<std::string> data_key(string data_string);
	std::set<std::string> unionofkeys(std::vector<std::string> query1, std::vector<std::string> query2);
	bool deletion(Key key);
	Element<Data> value(Key key);
	Element<Data> element_return(Key key);
	std::vector<std::string> child_return(string key);
	bool replace(Key original_key, Key replace_key);
	std::vector<std::string> time_interval(string t1,string t2);
	
	std::vector<std::string> search_rejex();
std::set<std::string> intersection(std::vector<std::string> query1, std::vector<std::string> query2);
	size_t count();
private:
	using Item = std::pair<Key, Element<Data>>;

	std::unordered_map<Key, Element<Data>> store;

	//std::unordered_map<Key, Element<Data>> deletion;
};

template<typename Data>
typename NoSqlDb<Data>::Keys NoSqlDb<Data>::keys()
{
	Keys keys;
//	Keys categorykeys();
	for (Item item : store)
	{
		keys.push_back(item.first);
	}
	return keys;
}
// SAVING RECORDS TO UNORDERED MAP
template<typename Data>
bool NoSqlDb<Data>::save(Key key, Element<Data> elem)
{
	if (store.find(key) != store.end())
		return false;
	store[key] = elem;
	return true;
}
// EDITING THE ELEMENT INFORMATION
template<typename Data>
bool NoSqlDb<Data>::editElement(Key key, Element<Data> elem)
{
	Element<Data> element;

		if (store.find(key) != store.end())
	{
		element = store[key];
		element.name = elem.name;
		element.category = elem.category;
		element.description = elem.description;
		element.timeDate = elem.timeDate;
		element.children = elem.children;
		
		store[key] = element;
		return true;
	}
	
	return false;
}
// REPLACING ONE ELEMENT WITH OTHER
template<typename Data>
bool  NoSqlDb<Data>::replace(Key original_key, Key replace_key)
{
		Element<Data> element;
	Element<Data> replace;
	if (store.find(original_key) != store.end())
	{
		 
		element = store[original_key];
		replace = store[replace_key];
		element.name = replace.name;
		element.category = replace.category;
		element.description = replace.description;
		element.timeDate = replace.timeDate;
		element.children = replace.children;
		element.timeDate = replace.timeDate;
		store[original_key] = element;
		return true;
	}

	return false;
}
// RETRIEVING ALL RECORDS
template<typename Data>
Element<Data> NoSqlDb<Data>::value(Key key)
{
	if (store.find(key) != store.end())
		return store[key];
	return Element<Data>();
}


template<typename Data>
bool NoSqlDb<Data>::deletion(Key key)
{
	if (store.find(key) != store.end())
	{
		store.erase(key);
		return true;


	}
	
	return false;
}
// DELETING CHILD FROM A KEY

template<typename Data>
bool NoSqlDb<Data>::deleteChild(Key key, Keys childkeys)
{
	Element<Data> element;
	vector<Key>::iterator it;  
	for (Item item : store) {
		if (item.first == key) {
			element = item.second;
		/*	cout << element.name << "    Element Name" << endl;
			for (Key ks : element.children) {
				cout << "testing elem3 children" << endl;
				cout << ks << endl;
			}

			for (Key ks : childkeys) {
				cout << "testing elem3 children" << endl;
				cout << ks << endl;
			}
*/
				//for (Key y : childkeys)
					for (auto i=0; i!=childkeys.size(); i++)
				{
					//element.children.erase(std::remove(element.children.begin(), element.children.end(), y), element.children.end());
					it = std::find(element.children.begin(), element.children.end(), childkeys[i]);
					if (it != element.children.end())
					{
						element.children.erase(it);
						
					}

				}
			
					store[key] = element; 
					return true;
		}
	}
		return false;
	

}
// ADDING CHILD TO A KEY
template<typename Data>
bool NoSqlDb<Data>::addChild(Key key, Keys childkeys)
{
	Element<Data> element;

	if (store.find(key) != store.end())
	{
		element = store[key];
		for (Key childkey : childkeys)
		{
			if (std::find(element.children.begin(), element.children.end(), childkey) == element.children.end())
				element.children.push_back(childkey);
		}
		store[key] = element;
		return true;
	}
	return false;
}

template<typename Data>
size_t NoSqlDb<Data>::count()
{
	return store.size();
}

// value of specific key
template<typename Data>
Element<Data> NoSqlDb<Data>::value_return(Key key)
{
	Element<Data> element;
	if (store.find(key) != store.end())
	{
		element = store[key];
		//cout << "Records" <<element.show();
		return store[key];
	}
	else return Element<Data>();
}


// Children of a specific key

template<typename Data>
std::vector<std::string> NoSqlDb<Data>::child_return(string key)
{
	std::vector<std::string> key_child;
	Element<Data> element;
	if (store.find(key) != store.end())
	{
		element = store[key];	
		key_child = element.children;
	}
	return key_child;
	
}

//set of keys with specific pattern
template<typename Data> 
std::vector<std::string> NoSqlDb<Data>::key_return(string key_pattern,int x) {
	auto key_selector = [](auto pair)
	{return pair.first;};
	
	std::vector<std::string> record_keys(store.size());
	std::vector<std::string> elem_key;
	transform(store.begin(), store.end(), record_keys.begin(), key_selector);
	for (Key key : record_keys)
	{
		//cout << "record keys" << key;

		if (key.compare(0,x,key_pattern) == 0 )

		{
			elem_key.push_back(key);
		}
	}

	return elem_key;

}


// set of keys with specific string in item name

template<typename Data>
std::vector<std::string> NoSqlDb<Data>::name_key(string name_string){
	Element<Data> element;
	std::vector<std::string> elem_key;
	for (Item x : store) {
		element = x.second;
		string name = element.name;
		if (name.find(name_string) != string::npos)
			elem_key.push_back(x.first);	
	}
	return elem_key;
}

// set of keys with specific string in category name

template<typename Data>
std::vector<std::string> NoSqlDb<Data>::category_key(string category_string)
{

	Element<Data> element;
	std::vector<std::string> key_category;
	for (Item item : store)
	{
		element = item.second;
		string category_str = element.category;
		if (category_str.find(category_string) != string::npos)
		{
			key_category.push_back(item.first);
		}
	}
	return key_category;

}

template<typename Data>
std::vector<std::string> NoSqlDb<Data>::data_key(string data_string)
{

	Element<Data> element;
	std::vector<std::string> key_data;
	for (Item item : store)
	{
		element = item.second;
		string data_str = element.data;
		if (data_str.find(data_string) != string::npos)
		{
			key_data.push_back(item.first);
		}
	}
	return key_data;


}
//UNION OF 2 QUERIES
template<typename Data>
std::set<std::string> NoSqlDb<Data>::unionofkeys(std::vector<std::string> query1,std::vector<std::string> query2)
{

	set<string> setname;

	for (Key key : query1)
	{
		setname.insert(key);
	}

	for (Key key : query2)
	{
		setname.insert(key);
	}

	return setname;

}
//INTERSECTION OF 2 QUERIES
template<typename Data>
std::set<std::string> NoSqlDb<Data>::intersection(std::vector<std::string> query1, std::vector<std::string> query2)
{
	//vector<Key>::iterator it;
	set<string> result;
	set<string> setname1;
	set<string> setname2;

	for (Key key : query1)
	{
		setname1.insert(key);
	}

	for (Key key : query2)
	{
		setname2.insert(key);
	}
	for (Key k : setname2)
	{
		if (setname1.find(k) != setname1.end())
		{
			result.insert(k);
		}

	}
	
	return result;
	
	
}
// CHECKING TIME INTERVAL AND RETREIVING VALUES
template<typename Data>
std::vector<std::string> NoSqlDb<Data>::time_interval(string string_t1,string string_t2)
{
	Element<Data> element;
	std::vector<std::string> store_keys;
	std::tm tm = {};
		
	for (Item item : store)
	{
		
		element = item.second;
		
		string elementtime = element.timeDate;

		//if(strcmp(string_t1,string_t2) > 0)  
		//{
		if (elementtime <= string_t2 && elementtime >= string_t1)
		{
			store_keys.push_back(item.first);
		}
		
		//}
		/*else 
			if (elementtime >= string_t1 && elementtime <= string_t2)
			{
				store_keys.push_back(item.first);
			} */
	}

	return store_keys;
}

//Persistance
template<typename Data>
Element<Data> NoSqlDb<Data>::element_return(Key key)
{
	Element<Data> element;
	

	for (Item item : store)
	{
		if (item.first == key)
		{
			element = item.second;
			
			return element;
		}
		
	}	
	}
/// REJEX OPERATION ON STRING
template<typename Data>
std::vector<std::string> NoSqlDb<Data>::search_rejex()
{
	Element<Data> element;
	std::vector<std::string> key_category;
	//bool match;
	 std::regex e("test.*");
	for (Item item : store)
	{
		element = item.second;
		string category_str = element.category;
		//cout << "category_str" << element.category;
		if (std::regex_match(category_str, e))
		{
			key_category.push_back(item.first);
		}
		else
			break;
	}
	return key_category;

}


/////////////////////////////////////////////////////////////////////
// Persistance class
// - you will need to implement that using the XmlDocument class
//   from Handouts/Repository
#endif
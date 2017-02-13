/////////////////////////////////////////////////////////////////////
// NoSqlDb.cpp - TEST EXECUTIVE												//
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
#define _CRT_SECURE_NO_WARNINGS

#include "NoSqlDb.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <string>
#include <sstream>
#include <iomanip>
#include <set>
#include "../XmlDocument/XmlDocument/XmlDocument.h"
#include "../XmlDocument/XmlElement/XmlElement.h"
#include "../Convert/Convert.h"
#include "../CppProperties/CppProperties.h"
#include "../StrHelper.h"
#include <ctime>
#include <chrono>
#include <time.h>
#include <locale>
#include <stdlib.h>
#include "XMLPersistance.h";

using StrData = std::string;
using intData = int;
using Key = NoSqlDb<StrData>::Key;
using Keys = NoSqlDb<StrData>::Keys;
using namespace XmlProcessing;
using SPtr = std::shared_ptr<AbstractXmlElement>;
using namespace std::chrono;
using Key = std::string;
//Persistance Data

static std::string toXml(const Element<StrData> element)
{
	std::string xml;
	XmlDocument doc;
	SPtr pRoot = makeTaggedElement("Records");
	doc.docElement() = pRoot;
	
	// make Property<string> name element and add to root
	SPtr pNameElem = makeTaggedElement("Name");
	pRoot->addChild(pNameElem);
	SPtr pTextElem1 = makeTextElement(element.name);
	pNameElem->addChild(pTextElem1);

	// make Property<string> name element and add to root
	SPtr pCategoryElem = makeTaggedElement("Category");
	pRoot->addChild(pCategoryElem);
	SPtr pTextElem2 = makeTextElement(element.category);
	pCategoryElem->addChild(pTextElem2);

	// make Property<string> name element and add to root
	SPtr pDescElem = makeTaggedElement("Description");
	pRoot->addChild(pDescElem);
	SPtr pTextElem3 = makeTextElement(element.description);
	pDescElem->addChild(pTextElem3);

	// make Property<string> name element and add to root
	SPtr pTimeElem = makeTaggedElement("TimeDate");
	pRoot->addChild(pTimeElem);
	SPtr pTextElem4 = makeTextElement(element.timeDate);
	pTimeElem->addChild(pTextElem4);

	// make Property<string> name element and add to root
	SPtr pChildElem = makeTaggedElement("Children");
	pRoot->addChild(pChildElem);
	if (element.children.size() != 0)
	{
		int i = 1;
		for (Key childkey : element.children)
		{
			SPtr pChildElem1 = makeTaggedElement("Child");
			pChildElem->addChild(pChildElem1);
			SPtr pTextElem = makeTextElement(childkey);
			pChildElem1->addChild(pTextElem);
		}
	}
	else
	{
		SPtr pChildElem1 = makeTaggedElement("Child");
		pChildElem->addChild(pChildElem1);
		SPtr pTextElem = makeTextElement("no child found");
		pChildElem1->addChild(pTextElem);
	}
	xml = doc.toString();
	//cout << xml; 
	return xml;
}

static vector<Element<StrData>> fromXml(std::string& xml)
{std::vector<Element<StrData>> vec;
	//Element<StrData> data;
	try {
	XmlDocument doc(xml, XmlDocument::str);
		std::vector<SPtr> desc = doc.descendents("Records").select();
		Element<StrData> el;
		for (auto i = 0; i != desc.size(); i++) {
			desc = doc.descendents("Name").select();
			std::string name_value = desc[i]->children()[i]->value();		
			name_value = trim(name_value);
			el.name = name_value; 
			desc = doc.descendents("Category").select();
			std::string category_value = desc[i]->children()[i]->value();
			category_value = trim(category_value);
			el.category = category_value;
			desc = doc.descendents("Description").select();
			std::string description_value = desc[i]->children()[i]->value();
			description_value = trim(description_value);
			el.description = description_value;
			desc = doc.descendents("Children").select();
			std::vector<std::string> children1;
			 children1.push_back(trim(desc[i]->children()[i]->value()));
			for (Key childkey : children1)
			{
				children1.push_back(trim(childkey));
				el.children = children1;
			}
		desc = doc.descendents("TimeDate").select();
			std::string timedate_value = desc[i]->children()[i]->value();
			timedate_value = trim(timedate_value);
			el.timeDate = timedate_value;
			desc = doc.descendents("Data").select();
			std::string data_value = desc[i]->children()[i]->value();
			data_value = trim(data_value);
			el.data = data_value;
			vec.push_back(el);
		}
		}
	catch (std::exception& ex)
	{
		std::cout << "\n  something bad happend";
		std::cout << "\n  " << ex.what();
	}

	return vec;
}


string currenttime() {

	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", timeinfo);
	std::string str(buffer);

	return str;
}

// Data persist in XML

int main()

{
	std::cout << "\n  Building a NOSQL Database like MONGODB, REDIS etc.";
	std::cout << "\n =========================================================n";
	std::cout << "\n  QUERING DATABASE AND ALSO PERSISTING THE CONTENTS TO XML FILE";
	std::cout << "\n =========================================================\n";

	std::cout << "\n  Requirement 10 : Showing the package and file structure in NOSQLDB";
	std::cout << "\n ==================================================\n";


	std::cout << "\n Creating and saving InMemory Package Structure with string data";
	std::cout << "\n -------------------------------------------------------\n";
	
	
	NoSqlDb<StrData> db,file_structure;
	Element<StrData> record1;
	Element<StrData> record2;
	Element<StrData> record3;
	Element<StrData> record4;
	

	record1.name = "InMemoryDb";
	record1.category = "solution type";
	record1.description = "project data is stored";
	record1.data = "files are stored";
	record1.timeDate = currenttime();

	file_structure.save(record1.name, record1);

	record2.name = "Convert";
	record2.category = "reference file";
	record2.description = "sqldata data is stored";
	record2.data = "record's StrData";
	record2.timeDate = currenttime();
	
	file_structure.save(record2.name, record2);

	record3.name = "CppProperties";
	record3.category = "reference file";
	record3.description = "property data is stored";
	record3.data = "record's StrData";
	record3.timeDate = currenttime();
	file_structure.save(record3.name, record3);

	record4.name = "InMemoryDb";
	record4.category = "test executive";
	record4.description = "sqldata data is stored";
	record4.data = "record's StrData";
	record4.children.push_back("Convert");
	record4.children.push_back("CppProperties");
	record4.children.push_back("XMLDocument");
	record4.timeDate = currenttime();
	file_structure.save(record4.name, record4);

	std::cout << "\n  Retrieving File Structure from NoSqlDb Databse";
	std::cout << "\n ---------------------------------------\n";

	std::cout << "\n  size of Database = " << file_structure.count() << "\n";
	Keys filekeys = file_structure.keys();
	for (Key filekey : filekeys)
	{
		std::cout << "\n  " << filekey << ":";
		std::cout << file_structure.value(filekey).show();
	};
	std::cout << "\n  Requirement 2 and Requirement 3 : Creating and adding the records of database with string data";
	std::cout << "\n ==================================================================\n";

	Element<StrData> elem1;
	Element<StrData> elem2;
	Element<StrData> elem3;
	elem1.name = "elem1";
	elem1.category = " element1 type data";
	elem1.description = "element 1 data is stored";
	elem1.data = "elem1's StrData";
	elem1.timeDate = currenttime();
	elem1.children.push_back("elem4");
	
	db.save(elem1.name, elem1);
	
	
	elem2.name = "elem2";
	elem2.category = "test element2";
	elem2.description = "string data for  elem2";
	elem2.data = "elem2's StrData";
	elem2.children.push_back("elem1");
	elem2.children.push_back("elem4");
	elem2.children.push_back("elem5");
	elem2.timeDate = currenttime();
	
	
	
	db.save(elem2.name, elem2);


	elem3.name = "elem3";
	elem3.category = "test element3";
	elem3.description = "Element 3 data is stored";
	elem3.data = "elem3's StrData";
	elem3.children.push_back("elem1");
	elem3.children.push_back("elem2");
	elem3.timeDate = currenttime();

	db.save(elem3.name, elem3);

	for (Key newKEY : db.keys())
	{
		std::cout << "\n  " << newKEY << ":";
		std::cout << db.value(newKEY).show();
	}

	std::cout << "\n  Requirement 4 : Editing records of database with string data";
	std::cout << "\n ==================================================================\n";
	std::cout << "\n  Editing element 1 from NoSqlDb<string>";
	std::cout << "\n ---------------------------------------\n";
	Element<std::string> elemnew;
	elemnew.name = "elem8";
	elemnew.category = "test string type";
	elemnew.description = "element8 data is stored";
	elemnew.timeDate = currenttime();
	db.editElement("elem1",elemnew);

	std::cout << "\n ---------------------------------------\n";
	std::cout << "\n  Retreiving element 1 after editing";
	std::cout << "\n ---------------------------------------\n";
	cout<<db.value_return("elem1").show();


	std::cout << "\n  Requirement 4: Replacing element 3 to element 1 from NoSqlDb<string>";
	std::cout << "\n ==================================================================\n";
	
	db.replace("elem3", "elem1");

	std::cout << "\n  Retrieving all elements from NoSqlDb<string> after relacing of elem3 with elem1";
	std::cout << "\n ------------------------------------------\n";
	std::cout << "\n  size of db = " << db.count() << "\n";
	Keys keys2 = db.keys();
	for (Key key : keys2)
	{
		std::cout << "\n  " << key << ":";
		std::cout << db.value(key).show();
	}

	std::cout << "\n -----------------------------------------------------------------------\n";
	
	std::cout << "\n  Requirement 4: Adding children from NoSqlDb<int>";
	std::cout << "\n ==================================================================\n";

	Element<std::string> em1;
	std::vector<std::string> childvector;
	childvector.push_back("elem1");
	childvector.push_back("elem2");

	db.addChild("elem1", childvector);
	std::cout << "\n ---------------------------------------------------------------------\n";

	std::cout << "\n  Retrieving element element 1 from NoSqlDb<string> after adding children to element 1 \n";

	std::cout << "\n ---------------------------------------------------------------------\n";

	cout<<db.value_return("elem1").show();

	std::cout << "\n -----------------------------------------------------------------------\n";

	std::cout << "\n  Requirement 4: Deleting collection of children from NoSqlDb<int> from element 1";
	std::cout << "\n ==================================================================\n";
	
	db.deleteChild("elem1", childvector);
	

	std::cout << "\n ---------------------------------------------------------------------\n";

	std::cout << "\n  Retrieving element 1 from NoSqlDb<string> after deleting children to element 1 \n";

	std::cout << "\n ---------------------------------------------------------------------\n";

	cout << db.value_return("elem1").show();

	std::cout << "\n -----------------------------------------------------------------------\n";

	std::cout << "\n  Requirement 7.1: Retreiving elements of specific key";
	std::cout << "\n ==================================================================\n";
	cout<<db.value_return("elem2").show();
	
	std::cout << "\n  Requirement 7.2:Retrieving children from NoSqlDb<string> \n";
	std::cout << "\n ==================================================================\n";
	//Element<std::string> element;
	std::vector<std::string> childs;
	childs =	db.child_return("elem3");
	int j = 1;
	for (Key child_key : childs)
	{
		cout <<"\n Children"<<j<<"		:		" <<  child_key;
		cout << "\n";
		j++;
	}
	std::cout << "\n Requirement 7.3 : Retrieving keys from NoSqlDb<string> of specific type with first four letters as elem \n";
	std::cout << "\n ========================================================================================\n";

	std::vector<std::string> key_element;
	key_element = db.key_return("elem",4);
	int k = 1;
	for (Key elem_key : key_element)
	{
		cout << "\n Element Keys"<<k<<"		:		" << elem_key;
		cout << "\n";
		k++;
	}
	std::cout << "\n\n";
	std::cout << "\n Requirement 7.4 : Retrieving keys from NoSqlDb<string> of specific string in";
	std::cout <<"\n item name where string is elem in item name \n";
	std::cout << "\n ===============================================================================\n";
	Element<std::string> el;
	std::vector<std::string> key_name;
	//cout << "records" << el.show();
	key_name = db.name_key("elem");
	
	int l = 1;
	for (Key elem_key : key_name)
	{
		
		cout << "\n Element Keys" << l << "		:		" << elem_key;
		cout << "\n";
		l++;
	}

	std::cout << "\n";
	std::cout << "\n  Requirement 7.5 : Retrieving keys from NoSqlDb<string> of specific string in item category";
		cout<<"\n with category as test";
	std::cout << "\n ========================================================================================\n";
	//Element<std::string> el;
	std::vector<std::string> key_category;
	//cout << "records" << el.show();
	key_category = db.category_key("test");

	int m = 1;
	for (Key elem_key : key_category)
	{

		cout << "\n Element Keys" << m << "		:		" << elem_key;
		cout << "\n";
		m++;
	}
	std::cout << "\n\n";


	std::cout << "\n\n";
	std::cout << "\n Requirement 7.6 : Retrieving keys from NoSqlDb<string> of specific string as StrData in item data \n";
	std::cout << "\n =============================================================================================\n";
	//Element<std::string> el;
	std::vector<std::string> key_data;
	//cout << "records" << el.show();
	key_data = db.data_key("StrData");

	int n = 1;
	cout << "\n The following elements are of string type data \n";
	for (Key elem_key : key_data)

	{

		cout << "\n Element Keys" << n << "		:		" << elem_key;
		cout << "\n";
		n++;
	}
	std::cout << "\n\n";
	std::cout << "\n  Requirement 9 : Union of Queries of name key and key return of Requirement 7.3 and 7.4 ";
	std::cout << "\n =======================================================================================";
	std::set<std::string> s;

	std::vector<std::string> vector1 = key_element;
	
	std::vector<std::string> vector2 = key_name;

	s = db.unionofkeys(vector1, vector2);
	int o = 1;
	for (Key k : s)
	{
		cout << "Element Data"<<o<<"		:"<<k;
		std::cout << "\n\n";
		o++;
	}
	std::cout << "\n\n";
	std::cout << "\n Requirement 8 : Intersection of Queries of name key and key return of Requitement 7.3 and 7.4";
	std::cout << "\n ===========================================================================================";
	std::set<std::string> store_result;

	std::vector<std::string> vector3 = key_element;

	std::vector<std::string> vector4 = key_name;

	store_result = db.intersection(vector3, vector4);
	int y = 1;
	for (Key type : store_result)
	{
		cout << "Element Data" << y << "		:" << type;
		std::cout << "\n\n";
		y++;
	}
	std::cout << "\n\n";
	std::cout << "\n  Requirement 7.7 : Retrieving keys from NoSqlDb<string> of specific time interval from a given start time to current time  \n";
	std::cout << "\n ==============================================================================================================";
	std::vector<std::string> key_time;
	
	key_time = db.time_interval("07-02-2016 09:12:12",currenttime());

	int m1 = 1;
	for (Key elem_key : key_time)
	{
		cout << "\n Element Key #" << m1 << "		:		" << elem_key;
		cout << "\n";
		m1++;
	}
	std::cout << "\n\n";
	

	std::cout << "\n  Requirement 2 and 3 for Integer Type :Creating and saving NoSqlDb elements with int data";
	std::cout << "\n ============================================================================";

	NoSqlDb<intData> idb;

	Element<intData> ielem1;
	ielem1.name = "elem1";
	ielem1.category = "test";
	ielem1.data = 1;
	ielem1.timeDate = currenttime();

	idb.save(ielem1.name, ielem1);

	Element<intData> ielem2;
	ielem2.name = "elem2";
	ielem2.category = "test";
	ielem2.data = 2;
	ielem2.timeDate = currenttime();

	idb.save(ielem2.name, ielem2);
	Element<intData> ielem3;
	ielem3.name = "elem3";
	ielem3.category = "test";
	ielem3.data = 3;
	ielem3.timeDate = currenttime();

	idb.save(ielem3.name, ielem3);

	Element<intData> ielem4;
	ielem4.name = "elem4";
	ielem4.category = "test";
	ielem4.data = 4;
	ielem4.timeDate = currenttime();

	idb.save(ielem4.name, ielem4);

	Keys intkeys = idb.keys();
	for (Key key : intkeys)
	{
		std::cout << "\n  " << key << ":";
		std::cout << idb.value(key).show();
	}

	std::cout << "\n Requirement 3 : Deleting elements from NoSqlDb<int> for integer type";
	std::cout << "\n ===========================================================================";
	idb.deletion("elem4");

	
	std::cout << "\n  Retrieving elements from NoSqlDb<int> after deleting elemen4";
	std::cout << "\n ---------------------------------------\n";

	std::cout << "\n  size of idb = " << idb.count() << "\n";
	Keys ikeys = idb.keys();
	for (Key key : ikeys)
	{
		std::cout << "\n  " << key << ":";
		std::cout << idb.value(key).show();
	}
	// Persistance code

	std::cout << "\n -----------------------------------------------------------------------\n";

	std::cout << "\n  Requirement 5: Persisting the contents to XML file";
	std::cout << "\n ==================================================================\n";
	Element<StrData> element1,element_xml;

	std::string xml,str1,str2;
	std::fstream fs;
	fs.open("nosqldb.xml",std::ios::app);

	for (Key key : db.keys())
	{
		
		//cout << "KEY" << key;
		// element1 = 
		element1 = db.element_return(key);
		///std::cout << "\n new element\n\n";
		xml=toXml(element1);
		std::cout << "\n" << xml;
		fs << xml;
		
	}
	std::cout << "\n -----------------------------------------------------------------------\n";

	std::cout << "\n Requirement 5: Getting the contents from XML file and storing it in database ";
	std::cout << "\n Augmenting Element 5 and Deleting element 3";
	std::cout << "\n ==================================================================\n";
	vector<Element<StrData>> vec1;
	vec1 = fromXml(xml);
	Element<StrData> elem_xml;
	for (auto i = 0; i != vec1.size(); i++) {

		element_xml.name = vec1[i].name;
		element_xml.category = vec1[i].category;
		element_xml.description = vec1[i].description;
		element_xml.timeDate = vec1[i].timeDate;
		element_xml.data = vec1[i].timeDate;
		element_xml.children = vec1[i].children;
	//	cout << "show" << element_xml.show();
	db.save(element_xml.name, element_xml);
	}

	fs.close();
	
	
	
	std::cout << "\n\n";

	db.deletion("elem3");
	//Element<StrData> newX;
	element_xml.name = "elem5";
	element_xml.category = "TEST CATEGORY-(AUGMENTED)";
	element_xml.timeDate = "2017/31/05  19:34:32";
	element_xml.data = "TEST DATA-(AUGMENTED)";
	element_xml.description = "Augmented Data";
	//newX.addchild("elem5","elem6");
	db.save("elem5",element_xml);
	//counter++;
	std::cout << "\n ---------------------------------------\n";
	std::cout << "\n  Retrieving elements from NoSqlDb<int> after implementing Requirement 5";
	std::cout << "\n ---------------------------------------\n";
	for (Key newKEY : db.keys())
	{
		std::cout << "\n  " << newKEY << ":";
		std::cout << db.value(newKEY).show();
	}

	//Persistance code
	std::cout << "\n\n";
	std::cout << "\n Requirement 12 : Support regular expression matching for the query type with";
	std::cout << "\n specific string and here item category should hold first four characters as test \n";
	std::cout << "\n =======================================================================================\n";

	std::vector<std::string> key_search;
	//cout << "records" << el.show();
	key_search = db.search_rejex();

	int v = 1;
	for (Key elem_key : key_search)
	{

		cout << "\n Element Keys" << v << "		:		" << elem_key;
		cout << "\n";
		v++;
	}
	std::cout << "\n";
	char ch;
	std::cin >> ch;

	getchar();
}
// #endif // DEBUG

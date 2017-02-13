// Help.cpp - Help Session demo 1/27/2017

#include "../XmlDocument/XmlDocument/XmlDocument.h"
#include "../XmlDocument/XmlElement/XmlElement.h"
#include "../HelpSessionDemo/CppProperties/CppProperties.h"
#include "../HelpSessionDemo/Convert/Convert.h"
#include "../StrHelper.h"

#include "Help.h"

using namespace XmlProcessing;
using SPtr = std::shared_ptr<AbstractXmlElement>;

std::string toXml(const X& x)
{
  std::string xml;
  XmlDocument doc;
  SPtr pRoot = makeTaggedElement("X");
  doc.docElement() = pRoot;

  // make Property<string> name element and add to root
  SPtr pNameElem = makeTaggedElement("name");
  pRoot->addChild(pNameElem);
  SPtr pTextElem = makeTextElement(x.name);
  pNameElem->addChild(pTextElem);

  // make Property<double> pi element and add to root
  SPtr pPiElem = makeTaggedElement("pi");
  pRoot->addChild(pPiElem);
  double pi = x.pi;
  std::string piString = Convert<double>::toString(pi);
  pTextElem = makeTextElement(piString);
  pPiElem->addChild(pTextElem);

  xml = doc.toString();
  return xml;
}

X fromXml(const std::string& xml)
{
  X x;
  try {
    std::cout << "\n  X.name = " << x.name;
    std::cout << "\n  x.pi = " << x.pi;

    XmlDocument doc(xml, XmlDocument::str);

    // fetch the name string from XML element
    std::vector<SPtr> desc = doc.descendents("name").select();
    std::string name_value = desc[0]->children()[0]->value();
    //std::cout << "\n  indented value of name = " << name_value;
    name_value = trim(name_value);
    x.name = name_value;

    // fetch the pi string from XML Element and convert to doubl
    desc = doc.descendents("pi").select();
    std::string piString = desc[0]->children()[0]->value();
    x.pi = Convert<double>::fromString(piString);
  }
  catch (std::exception& ex)
  {
    std::cout << "\n  something bad happend";
    std::cout << "\n  " << ex.what();
  }

  return x;
}

int main()
{
  X x;
  x.name = "Yadav";
  x.pi = 3.14;
  std::cout << "\n  X.name = " << x.name;
  std::cout << "\n  x.pi = " << x.pi;

  std::string xml = toXml(x);
  std::cout << "\n  X xml string:" << xml;

  X newX = fromXml(xml);
  std::cout << "\n  newX.name = " << newX.name;
  std::cout << "\n  newX.pi = " << newX.pi;

  std::cout << "\n\n";
}
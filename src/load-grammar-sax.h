#ifndef __RTZassistSax__
#define __RTZassistSax__

#include <iostream>
#include <string>
#include <memory>   // std::auto_ptr
#include <cstddef>  // std::size_t
#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMNode.hpp>
#include <xercesc/dom/DOMText.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/framework/XMLGrammarPoolImpl.hpp>
#include <xercesc/framework/Wrapper4InputSource.hpp>
#include <xercesc/dom/DOMDocument.hpp>  
#include "RTZassistUI.h"


//void write(XERCES_CPP_NAMESPACE::DOMNode* node);
//void writeElement(XERCES_CPP_NAMESPACE::DOMElement* element);
//void writeText(XERCES_CPP_NAMESPACE::DOMText* text);



int mainParser(int argc, const char* args[]);

#endif
#include "load-grammar-sax.h"
#include <fstream>
#include <wx/msgdlg.h>

class loadgrammarsax;

using namespace std;
using namespace xercesc;

//void write(XERCES_CPP_NAMESPACE::DOMNode* node);
//void writeElement(DOMElement* element);
//void writeText(DOMText* text);

FILE *ofp;

class loadgrammarsax
{

public:

	loadgrammarsax();
	~loadgrammarsax();

	void testMessage();
	loadgrammarsax* mySax;

};



/**/

loadgrammarsax::loadgrammarsax()
{
	mySax = new loadgrammarsax;
}

loadgrammarsax::~loadgrammarsax()
{

}

void loadgrammarsax::testMessage() {
	wxMessageBox("here");

}

void writeElement(DOMElement* element) {
	char* name = XMLString::transcode(element->getTagName());

	fprintf(ofp,"tag    : " );
	fprintf(ofp,name);
	fprintf(ofp, "\n");

	
	XMLString::release(&name);

	DOMNamedNodeMap* map = element->getAttributes();
	for (XMLSize_t i = 0; i < map->getLength(); i++) {
		DOMAttr* attr = static_cast<DOMAttr*>(map->item(i));
		char* attr_name = XMLString::transcode(attr->getName());
		char* attr_value = XMLString::transcode(attr->getValue());

		fprintf(ofp, attr_name);
		fprintf(ofp, ": ");
		fprintf(ofp, attr_value);
		fprintf(ofp, "\n");
		
		XMLString::release(&attr_name);
		XMLString::release(&attr_value);
	}
}

void writeText(DOMText* text) {
	

	XMLCh* buffer = new XMLCh[XMLString::stringLen(text->getData()) + 1];
	XMLString::copyString(buffer, text->getData());
	XMLString::trim(buffer);
	char* content = XMLString::transcode(buffer);
	
	//wxMessageBox(content);

	delete[] buffer;

	fprintf(ofp,"content: " );
	fprintf(ofp, content);
	fprintf(ofp, "\n");

	
	XMLString::release(&content);
}

void write(XERCES_CPP_NAMESPACE::DOMNode* node) {
	if (node) {
		switch (node->getNodeType()) {
		case DOMNode::ELEMENT_NODE:
			writeElement(static_cast<DOMElement*>(node));
			break;
		case DOMNode::TEXT_NODE:
			writeText(static_cast<DOMText*>(node));
			break;
		}

		DOMNode* child = node->getFirstChild();
		while (child) {
			DOMNode* next = child->getNextSibling();
			write(child);
			child = next;
		}
	}
}



int mainParser(int argc, const char* args[]) {

	
	ofp = fopen("dom_out.txt", "w");
	string forTextBox = "";

	try {
		XMLPlatformUtils::Initialize();
	}
	catch (const XMLException& toCatch) {
		char* message = XMLString::transcode(toCatch.getMessage());
		fprintf(ofp, "Error during initialization! :\n");
		fprintf(ofp, message );
		fprintf(ofp, "\n");
				
		XMLString::release(&message);

		return 1;
	}

	XercesDOMParser* parser = new XercesDOMParser();
	parser->setValidationScheme(XercesDOMParser::Val_Always);
	parser->setDoNamespaces(true); // optional

	ErrorHandler* errHandler = (ErrorHandler*) new HandlerBase();
	parser->setErrorHandler(errHandler);
//"NCA_Ardalstangen_Holmengra_In_20200115.rtz"

	const char* xmlFile = args[1];

	try {
		parser->parse(xmlFile);
		XERCES_CPP_NAMESPACE::DOMDocument* dom = parser->getDocument();
		write(dom);

	}
	catch (const XMLException& toCatch) {
		char* message = XMLString::transcode(toCatch.getMessage());

		fprintf(ofp, "Exception message is: \n");
		fprintf(ofp, message);
		fprintf(ofp, "\n");
		
		XMLString::release(&message);
		return -1;
	}
	catch (const DOMException& toCatch) {
		char* message = XMLString::transcode(toCatch.msg);
		
		fprintf(ofp, "Exception message is: \n");
		fprintf(ofp, message);
		fprintf(ofp, "\n");

		XMLString::release(&message);
		return -1;
	}
	catch (...) {

		fprintf(ofp, "Unexpected Exception \n");
		return -1;
	}

	fclose(ofp);

	delete parser;
	delete errHandler;
	return 0;
}
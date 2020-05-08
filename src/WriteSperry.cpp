
#include <iostream>
#include <string>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>
#include <xercesc/framework/XMLFormatter.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationRegistry.hpp>
#include <xercesc/dom/DOMLSSerializer.hpp>
#include <xercesc/dom/DOMLSOutput.hpp>
#include "WriteSperry.h"
#include <fstream>
#include <wx/msgdlg.h>

#include <windows.h>

using namespace xercesc;
using namespace std;

FILE *ofxml;

class XStr
{
public:
	XStr(const char* const toTranscode)
	{
		// Call the private transcoding method
		fUnicodeForm = XMLString::transcode(toTranscode);
	}

	~XStr()
	{
		XMLString::release(&fUnicodeForm);
	}

	const XMLCh* unicodeForm() const
	{
		return fUnicodeForm;
	}

private:
	XMLCh*   fUnicodeForm;
};

#define X(str) XStr(str).unicodeForm()

int mainWriter(int argc, char* args[])
{
	ofxml = fopen("dom_xml.txt", "w");
	fclose(ofxml);


	try
	{
		XMLPlatformUtils::Initialize();
	}
	catch (const XMLException& e)
	{
		char* message = XMLString::transcode(e.getMessage());

		wxMessageBox(message, "Error Message");
		//cout << "Error Message: " << message << "\n";
		XMLString::release(&message);
		return 1;
	}

	int errorCode = 0;
	{

		DOMImplementation* impl = DOMImplementationRegistry::getDOMImplementation(X("Core"));

		if (impl != NULL)
		{
			try
			{
				xercesc::DOMDocument* doc = impl->createDocument(
					0,                    // root element namespace URI.
					X("company"),         // root element name
					0);                   // document type object (DTD).

				DOMElement* rootElem = doc->getDocumentElement();

				DOMElement*  prodElem = doc->createElement(X("product"));
				rootElem->appendChild(prodElem);

				DOMText*    prodDataVal = doc->createTextNode(X("Xerces-C"));
				prodElem->appendChild(prodDataVal);

				DOMElement*  catElem = doc->createElement(X("category"));
				rootElem->appendChild(catElem);

				catElem->setAttribute(X("idea"), X("great"));

				DOMText*    catDataVal = doc->createTextNode(X("XML Parsing Tools"));
				catElem->appendChild(catDataVal);

				DOMElement*  devByElem = doc->createElement(X("developedBy"));
				rootElem->appendChild(devByElem);

				DOMText*    devByDataVal = doc->createTextNode(X("Apache Software Foundation"));
				devByElem->appendChild(devByDataVal);

				//OutputXML(doc, "dom_xml.txt");

				doc->release();
			}
			catch (const OutOfMemoryException&)
			{
				XERCES_STD_QUALIFIER cerr << "OutOfMemoryException" << XERCES_STD_QUALIFIER endl;
				errorCode = 5;
			}
			catch (const DOMException& e)
			{
				XERCES_STD_QUALIFIER cerr << "DOMException code is:  " << e.code << XERCES_STD_QUALIFIER endl;
				errorCode = 2;
			}
			catch (const XMLException& e)
			{
				char* message = XMLString::transcode(e.getMessage());

				wxMessageBox(message, "Error Message");
				//cout << "Error Message: " << message << endl;
				XMLString::release(&message);
				return 1;
			}
			catch (...)
			{
				XERCES_STD_QUALIFIER cerr << "An error occurred creating the document" << XERCES_STD_QUALIFIER endl;
				errorCode = 3;
			}
		}  // (inpl != NULL)
		else
		{
			XERCES_STD_QUALIFIER cerr << "Requested implementation is not supported" << XERCES_STD_QUALIFIER endl;
			errorCode = 4;
		}
	}

	XMLPlatformUtils::Terminate();

	return errorCode;
}
/*
void OutputXML(xercesc::DOMDocument* pmyDOMDocument, std::string filePath)
{
	//Return the first registered implementation that has the desired features. In this case, we are after a DOM implementation that has the LS feature... or Load/Save. 
	static const XMLCh gLS[] = { chLatin_L, chLatin_S, chNull };
	DOMImplementation *implementation = DOMImplementationRegistry::getDOMImplementation(gLS);

	// Create a DOMLSSerializer which is used to serialize a DOM tree into an XML document. 
	DOMLSSerializer *serializer = ((DOMImplementationLS*)implementation)->createLSSerializer();

	// Make the output more human readable by inserting line feeds. 
	if (serializer->getDomConfig()->canSetParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true))
		serializer->getDomConfig()->setParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true);

	// The end-of-line sequence of characters to be used in the XML being written out.  
	serializer->setNewLine(XMLString::transcode("\r\n"));

	// Convert the path into Xerces compatible XMLCh*. 
	XMLCh *tempFilePath = XMLString::transcode(filePath.c_str());

	// Specify the target for the XML output. 
	XMLFormatTarget *formatTarget = new LocalFileFormatTarget(tempFilePath);

	// Create a new empty output destination object. 
	DOMLSOutput *output = ((DOMImplementationLS*)implementation)->createLSOutput();

	// Set the stream to our target. 
	output->setByteStream(formatTarget);

	// Write the serialized output to the destination. 
	serializer->write(pmyDOMDocument, output);

	// Cleanup. 
	serializer->release();
	XMLString::release(&tempFilePath);
	delete formatTarget;
	output->release();
}*/
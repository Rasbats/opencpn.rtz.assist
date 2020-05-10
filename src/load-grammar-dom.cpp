

#include "load-grammar-dom.h"
#include "RTZassistPanelMain.h"

class RTZassistPanelMain;

using namespace std;
using namespace xercesc;

FILE* ofp2;

class error_handler : public DOMErrorHandler
{
public:
	error_handler() : failed_(false) {}

	bool
		failed() const { return failed_; }

	virtual bool
		handleError(const xercesc::DOMError&);

private:
	bool failed_;
};

DOMLSParser* create_parser(XMLGrammarPool* pool)
{
	const XMLCh ls_id[] = { chLatin_L, chLatin_S, chNull };

	DOMImplementation* impl(
		DOMImplementationRegistry::getDOMImplementation(ls_id));

	DOMLSParser* parser(
		impl->createLSParser(
			DOMImplementationLS::MODE_SYNCHRONOUS,
			0,
			XMLPlatformUtils::fgMemoryManager,
			pool));

	DOMConfiguration* conf(parser->getDomConfig());

	// Commonly useful configuration.
 //
	conf->setParameter(XMLUni::fgDOMComments, false);
	conf->setParameter(XMLUni::fgDOMDatatypeNormalization, true);
	conf->setParameter(XMLUni::fgDOMEntities, false);
	conf->setParameter(XMLUni::fgDOMNamespaces, true);
	conf->setParameter(XMLUni::fgDOMElementContentWhitespace, false);

	// Enable validation.
	//
	conf->setParameter(XMLUni::fgDOMValidate, true);
	conf->setParameter(XMLUni::fgXercesSchema, true);
	conf->setParameter(XMLUni::fgXercesSchemaFullChecking, false);

	// Use the loaded grammar during parsing.
	//
	conf->setParameter(XMLUni::fgXercesUseCachedGrammarInParse, true);

	// Don't load schemas from any other source (e.g., from XML document's
	// xsi:schemaLocation attributes).
	//
	conf->setParameter(XMLUni::fgXercesLoadSchema, false);

	// Xerces-C++ 3.1.0 is the first version with working multi
	// import support.
	//

	// Xerces-C++ 3.1.0 is the first version with working multi
	// import support.
	//
#if _XERCES_VERSION >= 30100
	conf->setParameter(XMLUni::fgXercesHandleMultipleImports, true);
#endif

	// We will release the DOM document ourselves.
	//
	conf->setParameter(XMLUni::fgXercesUserAdoptsDOMDocument, true);

	return parser;
}

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
}


int mainValidator(int argc, const char* argv[])
{

	//wxMessageBox(myPanel->testString);

	string startURI = "file:///";

	char* fileName = "XML_errors_out.txt";
	ofp2 = fopen(fileName, "w");

	if (argc < 2)
	{
		fprintf(ofp2, "usage:  \n");
		fprintf(ofp2, " [test.xsd ... ] [test.xml ...]");
		fprintf(ofp2, "\n");
		return 1;
	}

	XMLPlatformUtils::Initialize();

	int r(0);

	while (true)
	{
		MemoryManager* mm(XMLPlatformUtils::fgMemoryManager);
		unique_ptr<XMLGrammarPool> gp(new XMLGrammarPoolImpl(mm));

		int i(1);

		// Load the schemas into grammar pool.
		//
		{
			DOMLSParser* parser(create_parser(gp.get()));

			error_handler eh;
			parser->getDomConfig()->setParameter(XMLUni::fgDOMErrorHandler, &eh);

			wxFileName file;
			wxString path_and_file;

			file.Assign(argv[0]);         // mist.txt in current directory
			file.MakeAbsolute();
			path_and_file = file.GetFullPath(); // returns abs. path with file and ext.
			//path = file.GetPath();     // returns abs. path only

			//fprintf(ofp2, path_and_file + "\n");
            string pf = std::string(path_and_file);
			string s = startURI + pf;  //  "file:///C:/Projects/RTZassist/rtz-sax/build/Debug/RTZSchemaversion1_0.xsd";



			for (; i < argc; ++i)
			{

				size_t n(s.size());

				if (n < 5 || s[n - 4] != '.' || s[n - 3] != 'x' ||
					s[n - 2] != 's' || s[n - 1] != 'd')
					break;

				//cerr << "loading " << s << endl;

				if (!parser->loadGrammar(s.c_str(), Grammar::SchemaGrammarType, true))
				{
					fprintf(ofp2, "'%s'", s);
					fprintf(ofp2, ": error: unable to load");
					fprintf(ofp2, "\n");
					r = 1;
					break;
				}

				if (eh.failed())
				{
					r = 1;
					break;
				}
			}

			parser->release();

			if (r != 0)
				break;
		}

		// Lock the grammar pool. This is necessary if we plan to use the
		// same grammar pool in multiple threads (this way we can reuse the
		// same grammar in multiple parsers). Locking the pool disallows any
		// modifications to the pool, such as an attempt by one of the threads
		// to cache additional schemas.
		//
		gp->lockPool();

		// Parse the XML documents.
		//
		DOMLSParser* parser(create_parser(gp.get()));

		error_handler eh;
		parser->getDomConfig()->setParameter(XMLUni::fgDOMErrorHandler, &eh);

		wxFileName file1;
		wxString path_and_file1;

		file1.Assign(argv[1]);         // mist.txt in current directory
		file1.MakeAbsolute();
		path_and_file1 = file1.GetFullPath();
        string pf1 = std::string(path_and_file1);
		string st = startURI + pf1;  // "file:///C:/Projects/RTZassist/rtz-sax/build/Debug/NCA_Ardalstangen_Holmengra_In_20200115.rtz";

		//fprintf(ofp2, "here\n");

		i = 1;

		for (; i < argc; ++i)
		{
			//fprintf(ofp2, "parsing ");
			//fprintf(ofp2, argv[i]);
			//fprintf(ofp2, "\n");



			XERCES_CPP_NAMESPACE::DOMDocument* doc(parser->parseURI(st.c_str()));

			//fprintf(ofp2, "here2\n");

			//OutputXML(doc, "Parser.rtz" );

			if (doc)

				doc->release();

			if (eh.failed())
			{
				r = 1;
				break;
			}
		}

		parser->release();
		break;
	}
	fclose(ofp2);
	XMLPlatformUtils::Terminate();



	return r;
}

bool error_handler::handleError(const xercesc::DOMError& e)
{
	bool warn(e.getSeverity() == DOMError::DOM_SEVERITY_WARNING);

	if (!warn)
		failed_ = true;

	DOMLocator* loc(e.getLocation());

	char* uri(XMLString::transcode(loc->getURI()));
	char* msg(XMLString::transcode(e.getMessage()));

	int gln = loc->getLineNumber();
	int gcn = loc->getColumnNumber();

	std::string sgln = std::to_string(gln);
	std::string sgcn = std::to_string(gcn);

	fprintf(ofp2, uri);
	fprintf(ofp2, ":");

	fprintf(ofp2, sgln.c_str());
	fprintf(ofp2, ":");
	fprintf(ofp2, sgcn.c_str());

	fprintf(ofp2, "\n");
	fprintf(ofp2, msg);

	XMLString::release(&uri);
	XMLString::release(&msg);

	return true;
}

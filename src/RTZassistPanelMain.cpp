#include "RTZassistPanelMain.h"
#include "load-grammar-sax.h"
#include "load-grammar-dom.h"
//#include "WriteSperry.h"
//#include "WriteRouteFile.h"

#include "wx/dir.h"
#include <wx/filedlg.h>
#include <wx/wfstream.h>
#include <wx/txtstrm.h>
#include <iostream>
#include <algorithm>

#include "tinyxml2.h"

class waypoint;
class route;


RTZassistPanelMain::RTZassistPanelMain( wxWindow* parent )
:
PanelMain( parent )
{
	// fill the combobox with the schemas
	wxArrayString items;
	items.Add("RTZ_Schema_version_1_0.xsd");
	items.Add("RTZ_Schema_version_1_1.xsd");
	m_choiceSchema->Set(items);
	m_choiceSchema->SetSelection(0);

};



void RTZassistPanelMain::OnReadGPX(wxCommandEvent& event)
{

	if(ReadGPX()) GPXtoWaypoints(filename);

}


bool RTZassistPanelMain::ReadGPX()
{
	int response = wxID_CANCEL;
	int my_count = 0;

	wxArrayString file_array;

	wxString m_gpx_path;
	wxFileDialog openDialog(this, _("Import GPX Route file"), m_gpx_path, wxT(""),
		wxT("GPX files (*.gpx)|*.gpx|All files (*.*)|*.*"),
		wxFD_OPEN );
	response = openDialog.ShowModal();
	if (response == wxID_OK) {
		openDialog.GetPaths(file_array);

		//    Record the currently selected directory for later use
		if (file_array.GetCount()) {
			wxFileName fn(file_array[0]);
			filename = file_array[0];
			m_gpx_path = fn.GetPath();
			return true;
		}
	}
	else if (response = wxID_CANCEL) {
		return false;
	}

}

route RTZassistPanelMain::GPXtoWaypoints(wxString myGPX) {

	waypoint myPoint;

	tinyxml2::XMLDocument doc;
	doc.LoadFile(myGPX);

	// Let's make sure the file loaded fine...
	if (doc.ErrorID() == 0) {

		m_waypointList.clear();
		waypointsList.clear();

		tinyxml2::XMLElement *pRoot = doc.RootElement();

		// This is set to the first element named "rte" in the file

		wxString nm;
		wxString temp  = "";

		size_t it = 1;

		int i = 0;
		for (tinyxml2::XMLElement* e = pRoot->FirstChildElement(); e; e = e->NextSiblingElement(), i++) {

			for (tinyxml2::XMLElement* f = e->FirstChildElement(); f; f = f->NextSiblingElement()) {
				if (!strcmp(f->Value(), "name")) {
					nm = f->GetText();
					myRoute.routeName = nm;


				}

				if (!strcmp(f->Value(), "rtept")) {
					wxString pt_lat = wxString::FromUTF8(f->Attribute("lat"));
					wxString pt_lon = wxString::FromUTF8(f->Attribute("lon"));

					wxString pt_name;
					if (f->FirstChildElement("name") == nullptr) {
						pt_name =  "blank";
					}
					else {
						pt_name = f->FirstChildElement("name")->GetText();
					}

					temp = pt_name + "    " + pt_lat + "   " + pt_lon + "\n";

					waypointsList.Add(temp, it);

					myPoint.lat = pt_lat;
					myPoint.lon = pt_lon;
					myPoint.name = pt_name;

					m_waypointList.push_back(myPoint);

				}

			}

			myRoute.waypoints = m_waypointList;
		}
	}
	else {
		wxMessageBox("Error... returning");
	}

	//wxMessageBox("here");

	wxString myTextWaypoints = "";
	int sz = waypointsList.size();
	wxString item;
	for (int z = 0; z < sz; z++) {

		item = waypointsList.Item(z);

		myTextWaypoints += item;

	}

	m_textCtrlShowResult->SetValue(myTextWaypoints);

	return myRoute;
}

void RTZassistPanelMain::OnExportRTZ(wxCommandEvent& event) {

	if (ReadGPX()) {
		GPXtoWaypoints(filename);
	}

	int r = ExportRTZ();

}

int RTZassistPanelMain::ExportRTZ() {

	wxString rtzFileName;
	wxString fileName;
	wxFileDialog dlg(this, _("Save in RTZ format"), wxEmptyString, wxEmptyString, _T("RTZ files (*.rtz)|*.rtz|All files (*.*)|*.*"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	if (dlg.ShowModal() == wxID_CANCEL) {
		//error_occured = true;     // the user changed idea...
		return 999;
	}
	else {

		//dlg.ShowModal();
		fileName = dlg.GetPath();
		rtzFileName = dlg.GetFilename();
		//  std::cout<<s<< std::endl;
		if (dlg.GetPath() == wxEmptyString) {
			wxMessageBox("Error");
			return 999;
		}
	}


	// put the correct version in the RTZ file
	wxString versn;
	int selection = m_choiceSchema->GetSelection();

	if (selection == 0) {
		versn = "1.0";
	}
	else
		if (selection == 1) {
			versn = "1.1";
		}


	// Create Main level XML container
	tinyxml2::XMLDocument xmlDoc;
	tinyxml2::XMLDeclaration* decl = xmlDoc.NewDeclaration();

	if (selection == 0) {
		decl->SetValue("xml version=""\"1.0\" " "encoding=""\"UTF-8\" " "standalone=""\"no\"");
	}
	else
		if (selection == 1) {
			decl->SetValue("xml version=""\"1.0\" " "encoding=""\"UTF-8\"");
		}

	xmlDoc.LinkEndChild(decl);

	// Create XML root node called animals
	tinyxml2::XMLElement* pRoot = xmlDoc.NewElement("route");

	const char* value;
	if (selection == 0) {
		value = "http://www.cirm.org/RTZ/1/0";
	}
	else if (selection == 1) {
		value = "http://www.cirm.org/RTZ/1/1";
	}

	char* sv = (const_cast<char*>((const char*)versn.mb_str()));

	pRoot->SetAttribute("xmlns", value);
	pRoot->SetAttribute("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");

	if (selection == 0) {
		pRoot->SetAttribute("xmlns:xsd", "http://www.w3.org/2001/XMLSchema");
	}

	pRoot->SetAttribute("version", sv);

	if (selection == 1) {
		pRoot->SetAttribute("xmlns:stm", "http://stmvalidation.eu/STM/1/0/0");
	}

	// Add pRoot to xmlDoc after prolog
	xmlDoc.InsertEndChild(pRoot);

	// ************* Add routeInfo to root node *******

	tinyxml2::XMLElement* routeInfo = xmlDoc.NewElement("routeInfo");
	pRoot->InsertFirstChild(routeInfo);

	// Route name must be the same as the file name, without file extension

	int fl = rtzFileName.length();
	wxString rtzFileBit = rtzFileName.SubString(0, (fl - 5));

	char* rtzFN = (const_cast<char*>((const char*)rtzFileBit.mb_str()));
	routeInfo->SetAttribute("routeName", rtzFN);

	// Insert cat's name as first child of animal


	// ************* Add waypoints *******
	waypoints = xmlDoc.NewElement("waypoints");
	pRoot->InsertEndChild(waypoints);

	int nm = m_waypointList.size();
	if (nm == 0) {
		wxMessageBox("No waypoints available", "Warning");
		return 999;
	}

	int idn = 0;

	for (std::vector<waypoint>::iterator itOut = m_waypointList.begin(); itOut != m_waypointList.end(); itOut++) {


		tinyxml2::XMLElement*m_waypoint = xmlDoc.NewElement("waypoint");
		waypoints->InsertEndChild(m_waypoint);
		wxString myIdn = wxString::Format(wxT("%i"), idn);
		m_waypoint->SetAttribute("id", myIdn.mb_str());
		m_waypoint->SetAttribute("name", (*itOut).name.mb_str());


		tinyxml2::XMLElement* position = xmlDoc.NewElement("position");


		position->SetAttribute("lat", (*itOut).lat.mb_str());
		position->SetAttribute("lon", (*itOut).lon.mb_str());
		m_waypoint->InsertEndChild(position);

		idn++;

	}
	// done adding waypoints
	// Write xmlDoc into a file

	xmlDoc.SaveFile(fileName);


	return 0;
}

void RTZassistPanelMain::OnReadRTZ( wxCommandEvent& event )
{

	wxFileName f(wxStandardPaths::Get().GetExecutablePath());
	wxString appPath(f.GetPath());


	wxString schemaSelection = appPath + "/data/" + m_choiceSchema->GetStringSelection();
	if (schemaSelection == wxEmptyString) {
		wxMessageBox("Please select a schema");
		return;
	}

	wxFileDialog dlg(this, _("Select RTZ file for reading"), wxEmptyString, wxEmptyString, _T("RTZ files (*.rtz)|*.rtz|All files (*.*)|*.*"), wxFD_OPEN);
	if (dlg.ShowModal() == wxID_CANCEL) {
		//error_occured = true;     // the user changed idea...
		return;
	}
	else {

		wxString fileName = dlg.GetPath();
		//  std::cout<<s<< std::endl;
		if (dlg.GetPath() == wxEmptyString) {
			wxMessageBox("Error");
			return;
		}

		ReadRTZ(schemaSelection.ToStdString(), fileName.ToStdString());
	}

}

void RTZassistPanelMain::ReadRTZ(string schema, string rtz)
{
	int argc = 1;
	const char* args[] = { schema.c_str(), rtz.c_str() };
	int r = 0;
	r = mainParser(argc, args);

	wxString line = "";

	wxFileInputStream input("dom_out.txt");
	wxTextInputStream text(input, wxT("\x09"), wxConvUTF8);
	while (input.IsOk() && !input.Eof())
	{
		line += text.ReadLine();
		line += "\n";
		// do something with the string
	}

	m_textCtrlShowResult->SetValue(line);
}

void RTZassistPanelMain::OnValidateRTZ(wxCommandEvent& event) {

	wxString schemaSelection = "/data/" + m_choiceSchema->GetStringSelection();

	//wxMessageBox(schemaSelection);

	wxFileName f(wxStandardPaths::Get().GetExecutablePath());
	wxString appPath(f.GetPath());

	if (schemaSelection == wxEmptyString) {
		wxMessageBox("Please select a schema");
		return;
	}

	schemaSelection = appPath + schemaSelection;

	wxFileDialog dlg(this, _("Select RTZ file for validation"), wxEmptyString, wxEmptyString, _T("RTZ files (*.rtz)|*.rtz|All files (*.*)|*.*"), wxFD_OPEN);
	if (dlg.ShowModal() == wxID_CANCEL) {
		return;
	}
	else {

		wxString fileName = dlg.GetPath();
		if (dlg.GetPath() == wxEmptyString) {
			wxMessageBox("Error");
			return;
		}

		ValidateRTZ(schemaSelection.ToStdString(), fileName.ToStdString());
	}
}


void RTZassistPanelMain::ValidateRTZ(string schema, string rtz) {

	int argc = 2;
	const char* args[] = {schema.c_str(), rtz.c_str()};
	int error = 0;
	int r = 0;

	startURI = "file:///";

	r = mainValidator(argc, args);

	wxString line = "";

	if (r != 0) {
		wxMessageBox("Validation Errors", "myMessage");

		m_textCtrlShowResult->Clear();

		wxString line = "VALIDATION ERRORS FOUND:\n";

		wxFileInputStream input("XML_errors_out.txt");
		wxTextInputStream text(input, wxT("\x09"), wxConvUTF8);
		while (input.IsOk() && !input.Eof())
		{
			line += text.ReadLine();
			line += "\n";
			// do something with the string
		}

		m_textCtrlShowResult->SetValue(line);
	}
	else {
		line = "\nNo Validation Errors";
		m_textCtrlShowResult->SetValue(line);
	}
}

void RTZassistPanelMain::OnExportGPX(wxCommandEvent& event)
{

	m_textCtrlShowResult->Clear();

	wxFileName f(wxStandardPaths::Get().GetExecutablePath());
	wxString appPath(f.GetPath());


	wxString schemaSelection = appPath + "/data/" + m_choiceSchema->GetStringSelection();
	if (schemaSelection == wxEmptyString) {
		wxMessageBox("Please select a schema");
		return;
	}

	wxFileDialog dlg(this, _("Select RTZ file for reading"), wxEmptyString, wxEmptyString, _T("RTZ files (*.rtz)|*.rtz|All files (*.*)|*.*"), wxFD_OPEN);
	if (dlg.ShowModal() == wxID_CANCEL) {
		//error_occured = true;     // the user changed idea...
		return;
	}
	else {

		wxString fileName = dlg.GetPath();
		//  std::cout<<s<< std::endl;
		if (dlg.GetPath() == wxEmptyString) {
			wxMessageBox("Error");
			return;
		}

		ReadRTZ(schemaSelection.ToStdString(), fileName.ToStdString());
	}

	ExportGPX();

}


int RTZassistPanelMain::ExportGPX() {


	// temporary place holders
	route myRoute;
	waypoint myWaypoint;
	vector<waypoint> myVectorWaypoints;
	// end of placeholders

	wxString isExtension = "";

	string readFile = "dom_out.txt"; // intermediate file - make temporary?
	vector<string> myVector;

	ifstream ips;
	ips.open(readFile);
	string line;
	while (getline(ips, line))
	{
		std::string::iterator end_pos = std::remove(line.begin(), line.end(), ' ');
        line.erase(end_pos, line.end());

		myVector.push_back(line);  // hold lines of file, without white space
	}

	int c = myVector.size();

	for (int z = 0; z < c; z++) {

		if (myVector[z] == "tag:extensions") {			
			break;
		}
		
		wxStringTokenizer tokenizer(myVector[z], ":");
		while (tokenizer.HasMoreTokens())
		{
			wxString token = tokenizer.GetNextToken();
			// process token here

			if (token == "routeName") {
				myRoute.routeName = tokenizer.GetNextToken();
			}

			if (token == "tag") {
				isExtension = tokenizer.GetNextToken();
				if (isExtension == "extension") {
					break;	// this eliminates RTZ refpoints, which have lat/lon and could be misinterpreted as waypoints.
				}
			}

			if (token == "id") {
				myWaypoint.id = tokenizer.GetNextToken();
			}

			if (token == "name") {
				myWaypoint.name = tokenizer.GetNextToken();
			}

			if (token == "lat") {
				myWaypoint.lat = tokenizer.GetNextToken();
			} 

			if (token == "lon") {

				myWaypoint.lon = tokenizer.GetNextToken();
				//
				myRoute.waypoints.push_back(myWaypoint);   
				//
			}
		}
	}

	int waypointCount = myRoute.waypoints.size();

	tinyxml2::XMLDocument doc;  // main document for writing file

	tinyxml2::XMLDeclaration* decl = doc.NewDeclaration();
	decl->SetValue("xml version=""\"1.0\"");
	doc.LinkEndChild(decl);

	tinyxml2::XMLElement* root = doc.NewElement("gpx");	

	root->SetAttribute("xmlns", "test");
	root->SetAttribute("version", "1.1");
	root->SetAttribute("creator", "RTZassist_RTZ");
	root->SetAttribute("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
	root->SetAttribute("xmlns", "http://www.topografix.com/GPX/1/1");

	root->SetAttribute("xmlns:gpxx", "http://www.garmin.com/xmlschemas/GpxExtensions/v3");
	root->SetAttribute("xsi:schemaLocation", "http://www.topografix.com/GPX/1/1/gpx.xsd");
	root->SetAttribute("xmlns:opencpn", "http://www.opencpn.org");

	doc.InsertEndChild(root);

	tinyxml2::XMLElement* Route = doc.NewElement("rte");
	root->LinkEndChild(Route);

	tinyxml2::XMLElement* RouteName = doc.NewElement("name");
	Route->LinkEndChild(RouteName);
	RouteName->SetText(myRoute.routeName.mb_str());

	tinyxml2::XMLElement* Extensions = doc.NewElement("extensions");

	tinyxml2::XMLElement* StartN = doc.NewElement("opencpn:start");
	Extensions->LinkEndChild(StartN);
	StartN->SetText("Start");

	tinyxml2::XMLElement* EndN = doc.NewElement("opencpn:end");
	Extensions->LinkEndChild(EndN);
	EndN->SetText("End");

	Route->InsertEndChild(Extensions);


	// ************* Add waypoints to Route *******


	for (int i = 0; i < waypointCount; i++) {

		tinyxml2::XMLElement*m_waypoint = doc.NewElement("rtept");
				
			Route->InsertEndChild(m_waypoint);
			m_waypoint->SetAttribute("lat", myRoute.waypoints[i].lat.mb_str());
			m_waypoint->SetAttribute("lon", myRoute.waypoints[i].lon.mb_str());

			tinyxml2::XMLElement* name = doc.NewElement("name");
			m_waypoint->InsertFirstChild(name);
			name->SetText(myRoute.waypoints[i].name.mb_str());

			tinyxml2::XMLElement* symbol = doc.NewElement("sym");
			m_waypoint->InsertFirstChild(symbol);
			symbol->SetText("diamond");

			tinyxml2::XMLElement* type = doc.NewElement("type");
			m_waypoint->InsertFirstChild(type);
			type->SetText("WPT");

	}

	// done adding waypoints
	// Write doc into a file
	wxFileDialog dlg(this, _("Save in GPX format"), wxEmptyString, wxEmptyString, _T("GPX files (*.gpx)|*.gpx|All files (*.*)|*.*"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	if (dlg.ShowModal() == wxID_CANCEL) {
		//error_occured = true;     // the user changed idea...
		return 999;
	}
	else {

		//dlg.ShowModal();
		wxString fileName = dlg.GetPath();
		if (dlg.GetPath() == wxEmptyString) {
			wxMessageBox("Error");
			return 999;
		}
		doc.SaveFile(fileName);
	}

	return 0;
	//end of if no error occured

}

void RTZassistPanelMain::OnClearTextbox(wxCommandEvent& event) {

	ClearTextbox();

}

void RTZassistPanelMain::ClearTextbox() {

	m_textCtrlShowResult->Clear();

}


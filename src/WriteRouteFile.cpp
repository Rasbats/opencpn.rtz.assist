#include <iostream>
#include <fstream>
#include "tinyxml2.h"
#include <wx/wx.h>
#include "WriteRouteFile.h"

using namespace std;
using namespace tinyxml2;

void WriteSchema() {

	std::ifstream    inFile("schema.txt");
	std::ofstream    outFile("test.route");

	outFile << inFile.rdbuf();

	inFile.close();
	outFile.close();

}
/*
void Addpoint(XMLElement* Route, wxString ptlat, wxString ptlon, wxString ptname){
	//add point
	//XMLElement * RoutePoint = new XMLElement();
	//RoutePoint->SetAttribute("lon", ptlon.mb_str());
	
	//Route->LinkEndChild(RoutePoint);
	//done adding point
}
*/
void CopyOpenRoute() {




}
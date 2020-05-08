#include <wx/wx.h>
#include <wx/image.h>

#include "RTZassistFrameMain.h"
#include "RTZassistPanelMain.h"

//#include "../data/folder.xpm"
//wxIcon icon(play);


class wxRTZassistApp : public wxApp {

public:
	wxRTZassistApp() = default;
	virtual ~wxRTZassistApp() = default;
	bool OnInit() override;
	int OnExit() override { return 0; }

};

IMPLEMENT_APP(wxRTZassistApp);

inline bool wxRTZassistApp::OnInit() {

	auto *mainFrame = new RTZassistFrameMain(nullptr);
	new RTZassistPanelMain(mainFrame);
	//mainFrame->SetIcon(icon);
	mainFrame->Show(true);
	mainFrame->Fit();

	SetTopWindow(mainFrame);
	return true;
}

#include <wx/wx.h>
#include <wx/image.h>

#include "RTZassistFrameMain.h"
#include "RTZassistPanelMain.h"
#include "bitmaps/rtzassist.xpm"

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
	wxIcon app_icon(rtzassist);          // This comes from opencpn.xpm inclusion above
	
	mainFrame->SetIcon(app_icon);
	mainFrame->Show(true);
	mainFrame->Fit();

	mainFrame->SetTitle("RTZassist 0.3");

	SetTopWindow(mainFrame);
	return true;
}

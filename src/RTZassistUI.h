///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/frame.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/choice.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/button.h>
#include <wx/panel.h>
#include <wx/textctrl.h>
#include <wx/splitter.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class FrameMain
///////////////////////////////////////////////////////////////////////////////
class FrameMain : public wxFrame
{
	private:

	protected:

	public:

		FrameMain( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("RTZassist"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 431,645 ), long style = wxCLOSE_BOX|wxDEFAULT_FRAME_STYLE|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|wxRESIZE_BORDER|wxTAB_TRAVERSAL );

		~FrameMain();

};

///////////////////////////////////////////////////////////////////////////////
/// Class PanelMain
///////////////////////////////////////////////////////////////////////////////
class PanelMain : public wxPanel
{
	private:

	protected:
		wxSplitterWindow* m_splitter;
		wxPanel* m_panel1;
		wxButton* m_buttonParse;
		wxPanel* m_panel2;

		// Virtual event handlers, overide them in your derived class
		virtual void OnClearTextbox( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnExportRTZ( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnReadRTZ( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnValidateRTZ( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnExportGPX( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnReadGPX( wxCommandEvent& event ) { event.Skip(); }


	public:
		wxChoice* m_choiceSchema;
		wxButton* m_buttonClearText;
		wxButton* m_buttonExportRTZ;
		wxButton* m_buttonLoad;
		wxButton* m_buttonExportRTZ1;
		wxButton* m_buttonReadGPX;
		wxTextCtrl* m_textCtrlShowResult;

		PanelMain( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxTAB_TRAVERSAL, const wxString& name = wxEmptyString );
		~PanelMain();

		void m_splitterOnIdle( wxIdleEvent& )
		{
			m_splitter->SetSashPosition( 0 );
			m_splitter->Disconnect( wxEVT_IDLE, wxIdleEventHandler( PanelMain::m_splitterOnIdle ), NULL, this );
		}

};


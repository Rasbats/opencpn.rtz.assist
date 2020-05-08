///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "RTZassistUI.h"

///////////////////////////////////////////////////////////////////////////

FrameMain::FrameMain( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );


	this->Centre( wxBOTH );
}

FrameMain::~FrameMain()
{
}

PanelMain::PanelMain( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name )
{
	this->SetBackgroundColour( wxColour( 206, 255, 255 ) );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );

	m_splitter = new wxSplitterWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D );
	m_splitter->Connect( wxEVT_IDLE, wxIdleEventHandler( PanelMain::m_splitterOnIdle ), NULL, this );

	m_panel1 = new wxPanel( m_splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer41;
	bSizer41 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );

	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( m_panel1, wxID_ANY, _("Schema Selection:") ), wxVERTICAL );

	wxString m_choiceSchemaChoices[] = { _("RTZ Schema Version 1.0"), _("RTZ Schema Version 1.1"), _("STM Extensions") };
	int m_choiceSchemaNChoices = sizeof( m_choiceSchemaChoices ) / sizeof( wxString );
	m_choiceSchema = new wxChoice( sbSizer2->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceSchemaNChoices, m_choiceSchemaChoices, 0 );
	m_choiceSchema->SetSelection( 0 );
	sbSizer2->Add( m_choiceSchema, 0, wxALL|wxEXPAND, 5 );


	bSizer2->Add( sbSizer2, 1, wxEXPAND, 5 );

	m_buttonClearText = new wxButton( m_panel1, wxID_ANY, _("Clear Textbox"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonClearText->SetFont( wxFont( 9, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );

	bSizer2->Add( m_buttonClearText, 0, wxALL|wxEXPAND, 5 );


	bSizer41->Add( bSizer2, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );

	m_buttonExportRTZ = new wxButton( m_panel1, wxID_ANY, _("GPX ---> RTZ"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonExportRTZ->SetFont( wxFont( 9, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );

	bSizer4->Add( m_buttonExportRTZ, 0, wxALL|wxEXPAND, 5 );

	m_buttonLoad = new wxButton( m_panel1, wxID_ANY, _("Read RTZ"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonLoad->SetFont( wxFont( 9, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );

	bSizer4->Add( m_buttonLoad, 0, wxALL|wxEXPAND, 5 );

	m_buttonParse = new wxButton( m_panel1, wxID_ANY, _("Validate RTZ"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonParse->SetFont( wxFont( 9, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );

	bSizer4->Add( m_buttonParse, 0, wxALL|wxEXPAND, 5 );

	m_buttonExportRTZ1 = new wxButton( m_panel1, wxID_ANY, _("RTZ --> GPX"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonExportRTZ1->SetFont( wxFont( 9, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );

	bSizer4->Add( m_buttonExportRTZ1, 0, wxALL|wxEXPAND, 5 );

	m_buttonReadGPX = new wxButton( m_panel1, wxID_ANY, _("Read OpenCPN GPX"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonReadGPX->SetFont( wxFont( 9, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );

	bSizer4->Add( m_buttonReadGPX, 0, wxALL|wxEXPAND, 5 );


	bSizer41->Add( bSizer4, 1, wxEXPAND, 5 );


	m_panel1->SetSizer( bSizer41 );
	m_panel1->Layout();
	bSizer41->Fit( m_panel1 );
	m_panel2 = new wxPanel( m_splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );

	m_textCtrlShowResult = new wxTextCtrl( m_panel2, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_BESTWRAP|wxTE_MULTILINE|wxTE_WORDWRAP );
	bSizer7->Add( m_textCtrlShowResult, 5, wxALL|wxEXPAND, 5 );


	m_panel2->SetSizer( bSizer7 );
	m_panel2->Layout();
	bSizer7->Fit( m_panel2 );
	m_splitter->SplitHorizontally( m_panel1, m_panel2, 0 );
	bSizer1->Add( m_splitter, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );

	// Connect Events
	m_buttonClearText->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelMain::OnClearTextbox ), NULL, this );
	m_buttonExportRTZ->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelMain::OnExportRTZ ), NULL, this );
	m_buttonLoad->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelMain::OnReadRTZ ), NULL, this );
	m_buttonParse->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelMain::OnValidateRTZ ), NULL, this );
	m_buttonExportRTZ1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelMain::OnExportGPX ), NULL, this );
	m_buttonReadGPX->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelMain::OnReadGPX ), NULL, this );
}

PanelMain::~PanelMain()
{
	// Disconnect Events
	m_buttonClearText->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelMain::OnClearTextbox ), NULL, this );
	m_buttonExportRTZ->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelMain::OnExportRTZ ), NULL, this );
	m_buttonLoad->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelMain::OnReadRTZ ), NULL, this );
	m_buttonParse->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelMain::OnValidateRTZ ), NULL, this );
	m_buttonExportRTZ1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelMain::OnExportGPX ), NULL, this );
	m_buttonReadGPX->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelMain::OnReadGPX ), NULL, this );

}

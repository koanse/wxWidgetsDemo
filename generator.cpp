#include "wx/wxprec.h"
#include "wx/wx.h"
#include "wx/sizer.h"
#include "wx/notebook.h"
#include "wx/textfile.h"
#include "generator.h"

// ----------------------------------------------------------------------------
// MyApp
// ----------------------------------------------------------------------------

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
  if ( !wxApp::OnInit() )
      return false;

  // �������� �������� ����
  MyFrame *frame = new MyFrame;

  frame->Show(true);

  return true;
}

// ����������� ������ �������� ����
// ----------------------------------------------------------------------------
// MyFrame
// ----------------------------------------------------------------------------

MyFrame::MyFrame()
       : wxFrame(NULL, wxID_ANY, wxT("wxWidgets File Generator"))
{
	// Sizer ��� ������� ���� ��������� ����
	wxBoxSizer *topsizer = new wxBoxSizer(wxVERTICAL);

	// �������
	wxNotebook *notebook = new wxNotebook(this, wxID_ANY);
	topsizer->Add(notebook, 1, wxGROW);

	// ��������-���
	gauge = new wxGauge(this, this->GetId(), 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL);
	topsizer->Add(gauge, 0, wxALIGN_LEFT | wxALL, 1);

	// ������-���
	statusBar = new wxStatusBar(this, wxID_ANY, wxST_SIZEGRIP);
	int widths[] = { 60 };
	statusBar->SetStatusWidths(WXSIZEOF(widths), widths);
	statusBar->SetStatusText(wxT("Ready"), 0);
	topsizer->Add(statusBar, 0, wxALIGN_LEFT | wxALL, 10);

	// ������ �������
	wxPanel *panel1 = new wxPanel(notebook, wxID_ANY);
	notebook->AddPage(panel1, wxT("Generation"));

	wxSizer *panelsizer1 = new wxBoxSizer(wxVERTICAL);

	textGenerateFileName = new wxTextCtrl(panel1, wxID_ANY, wxT("test.txt"), wxDefaultPosition, wxSize(250, wxDefaultCoord));
	panelsizer1->Add(textGenerateFileName, 0, wxGROW | wxALL, 30);
	buttonSelectGenerateFile = new wxButton(panel1, wxID_ANY, wxT("Select Generate File"));
	panelsizer1->Add(buttonSelectGenerateFile, 0, wxALIGN_RIGHT | wxLEFT | wxRIGHT | wxBOTTOM, 30);
	textGenerateFileSize = new wxTextCtrl(panel1, wxID_ANY, wxT("1111111"), wxDefaultPosition, wxSize(250, wxDefaultCoord));
	panelsizer1->Add(textGenerateFileSize, 0, wxGROW | wxALL, 30);
	buttonGenerate = new wxButton(panel1, wxID_ANY, wxT("Generate"));
	panelsizer1->Add(buttonGenerate, 0, wxALIGN_RIGHT | wxLEFT | wxRIGHT | wxBOTTOM, 30);

	panel1->SetSizer(panelsizer1);

	// ������ �������
	wxPanel *panel2 = new wxPanel(notebook, wxID_ANY);
	notebook->AddPage(panel2, wxT("Transformation"));

	wxSizer *panelsizer = new wxBoxSizer(wxVERTICAL);

	textTransformFileName = new wxTextCtrl(panel2, wxID_ANY, wxT("test.txt"), wxDefaultPosition, wxSize(250, wxDefaultCoord));
	panelsizer->Add(textTransformFileName, 0, wxGROW | wxALL, 30);
	buttonSelectTransformFile = new wxButton(panel2, wxID_ANY, wxT("Select Transform File"));
	panelsizer->Add(buttonSelectTransformFile, 0, wxALIGN_RIGHT | wxLEFT | wxRIGHT | wxBOTTOM, 30);
	buttonTransform = new wxButton(panel2, wxID_ANY, wxT("Transform"));
	panelsizer->Add(buttonTransform, 0, wxALIGN_RIGHT | wxLEFT | wxRIGHT | wxBOTTOM, 30);

	panel2->SetSizer(panelsizer);

	// �������� ������� � �������
	buttonGenerate->Bind(wxEVT_BUTTON, &MyFrame::ButtonGenerateClicked, this);
	buttonTransform->Bind(wxEVT_BUTTON, &MyFrame::ButtonTransformClicked, this);
	buttonSelectGenerateFile->Bind(wxEVT_BUTTON, &MyFrame::ButtonSelectGenerateClicked, this);
	buttonSelectTransformFile->Bind(wxEVT_BUTTON, &MyFrame::ButtonSelectTransformClicked, this);

	// ���������������� ���������
	SetSizerAndFit(topsizer);
	// ����� ��������-����
	gauge->SetValue(0);
}

// ��������� �����
void MyFrame::ButtonGenerateClicked(wxCommandEvent& event)
{
	statusBar->SetStatusText(wxT("Work..."), 0);
	
	// ������ � ������� � ����� ������� ������������� �����
	wxString number(textGenerateFileSize->GetValue());
	long size;
	if (!number.ToLong(&size))
	{
		statusBar->SetStatusText(wxT("Error"), 0);

		return;
	}

	// �������� �����
	wxTextFile out(textGenerateFileName->GetValue());
	out.Open();
	wxString result;
	
	// ��������� �����
	for (size_t i = 0; i < size; i++)
	{
		result += (char)(i % 24) + 'a';

		// ���������� ���������
		gauge->SetValue(i * 100 / size);
	}

	out.Clear();
	out.AddLine(result);
	out.Write();
	out.Close();
	
	gauge->SetValue(0);
	statusBar->SetStatusText(wxT("Done"), 0);
}

// ������������� �����
void MyFrame::ButtonTransformClicked(wxCommandEvent & event)
{
	statusBar->SetStatusText(wxT("Work..."), 0);
	gauge->SetValue(0);

	wxTextFile out(textGenerateFileName->GetValue());
	out.Open();
	wxString line;
	wxString result;

	// ������� � ������� �������
	for (line = out.GetFirstLine(); !out.Eof(); line = out.GetNextLine())
	{
		for (size_t i = 0; i < line.Length(); i++)
		{
			if (line[i] >= 'a' && line[i] <= 'z')
			{
				line[i] = line[i] - 'a' + 'A';

				// ���������� ���������
				gauge->SetValue(i * 100 / line.Length());
			}
		}
		result += line;
	}

	out.Clear();
	out.AddLine(result);
	out.Write();
	out.Close();

	statusBar->SetStatusText(wxT("Done"), 0);
	gauge->SetValue(0);
}

// ����� ����� ��� ���������
void MyFrame::ButtonSelectGenerateClicked(wxCommandEvent & event)
{
	wxFileDialog *openFileDialog = new wxFileDialog(this);
	if (openFileDialog->ShowModal() == wxID_OK)
	{
		textGenerateFileName->SetValue(openFileDialog->GetPath());
	}
}

// ����� ����� ��� �������������
void MyFrame::ButtonSelectTransformClicked(wxCommandEvent & event)
{
	wxFileDialog *openFileDialog = new wxFileDialog(this);
	if (openFileDialog->ShowModal() == wxID_OK)
	{
		textTransformFileName->SetValue(openFileDialog->GetPath());
	}
}
// ���������� ����� ����������
#include <wx/msw/frame.h>

class MyApp: public wxApp
{
public:
    MyApp(){};
    bool OnInit() wxOVERRIDE;
};

// ���������� �������� Frame ������ (������ �������� ����)
class MyFrame : public wxFrame
{
public:
    MyFrame();

	void ButtonGenerateClicked(wxCommandEvent& event);
	void ButtonTransformClicked(wxCommandEvent& event);
	void ButtonSelectGenerateClicked(wxCommandEvent& event);
	void ButtonSelectTransformClicked(wxCommandEvent& event);

private:
	wxStatusBar *statusBar;
	wxTextCtrl *textGenerateFileName;
	wxButton *buttonSelectGenerateFile;
	wxTextCtrl *textGenerateFileSize;
	wxButton *buttonGenerate;
	wxTextCtrl *textTransformFileName;
	wxButton *buttonSelectTransformFile;
	wxButton *buttonTransform;
	wxGauge *gauge;
};
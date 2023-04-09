#include "gui_mainframe.h"
#include "factory.h"
#include "orchestrator.h"
#include "output_stream_gui.h"

enum ElementID {
    RUN_BUTTON_ID = 2,
    SUBNET_INPUT_ID,
    MASK_INPUT_ID,
};

Mainframe::Mainframe(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
    this->create_controls();
    this->CreateStatusBar();
    this->CreateToolBar();
}

void Mainframe::create_controls()
{
    this->panel = new wxPanel(this);
    this->run_button = new wxButton(panel, RUN_BUTTON_ID, "Run", wxPoint(350, 150), wxSize(100, 25));
    this->run_button->Bind(wxEVT_BUTTON, &Mainframe::run_button_handler, this);

    this->subnet_input = new wxTextCtrl(panel, SUBNET_INPUT_ID, wxEmptyString, wxPoint(300, 30), wxSize(200, 50));
    this->subnet_label = new wxStaticText(panel, wxID_ANY, "Subnet", wxPoint(240, 46));

    this->mask_input = new wxTextCtrl(panel, MASK_INPUT_ID, wxEmptyString, wxPoint(300, 80), wxSize(200, 50));
    this->mask_label = new wxStaticText(panel, wxID_ANY, "Mask", wxPoint(240, 96));

    this->text_output = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxPoint(30, 200), wxSize(745, 420), wxTE_MULTILINE | wxTE_READONLY);
    this->text_output_stream = std::make_shared<std::ostream>(this->text_output);
    this->text_output_stream_inferface = std::make_shared<OutputStreamGUI>(this->text_output_stream);
}

void Mainframe::run_button_handler(wxCommandEvent &event)
{
    if (this->run_button_handler_thread.joinable()) {
        this->orchestrator->stop();
        this->run_button_handler_thread.join();
    }

    this->text_output->Clear();
    this->run_button_handler_thread = std::thread([this]() {
        std::string address_and_mask = (std::string)this->subnet_input->GetValue() + "/" + (std::string)this->mask_input->GetValue();
        this->orchestrator = factory_create_object<Orchestrator, std::string&, OutputStreamBase&>(address_and_mask, *this->text_output_stream_inferface);
        this->orchestrator->start();
    });
}

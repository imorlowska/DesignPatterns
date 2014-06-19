/****************************************
 * Izabela Orlowska                     *
 *                                      *
 * Example of builder design pattern    *
 ****************************************/

#include <iostream>

using namespace std;

class Form
{
    public:
        string buttonText, welcomeMessage;
        void print()
        {
            cout << "Button: " << buttonText << endl;
            cout << "WM: " << welcomeMessage << endl;
        }
        void setButtonText(string text)
        {
            this->buttonText = text;
        }
        void setWelcomeMessage(string text)
        {
            this->welcomeMessage = text;
        }
};

class WMBuilder
{
    public:
        string message;
};

class StudentsWMBuilder: public WMBuilder
{
    public:
        StudentsWMBuilder()
        {
            this->message = "Welcome student!";
        }
};

class AdminWMBuilder: public WMBuilder
{
    public:
        AdminWMBuilder()
        {
            this->message = "Welcome admin!";
        }
};

class ButtonsBuilder
{
    public:
        string message;
};

class StudentsButtonsBuilder: public ButtonsBuilder
{
    public:
        StudentsButtonsBuilder()
        {
            this->message = "Button for students";
        }
};

class AdminButtonsBuilder: public ButtonsBuilder
{
    public:
        AdminButtonsBuilder()
        {
            this->message = "Button for admin";
        }

};

class FormBuilder
{
    private:
        ButtonsBuilder* buttonBuilder;
        WMBuilder* wmBuilder;
        Form* form;

    public:
        FormBuilder()
        {
            this->buttonBuilder = NULL;
            this->wmBuilder = NULL;
            this->form = NULL;
        }
        void setButtonsBuilder(ButtonsBuilder* builder)
        {
            this->buttonBuilder = builder;
        }
        void setWMBuilder(WMBuilder* builder)
        {
            this->wmBuilder = builder;
        }
        void constructForm()
        {
            if (this->buttonBuilder == NULL || this->wmBuilder == NULL)
            {
                cout << "Cannot construct form." << endl;
                cout << "Insufficient number of builders." << endl;
            }
            else
            {
                this->form = new Form();
                this->form->setButtonText(buttonBuilder->message);
                this->form->setWelcomeMessage(wmBuilder->message);
            }
        }
        Form* getForm()
        {
            if (this->form == NULL)
            {
                cout << "No form constructed!" << endl;
            }
            return form;
        }
};


int main()
{
    FormBuilder* fBuilder = new FormBuilder ();
    StudentsButtonsBuilder* bBuilder = new StudentsButtonsBuilder();
    StudentsWMBuilder* wmBuilder= new StudentsWMBuilder ();

    fBuilder->setButtonsBuilder(bBuilder);
    fBuilder->setWMBuilder(wmBuilder);

    fBuilder->constructForm();

    Form* form = fBuilder->getForm();

    form->print();

    return 0;
}

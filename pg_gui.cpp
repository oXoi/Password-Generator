#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Box.H>
#include <FL/fl_ask.H> // For fl_alert
#ifdef _WIN32 // Windows-specific include for LoadIcon and HINSTANCE
#include <windows.h>
#endif
#include <string>
#include <vector>
#include <random>
#include <algorithm> // Required for std::shuffle if used, or for other algorithms
#include <iostream>  // For debugging, can be removed



// ---PasswordGenerationLogic (from your previous cpp file)---

std::string generatePasswordLogic(int length, bool useUppercase, bool useLowercase, bool useNumbers, bool useSymbols) {

    std::string charset = "";
    if (useUppercase) {
        charset += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    }
    if (useLowercase) {
        charset += "abcdefghijklmnopqrstuvwxyz";
    }
    if (useNumbers) {
        charset += "0123456789";
    }
    if (useSymbols) {
        charset += "!@#$%^&*()_+~`|}{[]:;?><,./-=";
    }
    if (charset.empty()) {
        return "Error: No character types selected.";
    }
    if (length <= 0) {
        return "Error: Length must be positive.";
    }

    std::string password = "";
    std::random_device rd;
    std::mt19937 generator(rd());
    // Ensure charset is not empty before creating distribution

    if (charset.length() == 0) return "Error: Charset became empty unexpectedly.";

    std::uniform_int_distribution<int> distribution(0, charset.length() - 1);
    for (int i = 0; i < length; ++i) {
        password += charset[distribution(generator)];
    }
    return password;

}

// ---End of PasswordGenerationLogic---



// Global FLTK Widgets (for easy access in callbacks)

Fl_Input* length_input;
Fl_Check_Button* uppercase_check;
Fl_Check_Button* lowercase_check;
Fl_Check_Button* numbers_check;
Fl_Check_Button* symbols_check;
Fl_Input* password_output; // Use Fl_Input as a simple text display



// Callback function for the "Generate" button

void generate_cb(Fl_Widget* w, void* data) {

    int length = 0;
    if (length_input->value() && strlen(length_input->value()) > 0) {
        length = atoi(length_input->value());
    } else {
        fl_alert("Please enter a password length.");
        return;
    }
    if (length < 1 || length > 128) { // Basic validation
        fl_alert("Password length must be between 1 and 128.");
        return;
    }

    bool use_upper = uppercase_check->value();
    bool use_lower = lowercase_check->value();
    bool use_nums = numbers_check->value();
    bool use_syms = symbols_check->value();


    if (!use_upper && !use_lower && !use_nums && !use_syms) {
        fl_alert("Please select at least one character type.");
        return;
    }

    std::string new_password = generatePasswordLogic(length, use_upper, use_lower, use_nums, use_syms);
    password_output->value(new_password.c_str());

}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) {

    Fl_Window* window = new Fl_Window(420, 280, "Password Generator");
    window->color(fl_rgb_color(211, 235, 211)); // Light green background
#ifdef _WIN32
    // HINSTANCE hInstance = GetModuleHandle(NULL); // hInstance is now a parameter of WinMain
    if (hInstance) {

        // Load the icon from the resource. 101 should match the ID in your .rc file.
        HICON hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(101));
        if (hIcon) {
            window->icon((char*)hIcon); // Set the window icon
        }

        // else {

        // std::cerr << "Failed to load icon. Error: " << GetLastError() << std::endl;

        // }

    }

    // else {

    // std::cerr << "Failed to get hInstance. Error: " << GetLastError() << std::endl;

    // }

#endif
    window->begin(); // Start adding widgets to this window
    // Password Length

    Fl_Box* len_label = new Fl_Box(20, 20, 120, 25, "Password Length:");
    len_label->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
    length_input = new Fl_Input(150, 20, 50, 25);
    length_input->value("12"); // Default length
    // Character Type Checkboxes

    uppercase_check = new Fl_Check_Button(20, 60, 180, 25, "Uppercase (ABC)");
    uppercase_check->value(1); // Checked by default
    lowercase_check = new Fl_Check_Button(20, 90, 180, 25, "Lowercase (abc)");
    lowercase_check->value(1); // Checked by default
    numbers_check = new Fl_Check_Button(220, 60, 180, 25, "Numbers (123)");
    numbers_check->value(1); // Checked by default
    symbols_check = new Fl_Check_Button(220, 90, 180, 25, "Symbols (#$&)");
    symbols_check->value(0); // Unchecked by default



    // Generate Button

    Fl_Button* generate_button = new Fl_Button(150, 130, 120, 30, "Generate");
    generate_button->box(FL_ROUND_UP_BOX);
    generate_button->color(fl_rgb_color(135, 206, 235)); // Sky Blue
    generate_button->selection_color(fl_rgb_color(100, 180, 220)); // Darker blue for selection
    generate_button->callback(generate_cb);
    // Password Output

    Fl_Box* out_label = new Fl_Box(20, 180, 150, 25, "Generated Password:");
    out_label->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
    password_output = new Fl_Input(20, 210, 380, 25);
    password_output->readonly(1); // Make it read-only
    window->end(); // Finish adding widgets
    window->show();
    return Fl::run();

}













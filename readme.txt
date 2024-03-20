A ImGUI style intermediate mode gui wrapper over qt for ease of use.

Currently implemented (same usage as imgui, some slightly different names):

void simpleGUI::init();
void simpleGUI::init(int argc, char** argv);
void simpleGUI::exit();
bool simpleGUI::isRunning();
void simpleGUI::pollEvents();
void simpleGUI::render();
void simpleGUI::text(const std::string_view label);
bool simpleGUI::button(const std::string_view label);
bool simpleGUI::checkbox(const std::string_view label, bool* check);
bool simpleGUI::radioButton(const std::string_view label, int* v, int button_v);
bool simpleGUI::textInput(const std::string_view label, std::span<char> buf);
bool simpleGUI::textInput(const std::string_view label, std::string& buf);



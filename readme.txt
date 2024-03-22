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
bool simpleGUI::combo(const std::string_view label, int* current_item, const std::span<const std::string_view> items);
bool simpleGUI::combo(const std::string_view label, int* current_item, const std::span<const char*> items);
bool simpleGUI::combo(const std::string_view label, int* current_item, const char** items, unsigned int num_items);
bool simpleGUI::combo(const std::string_view label, int* current_item, std::initializer_list<const char*> items);


#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <thread>

void typewrite(const std::string& text) {
    for (char c : text) {
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    std::cout << std::endl;
}

int main() {
    std::string command = "wmic path win32_VideoController get name";
    FILE* pipe = _popen(command.c_str(), "r");
    if (!pipe) {
        std::cerr << "Error: Couldn't open pipe." << std::endl;
        return -1;
    }

    char buffer[128];
    std::string output = "";
    while (!feof(pipe)) {
        if (fgets(buffer, 128, pipe) != NULL)
            output += buffer;
    }
    _pclose(pipe);

    std::vector<std::string> lines;
    size_t pos = 0;
    while ((pos = output.find("\n")) != std::string::npos) {
        lines.push_back(output.substr(0, pos));
        output.erase(0, pos + 1);
    }

    if (lines.size() < 2) {
        std::cout << "nothing is here..." << std::endl;
        return 0;
    }
    std::string text = "";
    for (size_t i = 1; i < lines.size(); ++i)
        text += lines[i] + "\n ";

    std::cout << R"(
                      _            _ 
   __ _ _ __  _   _  | |_ ___  ___| |_ 
  / _` | '_ \| | | | | __/ _ \/ __| __|
 | (_| | |_) | |_| | | ||  __/\__ \ |_ 
  \__, | .__/ \__,_|  \__\___||___/\__|
  |___/|_|                             )" << std::endl;

    std::cout << "\n  " + text << std::endl;

    if (text.find("RTX") != std::string::npos) {
        typewrite("  will work well");
    }
    else if (text.find("GTX") != std::string::npos ||
        text.find("XT") != std::string::npos ||
        text.find("RX") != std::string::npos) {
        typewrite("  will work fine");
    }
    else if (text.find("VEGA") != std::string::npos) {
        typewrite("  probably won't work");
    }
    else {
        typewrite("  couldn't get GPU, probably won't work with aimmy");
    }
    std::cout << "  press enter to exit..." << std::endl;
    std::cin.ignore();

    return 0;
}
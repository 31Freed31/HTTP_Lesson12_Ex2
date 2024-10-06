#include <iostream>
#include <cpr/cpr.h>
#include <string>

std::string extractTitle(const std::string& html) {
    std::size_t start_pos = html.find("<h1>");
    std::size_t end_pos = html.find("</h1>");

    if (start_pos != std::string::npos && end_pos != std::string::npos) {
        return html.substr(start_pos + 4, end_pos - start_pos - 4);
    }
    else {
        return "Заголовок не найден";
    }
}

int main() {
    setlocale(LC_CTYPE, "rus");
    auto response = cpr::Get(cpr::Url{ "http://httpbin.org/html" },
        cpr::Header{ {"accept", "text/html"} });

    if (response.status_code == 200) {
        std::string title = extractTitle(response.text);
        std::cout << "Заголовок статьи: " << title << std::endl;
    }
    else {
        std::cout << "Ошибка запроса: " << response.status_code << std::endl;
    }

    return 0;
}

#include <iostream>
#include "Application.h"

int main() {
    auto& app = Application::get();
    app.run();
    return 0;
}
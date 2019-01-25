#include "Application.h"

Application& Application::get() const {
    static Application app;
    return app;
}
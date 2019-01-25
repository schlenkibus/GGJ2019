#pragma once


class Application {
protected:
    Application() = default;
public:
    static Application& get() const;
};

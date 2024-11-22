#pragma once
#include <iostream>

using namespace std;

class Color {
protected:
    int value;
    int brightness;

public:
    Color() : value(0), brightness(50) {}

    virtual ~Color() {}


    int getValue() const { return value; }
    void setvalue(int val) { brightness = val; }
    int getBrightness() const { return brightness; }
    void setBrightness(int bright) { brightness = bright; }


    virtual void display() const = 0;

};

class Red : public Color {
public:
    Red() : Color() {}
    ~Red() {}

    //display color
    void display() const override {
        std::cout << "Red\n" << value << "Brightness: " << brightness << "%" << std::endl;
    }
};

class Green : public Color {
public:
    Green() : Color() {}
    ~Green() {}

    //display color
    void display() const override {
        std::cout << "Green\n" << value << "Brightness: " << brightness << "%" << std::endl;
    }

};

class Blue : public Color {
public:
    Blue() : Color() {}
    ~Blue() {}

    //display color
    void display() const override {
        std::cout << "Blue\n" << value << "Brightness: " << brightness << "%" << std::endl;
    }
};
//this is the class that utilizes a color at a time
class lightsColor {
private:
    Red red;
    Blue blue;
    Green green;
public:
    lightsColor() {}
    ~lightsColor() {}

    Red& getRed() { return red; }
    Green& getGreen() { return green; }
    Blue& getBlue() { return blue; }

    void display() const {
        red.display();
        green.display();
        blue.display();
    }
};


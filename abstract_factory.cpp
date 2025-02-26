#include <iostream>
#include <memory>
using namespace std;
class Button;
class Radio;
class GUI {
public:
  virtual unique_ptr<Button> createButton() = 0;
  virtual unique_ptr<Radio> createRadio() = 0;
};

class Button {
public:
  virtual void render() = 0;
  virtual void onClick() = 0;
};
class LinuxButton : public Button {
public:
  void render() override { cout << "Rendering Linux Button" << "\n"; }
  void onClick() override { std::cout << "Linux Button Clicked On" << "\n"; }
};
class WinButton : public Button {
public:
  void render() override { cout << "Rendering Windows Button" << "\n"; }
  void onClick() override { std::cout << "Windows Button Clicked On" << "\n"; }
};
class Radio {
public:
  virtual void render() = 0;
  virtual void onSelect() = 0;
};
class LinuxButton : public Radio {
public:
  void render() override { cout << "Rendering Linux Radio" << "\n"; }
  void onSelect() override { std::cout << "Linux Radio Selected" << "\n"; }
};
class WinButton : public Button {
public:
  void render() override { cout << "Rendering Windows Radio" << "\n"; }
  void onSelect() override { std::cout << "Windows Radio Selected" << "\n"; }
};
class WinGUI : public GUI {
public:
  unique_ptr<Button> createButton() override {
    return make_unique<WinButton>(WinButton{});
  }
};

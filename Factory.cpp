#include <iostream>
#include <memory>
using namespace std;
enum class GUI { WINDOWS, LINUX, ANDROID, IOS };
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
class AndroidButton : public Button {
public:
  void render() override { cout << "Rendering Android Button" << "\n"; }
  void onClick() override { std::cout << "Android Button Clicked On" << "\n"; }
};
class ButtonFactory {
public:
  static unique_ptr<Button> createButton(GUI gui) {
    if (GUI::LINUX == gui) {
      return make_unique<LinuxButton>(LinuxButton{});
    } else {

      return make_unique<AndroidButton>(AndroidButton{});
    }
  }
};

int main(int argc, char *argv[]) {
  GUI os = GUI::LINUX;
  unique_ptr<Button> button = ButtonFactory::createButton(os);
  button->render();
  button->onClick();
  return 0;
}

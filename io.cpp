#include <fstream>
#include <ios>
#include <iostream>
#include <string>
using namespace std;
int main() {
  string file_name = "my_file.txt";
  fstream output_file(file_name,
                      ios_base::in | ios_base::out | ios_base::trunc);
  if (output_file.is_open()) {
    string line;
    while (getline(cin, line)) {
      cout << "Writing " << line << "\n";
      output_file << line << "\n";
    }
  }
  output_file.close();
  int target_line = 3;
  int target_pos = 5;
  int i = 0;
  int cursor = 0;
  string line;
  output_file.open(file_name);
  while (getline(output_file, line)) {

    ++i;
    cout << "Reading " << line << " Size: " << line.size() << '\n';
    cursor += line.size();
    if (i == target_line) {
      output_file.seekp(cursor + target_pos);
      output_file << "C++";
      break;
    }
  }
  cout << "Closing" << "\n";
  return 0;
}

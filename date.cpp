#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;
int main(int argc, char *argv[]) {

  string d1 = "2011/04/16-06:14:37";
  string d2 = "2011/04/30-24:00:00";
  string frmt = "%Y/%m/%d-%H:%M:%S";
  struct tm tm1 = {0};
  struct tm tm2 = {0};
  istringstream ss1(d1), ss2(d2);
  ss1 >> get_time(&tm1, frmt.c_str());
  ss2 >> get_time(&tm2, frmt.c_str());
  time_t t1 = mktime(&tm1);
  time_t t2 = mktime(&tm2);
  cout << setprecision(10);
  cout << abs(difftime(t2, t1)) << "\n";
  return 0;
}

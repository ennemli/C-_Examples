#include "contract.h"
#include <cstdlib>
#include <iostream>
#include <map>
#include <memory>
#include <queue>
#include <sstream>
#include <string>
using namespace std;

int main(int argc, char *argv[]) {
  // このコードは標準入力と標準出力を用いたサンプルコードです。
  // このコードは好きなように編集・削除してもらって構いません。
  // ---
  // This is a sample code to use stdin and stdout.
  // Edit and remove this code as you like.
  map<int, unique_ptr<Contract>> contracts;

  queue<string> queue_query;
  string line;
  while (!cin.eof()) {
    getline(cin, line);
    queue_query.push(line);
  }
  while (!queue_query.empty()) {
    string query_line = queue_query.front();
    queue_query.pop();
    istringstream ss(query_line);
    string key;
    ss >> key;
    if (key == "Contract") {

      string date_time;
      int contract_number;
      int device_cost;
      int installment_count;
      ss >> date_time;
      ss >> contract_number;
      ss >> device_cost;
      ss >> installment_count;
      contracts[contract_number] = make_unique<Contract>(
          Contract(date_time, contract_number, device_cost, installment_count));
    } else if (key == "Cancel") {
      int contract_number;
      double data_traffic;
      string date_time;
      ss >> date_time;
      ss >> contract_number;
      if (auto contract = contracts.find(contract_number);
          contract != contracts.end()) {

        ss >> data_traffic;
        Calculation calculation = {data_traffic, date_time};
        contract->second->cancel(calculation);
        contracts.erase(contract);
      } else {
        cout << "Error: " << contract_number << " doesn't exist." << endl;
      }
    } else if (key == "Calculate") {
      int contract_number;
      double data_traffic;
      string date_time;
      ss >> date_time;
      ss >> contract_number;
      if (auto contract = contracts.find(contract_number);
          contract != contracts.end()) {

        ss >> data_traffic;
        Calculation calculation = {data_traffic, date_time};
        contract->second->calculate_monthly(calculation);
      }
    } else if (key == "Start") {
      int contract_number;
      string start_date_time;
      ss >> start_date_time;
      ss >> contract_number;
      if (auto contract = contracts.find(contract_number);
          contract != contracts.end()) {
        contract->second->startVoiceCall(start_date_time);
      } else {
        cout << "Error: " << contract_number << " doesn't exist." << endl;
      }
    } else if (key == "Finish") {
      int contract_number;
      string finish_date_time;
      ss >> finish_date_time;
      ss >> contract_number;
      if (auto contract = contracts.find(contract_number);
          contract != contracts.end()) {

        contract->second->finishVoiceCall(finish_date_time);
      } else {
        cout << "Error: " << contract_number << " doesn't exist." << endl;
      }
    }
  }
  return 0;
}

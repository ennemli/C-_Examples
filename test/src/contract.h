#pragma once
#include "voice_call.h"
#include <cmath>
#include <iomanip>
#include <ios>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

struct Calculation {
  double data_traffic;
  string date_time;
};
class Contract {
private:
  string date_time;
  int contract_number;
  int device_cost;
  int installment_count;
  int monthly_device_cost = 0;
  VoiceCallChannel voice_call_channel;
  int calculateDeviceCharge(bool canceled) {
    int cost = 0;
    if (canceled) {
      cost = device_cost;
      device_cost = 0;
    } else if (device_cost > 0) {
      cost = monthly_device_cost;
      device_cost -= device_cost > 0 ? monthly_device_cost : 0;
    }
    return cost;
  }
  int calculateMonthlyVoiceCallTime(int voice_call_time) {
    int voice_call_time_minutes = voice_call_time / 60.0;
    int voice_call_charge = voice_call_time_minutes > 5.0
                                ? ceil(voice_call_time_minutes - 5.0) * 50.0
                                : 0.0;
    return voice_call_charge;
  }

public:
  explicit Contract(string dateTime, int contractNumber, int deviceCost,
                    int installmentCount)
      : date_time(dateTime), contract_number(contractNumber),
        device_cost(deviceCost), installment_count(installmentCount) {
    monthly_device_cost =
        installment_count > 0 ? device_cost / installment_count : 0;
    if (installment_count == 0) {
      cout << contract_number << " status: no terminal charge." << endl;
    } else if (installment_count == 1) {
      cout << contract_number << " status: lump-sum." << endl;
    } else {
      cout << contract_number << " status: hire-purchase." << endl;
    }
  }
  void startVoiceCall(string startDateTime) {
    if (!voice_call_channel.hasStarted()) {
      voice_call_channel.start(startDateTime);

      cout << contract_number << " has started a voice call at "
           << startDateTime << ".\n";

    } else {
      cout << "Error: " << contract_number
           << " has already started a voice call." << endl;
    }
  }
  void finishVoiceCall(string finishDateTime) {
    if (voice_call_channel.hasStarted()) {

      cout << contract_number << " has finished a voice call at "
           << finishDateTime
           << ". Voice call time: " << voice_call_channel.finish(finishDateTime)
           << "." << endl;
    } else {
      cout << "Error: " << contract_number << " hasn't started a voice call."
           << endl;
    }
  }
  void cancel(Calculation calculation) {

    int voice_call_time =
        voice_call_channel.monthlyVoiceCall(calculation.date_time);

    int charges = calculate_charges(calculation, voice_call_time, true);
    cout << contract_number << " has been canceled. Charges: " << charges
         << " yen." << endl;
  }
  int calculate_charges(Calculation calculation, int voice_call_time,
                        bool canceled = false) {

    int data_traffic_charge;

    if (calculation.data_traffic < 3) {
      data_traffic_charge = 1000;
    } else if (calculation.data_traffic >= 3 && calculation.data_traffic < 20) {

      data_traffic_charge = 2500;
    } else if (calculation.data_traffic >= 20 &&
               calculation.data_traffic < 50) {
      data_traffic_charge = 5000;
    } else {
      data_traffic_charge = 7000;
    }
    int voice_call_charge = calculateMonthlyVoiceCallTime(voice_call_time);
    int charge = calculateDeviceCharge(canceled) + data_traffic_charge +
                 voice_call_charge;
    return charge;
  }
  void calculate_monthly(Calculation calculation) {
    cout << fixed << setprecision(2);
    int voice_call_time =
        voice_call_channel.monthlyVoiceCall(calculation.date_time);
    int charges = calculate_charges(calculation, voice_call_time);
    cout << "Number: " << contract_number
         << ". Voice call time: " << voice_call_time
         << ". Data traffic: " << calculation.data_traffic
         << ". Charges: " << charges << " yen." << endl;
  }
};

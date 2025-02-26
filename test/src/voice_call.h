#pragma once
#include <cmath>
#include <cstddef>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;
class VoiceCallChannel {
private:
  string voiceCall_datetime_start;
  string voiceCall_datetime_finish;
  string last_date;
  int remaining_voice_call_time = 0;
  bool has_started = false;

public:
  bool hasStarted() { return has_started; }
  void start(string startDateTime) {
    voiceCall_datetime_start = startDateTime;
    last_date = startDateTime;
    has_started = true;
  }
  int finish(string finishDateTime) {
    voiceCall_datetime_finish = finishDateTime;
    has_started = false;
    int voice_call_time = calculateVoiceTime(voiceCall_datetime_start,
                                             voiceCall_datetime_finish, true);
    remaining_voice_call_time += voice_call_time;
    struct tm tm1 = {};
    struct tm tm2 = {};
    istringstream ss1(last_date), ss2(voiceCall_datetime_start);
    ss1 >> get_time(&tm1, "%Y/%m/%d-%H:%M:%S");
    ss2 >> get_time(&tm2, "%Y/%m/%d-%H:%M:%S");

    time_t time1 = mktime(&tm1);
    time_t time2 = mktime(&tm2);
    if (time1 > time2) {
      remaining_voice_call_time =
          calculateVoiceTime(last_date, voiceCall_datetime_finish, false);
    }
    return voice_call_time;
  }

  int calculateVoiceTime(string &start_date_time, string &finish_date_time,
                         bool calculate_finish) {
    // converting date string to seconds
    struct tm tm1 = {};
    struct tm tm2 = {};
    istringstream ss1(start_date_time), ss2(finish_date_time);
    ss1 >> get_time(&tm1, "%Y/%m/%d-%H:%M:%S");
    ss2 >> get_time(&tm2, "%Y/%m/%d-%H:%M:%S");

    time_t time1 = mktime(&tm1);
    time_t time2 = mktime(&tm2);
    if ((tm2.tm_hour != 0 || tm2.tm_sec != 0 || tm2.tm_min != 0) &&
        !calculate_finish) {
      time1 += 24 * 60 * 60;
    }
    return static_cast<int>(abs(difftime(time2, time1)));
  }
  int monthlyVoiceCall(string &datetime) {

    int voice_call_time = remaining_voice_call_time;
    if (has_started) {
      voice_call_time += calculateVoiceTime(last_date, datetime, false);
      last_date = datetime;
    }

    remaining_voice_call_time = 0;
    return voice_call_time;
  }
};

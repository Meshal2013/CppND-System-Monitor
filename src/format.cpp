#include <string>

#include "format.h"

using std::string;
using std::to_string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
 
   
	long hour;
	long min ;
	long sec ;

// 	hour = seconds/3600;
// 	seconds = seconds%3600;
// 	min = seconds/60;
// 	seconds = seconds%60;
// 	sec = seconds;
  sec = seconds % 60;
  seconds = seconds - sec;
  seconds = seconds / 60;
  
  min = seconds%60;
  seconds = seconds-min;
  seconds /= 60;
  
  hour = seconds;
  
  string secondsStr;
  string minStr;
  string hourStr;
  if(sec <10){
  	secondsStr = "0" + to_string(sec);
  }
  else{
    secondsStr = to_string(sec);
  }
  if(min <10){
  	minStr = "0" + to_string(min);
  }
  else{
    minStr = to_string(min);
  }
  if(hour <10){
  	hourStr = "0" + to_string(hour);
  }
  else{
   hourStr = to_string(hour);
  }
  
//   string upTime = to_string(hour)+":"+to_string(min)+":"+to_string(sec);
  string upTime =hourStr + ":" +minStr + ":" +secondsStr;
  return upTime;
}
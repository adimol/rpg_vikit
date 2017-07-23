#ifndef TIMER_H
#define TIMER_H

#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

namespace vk
{

class Timer
{
private:
  timespec start_time_; // timeval was before
  double time_;
  double accumulated_;
public:

  /// The constructor directly starts the timer.
  Timer() :
    time_(0.0),
    accumulated_(0.0)
  {
    start();
  }

  ~Timer()
  {}

  inline void start()
  {
    accumulated_ = 0.0;
    //gettimeofday(&start_time_, NULL);
    clock_gettime(CLOCK_MONOTONIC, &start_time_);
  }

  inline void resume()
  {
    //gettimeofday(&start_time_, NULL);
    clock_gettime(CLOCK_MONOTONIC, &start_time_);
  }

  inline double stop()
  {
    timespec end_time;
    //gettimeofday(&end_time, NULL);
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    long seconds  = end_time.tv_sec  - start_time_.tv_sec;
    long nseconds = end_time.tv_nsec - start_time_.tv_nsec;
    time_ = ((seconds) + nseconds*0.000000001) + accumulated_;
    accumulated_ = time_;
    return time_;
  }

  inline double getTime() const
  {
    return time_;
  }

  inline void reset()
  {
    time_ = 0.0;
    accumulated_ = 0.0;
  }

  static double getCurrentTime()
  {
    timeval time_now;
    gettimeofday(&time_now, NULL);
    return time_now.tv_sec + time_now.tv_usec*0.000001;
  }

  static double getCurrentSecond()
  {
    timeval time_now;
    gettimeofday(&time_now, NULL);
    return time_now.tv_sec;
  }

};

} // end namespace vk

#endif

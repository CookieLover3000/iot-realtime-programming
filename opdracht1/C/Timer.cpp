
#include "Timer.h"


Timer::Timer(){
}

void Timer::Reset()
{
    _start = high_resolution_clock::now();
}
void Timer::Stop()
{
    _stop = high_resolution_clock::now();
}

unsigned long Timer::deTijd() const {
	return std::chrono::duration_cast<milliseconds>(_stop- _start).count();
}

 unsigned long Timer::deNtijd() const {
 	return (_stop - _start).count();
 }

milliseconds Timer::Elapsed() const
{
   return std::chrono::duration_cast<milliseconds>(high_resolution_clock::now() - _start);
}



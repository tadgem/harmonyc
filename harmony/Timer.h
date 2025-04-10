#pragma once
#include <chrono>
#include "Primitives.h"
namespace harmony
{
	typedef std::chrono::high_resolution_clock HighResolutionClock;

	class Timer
	{
	public:
		typedef HighResolutionClock::time_point TimePoint;

		TimePoint mStart;

		Timer() : mStart(HighResolutionClock::now()) {}

		auto Elapsed()
		{
			return HighResolutionClock::now() - mStart;
		}

		int64 ElapsedMilliseconds()
		{
			auto ms = stl::chrono::duration_cast<stl::chrono::milliseconds>(Elapsed());
			return static_cast<int64>(ms.count());
		}

		int64 ElapsedNanoseconds()
		{
			auto ms = stl::chrono::duration_cast<stl::chrono::nanoseconds>(Elapsed());
			return static_cast<int64>(ms.count());
		}

		f64 ElapsedMillisecondsF()
		{

			auto ns_raw = stl::chrono::duration_cast<stl::chrono::nanoseconds>(Elapsed());
			auto ns_f = static_cast<f64>(ns_raw.count());
			return ns_f / 1000000.0;
		}

		f64 ElapsedNanosecondsF()
		{

			auto ns_raw = stl::chrono::duration_cast<stl::chrono::nanoseconds>(Elapsed());
			auto ns_f = static_cast<f64>(ns_raw.count());
			return ns_f;
		}
	};
}
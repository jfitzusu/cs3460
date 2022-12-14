
#include <chrono>
#include <cstdint>
#include <format>
#include <iostream>

using seconds = std::chrono::duration<std::uint32_t, std::ratio<1, 1>>;
using milliseconds = std::chrono::duration<std::uint32_t, std::ratio<1, 1000>>;
using minutes = std::chrono::duration<std::uint32_t, std::ratio<60, 1>>;

std::uint64_t fibonacci(std::uint16_t n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;

    return fibonacci(n - 2) + fibonacci(n - 1);
}

//
// Demonstration of the std::chrono library
//
int main(int argc, char* argv[])
{
    {
        std::chrono::duration<std::uint32_t, std::ratio<1, 1>> seconds(10);
        std::chrono::duration<std::uint32_t, std::ratio<1, 1000>> milliseconds(10000);
        std::chrono::duration<std::uint32_t, std::ratio<60, 1>> minutes(4);
    }

    {
        seconds s(10);
        milliseconds ms(10000);
        minutes min(4);
    }

    {
        std::chrono::seconds s(10);
        std::chrono::milliseconds ms(10000);
        std::chrono::minutes min(4);
    }

    {
        std::chrono::seconds seconds(30);
        std::chrono::minutes minutes(1);
        std::chrono::seconds minutesToSeconds = minutes;

        std::cout << seconds.count() << " seconds" << std::endl;
        std::cout << minutes.count() << " minutes" << std::endl;
        std::cout << minutesToSeconds.count() << " seconds" << std::endl;

        seconds += minutes;
        std::cout << seconds.count() << " seconds" << std::endl;

        minutes += std::chrono::duration_cast<std::chrono::minutes>(seconds);
        std::cout << minutes.count() << " minutes" << std::endl;
    }

    {
        std::chrono::duration<float, std::ratio<60, 1>> minutes(1);
        std::chrono::duration<std::uint32_t, std::ratio<1, 1>> seconds(10);

        minutes += seconds;
        std::cout << minutes.count() << " minutes" << std::endl;

        auto periodSystem = std::chrono::system_clock::period();
        std::cout << "System Clock Period          : " << periodSystem.num << " / " << periodSystem.den << std::endl;

        auto periodSteady = std::chrono::steady_clock::period();
        std::cout << "Steady Clock Period          : " << periodSteady.num << " / " << periodSteady.den << std::endl;

        auto periodHigh = std::chrono::high_resolution_clock::period();
        std::cout << "High Resolution Clock Period : " << periodHigh.num << " / " << periodHigh.den << std::endl;

        auto periodGPS = std::chrono::gps_clock::period();
        std::cout << "GPS Clock Period             : " << periodGPS.num << " / " << periodGPS.den << std::endl;

        auto periodUTC = std::chrono::utc_clock::period();
        std::cout << "UTC Clock Period             : " << periodUTC.num << " / " << periodUTC.den << std::endl;

        auto periodTAI = std::chrono::tai_clock::period();
        std::cout << "TAI Clock Period             : " << periodTAI.num << " / " << periodTAI.den << std::endl;

        auto systemNow = std::chrono::system_clock::now();
        std::cout << "System clock periods since clock epoch          : " << systemNow.time_since_epoch().count() << std::endl;

        auto steadyNow = std::chrono::steady_clock::now();
        std::cout << "Steady clock periods since clock epoch          : " << steadyNow.time_since_epoch().count() << std::endl;

        auto highResolutionNow = std::chrono::steady_clock::now();
        std::cout << "High resolution clock periods since clock epoch : " << highResolutionNow.time_since_epoch().count() << std::endl;

        auto gpsNow = std::chrono::steady_clock::now();
        std::cout << "GPS clock periods since clock epoch             : " << gpsNow.time_since_epoch().count() << std::endl;

        auto utcNow = std::chrono::steady_clock::now();
        std::cout << "UTC clock periods since clock epoch             : " << utcNow.time_since_epoch().count() << std::endl;

        auto taiNow = std::chrono::steady_clock::now();
        std::cout << "TAI clock periods since clock epoch             : " << taiNow.time_since_epoch().count() << std::endl;

        std::chrono::hours systemHours = std::chrono::duration_cast<std::chrono::hours>(systemNow.time_since_epoch());
        std::cout << "System clock hours since epoch          : " << systemHours.count() << std::endl;

        std::chrono::hours steadyHours = std::chrono::duration_cast<std::chrono::hours>(steadyNow.time_since_epoch());
        std::cout << "Steady clock hours since epoch          : " << steadyHours.count() << std::endl;

        std::chrono::hours highResolutionHours = std::chrono::duration_cast<std::chrono::hours>(highResolutionNow.time_since_epoch());
        std::cout << "High resolution clock hours since epoch : " << steadyHours.count() << std::endl;

        std::chrono::hours gpsHours = std::chrono::duration_cast<std::chrono::hours>(gpsNow.time_since_epoch());
        std::cout << "GPS clock hours since epoch             : " << gpsHours.count() << std::endl;

        std::chrono::hours utcHours = std::chrono::duration_cast<std::chrono::hours>(utcNow.time_since_epoch());
        std::cout << "UTC clock hours since epoch             : " << utcHours.count() << std::endl;

        std::chrono::hours taiHours = std::chrono::duration_cast<std::chrono::hours>(taiNow.time_since_epoch());
        std::cout << "TAI clock hours since epoch             : " << taiHours.count() << std::endl;

        //
        // Demonstrate how to time something
        auto start = std::chrono::high_resolution_clock::now();
        auto result = fibonacci(24);
        auto end = std::chrono::high_resolution_clock::now();
        auto diff = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        std::cout << "Fibonacci(24) = " << result << std::endl;
        std::cout << "fibonacci(24) took " << diff.count() << " microseconds" << std::endl;
    }

    {
        //
        // Let's do some calendar demonstrations
        std::chrono::year_month_day ymd = std::chrono::September / 24 / 1985;
        std::cout << std::format("Start Date   : {:%Y-%m-%d}\n", ymd);

        //
        // Add a couple of days.  This isn't as obvious as it should be, but here is what is going on...
        // Step 1: Convert the ymd to some number of days
        // Step 2: Add in the desired number of days
        // Step 3: convert the number of days back into a year_month_day
        // Good reference: https://stackoverflow.com/questions/62734974/how-do-i-add-a-number-of-days-to-a-date-in-c20-chrono
        auto ymdTP = std::chrono::sys_days{ ymd };
        ymdTP += std::chrono::days{ 7 };
        ymd = std::chrono::year_month_day{ ymdTP };
        std::cout << std::format("Add 7 days   : {:%Y-%m-%d}\n", ymd);

        //
        // Adding in a couple of months is easier
        ymd += std::chrono::months{ 2 };
        std::cout << std::format("Add 2 months : {:%Y-%m-%d}\n", ymd);
    }

    return 0;
}

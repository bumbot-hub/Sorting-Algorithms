#pragma once
#include<chrono>

/**
 * @class Timer
 * @brief High-precision timer based on std::chrono.
 * Provides microsecond/millisecond resolution for algorithm benchmarking.
 */
class Timer {
    std::chrono::high_resolution_clock::time_point startTime;
    bool isRunning = false;
public:
    /** @brief Captures the starting time point. */
    void Start() {
        startTime = std::chrono::high_resolution_clock::now();
        isRunning = true;
    }

    /** * @brief Calculates elapsed time since Start() and resets the timer.
     * @return Elapsed time in milliseconds (double).
     */
    double ElapsedTimeMs() {
        if (!isRunning) {
            return 0.0;
        }

        auto endTime = std::chrono::high_resolution_clock::now();
        isRunning = false;
        // Calculation with millisecond precision as required by project guidelines
        return std::chrono::duration<double, std::milli>(endTime - startTime).count();
    }
};


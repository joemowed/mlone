#include "benchmark.hpp"
#include <chrono>
#include <iostream>
benchMark::benchMark(std::string nameOfItem) {
  benchMark::nameOfItem = nameOfItem;
  benchMark::startTime = std::chrono::high_resolution_clock::now();
}
void benchMark::stop() {
  auto stopTime = std::chrono::high_resolution_clock::now();
  auto elapsed = (stopTime - startTime);

  elapsed = std::chrono::duration_cast<std::chrono::microseconds>(elapsed);
  std::cout << "\nExecution of " << benchMark::nameOfItem << " took\n";
  std::cout << std::chrono::duration_cast<std::chrono::microseconds>(elapsed)
            << " microseconds\n";
  std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(elapsed)
            << " milliseconds\n";
  std::cout << std::chrono::duration_cast<std::chrono::seconds>(elapsed)
            << " seconds\n";

  std::cout << std::chrono::duration_cast<std::chrono::minutes>(elapsed)
            << " minutes\n";
}

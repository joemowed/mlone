#include <chrono>
class benchMark {
private:
  std::chrono::time_point<std::chrono::system_clock> startTime;
  std::string nameOfItem;

public:
  benchMark(std::string nameOfItem);
  void stop();
};

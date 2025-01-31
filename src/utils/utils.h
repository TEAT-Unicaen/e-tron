#define SLEEP(second) std::this_thread::sleep_for(std::chrono::seconds(second))
#define SLEEP_MS(millisecond) std::this_thread::sleep_for(std::chrono::milliseconds(millisecond))

#define BIT(x) (1 << x)
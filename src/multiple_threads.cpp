#include <mutex>
#include <thread>
#include <chrono>

#include <string>
#include <iostream>

#include "../include/util.h"

std::mutex _car_mutex;

void DriveCar(const std::string & _driver_name) {
	std::lock_guard guard(_car_mutex);
	std::cout << _driver_name << " is driving\n";
	__time_sleep_sec(1);
	std::cout << _driver_name << " driving done\n";
}

void DriveCarV2(const std::string & _driver_name) {
	std::unique_lock ulock(_car_mutex); // acquire is lock
	// ulock.lock();
	std::cout << _driver_name << " is driving\n";
	__time_sleep_sec(2);
	std::cout << _driver_name << " driving done\n";
	ulock.unlock();
}

int main() {
	std::chrono::time_point startTime = __time_now_();

	std::thread Matan(DriveCarV2, "Matan");
	std::thread Elon(DriveCarV2, "Elon");
	std::thread Sam(DriveCarV2, "Sam");

	Matan.join();
	Elon.join();
	Sam.join();

	std::cout << "total time: " << __time_tillnow_dur_ms_(startTime) <<"ms" << '\n';

	return 0;
}
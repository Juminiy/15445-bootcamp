#include <mutex>
#include <thread>
#include <chrono>

#include <string>
#include <iostream>

std::mutex _car_mutex;

void DriveCar(const std::string & _driver_name) {
	
	std::cout << _driver_name << "is driving\n";
	std::this_thread::sleep_for (std::chrono::seconds(1));
}

int main() {
	std::thread Elon(DriveCar, "Elon");
	std::thread Sam(DriveCar, "Sam");

	Elon.join();
	Sam.join();

	return 0;
}
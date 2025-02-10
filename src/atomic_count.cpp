#include <atomic>

#include <iostream>

#include <mutex>
#include <ostream>
#include <thread>
#include <utility>
#include <vector>

class mutexInt {
	public:
		mutexInt() {
			_i = 0;
		}

		mutexInt(int i) {
			_i = i;
		}

		mutexInt(mutexInt const&) = delete;
		mutexInt operator=(mutexInt const&) = delete;

		int operator++() { // ++i
			_mu.lock();
			int _icopy = _i+1;
			_i++;
			_mu.unlock();
			return _icopy;
		}

		int operator++(int _) { // i++
			_mu.lock();
			int _icopy = _i;
			_i++;
			_mu.unlock();
			return _icopy;
		}

		int DirtyLoad() const {
			return _i;
		}

		~mutexInt(){
			_mu.unlock();
		}

		friend std::ostream& operator<<(std::ostream& _os, mutexInt const & _mi) {
			_os << _mi.DirtyLoad();
			return _os;
		}

	private:
		int _i;
		std::mutex _mu;
};

int main(int argc, char** argv) {

	std::atomic_int aicnt = 0;
	int nmcnt = 0;
	mutexInt micnt(0);

	auto addcnt = [&aicnt, &nmcnt, &micnt]() {
		for(int lpi = 0; lpi < 1024; ++lpi){
			aicnt++, nmcnt++, micnt++;
		}
	};
	std::vector<std::thread> thds;
	thds.reserve(16);

	for(size_t i = 0; i < 16; ++i) {
		thds.emplace_back(std::move(std::thread(addcnt)));
	}

	for(auto &thd: thds){
		thd.join();
	}

	std::cout << "aicnt = " << aicnt << '\n';
	std::cout << "nmcnt = " << nmcnt << '\n';
	std::cout << "nmcnt = " << micnt << '\n';

	return 0;
}
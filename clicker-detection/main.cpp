#include <iostream>
#include <Windows.h>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <vector>

uint64_t time() {
	using namespace std::chrono;
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

int main() {
	int prev = 0;
	uint64_t delta = time();
	uint64_t entropy = time() - delta + 1;
	std::vector<int> l_entropy{};

	while (true) {
		int ks = GetAsyncKeyState(1);
		if ((bool)(ks < 0 && prev == 0) || (bool)(ks == 0 && prev < 0)) {
			l_entropy.push_back((abs((int)(time() - delta)) / abs((int)entropy)));
			if ((ks == 0 && prev < 0))
				entropy = time() - delta;
			delta = time();
		}
		if (l_entropy.size() == 75) {
			int _1 = 0;
			int _0 = 0;
			for (auto& click : l_entropy) {
				if (click == 1)
					_1++;
				if (click == 0)
					_0++;
			}
			std::cout << "autoclicker: " << (ceil(((_0+_1)/75.0)*100.0)>98 ? "yes" : "no") << std::endl;
			l_entropy.clear();
		}
		prev=ks;
	}
	std::cin.get();
}
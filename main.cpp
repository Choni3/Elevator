#include <bits/stdc++.h>
#include "ElevatorManager.h"
#include <thread>
#include<vector>


void timerThread(ElevatorManager& orchestrator, std::chrono::steady_clock::time_point startTime) {
	while(true) {
		auto now = std::chrono::steady_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count();
		std::cout << "Time elapsed: " << elapsed << " seconds" << std::endl;

		if(elapsed >= 30) {
			std::cout << "30 seconds reached, finishing all..." << std::endl;
			orchestrator.stop();
			break;
		}

		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}
int main() {
    auto startTime = std::chrono::steady_clock::now();

	ElevatorManager orchestrator(std::vector<int>{1, 30, 100});
	
	orchestrator.start();
	orchestrator.requestPath(30, 15);
	orchestrator.requestPath(18, 12);

	std::thread timer(timerThread, std::ref(orchestrator), startTime);
	timer.detach();

	std::this_thread::sleep_for(std::chrono::seconds(50));

	return 0;
}


#include "Elevator.h"
#include<iostream>
#include<thread>
#include<chrono>

Elevator::Elevator(int id, int starting_floor): id(id), currentFloor(starting_floor), running(true) {}

Elevator::~Elevator() {
	stop();
}
void Elevator::requestFloor(int floor){
	std::lock_guard<std::mutex> lock(mtx);
	requests.push(floor);
	cv.notify_one();
}

void Elevator::run() {
	while(running) {
		std::unique_lock<std::mutex> lock(mtx);
		cv.wait(lock, [this] {return !requests.empty() || !running;});
		while(!requests.empty()) {
			int targetFloor = requests.front();
			requests.pop();
			lock.unlock();
			std::cout << "Ascensor " << id << " moviéndose de " << currentFloor << " a " <<  targetFloor << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(abs(targetFloor-currentFloor)*1));
			currentFloor = targetFloor;
			lock.lock();
		}
	}
}
void Elevator::stop() {
    running = false;
    cv.notify_all();
}

int Elevator::getCurrentFloor() {
    std::lock_guard<std::mutex> lock(mtx);
    return currentFloor;
}
#include "ElevatorManager.h"
#include <iostream>
#include <limits>
#include<thread>



ElevatorManager::ElevatorManager(std::vector<int> startingFloors) {
    for (int i = 0; i < startingFloors.size(); ++i) {
        elevators.push_back(new Elevator(i, startingFloors[i]));
    }
}

ElevatorManager::~ElevatorManager() {
    stop();
    for (Elevator* e : elevators) {
        delete e;
    }
}

Elevator* ElevatorManager::requestElevator(int floor) {
    Elevator* bestElevator = nullptr;
    int minDistance = std::numeric_limits<int>::max();
	
    for (Elevator* e : elevators) {
        int distance = abs(e->getCurrentFloor() - floor);
        if (distance < minDistance) {
            minDistance = distance;
            bestElevator = e;
        }
    }

    if (bestElevator) {
        bestElevator->requestFloor(floor);
    }
	return bestElevator;
}
void ElevatorManager::requestPath(int startFloor, int endFloor) {
	Elevator* currentElevator = requestElevator(startFloor);
	currentElevator->requestFloor(endFloor);
}

void ElevatorManager::start() {
    for (Elevator* e : elevators) {
        threads.emplace_back(std::thread(&Elevator::run, e));
    }
}

void ElevatorManager::stop() {
    for (Elevator* e : elevators) {
        e->stop();
    }
	for(auto& t : threads) {
		if(t.joinable()) t.join();
	}
}
#ifndef ELEVATORMANAGER_H
#define ELEVATORMANAGER_H

#include "Elevator.h"
#include <vector>
#include<thread>

class ElevatorManager {
private:
    std::vector<Elevator*> elevators;
	std::vector<std::thread> threads;

public:
    ElevatorManager(std::vector<int>startingFloors);
    ~ElevatorManager();
    
	void requestPath(int startFloor, int endFloor);
    Elevator* requestElevator(int floor);
    void start();
    void stop();
};

#endif
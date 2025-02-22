#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <queue>
#include <mutex>
#include <condition_variable>

class Elevator{
	private:
		int id;
		int currentFloor;
		std::queue<int>requests;
		std::mutex mtx;
		std::condition_variable cv;
		bool running;

	public:
		Elevator(int id, int starting_floor);
		~Elevator();

		void requestFloor(int floor);
		void run();
		void stop();

		int getCurrentFloor();
};

#endif

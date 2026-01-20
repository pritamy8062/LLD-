#include <bits/stdc++.h>
using namespace std;

//classes 
//Elevator, floor , button, elevator system
//button -get pressed sends request

//Elevator class 
//knows its current floor 
//knows which direction its going 

//Moves up or down
//open and closes door 
class Elevator {
private:
    int currentFloor;
    bool movingUp;

public:
    Elevator(int floor) {
        currentFloor = floor;
        movingUp = true;
    }

    int getCurrentFloor() {
        return currentFloor;
    }

    void moveToFloor(int floor) {
        if (floor == currentFloor) {
            cout << "Elevator already at floor " << floor << endl;
            return;
        }

        movingUp = (floor > currentFloor);

        cout << "Elevator moving from floor "
             << currentFloor << " to floor "
             << floor << endl;

        currentFloor = floor;

        openDoor();
        closeDoor();
    }

    void openDoor() {
        cout << "Door opening at floor " << currentFloor << endl;
    }

    void closeDoor() {
        cout << "Door closing at floor " << currentFloor << endl;
    }
};

//Floor class
//has floor number
//has up/down button
class Floor {
private:
    int floorNumber;

public:
    Floor(int number) {
        floorNumber = number;
    }

    int getFloorNumber() {
        return floorNumber;
    }

    void pressButton() {
        cout << "Button pressed at floor " << floorNumber << endl;
    }
};


//Elevator System (brain of system)
//Simple rule : send the nearest idle elevator 
//receives requests
//decides which elevator to send 
class ElevatorSystem {
private:
    vector<Elevator*> elevators;

public:
    void addElevator(Elevator* elevator) {
        elevators.push_back(elevator);
    }

    Elevator* getNearestElevator(int floor) {
        Elevator* best = nullptr;
        int minDistance = INT_MAX;

        for (auto e : elevators) {
            int distance = abs(e->getCurrentFloor() - floor);
            if (distance < minDistance) {
                minDistance = distance;
                best = e;
            }
        }
        return best;
    }

    void requestElevator(int floor) {
        cout << "\nRequest received for floor " << floor << endl;
        Elevator* e = getNearestElevator(floor);

        if (e) {
            e->moveToFloor(floor);
        } else {
            cout << "No elevators available\n";
        }
    }
};

//When a user presses a button on a floor , the system receices the floor number .
//The system finds the nearest eleveator and sends it to that floor.


//---------------- MAIN ----------------
int main() {
    ElevatorSystem system;

    Elevator e1(0);
    Elevator e2(5);

    system.addElevator(&e1);
    system.addElevator(&e2);

    Floor f3(3);
    Floor f7(7);

    f3.pressButton();
    system.requestElevator(3);

    f7.pressButton();
    system.requestElevator(7);

    return 0;
}
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Enum for Vehicle types
enum class VehicleType { CAR, BIKE, TRUCK };

// Base Class: Vehicle
class Vehicle {
protected:
    string licensePlate;
    VehicleType type;

public:
    Vehicle(string plate, VehicleType t) : licensePlate(plate), type(t) {}
    virtual VehicleType getType() { return type; }
    string getPlate() { return licensePlate; }
    virtual ~Vehicle() = default;
};

// Derived Classes
class Car : public Vehicle {
public:
    Car(string plate) : Vehicle(plate, VehicleType::CAR) {}
};

class Bike : public Vehicle {
public:
    Bike(string plate) : Vehicle(plate, VehicleType::BIKE) {}
};

// Parking Slot Representation
class ParkingSlot {
    int slotNumber;
    VehicleType typeSupported;
    Vehicle* parkedVehicle;

public:
    ParkingSlot(int number, VehicleType type) 
        : slotNumber(number), typeSupported(type), parkedVehicle(nullptr) {}

    bool isFree() { return parkedVehicle == nullptr; }

    bool canFit(Vehicle* v) {
        return isFree() && v->getType() == typeSupported;
    }

    void park(Vehicle* v) {
        parkedVehicle = v;
        cout << "Vehicle " << v->getPlate() << " parked in slot " << slotNumber << endl;
    }

    void remove() {
        parkedVehicle = nullptr;
    }
};

// Main Parking Lot System (Singleton Pattern could be applied here)
class ParkingLot {
    vector<ParkingSlot*> slots;

public:
    ParkingLot(int carSlots, int bikeSlots) {
        for (int i = 1; i <= carSlots; i++) 
            slots.push_back(new ParkingSlot(i, VehicleType::CAR));
        for (int i = 1; i <= bikeSlots; i++) 
            slots.push_back(new ParkingSlot(carSlots + i, VehicleType::BIKE));
    }

    bool parkVehicle(Vehicle* v) {
        for (auto slot : slots) {
            if (slot->canFit(v)) {
                slot->park(v);
                return true;
            }
        }
        cout << "No available slots for vehicle: " << v->getPlate() << endl;
        return false;
    }
};

int main() {
    ParkingLot myLot(2, 2); // 2 Car slots, 2 Bike slots

    Car c1("ABC-123");
    Bike b1("BIKE-99");
    Car c2("XYZ-789");
    Car c3("FULL-111");

    myLot.parkVehicle(&c1);
    myLot.parkVehicle(&b1);
    myLot.parkVehicle(&c2);
    myLot.parkVehicle(&c3); // Should fail

    return 0;
}
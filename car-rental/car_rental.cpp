#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

// ---------- ENUM ----------
enum class CarType {
    SEDAN,
    SUV,
    HATCHBACK
};

// ---------- CAR ----------
class Car {
public:
    int carId;
    CarType carType;
    bool isAvailable;

    Car(int id, CarType type) {
        carId = id;
        carType = type;
        isAvailable = true;
    }
};

// ---------- USER ----------
class User {
public:
    int userId;
    string name;

    User(int id, string name) {
        this->userId = id;
        this->name = name;
    }
};

// ---------- BOOKING ----------
class Booking {
public:
    int bookingId;
    User user;
    Car* car;
    time_t startTime;
    time_t endTime;

    Booking(int id, User user, Car* car)
        : user(user) {
        bookingId = id;
        this->car = car;
        startTime = time(nullptr);
        endTime = 0;
    }

    void closeBooking() {
        endTime = time(nullptr);
        car->isAvailable = true;
    }
};

// ---------- CAR RENTAL SYSTEM ----------
class CarRentalSystem {
private:
    vector<Car> cars;
    vector<Booking> bookings;

public:
    void addCar(Car car) {
        cars.push_back(car);
    }

    vector<Car*> getAvailableCars() {
        vector<Car*> availableCars;
        for (auto& car : cars) {
            if (car.isAvailable) {
                availableCars.push_back(&car);
            }
        }
        return availableCars;
    }

    Booking* bookCar(User user, int carId) {
        for (auto& car : cars) {
            if (car.carId == carId && car.isAvailable) {
                car.isAvailable = false;
                bookings.emplace_back(bookings.size() + 1, user, &car);
                return &bookings.back();
            }
        }
        return nullptr;
    }
};

int main() {
    CarRentalSystem system;

    system.addCar(Car(1, CarType::SEDAN));
    system.addCar(Car(2, CarType::SUV));

    User user1(101, "Pritam");

    Booking* booking = system.bookCar(user1, 1);

    if (booking != nullptr) {
        cout << "Car booked successfully!" << endl;
        booking->closeBooking();
        cout << "Car returned successfully!" << endl;
    } else {
        cout << "Car not available." << endl;
    }

    return 0;
}

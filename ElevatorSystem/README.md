# Elevator System – Low Level Design (C++)

## Problem Statement
Design a basic Elevator System using Object-Oriented principles.
The system should handle floor requests and assign the nearest elevator.

---

## Requirements
- Multiple elevators
- Multiple floors
- Floor buttons to request elevator
- Elevator moves up/down
- Elevator opens and closes doors
- Assign nearest elevator to a request

---

## Class Design

### 1. Elevator
Represents a single elevator.

**Attributes**
- currentFloor
- movingUp

**Responsibilities**
- Move to requested floor
- Open and close doors
- Maintain its current state

---

### 2. Floor
Represents a building floor.

**Attributes**
- floorNumber

**Responsibilities**
- Trigger elevator request when button is pressed

---

### 3. ElevatorSystem
Acts as the brain of the system.

**Responsibilities**
- Receive floor requests
- Find nearest available elevator
- Assign elevator to floor

---

## Design Principles Used
- Single Responsibility Principle
- Encapsulation
- Separation of Concerns
- Simple decision-making logic

---

## Assumptions
- All elevators are always operational
- No direction-based optimization
- Single request handled at a time

---

## Possible Extensions
- Direction-based scheduling
- Elevator capacity handling
- Request queueing
- Emergency mode
- Real-time simulation

---

## How to Run

```bash
g++ elevator_system.cpp -o elevator
./elevator

// Copyright 2024 Nedelin Dmitry

#include <iostream>
#include<stdexcept>
#include "TimedDoor.h"

DoorTimerAdapter::DoorTimerAdapter(TimedDoor& door) : door(door) {}

void DoorTimerAdapter::Timeout() {
    door.throwState();
}

TimedDoor::TimedDoor(int timeout) : isOpened(false), iTimeout(timeout) {
    iTimeout = timeout;
    isOpened = false;
    adapter = new DoorTimerAdapter(*this);
}

bool TimedDoor::isDoorOpened() {
    return isOpened;
}

void TimedDoor::unlock() {
    if (isOpened) {
        throw std::logic_error("The door is adlready open");
    }
    isOpened = true;
}

void TimedDoor::lock() {
    if (!isOpened) {
        throw std::logic_error("The door is already closed");
    }
    isOpened = false;
}

int TimedDoor::getTimeOut() const {
    if (!isOpened) {
        throw std::runtime_error("Door Timeout");
    }
    return 1;
}

void TimedDoor::throwState() {
    getTimeOut();
}

void Timer::sleep(int time) {
    for (int rem_time = time; rem_time > 0; rem_time--) {}
}

void Timer::tregister(int time, TimerClient* timerClient) {
    sleep(time);
    client->Timeout();
}

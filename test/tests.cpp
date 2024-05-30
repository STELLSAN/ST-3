// Copyright 2024 Nedelin Dmitry

#include<threads.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdint>
#include "TimedDoor.h"

class MockTimerClient : public TimerClient {
 public:
    MOCK_METHOD(void, Timeout, ());
};

class TaskDoorTime : public ::testing::Test {
 protected:
    TimedDoor* door;

    void SetUp() override {
        door = new TimedDoor(100);
    }

    void TearDown() override {
        delete door;
    }
};

TEST_F(TaskDoorTime, CheckDoorTimeOutMethod) {
    door->unlock();
    door->lock();
    EXPECT_THROW(door->getTimeOut(), std::runtime_error);
    EXPECT_FALSE(door->isDoorOpened());
}

TEST_F(TaskDoorTime, checkDoorLockMetod_unlock) {
    door->unlock();
    door->lock();
    EXPECT_FALSE(door->isDoorOpened());
}

TEST_F(TaskDoorTime, checkManyDoorInteractions) {
    door->unlock();
    door->lock();
    door->unlock();
    EXPECT_TRUE(door->isDoorOpened());
}

TEST_F(TaskDoorTime, checkDoorOpenMetod) {
    door->unlock();
    EXPECT_TRUE(door->isDoorOpened());
}

TEST_F(TaskDoorTime, checkTimeLockDoorOpened) {
    door->unlock();
    EXPECT_NO_THROW(door->getTimeOut());
    EXPECT_TRUE(door->isDoorOpened());
}

TEST_F(TaskDoorTime, checkDoorClosedAfterTimeout) {
    EXPECT_THROW(door->getTimeOut(), std::runtime_error);
    EXPECT_FALSE(door->isDoorOpened());
}

TEST_F(TaskDoorTime, checkIsClosedThrow) {
    EXPECT_FALSE(door->isDoorOpened());
}


TEST_F(TaskDoorTime, checkOutDoorOpened) {
    door->unlock();
    EXPECT_NO_THROW(door->getTimeOut());
    EXPECT_TRUE(door->isDoorOpened());
}

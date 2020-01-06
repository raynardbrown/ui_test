////////////////////////////////////////////////////////////////////////////////
//
// File: IdManagerTest.cpp
//
// Author: Raynard Brown
//
// Copyright (c) 2019 Raynard Brown
//
// All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#include <cstring>

#include "IdManagerTest.h"

#include "ui/private/windows/IdManager.h"

IdManagerTest::IdManagerTest()
:idManager(NULL)
{
}

IdManagerTest::~IdManagerTest()
{
}

void IdManagerTest::SetUp()
{
}

void IdManagerTest::TearDown()
{
  delete idManager;
  idManager = NULL;
}

TEST_F(IdManagerTest, TestRequestId_OneRangeZeroOffset)
{
  IdManager * idManager = new IdManager(0, 0);

  int result = idManager->requestId();

  const int expectedResult = 0;

  ASSERT_EQ(result, expectedResult);
}

TEST_F(IdManagerTest, TestRequestId_OneRangeOneOffset)
{
  IdManager * idManager = new IdManager(1, 1);

  int result = idManager->requestId();

  const int expectedResult = 1;

  ASSERT_EQ(result, expectedResult);
}

TEST_F(IdManagerTest, TestRequestId_OneRangeCalledTwiceZeroOffset)
{
  IdManager * idManager = new IdManager(0, 0);

  // throw away the result, we know it is 0 from the first test
  idManager->requestId();

  int result = idManager->requestId();

  const int expectedResult =-1;

  ASSERT_EQ(result, expectedResult);
}

TEST_F(IdManagerTest, TestRequestId_OneRangeCalledTwiceOneOffset)
{
  IdManager * idManager = new IdManager(1, 1);

  // throw away the result, we know it is 1 from the first test
  idManager->requestId();

  int result = idManager->requestId();

  const int expectedResult = -1;

  ASSERT_EQ(result, expectedResult);
}

TEST_F(IdManagerTest, TestRequestId_ZeroToFiveRangeZeroOffset)
{
  IdManager * idManager = new IdManager(0, 5);

  int result = idManager->requestId();

  int expectedResult = 0;

  ASSERT_EQ(result, expectedResult);

  result = idManager->requestId();

  expectedResult = 1;

  ASSERT_EQ(result, expectedResult);

  result = idManager->requestId();

  expectedResult = 2;

  ASSERT_EQ(result, expectedResult);

  result = idManager->requestId();

  expectedResult = 3;

  ASSERT_EQ(result, expectedResult);

  result = idManager->requestId();

  expectedResult = 4;

  ASSERT_EQ(result, expectedResult);

  result = idManager->requestId();

  expectedResult = 5;

  ASSERT_EQ(result, expectedResult);
}

TEST_F(IdManagerTest, TestRequestId_OneToFiveRangeOneOffset)
{
  IdManager * idManager = new IdManager(1, 5);

  int result = idManager->requestId();

  int expectedResult = 1;

  ASSERT_EQ(result, expectedResult);

  result = idManager->requestId();

  expectedResult = 2;

  ASSERT_EQ(result, expectedResult);

  result = idManager->requestId();

  expectedResult = 3;

  ASSERT_EQ(result, expectedResult);

  result = idManager->requestId();

  expectedResult = 4;

  ASSERT_EQ(result, expectedResult);

  result = idManager->requestId();

  expectedResult = 5;

  ASSERT_EQ(result, expectedResult);
}

TEST_F(IdManagerTest, TestRequestId_ZeroToFiveRangeZeroOffsetCalledOneExtraTime)
{
  IdManager * idManager = new IdManager(0, 5);

  // throw away the results except for the extra call
  idManager->requestId();
  idManager->requestId();
  idManager->requestId();
  idManager->requestId();
  idManager->requestId();
  idManager->requestId();

  // one extra call
  int result = idManager->requestId();

  const int expectedResult = -1;

  ASSERT_EQ(result, expectedResult);
}

TEST_F(IdManagerTest, TestRequestId_OneToFiveRangeOneOffsetCalledOneExtraTime)
{
  IdManager * idManager = new IdManager(1, 5);

  // throw away the results except for the extra call
  idManager->requestId();
  idManager->requestId();
  idManager->requestId();
  idManager->requestId();
  idManager->requestId();

  // one extra call
  int result = idManager->requestId();

  const int expectedResult = -1;

  ASSERT_EQ(result, expectedResult);
}

TEST_F(IdManagerTest, TestReturnId_OneSlotZeroOffset)
{
  IdManager * idManager = new IdManager(0, 0);

  int result = idManager->requestId();

  int expectedResult = 0;

  ASSERT_EQ(result, expectedResult);

  idManager->returnId(result);

  result = idManager->requestId();

  ASSERT_EQ(result, expectedResult);

  result = idManager->requestId();

  expectedResult = -1;

  ASSERT_EQ(result, expectedResult);
}

TEST_F(IdManagerTest, TestReturnId_ThreeSlotsZeroOffset)
{
  IdManager * idManager = new IdManager(0, 2);

  // get 0 and 1 out of the slots
  idManager->requestId();
  int result = idManager->requestId();

  int expectedResult = 1;

  ASSERT_EQ(result, expectedResult);

  // return 1 to the slot
  idManager->returnId(result);

  // get one back out
  result = idManager->requestId();

  expectedResult = 1;

  ASSERT_EQ(result, expectedResult);

  // only 2 should be left
  result = idManager->requestId();

  expectedResult = 2;

  ASSERT_EQ(result, expectedResult);

  // nothing  should be left
  result = idManager->requestId();

  expectedResult = -1;

  ASSERT_EQ(result, expectedResult);
}

TEST_F(IdManagerTest, TestReturnId_ThreeSlotsZeroOffsetOutOfOrder)
{
  IdManager * idManager = new IdManager(0, 2);

  idManager->requestId();
  int result = idManager->requestId();

  int expectedResult = 1;

  ASSERT_EQ(result, expectedResult);

  // return 0 to the slots
  idManager->returnId(0);

  // get 0 back out
  result = idManager->requestId();

  expectedResult = 0;

  ASSERT_EQ(result, expectedResult);

  // only 2 should be left
  result = idManager->requestId();

  expectedResult = 2;

  ASSERT_EQ(result, expectedResult);

  result = idManager->requestId();

  expectedResult = -1;

  ASSERT_EQ(result, expectedResult);
}

TEST_F(IdManagerTest, TestReturnId_ThreeSlotsZeroOffsetReturnAnIdThatWasNotClaimed)
{
  IdManager * idManager = new IdManager(0, 2);

  // pull 0 out
  int result = idManager->requestId();

  int expectedResult = 0;

  ASSERT_EQ(result, expectedResult);

  // try to return 2 even though it was never claimed
  idManager->returnId(2);

  // get 1 back out
  result = idManager->requestId();

  expectedResult = 1;

  ASSERT_EQ(result, expectedResult);

  // only 2 should be left
  result = idManager->requestId();

  expectedResult = 2;

  ASSERT_EQ(result, expectedResult);

  result = idManager->requestId();

  expectedResult = -1;

  ASSERT_EQ(result, expectedResult);
}

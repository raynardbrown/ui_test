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

#include "private/windows/IdManager.h"

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

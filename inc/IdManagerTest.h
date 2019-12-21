////////////////////////////////////////////////////////////////////////////////
//
// File: IdManagerTest.h
//
// Author: Raynard Brown
//
// Copyright (c) 2019 Raynard Brown
//
// All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef IDMANAGERTEST_H_
#define IDMANAGERTEST_H_

#include "gtest/gtest.h"

class IdManager;

class IdManagerTest : public testing::Test
{
  protected:

    IdManagerTest();

    virtual ~IdManagerTest();

    virtual void SetUp();

    virtual void TearDown();

    IdManager * idManager;
};
#endif /* IDMANAGERTEST_H_ */

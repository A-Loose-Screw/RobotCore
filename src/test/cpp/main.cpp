#include "RobotCore.h"

#include "gtest/gtest.h"

class Robot : public RBC::RobotBase {
 public:
  Robot(int argc, char** argv) : RBC::RobotBase("Levi-Test", argc, argv) {
    ::testing::InitGoogleTest(&argc, argv);
  }

  void robotInit() override {
    shutdown(RUN_ALL_TESTS());
  }
  void robotPeriodic() override {}

  void enabledInit() override {}
  void enabledPeriodic() override {}
};

RBC_ROBOT_MAIN(Robot);
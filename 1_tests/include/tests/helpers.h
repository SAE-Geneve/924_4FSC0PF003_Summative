#ifndef HELPERS_H
#define HELPERS_H

#include <gtest/gtest.h>
#include "behaviour_tree/behaviour_tree.h"

using namespace behaviour_tree;

inline Status simple_action (const bool check_conditions, const bool action_executed){
  Status status;

  if (check_conditions) {
    if (action_executed) {
      status = Status::kSuccess;
    }else {
      status = Status::kRunning;
    }
  }else {
    status = Status::kFailure;
  }

  std::cout << "Status : " << check_conditions << " : " << action_executed << " : " << status_to_str(status) << std::endl;
  return status;
};

inline auto AlwaysSuccess = [](){return Status::kSuccess;};
inline auto AlwaysRunning = [](){return Status::kRunning;};
inline auto AlwaysFailed = [](){return Status::kFailure;};

#endif //HELPERS_H
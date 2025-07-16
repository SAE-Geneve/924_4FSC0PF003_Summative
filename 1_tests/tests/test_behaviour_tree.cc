#include <gtest/gtest.h>
#include "behaviour_tree/behaviour_tree.h"
#include "tests/helpers.h"

using namespace behaviour_tree;

// Helpers ---------------------------------------------------------------------------------------

TEST(BehaviourTree, leaf_basics) {

  Leaf leaf_a(AlwaysSuccess);
  EXPECT_EQ(leaf_a.Tick(), Status::kSuccess);

  Leaf leaf_b(AlwaysRunning);
  EXPECT_EQ(leaf_b.Tick(), Status::kRunning);

  Leaf leaf_c(AlwaysFailed);
  EXPECT_EQ(leaf_c.Tick(), Status::kFailure);

}

TEST(BehaviourTree, no_loop_empty) {

  NoLoop no_loop;

  no_loop.Tick();
  EXPECT_EQ(no_loop.Tick(), Status::kFailure);

}

TEST(BehaviourTree, no_loop_one_child) {

  bool check_conditions = false;
  bool action_executed = false;
  NoLoop no_loop;

  no_loop.Add(std::make_unique<Leaf>([&]{return simple_action(check_conditions, action_executed);}));

  EXPECT_EQ(no_loop.Tick(), Status::kFailure);

  check_conditions = true;
  EXPECT_EQ(no_loop.Tick(), Status::kRunning);

  action_executed = true;
  EXPECT_EQ(no_loop.Tick(), Status::kSuccess);

  check_conditions = false;
  EXPECT_EQ(no_loop.Tick(), Status::kSuccess);

}

TEST(BehaviourTree, no_loop_multiple_children) {

  bool check_conditions_a, action_executed_a;
  bool check_conditions_b, action_executed_b;

  check_conditions_a = false;
  check_conditions_b = false;
  action_executed_a = false;
  action_executed_b = false;

  NoLoop no_loop;
  no_loop.Add(std::make_unique<Leaf>([&]{return simple_action(check_conditions_a, action_executed_a);}));
  no_loop.Add(std::make_unique<Leaf>([&]{return simple_action(check_conditions_b, action_executed_b);}));

  EXPECT_EQ(no_loop.Tick(), Status::kFailure);

  check_conditions_a = true;
  EXPECT_EQ(no_loop.Tick(), Status::kRunning);

  action_executed_a = true;
  EXPECT_EQ(no_loop.Tick(), Status::kFailure);

  check_conditions_b = true;
  EXPECT_EQ(no_loop.Tick(), Status::kRunning);

  action_executed_b = true;
  EXPECT_EQ(no_loop.Tick(), Status::kSuccess);

}

TEST(BehaviourTree, selector_one_child) {
  bool check_conditions = false;
  bool action_executed = false;
  Selector selector;

  selector.Add(std::make_unique<Leaf>([&]{return simple_action(check_conditions, action_executed);}));

  EXPECT_EQ(selector.Tick(), Status::kFailure);

  check_conditions = true;
  EXPECT_EQ(selector.Tick(), Status::kRunning);

  action_executed = true;
  EXPECT_EQ(selector.Tick(), Status::kSuccess);
  EXPECT_EQ(selector.Tick(), Status::kSuccess);

}

TEST(BehaviourTree, selector_multiple_children) {

  int choice = 0;
  std::string action_result = "";

  auto choice_a = [&] (){
    if (choice == 1) {
      action_result = "manger";
      return Status::kSuccess;
    }else {
      return Status::kFailure;
    }
  };
  auto choice_b = [&] (){
    if (choice == 2) {
      action_result = "dormir";
      return Status::kSuccess;
    }else {
      return Status::kFailure;
    }
  };

  Selector selector;
  selector.Add(std::make_unique<Leaf>(choice_a));
  selector.Add(std::make_unique<Leaf>(choice_b));

  choice = 1;
  selector.Tick();
  EXPECT_EQ(action_result, "manger");

  choice = 2;
  selector.Tick();
  EXPECT_EQ(action_result, "dormir");

}

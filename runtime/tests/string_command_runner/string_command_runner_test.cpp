#include <gtest/gtest.h>

#include <Core/StringCommandRunner.h>

using namespace ERUNTIME_NAMESPACE;

TEST(string_command_runner_test, command_args)
{
    EXPECT_EQ(CommandArgs::Parse("one two three").Count(), 3);
    EXPECT_EQ(CommandArgs::Parse("").Count(), 0);
    EXPECT_EQ(CommandArgs::Parse("a b c d e f g").Count(), 7);
    EXPECT_EQ(CommandArgs::Parse("onlyone").Count(), 1);
}

TEST(string_command_runner_test, basic_assertions)
{
    ASSERT_TRUE(StringCommandRunner::Instance().AddCommand(
        { .name = "just_a_cmd", .description = "description" },
                      [](CommandArgs args) { EXPECT_EQ(args.Count(), 2); }
    ).has_value());

    ASSERT_FALSE(StringCommandRunner::Instance().AddCommand(
        { .name = "just_a_cmd", .description = "description" },
        [](auto _) {}
    ).has_value());

    ASSERT_TRUE(StringCommandRunner::Instance().Run("just_a_cmd 1 2").has_value());

    ASSERT_TRUE(StringCommandRunner::Instance().RemoveCommand("just_a_cmd").has_value());

    ASSERT_FALSE(StringCommandRunner::Instance().Run("just_a_cmd 1 2").has_value());

    ASSERT_FALSE(StringCommandRunner::Instance().RemoveCommand("just_a_cmd").has_value());
}
/**
 * Unit Tests for the class
**/

#include <gtest/gtest.h>
#include "Guesser.h"

class GuesserTest : public ::testing::Test
{
	protected:
		GuesserTest(){} //constructor runs before each test
		virtual ~GuesserTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};

/* Example test
TEST(GuesserTest, smoke_test)
{
    ASSERT_EQ( 1+1, 2 );
}
*/

TEST(GuesserTest, Matchsuccess) {
	Guesser guesser("secret");
	ASSERT_TRUE(guesser.match("secret"));
}

TEST(GuesserTest, MatchFailOneWrong) {
    Guesser guesser("secret");
    ASSERT_FALSE(guesser.match("secret1"));
}

TEST(GuesserTest, MatchSuccessOneWrongThenSuccess) {
    Guesser guesser("secret");
	guesser.match("secret1");
    ASSERT_TRUE(guesser.match("secret"));
}

TEST(GuesserTest, MatchSuccessTwoWrongThenSuccess) {
    Guesser guesser("secret");
	guesser.match("secret1");
	guesser.match("secret2");
    ASSERT_TRUE(guesser.match("secret"));
}

TEST(GuesserTest, MatchSuccessThreeWrongThenCorrectGuess) {
    Guesser guesser("secret");
	guesser.match("secret1");
	guesser.match("secret2");
	guesser.match("secret3");
    ASSERT_FALSE(guesser.match("secret"));
}

TEST(GuesserTest, MatchLocksAfterThreeFailures) {
    Guesser guesser("secret");
    guesser.match("secret1");
    guesser.match("secret1");
    guesser.match("secret1");
    ASSERT_FALSE(guesser.match("secret"));
}

TEST(GuesserTest, EarlyMatchLockLongGuess) {
    Guesser guesser("secret");
    guesser.match("secretwithextratext");
    ASSERT_FALSE(guesser.match("secret"));
}

TEST(GuesserTest, EarlyMatchLockShortGuess) {
    Guesser guesser("secret");
    guesser.match("sec");
    ASSERT_FALSE(guesser.match("secret"));
}

TEST(GuesserTest, EarlyMatchLockVeryWrongGuess) {
    Guesser guesser("secret");
    guesser.match("wrong");
    ASSERT_FALSE(guesser.match("secret"));
}

TEST(GuesserTest, SecretTrunicationSuccess) {
    Guesser guesser("THISSECRETISEXACTLY35CHARACTERSLONG");
    ASSERT_TRUE(guesser.match("THISSECRETISEXACTLY35CHARACTERSL"));
}

TEST(GuesserTest, SecretTrunicationFailure) {
    Guesser guesser("THISSECRETISEXACTLY35CHARACTERSLONG");
    ASSERT_FALSE(guesser.match("THISSECRETISEXACTLY35CHARACTERSLONG"));
}

TEST(GuesserTest, OneGuessTwoRemaining) {
    Guesser guesser("secret");
	guesser.match("secret1");
    ASSERT_EQ(guesser.remaining(), 2);
}

TEST(GuesserTest, TwoGuessOneRemaining) {
    Guesser guesser("secret");
	guesser.match("secret1");
	guesser.match("secret2");
    ASSERT_EQ(guesser.remaining(), 1);
}

TEST(GuesserTest, ThreeGuessZeroRemaining) {
    Guesser guesser("secret");
	guesser.match("secret1");
	guesser.match("secret2");
	guesser.match("secret3");
    ASSERT_EQ(guesser.remaining(), 0);
}

TEST(GuesserTest, SuccessResetRemainingGuess) {
    Guesser guesser("secret");
	guesser.match("secret1");
	guesser.match("secret2");
	guesser.match("secret");
    ASSERT_EQ(guesser.remaining(), 3);
}

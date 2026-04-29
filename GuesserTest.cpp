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

// Example "smoke test" (can be deleted)
TEST(GuesserTest, DistanceIsZeroForExactMatch)
{
  Guesser object("Secret");
  EXPECT_EQ(object.distance("Secret"), 0);
}

TEST(GuesserTest, DistanceCountsDifferentCharactersSameLength)
{
  Guesser object("Secret");
  EXPECT_EQ(object.distance("SecRet"), 1);
  EXPECT_EQ(object.distance("Sxxxxx"), 5);
}

TEST(GuesserTest, DistanceCountsExtraCharactersInLongerGuess)
{
  Guesser object("Secret");
  EXPECT_EQ(object.distance("Secret123"), 3);
}

TEST(GuesserTest, DistanceCountsMissingCharactersInShorterGuess)
{
  Guesser object("Secret");
  EXPECT_EQ(object.distance("Sec"), 3);
}

TEST(GuesserTest, DistanceCannotExceedSecretLength)
{
  Guesser object("Secret");
  EXPECT_EQ(object.distance("CompletelyDifferentAndVeryLong"), 6);
}

TEST(GuesserTest, DistanceWorksWithEmptyGuess)
{
  Guesser object("Secret");
  EXPECT_EQ(object.distance(""), 6);
}

// match() tests

TEST(GuesserTest, MatchReturnsTrueForCorrectGuess)
{
  Guesser object("Secret");
  EXPECT_TRUE(object.match("Secret"));
}

TEST(GuesserTest, MatchReturnsFalseForIncorrectGuess)
{
  Guesser object("Secret");
  EXPECT_FALSE(object.match("SecRet"));
}

TEST(GuesserTest, CorrectGuessResetsRemainingGuesses)
{
  Guesser object("Secret");

  EXPECT_FALSE(object.match("Secrex"));
  EXPECT_FALSE(object.match("Secrey"));

  EXPECT_TRUE(object.match("Secret"));

  EXPECT_FALSE(object.match("Secrex"));
  EXPECT_FALSE(object.match("Secrey"));
  EXPECT_TRUE(object.match("Secret"));
}

TEST(GuesserTest, ThreeConsecutiveWrongGuessesLockObject)
{
  Guesser object("Secret");

  EXPECT_FALSE(object.match("Secrex"));
  EXPECT_FALSE(object.match("Secrey"));
  EXPECT_FALSE(object.match("Secrez"));

  EXPECT_FALSE(object.match("Secret"));
}

TEST(GuesserTest, BruteForceGuessLocksObject)
{
  Guesser object("Secret");

  EXPECT_FALSE(object.match("Wrong"));
  EXPECT_FALSE(object.match("Secret"));
}


TEST(GuesserTest, LockedObjectAlwaysReturnsFalse)
{
  Guesser object("Secret");

  EXPECT_FALSE(object.match("TotallyWrong"));
  EXPECT_FALSE(object.match("Secret"));
  EXPECT_FALSE(object.match("Secret"));
}

/*!
 * @file    test_parsy_uint.c
 * @brief   Test file for the unsigned integer parsy API
 * 
 * @author  Abdullah Almosalami @c85hup8
 * @date    Tues Oct 2025
 * @copyright MIT License
 */

/* File Inclusions */
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "unity.h"
#include "parsy_uint.h"

/* Local Macro Definitions */

/* Local Datatypes */

/* Forward Function Declarations */
// Test Setup
void setUp(void);
void tearDown(void);

// ----- Unit Test Cases -----
// -- Single Integer Parsing --
// - Invalid Inputs -
void test_ParsyUInt_NullStr(void);
void test_ParsyUInt_NonNullTerminatedStr(void);
void test_ParsyUInt_NullBuf(void);
void test_ParsyUInt_InvalidDefaultFmt(void);

// - Basic Usage -
// String that's just a number
void test_ParsyUInt_Unsigned_NumStr_Zero(void);

void test_ParsyUInt_Unsigned_NumStr_Dec_8bit_NonZero(void);
void test_ParsyUInt_Unsigned_NumStr_Dec_16bit_NonZero(void);
void test_ParsyUInt_Unsigned_NumStr_Dec_32bit_NonZero(void);
void test_ParsyUInt_Unsigned_NumStr_Dec_64bit_NonZero(void);

void test_ParsyUInt_Unsigned_NumStr_Hex_8bit_NonZero(void);
void test_ParsyUInt_Unsigned_NumStr_Hex_16bit_NonZero(void);
void test_ParsyUInt_Unsigned_NumStr_Hex_32bit_NonZero(void);
void test_ParsyUInt_Unsigned_NumStr_Hex_64bit_NonZero(void);

void test_ParsyUInt_Unsigned_NumStr_Bin_8bit_NonZero(void);
void test_ParsyUInt_Unsigned_NumStr_Bin_16bit_NonZero(void);
void test_ParsyUInt_Unsigned_NumStr_Bin_32bit_NonZero(void);
void test_ParsyUInt_Unsigned_NumStr_Bin_64bit_NonZero(void);

void test_ParsyUInt_Unsigned_NumStr_Oct_8bit_NonZero(void);
void test_ParsyUInt_Unsigned_NumStr_Oct_16bit_NonZero(void);
void test_ParsyUInt_Unsigned_NumStr_Oct_32bit_NonZero(void);
void test_ParsyUInt_Unsigned_NumStr_Oct_64bit_NonZero(void);
// Setence with a number
void test_ParsyUInt_Unsigned_SentenceStr_Dec_8Bit_NonZero(void);
void test_ParsyUInt_Unsigned_SentenceStr_Dec_8Bit_NonZero(void);
void test_ParsyUInt_Unsigned_SentenceStr_Dec_8Bit_NonZero(void);
void test_ParsyUInt_Unsigned_SentenceStr_Dec_8Bit_NonZero(void);

void test_ParsyUInt_Unsigned_SentenceStr_Hex_8bit_NonZero(void);
void test_ParsyUInt_Unsigned_SentenceStr_Hex_16bit_NonZero(void);
void test_ParsyUInt_Unsigned_SentenceStr_Hex_32bit_NonZero(void);
void test_ParsyUInt_Unsigned_SentenceStr_Hex_64bit_NonZero(void);

void test_ParsyUInt_Unsigned_SentenceStr_Bin_8bit_NonZero(void);
void test_ParsyUInt_Unsigned_SentenceStr_Bin_16bit_NonZero(void);
void test_ParsyUInt_Unsigned_SentenceStr_Bin_32bit_NonZero(void);
void test_ParsyUInt_Unsigned_SentenceStr_Bin_64bit_NonZero(void);

void test_ParsyUInt_Unsigned_SentenceStr_Oct_8bit_NonZero(void);
void test_ParsyUInt_Unsigned_SentenceStr_Oct_16bit_NonZero(void);
void test_ParsyUInt_Unsigned_SentenceStr_Oct_32bit_NonZero(void);
void test_ParsyUInt_Unsigned_SentenceStr_Oct_64bit_NonZero(void);

// - Signed Integer Cases -
// String that's just a number
void test_ParsyUInt_NumStr_Dec_8bit_Signed(void);
void test_ParsyUInt_NumStr_Dec_16bit_Signed(void);
void test_ParsyUInt_NumStr_Dec_32bit_Signed(void);
void test_ParsyUInt_NumStr_Dec_64bit_Signed(void);
// TODO
// Setence with a number
void test_ParsyUInt_SetenceStr_Dec_8bit_Signed(void);
void test_ParsyUInt_SetenceStr_Dec_16bit_Signed(void);
void test_ParsyUInt_SetenceStr_Dec_32bit_Signed(void);
void test_ParsyUInt_SetenceStr_Dec_64bit_Signed(void);
// TODO

// - Floating-Point Cases -
// String that's just a number
void test_ParsyUInt_NumStr_Float(void);
void test_ParsyUInt_NumStr_Double(void);
// Setence with a number
void test_ParsyUInt_SentenceStr_Float(void);
void test_ParsyUInt_SentenceStr_Double(void);

// - Larger Integer Cases -
// String that's just a number
void test_ParsyUInt_NumStr_Dec_ExtremelyLargeNumber(void);
void test_ParsyUInt_NumStr_Hex_ExtremelyLargeNumber(void);
void test_ParsyUInt_NumStr_Bin_ExtremelyLargeNumber(void);
void test_ParsyUInt_NumStr_Oct_ExtremelyLargeNumber(void);
// Sentence with a number
void test_ParsyUInt_SentenceStr_Dec_ExtremelyLargeNumber(void);
void test_ParsyUInt_SentenceStr_Hex_ExtremelyLargeNumber(void);
void test_ParsyUInt_SentenceStr_Bin_ExtremelyLargeNumber(void);
void test_ParsyUInt_SentenceStr_Oct_ExtremelyLargeNumber(void);

/******************************************************************************/
/* Main Test Suite Functions */
int main(void)
{
   UNITY_BEGIN();

   RUN_TEST(test_ParsyUInt_NullStr);
   RUN_TEST(test_ParsyUInt_NonNullTerminatedStr);
   RUN_TEST(test_ParsyUInt_NullBuf);
   RUN_TEST(test_ParsyUInt_InvalidDefaultFmt);

   return UNITY_END();
}

void setUp(void)
{
   // Do nothing
}
void tearDown(void)
{
   // Do nothing
}

/* Test Cases */
void test_ParsyUInt_NullStr(void)
{
   enum ParsyResult res = ParsyUInt(nullptr, "25", Parsy_Dec);
   TEST_ASSERT_NOT_EQUAL_INT(Parsy_GoodResult, res);
   TEST_ASSERT_EQUAL_INT(Parsy_InvalidString, res);
}

void test_ParsyUInt_NonNullTerminatedStr(void)
{
   TEST_ASSERT_TRUE(false);
}

void test_ParsyUInt_NullBuf(void)
{
   TEST_ASSERT_FALSE(true);
}

void test_ParsyUInt_InvalidDefaultFmt(void)
{
   TEST_ASSERT_TRUE(false);
}

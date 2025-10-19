/*!
 * @file    nparsy_uint.c
 * @brief   Implementation of NParsy's unsigned integer parsing.
 * @author  Abdullah Almosalami @memphis242
 * @date    Oct 2025
 * @copyright MIT License
 */

/* File Inclusions */
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

#include "nparsy_uint.h"

/* Local Macro Definitions */

/* Datatypes */

/* Local Data */

/*** Private Function Prototypes ***/
static bool nparsy_atoi(char digit, uint8_t * converted_digit);

/* Public Function Implementations */

/******************************************************************************/
// Acceptable formats:
// Hex:     0xZZ, ZZ, ZZh, ZZH, ZZx, ZZX, xZZ, XZZ
// Decimal: ZZd, ZZD ZZ
// Binary:  0bZZ ZZ
[[nodiscard]]
enum NParsyResult NParsyUInt(
         const char * str,
         uint64_t * parsed_val,
         size_t * accumulated_strlen,
         enum NParsyNumFormat default_fmt )
{
   // Initial input validation
   if ( str == nullptr )
      return NParsy_InvalidString;
   else if ( parsed_val == nullptr )
      return NParsy_NullPtr;
   else if ( (int)default_fmt < 0 || (int)default_fmt > (int)NParsy_NumOfFmts )
      return NParsy_InvalidDefaultFormat;

   // TODO
   // Parsing State Machine Time!
   enum ParserState
   {
      Parser_Init,
      Parser_NonDigitChars,
      Parser_AmbiguousDigit,
      Parser_HexPrefix,
      Parser_BinPrefix,
      Parser_HexNum,
      Parser_BinNum,
      Parser_DecSuffix,
      Parser_HexSuffix,
      Parser_UIntObtained
   } parser_state = Parser_Init;

   size_t nchars_parsed = 1;
   ptrdiff_t str_idx = 0;
   uint64_t valbuf = 0;
   enum NParsyResult result = NParsy_GoodResult;
   do
   {
      // TODO

      ++nchars_parsed;
      ++str_idx;
   }
   while ( parser_state != Parser_UIntObtained
           && nchars_parsed < NPARSY_MAX_PARSABLE_STRING_LEN );

   if ( parser_state == Parser_UIntObtained )
      *parsed_val = valbuf;

   if ( accumulated_strlen != nullptr )
      *accumulated_strlen = nchars_parsed;

   return result;
}

/******************************************************************************/
[[nodiscard]]
enum NParsyResult NParsyUIntList(
      const char * str,
      uint64_t * buf,
      size_t len )
{
   // TODO

   return NParsy_GoodResult;
}

STATIC enum LIN_PID_Result_E GetID( const char * str,
                                    uint8_t * id,
                                    bool * ishex,
                                    bool * isdec )
{
   assert( (str != NULL) &&
           (id  != NULL) &&
           (!(*ishex) || !(*isdec)) );

   enum LIN_PID_Result_E result = GoodResult;
   size_t idx = 0;
   size_t loop_limit_counter = 0;

   // Skip over any leading whitespace
   // TODO: Do I need to check for this? Can I trust that the terminal will not
   //       pass in white-space leading characters?
   while (
      /* x2 as max allowance of leading whitespace */
      (loop_limit_counter <= (MAX_NUM_LEN * 2)) &&
      (str[idx] != '\0') &&
      (isblank( (int)str[idx] ))
   )
   {
      idx++;
      loop_limit_counter++;
   }
   if ( str[idx] == '\0' )
   {
      return WhiteSpaceOnlyIDArg;
   }

   // Parser State Machine Time!
   enum ParserState_E
   {
      ParserInit,
      ParserOneZeroIn,
      ParserHexPrefix,
      ParserIndeterminateOneDigitIn,
      ParserIndeterminateTwoDigitsIn,
      ParserOneDecDigit,
      ParserTwoDecDigits,
      ParserHexDigits,
      ParserTwoHexDigits,
      ParserTwoZerosIn,
      ParserTwoDigitsAlreadyRead,
      ParserPreemptivelyHex,
      ParserPreemptivelyDec,
      ParserPreemptivelyDecOneZeroIn,
      ParserPreemptivelyDecTwoZerosIn
   } parser_state;
   loop_limit_counter = 0;
   bool exit_loop = false;
   char first_digit = '\0';
   char second_digit = '\0';
   bool assume_hex = *ishex;
   bool assume_dec = *isdec;
   bool hex_prefix_already_encountered = false;

   if ( *ishex )
   {
      parser_state = ParserPreemptivelyHex;
   }
   else if ( *isdec )
   {
      parser_state = ParserPreemptivelyDec;
   }
   else
   {
      parser_state = ParserInit;
   }

   char ch = '\0';
   while (
      (loop_limit_counter <= MAX_NUM_LEN) &&
      (str[idx] != '\0') && /* Continue until terminating null character */
      !exit_loop /* Redundant here but I like extra guard rails */
   )
   {
      ch = str[idx];
      switch (parser_state)
      {
         case ParserInit:
            if ( '0' == ch )
            {
               first_digit = ch;
               parser_state = ParserOneZeroIn;
            }
            else if ( isxdigit(ch) )
            {
               if ( isdigit(ch) )
               {
                  // Determined to be within hex range but also within dec range
                  // so, still indeterminate...
                  parser_state = ParserIndeterminateOneDigitIn;
               }
               else
               {
                  // Must be a uniquely hex digit
                  assume_hex = true;
                  parser_state = ParserHexDigits;
               }
               first_digit = ch;
            }
            else if ( ('x' == ch) || ('X' == ch) )
            {
               assume_hex = true;
               hex_prefix_already_encountered = true;
               parser_state = ParserHexPrefix;
            }
            else
            {
               result = InvalidCharacterEncountered_FirstChar;
               exit_loop = true;
            }
            break;

         case ParserOneZeroIn:
            if ( '0' == ch )
            {
               second_digit = ch;
               parser_state = ParserTwoZerosIn;
            }
            else if ( ('x' == ch) || ('X' == ch) )
            {
               assume_hex = true;
               hex_prefix_already_encountered = true;
               parser_state = ParserHexPrefix;
            }
            else if ( isxdigit(ch) )
            {
               if ( !isdigit(ch) )
               {
                  // Must be a uniquely hex digit
                  // NOTE: The 'd' suffix would also lead to this line,
                  //       and the user may have intended a decimal number.
                  //       I have chosen that the hex variant will take hold unless
                  //       --dec | -d was specified.
                  assume_hex = true;
                  parser_state = ParserTwoHexDigits;
               }
               else
               {
                  parser_state = ParserIndeterminateTwoDigitsIn;
               }
               first_digit = ch;
            }
            else if ( ('h' == ch) || ('H' == ch) )
            {
               assume_hex = true;
               parser_state = ParserTwoDigitsAlreadyRead;
            }
            else
            {
               result = InvalidDigitEncountered_SecondDigit;
               exit_loop = true;
            }
            break;

         case ParserHexPrefix:
            if ( isxdigit(ch) )
            {
               first_digit = ch;
               parser_state = ParserHexDigits;
            }
            else
            {
               result = InvalidDigitEncountered_FirstDigit;
               exit_loop = true;
            }
            break;

         case ParserIndeterminateOneDigitIn:
            if ( isxdigit(ch) )
            {
               if ( isdigit(ch) )
               {
                  parser_state = ParserIndeterminateTwoDigitsIn;
               }
               else
               {
                  assume_hex = true;
                  parser_state = ParserTwoHexDigits;
               }
               second_digit = ch;
            }
            else if ( ('x' == ch) || ('X' == ch) ||
                      ('h' == ch) || ('H' == ch) )
            {
               assume_hex = true;
               parser_state = ParserTwoDigitsAlreadyRead;
            }
            else
            {
               result = InvalidDigitEncountered_SecondDigit;
               exit_loop = true;
            }
            break;
         
         case ParserIndeterminateTwoDigitsIn:
            if ( ('x' == ch) || ('X' == ch) || ('h' == ch) || ('H' == ch) )
            {
               assume_hex = true;
               parser_state = ParserTwoDigitsAlreadyRead;
            }
            else if ( ('d' == ch) || ('D' == ch) )
            {
               assume_dec = true;
               parser_state = ParserTwoDigitsAlreadyRead;
            }
            else
            {
               result = TooManyDigitsEntered;
               exit_loop = true;
            }
            break;

         case ParserOneDecDigit:
            if ( isdigit(ch) )
            {
               second_digit = ch;
               parser_state = ParserTwoDecDigits;
            }
            else
            {
               result = InvalidDigitEncountered_SecondDigit;
               exit_loop = true;
            }
            break;

         case ParserTwoDecDigits:
            // Two decimal digits will have already been read in...
            if ( ('d' == ch) || ('D' == ch) )
            {
               parser_state = ParserTwoDigitsAlreadyRead;
            }
            else
            {
               result = InvalidDecimalSuffixEncountered;
               exit_loop = true;
            }
            break;
         
         case ParserHexDigits:
            if ( isxdigit(ch) )
            {
               second_digit = ch;
               parser_state = ParserTwoHexDigits;
            }
            else if ( ('x' == ch) || ('X' == ch) ||
                      ('h' == ch) || ('H' == ch) )
            {
               if ( hex_prefix_already_encountered )
               {
                  result = HexPrefixAndSuffixEncountered;
                  exit_loop = true;
               }
               else
               {
                  assume_hex = true;
                  parser_state = ParserTwoDigitsAlreadyRead;
               }
            }
            else
            {
               result = InvalidDigitEncountered_SecondDigit;
               exit_loop = true;
            }
            break;

         case ParserTwoHexDigits:
            // Two hex digits will have already been read in...
            if ( ('x' == ch) || ('X' == ch) ||
                 ('h' == ch) || ('H' == ch) )
            {
               parser_state = ParserTwoDigitsAlreadyRead;
            }
            else
            {
               result = InvalidDecimalSuffixEncountered;
               exit_loop = true;
            }
            break;

         case ParserTwoZerosIn:
            if ( !assume_dec &&
                     ( ('x' == ch) || ('X' == ch) || ('h' == ch) || ('H' == ch) ) )
            {
               assume_hex = true;
               parser_state = ParserTwoDigitsAlreadyRead;
            }
            else if ( !assume_hex &&
                     ( ('d' == ch) || ('D' == ch) ) )
            {
               assume_dec = true;
               parser_state = ParserTwoDigitsAlreadyRead;
            }
            else
            {
               result = TooManyDigitsEntered;
               exit_loop = true;
            }
            break;

         case ParserTwoDigitsAlreadyRead:
            result = TooManyDigitsEntered;
            exit_loop = true;
            break;

         case ParserPreemptivelyHex:
            if ( ('x' == ch) || ('X' == ch) )
            {
               hex_prefix_already_encountered = true;
               parser_state = ParserHexPrefix;
            }
            else if ( '0' == ch )
            {
               parser_state = ParserOneZeroIn;
            }
            else if ( isxdigit(ch) )
            {
               first_digit = ch;
               parser_state = ParserHexDigits;
            }
            else
            {
               result = InvalidCharacterEncountered_FirstChar;
               exit_loop = true;
            }
            break;

         case ParserPreemptivelyDec:
            if ( ('x' == ch) || ('X' == ch) || (isxdigit(ch) && !isdigit(ch)) )
            {
               result = HexDigitEncounteredUnderDecSetting_FirstDigit;
               exit_loop = true;
            }
            else if ( '0' == ch )
            {
               first_digit = ch;
               parser_state = ParserPreemptivelyDecOneZeroIn;
            }
            else if ( isdigit(ch) )
            {
               first_digit = ch;
               parser_state = ParserOneDecDigit;
            }
            else
            {
               result = InvalidCharacterEncountered_FirstChar;
               exit_loop = true;
            }
            break;

         case ParserPreemptivelyDecOneZeroIn:
            if ( ('x' == ch) || ('X' == ch) || (isxdigit(ch) && !isdigit(ch)) )
            {
               result = HexDigitEncounteredUnderDecSetting_SecondDigit;
               exit_loop = true;
            }
            else if ( '0' == ch )
            {
               parser_state = ParserPreemptivelyDecTwoZerosIn;
            }
            else if ( isdigit(ch) )
            {
               first_digit = ch;
               parser_state = ParserTwoDecDigits;
            }
            else
            {
               result = InvalidCharacterEncountered_SecondChar;
               exit_loop = true;
            }
            break;

         case ParserPreemptivelyDecTwoZerosIn:
            if ( ('d' == ch) || ('D' == ch) )
            {
               parser_state = ParserTwoDigitsAlreadyRead;
            }
            else
            {
               result = InvalidDecimalSuffixEncountered;
               exit_loop = true;
            }
            break;

         default:
            assert(false); // Something went wrong /w the parser_state or we
                           // forgot to account for a state!
            break;
      }
      
      // Do we need to exit the loop pre-emptively due to an erroneous situation?
      if ( exit_loop )
      {
         break;
      }

      idx++;
      loop_limit_counter++;
   }
   
   // Logic should not determine that input was both hex and dec at the same time
   assert( !(assume_hex && assume_dec) );
   
   // Post state machine processing
   if ( loop_limit_counter >= MAX_NUM_LEN )
   {
      result = TooManyDigitsEntered;
   }
   else if ( exit_loop )
   {
      // Something erroneous was detected. Don't update ID!
   }
   else if ( (assume_hex || assume_dec) && ('\0' == first_digit) && ('\0' == second_digit) )
   {
      result = NoNumericalDigitsEnteredWithFormat;
   }

   else
   {
      // We got valid digits! Let's get that ID.
      uint8_t most_significant_digit = 0xFF;
      uint8_t least_significant_digit = 0xFF;

      // By this point, I assume we have at least one digit placed in first_digit.
      assert( (first_digit != '\0') );

      // Only one digit entered
      if ( second_digit == '\0' )
      {
         most_significant_digit = 0x00u;
#ifndef NDEBUG
         bool conv = nparsy_atoi( first_digit, &least_significant_digit );
#else
         (void)nparsy_atoi( first_digit, &least_significant_digit );
#endif
         assert( conv );
         assert( (most_significant_digit == 0x00) && (least_significant_digit <= 0x0F) );
      }

      // Two digits entered
      else
      {
#ifndef NDEBUG
         bool conv1 = nparsy_atoi( first_digit, &most_significant_digit );
         bool conv2 = nparsy_atoi( second_digit, &least_significant_digit );
#else
         (void)nparsy_atoi( first_digit, &most_significant_digit );
         (void)nparsy_atoi( second_digit, &least_significant_digit );
#endif
         assert( conv1 && conv2 );
         assert( (most_significant_digit <= 0x0F) && (least_significant_digit <= 0x0F) );
      }

      // Digits obtained should be <= 0xF
      assert( (most_significant_digit <= 0x0F) && (least_significant_digit <= 0x0F) );

      // Final step!
      if ( (0 == most_significant_digit) && (0 == least_significant_digit) )
      {
         *id = 0x00u;
      }
      else if ( assume_hex || !assume_dec )
      {
         *id = (uint8_t)( (most_significant_digit * 0x10) + least_significant_digit );
      }
      else  // Must be decimal
      {
         *id = (uint8_t)( (most_significant_digit * 10) + least_significant_digit );
      }
   }

   *ishex = assume_hex;
   *isdec = assume_dec;
   
   return result;
}

/*** Private Function Implementations ***/

/**
 * @brief Like the C std lib atoi, but safer and more expressive.
 */
static bool nparsy_atoi(char digit, uint8_t * converted_digit)
{
   assert( converted_digit != NULL );

   // Check input validity
   if (   ( digit >= '0' && digit <= '9' )
       || ( digit >= 'A' && digit <= 'F' )
       || ( digit >= 'a' && digit <= 'f' ) )
   {
      if ( (digit >= '0') && (digit <= '9') )
         *converted_digit = (uint8_t)(digit - '0');

      else if ( (digit >= 'A') && (digit <= 'F') )
         *converted_digit = (uint8_t)(10 + (digit - 'A'));

      else
         *converted_digit = (uint8_t)(10 + (digit - 'a'));

      return true;
   }

   return false;
}

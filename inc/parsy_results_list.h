/**
 * @file parsy_results_list.h
 * @brief PARSY_RESULT X-macro declarations
 * @author Abdulla Almosalami (memphis242)
 * @date Oct 2025
 * @copyright MIT License
 */

//            Result Enum                                      Error String
PARSY_RESULT( GoodResult,                                      "Good result ☺" )
PARSY_RESULT( InvalidString,                                   "Malformed string passed in. Either nullptr or no null termination detected within PARSY_MAX_PARSABLE_STRING_LEN character limit." )
PARSY_RESULT( NullPtr,                                         "Null pointer was passed in for return-value parameter." )
PARSY_RESULT( InvalidDefaultFormat,                            "Default format argument out-of-range." )
PARSY_RESULT( HexAndDecFlagsSimultaneouslyUsed,                "Can't use both hex and dec format flags simultaneously." )
PARSY_RESULT( ID_OOR,                                          "ID is out of range. Enter a number between 0 and 63d (0x3F)." )
PARSY_RESULT( WhiteSpaceOnlyIDArg,                             "Only encountered whitespace in input." )
PARSY_RESULT( InvalidCharacterEncountered_FirstChar,           "Invalid character encountered (first character)." )
PARSY_RESULT( InvalidCharacterEncountered_SecondChar,          "Invalid character encountered (first character)." )
PARSY_RESULT( InvalidDigitEncountered_FirstDigit,              "Invalid digit encountered (first digit)." )
PARSY_RESULT( InvalidDigitEncountered_SecondDigit,             "Invalid digit encountered (second digit)." )
PARSY_RESULT( TooManyDigitsEntered,                            "Too many digits entered." )
PARSY_RESULT( HexDigitEncounteredUnderDecSetting_FirstDigit,   "Hexadecimal digit encountered under decimal settings (first digit)." )
PARSY_RESULT( HexDigitEncounteredUnderDecSetting_SecondDigit,  "Hexadecimal digit encountered under decimal settings (second digit)." )
PARSY_RESULT( InvalidDecimalSuffixEncountered,                 "Invalid decimal suffix encountered. Possibly too many digits." )
PARSY_RESULT( DuplicateFormatFlagsUsed,                        "Duplicate format flag detected. Please only specify (-d | --dec) or (-h | --hex) once." )
PARSY_RESULT( InvalidFlagDetected,                             "Invalid flag detected. Please use only from the following: -d, --dec, -h, --hex, --no-new-line, --quiet, -q, -t, --table, --help" )
PARSY_RESULT( InvalidPositionOfNumber,                         "Number was not placed properly. It needs to either be the first or second argument." )
PARSY_RESULT( CantUseNoNewLineWithoutQuiet,                    "Can't use --no-new-line without (--quiet | -q)" )
PARSY_RESULT( PrematureTerminatingCharEncounted,               "Premature terminating character encountered when a digit was expected." )
PARSY_RESULT( NoNumericalDigitsEnteredWithFormat,              "No numerical digits entered wit." )
PARSY_RESULT( HexPrefixAndSuffixEncountered,                   "Hexadecimal prefix and suffix encountered. That is not allowed." )

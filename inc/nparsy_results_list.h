/**
 * @file nparsy_results_list.h
 * @brief NPARSY_RESULT X-macro declarations
 * @author Abdulla Almosalami (memphis242)
 * @date Oct 2025
 * @copyright MIT License
 */

//            Result Enum                                      Error String
NPARSY_RESULT( GoodResult,                                      "Good result ☺" )
NPARSY_RESULT( InvalidString,                                   "Malformed string passed in. Either nullptr or no null termination detected within NPARSY_MAX_PARSABLE_STRING_LEN character limit." )
NPARSY_RESULT( NullPtr,                                         "Null pointer was passed in for return-value parameter." )
NPARSY_RESULT( InvalidDefaultFormat,                            "Default format argument out-of-range." )
NPARSY_RESULT( HexAndDecFlagsSimultaneouslyUsed,                "Can't use both hex and dec format flags simultaneously." )
NPARSY_RESULT( ID_OOR,                                          "ID is out of range. Enter a number between 0 and 63d (0x3F)." )
NPARSY_RESULT( WhiteSpaceOnlyIDArg,                             "Only encountered whitespace in input." )
NPARSY_RESULT( InvalidCharacterEncountered_FirstChar,           "Invalid character encountered (first character)." )
NPARSY_RESULT( InvalidCharacterEncountered_SecondChar,          "Invalid character encountered (first character)." )
NPARSY_RESULT( InvalidDigitEncountered_FirstDigit,              "Invalid digit encountered (first digit)." )
NPARSY_RESULT( InvalidDigitEncountered_SecondDigit,             "Invalid digit encountered (second digit)." )
NPARSY_RESULT( TooManyDigitsEntered,                            "Too many digits entered." )
NPARSY_RESULT( HexDigitEncounteredUnderDecSetting_FirstDigit,   "Hexadecimal digit encountered under decimal settings (first digit)." )
NPARSY_RESULT( HexDigitEncounteredUnderDecSetting_SecondDigit,  "Hexadecimal digit encountered under decimal settings (second digit)." )
NPARSY_RESULT( InvalidDecimalSuffixEncountered,                 "Invalid decimal suffix encountered. Possibly too many digits." )
NPARSY_RESULT( DuplicateFormatFlagsUsed,                        "Duplicate format flag detected. Please only specify (-d | --dec) or (-h | --hex) once." )
NPARSY_RESULT( InvalidFlagDetected,                             "Invalid flag detected. Please use only from the following: -d, --dec, -h, --hex, --no-new-line, --quiet, -q, -t, --table, --help" )
NPARSY_RESULT( InvalidPositionOfNumber,                         "Number was not placed properly. It needs to either be the first or second argument." )
NPARSY_RESULT( CantUseNoNewLineWithoutQuiet,                    "Can't use --no-new-line without (--quiet | -q)" )
NPARSY_RESULT( PrematureTerminatingCharEncounted,               "Premature terminating character encountered when a digit was expected." )
NPARSY_RESULT( NoNumericalDigitsEnteredWithFormat,              "No numerical digits entered wit." )
NPARSY_RESULT( HexPrefixAndSuffixEncountered,                   "Hexadecimal prefix and suffix encountered. That is not allowed." )

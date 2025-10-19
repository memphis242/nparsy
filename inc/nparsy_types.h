/**
 * @file nparsy_results.h
 * @brief NParsy library result types (e.g., enum).
 * @author Abdulla Almosalami (memphis242)
 * @date Oct 2025
 * @copyright MIT License
 */

#ifndef NPARSY_RESULTS_TYPE_H_
#define NPARSY_RESULTS_TYPE_H_

/* Definitions */
constexpr size_t NPARSY_MAX_ERR_MSG_LEN = 250u;

enum NParsyNumFormat
{
   NParsy_Dec,
   NParsy_Hex,
   NParsy_Bin,
   NParsy_NumOfFmts
};

#define NPARSY_RESULT(enum, msg) NParsy_##enum,
// All possible result types from the nparsy API
enum NParsyResult
{
   #include "nparsy_results_list.h"
   NPARSY_NUM_OF_RESULTS
};
#undef NPARSY_RESULT

/*** Extern Declarations ***/
#ifdef NPARSY_INCLUDE_RESULT_STRINGS_TABLE
// Optional list of strings that correspond to each NParsyResult enum value for
// the sake of printing out. You'd index into this array using the result enum value.
// For example:
// -----------
//    char demo_str[] = "Hi, there are no numbers here.";
//    int demo_num;
//    enum NParsyResult result = NParsyInt( demo_str, &demo_num );
//    if ( result != GoodResult ) {
//       assert( (result >= (enum NParsyResult)0) && (result < NPARSY_NUM_OF_RESULTS) );
//       fprintf(stderr, "%.*s", NPARSY_MAX_ERR_MSG_LEN, ResultStrings[err]);
//    }
extern const char * ResultStrings[];
#endif

#endif // NPARSY_RESULTS_TYPE_H_

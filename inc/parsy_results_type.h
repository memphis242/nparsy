/**
 * @file parsy_results.h
 * @brief Parsy library result types (e.g., enum).
 * @author Abdulla Almosalami (memphis242)
 * @date Oct 2025
 * @copyright MIT License
 */

#ifndef PARSY_RESULTS_TYPE_H_
#define PARSY_RESULTS_TYPE_H_

/* Definitions */
constexpr size_t PARSY_MAX_ERR_MSG_LEN = 250u;

#define PARSY_RESULT(enum, msg) Parsy_##enum,
// All possible result types from the parsy API
enum ParsyResult
{
   #include "parsy_results_list.h"
   PARSY_NUM_OF_RESULTS
};
#undef PARSY_RESULT

/*** Extern Declarations ***/
#ifndef PARSY_EXCLUDE_RESULT_STRINGS_TABLE
// Optional list of strings that correspond to each ParsyResult enum value for
// the sake of printing out. You'd index into this array using the result enum value.
// For example:
// -----------
//    char demo_str[] = "Hi, there are no numbers here.";
//    int demo_num;
//    enum ParsyResult result = ParsyInt( demo_str, &demo_num );
//    if ( result != GoodResult ) {
//       assert( (result >= (enum ParsyResult)0) && (result < PARSY_NUM_OF_RESULTS) );
//       fprintf(stderr, "%.*s", PARSY_MAX_ERR_MSG_LEN, ResultStrings[err]);
//    }
extern const char * ResultStrings[];
#endif

#endif // PARSY_RESULTS_TYPE_H_

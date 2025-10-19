/**
 * @file nparsy_results_str_table.c
 * @brief Optional string results table for convenient error message printing.
 * @author Abdulla Almosalami (memphis242)
 * @date Oct 2025
 * @copyright MIT License
 */

#ifndef NPARSY_EXCLUDE_RESULTS_STR_TABLE

#define NPARSY_RESULT(enum, msg) "\n\033[31;1mError: " msg "\033[0m\n\n",
const char * ResultStrings[] =
{
#   include "parsy_results_list.h"
};

#endif // NPARSY_EXCLUDE_RESULTS_STR_TABLE

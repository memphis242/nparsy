/**
 * @file parsy_constants.h
 * @brief Constants for parsy API usage
 * @author Abdulla Almosalami (memphis242)
 * @date Oct 2025
 * @copyright MIT License
 */

#ifndef PARSY_CONSTANTS_H_
#define PARSY_CONSTANTS_H_

/* File Inclusions */
#include <stdlib.h>
#include <stdint.h>

// Why a limit? This helps the library lessen the damage when character arrays
// are passed in without null termination. Now, the API always treats the array
// passed in as read-only (const), but nonetheless, a limit can't hurt.
constexpr size_t PARSY_MAX_PARSABLE_STRING_LEN = 1'000'000u;

#endif // PARSY_CONSTANTS_H_

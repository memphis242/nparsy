/**
 * @file parsy_uint.h
 * @brief API for parsing an unsigned integer out of a string.
 * @author Abdulla Almosalami (memphis242)
 * @date Oct 2025
 * @copyright MIT License
 */

/* File Inclusions */
#include <stdint.h>

#include "parsy_types.h"
#include "parsy_constants.h"

/**
 * @brief Parse out the first unsigned integer occurrence.
 * @note Integers may be decimal, hex, or binary - see README.md.
 * @note Can be repeatedly called by making use of the accumulated_strlen param
 * @note Up to 64-bit unsigned integers are parsable. Larger integers are skipped.
 * @param[in] str : string to parse through
 * @param[out] parsed_val : where the parse result is placed, if one is found; otherwise, nothing is done.
 * @param[out] accumulated_strlen : [Optional] How many chars were passed-through before result was obtained
 *                                             If nullptr, nothing happens.
 * @param[in] default_fmt : Assume bare numbers like 10 (which could be dec, hex, or bin) are of this format.
 * @return enum ParsyResult : parsy library result type
 */
[[nodiscard]]
enum ParsyResult ParsyUInt(
      const char * str,
      uint64_t * parsed_val,
      size_t * accumulated_strlen,
      enum ParsyNumFormat default_fmt );

/**
 * @brief Parse out any unsigned integers found until a limit is hit (see below).
 * @note Limits include the len of the buf passed in, the null terminator,
 *       and PARSY_MAX_PARSABLE_STRING_LEN characters reached.
 * @note Integers may be decimal, hex, or binary, with various prefix/suffix
 *       possiblities. See README.md.
 * @param[in] str : string to parse through
 * @param[out] buf : where the parse results are placed, if found; otherwise, nothing is done.
 * @param[in] len : length of buf
 * @return enum ParsyResult - library result type
 */
[[nodiscard]]
enum ParsyResult ParsyUIntList(const char * str, uint64_t * buf, size_t len);

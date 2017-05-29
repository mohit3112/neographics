/*\
|*|
|*|   Neographics: a tiny graphics library.
|*|   Copyright (C) 2016 Johannes Neubrand <johannes_n@icloud.com>
|*|
|*|   This program is free software; you can redistribute it and/or
|*|   modify it under the terms of the GNU General Public License
|*|   as published by the Free Software Foundation; either version 2
|*|   of the License, or (at your option) any later version.
|*|
|*|   This program is distributed in the hope that it will be useful,
|*|   but WITHOUT ANY WARRANTY; without even the implied warranty of
|*|   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
|*|   GNU General Public License for more details.
|*|
|*|   You should have received a copy of the GNU General Public License
|*|   along with this program; if not, write to the Free Software
|*|   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
|*|
\*/

#pragma once
#include "colors.h"

/*-----------------------------------------------------------------------------.
|                                                                              |
|                                   Color                                      |
|                                                                              |
`-----------------------------------------------------------------------------*/

/*! \addtogroup Types
 *  @{
 *  \addtogroup Color
 *  Color-handling code.
 *  @{
 */

/*!
 * Internal representation of colors: now with revolutionary 2-bit-per-channel
 * technology!
 */
typedef union n_GColor8 {
    struct {
        // little endian, so reverse field order (within byte)
        uint8_t b:2;
        uint8_t g:2;
        uint8_t r:2;
        uint8_t a:2;
    };
    uint8_t argb;
} n_GColor8;

typedef n_GColor8 n_GColor;

/*!
 * Check for the equality of two n_GColor(s).
 */
bool n_gcolor_equal(n_GColor8 a, n_GColor8 b) __attribute__((always_inline)) {
   return a.argb == b.argb;
}

/*!
 * Get the ideal text n_GColor over a given background.
 */
n_GColor8 n_gcolor_legible_over(n_GColor8 color) __attribute__((always_inline)) {
   return (color.r + color.g + color.b > 6) ? n_GColorWhite : n_GColorBlack;
}

/*!
 * Convenience macro to create the closest n_GColor to 4 8-bit values.
 */
#define n_GColorFromRGBA(_r, _g, _b, _a) \
    ((n_GColor8) {{.a = ((_a) >> 6) & 0b11, .r = ((_r) >> 6) & 0b11,\
                   .g = ((_g) >> 6) & 0b11, .b = ((_b) >> 6) & 0b11}})

/*!
 * Convenience macro to create the closest n_GColor to 3 8-bit values.
 */
#define n_GColorFromRGB(_r, _g, _b) \
    ((n_GColor8) {{.a =               0b11, .r = ((_r) >> 6) & 0b11,\
                   .g = ((_g) >> 6) & 0b11, .b = ((_b) >> 6) & 0b11}})

/*!
 * Convenience macro to create the closest n_GColor to a hex value (eg 0xFF7700).
 */
#define n_GColorFromHEX(_h) n_GColorFromRGB(((_h) >> 16) & 0b11111111, \
                                            ((_h) >>  8) & 0b11111111, \
                                             (_h)        & 0b11111111)

/*! @}
 *  @}
 */

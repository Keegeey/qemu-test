/**
 * @file debug.h
 */

#ifndef DEBUG_H
#define DEBUG_H

#include <stdbool.h>
#include <stdint.h>

typedef uint32_t debug_mask_t;

typedef enum {
    DEBUG_MASK_INFO    = 0x00000001,
    DEBUG_MASK_WARNING = 0x00000002,
    DEBUG_MASK_ERROR   = 0x00000004,
    DEBUG_MASK_ALL     = 0xFFFFFFFF,
} debug_masks_t;

void debug(const char *msg);
void debug_masked(debug_mask_t mask, const char *msg);
void debug_set_mask(debug_mask_t mask);
debug_mask_t debug_get_mask(void);
bool debug_is_enabled(debug_mask_t mask);

#endif // DEBUG_H

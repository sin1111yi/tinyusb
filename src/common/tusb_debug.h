/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2022, Ha Thach (tinyusb.org)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * This file is part of the TinyUSB stack.
 */

#ifndef TUSB_DEBUG_H_
#define TUSB_DEBUG_H_

#ifdef __cplusplus
 extern "C" {
#endif

// CFG_TUSB_DEBUG levels:
// 0 = no debug, 1 = error, 2 = warn, 3 = info

#ifndef CFG_TUSB_DEBUG_PRINTF
#define tu_printf(...) ((void)(0))
#else
#define tu_printf CFG_TUSB_DEBUG_PRINTF
#endif

// Single interface macro with level tag
#define TU_LOG_TAG(tag, ...)  tu_printf("[" tag "] " __VA_ARGS__)

// Compile-time level filtering
#if CFG_TUSB_DEBUG >= 1
#define TU_LOG_ERROR(...)   TU_LOG_TAG("ERR", __VA_ARGS__)
#else
#define TU_LOG_ERROR(...)   ((void)(0))
#endif

#if CFG_TUSB_DEBUG >= 2
#define TU_LOG_WARN(...)    TU_LOG_TAG("WRN", __VA_ARGS__)
#else
#define TU_LOG_WARN(...)    ((void)(0))
#endif

#if CFG_TUSB_DEBUG >= 3
#define TU_LOG_INFO(...)    TU_LOG_TAG("INF", __VA_ARGS__)
#else
#define TU_LOG_INFO(...)    ((void)(0))
#endif

// Unified runtime-level interface
#define TU_LOG(n, ...)                          \
    do {                                        \
        if ((n) <= CFG_TUSB_DEBUG) {            \
            tu_printf("[" #n "] " __VA_ARGS__); \
        }                                       \
    } while(0)

// Lookup table utilities
typedef struct {
  uint32_t key;
  const char* data;
} tu_lookup_entry_t;

typedef struct {
  uint16_t count;
  tu_lookup_entry_t const* items;
} tu_lookup_table_t;

static inline const char* tu_lookup_find(tu_lookup_table_t const* p_table, uint32_t key) {
  for(uint16_t i=0; i<p_table->count; i++) {
    if (p_table->items[i].key == key) {
      return p_table->items[i].data;
    }
  }
  return "NotFound";
}

#ifdef __cplusplus
 }
#endif

#endif /* TUSB_DEBUG_H_ */

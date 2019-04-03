#include "gfx.h"

PROGMEM uint8_t PADDLE[] = {
  PADDLE_WIDTH, PADDLE_HEIGHT,
//  0x7f, 0xff, 0x80,
//  0x80, 0xff, 0xff,
//  0x80, 0xff, 0xff,
//  0x7f, 0xff, 0x80
  0x7f, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0x7f
};

PROGMEM uint8_t BLOCK[] = {
  BLOCK_WIDTH, BLOCK_HEIGHT,
  0x7e,
  0xff,
  0xff,
  0x7e
};

PROGMEM uint8_t level[ROWS][COLUMNS] = {
//  { 0, 1, 1, 0, 0, 1, 1, 0 },
//  { 1, 1, 1, 0, 0, 1, 1, 0 },
//  { 1, 0, 0, 0, 1, 1, 1, 1 },
//  { 1, 1, 1, 0, 0, 1, 1, 0 },
//  { 0, 1, 1, 0, 0, 0, 1, 1 }
  
  { 0, 1, 1, 0, 0, 1, 1, 0 },
  { 0, 1, 1, 0, 0, 1, 1, 0 },
  { 0, 1, 1, 0, 0, 1, 1, 0 }
};


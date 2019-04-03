# include <avr/pgmspace.h>

# ifndef GFX_H
# define GFX_H
const uint8_t PADDLE_WIDTH = 32;
const uint8_t PADDLE_HEIGHT = 4;
const uint8_t BLOCK_WIDTH = 8;
const uint8_t BLOCK_HEIGHT = 4;
const uint8_t COLUMNS = 8;
const uint8_t ROWS = 5;

extern uint8_t PADDLE[];
extern uint8_t BLOCK[];
extern uint8_t level[ROWS][COLUMNS];
#endif


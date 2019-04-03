#include <Wire.h>
#include <TVout.h>
#include <fontALL.h>
#include "gfx.h"

const uint8_t WIDTH = 128;
const uint8_t HEIGHT = 96;
const uint8_t PLAYFIELD_WIDTH = 86;
const uint8_t MIN_X = (WIDTH - PLAYFIELD_WIDTH) / 2 + 1;
const uint8_t MIN_Y = 1;
const uint8_t MAX_X = MIN_X + PLAYFIELD_WIDTH;
const uint8_t MAX_Y = HEIGHT - 1;
const uint8_t MARGIN = 4;
const uint8_t PADDLE_Y = 91;
const uint8_t MAX_VELOCITY = 1;
const uint8_t BALL_RADIUS = 2;
const uint8_t BALL_DIAMETER = BALL_RADIUS * 2;
const uint8_t MAX_BALLS = 5;

int buttonPin1 = 12;
int buttonPin2= 10;
int buttonPin3 = 11;
boolean pressed = false;

enum GameState {
  INTRO, STARTING, RUNNING, PAUSED, DONE
};

TVout tv;
unsigned int paddle_speed = 3;
unsigned int balls = MAX_BALLS;
int paddle_x = (WIDTH - PADDLE_WIDTH) / 2;
int px, py, vx, vy;
boolean left, right, button;
GameState state = INTRO;
uint8_t blocks[ROWS][COLUMNS] = { { 0 } };

void init_ball() {
  px = WIDTH / 2;
  py = MAX_Y - PADDLE_HEIGHT - BALL_RADIUS - 1;
  vx = int(random(-MAX_VELOCITY, MAX_VELOCITY + 1));
  vy = -2;
}

void init_blocks() {
  for (unsigned int i = 0; i < ROWS; i++) {
    for (unsigned int j = 0; j < COLUMNS; j++) {
      blocks[i][j] = pgm_read_byte(&level[i][j]);
    }
  }
}

void init_game() {
  paddle_x = (WIDTH - PADDLE_WIDTH) / 2;
  balls = MAX_BALLS;
  left = right = button = false;
  state = INTRO;
  init_ball();
  init_blocks();
  tv.select_font(font6x8);
}

int draw_blocks() {
  unsigned int count = 0;
  unsigned int x = MIN_X + MARGIN;
  unsigned int y = MIN_Y + MARGIN;
  for (unsigned int i = 0; i < ROWS; i++) {
    for (unsigned int j = 0; j < COLUMNS; j++) {
      if (blocks[i][j] == 1) {
        tv.bitmap(x, y, BLOCK);
        count++;
      }
      x += BLOCK_WIDTH + 2;
    }
    x = MIN_X + MARGIN;
    y += BLOCK_HEIGHT + 2;
  }
  return count;
}

void check_controls() {
  left = right = button = false;
  
  if ( digitalRead( buttonPin1 )  ) {
      right = true;
  } 
  if ( digitalRead( buttonPin2 ) ) {
      left = true;
  } 
  if ( digitalRead( buttonPin3 )  ) {
    button = true;
  } 
//  if (nunchuk.update())
//  {
//    if (nunchuk.joystick_x() < 50)
//      left = true;
//    if (nunchuk.joystick_x() > 190)
//      right = true;
//    if (nunchuk.c_button())
//      button = true;
//  }
}

void move_paddle() {
  if (left)
    paddle_x -= paddle_speed;
  if (right)
    paddle_x += paddle_speed;
  
  if (paddle_x <= MIN_X)
    paddle_x = MIN_X;
  if (paddle_x >= MAX_X - PADDLE_WIDTH)
    paddle_x = MAX_X - PADDLE_WIDTH;
}

void draw_border() {
  tv.draw_line(MIN_X - 1, 0, MAX_X, 0, WHITE);
  tv.draw_line(MIN_X - 1, 0, MIN_X - 1, MAX_Y, WHITE);
  tv.draw_line(MAX_X, 0, MAX_X, MAX_Y, WHITE);
}

boolean ball_dropped() {
  return py + vy > MAX_Y - BALL_RADIUS;
}

boolean in_x_range(const int row, const int v) {
  return px + v > MIN_X + MARGIN + row * (BLOCK_WIDTH + 2) && 
         px + v < MIN_X + MARGIN + (row + 1) * (BLOCK_WIDTH + 2) + BALL_DIAMETER;
}

boolean in_y_range(const int col, const int v) {
  return py + v > MIN_Y + MARGIN + col * (BLOCK_HEIGHT + 2) &&
         py + v < MIN_Y + MARGIN + (col + 1) * (BLOCK_HEIGHT + 2) + BALL_DIAMETER;
}

void check_block_collision() {
  for (unsigned int y = 0; y < ROWS; y++) {
    for (unsigned int x = 0; x < COLUMNS; x++) {
      if (blocks[y][x] > 0) {
        if (in_x_range(x, vx) && in_y_range(y, vy)) {
          blocks[y][x] = 0;
          if (in_x_range(x, 0)) // Hit top or bottom of brick.
            vy = -vy;
          if (in_y_range(y, 0)) // Hit left or right side of brick.
            vx = -vx; 
        }
      }
    }
  }
}

void check_wall_collision() {
  if (px + vx < MIN_X + BALL_RADIUS || px + vx > MAX_X - BALL_RADIUS)
    vx = -vx;
  if (py + vy < BALL_RADIUS || py + vy > MAX_Y - BALL_RADIUS)
    vy = -vy;
}

void check_paddle_collision() {
  if (py + vy >= MAX_Y - PADDLE_HEIGHT &&
      px >= paddle_x && px <= paddle_x + PADDLE_WIDTH)
  {
    vy = -vy;
    vx = int(
           map(
             px - paddle_x,
             -(PADDLE_WIDTH / 2), PADDLE_WIDTH / 2,
             -MAX_VELOCITY + 1,
             MAX_VELOCITY + 1
           )
         );
  }  
}

void pause_game() {
  tv.select_font(font6x8);
  if (balls == 1) {
    tv.printPGM(31, 44, PSTR("Letzter Ball!"));
  } else {
    tv.print(28, 44, balls);
    tv.printPGM(36, 44, PSTR(" Baelle"));
  }
  if (button)
    state = RUNNING;
}

void update_game() {
  tv.clear_screen();
  draw_border();
  if (draw_blocks() == 0) {
      state = DONE;
      return;
  }  
  if (ball_dropped()) {
    balls--;
    if (balls == 0) {
      state = DONE;
    } else {
      init_ball();
      paddle_x = (WIDTH - PADDLE_WIDTH) / 2;
      state = PAUSED;
    }
  } else {
    check_block_collision();
    check_wall_collision();
    check_paddle_collision();
    px += vx;
    py += vy;
  }

  move_paddle();
  tv.draw_circle(px, py, BALL_RADIUS, WHITE, WHITE);
  tv.bitmap(paddle_x, PADDLE_Y, PADDLE);
}

void intro() {
  tv.select_font(font8x8);
  tv.printPGM(14, 20, PSTR("the jurekxp"));
  tv.select_font(font6x8);
  tv.printPGM(34, 40, PSTR("judonoid"));
  tv.select_font(font4x6);
  tv.printPGM(33, 74, PSTR("Drueck druff"));
  if (button) {
    state = STARTING;
  }
}

void game_over() {
  tv.clear_screen();
  if (balls == 0) {
    tv.select_font(font8x8);
    tv.printPGM(28, 44, PSTR("DAS WARS!!!"));
  } else {
    tv.printPGM(32, 44, PSTR("GEWONNEN!"));
  }
  if (button) {
    init_game();
    state = STARTING;
  }
}

void start_game() {
  tv.clear_screen();
  draw_border();
  draw_blocks();
  tv.draw_circle(px, py, BALL_RADIUS, WHITE, WHITE);
  tv.bitmap(paddle_x, PADDLE_Y, PADDLE);
  delay(1000);
  if (button) {
    init_game();
    state = RUNNING;
  }
}

void setup() {
  pinMode( buttonPin1, INPUT);
  pinMode( buttonPin2 ,INPUT);
  pinMode( buttonPin3 ,INPUT);
  randomSeed(analogRead(A0));
  tv.begin(_PAL, WIDTH, HEIGHT);

  init_game();
}

void loop() {
  check_controls();
  switch (state) {
    case INTRO:    intro();       break;
    case PAUSED:   pause_game();  break;
    case STARTING: start_game();  break;
    case RUNNING:  update_game(); break;
    case DONE:     game_over();   break;
  }
  tv.delay_frame(1);
}


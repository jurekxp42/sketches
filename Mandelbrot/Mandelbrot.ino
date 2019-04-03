#include <TVout.h>
#include <fontALL.h>

TVout TV;

void setup() {
  TV.begin(_PAL, 128, 96);
  TV.clear_screen();
  TV.select_font(font8x8);
  TV.print(4, 44, "Mandelbrot-Demo");
  delay(5000);
  TV.clear_screen();
  
  const unsigned int width = TV.hres();
  const unsigned int height = TV.vres();
  const float min_re = -2.5;
  const float max_re = 1.0;
  const float min_im = -1.2;
  const float max_im = 1.2;
  
  for (unsigned int y = 0; y < height; y++) {
    float im = min_im + y * (max_im - min_im) / height;
    for (unsigned int x = 0; x < width; x++) {
      float re = min_re + x * (max_re - min_re) / width;
      float tr = re;
      float ti = im;

      unsigned int depth = 0;
      while (depth++ < 20) {
        float temp = tr * tr - ti * ti + re;
        ti = 2 * tr * ti + im;
        tr = temp;
        if (tr * tr + ti * ti > 4)
          break;
      }
      if (depth < 16)
        TV.set_pixel(x, y, WHITE);
    }
  }
}

void loop() {}


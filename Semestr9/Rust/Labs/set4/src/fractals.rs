use crate::complex::{Complex};
use crate::image::{Pixel, Image};

fn is_outside(c: &Complex) -> bool {
    c.norm_sqr() > 4.0
}

fn fractal(c: Complex, max_iter: u32) -> u32 {
    let mut z = Complex::new(0.0, 0.0);
    for i in 0..max_iter {
        if is_outside(&z) {
            return i;
        }
        z = z*z + c;
    }
    return max_iter;
}

fn color(iter: u32, max_iter: u32) -> Pixel {
    if iter == max_iter {
        return Pixel::new(0, 0, 0);          // inside the set
    }
    let t = iter as f64 / max_iter as f64;  // 0.0 ..= 1.0
    Pixel::new(
        (9.0 * (1.0 - t) * t * t * t * 255.0) as u8,
        (15.0 * (1.0 - t).powi(2) * t * t * 255.0) as u8,
        (8.5 * (1.0 - t).powi(3) * t * 255.0) as u8,
    )
}

pub fn mandelbrot(
    width   : usize, 
    height  : usize,
    re_min  : f64, 
    re_max  : f64, 
    im_min  : f64, 
    im_max  : f64,
    max_iter: u32
) -> Image {
    let mut img = Image::new(width, height);
    for y in 0..height {
        for x in 0..width {
            let re = re_min + (x as f64 / width as f64) * (re_max - re_min);
            let im = im_max - (y as f64 / height as f64) * (im_max - im_min);
            let n = fractal(Complex::new(re, im) , max_iter);
            img.set_pixel(x, y, color(n, max_iter));
        }
    }
    img
}

use crate::fractals::mandelbrot;

mod image;
mod complex;
mod fractals;
fn main() {
    mandelbrot(1200, 800, -2.5, 1.0, -1.0, 1.0, 200)
        .save_ppm("mandelbrot.ppm").unwrap();
    
    let examples = [
        ("seahorse_valley.ppm",      1000, 800,  -0.745,       0.11,        0.03,    500),
        ("elephant_valley.ppm",      1000, 800,   0.282,       0.01,        0.02,    500),
        ("triple_spiral_valley.ppm",  800, 800,  -0.088,       0.654,       0.02,    600),
        ("mini_mandelbrot.ppm",       800, 600,  -1.7685,      0.0,         0.04,    500),
        ("scepter_valley.ppm",        800, 600,  -1.36,        0.005,       0.05,    500),
        ("deep_spiral.ppm",          1000, 1000, -0.743643887, 0.131825904, 0.00012, 2000),
        ("full_hd.ppm",              1920, 1080, -0.75,        0.0,         4.0,     300),
    ];
    for (file, w, h, re, im, span, max_iter) in examples {
        let half_re = span / 2.0;
        let half_im = half_re * h as f64 / w as f64;
        let img = mandelbrot(w, h, re - half_re, re + half_re, im - half_im, im + half_im, max_iter);
        img.save_ppm(file).unwrap();
    }
}

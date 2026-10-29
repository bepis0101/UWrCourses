use std::{fs::File, io::Write};

#[derive(Debug, Clone, Copy, PartialEq)]
pub struct Pixel {
    r: u8,
    g: u8,
    b: u8,
}

pub struct Image {
    width: usize,
    height: usize,
    data: Vec<Pixel>
}

impl Pixel {
    pub fn new(r: u8, g: u8, b: u8) -> Pixel {
        Pixel { r,g,b }
    }
}

impl Image {
    pub fn new(width: usize, height: usize) -> Image {
        Image {
            height: height,
            width: width,
            data: vec![Pixel::new(0, 0, 0); width * height],
        }
    }

    pub fn set_pixel(&mut self, x: usize, y: usize, pixel: Pixel) {
        assert!(x < self.width);
        assert!(y < self.height);
        self.data[y * self.width + x] = pixel;
    }

    fn convert_to_bytes(&self) -> Vec<u8> {
        self.data
            .iter()
            .flat_map(|p| [p.r, p.g, p.b])
            .collect()
    }

    pub fn save_ppm(&self, filename: &str) -> std::io::Result<()> {
        let mut f = File::create(filename)?;
        write!(f, "P6\n{} {}\n255\n", self.width, self.height)?;
        f.write_all(&self.convert_to_bytes())?;
        Ok(())
    }
}
#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn generate_gradient_file() {
        // Red grows left to right, green grows top to bottom, blue is constant.
        let (w, h) = (256, 256);
        let mut img = Image::new(w, h);
        for y in 0..h {
            for x in 0..w {
                img.set_pixel(x, y, Pixel::new(x as u8, y as u8, 128));
            }
        }

        let dir = std::path::Path::new(env!("CARGO_MANIFEST_DIR")).join("output");
        std::fs::create_dir_all(&dir).unwrap();
        let path = dir.join("gradient.ppm");
        img.save_ppm(path.to_str().unwrap()).unwrap();

        let size = std::fs::metadata(&path).unwrap().len() as usize;
        assert_eq!(size, "P6\n256 256\n255\n".len() + w * h * 3);
    }
}
use std::ops;
#[derive(Clone, Copy, PartialEq)]
pub struct Complex {
    real: f64,
    imaginary: f64,
}

impl ops::Add<Complex> for Complex {
    type Output = Complex;
    fn add(self, rhs: Complex) -> Self::Output {
        Complex {
            real: rhs.real + self.real,
            imaginary: rhs.imaginary + self.imaginary,
        }
    }
}

impl ops::Mul<Complex> for Complex {
    type Output = Complex;
    fn mul(self, rhs: Complex) -> Self::Output {
        Complex {
            real: self.real*rhs.real - self.imaginary*rhs.imaginary,
            imaginary: self.imaginary*rhs.real + self.real*rhs.imaginary,
        }
    }
}

impl Complex {
    pub fn new(r: f64, i: f64) -> Complex {
        Complex { real: r, imaginary: i }
    }
    pub fn norm_sqr(&self) -> f64 {
        self.imaginary*self.imaginary + self.real*self.real
    }
}

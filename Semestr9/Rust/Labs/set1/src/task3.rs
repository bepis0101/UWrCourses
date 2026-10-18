pub mod task3 {
    use std::f64::consts::PI;
    
    fn circle_area(area_full: f64) -> f64 {
        area_full * PI / 4.0
    }

    fn is_close(f1: f64, f2: f64) -> bool {
        (f1-f2).abs() <= f64::EPSILON
    }

    #[test]
    fn test1_task3() {
        assert!(is_close(circle_area(1.0), PI / 4.0))
    }
    #[test]
    fn test2_task3() {
        assert!(is_close(circle_area(7.0), 7.0*PI / 4.0))
    }
    #[test]
    fn test3_task3() {
        assert!(is_close(circle_area(10.0), 5.0*PI / 2.0))
    }
    #[test]
    fn test4_task3() {
        assert!(is_close(circle_area(12.0), 3.0*PI))
    }
    #[test]
    fn test5_task3() {
        assert!(is_close(circle_area(100.0), 25.0*PI))
    }
}

// area_full = (2r)^2 = 4r^2
// area_circle = area_full / 4 * pi
mod task4 {
    fn sum_two_smallest_numbers(numbers: &[u32]) -> u32 {
        let mut sorted = numbers.to_vec();
        sorted.sort_unstable();
        sorted[0] + sorted[1]
    }

    #[test]
    fn test1() {
        assert_eq!(sum_two_smallest_numbers(&[5, 8, 12, 19, 22]),  13, "Incorrect result for [5, 8, 12, 19, 22]");
    }
    #[test]
    fn test2() {
        assert_eq!(sum_two_smallest_numbers(&[15, 28, 4, 2, 43]), 6, "Incorrect result for [15, 28, 4, 2, 43]");
    }
    #[test]
    fn test3() {
        assert_eq!(sum_two_smallest_numbers(&[1, 1, 5, 5]),  2, "Incorrect result for [1, 1, 5, 5]");
    }
    #[test]
    fn test4() {
        assert_eq!(sum_two_smallest_numbers(&[52, 76, 14, 12, 4]), 16, "Incorrect result for [52, 76, 14, 12, 4]");
    }
    #[test]
    fn test5() {
        assert_eq!(sum_two_smallest_numbers(&[23, 71, 33, 82, 1]), 24, "Incorrect result for [23, 71, 33, 82, 1]");
    }

}
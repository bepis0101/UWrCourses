mod task3 {

    fn solution(num: i32) -> i32 {
        if num <= 0 { 0 }
        else {
            (1..num)
              .filter(|&x| x % 5 == 0 || x % 3 == 0)
              .sum()
        }
    }
    
    fn assertion(expected : i32, input : i32) {
        let actual = solution(input);
        
        assert!(
            expected == actual,
            "\nTest failed!\n expected: {}\n actual: {}\n input: {}\n", expected, actual, input
        );
    }

    #[test]
    fn test1() {
      assertion(  23,   10);
    }
    #[test]
    fn test2() {
      assertion(25719750, 10500);
    }
    #[test]
    fn test3() {
      assertion(   0, -203);
    }
    #[test]
    fn test4() {
      assertion(3420,  123);
    }
    #[test]
    fn test5() {
      assertion( 543,   50);
    }
}
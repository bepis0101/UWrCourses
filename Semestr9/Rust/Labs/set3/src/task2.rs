mod task2 {
    fn summy(strng: &str) -> i32 {
        strng.split(' ')
             .map(|x| x.parse::<i32>().unwrap())
             .fold(0, |acc, x| acc+x)
    }
    
    #[test]
    fn test1() {
        assert_eq!(summy("1 2 3"), 6);
    }
    #[test]
    fn test2() {
        assert_eq!(summy("0 0"), 0);
    }
    #[test]
    fn test3() {
        assert_eq!(summy("10 10"), 20);
    }
    #[test]
    fn test4() {
        assert_eq!(summy("1 2 3 4 5"), 15);
    }
    #[test]
    fn test5() {
        assert_eq!(summy("1 2 3 4"), 10);
    }
}
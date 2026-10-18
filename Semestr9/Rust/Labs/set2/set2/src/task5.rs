mod task5 {
    fn count_bits(n: i64) -> u32 {
        n.count_ones()
    }

    #[test]
    fn test1() {
        assert_eq!(count_bits(4), 1);
    }
    #[test]
    fn test2() {
        assert_eq!(count_bits(0), 0);
    }
    #[test]
    fn test3() {
        assert_eq!(count_bits(7), 3);
    }
    #[test]
    fn test4() {
        assert_eq!(count_bits(77231418), 14);
    }
    #[test]
    fn test5() {
        assert_eq!(count_bits(12525589), 11);
    }

}

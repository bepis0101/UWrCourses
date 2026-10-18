mod task1 {
    fn get_count(string: &str) -> usize {
        let sum = 
            string
                .chars()
                .filter(|c| ['a', 'e', 'i', 'o', 'u'].contains(c))
                .count();
        sum
    }

    #[test]
    fn test1() {
        assert_eq!(get_count("abracadabra"), 5);
    }
    #[test]
    fn test2() {
        assert_eq!(get_count("abracad"), 3);
    }
    #[test]
    fn test3() {
        assert_eq!(get_count("alabamauuu"), 7);
    }
    #[test]
    fn test4() {
        assert_eq!(get_count("employee"), 4);
    }
    #[test]
    fn test5() {
        assert_eq!(get_count("value"), 3);
    }
}
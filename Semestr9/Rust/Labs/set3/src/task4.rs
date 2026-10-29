mod task4 {
    use std::collections::HashSet;
    
    fn longest(a1: &str, a2: &str) -> String {
        let set: HashSet<char> = a1.chars()
                                   .chain(a2.chars())
                                   .collect();
        let mut chars: Vec<char> = set.into_iter().collect();
        chars.sort_unstable();
        chars.into_iter().collect()
    }
    fn testing(s1: &str, s2: &str, exp: &str) -> () {
        println!("s1:{:?} s2:{:?}", s1, s2);
        println!("{:?} {:?}", longest(s1, s2), exp);
        println!("{}", longest(s1, s2) == exp);
        assert_eq!(&longest(s1, s2), exp)
    }

    #[test]
    fn test1() {
        testing("loopingisfunbutdangerous", "lessdangerousthancoding", "abcdefghilnoprstu");
    }
    #[test]
    fn test2() {
        testing("aretheyhere", "yestheyarehere", "aehrsty");
    }
    #[test]
    fn test3() {
        testing("xyaabbbccccdefww", "xxxxyyyyabklmopq", "abcdefklmopqwxy");
    }
    #[test]
    fn test4() {
        testing("abcdefghijklmnopqrstuvwxyz", "abcdefghijklmnopqrstuvwxyz", "abcdefghijklmnopqrstuvwxyz");
    }
    #[test]
    fn test5() {
        testing("", "", "");
    }
}
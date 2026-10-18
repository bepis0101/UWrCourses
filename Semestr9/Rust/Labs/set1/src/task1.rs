pub mod task1 {
    fn string_to_int(s: String) -> i32 {
        s.parse().unwrap()
    }

    #[test]
    fn test1_task1() {
        assert_eq!(5, string_to_int(String::from("5")))
    }
    #[test]
    fn test2_task1() {
        assert_eq!(1234, string_to_int(String::from("1234")))
    }

    #[test]
    fn test3_task1() {
        assert_eq!(605, string_to_int(String::from("605")))
    }

    #[test]
    fn test4_task1() {
        assert_eq!(1405, string_to_int(String::from("1405")))
    }
    #[test]

    fn test5_task1() {
        assert_eq!(-7, string_to_int(String::from("-7")))
    }
}
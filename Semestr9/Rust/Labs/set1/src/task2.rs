pub mod task2 {
    fn cnt_red_beads(n: u32) -> u32 {
        if n < 2 {
            0
        } else {
            (n-1) * 2
        }
    }
    #[test]
    fn test1_task2() {
        assert_eq!(0, cnt_red_beads(1))
    }
    #[test]
    fn test2_task2() {
        assert_eq!(10, cnt_red_beads(6))
    }
    #[test]
    fn test3_task2() {
        assert_eq!(2, cnt_red_beads(2))
    }
    #[test]
    fn test4_task2() {
        assert_eq!(12, cnt_red_beads(7))
    }
    #[test]
    fn test5_task2() {
        assert_eq!(5998, cnt_red_beads(3000))
    }
} 

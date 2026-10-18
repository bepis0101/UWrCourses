mod task2 {
    fn number(bus_stops:&[(i32,i32)]) -> i32 {
        bus_stops
            .iter()
            .fold(0, |acc, x| acc + x.0 - x.1)
    }

    #[test]
    fn test1() {
        assert_eq!(number(&[(3,0),(9,1),(4,10),(12,2),(6,1),(7,10)]), 17);
    }
    #[test]
    fn test2() {
        assert_eq!(number(&[(10,0),(3,5),(5,8)]), 5);
    }
    #[test]
    fn test3() {
        assert_eq!(number(&[(3,0),(9,1),(4,8),(12,2),(6,1),(7,8)]), 21);
    }
    #[test]
    fn test4() {
        assert_eq!(number(&[(1,0),(1,1),(4,4),(2,2),(1,1),(7,8)]), 0);
    }
    #[test]
    fn test5() {
        assert_eq!(number(&[(1, 0), (3, 2), (7, 2)]), 7);
    }
}
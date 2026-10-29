mod task1 {
    fn open_or_senior(data: Vec<(i32, i32)>) -> Vec<String> {
        data.into_iter()
            .map(|(age, handicap)| {
                if age >= 55 && handicap > 7 {
                    "Senior".to_string()
                } else {
                    "Open".to_string()
                }
            })
            .collect()
    }
    #[test]
    fn test1() {
        assert_eq!(open_or_senior(vec![(45, 12), (55,21), (19, -2), (104, 20)]), vec!["Open", "Senior", "Open", "Senior"]);
    }
    #[test]
    fn test2() {
        assert_eq!(open_or_senior(vec![(3, 12), (55,1), (91, -2), (54, 23)]), vec!["Open", "Open", "Open", "Open"]);
    }
    #[test]
    fn test3() {
        assert_eq!(open_or_senior(vec![(0, 11), (55, 23)]), vec!["Open", "Senior"]);
    }
    #[test]
    fn test4() {
        assert_eq!(open_or_senior(vec![(77, 55), (61, 24)]), vec!["Senior", "Senior"]);
    }
    #[test]
    fn test5() {
        assert_eq!(open_or_senior(vec![(3, 12), (55,1), (66, 8)]), vec!["Open", "Open", "Senior"]);        
    }
}
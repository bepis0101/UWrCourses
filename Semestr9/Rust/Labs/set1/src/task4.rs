pub mod task4 {
    pub fn complement_dna(dna: String) -> String {
        dna
            .chars()
            .map(|c| match c {
                'A' => 'T',
                'T' => 'A',
                'C' => 'G',
                'G' => 'C',
                _ => c,
            })
            .collect::<String>()
    }

    #[test]
    fn test1_task4() {
        assert_eq!(complement_dna(String::from("ATTGC")), String::from("TAACG"))
    }
    #[test]
    fn test2_task4() {
        assert_eq!(complement_dna(String::from("TAACG")), String::from("ATTGC"))
    }
    #[test]
    fn test3_task4() {
        assert_eq!(complement_dna(String::from("GTAT")), String::from("CATA"))
    }
    #[test]
    fn test4_task4() {
        assert_eq!(complement_dna(String::from("CATA")), String::from("GTAT"))
    }
    #[test]
    fn test5_task4() {
        assert_eq!(complement_dna(String::from("ATTT")), String::from("TAAA"))
    }
}
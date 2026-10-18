mod task3 {
    fn printer_error(s: &str) -> String {
        let errors = 
            s
                .chars()
                .filter(|&c| c > 'm')
                .count();
        format!("{}/{}", errors, s.len())
    }

    #[test]
    fn test1() {
        assert_eq!(&printer_error("aaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbmmmmmmmmmmmmmmmmmmmxyz"), "3/56");
    }
    #[test]
    fn test2() {
        assert_eq!(&printer_error("kkkwwwaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbmmmmmmmmmmmmmmmmmmmxyz"), "6/60");
    }
    #[test]
    fn test3() {
        assert_eq!(&printer_error("kkkwwwaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbmmmmmmmmmmmmmmmmmmmxyzuuuuu"), "11/65");
    }
    #[test]
    fn test4() {
        assert_eq!(&printer_error("mamammammfdmmmmdmammdm"), "0/22")
    }
    #[test]
    fn test5() {
        assert_eq!(&printer_error("mamammammfdmmmmdmammdmopqoo"), "5/27")
    }
}
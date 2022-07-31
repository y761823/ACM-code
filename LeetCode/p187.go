func findRepeatedDnaSequences(s string) []string {
    mp := map[string]int{}
    for i := 0; i + 10 <= len(s); i++ {
        mp[s[i:i + 10]]++
    }
    res := []string{}
    for k, v := range mp {
        if v > 1 {
            res = append(res, k)
        }
    }
    return res
}

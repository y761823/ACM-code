func max(a, b int) int {
    if a > b {
        return a
    }
    return b
}

func rob(nums []int) int {
    last1, last2 := 0, 0
    for _, v := range nums {
        t := max(last2 + v, last1)
        last1, last2 = t, last1
    }
    return max(last1, last2)
}

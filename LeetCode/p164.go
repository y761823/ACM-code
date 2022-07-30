func maximumGap(nums []int) int {
    sz := len(nums)
    if sz < 2 {
        return 0
    }
    maximum, minimum := nums[0], nums[0]
    for _, v := range nums {
        if v > maximum {
            maximum = v
        }
        if v < minimum {
            minimum = v
        }
    }
    
    minb, maxb := make([]int, sz + 1), make([]int, sz + 1)
    for i := 0; i < len(minb); i++ {
        minb[i], maxb[i] = -1, -1
    }
    bsize := (maximum - minimum + 1 + sz) / (sz + 1)
    for _, v := range nums {
        pos := (v - minimum) / bsize
        if minb[pos] == -1 || v < minb[pos] {
            minb[pos] = v
        }
        if v > maxb[pos] {
            maxb[pos] = v
        }
    }
    
    res := 0
    last := minb[0]
    for i := 0; i < len(minb); i++ {
        if minb[i] - last > res {
            res = minb[i] - last
        }
        if maxb[i] != -1 {
            last = maxb[i]
        }
    }
    return res
}

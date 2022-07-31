func max(a, b int) int {
    if a > b {
        return a
    }
    return b
}

func maxProfit(k int, prices []int) int {
    n := len(prices)
    pre, cur := make([]int, n), make([]int, n)
    for i := 0; i < k; i++ {
        maxdp, maxp := 0, -1000
        for j := 0; j < n; j++ {
            cur[j] = maxp + prices[j]
            maxp = max(maxp, maxdp - prices[j])
            maxdp = max(maxdp, pre[j])
        }
        pre, cur = cur, pre
    }
    res := 0
    for _, v := range pre {
        res = max(res, v)
    }
    return res
}

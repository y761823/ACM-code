import "strconv"

func fractionToDecimal(numerator int, denominator int) string {
    if numerator == 0 {
        return "0"
    }
    flag := false
    if numerator < 0 {
        flag = !flag
        numerator = -numerator
    }
    if denominator < 0 {
        flag = !flag
        denominator = -denominator
    }
    res := strconv.Itoa(numerator / denominator)
    if flag {
        res = "-" + res
    }
    numerator = numerator % denominator
    if numerator == 0 {
        return res
    }
    mp := map[int]int{}
    decimal := []rune{}
    for numerator != 0 {
        n := numerator * 10 / denominator
        r := numerator * 10 % denominator
        pos, ok := mp[numerator]
        if ok {
            return fmt.Sprintf("%s.%s(%s)", res, string(decimal[:pos]), string(decimal[pos:]))
        }
        mp[numerator] = len(decimal)
        decimal = append(decimal, rune('0' + n))
        numerator = r
    }
    return res + "." + string(decimal)
}

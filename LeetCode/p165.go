func split(version string) (int, string) {
    idx := strings.Index(version, ".")
    if idx == -1 {
        num, _ := strconv.Atoi(version)
        return num, ""
    }
    num, _ := strconv.Atoi(version[:idx])
    return num, version[idx + 1:]
}

func compareVersion(version1 string, version2 string) int {
    for len(version1) > 0 || len(version2) > 0 {
        var v1, v2 int
        v1, version1 = split(version1)
        v2, version2 = split(version2)
        if v1 > v2 {
            return 1
        } else if v1 < v2 {
            return -1
        }
    }
    return 0
}

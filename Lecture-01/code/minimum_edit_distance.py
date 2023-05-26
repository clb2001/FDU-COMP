import numpy as np


def minimum_edit_distance(source, target):
    n = len(source)
    m = len(target)
    d_mat = np.zeros((n + 1, m + 1))
    for i in range(1, n + 1):
        d_mat[i, 0] = i
    for j in range(1, m + 1):
        d_mat[0, j] = j
    for i in range(1, n + 1):
        for j in range(1, m + 1):
            sub = 0 if source[i - 1] == target[j - 1] else 2
            del_ = d_mat[i - 1][j] + 1
            ins_ = d_mat[i][j - 1] + 1
            d_mat[i][j] = min(del_, ins_, d_mat[i - 1][j - 1] + sub)
    trace, align_source, align_target = backtrack_alignment(source, target, d_mat)
    return d_mat[n, m], trace, align_source, align_target


def backtrack_alignment(source, target, d_mat):
    align_source, align_target = [], []
    i = len(source)
    j = len(target)
    back_trace = [[i, j]]
    while (i, j) != (0, 0):
        sub = 0 if source[i - 1] == target[j - 1] else 2
        del_ = d_mat[i - 1][j]
        ins_ = d_mat[i][j - 1]
        # substitution operation
        if d_mat[i][j] == d_mat[i - 1][j - 1] + sub:
            back_trace.append([i - 1, j - 1])
            align_source = [source[i - 1]] + align_source
            align_target = [target[j - 1]] + align_target
            i, j = i - 1, j - 1
        else:
            # deletion operation
            if d_mat[i][j] == del_ + 1:
                back_trace.append([i - 1, j])
                align_source = [source[i - 1]] + align_source
                align_target = ["*"] + align_target
                i, j = i - 1, j
            # insertion operation
            elif d_mat[i][j] == ins_ + 1:
                back_trace.append([i, j - 1])
                align_source = ["*"] + align_source
                align_target = [target[j - 1]] + align_target
                i, j = i, j - 1
    return back_trace, align_source, align_target


def test_med(source, target):
    med, trace, align_source, align_target = minimum_edit_distance(source, target)
    print(f"input source: {source} and target: {target}")
    print(f"med: {med}")
    print(f"trace: {trace}")
    print(f"aligned source: {align_source}")
    print(f"aligned target: {align_target}")


def main():
    test_med(source="INTENTION", target="EXECUTION")
    test_med(source="AGGCTATCACCTGACCTCCAGGCCGATGCCC", target="TAGCTATCACGACCGCGGTCGATTTGCCCGAC")


if __name__ == '__main__':
    main()

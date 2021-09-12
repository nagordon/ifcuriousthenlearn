@mfunction("L, U")
def LUCrout(A=None):
    # Decomposes matrix A into a Lower matrix L and Upper matrix U
    # A = LU
    [R, C] = size(A)
    for i in mslice[1:R]:
        L(i, 1).lvalue = A(i, 1)
        U(i, i).lvalue = 1
    end
    for j in mslice[2:R]:
        U(1, j).lvalue = A(1, j) / L(1, 1)
    end
    for i in mslice[2:R]:
        for j in mslice[2:i]:
            L(i, j).lvalue = A(i, j) - L(i, mslice[1:j - 1]) * U(mslice[1:j - 1], j)
        end
        for j in mslice[i + 1:R]:
            U(i, j).lvalue = (A(i, j) - L(i, mslice[1:i - 1]) * U(mslice[1:i - 1], j)) / L(i, i)
        end
    end
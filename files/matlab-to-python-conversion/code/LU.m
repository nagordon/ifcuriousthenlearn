% function [L,U] = LUCrout(A)
% Decomposes matrix A into a Lower matrix L and Upper matrix U
% A = LU
A = [1,5,3,5;  2,5,6,7; 9,0,3,4; 9,4,7,6]
A
[R,C] = size(A);
for i = 1:R
    L(i,1) = A(i,1);
    U(i,i) = 1;
end
for j = 2:R
    U(1,j) = A(1,j)/L(1,1);
end
for i = 2:R
    for j = 2:i
        L(i,j) = A(i,j) - L(i,1:j-1)*U(1:j-1,j);
    end
    for j = i+1:R
        U(i,j) = (A(i,j) - L(i,1:i-1)*U(1:i-1,j))/L(i,i);
    end
end
L
U
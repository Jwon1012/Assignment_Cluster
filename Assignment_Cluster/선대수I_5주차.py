#실습 I(행렬식의 일반적인 성질)

import numpy as np

A = np.array([
    [2,1,3,4],
    [0,1,1,0],
    [1,0,1,1],
    [4,2,1,-1],
], dtype = int)

original_A = A.copy()
swap_count = 0

def show(step,matrix):
  print(f"\n{step}")
  print(matrix)

show("초기 행렬 A", A)

#1, R1과 R3교환
A[[0,2]] = A[[2,0]]
swap_count += 1
show("1단계: R1 <-> R3", A)

#2, 1번째 열의 아래쪽 원소를 0으로
A[2] = A[2] - 2 * A[0] #R3 <- R3 - 2R1
show("2단계 R3 <- R3 - 2R1", A)

A[3] = A[3] - 4*A[0] #R4 <-- R4 - 4R1
show("3단계 R4 <- R4 - 4R1", A)

# 3. 두번쨰 열의 아래쪽 원소를 0으로
A[2] = A[2] - A[1] #R3 <- R3 - R2
show("4단계 R3 <- R3 - R2", A)

A[3] = A[3] - 2*A[1] #R4 <- R4 - 2R2
show("5단계 R4 <- R4 - 2R2", A)

# 4. 피벗 위치를 맞추기 위해 R3과 R4 교환
A[[2,3]] = A[[3,2]]
swap_count += 1
show("6단계 R3 <-> R4", A)

#상삼격행렬의 대각 원소 곱
diagonal_product = np.prod(np.diag(A))

#행 교환이 일어날 때마다 행렬식의 부호 변환
det_A = ((-1) ** swap_count) * diagonal_product

print("\n행 사다리꼴:")
print(A)

print("\n대각 원소의 곱:", diagonal_product)
print("행렬식의 부호 변환 횟수:", swap_count)
print("det(A)", det_A)

#Numpy 계산결과와 비교
det_check = round(np.linalg.det(original_A))
print("\nNumpy 계산 결과:", det_check)

#실습 II(역행렬)

A = np.array([
    [1, 0, 2],
    [2, -1, 3],
    [4, 1, 8]
])

B = np.array([
    [-11, 2, 2],
    [-4, 0, 1],
    [6, -1, -1]
])

#3*3 단위행렬
L = np.eye(3, dtype = int)

#행렬곱 계산
AB = A @ B
BA = B @ A

print("A = ")
print(A)

print("\nB = ")
print(B)

print("\nAB = ")
print(AB)

print("\nBA = ")
print(BA)

print("\nAB = L: ", np.array_equal(AB,L))
print("BA = L:", np.array_equal(BA,L))

if np.array_equal(AB , L) and np.array_equal(BA, L):
  print("\nA와 B는 서로 역행렬입니다. \n 즉, B = A^-1이고, A = B^-1입니다.")
else:
  print("\nA와 B는 서로 역행렬이 아닙니다.")

#실습 III(역행렬 II)
A = np.array([
    [1, 2],
    [1, 3]
], dtype=float)

B = np.array([
    [3, 2],
    [2, 2]
])

# 각각의 역행렬
A_inv = np.linalg.inv(A)
B_inv = np.linalg.inv(B)

AB = A @ B

left = np.linalg.inv(AB) #(AB)^-1

right = B_inv @ A_inv #B^-1 A^-1

np.set_printoptions(precision=3, suppress=True)

print("A^-1 = ")
print(A_inv)

print("\nB^-1 = ")
print(B_inv)

print("\nAB = ")
print(AB)

print("\n(AB)^-1 = ")
print(left)

print("\nB^-1 A^-1 = ")
print(right)

print("\nIs (AB)^-1 = B^-1 A^-1? ")
print(np.allclose(left, right))

#실습 IV (역행렬III)

from fractions import Fraction

def print_augmented(title, matrix):
  """첨가행렬 [A | I]를 출력하는 함수"""
  print(f"\n{title}")

  for row in matrix:
    left = " ".join(f"{str(x):>4}" for x in row[:2])
    right = " ".join(f"{str(x):>4}" for x in row[2:])
    print(f"[ {left} | {right}]")

#행렬 A와 단위행렬 I로 철가행렬 생성
augmented = [
    [Fraction(3), Fraction(4), Fraction(1), Fraction(0)],
    [Fraction(2), Fraction(3), Fraction(0), Fraction(1)]
]

print_augmented("초기 첨가행렬 [A | I]", augmented)

#1단계: (1/3)R1 -> R1
augmented[0] = [
    value / 3 for value in augmented[0]
]

print_augmented("1단계: (1/3)R1 -> R1", augmented)

#2단계 : 첫번째 열의 2를 0으로
#R2 - 2R1 -> R2
augmented[1] = [
    augmented[1][i] - 2 * augmented[0][i] for i in range(4)
]

print_augmented("2단계: R2 - 2R1 -> R2", augmented)

#3단계 : 두 번째 피벗을 1로
#3R2 -> R2

augmented[1] = [
    value * 3 for value in augmented[1]
]

print_augmented("3단계: R2 -> R2 / 3", augmented)

#4단계: 첫 번째 행의 4/3을 0으로
#R1 - (4/3)R2 -> R1

augmented[0] = [
    augmented[0][i] - Fraction(4,3) * augmented[1][i] for i in range(4)
]

print_augmented("4단계: R1 - (4/3)R2 -> R1", augmented)

#오른쪽 부분이 역행렬
A_inverse = [
    row[2:] for row in augmented
]

print("\nA의 역행렬")
for row in A_inverse:
  print(" ".join(f"{str(x):>4}" for x in row))


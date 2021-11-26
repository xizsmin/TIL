""
주사위 눈 >= 5 <- 바구니에 흰 공 2개
주사위 눈 < 5 <- 바구니에 검은 공 1개

5회 반복 후 바구니에 든 공 갯수가 7개 이상일 때,
흰 공과 검은 공의 갯수가 같았던 순간이 있었을 확률
""

import random

q = 0
p = 0
def f():
    global p, q
    
    k = 0
    a = 0
    b = 0
    for i in range(1,6):
        x = random.randint(1,6)
        if x >= 5:
            a = a + 2
        else:
            b = b + 1
        if a == b:
            k = k + 1
            
    if a + b >= 7:
        q = q + k
        p = p + 1
            
def main():
    print("main")
    for i in range(1, 500000):  # 횟수 커질수록 유리
        f()
    print(q)
    print(p)

if __name__ == "__main__":
    main()
    
    
    

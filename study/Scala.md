### Scala basic
- Class vs. Object
  - Class: JAVA의 class
  - Object: Class의 한 종류, singleton 객체(한 프로그램 내에 하나만 존재)
    - main 포함하는 class는 object
- 강타입 언어(변수 type이 정해져 있음)
- val vs. var: val은 할당 후 변경불가(val 권장) - 한번 결정되면 code flow에서 변경 안된다는 보장 있어서 편함
- 함수선언:
  - return 따로 안쓰고 수식처럼(flow 마지막에 있는 게 리턴)
  - 나머지는 문법문제..
  - return할 게 없으면 Unit type(~= void)
```scala
def f(x: Int, y: Int) : Int = {
  if (x < y) x
  else y
}
```

- 함수든 변수든 그냥 객체
```scala
val f = (x:Int, y:Int) => if (x > y) x else y   // 단순 대입

// 함수(객체)의 타입을 명시적으로 지정하면
val f2: (Int, Int) => Int = (x: Int, y: Int) => if (x > y) x else y

// 복수 개 리턴
def max(x: Int, y: Int): (Int, Int) = if (x > y) (x, y) else (y, x+y)
```



 

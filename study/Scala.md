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

// 복수 개 리턴(하고 싶으면 튜플 등으로 묶어서)
def max(x: Int, y: Int): (Int, Int) = if (x > y) (x, y) else (y, x+y)
```

- Unit == Void
```scala
def greet(): Unit = println("Hello world!")
```

- 명령형 vs. 함수형
  - 명령할 내용을 일일이 지시하는 대신 기능(함수) 단위로
```scala
// list 중 10 이상인 x에 대해 2로 나누고 리턴
def f(list:List[Int]): List[Int] = list.filter(x => x > 10).map(x => x / 2)

def filterFunc(x: Int) = Boolean = x > 10
def f(list:List[Int]): List[Int] = list.filter(filterFunc).map(x=> x / 2)
```

- Example) 0 이상의 정수를 이진법으로 나타냈을 때 1의 개수
```scala
def g(x: Int): Int = if (x == 0) 0 else if ((x & 1) == 1) 1 + g(x >> 1) else g(x >> 1)
```

- 배열
```scala
// [] : Type 지정할 때만 사용
// index는 ()로 접근
// array는 배열 주소를 저장하는 val -> append 불가
// 배열 값 각각은 var처럼 취급
val array = new Array[Int](5)
array(0) = 3
array(2) = 2

// 값으로 초기화 가능 (초기화시 사이즈로 고정)
val names = Array("zero", "one", "two")

```

- 연산자는 없음 -> 다 함수
  - 1 + 2  <-->  (1).+(2)

- List
  - index로 접근 불가, 하나씩 순회만 가능
  - 초기화 이후에는 값 변경 불가
  - 2개 이상의 List를 cons (:::) 로 이어붙이는 건 가능
```scala
val list1 = List(1,2,3)
val list2 = List(4,5)
// list2의 ::: 가 호출되어 list1을 앞에 붙임
val list3 = list1 ::: list2     // 1,2,3,4,5
// !!!
val list3_1 = list1.:::(list2)
// :: -> list의 api
val list4 = 0 :: list4        // 0,1,2,3,4,5

// Nil : 빈 리스트 ( -> Nil.
val list5 = 1 :: 2 :: 3 :: Nil
  
```

- Tuple
  - 변경 불가능, 원소별로 다른 타입 지정 가능
``` scala
  val pair = (99, "aaa")
  println(pair._1)      // 99
  println(pair._2)      // aaa
  
```
 
- Set: 중복 및 순서 없음
- Map
``` scala
val map1 = Map( 1 -> "I", 2 -> "II", 3 -> "III", 4 -> "IV", 5 -> "V", 6 -> "III")
println(map1(2))      // II
println(map1.filter(x => x._2 == "III"))   // HashMap(6->"III", 3->"III")
```  
 

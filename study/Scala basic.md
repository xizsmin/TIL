# Types and operations

## 기본 타입
- Byte, Short, Int, Long, Char
- Float, Double

## Literal
```scala
val hex = 5
val hex2 = 0xff
val tower = 3L    // long
val big = 3.14    // double
val little = 1.234f  // float
```

## 문자 literal
```scala
val a = 'A'   // character
val d = '\u0041'
val str = "string"   // string

// Aligning with \n
println(
    """Welcome to Ultamix 3000.
      |Type "Help" for help.
      |""".stripMargin)
```

## 문자열 interpolation
```scala
val name = "Eric"
println(s"Hello, $name!")           // Hello, Eric!

println(s"Sum of 1 and 7: ${1+7})   // Sum of 1 and 7: 8
```

## Operator is Method
```scala
val sum = 1 + 2                     // 3
val sumlikeMethod = 1.+(2)          // 3
```

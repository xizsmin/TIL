- Coroutines & Threads:
  - Multitasking에 활용 가능
  - Coroutine의 경우 사용자 의도대로, 의도한 시점에서 pause / resume 가능하며
  - Native OS thread에 묶인 개념이 아니다 (오히려 작업 단위에 가까움).
  - 따라서 OS scheduler가 관리하지는 않음
  - Threading보다 상위 레벨에서 동작하는 프레임워크
  
- Kotlin coroutines are STACKLESS
  - thread는 자기 stack이 있는 반면 Kotlin에서의 coroutine은 그렇지 않음
  - "Kotlin coroutine as a light-weight thread"
  
- Kotlin coroutines vs. Threads:
  - 공통점: parallel하게 동작 가능하며 상호 통신 가능.
  - 차이점: coroutine은 자원 소모가 매우 적음!
    - Threading framework 상위에서 동작, 좀더 편리하고 효율적인 방법으로 concurrency 확보 가능
    
  
  
![4_01_ThreadDiagram](https://user-images.githubusercontent.com/57291261/99969029-4004a280-2ddd-11eb-9a20-2d76f00f7e38.jpg)

[OS Thread 구조]


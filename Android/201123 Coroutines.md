- Coroutines & Threads:
  - Multitasking에 활용 가능
  - Coroutine의 경우 사용자 의도대로, 의도한 시점에서 pause / resume 가능하며
  - Native OS thread에 묶인 개념이 아니다 (오히려 작업 단위에 가까움).
  - 따라서 OS scheduler가 관리하지는 않음
  - Threading보다 상위 레벨에서 동작하는 프레임워크
  
- Kotlin coroutines are STACKLESS
  - thread는 자기 stack이 있는 반면 Kotlin에서의 coroutine은 그렇지 않음
  
  

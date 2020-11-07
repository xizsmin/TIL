# Fragment
### 의미
- Activity 내에 생성되는 여러 화면 요소들을 모듈처럼 묶어서 구성하는 단위

### 특징
1. 생명 주기, 입력 이벤트 등을 자체적으로 가지며 액티비티 실행 중 동적으로 추가/제거 가능
2. 액티비티를 분할 - UI 컴포넌트 여러 개를 모듈식으로 구성, 재사용성 높음
- 태블릿 등 큰 화면에서 역동적이고 유연한 UI를 지원하는 것이 목적이었음
  

### 기존의 UI 구성방식에 대한 차이점
1. 레이아웃에 정의하는 것에 비해 이벤트/데이터 처리가 유연
2. 액티비티 중첩시 생명주기 관계가 복잡해지는 등 다루기 어려워지는 문제 해결

### 생명 주기

- (Fragment added) -> onAttach -> onCreate -> onCreateView -> onActivityCreated -> onStart -> onResume -> (Fragment Activated!)
                                                    |                                                                 |
                                                    <------------ onDestroyView <- onStop <- onPause <-----------------



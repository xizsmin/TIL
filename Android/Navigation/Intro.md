# Navigation
- 사용자가 앱 내의 여러 contents를 탐색하고 돌아다닐 수 있게 하는 interaction
- Android Jetpack에서 보완, 복잡한 패턴(Appbar, search windows) 등을 풍부하게 구현

## Navigation 구성요소
- `Navigation Graph`: target app 내의 이동 가능한 경로
- `NavHost`: Navigation graph에서 대상을 표시하는 container 
- `NavController`: `NavHost`에서 navigation 관리하는 객체

*Navigation graph가 경로를 따라 이동할지, 대상으로 직접 이동할지 등을 NavController에 전달하면 NavController에서 NavHost에 대상 표시*

### 장점
- Fragment Transaction 관리
- Back / Up action 등 명확히 처리
  - Back: 시간 순서의 역순, Up: 앱 구조상 상위 hierarchy
- Animation 및 Transition에 표준화된 리소스 제공
- **Safe Args**: Navigate하면서 데이터 전달
- `ViewModel` 지원: Navigate 대상들 사이에서 UI 데이터 효율적 공유
- Navigation UI (Navigation drawer, 하단 navigation bar 등)
- 딥링크 지원

**`활용가능한 분야: 설문조사나 심리테스트 등 선택내용 기반해서 다음 단계가 결정되고 계속 따라가야 되는 경우`**


# Navigation 원리
- 앱이 실행되면 새로운 task 생성, start destination 표시 -> back stack 맨 하단에 위치
- 새로운 Destination으로 이동하면서 push, 이전으로 돌아가면서 pop
- 기본적으로 Navigation component에서 back stack 관리, 개발자가 직접 관리할 수도 있음

## Up & back are identical within your app's task?
- Back: 화면 하단의 navigation bar에 위치, 최근 task 기록을 역순으로 -> 현재 destination을 pop
- Up: App bar에 표시, task 내에서는 Back button과 동일

## Up button은 앱 종료X
- App 의 start destination에 있는 경우 Up button 없음 (Back button은 존재, 앱 종료 가능)
- App A가 다른 app B의 task에서 deep link 통해 실행된 후 Up button 동작 -> 앱 A 내에서 상위로

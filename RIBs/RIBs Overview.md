## RIBs
- Mobile cross platform arch.
- 비즈니스 로직 중심으로 앱을 구성, 비즈니스 로직에 따라 앱 상태를 노드로 하는 state machine (Tree)
  - 단방향 트리, 부모가 자식에게 정보 받으려면 자식의 listener를 구현해서 observe
  - Child는 이벤트 있을 때 listener.event() 호출 -> Parent는 갖고 있는 listener에서 해당 event 감지 가능
  - Parent는 child보다 오래 산다
- 이 state tree 중심으로 앱을 구성: 각 노드는 RIB, 하나의 RIB은 하나의 상태를 나타냄
- 뷰 대신 비즈니스 로직이 중심이 됨: 뷰 단위의 구성방식 대신 비즈니스 로직에 집중, 뷰 - 로직간 결합도 낮춤

## Interactor
- 비즈니스 로직 담당
- RIB 간의 커뮤니케이션, 
- 비즈니스 상태변경 / 뷰 이벤트 받아서 비즈니스 로직 실행 
- 어떤 state인지 결정됨에 따라 어떤 child RIB이 붙을지 결정

## Router
- RIB 간의 연결 담당
- `Interactor`에서 어떤 child RIB이 붙을지 /떨어질지 결정되면 라우터가 실제로 수행
- Child RIB의 builder를 가지고 있다

## Builder
- Factory pattern으로 한 RIB의 생성을 담당
- 의존성 주입/관리
### Component
- RIB의 dependency 관리
- 다른 RIB의 dependency에 접근 가능 - 해당 RIB을 구성하는 데 필요한 dependency 만들 수 있음
- 주로 child RIB에서 parent RIB의 dependency에 접근하기 위해 parent component를 사용

## (Optional) View, Presenter

### Communication
- 위 -> 아래 방향으로: Rx stream을 DI하거나 build method 에 parameter로 전달
- 아래 -> 위 방향으로: listener

## Workflow
- Generic class로 정의되어 있음, parameter type으로 `ActionableItem`
  - `ActionableItem`: RIB 트리에서 path를 이루는 각 `Step`에서 할 일과 로직을 정의
  - Workflow를 이루는 각 `Step` (각 RIB의 Interactor) 는 이 ActionableItem에 정의된 프로토콜을 따라야 함
- Custom url scheme 처리 지원
- RIB 트리에서 실행 가능한 특정 path의 일련의 `Step`들 (root ~ <path> ~ 기대하는 상태까지)을 정의
  
https://play-tv.kakao.com/embed/player/cliplink/414004680?popup=1&autoplay=1
  
  

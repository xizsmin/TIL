# Navigation
- 사용자가 앱 내의 여러 contents를 탐색하고 돌아다닐 수 있게 하는 interaction
- Android Jetpack에서 보완, 복잡한 패턴(Appbar, search windows) 등을 풍부하게 구현

## Navigation 구성요소
- `Navigation Graph`: target app 내의 이동 가능한 경로
- `NavHost`: Navigation graph에서 대상을 표시하는 container 
- `NavController`: `NavHost`에서 navigation 관리하는 객체

*Navigation graph가 경로를 따라 이동할지, 대상으로 직접 이동할지 등을 NavController에 전달하면 NavController에서 NavHost에 대상 표시*

### 장점
- Fragment Transaction 및 뒤로가기 / 상위 이동 등 명확히 처리 (PopUpTo)
- Animation 및 Transition에 표준화된 리소스 제공
- **Safe Args**: Navigate하면서 데이터 전달
- `ViewModel` 지원: Navigate 대상들 사이에서 UI 데이터 효율적 공유

**`활용가능한 분야: 설문조사나 심리테스트 등 선택내용 기반해서 다음 단계가 결정되고 계속 따라가야 되는 경우`**


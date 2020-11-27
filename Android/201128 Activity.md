# Activity
## 개념
- App과 사용자의 상호작용을 위한 진입점 역할: (대부분의) app은 여러 Activity로 구성
- App이 UI를 그리는 Window를 제공
  - Floating 가능, fullscreen 아닐 수도 있음, 투명,...
  - **각 상태에 따른 이전 activity 상태(callback), setResult <-> onActivityResult**

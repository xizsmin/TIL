# Activity
## 개념
- App과 사용자의 상호작용을 위한 진입점 역할: (대부분의) app은 여러 Activity로 구성
- App이 UI를 그리는 Window를 제공
  - Floating 가능, fullscreen 아닐 수도 있음, 투명,...
  - **각 상태에 따른 이전 activity 상태(callback), setResult <-> onActivityResult**
  - 여러 액티비티 중 하나가 최초 앱 시작점 역할을 함: `AndroidManifest.xml => <application>`하위에 다음 내용 포함
  
  ```xml
  <intent-filter>
     <action android:name="android.intent.action.MAIN />
     <category android:name="android.intent.category.LAUNCHER" />
  </intent-filter>                                                              
  ```

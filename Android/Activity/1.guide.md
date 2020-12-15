# Activity
## Concept
- 앱과 사용자 사이의 진입점 역할을 하는 Android app의 component 중 하나 (나머지: service, broadcast receiver, content provider)
- Android app의 구성요소 중 하나
- 앱을 호출할 때, 앱 자체가 아니라 **앱의 액티비티**를 호출하는 것: 앱과 사용자 사이의 진입점 역할
- 일반적으로는 한 액티비티 == 한 화면 구현, 여러 액티비티가 앱 하나를 구성하는 경우가 많음
  - 그 중 한 액티비티가 launcher 역할: 앱 진입시 올라오는 첫번째 화면
- UI를 그리는 window 제공: 화면을 채우거나 더 작은 상태로 떠 있을 수 있음.
  - `android:windowIsFloating`, `android:windowIsTranslucent`
- 액티비티 간 종속성 높지 않음: 다른 앱에 속하는 액티비티를 실행할 수 있음.
- 대부분의 앱은 여러 액티비티로 구성 - 이 중 하나가 default activity로 지정
```xml
        <activity android:name=".MainActivity">
            <intent-filter>
                <action android:name="android.intent.action.MAIN" />
                <category android:name="android.intent.category.LAUNCHER" />
            </intent-filter>
        </activity>
```

# Activity 사용
## manifest 구성
- Manifest 파일에 Activity 및 관련 속성을 설정해야 사용 가능
### Activity 선언
- `android:name` 필수 속성
```xml
<manifest ...>
  <application ...>
    <activity android:name=".ExampleActivity" />
    ...
  </application ...>
</manifest>
```

### Intent filter 선언
- Explicit/implicit 요청을 기반으로 Activity 실행
  - Explicit: 액티비티 이름을 지정
  - Implicit: 수행할 작업이 가능한 Activity를 시작(혹은 선택하도록 chooser 제공)
- intent filter 요소: action, category, data
  - action: 액션 네임(필수)
  - category: 보통 DEFAULT
  - data: 허용 data type (text/plain, mime 등)
  - manifest에 intent-filter 설정 예시
  ```xml
  <activity android:name=".ExampleActivity" android:icon="@drawable/app_icon">
      <intent-filter>
          <action android:name="android.intent.action.SEND/>
          <category android:name="android.intent.category.DEFAULT />
          <data android:mimeType="text/plain" />
      </intent-filter>
  </activity>
  ```

  - 위와 같은 Activity를 코드상에서 호출하려면
    - **암시적 호출: 호출할 Activity 이름을 지정하지 않음!**
  ```kotlin
  val sendIntent = Intent().apply {
      action = Intent.ACTION_SEND
      type = "text/plain"
      putExtra(Intent.EXTRA_TEXT, textMessage)
  }
  startActivity(sendIntent)
  ```
  
## Activity Lifecycle
### onCreate()
- 시스템이 Activity 생성시 호출
- 필수 구성요소 초기화 (최초 1회만 필요한 것, e.g., `setContentView()`)
- *onCreate() 다음은 항상 onStart()*

### onStart()
- Activity가 visible한 상태가 됨

### onResume()
- 사용자 interaction 가능, focus 가져옴 - 주요 기능 구현
- *Activity stack의 TOP 에 위치*

### onPause()
- 포커스 잃고 Paused 상태로 전환
- (부분적으로) visible한 상태 유지, interaction은 불가 (일부만 가리거나 투명 액티비티로 덮일 때 등)
- UI 업데이트는 계속 가능 (focus 잃어도 영상은 계속 플레이되는 등)
- **!! 데이터 저장이나 네트워크/DB 작업 수행 등은 여기서 하지 말 것**
- 다음 상태: onResume() or onStop()

### onStop()
- **이제 invisible**
- 다음 상태: onRestart() or onDestroy()

### onDestroy()
- Activity 제거되기 전
- back button 등으로 activity 떠나거나, `finish()` 호출 등
- 관련 리소스 해제 구현






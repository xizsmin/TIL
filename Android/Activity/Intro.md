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
  

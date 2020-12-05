# Activity
## Concept
- Android app의 구성요소 중 하나
- 앱을 호출할 때, 앱 자체가 아니라 **앱의 액티비티**를 호출하는 것: 앱과 사용자 사이의 진입점 역할
- 일반적으로는 한 액티비티 == 한 화면 구현, 여러 액티비티가 앱 하나를 구성하는 경우가 많음
  - 그 중 한 액티비티가 launcher 역할: 앱 진입시 올라오는 첫번째 화면
- UI를 그리는 window 제공: 화면을 채우거나 더 작은 상태로 떠 있을 수 있음.
- 액티비티 간에는 최소한의 종속성: 다른 앱에 속하는 액티비티를 실행할 수 있음.


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
  
### Permission 선언  

## Activity Life-cycle
- 액티비티 상태에 따른 콜백

### onCreate()
- 시스템이 Activity 생성시 부르는 callback
- 구현 시 필수요소를 초기화 (생성 초기에 한 번만 해도 되는것)

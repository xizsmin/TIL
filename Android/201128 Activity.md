# Activity
## 개념
- App과 사용자의 상호작용을 위한 진입점 역할: (대부분의) app은 여러 Activity로 구성
- App이 UI를 그리는 Window를 제공
  - Floating 가능, fullscreen 아닐 수도 있음, 투명,...
  - **각 상태에 따른 이전 activity 상태(callback), setResult <-> onActivityResult**
  - 여러 액티비티 중 하나가 최초 앱 시작점 역할을 함: `AndroidManifest.xml => <application>`하위에 다음 내용 포함
    - 없으면 No Launcher activity found 에러 발생!
    
  
  ```xml
  <intent-filter>
     <action android:name="android.intent.action.MAIN />
     <category android:name="android.intent.category.LAUNCHER" />
  </intent-filter>                                                              
  ```


## Manifest 구성
### Activity 선언
- `AndroidManifest.xml` => `<application>` => **`<activity>`** 추가

```xml
    <manifest ... >
      <application ... >
          <activity android:name=".ExampleActivity" />
          ...
      </application ... >
      ...
    </manifest >
```

### Intent-filter 선언
- 앱이 수신할 수 있는 *Implicit* intent 선언 (Explicit intent는 무조건 대상에 전달)
- 구성요소 : **`action`, `data`, `category`**

```xml
<activity android:name="ShareActivity">
    <intent-filter>
        <action android:name="android.intent.action.SEND"/>
        <category android:name="android.intent.category.DEFAULT"/>
        <data android:mimeType="text/plain"/>
    </intent-filter>
</activity>
```
- !! 주의사항: Intent name을 알면 다른 앱에 의해 활성화될 수도 있음 -> 방지 필요


### Permission 선언
```xml
    <manifest>
    <activity android:name="...."
       android:permission=”com.google.socialapp.permission.SHARE_POST”

    />
    
```



# Activity Life-cycle
수명주기 전반에 걸쳐 여러 상태를 거치게 되며, 상태 간 전환 처리에 콜백 사용 가능

## onCreate()
- 시스템이 Activity를 생성할 때 실행
- Activity 필수 구성요소를 초기화 (뷰 생성 등)
- **`setContentView()`** 호출, Activity의 UI를 위한 레이아웃 정의

## onStart()
- Activity *시작* 단계로 전환, 사용자에게 Activity 표시
- Activity가 Foreground로 나올 준비

## onResume()
- Activity-User interaction 시작 직전에 호출
- **Activity stack의 TOP에 위치**, 모든 user input 캡처
- App의 핵심 기능 대부분을 구현


## onPause()  
### *`onResume()` 다음에만 불림*
- Activity가 포커스 잃고 일시정지 상태가 됨 (back, recent 버튼 클릭 등)
- UI update는 가능 (e.g., 내비게이션 지도 화면 등)
- 다음 단계: (상황에 따라) `onResume()` 또는 `onStop()`

## onStop()
- 사용자에게 **invisible한 상태**
  - `destroy` 중
  - 다른 activity가 시작
  - 원래 있던 activity가 resume되면서 현재 activity를 덮음
  
- 다음 단계: (상황에 따라)
  - 복원되어 User interaction 시작할 경우엔 `onRestart()`
  - 완전히 종료될 경우는 `onDestroy()`
  
## onRestart()
- `stopped` 상태였던 activity가 재시작될 때 상태복원
- 끝나면 `onStart()` 불림
  
## onDestroy()
- Activity가 수신하는 마지막 콜백
- Activity (또는 activity를 포함하는 프로세스)가 완전히 제거되기 전에 호출
- Activity가 갖는 모든 리소스를 해제하도록 구현
  



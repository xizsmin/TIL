# Activity Lifecycle

## Activity lifecycle 개념
- 기본 콜백: `onCreate()`, `onStart()`, `onResume()`, `onPause()`, `onStop()`, `onDestroy()`
  - `onRestart()`
  
- 사용자가 Activity 벗어나기 시작하면 destroy 과정 시작되지만 메모리상에는 남아 있을 수 있음

## Activity lifecycle callbacks
### onCreate()
- 필수 구현, CREATED 상태 됨
- 이 Activity의 lifecycle과 연관된 **lifecycle-aware components** (*see architecture components*)는 `ON_CREATE` event 수신
- 전체 수명주기 동안 1회만 발생해야 하는 기본 app 시작 로직 실행
  - e.g., list에 data bind, Activity와 view model 연결, `setContentView()` 호출 등
  - `setContentView()` 에 레이아웃 전달하는 대신 `View` 객체를 생성하고 `ViewGroup`에 넣어서 새로운 view 계층구조 빌드한 뒤 `setContentView`에 이 ViewGroup 넣어서 전달 가능
  - `savedInstanceState` 매개변수 수신: Activity의 이전 저장 상태가 포함된 bundle 객체
    - configuration (screen rotation) change, locale 변화 등 일어나서 destroy되고 재생성되는 경우 UI data 저장용 등으로 사용 가능
    
- @OnLifecycleEvent

### onStart()
- STARTED 상태로 전환, visible해지고 interaction 준비
- 기간 짧으므로 오래 걸리는 작업 하지 말 것
- lifecycle-aware: `ON_START` event

### onResume()
- Foreground에 activity 표시, 사용자 interaction 가능, focus 가져옴
- 사용자에게 보이는 동안 실행해야 하는 모든 기능을 활성화
- lifecycle-aware: `ON_RESUME` event
```kotlin
  class CameraComponent : LifecycleObserver {
    ...
    @OnLifecycleEvent(Lifecycle.Event.ON_RESUME)
    fun initializeCamrera() {
        getCamera()
    }
    ...
  }
```  
- 이 경우는 액티비티에 focus 가져왔을 때만 카메라 초기화 가능
- focus 없이 보이기만 하는 상태 (e.g., 멀티윈도우에서 안 선택된 상황)에서도 카메라 쓰고 싶으면 `ON_START`로 구현해야
  - 주의: 다른 앱들과(멀티 윈도우 지원상태 등) 공유해야 하는 시스템 자원은 신중하게 제어
  
### onPause()
- 액티비티 떠나는 첫 번째 신호, foreground에서 내려옴 - interaction 중지
- Multi window 상에서, 아니면 부분적으로 가려지는 등의 이벤트. 이 상태에서 stop되기 전까지는 visible함
- 필요에 따라 리소스 해제도 가능하지만 multi window 상태 등에서는 사용자에게 여전히 보일 수 있으므로 `onStop()`에서 해제하는 것도 고려
- !! 실행시간 짧으므로 오래 걸리는데 확실히 끝내야 되는(중요한) 작업 하지 말 것 (데이터 저장, DB/네트워크 작업 등)
  - **부하가 큰 종료 작업은 `onStop()`에서**
- lifecycle-aware: `ON_PAUSE`

### onStop()
- Activity가 사용자에게 더 이상 표시되지 않음
- 부분적으로 가리는 정도가 아니고 완전히 안 보임 - 이 때 리소스 해제하거나 조정
- 부하가 큰 종료작업 실행 (DB에 백업 등)
- Stop 상태가 되면 activity는 메모리에 저장, Window와는 연결 X
- start시 이 정보를 다시 호출
- Stop 상태에서 시스템에 의해 소멸시키더라도 bundle에 있는 view 객체 상태는 유지, 사용자가 activity로 돌아왔을 때 복원
- lifecycle-aware: `ON_STOP`

### onDestroy()
- 완전히 activity가 소멸되기전 호출
  - 사용자가 완전히 activity를 떠나거나, Activity 상에서 `finish()` 호출하여 종료되는 경우
  - Config 변경 (screen rotation, locale change, multi window 등)으로 일시적 종료 (곧 재생성)
    - UI 데이터 보존에는 **ViewModel**을 활용해봄
    - 두 상황은 `isFinishing()`으로 구분 가능: 완전히 종료될 경우는 ViewModel의 `onCleared()`로 완전히 정리
    
- `onStop()`에서 정리 못한 리소스 완전히 정리할 것    


## Activity 상태 및 메모리에서 제거
- RAM 모자라면 시스템에서 프로세스 강제 종료 (LMK)
- 프로세스 상태에 따라 우선순위 결정: 덜 중요한 프로세스부터 kill


    
  

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

# Activity Lifecycle

## Activity lifecycle 개념
- 기본 콜백: `onCreate()`, `onStart()`, `onResume()`, `onPause()`, `onStop()`, `onDestroy()`
  - + `onRestart()`
  
- 사용자가 Activity 벗어나기 시작하면 destroy 과정 시작되지만 메모리상에는 남아 있을 수 있음

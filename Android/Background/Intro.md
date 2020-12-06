# Background 처리
## 기본 원칙
- 몇 밀리초 이상 걸리는 작업은 백그라운드 스레드에 위임
- 예시: 네트워크 요청, storage access, 비트맵 디코딩 등

## 백그라운드 작업 분류
- 즉시, 지연, 정시.
![task-category-tree](https://user-images.githubusercontent.com/57291261/101274966-872f6200-37e5-11eb-9990-7525e00d7be8.png)
[그림: 백그라운드 작업 결정 트리] https://developer.android.com/guide/background

- 즉시: 사용자 interaction 끝나기 전 완료해야 할 작업
  - **Coroutine**(ViewModelScope, LifecycleScope 등)
  - 미디어 재생 등 활성화시킨 채로 탐색하는 경우는 Foreground service
- 지연: 향후 언제든 실행할 수 있는 작업들
  - WorkManager: 앱이 종료되거나 단말 리부팅시에도 예약 가능
- 정시: 무조건 정시에 시작
  - AlarmManager
  
  
  

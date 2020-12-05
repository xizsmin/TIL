# Service
- 백그라운드에서 오래 실행 가능한 작업을 수행하는 App 구성요소
- UI 제공하지 않음
- 다른 App 구성요소에 의해 시작 가능 (Activity 등)
- App 구성요소와 바인딩 가능, 통신 (Broadcast, IPC 등) 가능
- 활용분야: 네트워크 트랜잭션(다운로드/업로드 등), 음악 재생, 파일 I/O, ContentsProvider 상호작용 등

## 유형
### Foreground
- 사용자에게 보이는 작업
  - e.g., 음악 재생, Noti 등
- (주의) 사용자가 앱(액티비티)과 interaction하지 않아도 계속 돌고 있음
- 실행중에는 StatusBar에 on going으로 Noti 표시해야 함 (>= PRIORITY_LOW), user가 존재 알 수 있게


### Background
- 사용자에게 안 보이는 작업 (보통은)....

### Bind
- App component가 서비스에 바인딩, Cli-server 인터페이스를 제공하여 interaction 가능
- startService() 대신 bindService()를 이용하여 생성/바인딩될 수 있고
- startService()로 생성된 서비스가 이후에 bindService()를 통해 바인드될 수도 있음
  - bindService()로 생성된 서비스는 bind가 모두 해제되면 자동 소멸
  - startService()로 생성되었으면 stopSelf()로 스스로 소멸시키거나, 다른 component가 stopService() 호출해서 명시적으로 죽여야 함
- 여러 component들이 한꺼번에 bind 가능하기도 함

## Service vs. Thread
- 서비스는 백그라운드에서 실행 가능할 뿐이고
- 기본적으로는 main thread에서 돌게 된다. 스레드 자체를 메인으로부터 분리해야 하는 경우(네트워크 작업 등)에는 별도 스레드에서 돌도록 조치해야 함
  - Thread, AsyncTask, Coroutine, HandlerThread...
  
## 사용 기본 사항
### 수명주기 처리
- onStartCommand()
  - startService() 불릴 때
  - 따라서 binding만 제공할 경우는 구현 불필요
  - 리턴값: 시스템이 강제 종료시 서비스 유지하는 방법을 명시
    - **START_NOT_STICKY** : 강제종료 후 다시 안 살아도 될 때
    - **START_STICKY** : 강제종료되어도 재생성하고 onStartCommand() 호출 (마지막 인텐트는 null) - 미디어 플레이어 등 대기는 해야 되는 것들
    - **START_REDELIVER_INTENT** : 강제종료시 재생성하며 마지막 intent값까지 유지 - 즉시 재개되어야 하는 작업 (파일 다운로드 등)
  
- onBind()
  - bindService() 불릴 때
  - 클라이언트-서비스 통신을 위한 인터페이스 제공해야 함 (IBinder)
  
- onCreate()
  - 서비스 생성시 (onStartCommand() 나 onBind() 호출 전) 1회 호출
  - 일회성 설정 절차 수행
  
- onDestroy()  
  - 소멸시 호출(stopSelf(), stopService(), 바인드로 생성됐을 경우는 바인딩 해제 등)
  - 리소스 정리
  
  ![service_lifecycle](https://user-images.githubusercontent.com/57291261/101259162-873e4c00-376a-11eb-8e8c-017182d3caba.png)

  
### 시스템에 의한 중단 (LMK)
- Foreground service는 종료될 가능성 거의 없음
- Foreground 에서 돌고 있는 액티비티(Focused)에서 메모리 부족한 정도까지 되어야 중단

### Manifest에서 서비스 선언
```xml
<manifest ... >
  ...
  <application ... >
      <service android:name=".ExampleService" />
      ...
  </application>
</manifest>
```
- `android:exported="false"` 본인의 앱에서만 서비스 사용 가능 (다른 앱에서 명시적 인텐트로도 호출 불가!)

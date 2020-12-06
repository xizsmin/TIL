# Background thread에서 Android 작업 실행
- main thread에서는 UI 업데이트 처리, bg thread에서 네트워크 요청 수행
- main thread에서 네트워크 요청하려고 시도할 경우: 응답이 올 때까지 **thread가 blocking되므로 ANR 발생**

# Background 최적화
Implicit broadcast는 인텐트 등록한 BroadcastReceiver 전체에 영향을 줄 수 있으므로 메모리와 베터리 사용 영향
## M OS (Android 7, API 24)부터
- 매니페스트에서 broadcast receiver 선언시 CONNECTIVITY_ACTION (network 관련) 수신하지 않음 (registerReceiver()로 등록한 건 수신가능)
- ACTION_NEW_PICTURE 나 ACTION_NEW_VIDEO 브로드캐스트 송수신 불가
  - **대체 메서드: WorkManager**



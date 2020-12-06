# Device Awake
## wake lock 대안
- 다운로드: `DownloadManager`
- 외부 서버의 데이터 동기화: `sync adapter`
- 백그라운드 서비스 trigger: **JobScheduler, Firebase Cloud Messaging**

## Keep the screen on
- 게임, 영화 등 화면 켜진 상태로 계속 유지해야 하는 경우: 

1. Activity에 `FLAG_KEEP_SCREEN_ON` 추가

```kotlin

    class MainActivity : Activity() {

        override fun onCreate(savedInstanceState: Bundle?) {
            super.onCreate(savedInstanceState)
            setContentView(R.layout.activity_main)
            window.addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON)
        }
    }
    
```

2. `android:keepScreenOn="true"`
- 근본적으로 Programatic 방식과 동일한데 나중에 cancel하려면 1번으로.

```xml
    <RelativeLayout xmlns:android="http://schemas.android.com/apk/res/android"
        android:layout_width="match_parent"
        android:layout_height="match_parent"
        android:keepScreenOn="true">
        ...
    </RelativeLayout>
```

## Keep the CPU on - wakelock
- 꼭 필요할 때만 wakelock 사용하고 가능한 짧게 유지
- 절전모드 전환 전 일부 필수작업 완료 등: Screen 켜 놓으려고 굳이 wake lock 잡을 필요는 없음
- 화면 꺼진 상태에서 작업 처리하는 백그라운드 서비스 등에서

```xml
<uses-permission android:name="android.permission.WAKE_LOCK" />
```
```kotlin
    val wakeLock: PowerManager.WakeLock =
            (getSystemService(Context.POWER_SERVICE) as PowerManager).run {
                newWakeLock(PowerManager.PARTIAL_WAKE_LOCK, "MyApp::MyWakelockTag").apply {
                    acquire()
                }
            }
    
    ...
    // 해제
    //wakeLock.release()
    
```

### Broadcast Receiver - to keep the device awaken
- `WakefulBroadcastReceiver`


# 반복 알람 예약 - AlarmManager
- App 사용하고 있지 않을 때에도 시간 기반 작업 실행 가능 (하루 1회 다운로드 / feedback 등)
- 지정된 시간/ 정해진 간격으로 Intent 실행
- Broadcast Receiver와 함께 알람을 사용하여 서비스 시작, 다른 작업 실행 가능
- App 미사용 중이거나 디바이스 sleep 모드일 때도 Event Trigger 가능
- 백그라운드 서비스나 타이머 등 없이 작업 예약 가능

## 장단점

### 장점
- 단순한 사용

### 단점
- 잘못 설계하거나 오사용하면 소모전류 증가
- e.g., 서버와 주기적으로 데이터 동기화: AlarmManager보다는 `Async adapter`와 `Google Cloud Messaging` 추천(...)



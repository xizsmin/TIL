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

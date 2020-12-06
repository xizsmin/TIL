# Broadcast
- Android 시스템 및 다른 app에서 관심 있는 event가 발생할 때 수신 가능 / 다른 app에 특정 상황 발생을 알리고 싶을 때 메시지 전송
- App에서 특정 브로드캐스트 수신 등록, 시스템이 브로드캐스트 라우팅

## OS 버전별 시스템 브로드캐스트 변경사항
### Android 7 (API 24) 이상
- 시스템에서 `ACTION_NEW_PICTURE`, `ACTION_NEW_VIDEO` 전송하지 않음
- `CONNECTIVITY_ACTION` 브로드캐스트는 context에 `registerReceiver(BroadcastReceiver, IntentFilter)` 로 등록해야 수신 가능

## 브로드캐스트 수신 (!!)
### Manifest에 Receiver 선언
- 브로트캐스트 발생시 해당 앱이 실행중이 아니면 **시스템에서 강제로 살림**
- 주의: 등록은 Manifest에 해도 Receiver 구현은 코드상에 해줘야 처리됨;

1. AndroidManifest.xml
```xml
    <receiver android:name=".MyBroadcastReceiver"  android:exported="true">
        <intent-filter>
            <action android:name="android.intent.action.BOOT_COMPLETED"/>
            <action android:name="android.intent.action.INPUT_METHOD_CHANGED" />
        </intent-filter>
    </receiver>
```    

2. 코드에서
```kotlin
    private const val TAG = "MyBroadcastReceiver"
    // 부팅 끝나거나 입력기 바뀌면 어떻게 처리할지 !
    class MyBroadcastReceiver : BroadcastReceiver() {

        override fun onReceive(context: Context, intent: Intent) {
            StringBuilder().apply {
                append("Action: ${intent.action}\n")
                append("URI: ${intent.toUri(Intent.URI_INTENT_SCHEME)}\n")
                toString().also { log ->
                    Log.d(TAG, log)
                    Toast.makeText(context, log, Toast.LENGTH_LONG).show()
                }
            }
        }
    }
    
```

### Context에 등록
코드상에 Broadcast receiver 생성하고 어떤 intent 받을 건지 필터 생성해서 적용
```kotlin
  val br: BroadcastReceiver = MyBroadcastReceiver()
  val filter = IntentFilter(ConnectivityManager.CONNECTIVITY_ACTION).apply {
    addAction(Intent.ACTION_AIRPLANE_MODE_CHANGED)
  }
  registerReceiver(br, filter)
  
```  



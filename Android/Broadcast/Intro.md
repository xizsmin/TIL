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
- BroadcastReceiver가 Context에 register되면 해당 context가 유효할 때까지 계속 수신 가능
    - Activity context: 해당 activity destroy 전까지, Application context: 앱 실행중이면
- 수신중지: `unregisterReceiver()` 호출
    - register/ unregister 위치 잘 선택해서 중복 등록 / 원하지 않는 상태에서 수신 안되게
    - onCreate에서 register했으면 onDestroy에서, onResume에서 등록했으면 onPause에서 등록 취소


### 프로세스 상태에 미치는 영향
- onReceive() 실행중일 때는 Foreground로 간주
- [TBD] 관리하려면?


## Broadcast 전송 (send)
### `sendOrderedBroadcast(Intent, String)`
- 한 번에 하나의 receiver에 브로드캐스트를 순차적으로 전송
- 한 receiver가 다른 receiver(먼저 받은)의 결과를 참조하는 등 순차적으로 작업이 전파될 때 유리
- 실행순서: Intent-filter의 `android:priority` 로 제어, 우선순위 같으면 임의 순서로 실행

### `sendBroadcast(Intent)`
- 순서 정의 없이 모든 receiver에 broadcast 전송 (일반)
- 효율적이나 순차 전파는 무리

### `LocalBroadcastManager.sendBroadcast()`
- 한 앱 내에서만 쓰고 싶은 broadcast
- 보안상 안전

## Permission으로 broadcast 제한
### 전송시 권한도 같이 명시
- 전송시 명시된 권한을 가진 receiver만 수신 가능

전송자:
```kotlin
    sendBroadcast(Intent("com.example.NOTIFY"), Manifest.permission.SEND_SMS)
```
수신자: 위 브로드캐스트 받으려면 권한 요청되어 있어야 함
```kotlin
    <uses-permission android:name="android.permission.SEND_SMS" />
```

### 권한 사용하여 수신
수신 측에서 권한을 설정하고, 권한 사용해야만 해당 receiver에 전송되는 broadcast send 가능

수신자:
```kotlin
<receiver android:name=".MyBroadcastReceiver"
              android:permission="android.permission.SEND_SMS">
        <intent-filter>
            <action android:name="android.intent.action.AIRPLANE_MODE"/>
        </intent-filter>
    </receiver>
    
```
또는
```kotlin
    var filter = IntentFilter(Intent.ACTION_AIRPLANE_MODE_CHANGED)
    registerReceiver(receiver, filter, Manifest.permission.SEND_SMS, null )
    
```

전송자:
```kotlin
<uses-permission android:name="android.permission.SEND_SMS"/>
    
```

# Permissions
- **목적: Android 사용자의 개인정보 보호**
- App에서 민감한 사용자 데이터(SMS, 연락처 등)나 특정 시스템 기능(카메라, 인터넷, BT, ...) 사용시 액세스 권한 요청 필요
- Permission의 보호 수준에 따라 시스템에서 자동으로 승인하거나 사용자에게 동의 요청 가능

## 권한 승인

- 필요한 권한 표시:
```xml

<manifest xmlns:android="http://schemas.android.com/apk/res/android"
          package="com.example.snazzyapp">

    <uses-permission android:name="android.permission.SEND_SMS"/>

    <application ...>
        ...
    </application>
</manifest>

```

### Dangerous permission (위험권한)
- M OS 이상 (Android 6, API 23): 설치 완료후 앱 실행시(런타임)에 사용자에게 권한 부여 요청을 팝업으로 생성
- 시스템 설정에서 권한 각각을 사용 설정/중지 가능: `SecurityException` 처리 필요
- L OS 이하 (Android 5.1.1, API 22): 앱 설치 단계에서 한꺼번에 동의 요청

### 사용자 정보 액세스 요청
- 통화기록, SMS 메시지 등 민감한 정보에 접근할 때에는 사용자에게 허용 여부 메시지를 표시

## HW 기능 관련 권한 (BT, Camera 등)

```xml
<uses-feature android:name="android.hardware.camera" android:required="false" />
```
- `android:required="false"` : 필요한데 기능 없는 상황이면 Play store 통해 설치 가능
- 이후 runtime에 `PackageManager.hasSystemFeature()` 호출, 디바이스에서 현재 기능제공 가능한 상태인지 확실히 하고 분기 처리
- `<uses-feature>` 없으면: 카메라 앱 없으면 실행 못함

## 일회성 권한
- Android 11, API 30부터는 위치, 마이크, 카메라 권한 등에 대해 **이번만 허용** 가능: 임시 일회성 권한 부여

## 권한 적용
### Activity 권한 적용
- `android:permission` -> `<activity>` : Activity 시작 가능한 사용자 제한
- `Context.startActivity()`나 `Activity.startActivityForResult()` 중에 확인, 오류시 `SecurityException` 발생

### 서비스 권한 적용
- `android:permission` -> `<service>` : Service 시작하거나 바인딩 가능한 사용자 제한
- `Context.startService()`, `Context.stopService()`, `Context.bindService()` 중에 확인, 오류시 `SecurityException` 발생


### Broadcast 권한 적용
- `android:permission` -> `<receiver>`: BroadcastReceiver에 브로드캐스트 전송 가능한 사용자 제한
- `Context.registerReceiver()`에서 Permission 넘기는 방식으로 제어 가능, `Context.sendBroadcast()` 호출시 Permission 제공 가능

### ContentProvider 권한 적용
- `android:permission` -> `<provider>`: ContentProvider 데이터에 액세스 가능한 사용자 제한
- `android:readPermission`: data read 가능한 사용자 제한 (`ContentResolver.query()`)
- `android:writePermission`: data write 가능한 사용자 제한 (`ContentResolver.insert(), update(), delete()`)





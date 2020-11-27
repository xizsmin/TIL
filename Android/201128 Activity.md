# Activity
## 개념
- App과 사용자의 상호작용을 위한 진입점 역할: (대부분의) app은 여러 Activity로 구성
- App이 UI를 그리는 Window를 제공
  - Floating 가능, fullscreen 아닐 수도 있음, 투명,...
  - **각 상태에 따른 이전 activity 상태(callback), setResult <-> onActivityResult**
  - 여러 액티비티 중 하나가 최초 앱 시작점 역할을 함: `AndroidManifest.xml => <application>`하위에 다음 내용 포함
    - 없으면 No Launcher activity found 에러 발생!
    
  
  ```xml
  <intent-filter>
     <action android:name="android.intent.action.MAIN />
     <category android:name="android.intent.category.LAUNCHER" />
  </intent-filter>                                                              
  ```


## Manifest 구성
### Activity 선언
- `AndroidManifest.xml` => `<application>` => **`<activity>`** 추가

```xml
    <manifest ... >
      <application ... >
          <activity android:name=".ExampleActivity" />
          ...
      </application ... >
      ...
    </manifest >
```

### Intent-filter 선언
- 앱이 수신할 수 있는 *Implicit* intent 선언 (Explicit intent는 무조건 대상에 전달)
- 구성요소 : **`action`, `data`, `category`**

```xml
<activity android:name="ShareActivity">
    <intent-filter>
        <action android:name="android.intent.action.SEND"/>
        <category android:name="android.intent.category.DEFAULT"/>
        <data android:mimeType="text/plain"/>
    </intent-filter>
</activity>
```
- !! 주의사항: Intent name을 알면 다른 앱에 의해 활성화될 수도 있음 -> 방지 필요


### Permission 선언
```xml
    <manifest>
    <activity android:name="...."
       android:permission=”com.google.socialapp.permission.SHARE_POST”

    />
    
```

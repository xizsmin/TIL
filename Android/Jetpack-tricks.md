## NavArgs 로 넘어온 값 파싱하기

```kotlin
// Way 1
val url = WebFragmentArgs.fromBundle(requireArguments()).webViewUrl

// Way 2
val args = WebFragmentArgs by NagArgs
val url = args.url
```

## Navigation - GlobalAction
![image](https://user-images.githubusercontent.com/57291261/143034804-1b181234-00f4-4639-96b4-2ddb1e2c0a08.png)

### 만드는 단계
1. Graph Editor에서 대상을 클릭하여 강조표시합니다.
2. 대상을 마우스 오른쪽 버튼으로 클릭하여 컨텍스트 메뉴를 표시합니다.
3. Add Action > Global을 선택합니다. 화살표()가 대상의 왼쪽에 나타납니다.
4. Text 탭을 클릭하여 XML 텍스트 뷰로 이동합니다. 전역 작업의 XML은 다음과 유사합니다.

```xml
<?xml version="1.0" encoding="utf-8"?>
<navigation xmlns:app="http://schemas.android.com/apk/res-auto"
            xmlns:tools="http://schemas.android.com/tools"
            xmlns:android="http://schemas.android.com/apk/res/android"
            android:id="@+id/main_nav"
            app:startDestination="@id/mainFragment">

  ...

  <action android:id="@+id/action_global_mainFragment"
          app:destination="@id/mainFragment"/>

</navigation>
```

### 코드에서 사용
```kotlin
viewTransactionButton.setOnClickListener { view ->
    view.findNavController().navigate(R.id.action_global_mainFragment)
}
```


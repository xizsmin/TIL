#WebView
- 웹앱 / 웹페이지만 app에서 표시하려는 경우
- 웹페이지를 Activity layout의 일부로 표시
  - **브라우저 기능 없음!**
  - 사용예시: 로그인, user agreement, user guide 등 네트워크에 접속해서 업데이트되어야 하는 데이터를 사용자 앱에 표시해야 할 때
  
- 기본 Activity에서 네트워크 요청 수행하고 레이아웃 렌더링하는 것보다 웹뷰에서 URL 표시하는 게 더 쉬움

## 설정
- `WebChromeClient` 전체화면 지원 사용 설정
  - Debugging: `onConsoleMessage`에서 `console.log()`
  
  ```kotlin
  
    val myWebView: WebView = findViewById(R.id.webview)
    myWebView.webChromeClient = object : WebChromeClient() {

        override fun onConsoleMessage(message: String, lineNumber: Int, sourceID: String) {
            Log.d("MyApplication", "$message -- From line $lineNumber of $sourceID")
        }
    }
    
  ```

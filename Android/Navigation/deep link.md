# Deep link
## Explicit deep link
- `PendingIntent` `NavDeepLinkBuilder` 사용, 사용자를 app 내의 특정 위치로 이동 
  - e.g., Notification, App widget 등의 action
- Explicit Intent를 통해 앱을 열면 task의 back stack 삭제, deep link destination으로 대체
  - 이 때 해당 destination에서 **Back button** 누르면 해당 앱을 처음부터 launching한 것처럼 navigation 동작
  
```kotlin
val pendingIntent = NavDeepLinkBuilder(context)
    .setGraph(R.navigation.nav_graph)
    .setDestination(R.id.android)
    .setArguments(args)
    .createPendingIntent()
```

## Implicit deep link
- 앱의 특정 대상을 나타내는 URI
- Intent의 `Intent.FLAG_ACTIVITY_NEW_TASK` 설정여부에 따라
  - 설정: Task back stack 삭제, deep link destination으로 교체 (explicit deep link 와 동일한 동작)
  - 미설정: **Back button** 누르면 이전 앱으로, up button 누르면 Navigation graph 내의 상위 hierarchy로
  

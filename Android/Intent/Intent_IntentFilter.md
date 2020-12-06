# Intent / Intent filter
- Intent: 메시징 객체, 다른 app component로부터 작업 요청시 사용
- **사용 사례: 액티비티/서비스 시작, 브로드캐스트**
  - 액티비티 시작: Intent를 startActivity()로 전달, 결과 수신하려면 startActivityForResult()
    - 결과 수신은 onActivityResult()
  - 서비스 시작: startService()로 Intent 전달 (서비스 설명 및 필요 데이터 등)
  - 브로드캐스트 전달: 시스템 이벤트(부팅, 충전 등)
    - sendBroadcast()나 sendOrderedBroadcast()

## 인텐트 유형
- Explicit: 시작하고자 하는 대상 (액티비티나 서비스) 이름을 명시
  - e.g., 명시적으로 새로운 액티비티 시작, 백그라운드에서 파일 다운로드 시작 등
- Implicit: 수행하고자 하는 작업이 가능한 app component들 모두 해당
  - e.g., 사진 열기: 이미지 뷰어 기능 있는 앱들 모두 표시, 공유하기: 공유 가능한 메신저 리스트 표시 등
  - **주의** 서비스 시작시에는 명시적으로 호출하도록 함 (어느 서비스가 인텐트에 응답할지 알 수 없고, 백그라운드에서 도니까 사용자도 존재를 모름)
  
## 인텐트 필터
- 해당 app component가 수신하고자 하는 인텐트 표현(manifest에 표시)
- 인텐트 필터를 선언하지 않으면 명시적으로만 호출될 수 있음


## 인텐트 빌드
- Intent가 포함하는 요소
  - Component name: 시작할 대상(액티비티, 서비스 등) 이름
    - Optional한 정보. 넣으면 Explicit, 빼면 Implicit
    - 안 넣어서 Implicit하게 되면 data나 category 등 다른 정보 기반으로 결정하는데 하나 이상의 액티비티가 응답할 수도 있음(chooser 표시해야)
    - implicit 사용 예시: 이미지 열 때 Gallery / Google photo 등 이미지뷰어 선택 가능, 공유하기 누르면 메신저 리스트...
    
  - Action: 수행할 일반적인 작업을 나타내는 문자열 (ACTION_VIEW, ACTION_SEND, ...)
  - Data: URI, 데이터의 MIME 유형 등
  - Category: 추가 정보 성격, 보통은 잘 안 씀 (CATEGORY_LAUNCHER, CATEGORY_BROWSABLE, ..)
  - Extra: key-value pair, putExtra()로 추가
  - Flag: 액티비티 시작 및 처리방법 등의 정보 ( FLAG_ACTIVITY_SINGLE_TOP, FLAG_ACTIVITY_NEW_TASK, FLAG_ACTIVITY_CLEAR_TOP, FLAG_ACTIVITY_CLEAR_TASK...)
  
- Explicit Intent: 특정 App component를 명시적으로 실행(이름 정의 필수, 나머지는 선택)
- Implicit Intent: 수행할 action을 처리할 수 있는 모든 앱 호출(선택 필요할 수 있고, 상황에 따라 사용자가 기본앱 지정할 수 있음)

- **PendingIntent** 원하는 특정 시점에 외부 앱에서의 action을 실행
  - Noti에 액션 연결시키는 경우 (메시지 클릭하면 해당 메신저앱 열기, inline reply, etc.) -> **NotificationManager**
  - 위젯에서 앱 진입시킬때 -> **HomeScreen**
  - 지정된 시간에 실행되도록 예약 가능-> **AlarmManager**
  
  
  

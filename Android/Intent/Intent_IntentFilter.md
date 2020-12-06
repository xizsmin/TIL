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
  
## 인텐트 빌드
- Intent가 포함하는 요소
  - Component 이름: 시작할 대상(액티비티, 서비스 등) 이름
    - Optional한 정보. 넣으면 Explicit, 빼면 Implicit
    - 안 넣어서 Implicit하게 되면 data나 category 등 다른 정보 기반으로 결정
    
  -     
  

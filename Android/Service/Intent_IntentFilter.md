# Intent / Intent filter
- Intent: 메시징 객체, 다른 app component로부터 작업 요청시 사용
- **사용 사례: 액티비티/서비스 시작, 브로드캐스트**
  - 액티비티 시작: Intent를 startActivity()로 전달, 결과 수신하려면 startActivityForResult()
    - 결과 수신은 onActivityResult()
  - 서비스 시작: startService()로 Intent 전달 (서비스 설명 및 필요 데이터 등)
  - 브로드캐스트 전달: 시스템 이벤트(부팅, 충전 등)
    - sendBroadcast()나 sendOrderedBroadcast()

# BLE (Bluetooth Low Energy)
- 저전력 블루투스 지원 (Jellybin~)
- 적은 데이터량 전송에 유리, 배터리 소모 낮음: 저전력 블루투스 기기와 통신

- Google beacon과 통신 (deprecated !)

## IoT
- 모바일 <-> IoT 기기 연동의 경우, 주로 IoT 기기가 Advertiser, 단말이 Scanner 역할
- 이때 IoT 기기는 Non-connectable Advertising packet을 주기적으로 보내고, 모단말이 주기적으로 scanning
- Advertising은 매우 작은 데이터(31KB 이하)를 전달할 때도 사용된다(Non-connectable하게 보낼 수 있으므로 굳이 pairing / connectiono 과정 거치지 않아도 됨)

## 주요 Concept
- **GATT** 저전력 블루투스 링크를 통해 작은 데이터 주고받는 프로토콜
- **ATT** 

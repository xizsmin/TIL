# BLE (Bluetooth Low Energy)
- 저전력 블루투스 지원 (Jellybin~)
- 적은 데이터량 전송에 유리, 배터리 소모 낮음: 저전력 블루투스 기기와 통신

- Google beacon과 통신 (deprecated !)

## IoT
- 모바일 <-> IoT 기기 연동의 경우, 주로 IoT 기기가 Advertiser, 단말이 Scanner 역할

| Mobile | IoT device|
|--------|-----------|
|Observer|Advertiser|
|Master  |  Slave    |
|Central|Peripheral|
  * Master 입장의 장치는 추후 connection 과정을 주도하므로 배터리나 컴퓨팅 성능이 상대적으로 높은 쪽으로

### Advertise mode
- IoT 기기는 Non-connectable Advertising packet을 주기적으로 보내고, 모단말이 주기적으로 scanning
- Advertising은 매우 작은 데이터(31KB 이하)를 전달할 때도 사용된다(Non-connectable하게 보낼 수 있으므로 굳이 pairing / connectiono 과정 거치지 않아도 됨)
  - Scan request / response 과정에 데이터 좀 더 달아서 확장할 수도 있음
  - !! 일방적인 broadcast: 보안에 취약 (**BLE Advertising packet은 평문이다**) cf. BLESA: 기존에 페어링된 장치가 reconnect될 때 인증이 거의 필요 없는 점을 악용
- **1:N** Broadcast 방식이기 때문에 한 번에 한 개 이상의 디바이스와 통신 가능  
  

### Connection mode
- **1:1** 양방향 / 많은 데이터 송수신
- Advertise보다 안전: 디바이스간 channel hopping 규칙을 정해놓고 통신
- **Master**: 
  - Connectable Advertising Signal을 주기적으로 스캔하다가 적절한 디바이스에 연결 요청(사용자 요청, auto-connection 등)
  - 연결 성공하면 Master에서 timing(channel hopping 규칙)을 설정하고 주기적인 데이터 교환 주도
  
- **Slave**:
  - 다른 디바이스에 연결되기 위해 Connectable Advertising signal을 주기적으로 보냄
  - Master에서 connection request 보내면 수락, connection 진행
  

## Protocol stack
Controller (Physical, Link) + Host (L2CAP, SMP, ATT, GAP, GATT) + App

### Link Layer
**Role**
- Connection 전의 역할:
  - Advertiser: Advertising packet 송신
  - Scanner: Advertising packet 스캔하는 역할
- Connection 후의 역할:
  - Master: 연결 시도, 연결 후 connection 관리
  - Slave: Master의 연결 요청을 받고 timing 규칙을 따름
  
### GAP (Generic Access Profile)
- 서로 다른 제조사의 BLE 디바이스들끼리 호환 및 통신 가능하게 하는 프로토콜
- 디바이스간 인지, data advertise, connection establishment 관련 framework

### GATT (Generic Attribute Profile)
- BLE data 교환을 관리
- 데이터 발견 및 R/W 관련한 기초 Data model 및 procedure 정의

## Communication
- Frequency hopping 규칙 통일, 같은 채널로 signal 교환



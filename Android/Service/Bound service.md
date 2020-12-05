# Binding 된 서비스
- 액티비티 등에 바인드되어 작업하고 통신함
- (일반적으로는) bind 풀리면 소멸되고 무한히 돌지 않음

## 기본 사항
- onBind() 구현 - IBinder 객체 반환

### 시작된 서비스에 바인드
![service_binding_tree_lifecycle](https://user-images.githubusercontent.com/57291261/101259363-d173fd00-376b-11eb-8bec-a81e67e05d24.png)

- 먼저 시작된 뒤에 바인드되면 바인드가 모두 풀려도 소멸 안 됨 (명시적 중단 필요)
  - e.g., 뮤직플레이어: 서비스 무한 실행 + bind 모두 필요, app 닫아도 음악이 계속 재생되므로 기본적으로 백그라운드 서비스로 구현하되 액티비티 올라올 때만 바인드되어 제어하도록 함
- 여러 클라이언트가 서비스 하나에 바인드 가능함
  - onBind()는 최초 1회만 불리고 IBinder 객체는 캐싱되어, 다음 요청하는 클라이언트에게 캐싱된 값을 전달만 해주고 onBind() 다시 호출하지는 않음
  
  
## 바인딩된 서비스 생성
- IBinder 제공하여 인터페이스 정의해야 함
### Binder class 확장
  - Local app에서만 서비스 사용하고 여러 프로세스에 걸치지 않는 경우
  - Client에서는 onServiceConnected() 콜백에서 받아서 제공된 메서드로 바인딩된 서비스 호출
### Messenger 사용
### AIDL (Android Interface Definition Language)
  - IPC: 여러 프로세스간 통신 필요할 때 (여러 app에서 서비스와 통신한다든지..)
    - 기본적으로 다른 프로세스의 메모리 영역에 접근할 수 없으니까
  - 객체를 OS가 이해 가능한 raw 유형으로 해체 후 여러 프로세스에서 marshalling
  - 서비스가 동시에 여러 요청을 처리하게 하고 싶을 때 주로 사용 (멀티스레딩 처리 가능해야)

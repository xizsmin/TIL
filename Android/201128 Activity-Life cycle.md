# Activity Life Cycle
- 사용자가 app을 실행하거나 나가고, 다시 돌아오는 등의 작업에 따라 Activity instance가 여러 상태 사이를 전환
- Activity가 이러한 상태 변화를 감지할 수 있는 callback 제공, 상태 변화에 적합한 특정 작업을 수행하도록 함
- Life cycle에 따라 callback을 잘 구현하면 방지할 수 있는 문제:

  > - User가 잠시 나갔다가 들어왔을 때 의도치 않게 데이터를 잃는 문제 (혹은 screen rotation 등)
  > - User가 사용을 중단했는데도 발생하는 Resource leak
  > - 다른 app으로 전환할 때 비정상 종료

![activity_lifecycle](https://user-images.githubusercontent.com/57291261/100474367-c560bd80-3123-11eb-98dc-f1dd868e429f.png)
--------------------------------------------

## Lifecycle Callbacks

### onCreate()
- 반드시 구현해야 함!
- 시스템이 Activity를 최초로 생성할 때 호출
- Activity life 에서 최초로 한 번만, 반드시 실행되어야 할 로직을 작성
  - `setContentView()`: User interface layout 설정
  - ViewModel 작성, list에 data binding, 뷰 생성 등
- `savedInstanceState` 파라미터(`Bundle`객체)를 받음: Activity 이전 저장 상태를 포함

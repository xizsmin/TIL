# Activity Life Cycle
- 사용자가 app을 실행하거나 나가고, 다시 돌아오는 등의 작업에 따라 Activity instance가 여러 상태 사이를 전환
- Activity가 이러한 상태 변화를 감지할 수 있는 callback 제공, 상태 변화에 적합한 특정 작업을 수행하도록 함
- Life cycle에 따라 callback을 잘 구현하면 방지할 수 있는 문제:

  > - User가 잠시 나갔다가 들어왔을 때 의도치 않게 데이터를 잃는 문제 (혹은 screen rotation 등)
  > - User가 사용을 중단했는데도 발생하는 Resource leak
  > - 다른 app으로 전환할 때 비정상 종료


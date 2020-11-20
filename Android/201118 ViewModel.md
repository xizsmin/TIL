- Activity나 Fragment 등의 UI controller들이 destroy되거나 recreate될때 (화면 내려가거나, screen rotation 등)
기본적으로는 원래 보관중이었던 데이터를 잃게 된다.
- 이런 상황에서 데이터를 복원하려면 원래는 onSavedInstanceState()에서 저장하고 싶은 데이터를 bundle에 담고
onRestoredInstanceState() (또는 onCreate())에서 전달받은 bundle로부터 해당 데이터를 추출한다(key로 식별).
- 다만 복잡한 데이터(URI, 이미지 등)는 이런 방법으로 저장/복원이 어려움.
- UI controller는 보여 주는 데에 집중해야 함. heavy한 데이터를 다루는 작업까지 맡으면 구조가 복잡해져서 설계/관리가 어려워지고,
- 액티비티 수명 주기에 사용자 데이터가 영향을 받게 된다.
- => UI와 data model를 분리할 필요성!
- app이 destroy되거나 screen rotation 발생, 네트워크 연결이 약해지는 등의 이벤트에도 사용자 데이터 유지


![1_3Kr2-5HE0TLZ4eqq8UQCkQ](https://user-images.githubusercontent.com/57291261/99828085-d3e82b80-2b9d-11eb-923b-4ea7209ebd25.png)


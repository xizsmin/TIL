- Activity나 Fragment 등의 UI controller들이 destroy되거나 recreate될때 (화면 내려가거나, screen rotation 등)
기본적으로는 원래 보관중이었던 데이터를 잃게 된다.
- 이런 상황에서 데이터를 복원하려면 원래는 onSavedInstanceState()에서 저장하고 싶은 데이터를 bundle에 담고
onRestoredInstanceState() (또는 onCreate())에서 전달받은 bundle로부터 해당 데이터를 추출한다(key로 식별).
- 다만 복잡한 데이터(URI, 이미지 등)는 이런 방법으로 저장/복원이 어려움.
- UI controller는 보여 주는 데에 집중해야 함. heavy한 데이터를 다루는 작업까지 맡으면 구조가 복잡해져서 설계/관리가 어려워진다.
- => UI와 data model를 분리할 필요성!

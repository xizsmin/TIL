# Android Lifecycle
## Scenarios
### Initial launch
- onCreate() (**NO savedInstanceState**) -> onStart() -> onResume()

### Plain destroy
- onPause() -> onStop() -> onDestroy()

### Screen Rotation
- onPause() -> onStop() -> onDestroy() -> onCreate()(**WITH savedInstanceState**) -> onStart() -> **onRestoreInstanceState()** -> onResume()

### Nav: A->B->A
![navscenario_A_B_A](https://user-images.githubusercontent.com/57291261/101992522-55436180-3cf7-11eb-964c-683f4256d4c7.PNG)

- *Each height doesn't represent the length of period*

### Nav: A->B->A (Translucent or Floating)
![navscenario_transparent_or_floating](https://user-images.githubusercontent.com/57291261/101992544-7906a780-3cf7-11eb-92cd-d409d5dd1e5a.PNG)
- onStop()은 visibility 연관
- Floating activity의 경우 `android:windowCloseOnTouchOutside`를 `true`설정하여 바깥(A) 터치시 back button으로 이전으로 돌아간 것과 같은 효과를 줄 수 있으나 생명주기는 변화 없음

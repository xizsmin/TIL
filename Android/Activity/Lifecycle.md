# Android Lifecycle
## Scenarios
### Initial launch
- onCreate() (**NO savedInstanceState**) -> onStart() -> onResume()

### Plain destroy
- onPause() -> onStop() -> onDestroy()

### Screen Rotation
- onPause() -> onStop() -> onDestroy() -> onCreate()(**WITH savedInstanceState**) -> onStart() -> **onRestoreInstanceState()** -> onResume()

### Nav: A->B->A
![navscenario_A_B_A](https://user-images.githubusercontent.com/57291261/101991766-2676bc80-3cf2-11eb-898a-31d6191fd14f.PNG)
- *Each height doesn't represent the length of period*

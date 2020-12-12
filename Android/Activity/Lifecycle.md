# Android Lifecycle
## Scenarios
### Initial launch
- onCreate() (**NO savedInstanceState**) -> onStart() -> onResume()

### Plain destroy
- onPause() -> onStop() -> onDestroy()

### Screen Rotation
- onPause() -> onStop() -> onDestroy() -> onCreate()(**WITH savedInstanceState**) -> onStart() -> **onRestoreInstanceState()** -> onResume()


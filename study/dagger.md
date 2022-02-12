## @Component
- `<package>/di/AppComponent.kt`
- Dagger에 어떤 모듈이 injection 필요한지 전달, dependency graph 생성하게 함

## @BindsInstance
- Android system에서 제공하는 요소 (e.g., `Context`) 주입이 필요할 때

## @Module, @Binds
- interface 만들어서 주입할 때 뭘 써야 하는지
- return type: interface 이름
- parameter: interface implement하는 class 이름
- e.g., XXX interface 제공할 때 FooXXX를 이용해서 object 만들어 제공해라:

```kotlin
// XXXModule.kt: Dagger module
@Module
abstract class XXXModule {
  @Binds
  abstract fun provideXXX(xxx: FooXXX): XXX
}

// FooXXX.kt:
class FooXXX @Inject constructor(context: Context): XXX { ... }

// AppComponent.kt:
@Component(modules = [XXXModule::class])
interface AppComponent {
  fun inject(activity: YYYActivity)
  
  @Component.Factory
  interface Factory {
    fun create(@BindsInstance context: Context): AppComponent
  }
}
```

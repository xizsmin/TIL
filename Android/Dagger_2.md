# Dagger 2 for Android



![LoginActivity는 LoginViewModel에 종속되며, 이 클래스는 다시 UserRepository에 종속되고, 이 클래스는 다시 UserLocalDataSource 및 UserRemoteDataSource에 종속되며, 이는 다시 Retrofit에 종속됩니다.](https://developer.android.com/images/training/dependency-injection/4-application-graph.png)

## 기본설정

- Android에서는 일반적으로 Dagger graph를 **Application class**에 생성함 - 앱 lifecycle에 연결

  - Application class: 안드로이드 앱의 base class
  - 앱 실행되면 최초로 (액티비티 등 다른 컴포넌트들보다) instantiate됨

- 그래프를 생성하는 인터페이스: **`@Component`**

  - 생성하고자 하는 곳 (주로 custom Application class) 에서 **`ApplicationComponent`**로 호출함

  - `@Component` 인터페이스에서는 dagger의 의존성 그래프로부터 얻고자 하는 object들을, 해당 object type을 반환하는 함수로 정의해 놓는다.

    ```kotlin
    // Definition of the Application graph
    @Component
    interface ApplicationComponent {
        ...
        fun repository(): UserRepository
        ...
    }
    
    // appComponent lives in the Application class to share its lifecycle
    class MyApplication: Application() {
        // Reference to the application graph that is used across the whole app
        val appComponent = DaggerApplicationComponent.create()
    }
    ```



## Android Framework에서 제공하는 클래스의 경우 (e.g., Activity, Fragment) 

- Activity나 Fragment처럼 시스템에서 instantiate하는 안드로이드 프레임워크 클래스들은 Dagger에서 만들 수 없으므로 아래와 같은 constructor injection은 불가

  - ```kotlin
    // @Inject lets Dagger know how to create instances of this object
    class UserRepository @Inject constructor(
        private val localDataSource: UserLocalDataSource,
        private val remoteDataSource: UserRemoteDataSource
    ) { ... }
    
    // @Inject lets Dagger know how to create instances of these objects
    class UserLocalDataSource @Inject constructor() { ... }
    class UserRemoteDataSource @Inject constructor() { ... }
    
    ```

- 대신 **`@Inject` ** 어노테이션으로 **Field injection**

  - ```kotlin
    class LoginActivity: Activity() {
        // You want Dagger to provide an instance of LoginViewModel from the graph
        // Following is NOT an AAC ViewModel; just a regular class
        @Inject lateinit var loginViewModel: LoginViewModel
    }
    ```

  

  - 이 경우 Dagger는 `LoginActivity`에 `LoginViewModel` 이 필요하다는 것을 알고 있어야 함 (i.e., `LoginActivity` 는 Dagger의 의존성 그래프에 접근 필요) -> Component interface에 명시함

  - ```kotlin
    @Component
    interface ApplicationComponent {
        // This tells Dagger that LoginActivity requests injection so the graph needs to
        // satisfy all the dependencies of the fields that LoginActivity is requesting.
        fun inject(activity: LoginActivity)
    }
    ```

- 그리고 Activity의 `onCreate()`에 코드 추가 (`super.onCreate()` 호출 전에!)

  - ```kotlin
    class LoginActivity: Activity() {
        // You want Dagger to provide an instance of LoginViewModel from the graph
        @Inject lateinit var loginViewModel: LoginViewModel
    
        override fun onCreate(savedInstanceState: Bundle?) {
            // Make Dagger instantiate @Inject fields in LoginActivity
            (applicationContext as MyApplication).appComponent.inject(this)
            // Now loginViewModel is available
    
            super.onCreate(savedInstanceState)
        }
    }
    
    // @Inject tells Dagger how to create instances of LoginViewModel
    class LoginViewModel @Inject constructor(
        private val userRepository: UserRepository
    ) { ... }
    ```



## Dagger Modules

- ```kotlin
  class UserRepository @Inject constructor(
      private val localDataSource: UserLocalDataSource,
      private val remoteDataSource: UserRemoteDataSource
  ) { ... }
  
  class UserLocalDataSource @Inject constructor() { ... }
  class UserRemoteDataSource @Inject constructor(
      private val loginService: LoginRetrofitService
  ) { ... }
  ```

- 여기서 `UserRemoteDataSource` 생성을 위해서는 `LoginRetrofitService` 제공이 필요함

  - ```kotlin
    // @Module informs Dagger that this class is a Dagger Module
    @Module
    class NetworkModule {
    
        // @Provides tell Dagger how to create instances of the type that this function
        // returns (i.e. LoginRetrofitService).
        // Function parameters are the dependencies of this type.
        @Provides
        fun provideLoginRetrofitService(): LoginRetrofitService {
            // Whenever Dagger needs to provide an instance of type LoginRetrofitService,
            // this code (the one inside the @Provides method) is run.
            return Retrofit.Builder()
                    .baseUrl("https://example.com")
                    .build()
                    .create(LoginService::class.java)
        }
    }
    
    
    // The "modules" attribute in the @Component annotation tells Dagger what Modules
    // to include when building the graph
    @Component(modules = [NetworkModule::class])
    interface ApplicationComponent {
        ...
        fun repository(): UserRepository
        ...
    }
    
    ```


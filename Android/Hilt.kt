
// root/build.gradle
buildscript {
    ...
    ext.hilt_version = '2.28-alpha'
    dependencies {
        ...
        classpath "com.google.dagger:hilt-android-gradle-plugin:$hilt_version"
    }
}

// app/build.gradle
...
apply plugin: 'kotlin-kapt'
apply plugin: 'dagger.hilt.android.plugin'

android {
    ...
}

...
dependencies {
    ...
    implementation "com.google.dagger:hilt-android:$hilt_version"
    kapt "com.google.dagger:hilt-android-compiler:$hilt_version"
}


@HiltAndroidApp
class FooApplication: Application() {}

// Entrypoint: Fragment, Activity, View, Service, BroadcastReceiver
@AndroidEntryPoint
class FooFragment : Fragment() {

    @Inject lateinit var logger: LoggerLocalDataSource
    @Inject lateinit var dateFormatter: DateFormatter

    ...
}

@Singleton
class LoggerLocalDataSource @Inject constructor(private val logDao: LogDao) {
    ...
}

package com.example.android.hilt.di

@InstallIn(ApplicationComponent::class)
@Module
object DatabaseModule {
  
    @Provides
    @Singleton
    fun provideDatabase(@ApplicationContext appContext: Context): AppDatabase {
        return Room.databaseBuilder(
            appContext,
            AppDatabase::class.java,
            "logging.db"
        ).build()
    }
    
    @Provides
    fun provideLogDao(database: AppDatabase): LogDao {
        return database.logDao()
    }
}

@AndroidEntryPoint
class MainActivity: AppCompatActivity() { ... }



@InstallIn(ActivityComponent::class)
@Module
abstract class NavigationModule {
    // Binds: for interface
    @Binds
    abstract fun bindNavigator(impl: AppNavigatorImpl): AppNavigator
}


class AppNavigatorImpl @Inject constructor(
    private val activity: FragmentActivity
) : AppNavigator {
    ...
}


@AndroidEntryPoint
class MainActivity : AppCompatActivity() {

    @Inject lateinit var navigator: AppNavigator

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        if (savedInstanceState == null) {
            navigator.navigateTo(Screens.BUTTONS)
        }
    }

    ...
}





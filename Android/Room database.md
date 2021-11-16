# Room database
- SQLite 추상화
- 직접 sql 쿼리 날리는 대신 인터페이스 사용

![image](https://user-images.githubusercontent.com/57291261/141995047-379b50f4-a0b6-406b-905f-bc318403fa8a.png)


![image](https://user-images.githubusercontent.com/57291261/141994990-06b1250e-c9a6-4dc9-a9fb-35b30c24d4d4.png)

## 필요 요소
1. Data class 정의 (Entity)
```kotlin
import androidx.room.ColumnInfo
import androidx.room.Entity
import androidx.room.PrimaryKey

@Entity(tableName = "daily_sleep_quality_table")
data class SleepNight(
       @PrimaryKey(autoGenerate = true)
       var nightId: Long = 0L,

       @ColumnInfo(name = "start_time_milli")
       val startTimeMilli: Long = System.currentTimeMillis(),

       @ColumnInfo(name = "end_time_milli")
       var endTimeMilli: Long = startTimeMilli,

       @ColumnInfo(name = "quality_rating")
       var sleepQuality: Int = -1
)
```

2. 인터페이스 정의 (쿼리)
- Room은 기본적으로 Dispatchers.IO를 사용
```kotlin
@Dao
interface SleepDatabaseDao {
    @Insert
    suspend fun insert(night: SleepNight)

    @Update
    suspend fun update(night: SleepNight)

    @Query("SELECT * from daily_sleep_quality_table WHERE nightId = :key")
    suspend fun get(key: Long): SleepNight?

    @Query("DELETE from daily_sleep_quality_table")
    suspend fun clear()

    @Query("SELECT * from daily_sleep_quality_table ORDER BY nightId DESC LIMIT 1")
    suspend fun getTonight(): SleepNight?

    @Query("SELECT * from daily_sleep_quality_table ORDER BY nightId DESC")
    fun getAllNights(): LiveData<List<SleepNight>>
}

//...

// Dao 사용예시
suspend fun insertNight() {
    db.insert(SleepNight())
}

fun workWithNights() {
    viewModelScope.launch { insertNight() }
}
```


3. DB 생성
```kotlin
@Database(entities = [SleepNight::class], version = 1, exportSchema = false)
abstract class SleepDatabase : RoomDatabase() {

   abstract val sleepDatabaseDao: SleepDatabaseDao

   companion object {

       @Volatile
       private var INSTANCE: SleepDatabase? = null

       fun getInstance(context: Context): SleepDatabase {
           synchronized(this) {
               var instance = INSTANCE

               if (instance == null) {
                   instance = Room.databaseBuilder(
                           context.applicationContext,
                           SleepDatabase::class.java,
                           "sleep_history_database"
                   )
                           .fallbackToDestructiveMigration()
                           .build()
                   INSTANCE = instance
               }
               return instance
           }
       }
   }
}
```

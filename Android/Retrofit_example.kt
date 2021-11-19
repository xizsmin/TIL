// 1. Define models
data class ResponseVO(var id: Long, var dataList: List<ItemVO>)
data class ItemVO(var id: Long, var title: String, var contents: String)

// 2. Define Retrofit builder
class AppApplication: Application() {
	companion object {
		fun apiService(): RetrofitService = 
					Retrofit.Builder()
						.baseUrl("https://api.com")
						.addConverterFactory(GsonConverterFactory.create())
						.build()
						.create(RetrofitService::class.java)
	}
}

// 3. Prepare interface
interface RetrofitService {
	@GET("/v2/everything")
	fun retrieveData(
		@Query("q") q: String,
		@Query("size") size: Int
		): Call<ResponseVO>
}

// 4. Write a wrapper function
fun retriveData(query: String, callback: Callback<ResponseVO>) {
	AppApplication.apiService().retrieveData(q=query, size=10).enqueue(callback)
}

// 5. Call the function where(mostly in ViewModel) you'd like to retrieve data, along with callback definition
//...
	retrieveData("queryText", object: Callback<ResponseVO> {
		override fun onResponse(call: Call<ResponseVO>, response: Response<ResponseVO>) {
			// You will do something with response.body()
		}
		
		override fun onFailure(call: Call<ResponseVO>, t: Throwable) {
			// Exception handling?
		}
	})
//...


	

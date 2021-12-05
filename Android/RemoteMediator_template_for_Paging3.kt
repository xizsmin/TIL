// DummyRemoteMediator.kt
// 

@OptIn(ExperimentalPagingApi::class)
class DummyRemoteMediator(
    private val keyword: String,
    private val service: RetrofitService,
    private val database: DummyDatabase
): RemoteMediator<Int, DummyItemEntity>()
{

    override suspend fun load(loadType: LoadType, state: PagingState<Int, DummyItemEntity>): MediatorResult {
        
        val page = when (loadType) {
            LoadType.REFRESH -> 0
            LoadType.PREPEND -> {
                val remoteKeys = getRemoteKeyForFirstItem(state)
                val prevKey = remoteKeys?.prevKey
                if (prevKey == null) {
                    return MediatorResult.Success(endOfPaginationReached = remoteKeys != null)
                }
                prevKey
            }
            LoadType.APPEND -> {
                val remoteKeys = getRemoteKeyForLastItem(state)
                val nextKey = remoteKeys?.nextKey
                if (nextKey == null) {
                    return MediatorResult.Success(endOfPaginationReached = remoteKeys != null)
                }
                nextKey
            }
        }
        

        try {
       
            val apiResponse: ApiResponseVO = service.getRequestResult(param)      // Retrofit API request

            val data = apiResponse.body

            val endOfPaginationReached = data?.isEmpty() ?: true
            database.withTransaction {
                if (loadType == LoadType.REFRESH) {
                    database.remoteKeysDao().clearRemoteKeys()
                    database.dummyDatabaseDao().clear()
                }

                val prevKey = if (page == 1) null else page - 1
                val nextKey = if (endOfPaginationReached) null else page + 1
                val keys = data.map {
                    RemoteKeys(
                        repoId = id,
                        prevKey = prevKey,
                        nextKey = nextKey
                    )
                }
                database.remoteKeysDao().insertAll(keys!!)
                database.dummyDatabaseDao().insertAll(data.map { DummyItemEntity(id, name) } )    // convert response body to entity format here if needed.

            }

            return MediatorResult.Success(endOfPaginationReached = endOfPaginationReached)
        } catch (exception: Exception) {
            return MediatorResult.Error(exception)
        }
    }

    private suspend fun getRemoteKeyForFirstItem(state: PagingState<Int, DummyItemEntity>): RemoteKeys? {

        return state.pages.firstOrNull { it.data.isNotEmpty() }?.data?.firstOrNull()
            ?.let { item -> database.remoteKeysDao().remoteKeysRepoId(item.id) }
    }
    
    private suspend fun getRemoteKeyForLastItem(state: PagingState<Int, DummyItemEntity>): RemoteKeys? {

        return state.pages.lastOrNull() { it.data.isNotEmpty() }?.data?.lastOrNull()
            ?.let { item -> database.remoteKeysDao().remoteKeysRepoId(item.id) }
    }
}



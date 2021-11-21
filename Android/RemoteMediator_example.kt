package com.example.android.a2ndandroidmission.paging

import android.util.Log
import androidx.paging.ExperimentalPagingApi
import androidx.paging.LoadType
import androidx.paging.PagingState
import androidx.paging.RemoteMediator
import androidx.room.withTransaction
import com.example.android.a2ndandroidmission.database.NewsDatabase
import com.example.android.a2ndandroidmission.database.NewsEntity
import com.example.android.a2ndandroidmission.database.RemoteKeys
import com.example.android.a2ndandroidmission.retrofit.RetrofitService
import java.lang.Exception


@OptIn(ExperimentalPagingApi::class)
class NewsRemoteMediator(
    private val query: String,
    private val service: RetrofitService,
    private val database: NewsDatabase
): RemoteMediator<Int, NewsEntity>()
{

    override suspend fun load(loadType: LoadType, state: PagingState<Int, NewsEntity>): MediatorResult {
        val page = when (loadType) {
            LoadType.REFRESH -> {
                Log.d("!!!test!!!", "loadtype REFRESH")
                database.remoteKeysDao().clearRemoteKeys()
                database.newsDatabaseDao.clear()
                0
            }
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
            val apiResponse = service.newsList(
                q = query,
                apiKey = RetrofitService.API_KEY,
                page = 1,
                pageSize = 20)


            val articles = apiResponse.articles
            val endOfPaginationReached = articles.isEmpty()
            database.withTransaction {
                if (loadType == LoadType.REFRESH) {
                    database.remoteKeysDao().clearRemoteKeys()
                    database.newsDatabaseDao.clear()
                }
                val prevKey = if (page == 1) null else page - 1
                val nextKey = if (endOfPaginationReached) null else page + 1
                val keys = articles.map {
                    RemoteKeys(repoId = it.id, prevKey = prevKey, nextKey = nextKey)
                }
                database.remoteKeysDao().insertAll(keys)
                database.newsDatabaseDao.insertAllNews(articles)
            }
            return MediatorResult.Success(endOfPaginationReached = endOfPaginationReached)
        } catch (exception: Exception) {
            return MediatorResult.Error(exception)
        }
    }

    private suspend fun getRemoteKeyForFirstItem(state: PagingState<Int, NewsEntity>): RemoteKeys? {

        return state.pages.firstOrNull { it.data.isNotEmpty() }?.data?.firstOrNull()
            ?.let { news -> database.remoteKeysDao().remoteKeysRepoId(news.id) }
    }
    private suspend fun getRemoteKeyForLastItem(state: PagingState<Int, NewsEntity>): RemoteKeys? {

        return state.pages.lastOrNull() { it.data.isNotEmpty() }?.data?.lastOrNull()
            ?.let { news -> database.remoteKeysDao().remoteKeysRepoId(news.id) }
    }
}

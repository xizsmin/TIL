# Paging 3.0
- 데이터를 가져올 때 일정한 chunk로 나눠서 로딩(성능, 메모리, 비용 절감)
- Paging3 라이브러리는 Jetpack 컴포넌트와 연동하기 쉽도록 설계

## Paging library components
- `PagingData` 
  - 페이징되어 로딩되는 데이터
  - 한번 리프레시될 때마다 새로 받아오는 단위
  - `PagingData<EntityClassName>`

- `PagingSource`
  - 로드하는 데이터를 `PagingData` 스트림으로 변경

- `Pager.flow`
  - `Flow<PagingData>` 생성
  - `PagingSource` 생성을 위한 `PagingConfig` 필요
  - `PagingConfig` 필요

- `PagingDataAdapter`
  - `PagingData`를 `RecyclerView`로 표현하기 위한 `RecyclerView.Adapter`
  - Kotlin `Flow`, `LiveData`, RxJava `Flowable` 또는 `Observable`로 구현 가능
  - `PagingData` loading event에 대한 callback

- `RemoteMediator`
  - 받아온 데이터를 끝까지 읽는 시점에 새로 네트워크나 DB로부터 로딩해옴
  - Experimental


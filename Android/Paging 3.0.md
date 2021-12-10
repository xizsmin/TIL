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
  - `PagingConfig` :
    - pageSize(필수 매개변수) : 각 페이지에 로드할 데이터 수를 가리킨다.
    - enablePlaceholders : Placeholder 사용 여부
    - maxSize : 기본적으로 모든 페이지를 메모리에 유지한다. 메모리 낭비 등을 해결하기 위해서 설정할 수 있다. 너무 작게 설정하면 부하가 걸림

- `PagingDataAdapter`
  - `PagingData`를 `RecyclerView`로 표현하기 위한 `RecyclerView.Adapter`
  - Kotlin `Flow`, `LiveData`, RxJava `Flowable` 또는 `Observable`로 구현 가능
  - `PagingData` loading event에 대한 callback

- `RemoteMediator`
  - 받아온 데이터를 끝까지 읽는 시점에 새로 네트워크나 DB로부터 로딩해옴
  - Experimental


## 참고 (TBD)
- 여러 번 검색했을 때 이전 검색결과와 현재 결과가 섞이는 현상 (이전 검색내용까지 페이징이 불필요하게 받아오는 경우):
- remoteKey에 키워드를 추가해서 키워드별로 페이징하도록?

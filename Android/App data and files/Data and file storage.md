# 개요
앱 데이터 저장 장소:
- **App별 storage**: Storage 내의 전용 directory (민감정보는 내부 스토리지에)
- **Shared storage**: 다른 앱과 공유할 파일 저장
- **Preferences**: Private primitive data의 key-value pair
- **DB**: Room persistence library 사용, structured data 사용
  - SQLite도 있...
  
  
Contents | Access | Permission | 다른 앱에서 access 가능? | App 제거시 삭제여부
---------|--------|------------|-------------------------|-------------------|
앱별 파일(앱 전용) | 내부 저장소: `getFilesDir()`, `getCacheDir()` </br> 외부 저장소: `getExternalFilesDir()`, `getExternalCacheDir()` | 내부: 필요X, 외부: Kitkat 이후 필요X | 내부: X, 외부: O | Yes
미디어(공유 가능한 미디어 파일) | MediaStore API | P OS (Android 9, API 28)이하에서 모든 파일에 권한필요 </br> Q부터는 다른 앱의 파일 액세스에 대해서만 **READ_EXTERNAL_STORAGE** or **WRITE_EXTERNAL_STORAGE** | Yes (with **READ_EXTERNAL_STORAGE**) |  Yes
기타 파일(Shareable, including downloaded) | Storage Access Framework | X | Yes (through the system file picker) | No
Preferences | Key-value pair | SharedPreference (deprecated?) </br> Jetpack library | X | No | Yes
DB | structrued data | Room persistence library (SQLite....) | X | No | Yes

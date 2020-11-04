# Singleton
- 인스턴스가 1개만 생성되어야(존재해야) 하는 경우에 사용
- 최초 1회만 메모리를 할당(static)
- 생성자 호출을 막거나, 호출되더라도 기존 instance(최초에 생성한 객체)를 반환

## 사용이유
- 설정파일, 로거 등 객체가 여러개 생성되어 서로 다른 값을 가지면 안 되는 경우
- 데이터 공유에 유리
- 메모리 절약 가능

```java

public class SingletonClass {
    private SingletonClass() {}
    
    private static class InnerSingletonClass {
        private static final SingletonClass instance = new SingletonClass();
    }
    
    public static SingletonClass getInstance() {
        return InnerSingletonClass.instance;
    }
}

```

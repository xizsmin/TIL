# Singleton
- 인스턴스가 1개만 생성되어야(존재해야) 하는 경우에 사용
- 최초 1회만 메모리를 할당(static)
- 생성자 호출을 막거나, 호출되더라도 기존 instance(최초에 생성한 객체)를 반환
- Java의 경우 class loading time에 초기화하는 방식 / run-time(최초로 instance 얻을 때 등)시 초기화 방식 등

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

## 주의사항
- 과도하게 사용할 경우 객체지향성 저해, 유지보수 어려워질 수 있음
- thread-safety 신경쓸 것 (위처럼 lazyholder, thread-safe 방식으로 구현하는 등)

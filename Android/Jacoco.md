# Jacoco

- Java 코드의 test coverage를 측정하는 library (in Java VM based environments)
- 정적 분석 툴

## Features
- 명령어(C0), 브랜치(C1), lines, methods, types, 순환 복잡도 등의 커버리지 분석
- Java bytecode 기반으로 동작 (소스코드 없이도 테스트 가능)
- Report formats supported: HTML, XML, CSV

### 설정
- build.gradle (app)
```gradle
apply plugin: 'jacoco'

jacoco {
	toolVersion "0.8.5"
  
  // default: "${project.reporting.baseDir}/jacoco"
  reportsDir = file("$buildDir/customJacocoReportDir")
} 
```

- Enable Coverage
```gradle
android {
  // ...
  buildTypes {
    debug {
      testCoverageEnabled jacocoEnabled.toBoolean()   // 변수로 선택 가능
    }
    release {
    testCoverageEnabled ㅅ겯
    }
  }
}
```

- Enable Unit Test
```gradle
    testOptions {
        unitTests {
            includeAndroidResources = true
            returnDefaultValues = true
        }
    }
```


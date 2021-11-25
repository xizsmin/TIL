# Clean Architecture
![image](https://user-images.githubusercontent.com/57291261/143443963-33c7daaf-67dc-4a5e-8e5c-7d0274152b09.png)
- Dependency rule 에 따라, 의존성이 outer -> inner로
- Domain -> Entities, Use cases
- Adapter -> Domain과 Infrastructure 경계

### Entity
- 핵심 business rule
- 자신 외 다른 layer에 속한 컴포넌트들을 몰라야 됨

### Use cases
- 특정 app에 대한 business rule
- 앱의 행위 결정
- Entity에 의존
- Outer layer에서 사용할 수 있는 abstract class/interface 정의

### Adapters
- Domain <-> Infrastructure 매개
- UI로부터 오는 데이터를 Use cases / Entity 포맷으로 변경하거나
- Use cases/Entity로부터 받아서 UI에 표시하거나 db에 저장하기 쉬운 형태로
- MVC 모두 여기 속함

### Infrastructure
- I/O components (UI, DB, frameworks, devices..)

## 의존성 역전의 원칙
- 제어의 흐름은 원의 inner -> outer로 향하게 될 수 있는데 이것을 막아야 함.
- 고수준의 정책이 저수준을 참고하는 위치에 인터페이스를 두고, 저수준의 component가 인터페이스를 구현하고 고수준 Layer에서 이를 참조


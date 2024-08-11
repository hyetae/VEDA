## 4. Qt의 레이아웃

### QWidget의 위젯 배치/화면 구성

- 위치 관련 메소드는 윈도우 프레임에 영향 o
- 크기 관련 메소드는 윈도우 프레임에 영향 x

### 좌표계

![computer_coordinates](https://github.com/user-attachments/assets/6fee8934-2a2f-4892-bbac-856559c8f964)

[ 출처 | [https://learn365project.com/2015/08/01/why-do-computer-coordinates-start-from-the-upper-left-corner/](https://learn365project.com/2015/08/01/why-do-computer-coordinates-start-from-the-upper-left-corner/) ]

- Qr에서 좌표계는 이차원 평면 구조로, 왼쪽 제일 위가 기준점
- x축→, y축↓
- 모니터: 픽셀 단위, 프린터: 포인트 단위
- 위젯의 좌표는 부모 윈도우와 전체 화면에서 다름

### 레이아웃

- 위젯들의 좌표를 계산해서 하드코딩 → 시간 많이 소요
    
    → 레이아웃 매니저로 위젯 정렬
    
- 마진과 간격을 고려해 코드 작성
- QWidget
    - 최대.최소 크기, 권장 크기 등

### 배치

상속이미지

- 컨테이너 위젯
    - 위젯들을 하나의 그룹으로 묶을 때 사용 → 가독성 향상
    - QFrame 클래스 상속 (QGroupBox, QTabWidget은 QWidget 상속)

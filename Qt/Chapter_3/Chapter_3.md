## 3. Qt의 기본 위젯

### 위젯

![Beginner-Class-Hierarchy](https://github.com/user-attachments/assets/f276eb7c-8be5-4a84-a525-17b5c15ba272)

[ 출처 | [https://wiki.qt.io/Qt_for_Beginners](https://wiki.qt.io/Qt_for_Beginners) ]

- 사용자와의 의사소통을 위해 사용하는 버튼, 메시지 박스 같은 요소
- Qt의 위젯들은 QWidget 클래스 상속
- input과 display로 용도 구분

### Display 위젯

- QFrame → QLCDNumber, QLabel
- QWidget → QProgressBar
- QTextEdit → QTextBrowser

### 버튼 위젯

- 버튼은 모두 QAbstractionButton 클래스 상속
    - 버튼이 가지는 기본적인 기능을 구현한 추상 클래스
    - autoRepeat 속성: 버튼을 누르고 있으면 주기적으로 시그널 발생
    - 토글과 푸시 버튼 모두 제공
- 라디오 버튼: 한 번에 하나의 옵션
- 체크 박스: 동시에 단일 혹은 여러 옵션

### 범위 조정 위젯

- 숫자로 되어 있는 범위 내의 값 입력 및 표시
- 기본값 범위: 0 ~ 99
- 원형 순환: setWrapping()

### 문자열 입력 위젯

- QString 형으로 문자열 사용

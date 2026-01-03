# 🚀 HoROS: Mini-ROS2 Pub/Sub Engine
Pub/Sub 통신 구조를 C++17로 직접 구현하며 학습하는 로보틱스 미들웨어 엔진입니다.

## 1. 프로젝트 개요 (Overview)

ROS2의 rclcpp API 뒤에서 일어나는 토픽 등록, 데이터 배분, 그리고 비동기 콜백 실행의 흐름을 이해하는 것을 목표로 합니다. "발행자와 구독자는 서로를 몰라도 데이터(Topic)로 연결된다"는 데이터 중심(Data-centric) 설계 철학을 바탕으로 합니다.

## 2. 주요 클래스 및 기능 특징

### 📦 Data Layer

- `IntMessage`: 가장 기초적인 정수형 데이터(int data)를 담고 있는 구조체입니다.

### ⚙️ Middleware Layer

- TopicRegistry:

    - `std::map<std::string, std::vector<Callback>>`을 통해 토픽별 구독자를 관리합니다.

    - `set_executor()`를 통해 비동기 실행 모드를 활성화할 수 있습니다.

- Executor:

    - Task Queue: 발행된 메시지에 따른 콜백 작업을 큐에 쌓습니다.

    - Worker Thread: std::thread를 활용하여 메인 루프를 방해하지 않고 배경에서 작업을 처리합니다.

    - `std::condition_variable`을 사용하여 불필요한 CPU 점유를 방지합니다.

### 🤖 Participant Layer

- `Node`:

    - 실제 ROS2 스타일의 create_publisher, create_subscription 인터페이스를 제공합니다.

    - 노드 이름을 소유하며 통신 엔드포인트의 관리 주체가 됩니다.

- `Publisher`:

    - 특정 토픽으로 메시지를 전달하는 역할을 캡슐화합니다.

## 3. How To Run

### Build

```Bash
mkdir build && cd build
cmake ..
make
```

### Run

```Bash
./horos_demo
```

### Example

```Bash
[Node : talker] has been initialized.
[Node : listener] has been initialized.
[Topic : chatter] Publisher sent: 100
[Main] Publisher call is finished immediately!
 -> [Listener Node] Started Processing: 100
 -> [Listener Node] Finished Processing: 100
```


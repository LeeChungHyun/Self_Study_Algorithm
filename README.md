# Self_Study_Algorithm
감 잃지 않기 위한 나의 Toy Project...겸사겸사...시간 날때마다..
```
Focus --> 어떻게 하면 논.리.적이고 효.율.적으로 짜볼까?!
```

```
1. 주소록 toy project 프로젝트

  12.02 = 일반적인 스택 자료구조 + Binary파일을 Load & Save하는 모듈로 만들어 봄
  12.04 = CUI설계 + Arrange/ShowAll 할 시, 10개씩 출력하도록 설계
  12.20 = Heap을 이용한 동적배열 할당으로 설계헤봄 + Create & Destroy으로 동적배열 할당 및 해제
  01.04 = Binary파일을 Load & Save하는 모듈로 설계 + Heap을 이용한 CUI설계(동적배열 할당 및 해제)
  01.08 = MFC를 이용한 GUI프로그램(MSDN활용)
          특징: 닫기 클릭시 자동으로 bin파일 저장 + 찾기 클릭시 찾기에 대한 해당 윈도우 생성(FindingForm)
  01.23 = Array 라이브러리를 이용한 Heap 기반 동적할당 설계 및 테스트
  [깃헙](https://github.com/)
```

```
2. 단어장 toy project 프로젝트

  2.1. 일반적인 스택 자료구조 + Binary파일을 Load & Save하는 모듈로 만들어 봄
  2.2. CUI설계 + Arrange/ShowAll 할 시, 10개씩 출력하도록 설계
  2.3. Heap을 이용한 동적배열 할당으로 설계헤봄 + Create & Destroy으로 동적배열 할당 및 해제
  2.4. Binary파일을 Load & Save하는 모듈로 설계 + Heap을 이용한 CUI설계(동적배열 할당 및 해제)
  2.5. MFC를 이용한 GUI프로그램(MSDN활용)
       특징: 닫기 클릭시 자동으로 bin파일 저장 + 찾기 클릭시 찾기에 대한 해당 윈도우 생성(FindingForm)
```

```
3. Array Library 설계 프로젝트

  3.1. CREATE

  3.2. UPDATE
    -Insert(front/rear)
    -Delete(front/rear)
    -Clear
    -Modify

  3.3. QUERY
    -LinearSearch(unique/duplicate)
    -BinarySearch(unique/duplicate)
    -SelectionSort
    -BubbleSort
    -InsertionSort
    -MergeSort

  3.4. DESTROY
```

```
4. BusinessCardHolder 프로젝트

  4.1. LinkedList 기반 명함 관리 프로그램(MFC포함)
    4.1.1. 주요 기능
        -꽂기(PutIn)
          -->같은 상호 이름을 입력시 직전에 입력된 회사 필드들이 나오도록 함
        -들어내기(PutOut)
          -->닫기 클릭시, 다시 끼우기에 대한 메세지 박스 나오도록 설계
        -찾기(Find)
        -정리하기(Arrange)
        -First, Next, Previous, Last
        
  4.2. File Processing(Load/Save)기능 추가
  
  4.3. LinkedList 라이브러리를 활용한 명함 관리 프로그램(ApplyLinkedList)
    4.3.1. 정리하기(Arrange)를 제외한 기능들은 기존과 동일
  
```

```
5. WordCardHolder 프로젝트

  5.1. LinkedList 기반 명함 관리 프로그램(MFC포함)
    5.1.1 주요 기능
      -꽂기(PutIn)
      -들어내기(PutOut)
        -->닫기 클릭시, 다시 끼우기에 대한 메세지 박스 나오도록 설계
      -찾기(Find)
        --> Radio Button에 대한 event 처리 추가
      -정리하기(Arrange)
      -외우기(Memorize)
        --> 플래시 카드 식으로 외우기
        --> 찜하기 기능 추가(찜한 단어로 자동이동)
      -찜한 단어(Keep)
        --> 찜한 단어가 없을 경우 알림 메세지 박스 출력
        --> 찜한 단어가 있을 경우 되돌리기 기능으로 메인 윈도우로 이동
      -테스트(Test)
        --> 메인 윈도우에 대한 단어들로 테스트
        --> 정답을 쓰고 제출하기 버튼 클릭한다 
        --> 틀릴 시, 정답을 보여주고 다시 푼다
      -First, Next, Previous, Last
      
    5.1.2 추가 기능
      -단어가 없을 시 없다는 메세지 출력
      
   5.2. File Processing(Load/Save)기능과 찜한 단어만의 File Processing(KeepCardLoad/KeepCardSave)기능 추가

   5.3. LinkedList 라이브러리를 활용한 명함 관리 프로그램(ApplyLinkedList)
    5.3.1. 정리하기(Arrange)를 제외한 기능들은 기존과 동일
    
```

```
6. LinkedList Library 설계 프로젝트

  6.1. CREATE(연결리스트 생성)

  6.2. UPDATE
    6.2.1. INSERT
    -INSERT_BEFORE(특정 노드 앞에 삽입)
    -INSERT_AFTER(특정 노드 뒤에 삽입)
    -APPEND_FROM_HEAD(맨 앞 노드 삽입)
    -APPEND_FROM_TAIL(맨 뒤 노드 삽입)
    
    6.2.2. DELETE
    -DELETE(특정 노드 삭제)
    -DELETE_FROM_HEAD(맨 앞 노드 삭제)
    -DELETE_FROM_TAIL(맨 뒤 노드 삭제)
    -DELETE_ALL_ITEMS(전체 노드 삭제)
    
  6.3. QUERY
    6.3.1.SEARCH
    -LINEARSEARCH_UNIQUE(단수 노드 탐색)
    -LINEARSEARCH_DUPLICATE(복수 노드 탐색)
    
    6.3.2. ITERATION
    -FIRST
    -NEXT
    -PREVIOUS
    -LAST
    -MOVE(특정 노드 이동)
    
  6.4. DESTROY
```

```
7. BinarySearchTree Library 설계 프로젝트
  7.1. Recursive Function(재귀)
    -CREATE
    -INSERT
    -SEARCH
    -DELETE
    -MAKEBALANCE
      -MAKEKEYS
        -NODE_MAKEKEYS
      -DELETEALLITEMS
        -NODE_DELETEALLITEMS
      -MAKETREE
        -NODE_MAKETREE
    -DESTROY
      -NODE_DESTROY
      
  7.2. Stack Function
```

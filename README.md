# KNOCKturne
BRIDGE Ludico KNOCKturne

---

## 작업 전 세팅 순서

1. 카카오톡, 디스코드 등에서 업데이트된 애셋이 있는지 확인 후 구글 드라이브에서 다운로드 받는다.
2. 깃허브 데스크탑에서 Fetch 내용이 있는지 확인한다.
3. 깃허브 데스크탑의 Current Branch를 자신의 것으로 세팅한다.
4. 작업을 시작한다.

---

## 이슈 작성 요령

깃허브 게시글, 문서는 [마크다운](https://gist.github.com/ihoneymon/652be052a0727ad59601)이라는 형식으로 작성된다.<br>
특정 규칙에 따라 문서를 작성하면 규칙에 맞는 서식이 적용된다.
<p align="center"><img src = "https://user-images.githubusercontent.com/57585303/196473866-3d0764d2-c771-4d8e-afca-cb7e43d7c4c9.png"></p>

우측 상단의 `New issue` 버튼을 클릭하면 새로운 이슈 게시글 작성이 가능하다. 만들어 둔 3개 템플릿 중 하나를 선택하여 이슈를 작성하고, 
더 세부적인 이슈 템플릿이 필요하다면 플밍 송영민에게 요청시 하루 내로 템플릿이 추가된다.

<p align="center"><img src = "https://user-images.githubusercontent.com/57585303/196474391-2c0ffad9-6cae-4a4b-a3e6-78555d610e39.png"></p>

각 항목의 괄호 부분은 항목에 대한 상세 설명이고, 해당부를 지우고 내용을 작성한다. 내용을 모두 작성하면 우측 `Assignees`에서 해당 이슈 해결에 도움을 줄 책임자(없다면 선택하지 않아도 된다)를 선택하고, `Labels`에서 해당 이슈의 분류를 선택하고 `Submit new issue`를 해준다. 만약 추가적인 라벨이 필요하다면 마찬가지로 요청시 하루 내에 추가된다.

만약 이슈 내용을 작성할 때 사진이나 링크를 첨부해야 할 경우 다음과 같은 방식을 사용한다.

---

### 사진
사진은 아래와 같은 마크다운 형식으로 작성되며, 사진을 첨부하는 방식은 크게 3가지이다.
```
![image](https://user-images.githubusercontent.com/57585303/196475325-de5be145-53d1-4a81-b90b-b7576e23de59.png)
```

1. 인터넷에 배포된 사진이라면 아래와 같이 이미지 복사해 클립보드에 저장 후 게시글에 붙여넣기로 첨부가 가능하다.
<p align="center"><img src = "https://user-images.githubusercontent.com/57585303/196475325-de5be145-53d1-4a81-b90b-b7576e23de59.png"></p>

2. 클립보드에 저장된 사진을 바로 첨부할 수 있으므로, 키보드 `PrtSc(Print Screen)` 버튼이나,<br>
`캡처 도구`(단축키 : `Win` + `Shift` + `S`)로 캡처한 사진을 붙여넣기하는 것도 가능하다.

3. 파일로 보유 중인 사진이라면, 아래와 같이 드래그 앤 드롭으로 게시글에 첨부할 수 있다.
<p align="center"><img src = "https://user-images.githubusercontent.com/57585303/196476790-5ae3317c-5353-4a8b-b2f5-e8c65b0c2da6.png"></p>

이때, 위 사진에서 이미지 형식이 조금 다른데, 이는 가운데 정렬된 이미지를 첨부하는 방식으로
```
<p align="center"><img src = "https://user-images.githubusercontent.com/57585303/196476790-5ae3317c-5353-4a8b-b2f5-e8c65b0c2da6.png"></p>
```

와 같이 작성하여 가운데 정렬된 사진을 첨부할 수 있다.

---

### 링크
링크는 아래와 같은 마크다운 형식으로 작성된다.
```
[브릿지 네이버 카페](https://cafe.naver.com/bridge100)
```

[브릿지 네이버 카페](https://cafe.naver.com/bridge100)처럼 대괄호 안의 텍스트에 하이퍼 링크를 다는 것이 가장 가독성이 좋으며,<br>
https://cafe.naver.com/bridge100 과 같이 그냥 링크만 첨부하여도 자동으로 상호작용이 생성되긴 한다. 필자는 아래와 같은 형식으로 링크를 자주 첨부한다.
```
▶ [[Wikipedia] 미리 컴파일된 헤더](https://en.wikipedia.org/wiki/Precompiled_header)
```
▶ [[Wikipedia] 미리 컴파일된 헤더](https://en.wikipedia.org/wiki/Precompiled_header)

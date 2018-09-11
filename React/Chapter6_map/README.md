컴포넌트 반복
=============

### 6.1 자바스크립트 배열의 map() 함수

arr.map(callback, [thisArg]) 의 형태로 사용

-	callback: 새로운 배열의 요소를 생성하는 함수로 파라미터는 다음 세 가지이다.

	-	currentValue: 현재 처리하고 있는 요소
	-	index: 현재 처리하고 있는 요소의 index 값
	-	array: 현재 처리하고 있는 원본 배열

-	thisArg(선택 항목): callback 함수 내부에서 사용할 this 레퍼런스

```javascript
const numbers = [1, 2, 3, 4, 5];
const result = numbers.map(num => num * num);

console.log(result);
```

> [1, 4, 9, 16, 25]의 결과를 가진다.

### 6.2 key

key가 없을 때는 가상 DOM을 비교하는 과정에서 리스트를 순차적으로 비교하면서 변화를 감지한다. 하지만 key가 있다면 이 값을 사용하여 어떤 변화가 일어났는지 더욱 빠르게 알아낼 수 있다.

#### key 설정

key 값은 언제나 유일해야 하므로 데이터가 가진 고유값을 key값으로 설정해야 한다.

고유번호가 없을 때는 map 함수에 전달되는 콜백 함수의 인수인 **index** 값을 사용하도록 하자.

```javascript
import React, { Component } from 'react';

class IterationSample extends Component {
  render() {
    const names = ['눈사람', '얼음', '눈', '바람'];
    const nameList = names.map(
      (name) => (<li>{name}</li>)
    );

    return (
      <ul>
        {nameList}
      </ul>
    );
  }
}

export default IterationSample;
```

> 위의 코드처럼 작성을 하게 되면 렌더링은 되지만 key가 없기 때문에 Warning 메시지가 뜬다. 따라서 아래와 같이 수정하도록 하자.

```javascript
import React, { Component } from 'react';

class IterationSample extends Component {
  render() {
    const names = ['눈사람', '얼음', '눈', '바람'];
    const nameList = names.map(
      (name, index) => (<li key={index}>{name}</li>)
    );

    return (
      <ul>
        {nameList}
      </ul>
    );
  }
}

export default IterationSample;
```

> 위에서 말했던 것 처럼 callback 함수의 인수인 index를 이용하여 key로 사용하면 Warning을 없앨 수 있다.

### 전개 연산자

... 문법을 전개 연산자라고 하는데 전개 연산자의 역할은 ... 뒤에 위치한 배열 값을 그대로 꺼내서 현재 배열에 복사하는 것이다.

```javascript
const numbers = [1, 2, 3, 4, 5];
const moreNumbers = [ ...numbers, 6];
```

> moreNumbers의 결과로는 [1, 2, 3, 4, 5, 6]의 결과를 가지게 된다.

#### 주의해야할 점

상태 안에서 배열을 변형할 때는 배열에 직접 접근하여 수정하는 것이 아닌 concat, slice, 전개 연산자, filter 함수 등을 사용해서 새로운 배열을 만든 후, setState 메서드로 적용해야 한다.

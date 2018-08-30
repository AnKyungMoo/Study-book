Component
=========

3.1 컴포넌트
------------

```javascript
import React, { Component } from 'react';

class MyComponent extends Component {
  render() {
    return (
      <div>
        나의 새롭고 멋진 컴포넌트
      </div>
    )
  }
}

export default MyComponent;
```

> export default MyComponent의 의미는 다른 파일에서 이 파일을 import 할 때 위쪽에서 선언한 MyComponent 클래스를 불러오도록 설정하는 것

```javascript
import React, { Component } from 'react';
import MyComponent from './MyComponent';

class App extends Component {
  render() {
    return (
      <MyComponent />
    )
  }
}

export default App;
```

> App 컴포넌트에서 MyComponent 컴포넌트를 불러와 사용하는 방법

3.2 props
---------

props는 properties를 줄인 표현으로 컴포넌트 속성을 설정할 때 사용하는 요소<br/> props는 부모 컴포넌트가 설정하며 컴포넌트 자신은 해당 props를 읽기 전용으로만 사용할 수 있음<br/> 아래는 사용 예시

```javascript
import React, { Component } from 'react';

class MyComponent extends Component {
  render() {
    return (
      <div>
        안녕하세요, 제 이름은 {this.props.name} 입니다.
      </div>
    )
  }
}

export default MyComponent;
```

```javascript
import React, { Component } from 'react';
import MyComponent from './MyComponent';

class App extends Component {
  render() {
    return (
      <MyComponent name="React"/>
    )
  }
}

export default App;
```

#### defaultProps

위의 코드에서 name 값을 지정하지 않았을 때, 즉 props의 값을 지정하지 않았을 때 기본 값으로 설정하는 것

```javascript
class MyComponent extends Component {
  (...)
}

MyComponent.defaultProps = {
  name: '기본 이름'
}
```

> defaultProps를 설정하는 전통적인 방법이지만 해당 책에서 추천하는 방식은 다름

```javascript
import React, { Component } from 'react';

class MyComponent extends Component {
  static defaultProps = {
    name: '기본 이름'
  }
  render() {
    return (
      <div>
        안녕하세요, 제 이름은 {this.props.name} 입니다.
      </div>
    )
  }
}

export default MyComponent;
```

> 위 두개의 코드의 차이점은 없다. 빌드 작업에서 바벨을 통해 ES5 형태의 코드로 변환할 때 동일한 결과를 보인다. 해당 책에서 추천하는 방식은 두 번째 방식이다.

#### propsTypes

propsTypes를 사용하기 위해서는 코드 맨 위쪽에서 propTypes를 불러와야 한다.

```javascript
import PropTypes from 'prop-types';
```

```javascript
import React, { Component } from 'react';
import PropTypes from 'prop-types';

class MyComponent extends Component {
  static defaultProps = {
    name: '기본 이름'
  }

  static propTypes = {
    name: PropTypes.string  // name props 타입을 문자열로 설정
  }

  render() {
    return (
      <div>
        안녕하세요, 제 이름은 {this.props.name} 입니다.
      </div>
    )
  }
}

export default MyComponent;
```

```javascript
<MyComponent name={3} />
```

> name props 타입을 문자열로 설정. App 컴포넌트에서 MyComponent의 name 값을 문자열이 아닌 숫자 등의 다른 타입의 데이터를 보내게 되면 렌더링은 성공하지만 오류 메시지를 출력한다.
>
> 문자열 종류 외의 값을 컴포넌트에 전달할 때는 { }로 감싸야 한다.<br /> 그렇지 않을 경우 오류가 발생

#### 필수 propTypes 설정

```javascript
import React, { Component } from 'react';
import PropTypes from 'prop-types';

class MyComponent extends Component {
  static defaultProps = {
    name: '기본 이름'
  }

  static propTypes = {
    name: PropTypes.string  // name props 타입을 문자열로 설정
    age: PropTypes.number.isRequired  // 필수적으로 존재해야 하며, 숫자이다.
  }

  render() {
    return (
      <div>
        <p>안녕하세요, 제 이름은 {this.props.name} 입니다.</p>
        <p>저는 {this.props.age}살 입니다.</p>
      </div>
    )
  }
}

export default MyComponent;
```

```javascript
<MyComponent name="React" age={4} />
```

> isRequired를 설정해둔 props는 값을 받지 않으면 오류가 발생한다.

3.3 state
---------

컴포넌트 내부에서 읽고 업데이트 할 수 있는 값<br/> 기본 값을 미리 설정해야 사용할 수 있으며, this.setState() 메서드로만 값을 업데이트 해야 한다.

#### constructor()

state의 초기값은 컴포넌트의 생성자 메서드인 constructor() 내부에서 설정한다.

```javascript
constructor(props) {
  super(props);
  this.state = {
    number: 0
  }
}
```

> state의 number 값을 0으로 설정

#### JSX 내부에서 state 렌더링

```javascript
  render() {
    return (
      <div>
        <p>안녕하세요, 제 이름은 {this.props.name} 입니다. </p>
        <p>저는 {this.props.age}살 입니다.</p>
        <p>숫자: {this.state.number}</p>
      </div>
    )
  }
```

> state를 렌더링 하는 방법은 props를 렌더링 하는 방법과 비슷하다.

#### setState()

state 값을 업데이트할 때는 this.setState 메서드를 이용한다.

```javascript
  render() {
    return (
      <div>
        <p>안녕하세요, 제 이름은 {this.props.name} 입니다. </p>
        <p>저는 {this.props.age}살 입니다.</p>
        <p>숫자: {this.state.number}</p>
        <button onClick={() => {
          this.setState({
            number: this.state.number + 1
          })
        }
      }>더하기</button>
      </div>
    )
  }
```

> 버튼을 누를 때 마다 number 값이 1씩 추가된다.

#### 화살표 함수

화살표 함수와 function()의 가장 큰 차이중 하나는 this로 확인할 수 있다.<br/>

```javascript
function BlackDog() {
  this.name = '흰둥이';
  return {
    name: '검둥이',
    bark: function() {
      console.log(this.name + ': 멍멍!');
    }
  }
}

const blackDog = new BlackDog;
blackDog.bark(); // 검둥이: 멍멍
```

function()은 자신이 종속된 객체를 this로 가리키고

```javascript
function WhiteDog() {
  this.name = '흰둥이';
  return {
    name: '검둥이',
    bark: () => {
      console.log(this.name + ': 멍멍!');
    }
  }
}

const whitekDog = new WhiteDog;
whiteDog.bark(); // 흰둥이: 멍멍
```

화살표 함수는 자신이 종속된 인스턴스를 가리킨다.

#### state를 constructor에서 꺼내기

원래 초기 state는 constructor 메서드에서 정의해야 하지만, defaultProps와 propTypes를 정의 할 때 사용한 transform-class-properties 문법으로 constructor 바깥에서 정의할 수도 있다.

```javascript
import React, { Component } from 'react';

class MyComponent extends Component {
  state = {
    number: 0
  }

  render() {
    (...)
  }
}

export default MyComponent;
```

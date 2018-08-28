JSX
===

2.1 코드 이해
-------------

### 모듈 불러오기

```javascript
import React, { Component } from 'react';
```

> ES6부터는 import 키워드를 이용하여 모듈을 불러 올 수 있다. <br/> 이전까지는 require()을 이용했었다.

### 클래스 선언

```javascript
class App extends Component {}
```

> App 이라는 클래스를 선언.<br/> 이 클래스는 React 라이브러리 내부에 있는 Component 클래스를 상속한다.<br> 새로운 클래스를 만들 때는 이렇게 클래스를 선언한다.

```javascript
render(){
  return (
    <div className="App">
      <div className="App-header">
        <img src={logo} className="App-logo" alt="logo" />
        <h2>Welcome to React</h2>
      </div>
      <p className="App-intro">
        To get started, edti <code>src/App.js</code> and save to reload.
      </p>
    </div>
  );
}
```

> render() 함수 내부에서 컴포넌트를 유저에게 어떻게 보일지 return 한다.

2.2 JSX란?
----------

> JSX란 javascript의 확장 문법으로 XML과 매우 비슷하게 생겼다.<br/> 이런 형식으로 작성한 코드는 나중에 코드가 번들링되면서 babel-loader를 사용하여<br/> 자바스크립트로 변환한다.<br/> JSX는 리액트용이기 때문에 공식 자바스크립트 문법은 아니다!<br/> 하지만 babel이 이를 변환해주고 있다.

2.3 JSX 문법
------------

JSX는 편리한 문법이지만, 지켜야할 규칙들이 존재한다.

### 감싸인 요소

```javascript
render() {
  return (
    <div>
      <h1>리액트 안녕!</h1>
      <h2>당신은 어썸한가요?</h2>
    </div>
  );
}
```

> 컴포넌트에 여러 요소가 있다면 부모 요소 하나로 꼭 감싸야 한다.<br/> div 태그를 제외하고 코드를 작성할 시 에러가 발생.<br/> 이유는 Virtual DOM에서 컴포넌트 변화를 감지해 낼 때 효율적으로 비교할 수 있도록<br> 컴포넌트 내부는 DOM 트리 구조 하나여야 한다는 규칙이 존재하기 때문!

div 같은 것으로 감싸지 않고 여러 요소를 렌더링 하고 싶다면 Fragment를 이용하자.

```javascript
render() {
  return (
    <Fragment>
      <h1>리액트 안녕!</h1>
      <h2>당신은 어썸한가요?</h2>
    </Fragment>
  );
}
```

### 자바스크립트의 표현

```javascript
render() {
  const text = '당신은 어썸한가요?';
  return (
    <div>
      <h1>리액트 안녕!</h1>
      <h2>{text}</h2>
    </div>
  );
}
```

> 자바스크립트 표현식을 작성하려면 JSX 내부에서 코드를 { }로 감싸면 된다.

```javascript
render() {
  const text = '당신은 어썸한가요?';
  const condition = true;
  return (
    <div>
      <h1>리액트 안녕!</h1>
      <h2>{text}</h2>
      {
        condition ? '참' : '거짓'
      }
    </div>
  );
}
```

> JSX 내부의 자바스크립트 표현식에서 if 문을 사용할 수 없다. <br/> 하지만 조건에 따라 다른 것을 렌더링해야할 때는 JSX 밖에서 if문을 사용하여 작업하거나,<br/> { } 안에 삼항 연산자를 사용하면 된다.

```javascript
render() {
  const text = '당신은 어썸한가요?';
  const condition = true;
  const style = {
    backgroundColor: 'gray',
    border: '1px solid black',
    height: Math.round(Math.random() * 300) + 50,
    width: Math.round(Math.random() * 300) + 50,
    WebkitTransition: 'all',
    MozTransition: 'all',
    msTransition: 'all'
  };

  return (
    <div>
      <h1>리액트 안녕!</h1>
      <h2>{text}</h2>
      {
        condition ? '참' : '거짓'
      }
      <div style={style}></div>
    </div>
  );
}
```

> 자바스크립트의 객체 key에서는 '-'을 사용할 수 없으므로 camelCase를 이용한다.<br/> 접두어인 -mos, -webkit을 사용할 때도 마찬가지로 Mos, Webkit으로 바꾸어 사용한다.<br/> -ms는 예외로 소문자 ms로 사용한다.

src/App.css

```css
.my-div {
  background-color: aqua;
  font-size: 15px;
}
```

src/App.js

```javascript
import React, { Component } from 'react';
import './App.css';

class App extends Component {
  render() {
    const text = '당신은 어썸한가요?';

    return (
      <div className="my-div">
        <h1>리액트 안녕!</h1>
        <h2>{text}</h2>
        <div style={style}></div>
      </div>
    );
  }
}
```

> 리액트에서 class를 설정할 때는 class 키워드 대신 className으로 설정해야 한다.<br/> class 키워드는 이미 자바스크립트에 존재하는 키워드이기 때문이다.

```javascript
render() {
  return (
    <div className="my-div">
      { /* 요소 밖에서는 이렇게 작성해요. */ }
      <h1>리액트 안녕!</h1>
      <div style={style}
        // self-closed 태그에서만 작동하는 주석
        // 마지막 />가 꼭 새 줄에 있어야 합니다.
        /*이렇게 작성할 수도 있고요.*/
      />
      // 여기 쓰는 건 그대로 렌더링됩니다.
      /* 여기에선 주석 못 써요 */
    </div>
  );
}
```

> 일반적으로 주석을 작성할 때는 { /* 이런 형식으로 */ } 자바스크립트 표현식을 사용할 때 처럼 작성합니다.<br> 일반 자바스크립트에서 주석을 작성할 때처럼 아무 데나 // 이런 주석이나 /* 이런 주석 */ 작성한다면 그 주석은 페이지에 렌더링 됩니다.<br> 하지만 self-closed 요소(여는 태그와 닫는 태그가 분리되어 있지 않고 자체적으로 닫는 요소를 의미)에서 />를 다음 줄에 작성할 때는 그 사이에서 주석을 { } 없이 작성할 수 있다.

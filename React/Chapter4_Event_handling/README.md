이벤트 핸들링
=============

#### 이벤트란?

유저가 웹 브라우저에서 DOM 요소들과 상호 작용 하는 것

### 리액트의 이벤트를 사용할 때 주의 사항

1.	이벤트 이름은 camelCase로 작성한다.
2.	이벤트에 실행할 자바스크립트 코드를 전달하는 것이 아니라, 함수 형태의 값을 전달한다.<br/>*ㄴ HTML에서 이벤트를 설정할 때는 큰따옴표 안에 실행할 코드를 넣었지만, 리액트에서는 함수 형태의 객체를 전달한다. 화살표 함수 문법 등을 이용*
3.	DOM 요소에만 이벤트를 설정할 수 있다.<br/>*ㄴ div, button, input, form, span 등 DOM 요소에는 이벤트를 설정할 수 있지만, 우리가 직접 만든 컴포넌트에는 이벤트를 자체적으로 설정할 수 없다.<br/> 예를 들어 MyComponent에 onClick 이벤트를 설정한다면 MyComponent를 클릭 할 때 doSomething 함수를 실행하는 것이 아닌, 그냥 이름이 onClick인 props를 전달 받는다.*

```javascript
<MyComponent onClick={doSomething}/>
```

하지만 전달 받은 props를 컴포넌트 내부의 DOM 이벤트로 설정할 수 있다.

```javascript
<div onClick={this.props.onClick}>
  {...}
</div>
```

```javascript
import React, { Component } from 'react';

class EventPractice extends Component {

  state = {
    username: '',
    message: ''
  }

  handleChange = (e) => {
    // [] 안에 있는 값을 key 값으로 사용하는 것
    this.setState({
      [e.target.name] = e.target.value
    });
  }

  handleClick = () => {
    alert(this.state.username + ': ' + this.state.message);
    this.setState({
      username = '',
      message = ''
    });
  }

  render() {
    return(
      <div>
        <input
          type="text"
          name="username"
          placeholder="유저명"
          value={this.state.username}
          onChange={this.handleChange}
        />
        <input
          type="text"
          name="message"
          placeholder="아무거나 입력해보세요"
          value={this.state.message}
          onChange={this.handleChange}
        />
        <button onClick={this.handleClick}>확인</button>
      </div>
    );
  }
}

export default EventPractice;
```

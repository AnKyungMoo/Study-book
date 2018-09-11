ref: DOM에 이름 달기
====================

*일반 HTML에서 DOM 요소에 이름을 달 때는 id를 이용한다. 리액트 컴포넌트 안에서도 id를 사용할 수 있으나, 리액트에서 DOM에 id를 달면 해당 DOM을 렌더링할 때 그대로 전달된다. 컴포넌트를 여러 번 사용한다고 가정했을 때, HTML에서 DOM의 id는 유일해야하는데, 이런 상황에서는 중복 id를 가진 DOM이 여러 개 생기기 때문에 잘못된 방식이다.*

ref는 전역적으로 작동하지 않고 컴포넌트 내부에서만 작동하기 때문에 이런 문제가 발생하지 않는다.<br/>

따라서 대부분은 **ref**를 이용하도록 하자.

5.1 ref는 어떤 상황에서 사용해야 할까?
--------------------------------------

ref는 DOM을 꼭 직접적으로 건드려야 할 때 사용한다.

```javascript
import React, { Component } from 'react';
import './ValidationSample.css';

class ValidationSample extends Component {
    state = {
        password: '',
        clicked: false,
        validated: false
    }

    handleChange = (e) => {
        this.setState({
            password: e.target.value
        });
    }

    handleButtonClick = () => {
        this.setState({
            clicked: true,
            validated: this.state.password === '0000'
        })
        // 2. 설정한 ref를 이용하여 focus를 변경
        this.km.focus();
    }

    render() {
        return (
            <div>
                <input
                // 1. km은 사용자가 설정하는 ref의 이름
                ref={(ref) => this.km=ref}
                type="password"
                value={this.state.password}
                onChange={this.handleChange}
                className={this.state.clicked ? (this.state.validated ? 'success' : 'failure') : ''}
                />

                <button onClick={this.handleButtonClick}>검증하기</button>
            </div>
        );
    }
}

export default ValidationSample;
```

> ref를 이용하면 input 요소를 직접적으로 접근할 수 있다!<br/> ref의 이름은 DOM 타입과는 관꼐 없이 마음대로 지정할 수 있다.<br/> input 요소 일 때 this.input이 아닌 this.km으로 작성해도 된다는 이야기다.

### ref는 DOM 요소 뿐만 아니라 컴포넌트에도 달 수 있다.

ref를 컴포넌트에 달 때는 주로 컴포넌트 내부에 있는 DOM을 컴포넌트 외부에서 사용할 때이다.

```javascript
<MyComponent ref = {(ref) => this.my=ref} />
<button onClick={() => this.my.scrollToBottom()}>
버튼
</button>
```

> MyComponent 라는 컴포넌트 안에 존재하는 scrollToBottom() 이라는 함수를 가져오기 위해서 MyComponent를 렌더링 할 때 ref를 지정해주고, 해당 ref를 통해서 scrollToBottom을 호출한다.

주의 할 점으로 서로 다른 컴포넌트끼리 데이터를 교류할 때는 ref를 사용하면 안된다. 물론 할 수는 있지만 그럴 땐 redux를 사용하도록하자.

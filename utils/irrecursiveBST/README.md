# An irrecursive BST implementation
## motivation

### use a stack to simulate pre/in/post-order traversals

![](https://i.imgur.com/TGuemNo.png)

## universal
```c++
stk.clear(); stk.push(root);
while(!stk.empty()){
    (cur, cnt) = stk.top(); stk.pop();
    if(cnt==1){
        printf("Here's pre-order %d\n", cur);
        stk.push(cur, 2);
        stk.push(cur->lf);
        // until left-subtree is finished, we won't traverse (cur, 2)
    }
    if(cnt==2){
        printf("Here's in-order %d\n", cur);
        // do anything you want it in-order
        stk.push(cur, 3);
        stk.push(cur->rt);
    }
    if(cnt==3){
        printf("Here's post-order %d\n", cur);
        // do anything you want it post-order
    }
}
```

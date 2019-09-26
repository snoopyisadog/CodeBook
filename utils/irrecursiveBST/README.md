# A Non-Recursive BST Implementation in C++
### **keywords**
- Binary Search Tree
- non-recursive

## motivation
When we are preparing problems for a programming contest, we would expect the participants to summit a faster solution than a naive one. However, we may need the naive one to side check if the testcases are correct. For BST-related problems, especially the unbalanced BSTs, we all know that the worst case is a linked-list, which complexify the time complexity of every single Insert/Delete/Search to $O(n)$, where $n$ is the number of nodes in the tree. While $n$ increases to tens of thousands or above, a recursive BST program will throw out stack overflow exceptions (RunTime Error).
Hereby, we have implemented a non-recursive BST in C++, in order to avoid getting stack overflow exceptions.

Details
==
## Insert
```cpp=

```
## Traverse
The most common pre/in/post-order traversal implementations are based on Depth-First-Search:
```cpp=
void DFS_traverse(node *current){
    if(NULL==current) return;
    printf("%d_pre-order\n", current->value);
    traverse(current->left_child);
    printf("%d_in-order\n", current->value);
    traverse(current->right_child);
    printf("%d_post-order\n", current->value);
}
```
Intuitively, we may use a stack to simutlate the DFS-behavior. If you are not familiar with how the program counter and the stack pointer work when a program encounters a function, we can start from the simple function below:
```cpp=1
void non_recursive_pre_order_traversal(node *root){
    stk.clear(); stk.push(root);
    while(!stk.empty()){
        cur = stk.top(); stk.pop();
        puts("Here's pre-order");
        stk.push(cur->right_child);
        // ...?
        stk.push(cur->left_child);
    }
}
```
Because we want to pop out **left_child** from the stack ealier than **right_child**, the order of **line_6** and **line_8** is clear.
Unfortunately, it's easy to see that **line_6** isn't related to in-order traversal; however, it's sufficient to simulate a pre-order traversal.
After we pair the nodes with a respectively counter, for a node in the auxiliary stack, we can finally tell if we just meet, finished left subtree but not the right one yet, or about to leave for the node's predecessor.
```c++=
void non_recursive_traversal(node *root){
    stk.clear(); stk.push(root);
    while(!stk.empty()){
        (cur, cnt) = stk.top(); stk.pop();
        if(cnt==1){
            printf("Here's pre-order %d\n", cur);
            stk.push(cur, 2);
            stk.push(cur->lf, 1);
            // until left-subtree is finished, we won't traverse (cur, 2)
        }
        if(cnt==2){
            printf("Here's in-order %d\n", cur);
            // do anything you want it in-order
            stk.push(cur, 3);
            stk.push(cur->rt, 1);
        }
        if(cnt==3){
            printf("Here's post-order %d\n", cur);
            // do anything you want it post-order
        }
    }
}
```
Finally, we can see that the workflow is the same as what the program counter and the stack pointer do: "push down" current data, and immediately process the new data.
In our implemtation, the counter is implemented with another auxiliary stack.

By the way, if you don't need post-order, the traveral function can be reduced to
```c++=
void non_recursive_in_order_traversal(node *root){
    stk.clear(); stk.push(root);
    while(!stk.empty()){
        (cur, cnt) = stk.top(); stk.pop();
        if(cnt<2){
            // pre-order
            stk.push(cur->rt);
            stk.push(cur, 2);
            stk.push(cur->lf);
        }else{
            // in-order
        }
    }
}
```

## Delete
Here we choose to promote the smallest element in the right subtree of which node we are going to delete.

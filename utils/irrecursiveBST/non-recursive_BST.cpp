#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define for0(a, b) for(a=0;a<b;a++)
#define it_c(container) while(!container.empty())
// iterate a container

typedef struct A{
    struct A *ch[2];
    int v;
    A(){}
    A(int x){
        v = x;
        ch[0] = ch[1] = NULL;
    }
}node;

// auxiliary containers for traversing the BST
queue<node*> que;
stack<node*> stk;
stack<int> stk2;
vector<int> vec;

typedef struct B{
    node *root, *it;
    void clear(){
        if(NULL==root) return;
        it_c(que) que.pop();
        que.push(root);
        it_c(que){
            it = que.front(); que.pop();
            if(it==NULL) continue;
            que.push(it->ch[0]);
            que.push(it->ch[1]);
            delete(it);
        }
        root = NULL;
    }
    void ins(int val){
        it = new node(val);
        if(root == NULL) root = it;
        else{
            int is_rt;
            node *pre, *cur;
            pre = cur = root;
            while(cur != NULL){
                pre = cur;
                if(val < cur->v){
                    cur = cur->ch[0];
                    is_rt = 0;
                }else{
                    cur = cur->ch[1];
                    is_rt = 1;
                }
            }
            pre->ch[is_rt] = it;
        }
    }
    node *contains(int val){
        node *cur = root;
        while((NULL!=cur) && (cur->v != val)){
            if(val < cur->v) cur = cur->ch[0];
            if(val > cur->v) cur = cur->ch[1]; // may enter both if-statements, but doesn't matter
        }
        return cur;
    }
    void del(int del_val){
        int is_rt, i;
        node *pre, *cur;
        cur = root;
        if(root == NULL) return;
        if(root->v == del_val){
            // special case, since root has no predecessors
            for0(i, 2){
                if(root->ch[i] == NULL){
                    pre = root;
                    root = root->ch[i^1];
                    delete(pre);
                    return;
                }
            }
            // find the smallest in right subtree
            pre = root;
            cur = root->ch[1];
            is_rt = 1;
            while(cur->ch[0] != NULL){
                pre = cur;
                cur = cur->ch[0];
                is_rt = 0;
            }// now, cur->lf is NULL
            root->v = cur->v;
            pre->ch[is_rt] = cur->ch[1];
            delete(cur);
            return;
        }
        cur = root;
        while((cur!=NULL)&&(cur->v!=del_val)){
            pre = cur;
            if(del_val<cur->v){
                is_rt = 0;
            }else if(del_val>cur->v){
                is_rt = 1;
            }
            cur = cur->ch[is_rt];
        }
        if(cur == NULL){
            //printf("no such value\n");
            return;
        }
        for0(i, 2){
            if(cur->ch[i] == NULL){
                pre->ch[is_rt] = cur->ch[i^1];
                break;
            }
        }
        if(i>=2){ // both subtrees are non-empty
            node *sub_root;
            sub_root = pre = cur;
            //printf("sub_root=%d->%d\n", sub_root, sub_root->v);
            //printf("cur->rt=%d\n", cur->ch[1]);
            cur = cur->ch[1];
            is_rt = 1;
            while(cur->ch[0] != NULL){
                pre = cur;
                cur = cur->ch[0];
                is_rt = 0;
            }
            //printf("cur->v=%d\n", cur->v);
            sub_root->v = cur->v;
            pre->ch[is_rt] = cur->ch[1];
        }
        delete(cur);
    }
    void traverseOrder(int mode){
        /* 1/2/3: pre/in/post-order, 4: level-order. */
        vec.clear();
        if(mode==4){
            it_c(que) que.pop();
            que.push(root);
            it_c(que){
                it = que.front(); que.pop();
                if(NULL == it) continue;
                vec.pb(it->v);
                que.push(it->ch[0]);
                que.push(it->ch[1]);
            }
        }else{
            int cnt; // 1==pre, 2==in, 3==post
            it_c(stk) stk.pop();
            it_c(stk2) stk2.pop();
            stk.push(root); stk2.push(1);
            it_c(stk){
                it = stk.top(); stk.pop();
                cnt = stk2.top(); stk2.pop();
                if(NULL==it) continue;
                if(cnt==mode) vec.pb(it->v);
                if(cnt==1){
                    //pre-order
                    stk.push(it); stk2.push(2);
                    stk.push(it->ch[0]); stk2.push(1);
                }else if(cnt==2){
                    //in-order
                    stk.push(it); stk2.push(3);
                    stk.push(it->ch[1]); stk2.push(1);
                }else{
                    //post-order
                    ;
                }
            }
        }
        printVec();
    }
    void printVec(){
        if(!vec.empty()){
            printf("%d", vec[0]);
            for(int i=1;i<vec.size();i++) printf(" %d", vec[i]);
        }
        puts("");
    }
}BST;

BST bst;
bst.ins(value_you_want_to_insert);
bst.del(value_you_want_to_delete);
bst.contains(value_to_check_if_in_BST);
bst.traverseOrder(traverse_ordering_id);

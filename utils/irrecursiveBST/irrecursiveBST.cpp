#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define FOR1(a, b) for(int a=1;a<=b;a++)
#define FOR0(a, b) for(int a=0;a<b;a++)
#define SIZE_N 100005
const int INF = 0x3fffffff;
#define it_c(container) while(!container.empty())
// iterate a container

int T, n;

typedef struct A{
    struct A *lf, *rt;
    int val;
    A(){}
    A(int x){
        val = x;
        lf = rt = NULL;
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
        sz = 0;
		if(NULL==root) return;
        while(!que.empty()) que.pop();
        que.push(root);
        while(!que.empty()){
            it = que.front(); que.pop();
			if(it==NULL) continue;
            que.push(it->lf);
            que.push(it->rt);
            delete(it);
        }
        root = NULL;
    }
    void ins(int val){
        it = new node(val);
        if(root == NULL) root = it;
        else{
            int is_lf;
            node *pre, *cur;
            pre = cur = root;
            while(cur != NULL){
                pre = cur;
                if(val < cur->val){
                    cur = cur->lf;
                    is_lf = 1;
                }else{
                    cur = cur->rt;
                    is_lf = 0;
                }
            }
            // cur is child of pre
            if(is_lf) pre->lf = it;
            else pre->rt = it;
        }
    }
    void del(int del_val){
        int is_lf;
        node *pre, *cur;
        cur = root;
        if(root == NULL) return;
        if(root->val == del_val){
            if(root->lf == NULL){
                pre = root;
                root = root->rt;
                delete(pre);
            }else if(root->rt == NULL){
                pre = root;
                root = root->lf;
                delete(pre);
            }else{
                // messy
                pre = root;
                cur = root->rt;
                is_lf = 0;
                while(cur->lf != NULL){
                    pre = cur;
                    cur = cur->lf;
                    is_lf = 1;
                }// now, cur->lf is NULL
                root->val = cur->val;
                if(is_lf){
                    pre->lf = cur->rt;
                }else{
                    pre->rt = cur->rt;
                }
                delete(cur);
            }
            return;
        }
        cur = root;
        while((cur!=NULL)&&(cur->val!=del_val)){
            pre = cur;
            if(del_val<cur->val){
                is_lf = 1;
                cur = cur->lf;
            }else if(del_val>cur->val){
                is_lf = 0;
                cur = cur->rt;
            }
        }
        if(cur == NULL){
            //printf("no suck value\n");
            return;
        }
        if(cur->lf == NULL){
            if(is_lf){
                pre->lf = cur->rt;

            }else{
                pre->rt = cur->rt;
            }
            delete(cur);
            return;
        }else if(cur->rt == NULL){
            if(is_lf){
                pre->lf = cur->lf;

            }else{
                pre->rt = cur->lf;
            }
            delete(cur);
            return;
        }else{
            node *sub_root;
            sub_root = pre = cur;
            cur = cur->rt;
            is_lf = 0;
            while(cur->lf != NULL){
                pre = cur;
                cur = cur->lf;
                is_lf = 1;
            }
            sub_root->val = cur->val;
            if(is_lf){
                pre->lf = cur->rt;
            }else{
                pre->rt = cur->rt;
            }
            delete(cur);
        }
    }
    void traverseOrder(int mode){
        /* 1/2/3: pre/in/post-order, 4: level-order. */
        vec.clear();
        if(mode==4){
            while(!que.empty()) que.pop();
            que.push(root);
            it_c(que){
                it = que.front();
                if(NULL == it) continue;
                vec.pb(it->val);
                que.push(it->lf);
                que.push(it->rt);
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
                if(cnt==mode) vec.pb(it->val);
                if(cnt==1){
                    //pre-order
                    stk.push(it); stk2.push(2);
                    stk.push(it->lf); stk2.push(1);
                }else if(cnt==2){
                    //in-order
                    stk.push(it); stk2.push(3);
                    stk.push(it->rt); stk2.push(1);
                }else{
                    //post-order
                    ;
                }
            }
        }
        printVec();
    }
    /***
        pre/in-order can be simpler than the generalized traversal,
        but not helpful in time complexity.
    ***/
    void printPreOrder(){
		vec.clear();
        while(!stk.empty()) stk.pop();
        stk.push(root);
        while(!stk.empty()){
            it = stk.top();
            stk.pop();
            if(it==NULL) continue;
            vec.pb(it->val);
            stk.push(it->rt);
            stk.push(it->lf);
        }
        printVec();
    }
	void printInOrder(){
	    int cnt;
		vec.clear();
		it_c(stk) stk.pop();
		it_c(stk2) stk2.pop();
        stk.push(root); stk2.push(1);
        while(!stk.empty()){
            it = stk.top(); stk.pop();
            cnt = stk2.top(); stk2.pop();
            if(it==NULL) continue;
            if(cnt==1){
                stk.push(it->rt); stk2.push(1);
                stk.push(it); stk2.push(2);
                stk.push(it->lf); stk2.push(1);
            }else{
                // cnt==2: in-order
                vec.pb(it->val);
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

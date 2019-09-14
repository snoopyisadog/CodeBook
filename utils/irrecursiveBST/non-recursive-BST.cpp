#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define it_c(container) while(!container.empty())
// iterate a container

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
		if(NULL==root) return;
        it_c(que) que.pop();
        que.push(root);
        it_c(que){
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
            if(is_lf) pre->lf = it;
            else pre->rt = it;
        }
    }
    node *contains(int val){
        node *cur = root;
        while((NULL!=cur) && (cur->val != val)){
            if(val < cur->val) cur = cur->lf;
            if(val > cur->val) cur = cur->rt; // may enter both if-statements, but doesn't matter
        }
        return cur;
    }
    void del(int del_val){
        int is_lf;
        node *pre, *cur;
        cur = root;
        if(root == NULL) return;
        if(root->val == del_val){
            // special case, since root has no predecessors
            if(root->lf == NULL){
                pre = root;
                root = root->rt;
                delete(pre);
            }else if(root->rt == NULL){
                pre = root;
                root = root->lf;
                delete(pre);
            }else{
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
        }else if(cur->rt == NULL){
            if(is_lf){
                pre->lf = cur->lf;

            }else{
                pre->rt = cur->lf;
            }
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

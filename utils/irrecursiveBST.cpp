typedef struct A{
    struct A *lf, *rt;
    int val;
    void setval(int x){
        val = x;
        lf = rt = NULL;
    }
}node;

// auxiliary containers for traversing the BST
queue<node*> que;
stack<node*> stk;

typedef struct B{
    node *root, t;
    void init(){
		if(NULL==root) return;
        while(!que.empty()) que.pop();
        que.push(root);
        node *t;
        while(!que.empty()){
            t = que.front();
            que.pop();
            /*
			if(t==NULL) continue;
            que.push(t->lf);
            que.push(t->rt);
			*/
			if(NULL!=t->lf) que.push(t->lf);
			if(NULL!=t->rt) que.push(t->rt);
            free(t);
        }
        root = NULL;
    }
    void ins(int val){
        node *t = (node*)malloc(sizeof(node));
        t->setval(val);
        if(root == NULL) root = t;
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
            if(is_lf) pre->lf = t;
            else pre->rt = t;
        }
    }
    void printPreOrder(){
        while(!stk.empty()) stk.pop();
        stk.push(root);
        node *t;
        while(!stk.empty()){
            t = stk.top();
            stk.pop();
            if(t==NULL) continue;
            ans[ans_c++] = t->val;
            stk.push(t->rt);
            stk.push(t->lf);
        }
    }
}BST;

BST bst;

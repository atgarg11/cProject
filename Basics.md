# Binary Trees
## Level order Traversal
### 1.
* Maintain a que 
* iterate on que till que is not empty
* Maintain a count of nodes at a level and iterate for those nodes to complete the level within the out Loop.
```
   queue<TreeNode*> que;
        que.push(root);
        while ( !que.empty()) {
            len = que.size();
            while (len) {
                node = que.front();que.pop();
                len--;
                if ( node->left) {
                    que.push(node->left);
                } 
                if ( node->right) {
                    que.push(node->right);
                }
            }
            res.push_back(node->val);
        }
```

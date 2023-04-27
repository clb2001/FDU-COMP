void Convert(TreeNode *tree, vector<string> &outcome){
    queue<TreeNode*> q;
    q.push(tree);
    bool flag = false;
    while (!q.empty()){
        TreeNode *node = q.front();
        q.pop();
        outcome.push_back();
        int count = 0;
        while (node == nullptr && q.front() == nullptr){
            q.pop();
            outcome.push_back();
            if (q.empty()){
                count = 1;
                break;
            }
            else if (q.front() != nullptr){
                count = 1;
                flag = true;
                break;
            }
        }
        if (flag){
            outcome = "no";
            break;
        }
        if (count == 1){
            break;
        }
        q.push(node->left);
        q.push(node->right);
    } 
}
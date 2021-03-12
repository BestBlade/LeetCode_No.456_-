/* ------------------------------------------------------------------|
给定一个整数序列：a1, a2, ..., an，一个132模式的子序列 ai, aj, ak 被定义为：当 i < j < k 时，ai < ak < aj。设计一个算法，当给定有 n 个数字的序列时，验证这个序列中是否含有132模式的子序列。

注意：n 的值小于15000。

示例1:

输入: [1, 2, 3, 4]

输出: False

解释: 序列中不存在132模式的子序列。
示例 2:

输入: [3, 1, 4, 2]

输出: True

解释: 序列中有 1 个132模式的子序列： [1, 4, 2].
示例 3:

输入: [-1, 3, 2, 0]

输出: True

解释: 序列中有 3 个132模式的的子序列: [-1, 3, 2], [-1, 3, 0] 和 [-1, 2, 0].

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/132-pattern
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。|
-------------------------------------------------------------------*/

/*	单调栈法
*
*	执行用时：4 ms, 在所有 C++ 提交中击败了100.00%的用户
*	内存消耗：13.5 MB, 在所有 C++ 提交中击败了52.30%的用户
*/

#include <iostream>
#include <string> 
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <stack>
#include <queue>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}

};

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

bool find132pattern(vector<int>& nums) {
    if (nums.size() < 3) {
        return false;
    }
    //nums为j，min为i
    vector<int> min = nums;
    for (int i = 1; i < nums.size(); i++) {
        if (min[i - 1] < min[i]) {
            min[i] = min[i - 1];
        } 
    }
    //寻找k，满足i<k<j
    stack<int> st;
    for (int i = nums.size() - 1; i >= 0; --i) {
        if (nums[i] > min[i]) {
            //确保st.top() > min[i],即k > i
            while (!st.empty() && st.top() <= min[i]) {
                st.pop();
            }
            //同时如果k < j,返回true
            if (!st.empty() && st.top() < nums[i]) {
                return true;
            }
            st.emplace(nums[i]);
        }
    }

    return false;
}
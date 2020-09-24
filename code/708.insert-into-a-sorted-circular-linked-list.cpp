class Solution {
 public:
  Node* insert(Node* head, int insertVal) {
    std::function<void(Node*, Node*)> fold = [&](Node* prev, Node* curr) {
      if (prev == nullptr and head == nullptr) {
        std::exchange(head, new Node(insertVal));
        std::exchange(head->next, head);
        return;
      }
      else if (prev == nullptr and curr != nullptr) {
        if (curr->next == curr) {
          curr->next = new Node(insertVal, curr);
          return;
        }
        else {
          fold(curr, curr->next);
        }
      }
      else if (prev != nullptr and curr != nullptr) {
        if (curr->val >= insertVal and prev->val <= insertVal) {
          prev->next = new Node(insertVal, curr);
        }
        else if (curr->val < prev->val and insertVal <= curr->val) {
          prev->next = new Node(insertVal, curr);
        }
        else if (curr->val < prev->val and insertVal > prev->val) {
          prev->next = new Node(insertVal, curr);
        }
        else if (curr == head) {
          prev->next = new Node(insertVal, curr);
        }
        else {
          fold(curr, curr->next);
        }
      }
    };

    return fold(nullptr, head), head;
  }
};

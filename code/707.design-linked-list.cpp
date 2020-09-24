struct Node {
  int val;
  Node* next;
  Node() = default;
  explicit Node(int val) : val{val}, next{nullptr} {}
  explicit Node(int val, Node* next) : val{val}, next{next} {}
};

class MyLinkedList {
 private:
  Node* head;
  int len;

  Node* access(int index) {
    std::function<Node*(int, Node*)> fold = [&](int i, Node* n) {
      if (i == 0) {
        return n;
      }
      else {
        return fold(i - 1, n->next);
      }
    };
    return fold(index, head);
  };
    

  
 public:
  /** Initialize your data structure here. */
  MyLinkedList() : head{nullptr}, len{0} {}
    
  /** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
  int get(int index) {
    std::function<int(int, Node*)> fold = [&](int i, Node* n) {
      if (i == 0) {
        return n->val;
      }
      else {
        return fold(i - 1, n->next);
      }
    };
    if (index >= len) {
      return -1;
    }
    else {
      return fold(index, head);
    }
  }
    
  /** Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list. */
  void addAtHead(int val) {
    ++len;
    if (head == nullptr) {
      std::exchange(head, new Node(val));
    }
    else {
      std::exchange(head, new Node(val, head));
    }
  }
    
  /** Append a node of value val to the last element of the linked list. */
  void addAtTail(int val) {
    std::function<void(Node*)> fold = [&](Node* n) {
      if (n->next == nullptr) {
        ++len;
        n->next = new Node(val);
      }
      else {
        fold(n->next);
      }
    };

    if (head == nullptr) {
      addAtHead(val);
    }
    else {
      fold(head);
    }
  }
    
  /** Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted. */
  void addAtIndex(int index, int val) {
    if (index == len) {
      addAtTail(val);
    }
    else if (index > len) {
      // do nothing
    }
    else if (index == 0) {
      addAtHead(val);
    }
    else {
      ++len;
      const auto insert_point = access(index - 1);
      insert_point->next = new Node(val, insert_point->next);
    }
  }


  /** Delete the index-th node in the linked list, if the index is valid. */
  void deleteAtIndex(int index) {
    if (index == 0) {
      if (head != nullptr) {
        --len;
        std::exchange(head, head->next);
      }
    }
    else if (index >= len) {
      return;
    }
    else {
      --len;
      access(index - 1)->next = access(index)->next;
    }
  }
};

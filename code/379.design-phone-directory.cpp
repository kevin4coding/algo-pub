class PhoneDirectory {
 private:
  std::unordered_set<int> available_;
 public:
  /** Initialize your data structure here
      @param maxNumbers - The maximum numbers that can be stored in the phone directory. */
  PhoneDirectory(int maxNumbers) : available_{} {
    for (int i = 0; i < maxNumbers; ++i) {
      available_.emplace(i);
    }
  }
    
  /** Provide a number which is not assigned to anyone.
      @return - Return an available number. Return -1 if none is available. */
  int get() {
    if (std::empty(available_)) {
      return -1;
    }
    else {
      const auto result = *std::begin(available_);
      available_.erase(result);
      return result;
    }
  }
    
  /** Check if a number is available or not. */
  bool check(int number) {
    return available_.count(number);
  }
    
  /** Recycle or release a number. */
  void release(int number) {
    available_.emplace(number);
  }
};

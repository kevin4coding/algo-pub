class SubrectangleQueries {

 private:
  std::vector<std::vector<int>> data_;
 public:
  SubrectangleQueries(vector<vector<int>>& rectangle) {
    std::copy(std::begin(rectangle), std::end(rectangle), std::back_inserter(data_));
  }
    
  void updateSubrectangle(int row1, int col1, int row2, int col2, int newValue) {
    for (int r = row1; r <= row2; ++r) {
      for (int c = col1; c <= col2; ++c) {
        data_[r][c] = newValue;
      }
    }
  }
    
  int getValue(int row, int col) {
    return data_[row][col];
  }
};

/**
 * Your SubrectangleQueries object will be instantiated and called as such:
 * SubrectangleQueries* obj = new SubrectangleQueries(rectangle);
 * obj->updateSubrectangle(row1,col1,row2,col2,newValue);
 * int param_2 = obj->getValue(row,col);
 */

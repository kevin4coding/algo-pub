class FileSharing {
  std::set<int> available_;
  std::unordered_map<int, std::unordered_set<int>> file_user_map_;
  std::unordered_map<int, std::unordered_set<int>> user_file_map_;
  
 public:
  FileSharing(int m) {
    for (int i = 1; i <= m; ++i) {
      available_.emplace(i);
    }
  }
    
  int join(vector<int> ownedChunks) {
    const auto uid = *std::begin(available_);
    available_.erase(uid);
    for (const auto fid : ownedChunks) {
      file_user_map_[fid].emplace(uid);
      user_file_map_[uid].emplace(fid);
    }
    return uid;
  }
    
  void leave(int userID) {
    available_.emplace(userID);
    for (auto fid : user_file_map_[userID]) {
      file_user_map_[fid].erase(userID);
    }
    user_file_map_.erase(userID);
  }
    
  vector<int> request(int userID, int chunkID) {
    const auto result = [&](std::vector<int> self = {}) {
      std::copy(std::begin(file_user_map_[chunkID]), std::end(file_user_map_[chunkID]), std::back_inserter(self));
      std::sort(std::begin(self), std::end(self));
      return self;
    }();

    if (not std::empty(result)) {
      user_file_map_[userID].emplace(chunkID);
      file_user_map_[chunkID].emplace(userID);
    }
    
    return result;
  }
};


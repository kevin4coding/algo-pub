class Solution {
 public:
  int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
    const int L_SPLIT = (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5);
    const int R_SPLIT = (1 << 6) | (1 << 7) | (1 << 8) | (1 << 9);
    const int MIDDLE = (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7);
    
    auto calc_seat = [&](int seat_map) {
      if ((seat_map & L_SPLIT) == 0 and (seat_map & R_SPLIT) == 0) {
        return 2;
      }
      else if ((seat_map & L_SPLIT) == 0 or (seat_map & R_SPLIT) == 0) {
        return 1;
      }
      else if ((seat_map & MIDDLE) == 0) {
        return 1;
      }
      else {
        return 0;
      }
    };
    
    const auto occupied_seat_map = [&](std::unordered_map<int, int> self = {}) {
      for (const auto & seat : reservedSeats) {
        const auto [row, col] = std::pair{seat[0], seat[1]};
        self[row] |= (1 << col);
      }
      return self;
    }();


    const auto cnt_occupied = [&](int acc = 0) {
      for (const auto [row, seat_map] : occupied_seat_map) {
        acc += calc_seat(seat_map);
      }
      return acc;
    }();

    const auto cnt_unoccupied = 2 * (n - std::size(occupied_seat_map));

    const auto solution = cnt_occupied + cnt_unoccupied;

    return solution;
  }
};

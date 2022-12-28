import math
from copy import deepcopy
import random


class GO:
    def __init__(self, n):
        """
        Go game.

        :param n: size of the board n*n
        """
        self.size = n
        #self.previous_board = None # Store the previous board
        self.X_move = True # X chess plays first
        self.died_pieces = [] # Intialize died pieces to be empty
        self.n_move = 0 # Trace the number of moves
        self.max_move = n * n - 1 # The max movement of a Go game
        self.komi = n/2 # Komi rule
        self.verbose = False # Verbose only when there is a manual player

    def init_board(self, n):
        '''
        Initialize a board with size n*n.

        :param n: width and height of the board.
        :return: None.
        '''
        board = [[0 for x in range(n)] for y in range(n)]  # Empty space marked as 0
        # 'X' pieces marked as 1
        # 'O' pieces marked as 2
        self.board = board
        self.previous_board = deepcopy(board)

    def set_board(self, piece_type, previous_board, board):
        '''
        Initialize board status.
        :param previous_board: previous board state.
        :param board: current board state.
        :return: None.
        '''

        # 'X' pieces marked as 1
        # 'O' pieces marked as 2

        for i in range(self.size):
            for j in range(self.size):
                if previous_board[i][j] == piece_type and board[i][j] != piece_type:
                    self.died_pieces.append((i, j))

        # self.piece_type = piece_type
        self.previous_board = previous_board
        self.board = board

    def compare_board(self, board1, board2):
        for i in range(self.size):
            for j in range(self.size):
                if board1[i][j] != board2[i][j]:
                    return False
        return True

    def copy_board(self):
        '''
        Copy the current board for potential testing.

        :param: None.
        :return: the copied board instance.
        '''
        return deepcopy(self)

    def detect_neighbor(self, i, j):
        '''
        Detect all the neighbors of a given stone.

        :param i: row number of the board.
        :param j: column number of the board.
        :return: a list containing the neighbors row and column (row, column) of position (i, j).
        '''
        board = self.board
        neighbors = []
        # Detect borders and add neighbor coordinates
        if i > 0: neighbors.append((i-1, j))
        if i < len(board) - 1: neighbors.append((i+1, j))
        if j > 0: neighbors.append((i, j-1))
        if j < len(board) - 1: neighbors.append((i, j+1))
        return neighbors

    def detect_neighbor_ally(self, i, j):
        '''
        Detect the neighbor allies of a given stone.

        :param i: row number of the board.
        :param j: column number of the board.
        :return: a list containing the neighbored allies row and column (row, column) of position (i, j).
        '''
        board = self.board
        neighbors = self.detect_neighbor(i, j)  # Detect neighbors
        group_allies = []
        # Iterate through neighbors
        for piece in neighbors:
            # Add to allies list if having the same color
            if board[piece[0]][piece[1]] == board[i][j]:
                group_allies.append(piece)
        return group_allies

    def ally_dfs(self, i, j):
        '''
        Using DFS to search for all allies of a given stone.

        :param i: row number of the board.
        :param j: column number of the board.
        :return: a list containing the all allies row and column (row, column) of position (i, j).
        '''
        stack = [(i, j)]  # stack for DFS serach
        ally_members = []  # record allies positions during the search
        while stack:
            piece = stack.pop()
            ally_members.append(piece)
            neighbor_allies = self.detect_neighbor_ally(piece[0], piece[1])
            for ally in neighbor_allies:
                if ally not in stack and ally not in ally_members:
                    stack.append(ally)
        return ally_members

    def find_liberty(self, i, j):
        '''
        Find liberty of a given stone. If a group of allied stones has no liberty, they all die.

        :param i: row number of the board.
        :param j: column number of the board.
        :return: boolean indicating whether the given stone still has liberty.
        '''
        board = self.board
        ally_members = self.ally_dfs(i, j)
        for member in ally_members:
            neighbors = self.detect_neighbor(member[0], member[1])
            for piece in neighbors:
                # If there is empty space around a piece, it has liberty
                if board[piece[0]][piece[1]] == 0:
                    return True
        # If none of the pieces in a allied group has an empty space, it has no liberty
        return False

    def find_died_pieces(self, piece_type):
        '''
        Find the died stones that has no liberty in the board for a given piece type.

        :param piece_type: 1('X') or 2('O').
        :return: a list containing the dead pieces row and column(row, column).
        '''
        board = self.board
        died_pieces = []

        for i in range(len(board)):
            for j in range(len(board)):
                # Check if there is a piece at this position:
                if board[i][j] == piece_type:
                    # The piece die if it has no liberty
                    if not self.find_liberty(i, j):
                        died_pieces.append((i,j))
        return died_pieces

    def remove_died_pieces(self, piece_type):
        '''
        Remove the dead stones in the board.

        :param piece_type: 1('X') or 2('O').
        :return: locations of dead pieces.
        '''

        died_pieces = self.find_died_pieces(piece_type)
        if not died_pieces: return []
        self.remove_certain_pieces(died_pieces)
        return died_pieces

    def remove_certain_pieces(self, positions):
        '''
        Remove the stones of certain locations.

        :param positions: a list containing the pieces to be removed row and column(row, column)
        :return: None.
        '''
        board = self.board
        for piece in positions:
            board[piece[0]][piece[1]] = 0
        self.update_board(board)

    def place_chess(self, i, j, piece_type):
        '''
        Place a chess stone in the board.

        :param i: row number of the board.
        :param j: column number of the board.
        :param piece_type: 1('X') or 2('O').
        :return: boolean indicating whether the placement is valid.
        '''
        board = self.board

        valid_place = self.valid_place_check(i, j, piece_type)
        if not valid_place:
            return False
        self.previous_board = deepcopy(board)
        board[i][j] = piece_type
        self.update_board(board)
        # Remove the following line for HW2 CS561 S2020
        # self.n_move += 1
        return True

    def valid_place_check(self, i, j, piece_type, test_check=False):
        '''
        Check whether a placement is valid.

        :param i: row number of the board.
        :param j: column number of the board.
        :param piece_type: 1(white piece) or 2(black piece).
        :param test_check: boolean if it's a test check.
        :return: boolean indicating whether the placement is valid.
        '''
        board = self.board
        verbose = self.verbose
        if test_check:
            verbose = False

        # Check if the place is in the board range
        if not (i >= 0 and i < len(board)):
            if verbose:
                print(('Invalid placement. row should be in the range 1 to {}.').format(len(board) - 1))
            return False
        if not (j >= 0 and j < len(board)):
            if verbose:
                print(('Invalid placement. column should be in the range 1 to {}.').format(len(board) - 1))
            return False

        # Check if the place already has a piece
        if board[i][j] != 0:
            if verbose:
                print('Invalid placement. There is already a chess in this position.')
            return False

        # Copy the board for testing
        test_go = self.copy_board()
        test_board = test_go.board

        # Check if the place has liberty
        test_board[i][j] = piece_type
        test_go.update_board(test_board)
        if test_go.find_liberty(i, j):
            return True

        # If not, remove the died pieces of opponent and check again
        test_go.remove_died_pieces(3 - piece_type)
        if not test_go.find_liberty(i, j):
            if verbose:
                print('Invalid placement. No liberty found in this position.')
            return False

        # Check special case: repeat placement causing the repeat board state (KO rule)
        else:
            if self.died_pieces and self.compare_board(self.previous_board, test_go.board):
                if verbose:
                    print('Invalid placement. A repeat move not permitted by the KO rule.')
                return False
        return True

    def update_board(self, new_board):
        '''
        Update the board with new_board

        :param new_board: new board.
        :return: None.
        '''
        self.board = new_board

    def visualize_board(self):
        '''
        Visualize the board.

        :return: None
        '''
        board = self.board

        print('-' * len(board) * 2)
        for i in range(len(board)):
            for j in range(len(board)):
                if board[i][j] == 0:
                    print(' ', end=' ')
                elif board[i][j] == 1:
                    print('X', end=' ')
                else:
                    print('O', end=' ')
            print()
        print('-' * len(board) * 2)

    def game_end(self, piece_type, action="MOVE"):
        '''
        Check if the game should end.

        :param piece_type: 1('X') or 2('O').
        :param action: "MOVE" or "PASS".
        :return: boolean indicating whether the game should end.
        '''

        # Case 1: max move reached
        if self.n_move >= self.max_move:
            return True
        # Case 2: two players all pass the move.
        if self.compare_board(self.previous_board, self.board) and action == "PASS":
            return True
        return False

    def score(self, piece_type):
        '''
        Get score of a player by counting the number of stones.

        :param piece_type: 1('X') or 2('O').
        :return: boolean indicating whether the game should end.
        '''

        board = self.board
        cnt = 0
        for i in range(self.size):
            for j in range(self.size):
                if board[i][j] == piece_type:
                    cnt += 1
        return cnt

    def judge_winner(self):
        '''
        Judge the winner of the game by number of pieces for each player.

        :param: None.
        :return: piece type of winner of the game (0 if it's a tie).
        '''

        cnt_1 = self.score(1)
        cnt_2 = self.score(2)
        if cnt_1 > cnt_2 + self.komi: return 1
        elif cnt_1 < cnt_2 + self.komi: return 2
        else: return 0

    def play(self, player1, player2, verbose=False):
        '''
        The game starts!

        :param player1: Player instance.
        :param player2: Player instance.
        :param verbose: whether print input hint and error information
        :return: piece type of winner of the game (0 if it's a tie).
        '''
        self.init_board(self.size)
        # Print input hints and error message if there is a manual player
        if player1.type == 'manual' or player2.type == 'manual':
            self.verbose = True
            print('----------Input "exit" to exit the program----------')
            print('X stands for black chess, O stands for white chess.')
            self.visualize_board()

        verbose = self.verbose
        # Game starts!
        while 1:
            piece_type = 1 if self.X_move else 2

            # Judge if the game should end
            if self.game_end(piece_type):
                result = self.judge_winner()
                if verbose:
                    print('Game ended.')
                    if result == 0:
                        print('The game is a tie.')
                    else:
                        print('The winner is {}'.format('X' if result == 1 else 'O'))
                return result

            if verbose:
                player = "X" if piece_type == 1 else "O"
                print(player + " makes move...")

            # Game continues
            if piece_type == 1: action = player1.get_input(self, piece_type)
            else: action = player2.get_input(self, piece_type)

            if verbose:
                player = "X" if piece_type == 1 else "O"
                print(action)

            if action != "PASS":
                # If invalid input, continue the loop. Else it places a chess on the board.
                if not self.place_chess(action[0], action[1], piece_type):
                    if verbose:
                        self.visualize_board()
                    continue

                self.died_pieces = self.remove_died_pieces(3 - piece_type) # Remove the dead pieces of opponent
            else:
                self.previous_board = deepcopy(self.board)

            if verbose:
                self.visualize_board() # Visualize the board again
                print()

            self.n_move += 1
            self.X_move = not self.X_move # Players take turn


class CustomAlphaBetaPlayer():
    def __init__(self):
        self.type = 'custom'

    def get_possible_moves(self, go, piece_type):
        possible_placements = []
        for i in range(go.size):
            for j in range(go.size):
                if go.valid_place_check(i, j, piece_type, test_check=True):
                    possible_placements.append((i, j))

        random.shuffle(possible_placements)
        return possible_placements

    def remove_instant_death_moves(self, go, piece_type, possible_moves):
        moves_to_remove = set()

        for move in possible_moves:
            # Apply move to copy of board
            copied_board = go.copy_board()
            self.apply_move_to_board(copied_board, move, piece_type)

            opp_moves = self.get_possible_moves(copied_board, 3-piece_type)

            for opp_move in opp_moves:
                # Place opponent move
                copied_board.board[opp_move[0]][opp_move[1]] = 3-piece_type

                # Get died pieces
                died_pieces = copied_board.find_died_pieces(piece_type)

                if move in died_pieces:
                    # Last move instantly dies to this oppoent move
                    moves_to_remove.add(move)
                    break

                # Remove opponent move from board before trying next one
                copied_board.board[opp_move[0]][opp_move[1]] = 0

        for move in moves_to_remove:
            possible_moves.remove(move)

        return possible_moves

    def find_cluster_liberties(self, go, cluster):
        liberties = set()

        for cluster_piece in cluster:
            neighbors = go.detect_neighbor(cluster_piece[0], cluster_piece[1])
            for piece in neighbors:
                if board[piece[0]][piece[1]] == 0:
                    liberties.add((piece[0], piece[1]))

        return liberties

    def get_num_liberties(self, go, piece_type):
        """
        Finding all liberties on board for a specific piece type.
        We want heuristic to emphasize having more liberties in position. This will help.
        """
        explored = set()
        liberties = set()

        for i in range(go.size):
            for j in range(go.size):
                if go.board[i][j] in explored:
                    continue
                if go.board[i][j] == piece_type:
                    explored.add((i, j))
                    cluster = go.ally_dfs(i, j)
                    explored.update(set(cluster))
                    cluster_liberties = self.find_cluster_liberties(go, cluster)
                    liberties.update(set(cluster_liberties))

        return len(liberties)

    def heuristic(self, go, piece_type):
        """
        Heuristic function to evaluate value of a position
        :return: utility value of position.
        """
        # TODO: Make this a better function
        # It is currently naive and returns current difference between my pieces and opponent pieces
        # Also factors in komi
        opponent_count, my_count = 0, 0
        my_pieces = set()
        opponent_pieces = set()
        for i in range(go.size):
            for j in range(go.size):
                if go.board[i][j] == piece_type:
                    my_count += 1
                    my_pieces.add((i, j))
                elif go.board[i][j] == 3 - piece_type:
                    opponent_count += 1
                    opponent_pieces.add((i, j))

        # Account for komi which goes to the player with piece type 2
        if piece_type == 2:
            my_count += go.komi
        else:
            opponent_count += go.komi

        my_liberties = self.get_num_liberties(go, my_pieces)
        opponent_liberties = self.get_num_liberties(go, opponent_pieces)

        return 50 * (my_count - opponent_count) + (my_liberties - opponent_liberties)

    def is_winning(self, go, piece_type):
        opponent_count, my_count = 0, 0
        for i in range(go.size):
            for j in range(go.size):
                if go.board[i][j] == piece_type:
                    my_count += 1
                elif go.board[i][j] == 3 - piece_type:
                    opponent_count += 1

        # Account for komi which goes to the player with piece type 2
        if piece_type == 2:
            my_count += go.komi
        else:
            opponent_count += go.komi

        return my_count > opponent_count

    def total_piece_count(self, go):
        count = 0
        for i in range(go.size):
            for j in range(go.size):
                if go.board[i][j] != 0:
                    count += 1

        return count

    def move(self, go, piece_type):
        """
        Determine next move to make.

        :param go: Go instance.
        :param piece_type: 1('X') or 2('O').
        :return: (row, column) coordinate of input.
        """
        if go.board == go.previous_board and go.board and self.is_winning(go, piece_type):
            # Automatically take chance to end game with win (don't pass on first move)
            return "PASS"

        piece_count = self.total_piece_count(go)
        possible_moves = self.get_possible_moves(go, piece_type)
        possible_moves = self.remove_instant_death_moves(go, piece_type, possible_moves)

        if piece_count <= 1:
            if go.board[2][2] == 0:
                # Try to use center of board
                return (2, 2)
            else:
                return (1, 1)
        elif len(possible_moves) >= 15:
            # Smart play will first take over center
            center = (2, 2)

            # Then try taking over direct corners
            direct_corners = [(1, 1), (1, 3), (3, 1), (3, 3)]

            # Then move out to alternating squares on edges
            edge_corners = [(2, 0), (2, 4), (0, 2), (4, 2)]

            # This checker pattern, although a bit naive, should get as many "eye" formations as possible
            # It seems to perform decently well without building the eye stuff into the heuristic which is
            # another option

            if center in possible_moves:
                return center

            for move in direct_corners:
                if move in possible_moves:
                    return move

            for move in edge_corners:
                if move in possible_moves:
                    return move

        move = self.find_max(go, -math.inf, math.inf, piece_type, 0, possible_moves=possible_moves)
        return move

    def apply_move_to_board(self, go, move, piece_type):
        # Set previous board to current board
        go.previous_board = deepcopy(go.board)

        # Make move
        if move != "PASS":
            go.place_chess(move[0], move[1], piece_type)
            go.remove_died_pieces(3 - piece_type)

    def find_max(self, go, alpha, beta, piece_type, depth, possible_moves=None):
        if depth >= 4:
            # Terminal state, return value of position
            return self.heuristic(go, piece_type)

        if not possible_moves:
            possible_moves = self.get_possible_moves(go, piece_type)
            possible_moves = self.remove_instant_death_moves(go, piece_type, possible_moves)

        if not possible_moves:
            if depth == 0:
                # No valid moves at top level just pass since invalid move ends game
                return "PASS"
            else:
                # Assume pass
                return self.heuristic(go, piece_type)

        v = -math.inf
        best_move = None

        for move in possible_moves:
            # Apply move to copy of board
            copied_board = go.copy_board()
            self.apply_move_to_board(copied_board, move, piece_type)

            # Find min value
            min_val = self.find_min(copied_board, alpha, beta, 3 - piece_type, depth + 1)

            if min_val > v:
                # This move was better than current best move
                best_move = move

            v = max(v, min_val)

            # Handle alpha-beta pruning
            if v >= beta:
                return v

            alpha = max(alpha, v)

        if depth == 0:
            # Just need the actual move at top level call
            return best_move
        else:
            # Return utility value at lower levels
            return v

    def find_min(self, go, alpha, beta, piece_type, depth):
        if depth >= 4:
            # Terminal state, return value of position
            # Be sure to calculate using our piece type rather than opponent's
            return self.heuristic(go, 3 - piece_type)

        possible_moves = self.get_possible_moves(go, piece_type)

        if not possible_moves:
            # Basically assume they'll pass
            return self.heuristic(go, 3 - piece_type)

        v = math.inf

        for move in possible_moves:
            # Apply move to copy of board
            copied_board = go.copy_board()
            self.apply_move_to_board(copied_board, move, piece_type)

            # Find max value
            max_val = self.find_max(copied_board, alpha, beta, 3 - piece_type, depth + 1)

            v = min(v, max_val)

            # Handle alpha-beta pruning
            if v <= alpha:
                return v

            beta = min(beta, v)

        return v


def read_input(n, path="input.txt"):
    with open(path, 'r') as f:
        lines = f.readlines()

        piece_type = int(lines[0])

        previous_board = [[int(x) for x in line.rstrip('\n')] for line in lines[1:n+1]]
        board = [[int(x) for x in line.rstrip('\n')] for line in lines[n+1: 2*n+1]]

        return piece_type, previous_board, board


def write_output(result, path="output.txt"):
    res = ""
    if result == "PASS":
        res = "PASS"
    else:
        res += str(result[0]) + ',' + str(result[1])

    with open(path, 'w') as f:
        f.write(res)


if __name__ == "__main__":
    N = 5
    piece_type, previous_board, board = read_input(N)
    go = GO(N)
    go.set_board(piece_type, previous_board, board)
    player = CustomAlphaBetaPlayer()
    action = player.move(go, piece_type)
    write_output(action)
